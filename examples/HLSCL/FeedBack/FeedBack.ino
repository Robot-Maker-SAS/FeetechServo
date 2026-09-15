/*
Read back all servo feedback parameters: position, speed, load, voltage, temperature, moving state, current.
The FeedBack function reads the servo parameters into a buffer; Readxxx(-1) returns the corresponding
state from that buffer. For Readxxx(ID): ID=-1 returns the buffered FeedBack value; ID>=0 issues a read
instruction directly and returns the given servo's state, with no need to call FeedBack first.
*/

#include <SCServo.h>

HLSCL hlscl;
int LEDpin = 13;

void setup()
{
  pinMode(LEDpin,OUTPUT);
  digitalWrite(LEDpin, HIGH);
  Serial1.begin(1000000);//mega2560
  //Serial1.begin(1000000, SERIAL_8N1, 18, 17);//esp32-s32
  Serial.begin(115200);
  hlscl.pSerial = &Serial1;
  delay(1000);
}

void loop()
{
  int Pos;
  int Speed;
  int Load;
  int Voltage;
  int Temper;
  int Move;
  int Current;
  hlscl.FeedBack(1);
  if(!hlscl.getLastError()){
    digitalWrite(LEDpin, LOW);
    Pos = hlscl.ReadPos(-1);
    Speed = hlscl.ReadSpeed(-1);
    Load = hlscl.ReadLoad(-1);
    Voltage = hlscl.ReadVoltage(-1);
    Temper = hlscl.ReadTemper(-1);
    Move = hlscl.ReadMove(-1);
    Current = hlscl.ReadCurrent(-1);
    Serial.print("Position:");
    Serial.println(Pos);
    Serial.print("Speed:");
    Serial.println(Speed);
    Serial.print("Load:");
    Serial.println(Load);
    Serial.print("Voltage:");
    Serial.println(Voltage);
    Serial.print("Temper:");
    Serial.println(Temper);
    Serial.print("Move:");
    Serial.println(Move);
    Serial.print("Current:");
    Serial.println(Current);
    delay(10);
  }else{
    digitalWrite(LEDpin, HIGH);
    Serial.println("FeedBack err");
    delay(500);
  }

  Pos = hlscl.ReadPos(1);
  if(!hlscl.getLastError()){
    digitalWrite(LEDpin, LOW);
    Serial.print("Servo position:");
    Serial.println(Pos, DEC);
    delay(10);
  }else{
    Serial.println("read position err");
    digitalWrite(LEDpin, HIGH);
    delay(500);
  }

  Serial.println();
}
