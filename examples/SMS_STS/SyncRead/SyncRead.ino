/*
Sync read instruction: reads back position and speed information for both servo ID1 and ID2.
*/

#include <SCServo.h>

SMS_STS sms_sts;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);//SMS servo baud rate 115200
  //Serial1.begin(1000000);//STS servo baud rate 1000000
  sms_sts.pSerial = &Serial1;
  delay(1000);
}

void loop()
{
  uint8_t ID[] = {1, 2};
  uint8_t rxPacket[4];
  int16_t Position;
  int16_t Speed;
  
  sms_sts.syncReadPacketTx(ID, sizeof(ID), SMS_STS_PRESENT_POSITION_L, sizeof(rxPacket));//send the sync read instruction packet

  uint8_t i;
  for(i=0; i<sizeof(ID); i++){
    //receive the sync read response packet for ID[i]
    if(!sms_sts.syncReadPacketRx(ID[i], rxPacket)){
     Serial.print("ID:");
     Serial.println(ID[i]);
     Serial.println("sync read error!");
     continue;//failed to receive/decode
    }
    Position = sms_sts.syncReadRxPacketToWrod(15);//decode two bytes; bit15 is the sign bit, 0 means no sign bit
    Speed = sms_sts.syncReadRxPacketToWrod(15);//decode two bytes; bit15 is the sign bit, 0 means no sign bit
    Serial.print("ID:");
    Serial.println(ID[i]);
    Serial.print("Position:");
    Serial.println(Position);
    Serial.print("Speed:");
    Serial.println(Speed);
  }
  delay(10);
}
