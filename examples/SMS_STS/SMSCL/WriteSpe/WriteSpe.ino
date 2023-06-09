/*
恒速模式例子在SMS85CL中测试通过，舵机出厂速度单位V=0为停止状态
*/

#include <SCServo.h>

SMS_STS sm;

void setup()
{
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
  delay(1000);
  sm.WheelMode(1);//恒速模式
}

void loop()
{
  sm.WriteSpe(1, 2400, 50);//舵机(ID1)以最高速度V=2400步/秒，加速度A=50(50*100步/秒^2)，旋转
  delay(4000);
  sm.WriteSpe(1, 0, 50);//舵机(ID1)以加速度A=50(50*100步/秒^2)，停止旋转(V=0)
  delay(2000);
  sm.WriteSpe(1, -2400, 50);//舵机(ID1)以最高速度V=-2400步/秒，加速度A=50(50*100步/秒^2)，反向旋转
  delay(4000);
  sm.WriteSpe(1, 0, 50);//舵机(ID1)以加速度A=50(50*100步/秒^2)，停止旋转(V=0)
  delay(2000);
}
