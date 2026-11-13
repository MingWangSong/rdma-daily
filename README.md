# RDMA 论文早报

面向 RDMA、远端内存与分布式存储研发的中文技术研读。

- [11月13日：共享连接、远端状态与多路径：RDMA 存储的扩展边界](https://mingwangsong.github.io/rdma-daily/2026-11-13/)
- [11月12日：从 RNIC 与 DPA 到远端 SSD](https://mingwangsong.github.io/rdma-daily/2026-11-12/)
- [11月10日：从远端 SSD 路径到缓存一致性](2026-11-10/index.html)
- [11月11日：从索引热点到公平锁与远端内存管理](2026-11-11/index.html)
- [HTML 归档首页](index.html)

## 研究专题

- [NVMe-oF × KV Cache：最新研究与创新路线](https://mingwangsong.github.io/rdma-daily/reports/2026-11-12-nvmeof-kvcache/)

## 11月12日新增

三篇近期正式顶会研究，含六幅必要原图与逐图解读。一篇直接RDMA传输研究，两篇存储数据路径设计对照，显式区分GPU/UDP/NVMe-TCP实验与存储迁移。未核实当日新增论文。UCCL按Apache-2.0保存固定commit源码阅读子集，非完整可构建分发或fork。

## 前两期修订

十篇全部改为机制、实验与适用边界的深入分析，加入13张与评论直接对应的原论文局部图表。采用紧凑深色版式、双栏研读布局、手机适配、目录定位和原图放大。旧版10张低信息量自绘框图已移除。

GitHub文件页显示源码。下载仓库后在浏览器打开根目录 index.html 可离线阅读全部正文、样式与图片；论文及上游代码链接需要联网。

## 资料与核验

- [原图来源、作者、图号与页码](figure-sources.json)
- [结构化技术分析](research-notes.json)
- [引用及归档范围](PUBLICATION_READINESS.md)
- [质量核验记录](VALIDATION.md)
- [文件清单](manifest.json)与[SHA-256校验](SHA256SUMS.txt)

FARLock（GPL-3.0-or-later）与FineMem（BSD-3-Clause）保留已核验源码子集和原许可证，不是完整可构建仓库。原论文、报告未整篇重发；原图版权归各自作者，不因被引用而成为开放许可素材。性能数字为作者报告结果，未独立复现。
