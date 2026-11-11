# Juneberry 材料索引

Achieving Wire-Latency Storage Systems by Exploiting Hardware ACKs

- 作者：Qing Wang, Jiwu Shu, Jing Wang, Yuhao Zhang
- 会议：USENIX NSDI 2025
- 原文：https://www.usenix.org/system/files/nsdi25-wang-qing.pdf
- 会议页：https://www.usenix.org/conference/nsdi25/presentation/wang-qing
- 核验日期：2026-11-11

Ordered Queue 将硬件接收确认与严格执行顺序结合，让不需返回状态的 nil-externalizing 请求能先提交、后由 CPU 执行。读取等需要返回状态的请求仍走软件响应。

## 公开归档边界

已核对论文全文，未见向公众再分发全文或图片的明确许可。USENIX 的开放获取说明不等于再分发授权；作者保留著作权，示例出版许可授予 USENIX 且不可转授权。公开包仅保留原站链接、事实性元数据和原创解读。

公开包不包含原论文 PDF、全文提取文本或论文裁图。以下中文说明由本归档独立撰写，原文事实请通过页码链接核对。

- 官方版权政策：https://www.usenix.org/conferences/author-resources/submissions-policy
- 示例出版授权：https://www.usenix.org/sites/default/files/consent_author_proceedings.pdf

- 幻灯片：https://www.usenix.org/system/files/nsdi25_slides-wang_qing.pdf（未核实再分发许可，仅保留链接）

## 源码

本次给定资料未包含已核实的官方源码仓库；不把同名项目当作本文代码。

## 图与性能定位

### Figure 1：硬件 ACK 提交与 CPU 有序执行

PDF 第 5 页（论文印刷页 1088），§4。
https://www.usenix.org/system/files/nsdi25-wang-qing.pdf#page=5

RNIC 按顺序分配接收缓冲并在分配后发 ACK；CPU 也按该缓冲次序执行。这样先提交的 set 会在后续 get 返回值前执行，从而维持线性一致性。
- 客户端发出 nil-externalizing 请求。
- RNIC 依序分配接收缓冲，再发硬件 ACK 作为提交信号。
- CPU 依序执行已接收请求。
- 需要返回状态的请求在执行后发软件响应。
- 边界：硬件 ACK 不代表请求已经执行；快路径也不适用于所有操作。耐久版本还要求持久内存及相应平台条件。

### Figure 7：Memcached 的中位延迟与吞吐

PDF 第 11 页（论文印刷页 1094），§6.3。
https://www.usenix.org/system/files/nsdi25-wang-qing.pdf#page=11

四种 Twitter 负载的 set 比例不同，写密集负载获益更大；各系统峰值吞吐相同，因为瓶颈在后端存储引擎。
- 中位延迟：82.30% / 50.74% / 32.89% / 90.70% 更低。范围：峰值吞吐下，Cluster-12/19/27/31 相对 RawRPC。位置：§6.3, Fig.7, PDF p.11。
- P99 延迟：最高 32.43% / 42.86% 更低。范围：写密集 Cluster-12/31 相对第二名 DeferredExec。位置：§6.3, Fig.8, PDF p.11。
- 实验条件：后端 Memcached 1.6.19；四个负载 set 比例为 80%、25%、15%、94%。

详细字段、补充图锚点与来源保存在 materials.json。
