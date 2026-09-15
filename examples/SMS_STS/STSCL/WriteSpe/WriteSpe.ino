/*
Constant speed mode example, tested and passed on the STS3215. A speed unit of V=0 is the stopped state.
*/

#include <SCServo.h>

SMS_STS st;

void setup()
{
  Serial1.begin(1000000);
  st.pSerial = &Serial1;
  delay(1000);
  st.unLockEprom(1);
  st.WheelMode(1);//constant speed mode
  st.LockEprom(1);
}

void loop()
{
  st.WriteSpe(1, 3400, 50);//servo (ID1) rotates at max speed V=3400 steps/s, acceleration A=50 (50*100 steps/s^2)
  delay(4000);
  st.WriteSpe(1, 0, 50);//servo (ID1) stops rotating (V=0) with acceleration A=50 (50*100 steps/s^2)
  delay(2000);
  st.WriteSpe(1, -3400, 50);//servo (ID1) rotates in reverse at max speed V=-3400 steps/s, acceleration A=50 (50*100 steps/s^2)
  delay(4000);
  st.WriteSpe(1, 0, 50);//servo (ID1) stops rotating (V=0) with acceleration A=50 (50*100 steps/s^2)
  delay(2000);
}
