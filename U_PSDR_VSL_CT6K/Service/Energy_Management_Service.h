/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Energy_Management_Service.h 
 用途 : 能量管理头文件
***********************************************************************************************************************/
#ifndef _ENERGY_MANAGEMENT_H_
#define _ENERGY_MANAGEMENT_H_

#include "HeadFile.h"
#include "LCD_Service.h"
#include "RTC_Service.h"
#include "Modbus_PCS_COMData.h"

#define OLD_MODE_ACTIVE_POWER                                            (6000) //老化模式有功功率值
#define OLD_MODE_MAX_DISCHG_CURR                                         ( 500) //老化模式最大放电电流值
#define OLD_MODE_CHG_CUT_OFF_VOLT                                        ( 592) //老化模式电池充电截止电压值
#define OLD_MODE_DISCHG_CUT_OFF_VOLT                                     ( 432) //老化模式电池放电截止电压值
#define OLD_MODE_LIVE_SOC                                                ( 500) //老化模式实时SOC值
#define OLD_MODE_CHG_CUT_OFF_SOC                                         ( 800) //老化模式电池充电截止SOC值
#define OLD_MODE_DISCHG_CUT_OFF_SOC                                      ( 200) //老化模式电池放电截止SOC值
#define OLD_MODE_PV1_MAX_POWER                                           (2000) //老化模式PV1最大功率值
#define OLD_MODE_PV2_MAX_POWER                                           (2000) //老化模式PV2最大功率值

typedef enum
{
    ENERGY_INIT,          //能量管理模块初始化
    ENERGY_RUNNING,       //能量管理模块运行
    ENERGY_DESTRCUCTION,  //能量管理模块析构
    ENERGY_STATE_NULL 
}EnergyStatus_TypeDef;

typedef struct
{
    uint8_t u8TPFVStatus;     //峰谷模式状态
    uint8_t u8StopSOC;       //停止SOC
    int16_t s16Power;        //充放电功率
}EMS_Effective_ParaDef;

typedef enum
{
    DRYRLY_ACTION_VOILD,    //无效
    DRYRLY_ACTION_ACCESS,   //接入
    DRYRLY_ACTION_EXIT      //退出
}DryRly_Action_TypeDef;

typedef enum
{
    GENACTION_INIT,          //发电机无动作
    GENACTION_STARTUP,       //发电机启动
    GENACTION_CLOSE,         //发电机关闭
}GenAction_TypeDef;

//通用功能控制运行函数
static void GenericControlRunning(EmsParam_t* pEmsParam);
//本地控制Energy管理函数
static void LocalControlEnergyRunning(EmsParam_t* pEmsParam,  Display_EnableDetection_Status stEnableDetection);
//远程控制Energy管理函数
static void RemoteControlEnergyRunning(EmsParam_t* pEmsParam);
//发电机控制运行函数
static void GenControlRunning(EmsParam_t* pEmsParam);
//智能控制运行函数
static void AILoadControlRunning(EmsParam_t* pEmsParam);
//清楚发电机控制标志位
static void ClearGenControlFlag(void);
//Energy管理总初始化函数
static void EnergyInit(void);
//Energy管理总运行函数
static void EnergyRunning(void);
//Energy管理析构函数
static void EnergyDestruction(void);
//
static EMS_Effective_ParaDef getEnergyRunParabyTPFVMode(Display_SET_System_Strategy* pStrategy, int32_t u32SystemSec);
//
static EMS_Effective_ParaDef getEnergyRunParabyRegularMode(Display_SET_System_Strategy* pStrategy, int32_t u32SystemSec);

//能量管理处理总入口函数,给main模块存储模块总接口函数
extern void EnergyManagement_Handler(void);
//初始化变量函数
extern void Energy_Service_InitVar(void);
//初始化变量函数
extern void Energy_Service_HwInit(void);

#endif

/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
