/*
Normal write example, tested and passed on the SMS80CL. Factory speed unit is 0.0146rpm, servo running speed V=2400.
If the factory speed unit in use is 0.732rpm instead, change the speed to V=48; delay formula T=[(P1-P0)/(50*V)]*1000+[(50*V)/(A*100)]*1000
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
  sm.WritePosEx(1, 4095, 2400, 50);//servo (ID1) moves to position P1=4095 at max speed V=2400 steps/s, acceleration A=50 (50*100 steps/s^2)
  delay(2240);//[(P1-P0)/V]*1000+[V/(A*100)]*1000

  sm.WritePosEx(1, 0, 2400, 50);//servo (ID1) moves to position P0=0 at max speed V=2400 steps/s, acceleration A=50 (50*100 steps/s^2)
  delay(2240);//[(P1-P0)/V]*1000+[V/(A*100)]*1000
}
