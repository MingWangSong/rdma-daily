# FORGE 材料索引

FORGE: Mitigating Synchronization Amplification for Memory-Disaggregated Caching Systems

- 作者：Zhijun Yang, Yu Hua, Ming Zhang, Menglei Chen, Yixiao Wang
- 会议：USENIX OSDI 2026
- 原文：https://sosposdi.com/publications/2026/forge/OSDI26-FORGE-paper.pdf
- 会议页：https://www.usenix.org/conference/osdi26/presentation/yang-zhijun
- 核验日期：2026-11-11

按相近访问模式分组缓存对象，用组级同步摊薄热点追踪和淘汰开销；借助 FIFO 的可预测淘汰位置延迟刷新热度，并把热度同步放到 RNIC 片上内存。

## 公开归档边界

已核对论文全文，未见向公众再分发全文或图片的明确许可。USENIX 的开放获取说明不等于再分发授权；作者保留著作权，示例出版许可授予 USENIX 且不可转授权。公开包仅保留原站链接、事实性元数据和原创解读。

公开包不包含原论文 PDF、全文提取文本或论文裁图。以下中文说明由本归档独立撰写，原文事实请通过页码链接核对。

- 官方版权政策：https://www.usenix.org/conferences/author-resources/submissions-policy
- 示例出版授权：https://www.usenix.org/sites/default/files/consent_author_proceedings.pdf

- 幻灯片：https://sosposdi.com/publications/2026/forge/OSDI26-FORGE-slides.pdf（未核实再分发许可，仅保留链接）

## 源码

根目录和 README 没有明确项目许可证；README 提到使用部分 Ditto 代码，不能据此推定整个 FORGE 可再分发。

https://github.com/cszjyang/forge

## 图与性能定位

### Figure 4：按组维护与临近淘汰时同步

PDF 第 6 页（论文印刷页 981），§3–5。
https://sosposdi.com/publications/2026/forge/OSDI26-FORGE-paper.pdf#page=6

计算侧在 OFM 中记录细粒度对象访问，再按组、临近淘汰时刷新至内存侧 RNIC；淘汰窗口挑选冷组，保留热对象并重新成组。
- 计算侧：Get/Set、对象频率表 OFM、热对象合并缓冲。
- 内存侧：哈希索引、对象组、FIFO 淘汰队列。
- 同步路径：按组、延迟、面向即将淘汰的窗口。
- 回收路径：识别热对象，重新成组，冷组释放。
- 边界：不是只做批量驱逐；保留对象级热度信息并结合组级处理，且使用热度感知虚拟分段。

### Figure 13：YCSB 的吞吐、P50 与 P99

PDF 第 12 页（论文印刷页 987），§6.1–6.2。
https://sosposdi.com/publications/2026/forge/OSDI26-FORGE-paper.pdf#page=12

横轴是吞吐，纵轴分别为 P50、P99 延迟；图内另列命中率。应同时看性能与命中率，确认不是以更差缓存效果换取减少同步。
- 吞吐量：2.0–8.7×。范围：YCSB 20% 缓存实验，相对全部被测基线的汇总范围。位置：§6.2, PDF p.12。
- P50 / P99 延迟：1.3–5.9× / 3.9–13.3× 更低。范围：同一 YCSB 实验及所有被测基线。位置：§6.2, PDF p.12。
- 摘要中的吞吐 / P50 / P99 改善：最高 4.5× / 4.0× / 7.5×。范围：摘要对 state-of-the-art systems 的总结口径，不与 Fig.13 的所有基线范围混用。位置：Abstract, PDF p.2。
- 实验条件：100Gbps ConnectX-5；YCSB A–E，256B 对象，20% 缓存，3 个计算节点合计 16–256 线程；基线为 Ditto、S3FIFO-DM、GLCache-DM。

详细字段、补充图锚点与来源保存在 materials.json。
