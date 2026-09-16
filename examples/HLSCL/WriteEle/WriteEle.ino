#include <SCServo.h>

HLSCL hlscl;

void setup()
{
  //Serial1.begin(1000000, SERIAL_8N1, 18, 17);//esp32-s3
  Serial1.begin(1000000);//mega2560
  hlscl.pSerial = &Serial1;
  delay(1000);
  hlscl.EleMode(1);//servo ID1 switches to constant force (torque) mode
}

void loop()
{
  //servo (ID1) rotates forward with max torque current T=300*6.5=1950mA
  hlscl.WriteEle(1, 300);
  delay(5000);

  //servo (ID1) stops rotating with torque 0
  hlscl.WriteEle(1, 0);
  delay(2000);

  //servo (ID1) rotates in reverse with max torque current T=300*6.5=1950mA
  hlscl.WriteEle(1, -300);
  delay(5000);

  //servo (ID1) stops rotating with torque 0
  hlscl.WriteEle(1, 0);
  delay(2000);
}
