# 第 01 讲：读一个 4 KiB 缓存块，谁在搬数据？

[阅读排版版](https://mingwangsong.github.io/rdma-daily/2026-11-23/) · 经典论文导读 · 约 25 分钟。

**本课目标**：区分 RPC 的业务请求和单边 RDMA READ 的搬运，能解释网卡、主存与存储软件各自做什么。

- **必读**：[论文集版 PDF 第 3 页](https://www.cs.cmu.edu/~xia/resources/Documents/kalia-usenix2016.pdf#page=3)看 §2 图 1；第 3–4 页看 §2.2.1 和表 1。第 4 页的 §2.2.2 暂只了解 WQE；不用第一遍看优化。
- **练习**：若只有块号、若已知远端内存地址、若缓存刚被回收，分别由谁负责定位、搬运和校验？
- **实验证据**：[图 12](https://www.cs.cmu.edu/~xia/resources/Documents/kalia-usenix2016.pdf#page=10)与 §5.3.1，比较不同实验平台上 READ 从网卡处理率受限转向链路带宽受限的现象；不是生产 4 KiB I/O 延迟。
- **下一课**：工作队列、门铃与完成通知，之后进入 Pilaf 的读写分工。

论文：Anuj Kalia、David G. Andersen（Carnegie Mellon University）；Michael Kaminsky（Intel Labs）。*Design Guidelines for High Performance RDMA Systems*，2016 年 6 月 22–24 日，USENIX ATC 正式论文集 pp. 437–450，最佳学生论文。

来源：[会议论文与报告](https://www.usenix.org/conference/atc16/technical-sessions/presentation/kalia)、[CMU 镜像论文集版](https://www.cs.cmu.edu/~xia/resources/Documents/kalia-usenix2016.pdf)、[论文列出的测量代码](https://github.com/efficient/rdma_bench)。完整 PDF 和报告未在此重发，论文集开放阅读不等于第三方可公开再分发；图 1 和图 12 请从正文页码链接查看。

[测量代码归档说明](papers/kalia/source/ARCHIVE-NOTES.md)：固定在上游提交 a038ec5 的 Apache-2.0 子集，不是完整 fork 或论文发表时的精确版本。
