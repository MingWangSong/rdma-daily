# 引用与归档范围

修订：2026-11-12。对应2026年11月10日和11日两期早报。

## 论文与图表

本仓库包含十篇论文的原创中文技术评论，以及13张与分析直接相关的原论文图表局部节选。没有重新发布完整论文、完整页面截图、幻灯片或全文提取。每张图均保留作者、论文、会议、图号、PDF页码和原文链接；裁剪仅去除无关正文，不改变图中的数据、坐标轴、图例或协议内容。

未发现这些论文图表的通用开放再分发许可，也未发现针对所选图表的明示禁止引用。这里按必要技术评论和研究引用进行逐项控制，不将“开放获取”解释为开放授权，不声称存在统一许可或固定数量的法律安全线。版权和使用限制仍属于原作者/权利人。

图表选择以论证所需为限：CETOFS 1、PD3 2、BURST 1、OneSidedMW 1、Scalio 2、DMTree 1、FARLock 1、FORGE 1、Juneberry 2、FineMem 1。每图具体评论与裁剪范围见 figure-sources.json 及各论文 images/attribution.json。旧版低信息量自绘图已移除。

参考：[USENIX作者政策](https://www.usenix.org/conferences/author-resources/submissions-policy)、[USENIX出版授权书](https://www.usenix.org/sites/default/files/consent_author_proceedings.pdf)、[美国版权局合理使用说明](https://www.copyright.gov/fair-use/)。合理使用等版权例外需结合具体事实和法域判断；本说明不是法律意见。

## 代码

- FARLock：GPL-3.0-or-later；commit a1dcda36d74b1242be2a854b1ccaf628861d7da2。31个文件源码子集，排除未完整核验的第三方依赖。
- FineMem：BSD-3-Clause；commit 3a9ecc5955ae2cd394e473ab6abe6b912e14b3fa。83个文件源码子集，排除论文、图片、轨迹数据和独立GPL配置文件。
- PD3：根许可证MIT，但部分external/dma_common文件明示NVIDIA proprietary/EULA，故不公开整仓快照。
- DMTree、FORGE、Scalio、OneSidedMW：未核实覆盖整仓的明确再分发许可，保留作者仓库链接。
- CETOFS、BURST、Juneberry：未定位可确认的官方公开实现，未用同名无关项目替代。

原源码和许可证保持原样；未运行论文复现实验，也未创建上游fork。软件代码许可证不自动覆盖同仓库的论文图表。

## 阅读和性能结论

本地HTML、CSS、JavaScript和图表可离线阅读；不依赖在线字体、CDN、分析追踪或第三方脚本。JavaScript仅用于目录高亮与图片放大，关闭JavaScript仍能阅读正文、直接打开图片。

所有结果为作者报告值，保留实验硬件、负载、比较基线及边界，不跨论文排名。早报日期是整理日期，不是“当天新发表”的声明。结构和视觉验收状态详见 VALIDATION.md。


## 2026年11月12日新增

新增三篇评论与六幅必要原图局部节选，图号/来源/逐图分析见当期materials-index.json。完整论文、报告与全文提取未进入公开归档。UCCL源码阅读子集来自52d4184c89deb5631be6dac6a9b1c40896c9e26e，保留Apache-2.0 LICENSE及原文件，不含第三方依赖，非完整可构建分发或fork。其代码许可不扩展至论文。DPA-Store和NVMe-oF流控未核实作者专属代码仓库。
