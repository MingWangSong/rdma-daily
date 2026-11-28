# 06 · Tailwind：写进备机多少，才算有效？

[打开图文导读](https://mingwangsong.github.io/rdma-daily/2026-11-28/) · [上一课 FaSST](../2026-11-27/) · [参考资料](papers/tailwind/REFERENCES.md)

**25 分钟。** USENIX ATC 2018 正式论文：Yacine Taleb、Gabriel Antoniu（Rennes / Inria / CNRS / IRISA），Ryan Stutsman（犹他大学），Toni Cortes（BSC / UPC）。

- 图 3：打开和关闭缓冲区用 RPC；单边 RDMA WRITE 负责日常日志复制。
- 图 5：一条记录只有正文和校验项都完整，才可推进可恢复前缀。能恢复不意味着客户端已收到回复，也不意味着已落盘。
- 图 7：论文报告在 500 KOp/s 下，PUT 的中位延迟 32 → 16 µs、P99 78 → 28 µs，对照原 RAMCloud RPC 复制；不要外推到 SSD 写延迟。
- 下一课：RAMCloud 并行重建日志对应的对象。
