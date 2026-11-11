# 公开归档范围与许可说明

整理日期：2026-11-11。归档仓库：https://github.com/MingWangSong/rdma-daily 。本仓库包含两期 HTML 早报、原创机制图、来源索引和经过许可核验的源码子集；未创建上游 fork。

## 如何阅读

解压后打开根目录 index.html。两期分别在 2026-11-10/index.html 与 2026-11-11/index.html。HTML、样式及原创图片均使用相对路径，不依赖 CDN、脚本或在线字体。原论文及仓库链接需要联网。

## 已包含

- 两期中文 HTML 早报，共 10 篇论文，保留作者单位、发表会议、机制、实验条件与局限。
- 10 张独立设计的原创机制示意图，每张包含 PNG、SVG、来源及解读。它们不是论文原图或原图复刻。
- 每篇的来源索引、原图图号及 PDF 页码、原创阅读指南、代码许可核验说明。
- FARLock 与 FineMem 的已核验源码子集及 tar.gz，附原始许可证、文件校验值与排除清单。它们不是完整可构建仓库。
- 文件 manifest.json 与 SHA256SUMS.txt。

## 明确未包含的论文与报告原件

以下 10 篇 paper.pdf 以及对应所有原图裁剪、原文全文提取均未纳入公开包：

1. CETOFS — fast26-jia.pdf
2. PD3 — nsdi26-sankhe.pdf
3. BURST — nsdi26-shen.pdf
4. OneSidedMW — nsdi26-wang-zixuan.pdf
5. Scalio — osdi25-sun.pdf
6. DMTree — fast26-wei.pdf
7. FARLock — farlock.pdf
8. FORGE — OSDI26-FORGE-paper.pdf
9. Juneberry — nsdi25-wang-qing.pdf
10. FineMem — osdi25-wang-xiaoyang.pdf

以下 3 份幻灯片也未纳入：OneSidedMW 的 nsdi26_slides-wang-zixuan.pdf、FORGE 的 OSDI26-FORGE-slides.pdf、Juneberry 的 nsdi25_slides-wang_qing.pdf。

原因：检查到可公开访问的官方或作者原件，但未核实足以覆盖第三方公开再分发全文／图片／幻灯片的明确许可。开放获取不自动等于可再发布。本包保留对应原站链接。若以后取得具体授权，可在保留署名和许可条件后另行补入。

版权背景参考：[USENIX 作者政策](https://www.usenix.org/conferences/author-resources/submissions-policy) 与 [出版授权示例](https://www.usenix.org/sites/default/files/consent_author_proceedings.pdf)。此说明是审慎的归档范围记录，不是法律意见，也不表示其他许可必然不存在。

## 代码范围

- FARLock：GPL-3.0-or-later；commit a1dcda36d74b1242be2a854b1ccaf628861d7da2。31 个文件源码子集，排除未完整核验的第三方依赖。
- FineMem：BSD-3-Clause；commit 3a9ecc5955ae2cd394e473ab6abe6b912e14b3fa。83 个文件源码子集，排除论文、图片、轨迹数据和独立 GPL 配置文件。
- PD3：根许可证为 MIT，但 src/PD3/system/external/dma_common.c 与 dma_common.h 明示 NVIDIA proprietary/EULA，故不公开整仓快照。
- DMTree、FORGE、Scalio、OneSidedMW：未核实覆盖整仓的明确再分发许可，保留来源／可得提交，不纳入整仓快照。
- CETOFS、BURST、Juneberry：未定位可确认的官方公开实现，未用同名无关项目替代。

所有已收入的上游源码保持原样，原始版权与许可声明随附。没有编译、执行或运行复现实验。第三方代码各自遵循其原许可，本归档说明不会替它们重新授权。

## 内容与质量核验

正文来自对应两期已发布早报，图解与验证清单是补充原创解读。PD3 的请求时点根据架构图澄清为“请求抵达 DPU 时”，避免把主机已开始处理当作必要前提。性能数字全部是作者报告值，保留硬件、负载及比较基线，不跨论文排名。

已对 10 张 PNG 进行视觉检查，并检查 HTML 结构、每期五篇论文、相对链接、图片尺寸和文件校验值。当前环境的浏览器不允许本地 file 协议预览，因此尚未完成浏览器中的整页桌面／移动视觉验收。响应式样式已提供；发布前建议在获准的预览环境检查两期页面。
