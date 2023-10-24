/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Battery_Protect_Service.h
 用途 : 电池保护头文件
***********************************************************************************************************************/
#ifndef _BATTERY_PROTECT_H_
#define _BATTERY_PROTECT_H_

#include "HeadFile.h"
#include "LCD_Service.h"
#include "RTC_Service.h"

#define SOC_RETURNDIFFERENCE                (5)                                //回差SOC
#define SOC_REPAIR                          (50)                               //修复SOC
#define COULOMBICEFFICIENCY                 (1)                                //假定昆仑效率为1
#define CLOSETOZERO                         (10)                               //电池电流小于1A，认为趋向0
#define RECOVERTIME                         (900)                              //电池由运行恢复到静置时间，默认15min

#define ArrayMax                            (50)                               //数字滤波器最大容量
#define MIN(x , y)						     x >= y ? y : x
#define MAX(x , y)						     x >= y ? x : y

typedef enum
{
    STOP    = 0,
    RUNNING = 1
} ChgOrDisChgState_t;

typedef enum
{
    BATTERY_OK = 0,
    BATTERY_ERROR  = 1
} BATTERY_STATE_t;

typedef enum
{
    BATTERY_INIT,          //电池保护模块初始化
    BATTERY_RUNNING,       //电池保护模块运行
    BATTERY_DESTRCUCTION,  //电池保护模块析构
    BATTERY_STATE_NULL
} BatteryStatus_TypeDef;

typedef enum
{
    STATIC_STATE,                       //静置
    RUNNING_STATE,                      //充/放电运行
    RECOVER_STATE,                      //恢复
}LeadBattery_State_TypeDef;             //铅酸电池状态机

typedef enum
{
    CONSTANTCURRENT_STAGE,              //恒流阶段
    CONSTANTVOLTAGE_STAGE,              //恒压阶段
    FLOATINGCHARGE_STAGE,               //浮充阶段
}LeadBattery_ChargeStage_TypeDef;       //铅酸电池充电步骤   

typedef struct
{
    uint16_t u16LimitVoltage;               //铅酸电池限压     
    int16_t s16LimitCurrentFactor;          //铅酸电池限流乘数 
}LeadBattery_ChargeState_Value_TypeDef;     //铅酸电池阶段值  

typedef struct
{
    uint8_t  u8NominalCapacity;                                 //额定容量
    uint16_t u16ActualCapacity;                                 //实际最大容量,扩大100倍
    int32_t  s32CapacityIntegral;                               //安时积分值,扩大3600*10倍
    uint8_t  u8StartSOC;                                        //起始SOC
    uint8_t  u8EndSOC;                                          //结束SOC
    uint8_t  u8SOCStaticDifference;                             //SOC差值
    uint8_t  u8NowSOC;                                          //当前SOC
    uint8_t  u8LastSOH;                                         //上次SOH
    uint8_t  u8NowSOH;                                          //当前SOH
    uint16_t u16RecoverTime;                                    //恢复时间
    LeadBattery_State_TypeDef eLeadBattery_LastState;           //铅酸电池上次运行状态
    LeadBattery_State_TypeDef eLeadBattery_State;               //铅酸电池当前运行状态
    LeadBattery_ChargeStage_TypeDef eChargeStage;               //铅酸电池充电阶段
}LeadBattery_Paras_TypeDef;                                     //铅酸电池参数 

typedef struct
{   
    int16_t  s16CurrentRange;             //铅酸电池放电范围
    uint16_t u16LimitVoltage;             //铅酸电池放电限压
}LeadBattery_DisCharge_Value_TypeDef;     //铅酸电池放电值 

typedef struct
{
    uint16_t u16BatVolt;                     //电池电压
    int16_t  s16ChgCurr;                     //电池充放电电流
    int16_t  s16BatPower;                    //电池功率
    uint16_t u16BatState;                     //电池状态
}BatteryCorePara_TypeDef;                    //PCS上报的电池核心参数

typedef struct
{
    uint8_t u8LowSOC_Count;                  //低电量标志
    TimeInf_t tCompleteRepairTime;           //完成修复时间
    uint32_t u32CompleteRepairTimestamp;     //完成修复时间戳
} WeakBattery_ParaDef;

typedef struct
{
    uint16_t u16MaxChargeVoltage;            //电池最大充电电压
    int16_t s16MaxChargeCurrent;             //电池最大充电电流
    uint16_t u16MaxDisChargeVoltage;         //电池最大放电电压
    int16_t s16MaxDisChargeCurrent;          //电池最大放电电流
    uint16_t u16BMSVoltage;                  //电池电压
    uint16_t u16BMSSOC;                      //BMS上传SOC
    uint8_t u8NowSOC;                        //当前SOC
    uint8_t u8ChargeStopSOC;                 //充电停止SOC
    uint8_t u8ChargeLimitSOC;                //充电限制SOC
    uint8_t u8DisChargeLimitSOC;             //放电限制SOC
    uint8_t u8DisChargeStopSOC;              //放电停止SOC
    ChgOrDisChgState_t  eChargeState;        //充电运行状态
    ChgOrDisChgState_t  eDisChargeState;     //放电运行状态
    WeakBattery_ParaDef WeakBatteryPara[2];  //电池保护参数
    BATTERY_STATE_t eWeakBatteryFault;       //弱电池故障标志
} Battery_Protect_Para_t;

extern uint8_t u8BatteryType;
extern Battery_Protect_Para_t Battery_Protect_Para;

//电池保护处理总入口函数,给main模块存储模块总接口函数
extern void BatteryProtect_Handler(void);
//初始化变量函数
extern void Battery_Service_InitVar(void);
//初始化变量函数
extern void Battery_Service_HwInit(void);
//获取BMS保护参数
extern void GetBMSProtectParam(Battery_Protect_Para_t* pBattery_Protect_Para);
//获取铅酸电池显示参数
extern void GetDisplayRealTimeLeadBatteryData(Display_DATA_BMS* ptDisplayBmsData);
//平均值数字滤波器
extern int16_t CalculateAverageFilterValue(int16_t s16value);
#endif

/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
