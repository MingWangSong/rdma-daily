# PD3 代码归档状态

核验时间：2026-11-11T08:30:50Z。目标为公开归档，当前没有发布。

## 结果

根 LICENSE 为 MIT，但两个随仓文件声明为 NVIDIA proprietary 并受另行 EULA 管辖。未核验到足够的整仓再分发许可，因此不生成公开源码快照。

- 状态：`link_only_mixed_license_restriction`
- 可再分发源码快照：未收录。
- 仓库：https://github.com/fardatalab/PD3
- 分支：main
- 固定提交：a431cd05b93082f87d880d222a7dc5bfdd6adc06
- 许可证：MIT at repository root; NVIDIA proprietary files present

## 核验依据

- 根 MIT 许可证允许复制与分发，并要求保留版权及许可声明
- NVIDIA 两个文件使用专有软件版权头，根 MIT 不能替第三方授予权利
- 未下载整仓、未抓取子模块内容、未执行代码

## 来源

- https://github.com/fardatalab/PD3/blob/a431cd05b93082f87d880d222a7dc5bfdd6adc06/LICENSE
- https://github.com/fardatalab/PD3/blob/a431cd05b93082f87d880d222a7dc5bfdd6adc06/src/PD3/system/external/dma_common.c
- https://github.com/fardatalab/PD3/blob/a431cd05b93082f87d880d222a7dc5bfdd6adc06/src/PD3/system/external/dma_common.h

## 使用说明

这里只提供公开链接、版本和许可证筛查说明，不包含源代码快照。可访问上游资料自行查看。如需公开快照，应先核验相关 NVIDIA EULA 的再分发条款，或在完整逐文件审核后建立明确标注删减内容的许可子集。 不应把公开可读、可 clone 或 GitHub 上的 fork 功能等同于取得再分发许可。
