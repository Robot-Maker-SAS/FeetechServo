/*
Servo parameter programming
*/

#include <SCServo.h>

int LEDpin = 13;
SMS_STS sms_sts;

void setup()
{
  pinMode(LEDpin, OUTPUT);
  Serial1.begin(115200);//SMS servo baud rate 115200
  //Serial1.begin(1000000);//STS servo baud rate 1000000
  sms_sts.pSerial = &Serial1;
  delay(1000);
  digitalWrite(LEDpin, LOW);
  sms_sts.unLockEprom(1);//enable EPROM save
  sms_sts.writeByte(1, SMS_STS_ID, 2);//ID
  sms_sts.LockEprom(2);//disable EPROM save
  digitalWrite(LEDpin, HIGH);
}

void loop()
{

}
