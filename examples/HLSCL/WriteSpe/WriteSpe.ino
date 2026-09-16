#include <SCServo.h>

HLSCL hlscl;

void setup()
{
  //Serial1.begin(1000000, SERIAL_8N1, 18, 17);//esp32-s3
  Serial1.begin(1000000);//mega2560
  hlscl.pSerial = &Serial1;
  delay(1000);
  hlscl.WheelMode(1);//servo ID1 switches to constant speed mode
}

void loop()
{
  //servo (ID1) accelerates at A=50*8.7deg/s^2 up to max speed V=60*0.732=43.92rpm and holds constant forward rotation, max torque current T=500*6.5=3250mA
  hlscl.WriteSpe(1, 60, 50, 500);
  delay(5000);

  //servo (ID1) decelerates at A=50*8.7deg/s^2 down to speed 0 and stops rotating
  hlscl.WriteSpe(1, 0, 50, 500);
  delay(2000);

  //servo (ID1) accelerates at A=50*8.7deg/s^2 up to max speed V=-60*0.732=-43.92rpm and holds constant reverse rotation, max torque current T=500*6.5=3250mA
  hlscl.WriteSpe(1, -60, 50, 500);
  delay(5000);

  //servo (ID1) decelerates at A=50*8.7deg/s^2 down to speed 0 and stops rotating
  hlscl.WriteSpe(1, 0, 50, 500);
  delay(2000);
}
