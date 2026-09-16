/*
 * SCSerial.h
 * Feetech serial servo hardware interface layer
 * Date: 2022.3.29
 * Author:
 */

#ifndef _SCSERIAL_H
#define _SCSERIAL_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "SCS.h"

class SCSerial : public SCS
{
public:
	SCSerial();
	SCSerial(u8 End);
	SCSerial(u8 End, u8 Level);
	int readByteRetry(u8 ID, u8 MemAddr, u8 Retry = 5, u32 DelayMs = 10);//retries readByte up to Retry times, waiting DelayMs between attempts, until it stops returning -1
	int readWordRetry(u8 ID, u8 MemAddr, u8 Retry = 5, u32 DelayMs = 10);//retries readWord up to Retry times, waiting DelayMs between attempts, until it stops returning -1

protected:
	int writeSCS(unsigned char *nDat, int nLen);//output nLen bytes
	int readSCS(unsigned char *nDat, int nLen);//input nLen bytes
	int readSCS(unsigned char *nDat, int nLen, unsigned long TimeOut);
	int writeSCS(unsigned char bDat);//output 1 byte
	void rFlushSCS();//
	void wFlushSCS();//
public:
	unsigned long IOTimeOut;//I/O timeout
	Stream *pSerial;//serial port pointer — Stream rather than HardwareSerial, so a SoftwareSerial (or any other Stream) works too
	int Err;
public:
	virtual int getErr(){  return Err;  }
};

#endif