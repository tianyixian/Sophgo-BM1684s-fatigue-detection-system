# -BM1684-
2024集创赛算能杯一等奖（企业大奖）| CICC3013团队 | 不必劳驾

Group members/Contributors: Yixian Tian, Jian Zhao, Zhimu Zhou

## 不必劳驾——基于算能芯片的火车驾驶安全监测系统
本项目主要针对公共服务中较为贫乏的货车驾驶疲劳监测系统功能的完善和集成，结合TPU优秀的边缘计算能力于其上搭载AI算法，实现疲劳检测、心率检测、姿态识别等多种集成功能，为目前业界疲劳检测系统产品简单、算法单一提供一种合理的优化方案。通过算子加速、进程并行等多种本地化方式最大优化推理速度，达到实际落地需求。

1.1 作品选题背景
交通安全危险是当前最严重的安全问题之一。对于需要长途驾驶的卡车来说，卡车司机的生命往往关系到一个并不富裕的家庭。然而在实际中卡车中发生疲劳驾驶的概率往往更高。现有数据显示，自动驾驶技术仍然无法解决疲劳驾驶的问题，且在卡车中的采用率相对较低。因此，我们打算开发一种主要用于卡车的产品，该产品可以执行疲劳检测，并能够在检测到疲劳一段时间后完成自动靠边停车，以确保卡车司机在长途驾驶期间的安全。
1.2 作品功能介绍
我们构建的模拟现实疲劳驾驶检测的模型中有两个部分，分别是搭载了疲劳检测系统的TPU (bm1684) 以及搭载了aduino和驱动控制模块的小车。我们的产品能够在驾驶过程中实时检测驾驶员的状态，并通过自主研发的算法让驾驶员提前获得必要的提示和警告。当我们的系统检测到司机疲劳驾驶时，驾驶员会立即收到警告提示，若多次提示未果，则采取紧急靠边停车措施，以及联系控制中心等相关功能。
在驾驶安全问题日益受到关注的今天，我们的产品可以为驾驶员提供更全面和安全的驾驶体验，为驾驶员和乘客的生命安全保驾护航。
1.2.1 主要功能
对用户的疲劳程度进行检测，在倒数结束之前一定时间内对用户进行提醒操作，提醒未果则实现靠边停车。
1.2.2 作品优势
我们使用了目标检测算法和疲劳识别算法，安全稳定，检测精度高，并能做到快速相应并提醒司机，争取危险前的黄金时间，为司机的驾驶安全保驾护航。
