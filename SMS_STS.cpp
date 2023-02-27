/*
 * SMS_STS.cpp
 * 飞特SMS_STS系列串行舵机应用层程序
 * 日期: 2020.6.17
 * 作者: 
 */

#include "SMS_STS.h"

SMS_STS::SMS_STS()
{
	End = 0;
}

SMS_STS::SMS_STS(u8 End):SCSerial(End)
{
}

SMS_STS::SMS_STS(u8 End, u8 Level):SCSerial(End, Level)
{
}

u8 SMS_STS::baudConf(u32 baud) {
	if(baud < 8) return baud;
	else if(baud < (38400 + 57600) / 2) return BAUD_38400;
	else if(baud < (57600 + 76800) / 2) return BAUD_57600;
	else if(baud < (76800 + 115200) / 2) return BAUD_76800;
	else if(baud < (115200 + 128000) / 2) return BAUD_115200;
	else if(baud < (128000 + 250000) / 2) return BAUD_128000;
	else if(baud < (250000 + 500000) / 2) return BAUD_250000;
	else if(baud < (500000 + 1000000) / 2) return BAUD_500000;
	else return BAUD_1000000;
}
// WriteID: The ID is a value between 0 and 253
int SMS_STS::WriteID(u8 ID, u8 NewID)
{
	unLockEprom(ID);
	int result = genWrite(ID, SMS_STS_ID, &NewID, 1);
	LockEprom(NewID);
	return result;
}

/* WriteBaud: The baud rate is a value between 0 and 7
And each value represents a baud rate as follows:
0 : 1000000
1 : 500000
2 : 250000
3 : 128000
4 : 115200
5 : 76800
6 : 57600
7 : 38400
*/
int SMS_STS::WriteBaud(u8 ID, u32 Baud)
{
	u8 baudConfig = baudConf(Baud);
	unLockEprom(ID);
	int result = genWrite(ID, SMS_STS_BAUD_RATE, &baudConfig, 1);
	LockEprom(ID);
	return result;
}

// WriteMinAngleLimit: The min angle is a value between -30719 and 30719
int SMS_STS::WriteMinAngleLimit(u8 ID, s16 MinAngle)
{
	if (MinAngle > 30719) MinAngle = 30719;
	else if (MinAngle < -30719) MinAngle = -30719;
	unLockEprom(ID);
	u8 bBuf[2];
	Host2SCS(bBuf, bBuf+1, MinAngle);
	int result = genWrite(ID, SMS_STS_MIN_ANGLE_LIMIT_L, bBuf, 2);
	LockEprom(ID);
	return result;
}

// WriteMaxAngle: The max angle is a value between -30719 and 30719
int SMS_STS::WriteMaxAngleLimit(u8 ID, s16 MaxAngle)
{
	if (MaxAngle > 30719) MaxAngle = 30719;
	else if (MaxAngle < -30719) MaxAngle = -30719;
	unLockEprom(ID);
	u8 bBuf[2];
	Host2SCS(bBuf, bBuf+1, MaxAngle);
	int result = genWrite(ID, SMS_STS_MAX_ANGLE_LIMIT_L, bBuf, 2);
	LockEprom(ID);
	return result;
}

// WriteMinMaxAngle: The min and max angle are values between -30719 and 30719
int SMS_STS::WriteMinMaxAngleLimit(u8 ID, s16 MinAngle, s16 MaxAngle)
{
	if (MinAngle > 30719) MinAngle = 30719;
	else if (MinAngle < -30719) MinAngle = -30719;
	if (MaxAngle > 30719) MaxAngle = 30719;
	else if (MaxAngle < -30719) MaxAngle = -30719;
	unLockEprom(ID);
	u8 bBuf[4];
	Host2SCS(bBuf, bBuf+1, MinAngle);
	Host2SCS(bBuf+2, bBuf+3, MaxAngle);
	int result = genWrite(ID, SMS_STS_MIN_ANGLE_LIMIT_L, bBuf, 4);
	LockEprom(ID);
	return result;
}

// WriteTorqueLimit: Change torque in the SRAM and EPROM, The torque limit is a value between 1 and 1000
int SMS_STS::WriteTorqueLimit(u8 ID, u16 TorqueLimit)
{
	if(TorqueLimit >= 0 && TorqueLimit <= 1000) {
	    u8 bBuf[2];
	    Host2SCS(bBuf, bBuf+1, TorqueLimit);
	    unLockEprom(ID);
	    int result = genWrite(ID, SMS_STS_MAX_TORQUE_LIMIT_L, bBuf, 2);
	    LockEprom(ID);
	    return result;
	} else {
	    return -1; // Torque limit out of range
	}	
}

/* WriteMode: change control mode. Mode values set as follow:
0: Position control
1: Wheel mode / Speed control closed loop speed
2: PWM mode open loop speed
3: Step mode
*/
int SMS_STS::WriteMode(u8 ID, u8 Mode)
{
	unLockEprom(ID);
	int result = genWrite(ID, SMS_STS_MODE, &Mode, 1);
	LockEprom(ID);
	return result;
}

//WriteOverloadCurrent: Change overload current value between 0 and 255
int SMS_STS::WriteOverloadCurrent(u8 ID, u8 Current)
{
	unLockEprom(ID);
	u8 bBuf[2];
	Host2SCS(bBuf, bBuf+1, Current);
	int result = genWrite(ID, SMS_STS_OVERLOAD_CURRENT_L, bBuf, 2);
	LockEprom(ID);
	return result;
}

int SMS_STS::WritePosEx(u8 ID, s16 Position, u16 Speed, u8 ACC)
{
	if(Position<0){
		Position = -Position;
		Position |= (1<<15);
	}
	u8 bBuf[7];
	bBuf[0] = ACC;
	Host2SCS(bBuf+1, bBuf+2, Position);
	Host2SCS(bBuf+3, bBuf+4, 0);
	Host2SCS(bBuf+5, bBuf+6, Speed);
	
	return genWrite(ID, SMS_STS_ACC, bBuf, 7);
}

int SMS_STS::RegWritePosEx(u8 ID, s16 Position, u16 Speed, u8 ACC)
{
	if(Position<0){
		Position = -Position;
		Position |= (1<<15);
	}
	u8 bBuf[7];
	bBuf[0] = ACC;
	Host2SCS(bBuf+1, bBuf+2, Position);
	Host2SCS(bBuf+3, bBuf+4, 0);
	Host2SCS(bBuf+5, bBuf+6, Speed);
	
	return regWrite(ID, SMS_STS_ACC, bBuf, 7);
}

void SMS_STS::SyncWritePosEx(u8 ID[], u8 IDN, s16 Position[], u16 Speed[], u8 ACC[])
{
    u8 offbuf[7*IDN];
    for(u8 i = 0; i<IDN; i++){
		if(Position[i]<0){
			Position[i] = -Position[i];
			Position[i] |= (1<<15);
		}
		u16 V;
		if(Speed){
			V = Speed[i];
		}else{
			V = 0;
		}
		if(ACC){
			offbuf[i*7] = ACC[i];
		}else{
			offbuf[i*7] = 0;
		}
        Host2SCS(offbuf+i*7+1, offbuf+i*7+2, Position[i]);
        Host2SCS(offbuf+i*7+3, offbuf+i*7+4, 0);
        Host2SCS(offbuf+i*7+5, offbuf+i*7+6, V);
    }
    syncWrite(ID, IDN, SMS_STS_ACC, offbuf, 7);
}

int SMS_STS::WheelMode(u8 ID)
{
	return writeByte(ID, SMS_STS_MODE, 1);		
}

int SMS_STS::JoinMode(u8 ID)
{
	return writeByte(ID, SMS_STS_MODE, 0);		
}

int SMS_STS::WriteSpe(u8 ID, s16 Speed, u8 ACC)
{
	if(Speed<0){
		Speed = -Speed;
		Speed |= (1<<15);
	}
	u8 bBuf[2];
	bBuf[0] = ACC;
	genWrite(ID, SMS_STS_ACC, bBuf, 1);
	Host2SCS(bBuf+0, bBuf+1, Speed);
	
	return genWrite(ID, SMS_STS_GOAL_SPEED_L, bBuf, 2);
}

int SMS_STS::EnableTorque(u8 ID, u8 Enable)
{
	return writeByte(ID, SMS_STS_TORQUE_ENABLE, Enable);
}

int SMS_STS::unLockEprom(u8 ID)
{
	return writeByte(ID, SMS_STS_LOCK, 0);
}

int SMS_STS::LockEprom(u8 ID)
{
	return writeByte(ID, SMS_STS_LOCK, 1);
}

int SMS_STS::CalibrationOfs(u8 ID)
{
	return writeByte(ID, SMS_STS_TORQUE_ENABLE, 128);
}

int SMS_STS::FeedBack(int ID)
{
	int nLen = Read(ID, SMS_STS_PRESENT_POSITION_L, Mem, sizeof(Mem));
	if(nLen!=sizeof(Mem)){
		Err = 1;
		return -1;
	}
	Err = 0;
	return nLen;
}

int SMS_STS::ReadPos(int ID)
{
	int Pos = -1;
	if(ID==-1){
		Pos = Mem[SMS_STS_PRESENT_POSITION_H-SMS_STS_PRESENT_POSITION_L];
		Pos <<= 8;
		Pos |= Mem[SMS_STS_PRESENT_POSITION_L-SMS_STS_PRESENT_POSITION_L];
	}else{
		Err = 0;
		Pos = readWord(ID, SMS_STS_PRESENT_POSITION_L);
		if(Pos==-1){
			Err = 1;
		}
	}
	if(!Err && (Pos&(1<<15))){
		Pos = -(Pos&~(1<<15));
	}
	
	return Pos;
}

int SMS_STS::ReadSpeed(int ID)
{
	int Speed = -1;
	if(ID==-1){
		Speed = Mem[SMS_STS_PRESENT_SPEED_H-SMS_STS_PRESENT_POSITION_L];
		Speed <<= 8;
		Speed |= Mem[SMS_STS_PRESENT_SPEED_L-SMS_STS_PRESENT_POSITION_L];
	}else{
		Err = 0;
		Speed = readWord(ID, SMS_STS_PRESENT_SPEED_L);
		if(Speed==-1){
			Err = 1;
			return -1;
		}
	}
	if(!Err && (Speed&(1<<15))){
		Speed = -(Speed&~(1<<15));
	}	
	return Speed;
}

int SMS_STS::ReadLoad(int ID)
{
	int Load = -1;
	if(ID==-1){
		Load = Mem[SMS_STS_PRESENT_LOAD_H-SMS_STS_PRESENT_POSITION_L];
		Load <<= 8;
		Load |= Mem[SMS_STS_PRESENT_LOAD_L-SMS_STS_PRESENT_POSITION_L];
	}else{
		Err = 0;
		Load = readWord(ID, SMS_STS_PRESENT_LOAD_L);
		if(Load==-1){
			Err = 1;
		}
	}
	if(!Err && (Load&(1<<10))){
		Load = -(Load&~(1<<10));
	}
	return Load;
}

int SMS_STS::ReadVoltage(int ID)
{	
	int Voltage = -1;
	if(ID==-1){
		Voltage = Mem[SMS_STS_PRESENT_VOLTAGE-SMS_STS_PRESENT_POSITION_L];	
	}else{
		Err = 0;
		Voltage = readByte(ID, SMS_STS_PRESENT_VOLTAGE);
		if(Voltage==-1){
			Err = 1;
		}
	}
	return Voltage;
}

int SMS_STS::ReadTemper(int ID)
{	
	int Temper = -1;
	if(ID==-1){
		Temper = Mem[SMS_STS_PRESENT_TEMPERATURE-SMS_STS_PRESENT_POSITION_L];	
	}else{
		Err = 0;
		Temper = readByte(ID, SMS_STS_PRESENT_TEMPERATURE);
		if(Temper==-1){
			Err = 1;
		}
	}
	return Temper;
}

int SMS_STS::ReadMove(int ID)
{
	int Move = -1;
	if(ID==-1){
		Move = Mem[SMS_STS_MOVING-SMS_STS_PRESENT_POSITION_L];	
	}else{
		Err = 0;
		Move = readByte(ID, SMS_STS_MOVING);
		if(Move==-1){
			Err = 1;
		}
	}
	return Move;
}

int SMS_STS::ReadCurrent(int ID)
{
	int Current = -1;
	if(ID==-1){
		Current = Mem[SMS_STS_PRESENT_CURRENT_H-SMS_STS_PRESENT_POSITION_L];
		Current <<= 8;
		Current |= Mem[SMS_STS_PRESENT_CURRENT_L-SMS_STS_PRESENT_POSITION_L];
	}else{
		Err = 0;
		Current = readWord(ID, SMS_STS_PRESENT_CURRENT_L);
		if(Current==-1){
			Err = 1;
			return -1;
		}
	}
	if(!Err && (Current&(1<<15))){
		Current = -(Current&~(1<<15));
	}	
	return Current;
}

