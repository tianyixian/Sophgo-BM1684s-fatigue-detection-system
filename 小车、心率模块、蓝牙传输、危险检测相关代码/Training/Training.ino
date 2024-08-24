#include <SoftwareSerial.h>

int input1 = 5; // 定义uno的pin 5 向 input1 输出 
int input2 = 6; // 定义uno的pin 6 向 input2 输出
int input3 = 9; // 定义uno的pin 9 向 input3 输出
int input4 = 10; // 定义uno的pin 10 向 input4 输出
const int trigPin = 2;
const int echoPin = 3;

long duration;
int distance;
int PIR_pin = 12;
int LED_pin = 13;

int buzzer=8;
int cc=0;

// 设置Arduino软件串口，10-RX,11-TX
const int BT_RX = 11;
const int BT_TX = 12;
// Pin10为RX，接HC05的TXD
// Pin11为TX，接HC05的RXD
SoftwareSerial BT(BT_RX, BT_TX );


void setup() {
  pinMode(buzzer, OUTPUT);

  // 初始化各IO,模式为OUTPUT 输出模式
  pinMode(input1,OUTPUT);
  pinMode(input2,OUTPUT);
  pinMode(input3,OUTPUT);
  pinMode(input4,OUTPUT);
  
  // 初始化人体感应模块为输入
  pinMode(PIR_pin, INPUT);

  // 初始化LED模块
  pinMode(LED_pin, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600); //初始化Arduino串口，波特率自定，这里选38400
	Serial.println("Serial is ready!"); //测试与PC之间串口是否正常，正常则显示上述文字，异常则显示乱码
	BT.begin(9600); // HC-05的AT模式默认通信波特率为38400
  BT.println("BT is ready!");
}

void loop() {
      // Serial.println("up");
      // digitalWrite(LED_pin, HIGH);
      // //forward 向前转
      // analogWrite(input1,0);
      // analogWrite(input2,225/2);
      // analogWrite(input3,0);
      // analogWrite(input4,225/2);

      // delay(2*1000);

      // digitalWrite(LED_pin, LOW);
      

      // analogWrite(input1,0);
      // analogWrite(input2,0);
      // analogWrite(input3,0);
      // analogWrite(input4,225/2);

      // delay(1*600);

      // analogWrite(input1,0);
      // analogWrite(input2,225/2);
      // analogWrite(input3,0);
      // analogWrite(input4,225/2);

      // delay(1*1000);


      // analogWrite(input1,0);
      // analogWrite(input2,225/2);
      // analogWrite(input3,0);
      // analogWrite(input4,0);

      // delay(1*600);

      
      // analogWrite(input1,0);
      // analogWrite(input2,225/2);
      // analogWrite(input3,0);
      // analogWrite(input4,225/2);

      // delay(1*500);



      // //stop
      // analogWrite(input1,0);
      // analogWrite(input2,150/2);
      // analogWrite(input3,0);
      // analogWrite(input4,150/2);
      // delay(500);
      // analogWrite(input1,0);
      // analogWrite(input2,100/2);
      // analogWrite(input3,0);
      // analogWrite(input4,100/2);
      // delay(500);
      // analogWrite(input1,0);
      // analogWrite(input2,50/2);
      // analogWrite(input3,0);
      // analogWrite(input4,50/2);
      // delay(100);
      // analogWrite(input1,0);
      // analogWrite(input2,0/2);
      // analogWrite(input3,0);
      // analogWrite(input4,0/2);
    

  BT.println("Waiting for instruction...");
  while(1){
    //BT.println("w");   
    if(BT.available()>0){
      BT.println(cc=BT.read());
      if(cc == 's')
        break;
    }
  }
  digitalWrite(LED_pin, HIGH);
  int condition = -1;
  while(1){
    if(BT.available()){
      condition = BT.read() - '0';
    }
    //Serial.println("up");
    digitalWrite(LED_pin, HIGH);
    //forward 向前转
    analogWrite(input1,0);
    analogWrite(input2,225/2);
    analogWrite(input3,0);
    analogWrite(input4,225/2);
    
    if(condition == 1){
      int i = 1;
      BT.println("down");
      for(i = 1; i<=1000; i++){
        digitalWrite(buzzer, HIGH);
        delay(1);
        digitalWrite(buzzer, LOW);
        delay(1);
      }
      digitalWrite(LED_pin, LOW);
      analogWrite(input1,0);
      analogWrite(input2,225/2);
      analogWrite(input3,0);
      analogWrite(input4,225/2);

      delay(1*1000);

      digitalWrite(LED_pin, LOW);
      

      analogWrite(input1,0);
      analogWrite(input2,0);
      analogWrite(input3,0);
      analogWrite(input4,225/2);

      delay(1*1000);

      analogWrite(input1,0);
      analogWrite(input2,225/2);
      analogWrite(input3,0);
      analogWrite(input4,225/2);

      delay(1*1000);


      while(1){
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH);
        distance = duration * 0.034 / 2;
        BT.print("Distance: ");
        BT.print(distance);
        BT.println(" cm");
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");
      
        if(distance<30){
          break;
        }
        delay(500);
      }


      analogWrite(input1,0);
      analogWrite(input2,225/2);
      analogWrite(input3,0);
      analogWrite(input4,0);

      delay(1*1000);

      
      analogWrite(input1,0);
      analogWrite(input2,225/2);
      analogWrite(input3,0);
      analogWrite(input4,225/2);

      delay(1*500);



      //stop
      analogWrite(input1,0);
      analogWrite(input2,150/2);
      analogWrite(input3,0);
      analogWrite(input4,150/2);
      delay(500);
      analogWrite(input1,0);
      analogWrite(input2,100/2);
      analogWrite(input3,0);
      analogWrite(input4,100/2);
      delay(500);
      analogWrite(input1,0);
      analogWrite(input2,50/2);
      analogWrite(input3,0);
      analogWrite(input4,50/2);
      delay(100);
      analogWrite(input1,0);
      analogWrite(input2,0/2);
      analogWrite(input3,0);
      analogWrite(input4,0/2);
      break;
    }
  }


while(1)
{}

}