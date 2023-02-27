/*
异步写例子在SMS80CL中测试通过，舵机出厂速度单位为0.0146rpm，舵机机运行速度V=2400
如果使用的出厂速度单位是0.732rpm，则速度改为V=48，延时公式T=[(P1-P0)/(50*V)]*1000+[(50*V)/(A*100)]*1000
*/

#include <SCServo.h>

SMS_STS sm;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
  delay(1000);
}

void loop()
{
  sm.RegWritePosEx(1, 4095, 2400, 50);//舵机(ID1)以最高速度V=2400步/秒，加速度A=50(50*100步/秒^2)，运行至P1=4095位置
  sm.RegWritePosEx(2, 4095, 2400, 50);//舵机(ID2)以最高速度V=2400步/秒，加速度A=50(50*100步/秒^2)，运行至P1=4095位
  sm.RegWriteAction();
  delay(2240);//[(P1-P0)/V]*1000+[V/(A*100)]*1000

  sm.RegWritePosEx(1, 0, 2400, 50);//舵机(ID1)以最高速度V=2400步/秒，加速度A=50(50*100步/秒^2)，运行至P0=0位置
  sm.RegWritePosEx(2, 0, 2400, 50);//舵机(ID2)以最高速度V=2400步/秒，加速度A=50(50*100步/秒^2)，运行至P1=0位置
  sm.RegWriteAction();
  delay(2240);//[(P1-P0)/V]*1000+[V/(A*100)]*1000
}
