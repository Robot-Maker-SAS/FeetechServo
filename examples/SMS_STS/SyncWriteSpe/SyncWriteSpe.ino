#include <SCServo.h>
SMS_STS sms_sts;

byte ID[2];
s16 Speed[2];
byte ACC[2];

void setup()
{
  //Serial1.begin(115200);//SMS servo baud rate 115200
  Serial1.begin(1000000);//STS servo baud rate 1000000
  sms_sts.pSerial = &Serial1;
  delay(1000);
  sms_sts.WheelMode(1);//servo ID1 switches to constant speed mode
  sms_sts.WheelMode(2);//servo ID2 switches to constant speed mode
  ID[0] = 1;//servo ID1
  ID[1] = 2;//servo ID2
  ACC[0] = 50;//acceleration A=50*8.7deg/s^2
  ACC[1] = 50;//acceleration A=50*8.7deg/s^2
}

void loop()
{
  //servos (ID1/ID2) accelerate at A=50*8.7deg/s^2 up to max speed V=60*0.732=43.92rpm and hold constant forward rotation
  Speed[0] = 60;
  Speed[1] = 60;
  sms_sts.SyncWriteSpe(ID, 2, Speed, ACC);
  delay(5000);

  //servos (ID1/ID2) decelerate at A=50*8.7deg/s^2 down to speed 0 and stop rotating
  Speed[0] = 0;
  Speed[1] = 0;
  sms_sts.SyncWriteSpe(ID, 2, Speed, ACC);
  delay(2000);

  //servos (ID1/ID2) accelerate at A=50*8.7deg/s^2 up to max speed V=-60*0.732=-43.92rpm and hold constant reverse rotation
  Speed[0] = -60;
  Speed[1] = -60;
  sms_sts.SyncWriteSpe(ID, 2, Speed, ACC);
  delay(5000);

  //servos (ID1/ID2) decelerate at A=50*8.7deg/s^2 down to speed 0 and stop rotating
  Speed[0] = 0;
  Speed[1] = 0;
  sms_sts.SyncWriteSpe(ID, 2, Speed, ACC);
  delay(2000);
}
