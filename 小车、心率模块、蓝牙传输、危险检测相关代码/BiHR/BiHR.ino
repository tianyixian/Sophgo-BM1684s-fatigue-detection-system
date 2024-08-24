//////////////////////////////////////////////////////////////////////////////////////////
//
//   Arduino Library for ADS1292R Shield/Breakout
//   用于上位机代码
  
//  |ads1292r 引脚名称 | Arduino 连接         |引脚功能          |
//  |----------------- |:--------------------:|-----------------:|
//  | VDD              | +5V                  |  Supply voltage  |
//  | PWDN/RESET       | D4                   |  Reset           |
//  | START            | D5                   |  Start Input     |
//  | DRDY             | D6                   |  Data Ready Outpt|
//  | CS               | D7                   |  Chip Select     |
//  | MOSI             | D11                  |  Slave In        |
//  | MISO             | D12                  |  Slave Out       |
//  | SCK              | D13                  |  Serial Clock    |
//  | GND              | Gnd                  |  Gnd             |
//
/////////////////////////////////////////////////////////////////////////////////////////


#include "sAds1292r.h"
#include "ecgRespirationAlgo.h"
#include <SPI.h>

volatile uint8_t globalHeartRate = 0;
volatile uint8_t globalRespirationRate=0;

//Pin declartion the other you need are controlled by the SPI library
const int ADS1292_DRDY_PIN = 6;
const int ADS1292_CS_PIN = 7;
const int ADS1292_START_PIN = 5;
const int ADS1292_PWDN_PIN = 4;

#define CES_CMDIF_PKT_START_1   0x0A
#define CES_CMDIF_PKT_START_2   0xFA
#define CES_CMDIF_TYPE_DATA     0x02
#define CES_CMDIF_PKT_STOP      0x0B
#define DATA_LEN                8
#define ZERO                    0

volatile char DataPacket[DATA_LEN];
char DataPacketFooter[2] = {ZERO, 0x5A};
const char DataPacketHeader[5] = {CES_CMDIF_PKT_START_1, CES_CMDIF_PKT_START_2, DATA_LEN, ZERO, CES_CMDIF_TYPE_DATA};

int16_t ecgWaveBuff, ecgFilterout;
int16_t resWaveBuff,respFilterout;

ads1292r ADS1292R;
ecg_respiration_algorithm ECG_RESPIRATION_ALGORITHM;

uint16_t CRC16_Check(const uint8_t *data,uint8_t len)
{
    uint16_t CRC16 = 0xFFFF;
    uint8_t state,i,j;
    for(i = 0; i < len; i++ )
    {
        CRC16 ^= data[i];
        for( j = 0; j < 8; j++)
        {
            state = CRC16 & 0x01;
            CRC16 >>= 1;
            if(state)
            {
                CRC16 ^= 0xA001;
            }
        }
    }
    return CRC16;
}


void sendDataThroughUART(void){

  DataPacket[0] = ecgFilterout;
  DataPacket[1] = ecgFilterout >> 8;
  DataPacket[2] = resWaveBuff;
  DataPacket[3] = resWaveBuff >> 8;

  DataPacket[4] = globalRespirationRate;
  DataPacket[5] = globalRespirationRate >> 8;
  DataPacket[6] = globalHeartRate;
  DataPacket[7] = globalHeartRate >> 8;
  // DataPacket[0] = ecgFilterout;
  // DataPacket[1] = resWaveBuff;
  // DataPacket[2] = globalRespirationRate;
  // DataPacket[3] = globalHeartRate;
  

  //send packet header
  Serial.write(0xA5);
  // for(int i=0; i<1; i++){

  //   Serial.write(DataPacketHeader[i]);
  // }

  //send 30003 data
  for(int i=0; i<DATA_LEN; i++) // transmit the data
  {
    Serial.write(DataPacket[i]);
  }

  //send packet footer
  DataPacketFooter[0]=CRC16_Check(DataPacket,8);
  for(int i=0; i<2; i++) // transmit the data
  {
    Serial.write(DataPacketFooter[i]);
  }
}

void setup()
{
  delay(2000);

  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  //CPOL = 0, CPHA = 1
  SPI.setDataMode(SPI_MODE1);
  // Selecting 1Mhz clock for SPI
  SPI.setClockDivider(SPI_CLOCK_DIV16);

  pinMode(ADS1292_DRDY_PIN, INPUT);
  pinMode(ADS1292_CS_PIN, OUTPUT);
  pinMode(ADS1292_START_PIN, OUTPUT);
  pinMode(ADS1292_PWDN_PIN, OUTPUT);

  Serial.begin(9600);
  ADS1292R.ads1292Init(ADS1292_CS_PIN,ADS1292_PWDN_PIN,ADS1292_START_PIN);
  Serial.println("Initiliziation is done");
}

void loop()
{
  ads1292OutputValues ecgRespirationValues;
  boolean ret = ADS1292R.getAds1292EcgAndRespirationSamples(ADS1292_DRDY_PIN,ADS1292_CS_PIN,&ecgRespirationValues);

  if (ret == true)
  {
    ecgWaveBuff = (int16_t)(ecgRespirationValues.sDaqVals[1] >> 8) ;  // ignore the lower 8 bits out of 24bits
    resWaveBuff = (int16_t)(ecgRespirationValues.sresultTempResp>>8) ;

    if(ecgRespirationValues.leadoffDetected == false)
    {
      ECG_RESPIRATION_ALGORITHM.ECG_ProcessCurrSample(&ecgWaveBuff, &ecgFilterout);   // filter out the line noise @40Hz cutoff 161 order
      ECG_RESPIRATION_ALGORITHM.QRS_Algorithm_Interface(ecgFilterout,&globalHeartRate); // calculate
      // respFilterout = ECG_RESPIRATION_ALGORITHM.Resp_ProcessCurrSample(resWaveBuff);
      // ECG_RESPIRATION_ALGORITHM.RESP_Algorithm_Interface(respFilterout,&globalRespirationRate);

    }else{
      ecgFilterout = 0;
      respFilterout = 0;
    }

    sendDataThroughUART();
  }
}
