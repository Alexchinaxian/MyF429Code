/***********************************************************************************************************************
* Copyright (c)  , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
* 文件名        : iGlobalVar.h
* 用途         : 全局变量处理头文件
***********************************************************************************************************************/
#ifndef __GLOBALVAR_H_
#define __GLOBALVAR_H_

#include "HeadFile.h"

#define MODULE_GLOBAL_VAR       (1)
#if MODULE_GLOBAL_VAR

/***********************************************************************************************************************
* * Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
* * Enum definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
* * Typedef struct
***********************************************************************************************************************/

typedef struct
{
    uint32_t u32McuIdHighWord;
    uint32_t u32McuIdLowWord;
} ModelMessage_t;

typedef struct
{
    uint8_t u8CommunicationCanOrder;
} SysConfig_t;


typedef struct
{
    int16_t s16MaxSinPoint;                                  // 正弦索引最大值
    int16_t s16SinPointCount;                                // 当前正弦索引

    int16_t s16LineVoltageAlphaAxisValue;                    // Alpha轴线电压（Clark变换）
    int16_t s16LineVoltageBetaAxisValue;                     // Beta轴线电压（Clark变换）

    int16_t s16PowerFrequency;                               // 市电频率
    int16_t s16PowerPhase;                                   // 市电相位
} PowerPhaseVar_t;

typedef struct
{
    int16_t s16InvertCurrentAverage[PARALLEL_MAX_NUM];
    int16_t s16CarrierPhase[PARALLEL_MAX_NUM];
    int16_t s16InvertVoltageTrackValue[PARALLEL_MAX_NUM];

    union
    {
        uint16_t Word;
        struct
        {
            uint16_t Reserved: 16;
        } Bit;
    } SyncStatus[PARALLEL_MAX_NUM];

    uint32_t u32McuIdHigh[PARALLEL_MAX_NUM];
    uint32_t u32McuIdLow[PARALLEL_MAX_NUM];

    int16_t s16BatVoltage[PARALLEL_MAX_NUM];
    int16_t s16BatCurrent[PARALLEL_MAX_NUM];
    int16_t s16PvChargeCurrent[PARALLEL_MAX_NUM];
    int16_t s16LineVoltage[PARALLEL_MAX_NUM];

    int16_t s16LineFrequency[PARALLEL_MAX_NUM];
    int16_t s16PvVoltage[PARALLEL_MAX_NUM];
    int16_t s16PvCurrent[PARALLEL_MAX_NUM];
    int16_t s16PvPower[PARALLEL_MAX_NUM];

    int16_t s16OutputVoltage[PARALLEL_MAX_NUM];
    int16_t s16OutputCurrent[PARALLEL_MAX_NUM];
    int16_t s16OutputFrequency[PARALLEL_MAX_NUM];
    int16_t s16OutputWatt[PARALLEL_MAX_NUM];

    int16_t s16OutputVa[PARALLEL_MAX_NUM];
    int16_t s16OutputPowerRatio[PARALLEL_MAX_NUM];
    int16_t s16PvTemperature[PARALLEL_MAX_NUM];
    int16_t s16ChargerTemperature[PARALLEL_MAX_NUM];

    int16_t s16PvCollectPowerToday[PARALLEL_MAX_NUM];
    int16_t s16OutputCollectPowerToday[PARALLEL_MAX_NUM];

    int32_t s32PvCollectPowerTotal[PARALLEL_MAX_NUM];
    int32_t s32OutputCollectPowerTotal[PARALLEL_MAX_NUM];

    int16_t s16BmsBatVoltage[PARALLEL_MAX_NUM];
    int16_t s16BmsBatCurrent[PARALLEL_MAX_NUM];
    int16_t s16BmsBatTemperature[PARALLEL_MAX_NUM];
    int16_t s16BmsBatSoc[PARALLEL_MAX_NUM];

    int16_t s16BmsBatRatedCapacity[PARALLEL_MAX_NUM];
    int16_t s16BmsBatRealCapacity[PARALLEL_MAX_NUM];
    int16_t s16BmsConstantChargeVoltage[PARALLEL_MAX_NUM];
    int16_t s16BmsMaxChargeCurrent[PARALLEL_MAX_NUM];

    uint32_t u32BmsWarning[PARALLEL_MAX_NUM];
    uint32_t u32BmsError[PARALLEL_MAX_NUM];

    uint16_t u16BmsStatus[PARALLEL_MAX_NUM];
    uint8_t u8SystemBmsDataOrder;
} ParallelSyncVar_t;

typedef union
{
    uint16_t Word;
    struct
    {
        uint16_t InvDriverOn             : 1;      //逆变驱动开关
        uint16_t PfcDriverOn             : 1;      //PFC驱动开关
        uint16_t PvDriverOn              : 1;      //光伏驱动开关
        uint16_t DischargeDriverOn       : 1;      //LLC驱动关

        uint16_t ChargeDriverOn          : 1;      //LLC驱动开
        uint16_t LiveRelayDriverOn       : 1;      //？？不是很明白为什么这样定义继电器
        uint16_t NeutralRelayDriverOn    : 1;      //？？不是很明白为什么这样定义继电器
        uint16_t OutputRelayDriverOn     : 1;      //？？不是很明白为什么这样定义继电器

        uint16_t LiveScrDriverOn         : 1;      //这个变量的应用范围说明？？
        uint16_t OutputScrDriverOn       : 1;      //这个变量的应用范围说明？？
        uint16_t Reserved                : 6;
    } Bit;
} PowerStageDriverStatus_t;

/***********************************************************************************************************************
 * * Extern variables
***********************************************************************************************************************/
extern SysConfig_t gtSysConfig;
extern volatile ParallelSyncVar_t gtParallelSyncVar;
extern ModelMessage_t gtModelMessage;
extern volatile PowerPhaseVar_t gtPowerPhaseVar;
extern volatile PowerStageDriverStatus_t gtPowerStageDriverStatus;

/***********************************************************************************************************************
 * Extern functions
***********************************************************************************************************************/
extern void GlobalVar_InitVar(void);
extern void GlobalVar_InitModules(void);

#endif
#endif /***Module End***/
/***********************************************************************************************************************
* * Copyright (c)  CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
