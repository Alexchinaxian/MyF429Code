#ifndef _MODBUS_ASCII_MASTER_H_
#define _MODBUS_ASCII_MASTER_H_

#include "HeadFile.h"
#include "Modbus_Data_Deal.h"

extern void MB_Master_Transmit_ASCII_Prepare(uint16_t u16MBCID2,MBASCIIFrame_t* ptMBFrame);
extern MBErrorCode MB_Master_Transmit_ASCII_Frame(uint8_t u8Sciid,MBASCIIFrame_t* ptMBFrame);
extern MBErrorCode MB_Master_Receive_ASCII_Frame(uint8_t u8Sciid,MBASCIIFrame_t* ptMBFrame);
extern MBErrorCode MB_Master_Parsing_ASCII_Frame(uint8_t u8Sciid,uint8_t *pu8RxBuf,MBASCIIFrame_t* ptMBFrame);
extern uint8_t ModbusChar2Bin( uint8_t ucCharacter );
extern uint8_t ModbusBin2Char( uint8_t ucByte );

#endif

