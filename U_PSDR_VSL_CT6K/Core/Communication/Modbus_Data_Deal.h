/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Modbus_Data_Deal.h 
 用途 : modbus通讯数据的处理
***********************************************************************************************************************/
#ifndef _MODBUS_DATA_DEAL_H_
#define _MODBUS_DATA_DEAL_H_

#include "HeadFile.h"
#include "Modbus_PCS_COMData.h"
#include "Modbus_BMS_COMData.h"
#include "Modbus_Meter_COMData.h"
#include "Modbus_Bluetooth_COMData.h"
#include "Modbus_WifiGprs_COMData.h"

extern uint8_t PcsReceiveErrorFlag;     //PCS回复异常码的标志位
extern uint8_t WriteSingleCoilFlag;     //PCS写单个线圈成功的标志位
extern uint8_t WriteMultipleRegsFlag;   //PCS写多个寄存器成功的标志位
extern uint8_t WriteMultipleCoilsFlag;  //PCS写多个线圈成功的标志位

typedef union
{
    uint16_t u16Words;
    struct
    {
        uint8_t bUsart1RxDecodeFlag     : 1;    //  Bit0  : USART1接收数据解析标志
        uint8_t bUsart1TxPackageFlag    : 1;    //  Bit1  : USART1发送数据组包标志
        uint8_t bUsart2RxDecodeFlag     : 1;    //  Bit2  : USART2接收数据解析标志
        uint8_t bUsart2TxPackageFlag    : 1;    //  Bit3  : USART2发送数据组包标志
        uint8_t bUsart3RxDecodeFlag     : 1;    //  Bit4  : USART3接收数据解析标志
        uint8_t bUsart3TxPackageFlag    : 1;    //  Bit5  : USART3发送数据组包标志
        uint8_t bUsart4RxDecodeFlag     : 1;    //  Bit6  : USART4接收数据解析标志
        uint8_t bUsart4TxPackageFlag    : 1;    //  Bit7  : USART4发送数据组包标志
        uint8_t bUsart5RxDecodeFlag     : 1;    //  Bit8  : USART5接收数据解析标志
        uint8_t bUsart5TxPackageFlag    : 1;    //  Bit9  : USART5发送数据组包标志
        uint8_t bUsart6RxDecodeFlag     : 1;    //  Bit10 : USART6接收数据解析标志
        uint8_t bUsart6TxPackageFlag    : 1;    //  Bit11 : USART6发送数据组包标志
        uint8_t bReserved               : 4;    //  Bit12~15 : 保留位
    } Bits;
} UsartTaskFlag_t;

extern UsartTaskFlag_t tUsartFlag;

#define Comm2Pcs_GetFlag_RxDecode        (tUsartFlag.Bits.bUsart1RxDecodeFlag)          //EMS对PCS接收数据解析标志
#define Comm2Pcs_GetFlag_TxPackage       (tUsartFlag.Bits.bUsart1TxPackageFlag)         //EMS对PCS发送数据组包标志
#define Comm2Bms_GetFlag_RxDecode        (tUsartFlag.Bits.bUsart2RxDecodeFlag)          //EMS对BMS接收数据解析标志
#define Comm2Bms_GetFlag_TxPackage       (tUsartFlag.Bits.bUsart2TxPackageFlag)         //EMS对BMS发送数据组包标志
#define Comm2WifiGprs_GetFlag_RxDecode   (tUsartFlag.Bits.bUsart3RxDecodeFlag)          //EMS对WIFI/GPRS接收数据解析标志
#define Comm2WifiGprs_GetFlag_TxPackage  (tUsartFlag.Bits.bUsart3TxPackageFlag)         //EMS对WIFI/GPRS发送数据组包标志
#define Comm2Bluetooth_GetFlag_RxDecode  (tUsartFlag.Bits.bUsart4RxDecodeFlag)          //EMS对蓝牙接收数据解析标志
#define Comm2Bluetooth_GetFlag_TxPackage (tUsartFlag.Bits.bUsart4TxPackageFlag)         //EMS对蓝牙发送数据组包标志
#define Comm2Debug_GetFlag_RxDecode      (tUsartFlag.Bits.bUsart5RxDecodeFlag)          //EMS对调试口接收数据解析标志
#define Comm2Debug_GetFlag_TxPackage     (tUsartFlag.Bits.bUsart5TxPackageFlag)         //EMS对调试口发送数据组包标志
#define Comm2Meter_GetFlag_RxDecode      (tUsartFlag.Bits.bUsart6RxDecodeFlag)          //EMS对电表接收数据解析标志
#define Comm2Meter_GetFlag_TxPackage     (tUsartFlag.Bits.bUsart6TxPackageFlag)         //EMS对电表发送数据组包标志

extern uint16_t*   MB_RTU_01H_Register_Index(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame);  //获取0x01读线圈的数据地址索引
extern uint16_t*   MB_RTU_03H_Register_Index(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame);  //获取0x03读线圈的数据地址索引
extern uint16_t*   MB_RTU_05H_Register_Index(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame);  //获取0x05读线圈的数据地址索引
extern uint16_t*   MB_RTU_10H_Register_Index(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame);  //获取0x10读线圈的数据地址索引
extern uint16_t*   MB_RTU_0FH_Register_Index(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame);  //获取0x0F读线圈的数据地址索引

extern MBErrorCode MB_RTU_01H_Range_Check(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame);     //01H读线圈命令的数据地址和数量的越界判断函数
extern MBErrorCode MB_RTU_03H_Range_Check(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame);     //03H读线圈命令的数据地址和数量的越界判断函数
extern MBErrorCode MB_RTU_05H_Range_Check(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame);     //05H读线圈命令的数据地址和数量的越界判断函数
extern MBErrorCode MB_RTU_10H_Range_Check(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame);     //10H读线圈命令的数据地址和数量的越界判断函数
extern MBErrorCode MB_RTU_0FH_Range_Check(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame);     //0FH读线圈命令的数据地址和数量的越界判断函数

#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

