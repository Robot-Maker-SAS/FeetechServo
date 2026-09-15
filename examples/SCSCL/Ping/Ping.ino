/*
Ping instruction test: checks whether the servo with the given ID is ready on the bus. The broadcast
ID only works when there is a single servo on the bus.
*/

#include <SCServo.h>

SCSCL sc;

int LEDpin = 13;
void setup()
{
  pinMode(LEDpin,OUTPUT);
  digitalWrite(LEDpin, HIGH);
  Serial.begin(115200);
  Serial1.begin(1000000);
  sc.pSerial = &Serial1;
  delay(1000);
}

void loop()
{
  int ID = sc.Ping(1);
  if(ID!=-1){
    digitalWrite(LEDpin, LOW);
    Serial.print("Servo ID:");
    Serial.println(ID, DEC);
    delay(100);
  }else{
    Serial.println("Ping servo ID error!");
    digitalWrite(LEDpin, HIGH);
    delay(2000);
  }
}
