/*
Sync write example, tested and passed on the SMS40BL. Factory speed unit is 0.732rpm, servo running speed V=80.
If the factory speed unit in use is 0.0146rpm instead, change the speed to V=4000; delay formula T=[(P1-P0)/V]*1000+[V/(A*100)]*1000
*/

#include <SCServo.h>

SMS_STS sm;

byte ID[2];
s16 Position[2];
u16 Speed[2];
byte ACC[2];

void setup()
{
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
  delay(1000);
  ID[0] = 1;
  ID[1] = 2;
  Speed[0] = 80;
  Speed[1] = 80;
  ACC[0] = 100;
  ACC[1] = 100;
}

void loop()
{
  Position[0] = 4095;
  Position[1] = 4095;
  sm.SyncWritePosEx(ID, 2, Position, Speed, ACC);//servos (ID1/ID2) move to position P1=4095 at max speed V=80 (50*80 steps/s), acceleration A=100 (100*100 steps/s^2)
  delay(1495);//[(P1-P0)/(50*V)]*1000+[(50*V)/(A*100)]*1000

  Position[0] = 0;
  Position[1] = 0;
  sm.SyncWritePosEx(ID, 2, Position, Speed, ACC);//servos (ID1/ID2) move to position P0=0 at max speed V=80 (50*80 steps/s), acceleration A=100 (100*100 steps/s^2)
  delay(1495);//[(P1-P0)/(50*V)]*1000+[(50*V)/(A*100)]*1000
}
