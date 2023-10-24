/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Fault_Management_Service.c 
 用途 : 故障告警管理服务
***********************************************************************************************************************/
#ifndef _FAULT_MANAGEMENT_C_
#define _FAULT_MANAGEMENT_C_

#include "HeadFile.h"
#include "RTC_Service.h"
#include "Fault_Management_Service.h"
#include "Storage_Management_Service.h"
#include "Battery_Protect_Service.h"
#include "Modbus_BMS_COMData.h"
#include "Canbus_BMS_COMData.h"
#include "Modbus_PCS_COMData.h"

#if FAULT_SERVICE_MOUDLE

static Fault_Info_Real      stFaultReal;                        //实时故障
static Fault_Info_History   stFaultHistory;                     //历史故障
static Record_Info          stRecord;                           //操作记录
static Device_Fault_Control stBitFaultControl;                  //设备故障
static TimeInf_t SysCurrentTime_tab;                               //实时系统时间
static FaultStatus_TypeDef gEnumFaultStatus = FAULT_STATE_NULL; //故障告警管理模块状态

//PV故障转化为故障码并实现实时故障和历史故障处理
static void PVFaultBitTransformFaultCode(Display_PV_Fault_t* stPVFault);
//系统V故障转化为故障码并实现实时故障和历史故障处理
static void SYSFaultBitTransformFaultCode(Display_SYS_Fault_t* stSYSFault);
//Inv故障转化为故障码并实现实时故障和历史故障处理
static void InvFaultBitTransformFaultCode(Display_INV_Fault_t* stInvFault);
//DCDC故障转化为故障码并实现实时故障和历史故障处理
static void DCDCFaultBitTransformFaultCode(Display_DCDC_Fault_t* stDCDCFault);
//发电机故障转化为故障码并实现实时故障和历史故障处理
static void GenFaultBitTransformFaultCode(Display_Gen_Fault_t* stGenFault);
//系统告警故障转化为故障码并实现实时故障和历史故障处理
static void SYSAlarmBitTransformFaultCode(Display_SYS_Alarm_t* stSysAlarm);
//PCS故障转化为故障码并实现实时故障和历史故障处理
static void PCSFaultBitTransformFaultCode(Display_PCS_Fault_t* stPCSFault);
//BMS故障转化为故障码并实现实时故障和历史故障处理
static void BMSFaultBitTransformFaultCode(Display_BMS_Fault_t* stBMSFault);
static void BMSCanFaultBitTransformFaultCode(Display_BMSCan_Fault_t* stBMSCanFault);
//EMS故障转化为故障码并实现实时故障和历史故障处理
static void EMSFaultBitTransformFaultCode(Display_EMS_Fault_t* stEMSFault);
//在实时故障队列查找指定故障
static int8_t FindRealFaultQueue(uint16_t u16FaultCode);
//在实时故障队列插入新故障
static void InsertRealFaultQueue(Display_Fault_Info* pFault);
//在实时故障队列删除新故障
static void DeteleRealFaultQueue(Display_Fault_Info* pFault);
//历史故障队列插入一条记录
static void InsertHistoryFaultQueue(Display_Fault_Info* pFault);
//获取PCS故障数据
static void GetDisplayPCSFaultData(Display_PCS_Fault_t* ptDisplayPCSFault);
//获取BMS故障数据
static void GetDisplayBMSFaultData(Display_BMS_Fault_t* ptDisplayBMSFault);
//获取BMSCan故障数据
static void GetDisplayBMSCanFaultData(Display_BMSCan_Fault_t* ptDisplayBMSCanFault);
//获取设备故障数据
static void GetDisplayDeviceFaultData(Display_Fault_t* ptDisplayFault);

void FaultManagement_Handler(void)
{       
    if (STATUS_FALSE == TimeTask_GetFlag_1s)                         //1s触发一次
    {
        return;
    }

    switch (gEnumFaultStatus)
    {
        case FAULT_INIT://故障告警管理模块初始化
            {
                FaultInit();
                gEnumFaultStatus = FAULT_RUNNING;
            }     
            break;
        case FAULT_RUNNING://故障告警管理模块运行
            {
                FaultRunning();
            } 
            break;
        case FAULT_DESTRCUCTION://故障告警管理模块析构,用掉电检测村塾
            {
                FaultDestruction();
            }
            break;
        default:
            break;
    }
}

/***********************************************************************************************************************
 功能：故障告警管理模块全局变量初始化
***********************************************************************************************************************/
void Fault_Service_InitVar(void)
{
    gEnumFaultStatus = FAULT_INIT;
}

/***********************************************************************************************************************
 功能：故障告警管理模块析构
***********************************************************************************************************************/
void Fault_Service_DestructionVar(void)
{
    FaultDestruction();
    gEnumFaultStatus = FAULT_DESTRCUCTION;  
}

/***********************************************************************************************************************
 功能：故障告警管理模块硬件初始化
***********************************************************************************************************************/
void Fault_Service_HwInit(void)
{

}

/***************************************************************************
 功能:初始化驱动，全局变量等
****************************************************************************/
static void FaultInit(void)
{
    memset(&stFaultReal,0,sizeof(Fault_Info_Real));
    memset(&stFaultHistory,0,sizeof(Fault_Info_History));
    memset(&stBitFaultControl,0,sizeof(Device_Fault_Control));
    memset(&stRecord,0,sizeof(Record_Info));
    Flash_Device_FaultData_Read(&stFaultHistory,sizeof(Fault_Info_History));//重启加载历史故障数据
    Flash_Device_OperateRecord_Read(&stRecord,sizeof(Record_Info));         //重启加载操作记录数据
}

/***************************************************************************
 功能:故障告警管理总运行函数
****************************************************************************/
void FaultRunning(void)
{
    Display_Fault_t  stFault;
    memset(&stFault,0,sizeof(Display_Fault_t));
    
    //获取设备故障数据
    GetDisplayDeviceFaultData(&stFault);
    //查询PCS故障
    PCSFaultBitTransformFaultCode(&stFault.tPCSFault);
    //查询BMS故障
    switch (BmsComWayType)
    {
    	case BMS_LI_ION_CAN:
            BMSCanFaultBitTransformFaultCode(&stFault.tBMSCanFault);
    		break;
    	case BMS_LI_ION_485:
            BMSFaultBitTransformFaultCode(&stFault.tBMSFault);
            break;
        default:
            break;
    }    
    //查询EMS故障
    EMSFaultBitTransformFaultCode(&stFault.tEMSFault);
}

/***************************************************************************
 功能:故障告警管理析构函数，用于掉电触发保护逻辑
****************************************************************************/
void FaultDestruction(void)
{

}
/***************************************************************************
 功能:光伏故障bit位转化code实现函数
****************************************************************************/
static void PVFaultBitTransformFaultCode(Display_PV_Fault_t* stPVFault)
{
    static uint32_t u32Lsat_PVFault[2] = {0,0};
    
    Display_Fault_Info stDisplay;
    memset(&stDisplay,0,sizeof(stDisplay));
    
    if(stPVFault->stPVFault[0].PVFault_t.u32Error != u32Lsat_PVFault[0])         //故障字发生变化
    {
        u32Lsat_PVFault[0] = stPVFault->stPVFault[0].PVFault_t.u32Error;         //更新故障字缓存
        
        //欠压故障逻辑判断
        if((stPVFault->stPVFault[0].PVFault_t.Bits.bPvUV == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bUnderVoltageOccurFlag == BIT_RESET))                //故障标志位已置位，且未处理
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = PV1_FAULT_PvUV;
            stDisplay.u8FaultObj = 3;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);                                                                                                              //插入实时故障链表
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bUnderVoltageOccurFlag = BIT_SET;//置欠压故障标志为1，表示已经存在欠压故障
        }
        else if((stPVFault->stPVFault[0].PVFault_t.Bits.bPvUV == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bUnderVoltageOccurFlag == BIT_SET))            //故障标志位已清除，且已处理
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = PV1_FAULT_PvUV;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);                                                                                                               //从实时故障链表中删除 ，插入实时故障
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bUnderVoltageOccurFlag = BIT_RESET;  //置欠压故障标志为0，表示已经已经清除，移动到历史故障    
        }
       
        //过压故障逻辑判断
        if((stPVFault->stPVFault[0].PVFault_t.Bits.bPvOV == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bOverVoltageOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = PV1_FAULT_PvOV;
            stDisplay.u8FaultObj = 3;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bOverVoltageOccurFlag = BIT_SET;//置过压故障标志为1，表示已经存在过压故障
        }
        else if((stPVFault->stPVFault[0].PVFault_t.Bits.bPvOV == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bOverVoltageOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = PV1_FAULT_PvOV;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bOverVoltageOccurFlag = BIT_RESET;  //置过压故障标志为0，表示已经已经清除，移动到历史故障    
        }
       #if 0
        //PvIso故障逻辑判断
        if((stPVFault->stPVFault[0].PVFault_t.Bits.bPvISOErr == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bPvisoOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = PV1_FAULT_PVIso;
            stDisplay.u8FaultObj = 3;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bPvisoOccurFlag = BIT_SET;//置PvIso故障标志为1，表示已经存在过压故障
        }
        else if((stPVFault->stPVFault[0].PVFault_t.Bits.bPvISOErr == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bPvisoOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = PV1_FAULT_PVIso;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bPvisoOccurFlag = BIT_RESET;  //置PvIso故障标志为0，表示已经已经清除，移动到历史故障    
        }
       #endif
       
        //软件过流故障逻辑判断
        if((stPVFault->stPVFault[0].PVFault_t.Bits.bFWOI == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bSoftWareOverCurrentOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = PV1_FAULT_SWOC;
            stDisplay.u8FaultObj = 3;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bSoftWareOverCurrentOccurFlag = BIT_SET;//置软件过流故障标志为1，表示已经存在过压故障
        }
        else if((stPVFault->stPVFault[0].PVFault_t.Bits.bFWOI == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bSoftWareOverCurrentOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = PV1_FAULT_SWOC;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bSoftWareOverCurrentOccurFlag = BIT_RESET;  //置软件过流故障标志为0，表示已经已经清除，移动到历史故障
        }
       
        //硬件过流故障逻辑判断
        if((stPVFault->stPVFault[0].PVFault_t.Bits.bHWOI == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bHardWareOverCurrentOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = PV1_FAULT_HWOC;
            stDisplay.u8FaultObj = 3;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bHardWareOverCurrentOccurFlag  = 1;//置硬件过流故障标志为1，表示已经存在过压故障
        }
        else if((stPVFault->stPVFault[0].PVFault_t.Bits.bHWOI == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bHardWareOverCurrentOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = PV1_FAULT_HWOC;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bHardWareOverCurrentOccurFlag  = 0;  //置硬件过流故障标志为0，表示已经已经清除，移动到历史故障
        }

        //低功率锁定故障逻辑判断
        if((stPVFault->stPVFault[0].PVFault_t.Bits.bLowPowerLock == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bLowPowerLockOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = PV1_FAULT_LPLK;
            stDisplay.u8FaultObj = 3;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bLowPowerLockOccurFlag  = 1;//置低功率锁定故障标志为1，表示已经存在低功率锁定故障
        }
        else if((stPVFault->stPVFault[0].PVFault_t.Bits.bLowPowerLock == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bLowPowerLockOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = PV1_FAULT_LPLK;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[0].Bits.bLowPowerLockOccurFlag  = 0;  //置低功率锁定故障标志为0，表示已经已经清除，移动到历史故障
        }
    }

    if(stPVFault->stPVFault[1].PVFault_t.u32Error != u32Lsat_PVFault[1] )                        //故障字发生变化
    {
        u32Lsat_PVFault[1] = stPVFault->stPVFault[1].PVFault_t.u32Error;

        //欠压故障逻辑判断
        if((stPVFault->stPVFault[1].PVFault_t.Bits.bPvUV == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bUnderVoltageOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = PV2_FAULT_PvUV;
            stDisplay.u8FaultObj = 3;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bUnderVoltageOccurFlag = BIT_SET;//置欠压故障标志为1，表示已经存在过压故障
        }
        else if((stPVFault->stPVFault[1].PVFault_t.Bits.bPvUV == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bUnderVoltageOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = PV2_FAULT_PvUV;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bUnderVoltageOccurFlag = BIT_RESET; //置欠压故障标志为0，表示已经已经清除，移动到历史故障     
        }

        //过压故障逻辑判断
        if((stPVFault->stPVFault[1].PVFault_t.Bits.bPvOV == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bOverVoltageOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = PV2_FAULT_PvOV;
            stDisplay.u8FaultObj = 3;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bOverVoltageOccurFlag = BIT_SET;//置过压故障标志为1，表示已经存在过压故障
        }
        else if((stPVFault->stPVFault[1].PVFault_t.Bits.bPvOV == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bOverVoltageOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = PV2_FAULT_PvOV;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bOverVoltageOccurFlag = BIT_RESET;  //置过压故障标志为0，表示已经已经清除，移动到历史故障    
        }
        #if 0
        //PvIso故障逻辑判断
        if((stPVFault->stPVFault[1].PVFault_t.Bits.bPvISOErr == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bPvisoOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = PV2_FAULT_PVIso;
            stDisplay.u8FaultObj = 3;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bPvisoOccurFlag = BIT_SET;//置PvIso故障标志为1，表示已经存在过压故障
        }
        else if((stPVFault->stPVFault[1].PVFault_t.Bits.bPvISOErr == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bPvisoOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = PV2_FAULT_PVIso;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bPvisoOccurFlag = BIT_RESET;  //置PvIso故障标志为0，表示已经已经清除，移动到历史故障    
        }
        #endif
        //软件过流故障逻辑判断
        if((stPVFault->stPVFault[1].PVFault_t.Bits.bFWOI == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bSoftWareOverCurrentOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = PV2_FAULT_SWOC;
            stDisplay.u8FaultObj = 3;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bSoftWareOverCurrentOccurFlag = BIT_SET;//置软件过流故障标志为1，表示已经存在过压故障
        }
        else if((stPVFault->stPVFault[1].PVFault_t.Bits.bFWOI == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bSoftWareOverCurrentOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = PV2_FAULT_SWOC;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bSoftWareOverCurrentOccurFlag = BIT_RESET;  //置软件过流故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //硬件过流故障逻辑判断
        if((stPVFault->stPVFault[1].PVFault_t.Bits.bHWOI == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bHardWareOverCurrentOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = PV2_FAULT_HWOC;
            stDisplay.u8FaultObj = 3;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bHardWareOverCurrentOccurFlag = BIT_SET;//置硬件过流故障标志为1，表示已经存在过压故障
        }
        else if((stPVFault->stPVFault[1].PVFault_t.Bits.bHWOI == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bHardWareOverCurrentOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = PV2_FAULT_HWOC;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bHardWareOverCurrentOccurFlag = BIT_RESET;  //置硬件过流故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //低功率锁定故障逻辑判断
        if((stPVFault->stPVFault[1].PVFault_t.Bits.bLowPowerLock == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bLowPowerLockOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = PV2_FAULT_LPLK;
            stDisplay.u8FaultObj = 3;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bLowPowerLockOccurFlag  = 1;  //置低功率锁定故障标志为1，表示已经存在低功率锁定故障
        }
        else if((stPVFault->stPVFault[1].PVFault_t.Bits.bLowPowerLock == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bLowPowerLockOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = PV2_FAULT_LPLK;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stPVFaultControl.stPVFault[1].Bits.bLowPowerLockOccurFlag  = 0;  //置低功率锁定故障标志为0，表示已经已经清除，移动到历史故障
        }
    }
}

/***************************************************************************
 功能:系统故障bit位转化code实现函数
****************************************************************************/
static void SYSFaultBitTransformFaultCode(Display_SYS_Fault_t* stSYSFault)
{
    Display_Fault_Info stDisplay;
    memset(&stDisplay,0,sizeof(stDisplay));
    static uint32_t u32Lsat_SysFault = 0;
    
    if(stSYSFault->SysFault_t.u32Error != u32Lsat_SysFault)         //故障字发生变化
    {
        u32Lsat_SysFault = stSYSFault->SysFault_t.u32Error;

        //母线过压快检故障逻辑判断
        if((stSYSFault->SysFault_t.Bits.bBusFastOV == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bBusFastOVOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_BusFastOV;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bBusFastOVOccurFlag = BIT_SET;//置母线过压快检故障标志为1，表示已经存在过压故障
        }
        else if((stSYSFault->SysFault_t.Bits.bBusFastOV == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bBusFastOVOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_BusFastOV;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bBusFastOVOccurFlag = BIT_RESET;  //置母线过压快检故障标志为0，表示已经已经清除，移动到历史故障    
        }  

        //母线过压慢检故障逻辑判断
        if((stSYSFault->SysFault_t.Bits.bBusSlowOV == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bBusSlowOVOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_BusSlowOV;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bBusSlowOVOccurFlag = BIT_SET;//置母线过压慢检故障标志为1，表示已经存在过压故障
        }
        else if((stSYSFault->SysFault_t.Bits.bBusSlowOV == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bBusSlowOVOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_BusSlowOV;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bBusSlowOVOccurFlag = BIT_RESET;  //置母线过压慢检故障标志为0，表示已经已经清除，移动到历史故障    
        } 

        //母线欠压故障逻辑判断
        if((stSYSFault->SysFault_t.Bits.bBusUV == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bBusUVOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_BusUV;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bBusUVOccurFlag = BIT_SET;//置母线欠压故障标志为1，表示已经存在过压故障
        }
        else if((stSYSFault->SysFault_t.Bits.bBusUV == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bBusUVOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_BusUV;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bBusUVOccurFlag = BIT_RESET;  //置母线欠压故障标志为0，表示已经已经清除，移动到历史故障    
        } 

        //母线软起故障逻辑判断
        if((stSYSFault->SysFault_t.Bits.bBusSoft == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bBusSoftOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_BusSoft;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bBusSoftOccurFlag = BIT_SET;//置母线软起故障标志为1，表示已经存在过压故障
        }
        else if((stSYSFault->SysFault_t.Bits.bBusSoft == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bBusSoftOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_BusSoft;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bBusSoftOccurFlag = BIT_RESET;  //置母线软起故障标志为0，表示已经已经清除，移动到历史故障    
        } 

        //EMS通讯异常故障逻辑判断
        if((stSYSFault->SysFault_t.Bits.bEmsCommErr == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bEmsCommErrOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_EmsCommErr;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bEmsCommErrOccurFlag = BIT_SET;//置/EMS通讯异常故障标志为1，表示已经存在过压故障
        }
        else if((stSYSFault->SysFault_t.Bits.bEmsCommErr == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bEmsCommErrOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_EmsCommErr;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bEmsCommErrOccurFlag = BIT_RESET;  //置/EMS通讯异常故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //输出短路故障逻辑判断
        if((stSYSFault->SysFault_t.Bits.bOutputShort == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bOutputShortOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_OutputShort;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bOutputShortOccurFlag = BIT_SET;//置输出短路故障标志为1，表示已经存在过压故障
        }
        else if((stSYSFault->SysFault_t.Bits.bOutputShort == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bOutputShortOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_OutputShort;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bOutputShortOccurFlag = BIT_RESET;  //置输出短路故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //GFCI漏电故障三级逻辑判断
        if((stSYSFault->SysFault_t.Bits.bGFCIErrLv3 == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bGFCIErrLv3OccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_GFCIErrLv3;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bGFCIErrLv3OccurFlag = BIT_SET;//置GFCI漏电故障1标志为1，表示已经存在过压故障
        }
        else if((stSYSFault->SysFault_t.Bits.bGFCIErrLv3 == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bGFCIErrLv3OccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_GFCIErrLv3;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bGFCIErrLv3OccurFlag = BIT_RESET;  //置GFCI漏电故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //GFCI漏电故障二级逻辑判断
        if((stSYSFault->SysFault_t.Bits.bGFCIErrLv2 == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bGFCIErrLv2OccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_GFCIErrLv2;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bGFCIErrLv2OccurFlag = BIT_SET;//置GFCI漏电故障2标志为1，表示已经存在过压故障
        }
        else if((stSYSFault->SysFault_t.Bits.bGFCIErrLv2 == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bGFCIErrLv2OccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_GFCIErrLv2;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bGFCIErrLv2OccurFlag = BIT_RESET;  //置GFCI漏电故障2标志为0，表示已经已经清除，移动到历史故障    
        }

        //GFCI漏电故障一级逻辑判断
        if((stSYSFault->SysFault_t.Bits.bGFCIErrLv1 == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bGFCIErrLv1OccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_GFCIErrLv1;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bGFCIErrLv1OccurFlag = BIT_SET;//置GFCI漏电故障3标志为1，表示已经存在过压故障
        }
        else if((stSYSFault->SysFault_t.Bits.bGFCIErrLv1 == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bGFCIErrLv1OccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_GFCIErrLv1;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bGFCIErrLv1OccurFlag = BIT_RESET;  //置GFCI漏电故障3标志为0，表示已经已经清除，移动到历史故障    
        }

        //软件自锁故障逻辑判断
        if((stSYSFault->SysFault_t.Bits.bFWSelfLock == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bFWSelfLockOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_SWSelfLock;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bFWSelfLockOccurFlag = BIT_SET;//置软件自锁故障标志为1，表示已经存在过压故障
        }
        else if((stSYSFault->SysFault_t.Bits.bFWSelfLock == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bFWSelfLockOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_SWSelfLock;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bFWSelfLockOccurFlag = BIT_RESET;  //置软件自锁故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //系统过温故障逻辑判断
        if((stSYSFault->SysFault_t.Bits.bSysOT == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bSysOTOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_SysOT;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bSysOTOccurFlag = BIT_SET;//置系统过温故障标志为1，表示已经存在过压故障
        }
        else if((stSYSFault->SysFault_t.Bits.bSysOT == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bSysOTOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_SysOT;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bSysOTOccurFlag = BIT_RESET;  //置系统过温故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //系统过载故障逻辑判断
        if((stSYSFault->SysFault_t.Bits.bSysOverLoad == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bSysOverLoadOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_SysOL;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bSysOverLoadOccurFlag = BIT_SET;//置系统过载故障标志为1，表示已经存在过压故障
        }
        else if((stSYSFault->SysFault_t.Bits.bSysOverLoad == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bSysOverLoadOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_SysOL;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bSysOverLoadOccurFlag = BIT_RESET;  //置系统过载故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //Epo故障逻辑判断
        if((stSYSFault->SysFault_t.Bits.bEpo == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bEpoOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_Epo;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bEpoOccurFlag = BIT_SET;//置Epo故障故障标志为1，表示已经存在过压故障
        }
        else if((stSYSFault->SysFault_t.Bits.bEpo == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bEpoOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_Epo;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bEpoOccurFlag = BIT_RESET;  //置Epo故障故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //从cpu故障逻辑判断
        if((stSYSFault->SysFault_t.Bits.bSlaveCpuErr == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bSlaveCpuErrOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_SlaveCpuErr;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bSlaveCpuErrOccurFlag = BIT_SET;//置从cpu故障标志为1，表示已经存在过压故障
        }
        else if((stSYSFault->SysFault_t.Bits.bSlaveCpuErr == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bSlaveCpuErrOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_SlaveCpuErr;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bSlaveCpuErrOccurFlag = BIT_RESET;  //置从cpu故障标志为0，表示已经已经清除，移动到历史故障    
        }
        //ISO故障逻辑判断
        if((stSYSFault->SysFault_t.Bits.bIsoErr == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bIsoErrOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_IsoErr;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bIsoErrOccurFlag = BIT_SET;//置辅源故障标志为1，表示已经存在过压故障
        }
        else if((stSYSFault->SysFault_t.Bits.bIsoErr == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bIsoErrOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_IsoErr;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bIsoErrOccurFlag = BIT_RESET;  //置辅源故障标志为0，表示已经已经清除，移动到历史故障    
        }
        //母线板断连保护故障逻辑判断
        if((stSYSFault->SysFault_t.Bits.bBusBoardBrkProt == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bBusBoardBrkProtOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_BusBoardBrkProt;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bBusBoardBrkProtOccurFlag = BIT_SET;//置母线板断连保护故障标志为1，表示已经存在过压故障
        }
        else if((stSYSFault->SysFault_t.Bits.bBusBoardBrkProt == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bBusBoardBrkProtOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_BusBoardBrkProt;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bBusBoardBrkProtOccurFlag = BIT_RESET;  //置母线板断连保护故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //接地保护故障逻辑判断
        if((stSYSFault->SysFault_t.Bits.bGroundProt == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bGroundProtOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_GroundProt;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bGroundProtOccurFlag = BIT_SET;//置接地保护故障标志为1，表示已经存在过压故障
        }
        else if((stSYSFault->SysFault_t.Bits.bGroundProt == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bGroundProtOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_GroundProt;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bGroundProtOccurFlag = BIT_RESET;  //置接地保护故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //DCDC过载保护逻辑判断
        if((stSYSFault->SysFault_t.Bits.bDcDcOverLoadProt == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bDcDcOverLoadProtFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_DCDCOverLoadProt;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bDcDcOverLoadProtFlag = BIT_SET;//置DCDC过载保护故障标志为1，表示已经存在DCDC过载保护故障
        }
        else if((stSYSFault->SysFault_t.Bits.bDcDcOverLoadProt == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bDcDcOverLoadProtFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_DCDCOverLoadProt;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bDcDcOverLoadProtFlag = BIT_RESET;  //置DCDC过载保护故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //PV1反接故障逻辑判断
        if((stSYSFault->SysFault_t.Bits.bPVRevConnectErr1 == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bPVRevConnectErr1Flag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_PV1RevConnectProt;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bPVRevConnectErr1Flag = BIT_SET;//置PV1反接故障标志为1，表示已经存在PV1反接故障
        }
        else if((stSYSFault->SysFault_t.Bits.bPVRevConnectErr1 == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bPVRevConnectErr1Flag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_PV1RevConnectProt;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bPVRevConnectErr1Flag = BIT_RESET;  //置PV1反接故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //PV2反接故障逻辑判断
        if((stSYSFault->SysFault_t.Bits.bPVRevConnectErr2 == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bPVRevConnectErr2Flag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_PV2RevConnectProt;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bPVRevConnectErr2Flag = BIT_SET;//置PV2反接故障标志为1，表示已经存在PV1反接故障
        }
        else if((stSYSFault->SysFault_t.Bits.bPVRevConnectErr2 == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bPVRevConnectErr2Flag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_PV2RevConnectProt;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bPVRevConnectErr2Flag = BIT_RESET;  //置PV2反接故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //逆变器过温逻辑判断
        if((stSYSFault->SysFault_t.Bits.bInvOverTempProt == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bInvOverTempFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_InvOverTempProt;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bInvOverTempFlag = BIT_SET;//置逆变器过温故障标志为1，表示已经存在逆变器过温故障
        }
        else if((stSYSFault->SysFault_t.Bits.bInvOverTempProt == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bInvOverTempFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_InvOverTempProt;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bInvOverTempFlag = BIT_RESET;  //置逆变器过温故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //DCDC过温逻辑判断
        if((stSYSFault->SysFault_t.Bits.bDCDCOverTempProt == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bDCDCOverTempFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_DCDCOverTempProt;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bDCDCOverTempFlag = BIT_SET;//置DCDC过温故障标志为1，表示已经存在DCDC过温故障
        }
        else if((stSYSFault->SysFault_t.Bits.bDCDCOverTempProt == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bDCDCOverTempFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_DCDCOverTempProt;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bDCDCOverTempFlag = BIT_RESET;  //置DCDC过温故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //电网继电器故障逻辑判断
        if((stSYSFault->SysFault_t.Bits.bGridRlyError == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bGridRlyErrFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_GridRlyErrProt;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bGridRlyErrFlag = BIT_SET;//置电网继电器故障标志为1，表示已经存在电网继电器故障
        }
        else if((stSYSFault->SysFault_t.Bits.bGridRlyError == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bGridRlyErrFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_GridRlyErrProt;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bGridRlyErrFlag = BIT_RESET;  //置电网继电器故障故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //系统能量弱逻辑判断
        if((stSYSFault->SysFault_t.Bits.bSysEnergyWeak == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bSysWeakEnergyFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_SysWeakEnergyProt;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bSysWeakEnergyFlag = BIT_SET;//置系统能量弱故障标志为1，表示已经存在系统能量弱故障
        }
        else if((stSYSFault->SysFault_t.Bits.bSysEnergyWeak == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bSysWeakEnergyFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_SysWeakEnergyProt;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bSysWeakEnergyFlag = BIT_RESET;  //置系统能量弱故障故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //漏电流故障逻辑判断
        if((stSYSFault->SysFault_t.Bits.bLeakCurrError == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bLeakageCurrFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_FAULT_LeakageCurrProt;
            stDisplay.u8FaultObj = 0;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bLeakageCurrFlag = BIT_SET;//置漏电流故障故障标志为1，表示已经存在漏电流故障故障
        }
        else if((stSYSFault->SysFault_t.Bits.bLeakCurrError == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bLeakageCurrFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_FAULT_LeakageCurrProt;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSFaultControl.Bits.bLeakageCurrFlag = BIT_RESET;  //置漏电流故障故障故障标志为0，表示已经已经清除，移动到历史故障    
        }

    }
}

/***************************************************************************
 功能:逆变器故障bit位转化code实现函数
****************************************************************************/
static void InvFaultBitTransformFaultCode(Display_INV_Fault_t* stInvFault)
{
    Display_Fault_Info stDisplay;
    memset(&stDisplay,0,sizeof(stDisplay));
    static uint64_t u64Lsat_InvFault = 0;

    if(stInvFault->InvFault_t.u64Error != u64Lsat_InvFault)         //故障字发生变化
    {
        u64Lsat_InvFault = stInvFault->InvFault_t.u64Error;

        /*                                              电网故障1                                                         */
        //电网过压三级故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bbGridOVLv3 == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridOVLv3OccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_GridOVLv3;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridOVLv3OccurFlag = BIT_SET;//置电网过压三级障标志为1，表示已经存在过压故障
        }
        else if((stInvFault->InvFault_t.Bits.bbGridOVLv3 == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridOVLv3OccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_GridOVLv3;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridOVLv3OccurFlag = BIT_RESET;  //置电网过压三级障标志为0，表示已经已经清除，移动到历史故障    
        }  

        //电网过压二级故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bbGridOVLv2 == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridOVLv2OccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_GridOVLv2;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridOVLv2OccurFlag = BIT_SET;//置电网过压二级障标志为1，表示已经存在过压故障
        }
        else if((stInvFault->InvFault_t.Bits.bbGridOVLv2 == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridOVLv2OccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_GridOVLv2;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridOVLv2OccurFlag = BIT_RESET;  //置电网过压二级故障标志位0，表示已经已经清除，移动到历史故障    
        }  

        //电网过压一级故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bbGridOVLv1 == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridOVLv1OccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_GridOVLv1;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridOVLv1OccurFlag = BIT_SET;//置电网过压一级故障标志为1，表示已经存在过压故障
        }
        else if((stInvFault->InvFault_t.Bits.bbGridOVLv1 == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridOVLv1OccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_GridOVLv1;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridOVLv1OccurFlag = BIT_RESET;  //置电网过压一级故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //电网欠压三级故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bGridUVLv3 == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridUVLv3OccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_GridUVLv3;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridUVLv3OccurFlag = BIT_SET;//置电网欠压三级故障标志为1，表示已经存在过压故障
        }
        else if((stInvFault->InvFault_t.Bits.bGridUVLv3 == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridUVLv3OccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_GridUVLv3;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridUVLv3OccurFlag = BIT_RESET;  //置电网欠压三级故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //电网欠压二级故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bGridUVLv2 == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridUVLv2OccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_GridUVLv2;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridUVLv2OccurFlag = BIT_SET;//置电网欠压二级故障标志为1，表示已经存在过压故障
        }
        else if((stInvFault->InvFault_t.Bits.bGridUVLv2 == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridUVLv2OccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_GridUVLv2;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridUVLv2OccurFlag = BIT_RESET;  //置电网欠压二级故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //电网欠压一级故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bGridUVLv1 == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridUVLv1OccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_GridUVLv1;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridUVLv1OccurFlag = BIT_SET;//置电网欠压一级故障标志为1，表示已经存在过压故障
        }
        else if((stInvFault->InvFault_t.Bits.bGridUVLv1 == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridUVLv1OccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_GridUVLv1;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridUVLv1OccurFlag = BIT_RESET;  //置电网欠压一级故障标志为0，表示已经已经清除，移动到历史故障    
        }  

        //电网过频快检故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bGridFastOverFreq == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridFastOverFreqOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_GridFastOverFreq;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridFastOverFreqOccurFlag = BIT_SET;//置电网过频快检故障标志为1，表示已经存在过压故障
        }
        else if((stInvFault->InvFault_t.Bits.bGridFastOverFreq == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridFastOverFreqOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_GridFastOverFreq;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridFastOverFreqOccurFlag = BIT_RESET;  //置电网过频快检故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //电网过频慢检故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bGridSlowOverFreq == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridSlowOverFreqOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_GridSlowOverFreq;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridSlowOverFreqOccurFlag = BIT_SET;//置电网过频慢检故障标志为1，表示已经存在过压故障
        }
        else if((stInvFault->InvFault_t.Bits.bGridSlowOverFreq == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridSlowOverFreqOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_GridSlowOverFreq;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridSlowOverFreqOccurFlag = BIT_RESET;  //置电网过频慢检故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //电网欠频快检故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bGridFastUnderFreq == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridFastUnderFreqOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_GridFastUnderFreq;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridFastUnderFreqOccurFlag = BIT_SET;//置电网欠频快检故障标志为1，表示已经存在过压故障
        }
        else if((stInvFault->InvFault_t.Bits.bGridFastUnderFreq == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridFastUnderFreqOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_GridFastUnderFreq;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridFastUnderFreqOccurFlag = BIT_RESET;  //置电网欠频快检故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //电网欠频慢检故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bGridSlowUnderFreq == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridSlowUnderFreqOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_GridSlowUnderFreq;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridSlowUnderFreqOccurFlag = BIT_SET;//置电网欠频慢检故障标志为1，表示已经存在过压故障
        }
        else if((stInvFault->InvFault_t.Bits.bGridSlowUnderFreq == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridSlowUnderFreqOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_GridSlowUnderFreq;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridSlowUnderFreqOccurFlag = BIT_RESET;  //置电网欠频慢检故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //孤岛故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bIslandErr == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bIslandErrOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_IslandErr;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bIslandErrOccurFlag = BIT_SET;  //置孤岛故障标志为1，表示已经存在孤岛故障
        }
        else if((stInvFault->InvFault_t.Bits.bIslandErr == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bIslandErrOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_IslandErr;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bIslandErrOccurFlag = BIT_RESET;  //置孤岛故障标志为0，表示已经已经清除，移动到历史故障
        }

        //电网掉电快检故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bGridFastPowerDown == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridFastPowerDownOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_GridFastPowerDown;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridFastPowerDownOccurFlag = BIT_SET;//置电网掉电快检故障标志为1，表示已经存在过压故障
        }
        else if((stInvFault->InvFault_t.Bits.bGridFastPowerDown == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridFastPowerDownOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_GridFastPowerDown;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGridFastPowerDownOccurFlag = BIT_RESET;  //置电网掉电快检故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //锁相异常故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bPllErr == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bPllErrOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_PllErr;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bPllErrOccurFlag = BIT_SET;//置锁相异常故障标志为1，表示已经存在过压故障
        }
        else if((stInvFault->InvFault_t.Bits.bPllErr == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bPllErrOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_PllErr;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bPllErrOccurFlag = BIT_RESET;  //置锁相异常故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //系统LN反接故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bSysLNReverse == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bSysLNReverseOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_SysLNReverse;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bSysLNReverseOccurFlag = BIT_SET;//置系统LN反接故障标志为1，表示已经存在过压故障
        }
        else if((stInvFault->InvFault_t.Bits.bSysLNReverse == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bSysLNReverseOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_SysLNReverse;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bSysLNReverseOccurFlag = BIT_RESET;  //置系统LN反接故障标志为0，表示已经已经清除，移动到历史故障    
        } 

        //电网10分钟过压故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bGrid10MinOV == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGrid10MinOVOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_Grid10MinOV;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGrid10MinOVOccurFlag = BIT_SET;//置电网10分钟过压故障标志为1，表示已经存在过压故障
        }
        else if((stInvFault->InvFault_t.Bits.bGrid10MinOV == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGrid10MinOVOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_Grid10MinOV;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bGrid10MinOVOccurFlag = BIT_RESET;  //置电网10分钟过压故障标志为0，表示已经已经清除，移动到历史故障    
        } 

        /*                                              设备故障1                                                         */
        //软件过流快检故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bFwFastOC == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bFwFastOC1OccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_FwFastOC1;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bFwFastOC1OccurFlag = BIT_SET;//置软件过流快检故障标志为1，表示已经存在软件过流故障
        }
        else if((stInvFault->InvFault_t.Bits.bFwFastOC == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bFwFastOC1OccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_FwFastOC1;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bFwFastOC1OccurFlag = BIT_RESET;  //置软件过流快检故障标志为0，表示已经已经清除，移动到历史故障    
        } 

        //硬件过流故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bHwOV == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bHwOV1OccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_HwOV1;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bHwOV1OccurFlag = BIT_SET;//置硬件过流故障标志为1，表示已经存在硬件过流故障
        }
        else if((stInvFault->InvFault_t.Bits.bHwOV == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bHwOV1OccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_HwOV1;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bHwOV1OccurFlag = BIT_RESET;  //置硬件过流故障标志为0，表示已经已经清除，移动到历史故障    
        } 

        //软件过流慢检故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bFwSlowOC == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bFwSlowOC1OccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_FwSlowOC1;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bFwSlowOC1OccurFlag = BIT_SET;//置软件过流慢检故障标志为1，表示已经存在软件过流慢检故障
        }
        else if((stInvFault->InvFault_t.Bits.bFwSlowOC == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bFwSlowOC1OccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_FwSlowOC1;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bFwSlowOC1OccurFlag = BIT_RESET;  //置软件过流慢检故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //逆变器继电器故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bInvRlyErr == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bInvRlyErr1OccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_InvRlyErr1;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bInvRlyErr1OccurFlag = BIT_SET;//置逆变器继电器压故障标志为1，表示已经存在逆变器继电器压故障故障
        }
        else if((stInvFault->InvFault_t.Bits.bInvRlyErr == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bInvRlyErr1OccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_InvRlyErr1;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bInvRlyErr1OccurFlag = BIT_RESET;  //置逆变器继电器压故障标志为0，表示已经已经清除，移动到历史故障    
        } 

        //过温故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bOTP == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bOTP1OccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_OTP1;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bOTP1OccurFlag = BIT_SET;//置过温故障标志为1，表示已经存在过温故障
        }
        else if((stInvFault->InvFault_t.Bits.bOTP == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bOTP1OccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_OTP1;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bOTP1OccurFlag = BIT_RESET;  //置过温故障标志为0，表示已经已经清除，移动到历史故障    
        } 

        //过压故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bOVP == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bOVP1OccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_OVP1;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bOVP1OccurFlag = BIT_SET;//置过压故障标志为1，表示已经存在过压故障
        }
        else if((stInvFault->InvFault_t.Bits.bOVP == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bOVP1OccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_OVP1;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bOVP1OccurFlag = BIT_RESET;  //置过压故障标志为0，表示已经已经清除，移动到历史故障    
        }  

        //IGBT故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bIgbtErr == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bIgbtErr1OccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_IgbtErr1;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bIgbtErr1OccurFlag = BIT_SET;//置IGBT故障标志为1，表示已经存在IGBT故障
        }
        else if((stInvFault->InvFault_t.Bits.bIgbtErr == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bIgbtErr1OccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_IgbtErr1;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bIgbtErr1OccurFlag = BIT_RESET;  //置IGBT故障标志为0，表示已经已经清除，移动到历史故障    
        } 

        //电感过温逻辑判断
        if((stInvFault->InvFault_t.Bits.bInductanceOT == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bInductanceOT1OccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_InductanceOT1;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bInductanceOT1OccurFlag = BIT_SET;//置电感过温故障标志为1，表示已经存在电感过温故障
        }
        else if((stInvFault->InvFault_t.Bits.bInductanceOT == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bInductanceOT1OccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_InductanceOT1;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bInductanceOT1OccurFlag = BIT_RESET;  //置电感过温故障标志为0，表示已经已经清除，移动到历史故障    
        } 

        //电压直流分量故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bVoltDcComponentErr == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bVoltDcComponentErr1OccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_VoltDcComponentErr1;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bVoltDcComponentErr1OccurFlag = BIT_SET;//置电压直流分量故障标志为1，表示已经存在电压直流分量故障
        }
        else if((stInvFault->InvFault_t.Bits.bVoltDcComponentErr == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bVoltDcComponentErr1OccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_VoltDcComponentErr1;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bVoltDcComponentErr1OccurFlag = BIT_RESET;  //置电压直流分量故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //电流直流分量故障逻辑判断
        if((stInvFault->InvFault_t.Bits.bCurrDcComponentErr == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bCurrDcComponentErr1OccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_CurrDcComponentErr1;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bCurrDcComponentErr1OccurFlag = BIT_SET;//置电流直流分量故障标志为1，表示已经存在电流直流分量故障
        }
        else if((stInvFault->InvFault_t.Bits.bCurrDcComponentErr == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bCurrDcComponentErr1OccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_CurrDcComponentErr1;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bCurrDcComponentErr1OccurFlag = BIT_RESET;  //置电流直流分量故障标志为0，表示已经已经清除，移动到历史故障    
        }

        /*                                              电网故障2                                                         */
        //CT未接故障
        if((stInvFault->InvFault_t.Bits.bCTDisconnect == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bCTDisconnectOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_CT_DisConnect;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bCTDisconnectOccurFlag = BIT_SET;//置CT未接故障标志为1
        }
        else if((stInvFault->InvFault_t.Bits.bCTDisconnect == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bCTDisconnectOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_CT_DisConnect;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bCTDisconnectOccurFlag = BIT_RESET;  //置CT未接故障标志为0
        }

        //电表未接故障
        if((stInvFault->InvFault_t.Bits.bMeterDisconnect == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bMeterDisconnectOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_Meter_DisConnect;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bMeterDisconnectOccurFlag = BIT_SET;//置电表未接故障标志为1
        }
        else if((stInvFault->InvFault_t.Bits.bMeterDisconnect == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bMeterDisconnectOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_Meter_DisConnect;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.bMeterDisconnectOccurFlag = BIT_RESET;  //置电表未接故障标志为0，表示已经已经清除，移动到历史故障    
        }

        /*                                              并机故障1                                                         */
        if((stInvFault->InvFault_t.Bits.ParallelCanErr == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.ParallelCanErrOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_ParallelCanErr;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.ParallelCanErrOccurFlag = BIT_SET;//置并机CAN通讯故障标志为1，表示已经存在过压故障
        }
        else if((stInvFault->InvFault_t.Bits.ParallelCanErr == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.ParallelCanErrOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_ParallelCanErr;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.ParallelCanErrOccurFlag = BIT_RESET;  //置并机CAN通讯故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //并机均流故障
        if((stInvFault->InvFault_t.Bits.ParaCurrShareErr == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.ParaCurrShareErrOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = INV_FAULT_ParaCurrShareErr;
            stDisplay.u8FaultObj = 1;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.ParaCurrShareErrOccurFlag = BIT_SET;//置并机均流故障标志为1，表示已经存在过压故障
        }
        else if((stInvFault->InvFault_t.Bits.ParaCurrShareErr == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.ParaCurrShareErrOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = INV_FAULT_ParaCurrShareErr;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stINVFaultControl.Bits.ParaCurrShareErrOccurFlag = BIT_RESET;  //置并机均流故障标志为0，表示已经已经清除，移动到历史故障    
        }
    }
}

/***************************************************************************
 功能:DCDC故障bit位转化code实现函数
****************************************************************************/
static void DCDCFaultBitTransformFaultCode(Display_DCDC_Fault_t* stDCDCFault)
{
    Display_Fault_Info stDisplay;
    memset(&stDisplay,0,sizeof(stDisplay));
    static uint16_t u16Lsat_DCDCFault = 0;
    
    if(stDCDCFault->DCDCError1_t.u16Error != u16Lsat_DCDCFault)         //故障字发生变化
    {
        u16Lsat_DCDCFault = stDCDCFault->DCDCError1_t.u16Error;    

        //中间故障过压故障
        if((stDCDCFault->DCDCError1_t.Bits.bMidBusOVP == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bMidBusOVPOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = DCDC_FAULT_MidBusOVP;
            stDisplay.u8FaultObj = 2;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bMidBusOVPOccurFlag = BIT_SET;//置中间故障过压故障标志为1，表示已经存在过压故障
        }
        else if((stDCDCFault->DCDCError1_t.Bits.bMidBusOVP == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bMidBusOVPOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = DCDC_FAULT_MidBusOVP;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bMidBusOVPOccurFlag = BIT_RESET;  //置中间故障过压故障标志为0，表示已经已经清除，移动到历史故障    
        } 

        //LLC硬件过流故障
        if((stDCDCFault->DCDCError1_t.Bits.bLLCHwOC == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bLLCHwOCOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = DCDC_FAULT_LLCHwOC;
            stDisplay.u8FaultObj = 2;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bLLCHwOCOccurFlag = BIT_SET;//置LLC硬件过流故障标志为1，表示已经存在过压故障
        }
        else if((stDCDCFault->DCDCError1_t.Bits.bLLCHwOC == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bLLCHwOCOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = DCDC_FAULT_LLCHwOC;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bLLCHwOCOccurFlag = BIT_RESET;  //置LLC硬件过流故障标志为0，表示已经已经清除，移动到历史故障    
        } 

        //BuckBoost硬件过流故障
        if((stDCDCFault->DCDCError1_t.Bits.bBuckBoostHwOC == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bBuckBoostHwOCOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = DCDC_FAULT_BuckBoostHwOC;
            stDisplay.u8FaultObj = 2;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bBuckBoostHwOCOccurFlag = BIT_SET;//置BuckBoost硬件过流故障标志为1，表示已经存在过压故障
        }
        else if((stDCDCFault->DCDCError1_t.Bits.bBuckBoostHwOC == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bBuckBoostHwOCOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = DCDC_FAULT_BuckBoostHwOC;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bBuckBoostHwOCOccurFlag = BIT_RESET;  //置BuckBoost硬件过流故障标志为0，表示已经已经清除，移动到历史故障    
        } 

        //BuckBoost软件过流故障
        if((stDCDCFault->DCDCError1_t.Bits.bBuckBoostFwOC == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bBuckBoostFwOCOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = DCDC_FAULT_BuckBoostSwOC;
            stDisplay.u8FaultObj = 2;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bBuckBoostFwOCOccurFlag = BIT_SET;//置BuckBoost软件过流故障标志为1，表示已经存在过压故障
        }
        else if((stDCDCFault->DCDCError1_t.Bits.bBuckBoostFwOC == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bBuckBoostFwOCOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = DCDC_FAULT_BuckBoostSwOC;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bBuckBoostFwOCOccurFlag = BIT_RESET;  //置BuckBoost软件过流故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //SOP充电过流保护故障
        if((stDCDCFault->DCDCError1_t.Bits.bSOPChgOCP == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bSOPChgOCPOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = DCDC_FAULT_SOPChgOCP;
            stDisplay.u8FaultObj = 2;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bSOPChgOCPOccurFlag = BIT_SET;//置SOP充电过流保护故障标志为1，表示已经存在过压故障
        }
        else if((stDCDCFault->DCDCError1_t.Bits.bSOPChgOCP == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bSOPChgOCPOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = DCDC_FAULT_SOPChgOCP;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bSOPChgOCPOccurFlag = BIT_RESET;  //置SOP充电过流保护故障标志为0，表示已经已经清除，移动到历史故障    
        }  

        //SOP放电过流保护故障
        if((stDCDCFault->DCDCError1_t.Bits.bSOPDisChgOCP == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bSOPDisChgOCPOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = DCDC_FAULT_SOPDisChgOCP;
            stDisplay.u8FaultObj = 2;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bSOPDisChgOCPOccurFlag = BIT_SET;//置SOP放电过流保护故障标志为1，表示已经存在过压故障
        }
        else if((stDCDCFault->DCDCError1_t.Bits.bSOPDisChgOCP == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bSOPDisChgOCPOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = DCDC_FAULT_SOPDisChgOCP;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bSOPDisChgOCPOccurFlag = BIT_RESET;  //置SOP放电过流保护故障标志为0，表示已经已经清除，移动到历史故障    
        }  

        //DCDC过温保护故障
        if((stDCDCFault->DCDCError1_t.Bits.bDCDCOverTemp == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bDCDCOverTempOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = DCDC_FAULT_DCDCOverTemp;
            stDisplay.u8FaultObj = 2;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bDCDCOverTempOccurFlag = BIT_SET;//置DCDC过温保护故障标志为1，表示已经存在过压故障
        }
        else if((stDCDCFault->DCDCError1_t.Bits.bDCDCOverTemp == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bDCDCOverTempOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = DCDC_FAULT_DCDCOverTemp;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bDCDCOverTempOccurFlag = BIT_RESET;  //置DCDC过温保护故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //电池过压故障
        if((stDCDCFault->DCDCError1_t.Bits.bBatOverVolt == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bDCDCOverVoltOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = DCDC_FAULT_DCDCOverVolt;
            stDisplay.u8FaultObj = 2;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bDCDCOverVoltOccurFlag = BIT_SET;//置电池过压保护故障标志为1，表示已经存在过压故障
        }
        else if((stDCDCFault->DCDCError1_t.Bits.bBatOverVolt == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bDCDCOverVoltOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = DCDC_FAULT_DCDCOverVolt;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bDCDCOverVoltOccurFlag = BIT_RESET;  //置电池过压护故障标志为0，表示已经已经清除，移动到历史故障    
        }

        //电池欠压故障
        if((stDCDCFault->DCDCError1_t.Bits.bBatUnderVolt == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bDCDCUnderVoltOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = DCDC_FAULT_DCDCUnderVolt;
            stDisplay.u8FaultObj = 2;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bDCDCUnderVoltOccurFlag = BIT_SET;//置电池欠压保护故障标志为1
        }
        else if((stDCDCFault->DCDCError1_t.Bits.bBatUnderVolt == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bDCDCUnderVoltOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = DCDC_FAULT_DCDCUnderVolt;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stDCDCFaultControl.Bits.bDCDCUnderVoltOccurFlag = BIT_RESET;  //置电池欠压保护故障标志为0，表示已经已经清除，移动到历史故障    
        }
    }
}

/***************************************************************************
 功能:发电机故障bit位转化code实现函数
****************************************************************************/
static void GenFaultBitTransformFaultCode(Display_Gen_Fault_t* stGenFault)
{
    Display_Fault_Info stDisplay;
    memset(&stDisplay,0,sizeof(stDisplay));
    static uint16_t u16Lsat_GenFault = 0;
    
    if(stGenFault->u16Error != u16Lsat_GenFault)         //故障字发生变化
    {
        u16Lsat_GenFault = stGenFault->u16Error;

        //发电机继电器故障
        if((stGenFault->Bits.GenRlyErr == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenRlyErrFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = GEN_FAULT_RlyErr;
            stDisplay.u8FaultObj = 2;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenRlyErrFlag = BIT_SET;
        }
        else if((stGenFault->Bits.GenRlyErr == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenRlyErrFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = GEN_FAULT_RlyErr;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenRlyErrFlag = BIT_RESET;
        } 

        //发电机高压故障
        if((stGenFault->Bits.GenHighVoltErr == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenHighVoltErrFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = GEN_FAULT_HighVolt;
            stDisplay.u8FaultObj = 2;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenHighVoltErrFlag = BIT_SET;
        }
        else if((stGenFault->Bits.GenHighVoltErr == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenHighVoltErrFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = GEN_FAULT_HighVolt;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenHighVoltErrFlag = BIT_RESET;
        } 

        //发电机低压故障
        if((stGenFault->Bits.GenLowVoltErr == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenLowVoltErrFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = GEN_FAULT_LowVolt;
            stDisplay.u8FaultObj = 2;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenLowVoltErrFlag = BIT_SET;
        }
        else if((stGenFault->Bits.GenLowVoltErr == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenLowVoltErrFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = GEN_FAULT_LowVolt;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenLowVoltErrFlag = BIT_RESET;
        } 

        //发电机高频故障
        if((stGenFault->Bits.GenHighFreqErr == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenHighFreqErrFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = GEN_FAULT_HighFreq;
            stDisplay.u8FaultObj = 2;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenHighFreqErrFlag = BIT_SET;
        }
        else if((stGenFault->Bits.GenHighFreqErr == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenHighFreqErrFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = GEN_FAULT_HighFreq;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenHighFreqErrFlag = BIT_RESET;
        } 

        //发电机低频故障
        if((stGenFault->Bits.GenLowFreqErr == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenLowFreqErrFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = GEN_FAULT_LowFreq;
            stDisplay.u8FaultObj = 2;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenLowFreqErrFlag = BIT_SET;
        }
        else if((stGenFault->Bits.GenLowFreqErr == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenLowFreqErrFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = GEN_FAULT_LowFreq;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenLowFreqErrFlag = BIT_RESET;
        } 

        //发电机过载故障
        if((stGenFault->Bits.GenOverLoadErr == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenOverLoadErrFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = GEN_FAULT_OverLoad;
            stDisplay.u8FaultObj = 2;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenOverLoadErrFlag = BIT_SET;
        }
        else if((stGenFault->Bits.GenOverLoadErr == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenOverLoadErrFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = GEN_FAULT_OverLoad;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stGenFaultControl.Bits.GenOverLoadErrFlag = BIT_RESET;
        } 
    }
    
}

/***************************************************************************
 功能:系统告警bit位转化code实现函数
****************************************************************************/
static void SYSAlarmBitTransformFaultCode(Display_SYS_Alarm_t* stSysAlarm)
{
    Display_Fault_Info stDisplay;
    memset(&stDisplay,0,sizeof(stDisplay));
    static uint16_t u16Lsat_SysAlarm = 0;
    
    if(stSysAlarm->u16Alarm != u16Lsat_SysAlarm)         //故障字发生变化
    {
        u16Lsat_SysAlarm = stSysAlarm->u16Alarm;

        //系统风扇告警
        if((stSysAlarm->Bits.bFanErrAlarm == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSAlarmControl.Bits.bFanErrAlarmFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_ALARM_FANErr;
            stDisplay.u8FaultObj = 2;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSAlarmControl.Bits.bFanErrAlarmFlag = BIT_SET;
        }
        else if((stSysAlarm->Bits.bFanErrAlarm == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSAlarmControl.Bits.bFanErrAlarmFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_ALARM_FANErr;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSAlarmControl.Bits.bFanErrAlarmFlag = BIT_RESET;
        } 

        //系统过载告警
        if((stSysAlarm->Bits.bSysOverLoad == BIT_SET)&&(stBitFaultControl.stPCSFaultControl.stSYSAlarmControl.Bits.bSysOverLoadFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stDisplay.u16FaultCode = SYS_ALARM_OverLoad;
            stDisplay.u8FaultObj = 2;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSAlarmControl.Bits.bSysOverLoadFlag = BIT_SET;
        }
        else if((stSysAlarm->Bits.bSysOverLoad == BIT_RESET)&&(stBitFaultControl.stPCSFaultControl.stSYSAlarmControl.Bits.bSysOverLoadFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = SYS_ALARM_OverLoad;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stPCSFaultControl.stSYSAlarmControl.Bits.bSysOverLoadFlag = BIT_RESET;
        } 

    }
}

/***************************************************************************
 功能:PCS故障bit位转化code实现函数
****************************************************************************/
static void PCSFaultBitTransformFaultCode(Display_PCS_Fault_t* stPCSFault)
{
    //查询光伏故障
    PVFaultBitTransformFaultCode(&stPCSFault->tPvFault);
    //查询系统故障
    SYSFaultBitTransformFaultCode(&stPCSFault->tSysFault);
    //逆变器故障
    InvFaultBitTransformFaultCode(&stPCSFault->tInvFault);
    //查询DCDC逆变器故障
    DCDCFaultBitTransformFaultCode(&stPCSFault->tDCDCFault);
    //查询发电机故障
    GenFaultBitTransformFaultCode(&stPCSFault->tGenFault);
    //查询系统告警
    SYSAlarmBitTransformFaultCode(&stPCSFault->tSysAlarm);
}

/***************************************************************************
 功能:EMS故障bit位转化code实现函数
****************************************************************************/
static void EMSFaultBitTransformFaultCode(Display_EMS_Fault_t* stEMSFault)
{
    Display_Fault_Info stDisplay;
    memset(&stDisplay,0,sizeof(stDisplay));

    //获取屏幕下设使能参数
    Display_EnableDetection_Status stEnableDetection;
    memset(&stEnableDetection,0,sizeof(stEnableDetection));
    Display_Get_EnableDetection(&stEnableDetection);

    //获取屏幕下设电池类型参数
    uint8_t u8DisplayBattType;
    Display_SET_BMS*  pDisplay_Set_BMS = Display_Get_BmsSetPara();
    u8DisplayBattType = pDisplay_Set_BMS ->u8Type;

    //PCS通讯断联告警
    if((stEMSFault->EmsError_t.Bits.bPcsCommState == BIT_SET)&&(stBitFaultControl.stEMSFaultControl.Bits.bAlarmPcsCommErrOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stEMSFault->EmsError_t.Bits.bEMSErr = 1; //EMS 总故障位
        stDisplay.u16FaultCode = EMS_FAULT_PCS;
        stDisplay.u8FaultObj = 5;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stEMSFaultControl.Bits.bAlarmPcsCommErrOccurFlag = BIT_SET;//置PCS通讯断联告警为1，表示已经存在PCS通讯故障
    }
    else if((stEMSFault->EmsError_t.Bits.bPcsCommState == BIT_RESET)&&(stBitFaultControl.stEMSFaultControl.Bits.bAlarmPcsCommErrOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = EMS_FAULT_PCS;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stEMSFaultControl.Bits.bAlarmPcsCommErrOccurFlag = BIT_RESET;//置PCS通讯断联告警为0，表示已经已经清除，移动到历史故障
    }

    //电表通讯断联告警
    if((stEMSFault->EmsError_t.Bits.bMeterCommState == BIT_SET)&&(stBitFaultControl.stEMSFaultControl.Bits.bAlarmMeterCommErrOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stEMSFault->EmsError_t.Bits.bEMSErr = 1; //EMS 总故障位
        stDisplay.u16FaultCode = EMS_FAULT_METER;
        stDisplay.u8FaultObj = 5;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stEMSFaultControl.Bits.bAlarmMeterCommErrOccurFlag = BIT_SET;//置电表通讯断联告警为1，表示已经存在电表通讯故障
    }
    else if((stEMSFault->EmsError_t.Bits.bMeterCommState == BIT_RESET)&&(stBitFaultControl.stEMSFaultControl.Bits.bAlarmMeterCommErrOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = EMS_FAULT_METER;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stEMSFaultControl.Bits.bAlarmMeterCommErrOccurFlag = BIT_RESET;//置电表通讯断联告警为0，表示已经已经清除，移动到历史故障
    }

    //CT通讯断联告警
    if((stEMSFault->EmsError_t.Bits.bCTCommState == BIT_SET)&&(stBitFaultControl.stEMSFaultControl.Bits.bAlarmCTCommErrOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stEMSFault->EmsError_t.Bits.bEMSErr = 1; //EMS 总故障位
        stDisplay.u16FaultCode = EMS_FAULT_CT;
        stDisplay.u8FaultObj = 5;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stEMSFaultControl.Bits.bAlarmCTCommErrOccurFlag = BIT_SET;//置CT通讯断联告警为1，表示已经存在CT通讯故障
    }
    else if((stEMSFault->EmsError_t.Bits.bCTCommState == BIT_RESET)&&(stBitFaultControl.stEMSFaultControl.Bits.bAlarmCTCommErrOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = EMS_FAULT_CT;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stEMSFaultControl.Bits.bAlarmCTCommErrOccurFlag = BIT_RESET;//置CT通讯断联告警为0，表示已经已经清除，移动到历史故障
    }

    //BMS使能且BMS类型为锂电池时，BMS通讯断联告警
    if((stEnableDetection.bIsHasBMS == BIT_SET) && (u8DisplayBattType == 0))
    {
        //BMS通讯断联告警
        if((stEMSFault->EmsError_t.Bits.bBmsCommState == BIT_SET)&&(stBitFaultControl.stEMSFaultControl.Bits.bAlarmBmsCommErrOccurFlag == BIT_RESET)) 
        {
            //插入一条新纪录
            stEMSFault->EmsError_t.Bits.bEMSErr = 1; //EMS总故障位
            stDisplay.u16FaultCode = EMS_FAULT_BMS;
            stDisplay.u8FaultObj = 5;
            stDisplay.u8FaultLevel = 1;
            stDisplay.u8FaultState = NOT_CLEARED;
            InsertRealFaultQueue(&stDisplay);
            stBitFaultControl.stEMSFaultControl.Bits.bAlarmBmsCommErrOccurFlag = BIT_SET;//置BMS通讯断联告警为1，表示已经存在BMS通讯故障
        }
        else if((stEMSFault->EmsError_t.Bits.bBmsCommState == BIT_RESET)&&(stBitFaultControl.stEMSFaultControl.Bits.bAlarmBmsCommErrOccurFlag == BIT_SET))
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = EMS_FAULT_BMS;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stEMSFaultControl.Bits.bAlarmBmsCommErrOccurFlag = BIT_RESET;//置BMS通讯断联告警为0，表示已经已经清除，移动到历史故障
        }
    }
    else
    {
        if(stBitFaultControl.stEMSFaultControl.Bits.bAlarmBmsCommErrOccurFlag == BIT_SET)
        {
            //实时故障已经清除，转移到历史故障
            stDisplay.u16FaultCode = EMS_FAULT_BMS;
            stDisplay.u8FaultState = CLEARED;
            DeteleRealFaultQueue(&stDisplay);
            stBitFaultControl.stEMSFaultControl.Bits.bAlarmBmsCommErrOccurFlag = BIT_RESET;//置BMS通讯断联告警为0，表示已经已经清除，移动到历史故障
        }
    }

    //BMS弱电池故障
    if((stEMSFault->EmsError_t.Bits.bWeakBatteryFault == BIT_SET) && (stBitFaultControl.stEMSFaultControl.Bits.bAlarmWeakBatteryOccurFlag == BIT_RESET))
    {
        //插入一条新纪录
        stEMSFault->EmsError_t.Bits.bEMSErr = 1; //EMS 总故障位
        stDisplay.u16FaultCode = EMS_FAULT_WEAKBATTERY;
        stDisplay.u8FaultObj = 5;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stEMSFaultControl.Bits.bAlarmWeakBatteryOccurFlag = BIT_SET;//置PCS通讯断联告警为1，表示已经存在PCS通讯故障
    }
    else if((stEMSFault->EmsError_t.Bits.bWeakBatteryFault == BIT_RESET) && (stBitFaultControl.stEMSFaultControl.Bits.bAlarmWeakBatteryOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = EMS_FAULT_WEAKBATTERY;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stEMSFaultControl.Bits.bAlarmWeakBatteryOccurFlag = BIT_RESET;//置PCS通讯断联告警为0，表示已经已经清除，移动到历史故障
    }

    if((stEMSFault->EmsError_t.Bits.bPcsCommState == BIT_RESET)      ||
       (stEMSFault->EmsError_t.Bits.bMeterCommState == BIT_RESET)    ||
       (stEMSFault->EmsError_t.Bits.bBmsCommState == BIT_RESET)      ||
       (stEMSFault->EmsError_t.Bits.bCTCommState == BIT_RESET)       ||
       (stEMSFault->EmsError_t.Bits.bWeakBatteryFault == BIT_RESET))
    {
        stEMSFault->EmsError_t.Bits.bEMSErr = 0; //EMS 总故障位
    }
}

/***************************************************************************
 功能:BMS故障bit位转化code实现函数
****************************************************************************/
static void BMSFaultBitTransformFaultCode(Display_BMS_Fault_t* stBMSFault)
{
    Display_Fault_Info stDisplay;
    memset(&stDisplay,0,sizeof(stDisplay));

     //MOSFET过温故障
    if((stBMSFault->SystemError1_t.Bits.bMosfetOT == BIT_SET)&&(stBitFaultControl.stBMSFaultControl.Bits.bFaultMosfetOTOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_FAULT_MosfetOT;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bFaultMosfetOTOccurFlag = BIT_SET;//置MOSFET过温故障标志为1，表示已经存在过压故障
    }
    else if((stBMSFault->SystemError1_t.Bits.bMosfetOT == BIT_RESET)&&(stBitFaultControl.stBMSFaultControl.Bits.bFaultMosfetOTOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_FAULT_MosfetOT;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bFaultMosfetOTOccurFlag = BIT_RESET;  //置MOSFET过温故障标志为0，表示已经已经清除，移动到历史故障    
    }
    
    //单芯温度欠温故障
    if((stBMSFault->SystemError1_t.Bits.bSingleUT == BIT_SET)&&(stBitFaultControl.stBMSFaultControl.Bits.bFaultSingleUTOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_FAULT_SingleUT;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bFaultSingleUTOccurFlag = BIT_SET;//置单芯温度欠温故障标志为1，表示已经存在过压故障
    }
    else if((stBMSFault->SystemError1_t.Bits.bSingleUT == BIT_RESET)&&(stBitFaultControl.stBMSFaultControl.Bits.bFaultSingleUTOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_FAULT_SingleUT;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bFaultSingleUTOccurFlag = BIT_RESET;  //置单芯温度欠温故障标志为0，表示已经已经清除，移动到历史故障    
    }
    
    //单芯温度过温故障
    if((stBMSFault->SystemError1_t.Bits.bSingleOT == BIT_SET)&&(stBitFaultControl.stBMSFaultControl.Bits.bFaultSingleOTOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_FAULT_SingleOT;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bFaultSingleOTOccurFlag = BIT_SET;//置单芯温度过温故障标志为1，表示已经存在过压故障
    }
    else if((stBMSFault->SystemError1_t.Bits.bSingleOT == BIT_RESET)&&(stBitFaultControl.stBMSFaultControl.Bits.bFaultSingleOTOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_FAULT_SingleOT;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bFaultSingleOTOccurFlag = BIT_RESET;  //置单芯温度过温故障标志为0，表示已经已经清除，移动到历史故障    
    }
    
    //单芯电压欠压故障
    if((stBMSFault->SystemError1_t.Bits.bSingleUV == BIT_SET)&&(stBitFaultControl.stBMSFaultControl.Bits.bFaultSingleUVOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_FAULT_SingleUV;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bFaultSingleUVOccurFlag = BIT_SET;//置单芯电压欠压故障标志为1，表示已经存在过压故障
    }
    else if((stBMSFault->SystemError1_t.Bits.bSingleUV == BIT_RESET)&&(stBitFaultControl.stBMSFaultControl.Bits.bFaultSingleUVOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_FAULT_SingleUV;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bFaultSingleUVOccurFlag = BIT_RESET;  //置单芯电压欠压故障标志为0，表示已经已经清除，移动到历史故障    
    }
    
    //单芯电压欠压故障
    if((stBMSFault->SystemError1_t.Bits.bSingleOV == BIT_SET)&&(stBitFaultControl.stBMSFaultControl.Bits.bFaultSingleOVOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_FAULT_SingleOV;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bFaultSingleOVOccurFlag = BIT_SET;//置单芯电压欠压故障标志为1，表示已经存在过压故障
    }
    else if((stBMSFault->SystemError1_t.Bits.bSingleOV == BIT_RESET)&&(stBitFaultControl.stBMSFaultControl.Bits.bFaultSingleOVOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_FAULT_SingleOV;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bFaultSingleOVOccurFlag = BIT_RESET;  //置单芯电压欠压故障标志为0，表示已经已经清除，移动到历史故障    
    }
    
    //模块总压欠压故障
    if((stBMSFault->SystemError1_t.Bits.bTotalModeUV == BIT_SET)&&(stBitFaultControl.stBMSFaultControl.Bits.bFaultTotalModeUVOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_FAULT_TotalModeUV;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bFaultTotalModeUVOccurFlag = BIT_SET;//置模块总压欠压故障标志为1，表示已经存在过压故障
    }
    else if((stBMSFault->SystemError1_t.Bits.bTotalModeUV == BIT_RESET)&&(stBitFaultControl.stBMSFaultControl.Bits.bFaultTotalModeUVOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_FAULT_TotalModeUV;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bFaultTotalModeUVOccurFlag = BIT_RESET;  //置模块总压欠压故障标志为0，表示已经已经清除，移动到历史故障    
    }
    
    //模块总压过压故障
    if((stBMSFault->SystemError1_t.Bits.bTotalModeOV == BIT_SET)&&(stBitFaultControl.stBMSFaultControl.Bits.bFaultTotalModeOVOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_FAULT_TotalModeOV;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bFaultTotalModeOVOccurFlag = BIT_SET;//置模块总压过压故障标志为1，表示已经存在过压故障
    }
    else if((stBMSFault->SystemError1_t.Bits.bTotalModeOV == BIT_RESET)&&(stBitFaultControl.stBMSFaultControl.Bits.bFaultTotalModeOVOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_FAULT_TotalModeOV;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bFaultTotalModeOVOccurFlag = BIT_RESET;  //置模块总压过压故障标志为0，表示已经已经清除，移动到历史故障    
    }
    
    //系统故障保护故障
    if((stBMSFault->SystemError2_t.Bits.bSysFault == BIT_SET)&&(stBitFaultControl.stBMSFaultControl.Bits.bFaultSysFaultOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_FAULT_SysFault;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bFaultSysFaultOccurFlag = BIT_SET;//置系统故障保护故障标志为1，表示已经存在过压故障
    }
    else if((stBMSFault->SystemError2_t.Bits.bSysFault == BIT_RESET)&&(stBitFaultControl.stBMSFaultControl.Bits.bFaultSysFaultOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_FAULT_SysFault;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bFaultSysFaultOccurFlag = BIT_RESET;  //置系统故障保护故障标志为0，表示已经已经清除，移动到历史故障    
    }
    
    //放电过流故障
    if((stBMSFault->SystemError2_t.Bits.bOCD == BIT_SET)&&(stBitFaultControl.stBMSFaultControl.Bits.bFaultOCDOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_FAULT_OCD;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bFaultOCDOccurFlag = BIT_SET;//置放电过流故障标志为1，表示已经存在过压故障
    }
    else if((stBMSFault->SystemError2_t.Bits.bOCD == BIT_RESET)&&(stBitFaultControl.stBMSFaultControl.Bits.bFaultOCDOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_FAULT_OCD;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bFaultOCDOccurFlag = BIT_RESET;  //置放电过流故障标志为0，表示已经已经清除，移动到历史故障    
    }
    
    //充电过流故障
    if((stBMSFault->SystemError2_t.Bits.bOCC == BIT_SET)&&(stBitFaultControl.stBMSFaultControl.Bits.bFaultOCCOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_FAULT_OCC;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bFaultOCCOccurFlag = BIT_SET;//置充电过流故障标志为1，表示已经存在过压故障
    }
    else if((stBMSFault->SystemError2_t.Bits.bOCC == BIT_RESET)&&(stBitFaultControl.stBMSFaultControl.Bits.bFaultOCCOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_FAULT_OCC;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bFaultOCCOccurFlag = BIT_RESET;  //置充电过流故障标志为0，表示已经已经清除，移动到历史故障    
    }

    //单芯电压一致性告警
    if((stBMSFault->SystemAlarm1_t.Bits.bSingleVoltDiff == BIT_SET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleVoltDiffOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_ALERM_SingleVoltDiff;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleVoltDiffOccurFlag = BIT_SET;//置单芯电压一致性告警标志为1，表示已经存在过压故障
    }
    else if((stBMSFault->SystemAlarm1_t.Bits.bSingleVoltDiff == BIT_RESET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleVoltDiffOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_ALERM_SingleVoltDiff;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleVoltDiffOccurFlag = BIT_RESET;  //置单芯电压一致性告警标志为0，表示已经已经清除，移动到历史故障    
    } 
    
    //MOSFET 高温告警
    if((stBMSFault->SystemAlarm1_t.Bits.bMosfetOT == BIT_SET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermMosfetOTOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_ALERM_MosfetOT;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermMosfetOTOccurFlag = BIT_SET;//置MOSFET 高温告警标志为1，表示已经存在过压故障
    }
    else if((stBMSFault->SystemAlarm1_t.Bits.bMosfetOT == BIT_RESET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermMosfetOTOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_ALERM_MosfetOT;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermMosfetOTOccurFlag = BIT_RESET;  //置MOSFET 高温告警标志为0，表示已经已经清除，移动到历史故障    
    } 
    
    //单芯温度低温告警
    if((stBMSFault->SystemAlarm1_t.Bits.bSingleUT == BIT_SET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleUTOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_ALERM_SingleUT;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleUTOccurFlag = BIT_SET;//置单芯温度低温告警标志为1，表示已经存在过压故障
    }
    else if((stBMSFault->SystemAlarm1_t.Bits.bSingleUT == BIT_RESET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleUTOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_ALERM_SingleUT;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleUTOccurFlag = BIT_RESET;  //置单芯温度低温告警标志为0，表示已经已经清除，移动到历史故障    
    } 
    
    //单芯温度高温告警
    if((stBMSFault->SystemAlarm1_t.Bits.bSingleOT == BIT_SET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleOTOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_ALERM_SingleOT;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleOTOccurFlag = BIT_SET;//置单芯温度高温告警标志为1，表示已经存在过压故障
    }
    else if((stBMSFault->SystemAlarm1_t.Bits.bSingleOT == BIT_RESET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleOTOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_ALERM_SingleOT;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleOTOccurFlag = BIT_RESET;  //置单芯温度高温告警标志为0，表示已经已经清除，移动到历史故障    
    } 
    
    //单芯电压低压告警
    if((stBMSFault->SystemAlarm1_t.Bits.bSingleVoltUV == BIT_SET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleVoltUVOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_ALERM_SingleVoltUV;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleVoltUVOccurFlag = BIT_SET;//置单芯电压低压告警标志为1，表示已经存在过压故障
    }
    else if((stBMSFault->SystemAlarm1_t.Bits.bSingleVoltUV == BIT_RESET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleVoltUVOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_ALERM_SingleVoltUV;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleVoltUVOccurFlag = BIT_RESET;  //置单芯电压低压告警标志为0，表示已经已经清除，移动到历史故障    
    } 
    
    //单芯电压高压告警
    if((stBMSFault->SystemAlarm1_t.Bits.bSingleVoltOV == BIT_SET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleVoltOVOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_ALERM_SingleVoltOV;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleVoltOVOccurFlag = BIT_SET;//置单芯电压高压告警标志为1，表示已经存在过压故障
    }
    else if((stBMSFault->SystemAlarm1_t.Bits.bSingleVoltOV == BIT_RESET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleVoltOVOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_ALERM_SingleVoltOV;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleVoltOVOccurFlag = BIT_RESET;  //置单芯电压高压告警故障标志为0，表示已经已经清除，移动到历史故障    
    }
    
    //模块总压低压告警
    if((stBMSFault->SystemAlarm1_t.Bits.bTotalVoltUV == BIT_SET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermTotalVoltUVOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_ALERM_TotalVoltUV;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermTotalVoltUVOccurFlag = BIT_SET;//置模块总压低压告警标志为1，表示已经存在过压故障
    }
    else if((stBMSFault->SystemAlarm1_t.Bits.bTotalVoltUV == BIT_RESET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermTotalVoltUVOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_ALERM_TotalVoltUV;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermTotalVoltUVOccurFlag = BIT_RESET;  //置模块总压低压告警标志为0，表示已经已经清除，移动到历史故障    
    }
    
    //模块总压高压告警
    if((stBMSFault->SystemAlarm1_t.Bits.bTotalVoltOV == BIT_SET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermTotalVoltOVOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_ALERM_TotalVoltOV;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermTotalVoltOVOccurFlag = BIT_SET;//置模块总压高压告警标志为1，表示已经存在过压故障
    }
    else if((stBMSFault->SystemAlarm1_t.Bits.bTotalVoltOV == BIT_RESET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermTotalVoltOVOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_ALERM_TotalVoltOV;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermTotalVoltOVOccurFlag = BIT_RESET;  //置模块总压高压告警标志为0，表示已经已经清除，移动到历史故障    
    }
    
    
    //内部通信错误告警
    if((stBMSFault->SystemAlarm2_t.Bits.bInternalComErr == BIT_SET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermInternalComErrOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_ALERM_InternalComErr;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermInternalComErrOccurFlag = BIT_SET;//置模块总压高压告警标志为1，表示已经存在过压故障
    }
    else if((stBMSFault->SystemAlarm2_t.Bits.bInternalComErr == BIT_RESET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermInternalComErrOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_ALERM_InternalComErr;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermInternalComErrOccurFlag = BIT_RESET;  //置模块总压高压告警标志为0，表示已经已经清除，移动到历史故障    
    }
    
    //放电过流告警
    if((stBMSFault->SystemAlarm2_t.Bits.bOCD == BIT_SET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermOCDOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_ALERM_OCD;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermOCDOccurFlag = BIT_SET;//置放电过流告警标志为1，表示已经存在过压故障
    }
    else if((stBMSFault->SystemAlarm2_t.Bits.bOCD == BIT_RESET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermOCDOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_ALERM_OCD;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermOCDOccurFlag = BIT_RESET;  //置放电过流告警标志为0，表示已经已经清除，移动到历史故障    
    }
    
    //充电过流告警
    if((stBMSFault->SystemAlarm2_t.Bits.bOCC == BIT_SET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermOCCOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_ALERM_OCC;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermOCCOccurFlag = BIT_SET;//置充电过流告警标志为1，表示已经存在过压故障
    }
    else if((stBMSFault->SystemAlarm2_t.Bits.bOCC == BIT_RESET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermOCCOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_ALERM_OCC;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermOCCOccurFlag = BIT_RESET;  //置充电过流告警标志为0，表示已经已经清除，移动到历史故障    
    }
    
    //单芯温度一致性告警
    if((stBMSFault->SystemAlarm2_t.Bits.bSingleTempDiff == BIT_SET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleTempDiffOccurFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_ALERM_SingleTempDiff;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleTempDiffOccurFlag = BIT_SET;//置单芯温度一致性告警标志为1，表示已经存在过压故障
    }
    else if((stBMSFault->SystemAlarm2_t.Bits.bSingleTempDiff == BIT_RESET)&&(stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleTempDiffOccurFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_ALERM_SingleTempDiff;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSFaultControl.Bits.bAlermSingleTempDiffOccurFlag = BIT_RESET;  //置单芯温度一致性告警标志为0，表示已经已经清除，移动到历史故障    
    }
}

/***************************************************************************
 功能:BMS故障bit位转化code实现函数
****************************************************************************/
static void BMSCanFaultBitTransformFaultCode(Display_BMSCan_Fault_t* stBMSCanFault)
{
    Display_Fault_Info stDisplay;
    memset(&stDisplay,0,sizeof(stDisplay));

    //电压过压故障
    if((stBMSCanFault->Protect0_t.Bits.bOV == BIT_SET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bOVProtectFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_FAULT_TotalModeOV;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bOVProtectFlag = BIT_SET;//置电压过压故障标志为1，表示已经存在过压故障
    }
    else if((stBMSCanFault->Protect0_t.Bits.bOV == BIT_RESET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bOVProtectFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_FAULT_TotalModeOV;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bOVProtectFlag = BIT_RESET;  //置电压过压故障标志为0，表示已经已经清除，移动到历史故障    
    }
    
    //电压欠压故障
    if((stBMSCanFault->Protect0_t.Bits.bUV == BIT_SET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bUVProtectFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_FAULT_TotalModeUV;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bUVProtectFlag = BIT_SET;//置电压欠压故障标志为1，表示已经存在电压欠压故障
    }
    else if((stBMSCanFault->Protect0_t.Bits.bUV == BIT_RESET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bUVProtectFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_FAULT_TotalModeUV;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bUVProtectFlag = BIT_RESET;  //置电压欠压故障标志为0，表示已经已经清除，移动到历史故障    
    }
    
    
    //过温故障
    if((stBMSCanFault->Protect0_t.Bits.bOT == BIT_SET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bOTProtectFlag  == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_FAULT_SingleOT;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bOTProtectFlag  = BIT_SET;//置过温故障标志为1，表示已经存在过温故障
    }
    else if((stBMSCanFault->Protect0_t.Bits.bOT == BIT_RESET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bOTProtectFlag  == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_FAULT_SingleOT;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bOTProtectFlag  = BIT_RESET;  //置过温故障标志为0，表示已经已经清除，移动到历史故障    
    }
    
    //欠温故障
    if((stBMSCanFault->Protect0_t.Bits.bUT == BIT_SET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bUTProtectFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_FAULT_SingleUT;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bUTProtectFlag = BIT_SET;//置欠温故障标志为1，表示已经存在欠温故障
    }
    else if((stBMSCanFault->Protect0_t.Bits.bUT == BIT_RESET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bUTProtectFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_FAULT_SingleUT;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bUTProtectFlag = BIT_RESET;  //置单芯电压欠压故障标志为0，表示已经已经清除，移动到历史故障    
    }
    
    //放电过流故障
    if((stBMSCanFault->Protect0_t.Bits.bOCD == BIT_SET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bOCDProtectFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_FAULT_OCD;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bOCDProtectFlag = BIT_SET;//置放电过流故障标志为1，表示已经存在放电过流故障
    }
    else if((stBMSCanFault->Protect0_t.Bits.bOCD == BIT_RESET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bOCDProtectFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_FAULT_OCD;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bOCDProtectFlag = BIT_RESET;  //置放电过流故障标志为0，表示已经已经清除，移动到历史故障    
    }
    
    //充电过流故障
    if((stBMSCanFault->Protect1_t.Bits.bOCC == BIT_SET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bOCCProtectFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_FAULT_OCC;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bOCCProtectFlag = BIT_SET;//置充电过流故障标志为1，表示已经存在充电过流故障
    }
    else if((stBMSCanFault->Protect1_t.Bits.bOCC == BIT_RESET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bOCCProtectFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_FAULT_OCC;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bOCCProtectFlag = BIT_RESET;  //置充电过流故障标志为0，表示已经已经清除，移动到历史故障    
    }
    
    //系统故障
    if((stBMSCanFault->Protect1_t.Bits.bFault == BIT_SET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bFaultFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_FAULT_SysFault;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bFaultFlag = BIT_SET;//置系统故障标志为1，表示已经存在系统故障
    }
    else if((stBMSCanFault->Protect1_t.Bits.bFault == BIT_RESET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bFaultFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_FAULT_SysFault;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bFaultFlag = BIT_RESET;  //置模块系统故障标志为0，表示已经已经清除，移动到历史故障    
    }
         
    //电压高压告警
    if((stBMSCanFault->Alarm0_t.Bits.bHV == BIT_SET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bHVAlarmFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_ALERM_TotalVoltOV;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bHVAlarmFlag = BIT_SET;//置电压高压告警标志为1，表示已经存在电压高压告警
    }
    else if((stBMSCanFault->Alarm0_t.Bits.bHV == BIT_RESET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bHVAlarmFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_ALERM_TotalVoltOV;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bHVAlarmFlag = BIT_RESET;  //置电压高压告警标志为0，表示已经已经清除，移动到历史故障    
    } 
    
    //电压低压告警
    if((stBMSCanFault->Alarm0_t.Bits.bLV == BIT_SET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bLVAlarmFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_ALERM_TotalVoltUV ;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bLVAlarmFlag = BIT_SET;//置电压低压告警标志为1，表示已经存在电压低压告警故障
    }
    else if((stBMSCanFault->Alarm0_t.Bits.bLV == BIT_RESET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bLVAlarmFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_ALERM_TotalVoltUV ;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bLVAlarmFlag = BIT_RESET;  //置电压低压告警告警标志为0，表示已经已经清除，移动到历史故障    
    } 
    
    //高温告警
    if((stBMSCanFault->Alarm0_t.Bits.bHT == BIT_SET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bHTAlarmFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_ALERM_SingleOT;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bHTAlarmFlag = BIT_SET;//置高温告警标志为1，表示已经存在过压故障
    }
    else if((stBMSCanFault->Alarm0_t.Bits.bHT == BIT_RESET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bHTAlarmFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_ALERM_SingleOT;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bHTAlarmFlag = BIT_RESET;  //置高温告警标志为0，表示已经已经清除，移动到历史故障    
    } 
    
    //低温告警
    if((stBMSCanFault->Alarm0_t.Bits.bLT == BIT_SET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bLTAlarmFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_ALERM_SingleUT;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bLTAlarmFlag = BIT_SET;//置低温告警标志为1，表示已经存在过压故障
    }
    else if((stBMSCanFault->Alarm0_t.Bits.bLT == BIT_RESET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bLTAlarmFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_ALERM_SingleUT;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bLTAlarmFlag = BIT_RESET;  //置低温告警标志为0，表示已经已经清除，移动到历史故障    
    } 
    
    //放电大电流告警
    if((stBMSCanFault->Alarm0_t.Bits.bOCD == BIT_SET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bOCDAlarmFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_ALERM_OCD;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bOCDAlarmFlag = BIT_SET;//置放电大电流告警标志为1，表示已经存在放电大电流故障
    }
    else if((stBMSCanFault->Alarm0_t.Bits.bOCD == BIT_RESET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bOCDAlarmFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_ALERM_OCD;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bOCDAlarmFlag = BIT_RESET;  //置放电大电流标志为0，表示已经已经清除，移动到历史故障    
    } 
    
    //充电大电流告警
    if((stBMSCanFault->Alarm1_t.Bits.bOCC == BIT_SET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bOCCAlarmFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_ALERM_OCC;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bOCCAlarmFlag = BIT_SET;//置充电大电流告警标志为1，表示已经存在充电大电流告警故障
    }
    else if((stBMSCanFault->Alarm1_t.Bits.bOCC == BIT_RESET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bOCCAlarmFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_ALERM_OCC;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bOCCAlarmFlag = BIT_RESET;  //置充电大电流告警故障标志为0，表示已经已经清除，移动到历史故障    
    }
    
    //从机掉线告警
    if((stBMSCanFault->Alarm1_t.Bits.bOffline == BIT_SET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bOfflineFlag == BIT_RESET)) 
    {
        //插入一条新纪录
        stDisplay.u16FaultCode = BMS_ALERM_InternalComErr;
        stDisplay.u8FaultObj = 4;
        stDisplay.u8FaultLevel = 1;
        stDisplay.u8FaultState = NOT_CLEARED;
        InsertRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bOfflineFlag = BIT_SET;//置从机掉线告警标志为1，表示已经存在过压故障
    }
    else if((stBMSCanFault->Alarm1_t.Bits.bOffline == BIT_RESET)&&(stBitFaultControl.stBMSCanFaultControl.Bits.bOfflineFlag == BIT_SET))
    {
        //实时故障已经清除，转移到历史故障
        stDisplay.u16FaultCode = BMS_ALERM_InternalComErr;
        stDisplay.u8FaultState = CLEARED;
        DeteleRealFaultQueue(&stDisplay);
        stBitFaultControl.stBMSCanFaultControl.Bits.bOfflineFlag = BIT_RESET;  //置从机掉线告警标志为0，表示已经已经清除，移动到历史故障    
    }   
}
/***************************************************************************
 功能:实时故障队列查找一条记录
****************************************************************************/
static int8_t FindRealFaultQueue(uint16_t u16FaultCode)
{
    int8_t s8Index = -1;
    for(int i=0;i<stFaultReal.u8RealFaultIndex;i++)
    {
        if(u16FaultCode == stFaultReal.stRealFault[i].u16FaultCode)
        {
            s8Index = i;
            break;
        }
    }
    return s8Index;
}

/***************************************************************************
 功能:实时故障队列插入一条数据记录
****************************************************************************/
static void InsertRealFaultQueue(Display_Fault_Info* pFault)
{
    int8_t s8InsertIndex = FindRealFaultQueue(pFault->u16FaultCode);                                                     //当前链表中是否已有此条目
    if(s8InsertIndex != -1)
    {
        return; 
    } 
    
    /*统一往后移动一个故障结构体大小字节*/
    Display_Fault_Info stRealFaultBuffer[DISPLAY_DATA_FAULT_REAL_MAX_COUNT];
    memset(&stRealFaultBuffer,0,sizeof(Display_Fault_Info)*DISPLAY_DATA_FAULT_REAL_MAX_COUNT);
    
    memcpy(&stRealFaultBuffer,&stFaultReal.stRealFault,sizeof(Display_Fault_Info)*stFaultReal.u8RealFaultIndex);  
    
    stFaultReal.stRealFault[0].u16FaultCode        = pFault->u16FaultCode;                                               //写最新一条数据
    stFaultReal.stRealFault[0].u8FaultLevel        = pFault->u8FaultLevel;
    stFaultReal.stRealFault[0].u8FaultObj          = pFault->u8FaultObj;
    stFaultReal.stRealFault[0].u8FaultState        = pFault->u8FaultState;

    Get_SysTime(&SysCurrentTime_tab);//获取系统时间
    stFaultReal.stRealFault[0].stOccurTime.u16Year = SysCurrentTime_tab.u16Year;
    stFaultReal.stRealFault[0].stOccurTime.u8Month = SysCurrentTime_tab.u8Month;
    stFaultReal.stRealFault[0].stOccurTime.u8Day   = SysCurrentTime_tab.u8Day;
    stFaultReal.stRealFault[0].stOccurTime.u8Hour  = SysCurrentTime_tab.u8Hour;
    stFaultReal.stRealFault[0].stOccurTime.u8Month = SysCurrentTime_tab.u8Month;
    stFaultReal.stRealFault[0].stOccurTime.u8Sec   = SysCurrentTime_tab.u8Sec;
    stFaultReal.stRealFault[0].stOccurTime.u16mSec = 0;

    if(stFaultReal.u8RealFaultIndex == DISPLAY_DATA_FAULT_REAL_MAX_COUNT )                                               //达到链表最大条目
    {
         stFaultReal.u8RealFaultIndex = DISPLAY_DATA_FAULT_REAL_MAX_COUNT - 1;
    }
  
    memcpy(&stFaultReal.stRealFault[1],&stRealFaultBuffer,sizeof(Display_Fault_Info)*stFaultReal.u8RealFaultIndex);      //将已有条目从缓存中拷贝到链表中
    
    stFaultReal.u8RealFaultIndex++;
}

/***************************************************************************
 功能:实时故障队列删除一条记录
****************************************************************************/
static void DeteleRealFaultQueue(Display_Fault_Info* pFault)
{   
    Display_Fault_Info stDisplay;
    Display_Fault_Info stRealFaultBuffer[DISPLAY_DATA_FAULT_REAL_MAX_COUNT];
    memset(&stDisplay,0,sizeof(Display_Fault_Info));   
    memset(&stRealFaultBuffer,0,sizeof(Display_Fault_Info)*DISPLAY_DATA_FAULT_REAL_MAX_COUNT);    
       
    int8_t u8DeleteIndex = FindRealFaultQueue(pFault->u16FaultCode);                                                     //目标故障是否还在实时故障记录中
    if(u8DeleteIndex == -1)
    {
        return;
    }

    memcpy(&stDisplay, &stFaultReal.stRealFault[u8DeleteIndex], sizeof(Display_Fault_Info));                             //给历史故障记录写数据
    stDisplay.u8FaultState = pFault->u8FaultState;
    Get_SysTime(&SysCurrentTime_tab);//获取系统时间
    stDisplay.stClearTime.u16Year = SysCurrentTime_tab.u16Year;
    stDisplay.stClearTime.u8Month = SysCurrentTime_tab.u8Month;
    stDisplay.stClearTime.u8Day   = SysCurrentTime_tab.u8Day;
    stDisplay.stClearTime.u8Hour  = SysCurrentTime_tab.u8Hour;
    stDisplay.stClearTime.u8Month = SysCurrentTime_tab.u8Month;
    stDisplay.stClearTime.u8Sec   = SysCurrentTime_tab.u8Sec;
    stDisplay.stClearTime.u16mSec = 0;
    InsertHistoryFaultQueue(&stDisplay);                                                                                 //拷贝到到历史故障列表
    
    memcpy(&stRealFaultBuffer,&stFaultReal.stRealFault[u8DeleteIndex + 1],sizeof(Display_Fault_Info)*(stFaultReal.u8RealFaultIndex - u8DeleteIndex));
    memcpy(&stFaultReal.stRealFault[u8DeleteIndex],&stRealFaultBuffer,sizeof(Display_Fault_Info)*(stFaultReal.u8RealFaultIndex - u8DeleteIndex));
    
    stFaultReal.u8RealFaultIndex--;                                                                                      //总条目数
    if(stFaultReal.u8RealFaultIndex > DISPLAY_DATA_FAULT_REAL_MAX_COUNT)                                                 //防止内存越界
    {
         stFaultReal.u8RealFaultIndex = 0;
    }   
}



/***************************************************************************
 功能:历史故障队列插入一条记录
****************************************************************************/
static void InsertHistoryFaultQueue(Display_Fault_Info* pFault)
{
    Display_Fault_Info stHistoryFaultBuffer[DISPLAY_DATA_FAULT_HISTORY_MAX_COUNT];
    memset(&stHistoryFaultBuffer,0,sizeof(Display_Fault_Info)*DISPLAY_DATA_FAULT_HISTORY_MAX_COUNT);
    memcpy(&stHistoryFaultBuffer,&stFaultHistory.stHistoryFault,sizeof(Display_Fault_Info)*stFaultHistory.u8HistoryFaultIndex);
    
    stFaultHistory.stHistoryFault[0].u16FaultCode        = pFault->u16FaultCode;                                         //给最新一条历史故障写数据
    stFaultHistory.stHistoryFault[0].u8FaultLevel        = pFault->u8FaultLevel;
    stFaultHistory.stHistoryFault[0].u8FaultObj          = pFault->u8FaultObj;
    stFaultHistory.stHistoryFault[0].u8FaultState        = pFault->u8FaultState; 
    stFaultHistory.stHistoryFault[0].stOccurTime.u16Year = pFault->stOccurTime.u16Year; 
    stFaultHistory.stHistoryFault[0].stOccurTime.u8Month = pFault->stOccurTime.u8Month; 
    stFaultHistory.stHistoryFault[0].stOccurTime.u8Day   = pFault->stOccurTime.u8Day; 
    stFaultHistory.stHistoryFault[0].stOccurTime.u8Hour  = pFault->stOccurTime.u8Hour; 
    stFaultHistory.stHistoryFault[0].stOccurTime.u8Month = pFault->stOccurTime.u8Month; 
    stFaultHistory.stHistoryFault[0].stOccurTime.u8Sec   = pFault->stOccurTime.u8Sec; 
    stFaultHistory.stHistoryFault[0].stOccurTime.u16mSec = pFault->stOccurTime.u16mSec;    
    stFaultHistory.stHistoryFault[0].stClearTime.u16Year = pFault->stClearTime.u16Year;
    stFaultHistory.stHistoryFault[0].stClearTime.u8Month = pFault->stClearTime.u8Month;
    stFaultHistory.stHistoryFault[0].stClearTime.u8Day   = pFault->stClearTime.u8Day; 
    stFaultHistory.stHistoryFault[0].stClearTime.u8Hour  = pFault->stClearTime.u8Hour;
    stFaultHistory.stHistoryFault[0].stClearTime.u8Month = pFault->stClearTime.u8Month;
    stFaultHistory.stHistoryFault[0].stClearTime.u8Sec   = pFault->stClearTime.u8Sec; 
    stFaultHistory.stHistoryFault[0].stClearTime.u16mSec = pFault->stClearTime.u16mSec; 
    
    if(stFaultHistory.u8HistoryFaultIndex == DISPLAY_DATA_FAULT_HISTORY_MAX_COUNT)                                       //达到队列最大条目
    {
         stFaultHistory.u8HistoryFaultIndex = DISPLAY_DATA_FAULT_HISTORY_MAX_COUNT - 1;
    }
    
    memcpy(&stFaultHistory.stHistoryFault[1],&stHistoryFaultBuffer,sizeof(Display_Fault_Info)*stFaultHistory.u8HistoryFaultIndex);
    
    stFaultHistory.u8HistoryFaultIndex++;
   
    Flash_Device_FaultData_Write(&stFaultHistory,sizeof(Fault_Info_History));
}

/***************************************************************************
 功能:操作记录队列插入一条记录
****************************************************************************/
void InsertOperationRecordQueue(Display_Record_Info* pRecord)
{
    Display_Record_Info stRecordBuffer[DISPLAY_DATA_ORRECORD_MAX_COUNT];
    memset(&stRecordBuffer,0,sizeof(Display_Record_Info)*DISPLAY_DATA_ORRECORD_MAX_COUNT);
    memcpy(&stRecordBuffer,&stRecord.stRecord,sizeof(Display_Record_Info)*stRecord.u8RecordIndex);
    
    stRecord.stRecord[0].u8No                  = pRecord->u8No;
    stRecord.stRecord[0].u16RecordType         = pRecord->u16RecordType;
    stRecord.stRecord[0].u8RecordObj           = pRecord->u8RecordObj;
    stRecord.stRecord[0].stOperateTime.u16Year = pRecord->stOperateTime.u16Year;
    stRecord.stRecord[0].stOperateTime.u8Month = pRecord->stOperateTime.u8Month;
    stRecord.stRecord[0].stOperateTime.u8Day   = pRecord->stOperateTime.u8Day;
    stRecord.stRecord[0].stOperateTime.u8Hour  = pRecord->stOperateTime.u8Hour;
    stRecord.stRecord[0].stOperateTime.u8Min   = pRecord->stOperateTime.u8Min;
    stRecord.stRecord[0].stOperateTime.u8Sec   = pRecord->stOperateTime.u8Sec;
    stRecord.stRecord[0].stOperateTime.u16mSec = pRecord->stOperateTime.u16mSec;

    if(stRecord.u8RecordIndex == DISPLAY_DATA_ORRECORD_MAX_COUNT)                                       //达到队列最大条目
    {
         stRecord.u8RecordIndex = DISPLAY_DATA_ORRECORD_MAX_COUNT - 1;
    }
    
    memcpy(&stRecord.stRecord[1],&stRecordBuffer,sizeof(Display_Record_Info)*stRecord.u8RecordIndex);
    
    stRecord.u8RecordIndex++;
    
    Flash_Device_OperateRecord_Write(&stRecord,sizeof(Record_Info));
}

/***************************************************************************
 功能:对外提供获取历史故障数据接口
****************************************************************************/
Fault_Info_History *Display_Get_HistoryFaultData(void)
{
    return &stFaultHistory;
}

/***************************************************************************
 功能:对外提供获取实时故障数据接口
****************************************************************************/
Fault_Info_Real* Display_Get_RealFaultData(void)
{
    return &stFaultReal;
}

/***************************************************************************
 功能:对外提供获取操作记录数据接口
****************************************************************************/
extern Record_Info* Display_Get_OperationRecordData(void)
{
    return &stRecord;
}


/***************************************************************************
功能:对外提供清除历史故障数据接口
****************************************************************************/
void Display_Clear_HistoryFaultData(void)
{
    memset(&stFaultHistory,0,sizeof(Fault_Info_History));
    Flash_Device_FaultData_Write(&stFaultHistory,sizeof(Fault_Info_History));
}

/***************************************************************************
功能:对外提供清除实时故障数据接口
****************************************************************************/
void Display_Clear_RealFaultData(void)
{
    memset(&stFaultHistory,0,sizeof(Fault_Info_History));
}

/***************************************************************************
功能:对外提供清除操作记录数据接口
****************************************************************************/
void Display_Clear_OperationRecordData(void)
{
    memset(&stRecord,0,sizeof(Record_Info));
    Flash_Device_OperateRecord_Read(&stRecord,sizeof(Record_Info));
}

/***************************************************************************
功能:获取pcs故障数据
****************************************************************************/
static void GetDisplayPCSFaultData(Display_PCS_Fault_t* ptDisplayPCSFault)
{
    GetDisplaySystemFault(&ptDisplayPCSFault->tSysFault);                  //获取系统故障
    GetDisplayPVFault(&ptDisplayPCSFault->tPvFault);                       //获取光伏故障
    GetDisplayInvFault(&ptDisplayPCSFault->tInvFault);                     //获取逆变器故障
    GetDisplayDCDCFault(&ptDisplayPCSFault->tDCDCFault);                   //获取DCDC故障
    GetDisplaySysAlarm(&ptDisplayPCSFault->tSysAlarm);                     //获取系统告警
    GetDisplayGenFault(&ptDisplayPCSFault->tGenFault);                     //获取发电机故障
}
/***************************************************************************
功能:获取BMS故障数据
****************************************************************************/
static void GetDisplayBMSFaultData(Display_BMS_Fault_t* ptDisplayBMSFault)
{
    GetDisplayBMSFault(ptDisplayBMSFault);                                //获取BMS故障
}
/***************************************************************************
功能:获取BMS故障数据
****************************************************************************/
static void GetDisplayBMSCanFaultData(Display_BMSCan_Fault_t* ptDisplayBMSCanFault)
{
    GetDisplayBMSCanFault(ptDisplayBMSCanFault);                                //获取BMS故障
}
/***************************************************************************
功能:获取EMS故障数据
****************************************************************************/
static void GetDisplayEMSFaultData(Display_EMS_Fault_t* ptDisplayEMSFault)
{
    GetDisplayEMSCommFault(ptDisplayEMSFault);                            //获取EMS故障
}
/***************************************************************************
功能:获取设备故障数据
****************************************************************************/
static void GetDisplayDeviceFaultData(Display_Fault_t* ptDisplayFault)
{
    GetDisplayPCSFaultData(&ptDisplayFault->tPCSFault);                     //获取PCS故障
    switch (BmsComWayType)
    {
    	case BMS_LI_ION_CAN:
             GetDisplayBMSCanFaultData(&ptDisplayFault->tBMSCanFault);               //获取BMSCan故障
    		break;
    	case BMS_LI_ION_485:
             GetDisplayBMSFaultData(&ptDisplayFault->tBMSFault);                     //获取BMS故障
            break;
        default:
            break;
    }
    GetDisplayEMSFaultData(&ptDisplayFault->tEMSFault);                     //获取EMS故障
}

/***************************************************************************
功能:获取整机设备故障状态
****************************************************************************/
void GetDisplayDeviceFaultState(Display_Fault_t* ptDisplayFault)
{
    //获取屏幕下设电池类型参数
    uint8_t u8DisplayBattType;
    Display_SET_BMS*  pDisplay_Set_BMS = Display_Get_BmsSetPara();
    u8DisplayBattType = pDisplay_Set_BMS ->u8Type;

    //获取屏幕下设使能参数
    Display_EnableDetection_Status stEnableDetection;
    memset(&stEnableDetection,0,sizeof(stEnableDetection));
    Display_Get_EnableDetection(&stEnableDetection);

    //获取PCS工作状态机参数
    DisplayInvRunState_t stInvState;
    memset(&stInvState,0,sizeof(stInvState));
    GetDisplayInvState(&stInvState);

    GetDisplayDeviceFaultData(ptDisplayFault);
    ptDisplayFault->eDeviceFault = DEVICESTATE_NORMAL;

    //EMS与PCS通讯断联故障
    if(ptDisplayFault->tEMSFault.EmsError_t.Bits.bPcsCommState != 0)
    {
        ptDisplayFault->eDeviceFault = DEVICESTATE_FAULT;
    }
    else
    {
        //工作状态机为故障
        if(stInvState.u16InvRunState == 0x0A)
        {
            ptDisplayFault->eDeviceFault = DEVICESTATE_FAULT;
        }
        else
        {
            //PCS侧除系统故障之外的故障定义为告警状态
            if((ptDisplayFault->tPCSFault.tDCDCFault.DCDCError1_t.u16Error != 0)         ||
               (ptDisplayFault->tPCSFault.tPvFault.stPVFault[0].PVFault_t.u32Error != 0) ||
               (ptDisplayFault->tPCSFault.tPvFault.stPVFault[1].PVFault_t.u32Error != 0) ||
               (ptDisplayFault->tPCSFault.tInvFault.InvFault_t.u64Error != 0)            ||
               (ptDisplayFault->tPCSFault.tGenFault.u16Error != 0)                       ||
               (ptDisplayFault->tPCSFault.tSysAlarm.u16Alarm != 0))
            {
                ptDisplayFault->eDeviceFault = DEVICESTATE_ALARM;
            }
            //BMS电池包信息中的故障和告警统一定义为告警
        switch (BmsComWayType)
        {
            case BMS_LI_ION_CAN:
                if((ptDisplayFault->tBMSCanFault.Protect0_t.u8Error != 0)                  ||
                   (ptDisplayFault->tBMSCanFault.Protect1_t.u8Error != 0)                  ||
                   (ptDisplayFault->tBMSCanFault.Alarm0_t.u8Warnning != 0)                 ||
                   (ptDisplayFault->tBMSCanFault.Alarm1_t.u8Warnning != 0))
                {
                    ptDisplayFault->eDeviceFault = DEVICESTATE_ALARM;
                }
                break;
            case BMS_LI_ION_485:
                if((ptDisplayFault->tBMSFault.SystemError1_t.u16Error != 0)                  ||
                   (ptDisplayFault->tBMSFault.SystemError2_t.u16Error != 0)                  ||
                   (ptDisplayFault->tBMSFault.SystemAlarm1_t.u16Warnning != 0)               ||
                   (ptDisplayFault->tBMSFault.SystemAlarm2_t.u16Warnning != 0))
                {
                    ptDisplayFault->eDeviceFault = DEVICESTATE_ALARM;
                }
                break;
            default:
                break;
        }
            if((ptDisplayFault->tEMSFault.EmsError_t.Bits.bMeterCommState != 0)          ||
               (ptDisplayFault->tEMSFault.EmsError_t.Bits.bCTCommState != 0)             ||
               (ptDisplayFault->tEMSFault.EmsError_t.Bits.bWeakBatteryFault != 0))
            {
                ptDisplayFault->eDeviceFault = DEVICESTATE_ALARM;
            }
            //电池使能并且电池类型为锂电池时EMS与BMS通讯断联定义为告警
            if ((stEnableDetection.bIsHasBMS == BIT_SET) && (u8DisplayBattType == 0))
            {
                if (ptDisplayFault->tEMSFault.EmsError_t.Bits.bBmsCommState != 0)
                {
                    ptDisplayFault->eDeviceFault = DEVICESTATE_ALARM;
                }
            }
        }
    }
}

#endif
#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
