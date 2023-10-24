/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Energy_Management_Service.c 
 用途 : 能量管理服务
***********************************************************************************************************************/
#ifndef _ENERGY_MANAGEMENT_C_
#define _ENERGY_MANAGEMENT_C_

#include "HeadFile.h"
#include "Flash_Device.h"
#include "RTC_Service.h"
#include "Modbus_PCS_COMData.h"
#include "Modbus_BMS_COMData.h"
#include "Modbus_Meter_COMData.h"
#include "Buzzer_Device.h"
#include "Energy_Management_Service.h"
#include "Battery_Protect_Service.h"

#if ENERGY_SERVICE_MOUDLE

/*能量管理模块状态*/
EnergyStatus_TypeDef gEnumEnergyStatus = ENERGY_STATE_NULL;
/*上一次通信数据备份*/
EmsParam_t stEmsParamBackup;

bool_t gbGenControlFlag = STATUS_FALSE;
/*DRY-RLY2首次置为标志*/
bool_t gbDryRly2FristFlag = STATUS_FALSE;
/*秒计数器*/
uint8_t gU8DryRly1SecondCounter = 0;
uint8_t gU8DryRly2SecondCounter = 0;
/*发电机启动失败计数器*/
uint8_t gU8StartUpSecondCounter = 0;
/*秒计数器*/
bool_t gbDrylay1Trueflag  = STATUS_FALSE;
bool_t gbDrylay1Falseflag = STATUS_FALSE;

void EnergyManagement_Handler(void)
{
    if (STATUS_FALSE == TimeTask_GetFlag_1s)
    {
        return;
    }

    switch (gEnumEnergyStatus)
    {
        case ENERGY_INIT://能量管理模块初始化
            {
                EnergyInit();
                gEnumEnergyStatus = ENERGY_RUNNING;
            }     
            break;
        case ENERGY_RUNNING://能量管理模块运行
            {
                EnergyRunning();
            }
            break;
        case ENERGY_DESTRCUCTION://能量管理模块析构,用掉电检测村塾
            {
                EnergyDestruction();
            }
            break;
        default:
            break;
    }
}

/***********************************************************************************************************************
 功能：能量管理模块全局变量初始化
***********************************************************************************************************************/
void Energy_Service_InitVar(void)
{
    gEnumEnergyStatus = ENERGY_INIT;
}

/***********************************************************************************************************************
 功能：能量管理模块析构
***********************************************************************************************************************/
void Energy_Service_DestructionVar(void)
{
    EnergyDestruction();
    gEnumEnergyStatus = ENERGY_DESTRCUCTION;  
}

/***********************************************************************************************************************
 功能：能量管理模块硬件初始化
***********************************************************************************************************************/
void Energy_Service_HwInit(void)
{
}

/***************************************************************************
 功能:初始化驱动，全局变量等
****************************************************************************/
static void EnergyInit(void)
{

}

/***************************************************************************
 功能:能量管理总运行函数
****************************************************************************/
static void EnergyRunning(void)
{
    uint8_t u8UpdateBMSdataFlag = 0;
    //从Modbus缓存中获取当前能量管理参数
    EmsParam_t stEmsParam;
    memset(&stEmsParam, 0, sizeof(stEmsParam));
    GetPcs10HEmsParam(&stEmsParam);
    
    //清除发电机控制标志
    ClearGenControlFlag();

    DCDCInformation_t stBatteryInformation;
    memset(&stBatteryInformation, 0, sizeof(stBatteryInformation));
    GetDCDCInformation(&stBatteryInformation);

    switch (u8BatteryType)
    {                                                                                                  //锂电通讯正常
    	case BMS_TYPE_LI_ION:
            switch (BmsComWayType)
            {
                case BMS_LI_ION_CAN:
                    if(tCommStatus.tCommDisconnectFlag.Bits.bEmsToBmsCanCommStateFlag == EMS_COMM_NORMAL)
                    {
                        u8UpdateBMSdataFlag = 1;
                    } 
                    break;
                case BMS_LI_ION_485:
                    if(tCommStatus.tCommDisconnectFlag.Bits.bEmsToBmsCommStateFlag == EMS_COMM_NORMAL)
                    {
                        u8UpdateBMSdataFlag = 1;
                    }  
                    break;
                default:
                    break;
            } 
    		break;
    	case BMS_TYPE_LEAD_ACID:                                                                                        //铅酸，PCS上报电池已连接
            if(stBatteryInformation.u16BatState != 2)
            {
                u8UpdateBMSdataFlag = 1;
            }  
    		break;
    	default:
    		break;
    }

    if(u8UpdateBMSdataFlag == 1)
    {
        //BMS保护数据
        Battery_Protect_Para_t BatteryData;
        memset(&BatteryData, 0, sizeof(BatteryData));
        GetBMSProtectParam(&BatteryData);

        stEmsParam.u16BmsVolt = BatteryData.u16BMSVoltage;
        stEmsParam.u16EmsLiveSOC = BatteryData.u16BMSSOC;
        stEmsParam.u16EmsMaxChgCurr  = BatteryData.s16MaxChargeCurrent;
        stEmsParam.u16EmsMaxDisChgCurr = BatteryData.s16MaxDisChargeCurrent;
        stEmsParam.u16EmsChgCutoffVolt = BatteryData.u16MaxChargeVoltage;
        stEmsParam.u16EmsDisChgCutoffVolt = BatteryData.u16MaxDisChargeVoltage;
    }
    
    //从显存中获取远控和本控的使能标志位
    Display_EnableDetection_Status stEnableDetection;
    memset(&stEnableDetection,0,sizeof(stEnableDetection));
    Display_Get_EnableDetection(&stEnableDetection);

    //本地控制使能
    if(stEnableDetection.bControlWay == STATUS_FALSE)
    {
        LocalControlEnergyRunning(&stEmsParam, stEnableDetection);
    }
    
    //远程控制使能
    else
    {
        RemoteControlEnergyRunning(&stEmsParam);
    }

    //干接点动作
    GenericControlRunning(&stEmsParam);

    if(memcmp(&stEmsParam,&stEmsParamBackup,sizeof(stEmsParamBackup)) != 0)
    {
       SetPcs10HEnergyStrategy(&stEmsParam);
       SetPcs05HPowerOnOffControl(0xFF00); //开机:0xFF00;关机:0x0000
       memcpy(&stEmsParamBackup,&stEmsParam,sizeof(stEmsParamBackup));
    }
    
    if((stEmsParam.u16EmsLiveSOC > stEmsParam.u16EmsChgCutoffSOC)||(stEmsParam.u16EmsLiveSOC > stEmsParam.u16EmsDisChgCutoffSOC))
    {
        SetPcs05HPowerOnOffControl(0x0000); //开机:0xFF00;关机:0x0000 
    }
}
/***************************************************************************
 功能:能量管理析构函数，用于掉电触发保护逻辑
****************************************************************************/
static void EnergyDestruction(void)
{

}

/***************************************************************************
 功能:跟配置峰谷模式配置数据或者要执行的配置
****************************************************************************/
static EMS_Effective_ParaDef getEnergyRunParabyTPFVMode(Display_SET_System_Strategy* pStrategy, int32_t u32SystemSec)
{
    EMS_Effective_ParaDef stPara;
    memset(&stPara,0,sizeof(stPara));
    
    Display_SET_BMS* pBMSInfo = Display_Get_BmsSetPara();
    Display_SET_System_Strategy_TPFV * pTPFV = &pStrategy->stTPFVStrategy;
    stPara.u8TPFVStatus = TPFV_FLAT;
    /*
     //尖段时间段1
    uint32_t u32TipOneStartSec = 0;
    u32TipOneStartSec = u32TipOneStartSec + pTPFV->stTipPeriod.stPeriod1.stPeriod.u8StartHour * 3600;
    u32TipOneStartSec = u32TipOneStartSec + pTPFV->stTipPeriod.stPeriod1.stPeriod.u8StartMin  * 60;
    u32TipOneStartSec = u32TipOneStartSec + pTPFV->stTipPeriod.stPeriod1.stPeriod.u8StartSec;  
    uint32_t u32TipOneEndSec = 0;
    u32TipOneEndSec = u32TipOneEndSec + pTPFV->stTipPeriod.stPeriod1.stPeriod.u8EndHour * 3600;
    u32TipOneEndSec = u32TipOneEndSec + pTPFV->stTipPeriod.stPeriod1.stPeriod.u8EndMin  * 60;
    u32TipOneEndSec = u32TipOneEndSec + pTPFV->stTipPeriod.stPeriod1.stPeriod.u8EndSec;
    stPara.u8TPFVStatus = pTPFV->u8TPFVStatus;
    if((u32SystemSec >= u32TipOneStartSec) && (u32SystemSec < u32TipOneEndSec))
    {
       stPara.s16Power = pTPFV->stTipPeriod.stPeriod1.s16Power;
       //stPara.u8StopSOC = pTPFV->stTipPeriod.stPeriod1.u8StopSOC;
       return stPara;
    }
    
    //尖段时间段2
    uint32_t u32TipTwoStartSec = 0;
    u32TipTwoStartSec = u32TipTwoStartSec + pTPFV->stTipPeriod.stPeriod2.stPeriod.u8StartHour * 3600;
    u32TipTwoStartSec = u32TipTwoStartSec + pTPFV->stTipPeriod.stPeriod2.stPeriod.u8StartMin  * 60;
    u32TipTwoStartSec = u32TipTwoStartSec + pTPFV->stTipPeriod.stPeriod2.stPeriod.u8StartSec;   
    uint32_t u32TipTwoEndSec = 0;
    u32TipTwoEndSec = u32TipTwoEndSec + pTPFV->stTipPeriod.stPeriod2.stPeriod.u8EndHour * 3600;
    u32TipTwoEndSec = u32TipTwoEndSec + pTPFV->stTipPeriod.stPeriod2.stPeriod.u8EndMin  * 60;
    u32TipTwoEndSec = u32TipTwoEndSec + pTPFV->stTipPeriod.stPeriod2.stPeriod.u8EndSec;
    if((u32SystemSec >= u32TipTwoStartSec) && (u32SystemSec < u32TipTwoEndSec))
    {
       stPara.s16Power = pTPFV->stTipPeriod.stPeriod2.s16Power;
       //stPara.u8StopSOC = pTPFV->stTipPeriod.stPeriod2.u8StopSOC;
       return stPara;
    }
    
    //尖段时间段3
    uint32_t u32TipThreeStartSec = 0;
    u32TipThreeStartSec = u32TipThreeStartSec + pTPFV->stTipPeriod.stPeriod3.stPeriod.u8StartHour * 3600;
    u32TipThreeStartSec = u32TipThreeStartSec + pTPFV->stTipPeriod.stPeriod3.stPeriod.u8StartMin  * 60;
    u32TipThreeStartSec = u32TipThreeStartSec + pTPFV->stTipPeriod.stPeriod3.stPeriod.u8StartSec;
    uint32_t u32TipThreeEndSec = 0;
    u32TipThreeEndSec = u32TipThreeEndSec + pTPFV->stTipPeriod.stPeriod3.stPeriod.u8EndHour * 3600;
    u32TipThreeEndSec = u32TipThreeEndSec + pTPFV->stTipPeriod.stPeriod3.stPeriod.u8EndMin  * 60;
    u32TipThreeEndSec = u32TipThreeEndSec + pTPFV->stTipPeriod.stPeriod3.stPeriod.u8EndSec;
    if((u32SystemSec >= u32TipThreeStartSec) && (u32SystemSec < u32TipThreeEndSec))
    {
       stPara.s16Power = pTPFV->stTipPeriod.stPeriod3.s16Power;
       //stPara.u8StopSOC = pTPFV->stTipPeriod.stPeriod3.u8StopSOC;
       return stPara;
    }
    */
    //峰段时间段1
    uint32_t u32PeakOneStartSec = 0;
    u32PeakOneStartSec = u32PeakOneStartSec + pTPFV->stPeakPeriod.stPeriod1.stPeriod.u8StartHour * 3600;
    u32PeakOneStartSec = u32PeakOneStartSec + pTPFV->stPeakPeriod.stPeriod1.stPeriod.u8StartMin  * 60;
    u32PeakOneStartSec = u32PeakOneStartSec + pTPFV->stPeakPeriod.stPeriod1.stPeriod.u8StartSec;  
    uint32_t u32PeakOneEndSec = 0;
    u32PeakOneEndSec = u32PeakOneEndSec + pTPFV->stPeakPeriod.stPeriod1.stPeriod.u8EndHour * 3600;
    u32PeakOneEndSec = u32PeakOneEndSec + pTPFV->stPeakPeriod.stPeriod1.stPeriod.u8EndMin  * 60;
    u32PeakOneEndSec = u32PeakOneEndSec + pTPFV->stPeakPeriod.stPeriod1.stPeriod.u8EndSec;
    if((u32SystemSec >= u32PeakOneStartSec) && (u32SystemSec < u32PeakOneEndSec))
    {
       stPara.s16Power = pTPFV->stPeakPeriod.stPeriod1.s16Power;
       stPara.u8TPFVStatus = TPFV_PEAK;
    
       if(pBMSInfo->u8Type == BMS_TYPE_LI_ION)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLiIonParas.u8EndOfDisCharSOC;
       }
       else if(pBMSInfo->u8Type == BMS_TYPE_LEAD_ACID)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLeadAcidParas.u8EndOfDisCharSOC;
       }
       
       return stPara;
    }
    
    //峰段时间段2
    uint32_t u32PeakTwoStartSec = 0;
    u32PeakTwoStartSec = u32PeakTwoStartSec + pTPFV->stPeakPeriod.stPeriod2.stPeriod.u8StartHour * 3600;
    u32PeakTwoStartSec = u32PeakTwoStartSec + pTPFV->stPeakPeriod.stPeriod2.stPeriod.u8StartMin  * 60;
    u32PeakTwoStartSec = u32PeakTwoStartSec + pTPFV->stPeakPeriod.stPeriod2.stPeriod.u8StartSec;   
    uint32_t u32PeakTwoEndSec = 0;
    u32PeakTwoEndSec = u32PeakTwoEndSec + pTPFV->stPeakPeriod.stPeriod2.stPeriod.u8EndHour * 3600;
    u32PeakTwoEndSec = u32PeakTwoEndSec + pTPFV->stPeakPeriod.stPeriod2.stPeriod.u8EndMin  * 60;
    u32PeakTwoEndSec = u32PeakTwoEndSec + pTPFV->stPeakPeriod.stPeriod2.stPeriod.u8EndSec;
    if((u32SystemSec >= u32PeakTwoStartSec) && (u32SystemSec < u32PeakTwoEndSec))
    {
       stPara.s16Power = pTPFV->stPeakPeriod.stPeriod2.s16Power;
       stPara.u8TPFVStatus = TPFV_PEAK;
       if(pBMSInfo->u8Type == BMS_TYPE_LI_ION)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLiIonParas.u8EndOfDisCharSOC;
       }
       else if(pBMSInfo->u8Type == BMS_TYPE_LEAD_ACID)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLeadAcidParas.u8EndOfDisCharSOC;
       }
       
       return stPara;
    }
    
    //峰段时间段3
    uint32_t u32PeakThreeStartSec = 0;
    u32PeakThreeStartSec = u32PeakThreeStartSec + pTPFV->stPeakPeriod.stPeriod3.stPeriod.u8StartHour * 3600;
    u32PeakThreeStartSec = u32PeakThreeStartSec + pTPFV->stPeakPeriod.stPeriod3.stPeriod.u8StartMin  * 60;
    u32PeakThreeStartSec = u32PeakThreeStartSec + pTPFV->stPeakPeriod.stPeriod3.stPeriod.u8StartSec;
    uint32_t u32PeakThreeEndSec = 0;
    u32PeakThreeEndSec = u32PeakThreeEndSec + pTPFV->stPeakPeriod.stPeriod3.stPeriod.u8EndHour * 3600;
    u32PeakThreeEndSec = u32PeakThreeEndSec + pTPFV->stPeakPeriod.stPeriod3.stPeriod.u8EndMin  * 60;
    u32PeakThreeEndSec = u32PeakThreeEndSec + pTPFV->stPeakPeriod.stPeriod3.stPeriod.u8EndSec;
    if((u32SystemSec >= u32PeakThreeStartSec) && (u32SystemSec < u32PeakThreeEndSec))
    {
       stPara.s16Power = pTPFV->stPeakPeriod.stPeriod3.s16Power;
       stPara.u8TPFVStatus = TPFV_PEAK;
       if(pBMSInfo->u8Type == BMS_TYPE_LI_ION)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLiIonParas.u8EndOfDisCharSOC;
       }
       else if(pBMSInfo->u8Type == BMS_TYPE_LEAD_ACID)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLeadAcidParas.u8EndOfDisCharSOC;
       }
       
       return stPara;
    }
    
    /*       
    //平段时间段1
    uint32_t u32FlatOneStartSec = 0;
    u32FlatOneStartSec = u32FlatOneStartSec + pTPFV->stFlatPeriod.stPeriod1.stPeriod.u8StartHour * 3600;
    u32FlatOneStartSec = u32FlatOneStartSec + pTPFV->stFlatPeriod.stPeriod1.stPeriod.u8StartMin  * 60;
    u32FlatOneStartSec = u32FlatOneStartSec + pTPFV->stFlatPeriod.stPeriod1.stPeriod.u8StartSec;  
    uint32_t u32FlatOneEndSec = 0;
    u32FlatOneEndSec = u32FlatOneEndSec + pTPFV->stFlatPeriod.stPeriod1.stPeriod.u8EndHour * 3600;
    u32FlatOneEndSec = u32FlatOneEndSec + pTPFV->stFlatPeriod.stPeriod1.stPeriod.u8EndMin  * 60;
    u32FlatOneEndSec = u32FlatOneEndSec + pTPFV->stFlatPeriod.stPeriod1.stPeriod.u8EndSec;
    if((u32SystemSec >= u32FlatOneStartSec) && (u32SystemSec < u32FlatOneEndSec))
    {
       stPara.s16Power = pTPFV->stFlatPeriod.stPeriod1.s16Power;
       stPara.u8StopSOC = pTPFV->stFlatPeriod.stPeriod1.u8StopSOC;
       return stPara;
    }
    
    //平段时间段2
    uint32_t u32FlatTwoStartSec = 0;
    u32FlatTwoStartSec = u32FlatTwoStartSec + pTPFV->stFlatPeriod.stPeriod2.stPeriod.u8StartHour * 3600;
    u32FlatTwoStartSec = u32FlatTwoStartSec + pTPFV->stFlatPeriod.stPeriod2.stPeriod.u8StartMin  * 60;
    u32FlatTwoStartSec = u32FlatTwoStartSec + pTPFV->stFlatPeriod.stPeriod2.stPeriod.u8StartSec;   
    uint32_t u32FlatTwoEndSec = 0;
    u32FlatTwoEndSec = u32FlatTwoEndSec + pTPFV->stFlatPeriod.stPeriod2.stPeriod.u8EndHour * 3600;
    u32FlatTwoEndSec = u32FlatTwoEndSec + pTPFV->stFlatPeriod.stPeriod2.stPeriod.u8EndMin  * 60;
    u32FlatTwoEndSec = u32FlatTwoEndSec + pTPFV->stFlatPeriod.stPeriod2.stPeriod.u8EndSec;
    if((u32SystemSec >= u32FlatTwoStartSec) && (u32SystemSec < u32FlatTwoEndSec))
    {
       stPara.s16Power = pTPFV->stFlatPeriod.stPeriod2.s16Power;
       stPara.u8StopSOC = pTPFV->stFlatPeriod.stPeriod2.u8StopSOC;
       return stPara;
    }
    
    //平段时间段3
    uint32_t u32FlatThreeStartSec = 0;
    u32FlatThreeStartSec = u32FlatThreeStartSec + pTPFV->stFlatPeriod.stPeriod3.stPeriod.u8StartHour * 3600;
    u32FlatThreeStartSec = u32FlatThreeStartSec + pTPFV->stFlatPeriod.stPeriod3.stPeriod.u8StartMin  * 60;
    u32FlatThreeStartSec = u32FlatThreeStartSec + pTPFV->stFlatPeriod.stPeriod3.stPeriod.u8StartSec;
    uint32_t u32FlatThreeEndSec = 0;
    u32FlatThreeEndSec = u32FlatThreeEndSec + pTPFV->stFlatPeriod.stPeriod3.stPeriod.u8EndHour * 3600;
    u32FlatThreeEndSec = u32FlatThreeEndSec + pTPFV->stFlatPeriod.stPeriod3.stPeriod.u8EndMin  * 60;
    u32FlatThreeEndSec = u32FlatThreeEndSec + pTPFV->stFlatPeriod.stPeriod3.stPeriod.u8EndSec;
    if((u32SystemSec >= u32FlatThreeStartSec) && (u32SystemSec < u32FlatThreeEndSec))
    {
       stPara.s16Power = pTPFV->stFlatPeriod.stPeriod3.s16Power;
       stPara.u8StopSOC = pTPFV->stFlatPeriod.stPeriod3.u8StopSOC;
       return stPara;
    }
    */
    //谷段时间段1
    uint32_t u32ValleyOneStartSec = 0;
    u32ValleyOneStartSec = u32ValleyOneStartSec + pTPFV->stValleyPeriod.stPeriod1.stPeriod.u8StartHour * 3600;
    u32ValleyOneStartSec = u32ValleyOneStartSec + pTPFV->stValleyPeriod.stPeriod1.stPeriod.u8StartMin  * 60;
    u32ValleyOneStartSec = u32ValleyOneStartSec + pTPFV->stValleyPeriod.stPeriod1.stPeriod.u8StartSec;  
    uint32_t u32ValleyOneEndSec = 0;
    u32ValleyOneEndSec = u32ValleyOneEndSec + pTPFV->stValleyPeriod.stPeriod1.stPeriod.u8EndHour * 3600;
    u32ValleyOneEndSec = u32ValleyOneEndSec + pTPFV->stValleyPeriod.stPeriod1.stPeriod.u8EndMin  * 60;
    u32ValleyOneEndSec = u32ValleyOneEndSec + pTPFV->stValleyPeriod.stPeriod1.stPeriod.u8EndSec;
    if((u32SystemSec >= u32ValleyOneStartSec) && (u32SystemSec < u32ValleyOneEndSec))
    {
       stPara.s16Power = pTPFV->stValleyPeriod.stPeriod1.s16Power;
       stPara.u8TPFVStatus = TPFV_VALLEY;
       if(pBMSInfo->u8Type == BMS_TYPE_LI_ION)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLiIonParas.u8EndOfCharSOC;
       }
       else if(pBMSInfo->u8Type == BMS_TYPE_LEAD_ACID)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLeadAcidParas.u8EndOfCharSOC;
       }
       
       return stPara;
    }
    
    //谷段时间段2
    uint32_t u32ValleyTwoStartSec = 0;
    u32ValleyTwoStartSec = u32ValleyTwoStartSec + pTPFV->stValleyPeriod.stPeriod2.stPeriod.u8StartHour * 3600;
    u32ValleyTwoStartSec = u32ValleyTwoStartSec + pTPFV->stValleyPeriod.stPeriod2.stPeriod.u8StartMin  * 60;
    u32ValleyTwoStartSec = u32ValleyTwoStartSec + pTPFV->stValleyPeriod.stPeriod2.stPeriod.u8StartSec;   
    uint32_t u32ValleyTwoEndSec = 0;
    u32ValleyTwoEndSec = u32ValleyTwoEndSec + pTPFV->stValleyPeriod.stPeriod2.stPeriod.u8EndHour * 3600;
    u32ValleyTwoEndSec = u32ValleyTwoEndSec + pTPFV->stValleyPeriod.stPeriod2.stPeriod.u8EndMin  * 60;
    u32ValleyTwoEndSec = u32ValleyTwoEndSec + pTPFV->stValleyPeriod.stPeriod2.stPeriod.u8EndSec;
    if((u32SystemSec >= u32ValleyTwoStartSec) && (u32SystemSec < u32ValleyTwoEndSec))
    {
       stPara.s16Power = pTPFV->stValleyPeriod.stPeriod2.s16Power;
       stPara.u8TPFVStatus = TPFV_VALLEY;
       if(pBMSInfo->u8Type == BMS_TYPE_LI_ION)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLiIonParas.u8EndOfCharSOC;
       }
       else if(pBMSInfo->u8Type == BMS_TYPE_LEAD_ACID)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLeadAcidParas.u8EndOfCharSOC;
       }
       
       return stPara;
    }
    
    //谷段时间段3
    uint32_t u32ValleyThreeStartSec = 0;
    u32ValleyThreeStartSec = u32ValleyThreeStartSec + pTPFV->stValleyPeriod.stPeriod3.stPeriod.u8StartHour * 3600;
    u32ValleyThreeStartSec = u32ValleyThreeStartSec + pTPFV->stValleyPeriod.stPeriod3.stPeriod.u8StartMin  * 60;
    u32ValleyThreeStartSec = u32ValleyThreeStartSec + pTPFV->stValleyPeriod.stPeriod3.stPeriod.u8StartSec;
    uint32_t u32ValleyThreeEndSec = 0;
    u32ValleyThreeEndSec = u32ValleyThreeEndSec + pTPFV->stValleyPeriod.stPeriod3.stPeriod.u8EndHour * 3600;
    u32ValleyThreeEndSec = u32ValleyThreeEndSec + pTPFV->stValleyPeriod.stPeriod3.stPeriod.u8EndMin  * 60;
    u32ValleyThreeEndSec = u32ValleyThreeEndSec + pTPFV->stValleyPeriod.stPeriod3.stPeriod.u8EndSec;
    if((u32SystemSec >= u32ValleyThreeStartSec) && (u32SystemSec < u32ValleyThreeEndSec))
    {
       stPara.s16Power = pTPFV->stValleyPeriod.stPeriod3.s16Power;
       stPara.u8TPFVStatus = TPFV_VALLEY;
       if(pBMSInfo->u8Type == BMS_TYPE_LI_ION)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLiIonParas.u8EndOfCharSOC;
       }
       else if(pBMSInfo->u8Type == BMS_TYPE_LEAD_ACID)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLeadAcidParas.u8EndOfCharSOC;
       }
       
       return stPara;
    }
    
    return stPara;
}

/***************************************************************************
 功能:跟配置定时充放电模式配置数据或者要执行的配置
****************************************************************************/
static EMS_Effective_ParaDef getEnergyRunParabyRegularMode(Display_SET_System_Strategy* pStrategy, int32_t u32SystemSec)
{
    EMS_Effective_ParaDef stPara;
    memset(&stPara,0,sizeof(stPara));
    stPara.u8TPFVStatus = TPFV_FLAT;
    Display_SET_System_Strategy_Timer * pRegular = &pStrategy->stTimerStrategy;
    Display_SET_BMS* pBMSInfo = Display_Get_BmsSetPara();
    //充电时间段1   峰段
    uint32_t u32ChargeOneStartSec = 0;
    u32ChargeOneStartSec = u32ChargeOneStartSec + pRegular->stChargePeriod.stPeriod1.stPeriod.u8StartHour * 3600;
    u32ChargeOneStartSec = u32ChargeOneStartSec + pRegular->stChargePeriod.stPeriod1.stPeriod.u8StartMin  * 60;
    u32ChargeOneStartSec = u32ChargeOneStartSec + pRegular->stChargePeriod.stPeriod1.stPeriod.u8StartSec;  
    uint32_t u32ChargeOneEndSec = 0;
    u32ChargeOneEndSec = u32ChargeOneEndSec + pRegular->stChargePeriod.stPeriod1.stPeriod.u8EndHour * 3600;
    u32ChargeOneEndSec = u32ChargeOneEndSec + pRegular->stChargePeriod.stPeriod1.stPeriod.u8EndMin  * 60;
    u32ChargeOneEndSec = u32ChargeOneEndSec + pRegular->stChargePeriod.stPeriod1.stPeriod.u8EndSec;
    if((u32SystemSec >= u32ChargeOneStartSec) && (u32SystemSec < u32ChargeOneEndSec))
    {
       stPara.s16Power = pRegular->stChargePeriod.stPeriod1.s16Power;
       if(pBMSInfo->u8Type == BMS_TYPE_LI_ION)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLiIonParas.u8EndOfDisCharSOC;
       }
       else if(pBMSInfo->u8Type == BMS_TYPE_LEAD_ACID)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLeadAcidParas.u8EndOfDisCharSOC;
       }
       stPara.u8TPFVStatus = TPFV_VALLEY;
       return stPara;
    }
    
    //充电时间段2  峰段
    uint32_t u32ChargeTwoStartSec = 0;
    u32ChargeTwoStartSec = u32ChargeTwoStartSec + pRegular->stChargePeriod.stPeriod2.stPeriod.u8StartHour * 3600;
    u32ChargeTwoStartSec = u32ChargeTwoStartSec + pRegular->stChargePeriod.stPeriod2.stPeriod.u8StartMin  * 60;
    u32ChargeTwoStartSec = u32ChargeTwoStartSec + pRegular->stChargePeriod.stPeriod2.stPeriod.u8StartSec;  
    uint32_t u32ChargeTwoEndSec = 0;
    u32ChargeTwoEndSec = u32ChargeTwoEndSec + pRegular->stChargePeriod.stPeriod2.stPeriod.u8EndHour * 3600;
    u32ChargeTwoEndSec = u32ChargeTwoEndSec + pRegular->stChargePeriod.stPeriod2.stPeriod.u8EndMin  * 60;
    u32ChargeTwoEndSec = u32ChargeTwoEndSec + pRegular->stChargePeriod.stPeriod2.stPeriod.u8EndSec;
    if((u32SystemSec >= u32ChargeTwoStartSec) && (u32SystemSec < u32ChargeTwoEndSec))
    {
       stPara.s16Power = pRegular->stChargePeriod.stPeriod2.s16Power;
       if(pBMSInfo->u8Type == BMS_TYPE_LI_ION)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLiIonParas.u8EndOfDisCharSOC;
       }
       else if(pBMSInfo->u8Type == BMS_TYPE_LEAD_ACID)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLeadAcidParas.u8EndOfDisCharSOC;
       }
       stPara.u8TPFVStatus = TPFV_VALLEY;
       return stPara;
    }
    
    //充电时间段3  峰段
    uint32_t u32ChargeThreeStartSec = 0;
    u32ChargeThreeStartSec = u32ChargeThreeStartSec + pRegular->stChargePeriod.stPeriod3.stPeriod.u8StartHour * 3600;
    u32ChargeThreeStartSec = u32ChargeThreeStartSec + pRegular->stChargePeriod.stPeriod3.stPeriod.u8StartMin  * 60;
    u32ChargeThreeStartSec = u32ChargeThreeStartSec + pRegular->stChargePeriod.stPeriod3.stPeriod.u8StartSec;  
    uint32_t u32ChargeThreeEndSec = 0;
    u32ChargeThreeEndSec = u32ChargeThreeEndSec + pRegular->stChargePeriod.stPeriod3.stPeriod.u8EndHour * 3600;
    u32ChargeThreeEndSec = u32ChargeThreeEndSec + pRegular->stChargePeriod.stPeriod3.stPeriod.u8EndMin  * 60;
    u32ChargeThreeEndSec = u32ChargeThreeEndSec + pRegular->stChargePeriod.stPeriod3.stPeriod.u8EndSec;
    if((u32SystemSec >= u32ChargeThreeStartSec) && (u32SystemSec < u32ChargeThreeEndSec))
    {
       stPara.s16Power = pRegular->stChargePeriod.stPeriod3.s16Power;
       if(pBMSInfo->u8Type == BMS_TYPE_LI_ION)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLiIonParas.u8EndOfDisCharSOC;
       }
       else if(pBMSInfo->u8Type == BMS_TYPE_LEAD_ACID)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLeadAcidParas.u8EndOfDisCharSOC;
       }
       stPara.u8TPFVStatus = TPFV_VALLEY;
       return stPara;
    }
    
    /*
    //充电时间段4
    uint32_t u32ChargeFourStartSec = 0;
    u32ChargeFourStartSec = u32ChargeFourStartSec + pRegular->stChargePeriod.stPeriod4.stPeriod.u8StartHour * 3600;
    u32ChargeFourStartSec = u32ChargeFourStartSec + pRegular->stChargePeriod.stPeriod4.stPeriod.u8StartMin  * 60;
    u32ChargeFourStartSec = u32ChargeFourStartSec + pRegular->stChargePeriod.stPeriod4.stPeriod.u8StartSec;  
    uint32_t u32ChargeFourEndSec = 0;
    u32ChargeFourEndSec = u32ChargeFourEndSec + pRegular->stChargePeriod.stPeriod4.stPeriod.u8EndHour * 3600;
    u32ChargeFourEndSec = u32ChargeFourEndSec + pRegular->stChargePeriod.stPeriod4.stPeriod.u8EndMin  * 60;
    u32ChargeFourEndSec = u32ChargeFourEndSec + pRegular->stChargePeriod.stPeriod4.stPeriod.u8EndSec;
    if((u32SystemSec >= u32ChargeFourStartSec) && (u32SystemSec < u32ChargeFourEndSec))
    {
       stPara.s16Power = pRegular->stChargePeriod.stPeriod4.s16Power;
       stPara.u8StopSOC = pRegular->stChargePeriod.stPeriod4.u8StopSOC;
       *pU8IsFlag = 1;
       return stPara;
    }
    */
    
    //放电时间段1  谷段
    uint32_t u32DisChargeOneStartSec = 0;
    u32DisChargeOneStartSec = u32DisChargeOneStartSec + pRegular->stDisChargePeriod.stPeriod1.stPeriod.u8StartHour * 3600;
    u32DisChargeOneStartSec = u32DisChargeOneStartSec + pRegular->stDisChargePeriod.stPeriod1.stPeriod.u8StartMin  * 60;
    u32DisChargeOneStartSec = u32DisChargeOneStartSec + pRegular->stDisChargePeriod.stPeriod1.stPeriod.u8StartSec;  
    uint32_t u32DisChargeOneEndSec = 0;
    u32DisChargeOneEndSec = u32DisChargeOneEndSec + pRegular->stDisChargePeriod.stPeriod1.stPeriod.u8EndHour * 3600;
    u32DisChargeOneEndSec = u32DisChargeOneEndSec + pRegular->stDisChargePeriod.stPeriod1.stPeriod.u8EndMin  * 60;
    u32DisChargeOneEndSec = u32DisChargeOneEndSec + pRegular->stDisChargePeriod.stPeriod1.stPeriod.u8EndSec;
    if((u32SystemSec >= u32DisChargeOneStartSec) && (u32SystemSec < u32DisChargeOneEndSec))
    {
       stPara.s16Power = pRegular->stDisChargePeriod.stPeriod1.s16Power;
       if(pBMSInfo->u8Type == BMS_TYPE_LI_ION)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLiIonParas.u8EndOfCharSOC;
       }
       else if(pBMSInfo->u8Type == BMS_TYPE_LEAD_ACID)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLeadAcidParas.u8EndOfCharSOC;
       }
       stPara.u8TPFVStatus = TPFV_PEAK;
       return stPara;
    }
    
    //放电时间段2  谷段
    uint32_t u32DisChargeTwoStartSec = 0;
    u32DisChargeTwoStartSec = u32DisChargeTwoStartSec + pRegular->stDisChargePeriod.stPeriod2.stPeriod.u8StartHour * 3600;
    u32DisChargeTwoStartSec = u32DisChargeTwoStartSec + pRegular->stDisChargePeriod.stPeriod2.stPeriod.u8StartMin  * 60;
    u32DisChargeTwoStartSec = u32DisChargeTwoStartSec + pRegular->stDisChargePeriod.stPeriod2.stPeriod.u8StartSec;  
    uint32_t u32DisChargeTwoEndSec = 0;
    u32DisChargeTwoEndSec = u32DisChargeTwoEndSec + pRegular->stDisChargePeriod.stPeriod2.stPeriod.u8EndHour * 3600;
    u32DisChargeTwoEndSec = u32DisChargeTwoEndSec + pRegular->stDisChargePeriod.stPeriod2.stPeriod.u8EndMin  * 60;
    u32DisChargeTwoEndSec = u32DisChargeTwoEndSec + pRegular->stDisChargePeriod.stPeriod2.stPeriod.u8EndSec;
    if((u32SystemSec >= u32DisChargeTwoStartSec) && (u32SystemSec < u32DisChargeTwoEndSec))
    {
       stPara.s16Power = pRegular->stDisChargePeriod.stPeriod2.s16Power;
       if(pBMSInfo->u8Type == BMS_TYPE_LI_ION)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLiIonParas.u8EndOfCharSOC;
       }
       else if(pBMSInfo->u8Type == BMS_TYPE_LEAD_ACID)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLeadAcidParas.u8EndOfCharSOC;
       }
       stPara.u8TPFVStatus = TPFV_PEAK;
       return stPara;
    }
    
    //放电时间段3  谷段
    uint32_t u32DisChargeThreeStartSec = 0;
    u32DisChargeThreeStartSec = u32DisChargeThreeStartSec + pRegular->stDisChargePeriod.stPeriod3.stPeriod.u8StartHour * 3600;
    u32DisChargeThreeStartSec = u32DisChargeThreeStartSec + pRegular->stDisChargePeriod.stPeriod3.stPeriod.u8StartMin  * 60;
    u32DisChargeThreeStartSec = u32DisChargeThreeStartSec + pRegular->stDisChargePeriod.stPeriod3.stPeriod.u8StartSec;  
    uint32_t u32DisChargeThreeEndSec = 0;
    u32DisChargeThreeEndSec = u32DisChargeThreeEndSec + pRegular->stDisChargePeriod.stPeriod3.stPeriod.u8EndHour * 3600;
    u32DisChargeThreeEndSec = u32DisChargeThreeEndSec + pRegular->stDisChargePeriod.stPeriod3.stPeriod.u8EndMin  * 60;
    u32DisChargeThreeEndSec = u32DisChargeThreeEndSec + pRegular->stDisChargePeriod.stPeriod3.stPeriod.u8EndSec;
    if((u32SystemSec >= u32DisChargeThreeStartSec) && (u32SystemSec < u32DisChargeThreeEndSec))
    {
       stPara.s16Power = pRegular->stDisChargePeriod.stPeriod3.s16Power;
       if(pBMSInfo->u8Type == BMS_TYPE_LI_ION)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLiIonParas.u8EndOfCharSOC;
       }
       else if(pBMSInfo->u8Type == BMS_TYPE_LEAD_ACID)
       {
            stPara.u8StopSOC = pBMSInfo->stHMISetBMSLeadAcidParas.u8EndOfCharSOC;
       }
       stPara.u8TPFVStatus = TPFV_PEAK;
       return stPara;
    }
     /*
    //放电时间段4
    uint32_t u32DisChargeFourStartSec = 0;
    u32DisChargeFourStartSec = u32DisChargeFourStartSec + pRegular->stDisChargePeriod.stPeriod4.stPeriod.u8StartHour * 3600;
    u32DisChargeFourStartSec = u32DisChargeFourStartSec + pRegular->stDisChargePeriod.stPeriod4.stPeriod.u8StartMin  * 60;
    u32DisChargeFourStartSec = u32DisChargeFourStartSec + pRegular->stDisChargePeriod.stPeriod4.stPeriod.u8StartSec;  
    uint32_t u32DisChargeFourEndSec = 0;
    u32DisChargeFourEndSec = u32DisChargeFourEndSec + pRegular->stDisChargePeriod.stPeriod4.stPeriod.u8EndHour * 3600;
    u32DisChargeFourEndSec = u32DisChargeFourEndSec + pRegular->stDisChargePeriod.stPeriod4.stPeriod.u8EndMin  * 60;
    u32DisChargeFourEndSec = u32DisChargeFourEndSec + pRegular->stDisChargePeriod.stPeriod4.stPeriod.u8EndSec;
    if((u32SystemSec >= u32DisChargeFourStartSec) && (u32SystemSec < u32DisChargeFourEndSec))
    {
       stPara.s16Power = pRegular->stDisChargePeriod.stPeriod4.s16Power;
       stPara.u8StopSOC = pRegular->stDisChargePeriod.stPeriod4.u8StopSOC;
       *pU8IsFlag = 0;
       return stPara;
    }
    */
    
    return stPara;
}

/***************************************************************************
 功能:本地控制运行函数
****************************************************************************/
static void LocalControlEnergyRunning(EmsParam_t* pEmsParam,  Display_EnableDetection_Status stEnableDetection)
{
    //获取屏幕下设的能量管理策略
    Display_SET_System_Strategy* pStrategy = Display_Get_SystemStrategy();
    Display_SET_Gen *pGenPara = Display_Get_GenPara();
    
    if(pStrategy->u8StrategyType == STRATEGY_NULL)
    {
        return;
    }

    //获取系统时间
    TimeInf_t tab_SysCurrentTime;
    memset(&tab_SysCurrentTime, 0, sizeof(TimeInf_t));
    Get_SysTime(&tab_SysCurrentTime);
    uint32_t u32SystemSec = tab_SysCurrentTime.u8Hour * 3600 +  tab_SysCurrentTime.u8Min * 60 + tab_SysCurrentTime.u8Sec;

//    memset(pEmsParam,0,sizeof(EmsParam_t));
    pEmsParam->u16EmsMethod =  pStrategy->u8StrategyType;
    pEmsParam->u16DryContactEnFlag = stEnableDetection.bIsHasGen;

//    //BMS保护数据
//    Battery_Protect_Para_t BatteryData;
//    memset(&BatteryData, 0, sizeof(BatteryData));
//    GetBMSProtectParam(&BatteryData);

//    pEmsParam->u16BmsVolt = BatteryData.u16BMSVoltage;
//    pEmsParam->u16EmsLiveSOC = BatteryData.u8NowSOC;
//    pEmsParam->u16EmsMaxChgCurr  = BatteryData.s16MaxChargeCurrent;
//    pEmsParam->u16EmsMaxDisChgCurr = BatteryData.s16MaxDisChargeCurrent;
//    pEmsParam->u16EmsChgCutoffVolt = BatteryData.u16MaxChargeVoltage;
//    pEmsParam->u16EmsDisChgCutoffVolt = BatteryData.u16MaxDisChargeVoltage;

    Display_SET_Grid* pGrid = Display_Get_Grid();
    
    switch(pEmsParam->u16EmsMethod)
    {
        /*自发自用模式，只用设置模式，不用设置参数*/
        case STRATEGY_SELF:
            {
                ;
            }
        break;
        /*削峰填谷模式*/
        case STRATEGY_TPFV:
            {
                EMS_Effective_ParaDef stTPFVPara = getEnergyRunParabyTPFVMode(pStrategy, u32SystemSec);
                pEmsParam->s16EmsWatt = stTPFVPara.s16Power; //需要从电网设置数据取
                pEmsParam->s16EmsVar = pGrid->s16ReactPower;
                
                if(stTPFVPara.u8TPFVStatus == TPFV_PEAK)
                {
                    pEmsParam->u16EmsDisChgCutoffSOC = stTPFVPara.u8StopSOC;
                }
                else if(stTPFVPara.u8TPFVStatus == TPFV_VALLEY)
                {
                    pEmsParam->u16EmsChgCutoffSOC = stTPFVPara.u8StopSOC;
                }
                else
                {
                    pEmsParam->s16EmsWatt = 6000;
                }

                pEmsParam->u16PeakValleyModeState = stTPFVPara.u8TPFVStatus;
            }
        break;
        /*定时充放电模式*/
        case STRATEGY_REGULAR:
            {
                EMS_Effective_ParaDef stTPFVPara = getEnergyRunParabyRegularMode(pStrategy, u32SystemSec);
                pEmsParam->s16EmsWatt = stTPFVPara.s16Power;//需要从电网设置数据取
                pEmsParam->s16EmsVar = pGrid->s16ReactPower;
                if(stTPFVPara.u8TPFVStatus == TPFV_PEAK)
                {
                    pEmsParam->u16EmsDisChgCutoffSOC = stTPFVPara.u8StopSOC;
                }
                else if(stTPFVPara.u8TPFVStatus == TPFV_VALLEY)
                {
                    pEmsParam->u16EmsChgCutoffSOC = stTPFVPara.u8StopSOC;
                }
                else
                {
                    pEmsParam->s16EmsWatt = 6000;
                }
                
                pEmsParam->u16PeakValleyModeState = stTPFVPara.u8TPFVStatus;
            }
            break;
        /*备电模式*/
        case STRATEGY_BACKUP:
            {
                pEmsParam->s16EmsWatt = pStrategy->stBackupStrategy.s16RatedPower;
                pEmsParam->s16EmsVar = 0;//无功发0
            }
            break;
        /*发电机模式*/
        case STRATEGY_GEN:
            {
                pEmsParam->u16EmsFbdGenChgSOC = pStrategy->stGenStrategy.u8ForbidSOC;
                pEmsParam->u16EmsSupplySOC = pStrategy->stGenStrategy.u8SupplySOC;
                pEmsParam->sGenRatedPower = pGenPara->stGenPara.u16RatedPower;
                pEmsParam->sGenMaxPower = pGenPara->stGenPara.u16MaxPower;
                pEmsParam->u16AILoadExitSOC = pGenPara->stIntelLoad.u8CutDrySOC;
                pEmsParam->u16AILoadEnterSOC = pGenPara->stIntelLoad.u8OnDrySOC;
                pEmsParam->u16DryContactEnFlag = pGenPara->u8DryNodeUse;
            }
            break;
        default:
            break;
    }
}

/***************************************************************************
 功能:远程控制运行函数
****************************************************************************/
static void RemoteControlEnergyRunning(EmsParam_t* pEmsParam)
{
    if(pEmsParam->u16EmsMethod == STRATEGY_NULL)
    {
        return;
    }

    switch(pEmsParam->u16EmsMethod)
    {
        case STRATEGY_OLD:  //老化模式
            {
                memset(pEmsParam,0,sizeof(EmsParam_t));
                pEmsParam->u16EmsMethod = STRATEGY_OLD;
                pEmsParam->s16EmsWatt = OLD_MODE_ACTIVE_POWER;
                pEmsParam->u16EmsMaxDisChgCurr = OLD_MODE_MAX_DISCHG_CURR;
                pEmsParam->u16EmsChgCutoffVolt = OLD_MODE_CHG_CUT_OFF_VOLT;
                pEmsParam->u16EmsDisChgCutoffVolt = OLD_MODE_DISCHG_CUT_OFF_VOLT;
                pEmsParam->u16EmsLiveSOC = OLD_MODE_LIVE_SOC;
                pEmsParam->u16EmsChgCutoffSOC = OLD_MODE_CHG_CUT_OFF_SOC;
                pEmsParam->u16EmsDisChgCutoffSOC = OLD_MODE_DISCHG_CUT_OFF_SOC;
                pEmsParam->u16PV1MaxPower = OLD_MODE_PV1_MAX_POWER;
                pEmsParam->u16PV2MaxPower = OLD_MODE_PV2_MAX_POWER;
            }
            break;
        default:
            break;
    }
}

/***************************************************************************
 功能:通用功能控制运行函数
****************************************************************************/
static void GenericControlRunning(EmsParam_t* pEmsParam)
{
    if(pEmsParam->u16DryContactEnFlag == GEN_USE_Gen)  //发电机
    {
        GenControlRunning(pEmsParam);
    }
    else if(pEmsParam->u16DryContactEnFlag == GEN_USE_IntelLoad)  //智能负载
    {
        AILoadControlRunning(pEmsParam);
    }
    else
    {
        pEmsParam->u16DryContactAccessFlag = DRYRLY_ACTION_VOILD;
    }
}

/***************************************************************************
功能:发电机功能控制运行函数
****************************************************************************/
static void GenControlRunning(EmsParam_t* pEmsParam)
{
    /*获取电网状态*/
    DisplayGenGridState_t stState;
    memset(&stState,0,sizeof(stState));
    GetDisplayGridGenState(&stState);

    /*实时SOC小于等于发电机启动SOC，启动发电机*/
    if(pEmsParam->u16EmsLiveSOC <= pEmsParam->u16EmsSupplySOC)
    {
        pEmsParam->u16DryContactAccessFlag = DRYRLY_ACTION_ACCESS;

        uint16_t u16GenActionStatus = GetGenRunState();
        if(u16GenActionStatus == DRYRLY_ACTION_ACCESS)
        {
            if(gbDryRly2FristFlag == STATUS_FALSE)
            {
                DRY_RLY2_DeviceCntrl(GENACTION_STARTUP);
                gbDryRly2FristFlag = STATUS_TRUE;
            }
            else
            {
                if((gbDrylay1Falseflag == STATUS_TRUE) && (gbDrylay1Trueflag == STATUS_TRUE))
                {
                    pEmsParam->u16GenStartFlag = DRYRLY_ACTION_ACCESS;
                }
                if(gbDrylay1Trueflag == STATUS_FALSE)
                {
                    if(gU8DryRly1SecondCounter == 3)
                    {
                        DRY_RLY1_DeviceCntrl(GENACTION_STARTUP);
                        gU8DryRly1SecondCounter = 0;
                        gbDrylay1Trueflag = STATUS_TRUE;
                    }
                    gU8DryRly1SecondCounter++;
                }
                else
                {
                    if(gU8DryRly2SecondCounter == 3)
                    {
                        DRY_RLY1_DeviceCntrl(GENACTION_CLOSE);
                        gU8DryRly2SecondCounter = 0;
                        gbDrylay1Falseflag = STATUS_TRUE;
                    }
                    gU8DryRly2SecondCounter++;
                }
            }
        }
        else if(u16GenActionStatus == DRYRLY_ACTION_VOILD)
        {
            DRY_RLY2_DeviceCntrl(GENACTION_CLOSE);
            pEmsParam->u16GenStartFlag = DRYRLY_ACTION_VOILD;
            gbDryRly2FristFlag = STATUS_FALSE;
            gbDrylay1Trueflag = STATUS_FALSE;
            gbDrylay1Falseflag = STATUS_FALSE;
            gU8DryRly1SecondCounter = 0;
            gU8DryRly2SecondCounter = 0;
        }
    }
    /*有市电或者实时SOC大于等于发电机停止SOC，关闭发电机*/
    else if(pEmsParam->u16EmsLiveSOC >= pEmsParam->u16EmsFbdGenChgSOC)
    {
        pEmsParam->u16DryContactAccessFlag = DRYRLY_ACTION_EXIT;
    }

    /*任意情况下，接收到关闭发电机的标志位后关闭发电机*/
    uint16_t u16GenActionStatus = GetGenRunState();
    if(u16GenActionStatus == DRYRLY_ACTION_EXIT)
    {
        DRY_RLY2_DeviceCntrl(GENACTION_CLOSE);
        pEmsParam->u16GenStartFlag = DRYRLY_ACTION_EXIT;
        gbDryRly2FristFlag = STATUS_FALSE;
        gbDrylay1Trueflag = STATUS_FALSE;
        gbDrylay1Falseflag = STATUS_FALSE;
        gU8DryRly1SecondCounter = 0;
        gU8DryRly2SecondCounter = 0;
    }
}

/***************************************************************************
功能:智能负载功能控制运行函数
****************************************************************************/
static void AILoadControlRunning(EmsParam_t* pEmsParam)
{
    if(pEmsParam->u16EmsLiveSOC >= pEmsParam->u16AILoadEnterSOC)
    {
        pEmsParam->u16DryContactAccessFlag = DRYRLY_ACTION_ACCESS;  //接入
    }
    else if(pEmsParam->u16EmsLiveSOC <= pEmsParam->u16AILoadExitSOC)
    {
        pEmsParam->u16DryContactAccessFlag = DRYRLY_ACTION_EXIT;  //退出
    }
}

/***************************************************************************
功能:清楚发电机控制标志位
****************************************************************************/
static void ClearGenControlFlag()
{
    TimeInf_t tab_SysTime;
    memset(&tab_SysTime, 0, sizeof(TimeInf_t));
    Get_SysTime(&tab_SysTime);

    /*年数据清零*/
    if((tab_SysTime.u8Hour == 23) && (tab_SysTime.u8Min == 59) && (tab_SysTime.u8Sec > 58))
    {

         gbDryRly2FristFlag = STATUS_FALSE;
         gU8DryRly1SecondCounter = 0;
         gU8DryRly2SecondCounter = 0;
         gU8StartUpSecondCounter = 0;
         gbDrylay1Trueflag  = STATUS_FALSE;
         gbDrylay1Falseflag = STATUS_FALSE;
    }
}

#endif
#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
