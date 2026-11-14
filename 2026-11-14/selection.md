# 选题与新鲜度核验

截至本轮检索，未核实到 2026-11-14 当天新发表或新收录、同时具备可深入阅读正文的合格 RDMA 存储论文。因此本期采用近期正式论文加明确标记的经典回溯，不将网页抓取日期当发表日期。

重点核查入口：SIGMOD 2026 官方研究论文名单、VLDB 2026 项目、SIGCOMM 2026 正式名单、NSDI 2027 spring accepted、作者出版列表与全文。已对照仓库往期目录避开已报道的 CETOFS/PD3/BURST/OneSidedMW/Scalio、DMTree/FARLock/FORGE/Juneberry/FineMem、Vedrfolnir/THEMIS/STORM/PSN-PATH/BALBOA、UCCL-Tran/DPA-Store/NVMe-oF flow control、DistVS/LCMP/ODRP/ScalaCN 等。

InfiniFlow（SIGCOMM 2026）已核实正式收录，但本轮未获取可完整阅读的正文，仅有摘要与仓库，不列入正文精读。NSDI 2027 已录用条目不因只有题名就当成已深入阅读论文；本期不纳入。SC26 搜索可发现 SigmaTrace 等正式日程，但本轮未完成足够正文核查，不列为当日新论文。

本期贯穿的问题：索引如何减少远端往返和读放大，LSM如何避免共享资源拥塞，服务如何维护与迁移，网络如何在丢包下保持正确性和可控尾延迟。每篇的建议实验均是分析推断，不冒充论文已证明结果。
