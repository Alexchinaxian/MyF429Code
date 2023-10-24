/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Fault_Management_Service.h 
 用途 : 故障告警管理头文件
***********************************************************************************************************************/
#ifndef _FAULT_MANAGEMENT_H_
#define _FAULT_MANAGEMENT_H_

#include "HeadFile.h"
#pragma pack(1)
#define DISPLAY_DATA_FAULT_REAL_MAX_COUNT        (20)        //实时故障告警显示最大条数
#define DISPLAY_DATA_FAULT_HISTORY_MAX_COUNT     (80)        //故障告警显示最大条数
#define DISPLAY_DATA_ORRECORD_MAX_COUNT          (50)        //操作记录显示最大条数
#define BIT_SET                                  (1)         //标志位置位1
#define BIT_RESET                                (0)         //标志位复位0
#define CLEARED                                  (0xAA)      //已清除
#define NOT_CLEARED                              (0x55)      //未清除

typedef enum
{
    FAULT_INIT,                                              //能量管理模块初始化
    FAULT_RUNNING,                                           //能量管理模块运行
    FAULT_DESTRCUCTION,                                      //能量管理模块析构
    FAULT_STATE_NULL 
}FaultStatus_TypeDef;

//LCD屏修改时间参数设置结构体
typedef struct {
    uint16_t u16Year;                                        //年
    uint8_t  u8Month;                                        //月
    uint8_t  u8Day;                                          //日
    uint8_t  u8Hour;                                         //时
    uint8_t  u8Min;                                          //分
    uint8_t  u8Sec;                                          //秒
    uint16_t u16mSec;                                        //毫秒
}Fault_System_TimeSync;

typedef struct
{
    uint8_t   u8No;                          //序号
    uint16_t  u16FaultCode;                  //故障类型
    uint8_t   u8FaultLevel;                  //故障等级
    uint8_t   u8FaultObj;                    //故障对象
    uint8_t   u8FaultState;                  //故障状态
    Fault_System_TimeSync stOccurTime;       //故障产生时间
    Fault_System_TimeSync stClearTime;       //故障产生时间
}Display_Fault_Info;

typedef struct
{
    uint8_t u8RealFaultIndex;
    Display_Fault_Info stRealFault[DISPLAY_DATA_FAULT_REAL_MAX_COUNT];
}Fault_Info_Real;

typedef struct
{
    uint8_t u8HistoryFaultIndex;
    Display_Fault_Info stHistoryFault[DISPLAY_DATA_FAULT_HISTORY_MAX_COUNT];
}Fault_Info_History;


//PV 故障结构体
typedef union
{
    uint32_t u32ErrorFlag;
    struct
    {    
        uint32_t bFaultOccurFlag                 : 1;             //光伏总状态位
        uint32_t bUnderVoltageOccurFlag          : 1;             //光伏欠压故障清除标志位
        uint32_t bOverVoltageOccurFlag           : 1;             //光伏过压故障清除标志位
        uint32_t bPvisoOccurFlag                 : 1;             //Pviso故障清除标志位
        uint32_t bSoftWareOverCurrentOccurFlag   : 1;             //软件过流故障清除标志位
        uint32_t bHardWareOverCurrentOccurFlag   : 1;             //硬件过流故障清除标志位
        uint32_t bLowPowerLockOccurFlag          : 1;             //低功率锁定故障清除标志位
        uint32_t bReserveOccurFlag2              : 1;             //预留
        uint32_t bReserveOccurFlag3              : 1;             //预留
        uint32_t bReserveOccurFlag4              : 1;             //预留
        uint32_t bReserveOccurFlag5              : 1;             //预留
        uint32_t bReserveOccurFlag6              : 1;             //预留
        uint32_t bReserveOccurFlag7              : 1;             //预留
        uint32_t bReserveOccurFlag8              : 1;             //预留
        uint32_t bReserveOccurFlag9              : 1;             //预留
        uint32_t bReserveOccurFlag10             : 1;             //预留
        uint32_t bReserveOccurFlag11             : 1;             //预留
        uint32_t bReserveOccurFlag12             : 1;             //预留
        uint32_t bReserveOccurFlag13             : 1;             //预留
        uint32_t bReserveOccurFlag14             : 1;             //预留
        uint32_t bReserveOccurFlag15             : 1;             //预留
        uint32_t bReserveOccurFlag16             : 1;             //预留
        uint32_t bReserveOccurFlag17             : 1;             //预留
        uint32_t bReserveOccurFlag18             : 1;             //预留
        uint32_t bReserveOccurFlag19             : 1;             //预留
        uint32_t bReserveOccurFlag20             : 1;             //预留
        uint32_t bReserveOccurFlag21             : 1;             //预留
        uint32_t bReserveOccurFlag22             : 1;             //预留
        uint32_t bReserveOccurFlag23             : 1;             //预留
        uint32_t bReserveOccurFlag24             : 1;             //预留
        uint32_t bReserveOccurFlag25             : 1;             //预留
        uint32_t bReserveOccurFlag26             : 1;             //预留
    }Bits;
}PV_Fault_Spec_Control;

//光伏故障控制标志位数据结构定义
typedef struct {
    PV_Fault_Spec_Control stPVFault[2];  //光伏故障
}PV_Fault_Control;

//系统故障控制标志位数据结构定义
typedef union 
{
    uint32_t ErrorFlag;
    struct 
    {
        uint32_t bSysErrOccurFlag                : 1;             //BIT0 系统故障
        uint32_t bBusFastOVOccurFlag             : 1;             //BIT1 母线过压快检
        uint32_t bBusSlowOVOccurFlag             : 1;             //BIT2 母线过压慢检
        uint32_t bBusUVOccurFlag                 : 1;             //BIT3 母线欠压
        uint32_t bBusSoftOccurFlag               : 1;             //BIT4 母线软起
        uint32_t bEmsCommErrOccurFlag            : 1;             //BIT5 EMS通讯异常
        uint32_t bOutputShortOccurFlag           : 1;             //BIT6 输出短路
        uint32_t bGFCIErrLv3OccurFlag            : 1;             //BIT7 GFCI漏电故障1
        uint32_t bGFCIErrLv2OccurFlag            : 1;             //BIT8 GFCI漏电故障2
        uint32_t bGFCIErrLv1OccurFlag            : 1;             //BIT9 GFCI漏电故障3
        uint32_t bFWSelfLockOccurFlag            : 1;             //BIT10 软件自锁故障
        uint32_t bSysOTOccurFlag                 : 1;             //BIT11 系统过温
        uint32_t bSysOverLoadOccurFlag           : 1;             //BIT12 过载
        uint32_t bEpoOccurFlag                   : 1;             //BIT13 Epo
        uint32_t bSlaveCpuErrOccurFlag           : 1;             //BIT14 从cpu故障
        uint32_t bIsoErrOccurFlag                : 1;             //BIT15 ISO故障
        uint32_t bBusBoardBrkProtOccurFlag       : 1;             //BIT16 母线板断连保护
        uint32_t bGroundProtOccurFlag            : 1;             //BIT17 接地保护
        uint32_t bDcDcOverLoadProtFlag           : 1;             //BIT18 DCDC过载保护故障
        uint32_t bPVRevConnectErr1Flag           : 1;             //BIT19 PV1反接故障
        uint32_t bPVRevConnectErr2Flag           : 1;             //BIT20 PV2反接故障
        uint32_t bInvOverTempFlag                : 1;             //BIT21 逆变器过温保护
        uint32_t bDCDCOverTempFlag               : 1;             //BIT22 DCDC过温保护
        uint32_t bGridRlyErrFlag                 : 1;             //BIT23 电网继电器故障
        uint32_t bSysWeakEnergyFlag              : 1;             //BIT24 系统能量弱
        uint32_t bLeakageCurrFlag                : 1;             //BIT25 漏电流故障
        uint32_t bReserved9OccurFlag             : 1;             //BIT26 预留
        uint32_t bReserved10OccurFlag            : 1;             //BIT27 预留
        uint32_t bReserved11OccurFlag            : 1;             //BIT28 预留
        uint32_t bReserved12OccurFlag            : 1;             //BIT29 预留
        uint32_t bReserved13OccurFlag            : 1;             //BIT30 预留
        uint32_t bReserved14OccurFlag            : 1;             //BIT31 预留
    }Bits;
}SYS_Fault_Control;

//逆变器故障控制标志位数据结构定义
typedef union
{
    uint64_t ErrorFlag;
    struct 
    {
        uint64_t bGridErrOccurFlag               : 1;             //BIT0 电网异常
        uint64_t bGridOVLv3OccurFlag             : 1;             //BIT1 电网过压三级故障
        uint64_t bGridOVLv2OccurFlag             : 1;             //BIT2 电网过压二级故障
        uint64_t bGridOVLv1OccurFlag             : 1;             //BIT3 电网过压一级故障
        uint64_t bGridUVLv3OccurFlag             : 1;             //BIT4 电网欠压三级故障
        uint64_t bGridUVLv2OccurFlag             : 1;             //BIT5 电网欠压二级故障
        uint64_t bGridUVLv1OccurFlag             : 1;             //BIT6 电网欠压一级故障
        uint64_t bGridFastOverFreqOccurFlag      : 1;             //BIT7 电网过频快检
        uint64_t bGridSlowOverFreqOccurFlag      : 1;             //BIT8 电网过频慢检
        uint64_t bGridFastUnderFreqOccurFlag     : 1;             //BIT9 电网欠频快检
        uint64_t bGridSlowUnderFreqOccurFlag     : 1;             //BIT10 电网欠频慢检
        uint64_t bIslandErrOccurFlag             : 1;             //BIT11 孤岛故障
        uint64_t bGridFastPowerDownOccurFlag     : 1;             //BIT12 电网掉电快检
        uint64_t bPllErrOccurFlag                : 1;             //BIT13 锁相异常
        uint64_t bSysLNReverseOccurFlag          : 1;             //BIT14 系统LN反接
        uint64_t bGrid10MinOVOccurFlag           : 1;             //BIT15 电网10分钟过压
        uint64_t bInvErr1OccurFlag               : 1;             //BIT16 逆变器故障1
        uint64_t bFwFastOC1OccurFlag             : 1;             //BIT17 软件过流快检1
        uint64_t bHwOV1OccurFlag                 : 1;             //BIT18 硬件过流1
        uint64_t bFwSlowOC1OccurFlag             : 1;             //BIT19 软件过流慢检1
        uint64_t bInvRlyErr1OccurFlag            : 1;             //BIT20 逆变器继电器故障1
        uint64_t bOTP1OccurFlag                  : 1;             //BIT21 过温故障1
        uint64_t bOVP1OccurFlag                  : 1;             //BIT22 过压故障1
        uint64_t bIgbtErr1OccurFlag              : 1;             //BIT23 IGBT故障1
        uint64_t bInductanceOT1OccurFlag         : 1;             //BIT24 电感过温1
        uint64_t bVoltDcComponentErr1OccurFlag   : 1;             //BIT25 电压直流分量故障1
        uint64_t bCurrDcComponentErr1OccurFlag   : 1;             //BIT26 电流直流分量故障1
        uint64_t bReserved1OccurFlag             : 1;             //BIT27 预留
        uint64_t bReserved2OccurFlag             : 1;             //BIT28 预留
        uint64_t bReserved3OccurFlag             : 1;             //BIT29 预留
        uint64_t bReserved4OccurFlag             : 1;             //BIT30 预留
        uint64_t bReserved5OccurFlag             : 1;             //BIT31 预留
        uint64_t bGridErr2OccurFlag              : 1;             //BIT32 电网故障2
        uint64_t bCTDisconnectOccurFlag          : 1;             //BIT33 CT未接故障
        uint64_t bMeterDisconnectOccurFlag       : 1;             //BIT34 电表未接故障
        uint64_t bReservedFlag0                  : 1;             //BIT35 预留
        uint64_t bReservedFlag1                  : 1;             //BIT36 预留
        uint64_t bReservedFlag2                  : 1;             //BIT37 预留
        uint64_t bReservedFlag3                  : 1;             //BIT38 预留
        uint64_t bReservedFlag4                  : 1;             //BIT39 预留
        uint64_t bReservedFlag5                  : 1;             //BIT40 预留
        uint64_t bReservedFlag6                  : 1;             //BIT41 预留
        uint64_t bReservedFlag7                  : 1;             //BIT42 预留
        uint64_t bReserved6OccurFlag             : 1;             //BIT43 预留
        uint64_t bReserved7OccurFlag             : 1;             //BIT44 预留
        uint64_t bReserved8OccurFlag             : 1;             //BIT45 预留
        uint64_t bReserved9OccurFlag             : 1;             //BIT46 预留
        uint64_t bReserved10OccurFlag            : 1;             //BIT47 预留
        uint64_t ParallelErrOccurFlag            : 1;             //BIT48 并机故障
        uint64_t ParallelCanErrOccurFlag         : 1;             //BIT49 并机CAN通讯故障
        uint64_t ParaCurrShareErrOccurFlag       : 1;             //BIT50 并机均流故障
        uint64_t bReserved11OccurFlag            : 1;             //BIT51 预留
        uint64_t bReserved12OccurFlag            : 1;             //BIT52 预留
        uint64_t bReserved13OccurFlag            : 1;             //BIT53 预留
        uint64_t bReserved14OccurFlag            : 1;             //BIT54 预留
        uint64_t bReserved15OccurFlag            : 1;             //BIT55 预留
        uint64_t bReserved16OccurFlag            : 1;             //BIT56 预留
        uint64_t bReserved17OccurFlag            : 1;             //BIT57 预留
        uint64_t bReserved18OccurFlag            : 1;             //BIT58 预留
        uint64_t bReserved19OccurFlag            : 1;             //BIT59 预留
        uint64_t bReserved20OccurFlag            : 1;             //BIT60 预留
        uint64_t bReserved21OccurFlag            : 1;             //BIT61 预留
        uint64_t bReserved22OccurFlag            : 1;             //BIT62 预留
        uint64_t bReserved23OccurFlag            : 1;             //BIT63 预留
    }Bits;
}INV_Fault_Control;

//DCDC故障控制标志位数据结构定义
typedef union
{
    uint16_t ErrorFlag;
    struct
    {
        uint16_t bFaultOccurFlag                  : 1;             //BIT0 故障
        uint16_t bMidBusOVPOccurFlag              : 1;             //BIT1 中间故障过压故障
        uint16_t bLLCHwOCOccurFlag                : 1;             //BIT2 LLC硬件过流
        uint16_t bBuckBoostHwOCOccurFlag          : 1;             //BIT3 BuckBoost硬件过流
        uint16_t bBuckBoostFwOCOccurFlag          : 1;             //BIT4 BuckBoost软件过流
        uint16_t bSOPChgOCPOccurFlag              : 1;             //BIT5 SOP充电过流保护
        uint16_t bSOPDisChgOCPOccurFlag           : 1;             //BIT6 SOP放电过流保护
        uint16_t bDCDCOverTempOccurFlag           : 1;             //BIT7 DCDC过温保护
        uint16_t bDCDCOverVoltOccurFlag           : 1;             //BIT8 电池过压保护
        uint16_t bDCDCUnderVoltOccurFlag          : 1;             //BIT9 电池欠压保护
        uint16_t bReserved3OccurFlag              : 1;             //BIT10 预留
        uint16_t bReserved4OccurFlag              : 1;             //BIT11 预留
        uint16_t bReserved5OccurFlag              : 1;             //BIT12 预留
        uint16_t bReserved6OccurFlag              : 1;             //BIT13 预留
        uint16_t bReserved7OccurFlag              : 1;             //BIT14 预留
        uint16_t bReserved8OccurFlag              : 1;             //BIT15 预留
    }Bits;
}DCDC_Fault_Control;

//发电机故障控制标志位数据结构定义
typedef union
{
    uint16_t ErrorFlag;
    struct
    {
        uint16_t GenErrFlag                       : 1;              //BIT0 发电机故障汇总
        uint16_t GenRlyErrFlag                    : 1;              //BIT1 发电机继电器故障(预留)
        uint16_t GenHighVoltErrFlag               : 1;              //BIT2 发电机高压
        uint16_t GenLowVoltErrFlag                : 1;              //BIT3 发电机低压
        uint16_t GenHighFreqErrFlag               : 1;              //BIT4 发电机高频
        uint16_t GenLowFreqErrFlag                : 1;              //BIT5 发电机低频
        uint16_t GenOverLoadErrFlag               : 1;              //BIT6 发电机过载
        uint16_t bReserved15Flag                  : 1;              //BIT7 预留
        uint16_t bReserved16Flag                  : 1;              //BIT8 预留
        uint16_t bReserved17Flag                  : 1;              //BIT9 预留
        uint16_t bReserved18Flag                  : 1;              //BIT10 预留
        uint16_t bReserved19Flag                  : 1;              //BIT11 预留
        uint16_t bReserved20Flag                  : 1;              //BIT12 预留
        uint16_t bReserved21Flag                  : 1;              //BIT13 预留
        uint16_t bReserved22Flag                  : 1;              //BIT14 预留
        uint16_t bReserved23Flag                  : 1;              //BIT15 预留
    }Bits;
}GEN_Fault_Control;

//系统告警控制标志位数据结构定义
typedef union
{
    uint16_t AlarmFlag;
    struct
    {
        uint16_t bSysAlarmFlag                    : 1;              //BIT0 系统告警汇总
        uint16_t bFanErrAlarmFlag                 : 1;              //BIT1 风扇故障告警
        uint16_t bSysOverLoadFlag                 : 1;              //BIT2 系统过载告警
        uint16_t bReserved0Flag                   : 1;              //BIT3 预留
        uint16_t bReserved1Flag                   : 1;              //BIT4 预留
        uint16_t bReserved2Flag                   : 1;              //BIT5 预留
        uint16_t bReserved3Flag                   : 1;              //BIT6 预留
        uint16_t bReserved4Flag                   : 1;              //BIT7 预留
        uint16_t bReserved5Flag                   : 1;              //BIT8 预留
        uint16_t bReserved6Flag                   : 1;              //BIT9 预留
        uint16_t bReserved7Flag                   : 1;              //BIT10 预留
        uint16_t bReserved8Flag                   : 1;              //BIT11 预留
        uint16_t bReserved9Flag                   : 1;              //BIT12 预留
        uint16_t bReserved10Flag                  : 1;              //BIT13 预留
        uint16_t bReserved11Flag                  : 1;              //BIT14 预留
        uint16_t bReserved12Flag                  : 1;              //BIT15 预留
    }Bits;
}SYS_Alarm_Control;

//BMS故障控制标志位数据结构定义
typedef union
{
    uint64_t ErrorFlag;
    struct
    {
        uint64_t bAlermSingleVoltDiffOccurFlag        : 1;     //BIT0 单芯电压一致性告警
        uint64_t bAlermMosfetOTOccurFlag              : 1;     //BIT1 MOSFET 高温
        uint64_t bAlermSingleUTOccurFlag              : 1;     //BIT2 单芯温度低温
        uint64_t bAlermSingleOTOccurFlag              : 1;     //BIT3 单芯温度高温
        uint64_t bAlermSingleVoltUVOccurFlag          : 1;     //BIT4 单芯电压低压
        uint64_t bAlermSingleVoltOVOccurFlag          : 1;     //BIT5 单芯电压高压
        uint64_t bAlermTotalVoltUVOccurFlag           : 1;     //BIT6 模块总压低压
        uint64_t bAlermTotalVoltOVOccurFlag           : 1;     //BIT7 模块总压高压
        uint64_t bAlermReserved0OccurFlag             : 1;     //BIT8 预留
        uint64_t bAlermReserved1OccurFlag             : 1;     //BIT9 预留
        uint64_t bAlermReserved2OccurFlag             : 1;     //BIT10 预留
        uint64_t bAlermReserved3OccurFlag             : 1;     //BIT11 预留
        uint64_t bAlermReserved4OccurFlag             : 1;     //BIT12 预留
        uint64_t bAlermReserved5OccurFlag             : 1;     //BIT13 预留
        uint64_t bAlermReserved6OccurFlag             : 1;     //BIT14 预留
        uint64_t bAlermReserved7OccurFlag             : 1;     //BIT15 预留
        uint64_t bAlermReserved8OccurFlag             : 1;     //BIT16 预留
        uint64_t bAlermReserved9OccurFlag             : 1;     //BIT17 预留
        uint64_t bAlermReserved10OccurFlag            : 1;     //BIT18 预留
        uint64_t bAlermReserved11OccurFlag            : 1;     //BIT19 预留
        uint64_t bAlermInternalComErrOccurFlag        : 1;     //BIT20 内部通信错误
        uint64_t bAlermOCDOccurFlag                   : 1;     //BIT21 放电过流告警
        uint64_t bAlermOCCOccurFlag                   : 1;     //BIT22 充电过流告警
        uint64_t bAlermSingleTempDiffOccurFlag        : 1;     //BIT23 单芯温度一致性告警
        uint64_t bAlermReserved12OccurFlag            : 1;     //BIT24 预留
        uint64_t bAlermReserved13OccurFlag            : 1;     //BIT25 预留
        uint64_t bAlermReserved14OccurFlag            : 1;     //BIT26 预留
        uint64_t bAlermReserved15OccurFlag            : 1;     //BIT27 预留
        uint64_t bAlermReserved16OccurFlag            : 1;     //BIT28 预留
        uint64_t bAlermReserved17OccurFlag            : 1;     //BIT29 预留
        uint64_t bAlermReserved18OccurFlag            : 1;     //BIT30 预留
        uint64_t bAlermReserved19OccurFlag            : 1;     //BIT31 预留
        uint64_t bFaultReserved0OccurFlag             : 1;     //BIT32 预留
        uint64_t bFaultMosfetOTOccurFlag              : 1;     //BIT33 MOSFET 过温
        uint64_t bFaultSingleUTOccurFlag              : 1;     //BIT34 单芯温度欠温
        uint64_t bFaultSingleOTOccurFlag              : 1;     //BIT35 单芯温度过温
        uint64_t bFaultSingleUVOccurFlag              : 1;     //BIT36 单芯电压欠压
        uint64_t bFaultSingleOVOccurFlag              : 1;     //BIT37 单芯电压过压
        uint64_t bFaultTotalModeUVOccurFlag           : 1;     //BIT38 模块总压欠压
        uint64_t bFaultTotalModeOVOccurFlag           : 1;     //BIT39 模块总压过压
        uint64_t bFaultReserved1OccurFlag             : 1;     //BIT40 预留
        uint64_t bFaultReserved2OccurFlag             : 1;     //BIT41 预留
        uint64_t bFaultReserved3OccurFlag             : 1;     //BIT42 预留
        uint64_t bFaultReserved4OccurFlag             : 1;     //BIT43 预留
        uint64_t bFaultReserved5OccurFlag             : 1;     //BIT44 预留
        uint64_t bFaultReserved6OccurFlag             : 1;     //BIT45 预留
        uint64_t bFaultReserved7OccurFlag             : 1;     //BIT46 预留
        uint64_t bFaultReserved8OccurFlag             : 1;     //BIT47 预留
        uint64_t bFaultReserved9OccurFlag             : 1;     //BIT48 预留
        uint64_t bFaultReserved10OccurFlag            : 1;     //BIT49 预留
        uint64_t bFaultReserved11OccurFlag            : 1;     //BIT50 预留
        uint64_t bFaultSysFaultOccurFlag              : 1;     //BIT51 系统故障保护
        uint64_t bFaultReserved12OccurFlag            : 1;     //BIT52 预留
        uint64_t bFaultOCDOccurFlag                   : 1;     //BIT53 放电过流故障
        uint64_t bFaultOCCOccurFlag                   : 1;     //BIT54 充电过流故障
        uint64_t bFaultReserved13OccurFlag            : 1;     //BIT55 预留
        uint64_t bFaultReserved14OccurFlag            : 1;     //BIT56 预留
        uint64_t bFaultReserved15OccurFlag            : 1;     //BIT57 预留
        uint64_t bFaultReserved16OccurFlag            : 1;     //BIT58 预留
        uint64_t bFaultReserved17OccurFlag            : 1;     //BIT59 预留
        uint64_t bFaultReserved18OccurFlag            : 1;     //BIT60 预留
        uint64_t bFaultReserved19OccurFlag            : 1;     //BIT61 预留
        uint64_t bFaultReserved20OccurFlag            : 1;     //BIT62 预留
        uint64_t bFaultReserved21OccurFlag            : 1;     //BIT63 预留
    }Bits;
}BMS_Fault_Control;

typedef union
{
    uint32_t ErrorFlag;
    struct
    {
        uint32_t bReserved0Flag                       : 1;     //BIT0 预留
        uint32_t bOVProtectFlag                       : 1;     //BIT1 电压过压
        uint32_t bUVProtectFlag                       : 1;     //BIT2 电压欠压
        uint32_t bOTProtectFlag                       : 1;     //BIT3 过温
        uint32_t bUTProtectFlag                       : 1;     //BIT4 欠温
        uint32_t bReserved1Flag                       : 1;     //BIT5 预留
        uint32_t bReserved2Flag                       : 1;     //BIT6 预留
        uint32_t bOCDProtectFlag                      : 1;     //BIT7 放电过流
        uint32_t bOCCProtectFlag                      : 1;     //BIT8 充电过流            
        uint32_t bReserved3Flag                       : 1;     //BIT9 预留
        uint32_t bReserved4Flag                       : 1;     //BIT10预留
        uint32_t bFaultFlag                           : 1;     //BIT11故障
        uint32_t bReserved5Flag                       : 1;     //BIT12预留
        uint32_t bReserved6Flag                       : 1;     //BIT13预留
        uint32_t bReserved7Flag                       : 1;     //BIT14预留
        uint32_t bReserved8Flag                       : 1;     //BIT15预留
        uint32_t bReserved9Flag                       : 1;     //BIT16预留
        uint32_t bHVAlarmFlag                         : 1;     //BIT17电压高压
        uint32_t bLVAlarmFlag                         : 1;     //BIT18电压低压
        uint32_t bHTAlarmFlag                         : 1;     //BIT19高温
        uint32_t bLTAlarmFlag                         : 1;     //BIT20低温
        uint32_t bReserved10Flag                      : 1;     //BIT21预留
        uint32_t bReserved11Flag                      : 1;     //BIT22预留
        uint32_t bOCDAlarmFlag                        : 1;     //BIT23放电大电流
        uint32_t bOCCAlarmFlag                        : 1;     //BIT24充电大电流            
        uint32_t bReserved12Flag                      : 1;     //BIT25预留
        uint32_t bReserved13Flag                      : 1;     //BIT26预留
        uint32_t bOfflineFlag                         : 1;     //BIT27掉线
        uint32_t bReserved14Flag                      : 1;     //BIT28预留
        uint32_t bReserved15Flag                      : 1;     //BIT29预留
        uint32_t bReserved16Flag                      : 1;     //BIT30预留
        uint32_t bReserved17Flag                      : 1;     //BIT31预留       
    }Bits;
}BMSCan_Fault_Control;
//EMS故障控制标志位数据结构定义
typedef union
{
    uint16_t ErrorFlag;
    struct
    {
        uint16_t bAlarmPcsCommErrOccurFlag            : 1;     //BIT0 PCS通讯故障
        uint16_t bAlarmMeterCommErrOccurFlag          : 1;     //BIT1 Meter通讯故障
        uint16_t bAlarmBmsCommErrOccurFlag            : 1;     //BIT2 BMS通讯故障
        uint16_t bAlarmCTCommErrOccurFlag             : 1;     //BIT3 CT通讯故障
        uint16_t bAlarmWeakBatteryOccurFlag           : 1;     //BIT4 弱电池故障
        uint16_t bAlarmReserved10OccurFlag            : 1;     //BIT5 预留
        uint16_t bAlarmReserved11OccurFlag            : 1;     //BIT6 预留
        uint16_t bAlarmReserved12OccurFlag            : 1;     //BIT7 预留
        uint16_t bAlarmReserved0OccurFlag             : 1;     //BIT8 预留
        uint16_t bAlarmReserved1OccurFlag             : 1;     //BIT9 预留
        uint16_t bAlarmReserved2OccurFlag             : 1;     //BIT10 预留
        uint16_t bAlarmReserved3OccurFlag             : 1;     //BIT11 预留
        uint16_t bAlarmReserved4OccurFlag             : 1;     //BIT12 预留
        uint16_t bAlarmReserved5OccurFlag             : 1;     //BIT13 预留
        uint16_t bAlarmReserved6OccurFlag             : 1;     //BIT14 预留
        uint16_t bAlarmReserved7OccurFlag             : 1;     //BIT15 预留
    }Bits;
}EMS_Fault_Control;

//界面操作类型
typedef enum
{
    SYS_FAULT_BusFastOV           = 0x0000,                //母线过压快检故障
    SYS_FAULT_BusSlowOV           = 0x0001,                //母线过压慢检故障
    SYS_FAULT_BusUV               = 0x0002,                //母线欠压故障
    SYS_FAULT_BusSoft             = 0x0003,                //母线软起故障
    SYS_FAULT_EmsCommErr          = 0x0004,                //EMS通讯异常故障
    SYS_FAULT_OutputShort         = 0x0005,                //输出短路故障
    SYS_FAULT_GFCIErrLv3          = 0x0006,                //GFCI漏电故障三级
    SYS_FAULT_GFCIErrLv2          = 0x0007,                //GFCI漏电故障二级
    SYS_FAULT_GFCIErrLv1          = 0x0008,                //GFCI漏电故障一级
    SYS_FAULT_SWSelfLock          = 0x0009,                //软件自锁故障
    SYS_FAULT_SysOT               = 0x000A,                //系统过温故障
    SYS_FAULT_SysOL               = 0x000B,                //系统过载故障
    SYS_FAULT_Epo                 = 0x000C,                //Epo故障
    SYS_FAULT_SlaveCpuErr         = 0x000D,                //从cpu故障
    SYS_FAULT_IsoErr              = 0x000E,                //ISO故障
    SYS_FAULT_BusBoardBrkProt     = 0x000F,                //母线板断连保护故障
    SYS_FAULT_GroundProt          = 0x0010,                //接地保护故障
    SYS_FAULT_DCDCOverLoadProt    = 0x0011,                //DCDC过载保护故障
    SYS_FAULT_PV1RevConnectProt   = 0x0012,                //PV1反接故障
    SYS_FAULT_PV2RevConnectProt   = 0x0013,                //PV2反接故障
    SYS_FAULT_InvOverTempProt     = 0x0014,                //逆变器过温保护
    SYS_FAULT_DCDCOverTempProt    = 0x0015,                //DCDC过温保护
    SYS_FAULT_GridRlyErrProt      = 0x0016,                //电网继电器故障
    SYS_FAULT_SysWeakEnergyProt   = 0x0017,                //系统能量弱
    SYS_FAULT_LeakageCurrProt     = 0x0018,                //漏电流故障
    INV_FAULT_GridOVLv3           = 0x0100,                //电网过压三级故障
    INV_FAULT_GridOVLv2           = 0x0101,                //电网过压二级故障
    INV_FAULT_GridOVLv1           = 0x0102,                //电网过压一级故障
    INV_FAULT_GridUVLv3           = 0x0103,                //电网欠压三级故障
    INV_FAULT_GridUVLv2           = 0x0104,                //电网欠压二级故障
    INV_FAULT_GridUVLv1           = 0x0105,                //电网欠压一级故障
    INV_FAULT_GridFastOverFreq    = 0x0106,                //电网过频快检故障
    INV_FAULT_GridSlowOverFreq    = 0x0107,                //电网过频慢检故障
    INV_FAULT_GridFastUnderFreq   = 0x0108,                //电网欠频快检故障
    INV_FAULT_GridSlowUnderFreq   = 0x0109,                //电网欠频慢检故障
    INV_FAULT_GridFastPowerDown   = 0x010A,                //电网掉电快检故障
    INV_FAULT_PllErr              = 0x010B,                //锁相异常故障
    INV_FAULT_SysLNReverse        = 0x010C,                //系统LN反接故障
    INV_FAULT_Grid10MinOV         = 0x010D,                //电网10分钟过压故障
    INV_FAULT_FwFastOC1           = 0x010F,                //软件过流快检1故障
    INV_FAULT_HwOV1               = 0x0110,                //硬件过流1故障
    INV_FAULT_FwSlowOC1           = 0x0111,                //软件过流慢检1故障
    INV_FAULT_InvRlyErr1          = 0x0112,                //逆变器继电器故障1
    INV_FAULT_OTP1                = 0x0113,                //过温故障1
    INV_FAULT_OVP1                = 0x0114,                //过压故障1
    INV_FAULT_IgbtErr1            = 0x0115,                //IGBT故障1
    INV_FAULT_InductanceOT1       = 0x0116,                //电感过温1
    INV_FAULT_VoltDcComponentErr1 = 0x0117,                //电压直流分量故障1
    INV_FAULT_CurrDcComponentErr1 = 0x0118,                //电流直流分量故障1
    INV_FAULT_CT_DisConnect       = 0x011D,                //CT未接故障
    INV_FAULT_Meter_DisConnect    = 0x011E,                //电表未接故障
    INV_FAULT_FwSlowOC2           = 0x011F,                //软件过流慢检2故障(预留)
    INV_FAULT_InvRlyErr2          = 0x0120,                //逆变器继电器故障2(预留)
    INV_FAULT_OTP2                = 0x0121,                //过温故障2(预留)
    INV_FAULT_OVP2                = 0x0122,                //过压故障2(预留)
    INV_FAULT_IgbtErr2            = 0x0123,                //IGBT故障2(预留)
    INV_FAULT_InductanceOT2       = 0x0124,                //电感过温2(预留)
    INV_FAULT_VoltDcComponentErr2 = 0x0125,                //电压直流分量故障2(预留)
    INV_FAULT_CurrDcComponentErr2 = 0x0126,                //电流直流分量故障2(预留)
    INV_FAULT_ParallelCanErr      = 0x012C,                //并机CAN通讯故障
    INV_FAULT_ParaCurrShareErr    = 0x012D,                //并机均流故障
    INV_FAULT_IslandErr           = 0x012E,                //孤岛故障
    DCDC_FAULT_MidBusOVP          = 0x0200,                //中间故障过压故障
    DCDC_FAULT_LLCHwOC            = 0x0201,                //LLC硬件过流故障
    DCDC_FAULT_BuckBoostHwOC      = 0x0202,                //BuckBoost硬件过流故障
    DCDC_FAULT_BuckBoostSwOC      = 0x0203,                //BuckBoost软件过流故障
    DCDC_FAULT_SOPChgOCP          = 0x0204,                //SOP充电过流保护故障
    DCDC_FAULT_SOPDisChgOCP       = 0x0205,                //SOP放电过流保护故障
    DCDC_FAULT_DCDCOverTemp       = 0x0206,                //DCDC过温保护故障
    DCDC_FAULT_DCDCOverVolt       = 0x0207,                //电池过压保护故障
    DCDC_FAULT_DCDCUnderVolt      = 0x0208,                //电池欠压保护故障
    PV1_FAULT_PvUV                = 0x0300,                //欠压故障
    PV1_FAULT_PvOV                = 0x0301,                //过压故障
    PV1_FAULT_PVIso               = 0x0302,                //PvIso故障
    PV1_FAULT_SWOC                = 0x0303,                //软件过流故障
    PV1_FAULT_HWOC                = 0x0304,                //硬件过流故障
    PV1_FAULT_LPLK                = 0x0305,                //低功率锁定故障
    PV2_FAULT_PvUV                = 0x0320,                //欠压故障
    PV2_FAULT_PvOV                = 0x0321,                //过压故障
    PV2_FAULT_PVIso               = 0x0322,                //PvIso故障
    PV2_FAULT_SWOC                = 0x0323,                //软件过流故障
    PV2_FAULT_HWOC                = 0x0324,                //硬件过流故障 
    PV2_FAULT_LPLK                = 0x0325,                //低功率锁定故障
    BMS_ALERM_SingleVoltDiff      = 0x0401,                //单芯电压一致性告警
    BMS_ALERM_MosfetOT            = 0x0402,                //MOSFET 高温告警
    BMS_ALERM_SingleUT            = 0x0403,                //单芯温度低温告警
    BMS_ALERM_SingleOT            = 0x0404,                //单芯温度高温告警
    BMS_ALERM_SingleVoltUV        = 0x0405,                //单芯电压低压告警
    BMS_ALERM_SingleVoltOV        = 0x0406,                //单芯电压高压告警
    BMS_ALERM_TotalVoltUV         = 0x0407,                //模块总压低压告警
    BMS_ALERM_TotalVoltOV         = 0x0408,                //模块总压高压告警
    BMS_ALERM_InternalComErr      = 0x0424,                //内部通信错误告警
    BMS_ALERM_OCD                 = 0x0425,                //放电过流告警
    BMS_ALERM_OCC                 = 0x0426,                //充电过流告警
    BMS_ALERM_SingleTempDiff      = 0x0427,                //单芯温度一致性告警
    BMS_FAULT_MosfetOT            = 0x0431,                //单芯温度一致性故障
    BMS_FAULT_SingleUT            = 0x0432,                //单芯温度欠温故障
    BMS_FAULT_SingleOT            = 0x0433,                //单芯温度过温故障
    BMS_FAULT_SingleUV            = 0x0434,                //单芯电压欠压故障
    BMS_FAULT_SingleOV            = 0x0435,                //单芯电压过压故障
    BMS_FAULT_TotalModeUV         = 0x0436,                //模块总压欠压故障
    BMS_FAULT_TotalModeOV         = 0x0437,                //模块总压过压故障
    BMS_FAULT_SysFault            = 0x0443,                //系统故障保护故障
    BMS_FAULT_OCD                 = 0x0445,                //放电过流故障
    BMS_FAULT_OCC                 = 0x0446,                //充电过流故障
    EMS_FAULT_PCS                 = 0x0500,                //PCS通讯故障
    EMS_FAULT_METER               = 0x0501,                //电表通讯故障
    EMS_FAULT_BMS                 = 0x0502,                //BMS通讯故障
    EMS_FAULT_CT                  = 0x0503,                //CT通讯故障
    EMS_FAULT_WEAKBATTERY         = 0x0504,                //弱电池故障
    GEN_FAULT_RlyErr              = 0x0600,                //发电机继电器故障
    GEN_FAULT_HighVolt            = 0x0601,                //发电机高压
    GEN_FAULT_LowVolt             = 0x0602,                //发电机低压
    GEN_FAULT_HighFreq            = 0x0603,                //发电机高频
    GEN_FAULT_LowFreq             = 0x0604,                //发电机低频
    GEN_FAULT_OverLoad            = 0x0605,                //发电机过载
    SYS_ALARM_FANErr              = 0x0700,                //系统风扇告警
    SYS_ALARM_OverLoad            = 0x0701,                //系统过载告警
    FAULT_END                                              //提示界面
}Fault_TypeDef;

//PCS故障控制标志数据结构定义
typedef struct {
    PV_Fault_Control   stPVFaultControl;     //光伏故障
    SYS_Fault_Control  stSYSFaultControl;    //系统故障
    INV_Fault_Control  stINVFaultControl;    //逆变器故障
    DCDC_Fault_Control stDCDCFaultControl;   //DCDC故障
    GEN_Fault_Control  stGenFaultControl;    //发电机故障
    SYS_Alarm_Control  stSYSAlarmControl;    //系统告警
}PCS_Fault_Control;

//PCS故障控制标志数据结构定义
typedef struct {
    PCS_Fault_Control       stPCSFaultControl;     //PCS故障
    BMS_Fault_Control       stBMSFaultControl;     //BMS故障
    BMSCan_Fault_Control    stBMSCanFaultControl;  //BMSCan故障
    EMS_Fault_Control       stEMSFaultControl;     //EMS故障
}Device_Fault_Control;

//系统故障数据结构定义
typedef struct
{
    union
    {
        uint32_t u32Error;
        struct
        {
            uint32_t bSysErr1              : 1;             //BIT0 系统故障1汇总
            uint32_t bBusFastOV            : 1;             //BIT1 母线过压快检
            uint32_t bBusSlowOV            : 1;             //BIT2 母线过压慢检
            uint32_t bBusUV                : 1;             //BIT3 母线欠压
            uint32_t bBusSoft              : 1;             //BIT4 母线软起
            uint32_t bEmsCommErr           : 1;             //BIT5 EMS通讯异常
            uint32_t bOutputShort          : 1;             //BIT6 输出短路
            uint32_t bGFCIErrLv3           : 1;             //BIT7 GFCI漏电故障3级
            uint32_t bGFCIErrLv2           : 1;             //BIT8 GFCI漏电故障2级
            uint32_t bGFCIErrLv1           : 1;             //BIT9 GFCI漏电故障1级
            uint32_t bFWSelfLock           : 1;             //BIT10 软件自锁故障
            uint32_t bSysOT                : 1;             //BIT11 系统过温
            uint32_t bSysOverLoad          : 1;             //BIT12 过载
            uint32_t bEpo                  : 1;             //BIT13 Epo
            uint32_t bSlaveCpuErr          : 1;             //BIT14 从cpu故障
            uint32_t bIsoErr               : 1;             //BIT15 ISO故障
            uint16_t bSysErr2              : 1;             //BIT0 系统故障2汇总
            uint16_t bBusBoardBrkProt      : 1;             //BIT1 母线板断连保护
            uint16_t bGroundProt           : 1;             //BIT2 接地保护
            uint16_t bDcDcOverLoadProt     : 1;             //BIT3 DCDC过载保护
            uint16_t bPVRevConnectErr1     : 1;             //BIT4 PV1反接故障
            uint16_t bPVRevConnectErr2     : 1;             //BIT5 PV2反接故障
            uint16_t bInvOverTempProt      : 1;             //BIT6 逆变器过温保护
            uint16_t bDCDCOverTempProt     : 1;             //BIT7 DCDC过温保护
            uint16_t bGridRlyError         : 1;             //BIT8 电网继电器故障
            uint16_t bSysEnergyWeak        : 1;             //BIT9 系统能量弱
            uint16_t bLeakCurrError        : 1;             //BIT10 漏电流故障
            uint16_t bReserved9            : 1;             //BIT11 预留
            uint16_t bReserved10           : 1;             //BIT12 预留
            uint16_t bReserved11           : 1;             //BIT13 预留
            uint16_t bReserved12           : 1;             //BIT14 预留
            uint16_t bReserved13           : 1;             //BIT15 预留
        }Bits;
    }SysFault_t;
}Display_SYS_Fault_t;

//系统告警数据结构定义
typedef union
{
    uint16_t u16Alarm;
    struct
    {
        uint16_t bSysAlarm             : 1;             //BIT0 系统告警汇总
        uint16_t bFanErrAlarm          : 1;             //BIT1 风扇故障告警
        uint16_t bSysOverLoad          : 1;             //BIT2 系统过载告警
        uint16_t bReserved0            : 1;             //BIT3 预留
        uint16_t bReserved1            : 1;             //BIT4 预留
        uint16_t bReserved2            : 1;             //BIT5 预留
        uint16_t bReserved3            : 1;             //BIT6 预留
        uint16_t bReserved4            : 1;             //BIT7 预留
        uint16_t bReserved5            : 1;             //BIT8 预留
        uint16_t bReserved6            : 1;             //BIT9 预留
        uint16_t bReserved7            : 1;             //BIT10 预留
        uint16_t bReserved8            : 1;             //BIT11 预留
        uint16_t bReserved9            : 1;             //BIT12 预留
        uint16_t bReserved10           : 1;             //BIT13 预留
        uint16_t bReserved11           : 1;             //BIT14 预留
        uint16_t bReserved12           : 1;             //BIT15 预留
    }Bits;
}Display_SYS_Alarm_t;

typedef union
{
     uint16_t u16Error;
     struct
     {
         uint16_t GenErr                 : 1;          //BIT0 发电机故障汇总
         uint16_t GenRlyErr              : 1;          //BIT1 发电机继电器故障(预留)
         uint16_t GenHighVoltErr         : 1;          //BIT2 发电机高压
         uint16_t GenLowVoltErr          : 1;          //BIT3 发电机低压
         uint16_t GenHighFreqErr         : 1;          //BIT4 发电机高频
         uint16_t GenLowFreqErr          : 1;          //BIT5 发电机低频
         uint16_t GenOverLoadErr         : 1;          //BIT6 发电机过载
         uint16_t bReserved15            : 1;          //BIT7 预留
         uint16_t bReserved16            : 1;          //BIT8 预留
         uint16_t bReserved17            : 1;          //BIT9 预留
         uint16_t bReserved18            : 1;          //BIT10 预留
         uint16_t bReserved19            : 1;          //BIT11 预留
         uint16_t bReserved20            : 1;          //BIT12 预留
         uint16_t bReserved21            : 1;          //BIT13 预留
         uint16_t bReserved22            : 1;          //BIT14 预留
         uint16_t bReserved23            : 1;          //BIT15 预留
     }Bits;
}Display_Gen_Fault_t;

typedef struct
{
    union
    {
        uint32_t u32Error;
        struct
        {
            uint32_t bPvErr                : 1;             //BIT0 故障
            uint32_t bPvUV                 : 1;             //BIT1 pV欠压
            uint32_t bPvOV                 : 1;             //BIT2 PV过压
            uint32_t bReserved             : 1;             //BIT3 预留
            uint32_t bFWOI                 : 1;             //BIT4 软件过流
            uint32_t bHWOI                 : 1;             //BIT5 硬件过流
            uint32_t bLowPowerLock         : 1;             //BIT6 低功率锁定
            uint32_t bReserved2            : 1;             //BIT7 预留
            uint32_t bReserved3            : 1;             //BIT8 预留
            uint32_t bReserved4            : 1;             //BIT9 预留
            uint32_t bReserved5            : 1;             //BIT10 预留
            uint32_t bReserved6            : 1;             //BIT11 预留
            uint32_t bReserved7            : 1;             //BIT12 预留
            uint32_t bReserved8            : 1;             //BIT13 预留
            uint32_t bReserved9            : 1;             //BIT14 预留
            uint32_t bReserved10           : 1;             //BIT15 预留
            uint32_t bReserved11           : 1;             //BIT16 预留
            uint32_t bReserved12           : 1;             //BIT17 预留
            uint32_t bReserved13           : 1;             //BIT18 预留
            uint32_t bReserved14           : 1;             //BIT19 预留
            uint32_t bReserved15           : 1;             //BIT20 预留
            uint32_t bReserved16           : 1;             //BIT21 预留
            uint32_t bReserved17           : 1;             //BIT22 预留
            uint32_t bReserved18           : 1;             //BIT23 预留
            uint32_t bReserved19           : 1;             //BIT24 预留
            uint32_t bReserved20           : 1;             //BIT25 预留
            uint32_t bReserved21           : 1;             //BIT26 预留
            uint32_t bReserved22           : 1;             //BIT27 预留
            uint32_t bReserved23           : 1;             //BIT28 预留
            uint32_t bReserved24           : 1;             //BIT29 预留
            uint32_t bReserved25           : 1;             //BIT30 预留
            uint32_t bReserved26           : 1;             //BIT31 预留
        }Bits;
    }PVFault_t;
}PV_Fault_t;

//光伏故障数据结构定义
typedef struct 
{
    PV_Fault_t stPVFault[2];  //光伏故障
}Display_PV_Fault_t;

//逆变器故障数据结构定义
typedef struct
{
    union
    {
        uint64_t u64Error;
        struct
        {
            uint64_t bGridErr               : 1;             //BIT0 电网异常
            uint64_t bbGridOVLv3            : 1;             //BIT1 电网过压三级故障
            uint64_t bbGridOVLv2            : 1;             //BIT2 电网过压二级故障
            uint64_t bbGridOVLv1            : 1;             //BIT3 电网过压一级故障
            uint64_t bGridUVLv3             : 1;             //BIT4 电网欠压三级故障
            uint64_t bGridUVLv2             : 1;             //BIT5 电网欠压二级故障
            uint64_t bGridUVLv1             : 1;             //BIT6 电网欠压一级故障(预留)
            uint64_t bGridFastOverFreq      : 1;             //BIT7 电网过频快检
            uint64_t bGridSlowOverFreq      : 1;             //BIT8 电网过频慢检
            uint64_t bGridFastUnderFreq     : 1;             //BIT9 电网欠频快检
            uint64_t bGridSlowUnderFreq     : 1;             //BIT10 电网欠频慢检
            uint64_t bIslandErr             : 1;             //BIT11 孤岛故障
            uint64_t bGridFastPowerDown     : 1;             //BIT12 电网掉电快检
            uint64_t bPllErr                : 1;             //BIT13 锁相异常
            uint64_t bSysLNReverse          : 1;             //BIT14 系统LN反接(预留)
            uint64_t bGrid10MinOV           : 1;             //BIT15 电网10分钟过压故障
            uint64_t bInvErr1               : 1;             //BIT16 逆变器故障
            uint64_t bFwFastOC              : 1;             //BIT17 软件过流快检
            uint64_t bHwOV                  : 1;             //BIT18 硬件过流
            uint64_t bFwSlowOC              : 1;             //BIT19 软件过流慢检
            uint64_t bInvRlyErr             : 1;             //BIT20 逆变器继电器故障
            uint64_t bOTP                   : 1;             //BIT21 过温故障
            uint64_t bOVP                   : 1;             //BIT22 过压故障
            uint64_t bIgbtErr               : 1;             //BIT23 IGBT故障
            uint64_t bInductanceOT          : 1;             //BIT24 电感过温
            uint64_t bVoltDcComponentErr    : 1;             //BIT25 电压直流分量故障
            uint64_t bCurrDcComponentErr    : 1;             //BIT26 电流直流分量故障
            uint64_t bReserved1             : 1;             //BIT27 预留
            uint64_t bReserved2             : 1;             //BIT28 预留
            uint64_t bReserved3             : 1;             //BIT29 预留
            uint64_t bReserved4             : 1;             //BIT30 预留
            uint64_t bReserved5             : 1;             //BIT31 预留
            uint64_t bGridErr2              : 1;             //BIT32 电网故障2汇总
            uint64_t bCTDisconnect          : 1;             //BIT33 CT未接故障
            uint64_t bMeterDisconnect       : 1;             //BIT34 电表未接故障
            uint64_t bReserved6             : 1;             //BIT35 预留
            uint64_t bReserved7             : 1;             //BIT36 预留
            uint64_t bReserved8             : 1;             //BIT37 预留
            uint64_t bReserved9             : 1;             //BIT38 预留
            uint64_t bReserved10            : 1;             //BIT39 预留
            uint64_t bReserved11            : 1;             //BIT40 预留
            uint64_t bReserved12            : 1;             //BIT41 预留
            uint64_t bReserved13            : 1;             //BIT42 预留
            uint64_t bReserved14            : 1;             //BIT43 预留
            uint64_t bReserved15            : 1;             //BIT44 预留
            uint64_t bReserved16            : 1;             //BIT45 预留
            uint64_t bReserved17            : 1;             //BIT46 预留
            uint64_t bReserved18            : 1;             //BIT47 预留
            uint64_t ParallelErr            : 1;             //BIT48 并机故障
            uint64_t ParallelCanErr         : 1;             //BIT49 并机CAN通讯故障
            uint64_t ParaCurrShareErr       : 1;             //BIT50 并机均流故障
            uint64_t bReserved19            : 1;             //BIT51 预留
            uint64_t bReserved20            : 1;             //BIT52 预留
            uint64_t bReserved21            : 1;             //BIT53 预留
            uint64_t bReserved22            : 1;             //BIT54 预留
            uint64_t bReserved23            : 1;             //BIT55 预留
            uint64_t bReserved24            : 1;             //BIT56 预留
            uint64_t bReserved25            : 1;             //BIT57 预留
            uint64_t bReserved26            : 1;             //BIT58 预留
            uint64_t bReserved27            : 1;             //BIT59 预留
            uint64_t bReserved28            : 1;             //BIT60 预留
            uint64_t bReserved29            : 1;             //BIT61 预留
            uint64_t bReserved30            : 1;             //BIT62 预留
            uint64_t bReserved31            : 1;             //BIT63 预留
        }Bits;
    }InvFault_t;
}Display_INV_Fault_t;

//DCDC故障数据结构定义
typedef struct
{
    union
    {
        uint16_t u16Error;
        struct
        {
            uint16_t bFault                  : 1;             //BIT0 故障
            uint16_t bMidBusOVP              : 1;             //BIT1 中间故障过压故障
            uint16_t bLLCHwOC                : 1;             //BIT2 LLC硬件过流
            uint16_t bBuckBoostHwOC          : 1;             //BIT3 BuckBoost硬件过流
            uint16_t bBuckBoostFwOC          : 1;             //BIT4 BuckBoost软件过流
            uint16_t bSOPChgOCP              : 1;             //BIT5 SOP充电过流保护
            uint16_t bSOPDisChgOCP           : 1;             //BIT6 SOP放电过流保护
            uint16_t bDCDCOverTemp           : 1;             //BIT7 DCDC过温保护
            uint16_t bBatOverVolt            : 1;             //BIT8 电池过压
            uint16_t bBatUnderVolt           : 1;             //BIT9 电池欠压
            uint16_t bReserved3              : 1;             //BIT10 预留
            uint16_t bReserved4              : 1;             //BIT11 预留
            uint16_t bReserved5              : 1;             //BIT12 预留
            uint16_t bReserved6              : 1;             //BIT13 预留
            uint16_t bReserved7              : 1;             //BIT14 预留
            uint16_t bReserved8              : 1;             //BIT15 预留
        }Bits;
    }DCDCError1_t;

    union
    {
        uint16_t u16Error;
        struct
        {
            uint16_t bReserved9              : 1;             //BIT0 预留
            uint16_t bReserved10             : 1;             //BIT1 预留
            uint16_t bReserved11             : 1;             //BIT2 预留
            uint16_t bReserved12             : 1;             //BIT3 预留
            uint16_t bReserved13             : 1;             //BIT4 预留
            uint16_t bReserved14             : 1;             //BIT5 预留
            uint16_t bReserved15             : 1;             //BIT6 预留
            uint16_t bReserved16             : 1;             //BIT7 预留
            uint16_t bReserved17             : 1;             //BIT8 预留
            uint16_t bReserved18             : 1;             //BIT9 预留
            uint16_t bReserved19             : 1;             //BIT10 预留
            uint16_t bReserved20             : 1;             //BIT11 预留
            uint16_t bReserved21             : 1;             //BIT12 预留
            uint16_t bReserved22             : 1;             //BIT13 预留
            uint16_t bReserved23             : 1;             //BIT14 预留
            uint16_t bReserved24             : 1;             //BIT15 预留
        }Bits;
    }Reserved1_t;

    union
    {
        uint16_t u16Error;
        struct
        {
            uint16_t bReserved25             : 1;            //BIT0 预留
            uint16_t bReserved26             : 1;            //BIT1 预留
            uint16_t bReserved27             : 1;            //BIT2 预留
            uint16_t bReserved28             : 1;            //BIT3 预留
            uint16_t bReserved29             : 1;            //BIT4 预留
            uint16_t bReserved30             : 1;            //BIT5 预留
            uint16_t bReserved31             : 1;            //BIT6 预留
            uint16_t bReserved32             : 1;            //BIT7 预留
            uint16_t bReserved33             : 1;            //BIT8 预留
            uint16_t bReserved34             : 1;            //BIT9 预留
            uint16_t bReserved35             : 1;            //BIT10 预留
            uint16_t bReserved36             : 1;            //BIT11 预留
            uint16_t bReserved37             : 1;            //BIT12 预留
            uint16_t bReserved38             : 1;            //BIT13 预留
            uint16_t bReserved39             : 1;            //BIT14 预留
            uint16_t bReserved40             : 1;            //BIT15 预留
        }Bits;
    }Reserved2_t;
}Display_DCDC_Fault_t;

//BMS故障数据结构定义
typedef struct
{
    union
    {
        uint16_t u16Warnning;
        struct
        {
            uint16_t bSingleVoltDiff        : 1;     //BIT0 单芯电压一致性告警
            uint16_t bMosfetOT              : 1;     //BIT1 MOSFET 高温
            uint16_t bSingleUT              : 1;     //BIT2 单芯温度低温
            uint16_t bSingleOT              : 1;     //BIT3 单芯温度高温
            uint16_t bSingleVoltUV          : 1;     //BIT4 单芯电压低压
            uint16_t bSingleVoltOV          : 1;     //BIT5 单芯电压高压
            uint16_t bTotalVoltUV           : 1;     //BIT6 模块总压低压
            uint16_t bTotalVoltOV           : 1;     //BIT7 模块总压高压
            uint16_t bReserved0             : 1;     //BIT8 预留
            uint16_t bReserved1             : 1;     //BIT9 预留
            uint16_t bReserved2             : 1;     //BIT10 预留
            uint16_t bReserved3             : 1;     //BIT11 预留
            uint16_t bReserved4             : 1;     //BIT12 预留
            uint16_t bReserved5             : 1;     //BIT13 预留
            uint16_t bReserved6             : 1;     //BIT14 预留
            uint16_t bReserved7             : 1;     //BIT15 预留
        }Bits;
    }SystemAlarm1_t;                                //系统告警状态 1

    union
    {
        uint16_t u16Warnning;
        struct
        {
            uint16_t bReserved0             : 1;     //BIT0 预留
            uint16_t bReserved1             : 1;     //BIT1 预留
            uint16_t bReserved2             : 1;     //BIT2 预留
            uint16_t bReserved3             : 1;     //BIT3 预留
            uint16_t bInternalComErr        : 1;     //BIT4 内部通信错误
            uint16_t bOCD                   : 1;     //BIT5 放电过流告警
            uint16_t bOCC                   : 1;     //BIT6 充电过流告警
            uint16_t bSingleTempDiff        : 1;     //BIT7 单芯温度一致性告警
            uint16_t bReserved4             : 1;     //BIT8 预留
            uint16_t bReserved5             : 1;     //BIT9 预留
            uint16_t bReserved6             : 1;     //BIT10 预留
            uint16_t bReserved7             : 1;     //BIT11 预留
            uint16_t bReserved8             : 1;     //BIT12 预留
            uint16_t bReserved9             : 1;     //BIT13 预留
            uint16_t bReserved10            : 1;     //BIT14 预留
            uint16_t bReserved11            : 1;     //BIT15 预留
        }Bits;
    }SystemAlarm2_t;                                //系统告警状态 2

    union
    {
        uint16_t u16Error;
        struct
        {
            uint16_t bReserved0             : 1;     //BIT0 预留
            uint16_t bMosfetOT              : 1;     //BIT1 MOSFET 过温
            uint16_t bSingleUT              : 1;     //BIT2 单芯温度欠温
            uint16_t bSingleOT              : 1;     //BIT3 单芯温度过温
            uint16_t bSingleUV              : 1;     //BIT4 单芯电压欠压
            uint16_t bSingleOV              : 1;     //BIT5 单芯电压过压
            uint16_t bTotalModeUV           : 1;     //BIT6 模块总压欠压
            uint16_t bTotalModeOV           : 1;     //BIT7 模块总压过压
            uint16_t bReserved1             : 1;     //BIT8 预留
            uint16_t bReserved2             : 1;     //BIT9 预留
            uint16_t bReserved3             : 1;     //BIT10 预留
            uint16_t bReserved4             : 1;     //BIT11 预留
            uint16_t bReserved5             : 1;     //BIT12 预留
            uint16_t bReserved6             : 1;     //BIT13 预留
            uint16_t bReserved7             : 1;     //BIT14 预留
            uint16_t bReserved8             : 1;     //BIT15 预留
        }Bits;
    }SystemError1_t;                                //系统保护状态 1

    union
    {
        uint16_t u16Error;
        struct
        {
            uint16_t bReserved0             : 1;     //BIT0 预留
            uint16_t bReserved1             : 1;     //BIT1 预留
            uint16_t bReserved2             : 1;     //BIT2 预留
            uint16_t bSysFault              : 1;     //BIT3 系统故障保护
            uint16_t bReserved3             : 1;     //BIT4 预留
            uint16_t bOCD                   : 1;     //BIT5 放电过流告警
            uint16_t bOCC                   : 1;     //BIT6 充电过流告警
            uint16_t bReserved4             : 1;     //BIT7 预留
            uint16_t bReserved5             : 1;     //BIT8 预留
            uint16_t bReserved6             : 1;     //BIT9 预留
            uint16_t bReserved7             : 1;     //BIT10 预留
            uint16_t bReserved8             : 1;     //BIT11 预留
            uint16_t bReserved9             : 1;     //BIT12 预留
            uint16_t bReserved10            : 1;     //BIT13 预留
            uint16_t bReserved11            : 1;     //BIT14 预留
            uint16_t bReserved12            : 1;     //BIT15 预留
        }Bits;
    }SystemError2_t;                                //系统保护状态 2
}Display_BMS_Fault_t;

typedef struct
{
    union
    {
        uint8_t u8Error;
        struct
        {
            uint8_t bReserved0             : 1;     //BIT0 预留
            uint8_t bOV                    : 1;     //BIT1 电压过压
            uint8_t bUV                    : 1;     //BIT2 电压欠压
            uint8_t bOT                    : 1;     //BIT3 过温
            uint8_t bUT                    : 1;     //BIT4 欠温
            uint8_t bReserved1             : 1;     //BIT5 预留
            uint8_t bReserved2             : 1;     //BIT6 预留
            uint8_t bOCD                   : 1;     //BIT7 放电过流
        }Bits;
    }Protect0_t;                                    //保护0
    union
    {
        uint8_t u8Error;
        struct
        {
            uint8_t bOCC                   : 1;     //BIT0 充电过流            
            uint8_t bReserved0             : 1;     //BIT1 预留
            uint8_t bReserved1             : 1;     //BIT2 预留
            uint8_t bFault                 : 1;     //BIT3 故障
            uint8_t bReserved2             : 1;     //BIT4 预留
            uint8_t bReserved3             : 1;     //BIT5 预留
            uint8_t bReserved4             : 1;     //BIT6 预留
            uint8_t bReserved5             : 1;     //BIT7 预留
        }Bits;
    }Protect1_t;                                    //保护1   
    union
    {
        uint8_t u8Warnning;
        struct
        {
            uint8_t bReserved0             : 1;     //BIT0 预留
            uint8_t bHV                    : 1;     //BIT1 电压过压
            uint8_t bLV                    : 1;     //BIT2 电压欠压
            uint8_t bHT                    : 1;     //BIT3 过温
            uint8_t bLT                    : 1;     //BIT4 欠温
            uint8_t bReserved1             : 1;     //BIT5 预留
            uint8_t bReserved2             : 1;     //BIT6 预留
            uint8_t bOCD                   : 1;     //BIT7 放电大电流
        }Bits;
    }Alarm0_t;                                      //告警0
    union
    {
        uint8_t u8Warnning;
        struct
        {
            uint8_t bOCC                   : 1;     //BIT0 充电大电流           
            uint8_t bReserved0             : 1;     //BIT1 预留
            uint8_t bReserved1             : 1;     //BIT2 预留
            uint8_t bOffline               : 1;     //BIT3 掉线
            uint8_t bReserved2             : 1;     //BIT4 预留
            uint8_t bReserved3             : 1;     //BIT5 预留
            uint8_t bReserved4             : 1;     //BIT6 预留
            uint8_t bReserved5             : 1;     //BIT7 预留
        }Bits;
    }Alarm1_t;                                      //告警1
}Display_BMSCan_Fault_t;                           //保护与告警帧

//界面操作类型
typedef enum
{
    OPERATE_OBJ_START,
    OPERATE_OBJ_LOCAL_EMS,                           //本地EMS
    OPERATE_OBJ_REMOTE_EMS,                          //远程EMS
    OPERATE_OBJ_UPPER_COMPUTER,                      //上位机
    OPERATE_OBJ_END                                  //
}OperateObj_TypeDef;

typedef struct
{
    Display_SYS_Fault_t tSysFault;
    Display_SYS_Alarm_t tSysAlarm;
    Display_PV_Fault_t tPvFault;
    Display_INV_Fault_t tInvFault;
    Display_DCDC_Fault_t tDCDCFault;
    Display_Gen_Fault_t tGenFault;
}Display_PCS_Fault_t;

typedef enum
{
    DEVICESTATE_NULL,
    DEVICESTATE_NORMAL,//正常
    DEVICESTATE_ALARM, //告警
    DEVICESTATE_FAULT  //故障
}Display_Device_Fault_t;

typedef struct
{
    union
    {
        uint16_t u16Error;
        struct
        {
            uint16_t bEMSErr                : 1;     //BIT0 预留
            uint16_t bPcsCommState          : 1;     //BIT1 PCS通信状态
            uint16_t bMeterCommState        : 1;     //BIT2 电表通讯状态
            uint16_t bBmsCommState          : 1;     //BIT3 电池包通信状态
            uint16_t bCTCommState           : 1;     //BIT4 CT通信状态
            uint16_t bWeakBatteryFault      : 1;     //BIT5 弱电池故障
            uint16_t bReserved4             : 1;     //BIT6 预留
            uint16_t bReserved5             : 1;     //BIT7 预留
            uint16_t bReserved6             : 1;     //BIT8 预留
            uint16_t bReserved7             : 1;     //BIT9 预留
            uint16_t bReserved8             : 1;     //BIT10 预留
            uint16_t bReserved9             : 1;     //BIT11 预留
            uint16_t bReserved10            : 1;     //BIT12 预留
            uint16_t bReserved11            : 1;     //BIT13 预留
            uint16_t bReserved12            : 1;     //BIT14 预留
            uint16_t bReserved13            : 1;     //BIT15 预留
        }Bits;
    }EmsError_t;                                     //EMS故障
}Display_EMS_Fault_t;
typedef struct
{
    Display_PCS_Fault_t     tPCSFault;
    Display_BMS_Fault_t     tBMSFault;
    Display_BMSCan_Fault_t  tBMSCanFault;
    Display_EMS_Fault_t     tEMSFault;
    Display_Device_Fault_t  eDeviceFault;
}Display_Fault_t;

//界面操作类型
typedef enum
{
    Record_START                                           = 0x0000,
    RECORD_SET_Language                                    = 0x0001,                //语言设置
    RECORD_SET_Time                                        = 0x0002,                //时间设置
    RECORD_SET_Password                                    = 0x0003,                //密码设置
    RECORD_SET_ClearFault                                  = 0x0004,                //清除故障
    RECORD_SET_ClearRecord                                 = 0x0005,                //清除操作记录
    RECORD_SET_Serial                                      = 0x0006,                //串口设置
    RECORD_SET_Factory                                     = 0x0007,                //出厂设置
    RECORD_SET_WIFI_RESET                                  = 0x0008,                //WIFI复位
    RECORD_SET_BLT_RESET                                   = 0x0009,                //蓝牙复位
    RECORD_SET_Local_Control                               = 0x000A,                //远程控制设置
    RECORD_SET_Remote_Control                              = 0x000B,                //远程控制设置
    RECORD_SET_STRATEGY_SELFUSE                            = 0x000C,                //自发自用策略设置
    RECORD_SET_TPFV_TIP_PERIOD_ONE                         = 0x000D,                //TPFV tip 时间段 1策略设置
    RECORD_SET_TPFV_TIP_PERIOD_TWO                         = 0x000E,                  //TPFV tip 时间段 2策略设置
    RECORD_SET_TPFV_TIP_PERIOD_THREE                       = 0x000F,                //TPFV tip 时间段 3策略设置
    RECORD_SET_TPFV_PEAK_PERIOD_ONE                        = 0x0010,                 //TPFV peak 时间段 1策略设置
    RECORD_SET_TPFV_PEAK_PERIOD_TWO                        = 0x0011,                 //TPFV peak 时间段 2策略设置
    RECORD_SET_TPFV_PEAK_PERIOD_THREE                      = 0x0012,               //TPFV peak 时间段 3策略设置
    RECORD_SET_TPFV_FLAT_PERIOD_ONE                        = 0x0013,                 //TPFV plat 时间段 1策略设置
    RECORD_SET_TPFV_FLAT_PERIOD_TWO                        = 0x0014,                 //TPFV plat 时间段 2策略设置
    RECORD_SET_TPFV_FLAT_PERIOD_THREE                      = 0x0015,               //TPFV plat 时间段 3策略设置
    RECORD_SET_TPFV_VALLEY_PERIOD_ONE                      = 0x0016,               //TPFV valley 时间段 1策略设置
    RECORD_SET_TPFV_VALLEY_PERIOD_TWO                      = 0x0017,               //TPFV valley 时间段 2策略设置
    RECORD_SET_TPFV_VALLEY_PERIOD_THREE                    = 0x0018,             //TPFV valley 时间段 3策略设置
    RECORD_SET_CHARGE_ONE                                  = 0x0019,                //定时充电策略时间段一设置
    RECORD_SET_CHARGE_TWO                                  = 0x001A,                //定时充电策略时间段二设置
    RECORD_SET_CHARGE_THREE                                = 0x001B,                //定时充电策略时间段三设置
    RECORD_SET_CHARGE_FOUR                                 = 0x001C,                //定时充电策略时间段四设置
    RECORD_SET_DISCHARGE_ONE                               = 0x001D,                //定时放电策略时间段一设置
    RECORD_SET_DISCHARGE_TWO                               = 0x001E,                //定时放电策略时间段二设置
    RECORD_SET_DISCHARGE_THREE                             = 0x001F,                //定时放电策略时间段三设置
    RECORD_SET_DISCHARGE_FOUR                              = 0x0020,                //定时放电策略时间段四设置
    RECORD_SET_STRATEGY_BACKUP                             = 0x0021,                //备电策略
    RECORD_SET_STRATEGY_GEN                                = 0x0022,                //发电机策略设置
    RECORD_SET_SYSTEM_DETECTION                            = 0x0023,                //绝缘阻抗检测
    RECORD_SET_PROTECT_ISLAND                              = 0x0024,                //孤岛保护使能设置
    RECORD_SET_PROTECT_GROUND                              = 0x0025,                //接地保护使能设置
    RECORD_SET_PROTECT_LEAKAG                              = 0x0026,                //漏电保护使能设置
    RECORD_SET_PROTECT_ARC                                 = 0x0027,                //拉弧保护使能设置
    RECORD_SET_PROTECT_LVRT                                = 0x0028,                //低电压穿越保护使能设置
    RECORD_SET_PROTECT_HVRT                                = 0x0029,                //高电压穿越保护使能设置
    RECORD_SET_PROTECT_LIGHT                               = 0x002A,                //防雷保护使能设置
    RECORD_SET_PROTECT_GEN                                 = 0x002B,                //发电机保护使能设置
    RECORD_SET_PROTECT_LFRT                                = 0x002C,                //低频率穿越保护使能设置
    RECORD_SET_PROTECT_HFRT                                = 0x002D,                //高频率穿越保护使能设置
    RECORD_SET_PROTECT_P_V                                 = 0x002E,                //P(V)保护使能设置    
    RECORD_SET_PROTECT_P_F                                 = 0x002F,                //P(F)保护使能设置
    RECORD_SET_PROTECT_Q_V                                 = 0x0030,                //Q(V)保护使能设置
    RECORD_SET_PROTECT_Q_P                                 = 0x0031,                //Q(P)保护使能设置
    RECORD_SET_PROTECT_CPF                                 = 0x0032,                //CPF保护使能设置
    RECORD_SET_PROTECT_CQ                                  = 0x0033,                //CQ保护使能设置
    RECORD_SET_PV_CONTROLWAY                               = 0x0034,                //光伏控制方式设置
    RECORD_SET_PV_SCAN                                     = 0x0035,                //光伏IV扫描设置
    RECORD_SET_BATTERY_ENABLE                              = 0x0036,                //电池使能
    RECORD_SET_BATTERY_WAKEUP                              = 0x0037,                //电池唤醒
    RECORD_SET_BATTERY_MANUFACT                            = 0x0038,                //电池厂商
    RECORD_SET_BATTERY_TYPE                                = 0x0039,                //电池类型设置
    RECORD_SET_SELL                                        = 0x003A,                //电网买电使能设置界面
    RECORD_SET_GRID_METER                                  = 0x003B,                //电表设置界面 
    RECORD_SET_GRID_SR                                     = 0x003C,                //安规设置
    RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_TIP                 = 0x003E,                //电网尖时电价设置
    RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_TIP_PERIOD_ONE      = 0x003F,                //电网尖时时间段一设置
    RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_TIP_PERIOD_TWO      = 0x0040,                //电网尖时时间段二设置
    RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_TIP_PERIOD_THREE    = 0x0041,                //电网尖时时间段三设置
    RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_PEAK                = 0x0042,                //电网峰时电价设置
    RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_PEAK_PERIOD_ONE     = 0x0043,                //电网峰时时间段一设置
    RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_PEAK_PERIOD_TWO     = 0x0044,                //电网峰时时间段一设置
    RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_PEAK_PERIOD_THREE   = 0x0045,                //电网峰时时间段一设置
    RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_FLAT                = 0x0046,                //电网平时电价设置
    RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_FLAT_PERIOD_ONE     = 0x0047,                //电网平时时间段一设置
    RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_FLAT_PERIOD_TWO     = 0x0048,                //电网平时时间段二设置
    RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_FLAT_PERIOD_THREE   = 0x0049,                //电网平时时间段三设置
    RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_VALLEY              = 0x004A,                //电网谷时电价设置
    RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_VALLEY_PERIOD_ONE   = 0x004B,                //电网谷时时间段一设置
    RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_VALLEY_PERIOD_TWO   = 0x004C,                //电网谷时时间段二设置
    RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_VALLEY_PERIOD_THREE = 0x004E,                //电网谷时时间段三设置
    RECORD_SET_GRID_REACTIVEPOWERCONTROLWAY                = 0x004F,                //无功控制方式修改设置
    RECORD_SET_GRID_REACTIVEPOWER                          = 0x0050,                //无功功率设置
    RECORD_SET_GRID_POWERFACTOR                            = 0x0051,                //功率因数设置
    RECORD_SET_GEN                                         = 0x0052,                //发电机设置界面
    RECORD_SET_LOWPOWER                                    = 0x0053,                //低功耗使能
    Record_END
}Record_TypeDef;

typedef struct
{
    uint8_t   u8No;                          //序号
    uint16_t  u16RecordType;                 //操作类型
    uint8_t   u8RecordObj;                   //操作对象
    Fault_System_TimeSync stOperateTime;     //操作记录产生时间
}Display_Record_Info;

typedef struct
{
    uint8_t u8RecordIndex;
    Display_Record_Info stRecord[DISPLAY_DATA_ORRECORD_MAX_COUNT];
}Record_Info;

//Fault管理总初始化函数
extern void FaultInit(void);
//Fault管理总运行函数
extern void FaultRunning(void);
//Fault管理析构函数
extern void FaultDestruction(void);
//故障告警管理处理总入口函数,给main模块存储模块总接口函数
extern void FaultManagement_Handler(void);
//初始化变量函数
extern void Fault_Service_InitVar(void);
//故障告警管理析构
extern void Fault_Service_DestructionVar(void);
//初始化变量函数
extern void Fault_Service_HwInit(void);
//获取历史故障接口函数
extern Fault_Info_History* Display_Get_HistoryFaultData(void);
//获取实时故障接口函数
extern Fault_Info_Real* Display_Get_RealFaultData(void);
//获取操作记录接口函数
extern Record_Info* Display_Get_OperationRecordData(void);
//清除历史故障接口函数
extern void Display_Clear_HistoryFaultData(void);
//清除实时故障接口函数
extern void Display_Clear_RealFaultData(void);
//清除操作记录接口函数
extern void Display_Clear_OperationRecordData(void);
//操作记录队列插入一条记录
extern void InsertOperationRecordQueue(Display_Record_Info* pRecord);
//获取整套设备故障状态
extern void GetDisplayDeviceFaultState(Display_Fault_t* ptDisplayFault);

#endif

/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
