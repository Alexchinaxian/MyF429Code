/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
文件 : Modbus_RTU_Master.h 
 用途 : Modbus主机头文件
***********************************************************************************************************************/
#ifndef _MODBUS_RTU_MASTER_H_
#define _MODBUS_RTU_MASTER_H_

#include "HeadFile.h"
#include "Modbus_Data_Deal.h"

extern void MB_Master_RTU_InitVar(void); //主机RTU模式全局变量初始化
extern void MB_Master_Transmit_RTU_Prepare(uint8_t u8Addr,uint8_t u8FuncCode,uint16_t u8StartRegs,uint16_t u8NumRegs,MBRTUFrame_t* ptMBFrame); //主机RTU模式发送参数的写入
extern void MB_Master_RTU_Retransmit(MBRTUFrame_t* ptMBRTUFrame1,MBRTUFrame_t* ptMBRTUFrame2);              //主机RTU模式的数据转移
extern void MB_Master_BMS_Retransmit(MBRTUFrame_t* ptMBRTUFrame2,InternalComData_t *ptInternalComData);     //BMS的数据转移
extern void MB_Master_Meter_Retransmit(MBRTUFrame_t* ptMBRTUFrame2,InternalComData_t *ptInternalComData);   //Meter的数据转移
extern void MB_Master_TEMP_COM_Retransmit(MBRTUFrame_t* ptMBRTUFrame2,InternalComData_t *ptInternalComData);//温度和通讯状态的数据转移

extern MBErrorCode MB_Master_Transmit_RTU_Frame(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame);                   //主机RTU模式的发送函数
extern MBErrorCode MB_Master_Receive_RTU_Frame(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame);                    //主机RTU模式的接收函数
extern int32_t Hex2Float_IEEE745(uint32_t u32HexData);                                                      //电表数据IEEE745协议解码转换

#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
