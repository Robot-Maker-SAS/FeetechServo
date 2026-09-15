/*
Async write example, tested and passed on the SCS15. If testing another SCS series servo model,
adjust the position, speed, and delay parameters accordingly.
*/

#include <SCServo.h>

SCSCL sc;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(1000000);
  sc.pSerial = &Serial1;
  delay(1000);
}

void loop()
{
  sc.RegWritePos(1, 1000, 0, 1500);//servo (ID1) moves to P1=1000 at max speed V=1500 steps/s
  sc.RegWritePos(2, 1000, 0, 1500);//servo (ID2) moves to P1=1000 at max speed V=1500 steps/s
  sc.RegWriteAction();
  delay(754);//[(P1-P0)/V]*1000+100

  sc.RegWritePos(1, 20, 0, 1500);//servo (ID1) moves to P1=20 at max speed V=1500 steps/s
  sc.RegWritePos(2, 20, 0, 1500);//servo (ID2) moves to P1=20 at max speed V=1500 steps/s
  sc.RegWriteAction();
  delay(754);//[(P1-P0)/V]*1000+100
}
