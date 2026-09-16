#include <SCServo.h>
HLSCL hlscl;

byte ID[2];
s16 Speed[2];
byte ACC[2];
u16 Torque[2];

void setup()
{
  //Serial1.begin(1000000, SERIAL_8N1, 18, 17);//esp32-s3
  Serial1.begin(1000000);//mega2560
  hlscl.pSerial = &Serial1;
  delay(1000);
  hlscl.WheelMode(1);//servo ID1 switches to constant speed mode
  hlscl.WheelMode(2);//servo ID2 switches to constant speed mode
  ID[0] = 1;//servo ID1
  ID[1] = 2;//servo ID2
  ACC[0] = 50;//acceleration A=50*8.7deg/s^2
  ACC[1] = 50;//acceleration A=50*8.7deg/s^2
  Torque[0] = 500;//max torque current T=500*6.5=3250mA
  Torque[1] = 500;//max torque current T=500*6.5=3250mA
}

void loop()
{
  //servos (ID1/ID2) accelerate at A=50*8.7deg/s^2 up to max speed V=60*0.732=43.92rpm and hold constant rotation, max torque current T=500*6.5=3250mA
  Speed[0] = 60;
  Speed[1] = 60;
  hlscl.SyncWriteSpe(ID, 2, Speed, ACC, Torque);
  delay(5000);

  //servos (ID1/ID2) decelerate at A=50*8.7deg/s^2 down to speed 0 and stop
  Speed[0] = 0;
  Speed[1] = 0;
  hlscl.SyncWriteSpe(ID, 2, Speed, ACC, Torque);
  delay(2000);

  //servos (ID1/ID2) accelerate at A=50*8.7deg/s^2 up to max speed V=-60*0.732=-43.92rpm and hold constant rotation, max torque current T=500*6.5=3250mA
  Speed[0] = -60;
  Speed[1] = -60;
  hlscl.SyncWriteSpe(ID, 2, Speed, ACC, Torque);
  delay(5000);

  //servos (ID1/ID2) decelerate at A=50*8.7deg/s^2 down to speed 0 and stop
  Speed[0] = 0;
  Speed[1] = 0;
  hlscl.SyncWriteSpe(ID, 2, Speed, ACC, Torque);
  delay(2000);
}
