/*
 * SCSCL.h
 * Feetech SCSCL series serial servo application layer
 * Date: 2021.3.11
 * Author:
 */

#ifndef _SCSCL_H
#define _SCSCL_H

// Memory table definitions
//-------EPROM (read-only)--------
#define SCSCL_VERSION_L 3
#define SCSCL_VERSION_H 4

//-------EPROM (read/write)--------
#define SCSCL_ID 5
#define SCSCL_BAUD_RATE 6
#define SCSCL_MIN_ANGLE_LIMIT_L 9
#define SCSCL_MIN_ANGLE_LIMIT_H 10
#define SCSCL_MAX_ANGLE_LIMIT_L 11
#define SCSCL_MAX_ANGLE_LIMIT_H 12
#define SCSCL_CW_DEAD 26
#define SCSCL_CCW_DEAD 27

//-------SRAM (read/write)--------
#define SCSCL_TORQUE_ENABLE 40
#define SCSCL_GOAL_POSITION_L 42
#define SCSCL_GOAL_POSITION_H 43
#define SCSCL_GOAL_TIME_L 44
#define SCSCL_GOAL_TIME_H 45
#define SCSCL_GOAL_SPEED_L 46
#define SCSCL_GOAL_SPEED_H 47
#define SCSCL_LOCK 48

//-------SRAM (read-only)--------
#define SCSCL_PRESENT_POSITION_L 56
#define SCSCL_PRESENT_POSITION_H 57
#define SCSCL_PRESENT_SPEED_L 58
#define SCSCL_PRESENT_SPEED_H 59
#define SCSCL_PRESENT_LOAD_L 60
#define SCSCL_PRESENT_LOAD_H 61
#define SCSCL_PRESENT_VOLTAGE 62
#define SCSCL_PRESENT_TEMPERATURE 63
#define SCSCL_MOVING 66
#define SCSCL_PRESENT_CURRENT_L 69
#define SCSCL_PRESENT_CURRENT_H 70

#include "SCSerial.h"
#include "ServoStatus.h"

class SCSCL : public SCSerial
{
public:
	SCSCL();
	SCSCL(u8 End);
	SCSCL(u8 End, u8 Level);
	virtual int WritePos(u8 ID, u16 Position, u16 Time, u16 Speed = 0);//normal write: single servo position instruction
	virtual int RegWritePos(u8 ID, u16 Position, u16 Time, u16 Speed = 0);//async write: single servo position instruction (takes effect on RegWriteAction)
	virtual void SyncWritePos(u8 ID[], u8 IDN, u16 Position[], u16 Time[], u16 Speed[]);//sync write: multiple servo positions instruction
	virtual int PWMMode(u8 ID);//PWM output mode
	virtual int WritePWM(u8 ID, s16 pwmOut);//PWM output mode instruction
	virtual int EnableTorque(u8 ID, u8 Enable);//torque control instruction
	virtual int unLockEprom(u8 ID);//unlock EEPROM
	virtual int LockEprom(u8 ID);//lock EEPROM
	virtual int FeedBack(int ID);//read back servo feedback info
	virtual bool ReadStatus(u8 ID, ServoStatus &status);//FeedBack + every Readxxx(-1) in one call
	virtual int ReadPos(int ID);//read position
	virtual int ReadSpeed(int ID);//read speed
	virtual int ReadLoad(int ID);//read output-to-motor voltage percentage (0~1000)
	virtual int ReadVoltage(int ID);//read voltage
	virtual int ReadTemper(int ID);//read temperature
	virtual int ReadMove(int ID);//read moving state
	virtual int ReadCurrent(int ID);//read current
private:
	u8 Mem[SCSCL_PRESENT_CURRENT_H-SCSCL_PRESENT_POSITION_L+1];
};

#endif