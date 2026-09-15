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

protected:
	int writeSCS(unsigned char *nDat, int nLen);//output nLen bytes
	int readSCS(unsigned char *nDat, int nLen);//input nLen bytes
	int readSCS(unsigned char *nDat, int nLen, unsigned long TimeOut);
	int writeSCS(unsigned char bDat);//output 1 byte
	void rFlushSCS();//
	void wFlushSCS();//
public:
	unsigned long IOTimeOut;//I/O timeout
	HardwareSerial *pSerial;//serial port pointer
	int Err;
public:
	virtual int getErr(){  return Err;  }
};

#endif