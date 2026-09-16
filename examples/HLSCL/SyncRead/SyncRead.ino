/*
Sync read instruction: reads back position and speed information for both servo ID1 and ID2.
*/

#include <SCServo.h>

HLSCL hlscl;

uint8_t ID[] = {1, 2};
uint8_t rxPacket[4];
int16_t Position;
int16_t Speed;

void setup()
{
  Serial.begin(115200);
  //Serial1.begin(1000000, SERIAL_8N1, 18, 17);//esp32-s3
  Serial1.begin(1000000);//mega2560
  hlscl.pSerial = &Serial1;
  hlscl.syncReadBegin(sizeof(ID), sizeof(rxPacket), 5);//10*10*2=200us<5ms
  delay(1000);
}

void loop()
{
  hlscl.syncReadPacketTx(ID, sizeof(ID), HLSCL_PRESENT_POSITION_L, sizeof(rxPacket));//send the sync read instruction packet
  for(uint8_t i=0; i<sizeof(ID); i++){
    //receive the sync read response packet for ID[i]
    if(!hlscl.syncReadPacketRx(ID[i], rxPacket)){
     Serial.print("ID:");
     Serial.println(ID[i]);
     Serial.println("sync read error!");
     continue;//failed to receive/decode
    }
    Position = hlscl.syncReadRxPacketToWrod(15);//decode two bytes; bit15 is the sign bit, 0 means no sign bit
    Speed = hlscl.syncReadRxPacketToWrod(15);//decode two bytes; bit15 is the sign bit, 0 means no sign bit
    Serial.print("ID:");
    Serial.println(ID[i]);
    Serial.print("Position:");
    Serial.println(Position);
    Serial.print("Speed:");
    Serial.println(Speed);
  }
  delay(10);
}
