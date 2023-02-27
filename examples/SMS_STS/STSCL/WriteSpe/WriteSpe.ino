/*
恒速模式例子在STS3215中测试通过，舵机出厂速度单位V=0为停止状态
*/

#include <SCServo.h>

SMS_STS st;

void setup()
{
  Serial1.begin(1000000);
  st.pSerial = &Serial1;
  delay(1000);
  st.unLockEprom(1);
  st.WheelMode(1);//恒速模式
  st.LockEprom(1);
}

void loop()
{
  st.WriteSpe(1, 3400, 50);//舵机(ID1)以最高速度V=3400步/秒，加速度A=50(50*100步/秒^2)，旋转
  delay(4000);
  st.WriteSpe(1, 0, 50);//舵机(ID1)以加速度A=50(50*100步/秒^2)，停止旋转(V=0)
  delay(2000);
  st.WriteSpe(1, -3400, 50);//舵机(ID1)以最高速度V=-3400步/秒，加速度A=50(50*100步/秒^2)，反向旋转
  delay(4000);
  st.WriteSpe(1, 0, 50);//舵机(ID1)以加速度A=50(50*100步/秒^2)，停止旋转(V=0)
  delay(2000);
}
