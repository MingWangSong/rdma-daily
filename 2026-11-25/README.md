# 第 03 讲 · Pilaf：两次 READ 都成功，为什么还要重读？

[打开课程 HTML](https://mingwangsong.github.io/rdma-daily/2026-11-25/) · [上一讲：门铃批量](https://mingwangsong.github.io/rdma-daily/2026-11-24/)

25 分钟。学习 Pilaf 的单边 GET、服务端 PUT，以及为什么完成两次 RDMA READ 后仍须核对索引和键值。

- Christopher Mitchell、Jinyang Li（纽约大学）；Yifeng Geng（清华大学）。USENIX ATC ’13 正式论文集，2013 年 6 月 26–28 日，pp. 103–114，经典回顾。
- [图 3–4 / §3.1–3.2](https://files.usenix.org/s3fs-public/cdn/atc13-mitchell.pdf#page=5)：第一次读取索引；取得地址与长度后再读键和值。
- [图 5 / §3.3](https://files.usenix.org/s3fs-public/cdn/atc13-mitchell.pdf#page=6)：第一道校验防索引混读，第二道检查数据区是否仍与索引一致。
- [图 9 / §5.3](https://files.usenix.org/s3fs-public/cdn/atc13-mitchell.pdf#page=9)：图中量的是检测到的重试；访问的键超过 20,000 时，作者在其峰值读写压力下报告小于 0.01%，不等于线上热点也不会造成重试。
- [出处、报告与归档说明](papers/pilaf/REFERENCES.md)。
- 下一讲：FaRM 与版本验证。
