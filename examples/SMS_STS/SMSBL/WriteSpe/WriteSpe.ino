/*
Constant speed mode example, tested and passed on the SMS40BL. A speed unit of V=0 is the stopped state.
*/

#include <SCServo.h>

SMS_STS sm;

void setup()
{
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
  delay(1000);
  sm.WheelMode(1);//constant speed mode
}

void loop()
{
  sm.WriteSpe(1, 80, 100);//servo (ID1) rotates at max speed V=80 (50*80 steps/s), acceleration A=100 (100*100 steps/s^2)
  delay(2000);
  sm.WriteSpe(1, 0, 100);//servo (ID1) stops rotating (V=0) with acceleration A=100 (100*100 steps/s^2)
  delay(2000);
  sm.WriteSpe(1, -80, 100);//servo (ID1) rotates in reverse at max speed V=-80 (-50*80 steps/s), acceleration A=100 (100*100 steps/s^2)
  delay(2000);
  sm.WriteSpe(1, 0, 100);//servo (ID1) stops rotating (V=0) with acceleration A=100 (100*100 steps/s^2)
  delay(2000);
}
