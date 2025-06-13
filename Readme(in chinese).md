
# 异构嵌入式智能座舱系统

基于 Raspberry Pi 和 RK3576 构建多域协同车载控制系统，使用 QNX 和 Linux 实现三域分工，部署轻量大语言模型，模拟智能座舱的交互、控制与可视化链路

实现以下目标：

系统通过 vsomeip 形成“AI语义→控制逻辑→仪表反馈”的端到端闭环；

在 RK3576 上部署量化大语言模型（如 ChatGLM）并使用 NPU 进行推理加速；

在 Raspberry Pi 上部署 QNX8.0，完成 vsomeip 通信与状态管理任务；

使用 Qt 构建仪表 UI，实现速度、档位、油门等实时可视化动态效果。



| 控制器     | 系统 |    职责描述     |
| :---        |    :----:   |          ---: |
| RK3576      |  Linux npu      | AI语义解析、命令下发、UI可选展示   |
| Raspberry Pi (QNX)   | QNX 8 RTOS    | 指令接收、逻辑判断、状态生成与广播      |
| Raspberry Pi (Ubuntu)   | Ubuntu + Qt | 接收状态广播并驱动仪表盘界面更新     |