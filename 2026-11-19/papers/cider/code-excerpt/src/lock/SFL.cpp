#include <endian.h>
#include "BusyWait.h"
#include "Common.h"
#include "DSM.h"
#include "GlobalAddress.h"
#include "QueueLock.h"
/**
    volatile uint64_t RdrCnt : 10;
    volatile uint64_t Epoch : 1;
    volatile uint64_t nodeId : 5;
    volatile uint64_t offset : 48;
    volatile uint64_t RelCnt : 64; high64
*/
extern thread_local MCS_LOCK_ALLOCATOR mla;
DSM* SHIFTLOCK::dsm;
void SHIFTLOCK::LOCK_INIT_DSM(DSM* x) {
    dsm = x;
}
void SHIFTLOCK::LOCK_INIT_ALLOC() {
    mla.INIT_DSM(dsm);
}
SHIFTLOCK::SHIFTLOCK(GlobalAddress addr) {
    MNlock = addr;
    addr.offset += 8;
    MNlock_high = addr;
}
void SHIFTLOCK::lock(bool mode, CoroPull* sink) {
    curMode = mode;
    hoctx = (SFLHO_CONTEXT*)mla.allocLockBuffer();
    hoctx->lockBuffer.val = 0;
    hoctx->lockBuffer.valid = 1;
    hoctx->lockBytes.op = 0;
    int wcnt = 0;
    if (curMode == ModeShare) {
        // uint64_t* bf = (uint64_t*)dsm->get_rbuf(0).get_KV_buffer();
        // dsm->faa_boundary_sync(MNlock, 1, bf, 9, sink);

        uint64_t addv[2], addm[2];
        uint64_t* bf = (uint64_t*)dsm->get_rbuf(0).get_KV_buffer();
        addv[0] = 1, addv[1] = 0;
        addm[0] = (1ull << 9), addm[1] = 0;
        dsm->faa128_boundray_sync(MNlock, addv, bf, addm, sink);

        SHIFTLOCK_CONTENT* entry = (SHIFTLOCK_CONTENT*)bf;
        if (entry->nodeId == 0 && entry->offset == 0) {
            return;
        }
        uint64_t curEpoch = entry->Epoch;

        while (1) {
            uint64_t* bf = (uint64_t*)dsm->get_rbuf(0).get_KV_buffer();
            dsm->read_sync((char*)bf, MNlock, 16, sink);
            entry = (SHIFTLOCK_CONTENT*)bf;
            if (curEpoch != entry->Epoch)
                return;
            busy_wait_us_clock(RemoteWait);
        }
    }
    // ModeExclusive

    uint64_t cmpv[2], swpv[2], cmpm[2], swpm[2];
    uint64_t* bf = (uint64_t*)dsm->get_rbuf(0).get_KV_buffer();
    cmpm[0] = cmpm[1] = 0;
    swpm[0] = (~0x7ffull), swpm[1] = 0;
    SHIFTLOCK_CONTENT* val = (SHIFTLOCK_CONTENT*)swpv;
    GlobalAddress glb = dsm->localToGlobal(&(hoctx->lockBuffer));
    val->nodeId = glb.nodeID, val->offset = glb.offset;

    dsm->cas128_mask_sync(MNlock, cmpv, swpv, bf, cmpm, swpm, sink);
    SHIFTLOCK_CONTENT entry = *(SHIFTLOCK_CONTENT*)bf;

    curRelCnt = entry.RelCnt;
    consWrt = 0;
    epoch = entry.Epoch;
    if (entry.nodeId != 0 || entry.offset != 0) {
        // wait for writer
        GlobalAddress pred = {entry.nodeId, entry.offset};
        GlobalAddress lockByteGlobal =
            (dsm->localToGlobal(&(hoctx->lockBytes)));
        SFL_LOCK_NODE_PART1 lc{lockByteGlobal.nodeID, lockByteGlobal.offset, 1,
                               0};
        uint64_t* tmp = (dsm->get_rbuf(sink)).get_cas_buffer();

        if (!dsm->cas_mask_sync(pred, VALID_BIT, lc.to_uint64(), tmp, VALID_BIT,
                                GLOBAL_ADDRESS_SET_MASK, sink))
            assert(0);
        volatile SFL_LOCKBYTE* lockByte = &(hoctx->lockBytes);
        while (!lockByte->op) {
        }
        if (lockByte->op == 1) {  // modechanged
            // return;               // debug
            uint64_t expect = lockByte->curRelCnt;
            while (1) {
                uint64_t* bf = (uint64_t*)dsm->get_rbuf(0).get_KV_buffer();
                dsm->read_sync((char*)bf, MNlock_high, 8, sink);
                // fault tolerance TODO
                if (*bf == expect) {
                    curRelCnt = expect;
                    epoch = lockByte->expectedEpoch;
                    return;
                }
                busy_wait_us_clock(RemoteWait);
            }
        } else if (lockByte->op == 2) {  // handover
            curRelCnt = lockByte->curRelCnt, consWrt = lockByte->consWrt;
            epoch = lockByte->expectedEpoch;
            return;
        }

    } else if (entry.RdrCnt != 0) {
        // wait for reader
        uint64_t expect = entry.RdrCnt + entry.RelCnt;
        while (1) {
            uint64_t* bf = (uint64_t*)dsm->get_rbuf(0).get_KV_buffer();
            dsm->read_sync((char*)bf, MNlock, 16, sink);
            SHIFTLOCK_CONTENT curEntry = *(SHIFTLOCK_CONTENT*)bf;
            if (curEntry.RelCnt == expect) {
                curRelCnt = expect;
                return;
            }
            busy_wait_us_clock(RemoteWait);
        }
    }
    return;
}
void SHIFTLOCK::unlock(CoroPull* sink) {
    if (curMode == ModeShare) {
        uint64_t addv[2], addm[2];
        uint64_t* bf = (uint64_t*)dsm->get_rbuf(0).get_KV_buffer();
        addv[0] = 0x3ff, addv[1] = 1;
        addm[0] = (1ull << 9), addm[1] = (1ull << 63);
        dsm->faa128_boundray_sync(MNlock, addv, bf, addm, sink);
        mla.deAllocLockBuffer((uint64_t*)hoctx);
        return;
    }
    // ModeExclusive

    SFL_LOCK_NODE_PART1* lockBuffer = &(hoctx->lockBuffer);
    if (lockBuffer->isUnSet()) {
        SHIFTLOCK_CONTENT eql, val;
        uint64_t cmpm[2], swpm[2];
        GlobalAddress glb = dsm->localToGlobal(lockBuffer);
        eql.nodeId = glb.nodeID, eql.offset = glb.offset;
        val.nodeId = val.offset = 0;
        val.RelCnt = curRelCnt + 1, val.Epoch = 1 - epoch;
        cmpm[0] = (~0x7ffull), cmpm[1] = 0;
        swpm[0] = (~0x3ffull), swpm[1] = (~0ull);
        // uint64_t* cmpv = (uint64_t*)&eql;
        uint64_t* tmp = (uint64_t*)(dsm->get_rbuf(sink)).get_KV_buffer();
        if (dsm->cas128_mask_sync(MNlock, (uint64_t*)&eql, (uint64_t*)&val, tmp,
                                  cmpm, swpm, sink)) {  // no follower
            SHIFTLOCK_CONTENT* entry = (SHIFTLOCK_CONTENT*)tmp;
            lockBuffer->val = 0;
            mla.deAllocLockBuffer((uint64_t*)hoctx);
            return;
        }
    }
    // rare case: wait for follower

    while (lockBuffer->isUnSet()) {
    }
    GlobalAddress succ = lockBuffer->toGlobalAddress();
    if (consWrt == HO_LIM) {  // ModeChanged
        uint64_t addv[2], addm[2];
        uint64_t* bf = (uint64_t*)dsm->get_rbuf(0).get_KV_buffer();
        addv[0] = (1 << 10), addv[1] = 1;
        addm[0] = (1ull << 10), addm[1] = (1ull << 63);
        dsm->faa128_boundray_sync(MNlock, addv, bf, addm, sink);

        SHIFTLOCK_CONTENT* entry = (SHIFTLOCK_CONTENT*)bf;
        uint64_t expect = entry->RelCnt + entry->RdrCnt + 1;

        uint64_t cmpv[2], swpv[2], cmpm[2], swpm[2];
        bf = (uint64_t*)dsm->get_rbuf(0).get_KV_buffer();
        cmpm[0] = cmpm[1] = 0;
        swpm[0] = swpm[1] = (~0ull);
        SFL_LOCKBYTE* slb = (SFL_LOCKBYTE*)swpv;
        slb->op = 1;
        slb->curRelCnt = expect;
        slb->expectedEpoch = epoch ^ 1;
        dsm->cas128_mask_sync(succ, cmpv, swpv, bf, cmpm, swpm, sink);
        mla.deAllocLockBuffer((uint64_t*)hoctx);
        return;
    }
    // Handover

    uint64_t* bf;
    // debug
    // bf = (uint64_t*)dsm->get_rbuf(0).get_KV_buffer();
    // dsm->faa_boundary_sync(MNlock_high, 1, bf, 63, sink);
    uint64_t addv[2], addm[2];
    bf = (uint64_t*)dsm->get_rbuf(0).get_KV_buffer();
    addv[0] = 0, addv[1] = 1;
    addm[0] = 0, addm[1] = (1ull << 63);
    dsm->faa128_boundray_sync(MNlock, addv, bf, addm, sink);

    uint64_t cmpv[2], swpv[2], cmpm[2], swpm[2];
    bf = (uint64_t*)dsm->get_rbuf(0).get_KV_buffer();
    cmpm[0] = cmpm[1] = 0;
    swpm[0] = swpm[1] = (~0ull);
    SFL_LOCKBYTE* slb = (SFL_LOCKBYTE*)swpv;
    slb->op = 2;
    slb->consWrt = consWrt + 1;
    slb->curRelCnt = curRelCnt + 1;
    slb->expectedEpoch = epoch;
    dsm->cas128_mask_sync(succ, cmpv, swpv, bf, cmpm, swpm, sink);
    mla.deAllocLockBuffer((uint64_t*)hoctx);
}