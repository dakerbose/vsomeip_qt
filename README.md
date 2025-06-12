
# 简易工程智能座舱开发
## 基于vsomeip_qt_qnx

1_hello_world的内容是实现服务器和客户端发送hello 主要是基础功能测试 具体内容可以查看里面的readme
2_dashboard的内容是仪表盘的显示 目前因为实际设备的限制和工具链受限 只能在linux上面显示 在qnx上面目前显示屏不太行
3_vehicle_simulator的内容是驾驶模拟器的实现 后面会加入大模型对话的内容 目前是在rapspberry实现 后面考虑迁移到rk3576中 利用npu加速
Dashboard是前面二者的qmake实现 我不习惯qt-creator 这部分可以忽略或者参考
source存了本项目readme的图片资源
vsomeip_qnx子仓库是基于vscode qnx toolkit和qnx800工具栏链的实现 主要是实现交叉编译 qnx系统中是没有类似于linux的编译器

## QNX客户端和Linux服务端收发实验
二者均使用ssh和主机连接
![](source/qnx_client.png)

![](source/linux_server.png)

