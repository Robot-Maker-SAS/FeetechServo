/*
 * SMS_STS.h
 * Feetech SMS/STS series serial servo application layer
 * Date: 2021.3.11
 * Author:
 */

#ifndef _SMS_STS_H
#define _SMS_STS_H

// Memory table definitions
//-------EPROM (read-only)--------
#define SMS_STS_MODEL_L 3
#define SMS_STS_MODEL_H 4

//-------EPROM (read/write)--------
#define SMS_STS_ID 5
#define SMS_STS_BAUD_RATE 6
#define SMS_STS_DELAY_TIME_RETURN 7
#define SMS_STS_LEVEL_RETURN 8
#define SMS_STS_MIN_ANGLE_LIMIT_L 9
#define SMS_STS_MIN_ANGLE_LIMIT_H 10
#define SMS_STS_MAX_ANGLE_LIMIT_L 11
#define SMS_STS_MAX_ANGLE_LIMIT_H 12
#define SMS_STS_MAX_TEMP_LIMIT 13
#define SMS_STS_MAX_INPUT_VOLT 14
#define SMS_STS_MIN_INPUT_VOLT 15
#define SMS_STS_MAX_TORQUE_LIMIT_L 16
#define SMS_STS_MAX_TORQUE_LIMIT_H 17
#define SMS_STS_SETTING_BYTE 18
#define SMS_STS_ALARM_LED 20
#define SMS_STS_CW_DEAD 26
#define SMS_STS_CCW_DEAD 27
#define SMS_STS_OVERLOAD_CURRENT_L 28
#define SMS_STS_OVERLOAD_CURRENT_H 29
#define SMS_STS_OFS_L 31
#define SMS_STS_OFS_H 32
#define SMS_STS_MODE 33

//-------SRAM (read/write)--------
#define SMS_STS_TORQUE_ENABLE 40
#define SMS_STS_ACC 41
#define SMS_STS_GOAL_POSITION_L 42
#define SMS_STS_GOAL_POSITION_H 43
#define SMS_STS_GOAL_TIME_L 44
#define SMS_STS_GOAL_TIME_H 45
#define SMS_STS_GOAL_SPEED_L 46
#define SMS_STS_GOAL_SPEED_H 47
#define SMS_STS_TORQUE_LIMIT_L 48
#define SMS_STS_TORQUE_LIMIT_H 49
#define SMS_STS_LOCK 55

//-------SRAM (read-only)--------
#define SMS_STS_PRESENT_POSITION_L 56
#define SMS_STS_PRESENT_POSITION_H 57
#define SMS_STS_PRESENT_SPEED_L 58
#define SMS_STS_PRESENT_SPEED_H 59
#define SMS_STS_PRESENT_LOAD_L 60
#define SMS_STS_PRESENT_LOAD_H 61
#define SMS_STS_PRESENT_VOLTAGE 62
#define SMS_STS_PRESENT_TEMPERATURE 63
#define SMS_STS_MOVING 66
#define SMS_STS_PRESENT_CURRENT_L 69
#define SMS_STS_PRESENT_CURRENT_H 70

#include "SCSerial.h"

enum baud {BAUD_1000000, BAUD_500000, BAUD_250000, BAUD_128000, BAUD_115200, BAUD_76800, BAUD_57600, BAUD_38400, NBBAUD};
enum mode {POSITION, SPEED, PWM, STEP, NBMODE};

class SMS_STS : public SCSerial
{
public:
	SMS_STS();
	SMS_STS(u8 End);
	SMS_STS(u8 End, u8 Level);
	virtual u8 baudConf(u32 baud);
	virtual int WriteID(u8 ID, u8 NewID);//write a new servo ID
	virtual int WriteBaud(u8 ID, u32 Baud);//write a new servo baud rate
	virtual int WriteMinAngleLimit(u8 ID, s16 MinAngle);//write a new minimum angle value
	virtual int WriteMaxAngleLimit(u8 ID, s16 MaxAngle);//write a new maximum angle value
	virtual int WriteMinMaxAngleLimit(u8 ID, s16 MinAngle, s16 MaxAngle);
	virtual int WriteTorqueLimit(u8 ID, u16 TorqueLimit);//write a new maximum torque value
	virtual int WriteMode(u8 ID, u8 Mode);//write/switch mode
	virtual int WriteOverloadCurrent(u8 ID, u8 Current);//write a new overload current value
	virtual int WritePosEx(u8 ID, s16 Position, u16 Speed, u8 ACC = 0);//normal write: single servo position instruction
	virtual int RegWritePosEx(u8 ID, s16 Position, u16 Speed, u8 ACC = 0);//async write: single servo position instruction (takes effect on RegWriteAction)
	virtual void SyncWritePosEx(u8 ID[], u8 IDN, s16 Position[], u16 Speed[], u8 ACC[]);//sync write: multiple servo positions instruction
	virtual int WheelMode(u8 ID);//constant speed mode
	virtual int JoinMode(u8 ID);//servo (position) mode
	virtual int WriteSpe(u8 ID, s16 Speed, u8 ACC = 0);//constant speed mode control instruction
	virtual int EnableTorque(u8 ID, u8 Enable);//torque control instruction
	virtual int unLockEprom(u8 ID);//unlock EEPROM
	virtual int LockEprom(u8 ID);//lock EEPROM
	virtual int CalibrationOfs(u8 ID);//midpoint calibration
	virtual int FeedBack(int ID);//read back servo feedback info
	virtual int ReadPos(int ID);//read position
	virtual int ReadSpeed(int ID);//read speed
	virtual int ReadLoad(int ID);//read output-to-motor voltage percentage (0~1000)
	virtual int ReadVoltage(int ID);//read voltage
	virtual int ReadTemper(int ID);//read temperature
	virtual int ReadMove(int ID);//read moving state
	virtual int ReadCurrent(int ID);//read current
private:
	u8 Mem[SMS_STS_PRESENT_CURRENT_H-SMS_STS_PRESENT_POSITION_L+1];
};

#endif