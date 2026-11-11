# DMTree 材料索引

DMTree: Towards Efficient Tree Indexing on Disaggregated Memory via Compute-side Collaborative Design

- 作者：Guoli Wei, Yongkun Li, Haoze Song, Tao Li, Lulu Yao, Yinlong Xu, Heming Cui
- 会议：USENIX FAST 2026
- 原文：https://www.usenix.org/system/files/fast26-wei.pdf
- 会议页：https://www.usenix.org/conference/fast26/presentation/wei
- 核验日期：2026-11-11

把指纹定位和锁协作移到计算节点，使用计算节点之间尚未饱和的 RDMA 资源，缓解内存节点的带宽与 IOPS 压力。底层仍保留适合范围扫描的 FP-B+-tree。

## 公开归档边界

已核对论文全文，未见向公众再分发全文或图片的明确许可。USENIX 的开放获取说明不等于再分发授权；作者保留著作权，示例出版许可授予 USENIX 且不可转授权。公开包仅保留原站链接、事实性元数据和原创解读。

公开包不包含原论文 PDF、全文提取文本或论文裁图。以下中文说明由本归档独立撰写，原文事实请通过页码链接核对。

- 官方版权政策：https://www.usenix.org/conferences/author-resources/submissions-policy
- 示例出版授权：https://www.usenix.org/sites/default/files/consent_author_proceedings.pdf

## 源码

仓库根目录与 README 未找到明确再分发许可，未收入源码或上游 README 的复制件。

https://github.com/muouim/DMTree

## 图与性能定位

### Figure 6：计算侧协作的整体结构

PDF 第 6 页（论文印刷页 153），§3.1–3.3。
https://www.usenix.org/system/files/fast26-wei.pdf#page=6

计算节点维护私有内部树缓存，并协同存放叶节点指纹表与锁状态；内存节点保存树和键值数据。读写通过协作定位与锁管理减少直达内存节点的额外 RDMA。
- 计算节点：内部树缓存、共享指纹表、协作锁。
- 计算节点之间的协作路径承担定位与锁操作。
- 内存节点：FP-B+-tree 内部节点与有序叶节点。
- 边界：不能画成全部数据迁到计算端；主要迁移的是辅助元数据和相应操作。

### Figure 14：YCSB 混合负载吞吐量

PDF 第 12 页（论文印刷页 159），§5.2.3。
https://www.usenix.org/system/files/fast26-wei.pdf#page=12

图中分别比较均匀与 Zipfian 分布下 A–F 工作负载。相对不同基线的优势随点查询、写入和扫描占比而变化，不能合并成无条件的最大加速比。
- 吞吐量：3.8–9.7×。范围：相对 Sherman、ROLEX 的查写密集型 YCSB 工作负载（不含 E）。位置：§5.2.3, PDF p.12。
- 吞吐量：3.2×。范围：相对 SMART 的扫描密集型 YCSB E。位置：§5.2.3, PDF p.12。
- 吞吐量：1.1–1.7×。范围：相对 CHIME 的查写密集型工作负载。位置：§5.2.3, PDF p.12。
- 实验条件：6 个计算节点、1 个内存节点，100Gbps ConnectX-6；预载 10 亿条、每轮 1 亿次操作，默认 32B 键值项；配置见 §5.1 / PDF p.10。

详细字段、补充图锚点与来源保存在 materials.json。
