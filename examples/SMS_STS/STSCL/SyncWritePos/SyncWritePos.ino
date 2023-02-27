/*
同步写例子在STS3215中测试通过，舵机出厂速度单位为0.0146rpm，舵机机运行速度V=3400
如果使用的出厂速度单位是0.732rpm，则速度改为V=68，延时公式T=[(P1-P0)/(50*V)]*1000+[(50*V)/(A*100)]*1000
*/

#include <SCServo.h>
SMS_STS st;

byte ID[2];
s16 Position[2];
u16 Speed[2];
byte ACC[2];

void setup()
{
  Serial1.begin(1000000);
  st.pSerial = &Serial1;
  delay(1000);
  ID[0] = 1;
  ID[1] = 2;
  Speed[0] = 3400;
  Speed[1] = 3400;
  ACC[0] = 50;
  ACC[1] = 50;
}

void loop()
{
  Position[0] = 4095;
  Position[1] = 4095;
  st.SyncWritePosEx(ID, 2, Position, Speed, ACC);//舵机(ID1/ID2)以最高速度V=3400步/秒，加速度A=50(50*100步/秒^2)，运行至P1=4095位置
  delay(1884);//((P1-P0)/V)*1000+(V/(A*100))*1000

  Position[0] = 0;
  Position[1] = 0;
  st.SyncWritePosEx(ID, 2, Position, Speed, ACC);//舵机(ID1/ID2)以最高速度V=3400步/秒，加速度A=50(50*100步/秒^2)，运行至P0=0位置
  delay(1884);//((P1-P0)/V)*1000+(V/(A*100))*1000
}
