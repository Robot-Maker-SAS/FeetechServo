/*
 * SCS.h
 * Feetech serial servo communication layer protocol
 * Date: 2022.4.2
 * Author:
 */

#ifndef _SCS_H
#define _SCS_H

#include "INST.h"

class SCS{
public:
	SCS();
	SCS(u8 End);
	SCS(u8 End, u8 Level);
	int genWrite(u8 ID, u8 MemAddr, u8 *nDat, u8 nLen);//normal write instruction
	int regWrite(u8 ID, u8 MemAddr, u8 *nDat, u8 nLen);//async (registered) write instruction
	int RegWriteAction(u8 ID = 0xfe);//async write action instruction (triggers pending regWrite)
	void syncWrite(u8 ID[], u8 IDN, u8 MemAddr, u8 *nDat, u8 nLen);//sync write instruction
	int writeByte(u8 ID, u8 MemAddr, u8 bDat);//write 1 byte
	int writeWord(u8 ID, u8 MemAddr, u16 wDat);//write 2 bytes
	int Read(u8 ID, u8 MemAddr, u8 *nData, u8 nLen);//read instruction
	int readByte(u8 ID, u8 MemAddr);//read 1 byte
	int readWord(u8 ID, u8 MemAddr);//read 2 bytes
	int Ping(u8 ID);//ping instruction
	int syncReadPacketTx(u8 ID[], u8 IDN, u8 MemAddr, u8 nLen);//send sync read instruction packet
	int syncReadPacketRx(u8 ID, u8 *nDat);//decode sync read response packet; returns byte count read on success, 0 on failure
	int syncReadRxPacketToByte();//decode one byte
	int syncReadRxPacketToWrod(u8 negBit=0);//decode two bytes; negBit is the sign bit position, 0 means unsigned
	void syncReadBegin(u8 IDN, u8 rxLen, u32 TimeOut);//begin sync read
	void syncReadEnd();//end sync read
	int Recovery(u8 ID);//restore servo parameters to factory defaults
public:
	u8 Level;//servo response level
	u8 End;//processor endianness
	u8 Error;//servo state
	u8 syncReadRxPacketIndex;
	u8 syncReadRxPacketLen;
	u8 *syncReadRxPacket;
	u8 *syncReadRxBuff;
	u16 syncReadRxBuffLen;
	u16 syncReadRxBuffMax;
	u32 syncTimeOut;
protected:
	virtual int writeSCS(unsigned char *nDat, int nLen) = 0;
	virtual int readSCS(unsigned char *nDat, int nLen) = 0;
	virtual int readSCS(unsigned char *nDat, int nLen, unsigned long TimeOut) = 0;
	virtual int writeSCS(unsigned char bDat) = 0;
	virtual void rFlushSCS() = 0;
	virtual void wFlushSCS() = 0;
protected:
	void writeBuf(u8 ID, u8 MemAddr, u8 *nDat, u8 nLen, u8 Fun);
	void Host2SCS(u8 *DataL, u8* DataH, u16 Data);//split one 16-bit value into two 8-bit values
	u16	SCS2Host(u8 DataL, u8 DataH);//combine two 8-bit values into one 16-bit value
	int	Ack(u8 ID);//read the acknowledgement response
	int checkHead();//check for the frame header
};
#endif