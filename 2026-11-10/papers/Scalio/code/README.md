# Scalio 代码归档状态

核验时间：2026-11-11T08:30:50Z。目标为公开归档，当前没有发布。

## 结果

官方 artifact 仓库可访问，但根目录没有 LICENSE；SPDK/DPDK 等依赖的许可证不等于 Scalio 脚本、图表和全部新增代码获得了仓库级再分发授权。

- 状态：`link_only_no_repository_wide_license`
- 可再分发源码快照：未收录。
- 仓库：https://github.com/madsys-dev/scalio-osdi25-ae
- 分支：main
- 固定提交：e203addb26a4e1615b26dabab7566406c2786dda
- 许可证：未发现覆盖整个仓库的显式许可证。

## 核验依据

- README 明确说明是 Scalio OSDI '25 artifact
- GitHub repository license 字段为空；根目录未见 LICENSE
- 递归树发现许可证只位于 SPDK 及其依赖下
- scripts/evaluate.sh 头部未见许可证
- 未下载整仓、未执行脚本

## 来源

- https://github.com/madsys-dev/scalio-osdi25-ae/tree/e203addb26a4e1615b26dabab7566406c2786dda
- https://github.com/madsys-dev/scalio-osdi25-ae/blob/e203addb26a4e1615b26dabab7566406c2786dda/README.md
- https://github.com/madsys-dev/scalio-osdi25-ae/blob/e203addb26a4e1615b26dabab7566406c2786dda/spdk/LICENSE

## 使用说明

这里只提供公开链接、版本和许可证筛查说明，不包含源代码快照。可访问上游资料自行查看。如后续发现明确覆盖目标内容的许可，可复核后再补充快照。 不应把公开可读、可 clone 或 GitHub 上的 fork 功能等同于取得再分发许可。
