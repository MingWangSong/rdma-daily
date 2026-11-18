# HiDPU：存储映射查找卸载的真正收益，是减少 DPU→主机串行往返

**正式发表**：FAST 2025，2025 年 2 月 25–27 日，论文集 pp.271–285。本期为往年研究补读，不是当日新论文。**机构**：山东大学（Wenbin Zhu、Zhaoyan Shen、Qian Wei、Dongxiao Yu）；天津大学与华为（Renhai Chen）；华为（Xin Yao）；香港中文大学（Zili Shao）。

## 瓶颈与机制
DPU 已接管数据传输，不意味着 CPU 已退出存储关键路径：逻辑地址 LA 到物理地址 PA 的查询仍可能进入主机软件。把整个映射表搬到 DPU 又遇到容量限制；简单地把查表算子搬过去，则多级表的每一级都可能产生 PCIe/DMA 往返。论文针对的是这个**地址翻译路径**，不是一种新 RDMA 传输或新的一致性协议。

HiDPU 将已排序的逻辑地址按连续性切成三类段（图 4、§3.1–3.2）：
1. **强连续 Accurate 段**：保存 first key 与表起址，用偏移直接确定位置，随后一次主机访问取得映射项。
2. **随机 PTHash 段**：先按哈希选择 bucket，取该 bucket 的 pilot，再以 pilot 修正的哈希定位无碰撞的映射槽。pilot 与映射项都在主机，朴素路径有两次依赖性往返。
3. **弱连续 LPTHash 段**：以 `(LA-firstkey)/div` 分桶，把相邻 LA 放入同一桶，共用 pilot；这不是单纯换一个更快哈希，而是让局部性能够进入 pilot 缓存。代价是桶大小不均、空桶和更难构造 perfect hash；构造超时扩大表，找不到合适分桶时退回 PTHash。

DPU 保存多层 learned index 与段描述，预测属于哪一段后再校正邻近位置；**预测不是最终映射结果**，最终段内查找是精确定位。主机保存大映射数组和 pilot 数组。默认 1,000 段的内部索引为 23.74 KB，另有 1 MB pilot cache，不能把“23 KB”写成全部内存成本。

**作者仓库架构图（对应论文 §3、区别于论文图 4）**：读图要看 DPU/CPU 边界。右侧 Accurate 虚线绕过 bucket cache；Cache Miss 虚线先到主机 PTHash Buckets 获取 pilot，才可确定 Leaf Table 中的映射位置。LPTHash 与 super-bucket 缓存的作用，是把连续请求的第一步留在 DPU 内，既降 PCIe 流量又消除串行依赖。缓存将相邻 pilots 合成 super-bucket，一次缺失带回邻居；冲突时优先保留 LPTHash pilot。并发读取把标识符与 pilot 一起搬入线程局部内存，匹配后才使用；写入通过组内原子计数器分配槽位（图 5）。实现还以定点预测替代无 FPU 的软件浮点、批量加载相邻 first keys，并重叠加载与比较（§4）。

## 更新、并发与失败边界
更新和删除原地改映射项；新键先进主机 cuckoo buffer，DPU 并行读取两个候选槽。缓冲满或驱逐链超阈值时局部重建：主机复制旧段、并入新项并生成新 pilots，再发布带递增版本与新数组地址的段元数据。DPU 中旧版本缓存失效；旧数组延迟回收，供已经读取旧元数据的请求完成。论文图 6 把发布步骤标为 atomic update，但没有给出可照搬到任意 RNIC/DPU 的原子粒度、内存屏障及崩溃恢复协议。不要据此声称具备持久线性一致映射更新。

局部重建不阻塞未受影响段。全局重建则通过根模型阻止新查询，等待在途查询完成，底向上重建并清空缓存。因此“异步更新”不等于全部重建零停机。论文报告 1.2 PB 数据规模全局重建低于 10 分钟，没有证明这能满足在线存储的尾延迟或恢复 SLO。

## 实验证据与不能外推的部分
平台是 96 核 2.4 GHz Xeon Platinum 8260、512 GB DDR4、华为 Hi1823；DPU 具有数百轻量核，每核 4 个物理线程、每线程 4 KB 局部内存和共享 4 MB。D-Page 与 D-Learned 均由作者移植到同一 Hi1823；D-Learned 使用相同的计算优化。不是拿未经优化 CPU 实现充当唯一对照。

图 8(b) 使用 Filebench OLTP/websrv、TPC-DS/PostgreSQL、YCSB/LevelDB 在 FEMU 环境收集的地址轨迹，重放测量**映射查询吞吐与平均延迟**。并发 1–256：HiDPU 吞吐较 D-Page 为 1.3–4.3×、较 D-Learned 为 1.3–1.5×；论文汇总 HiDPU 各场景延迟低于 5.76 μs，对照分别达到 17.39 与 8.15 μs。该图的左轴是 MQPS，右轴是 μs；不能写成存储带宽加速 4.3×，更不能替代 p99 I/O 延迟。

**图 8(b) 读图**：OLTP 的高并发增益小于另外三组，不是方法失效，而是小事务、随机访问降低了 pilot cache 与索引元数据复用。64 到 256 客户端时吞吐趋于平台，延迟却继续上升，说明收益不是随线程无界增长。

图 10 的消融进一步拆开收益来源：先加入 Accurate 段，吞吐最高 1.27×、延迟降至 78%；仅添加 pilot cache 平均吞吐增益 1.03×，原因是普通哈希破坏连续性，命中率最低 19%。改用 LPTHash 后，256 并发下各 trace 命中率达到 80–97%，在前一变体上吞吐再提高最高 1.1×、延迟降至 91%。这说明“加缓存”本身不是核心，**先设计能被缓存的局部性**才是关键。

图 9 的扩大 prn 轨迹测内存，1.35 billion 映射项下 D-Page 102 GB、HiDPU 29 GB。正文同段的“1.26 PB、1 MB 大页、1.35 billion pages”容量表述彼此不自洽；建议只引用明确的映射项数与内存测量，不把容量换算继续传播。图 11(a) 的局部重建实验用一个线程连续 1,000 次查询为一批取均值，报告重建期间平均查询延迟 +0.69%、缓存命中率平均下降 0.15%，瞬时降幅最高 9.9%。这不能证明 p99/p999 无尖峰，也不是全局重建结果。

## 对分布式存储的具体落地判断（分析）
适合试在 DPU 前置块存储的 LBA→extent/page 映射，前提是映射数据能驻留主机 DRAM、地址具有连续性、查询远多于插入。它不直接加速数据复制、NVMe 设备访问或网络拥塞。对象存储的高熵对象 ID 不能假设具备同等 LPTHash 局部性；先转译到有连续性的内部 extent ID 才可能适配，且需要计入这一层开销。

建议最小实验分两阶段：①用作者 CPU simulator 重放本系统的真实 extent/LBA 轨迹，比较普通 page table、PTHash、LPTHash 的映射内存、pilot 命中率、构建时间，扫描段数 P、插入比例和碎片化程度；②在目标 DPU 上测每次查询 PCIe read 次数/字节数、每核 CPU 开销、平均及 p99/p999 翻译延迟，并在真实 I/O 中重新测端到端延迟。注入局部重建、全局重建、DPU reset、主机 crash，检查版本发布与旧表回收不会读到不一致地址。收益门槛应是“省下的 CPU/PCIe 成本大于新增缓存和维护成本”，不是只追一个倍数。

代价与落地风险：perfect-hash 重建消耗主机 CPU，copy-and-publish 暂时双份数组增加内存；高 churn 增加 buffer 与重建频率；全局暂停需要双版本索引或后台切换等额外设计。BlueField 兼容性是作者讨论，论文实验未证明在 BlueField、不同 PCIe 拓扑或 RoCE 端到端路径上同样有效。

## 阅读与资料
实际阅读：论文正文 §2–5、图 4–11 及结论；作者仓库 README 和 LICENSE。未运行代码、未验证硬件复现、未观看报告视频。
- 正式会议页：https://www.usenix.org/conference/fast25/presentation/zhu
- 论文：https://www.usenix.org/system/files/fast25-zhu.pdf
- 作者 slides：https://www.usenix.org/system/files/fast25_slides-zhu.pdf
- 作者源码：https://github.com/quieoo/lmpthash （检查版本 3b934e27c4b5d4da093f06a2ae1e9a673b1650cf）
- 公开代码是 CPU-only simulator，不含依赖专用 microcode 的完整 DPU 实现；README 提供 MSR/random/FEMU trace 入口。

图像依据：architecture.png 取自上述作者 MIT 仓库 documents/HiDPU.png，随附 LICENSE-code.txt；figure8b.png 是 FAST25 论文图 8(b) 的单一实验面板裁切，为逐项性能评论保留坐标/图例/单位，不替代论文，依据必要有限学术评论引用评估，非无限再发布授权。没有发现论文全文公开再分发许可，不上传全文或完整 slides；原文可通过 USENIX 链接阅读。保留来源和图号，版权例外适用性无保证。
