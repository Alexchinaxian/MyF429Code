/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Indication_Management_Service.h 
 用途 : 指示灯、蜂鸣器管理头文件
***********************************************************************************************************************/
#ifndef _INDICATION_MANAGEMENT_H_
#define _INDICATION_MANAGEMENT_H_

#include "HeadFile.h"

#define INDICATION_ALAWAYON_ENABLE   (1)                    //指示灯常亮使能
#define INDICATION_ALAWAYON_FORBID   (0)                    //指示灯常亮禁止
#define INDICATION_ALAWAYOFF_ENABLE  (1)                    //指示灯常灭使能
#define INDICATION_ALAWAYOFF_FORBID  (0)                    //指示灯常灭禁止
#define INDICATION_FLASH_ENABLE      (1)                    //指示灯闪烁使能
#define INDICATION_FLASH_FORBID      (0)                    //指示灯闪烁禁止

#define INDICATION_QUICK_PERIOD      (4)                    //指示灯快闪周期时间
#define INDICATION_QUICK_DUTY        (2)                    //指示灯快闪占空时间
#define INDICATION_SLOW_PERIOD       (20)                   //指示灯慢闪周期时间
#define INDICATION_SLOW_DUTY         (10)                   //指示灯慢闪占空时间

#define BIT_SET                      (1)                    //标志位置位1
#define BIT_RESET                    (0)                    //标志位复位0


typedef enum
{
    INDICATION_INIT,                                        //指示灯、蜂鸣器管理模块初始化
    INDICATION_RUNNING,                                     //指示灯、蜂鸣器管理模块运行
    INDICATION_DESTRCUCTION,                                //指示灯、蜂鸣器管理模块析构
    INDICATION_STATE_NULL 
}IndicationStatus_TypeDef;

typedef enum
{
    INDICATION_AKWAY_ON,                                    //常亮
    INDICATION_QUICK_FLASH,                                 //快闪
    INDICATION_SLOW_FLASH,                                  //慢闪
    INDICATION_AKWAY_OFF                                    //常灭
}IndicationStatus_Def;

typedef enum
{
    INDICATION_GEN,                                         //发电机灯，黄色
    INDICATION_GRID,                                        //电网灯，绿色
    INDICATION_FAULT                                        //故障灯，红色
}IndicationColour_Def;

typedef enum
{
    GRID_INDICATION_NONE,                                   //无
    GRID_INDICATION_ONGRID,                                 //并网
    GRID_INDICATION_OFFGRID,                                //离网
    GRID_INDICATION_POWEROFFGRID,                           //有市电未上网
    GRID_INDICATION_STATE_UBVERSUIBOFF                      //逆变关闭
}GridIndicationStatus_TypeDef;

typedef enum
{
    GEN_INDICATION_NONE,                                    //无
    GEN_INDICATION_RUN,                                     //发电机运行
    GEN_INDICATION_AILOAD,                                  //智能负载运行
    GEN_INDICATION_DETECTED,                                //检测到发电机
    GEN_INDICATION_NODETECTED,                              //未检测到发电机
}GENIndicationStatus_TypeDef;

typedef enum
{
    FAULT_INDICATION_NONE,                                  //无
    FAULT_INDICATION_NORMAL,                                //正常
    FAULT_INDICATION_ALARM,                                 //告警
    FAULT_INDICATION_FAULT,                                 //故障
}FAULTIndicationStatus_TypeDef;

//LCD屏电池BMS参数设置结构体
typedef struct {
    GridIndicationStatus_TypeDef  u8GridStatus;             //电网状态 
    GENIndicationStatus_TypeDef   u8GenStatus;              //发电机状态
    FAULTIndicationStatus_TypeDef u8FaultStatus;            //故障告警状态 
}IndicationStatus;

typedef struct
{
    uint16_t u16InvRunState;
}DisplayInvRunState_t;

typedef union
{
    uint16_t u16Word;
    struct
    {
        uint16_t bOnGridRun              : 1;               //BIT0 并网运行
        uint16_t bOffGridRun             : 1;               //BIT1 离网运行
        uint16_t bGridNoPar              : 1;               //BIT2 有市电未并网
        uint16_t bInvClosed              : 1;               //BIT3 逆变关闭
        uint16_t bReserved1              : 1;               //BIT4 预留
        uint16_t bReserved2              : 1;               //BIT5 预留
        uint16_t bReserved3              : 1;               //BIT6 预留
        uint16_t bReserved4              : 1;               //BIT7 预留
        uint16_t bGenRun                 : 1;               //BIT8 发电机运行
        uint16_t bAILoadRun              : 1;               //BIT9 智能负载运行
        uint16_t bGenDetected            : 1;               //BIT10 检测到发电机
        uint16_t bNoGenDetected          : 1;               //BIT11 未检测到发电机
        uint16_t bReserved7              : 1;               //BIT12 预留
        uint16_t bReserved8              : 1;               //BIT13 预留
        uint16_t bReserved9              : 1;               //BIT14 预留
        uint16_t bReserved10             : 1;               //BIT15 预留
    }Bits;
}DisplayGenGridState_t;

//指示灯、蜂鸣器管理处理总入口函数,给main模块存储模块总接口函数
extern void IndicationManagement_Handler(void);
//初始化变量函数
extern void Indication_Service_InitVar(void);
//硬件初始化函数
extern void Indication_Service_HwInit(void);
//指示灯、蜂鸣器管理模块析构
extern void Indication_Service_DestructionVar(void); 

#endif

/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
