#include <SCServo.h>

HLSCL hlscl;

void setup()
{
  //Serial1.begin(1000000, SERIAL_8N1, 18, 17);//esp32-s3
  Serial1.begin(1000000);//mega2560
  hlscl.pSerial = &Serial1;
  delay(1000);
}

void loop()
{
  //servos (ID1/ID2) move to position P1=4095 at max speed V=60*0.732=43.92rpm, acceleration A=50*8.7deg/s^2, max torque current T=500*6.5=3250mA
  hlscl.RegWritePosEx(1, 4095, 60, 50, 500);
  hlscl.RegWritePosEx(2, 4095, 60, 50, 500);
  hlscl.RegWriteAction();
  delay((4095-0)*1000/(60*50) + (60*50)*10/(50) + 50);//[(P1-P0)/(V*50)]*1000+[(V*50)/(A*100)]*1000 + 50 (margin)

  //servos (ID1/ID2) move to position P0=0 at max speed V=60*0.732=43.92rpm, acceleration A=50*8.7deg/s^2, max torque current T=500*6.5=3250mA
  hlscl.RegWritePosEx(1, 0, 60, 50, 500);
  hlscl.RegWritePosEx(2, 0, 60, 50, 500);
  hlscl.RegWriteAction();
  delay((4095-0)*1000/(60*50) + (60*50)*10/(50) + 50);//[(P1-P0)/(V*50)]*1000+[(V*50)/(A*100)]*1000 + 50 (margin)
}
