# FaSST · 阅读与归档记录

- 正式出版：[USENIX OSDI 2016](https://www.usenix.org/conference/osdi16/technical-sessions/presentation/kalia)，2016-11-02 至 11-04，论文集 185–201。作者：Anuj Kalia、David G. Andersen（卡内基梅隆大学）；Michael Kaminsky（Intel Labs）。
- [官方 PDF](https://files.usenix.org/s3fs-public/cdn/osdi16-kalia.pdf)：精读 §3.3.1（第 7 页）、§4.1–4.5（第 9–10 页），对照 §5 的哈希表布局（第 11 页）。[报告幻灯](https://files.usenix.org/s3fs-public/conference/protected-files/osdi16_slides_kalia.pdf)：对照第 4、7–10 页的两条查找路径及传输示意。未独立复现实验。
- 课程页只节选 [图 4](https://files.usenix.org/s3fs-public/cdn/osdi16-kalia.pdf#page=10) 柱图（正式版印刷页 193，不包括原图注和邻近正文）。用于逐柱讲解硬件分组、消融顺序和单位，保留图例、坐标与两组对照；不是整篇替代品。未核实 PDF 或幻灯整件再分发许可，故整件仅保留原始链接。
- [作者代码固定版本](https://github.com/efficient/fasst/tree/580abef01b48be4e1ab7f0d9ac95e554cccb4ce5)：阅读 `rpc/README.md` 和 `rpc/rpc_datapath.cc` 中的 `send_reqs`、`poll_comps`。备份包含上游说明、相关 RPC 源文件和 Apache-2.0 许可全文；不包括另有来源的驱动和 MICA 代码，不是可独立构建的完整仓库。
