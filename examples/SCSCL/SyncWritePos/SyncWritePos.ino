/*
Sync write example, tested and passed on the SCS15. If testing another SCS series servo model,
adjust the position, speed, and delay parameters accordingly.
*/

#include <SCServo.h>

SCSCL sc;

byte ID[2];
u16 Position[2];
u16 Speed[2];

void setup()
{
  Serial1.begin(1000000);
  sc.pSerial = &Serial1;
  delay(1000);
  ID[0] = 1;
  ID[1] = 2;
}

void loop()
{
  Position[0] = 1000;
  Position[1] = 1000;
  Speed[0] = 1500;
  Speed[1] = 1500;
  sc.SyncWritePos(ID, 2, Position, 0, Speed);//servos (ID1/ID2) move to P1=1000 at max speed V=1500 steps/s
  delay(754);//[(P1-P0)/V]*1000+100

  Position[0] = 20;
  Position[1] = 20;
  Speed[0] = 1500;
  Speed[1] = 1500;
  sc.SyncWritePos(ID, 2, Position, 0, Speed);//servos (ID1/ID2) move to P1=20 at max speed V=1500 steps/s
  delay(754);//[(P1-P0)/V]*1000+100
}
