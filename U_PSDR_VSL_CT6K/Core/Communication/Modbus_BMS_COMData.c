/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Modbus_BMS_COMData.c
 用途 : ModbusBMS协议相关函数
***********************************************************************************************************************/
#ifndef MODBUS_BMS_COMDATA_C_
#define MODBUS_BMS_COMDATA_C_

#include "Modbus_BMS_COMData.h"
#include "Battery_Protect_Service.h"

#define PROTO_NULL                              (0x7FFF) //无效位填充

/*BMS协议相关数据结构的定义*/
UnifiedBMSData_t   tUnifiedBMSData;     //BMS协议公用数据结构
BmsDataCvte_t      tBmsDataCvte;        //BMS协议CVTE数据结构
BMSDataGrowatt_t   tBmsDataGrowatt;     //BMS协议Growatt数据结构
BmsDataPylon_t     tBmsDataPylon;       //BMS协议Pylon数据结构
IronTowerBMSData_t tIronTowerBMSData;   //BMS协议Iron数据结构
VoltronicBmsData_t tVoltronicBmsData;   //BMS协议Voltronic数据结构

BMS_Manu_TypeDef MBBmsProtocolType;
BMS_COMWAY_TypeDef BmsComWayType;
/***********************************************************************************************************************
 功能：检查BMS_Growatt协议功能码03H的通讯数据范围是否越界
************************************************************************************************************************/
MBErrorCode CheckBmsGrowattComDataRange_03H(MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;

    if ((BMS_Growatt_03H_SPEC_QUERY_START <= (ptMBFrame->u16MBStartRegsAddr)) && (BMS_Growatt_03H_SPEC_QUERY_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        if((BMS_Growatt_03H_SPEC_QUERY_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - BMS_Growatt_03H_SPEC_QUERY_START)) || \
           (BMS_Growatt_03H_SPEC_QUERY_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - BMS_Growatt_03H_SPEC_QUERY_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if ((BMS_Growatt_03H_STATUS_QUERY_START <= (ptMBFrame->u16MBStartRegsAddr)) && (BMS_Growatt_03H_STATUS_QUERY_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        if((BMS_Growatt_03H_STATUS_QUERY_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - BMS_Growatt_03H_STATUS_QUERY_START)) || \
           (BMS_Growatt_03H_STATUS_QUERY_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - BMS_Growatt_03H_STATUS_QUERY_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if ((BMS_Growatt_03H_SPEC_QUERY2_START <= (ptMBFrame->u16MBStartRegsAddr)) && (BMS_Growatt_03H_SPEC_QUERY2_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        if((BMS_Growatt_03H_SPEC_QUERY2_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - BMS_Growatt_03H_SPEC_QUERY2_START)) || \
           (BMS_Growatt_03H_SPEC_QUERY2_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - BMS_Growatt_03H_SPEC_QUERY2_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if ((BMS_Growatt_03H_STATUS_QUERY2_START <= (ptMBFrame->u16MBStartRegsAddr)) && (BMS_Growatt_03H_STATUS_QUERY2_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        if((BMS_Growatt_03H_STATUS_QUERY2_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - BMS_Growatt_03H_STATUS_QUERY2_START)) || \
           (BMS_Growatt_03H_STATUS_QUERY2_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - BMS_Growatt_03H_STATUS_QUERY2_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if (BMS_Growatt_03H_BATTERY_PACK_ID_START == (ptMBFrame->u16MBStartRegsAddr))
    {
        if((BMS_Growatt_03H_BATTERY_PACK_ID_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - BMS_Growatt_03H_BATTERY_PACK_ID_START)) || \
           (BMS_Growatt_03H_BATTERY_PACK_ID_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - BMS_Growatt_03H_BATTERY_PACK_ID_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if ((BMS_Growatt_03H_CELL_VOL_STATUS_START <= (ptMBFrame->u16MBStartRegsAddr)) && (BMS_Growatt_03H_CELL_VOL_STATUS_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        if((BMS_Growatt_03H_CELL_VOL_STATUS_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - BMS_Growatt_03H_CELL_VOL_STATUS_START)) || \
           (BMS_Growatt_03H_CELL_VOL_STATUS_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - BMS_Growatt_03H_CELL_VOL_STATUS_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if ((BMS_Growatt_03H_CELL_VOL_STATUS2_START <= (ptMBFrame->u16MBStartRegsAddr)) && (BMS_Growatt_03H_CELL_VOL_STATUS2_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        if((BMS_Growatt_03H_CELL_VOL_STATUS2_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - BMS_Growatt_03H_CELL_VOL_STATUS2_START)) || \
           (BMS_Growatt_03H_CELL_VOL_STATUS2_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - BMS_Growatt_03H_CELL_VOL_STATUS2_START)))
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
 功能：定位起始地址对应的BMS_GROWATT协议功能码03H的数据结构地址
************************************************************************************************************************/
uint16_t* GetBmsGrowattComDataIndex_03H(MBRTUFrame_t* ptMBFrame)
{
    uint16_t *pu8ObjBuf = NULL;

    if ((BMS_Growatt_03H_SPEC_QUERY_START <= (ptMBFrame->u16MBStartRegsAddr)) && (BMS_Growatt_03H_SPEC_QUERY_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        pu8ObjBuf = (uint16_t*)& tBmsDataGrowatt.tBmsGrowattSpecQuery;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - BMS_Growatt_03H_SPEC_QUERY_START);
    }
    else if ((BMS_Growatt_03H_STATUS_QUERY_START <= (ptMBFrame->u16MBStartRegsAddr)) && (BMS_Growatt_03H_STATUS_QUERY_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        pu8ObjBuf = (uint16_t*)& tBmsDataGrowatt.tBmsGrowattStatusQuery;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - BMS_Growatt_03H_STATUS_QUERY_START);
    }
    else if ((BMS_Growatt_03H_SPEC_QUERY2_START <= (ptMBFrame->u16MBStartRegsAddr)) && (BMS_Growatt_03H_SPEC_QUERY2_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        pu8ObjBuf = (uint16_t*)& tBmsDataGrowatt.tBmsGrowattSpecQuery2;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - BMS_Growatt_03H_SPEC_QUERY2_START);
    }
    else if ((BMS_Growatt_03H_STATUS_QUERY2_START <= (ptMBFrame->u16MBStartRegsAddr)) && (BMS_Growatt_03H_STATUS_QUERY2_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        pu8ObjBuf = (uint16_t*)& tBmsDataGrowatt.tBmsGrowattStatusQuery2;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - BMS_Growatt_03H_STATUS_QUERY2_START);
    }
    else if (BMS_Growatt_03H_BATTERY_PACK_ID_START == (ptMBFrame->u16MBStartRegsAddr))
    {
        pu8ObjBuf = (uint16_t*)& tBmsDataGrowatt.tBmsGrowattBatteryPackID;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - BMS_Growatt_03H_BATTERY_PACK_ID_START);
    }
    else if ((BMS_Growatt_03H_CELL_VOL_STATUS_START <= (ptMBFrame->u16MBStartRegsAddr)) && (BMS_Growatt_03H_CELL_VOL_STATUS_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        pu8ObjBuf = (uint16_t*)& tBmsDataGrowatt.tBmsGrowattCellVoltageStatus;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - BMS_Growatt_03H_CELL_VOL_STATUS_START);
    }
    else if ((BMS_Growatt_03H_CELL_VOL_STATUS2_START <= (ptMBFrame->u16MBStartRegsAddr)) && (BMS_Growatt_03H_CELL_VOL_STATUS2_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        pu8ObjBuf = (uint16_t*)& tBmsDataGrowatt.tBmsGrowattCellVoltageStatus2;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - BMS_Growatt_03H_CELL_VOL_STATUS2_START);
    }
    else
    {
        ;
    }

    return pu8ObjBuf;
}

/***********************************************************************************************************************
 功能：BMS_CVTE协议地址识别表
************************************************************************************************************************/
typedef enum
{
    BMS_DATA_CVTE_03H_0x000x  =  0x0000,
    BMS_DATA_CVTE_03H_0x001x  =  0x0010,
    BMS_DATA_CVTE_03H_0x002x  =  0x0020,
    BMS_DATA_CVTE_03H_0x003x  =  0x0030,
    BMS_DATA_CVTE_03H_0x004x  =  0x0040,
    BMS_DATA_CVTE_03H_0x005x  =  0x0050,
    BMS_DATA_CVTE_03H_0x006x  =  0x0060,
}BMS_DATA_CVTE_ADDRESS;

/***********************************************************************************************************************
 功能：检查BMS_CVTE协议功能码03H的通讯数据范围是否越界
************************************************************************************************************************/
MBErrorCode CheckBmsCvteComDataRange_03H(MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;

    if ((BMS_DATA_CVTE_03H_0x000x == ((ptMBFrame->u16MBStartRegsAddr) & 0x00F0)) || \
        (BMS_DATA_CVTE_03H_0x001x == ((ptMBFrame->u16MBStartRegsAddr) & 0x00F0)))
    {
        if((BMS_CVTE_03H_VERSION_INFO_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - BMS_CVTE_03H_VERSION_INFO_START)) || \
           (BMS_CVTE_03H_VERSION_INFO_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - BMS_CVTE_03H_VERSION_INFO_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if ((BMS_DATA_CVTE_03H_0x002x == ((ptMBFrame->u16MBStartRegsAddr) & 0x00F0)) || \
             (BMS_DATA_CVTE_03H_0x003x == ((ptMBFrame->u16MBStartRegsAddr) & 0x00F0)))
    {
        if((BMS_CVTE_03H_PRIMARY_INFO_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - BMS_CVTE_03H_PRIMARY_INFO_START)) || \
           (BMS_CVTE_03H_PRIMARY_INFO_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - BMS_CVTE_03H_PRIMARY_INFO_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if ((BMS_DATA_CVTE_03H_0x004x == ((ptMBFrame->u16MBStartRegsAddr) & 0x00F0)) || \
             (BMS_DATA_CVTE_03H_0x005x == ((ptMBFrame->u16MBStartRegsAddr) & 0x00F0)))
    {
        if((BMS_CVTE_03H_VOLTAGE_INFO_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - BMS_CVTE_03H_VOLTAGE_INFO_START)) || \
           (BMS_CVTE_03H_VOLTAGE_INFO_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - BMS_CVTE_03H_VOLTAGE_INFO_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if (BMS_DATA_CVTE_03H_0x006x == ((ptMBFrame->u16MBStartRegsAddr) & 0x00F0))
    {
        if((BMS_CVTE_03H_TEMP_INFO_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - BMS_CVTE_03H_TEMP_INFO_START)) || \
           (BMS_CVTE_03H_TEMP_INFO_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - BMS_CVTE_03H_TEMP_INFO_START)))
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
 功能：定位起始地址对应的BMS_CVTE协议功能码03H的数据结构地址
************************************************************************************************************************/
uint16_t* GetBmsCvteComDataIndex_03H(MBRTUFrame_t* ptMBFrame)
{
    uint16_t *pu8ObjBuf = NULL;

    if ((BMS_DATA_CVTE_03H_0x000x == ((ptMBFrame->u16MBStartRegsAddr) & 0x00F0)) || \
        (BMS_DATA_CVTE_03H_0x001x == ((ptMBFrame->u16MBStartRegsAddr) & 0x00F0)))
    {
        pu8ObjBuf = (uint16_t*)& tBmsDataCvte.tBmsCvteVersionInfo;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - BMS_CVTE_03H_VERSION_INFO_START);
    }
    else if ((BMS_DATA_CVTE_03H_0x002x == ((ptMBFrame->u16MBStartRegsAddr) & 0x00F0)) || \
             (BMS_DATA_CVTE_03H_0x003x == ((ptMBFrame->u16MBStartRegsAddr) & 0x00F0)))
    {
        pu8ObjBuf = (uint16_t*)& tBmsDataCvte.tBmsCvtePrimaryInfo;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - BMS_CVTE_03H_PRIMARY_INFO_START);
    }
    else if ((BMS_DATA_CVTE_03H_0x004x == ((ptMBFrame->u16MBStartRegsAddr) & 0x00F0)) || \
             (BMS_DATA_CVTE_03H_0x005x == ((ptMBFrame->u16MBStartRegsAddr) & 0x00F0)))
    {
        pu8ObjBuf = (uint16_t*)& tBmsDataCvte.tBmsCvteVoltageInfo;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - BMS_CVTE_03H_VOLTAGE_INFO_START);
    }
    else if (BMS_DATA_CVTE_03H_0x006x == ((ptMBFrame->u16MBStartRegsAddr) & 0x00F0))
    {
        pu8ObjBuf = (uint16_t*)& tBmsDataCvte.tBmsCvteTempInfo;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - BMS_CVTE_03H_TEMP_INFO_START);
    }
    else
    {
        ;
    }
    return pu8ObjBuf;
}

/***********************************************************************************************************************
 功能：检查BMS功能码03H的通讯数据范围是否越界
//后期还需修改，加入协议选择的变量后，兼容不同协议的检测
************************************************************************************************************************/
MBErrorCode CheckBmsComDataRange_03H(MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;
    eStatus = CheckBmsGrowattComDataRange_03H(ptMBFrame);
    //eStatus = CheckBmsCvteComDataRange_03H(ptMBFrame);

    return eStatus;
}

/***********************************************************************************************************************
 功能：定位起始地址对应的BMS协议功能码03H的数据结构地址 
//后期还需要修改，加入协议选择的变量后，兼容不同协议的检测
************************************************************************************************************************/
uint16_t* GetBmsComDataIndex_03H(MBRTUFrame_t* ptMBFrame)
{
    uint16_t *pu8ObjBuf = NULL;
    //pu8ObjBuf = GetBmsGrowattComDataIndex_03H(ptMBFrame);
    pu8ObjBuf = GetBmsCvteComDataIndex_03H(ptMBFrame);

    return pu8ObjBuf;
}

/***************************************************************************
 功能:LCD屏电池包的数据绑定（派能协议）
****************************************************************************/
static void GetDisplayRealTimePlyonBMSData(Display_DATA_BMS* ptDisplayBmsData)
{
    ptDisplayBmsData->u16BMSVoltage = (uint16_t) (tBmsDataPylon.tBmsPylonAnalogInfo.u16SystemAvgVolt / 100);                //后续优化
    ptDisplayBmsData->sBMSCurrent = (int16_t) (tBmsDataPylon.tBmsPylonAnalogInfo.s16SystemTotalCurr / 10);                  //后续优化
    //ptDisplayBmsData->sChargePower = 100;                                                                                 //???
    //ptDisplayBmsData->sDisChargePower = 110;                                                                              //???
    ptDisplayBmsData->u8SOC = (uint8_t) (tBmsDataPylon.tBmsPylonAnalogInfo.u16SystemSOC & 0x00FF);
    ptDisplayBmsData->u8SOH = (uint8_t) (tBmsDataPylon.tBmsPylonAnalogInfo.u16AvgSOH & 0x00FF);
    //ptDisplayBmsData->u8BMSType = BMS_TYPE_LFP;                                                                           //用户设置，由存储部分获取
    //ptDisplayBmsData->u16BMSCapacity = 120;                                                                               //???
    //ptDisplayBmsData->u16OverValtagevalue = 130;                                                                          //???
    //ptDisplayBmsData->u8DOD = ;                                                                                           //用户设置，由存储部分获取
    ptDisplayBmsData->sMaxChargeCurrent = (int16_t) (tBmsDataPylon.tBmsPylonMutualInfo.s16MaxChgCurr);
    ptDisplayBmsData->u16MaxChargeVoltage = (uint16_t) (tBmsDataPylon.tBmsPylonMutualInfo.u16ChgVoltHighLimit / 100);       //后续优化
    //ptDisplayBmsData->u16UnderValtagevalue = 150;                                                       //???
    ptDisplayBmsData->sMaxDisChargeCurrent = (int16_t) (tBmsDataPylon.tBmsPylonMutualInfo.s16MaxDischgCurr);
    ptDisplayBmsData->u16MaxDisChargeVoltage = (uint16_t) (tBmsDataPylon.tBmsPylonMutualInfo.u16DisChgVoltLowLimit / 100);  //后续优化
}

/***************************************************************************
 功能:LCD屏实时Cvte协议的电池数据绑定
****************************************************************************/
static void GetDisplayRealTimeCvteBMSData(Display_DATA_BMS* ptDisplayBmsData)
{
    ;
}

/***************************************************************************
 功能:LCD屏实时电池数据绑定
****************************************************************************/
void GetDisplayRealTimeBmsData(Display_DATA_BMS* ptDisplayBmsData)
{
    switch (u8BatteryType)
    {                                                                                                  //锂电通讯正常
    	case BMS_TYPE_LI_ION:
            switch (BmsComWayType)
            {
                case BMS_LI_ION_CAN:
                    switch(MBBmsProtocolType)
                    {
                        case BMS_MANU_Pylon:
                            GetDisplayRealTimePlyonBMSCanData(ptDisplayBmsData);
                            break;
                        case BMS_MANU_CVTE:
                            ;
                            break;
                        default:
                            break;
                    }
                    break;
                case BMS_LI_ION_485:
                    switch(MBBmsProtocolType)
                    {
                        case BMS_MANU_Pylon:
                            GetDisplayRealTimePlyonBMSData(ptDisplayBmsData);
                            break;
                        case BMS_MANU_CVTE:
                            GetDisplayRealTimeCvteBMSData(ptDisplayBmsData);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
    		break;
    	case BMS_TYPE_LEAD_ACID:                                                                                       
            GetDisplayRealTimeLeadBatteryData(ptDisplayBmsData);
    		break;
    	default:
    		break;
    }
}

/***************************************************************************
 功能:派能协议电池包模拟量数据绑定
****************************************************************************/
void GetBmsPylonAnalogInfo(BmsDataPylonAnalogInfo_t* tBmsPylonAnalogInfo)
{
    memcpy(tBmsPylonAnalogInfo,&tBmsDataPylon.tBmsPylonAnalogInfo,sizeof(BmsDataPylonAnalogInfo_t));
}

/***************************************************************************
 功能:派能协议电池包告警量数据绑定
****************************************************************************/
void GetBmsPylonAlarmInfo(BmsDataPylonAlarmInfo_t* tBmsPylonAlarmInfo)
{
    memcpy(tBmsPylonAlarmInfo,&tBmsDataPylon.tBmsPylonAlarmInfo,sizeof(BmsDataPylonAlarmInfo_t));
}

/***************************************************************************
 功能:派能协议电池包交互信息数据绑定
****************************************************************************/
void GetBmsPylonMutualInfo(BmsDataPylonMutualInfo_t* tBmsPylonMutualInfo)
{
    memcpy(tBmsPylonMutualInfo,&tBmsDataPylon.tBmsPylonMutualInfo,sizeof(BmsDataPylonMutualInfo_t));
}

/***********************************************************************************************************************
 功能：LCD显示屏查询电池包故障的接口
************************************************************************************************************************/
void GetDisplayBMSFault(Display_BMS_Fault_t* ptDisplayBmsFault)
{
    memcpy(ptDisplayBmsFault,&tBmsDataPylon.tBmsPylonAlarmInfo,sizeof(Display_BMS_Fault_t));
}

/***********************************************************************************************************************
 功能：电池包协议类型设置对外接口
************************************************************************************************************************/
void SetBmsProtocolType(BMS_Manu_TypeDef ptBmsProtocolType)
{
    MBBmsProtocolType = ptBmsProtocolType;
}

/***********************************************************************************************************************
 功能：电池包通讯方式设置对外接口
************************************************************************************************************************/
void SetBmsComWayType(BMS_COMWAY_TypeDef ptBmsComWayType)
{
    BmsComWayType = ptBmsComWayType;
}   

#if 0
/***********************************************************************************************************************
 功能：派能协议读系统基本信息的接口
************************************************************************************************************************/
void GetPylonBasicInfo(BmsDataPylonBasicInfo_t* pBmsDataPylonBasicInfo,uint16_t u16Length)
{
    uint16_t i;
    uint16_t *pu16Source;
    uint16_t *pu16Object;
    pu16Source = (uint16_t*)& tBmsDataPylon.tBmsPylonBasicInfo;
    pu16Object = (uint16_t*)pBmsDataPylonBasicInfo;

    for(i = 0; i < u16Length; i++)
    {
        *pu16Object = *pu16Source;
        pu16Source++;
        pu16Object++;
    }
}

/***********************************************************************************************************************
 功能：派能协议读运行模拟量信息的接口
************************************************************************************************************************/
void GetPylonAnalogInfo(BmsDataPylonAnalogInfo_t* pBmsDataPylonAnalogInfo,uint16_t u16Length)
{
    uint16_t i;
    uint16_t *pu16Source;
    uint16_t *pu16Object;
    pu16Source = (uint16_t*)& tBmsDataPylon.tBmsPylonAnalogInfo;
    pu16Object = (uint16_t*)pBmsDataPylonAnalogInfo;

    for(i = 0; i < u16Length; i++)
    {
        *pu16Object = *pu16Source;
        pu16Source++;
        pu16Object++;
    }
}

/***********************************************************************************************************************
 功能：派能协议读状态告警量信息的接口
************************************************************************************************************************/
void GetPylonAlarmInfo(BmsDataPylonAlarmInfo_t* pBmsDataPylonAlarmInfo,uint16_t u16Length)
{
    uint16_t i;
    uint16_t *pu16Source;
    uint16_t *pu16Object;
    pu16Source = (uint16_t*)& tBmsDataPylon.tBmsPylonAlarmInfo;
    pu16Object = (uint16_t*)pBmsDataPylonAlarmInfo;

    for(i = 0; i < u16Length; i++)
    {
        *pu16Object = *pu16Source;
        pu16Source++;
        pu16Object++;
    }
}

/***********************************************************************************************************************
 功能：派能协议读充放电管理交互信息的接口
************************************************************************************************************************/
void GetPylonMutualInfo(BmsDataPylonMutualInfo_t* pBmsDataPylonMutualInfo,uint16_t u16Length)
{
    uint16_t i;
    uint16_t *pu16Source;
    uint16_t *pu16Object;
    pu16Source = (uint16_t*)& tBmsDataPylon.tBmsPylonMutualInfo;
    pu16Object = (uint16_t*)pBmsDataPylonMutualInfo;

    for(i = 0; i < u16Length; i++)
    {
        *pu16Object = *pu16Source;
        pu16Source++;
        pu16Object++;
    }
}

/***********************************************************************************************************************
 功能：提取BMS不同协议的公共故障信息
************************************************************************************************************************/

void BmsErrorUnified(MBModeBMS ProtocolType)
{
    switch ( ProtocolType )
    {
        case MB_RTU_GROWATT :
            tUnifiedBMSData.BMSError_t.Bits.u8OverVoltProt = tBmsDataGrowatt.tBmsGrowattStatusQuery.Error_t.Bits.u8OVP;
            tUnifiedBMSData.BMSError_t.Bits.u8UnderVoltProt = tBmsDataGrowatt.tBmsGrowattStatusQuery.Error_t.Bits.u8UVP;
            tUnifiedBMSData.BMSError_t.Bits.u8OverCurrProt = (tBmsDataGrowatt.tBmsGrowattStatusQuery.Error_t.Bits.u8OCD) | (tBmsDataGrowatt.tBmsGrowattStatusQuery.Error_t.Bits.u8OCC);
            tUnifiedBMSData.BMSError_t.Bits.u8ShortCircuitProt = tBmsDataGrowatt.tBmsGrowattStatusQuery.Error_t.Bits.u8SCD;
            tUnifiedBMSData.BMSError_t.Bits.u8HighTempProt = (tBmsDataGrowatt.tBmsGrowattStatusQuery.Error_t.Bits.u8OTD) | (tBmsDataGrowatt.tBmsGrowattStatusQuery.Error_t.Bits.u8OTC) | \
                                                             (tBmsDataGrowatt.tBmsGrowattStatusQuery.Error_t.Bits.u8EnvironmentOTP) | (tBmsDataGrowatt.tBmsGrowattStatusQuery.Error_t.Bits.u8MosfetOTP);
            tUnifiedBMSData.BMSError_t.Bits.u8UnderTempProt = (tBmsDataGrowatt.tBmsGrowattStatusQuery.Error_t.Bits.u8UTD) | \
                                                              (tBmsDataGrowatt.tBmsGrowattStatusQuery.Error_t.Bits.u8UTC) | (tBmsDataGrowatt.tBmsGrowattStatusQuery.Error_t.Bits.u8EnvironmentUTP);
            tUnifiedBMSData.BMSError_t.Bits.u8SystemProt = 0;
            tUnifiedBMSData.BMSError_t.Bits.u8LowPowerProt = 0;
            tUnifiedBMSData.BMSError_t.Bits.u8SoftStartProt = tBmsDataGrowatt.tBmsGrowattStatusQuery.Error_t.Bits.u8SoftStartFail;
            tUnifiedBMSData.BMSError_t.Bits.u8Reserved = 0;
            break;


        case MB_RTU_VOLTRONIC :
            tUnifiedBMSData.BMSError_t.Bits.u8OverVoltProt = 0;
            tUnifiedBMSData.BMSError_t.Bits.u8UnderVoltProt = 0;
            tUnifiedBMSData.BMSError_t.Bits.u8OverCurrProt = 0;
            tUnifiedBMSData.BMSError_t.Bits.u8ShortCircuitProt = 0;
            tUnifiedBMSData.BMSError_t.Bits.u8HighTempProt = 0;
            tUnifiedBMSData.BMSError_t.Bits.u8UnderTempProt = 0;
            tUnifiedBMSData.BMSError_t.Bits.u8SystemProt = 0;
            tUnifiedBMSData.BMSError_t.Bits.u8LowPowerProt = 0;
            tUnifiedBMSData.BMSError_t.Bits.u8SoftStartProt = 0;
            tUnifiedBMSData.BMSError_t.Bits.u8Reserved = 0;
            break;

        case MB_RTU_CVTE :
            tUnifiedBMSData.BMSError_t.Bits.u8OverVoltProt = tBmsDataCvte.tBmsCvtePrimaryInfo.Error_t.Bits.u8OVP;
            tUnifiedBMSData.BMSError_t.Bits.u8UnderVoltProt = tBmsDataCvte.tBmsCvtePrimaryInfo.Error_t.Bits.u8UVP;
            tUnifiedBMSData.BMSError_t.Bits.u8OverCurrProt = tBmsDataCvte.tBmsCvtePrimaryInfo.Error_t.Bits.u8OCP;
            tUnifiedBMSData.BMSError_t.Bits.u8ShortCircuitProt = tBmsDataCvte.tBmsCvtePrimaryInfo.Error_t.Bits.u8SCP;
            tUnifiedBMSData.BMSError_t.Bits.u8HighTempProt = tBmsDataCvte.tBmsCvtePrimaryInfo.Error_t.Bits.u8HTP;
            tUnifiedBMSData.BMSError_t.Bits.u8UnderTempProt = tBmsDataCvte.tBmsCvtePrimaryInfo.Error_t.Bits.u8LTP;
            tUnifiedBMSData.BMSError_t.Bits.u8SystemProt = tBmsDataCvte.tBmsCvtePrimaryInfo.Error_t.Bits.u8SysError;
            tUnifiedBMSData.BMSError_t.Bits.u8LowPowerProt = 0;
            tUnifiedBMSData.BMSError_t.Bits.u8SoftStartProt = tBmsDataCvte.tBmsCvtePrimaryInfo.Error_t.Bits.u8SoftStart;
            tUnifiedBMSData.BMSError_t.Bits.u8Reserved = 0;
            break;

        case MB_ASCII_PYLON :
            tUnifiedBMSData.BMSError_t.Bits.u8OverVoltProt = tBmsDataPylon.tBmsPylonAlarmInfo.SystemError1_t.Bits.u8TotalModeOV;
            tUnifiedBMSData.BMSError_t.Bits.u8UnderVoltProt = tBmsDataPylon.tBmsPylonAlarmInfo.SystemError1_t.Bits.u8TotalModeUV;
            tUnifiedBMSData.BMSError_t.Bits.u8OverCurrProt = (tBmsDataPylon.tBmsPylonAlarmInfo.SystemError2_t.Bits.u8OCC) | (tBmsDataPylon.tBmsPylonAlarmInfo.SystemError2_t.Bits.u8OCD);
            tUnifiedBMSData.BMSError_t.Bits.u8ShortCircuitProt = 0;
            tUnifiedBMSData.BMSError_t.Bits.u8HighTempProt = (tBmsDataPylon.tBmsPylonAlarmInfo.SystemError1_t.Bits.u8MosfetOT) | (tBmsDataPylon.tBmsPylonAlarmInfo.SystemError1_t.Bits.u8SingleOT);
            tUnifiedBMSData.BMSError_t.Bits.u8UnderTempProt = tBmsDataPylon.tBmsPylonAlarmInfo.SystemError1_t.Bits.u8SingleUT;
            tUnifiedBMSData.BMSError_t.Bits.u8SystemProt = tBmsDataPylon.tBmsPylonAlarmInfo.SystemError2_t.Bits.u8SysFault;
            tUnifiedBMSData.BMSError_t.Bits.u8LowPowerProt = 0;
            tUnifiedBMSData.BMSError_t.Bits.u8SoftStartProt = 0;
            tUnifiedBMSData.BMSError_t.Bits.u8Reserved = 0;
            break;


        case MB_ASCII_IRON :
            tUnifiedBMSData.BMSError_t.Bits.u8OverVoltProt = (tIronTowerBMSData.VoltStatus_t.Bits.u8SingleOVPrt) | (tIronTowerBMSData.VoltStatus_t.Bits.u8TotalOVPrt);
            tUnifiedBMSData.BMSError_t.Bits.u8UnderVoltProt = (tIronTowerBMSData.VoltStatus_t.Bits.u8SingleUVPrt) | (tIronTowerBMSData.VoltStatus_t.Bits.u8TotalUVPrt);
            tUnifiedBMSData.BMSError_t.Bits.u8OverCurrProt = (tIronTowerBMSData.CurrStatus_t.Bits.u8ChgOCPrt) | \
                                                             (tIronTowerBMSData.CurrStatus_t.Bits.u8DisChgOCPrt1) | (tIronTowerBMSData.CurrStatus_t.Bits.u8DisChgOCPrt2);
            tUnifiedBMSData.BMSError_t.Bits.u8ShortCircuitProt = 0;
            tUnifiedBMSData.BMSError_t.Bits.u8HighTempProt = (tIronTowerBMSData.TempStatus_t.Bits.u8ChgOTPrt) | (tIronTowerBMSData.TempStatus_t.Bits.u8DisChgOTPrt) | \
                                                             (tIronTowerBMSData.TempStatus_t.Bits.u8AmbientOTPrt) | (tIronTowerBMSData.TempStatus_t.Bits.u8PowerOTPrt);
            tUnifiedBMSData.BMSError_t.Bits.u8UnderTempProt = (tIronTowerBMSData.TempStatus_t.Bits.u8ChgUTPrt) | (tIronTowerBMSData.TempStatus_t.Bits.u8DisChgUTPrt) | \
                                                              (tIronTowerBMSData.TempStatus_t.Bits.u8AmbientUTPrt) | (tIronTowerBMSData.TempStatus_t.Bits.u8PowerUTPrt);
            tUnifiedBMSData.BMSError_t.Bits.u8SystemProt = 0;
            tUnifiedBMSData.BMSError_t.Bits.u8LowPowerProt = 0;
            tUnifiedBMSData.BMSError_t.Bits.u8SoftStartProt = 0;
            tUnifiedBMSData.BMSError_t.Bits.u8Reserved = 0;
            break;
        default:
            ;
    }
}

/***********************************************************************************************************************
 
 功能：提取BMS不同协议的公共告警信息
************************************************************************************************************************/

void BmsWarningUnified(MBModeBMS ProtocolType)
{
    switch ( ProtocolType )
    {
        case MB_RTU_GROWATT :
            tUnifiedBMSData.BMSWarning_t.Bits.u8OverVoltAlarm = tBmsDataGrowatt.tBmsGrowattStatusQuery.Warning_t.Bits.u8OVP;
            tUnifiedBMSData.BMSWarning_t.Bits.u8UnderVoltAlarm = tBmsDataGrowatt.tBmsGrowattStatusQuery.Warning_t.Bits.u8UVP;
            tUnifiedBMSData.BMSWarning_t.Bits.u8OverCurrAlarm = (tBmsDataGrowatt.tBmsGrowattStatusQuery.Warning_t.Bits.u8OCC) | (tBmsDataGrowatt.tBmsGrowattStatusQuery.Warning_t.Bits.u8OCD);
            tUnifiedBMSData.BMSWarning_t.Bits.u8HighTempAlarm = (tBmsDataGrowatt.tBmsGrowattStatusQuery.Warning_t.Bits.u8OTD) | (tBmsDataGrowatt.tBmsGrowattStatusQuery.Warning_t.Bits.u8OTC) | \
                                                                (tBmsDataGrowatt.tBmsGrowattStatusQuery.Warning_t.Bits.u8EnvironmentOT) | (tBmsDataGrowatt.tBmsGrowattStatusQuery.Warning_t.Bits.u8MosfetOT);
            tUnifiedBMSData.BMSWarning_t.Bits.u8LowTempAlarm = (tBmsDataGrowatt.tBmsGrowattStatusQuery.Warning_t.Bits.u8UTD) | (tBmsDataGrowatt.tBmsGrowattStatusQuery.Warning_t.Bits.u8UTC) | \
                                                               (tBmsDataGrowatt.tBmsGrowattStatusQuery.Warning_t.Bits.u8EnvironmentUT);
            tUnifiedBMSData.BMSWarning_t.Bits.u8SystemAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8OverChgAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8ReverseAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8LowCapAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8LowPowerShutAlarm = tBmsDataGrowatt.tBmsGrowattStatusQuery.Warning_t.Bits.u8UVShutdown;
            tUnifiedBMSData.BMSWarning_t.Bits.u8Reserved = 0;
            break;


        case MB_RTU_VOLTRONIC :
            if((0x02 == tVoltronicBmsData.u16CellVoltState1) || (0x02 == tVoltronicBmsData.u16CellVoltState3) || \
               (0x02 == tVoltronicBmsData.u16CellVoltState5) || (0x02 == tVoltronicBmsData.u16CellVoltState7) || \
               (0x02 == tVoltronicBmsData.u16CellVoltState9) || (0x02 == tVoltronicBmsData.u16CellVoltState11) || \
               (0x02 == tVoltronicBmsData.u16CellVoltState13) || (0x02 == tVoltronicBmsData.u16CellVoltState15) || \
               (0x02 == tVoltronicBmsData.u16CellVoltState17) || (0x02 == tVoltronicBmsData.u16CellVoltState19) || \
               (0x02 == tVoltronicBmsData.u16ChgVoltState) || (0x02 == tVoltronicBmsData.u16DisChgVoltState) || \
               (0x02 == tVoltronicBmsData.u16CellChgVoltState) || (0x02 == tVoltronicBmsData.u16CellDisChgVoltState))
            {
                tUnifiedBMSData.BMSWarning_t.Bits.u8OverVoltAlarm = 1;
            }
            else
            {
                tUnifiedBMSData.BMSWarning_t.Bits.u8OverVoltAlarm = 0;
            }

            if((0x01 == tVoltronicBmsData.u16CellVoltState1) || (0x01 == tVoltronicBmsData.u16CellVoltState3) || \
               (0x01 == tVoltronicBmsData.u16CellVoltState5) || (0x01 == tVoltronicBmsData.u16CellVoltState7) || \
               (0x01 == tVoltronicBmsData.u16CellVoltState9) || (0x01 == tVoltronicBmsData.u16CellVoltState11) || \
               (0x01 == tVoltronicBmsData.u16CellVoltState13) || (0x01 == tVoltronicBmsData.u16CellVoltState15) || \
               (0x01 == tVoltronicBmsData.u16CellVoltState17) || (0x01 == tVoltronicBmsData.u16CellVoltState19) || \
               (0x01 == tVoltronicBmsData.u16ChgVoltState) || (0x01 == tVoltronicBmsData.u16DisChgVoltState) || \
               (0x01 == tVoltronicBmsData.u16CellChgVoltState) || (0x01 == tVoltronicBmsData.u16CellDisChgVoltState))
            {
                tUnifiedBMSData.BMSWarning_t.Bits.u8UnderVoltAlarm = 1;
            }
            else
            {
                tUnifiedBMSData.BMSWarning_t.Bits.u8UnderVoltAlarm = 0;
            }

            if((0x02 == tVoltronicBmsData.u16ModuleChgCurrState) || (0x02 == tVoltronicBmsData.u16ModuleDisChgCurrState))
            {
                tUnifiedBMSData.BMSWarning_t.Bits.u8OverCurrAlarm = 1;
            }
            else
            {
                tUnifiedBMSData.BMSWarning_t.Bits.u8OverCurrAlarm = 0;
            }

            if((0x02 == tVoltronicBmsData.s16TempState1) || \
               (0x02 == tVoltronicBmsData.s16TempState3) || (0x02 == tVoltronicBmsData.s16TempState5) || \
               (0x02 == tVoltronicBmsData.s16TempState7) || (0x02 == tVoltronicBmsData.s16TempState9) || \
               (0x02 == tVoltronicBmsData.s16ModuleChgTempState) || (0x02 == tVoltronicBmsData.s16ModuleDischgTempState) || \
               (0x02 == tVoltronicBmsData.s16CellChgTempState) || (0x02 == tVoltronicBmsData.s16CellDischgTempState))
            {
                tUnifiedBMSData.BMSWarning_t.Bits.u8HighTempAlarm = 1;
            }
            else
            {
                tUnifiedBMSData.BMSWarning_t.Bits.u8HighTempAlarm = 0;
            }

            if((0x01 == tVoltronicBmsData.s16TempState1) || \
               (0x01 == tVoltronicBmsData.s16TempState3) || (0x01 == tVoltronicBmsData.s16TempState5) || \
               (0x01 == tVoltronicBmsData.s16TempState7) || (0x01 == tVoltronicBmsData.s16TempState9) || \
               (0x01 == tVoltronicBmsData.s16ModuleChgTempState) || (0x01 == tVoltronicBmsData.s16ModuleDischgTempState) || \
               (0x01 == tVoltronicBmsData.s16CellChgTempState) || (0x01 == tVoltronicBmsData.s16CellDischgTempState))
            {
                tUnifiedBMSData.BMSWarning_t.Bits.u8LowTempAlarm = 1;
            }
            else
            {
                tUnifiedBMSData.BMSWarning_t.Bits.u8LowTempAlarm = 0;
            }

            tUnifiedBMSData.BMSWarning_t.Bits.u8SystemAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8OverChgAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8ReverseAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8LowCapAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8LowPowerShutAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8Reserved = 0;
            break;


        case MB_RTU_CVTE :
            tUnifiedBMSData.BMSWarning_t.Bits.u8OverVoltAlarm = tBmsDataCvte.tBmsCvtePrimaryInfo.Warning_t.Bits.u8OVW;
            tUnifiedBMSData.BMSWarning_t.Bits.u8UnderVoltAlarm = tBmsDataCvte.tBmsCvtePrimaryInfo.Warning_t.Bits.u8UVW;
            tUnifiedBMSData.BMSWarning_t.Bits.u8OverCurrAlarm = tBmsDataCvte.tBmsCvtePrimaryInfo.Warning_t.Bits.u8OCW;
            tUnifiedBMSData.BMSWarning_t.Bits.u8HighTempAlarm = tBmsDataCvte.tBmsCvtePrimaryInfo.Warning_t.Bits.u8HTW;
            tUnifiedBMSData.BMSWarning_t.Bits.u8LowTempAlarm = tBmsDataCvte.tBmsCvtePrimaryInfo.Warning_t.Bits.u8LTW;
            tUnifiedBMSData.BMSWarning_t.Bits.u8SystemAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8OverChgAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8ReverseAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8LowCapAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8LowPowerShutAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8Reserved = 0;
            break;


        case MB_ASCII_PYLON :
            tUnifiedBMSData.BMSWarning_t.Bits.u8OverVoltAlarm = (tBmsDataPylon.tBmsPylonAlarmInfo.SystemAlarm1_t.Bits.u8SingleVoltOV) | (tBmsDataPylon.tBmsPylonAlarmInfo.SystemAlarm1_t.Bits.u8TotalVoltOV);
            tUnifiedBMSData.BMSWarning_t.Bits.u8UnderVoltAlarm = (tBmsDataPylon.tBmsPylonAlarmInfo.SystemAlarm1_t.Bits.u8SingleVoltUV) | (tBmsDataPylon.tBmsPylonAlarmInfo.SystemAlarm1_t.Bits.u8TotalVoltUV);
            tUnifiedBMSData.BMSWarning_t.Bits.u8OverCurrAlarm = (tBmsDataPylon.tBmsPylonAlarmInfo.SystemAlarm2_t.Bits.u8OCC) | (tBmsDataPylon.tBmsPylonAlarmInfo.SystemAlarm2_t.Bits.u8OCD);
            tUnifiedBMSData.BMSWarning_t.Bits.u8HighTempAlarm = (tBmsDataPylon.tBmsPylonAlarmInfo.SystemAlarm1_t.Bits.u8MosfetOT) | (tBmsDataPylon.tBmsPylonAlarmInfo.SystemAlarm1_t.Bits.u8SingleOT);
            tUnifiedBMSData.BMSWarning_t.Bits.u8LowTempAlarm = tBmsDataPylon.tBmsPylonAlarmInfo.SystemAlarm1_t.Bits.u8SingleUT;
            tUnifiedBMSData.BMSWarning_t.Bits.u8SystemAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8OverChgAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8ReverseAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8LowCapAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8LowPowerShutAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8Reserved = 0;
            break;


        case MB_ASCII_IRON :
            tUnifiedBMSData.BMSWarning_t.Bits.u8OverVoltAlarm = (tIronTowerBMSData.VoltStatus_t.Bits.u8SingleOVAlarm) | (tIronTowerBMSData.VoltStatus_t.Bits.u8TotalOVAlarm);
            tUnifiedBMSData.BMSWarning_t.Bits.u8UnderVoltAlarm = (tIronTowerBMSData.VoltStatus_t.Bits.u8SingleUVAlarm) | (tIronTowerBMSData.VoltStatus_t.Bits.u8TotalUVAlarm);
            tUnifiedBMSData.BMSWarning_t.Bits.u8OverCurrAlarm = (tIronTowerBMSData.CurrStatus_t.Bits.u8ChgOCAlarm) | (tIronTowerBMSData.CurrStatus_t.Bits.u8DisChgOCAlarm);
            tUnifiedBMSData.BMSWarning_t.Bits.u8HighTempAlarm = (tIronTowerBMSData.TempStatus_t.Bits.u8ChgOTAlarm) | (tIronTowerBMSData.TempStatus_t.Bits.u8DisChgOTAlarm);
            tUnifiedBMSData.BMSWarning_t.Bits.u8LowTempAlarm = (tIronTowerBMSData.TempStatus_t.Bits.u8ChgUTAlarm) | (tIronTowerBMSData.TempStatus_t.Bits.u8DisChgUTAlarm);;
            tUnifiedBMSData.BMSWarning_t.Bits.u8SystemAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8OverChgAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8ReverseAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8LowCapAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8LowPowerShutAlarm = 0;
            tUnifiedBMSData.BMSWarning_t.Bits.u8Reserved = 0;
            break;
        default:
            ;
    }
}

/***********************************************************************************************************************
 功能：提取BMS不同协议的公共数据信息
************************************************************************************************************************/

void sBmsDataUnified(MBModeBMS ProtocolType)
{
    switch ( ProtocolType )
    {
        case MB_RTU_GROWATT :
            tUnifiedBMSData.u16BMSDataStatus = tBmsDataGrowatt.tBmsGrowattStatusQuery.Status_t.u16State;
            tUnifiedBMSData.u16BMSDataVolt = tBmsDataGrowatt.tBmsGrowattStatusQuery.u16Voltage;
            tUnifiedBMSData.s16BMSDataChgCurr = tBmsDataGrowatt.tBmsGrowattStatusQuery.s16Current;
            tUnifiedBMSData.s16BMSDataDisChgCurr = tBmsDataGrowatt.tBmsGrowattStatusQuery.s16Current;
            tUnifiedBMSData.s16BMSDataTemp = tBmsDataGrowatt.tBmsGrowattStatusQuery.s16Temperature;
            tUnifiedBMSData.u16BMSDataSOC = tBmsDataGrowatt.tBmsGrowattStatusQuery.u16SOC;
            tUnifiedBMSData.u16BMSDataRemainingCap = tBmsDataGrowatt.tBmsGrowattStatusQuery.u16GaugeRM;
            tUnifiedBMSData.u16BMSDataFullCap = tBmsDataGrowatt.tBmsGrowattStatusQuery.u16GaugeFCC;
            tUnifiedBMSData.u16BMSDataMaxChgCurr = tBmsDataGrowatt.tBmsGrowattStatusQuery.u16MaxChargeCurrent;
            tUnifiedBMSData.u16BMSDataCVVolt = tBmsDataGrowatt.tBmsGrowattStatusQuery.u16CVVoltage;
            tUnifiedBMSData.u16BMSDataReserved0 = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved1 = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved2 = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved3 = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved4 = PROTO_NULL;
            BmsErrorUnified(ProtocolType);
            BmsWarningUnified(ProtocolType);
            break;


        case MB_RTU_VOLTRONIC :
            tUnifiedBMSData.u16BMSDataStatus = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataVolt = tVoltronicBmsData.u16ModuleVolt;
            tUnifiedBMSData.s16BMSDataChgCurr = tVoltronicBmsData.s16ChgCurr;
            tUnifiedBMSData.s16BMSDataDisChgCurr = tVoltronicBmsData.s16DisChgCurr;
            tUnifiedBMSData.s16BMSDataTemp = ((tVoltronicBmsData.s16Temp1 - 32) * 2) >> 5;
            tUnifiedBMSData.u16BMSDataSOC = tVoltronicBmsData.u16ModuleSOC;
            tUnifiedBMSData.u16BMSDataRemainingCap = tVoltronicBmsData.u16ModuleTotalCapcity;
            tUnifiedBMSData.u16BMSDataFullCap = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataMaxChgCurr = tVoltronicBmsData.u16ChgCurrLimit;
            tUnifiedBMSData.u16BMSDataCVVolt = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved0 = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved1 = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved2 = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved3 = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved4 = PROTO_NULL;
            BmsErrorUnified(ProtocolType);
            BmsWarningUnified(ProtocolType);


        case MB_RTU_CVTE :
            tUnifiedBMSData.u16BMSDataStatus = tBmsDataCvte.tBmsCvtePrimaryInfo.Status_t.u16Word;
            tUnifiedBMSData.u16BMSDataVolt = tBmsDataCvte.tBmsCvtePrimaryInfo.u16Voltage;
            tUnifiedBMSData.s16BMSDataChgCurr = tBmsDataCvte.tBmsCvtePrimaryInfo.s16Current;
            tUnifiedBMSData.s16BMSDataDisChgCurr = tBmsDataCvte.tBmsCvtePrimaryInfo.s16Current;
            tUnifiedBMSData.s16BMSDataTemp = tBmsDataCvte.tBmsCvtePrimaryInfo.s16MaxTemperature;
            tUnifiedBMSData.u16BMSDataSOC = tBmsDataCvte.tBmsCvtePrimaryInfo.u16SOC;
            tUnifiedBMSData.u16BMSDataRemainingCap = tBmsDataCvte.tBmsCvtePrimaryInfo.u16RemainingCapacity;
            tUnifiedBMSData.u16BMSDataFullCap = tBmsDataCvte.tBmsCvtePrimaryInfo.u16FullingCapacity;
            tUnifiedBMSData.u16BMSDataMaxChgCurr = tBmsDataCvte.tBmsCvtePrimaryInfo.u16MaxChargeCurr;
            tUnifiedBMSData.u16BMSDataCVVolt = tBmsDataCvte.tBmsCvtePrimaryInfo.u16CVVoltage;
            tUnifiedBMSData.u16BMSDataReserved0 = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved1 = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved2 = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved3 = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved4 = PROTO_NULL;
            BmsErrorUnified(ProtocolType);
            BmsWarningUnified(ProtocolType);
            break;

        case MB_ASCII_PYLON :
            tUnifiedBMSData.u16BMSDataStatus = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataVolt = tBmsDataPylon.tBmsPylonAnalogInfo.u16SystemAvgVolt;
            tUnifiedBMSData.s16BMSDataChgCurr = tBmsDataPylon.tBmsPylonAnalogInfo.s16SystemTotalCurr;
            tUnifiedBMSData.s16BMSDataDisChgCurr = tBmsDataPylon.tBmsPylonAnalogInfo.s16SystemTotalCurr;
            tUnifiedBMSData.s16BMSDataTemp = tBmsDataPylon.tBmsPylonAnalogInfo.s16SingleMaxTemp;
            tUnifiedBMSData.u16BMSDataSOC = tBmsDataPylon.tBmsPylonAnalogInfo.u16SystemSOC;
            tUnifiedBMSData.u16BMSDataRemainingCap = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataFullCap = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataMaxChgCurr = tBmsDataPylon.tBmsPylonMutualInfo.s16MaxChgCurr;
            tUnifiedBMSData.u16BMSDataCVVolt = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved0 = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved1 = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved2 = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved3 = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved4 = PROTO_NULL;
            BmsErrorUnified(ProtocolType);
            BmsWarningUnified(ProtocolType);
            break;
            
        case MB_ASCII_IRON :
            tUnifiedBMSData.u16BMSDataStatus = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataVolt = tIronTowerBMSData.u16SysVoltage;
            tUnifiedBMSData.s16BMSDataChgCurr = tIronTowerBMSData.s16SysCurrent;
            tUnifiedBMSData.s16BMSDataDisChgCurr = tIronTowerBMSData.s16SysCurrent;
            tUnifiedBMSData.s16BMSDataTemp = tIronTowerBMSData.s16BatPackTemp;
            tUnifiedBMSData.u16BMSDataSOC = tIronTowerBMSData.u16SysSOC;
            tUnifiedBMSData.u16BMSDataRemainingCap = tIronTowerBMSData.u16RemainingCapacity;
            tUnifiedBMSData.u16BMSDataFullCap = tIronTowerBMSData.u16FullCapacity;
            tUnifiedBMSData.u16BMSDataMaxChgCurr = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataCVVolt = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved0 = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved1 = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved2 = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved3 = PROTO_NULL;
            tUnifiedBMSData.u16BMSDataReserved4 = PROTO_NULL;
            BmsErrorUnified(ProtocolType);
            BmsWarningUnified(ProtocolType);
            break;
            
        default:
            ;
    }
}
#endif

#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

