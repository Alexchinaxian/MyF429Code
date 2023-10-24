/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
文件 : Modbus_RTU_Slave.h 
 用途 : Modbus从机头文件
***********************************************************************************************************************/
#ifndef _MODBUS_RTU_SLAVE_H_
#define _MODBUS_RTU_SLAVE_H_

#include "HeadFile.h"
#include "RTC_Service.h"
#include "Modbus_Data_Deal.h"

#define            SERIAL_NUMS               (10)                                           //序列号的个数
#define            SERIAL_BYTES              (20)                                           //序列号的字节数
#define            MODEL_NUMS                ( 8)                                           //机型号的个数
#define            MODEL_BYTES               (16)                                           //机型号的字节数
#define            PROT_CODE_NUMS            ( 6)                                           //防呆码的个数

#define            PROTECT_CODE              {'0','0','2','8','4','1'}                      //序列号和机型号的防呆码
#define            ReverseBytes(n)           (((n & 0x00ff) << 8) | ((n & 0xff00) >> 8))    //大小端字节反转

extern void        MB_Slave_RTU_InitVar(void);                                              //从机RTU模式的初始化函数
extern MBErrorCode MB_Slave_Response_RTU_Frame(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame);    //从机RTU模式的回复函数
extern MBErrorCode MB_Slave_Receive_RTU_Frame(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame);     //从机RTU模式的接收函数



#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
