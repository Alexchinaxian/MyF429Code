/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Modbus_PCS_COMData.h
 用途 : modbusPCS协议数据头文件
***********************************************************************************************************************/
#ifndef _MODBUS_PCS_COMDATA_H_
#define _MODBUS_PCS_COMDATA_H_

#include "HeadFile.h"
#include "Modbus.h"
#include "LCD_Service.h"
#include "Fault_Management_Service.h"
#include "Indication_Management_Service.h"
#include "Battery_Protect_Service.h"

/*区别PCS协议不同模块数据的地址位              */

#define    EMS_TO_PCS_01H_PROT_0x010x                   (0x0100)
#define    EMS_TO_PCS_01H_DEBUG_0x013x                  (0x0130)
#define    EMS_TO_PCS_01H_DEBUG_0x014x                  (0x0140)
#define    EMS_TO_PCS_01H_PROT_EN_0x015x                (0x0150)
#define    EMS_TO_PCS_01H_PROT_EN_0x016x                (0x0160)
#define    EMS_TO_PCS_01H_SYS_CTRL_0x017x               (0x0170)

#define    EMS_TO_PCS_03H_TOTAL_PARAM_0x10xx            (0x1000)
#define    EMS_TO_PCS_03H_PV_INFO_0x11xx                (0x1100)
#define    EMS_TO_PCS_03H_PV1_INFO_0x110x               (0x1100)
#define    EMS_TO_PCS_03H_PV2_INFO_0x111x               (0x1110)
#define    EMS_TO_PCS_03H_INV_INFO_0x12xx               (0x1200)
#define    EMS_TO_PCS_03H_DCDC_INFO_0x13xx              (0x1300)
#define    EMS_TO_PCS_03H_ATE_0x32xx                    (0x3200)

#define    EMS_TO_PCS_03H10H_PV_CTRL_0x20xx             (0x2000)
#define    EMS_TO_PCS_03H10H_INV_CTRL_0x21xx            (0x2100)
#define    EMS_TO_PCS_03H10H_DCDC_CTRL_0x22xx           (0x2200)
#define    EMS_TO_PCS_03H10H_SYS_PARAM_0x23xx           (0x2300)
#define    EMS_TO_PCS_03H10H_COM_PARAM_0x24xx           (0x2400)
#define    EMS_TO_PCS_03H10H_LINE_VP_0x25xx             (0x2500)
#define    EMS_TO_PCS_03H10H_SYS_INFO_0x26xx            (0x2600)
#define    EMS_TO_PCS_03H10H_METER_0x27xx               (0x2700)
#define    EMS_TO_PCS_03H10H_INV_STD_0x2Exx             (0x2E00)
#define    EMS_TO_PCS_03H10H_ATE_0x31xx                 (0x3100)

#define    EMS_TO_PCS_05H_DATA_0x02xx                   (0x0200)

#define    EMS_TO_PCS_10H_SR_INFO_0x28xx                (0x2800)
#define    EMS_TO_PCS_10H_EMS_CONTROL_0x29xx            (0x2900)
#define    EMS_TO_PCS_10H_EMS_PARAM_0x2Fxx              (0x2F00)
#define    EMS_TO_PCS_10H_ATE_0x30xx                    (0x3000)

#define    EMS_TO_PCS_10H_ACTIVE_POWER_0x2F02           (0x2F02)
#define    EMS_TO_PCS_10H_POWER_FACTOR_0x2F13           (0x2F13)

#define    EMS_TO_PCS_03H10H_TEMP_0x2630                (0x2630)
#define    EMS_TO_PCS_03H10H_TEMP_0x2634                (0x2634)
#define    EMS_TO_PCS_03H10H_SERIAL_0x2601              (0x2601)
#define    EMS_TO_PCS_03H10H_MODEL_0x2610               (0x2610)

#define    EMS_TO_PCS_03H10H_BMS_0x2F03                 (0x2F03)

#define    EMS_TO_PCS_03H10H_BMS_Length                 (0x0006)
#define    EMS_TO_PCS_03H10H_TEMP_Length                (0x0006)

#define    EMS_TO_PCS_Set_SingleReg_Length              (0x0001)

typedef union
{
    uint16_t u16word;
    struct
    {
        uint16_t bEnergyManageSetFlag       : 1;         //BIT0 能量管理下设标志位
        uint16_t bPowerOnOffSetFlag         : 1;         //BIT1 启停控制下设标志位
        uint16_t bGridStandardSetFlag       : 1;         //BIT2 安规信息下设
        uint16_t bReactivePowerFlag         : 1;         //BIT3 无功功率下设
        uint16_t bPowerFactorFlag           : 1;         //BIT4 功率因数下设
        uint16_t bInvAdjParaFlag            : 1;         //BIT5 逆变器校准系数下设
        uint16_t bReserved4                 : 1;         //BIT6 预留
        uint16_t bReserved5                 : 1;         //BIT7 预留
        uint16_t bReserved6                 : 1;         //BIT8 预留
        uint16_t bReserved7                 : 1;         //BIT9 预留
        uint16_t bReserved8                 : 1;         //BIT10 预留
        uint16_t bReserved9                 : 1;         //BIT11 预留
        uint16_t bReserved10                : 1;         //BIT12 预留
        uint16_t bReserved11                : 1;         //BIT13 预留
        uint16_t bReserved12                : 1;         //BIT14 预留
        uint16_t bReserved13                : 1;         //BIT15 预留
    }Bits;
}ExternalSetPCSFlag_t;

extern ExternalSetPCSFlag_t externalSetFlag;

/******************************************************************
 ModbusPCS协议数据结构
*******************************************************************/

/******************************************************************
 0X01读线圈数据（遥信）保护参数数据：
*******************************************************************/
typedef struct
{
    uint16_t u16BusOVP;                                    //0x0100 直流母线电压过压动作
    uint16_t u16BusUVP;                                    //0x0101 直流母线电压欠压动作
    uint16_t u16IslandProt;                                //0x0102 孤岛保护动作
    uint16_t u16GroundProt;                                //0x0103 接地保护动作
    uint16_t u16LeakageProt;                               //0x0104 漏电保护动作
    uint16_t u16ARCProt;                                   //0x0105 拉弧保护动作
    uint16_t u16OverHeatProt;                              //0x0106 过热保护动作
    uint16_t u16LowVoltRideProt;                           //0x0107 低电压穿越保护动作
    uint16_t u16HighVoltRideProt;                          //0x0108 高电压穿越保护动作
    uint16_t u16LightingProt;                              //0x0109 防雷保护动作
    uint16_t u16GeneratorProt;                             //0x010A 发电机保护动作
    uint16_t u16InternalComErr;                            //0x010B 主从通讯异常动作
    uint16_t u16BusBoardError;                             //0x010C 母线电路板连接异常动作
    //0x010D~0x010F 预留
}ProtData_t;
#define PCS_01H_PROT_PARAM_START                           (0x0100)
#define PCS_01H_PROT_LENGTH                                (sizeof(ProtData_t) / 2)

/******************************************************************
 0X01读取DI状态数据（遥信）调试模式数据：
 0X0F遥控命令数据 调试模式数据：
*******************************************************************/
typedef struct
{
    uint16_t u16DebugModeEn;                               //0x0130 调试模式使能
    uint16_t u16DebugRlyGridL;                             //0x0131 网侧继电器L调试
    uint16_t u16DebugRlyGridN;                             //0x0132 网侧继电器N调试
    uint16_t u16DebugRlyInv;                               //0x0133 逆变器侧继电器调试
    uint16_t u16DebugRlyGen;                               //0x0134 发电机侧继电器调试
    uint16_t u16DebugRlyLoad;                              //0x0135 负载侧继电器调试
    uint16_t u16DebugRlyOffGrid;                           //0x0136 离网继电器调试
    uint16_t u16DebugRlyInvSoftStart;                      //0x0137 逆变器侧软起继电器调试
    uint16_t u16InvPwmEn;                                  //0x0138 逆变PWM使能
    uint16_t u16BuckPwmEn;                                 //0x0139 BuckPWM使能
    uint16_t u16BoostPwmEn;                                //0x013A BoostPWM使能
    uint16_t u16LLCChgPwmEn;                               //0x013B LLC充电PWM使能
    uint16_t u16LLCDisChgPwmEn;                            //0x013C LLC放电PWM使能
    uint16_t u16PV1BuckPWMEn;                              //0x013D PV1BuckPWM使能
    uint16_t u16PV1BoostPwmEn;                             //0x013E PV1BoostPWM使能
    uint16_t u16PV2BuckPWMEn;                              //0x013F PV2BuckPWM使能
    uint16_t u16PV2BoostPwmEn;                             //0x0140 PV2BoostPWM使能
    uint16_t u16PV1InsulationImpedanceRly;                 //0x0141 PV1绝缘阻抗继电器测试
    uint16_t u16PV2InsulationImpedanceRly;                 //0x0142 PV2绝缘阻抗继电器测试
    uint16_t u16FanPwmEN;                                  //0x0143 风扇PWM使能
    uint16_t u16McuLRly;                                   //0x0144 MCU网侧继电器L调试
    uint16_t u16McuNRly;                                   //0x0145 MCU网侧继电器N调试
    //0x0146-0x014F 预留
}DebugMode_t;
#define PCS_01H_DEBUG_MODE_START                           (0x0130)
#define PCS_0FH_DEBUG_MODE_START                           (0x0130)
#define PCS_01H_DEBUG_LENGTH                               (sizeof(DebugMode_t) / 2)
#define PCS_0FH_DEBUG_LENGTH                               (sizeof(DebugMode_t) / 2)

/******************************************************************
 0X01读取DI状态数据（遥信）保护使能数据：
 0X0F遥控命令数据 保护使能数据：
*******************************************************************/
typedef struct
{
    uint16_t u16IslandProt;                                //0x0150 孤岛保护
    uint16_t u16GroundProt;                                //0x0151 接地保护
    uint16_t u16LeakageProt;                               //0x0152 漏电保护
    uint16_t u16ARCProt;                                   //0x0153 拉弧保护
    uint16_t u16OverHeatProt;                              //0x0154 过热保护
    uint16_t u16LowVoltRideProt;                           //0x0155 低电压穿越保护
    uint16_t u16HighVoltRideProt;                          //0x0156 高电压穿越保护
    uint16_t u16LightingProt;                              //0x0157 防雷保护
    uint16_t u16GeneratorProt;                             //0x0158 发电机保护
    uint16_t u16InsulationResProt;                         //0x0159 绝缘阻抗保护
    uint16_t u16LowfreqRideThroughProt;                    //0x015A 低频率穿越保护
    uint16_t u16HighfreqRideThroughProt;                   //0x015B 高频率穿越保护
    uint16_t u16PVoltProt;                                 //0x015C P(V)保护
    uint16_t u16PFreqProt;                                 //0x015D P(F)保护
    uint16_t u16QVoltProt;                                 //0x015E Q(V)保护
    uint16_t u16QPProt;                                    //0x015F Q(P)保护
    uint16_t u16CPFProt;                                   //0x0160 CPF保护
    uint16_t u16CQProt;                                    //0x0161 CQ保护
    uint16_t u16NoBackflowProt;                            //0x0162 防逆流保护
    //0x0163-0x016F 预留
}ProtEn_t;
#define PCS_01H_PROT_EN_START                              (0x0150)
#define PCS_0FH_PROT_EN_START                              (0x0150)
#define PCS_01H_PROT_EN_LENGTH                             (sizeof(ProtEn_t) / 2)
#define PCS_0FH_PROT_EN_LENGTH                             (sizeof(ProtEn_t) / 2)

/******************************************************************
0X01读取DI状态数据（遥信）系统控制参数数据：
0X0F遥控命令数据 系统控制参数数据：
*******************************************************************/
typedef struct
{
    uint16_t u16GenerationClr;                             //0x0170 清除发电量
    uint16_t u16PvBusCalibrateEn;                          //0x0171 PV母线电压校准使能
    uint16_t u16MeterCommEn;                               //0x0172 发送电表通信指令
    uint16_t u16Bms485CommEn;                              //0x0173 发送BMS RS485通信指令
    uint16_t u16BmsCanCommEn;                              //0x0174 发送BMS CAN通信指令
    uint16_t u16ParaCanEmsEn;                              //0x0175 发送并机CAN EMS通信指令
    uint16_t u16ParaCanPcsEn;                              //0x0176 发送并机CAN PCS通信指令
    uint16_t u16WriteDefaultAdjust;                        //0x0177 写默认校准数据
    uint16_t u16FactoryMode;                               //0x0178 设置工厂模式
    //0x0179-0x017F 预留
}SysCtrlParam_t;
#define PCS_0FH_SYS_CTRL_START                             (0x0170)
#define PCS_0FH_SYS_CTRL_LENGTH                            (sizeof(SysCtrlParam_t) / 2)
#define PCS_01H_SYS_CTRL_START                             (0x0170)
#define PCS_01H_SYS_CTRL_LENGTH                            (sizeof(SysCtrlParam_t) / 2)


/*****************************************************************
 0X05(写单个线圈)遥控数据：
******************************************************************/
typedef struct
{
    uint16_t u16StartStopCtrl;                             //0x0200 起停控制 兼容ATE
    uint16_t u16StopSelect;                                //0x0201 Stop键停机选择
    uint16_t u16EmerStopSelect;                            //0x0202 紧急停机开关选择
    uint16_t u16ExternStartStopSelect;                     //0x0203 外部启停开关选择
    //0x0204-0x02FF 预留
}Data05H_t;
#define PCS_05H_DATA_START                                 (0x0200)
#define PCS_05H_LENGTH                                     (sizeof(Data05H_t) / 2)

/******************************************************************
 0X03读实时数据（包括遥测、遥信）共有参数数据：
*******************************************************************/
typedef struct
{
    uint16_t u16StateMachine;                              //0x1000 工作状态机
    uint16_t u16BusVolt;                                   //0x1001 直流母线电压 0.1V
    uint16_t u16ModuleSelect;                              //0x1002 机型选择
    int16_t  s16ChassisTemp;                               //0x1003 机箱温度
    uint16_t u16PF;                                        //0x1004 功率因数
    uint16_t u16RunTimeOnDay;                              //0x1005 当天运行时间
    uint16_t u16RunTimeOnWeek;                             //0x1006 当月运行时间
    uint16_t u16RunTimeOnYear;                             //0x1007 当年运行时间
    uint16_t u16TotalRunTime;                              //0x1008 总运行时间
    int16_t  s16LiveActivePower;                           //0x1009 实时有功功率
    int16_t  s16TotalGenerateOnDay;                        //0x100A 当天总发电量

    union
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
    }SysAlarm_t;                                            //0x100B 系统告警

    struct
    {
        union
        {
            uint16_t u16Error;
            struct
            {
                uint16_t bSysErr               : 1;             //BIT0 系统故障汇总
                uint16_t bBusFastOV            : 1;             //BIT1 母线过压快检
                uint16_t bBusSlowOV            : 1;             //BIT2 母线过压慢检
                uint16_t bBusUV                : 1;             //BIT3 母线欠压
                uint16_t bBusSoft              : 1;             //BIT4 软起失败
                uint16_t bEmsCommErr           : 1;             //BIT5 EMS通讯异常
                uint16_t bOutputShort          : 1;             //BIT6 输出短路
                uint16_t bGFCIErrLevel3        : 1;             //BIT7 GFCI漏电故障三级
                uint16_t bGFCIErrLevel2        : 1;             //BIT8 GFCI漏电故障二级
                uint16_t bGFCIErrLevel1        : 1;             //BIT9 GFCI漏电故障一级
                uint16_t bFWSelfLock           : 1;             //BIT10 软件自锁故障
                uint16_t bSysOT                : 1;             //BIT11 系统过温
                uint16_t bSysOverLoad          : 1;             //BIT12 过载
                uint16_t bEpo                  : 1;             //BIT13 Epo
                uint16_t bSlaveCpuErr          : 1;             //BIT14 从cpu故障
                uint16_t bIsoErr               : 1;             //BIT15 ISO故障
            }Bits;
        }SysFault1_t;                                            //0x100C-0x100D 系统故障1

        union
        {
            uint16_t u16Error;
            struct
            {
                uint16_t bSysErr               : 1;             //BIT0 系统故障汇总
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
        }SysFault2_t;                                            //0x100C-0x100D 系统故障2
    }SysFault_t;

    union
    {
        uint16_t u16State;
        struct
        {
            uint8_t bBusSoftOver          : 1;             //BIT0 母线软起完成
            uint8_t bBusStable            : 1;             //BIT1 母线稳定
            uint8_t bMidBusSoftOver       : 1;             //BIT2 中间母线软起完成
            uint8_t bCharge2Discharge1    : 1;             //BIT3 充电转放电1
            uint8_t bDisCharge2charge1    : 1;             //BIT4 放电转充电1
            uint8_t bCharge2Discharge2    : 1;             //BIT5 放电转充电2
            uint8_t bDisCharge2charge2    : 1;             //BIT6 充电转放电2
            uint8_t bSynrectificatStart   : 1;             //BIT7 同步整流启动
            uint8_t bInvLoadMode          : 1;             //BIT8 逆变器负载模式
            uint8_t bInvGenMode           : 1;             //BIT9 逆变器发电模式
            uint8_t bBatNoAccess          : 1;             //BIT10 电池未接入检测
            uint8_t bReserved0            : 1;             //BIT11 预留
            uint8_t bReserved1            : 1;             //BIT12 预留
            uint8_t bReserved2            : 1;             //BIT13 预留
            uint8_t bReserved3            : 1;             //BIT14 预留
            uint8_t bReserved4            : 1;             //BIT15 预留
        }Bits;
    }u16SysState1_t;                                       //0x100E 系统状态1
    union
    {
        uint16_t u16State;
        struct
        {
            uint8_t bBusSoftOver          : 1;             //BIT0 母线软起完成
            uint8_t bBusStable            : 1;             //BIT1 母线稳定
            uint8_t bMidBusSoftOver       : 1;             //BIT2 中间母线软起完成
            uint8_t bCharge2Discharge1    : 1;             //BIT3 充电转放电1
            uint8_t bDisCharge2charge1    : 1;             //BIT4 放电转充电1
            uint8_t bCharge2Discharge2    : 1;             //BIT5 放电转充电2
            uint8_t bDisCharge2charge2    : 1;             //BIT6 充电转放电2
            uint8_t bSynrectificatStart   : 1;             //BIT7 同步整流启动
            uint8_t bInvLoadMode          : 1;             //BIT8 逆变器负载模式
            uint8_t bInvGenMode           : 1;             //BIT9 逆变器发电模式
            uint8_t bBatNoAccess          : 1;             //BIT10 电池未接入检测
            uint8_t bSysOT                : 1;             //BIT11 系统过温
            uint8_t bReserved1            : 1;             //BIT12 预留
            uint8_t bReserved2            : 1;             //BIT13 预留
            uint8_t bReserved3            : 1;             //BIT14 预留
            uint8_t bReserved4            : 1;             //BIT15 预留
        }Bits;
    }u16SysState2_t;                                       //0x100F 系统状态2
    int16_t  s16InvRadiatorTemp;                           //0x1010 逆变器散热器温度值 预留给ATE
    int16_t  s16EnvironmentTemp;                           //0x1011 环境温度 预留给ATE
    int16_t  s16DCDCRadiatorTemp;                          //0x1012 DCDC散热器温度 预留给ATE
    uint16_t u16ArmVersion;                                //0x1013 ARM版本号 预留给ATE
    struct
    {
        uint16_t u16MainDspVerV;                           //0x1014 主DSP版本号V 兼容ATE
        uint16_t u16MainDspVerB;                           //0x1015 主DSP版本号B 兼容ATE
        uint16_t u16MainDspVerD;                           //0x1016 主DSP版本号D 兼容ATE
        uint16_t u16BackMcuVerV;                           //0x1017 副DSP版本号V 兼容ATE
        uint16_t u16BackMcuVerB;                           //0x1018 副DSP版本号B 兼容ATE
        uint16_t u16BackMcuVerD;                           //0x1019 副DSP版本号D 兼容ATE
    }tDspMcuVersion;
    uint16_t u16ModemValue;                                //0x101A Modem阻值
    uint16_t u16FactoryModeInfo;                           //0x101B 读机器工厂模式配置信息 预留给ATE
    uint16_t u16FanSpeed;                                  //0x101C 风扇转速
    uint16_t u16GenRunState;                               //0x101D 使能发电机接入标志(DSP)
    //0x101D-0x10FF 预留
}TotalParam_t;
#define PCS_03H_TOTAL_PARAM_START                          (0x1000)
#define PCS_03H_TOTAL_PARAM_LENGTH                         (sizeof(TotalParam_t) / 2)

/******************************************************************
 0X03读实时数据（包括遥测、遥信）光伏信息数据：
*******************************************************************/
typedef struct
{
    uint16_t u16PVVolt;                                    //0x1100 PV电压 兼容ATE
    int16_t  s16PVCurr;                                    //0x1101 PV电流 兼容ATE
    int16_t  s16PVLivePower;                               //0x1102 实时PV功率
    int16_t  s16PVBusVolt;                                 //0x1103 PV母线电流
    uint16_t u16PVGeneratOnDay;                            //0x1104 当日PV发电量
    struct
    {
        union
        {
            uint16_t u16Error;
            struct
            {
                uint16_t bPvErr                : 1;        //BIT0 故障
                uint16_t bPvUV                 : 1;        //BIT1 PV欠压(预留)
                uint16_t bPvOV                 : 1;        //BIT2 PV过压
                uint16_t bReserved1            : 1;        //BIT3 预留
                uint16_t bFWOI                 : 1;        //BIT4 软件过流
                uint16_t bHWOI                 : 1;        //BIT5 硬件过流
                uint16_t bLowPowerLock         : 1;        //BIT6 低功率锁定
                uint16_t bReserved2            : 1;        //BIT7 预留
                uint16_t bReserved3            : 1;        //BIT8 预留
                uint16_t bReserved4            : 1;        //BIT9 预留
                uint16_t bReserved5            : 1;        //BIT10 预留
                uint16_t bReserved6            : 1;        //BIT11 预留
                uint16_t bReserved7            : 1;        //BIT12 预留
                uint16_t bReserved8            : 1;        //BIT13 预留
                uint16_t bReserved9            : 1;        //BIT14 预留
                uint16_t bReserved10           : 1;        //BIT15 预留
            }Bits;
        }PVFault1_t;                                       //0x1105 PV故障1

        union
        {
            uint16_t u16Error;
            struct
            {
                uint16_t bReserved11           : 1;        //BIT16 预留
                uint16_t bReserved12           : 1;        //BIT17 预留
                uint16_t bReserved13           : 1;        //BIT18 预留
                uint16_t bReserved14           : 1;        //BIT19 预留
                uint16_t bReserved15           : 1;        //BIT20 预留
                uint16_t bReserved16           : 1;        //BIT21 预留
                uint16_t bReserved17           : 1;        //BIT22 预留
                uint16_t bReserved18           : 1;        //BIT23 预留
                uint16_t bReserved19           : 1;        //BIT24 预留
                uint16_t bReserved20           : 1;        //BIT25 预留
                uint16_t bReserved21           : 1;        //BIT26 预留
                uint16_t bReserved22           : 1;        //BIT27 预留
                uint16_t bReserved23           : 1;        //BIT28 预留
                uint16_t bReserved24           : 1;        //BIT29 预留
                uint16_t bReserved25           : 1;        //BIT30 预留
                uint16_t bReserved26           : 1;        //BIT31 预留
            }Bits;
        }PVFault2_t;                                       //0x1106 PV故障2
    }PVFault_t;
    uint16_t u16PVState;                                   //0x1107 PV状态
    uint16_t u16PvIosP;                                    //0x1108 PV绝缘阻抗正
    uint16_t u16PvIosN;                                    //0x1109 PV绝缘阻抗负
}PVInformation_t;
#define PCS_03H_PV1_INFO_START                             (0x1100)
#define PCS_03H_PV1_INFO_LENGTH                            (sizeof(PVInformation_t) / 2)

#define PCS_03H_PV2_INFO_START                             (0x1110)
#define PCS_03H_PV2_INFO_LENGTH                            (sizeof(PVInformation_t) / 2)

/******************************************************************
 0X03读实时数据（包括遥测、遥信）逆变器信息数据：
*******************************************************************/
typedef struct
{
    int16_t  s16InvBusVolt;                                //0x1200 逆变器母线电压 兼容ATE
    int16_t  s16InvInductanceCurrR;                        //0x1201 逆变器R相电感电流兼容ATE
    int16_t  s16InvInductanceCurrS;                        //0x1202 逆变器S相电感电流
    int16_t  s16InvInductanceCurrT;                        //0x1203 逆变器T相电感电流
    uint16_t u16InvVoltR;                                  //0x1204 逆变器R相输出电压
    uint16_t u16InvVoltS;                                  //0x1205 逆变器S相输出电压
    uint16_t u16InvVoltT;                                  //0x1206 逆变器T相输出电压
    int16_t  s16InvCurrR;                                  //0x1207 逆变器R相输出电流兼容ATE
    int16_t  s16InvCurrS;                                  //0x1208 逆变器S相输出电流
    int16_t  s16InvCurrT;                                  //0x1209 逆变器T相输出电流
    int16_t  s16InvGridCurrR;                              //0x120A 逆变器R相电网电流
    int16_t  s16InvGridCurrS;                              //0x120B 逆变器S相电网电流
    int16_t  s16InvGridCurrT;                              //0x120C 逆变器T相电网电流
    int16_t  s16InvGridWattR;                              //0x120D 逆变器R相电网有功功率
    int16_t  s16InvGridWattS;                              //0x120E 逆变器S相电网有功功率
    int16_t  s16InvGridWattT;                              //0x120F 逆变器T相电网有功功率
    int16_t  s16InvGridVarR;                               //0x1210 逆变器R相电网无功功率
    int16_t  s16InvGridVarS;                               //0x1211 逆变器S相电网无功功率
    int16_t  s16InvGridVarT;                               //0x1212 逆变器T相电网无功功率
    uint16_t u16InvGridWattGenerateOnDay;                  //0x1213 逆变器电网当日有功发电量
    uint16_t u16InvGridVarGenerateOnDay;                   //0x1214 逆变器电网当日无功发电量
    uint16_t u16InvGridFreq;                               //0x1215 逆变器电网频率
    uint16_t u16InvOutputFreq;                             //0x1216 逆变器输出频率
    int16_t  s16InvLoadCurrR;                              //0x1217 逆变器R相负载电流
    int16_t  s16InvLoadCurrS;                              //0x1218 逆变器S相负载电流
    int16_t  s16InvLoadCurrT;                              //0x1219 逆变器T相负载电流
    int16_t  s16InvLoadCurrWattR;                          //0x121A 逆变器R相负载侧有功功率
    int16_t  s16InvLoadCurrWattS;                          //0x121B 逆变器S相负载侧有功功率
    int16_t  s16InvLoadCurrWattT;                          //0x121C 逆变器T相负载侧有功功率
    int16_t  s16InvLoadCurrVarR;                           //0x121D 逆变器R相负载侧无功功率
    int16_t  s16InvLoadCurrVarS;                           //0x121E 逆变器S相负载侧无功功率
    int16_t  s16InvLoadCurrVarT;                           //0x121F 逆变器T相负载侧无功功率
    uint16_t u16GridPurchaseOnDay;                         //0x1220 电网当日购电量
    uint16_t u16GridSellOnDay;                             //0x1221 电网当日卖电量
    uint16_t u16OnGirdTimeOnDay;                           //0x1222 当日并网时间
    uint16_t u16PowerConsumptionOnDay;                     //0x1223 当日用电量
    uint16_t  u16GenVoltR;                                 //0x1224 发电机R相输出电压
    int16_t  s16GenVoltS;                                  //0x1225 发电机S相输出电压
    int16_t  s16GenVoltT;                                  //0x1226 发电机T相输出电压
    int16_t  s16GenCurrR;                                  //0x1227 发电机R相输出电流
    int16_t  s16GenCurrS;                                  //0x1228 发电机S相输出电流
    int16_t  s16GenCurrT;                                  //0x1229 发电机T相输出电流
    uint16_t u16GenSpeed;                                  //0x122A 发电机转速
    uint16_t u16GenFreq;                                   //0x122B 发电机频率
    int16_t  s16GenWattR;                                  //0x122C 发电机R相有功功率
    int16_t  s16GenWattS;                                  //0x122D 发电机S相有功功率
    int16_t  s16GenWattT;                                  //0x122E 发电机T相有功功率
    int16_t  s16GenVarR;                                   //0x123F 发电机R相无功功率
    int16_t  s16GenVarS;                                   //0x1230 发电机S相无功功率
    int16_t  s16GenVarT;                                   //0x1231 发电机T相无功功率
    uint16_t u16GenWattGenerateOnDay;                      //0x1232 发电机当日有功发电量
    uint16_t u16GenVarGenerateOnDay;                       //0x1233 发电机当日无功发电量
    uint16_t u16GenCap;                                    //0x1234 发电机容量
    int16_t  s16InvTemp;                                   //0x1235 逆变器温度
    struct
    {
        union
        {
            uint16_t u16Error;
            struct
            {
                uint16_t bGridErr               : 1;       //BIT0 电网异常汇总
                uint16_t bGridOVLv3Error        : 1;       //BIT1 电网过压三级故障
                uint16_t bGridOVLv2Error        : 1;       //BIT2 电网过压二级故障
                uint16_t bGridOVLv1Error        : 1;       //BIT3 电网过压一级故障
                uint16_t bGridUVLv3Error        : 1;       //BIT4 电网欠压三级故障
                uint16_t bGridUVLv2Error        : 1;       //BIT5 电网欠压二级故障
                uint16_t bGridUVLv1Error        : 1;       //BIT6 电网欠压一级故障(预留)
                uint16_t bGridFastOverFreq      : 1;       //BIT7 电网过频快检
                uint16_t bGridSlowOverFreq      : 1;       //BIT8 电网过频慢检
                uint16_t bGridFastUnderFreq     : 1;       //BIT9 电网欠频快检
                uint16_t bGridSlowUnderFreq     : 1;       //BIT10 电网欠频慢检
                uint16_t bIslandErr             : 1;       //BIT11 孤岛故障
                uint16_t bGridFastPowerDown     : 1;       //BIT12 电网掉电快检
                uint16_t bPllErr                : 1;       //BIT13 锁相异常
                uint16_t bSysLNReverse          : 1;       //BIT14 系统LN反接(预留)
                uint16_t bGrid10MinOV           : 1;       //BIT15 电网10分钟过压
            }Bits;
        }GridFault_t;                                      //0x1236 电网故障1

        union
        {
            uint16_t u16Error;
            struct
            {
                uint16_t bInvErr                : 1;       //BIT0 逆变器故障汇总
                uint16_t bFwFastOC              : 1;       //BIT1 软件过流快检
                uint16_t bHwOV                  : 1;       //BIT2 硬件过流(预留)
                uint16_t bFwSlowOC              : 1;       //BIT3 软件过流慢检
                uint16_t bInvRlyErr             : 1;       //BIT4 逆变器继电器故障(预留)
                uint16_t bOTP                   : 1;       //BIT5 过温故障(预留)
                uint16_t bOVP                   : 1;       //BIT6 过压故障
                uint16_t bIgbtErr               : 1;       //BIT7 IGBT故障(预留)
                uint16_t bInductanceOT          : 1;       //BIT8 电感过温(预留)
                uint16_t bVoltDcComponentErr    : 1;       //BIT9 电压直流分量故障(预留)
                uint16_t bCurrDcComponentErr    : 1;       //BIT10 电流直流分量故障
                uint16_t bReserved1             : 1;       //BIT11 预留
                uint16_t bReserved2             : 1;       //BIT12 预留
                uint16_t bReserved3             : 1;       //BIT13 预留
                uint16_t bReserved4             : 1;       //BIT14 预留
                uint16_t bReserved5             : 1;       //BIT15 预留
            }Bits;
        }DeviceFault1_t;                                   //0x1237 设备故障1

        union
        {
            uint16_t u16Error;
            struct
            {
                uint16_t bGridError             : 1;       //BIT0 电网异常汇总
                uint16_t bCTDisconnectErr       : 1;       //BIT1 CT未接故障
                uint16_t bMeterDisconnectErr    : 1;       //BIT2 电表未接故障
                uint16_t bReserved1             : 1;       //BIT3 预留
                uint16_t bReserved2             : 1;       //BIT4 预留
                uint16_t bReserved3             : 1;       //BIT5 预留
                uint16_t bReserved4             : 1;       //BIT6 预留
                uint16_t bReserved5             : 1;       //BIT7 预留
                uint16_t bReserved6             : 1;       //BIT8 预留
                uint16_t bReserved7             : 1;       //BIT9 预留
                uint16_t bReserved8             : 1;       //BIT10 预留
                uint16_t bReserved9             : 1;       //BIT11 预留
                uint16_t bReserved10            : 1;       //BIT12 预留
                uint16_t bReserved11            : 1;       //BIT13 预留
                uint16_t bReserved12            : 1;       //BIT14 预留
                uint16_t bReserved13            : 1;       //BIT15 预留
            }Bits;
        }GridFault2_t;                                   //0x1238 电网故障2

        union
        {
            uint16_t u16Error;
            struct
            {
                uint16_t ParallelErr            : 1;       //BIT0 并机故障
                uint16_t ParallelCanErr         : 1;       //BIT1 并机CAN通讯故障
                uint16_t ParaCurrShareErr       : 1;       //BIT2 并机均流故障
                uint16_t bReserved11            : 1;       //BIT3 预留
                uint16_t bReserved12            : 1;       //BIT4 预留
                uint16_t bReserved13            : 1;       //BIT5 预留
                uint16_t bReserved14            : 1;       //BIT6 预留
                uint16_t bReserved15            : 1;       //BIT7 预留
                uint16_t bReserved16            : 1;       //BIT8 预留
                uint16_t bReserved17            : 1;       //BIT9 预留
                uint16_t bReserved18            : 1;       //BIT10 预留
                uint16_t bReserved19            : 1;       //BIT11 预留
                uint16_t bReserved20            : 1;       //BIT12 预留
                uint16_t bReserved21            : 1;       //BIT13 预留
                uint16_t bReserved22            : 1;       //BIT14 预留
                uint16_t bReserved23            : 1;       //BIT15 预留
            }Bits;
       }ParallelSysFault_t;                               //0x1239 并机故障
    }InvFault_t;

    uint16_t u16InvRunState;                               //0x123A 工作状态
    uint16_t u16InvRunState2;                              //0x123B 状态2
    uint16_t u16InvRunState3;                              //0x123C 状态3

     union
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
    }GenFault_t;                                           //0x123D 发电机故障

    int16_t  s16InvPF;                                     //0x123E 逆变器功率因数
    int16_t  s16LineLeakCurr;                              //0x123F 市电漏电流 兼容ATE
    int16_t  s16InvGirdVoltR;                              //0x1240 逆变器R相电网电压 兼容ATE
    int16_t  s16InvGirdVoltS;                              //0x1241 逆变器S相电网电压 兼容ATE 预留
    int16_t  s16InvGirdVoltT;                              //0x1242 逆变器T相电网电压 兼容ATE 预留
    union
    {
        uint16_t u16Word;
        struct
        {
            uint8_t bOnGridRun              : 1;           //BIT0 并网运行
            uint8_t bOffGridRun             : 1;           //BIT1 离网运行
            uint8_t bGridNoPar              : 1;           //BIT2 有市电未并网
            uint8_t bInvClosed              : 1;           //BIT3 逆变关闭
            uint8_t bReserved1              : 1;           //BIT4 预留
            uint8_t bReserved2              : 1;           //BIT5 预留
            uint8_t bReserved3              : 1;           //BIT6 预留
            uint8_t bReserved4              : 1;           //BIT7 预留
            uint8_t bGenRun                 : 1;           //BIT8 发电机运行
            uint8_t bAILoadRun              : 1;           //BIT9 智能负载运行
            uint8_t bGenDetected            : 1;           //BIT10 检测到发电机
            uint8_t bNoGenDetected          : 1;           //BIT11 未检测到发电机
            uint8_t bReserved7              : 1;           //BIT12 预留
            uint8_t bReserved8              : 1;           //BIT13 预留
            uint8_t bReserved9              : 1;           //BIT14 预留
            uint8_t bReserved10             : 1;           //BIT15 预留
        }Bits;
    }GenRunState_t;                                        //0x1243 电网发电机运行指示状态
    uint16_t u16LoadVoltR;                                 //0x1244 逆变器R相负载电压
    uint16_t u16LoadVoltS;                                 //0x1245 逆变器S相负载电压
    uint16_t u16LoadVoltT;                                 //0x1246 逆变器T相负载电压
    //0x1247-0x12FF 预留
}InvInformation_t; 
#define PCS_03H_INV_INFO_START                             (0x1200)
#define PCS_03H_INV_INFO_LENGTH                            (sizeof(InvInformation_t) / 2)

/******************************************************************
 0X03读实时数据（包括遥测、遥信）电池DC-DC信息数据：
*******************************************************************/
typedef struct
{
    uint16_t u16BatVolt;                                   //0x1300 电池电压 兼容ATE
    int16_t  s16ChgCurr;                                   //0x1301 电池充电电流 兼容ATE
    uint16_t u16LLCOutputVolt;                             //0x1302 LLC输出电压 兼容ATE
    int16_t  s16BuckBoostInductanceCurr;                   //0x1303 buck-boost电感电流 充电：负 放电：正
    int16_t  s16BatPower;                                  //0x1304 电池功率
    uint16_t u16BatChgPowerOnDay;                          //0x1305 电池当日充电量
    uint16_t u16BatDisChgPowerOnDay;                       //0x1306 电池当日放电量
    int16_t  s16BatIgbtTemp;                               //0x1307 电池IGBT温度
    struct
    {
        union
        {
            uint16_t u16Error;
            struct
            {
                uint8_t bFault                  : 1;       //BIT0 故障
                uint8_t bMidBusOVP              : 1;       //BIT1 中间故障过压故障
                uint8_t bLLCHwOC                : 1;       //BIT2 LLC硬件过流(预留)
                uint8_t bBuckBoostHwOC          : 1;       //BIT3 BuckBoost硬件过流(预留)
                uint8_t bBuckBoostFwOC          : 1;       //BIT4 BuckBoost软件过流(预留)
                uint8_t bSOPChgOCP              : 1;       //BIT5 SOP充电过流保护(预留)
                uint8_t bSOPDisChgOCP           : 1;       //BIT6 SOP放电过流保护(预留)
                uint8_t bDCDCOverTemp           : 1;       //BIT7 DCDC过温保护(预留)
                uint8_t bBatOverVolt            : 1;       //BIT8 电池过压
                uint8_t bBatUnderVolt           : 1;       //BIT9 电池欠压
                uint8_t bReserved3              : 1;       //BIT10 预留
                uint8_t bReserved4              : 1;       //BIT11 预留
                uint8_t bReserved5              : 1;       //BIT12 预留
                uint8_t bReserved6              : 1;       //BIT13 预留
                uint8_t bReserved7              : 1;       //BIT14 预留
                uint8_t bReserved8              : 1;       //BIT15 预留
            }Bits;
        }DCDCError1_t;
    
        union
        {
            uint16_t u16Error;
            struct
            {
                uint8_t bReserved9              : 1;       //BIT0 预留
                uint8_t bReserved10             : 1;       //BIT1 预留
                uint8_t bReserved11             : 1;       //BIT2 预留
                uint8_t bReserved12             : 1;       //BIT3 预留
                uint8_t bReserved13             : 1;       //BIT4 预留
                uint8_t bReserved14             : 1;       //BIT5 预留
                uint8_t bReserved15             : 1;       //BIT6 预留
                uint8_t bReserved16             : 1;       //BIT7 预留
                uint8_t bReserved17             : 1;       //BIT8 预留
                uint8_t bReserved18             : 1;       //BIT9 预留
                uint8_t bReserved19             : 1;       //BIT10 预留
                uint8_t bReserved20             : 1;       //BIT11 预留
                uint8_t bReserved21             : 1;       //BIT12 预留
                uint8_t bReserved22             : 1;       //BIT13 预留
                uint8_t bReserved23             : 1;       //BIT14 预留
                uint8_t bReserved24             : 1;       //BIT15 预留
            }Bits;
        }Reserved1_t;
    
        union
        {
            uint16_t u16Error;
            struct
            {
                uint8_t bReserved25             : 1;       //BIT0 预留
                uint8_t bReserved26             : 1;       //BIT1 预留
                uint8_t bReserved27             : 1;       //BIT2 预留
                uint8_t bReserved28             : 1;       //BIT3 预留
                uint8_t bReserved29             : 1;       //BIT4 预留
                uint8_t bReserved30             : 1;       //BIT5 预留
                uint8_t bReserved31             : 1;       //BIT6 预留
                uint8_t bReserved32             : 1;       //BIT7 预留
                uint8_t bReserved33             : 1;       //BIT8 预留
                uint8_t bReserved34             : 1;       //BIT9 预留
                uint8_t bReserved35             : 1;       //BIT10 预留
                uint8_t bReserved36             : 1;       //BIT11 预留
                uint8_t bReserved37             : 1;       //BIT12 预留
                uint8_t bReserved38             : 1;       //BIT13 预留
                uint8_t bReserved39             : 1;       //BIT14 预留
                uint8_t bReserved40             : 1;       //BIT15 预留
            }Bits;
        }Reserved2_t;
    }DCDC_Error_t;

    uint16_t u16DCDCState1;                                //0x130B DCDC状态1
    uint16_t u16DCDCState2;                                //0x130C DCDC状态2
    uint16_t u16DCDCState3;                                //0x130D DCDC状态3
    uint16_t u16DCDCState4;                                //0x130E DCDC状态4
    int16_t  s16ChgCurrLimit;                              //0x130F 电池最大充电电流(限流)
    int16_t  s16DisChgCurrLimit;                           //0x1310 电池最大放电电流(限流)
    int16_t  s16DisChgSOPLimit;                            //0x1311 电池放电最大sop(限流)
    int16_t  s16ChgSOPLimit;                               //0x1312 电池充电最大sop(限流)
    uint16_t u16SOC;                                       //0x1313 SOC
    uint16_t u16ChgShutSoc;                                //0x1314 充电截止SOC
    uint16_t u16DisChgShutSoc;                             //0x1315 放电截止SOC
    uint16_t u16BatState;                                  //0x1316 电池状态
    //0x1317-0x13FF预留
}DCDCInformation_t;
#define PCS_03H_DCDC_INFO_START                            (0x1300)
#define PCS_03H_DCDC_INFO_LENGTH                           (sizeof(DCDCInformation_t) / 2)

typedef struct
{
    uint16_t u16PV1Volt;                                   //0x3200 预留
    uint16_t u16PV2Volt;                                   //0x3201 预留
    uint16_t u16BusVolt;                                   //0x3202 预留
    uint16_t u16MidBusVolt;                                //0x3203 预留
    uint16_t u16GridVolt;                                  //0x3204 预留
    uint16_t u16GridHCTCurr;                               //0x3205 预留
    uint16_t u16GridCTCurr;                                //0x3206 预留
    uint16_t u16InvVolt;                                   //0x3207 预留
    uint16_t u16InvHCTCurr;                                //0x3208 预留
    uint16_t u16PV1HCTCurr;                                //0x3209 预留
    uint16_t u16PV2HCTCurr;                                //0x320A 预留
    uint16_t u16PV1InsulateResistorDetectEn;               //0x320B 预留
    uint16_t u16PV2InsulateResistorDetectEn;               //0x320C 预留
    uint16_t u16InvBatVolt;                                //0x320D 预留
    uint16_t u16InvBatCurr;                                //0x320E 预留
    uint16_t u16ARMFwVersion;                              //0x320F 预留
    uint16_t u16MainMCUFwVersion;                          //0x3210 预留
    uint16_t u16SecondaryMCUFwVersion;                     //0x3211 预留
    uint16_t u16HwVersion;                                 //0x3212 预留
    uint16_t u16FactoryModeInfo;                           //0x3213 预留
    uint16_t u16InverterTemperature;                       //0x3214 预留
    uint16_t u16InvRadiatorTemperature;                    //0x3215 预留
    uint16_t u16DCDCRadiatorTemperature;                   //0x3216 预留
    //0x3217-0x32FF 预留
}ATE03H_t;
#define PCS_03H_ATE_START                                  (0x3200)
#define PCS_03H_ATE_LENGTH                                 (sizeof(ATE03H_t) / 2)

/******************************************************************
 0X03读实时数据（包括遥测、遥信）PV控制参数数据：
 0X10(写单个或多个寄存器)写设置参数 PV控制参数：
*******************************************************************/
typedef struct
{
    uint16_t u16MaxOpenVolt;                               //0x2000 最大开路电压
    int16_t  s16MaxShortVolt;                              //0x2001 最大短路电流
    uint16_t u16PVArrayVoltCtrl;                           //0x2002 光伏阵列电压控制
    uint16_t u16PVArrayVoltCtrl1;                          //0x2003 光伏阵列电压控制1
    uint16_t u16PVArrayPowerCtrl;                          //0x2004 光伏阵列功率控制
    uint16_t u16PVArrayPowerCtrl1;                         //0x2005 光伏阵列功率控制1
    uint16_t u16DisturbStep;                               //0x2006 扰动步长 预留
    uint16_t u16Proportion;                                //0x2007 比例控制参数
    uint16_t u16Differential;                              //0x2008 微分控制参数
    uint16_t u16PVParModeEnL;                              //0x2009 PV并联模式使能
    union
    {
        uint16_t u16Word;
        struct
        {
            uint8_t bPV1VolTrackEn            : 1;        //BIT0 PV1定电压跟踪使能
            uint8_t bPV2VolTrackEn            : 1;        //BIT1 PV2定电压跟踪使能
            uint8_t bReserved0                : 1;        //BIT2 预留
            uint8_t bReserved1                : 1;        //BIT3 预留
            uint8_t bReserved2                : 1;        //BIT4 预留
            uint8_t bReserved3                : 1;        //BIT5 预留
            uint8_t bReserved4                : 1;        //BIT6 预留
            uint8_t bReserved5                : 1;        //BIT7 预留
            uint8_t bReserved6                : 1;        //BIT8 预留
            uint8_t bReserved7                : 1;        //BIT9 预留
            uint8_t bReserved8                : 1;        //BIT10 预留
            uint8_t bReserved9                : 1;        //BIT11 预留
            uint8_t bReserved10               : 1;        //BIT12 预留
            uint8_t bReserved11               : 1;        //BIT13 预留
            uint8_t bReserved12               : 1;        //BIT14 预留
            uint8_t bReserved13               : 1;        //BIT15 预留
        }Bits;
    }PVVolTrackEn_t;                                      //0x200A PV定电压跟踪使能
    //0x2009-0x20FF 预留
}PvCtrlParam_t;
#define PCS_03H_10H_PV_CTRL_START                          (0x2000)
#define PCS_03H_10H_PV_CTRL_LENGTH                         (sizeof(PvCtrlParam_t) / 2)

/******************************************************************
 0X03读实时数据（包括遥测、遥信）逆变器控制参数数据：
 0X10(写单个或多个寄存器)写设置参数 逆变器控制参数：
*******************************************************************/
typedef struct
{
    uint16_t u16BusVoltRef;                               //0x2100 母线电压给定 
    int16_t  s16InvRatePower;                             //0x2101 额定功率
    uint16_t u16OnGirdVoltLoopKp;                         //0x2102 并网电压环KP 
    uint16_t u16OnGirdVoltLoopKi;                         //0x2103 并网电压环Ki 
    uint16_t u16OnGirdVoltLoopKd;                         //0x2104 并网电压环kd 
    int16_t  s16OnGirdCurrRef;                            //0x2105 并网电流环电流给定
    int16_t  s16OnGirdCurrLoopKp;                         //0x2106 并网电流环kp
    int16_t  s16OnGirdCurrLoopKi;                         //0x2107 并网电流环ki
    int16_t  s16OnGirdCurrLoopKd;                         //0x2108 并网电流环kd
    uint16_t u16OffGirdCurrLoopKp;                        //0x2109 离网电压环kp
    uint16_t u16OffGirdCurrLoopKi;                        //0x210A 离网电压环ki
    uint16_t u16OffGirdCurrLoopKd;                        //0x210B 离网电压环kd
    uint16_t u16OffGridResFactor;                         //0x210C 离网阻尼系数r
    uint16_t u16InvTaskMode;                              //0x210D 工作模式 
    uint16_t u16VarCtrlSelect;                            //0x210E 无功功率控制选择 
    int16_t  s16VarCompensate;                            //0x210F 补偿无功功率值 
    uint16_t u16FaultClr;                                 //0x2110 清除故障记录 
    int16_t  s16InvWatt;                                  //0x2111 有功功率 兼容ATE
    int16_t  s16InvVar;                                   //0x2112 无功功率
    //0x2113~0x21FF 预留
}InvCtrlParam_t;
#define PCS_03H_10H_INV_CTRL_START                        (0x2100)
#define PCS_03H_10H_INV_CTRL_LENGTH                       (sizeof(InvCtrlParam_t) / 2)

/******************************************************************
 0X03读实时数据（包括遥测、遥信）DCDC电池控制参数数据：
 0X10(写单个或多个寄存器)写设置参数 DCDC电池控制参数数据：
*******************************************************************/
typedef struct
{
    uint16_t u16BatCap;                                   //0x2200 电池容量
    uint16_t u16BatType;                                  //0x2201 电池类型
    int16_t  s16BatRatePower;                             //0x2202 额定功率
    int16_t  s16BatRateCurr;                              //0x2203 额定电流
    uint16_t u16BatRateVolt;                              //0x2204 额定电压
    uint16_t u16BatVoltLoopKp;                            //0x2205 电池电压环kp
    uint16_t u16BatVoltLoopKi;                            //0x2206 电池电压环ki
    uint16_t u16BatCurrLoopKp;                            //0x2207 电池电流环kp
    uint16_t u16BatResFactor;                             //0x2208 电池阻尼系数r
    uint16_t  u16BatChgCurrRef;                           //0x2209 电池充电电流给定
    uint16_t  u16BatDisChgCurrRef;                        //0x220A 电池放电电流给定
    //0x220B-0x22FF 预留
}BatCtrlParam_t;
#define PCS_03H_10H_BAT_CTRL_START                        (0x2200)
#define PCS_03H_10H_BAT_CTRL_LENGTH                       (sizeof(BatCtrlParam_t) / 2) 

/******************************************************************
 0X03读实时数据（包括遥测、遥信）系统参数数据：
 0X10(写单个或多个寄存器)写设置参数 系统参数数据：
*******************************************************************/
typedef struct
{
    uint16_t u16SysYear;                                  //0x2300 日期校正-年
    uint16_t u16SysMonth;                                 //0x2301 日期校正-月
    uint16_t u16SysDay;                                   //0x2302 日期校正-日
    uint16_t u16SysHour;                                  //0x2303 时间校正-时
    uint16_t u16SysMinute;                                //0x2304 时间校正-分
    uint16_t u16SysSecond;                                //0x2305 时间校正-秒
    uint16_t u16SysWeek;                                  //0x2306 时间校正-周
    //0x2307-0x23FF 预留
}SysParam_t;
#define PCS_03H_10H_SYS_PARAM_START                       (0x2300)
#define PCS_03H_10H_SYS_PARAM_LENGTH                      (sizeof(SysParam_t) / 2)

/******************************************************************
 0X03读实时数据（包括遥测、遥信）通讯参数数据：
 0X10(写单个或多个寄存器)写设置参数 通讯参数数据：
*******************************************************************/
typedef struct
{
    uint16_t u16ComProtocol;                              //0x2400 通讯协议
    uint16_t u16LocalComAddr;                             //0x2401 本机通讯地址
    uint16_t u16ComBaudRate;                              //0x2402 通讯波特率
    uint16_t u16ComDataFormat;                            //0x2403 通讯数据格式
    uint16_t u16ComErrDetectTime;                         //0x2404 通讯断线检出时间
    //0x2405-0x24FF 预留
}ComParam_t;
#define PCS_03H_10H_COM_PARAM_START                       (0x2400)
#define PCS_03H_10H_COM_PARAM_LENGTH                      (sizeof(ComParam_t) / 2)

/******************************************************************
 0X03读实时数据（包括遥测、遥信）市电过压保护数据：
 0X10(写单个或多个寄存器)写设置参数 市电过压保护数据：
*******************************************************************/
typedef struct
{
    uint16_t u16LineOVLv1;                                //0x2500 市电一级过压保护值
    uint16_t u16LineOVLv2;                                //0x2501 市电二级过压保护值
    uint16_t u16LineUVLv1;                                //0x2502 市电一级欠压保护值
    uint16_t u16LineUVLv2;                                //0x2503 市电二级欠压保护值
    uint16_t u16LineUVLv3;                                //0x2504 市电三级欠压保护值
    uint16_t u16LineOverFreqLv1;                          //0x2505 市电一级过频保护值
    uint16_t u16LineOverFreqLv2;                          //0x2506 市电二级过频保护值
    uint16_t u16LineUnderFreqLv1;                         //0x2507 市电一级欠频保护值
    uint16_t u16LineUnderFreqLv2;                         //0x2508 市电二级欠频保护值
    uint16_t u16LineOVRecovery;                           //0x2509 市电过压恢复值
    uint16_t u16LineUVRecovery;                           //0x250A 市电欠压恢复值
    uint16_t u16LineOverFreqRecovery;                     //0x250B 市电过频恢复值
    uint16_t u16LineUnderFreqRecovery;                    //0x250C 市电欠频恢复值
    uint16_t u16LineOVLv1Time;                            //0x250D 市电一级过压保护时间
    uint16_t u16LineOVLv2Time;                            //0x250E 市电二级过压保护时间
    uint16_t u16LineUVLv1Time;                            //0x250F 市电一级欠压保护时间
    uint16_t u16LineUVLv2Time;                            //0x2510 市电二级欠压保护时间
    uint16_t u16LineUVLv3Time;                            //0x2511 市电三级欠压保护时间
    uint16_t u16LineOverFreqLv1Time;                      //0x2512 市电一级过频保护时间
    uint16_t u16LineOverFreqLv2Time;                      //0x2513 市电二级过频保护时间
    uint16_t u16LineUnderFreqLv1Time;                     //0x2514 市电一级欠频保护时间
    uint16_t u16LineUnderFreqLv2Time;                     //0x2515 市电二级欠频保护时间
    uint16_t u16LineOV10Min;                              //0x2516 市电10分钟过压保护
    uint16_t u16ReconnectTime;                            //0x2517 重连时间
    uint16_t u16GridLeakCurrUpLimit1;                     //0x2518 市电漏电流上限值1
    uint16_t u16GridLeakCurrUpLimit2;                     //0x2519 市电漏电流上限值2
    uint16_t u16GridLeakCurrUpLimit3;                     //0x251A 市电漏电流上限值3
    uint16_t u16HighSideOVPValueLv1;                      //0x251B 高穿一级过压保护值
    uint16_t u16HighSideOVPValueLv2;                      //0x251C 高穿二级过压保护值
    uint16_t u16LowSideUVPValueLv1;                       //0x251D 低穿一级欠压保护值
    uint16_t u16LowSideUVPValueLv2;                       //0x251E 低穿二级欠压保护值
    uint16_t u16LowSideUVPValueLv3;                       //0x251F 低穿三级欠压保护值
    uint16_t u16HighSideOFPValueLv1;                      //0x2520 高穿一级过频保护值
    uint16_t u16HighSideOFPValueLv2;                      //0x2521 高穿二级过频保护值
    uint16_t u16LowSideUFPValueLv1;                       //0x2522 低穿一级欠频保护值
    uint16_t u16LowSideUFPValueLv2;                       //0x2523 低穿二级欠频保护值
    //0x2524-0x2DFF 预留
}LineVoltProtParam_t;
#define PCS_03H_10H_LINE_VP_START                         (0x2500)
#define PCS_03H_10H_LINE_VP_LENGTH                        (sizeof(LineVoltProtParam_t) / 2)

/******************************************************************
 0X03读实时数据（包括遥测、遥信）系统参数:
 0X10(写单个或多个寄存器)写设置参数 系统参数:
*******************************************************************/
typedef struct
{
    uint16_t u16StartParam;                               //0x2600 开机参数
    uint16_t tSerialNum[10];                              //0x2601-0x260A 序列号
    uint16_t u16SerialNumB;                               //0x260B 预留
    uint16_t u16SerialNumC;                               //0x260C 预留
    uint16_t u16SerialNumD;                               //0x260D 预留
    uint16_t u16SerialNumE;                               //0x260E 预留
    uint16_t u16SerialNumF;                               //0x260F 预留
    uint16_t tModelCode[8];                               //0x2610-0x2617 机型号
    uint16_t u16ModelCode;                                //0x2618 机型码
    uint16_t u16SerialNum17;                              //0x2619 预留
    uint16_t u16SerialNum18;                              //0x261A 预留
    uint16_t u16SerialNum19;                              //0x261B 预留
    uint16_t u16SerialNum1A;                              //0x261C 预留
    uint16_t u16SerialNum1B;                              //0x261D 预留
    uint16_t u16SerialNum1C;                              //0x261E 预留
    uint16_t u16SerialNum1D;                              //0x261F 预留
    uint16_t u16SerialNum1E;                              //0x2620 预留
    uint16_t u16SerialNum1F;                              //0x2621 预留
    uint16_t u16SerialNum20;                              //0x2622 预留
    uint16_t u16SerialNum21;                              //0x2623 预留
    uint16_t u16SerialNum22;                              //0x2624 预留
    uint16_t u16SerialNum23;                              //0x2625 预留
    uint16_t u16SerialNum24;                              //0x2626 预留
    uint16_t u16SerialNum25;                              //0x2627 预留
    uint16_t u16SerialNum26;                              //0x2628 预留
    uint16_t u16SerialNum27;                              //0x2629 预留
    uint16_t u16SerialNum28;                              //0x262A 预留
    uint16_t u16SerialNum29;                              //0x262B 预留
    uint16_t u16SerialNum2A;                              //0x262C 预留
    uint16_t u16SerialNum2B;                              //0x262D 预留
    uint16_t u16SerialNum2C;                              //0x262E 预留
    uint16_t u16SerialNum2D;                              //0x262F 预留
    int16_t  s16AmbientTemp;                              //0x2630 环境温度
    int16_t  s16INVTemp;                                  //0x2631 逆变器温度
    int16_t  s16BatTemp;                                  //0x2632 电池温度
    union
    {
        uint16_t u16Word;
        struct
        {
            uint8_t bMeterCommState         : 1;          //BIT0 电表通讯状态
            uint8_t bBMSCommState           : 1;          //BIT1 电池包通信状态
            uint8_t bReserved0              : 1;          //BIT2 预留
            uint8_t bReserved1              : 1;          //BIT3 预留
            uint8_t bReserved2              : 1;          //BIT4 预留
            uint8_t bReserved3              : 1;          //BIT5 预留
            uint8_t bReserved4              : 1;          //BIT6 预留
            uint8_t bReserved5              : 1;          //BIT7 预留
            uint8_t bReserved6              : 1;          //BIT8 预留
            uint8_t bReserved7              : 1;          //BIT9 预留
            uint8_t bReserved8              : 1;          //BIT10 预留
            uint8_t bReserved9              : 1;          //BIT11 预留
            uint8_t bReserved10             : 1;          //BIT12 预留
            uint8_t bReserved11             : 1;          //BIT13 预留
            uint8_t bReserved12             : 1;          //BIT14 预留
            uint8_t bReserved13             : 1;          //BIT15 预留
        }Bits;
    }EmsCommState_t;                                      //0x2633 通讯状态

    union
    {
        uint16_t u16Word;
        struct
        {
            uint8_t bMeterEn                : 1;          //BIT0 电表使能
            uint8_t bBMSEn                  : 1;          //BIT1 电池包使能
            uint8_t bCTEn                   : 1;          //BIT2 CT使能
            uint8_t bReserved1              : 1;          //BIT3 预留
            uint8_t bReserved2              : 1;          //BIT4 预留
            uint8_t bReserved3              : 1;          //BIT5 预留
            uint8_t bReserved4              : 1;          //BIT6 预留
            uint8_t bReserved5              : 1;          //BIT7 预留
            uint8_t bReserved6              : 1;          //BIT8 电表通讯状态
            uint8_t bReserved7              : 1;          //BIT9 电池包通信状态
            uint8_t bReserved8              : 1;          //BIT10 预留
            uint8_t bReserved9              : 1;          //BIT11 预留
            uint8_t bReserved10             : 1;          //BIT12 预留
            uint8_t bReserved11             : 1;          //BIT13 预留
            uint8_t bReserved12             : 1;          //BIT14 预留
            uint8_t bReserved13             : 1;          //BIT15 预留
        }Bits;
    }EmsCommEN_t;                                         //0x2634 通讯使能

    uint16_t u16LowPowerEn;                               //0x2635 低功耗使能标志
    uint16_t u16ARMVersionV;                              //0x2636 ARM版本号V
    uint16_t u16ARMVersionB;                              //0x2637 ARM版本号B
    uint16_t u16ARMVersionD;                              //0x2638 ARM版本号D
    uint16_t u16Reserved39;                               //0x2639 预留
    uint16_t u16Reserved3A;                               //0x263A 预留
    uint16_t u16Reserved3B;                               //0x263B 预留
    uint16_t u16Reserved3C;                               //0x263C 预留
    uint16_t u16Reserved3D;                               //0x263D 预留
    uint16_t u16Reserved3E;                               //0x263E 预留
    uint16_t u16Reserved3F;                               //0x263F 预留
    uint16_t u16Reserved40;                               //0x2640 预留
    uint16_t u16Reserved41;                               //0x2641 预留
    uint16_t u16Reserved42;                               //0x2642 预留
    uint16_t u16Reserved43;                               //0x2643 预留
    uint16_t u16Reserved44;                               //0x2644 预留
    uint16_t u16Reserved45;                               //0x2645 预留
    uint16_t u16Reserved46;                               //0x2646 预留
    uint16_t u16Reserved47;                               //0x2647 预留
    uint16_t u16Reserved48;                               //0x2648 预留
    uint16_t u16Reserved49;                               //0x2649 预留
    uint16_t u16Reserved4A;                               //0x264A 预留
    uint16_t u16Reserved4B;                               //0x264B 预留
    uint16_t u16Reserved4C;                               //0x264C 预留
    uint16_t u16Reserved4D;                               //0x264D 预留
    uint16_t u16Reserved4E;                               //0x264E 预留
    uint16_t u16Reserved4F;                               //0x264F 预留
    uint16_t EMS2PCSHeartBeat;                            //0x2650 EMS对PCS通信心跳
    uint16_t FanSpeed;                                    //0x2651 风扇转速
    //0x2651-0x265F 预留
}SysInfo_t;
#define PCS_03H_10H_SYS_INFO_START                        (0x2600)
#define PCS_03H_10H_SYS_INFO_LENGTH                       (sizeof(SysInfo_t) / 2)

/******************************************************************
 0X03读实时数据（包括遥测、遥信）电表参数：
 0X10(写单个或多个寄存器)写设置参数 电表参数:
*******************************************************************/
typedef struct
{
    int16_t  s16InstantTotalWatt;                         //0x2700 瞬时总有功功率
    int16_t  s16InstantTotalVar;                          //0x2701 瞬时总无功功率
    int16_t  s16InstantTotalVA;                           //0x2702 瞬时总视在功率
    uint16_t u16GridFreq;                                 //0x2703 电网频率
    uint16_t u16TotalPF;                                  //0x2704 总功功率因数
    int16_t  s16PhaseAVolt;                               //0x2705 电压 预留
    int16_t  s16PhaseACurr;                               //0x2706 电流 预留
    //0x2707-0x27FF 预留
}MeterInfo_t;
#define PCS_03H_10H_METER_START                           (0x2700)
#define PCS_03H_10H_METER_LENGTH                          (sizeof(MeterInfo_t) / 2)

/******************************************************************
 0X03读实时数据（包括遥测、遥信）逆变器定标系数数据：
 0X10(写单个或多个寄存器)写设置参数 逆变器定标系数数据：
*******************************************************************/
typedef struct
{
    uint16_t u16Proportion;                               //比例系数
    int16_t s16Intercept;                                 //截距系数
}InvAdjPara_t;

typedef struct
{
    InvAdjPara_t tRGridVoltAdjPara;                       //R相 电网电压 校正参数
    InvAdjPara_t tSGridVoltAdjPara;                       //S相 电网电压 校正参数
    InvAdjPara_t tTGridVoltAdjPara;                       //T相 电网电压 校正参数
    InvAdjPara_t tRGridCurrAdjPara;                       //R相 电网电流 校正参数
    InvAdjPara_t tSGridCurrAdjPara;                       //S相 电网电流 校正参数
    InvAdjPara_t tTGridCurrAdjPara;                       //T相 电网电流 校正参数
    InvAdjPara_t tRInvVoltAdjPara;                        //R相 逆变电压 校正参数
    InvAdjPara_t tSInvVoltAdjPara;                        //S相 逆变电压 校正参数
    InvAdjPara_t tTInvVoltAdjPara;                        //T相 逆变电压 校正参数
    InvAdjPara_t tRInvCurrAdjPara;                        //R相 逆变输出电流 校正参数
    InvAdjPara_t tSInvCurrAdjPara;                        //S相 逆变输出电流 校正参数
    InvAdjPara_t tTInvCurrAdjPara;                        //T相 逆变输出电流 校正参数
    InvAdjPara_t tRInvInductorCurrAdjPara;                //R相 逆变电感电流 校正参数
    InvAdjPara_t tSInvInductorCurrAdjPara;                //S相 逆变电感电流 校正参数
    InvAdjPara_t tTInvInductorCurrAdjPara;                //T相 逆变电感电流 校正参数
    InvAdjPara_t tRGenVoltAdjPara;                        //R相 发电机电压 校正参数
    InvAdjPara_t tSGenVoltAdjPara;                        //S相 发电机电压 校正参数
    InvAdjPara_t tTGenVoltAdjPara;                        //T相 发电机电压 校正参数
    InvAdjPara_t tRGenCurrAdjPara;                        //R相 发电机电流 校正参数
    InvAdjPara_t tSGenCurrAdjPara;                        //S相 发电机电流 校正参数
    InvAdjPara_t tTGenCurrAdjPara;                        //T相 发电机电流 校正参数
    InvAdjPara_t tPBusVoltAdjPara;                        //正(P) 母线电压 校正参数
    InvAdjPara_t tNBusVoltAdjPara;                        //负(N) 母线电压 校正参数
    InvAdjPara_t tBuckBoostInducCurrAdjPara;              //Buck-Boost 电感电流 校正参数
    InvAdjPara_t tMidBusVoltAdjPara;                      //中间母线电压 校正参数
    InvAdjPara_t tBatVoltAdjPara;                         //电池电压 校正参数
    InvAdjPara_t tPV1VoltAdjPara;                         //PV1电压 校正参数
    InvAdjPara_t tPV1CurrAdjPara;                         //PV1电流 校正参数
    InvAdjPara_t tPV2VoltAdjPara;                         //PV2电压 校正参数
    InvAdjPara_t tPV2CurrAdjPara;                         //PV2电流 校正参数
}InvStdParam_t;

#define PCS_03H_10H_INV_STD_START                         (0x2E00)
#define PCS_03H_10H_INV_STD_LENGTH                        (sizeof(InvStdParam_t) / 2)

/******************************************************************
 0X03读实时数据（包括遥测、遥信）ATE：
 0X10(写单个或多个寄存器)写设置参数 ATE：
*******************************************************************/
typedef struct
{
    uint16_t u16SysTime;                                  //0x3100
    //0x3101-0x31FF 预留
}ATE0310H_t;
#define PCS_03H_10H_ATE_START                             (0x3100)
#define PCS_03H_10H_ATE_LENGTH                            (sizeof(ATE0310H_t) / 2)

/******************************************************************
 0X10(写单个或多个寄存器)写设置参数 安规信息:
*******************************************************************/
typedef struct
{
    uint16_t u16SRCountry;                                //0x2800 安规标准国家

    union
    {
        uint16_t u16Error;
        struct
        {
            uint8_t bGridConnectRule          : 1;        //BIT0 并网准则
            uint8_t bPublicParameters         : 1;        //BIT1 公共参数
            uint8_t bPhase3PowerSys           : 1;        //BIT2 三相网络
            uint8_t bGridUnderVoltProt        : 1;        //BIT3 欠压保护
            uint8_t bGridOverVoltProt         : 1;        //BIT4 过压保护
            uint8_t bGridUnderFreqProt        : 1;        //BIT5 电网欠频
            uint8_t bGridOverFreqProt         : 1;        //BIT6 电网过频
            uint8_t bHVRT                     : 1;        //BIT7 高电压穿越
            uint8_t bLVRT                     : 1;        //BIT8 低电压穿越
            uint8_t bReconnect                : 1;        //BIT9 断开重连
            uint8_t bLowFreqReduction         : 1;        //BIT10 低频降额
            uint8_t bOverFreqPowerResponse    : 1;        //BIT11 过频功率响应
            uint8_t bLowFreqPowerResponse     : 1;        //BIT12 低频功率响应
            uint8_t b10MinOvProtect           : 1;        //BIT13 10分钟过压保护
            uint8_t bReserved6                : 1;        //BIT14 预留
            uint8_t bReserved7                : 1;        //BIT15 预留
        }Bits;
    }SRTypeEn_t;                                          //0x2801 安规类别使能

    uint16_t u16RatedVoltage;                             //0x2802 额定电压
    uint16_t u16RatedPower;                               //0x2803 额定功率
    uint16_t u16RatedFrequence;                           //0x2804 额定频率
    uint16_t u16LowFreqReturnValue;                       //0x2805 欠频返回值
    uint16_t u16OverFreqReturnValue;                      //0x2806 过频返回值
    uint16_t u16LowVoltReturnValue;                       //0x2807 欠压返回值
    uint16_t u16OverVoltReturnValue;                      //0x2808 过压返回值
   
    uint16_t u16Pha1SysPowerMax;                          //0x2809 并网准则|单相系统的最大功率
    uint16_t u16Pha3OutputPowerDiff;                      //0x280A 三相网络|三相输出功率偏差功率

    uint16_t u16UnderVoltRatedPercentLv1;                 //0x280B 欠压保护|一级欠压额定电压百分比
    uint16_t u16UnderVoltResponseTimeLv1;                 //0x280C 欠压保护|一级响应时间
    uint16_t u16UnderVoltRatedPercentLv2;                 //0x280D 欠压保护|二级欠压额定电压百分比
    uint16_t u16UnderVoltResponseTimeLv2;                 //0x280E 欠压保护|二级响应时间
    uint16_t u16UnderVoltRatedPercentLv3;                 //0x280F 欠压保护|三级欠压额定电压百分比
    uint16_t u16UnderVoltResponseTimeLv3;                 //0x2810 欠压保护|三级响应时间

    uint16_t u16OverVoltRatedPercentLv1;                  //0x2811 过压保护|一级欠压额定电压百分比
    uint16_t u16OverVoltResponseTimeLv1;                  //0x2812 过压保护|一级响应时间
    uint16_t u16OverVoltRatedPercentLv2;                  //0x2813 过压保护|二级欠压额定电压百分比
    uint16_t u16OverVoltResponseTimeLv2;                  //0x2814 过压保护|二级响应时间
    uint16_t u16OverVoltRatedPercentLv3;                  //0x2815 过压保护|三级欠压额定电压百分比
    uint16_t u16OverVoltResponseTimeLv3;                  //0x2816 过压保护|三级响应时间

    uint16_t u16UnderFreqProtValueLv1;                    //0x2817 电网欠频|一级欠频保护值
    uint16_t u16UnderFreqResponseTimeLv1;                 //0x2818 电网欠频|一级欠频响应时间
    uint16_t u16UnderFreqProtValueLv2;                    //0x2819 电网欠频|二级欠频保护值
    uint16_t u16UnderFreqResponseTimeLv2;                 //0x281A 电网欠频|二级欠频响应时间
    uint16_t u16UnderFreqProtValueLv3;                    //0x281B 电网欠频|三级欠频保护值
    uint16_t u16UnderFreqResponseTimeLv3;                 //0x281C 电网欠频|三级欠频响应时间
    
    uint16_t u16OverFreqProtValueLv1;                     //0x281D 电网过频|一级过频保护值
    uint16_t u16OverFreqResponseTimeLv1;                  //0x281E 电网过频|一级过频响应时间
    uint16_t u16OverFreqProtValueLv2;                     //0x281F 电网过频|二级过频保护值
    uint16_t u16OverFreqResponseTimeLv2;                  //0x2820 电网过频|二级响应时间
    uint16_t u16OverFreqProtValueLv3;                     //0x2821 电网过频|三级过频保护值
    uint16_t u16OverFreqResponseTimeLv3;                  //0x2822 电网过频|三级响应时间

    uint16_t u16HVRTLevel1RatedPercent;                   //0x2823 高电压穿越|一级高穿电压百分比
    uint16_t u16HVRTLevel1Time;                           //0x2824 高电压穿越||一级高穿支撑时间
    uint16_t u16HVRTLevel2RatedPercent;                   //0x2825 高电压穿越|二级高穿电压百分比
    uint16_t u16HVRTLevel2Time;                           //0x2826 高电压穿越|二级高穿支撑时间
    uint16_t u16HVRTLevel3RatedPercent;                   //0x2827 高电压穿越|三级高穿电压百分比
    uint16_t u16HVRTLevel3Time;                           //0x2828 高电压穿越|三级高穿支撑时间
    uint16_t u16HVRTLevel4RatedPercent;                   //0x2829 高电压穿越|四级高穿电压百分比
    uint16_t u16HVRTLevel4Time;                           //0x282A 高电压穿越|四级高穿支撑时间
    uint16_t u16HVRTLevel5RatedPercent;                   //0x282B 高电压穿越|五级高穿电压百分比
    uint16_t u16HVRTLevel5Time;                           //0x282C 高电压穿越|五级高穿支撑时间
    uint16_t u16HVRTLevel6RatedPercent;                   //0x282D 高电压穿越|六级高穿电压百分比
    uint16_t u16HVRTLevel6Time;                           //0x282E 高电压穿越|六级高穿支撑时间
    
    uint16_t u16LVRTLevel1RatedPercent;                   //0x282F 低电压穿越|一级低穿电压百分比
    uint16_t u16LVRTLevel1Time;                           //0x2830 低电压穿越|一级低穿支撑时间
    uint16_t u16LVRTLevel2RatedPercent;                   //0x2831 低电压穿越|二级低穿电压百分比
    uint16_t u16LVRTLevel2Time;                           //0x2832 低电压穿越|二级低穿支撑时间
    uint16_t u16LVRTLevel3RatedPercent;                   //0x2833 低电压穿越|三级低穿电压百分比
    uint16_t u16LVRTLevel3Time;                           //0x2834 低电压穿越|三级低穿支撑时间
    uint16_t u16LVRTLevel4RatedPercent;                   //0x2835 低电压穿越|四级低穿电压百分比
    uint16_t u16LVRTLevel4Time;                           //0x2836 低电压穿越|四级低穿支撑时间
    uint16_t u16LVRTLevel5RatedPercent;                   //0x2837 低电压穿越|五级低穿电压百分比
    uint16_t u16LVRTLevel5Time;                           //0x2838 低电压穿越|五级低穿支撑时间
    uint16_t u16LVRTLevel6RatedPercent;                   //0x2839 低电压穿越|六级低穿电压百分比
    uint16_t u16LVRTLevel6Time;                           //0x283A 低电压穿越|六级低穿支撑时间

    uint16_t u16ReconnectRate;                            //0x283B 断开重连|并网速率
    uint16_t u16ReconnectTime;                            //0x283C 断开重连|重连时间
    uint16_t u16LowFreqDeratingValue;                     //0x283D 低频降额|阈值
    uint16_t u16LowFreqDeratingTime;                      //0x283E 低频降额|降额斜率

    uint16_t u16OverFreqPowerFreqValue;                   //0x283F 过频功率响应|频率阈值
    uint16_t u16OverFreqPowerStopValue;                   //0x2840 过频功率响应|停用阈值
    uint16_t u16OverFreqPowerStopTime;                    //0x2841 过频功率响应|停用时间
    uint16_t u16OverFreqPowerDeclineRate;                 //0x2842 过频功率响应|下降斜率
    uint16_t u16OverFreqPowerDelayTime;                   //0x2843 过频功率响应|延迟时间

    uint16_t u16LowFreqPowerFreqValue;                    //0x2844 低频功率响应|频率阈值
    uint16_t u16LowFreqPowerStopValue;                    //0x2845 低频功率响应|停用阈值
    uint16_t u16LowFreqPowerStopTime;                     //0x2846 低频功率响应|停用时间
    uint16_t u16LowFreqPowerDeclineRate;                  //0x2847 低频功率响应|下降斜率
    uint16_t u16LowFreqPowerDelayTime;                    //0x2848 低频功率响应|延迟时间
    uint16_t u1610MinOvProtectPercent;                    //0x2849 10分钟过压|保护百分比
    uint16_t u1610MinOvProtectTime;                       //0x284A 10分钟过压|保护时间
    //0x284B-0x28FF 预留
}SRInfo_t;

#define PCS_10H_SR_START                                 (0x2800)
#define PCS_10H_SR_LENGTH                                (sizeof(SRInfo_t) / 2)

typedef struct
{
    uint16_t RemoteControl;                              //0x2900 远程控制
}EMSControlInfo_t;

#define PCS_10H_EMSControl_START                         (0x2900)
#define PCS_10H_EMSControl_LENGTH                        (sizeof(EMSControlInfo_t) / 2)

/******************************************************************
 0X10(写单个或多个寄存器)写设置参数 能量管理数据：
*******************************************************************/
typedef struct
{
    uint16_t u16EmsMethod;                                //0x2F00 能量管理策略
    int16_t  s16EmsWatt;                                  //0x2F01 有功功率
    int16_t  s16EmsVar;                                   //0x2F02 无功功率
    uint16_t u16BmsVolt;                                  //0x2F03 BMS电压(总电压)
    uint16_t u16EmsMaxChgCurr;                            //0x2F04 最大充电电流
    uint16_t u16EmsMaxDisChgCurr;                         //0x2F05 最大放电电流
    uint16_t u16EmsChgCutoffVolt;                         //0x2F06 电池充电截止电压
    uint16_t u16EmsDisChgCutoffVolt;                      //0x2F07 电池放电截止电压
    uint16_t u16EmsLiveSOC;                               //0x2F08 实时SOC
    uint16_t u16EmsChgCutoffSOC;                          //0x2F09 电池充电截止SOC
    uint16_t u16EmsDisChgCutoffSOC;                       //0x2F0A 电池放电截止SOC
    uint16_t u16PeakValleyModeState;                      //0x2F0B 峰谷模式状态
    uint16_t u16TimedChgDischgEN;                         //0x2F0C 定时充放电使能
    uint16_t u16RemainBatOnGrid;                          //0x2F0D 余电上网标志
    uint16_t u16PV1MaxPower;                              //0x2F0E PV1最大功率
    uint16_t u16PV2MaxPower;                              //0x2F0F PV2最大功率
    int16_t  sPowerFactor;                                //0x2F10 功率因数
    int16_t  sGenRatedPower;                              //0x2F11 发电机额定功率
    int16_t  sGenMaxPower;                                //0x2F12 发电机最大功率
    uint16_t u16DryContactEnFlag;                         //0x2F13 干接点使能标志
    uint16_t u16EmsFbdGenChgSOC;                          //0x2F14 发电机禁止充电SOC
    uint16_t u16EmsSupplySOC;                             //0x2F15 发电机补电模式SOC
    uint16_t u16AILoadExitSOC;                            //0x2F16 智能负载退出SOC
    uint16_t u16AILoadEnterSOC;                           //0x2F17 智能负载接入SOC
    uint16_t u16DryContactAccessFlag;                     //0x2F18 干接点接入标志(DSP)
    uint16_t u16GenStartFlag;                             //0x2F19 发电机启动标志
    //0x2F19-0x2FFF 预留
}EmsParam_t;
#define PCS_10H_EMS_PARAM_START                           (0x2F00)
#define PCS_10H_EMS_PARAM_LENGTH                          (sizeof(EmsParam_t) / 2)

/******************************************************************
 0X10(写单个或多个寄存器)写设置参数 ATE数据：
*******************************************************************/
typedef struct
{
    uint16_t u16Grid1Rly;                                 //0x3000 预留
    uint16_t u16Grid2Rly;                                 //0x3001 预留
    uint16_t u16Grid3Rly;                                 //0x3002 预留
    uint16_t u16Grid4Rly;                                 //0x3003 预留
    uint16_t u16InvRly;                                   //0x3004 预留
    uint16_t u16GenRly;                                   //0x3005 预留
    uint16_t u16LoadRly;                                  //0x3006 预留
    uint16_t u16OffRly;                                   //0x3007 预留
    uint16_t u16SoftRly;                                  //0x3008 预留
    uint16_t u16InvPwmQ201Q206;                           //0x3009 预留
    uint16_t u16InvPwmQ202Q205;                           //0x300A 预留
    uint16_t u16InvPwmQ203;                               //0x300B 预留
    uint16_t u16InvPwmQ204;                               //0x300C 预留
    uint16_t u16InvPwmQ207;                               //0x300D 预留
    uint16_t u16InvPwmQ208;                               //0x300E 预留
    uint16_t u16InvPwmQ209;                               //0x300F 预留
    uint16_t u16InvPwmQ210;                               //0x3010 预留
    uint16_t u16BuckBoostPwmQ413;                         //0x3011 预留
    uint16_t u16BuckBoostPwmQ414;                         //0x3012 预留
    uint16_t u16LLCPwmUpQ401Q407;                         //0x3013 预留
    uint16_t u16LLCPwmUpQ402Q408;                         //0x3014 预留
    uint16_t u16LLCPwmDownQ403Q406Q409Q412;               //0x3015 预留
    uint16_t u16FactoryMode;                              //0x3016 预留
    uint16_t u16PowerOnParam;                             //0x3017 预留
    uint16_t u16SerialNumber;                             //0x3018 预留
    uint16_t u16TestMode;                                 //0x3019 预留
    uint16_t u16Standby;                                  //0x301A 预留
    uint16_t u16ClearGeneration;                          //0x301B 预留
    uint16_t u16WriteDefaultAdjust;                       //0x301C 预留
    uint16_t u16PVVoltAdjustMode;                         //0x301D 预留
    uint16_t u16PV1VoltAdjustFactor;                      //0x301E 预留
    uint16_t u16PV2VoltAdjustFactor;                      //0x301F 预留
    uint16_t u16BusVoltAdjustFactor;                      //0x3020 预留
    uint16_t u16MidBusVoltAdjustFactor;                   //0x3021 预留
    uint16_t u16PV1InsulationImpedanceRly;                //0x3022 预留
    uint16_t u16PV2InsulationImpedanceRly;                //0x3023 预留
    uint16_t u16Reserved3;                                //0x3024 预留
    uint16_t u16Reserved4;                                //0x3025 预留
    uint16_t u16Reserved5;                                //0x3026 预留
    uint16_t u16Reserved6;                                //0x3027 预留
    uint16_t u16Reserved7;                                //0x3028 预留
    uint16_t u16Reserved8;                                //0x3029 预留
    uint16_t u16Reserved9;                                //0x302A 预留
    uint16_t u16Reserved10;                               //0x302B 预留
    uint16_t u16Reserved11;                               //0x302C 预留
    uint16_t u16Reserved12;                               //0x302D 预留
    uint16_t u16SetPV1Power;                              //0x302E 预留
    uint16_t u16SetPV2Power;                              //0x302F 预留
    uint16_t u16SetBatteryPower;                          //0x3030 预留
    uint16_t u16SetGridActivePower;                       //0x3031 预留
    uint16_t u16GridVoltAdjustFactor;                     //0x3032 预留
    uint16_t u16GridHCTCurrAdjustFactor;                  //0x3033 预留
    uint16_t u16GridCTCurrAdjustFactor;                   //0x3034 预留
    uint16_t u16InvVoltAdjustFactor;                      //0x3035 预留
    uint16_t u16InvHCTCurrAdjustFactor;                   //0x3036 预留
    uint16_t u16PV1CurrAdjustFactor;                      //0x3037 预留
    uint16_t u16PV2CurrAdjustFactor;                      //0x3038 预留
    uint16_t u16InsulationResistorDetectEn;               //0x3039 预留
    uint16_t u16SetBattVoltAdjustFactor;                  //0x303A 预留
    uint16_t u16SetBattCurrAdjustFactor;                  //0x303B 预留
    uint16_t u16SetBattChgCurr;                           //0x303C 预留
    uint16_t u16SetGridChgMode;                           //0x303D 预留
    uint16_t u16MeterCom;                                 //0x303E 预留
    uint16_t u16BMSModbusCom;                             //0x303F 预留
    uint16_t u16BMSCANCom;                                //0x3040 预留
    uint16_t u16ParaCANEmsCom;                            //0x3041 预留
    uint16_t u16ParaCANPcsCom;                            //0x3042 预留
    //0x3043-0x30FF 预留
}ATE10H_t;
#define PCS_10H_ATE_START                                 (0x3000)
#define PCS_10H_ATE_LENGTH                                (sizeof(ATE10H_t) / 2)

typedef struct
{
    struct
    {
        ProtData_t tProtData;                             //0X01 0x0100 保护参数数据
    }Register01H_t;
    
    struct
    {
        DebugMode_t tDebugMode;                           //0X01 0X0F 0x0130 调试模式数据
        ProtEn_t tProtEn;                                 //0X01 0X0F 0x0150 保护使能数据
        SysCtrlParam_t tSysCtrlParam;                     //0X01 0X0F 0X0170 系统控制参数数据
    }Register010FH_t;
    
    struct
    {
        TotalParam_t tTotalParam;                         //0X03 0x1000 共有参数数据
        PVInformation_t tPV1Information;                  //0X03 0x1100 光伏1信息数据
        PVInformation_t tPV2Information;                  //0X03 0x1110 光伏2信息数据
        InvInformation_t tInvInformation;                 //0X03 0x1200 逆变器信息数据
        DCDCInformation_t tDCDCInformation;               //0X03 0x1300 电池DC-DC信息数据
    }Register03H_t;

    struct
    {
        PvCtrlParam_t tPvCtrlParam;                       //0X03 0x10 0x2000 PV控制参数
        InvCtrlParam_t tInvCtrlParam;                     //0X03 0x10 0x2100 逆变器控制参数
        BatCtrlParam_t tBatCtrlParam;                     //0X03 0x10 0x2200 DCDC电池控制参数
        SysParam_t tSysParam;                             //0X03 0x10 0x2300 系统参数
        ComParam_t tComParam;                             //0X03 0x10 0x2400 通讯参数
        LineVoltProtParam_t tLineVoltProtParam;           //0X03 0x10 0x2500 市电过压保护
        SysInfo_t tSysInfo;                               //0X03 0x10 0x2600 系统参数
        MeterInfo_t tMeterInfo;                           //0X03 0x10 0x2700 电表下发数据
        InvStdParam_t tInvStdParam;                       //0X03 0x10 0x2E00 逆变器定标系数
    }Register0310H_t;

    struct
    {
        SRInfo_t tSRInfo;                                 //0x10 0x2800 安规信息
        EmsParam_t tEmsParam;                             //0x10 0x2F00 能量管理数据
        EMSControlInfo_t tEMSControlInfo;                 //0x10 0x2900 远程控制
    }Register10H_t;

    struct
    {
        Data05H_t tData05H;                               //0x05 0x0200 数据
    }Register05H_t;
}InternalComData_t;
extern InternalComData_t tInternalComData;                //PCS内部通讯的数据结构

/*PCS协议各个功能码的数据范围检查函数的声明*/
extern MBErrorCode CheckPCSComDataRange_01H(MBRTUFrame_t* ptMBFrame);
extern MBErrorCode CheckPCSComDataRange_03H(MBRTUFrame_t* ptMBFrame);
extern MBErrorCode CheckPCSComDataRange_05H(MBRTUFrame_t* ptMBFrame);
extern MBErrorCode CheckPCSComDataRange_10H(MBRTUFrame_t* ptMBFrame);
extern MBErrorCode CheckPCSComDataRange_0FH(MBRTUFrame_t* ptMBFrame);

/*PCS协议各个功能码的数据结构定位函数的声明*/
extern uint16_t* GetPcsComDataIndex_01H(MBRTUFrame_t* ptMBFrame);
extern uint16_t* GetPcsComDataIndex_03H(MBRTUFrame_t* ptMBFrame);
extern uint16_t* GetPcsComDataIndex_05H(MBRTUFrame_t* ptMBFrame);
extern uint16_t* GetPcsComDataIndex_0FH(MBRTUFrame_t* ptMBFrame);
extern uint16_t* GetPcsComDataIndex_10H(MBRTUFrame_t* ptMBFrame);

/*PCS协议对显示屏的数据接口*/
extern void GetDisplayRealTimePVData(Display_DATA_PV* ptDisplayPVData);
extern void GetDisplayRealTimeLoadData(Display_DATA_LOAD* ptDisplayLoadData);
extern void GetDisplayRealTimeGenData(Display_DATA_Gen* ptDisplayGenData);

                                                                                                                                                                                                                                                                                           
/*PCS协议对外的数据接口*/
extern void GetDisplaySystemFault(Display_SYS_Fault_t* ptDisplaySysFault);
extern void GetDisplayPVFault(Display_PV_Fault_t* ptDisplayPVFault);
extern void GetDisplayInvFault(Display_INV_Fault_t* ptDisplayInvFault);
extern void GetDisplayDCDCFault(Display_DCDC_Fault_t* ptDisplayDCDCFault);
extern void GetDisplaySysAlarm(Display_SYS_Alarm_t* ptDisplaySysAlarm);
extern void GetDisplayGenFault(Display_Gen_Fault_t* ptDisplayGenFault);

extern void GetDisplayGridGenState(DisplayGenGridState_t* tGenRunState);
extern void GetDisplayInvState(DisplayInvRunState_t* tInvRunState);
extern void GetDisplaySoftwareVersion(Display_DSP_MCU_Version* tDspMcuVersion);
extern void GetDisplayEMSCommFault(Display_EMS_Fault_t* ptDisplayEMSFault);
extern void GetPcs10HEmsParam(EmsParam_t* pEmsParam);
extern uint16_t GetGenRunState(void);

extern void GetTotalParamInfo(TotalParam_t* tTotalParam);
extern void GetPV1Information(PVInformation_t* tPV1Information);
extern void GetPV2Information(PVInformation_t* tPV2Information);
extern void GetInvInformation(InvInformation_t* tInvInformation);
extern void GetDCDCInformation(DCDCInformation_t* tDCDCInformation);

extern void SetPcs05HPowerOnOffControl(uint16_t u16OnOffState);
extern void SetPcs10HEnergyStrategy(EmsParam_t* pEmsParam);
extern void SetPcs10HGridStandardInfo(SR_Universal* tSRUniversal);
extern void SetPcs10HReactivePower(int16_t sReactivePowerValue);
extern void SetPcs10HPowerFactor(int16_t sPowerFactorValue);

#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

