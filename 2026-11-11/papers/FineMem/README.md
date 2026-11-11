# FineMem 材料索引

FineMem: Breaking the Allocation Overhead vs. Memory Waste Dilemma in Fine-Grained Disaggregated Memory Management

- 作者：Xiaoyang Wang, Yongkun Li, Kan Wu, Wenzhe Zhu, Yuqi Li, Yinlong Xu
- 会议：USENIX OSDI 2025
- 原文：https://www.usenix.org/system/files/osdi25-wang-xiaoyang.pdf
- 会议页：https://www.usenix.org/conference/osdi25/presentation/wang-xiaoyang
- 核验日期：2026-11-11

用预注册 MR 避免每次分配都注册内存，再由计算侧可信分配服务、Memory Window、两层位图和日志实现细粒度、可隔离、可恢复的远程分配。

## 公开归档边界

已核对论文全文，未见向公众再分发全文或图片的明确许可。USENIX 的开放获取说明不等于再分发授权；作者保留著作权，示例出版许可授予 USENIX 且不可转授权。公开包仅保留原站链接、事实性元数据和原创解读。

公开包不包含原论文 PDF、全文提取文本或论文裁图。以下中文说明由本归档独立撰写，原文事实请通过页码链接核对。

- 官方版权政策：https://www.usenix.org/conferences/author-resources/submissions-policy
- 示例出版授权：https://www.usenix.org/sites/default/files/consent_author_proceedings.pdf

## 源码

项目源码采用 BSD-3-Clause。保留完整 LICENSE；论文、图片、数据轨迹/结果和带独立 GPL-2.0 声明的 .clang-format 未收入源码子集。

https://github.com/ADSLMemoryDisaggregation/FineMem

- 版本：https://github.com/ADSLMemoryDisaggregation/FineMem/commit/3a9ecc5955ae2cd394e473ab6abe6b912e14b3fa
- 许可证：BSD-3-Clause
- 快照：code-source-subset.tar.gz；展开内容：code/
- 完整文件清单、排除理由和哈希：code-manifest.json
- 范围说明：CODE-SNAPSHOT.md；源码未执行、未编译。

## 图与性能定位

### Figure 6：计算侧分配服务与内存侧元数据

PDF 第 7 页（论文印刷页 62），§3.2–4。
https://www.usenix.org/system/files/osdi25-wang-xiaoyang.pdf#page=7

应用调用计算节点的可信分配服务，服务经单边 RDMA 操作远程预注册区内的位图与日志。Memory Window 限制应用可访问的内存范围，避免把整个共享 MR 暴露给应用。
- 计算节点：应用与可信 Allocation Service，隔离分配元数据。
- 内存节点：预注册的大 MR 与细粒度 chunks。
- 元数据：两层位图、重做日志、MW capability 表。
- 分配热路径：计算侧以单边 RDMA 更新远程元数据，不由内存侧 CPU 逐次处理。
- 边界：“不涉及内存侧 CPU”指分配热路径，不是初始化、恢复等所有操作都不需要 CPU。

### Figure 10：平均分配延迟随并发与内存节点数变化

PDF 第 11 页（论文印刷页 66），§6.2。
https://www.usenix.org/system/files/osdi25-wang-xiaoyang.pdf#page=11

左图为线程数，右图为内存节点数；纵轴是平均分配延迟，不是吞吐量。4KB 分配下，RPC 基线超过 16 客户端线程后扩展受限，FineMem 依靠单边路径维持低延迟。
- 平均分配延迟：43.215μs vs 763.01μs。范围：4KB、512 客户端线程，FineMem 对比 Premmap-One-sided；约降低 94.3%。位置：Table 2, PDF p.11。
- 平均 CAS 重试次数：1.333 vs 45.108。范围：同一 Table 2 微基准。位置：Table 2, PDF p.11。
- 分配延迟：约 95% 更低。范围：两层位图与竞争控制组合，相对数组元数据基线的消融总结。位置：Fig.11 / §6.2, PDF p.11。
- 实验条件：4KB 分配粒度；多内存节点实验使用 round-robin 分配。评测的分配微基准先建立碎片化地址空间，测量不是纯空闲池的理想情况。

详细字段、补充图锚点与来源保存在 materials.json。
