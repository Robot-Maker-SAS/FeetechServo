/*
Servo parameter programming
*/

#include <SCServo.h>

int LEDpin = 13;
SCSCL sc;

void setup()
{
  pinMode(LEDpin, OUTPUT);
  Serial1.begin(1000000);
  sc.pSerial = &Serial1;
  delay(1000);
  digitalWrite(LEDpin, LOW);
  sc.unLockEprom(1);//enable EPROM save
  sc.writeByte(1, SCSCL_ID, 2);//ID
  sc.writeWord(2, SCSCL_MIN_ANGLE_LIMIT_L, 20);
  sc.writeWord(2, SCSCL_MAX_ANGLE_LIMIT_L, 1000);
  sc.LockEprom(2);////disable EPROM save
  digitalWrite(LEDpin, HIGH);
}

void loop()
{

}
