# Sophgo-BM1684s-fatigue-detection-system
2024集创赛算能杯一等奖（企业大奖）| CICC3013团队 | 不必劳驾

Group members/Contributors: Yixian Tian, Jian Zhao, Zhimu Zhou

## 不必劳驾——基于算能芯片的货车驾驶安全监测系统
本项目主要针对公共服务中较为贫乏的货车驾驶疲劳监测系统功能的完善和集成，结合TPU优秀的边缘计算能力于其上搭载AI算法，实现疲劳检测、心率检测、姿态识别等多种集成功能，为目前业界疲劳检测系统产品简单、算法单一提供一种合理的优化方案。通过算子加速、进程并行等多种本地化方式最大优化推理速度，达到实际落地需求。

## 作品选题背景
交通安全危险是当前最严重的安全问题之一。对于需要长途驾驶的卡车来说，卡车司机的生命往往关系到一个并不富裕的家庭。然而在实际中卡车中发生疲劳驾驶的概率往往更高。现有数据显示，自动驾驶技术仍然无法解决疲劳驾驶的问题，且在卡车中的采用率相对较低。因此，我们打算开发一种主要用于卡车的产品，该产品可以执行疲劳检测，并能够在检测到疲劳一段时间后完成自动靠边停车，以确保卡车司机在长途驾驶期间的安全。
## 作品功能介绍
### 主要功能
对用户的疲劳程度进行检测，在倒数结束之前一定时间内对用户进行提醒操作，提醒未果则实现靠边停车，并联系控制中心。在进行疲劳状态检测的同时还可以对用户的心率、呼吸率、心电变异性等特征进行健康状态检测，如果心率过快或者心率不齐等出现异常心率情况则进行健康状况监测，同时在疲劳检测功能启动的同时对用户的心率进行实时监测并上传到手机客户端，全方位护航用户驾驶过程中生命健康和人身安全。同时，实现了危险驾驶检测，即使检测并提醒驾驶员在驾驶中打电话/抽烟等危险驾驶行为，并在多次题提醒之后将危险驾驶记录上报远程控制中心进行记录。驾驶可以使用语音来控制本地系统的各个功能配置。远程控制中心能够实时更新并保存，驾驶源的驾驶数据，到岗数据，疲劳数据等，以及车辆的编队管理。
在驾驶安全问题日益受到关注的今天，我们的产品可以为驾驶员提供更全面和安全的驾驶体验，为驾驶员和乘客的生命安全保驾护航。
### 作品优势与创新点
 作品针对货车疲劳驾驶市场痛点，在本地计算中枢上创新性构造轻量疲劳检测算法，实现了低成本、本地化疲劳检测功能，为货车驾驶、公路运输的安全保驾护航。作品的主要创新点如下：
1、我们使用了当前世界精度最高的目标检测算法和疲劳识别算法face_alignment，安全稳定，并能做到快速相应并提醒司机，争取危险前的黄金时间，为司机的驾驶安全保驾护航。
2、创新性地引入了心率检测模型，创新性地尝试使用心电图(electrocardiogram，ECG)提取的心率变异性(heart rate variability，HRV)等特征作为疲劳特征和身体健康特征的提取指标，并使用心率数据辅助视频模块进行疲劳检测。
3、将传统摄像头升级为红外夜视摄像头，能够自动根据光线切换摄像头输入，并针对夜间场景采集红外数据集进行模型训练，使疲劳检测在白天以及夜间的识别准确度都接近100%.
4、我们大量使用模型并行和算法并发技术，使用多进程线程并发，用进程池将一个模型分成多个，使计算速度提高了两倍以上，并大幅提高了板上资源利用率，能够同时运行疲劳检测、危险驾驶检测模型、心率检测模型等。
5、本作品在实现疲劳驾驶检测功能之外部署了大量外设，充分利用了少林派的各类串口，并尝试新增PCIe板来解决少林派通信瓶颈，使用蓝牙、wifi等多种通信模式解决少林派的通信问题。


