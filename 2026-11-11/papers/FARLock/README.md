# FARLock 材料索引

FARLock: Asymmetric RDMA Locking Made Fair

- 作者：Yuehao Hu, Jiatang Zhou, Tianzheng Wang, Keval Vora
- 会议：USENIX OSDI 2026
- 原文：https://www2.cs.sfu.ca/~tzwang/farlock.pdf
- 会议页：https://www.usenix.org/conference/osdi26/presentation/hu-yuehao
- 核验日期：2026-11-11

用分离的本地/远程队列保留非对称访问优势，同时用全局票号保证公平次序；MCS 式交接和不破坏公平性的分组降低交接开销。

## 公开归档边界

已核对论文全文，未见向公众再分发全文或图片的明确许可。USENIX 的开放获取说明不等于再分发授权；作者保留著作权，示例出版许可授予 USENIX 且不可转授权。公开包仅保留原站链接、事实性元数据和原创解读。

公开包不包含原论文 PDF、全文提取文本或论文裁图。以下中文说明由本归档独立撰写，原文事实请通过页码链接核对。

- 官方版权政策：https://www.usenix.org/conferences/author-resources/submissions-policy
- 示例出版授权：https://www.usenix.org/sites/default/files/consent_author_proceedings.pdf

## 源码

项目自身代码头明确采用 GPL-3.0-or-later；保留完整 LICENSE 和源码版权头。未完全核验的 include/third_party 依赖被排除，故不是可直接构建的完整仓库。

https://github.com/pdclab/farlock

- 版本：https://github.com/pdclab/farlock/commit/a1dcda36d74b1242be2a854b1ccaf628861d7da2
- 许可证：GPL-3.0-or-later
- 快照：code-source-subset.tar.gz；展开内容：code/
- 完整文件清单、排除理由和哈希：code-manifest.json
- 范围说明：CODE-SNAPSHOT.md；源码未执行、未编译。

## 图与性能定位

### Figure 4：双队列与全局公平次序

PDF 第 6 页（论文印刷页 1535），§3–4.1。
https://www2.cs.sfu.ca/~tzwang/farlock.pdf#page=6

本地和远程请求分队列排队，票号统一决定获锁先后。本地访问无需因原子性而走 RNIC 回环；票号与队列顺序通过专门协议协调。
- 本地队列：本地内存访问。
- 远程队列：RDMA 访问。
- 全局 ticket 次序连接两个队列；Peterson 锁保护票号相关状态。
- FARLock-G 只将不破坏公平次序的连续请求合组。
- 边界：票号是协议建立的全局次序，不应画成无协调的 CPU 原子指令直接与 RDMA 原子指令混用。

### Figure 7：高竞争下本地与远程尾延迟

PDF 第 11 页（论文印刷页 1540），§5.1–5.2。
https://www2.cs.sfu.ca/~tzwang/farlock.pdf#page=11

1 与 10 把锁构成高竞争条件，图分开呈现本地/远程请求及四个尾分位。收益最显著的是本地尾延迟；不能把局部最优倍数说成所有请求的平均提升。
- 本地尾延迟：最高 62× 更低。范围：高竞争微基准中相对公平锁 MCS、Ticket。位置：§5.2, PDF p.10; Fig.7, PDF p.11。
- 本地尾延迟：8× 更低。范围：同一高竞争实验中相对 ALock。位置：§5.2, PDF p.10。
- 实验条件：10 节点，56Gbps Mellanox FDR CX3；每节点 12 线程，本地临界区约 100ns、远程约 5μs；图中分位为 P95、P99、P99.9、P99.999。

详细字段、补充图锚点与来源保存在 materials.json。
