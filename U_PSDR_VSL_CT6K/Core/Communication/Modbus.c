﻿/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
文件 : Modbus.c 
 用途 : Modbus协议公共函数库
***********************************************************************************************************************/
#ifndef MODBUS_C_
#define MODBUS_C_

#include "Modbus.h"
#include "Modbus_Data_Deal.h"

CommStatus_t tCommStatus;  //EMS与各串口间通讯状态
uint8_t CommErrPoweroffFlag;  //PCS通讯断联关机标志

/*ModbusRTU模式和ASCII模式通讯格式的结构定义*/
MBRTUFrame_t gtMBSlaveRTUCMDFrame[DEV_ID_MAX];
MBRTUFrame_t gtMBMasterRTUCMDFrame[DEV_ID_MAX];
MBASCIIFrame_t gtMBMasterASCIICMDFrame[DEV_ID_MAX];

/*CRC校验高字节表*/
static const uint8_t u8CRCHiTable[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40
};

/*CRC校验低字节表*/
static const uint8_t u8CRCLoTable[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
    0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
    0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9,
    0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
    0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
    0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
    0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
    0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF,
    0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
    0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
    0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB,
    0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
    0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
    0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97,
    0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
    0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89,
    0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
    0x41, 0x81, 0x80, 0x40
};

/***********************************************************************************************************************
 功能：Modbus协议全局变量初始化
***********************************************************************************************************************/
void Modbus_InitVar(void)
{
    memset(&gtMBMasterRTUCMDFrame, 0x00, sizeof (MBRTUFrame_t) * DEV_ID_MAX);
    memset(&gtMBSlaveRTUCMDFrame, 0x00, sizeof (MBRTUFrame_t) * DEV_ID_MAX);
}

/***********************************************************************************************************************
 功能：计算CRC16校验和
************************************************************************************************************************/
uint16_t ModbusCRC16( uint8_t * pu8Frame, uint16_t u16Len )
{
    uint8_t u8CRCHi = 0xFF;
    uint8_t u8CRCLo = 0xFF;
    uint8_t u8Index = 0;

    while( u16Len-- )
    {
        u8Index = u8CRCLo ^ *( pu8Frame++ );
        u8CRCLo = ( uint8_t )( u8CRCHi ^ u8CRCHiTable[u8Index] );
        u8CRCHi = u8CRCLoTable[u8Index];
    }
    return ( uint16_t )( u8CRCHi << 8 | u8CRCLo );
}

/***********************************************************************************************************************
 功能：计算LRC校验和
************************************************************************************************************************/
uint16_t ModbusLRC( uint8_t * pucFrame, uint16_t usLen )
{
    uint16_t ucLRC = 0;  /* LRC char initialized */

    while( usLen-- )
    {
        ucLRC += *pucFrame++;   /* Add buffer byte without carry */
    }

    /* Return twos complement */
    ucLRC = ( uint16_t ) ( -( ( int16_t ) ucLRC ) );
    return ucLRC;
}

/***********************************************************************************************************************
 功能：合并数据
************************************************************************************************************************/
uint16_t MergeData(uint8_t *pu8Buf)
{
    uint16_t wTemp = 0;

    wTemp = (((int16_t)(*pu8Buf) << 8) + (int16_t)(*(pu8Buf + 1)));

    return wTemp;
}

/***********************************************************************************************************************
 功能：计算数据长度对应的字节数
************************************************************************************************************************/
uint16_t GetRegsBytesNum(MBRTUFrame_t* ptMBFrame)
{
    uint16_t u16BytesNum = 0;

    if(((ptMBFrame->u16MBRegsNum) % 8) == 0)
    {
        u16BytesNum = (ptMBFrame->u16MBRegsNum) / 8;
    }
    else
    {
        u16BytesNum = (ptMBFrame->u16MBRegsNum) / 8 + 1;
    }
    return u16BytesNum;
    
}

/***********************************************************************************************************************
 功能：通讯断联检测函数
************************************************************************************************************************/
void EmsCommunicateBreakCheck(uint8_t u8Sciid,uint8_t u8DetectCnt)
{
    if(TimeTask_GetFlag_1s == STATUS_FALSE)
    {
        return;
    }

    switch (u8Sciid)
    {
        case DEV_ID_PCS:
            tCommStatus.tCommDisconnectCnt.u8PcsDisconnectCnt++;
            if(u8DetectCnt <= tCommStatus.tCommDisconnectCnt.u8PcsDisconnectCnt)
            {
                tCommStatus.tCommDisconnectFlag.Bits.bEmsToPcsCommStateFlag= EMS_COMM_ERROR;
                tCommStatus.tCommDisconnectCnt.u8PcsDisconnectCnt = 0;
                if (CommErrPoweroffFlag == 0)
                {
                    SetPcs05HPowerOnOffControl(0x0000);  //开机:0xFF00;关机:0x0000
                    CommErrPoweroffFlag++;
                }
            }
            break;
        case DEV_ID_METER:
            tCommStatus.tCommDisconnectCnt.u8MeterDisconnectCnt++;
            if(u8DetectCnt <= tCommStatus.tCommDisconnectCnt.u8MeterDisconnectCnt)
            {
                tCommStatus.tCommDisconnectFlag.Bits.bEmsToMeterCommStateFlag= EMS_COMM_ERROR;
                tCommStatus.tCommDisconnectCnt.u8MeterDisconnectCnt = 0;
            }
            break;
        case DEV_ID_BMS:
            tCommStatus.tCommDisconnectCnt.u8BmsDisconnectCnt++;
            if(u8DetectCnt <= tCommStatus.tCommDisconnectCnt.u8BmsDisconnectCnt)
            {
                tCommStatus.tCommDisconnectFlag.Bits.bEmsToBmsCommStateFlag= EMS_COMM_ERROR;
                tCommStatus.tCommDisconnectCnt.u8BmsDisconnectCnt = 0;

                //BMS通讯故障后将数据清0
                memset(&tBmsDataPylon, 0, sizeof (tBmsDataPylon));
            }
            break;
        case DEV_ID_WIFI_GPRS:
            tCommStatus.tCommDisconnectCnt.u8WifiDisconnectCnt++;
            if(u8DetectCnt <= tCommStatus.tCommDisconnectCnt.u8WifiDisconnectCnt)
            {
                tCommStatus.tCommDisconnectFlag.Bits.bEmsToWifiCommStateFlag= EMS_COMM_ERROR;
                tCommStatus.tCommDisconnectCnt.u8WifiDisconnectCnt = 0;
            }
            break;
        case DEV_ID_BLT:
            tCommStatus.tCommDisconnectCnt.u8BltDisconnectCnt++;
            if(u8DetectCnt <= tCommStatus.tCommDisconnectCnt.u8BltDisconnectCnt)
            {
                tCommStatus.tCommDisconnectFlag.Bits.bEmsToBltCommStateFlag= EMS_COMM_ERROR;
                tCommStatus.tCommDisconnectCnt.u8BltDisconnectCnt = 0;
            }
            break;
        case DEV_ID_DEBUG:
            tCommStatus.tCommDisconnectCnt.u8DebugDisconnectCnt++;
            if(u8DetectCnt <= tCommStatus.tCommDisconnectCnt.u8DebugDisconnectCnt)
            {
                tCommStatus.tCommDisconnectFlag.Bits.bEmsToDebugCommStateFlag= EMS_COMM_ERROR;
                tCommStatus.tCommDisconnectCnt.u8DebugDisconnectCnt = 0;
            }
            break;
        default:
            break;
    }
}

/***********************************************************************************************************************
 功能：通讯连接完成函数
************************************************************************************************************************/
void EmsCommunicateConnectFinish(uint8_t u8Sciid)
{
    switch (u8Sciid)
    {
        case DEV_ID_PCS:
            tCommStatus.tCommDisconnectCnt.u8PcsDisconnectCnt = 0;
            tCommStatus.tCommDisconnectFlag.Bits.bEmsToPcsCommStateFlag= EMS_COMM_NORMAL;
            CommErrPoweroffFlag = 0;
            break;
        case DEV_ID_METER:
            tCommStatus.tCommDisconnectCnt.u8MeterDisconnectCnt = 0;
            tCommStatus.tCommDisconnectFlag.Bits.bEmsToMeterCommStateFlag= EMS_COMM_NORMAL;
            break;
        case DEV_ID_BMS:
            tCommStatus.tCommDisconnectCnt.u8BmsDisconnectCnt = 0;
            tCommStatus.tCommDisconnectFlag.Bits.bEmsToBmsCommStateFlag= EMS_COMM_NORMAL;
            break;
        case DEV_ID_WIFI_GPRS:
            tCommStatus.tCommDisconnectCnt.u8WifiDisconnectCnt = 0;
            tCommStatus.tCommDisconnectFlag.Bits.bEmsToWifiCommStateFlag= EMS_COMM_NORMAL;
            break;
        case DEV_ID_BLT:
            tCommStatus.tCommDisconnectCnt.u8BltDisconnectCnt = 0;
            tCommStatus.tCommDisconnectFlag.Bits.bEmsToBltCommStateFlag= EMS_COMM_NORMAL;
            break;
        case DEV_ID_DEBUG:
            tCommStatus.tCommDisconnectCnt.u8DebugDisconnectCnt = 0;
            tCommStatus.tCommDisconnectFlag.Bits.bEmsToDebugCommStateFlag= EMS_COMM_NORMAL;
            break;
        default:
            break;
    }
}

#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

