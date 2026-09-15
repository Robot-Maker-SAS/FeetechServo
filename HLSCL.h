/*
 * HLSCL.h
 * Feetech HLS series serial servo application layer
 * Date: 2024.11.21
 * Author: txl
 */

#ifndef _HLSCL_H
#define _HLSCL_H

// Memory table definitions
//-------EPROM (read-only)--------
#define HLSCL_MODEL_L 3
#define HLSCL_MODEL_H 4

//-------EPROM (read/write)--------
#define HLSCL_ID 5
#define HLSCL_BAUD_RATE 6
#define HLSCL_SECOND_ID 7
#define HLSCL_MIN_ANGLE_LIMIT_L 9
#define HLSCL_MIN_ANGLE_LIMIT_H 10
#define HLSCL_MAX_ANGLE_LIMIT_L 11
#define HLSCL_MAX_ANGLE_LIMIT_H 12
#define HLSCL_CW_DEAD 26
#define HLSCL_CCW_DEAD 27
#define HLSCL_OFS_L 31
#define HLSCL_OFS_H 32
#define HLSCL_MODE 33

//-------SRAM (read/write)--------
#define HLSCL_TORQUE_ENABLE 40
#define HLSCL_ACC 41
#define HLSCL_GOAL_POSITION_L 42
#define HLSCL_GOAL_POSITION_H 43
#define HLSCL_GOAL_TORQUE_L 44
#define HLSCL_GOAL_TORQUE_H 45
#define HLSCL_GOAL_SPEED_L 46
#define HLSCL_GOAL_SPEED_H 47
#define HLSCL_TORQUE_LIMIT_L 48
#define HLSCL_TORQUE_LIMIT_H 49
#define HLSCL_LOCK 55

//-------SRAM (read-only)--------
#define HLSCL_PRESENT_POSITION_L 56
#define HLSCL_PRESENT_POSITION_H 57
#define HLSCL_PRESENT_SPEED_L 58
#define HLSCL_PRESENT_SPEED_H 59
#define HLSCL_PRESENT_LOAD_L 60
#define HLSCL_PRESENT_LOAD_H 61
#define HLSCL_PRESENT_VOLTAGE 62
#define HLSCL_PRESENT_TEMPERATURE 63
#define HLSCL_MOVING 66
#define HLSCL_PRESENT_CURRENT_L 69
#define HLSCL_PRESENT_CURRENT_H 70

#include "SCSerial.h"

class HLSCL : public SCSerial
{
public:
	HLSCL();
	HLSCL(u8 End);
	HLSCL(u8 End, u8 Level);
	int WritePosEx(u8 ID, s16 Position, u16 Speed, u8 ACC = 0, u16 Torque = 0);//normal write: single servo position instruction
	int RegWritePosEx(u8 ID, s16 Position, u16 Speed, u8 ACC = 0, u16 Torque = 0);//async write: single servo position instruction (takes effect on RegWriteAction)
	void SyncWritePosEx(u8 ID[], u8 IDN, s16 Position[], u16 Speed[], u8 ACC[], u16 Torque[]);//sync write: multiple servo positions instruction
	void SyncWriteSpe(u8 ID[], u8 IDN, s16 Speed[], u8 ACC[], u16 Torque[]);//sync write: multiple servo speeds instruction
	int ServoMode(u8 ID);//servo (position) mode
	int WheelMode(u8 ID);//constant speed mode
	int EleMode(u8 ID);//constant force (torque) mode
	int WriteSpe(u8 ID, s16 Speed, u8 ACC = 0, u16 Torque = 0);//constant speed mode control instruction
	int WriteEle(u8 ID, s16 Torque);//constant force mode control instruction
	int EnableTorque(u8 ID, u8 Enable);//torque control instruction
	int unLockEprom(u8 ID);//unlock EEPROM
	int LockEprom(u8 ID);//lock EEPROM
	int CalibrationOfs(u8 ID);//midpoint calibration
	int FeedBack(int ID);//read back servo feedback info
	int ReadPos(int ID);//read position
	int ReadSpeed(int ID);//read speed
	int ReadLoad(int ID);//read output-to-motor voltage percentage (0~1000)
	int ReadVoltage(int ID);//read voltage
	int ReadTemper(int ID);//read temperature
	int ReadMove(int ID);//read moving state
	int ReadCurrent(int ID);//read current
private:
	u8 Mem[HLSCL_PRESENT_CURRENT_H-HLSCL_PRESENT_POSITION_L+1];
};

#endif
