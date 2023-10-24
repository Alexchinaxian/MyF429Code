/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Modbus_PCS_COMData.c 
 用途 : ModbusPCS协议相关函数
***********************************************************************************************************************/
#ifndef MODBUS_PCS_COMDATA_C_
#define MODBUS_PCS_COMDATA_C_

#include "Modbus_PCS_COMData.h"
#include "Modbus_RTU_Master.h"
#include "Modbus_CLOUD_COMData.h"

InternalComData_t tInternalComData;   //PCS协议数据结构
ExternalSetPCSFlag_t externalSetFlag;     //PCS下设标志位

/***********************************************************************************************************************
 功能：检查PCS功能码01H的通讯数据范围是否越界
************************************************************************************************************************/
MBErrorCode CheckPCSComDataRange_01H(MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;

    /*判断起始地址的高12位是否匹配01H保护参数模块数据地址*/
    if(EMS_TO_PCS_01H_PROT_0x010x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0)) 
    {
        /*判断起始地址和数据个数是否越界*/
        if((PCS_01H_PROT_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_01H_PROT_PARAM_START)) || \
           (PCS_01H_PROT_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_01H_PROT_PARAM_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    /*判断起始地址的高12位是否匹配01H调试模式模块数据地址*/
    else if((EMS_TO_PCS_01H_DEBUG_0x013x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0)) || (EMS_TO_PCS_01H_DEBUG_0x014x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0))) 
    {
        /*判断起始地址和数据个数是否越界*/
        if((PCS_01H_DEBUG_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_01H_DEBUG_MODE_START)) || \
           (PCS_01H_DEBUG_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_01H_DEBUG_MODE_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if((EMS_TO_PCS_01H_PROT_EN_0x015x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0)) || (EMS_TO_PCS_01H_PROT_EN_0x016x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0))) 
    {
        /*判断起始地址和数据个数是否越界*/
        if((PCS_01H_PROT_EN_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_01H_PROT_EN_START)) || \
           (PCS_01H_PROT_EN_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_01H_PROT_EN_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if(EMS_TO_PCS_01H_SYS_CTRL_0x017x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0))
    {
        /*判断起始地址和数据个数是否越界*/
        if((PCS_01H_SYS_CTRL_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_0FH_SYS_CTRL_START)) || \
           (PCS_01H_SYS_CTRL_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_0FH_SYS_CTRL_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else
    {
        eStatus = MB_DATA_ADD_ERROR;
    }
    return eStatus;
}

/***********************************************************************************************************************
 功能：检查PCS功能码03H的通讯数据范围是否越界
************************************************************************************************************************/
MBErrorCode CheckPCSComDataRange_03H(MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;

    switch ((ptMBFrame->u16MBStartRegsAddr) & 0xFF00)
    {
        case EMS_TO_PCS_03H_TOTAL_PARAM_0x10xx://共有参数
            if((PCS_03H_TOTAL_PARAM_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_TOTAL_PARAM_START)) || \
               (PCS_03H_TOTAL_PARAM_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_TOTAL_PARAM_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;
        case EMS_TO_PCS_03H_PV_INFO_0x11xx://光伏信息
            if(EMS_TO_PCS_03H_PV1_INFO_0x110x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0))//光伏1信息
            {
                if((PCS_03H_PV1_INFO_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_PV1_INFO_START)) || \
                   (PCS_03H_PV1_INFO_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_PV1_INFO_START)))
                {
                    eStatus = MB_DATA_ADD_ERROR;
                }
                else
                {
                    ;
                }
            }
            else if(EMS_TO_PCS_03H_PV2_INFO_0x111x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0))//光伏2信息
            {
                if((PCS_03H_PV2_INFO_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_PV2_INFO_START)) || \
                   (PCS_03H_PV2_INFO_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_PV2_INFO_START)))
                {
                    eStatus = MB_DATA_ADD_ERROR;
                }
                else
                {
                    ;
                }
            }
            else
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            break;
        case EMS_TO_PCS_03H_INV_INFO_0x12xx://逆变器信息
            if((PCS_03H_INV_INFO_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_INV_INFO_START)) || \
               (PCS_03H_INV_INFO_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_INV_INFO_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;
        case EMS_TO_PCS_03H_DCDC_INFO_0x13xx://电池信息
            if((PCS_03H_DCDC_INFO_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_DCDC_INFO_START)) || \
               (PCS_03H_DCDC_INFO_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_DCDC_INFO_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;
        case EMS_TO_PCS_03H10H_PV_CTRL_0x20xx://PV控制参数
            if((PCS_03H_10H_PV_CTRL_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_PV_CTRL_START)) || \
               (PCS_03H_10H_PV_CTRL_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_PV_CTRL_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;
        case EMS_TO_PCS_03H10H_INV_CTRL_0x21xx://逆变器控制参数
            if((PCS_03H_10H_INV_CTRL_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_INV_CTRL_START)) || \
               (PCS_03H_10H_INV_CTRL_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_INV_CTRL_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;
        case EMS_TO_PCS_03H10H_DCDC_CTRL_0x22xx://DCDC电池控制参数
            if((PCS_03H_10H_BAT_CTRL_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_BAT_CTRL_START)) || \
               (PCS_03H_10H_BAT_CTRL_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_BAT_CTRL_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;
        case EMS_TO_PCS_03H10H_SYS_PARAM_0x23xx://系统参数
            if((PCS_03H_10H_SYS_PARAM_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_SYS_PARAM_START)) || \
               (PCS_03H_10H_SYS_PARAM_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_SYS_PARAM_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;
        case EMS_TO_PCS_03H10H_COM_PARAM_0x24xx://通讯参数
            if((PCS_03H_10H_COM_PARAM_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_COM_PARAM_START)) || \
               (PCS_03H_10H_COM_PARAM_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_COM_PARAM_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;
        case EMS_TO_PCS_03H10H_LINE_VP_0x25xx://市电过压保护
            if((PCS_03H_10H_LINE_VP_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_LINE_VP_START)) || \
               (PCS_03H_10H_LINE_VP_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_LINE_VP_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;
        case EMS_TO_PCS_03H10H_SYS_INFO_0x26xx://市电过压保护
            if((PCS_03H_10H_SYS_INFO_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_SYS_INFO_START)) || \
               (PCS_03H_10H_SYS_INFO_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_SYS_INFO_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;
        case EMS_TO_PCS_03H10H_METER_0x27xx://市电过压保护
            if((PCS_03H_10H_METER_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_METER_START)) || \
               (PCS_03H_10H_METER_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_METER_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;
        case EMS_TO_PCS_03H10H_INV_STD_0x2Exx://逆变器定标系数
            if((PCS_03H_10H_INV_STD_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_INV_STD_START)) || \
               (PCS_03H_10H_INV_STD_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_INV_STD_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;
        default:
            eStatus = MB_DATA_ADD_ERROR;
            break;
    }
    return eStatus;
}

/***********************************************************************************************************************
 功能：检查PCS功能码05H的通讯数据范围是否越界
************************************************************************************************************************/
MBErrorCode CheckPCSComDataRange_05H(MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;

    if((EMS_TO_PCS_05H_DATA_0x02xx != ((ptMBFrame->u16MBStartRegsAddr) & 0xFF00)) || (PCS_05H_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_05H_DATA_START)))
    {
        eStatus = MB_DATA_ADD_ERROR;
    }
    return eStatus;
}

/***********************************************************************************************************************
 功能：检查PCS功能码10H的通讯数据范围是否越界
************************************************************************************************************************/
MBErrorCode CheckPCSComDataRange_10H(MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;

    switch ((ptMBFrame->u16MBStartRegsAddr) & 0xFF00)
    {
        case EMS_TO_PCS_03H10H_PV_CTRL_0x20xx://PV控制参数
            if((PCS_03H_10H_PV_CTRL_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_PV_CTRL_START)) || \
               (PCS_03H_10H_PV_CTRL_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_PV_CTRL_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;

        case EMS_TO_PCS_03H10H_INV_CTRL_0x21xx://逆变器控制参数
            if((PCS_03H_10H_INV_CTRL_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_INV_CTRL_START)) || \
               (PCS_03H_10H_INV_CTRL_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_INV_CTRL_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;

        case EMS_TO_PCS_03H10H_DCDC_CTRL_0x22xx://DCDC电池控制参数
            if((PCS_03H_10H_BAT_CTRL_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_BAT_CTRL_START)) || \
               (PCS_03H_10H_BAT_CTRL_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_BAT_CTRL_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;

        case EMS_TO_PCS_03H10H_SYS_PARAM_0x23xx://系统参数
            if((PCS_03H_10H_SYS_PARAM_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_SYS_PARAM_START)) || \
               (PCS_03H_10H_SYS_PARAM_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_SYS_PARAM_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;

        case EMS_TO_PCS_03H10H_COM_PARAM_0x24xx://通讯参数
            if((PCS_03H_10H_COM_PARAM_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_COM_PARAM_START)) || \
               (PCS_03H_10H_COM_PARAM_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_COM_PARAM_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;

        case EMS_TO_PCS_03H10H_LINE_VP_0x25xx://市电过压保护
            if((PCS_03H_10H_LINE_VP_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_LINE_VP_START)) || \
               (PCS_03H_10H_LINE_VP_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_LINE_VP_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;

        case EMS_TO_PCS_03H10H_SYS_INFO_0x26xx://市电过压保护
            if((PCS_03H_10H_SYS_INFO_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_SYS_INFO_START)) || \
               (PCS_03H_10H_SYS_INFO_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_SYS_INFO_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;

        case EMS_TO_PCS_03H10H_METER_0x27xx://市电过压保护
            if((PCS_03H_10H_METER_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_METER_START)) || \
               (PCS_03H_10H_METER_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_METER_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;

        case EMS_TO_PCS_03H10H_INV_STD_0x2Exx://逆变器定标系数
            if((PCS_03H_10H_INV_STD_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_INV_STD_START)) || \
               (PCS_03H_10H_INV_STD_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_INV_STD_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;

        case EMS_TO_PCS_10H_EMS_PARAM_0x2Fxx://能量管理地址表
            if((PCS_10H_EMS_PARAM_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_10H_EMS_PARAM_START)) || \
               (PCS_10H_EMS_PARAM_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_10H_EMS_PARAM_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;

        case EMS_TO_PCS_10H_SR_INFO_0x28xx://安规信息地址表
            if((PCS_10H_SR_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_10H_SR_START)) || \
               (PCS_10H_SR_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_10H_SR_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;

        case EMS_TO_PCS_10H_EMS_CONTROL_0x29xx://EMS远程控制地址
            if((PCS_10H_EMSControl_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_10H_EMSControl_START)) || \
               (PCS_10H_EMSControl_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_10H_EMSControl_START)))
            {
                eStatus = MB_DATA_ADD_ERROR;
            }
            else
            {
                ;
            }
            break;

        default:
            eStatus = MB_DATA_ADD_ERROR;
            break;
    }
    return eStatus;
}

/***********************************************************************************************************************
 功能：检查PCS功能码0FH的通讯数据范围是否越界
************************************************************************************************************************/
MBErrorCode CheckPCSComDataRange_0FH(MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;

    if((EMS_TO_PCS_01H_DEBUG_0x013x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0)) || (EMS_TO_PCS_01H_DEBUG_0x014x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0)))
    {
        if((PCS_0FH_DEBUG_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_0FH_DEBUG_MODE_START)) || \
           (PCS_0FH_DEBUG_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_0FH_DEBUG_MODE_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if((EMS_TO_PCS_01H_PROT_EN_0x015x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0)) || (EMS_TO_PCS_01H_PROT_EN_0x016x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0)))
    {
        if((PCS_0FH_PROT_EN_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_0FH_PROT_EN_START)) || \
           (PCS_0FH_PROT_EN_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_0FH_PROT_EN_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if(EMS_TO_PCS_01H_SYS_CTRL_0x017x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0))
    {
        if((PCS_0FH_SYS_CTRL_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - PCS_0FH_SYS_CTRL_START)) || \
           (PCS_0FH_SYS_CTRL_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - PCS_0FH_SYS_CTRL_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else
    {
        eStatus = MB_DATA_ADD_ERROR;
    }
    return eStatus;
}

/***********************************************************************************************************************
 功能：定位起始地址对应的PCS协议功能码01H的数据结构地址
************************************************************************************************************************/
uint16_t* GetPcsComDataIndex_01H(MBRTUFrame_t* ptMBFrame)
{
    uint16_t *pu8ObjBuf = NULL;

    /*判断起始地址的高12位是否匹配01H保护参数模块的数据地址*/
    if(EMS_TO_PCS_01H_PROT_0x010x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0))
    {
        pu8ObjBuf = (uint16_t*)& tInternalComData.Register01H_t.tProtData; //定位01H保护参数模块的首地址
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_01H_PROT_PARAM_START); //定位起始地址对应的01H保护参数模块地址
    }
    /*判断起始地址的高12位是否匹配01H调试模式模块的数据地址*/
    else if((EMS_TO_PCS_01H_DEBUG_0x013x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0)) || (EMS_TO_PCS_01H_DEBUG_0x014x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0)))
    {
        pu8ObjBuf = (uint16_t*)& tInternalComData.Register010FH_t.tDebugMode; //定位01H调试模式模块的首地址
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_01H_DEBUG_MODE_START); //定位起始地址对应的01H调试模式模块地址
    }
    else if((EMS_TO_PCS_01H_PROT_EN_0x015x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0)) || (EMS_TO_PCS_01H_PROT_EN_0x016x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0)))
    {
        pu8ObjBuf = (uint16_t*)& tInternalComData.Register010FH_t.tProtEn; //定位01H调试模式模块的首地址
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_01H_PROT_EN_START); //定位起始地址对应的01H调试模式模块地址
    }
    else if(EMS_TO_PCS_01H_SYS_CTRL_0x017x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0))
    {
        pu8ObjBuf = (uint16_t*)& tInternalComData.Register010FH_t.tSysCtrlParam; //定位01H调试模式模块的首地址
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_01H_SYS_CTRL_START); //定位起始地址对应的01H调试模式模块地址
    }
    else
    {
        ;
    }
    return pu8ObjBuf;
}

/***********************************************************************************************************************
 功能：定位起始地址对应的PCS协议功能码03H的数据结构地址
************************************************************************************************************************/
uint16_t* GetPcsComDataIndex_03H(MBRTUFrame_t* ptMBFrame)
{
    uint16_t *pu8ObjBuf = NULL;
    if(MB_SLAVE_LOCAL_ADDR == ptMBFrame->u8MBAddress)
    {
        switch ((ptMBFrame->u16MBStartRegsAddr) & 0xFF00)
        {
            case EMS_TO_PCS_03H_TOTAL_PARAM_0x10xx://共有参数
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register03H_t.tTotalParam;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_TOTAL_PARAM_START);
                break;
            case EMS_TO_PCS_03H_PV_INFO_0x11xx://光伏信息
                if(EMS_TO_PCS_03H_PV1_INFO_0x110x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0))//光伏1信息
                {
                    pu8ObjBuf = (uint16_t*)& tInternalComData.Register03H_t.tPV1Information;
                    pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_PV1_INFO_START);
                }
                else if(EMS_TO_PCS_03H_PV2_INFO_0x111x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0))//光伏2信息
                {
                    pu8ObjBuf = (uint16_t*)& tInternalComData.Register03H_t.tPV2Information;
                    pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_PV2_INFO_START);
                }
                else
                {
                    ;
                }
                break;
            case EMS_TO_PCS_03H_INV_INFO_0x12xx://逆变器信息
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register03H_t.tInvInformation;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_INV_INFO_START);
                break;
            case EMS_TO_PCS_03H_DCDC_INFO_0x13xx://电池信息
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register03H_t.tDCDCInformation;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_DCDC_INFO_START);
                break;
            case EMS_TO_PCS_03H10H_PV_CTRL_0x20xx://PV控制参数
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register0310H_t.tPvCtrlParam;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_PV_CTRL_START);
                break;
            case EMS_TO_PCS_03H10H_INV_CTRL_0x21xx://逆变器控制参数
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register0310H_t.tInvCtrlParam;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_INV_CTRL_START);
                break;
            case EMS_TO_PCS_03H10H_DCDC_CTRL_0x22xx://DCDC电池控制参数
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register0310H_t.tBatCtrlParam;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_BAT_CTRL_START);
                break;
            case EMS_TO_PCS_03H10H_SYS_PARAM_0x23xx://系统参数
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register0310H_t.tSysParam;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_SYS_PARAM_START);
                break;
            case EMS_TO_PCS_03H10H_COM_PARAM_0x24xx://通讯参数
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register0310H_t.tComParam;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_COM_PARAM_START);
                break;
            case EMS_TO_PCS_03H10H_LINE_VP_0x25xx://市电过压保护
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register0310H_t.tLineVoltProtParam;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_LINE_VP_START);
                break;
            case EMS_TO_PCS_03H10H_SYS_INFO_0x26xx://序列号信息
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register0310H_t.tSysInfo;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_SYS_INFO_START);
                break;
            case EMS_TO_PCS_03H10H_METER_0x27xx://电表信息
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register0310H_t.tMeterInfo;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_METER_START);
                break;
            case EMS_TO_PCS_03H10H_INV_STD_0x2Exx://逆变器定标系数
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register0310H_t.tInvStdParam;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_INV_STD_START);
                break;
            default:
                break;
        }
    }
    /*对接英臻云平台协议地址*/
    if(MB_SLAVE_CLOUD_LOCAL_ADDR == ptMBFrame->u8MBAddress)
    {
        pu8ObjBuf = GetComDataToCloud_03H(ptMBFrame);
    }
	return pu8ObjBuf;

}

/***********************************************************************************************************************
 功能：定位起始地址对应的PCS协议功能码05H的数据结构地址
************************************************************************************************************************/
uint16_t* GetPcsComDataIndex_05H(MBRTUFrame_t* ptMBFrame)
{
    uint16_t *pu8ObjBuf = NULL;

    pu8ObjBuf = (uint16_t*)& tInternalComData.Register05H_t.tData05H;
    pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_05H_DATA_START);

    return pu8ObjBuf;
}

/***********************************************************************************************************************
 功能：定位起始地址对应的PCS协议功能码0FH的数据结构地址
************************************************************************************************************************/
uint16_t* GetPcsComDataIndex_0FH(MBRTUFrame_t* ptMBFrame)
{
    uint16_t *pu8ObjBuf = NULL;

    if((EMS_TO_PCS_01H_DEBUG_0x013x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0)) || (EMS_TO_PCS_01H_DEBUG_0x014x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0)))
    {
        pu8ObjBuf = (uint16_t*)& tInternalComData.Register010FH_t.tDebugMode;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_01H_DEBUG_MODE_START);
    }
    else if((EMS_TO_PCS_01H_PROT_EN_0x015x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0)) || (EMS_TO_PCS_01H_PROT_EN_0x016x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0)))
    {
        pu8ObjBuf = (uint16_t*)& tInternalComData.Register010FH_t.tProtEn;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_0FH_PROT_EN_START);
    }
    else if(EMS_TO_PCS_01H_SYS_CTRL_0x017x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFFF0))
    {
        pu8ObjBuf = (uint16_t*)& tInternalComData.Register010FH_t.tSysCtrlParam;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_0FH_SYS_CTRL_START);
    }
    else
    {
        ;
    }
    return pu8ObjBuf;
}

/***********************************************************************************************************************
 功能：定位起始地址对应的PCS协议功能码10H的数据结构地址
************************************************************************************************************************/
uint16_t* GetPcsComDataIndex_10H(MBRTUFrame_t* ptMBFrame)
{
    uint16_t *pu8ObjBuf = NULL;
    if(MB_SLAVE_LOCAL_ADDR == ptMBFrame->u8MBAddress)
    {
        switch ((ptMBFrame->u16MBStartRegsAddr) & 0xFF00)
        {
            case EMS_TO_PCS_03H10H_PV_CTRL_0x20xx://PV控制参数
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register0310H_t.tPvCtrlParam;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_PV_CTRL_START);
                break;

            case EMS_TO_PCS_03H10H_INV_CTRL_0x21xx://逆变器控制参数
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register0310H_t.tInvCtrlParam;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_INV_CTRL_START);
                break;

            case EMS_TO_PCS_03H10H_DCDC_CTRL_0x22xx://DCDC电池控制参数
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register0310H_t.tBatCtrlParam;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_BAT_CTRL_START);
                break;

            case EMS_TO_PCS_03H10H_SYS_PARAM_0x23xx://系统参数
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register0310H_t.tSysParam;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_SYS_PARAM_START);
                break;

            case EMS_TO_PCS_03H10H_COM_PARAM_0x24xx://通讯参数
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register0310H_t.tComParam;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_COM_PARAM_START);
                break;

            case EMS_TO_PCS_03H10H_LINE_VP_0x25xx://市电过压保护
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register0310H_t.tLineVoltProtParam;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_LINE_VP_START);
                break;

            case EMS_TO_PCS_03H10H_SYS_INFO_0x26xx://序列号信息
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register0310H_t.tSysInfo;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_SYS_INFO_START);
                break;

            case EMS_TO_PCS_03H10H_METER_0x27xx://电表信息
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register0310H_t.tMeterInfo;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_METER_START);
                break;

            case EMS_TO_PCS_03H10H_INV_STD_0x2Exx://逆变器定标系数
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register0310H_t.tInvStdParam;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_03H_10H_INV_STD_START);
                break;

            case EMS_TO_PCS_10H_SR_INFO_0x28xx://安规信息地址表
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register10H_t.tSRInfo;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_10H_SR_START);
                break;

            case EMS_TO_PCS_10H_EMS_CONTROL_0x29xx://EMS控制信息
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register10H_t.tEMSControlInfo;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_10H_EMSControl_START);
                break;

            case EMS_TO_PCS_10H_EMS_PARAM_0x2Fxx://能量管理地址表
                pu8ObjBuf = (uint16_t*)& tInternalComData.Register10H_t.tEmsParam;
                pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - PCS_10H_EMS_PARAM_START);
                break;
            default:
                break;
        }
    }
    /*对接英臻云平台协议地址*/
    if(MB_SLAVE_CLOUD_LOCAL_ADDR == ptMBFrame->u8MBAddress)
    {
        pu8ObjBuf = GetComDataToCloud_10H(ptMBFrame);
    }
    return pu8ObjBuf;
}

/***************************************************************************
 功能:PCS协议数据绑定(光伏1数据)对外接口
****************************************************************************/
static void GetDisplayRealTimePV1Data(Display_DATA_PVPara* ptDisplayPV1Data)
{
    ptDisplayPV1Data->u16PVVoltage = (uint16_t) (tInternalComData.Register03H_t.tPV1Information.u16PVVolt);
    ptDisplayPV1Data->sPVCurrent = (int16_t) (tInternalComData.Register03H_t.tPV1Information.s16PVCurr);
    ptDisplayPV1Data->sPVPower = (int16_t) (tInternalComData.Register03H_t.tPV1Information.s16PVLivePower);
}

/***************************************************************************
 功能:LPCS协议数据绑定(光伏2数据)对外接口
****************************************************************************/
static void GetDisplayRealTimePV2Data(Display_DATA_PVPara* ptDisplayPV2Data)
{
    ptDisplayPV2Data->u16PVVoltage = (uint16_t) (tInternalComData.Register03H_t.tPV2Information.u16PVVolt);
    ptDisplayPV2Data->sPVCurrent = (int16_t) (tInternalComData.Register03H_t.tPV2Information.s16PVCurr);
    ptDisplayPV2Data->sPVPower = (int16_t) (tInternalComData.Register03H_t.tPV2Information.s16PVLivePower);
}

/***************************************************************************
 功能:PCS协议数据绑定(光伏数据)对外接口
****************************************************************************/
void GetDisplayRealTimePVData(Display_DATA_PV* ptDisplayPVData)
{
    GetDisplayRealTimePV1Data(&(ptDisplayPVData->stPV1));
    GetDisplayRealTimePV2Data(&(ptDisplayPVData->stPV2));
}

/***************************************************************************
 功能:PCS协议数据绑定(负载数据)对外接口
****************************************************************************/
void GetDisplayRealTimeLoadData(Display_DATA_LOAD* ptDisplayLoadData)
{
    ptDisplayLoadData->u16LoadVoltage = (uint16_t) (tInternalComData.Register03H_t.tInvInformation.u16LoadVoltR);
    ptDisplayLoadData->sLoadcurrent = (int16_t) (tInternalComData.Register03H_t.tInvInformation.s16InvLoadCurrR);
    ptDisplayLoadData->sLoadPower = (int16_t) (tInternalComData.Register03H_t.tInvInformation.s16InvLoadCurrWattR);   //暂定为负载有功功率，后续需要添加负载无功功率
}

/***************************************************************************
功能:PCS协议数据绑定(发电机数据)对外接口
****************************************************************************/
void GetDisplayRealTimeGenData(Display_DATA_Gen* ptDisplayGenData)
{
    ptDisplayGenData->u16GenVoltage = (uint16_t) (tInternalComData.Register03H_t.tInvInformation.u16GenVoltR);
    ptDisplayGenData->sGencurrent = (int16_t) (tInternalComData.Register03H_t.tInvInformation.s16GenCurrR);
    ptDisplayGenData->sGenPower = (int16_t) (tInternalComData.Register03H_t.tInvInformation.s16GenWattR);   //暂定为发电机有功功率，后续需要添加发电机无功功率
    ptDisplayGenData->u16GenFrequency = (uint16_t) (tInternalComData.Register03H_t.tInvInformation.u16GenFreq);
}

/***********************************************************************************************************************
 功能：获取PCS协议10H功能码能量管理地址的数据接口
************************************************************************************************************************/
void GetPcs10HEmsParam(EmsParam_t* pEmsParam)
{
    memcpy(pEmsParam,&tInternalComData.Register10H_t.tEmsParam,sizeof(EmsParam_t));
}

/***********************************************************************************************************************
 功能：获取系统故障的接口
************************************************************************************************************************/
void GetDisplaySystemFault(Display_SYS_Fault_t* ptDisplaySysFault)
{
    memcpy(ptDisplaySysFault,&tInternalComData.Register03H_t.tTotalParam.SysFault_t,sizeof(Display_SYS_Fault_t));
}

/***********************************************************************************************************************
 功能：查询光伏1故障的接口
************************************************************************************************************************/
static void GetDisplayPV1Fault(PV_Fault_t* ptDisplayPV1Fault)
{
    memcpy(ptDisplayPV1Fault,&tInternalComData.Register03H_t.tPV1Information.PVFault_t,sizeof(PV_Fault_t));
}

/***********************************************************************************************************************
 功能：查询光伏2故障的接口
************************************************************************************************************************/
static void GetDisplayPV2Fault(PV_Fault_t* ptDisplayPV2Fault)
{
    memcpy(ptDisplayPV2Fault,&tInternalComData.Register03H_t.tPV2Information.PVFault_t,sizeof(PV_Fault_t));
}

/***********************************************************************************************************************
 功能：查询光伏故障的接口
************************************************************************************************************************/
void GetDisplayPVFault(Display_PV_Fault_t* ptDisplayPVFault)
{
    GetDisplayPV1Fault(&ptDisplayPVFault->stPVFault[0]);
    GetDisplayPV2Fault(&ptDisplayPVFault->stPVFault[1]);
}

/***********************************************************************************************************************
 功能：查询逆变器故障的接口
************************************************************************************************************************/
void GetDisplayInvFault(Display_INV_Fault_t* ptDisplayInvFault)
{
    memcpy(ptDisplayInvFault,&tInternalComData.Register03H_t.tInvInformation.InvFault_t,sizeof(Display_INV_Fault_t));
}

/***********************************************************************************************************************
 功能：查询DCDC故障的接口
************************************************************************************************************************/
void GetDisplayDCDCFault(Display_DCDC_Fault_t* ptDisplayDCDCFault)
{
    memcpy(ptDisplayDCDCFault,&tInternalComData.Register03H_t.tDCDCInformation.DCDC_Error_t,sizeof(Display_DCDC_Fault_t));
}

/***********************************************************************************************************************
 功能：查询系统告警的接口
************************************************************************************************************************/
void GetDisplaySysAlarm(Display_SYS_Alarm_t* ptDisplaySysAlarm)
{
    memcpy(ptDisplaySysAlarm,&tInternalComData.Register03H_t.tTotalParam.SysAlarm_t,sizeof(Display_SYS_Alarm_t));
}

/***********************************************************************************************************************
 功能：查询发电机故障的接口
************************************************************************************************************************/
void GetDisplayGenFault(Display_Gen_Fault_t* ptDisplayGenFault)
{
    memcpy(ptDisplayGenFault,&tInternalComData.Register03H_t.tInvInformation.GenFault_t,sizeof(Display_Gen_Fault_t));
}

/***********************************************************************************************************************
 功能：查询EMS通讯故障的接口
************************************************************************************************************************/
void GetDisplayEMSCommFault(Display_EMS_Fault_t* ptDisplayEMSFault)
{
    ptDisplayEMSFault->EmsError_t.Bits.bWeakBatteryFault = Battery_Protect_Para.eWeakBatteryFault; //EMS检测到的弱电池故障

    ptDisplayEMSFault->EmsError_t.Bits.bPcsCommState = !(tCommStatus.tCommDisconnectFlag.Bits.bEmsToPcsCommStateFlag);     //EMS本地检测到的PCS通信状态
    switch (BmsComWayType)
    {
        case BMS_LI_ION_CAN:
            ptDisplayEMSFault->EmsError_t.Bits.bBmsCommState = !(tCommStatus.tCommDisconnectFlag.Bits.bEmsToBmsCanCommStateFlag);     //EMS本地检测到的电池包通信状态
            break;
        case BMS_LI_ION_485:
            ptDisplayEMSFault->EmsError_t.Bits.bBmsCommState = !(tCommStatus.tCommDisconnectFlag.Bits.bEmsToBmsCommStateFlag);        //EMS本地检测到的电池包通信状态 
            break;
        default:
            break;
    }  
    
    ptDisplayEMSFault->EmsError_t.Bits.bCTCommState = tInternalComData.Register03H_t.tInvInformation.InvFault_t.GridFault2_t.Bits.bCTDisconnectErr;//PCS检测到的CT通信状态
    ptDisplayEMSFault->EmsError_t.Bits.bMeterCommState = tInternalComData.Register03H_t.tInvInformation.InvFault_t.GridFault2_t.Bits.bMeterDisconnectErr; //PCS检测到的电表通信状态
    //ptDisplayEMSFault->EmsError_t.Bits.bMeterCommState = !(tCommStatus.tCommDisconnectFlag.Bits.bEmsToMeterCommStateFlag); //EMS本地检测到的电表通信状态
}

/***********************************************************************************************************************
 功能：查询电网发电机状态的接口
************************************************************************************************************************/
void GetDisplayGridGenState(DisplayGenGridState_t* tGenRunState)
{
    memcpy(tGenRunState,&tInternalComData.Register03H_t.tInvInformation.GenRunState_t,sizeof(DisplayGenGridState_t));
}

/***********************************************************************************************************************
 功能：查询逆变器状态的接口
************************************************************************************************************************/
void GetDisplayInvState(DisplayInvRunState_t* tInvRunState)
{
    memcpy(tInvRunState,&tInternalComData.Register03H_t.tInvInformation.u16InvRunState,sizeof(DisplayInvRunState_t));
}

/***********************************************************************************************************************
 功能：查询版本号的接口
************************************************************************************************************************/
void GetDisplaySoftwareVersion(Display_DSP_MCU_Version* tDspMcuVersion)
{
    memcpy(tDspMcuVersion,&tInternalComData.Register03H_t.tTotalParam.tDspMcuVersion,sizeof(Display_DSP_MCU_Version));
}

/***********************************************************************************************************************
 功能：查询发电机启停状态的接口
************************************************************************************************************************/
uint16_t GetGenRunState(void)
{
    return tInternalComData.Register03H_t.tTotalParam.u16GenRunState;
}

/***********************************************************************************************************************
 功能：查询共有参数信息的接口
************************************************************************************************************************/
void GetTotalParamInfo(TotalParam_t* tTotalParam)
{
    memcpy(tTotalParam,&tInternalComData.Register03H_t.tTotalParam,sizeof(TotalParam_t));
}

/***********************************************************************************************************************
 功能：查询光伏1数据信息的接口
************************************************************************************************************************/
void GetPV1Information(PVInformation_t* tPV1Information)
{
    memcpy(tPV1Information,&tInternalComData.Register03H_t.tPV1Information,sizeof(PVInformation_t));
}

/***********************************************************************************************************************
 功能：查询光伏2数据信息的接口
************************************************************************************************************************/
void GetPV2Information(PVInformation_t* tPV2Information)
{
    memcpy(tPV2Information,&tInternalComData.Register03H_t.tPV2Information,sizeof(PVInformation_t));
}

/***********************************************************************************************************************
 功能：查询逆变器数据信息的接口
************************************************************************************************************************/
void GetInvInformation(InvInformation_t* tInvInformation)
{
    memcpy(tInvInformation,&tInternalComData.Register03H_t.tInvInformation,sizeof(InvInformation_t));
}

/***********************************************************************************************************************
 功能：查询逆变器数据信息的接口
************************************************************************************************************************/
void GetDCDCInformation(DCDCInformation_t* tDCDCInformation)
{
    memcpy(tDCDCInformation,&tInternalComData.Register03H_t.tDCDCInformation,sizeof(DCDCInformation_t));
}
/***********************************************************************************************************************
 功能：设置PCS协议10H功能码能量管理地址的数据接口
************************************************************************************************************************/
void SetPcs10HEnergyStrategy(EmsParam_t* pEmsParam)
{
    memcpy(&tInternalComData.Register10H_t.tEmsParam,pEmsParam,sizeof (EmsParam_t));
    externalSetFlag.Bits.bEnergyManageSetFlag = STATUS_TRUE;
}

/***********************************************************************************************************************
 功能：下设开关机指令的对外接口
************************************************************************************************************************/
void SetPcs05HPowerOnOffControl(uint16_t u16OnOffState)
{
    tInternalComData.Register05H_t.tData05H.u16StartStopCtrl = u16OnOffState;
    externalSetFlag.Bits.bPowerOnOffSetFlag = STATUS_TRUE;
}

/***********************************************************************************************************************
 功能：下设安规信息的接口
************************************************************************************************************************/
void SetPcs10HGridStandardInfo(SR_Universal* tSRUniversal)
{
    memcpy(&tInternalComData.Register10H_t.tSRInfo,tSRUniversal,sizeof(SR_Universal));
    externalSetFlag.Bits.bGridStandardSetFlag = STATUS_TRUE;
}

/***********************************************************************************************************************
 功能：下设无功功率的接口
************************************************************************************************************************/
void SetPcs10HReactivePower(int16_t sReactivePowerValue)
{
    tInternalComData.Register10H_t.tEmsParam.s16EmsVar = sReactivePowerValue;
    externalSetFlag.Bits.bReactivePowerFlag = STATUS_TRUE;
}

/***********************************************************************************************************************
 功能：下设功率因数的接口
************************************************************************************************************************/
void SetPcs10HPowerFactor(int16_t sPowerFactorValue)
{
    tInternalComData.Register10H_t.tEmsParam.sPowerFactor = sPowerFactorValue;
    externalSetFlag.Bits.bPowerFactorFlag = STATUS_TRUE;
}

#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/


