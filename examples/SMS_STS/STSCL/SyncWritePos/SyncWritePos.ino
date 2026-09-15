/*
Sync write example, tested and passed on the STS3215. Factory speed unit is 0.0146rpm, servo running speed V=3400.
If the factory speed unit in use is 0.732rpm instead, change the speed to V=68; delay formula T=[(P1-P0)/(50*V)]*1000+[(50*V)/(A*100)]*1000
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
  st.SyncWritePosEx(ID, 2, Position, Speed, ACC);//servos (ID1/ID2) move to position P1=4095 at max speed V=3400 steps/s, acceleration A=50 (50*100 steps/s^2)
  delay(1884);//((P1-P0)/V)*1000+(V/(A*100))*1000

  Position[0] = 0;
  Position[1] = 0;
  st.SyncWritePosEx(ID, 2, Position, Speed, ACC);//servos (ID1/ID2) move to position P0=0 at max speed V=3400 steps/s, acceleration A=50 (50*100 steps/s^2)
  delay(1884);//((P1-P0)/V)*1000+(V/(A*100))*1000
}
