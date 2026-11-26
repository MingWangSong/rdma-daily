# 第 04 讲 · FaRM：一次 RDMA READ，怎样知道没有读到一半新、一半旧？

2026-11-26 · 约 25 分钟 · 经典回顾

**FaRM: Fast Remote Memory** · USENIX NSDI ’14 正式论文集，2014 年 4 月 2–4 日，pp. 401–414。Aleksandar Dragojević、Dushyanth Narayanan、Orion Hodson、Miguel Castro（Microsoft Research）。

[打开 HTML 讲义](https://mingwangsong.github.io/rdma-daily/2026-11-26/) · [上一讲 Pilaf](../2026-11-25/) · [资料索引](papers/farm/REFERENCES.md)

1. [§3.5 / 图 8](https://www.usenix.org/system/files/conference/nsdi14/nsdi14-paper-dragojevic.pdf#page=8)：一条单边 READ 搬完整对象；读端检查头部锁状态与版本、每行低位版本和用时，调用方还要核对对象代号。成功完成 READ 本身不能证明对象一致。
2. 写端先锁、标记行版本、改数据，再发布新版本。缓存一致 DMA 和写入次序是必要前提；低位回绕要用可验证的时限约束。
3. [§4.2 / 图 12](https://www.usenix.org/system/files/conference/nsdi14/nsdi14-paper-dragojevic.pdf#page=11)：20 台、均匀分布、32 B 值时约 1.46 亿次查询/秒、35 μs；有热点时约 1 亿以上、51 μs。不是 P99，也不能把系统级结果全部归因于版本设计。
4. 练习：头和后两行的低位版本一致、但对象代号与指针不同，能交付吗？HTML 中有可展开答案。下一讲 FaSST。
