/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
文件 : Modbus_Data_Deal.c 
 用途 : Modbus协议公共函数库
***********************************************************************************************************************/
#ifndef MODBUS_DATA_DEAL_C_
#define MODBUS_DATA_DEAL_C_

#include "Modbus_Data_Deal.h"
#include "Modbus_CLOUD_COMData.h"

UsartTaskFlag_t tUsartFlag;     //Uart接收和发送数据的标志位
uint8_t PcsReceiveErrorFlag;    //PCS回复异常码的标志位
uint8_t WriteSingleCoilFlag;    //PCS写单个线圈成功的标志位
uint8_t WriteMultipleRegsFlag;  //PCS写多个寄存器成功的标志位
uint8_t WriteMultipleCoilsFlag; //PCS写多个线圈成功的标志位

/***********************************************************************************************************************
 功能：01H读线圈命令的数据地址和数量的越界判断函数
************************************************************************************************************************/
MBErrorCode MB_RTU_01H_Range_Check(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;

    switch (u8Sciid)
    {
        case DEV_ID_PCS:
            eStatus = CheckPCSComDataRange_01H(ptMBFrame);
            break;
        case DEV_ID_BMS:
            eStatus = CheckPCSComDataRange_01H(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_WIFI_GPRS:
            eStatus = CheckPCSComDataRange_01H(ptMBFrame);
            break;
        case DEV_ID_BLT:
            eStatus = CheckPCSComDataRange_01H(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_DEBUG:
            eStatus = CheckPCSComDataRange_01H(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_METER:
            eStatus = CheckPCSComDataRange_01H(ptMBFrame);//后续根据需求改正
            break;
        default:
            break;
    }
    return eStatus;
}

/***********************************************************************************************************************
 功能：03H读保持寄存器命令的数据地址和数量的越界判断函数
************************************************************************************************************************/
MBErrorCode MB_RTU_03H_Range_Check(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;

    switch (u8Sciid)
    {
        case DEV_ID_PCS:
            eStatus = CheckPCSComDataRange_03H(ptMBFrame);
            break;
        case DEV_ID_BMS:
            eStatus = CheckBmsComDataRange_03H(ptMBFrame);
            break;
        case DEV_ID_WIFI_GPRS:
            if(MB_SLAVE_CLOUD_LOCAL_ADDR == ptMBFrame->u8MBAddress)
            {
                eStatus = CheckEmsCloudComDataRange_03H(ptMBFrame);
            }
            else
            {
                eStatus = CheckPCSComDataRange_03H(ptMBFrame);
            }
            break;
        case DEV_ID_BLT:
            eStatus = CheckPCSComDataRange_03H(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_DEBUG:
            eStatus = CheckPCSComDataRange_03H(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_METER:
            eStatus = CheckPCSComDataRange_03H(ptMBFrame);//后续根据需求改正
            break;
        default:
            break;
    }
    
    return eStatus;
}

/***********************************************************************************************************************
 功能：05H写单个线圈的数据地址的越界判断函数
************************************************************************************************************************/
MBErrorCode MB_RTU_05H_Range_Check(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;

    switch (u8Sciid)
    {
        case DEV_ID_PCS:
            eStatus = CheckPCSComDataRange_05H(ptMBFrame);
            break;
        case DEV_ID_BMS:
            eStatus = CheckPCSComDataRange_05H(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_WIFI_GPRS:
            eStatus = CheckPCSComDataRange_05H(ptMBFrame);
            break;
        case DEV_ID_BLT:
            eStatus = CheckPCSComDataRange_05H(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_DEBUG:
            eStatus = CheckPCSComDataRange_05H(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_METER:
            eStatus = CheckPCSComDataRange_05H(ptMBFrame);//后续根据需求改正
            break;
        default:
            break;
    }

    return eStatus;
}

/***********************************************************************************************************************
 功能：10H写多个寄存器的数据地址和数量的越界判断函数
************************************************************************************************************************/
MBErrorCode MB_RTU_10H_Range_Check(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;

    switch (u8Sciid)
    {
        case DEV_ID_PCS:
            eStatus = CheckPCSComDataRange_10H(ptMBFrame);
            break;
        case DEV_ID_BMS:
            eStatus = CheckPCSComDataRange_10H(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_WIFI_GPRS:
            if(MB_SLAVE_CLOUD_LOCAL_ADDR == ptMBFrame->u8MBAddress)
            {
                eStatus = CheckEmsCloudComDataRange_10H(ptMBFrame);
            }
            else
            {
                eStatus = CheckPCSComDataRange_10H(ptMBFrame);
            }
            break;
        case DEV_ID_BLT:
            eStatus = CheckPCSComDataRange_10H(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_DEBUG:
            eStatus = CheckPCSComDataRange_10H(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_METER:
            eStatus = CheckPCSComDataRange_10H(ptMBFrame);//后续根据需求改正
            break;
        default:
            break;
    }

    return eStatus;
}

/***********************************************************************************************************************
 功能：0FH写多个线圈的数据地址的越界判断函数
************************************************************************************************************************/
MBErrorCode MB_RTU_0FH_Range_Check(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;

    switch (u8Sciid)
    {
        case DEV_ID_PCS:
            eStatus = CheckPCSComDataRange_0FH(ptMBFrame);
            break;
        case DEV_ID_BMS:
            eStatus = CheckPCSComDataRange_0FH(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_WIFI_GPRS:
            eStatus = CheckPCSComDataRange_0FH(ptMBFrame);
            break;
        case DEV_ID_BLT:
            eStatus = CheckPCSComDataRange_0FH(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_DEBUG:
            eStatus = CheckPCSComDataRange_0FH(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_METER:
            eStatus = CheckPCSComDataRange_0FH(ptMBFrame);//后续根据需求改正
            break;
        default:
            break;
    }

    return eStatus;
}

/***********************************************************************************************************************
 功能：获取0x01读线圈的数据地址索引
************************************************************************************************************************/
uint16_t* MB_RTU_01H_Register_Index(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame)
{
    uint16_t *pu8ObjBuf = NULL;

    switch (u8Sciid)
    {
        case DEV_ID_PCS:
            pu8ObjBuf = GetPcsComDataIndex_01H(ptMBFrame);
            break;
        case DEV_ID_BMS:
            pu8ObjBuf = GetPcsComDataIndex_01H(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_WIFI_GPRS:
            pu8ObjBuf = GetPcsComDataIndex_01H(ptMBFrame);
            break;
        case DEV_ID_BLT:
            pu8ObjBuf = GetPcsComDataIndex_01H(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_DEBUG:
            pu8ObjBuf = GetPcsComDataIndex_01H(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_METER:
            pu8ObjBuf = GetPcsComDataIndex_01H(ptMBFrame);//后续根据需求改正
            break;
        default:
            break;
    }

    return pu8ObjBuf;
}

/***********************************************************************************************************************
 功能：定位PCS协议0x03读保持寄存器命令的数据结构地址
************************************************************************************************************************/
uint16_t* MB_RTU_03H_Register_Index(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame)
{
    uint16_t *pu8ObjBuf = NULL;

    switch (u8Sciid)
    {
        case DEV_ID_PCS:
            pu8ObjBuf = GetPcsComDataIndex_03H(ptMBFrame);
            break;
        case DEV_ID_BMS:
            pu8ObjBuf = GetBmsComDataIndex_03H(ptMBFrame);
            break;
        case DEV_ID_WIFI_GPRS:
            pu8ObjBuf = GetPcsComDataIndex_03H(ptMBFrame);
            break;
        case DEV_ID_BLT:
            pu8ObjBuf = GetPcsComDataIndex_03H(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_DEBUG:
            pu8ObjBuf = GetPcsComDataIndex_03H(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_METER:
            pu8ObjBuf = GetMeterComDataIndex_03H(ptMBFrame);
            break;
        default:
            break;
    }

    return pu8ObjBuf;
}

/***********************************************************************************************************************
 功能：获取0x05写单个线圈的数据地址索引
************************************************************************************************************************/
uint16_t* MB_RTU_05H_Register_Index(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame)
{
    uint16_t *pu8ObjBuf = NULL;

    switch (u8Sciid)
    {
        case DEV_ID_PCS:
            pu8ObjBuf = GetPcsComDataIndex_05H(ptMBFrame);
            break;
        case DEV_ID_BMS:
            pu8ObjBuf = GetPcsComDataIndex_05H(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_WIFI_GPRS:
            pu8ObjBuf = GetPcsComDataIndex_05H(ptMBFrame);
            break;
        case DEV_ID_BLT:
            pu8ObjBuf = GetPcsComDataIndex_05H(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_DEBUG:
            pu8ObjBuf = GetPcsComDataIndex_05H(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_METER:
            pu8ObjBuf = GetPcsComDataIndex_05H(ptMBFrame);//后续根据需求改正
            break;
        default:
            break;
    }

    return pu8ObjBuf;
}

/***********************************************************************************************************************
 功能：获取0x10写多个寄存器的数据地址索引
************************************************************************************************************************/
uint16_t* MB_RTU_10H_Register_Index(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame)
{
    uint16_t *pu8ObjBuf = NULL;

    switch (u8Sciid)
    {
        case DEV_ID_PCS:
            pu8ObjBuf = GetPcsComDataIndex_10H(ptMBFrame);
            break;
        case DEV_ID_BMS:
            pu8ObjBuf = GetPcsComDataIndex_10H(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_WIFI_GPRS:
            pu8ObjBuf = GetPcsComDataIndex_10H(ptMBFrame);
            break;
        case DEV_ID_BLT:
            pu8ObjBuf = GetPcsComDataIndex_10H(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_DEBUG:
            pu8ObjBuf = GetPcsComDataIndex_10H(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_METER:
            pu8ObjBuf = GetPcsComDataIndex_10H(ptMBFrame);//后续根据需求改正
            break;
        default:
            break;
    }

    return pu8ObjBuf;
}

/***********************************************************************************************************************
 功能：获取0x0F写多个线圈的数据地址索引
************************************************************************************************************************/
uint16_t* MB_RTU_0FH_Register_Index(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame)
{
    uint16_t *pu8ObjBuf = NULL;

    switch (u8Sciid)
    {
        case DEV_ID_PCS:
            pu8ObjBuf = GetPcsComDataIndex_0FH(ptMBFrame);
            break;
        case DEV_ID_BMS:
            pu8ObjBuf = GetPcsComDataIndex_0FH(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_WIFI_GPRS:
            pu8ObjBuf = GetPcsComDataIndex_0FH(ptMBFrame);
            break;
        case DEV_ID_BLT:
            pu8ObjBuf = GetPcsComDataIndex_0FH(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_DEBUG:
            pu8ObjBuf = GetPcsComDataIndex_0FH(ptMBFrame);//后续根据需求改正
            break;
        case DEV_ID_METER:
            pu8ObjBuf = GetPcsComDataIndex_0FH(ptMBFrame);//后续根据需求改正
            break;
        default:
            break;
    }

    return pu8ObjBuf;
}


#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

