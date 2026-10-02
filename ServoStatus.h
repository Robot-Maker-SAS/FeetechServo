/*
 * ServoStatus.h
 * Shared snapshot struct filled by ReadStatus(), one field per Read* method
 * already exposed by SMS_STS, SCSCL and HLSCL (position/speed/load/
 * voltage/temperature/moving state/current). Kept in its own header,
 * included by all three, since SCServo.h pulls all three of their headers
 * into the same translation unit — a struct defined in each would clash.
 */

#ifndef _SERVOSTATUS_H
#define _SERVOSTATUS_H

struct ServoStatus {
	int Position;
	int Speed;
	int Load;
	int Voltage;
	int Temper;
	int Move;
	int Current;
	int HardwareError;
};

#endif
