/*
Normal write example, tested and passed on the SMS40BL. Factory speed unit is 0.732rpm, servo running speed V=80.
If the factory speed unit in use is 0.0146rpm instead, change the speed to V=4000; delay formula T=[(P1-P0)/V]*1000+[V/(A*100)]*1000
*/

#include <SCServo.h>

SMS_STS sm;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
  delay(1000);
}

void loop()
{
  sm.WritePosEx(1, 4095, 80, 100);//servo (ID1) moves to position P1=4095 at max speed V=80 (50*80 steps/s), acceleration A=100 (100*100 steps/s^2)
  delay(1495);//[(P1-P0)/(50*V)]*1000+[(50*V)/(A*100)]*1000

  sm.WritePosEx(1, 0, 80, 100);//servo (ID1) moves to position P0=0 at max speed V=80 (50*80 steps/s), acceleration A=100 (100*100 steps/s^2)
  delay(1495);//[(P1-P0)/(50*V)]*1000+[(50*V)/(A*100)]*1000
}
