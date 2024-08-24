import array
import serial
import threading
import pyqtgraph as pg
import numpy as np
import time



# 假设这些宏定义和全局变量已经被正确地转换和初始化
CES_CMDIF_PKT_START_1 = 0x0A
CES_CMDIF_PKT_START_2 = 0xFA
CES_CMDIF_TYPE_DATA = 0x02
CES_CMDIF_PKT_STOP = 0x0B
DATA_LEN = 4
ZERO = 0

DataPacket = bytearray(4)
DataPacketFooter = bytearray([ZERO, 0x5A])
DataPacketHeader = bytearray([CES_CMDIF_PKT_START_1, CES_CMDIF_PKT_START_2, DATA_LEN, ZERO, CES_CMDIF_TYPE_DATA])
voltage, heart_rate=0,0

# 假设ads1292r和ecg_respiration_algorithm类以及相应的方法和属性已经被正确地定义


historyLength = 200  # 横坐标长度
voltage_data = np.zeros(historyLength).__array__('d')
heart_rate_data = np.zeros(historyLength).__array__('d')

com3_port = 'COM4'
com4_port = 'COM7'
baud_rate = 9600  # 设置波特率

# 打开 COM3 串口
ser_com3 = serial.Serial(com3_port, baud_rate, timeout=1)
# 打开 COM4 串口
ser_com4 = serial.Serial(com4_port, 9600, timeout=1)


i = 0


def Serial():
    while(True):
        print("heartrate:",heart_rate)
        time.sleep(0.05)
        # 以下是处理数据的代码，根据实际情况进行调整
        global i
        global voltage_data, heart_rate_data
        # 假设 data 是一个列表，存储着电压和心率的元组
        if i < historyLength:
            voltage_data = np.append(voltage_data, voltage)
            heart_rate_data = np.append(heart_rate_data, heart_rate)
            i += 1
        else:
            # 如果数据达到历史长度，开始覆盖旧数据
            voltage_data = voltage_data[1:]
            heart_rate_data = heart_rate_data[1:]
            voltage_data = np.append(voltage_data, voltage)
            heart_rate_data = np.append(heart_rate_data, heart_rate)



def plotData():
    # time.sleep(0.1)
    curve.setData(voltage_data)
    heart_rate_curve.setData(heart_rate_data)  # 初始化心率曲线的数据


def readThread():
    while(True):
        line = ser_com3.readline().decode().strip()
        if line:
            try:
                global voltage
                global heart_rate
                # 分割字符串并转换为整数
                voltage, heart_rate = map(int, line.split())
            except ValueError:
                # 如果数据格式不正确，打印错误信息
                print("Error encoding data:", line)

def sendDataThread():
    while(True):
        global voltage, heart_rate
        sendDataThroughUART(voltage, heart_rate)

def sendDataThroughUART(ecgFilterout,globalHeartRate):

    # 填充数据包（这里只是示例，您需要根据实际情况填充数据）
    DataPacket[0] = (ecgFilterout & 0xFF)
    DataPacket[1] = (ecgFilterout >> 8) & 0xFF
    DataPacket[2] = (globalHeartRate & 0xFF)
    DataPacket[3] = (globalHeartRate >> 8) & 0xFF
    # 注意：ecgFilterout, resWaveBuff等需要根据实际情况填充
    # 发送数据包头部
    # ser.write(DataPacketHeader)  # 如果需要发送头部
    ser_com4.write(bytes([0xA5]))
    # 发送数据包数据
    for byte in DataPacket:
        ser_com4.write(bytes([byte]))
    # 计算CRC校验码并发送数据包尾部
    # DataPacketFooter[0] = CRC16_Check(DataPacket) & 0xFF
    DataPacketFooter[0] = (DataPacket[0]+DataPacket[1]+DataPacket[2]+DataPacket[3]) & 0xFF
    ser_com4.write(DataPacketFooter)
    print(voltage,heart_rate)
    print("Data ",voltage," ",heart_rate," succfully Sent to Phone")
    time.sleep(0.02)

if __name__ == "__main__":
    app = pg.mkQApp()  # 建立app
    win = pg.GraphicsLayoutWidget(show=True)
    win.setWindowTitle(u'HeartBeat Monitor')
    win.resize(800, 500)  # 小窗口大小
    # voltage_data = array.array('i')  # 可动态改变数组的大小,double型数组
    # heart_rate_data = array.array('i')  # 可动态改变数组的大小,double型数组
    a = 0
    p = win.addPlot()  # 把图p加入到窗口中
    p.showGrid(x=True, y=True)  # 把X和Y的表格打开
    p.setRange(xRange=[0, historyLength], yRange=[0, 255], padding=0)
    p.setLabel(axis='left', text='y / V')  # 靠左
    p.setLabel(axis='bottom', text='x / point')
    p.setTitle('semg')  # 表格的名字
    curve = p.plot()  # 绘制一个图形
    curve.setData(voltage_data)
    heart_rate_curve = p.plot()
    heart_rate_curve.setData(heart_rate_data)  # 初始化心率曲线的数据
    portx = com3_port
    bps = 9600
    # # 串口执行到这已经打开 再用open命令会报错
    # mSerial = serial.Serial(portx, int(bps))
    # if (mSerial.isOpen()):
    #     print("open success")
    #     mSerial.write("hello".encode()) # 向端口些数据 字符串必须译码
    #     mSerial.flushInput()  # 清空缓冲区
    # else:
    #     print("open failed")
    #     serial.close()  # 关闭端口
    th2 = threading.Thread(target=Serial)#目标函数一定不能带（）被这个BUG搞了好久
    th3 = threading.Thread(target=sendDataThread)
    th1 = threading.Thread(target=readThread)
    th1.start()
    th2.start()
    th3.start()
    timer = pg.QtCore.QTimer()
    timer.timeout.connect(plotData)  # 定时刷新数据显示
    timer.start(50)  # 多少ms调用一次
    app.exec_()
