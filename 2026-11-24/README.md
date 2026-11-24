# 第 02 讲 · 敲一次门铃，发两个响应

[打开导读 HTML](https://mingwangsong.github.io/rdma-daily/2026-11-24/) · [上一讲](https://mingwangsong.github.io/rdma-daily/2026-11-23/)

**24 分钟：**沿缓存服务器的响应路径读一遍 QP、WQE、Doorbell、CQE。第 4 页图 4 练习数 PCIe 上 CPU 写与设备读的箭头，然后用第 8 页图 9 分清单核与整机吞吐。

- 经典回顾：Anuj Kalia、David G. Andersen（卡内基梅隆大学），Michael Kaminsky（Intel Labs），《Design Guidelines for High Performance RDMA Systems》，USENIX ATC，2016 年 6 月 22–24 日，正式论文集 pp. 437–450，最佳学生论文。
- 读图路线：[图 4、§2.2.2](https://www.cs.cmu.edu/~xia/resources/Documents/kalia-usenix2016.pdf#page=4) → [§3.1、图 5（选读）](https://www.cs.cmu.edu/~xia/resources/Documents/kalia-usenix2016.pdf#page=5) → [图 9](https://www.cs.cmu.edu/~xia/resources/Documents/kalia-usenix2016.pdf#page=8) 与 [§4.3.1](https://www.cs.cmu.edu/~xia/resources/Documents/kalia-usenix2016.pdf#page=9)。
- HERD 小键值实验：逐条与批量提交的单核吞吐分别为 6.7 和 12.3 Mrps，整机峰值为 72.8 和 98.3 Mrps。READ-based 是模型线，不是运行 Pilaf 或 FaRM 的测量；本图无尾延迟结论。
- [正式会议页与影音](https://www.usenix.org/conference/atc16/technical-sessions/presentation/kalia) · [作者代码（固定版本，HERD）](https://github.com/efficient/rdma_bench/tree/a038ec5e2b9f1ac9d4da2fc0044786c82c9ee575/herd) · [第 01 讲已有的源码摘档](../2026-11-23/papers/kalia/source/ARCHIVE-NOTES.md)。原文与报告保留定位链接，未重发文件。
- 下一讲：Pilaf 的 GET/PUT，客户端直读如何识别并发更新。

[本课源码摘档及许可](papers/kalia/source/ARCHIVE-NOTES.md)。
