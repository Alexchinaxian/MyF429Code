/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Indication_Management_Service.c 
 用途 : 指示灯、蜂鸣器管理服务
***********************************************************************************************************************/
#ifndef _INDICATION_MANAGEMENT_C_
#define _INDICATION_MANAGEMENT_C_

#include "HeadFile.h"
#include "Buzzer_Device.h"
#include "Modbus_PCS_COMData.h"
#include "Indication_Management_Service.h"

#if INDICATION_SERVICE_MOUDLE

/*指示灯、蜂鸣器管理模块状态*/
static IndicationStatus_TypeDef gEnumIndicationStatus = INDICATION_STATE_NULL;

//Indication管理总初始化函数
static void IndicationInit(void);
//Indication管理总运行函数
static void IndicationRunning(void);
//Indication管理析构函数
static void IndicationDestruction(void);
//Indication获取指示灯状态函数
static void getIndicationStatus(IndicationStatus *pIndicationStatus);
//电网指示灯点灯逻辑
static void IndicationLightLogic(IndicationStatus_Def u8LightType,IndicationColour_Def u8LightColour);

void IndicationManagement_Handler(void)
{
    if ((STATUS_FALSE == TimeTask_GetFlag_100ms) || (LCD_ATE_TEST))
    {
        return;
    }

    switch (gEnumIndicationStatus)
    {
        case INDICATION_INIT://指示灯、蜂鸣器管理模块初始化
            {
                IndicationInit();
                gEnumIndicationStatus = INDICATION_RUNNING;
            }
            break;
        case INDICATION_RUNNING://指示灯、蜂鸣器管理模块运行
            {
                IndicationRunning();
            }
            break;
        case INDICATION_DESTRCUCTION://指示灯、蜂鸣器管理模块析构,用掉电检测村塾
            {
                IndicationDestruction();
            }
            break;
        default:
            break;
    }
}

/***********************************************************************************************************************
 功能：指示灯、蜂鸣器管理模块全局变量初始化
***********************************************************************************************************************/
void Indication_Service_InitVar(void)
{
    gEnumIndicationStatus = INDICATION_INIT;
}

/***********************************************************************************************************************
 功能：指示灯、蜂鸣器管理模块析构
***********************************************************************************************************************/
void Indication_Service_DestructionVar(void)
{
    IndicationDestruction();
    gEnumIndicationStatus = INDICATION_DESTRCUCTION;  
}

/***********************************************************************************************************************
 功能：指示灯、蜂鸣器管理模块硬件初始化
***********************************************************************************************************************/
void Indication_Service_HwInit(void)
{

}

/***************************************************************************
 功能:初始化驱动，全局变量等
****************************************************************************/
void IndicationInit(void)
{

}

/***************************************************************************
 功能:指示灯、蜂鸣器管理总运行函数
****************************************************************************/
static void IndicationRunning(void)
{
    /*预留获取发电机、电网、故障告警状态接口*/
    IndicationStatus stIndicationStatus;
    memset(&stIndicationStatus,0,sizeof(IndicationStatus));
    getIndicationStatus(&stIndicationStatus);

    /*发电机*/
    if(stIndicationStatus.u8GenStatus == GEN_INDICATION_RUN)
    {
        IndicationLightLogic(INDICATION_AKWAY_ON,INDICATION_GEN);
    }
    else if(stIndicationStatus.u8GenStatus == GEN_INDICATION_AILOAD)
    {
        IndicationLightLogic(INDICATION_QUICK_FLASH,INDICATION_GEN);
    }
    else if(stIndicationStatus.u8GenStatus == GEN_INDICATION_DETECTED)
    {
        IndicationLightLogic(INDICATION_SLOW_FLASH,INDICATION_GEN);
    }
    else if(stIndicationStatus.u8GenStatus == GEN_INDICATION_NODETECTED)
    {
        IndicationLightLogic(INDICATION_AKWAY_OFF,INDICATION_GEN);
    }
    
    /*电网*/
    if(stIndicationStatus.u8GridStatus == GRID_INDICATION_ONGRID)
    {
        IndicationLightLogic(INDICATION_AKWAY_ON,INDICATION_GRID);
    }
    else if(stIndicationStatus.u8GridStatus == GRID_INDICATION_OFFGRID)
    {
        IndicationLightLogic(INDICATION_QUICK_FLASH,INDICATION_GRID);
    }
    else if(stIndicationStatus.u8GridStatus == GRID_INDICATION_POWEROFFGRID)
    {
        IndicationLightLogic(INDICATION_SLOW_FLASH,INDICATION_GRID);
    }
    else if(stIndicationStatus.u8GridStatus == GRID_INDICATION_STATE_UBVERSUIBOFF)
    {
        IndicationLightLogic(INDICATION_AKWAY_OFF,INDICATION_GRID);
    }
    
     /*故障告警*/
    if(stIndicationStatus.u8FaultStatus == FAULT_INDICATION_FAULT)
    {
        IndicationLightLogic(INDICATION_AKWAY_ON,INDICATION_FAULT);
    }
    else if(stIndicationStatus.u8FaultStatus == FAULT_INDICATION_ALARM)
    {
        IndicationLightLogic(INDICATION_SLOW_FLASH,INDICATION_FAULT);
    }
    else if(stIndicationStatus.u8FaultStatus == FAULT_INDICATION_NORMAL)
    {
        IndicationLightLogic(INDICATION_AKWAY_OFF,INDICATION_FAULT);
    }
    
}

/***************************************************************************
 功能:指示灯、蜂鸣器管理析构函数，用于掉电触发保护逻辑
****************************************************************************/
static void IndicationDestruction(void)
{

}

/***************************************************************************
 功能:电网指示灯点灯逻辑
****************************************************************************/
static void IndicationLightLogic(IndicationStatus_Def u8LightType,IndicationColour_Def u8LightColour)                //形参1行为，形参2对象
{   
    switch (u8LightType)
    {
        case INDICATION_AKWAY_ON://常亮
            {
                if(u8LightColour == INDICATION_GEN)
                {
                    LED_Device_GenCntrl(INDICATION_ALAWAYON_ENABLE,INDICATION_ALAWAYOFF_FORBID,INDICATION_FLASH_FORBID,0,0); 
                }
                else if(u8LightColour == INDICATION_GRID)
                {
                   LED_Device_GridCntrl(INDICATION_ALAWAYON_ENABLE,INDICATION_ALAWAYOFF_FORBID,INDICATION_FLASH_FORBID,0,0); 
                }
                else if(u8LightColour == INDICATION_FAULT)
                {
                   LED_Device_FaultCntrl(INDICATION_ALAWAYON_ENABLE,INDICATION_ALAWAYOFF_FORBID,INDICATION_FLASH_FORBID,0,0); 
                }  
            }
            break;
        case INDICATION_QUICK_FLASH://快闪 0.2s 亮 0.2s 灭
            {
                if(u8LightColour == INDICATION_GEN)
                {
                    LED_Device_GenCntrl(INDICATION_ALAWAYON_FORBID,INDICATION_ALAWAYOFF_FORBID,INDICATION_FLASH_ENABLE,INDICATION_QUICK_DUTY,INDICATION_QUICK_PERIOD);
                }
                else if(u8LightColour == INDICATION_GRID)
                {
                    LED_Device_GridCntrl(INDICATION_ALAWAYON_FORBID,INDICATION_ALAWAYOFF_FORBID,INDICATION_FLASH_ENABLE,INDICATION_QUICK_DUTY,INDICATION_QUICK_PERIOD); 
                }
                else if(u8LightColour == INDICATION_FAULT)
                {
                    LED_Device_FaultCntrl(INDICATION_ALAWAYON_FORBID,INDICATION_ALAWAYOFF_FORBID,INDICATION_FLASH_ENABLE,INDICATION_QUICK_DUTY,INDICATION_QUICK_PERIOD); 
                } 
            } 
            break;
        case INDICATION_SLOW_FLASH://慢闪 1s 亮 1s 灭
            {
                if(u8LightColour == INDICATION_GEN)
                {
                    LED_Device_GenCntrl(INDICATION_ALAWAYON_FORBID,INDICATION_ALAWAYOFF_FORBID,INDICATION_FLASH_ENABLE,INDICATION_SLOW_DUTY,INDICATION_SLOW_PERIOD);
                }
                else if(u8LightColour == INDICATION_GRID)
                {
                    LED_Device_GridCntrl(INDICATION_ALAWAYON_FORBID,INDICATION_ALAWAYOFF_FORBID,INDICATION_FLASH_ENABLE,INDICATION_SLOW_DUTY,INDICATION_SLOW_PERIOD); 
                }
                else if(u8LightColour == INDICATION_FAULT)
                {
                    LED_Device_FaultCntrl(INDICATION_ALAWAYON_FORBID,INDICATION_ALAWAYOFF_FORBID,INDICATION_FLASH_ENABLE,INDICATION_SLOW_DUTY,INDICATION_SLOW_PERIOD); 
                } 
            }
            break;
        case INDICATION_AKWAY_OFF://常灭
            {
                if(u8LightColour == INDICATION_GEN)
                {
                     LED_Device_GenCntrl(INDICATION_ALAWAYON_FORBID,INDICATION_ALAWAYOFF_ENABLE,INDICATION_FLASH_FORBID,0,0);
                }
                else if(u8LightColour == INDICATION_GRID)
                {
                    LED_Device_GridCntrl(INDICATION_ALAWAYON_FORBID,INDICATION_ALAWAYOFF_ENABLE,INDICATION_FLASH_FORBID,0,0); 
                }
                else if(u8LightColour == INDICATION_FAULT)
                {
                    LED_Device_FaultCntrl(INDICATION_ALAWAYON_FORBID,INDICATION_ALAWAYOFF_ENABLE,INDICATION_FLASH_FORBID,0,0); 
                } 
            }
            break;
        default:
            break;
    }
}

/***********************************************************************************************************************
 功能：根据通信提供的接口转成对应的状态显示
************************************************************************************************************************/
static void getIndicationStatus(IndicationStatus *pIndicationStatus)
{
    Display_Fault_t ptDisplayFault;
    memset(&ptDisplayFault ,0, sizeof(ptDisplayFault));
      
    DisplayGenGridState_t stState;
    memset(&stState,0,sizeof(stState));
    GetDisplayGridGenState(&stState);

    /*并网运行状态*/
    if(stState.Bits.bOnGridRun == BIT_SET)
    {
        pIndicationStatus->u8GridStatus = GRID_INDICATION_ONGRID;
    }
    else if(stState.Bits.bOffGridRun == BIT_SET)
    {
        pIndicationStatus->u8GridStatus = GRID_INDICATION_OFFGRID;
    }
    else if(stState.Bits.bGridNoPar == BIT_SET)
    {
        pIndicationStatus->u8GridStatus = GRID_INDICATION_POWEROFFGRID;
    }
    else if(stState.Bits.bInvClosed == BIT_SET)
    {
        pIndicationStatus->u8GridStatus = GRID_INDICATION_STATE_UBVERSUIBOFF;
    }

    //发电机运行状态
    if(stState.Bits.bGenRun == BIT_SET)
    {
        pIndicationStatus->u8GenStatus = GEN_INDICATION_RUN;
    }
    else if(stState.Bits.bAILoadRun == BIT_SET)
    {
        pIndicationStatus->u8GenStatus = GEN_INDICATION_AILOAD;
    }
    else if(stState.Bits.bGenDetected == BIT_SET)
    {
        pIndicationStatus->u8GenStatus = GEN_INDICATION_DETECTED;
    }
    else if(stState.Bits.bNoGenDetected == BIT_SET)
    {
        pIndicationStatus->u8GenStatus = GEN_INDICATION_NODETECTED;
    }

    //逆变器运行状态
    GetDisplayDeviceFaultState(&ptDisplayFault);
    
    if(ptDisplayFault.eDeviceFault == DEVICESTATE_FAULT)
    { 
       pIndicationStatus->u8FaultStatus = FAULT_INDICATION_FAULT;
    } 
    else if(ptDisplayFault.eDeviceFault == DEVICESTATE_ALARM)
    {
        pIndicationStatus->u8FaultStatus = FAULT_INDICATION_ALARM;
    }
    else
    {
        pIndicationStatus->u8FaultStatus = FAULT_INDICATION_NORMAL;
    }
}

#endif
#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
