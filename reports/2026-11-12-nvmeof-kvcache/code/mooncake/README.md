# Mooncake source reading subset

Source: https://github.com/kvcache-ai/Mooncake
Pinned commit: dded3a2e49965657d78b7345e4b7986521c36073 (2026-11-12)
License: Apache-2.0, LICENSE-APACHE included.
Unmodified file: mooncake-store/include/types.h (stored as types.h).
This is a source reading subset, not a buildable copy or a GitHub fork.

Relevant verified definitions: NoFSegment; DEFAULT_NOF_* heartbeat/eviction parameters; NOF_REGISTRATION_STUCK; CHECKSUM_MISMATCH; REPLICA_IS_NOT_READY; LEASE_EXPIRED.
These definitions show that the current code already represents such states. They do not prove all execution paths implement any particular end-to-end recovery guarantee.
