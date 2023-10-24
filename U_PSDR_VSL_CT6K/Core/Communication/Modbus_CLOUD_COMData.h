/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Modbus_CLOUD_COMData.h
 用途 : modbusCLOUD协议数据头文件
***********************************************************************************************************************/
#ifndef _MODBUS_CLOUD_COMDATA_H_
#define _MODBUS_CLOUD_COMDATA_H_

#include "HeadFile.h"
#include "Modbus.h"
#include "LCD_Service.h"
#include "Fault_Management_Service.h"
#include "Indication_Management_Service.h"

#pragma pack(1)
/*功能：BMS_CLOUD 03功能码协议地址识别表*/
typedef enum
{
    EMS_TO_CLOUD_03H_SYS_PARAM_INFO_START       =  0x0000,
    EMS_TO_CLOUD_03H_SYS_PARAM_INFO_END         =  0x005F,
    EMS_TO_CLOUD_03H_GRID_PARAM_START           =  0x0060,
    EMS_TO_CLOUD_03H_GRID_PARAM_END             =  0x007F,
    EMS_TO_CLOUD_03H_PV_INFO_START              =  0x0080,
    EMS_TO_CLOUD_03H_PV_INFO_END                =  0x008F,
    EMS_TO_CLOUD_03H_BAT_INFO_START             =  0x0090,
    EMS_TO_CLOUD_03H_BAT_INFO_END               =  0x00AF,
    EMS_TO_CLOUD_03H_LOAD_INFO_START            =  0x00B0,
    EMS_TO_CLOUD_03H_LOAD_INFO_END              =  0x00BF,
    EMS_TO_CLOUD_03H_INV_INFO_START             =  0x00C0,
    EMS_TO_CLOUD_03H_INV_INFO_END               =  0x00FF,
    EMS_TO_CLOUD_03H_GIRD_INFO_START            =  0x0100,
    EMS_TO_CLOUD_03H_GIRD_INFO_END              =  0x01FF,
}EMS_DATA_CLOUD_03H_ADDRESS;


/******************************************************************
 0X03读实时数据 ：
*******************************************************************/
typedef struct
{
    uint16_t u16DeviceType;                                 //0x0000 设备类型
    uint16_t u16MachincePort[8];                            //0x0001 机器串号(ASCII)
    uint16_t u16MachinceType[10];                           //0x0009 机器型号(ASCII)
    uint16_t u16ManufactInfo[15];                           //0x0013 厂家信息(ASCII)
    uint16_t u16LanguageType;                                //0x0022 语言
    uint16_t u16DeviceStatus;                               //0x0023 设备状态
    uint16_t u16WorkMode;                                   //0x0024 工作模式
    uint16_t u16PVWorkMode;                                 //0x0025 PV工作模式
    uint16_t u16PVTrackMode;                                //0x0026 PV追踪模式
    uint16_t u16PV1WorkStatus;                              //0x0027 PV1工作状态
    uint16_t u16PV2WorkStatus;                              //0x0028 PV2工作状态
    uint16_t u16BatWorkStatus;                              //0x0029 电池工作状态
    uint16_t u16GirdWorkStatus;                             //0x002A 电网工作状态
    uint16_t u16GenWorkStatus;                              //0x002B 发电机工作状态
    uint16_t u16ParallelStatus;                             //0x002C 并机状态
    uint16_t u16EmsVersion[6];                              //0x002D EMS版本号(ASCII)
    uint16_t u16DspVersion[6];                              //0x0033 DSP版本号(ASCII)
    uint16_t u16BackupVersion[6];                           //0x0039 BackUp版本号(ASCII)
    uint16_t u16BHWVersion[10];                             //0x003F 硬件版本号 
    int16_t  s16InvRadiatorTemp;                            //0x0049 INV散热器温度值
    int16_t  s16EnvironmentTemp;                            //0x004A 环境温度
    int16_t  s16DCDCRadiatorTemp;                           //0x004B DC-DC散热器温度

//0x004C   系统故障1
//0x004D   系统故障2
    struct
    {
        union
        {
            uint16_t u16Error;
            struct
            {
                uint16_t bSysErr               : 1;             //BIT0 系统故障
                uint16_t bBusFastOV            : 1;             //BIT1 母线过压快检
                uint16_t bBusSlowOV            : 1;             //BIT2 母线过压慢检
                uint16_t bBusUV                : 1;             //BIT3 母线欠压
                uint16_t bBusSoft              : 1;             //BIT4 母线软起
                uint16_t bEmsCommErr           : 1;             //BIT5 EMS通讯异常
                uint16_t bOutputShort          : 1;             //BIT6 输出短路
                uint16_t bGFCIErr1             : 1;             //BIT7 GFCI漏电故障1
                uint16_t bGFCIErr2             : 1;             //BIT8 GFCI漏电故障2
                uint16_t bGFCIErr3             : 1;             //BIT9 GFCI漏电故障3
                uint16_t bFWSelfLock           : 1;             //BIT10 软件自锁故障
                uint16_t bSysOT                : 1;             //BIT11 系统过温
                uint16_t bSysOverLoad          : 1;             //BIT12 过载
                uint16_t bEpo                  : 1;             //BIT13 Epo
                uint16_t bSlaveCpuErr          : 1;             //BIT14 从cpu故障
                uint16_t bAssistSourceErr      : 1;             //BIT15 辅源故障
            }Bits;
        }SysFault1_t;                                           //0x004C 系统故障1
        union
        {
            uint16_t u16Error;
            struct
            {
                uint16_t bBusBoardBrkProt      : 1;             //BIT16 母线板断连保护
                uint16_t bGroundProt           : 1;             //BIT17 接地保护
                uint16_t bSoftStartErr         : 1;             //BIT18 软启失败
                uint16_t bDcDcOverLoadProt     : 1;             //BIT19 DCDC过载保护
                uint16_t bPVRevConnectErr      : 1;             //BIT20 PV反接故障
                uint16_t bReserved4            : 1;             //BIT21 pcs 通信故障
                uint16_t bReserved5            : 1;             //BIT22 电表通信
                uint16_t bReserved6            : 1;             //BIT23 BMS通信故障
                uint16_t bReserved7            : 1;             //BIT24 预留
                uint16_t bReserved8            : 1;             //BIT25 预留
                uint16_t bReserved9            : 1;             //BIT26 预留
                uint16_t bReserved10           : 1;             //BIT27 预留
                uint16_t bReserved11           : 1;             //BIT28 预留
                uint16_t bReserved12           : 1;             //BIT29 预留
                uint16_t bReserved13           : 1;             //BIT30 预留
                uint16_t bReserved14           : 1;             //BIT31 预留
            }Bits;
        }SysFault2_t;                                           //0x004D 系统故障2
        union
        {
            uint16_t u16Error;
            struct
            {
                uint16_t bReserved0            : 1;             //BIT16 预留
                uint16_t bReserved1            : 1;             //BIT17 预留
                uint16_t bReserved2            : 1;             //BIT18 预留
                uint16_t bReserved3            : 1;             //BIT19 预留
                uint16_t bReserved4            : 1;             //BIT20 预留
                uint16_t bReserved5            : 1;             //BIT21 预留
                uint16_t bReserved6            : 1;             //BIT22 预留
                uint16_t bReserved7            : 1;             //BIT23 预留
                uint16_t bReserved8            : 1;             //BIT24 预留
                uint16_t bReserved9            : 1;             //BIT25 预留
                uint16_t bReserved10           : 1;             //BIT26 预留
                uint16_t bReserved11           : 1;             //BIT27 预留
                uint16_t bReserved12           : 1;             //BIT28 预留
                uint16_t bReserved13           : 1;             //BIT29 预留
                uint16_t bReserved14           : 1;             //BIT30 预留
                uint16_t bReserved15           : 1;             //BIT31 预留
            }Bits;
        }SysFault3_t;                                           //0x004E 系统故障3
        union
        {
            uint16_t u16Error;
            struct
            {
                uint16_t bReserved0            : 1;             //BIT16 预留
                uint16_t bReserved1            : 1;             //BIT17 预留
                uint16_t bReserved2            : 1;             //BIT18 预留
                uint16_t bReserved3            : 1;             //BIT19 预留
                uint16_t bReserved4            : 1;             //BIT20 预留
                uint16_t bReserved5            : 1;             //BIT21 预留
                uint16_t bReserved6            : 1;             //BIT22 预留
                uint16_t bReserved7            : 1;             //BIT23 预留
                uint16_t bReserved8            : 1;             //BIT24 预留
                uint16_t bReserved9            : 1;             //BIT25 预留
                uint16_t bReserved10           : 1;             //BIT26 预留
                uint16_t bReserved11           : 1;             //BIT27 预留
                uint16_t bReserved12           : 1;             //BIT28 预留
                uint16_t bReserved13           : 1;             //BIT29 预留
                uint16_t bReserved14           : 1;             //BIT30 预留
                uint16_t bReserved15           : 1;             //BIT31 预留
            }Bits;
        }SysFault4_t;                                           //0x004F 系统故障4
    }SysFault_t;
//0x0050  系统状态1
//0x0051  系统状态2
    struct
    {
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
        }u16SysState1_t;                                       //0x0050 系统状态1
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
        }u16SysState2_t;                                       //0x0051 系统状态1
    }u16SysState_t;
//0x0052-0x005F  预留
}TotalSysParam;

//#define EMS_TO_CLOUD_03H_SYS_PARAM_INFO_START                             (0x0000)
#define EMS_TO_CLOUD_03H_SYS_PARAM_LENGTH                                 (sizeof(TotalSysParam) / 2)

typedef struct
{
    uint16_t tUGridVoltPara;                              //0x0060 电网U相电压
    uint16_t tVGridVoltPara;                              //0x0061 电网U相电压
    uint16_t tWGridVoltPara;                              //0x0062 电网U相电压
    uint16_t tGridFreqPara;                               //0x0063 电网U相电压
    int16_t  s16GridCurrU;                                //0x0064 电网U相电流
    int16_t  s16GridCurrV;                                //0x0065 电网V相电流
    int16_t  s16GridCurrW;                                //0x0066 电网W相电流
    uint16_t tGridVoltParaWattU;                          //0x0067 并网U相视在功率
    uint16_t tGridVoltParaWattV;                          //0x0068 并网V相视在功率
    uint16_t tGridVoltParaWattW;                          //0x0069 并网W相视在功率
    int16_t  s16GridLoadCurrWattU;                        //0x006A 并网U相有功功率
    int16_t  s16GridLoadCurrWattV;                        //0x006B 并网V相有功功率
    int16_t  s16GridLoadCurrWattW;                        //0x006C 并网W相有功功率
    int16_t  s16GridvLoadCurrVarU;                        //0x006D 并网U相无功功率
    int16_t  s16GridvLoadCurrVarV;                        //0x006E 并网V相无功功率
    int16_t  s16GridvLoadCurrVarW;                        //0x006F 并网W相无功功率

//0x0070  电网故障1
//0x0071  电网故障2
    struct
    {
        union
        {
            uint16_t u16Error;
            struct
            {
                uint16_t bGridErr               : 1;       //BIT0 电网异常
                uint16_t bGrid10MinOV           : 1;       //BIT1 电网10分钟过压
                uint16_t bGridFastOV            : 1;       //BIT2 电网过压快检
                uint16_t bGridSlowOV            : 1;       //BIT3 电网过压慢检
                uint16_t bGridUVLv3             : 1;       //BIT4 电网欠压三级故障
                uint16_t bGridUVLv2             : 1;       //BIT5 电网欠压二级故障
                uint16_t bGridUVLv1             : 1;       //BIT6 电网欠压一级故障
                uint16_t bGridFastOverFreq      : 1;       //BIT7 电网过频快检
                uint16_t bGridSlowOverFreq      : 1;       //BIT8 电网过频慢检
                uint16_t bGridFastUnderFreq     : 1;       //BIT9 电网欠频快检
                uint16_t bGridSlowUnderFreq     : 1;       //BIT10 电网欠频慢检
                uint16_t bIslandErr             : 1;       //BIT11 孤岛故障
                uint16_t bGridFastPowerDown     : 1;       //BIT12 电网掉电快检
                uint16_t bPllErr                : 1;       //BIT13 锁相异常
                uint16_t bSysLNReverse          : 1;       //BIT14 系统LN反接
                uint16_t bGridRlyErr            : 1;       //BIT15 电网继电器故障
            }Bits;
        }GridFault1_t;                                     //0x0070 电网故障1

        union
        {
            uint16_t u16Error;
            struct
            {
                uint16_t bCTDisconnectErr       : 1;       //BIT0 CT未接故障
                uint16_t bMeterDisconnectErr    : 1;       //BIT1 电表未接故障
                uint16_t bReserved0             : 1;       //BIT2 预留
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
        }GridFault2_t;                                     //0x0071 电网故障2
    }GridFault;
//0x0072-0x007F  预留
}GridStdParam;


//#define EMS_TO_CLOUD_03H_GRID_PARAM_START                          (0x0060)
#define EMS_TO_CLOUD_03H_GRID_PARAM_LENGTH                         (sizeof(GridStdParam) / 2)

typedef struct
{
    uint16_t u16PV1Volt;                                   //0x0080 PV1电压
    int16_t  s16PV1Curr;                                   //0x0081 PV1电流
    int16_t  s16PV1Watt;                                   //0x0082 PV1功率
    uint16_t u16PV2Volt;                                   //0x0083 PV2电压
    int16_t  s16PV2Curr;                                   //0x0084 PV2电流
    int16_t  s16PV2Watt;                                   //0x0085 PV2功率
//0x0086   PV1故障
//0x0087   PV2故障
    struct
    {
        union
        {
            uint16_t u16Error;
            struct
            {
                uint16_t bPvErr                : 1;        //BIT0 故障
                uint16_t bPvUV                 : 1;        //BIT1 PV欠压
                uint16_t bPvOV                 : 1;        //BIT2 PV过压
                uint16_t bPvISOErr             : 1;        //BIT3 PvIso故障
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
        }PVFault1_t;                                       //0x0086 PV故障1

        union
        {
            uint16_t u16Error;
            struct
            {
                uint16_t bPvErr                : 1;        //BIT0 故障
                uint16_t bPvUV                 : 1;        //BIT1 PV欠压
                uint16_t bPvOV                 : 1;        //BIT2 PV过压
                uint16_t bPvISOErr             : 1;        //BIT3 PvIso故障
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
        }PVFault2_t;                                       //0x0087 PV故障2
    }PVFault_t;
//0x0088-0x008F  预留
}PVInformation;
//#define EMS_TO_CLOUD_03H_PV_INFO_START                          (0x0080)
#define EMS_TO_CLOUD_03H_PV_INFO_LENGTH                         (sizeof(PVInformation) / 2)


typedef struct
{
    uint16_t u16BatTotalVolt;                                    //0x0090        电池总电压
    uint16_t u16BatTotalCurr;                                    //0x0091        电池总电流
    uint16_t u16LiveSOC;                                         //0x0092        实时SOC
    uint16_t u16AverSOH;                                         //0x0093        平均SOH
    uint16_t u16MiniSOH;                                         //0x0094        最小SOH
    uint16_t u16BatCharCap;                                      //0x0095        电池满充容量
    uint16_t u16BatRemainCap;                                    //0x0096        电池剩余容量
    uint16_t u16AverCycle;                                       //0x0097        平均循环次数
    uint16_t u16MaxCycle;                                        //0x0098        最大循环次数
    uint16_t u16SingUnitMaxVolt;                                 //0x0099        单体最高电压
    uint16_t u16HighVoltbitNumber;                               //0x009A        单体最高电压所属位号
    uint16_t u16SingUnitMiniVolt;                                //0x009B        单体最低电压
    uint16_t u16LowVoltbitNumber;                                //0x009C        单体最低电压所属位号
    uint16_t u16SingCoreHighTemp;                                    //0x009D        单芯最高温度
    uint16_t u16SingCoreHighTempbitNumber;                       //0x009E        单芯最高温度所属位号
    uint16_t u16SingCoreMiniTemp;                                //0x009F        单芯最低温度
    uint16_t u16SingCoreMiniTempbitNumber;                         //0x00A0        单芯最低温度所属位号
    uint16_t u16MaxCharCurr;                                     //0x00A1        最大充电电流
    uint16_t u16MaxDisharCurr;                                   //0x00A2        最大放电电流
    uint16_t u16UpperLimitCharVolt;                              //0x00A3        充电电压建议上限
    uint16_t u16UpperLimitDischarVolt;                           //0x00A4        放电电压建议上限
//0x00A5 电池故障1
//0x00A6 电池故障2
    struct
    {
        union
        {
            uint16_t u16Error;
            struct
            {
                uint8_t bBatOverVolt            : 1;       //BIT0 过压保护故障
                uint8_t bBatUnderVolt           : 1;       //BIT1 欠压保护
                uint8_t bHwOC                   : 1;       //BIT2 过流保护
                uint8_t bOutputShort            : 1;       //BIT3 短路保护
                uint8_t bHighTemp               : 1;       //BIT4 高温保护
                uint8_t bLowTemp                : 1;       //BIT5 低温保护
                uint8_t bDiffVolt               : 1;       //BIT6 压差保护
                uint8_t bSysErr                 : 1;       //BIT7 系统故障保护
                uint8_t bSoftStart              : 1;       //BIT8 软启动保护
                uint8_t bReserved9              : 1;       //BIT9 电池欠压
                uint8_t bReserved10             : 1;       //BIT10 电池未连接
                uint8_t bReserved11             : 1;       //BIT11 弱电池故障
                uint8_t bReserved12             : 1;       //BIT12 预留
                uint8_t bReserved13             : 1;       //BIT13 预留
                uint8_t bReserved14             : 1;       //BIT14 预留
                uint8_t bReserved15             : 1;       //BIT15 预留
            }Bits;
        }BatError1_t;
    
        union
        {
            uint16_t u16Error;
            struct
            {
                uint8_t bOVW                  : 1;     //BIT0  过压警告
                uint8_t bUVW                  : 1;     //BIT1  欠压警告
                uint8_t bOCW                  : 1;     //BIT2  过流警告
                uint8_t bHTW                  : 1;     //BIT3  高温警告
                uint8_t bLTW                  : 1;     //BIT4  低温警告
                uint8_t bDVW                  : 1;     //BIT5  压差警告
                uint8_t bReserved6            : 1;     //BIT6  预留
                uint8_t bReserved7            : 1;     //BIT7  预留
                uint8_t bReserved8            : 1;     //BIT8  预留
                uint8_t bReserved9            : 1;     //BIT9  预留
                uint8_t bReserved10           : 1;     //BIT10 预留
                uint8_t bReserved11           : 1;     //BIT11 预留
                uint8_t bReserved12           : 1;     //BIT12 预留
                uint8_t bReserved13           : 1;     //BIT13 预留
                uint8_t bReserved14           : 1;     //BIT14 预留
                uint8_t bReserved15           : 1;     //BIT15 预留
            }Bits;
        }BatWarning1_t;
    }BatError_t;
//DCDC变换器故障    0x00A7
    struct
    {
        union
        {
            uint16_t u16Error;
            struct
            {
                uint8_t bFault                  : 1;       //BIT0 故障
                uint8_t bMidBusOVP              : 1;       //BIT1 中间故障过压故障
                uint8_t bLLCHwOC                : 1;       //BIT2 LLC硬件过流
                uint8_t bBuckBoostHwOC          : 1;       //BIT3 BuckBoost硬件过流
                uint8_t bBuckBoostFwOC          : 1;       //BIT4 BuckBoost软件过流
                uint8_t bSOPChgOCP              : 1;       //BIT5 SOP充电过流保护
                uint8_t bSOPDisChgOCP           : 1;       //BIT6 SOP放电过流保护
                uint8_t bDCDCOverTemp           : 1;       //BIT7 DCDC过温保护
                uint8_t bBatOverVolt            : 1;       //BIT8 电池过压
                uint8_t bBatUnderVolt           : 1;       //BIT9 电池欠压
                uint8_t bBatNoConnected         : 1;       //BIT10 电池未连接
                uint8_t bWeakBatFault           : 1;       //BIT11 弱电池故障
                uint8_t bReserved5              : 1;       //BIT12 预留
                uint8_t bReserved6              : 1;       //BIT13 预留
                uint8_t bReserved7              : 1;       //BIT14 预留
                uint8_t bReserved8              : 1;       //BIT15 预留
            }Bits;
        }DCDCError1_t;
    }DCDC_Error_t;
//0x00A8-0x00AF  预留
}BatInformation;

//#define EMS_TO_CLOUD_03H_BAT_INFO_START                          (0x0090)
#define EMS_TO_CLOUD_03H_BAT_INFO_LENGTH                         (sizeof(BatInformation) / 2)


typedef struct
{
    uint16_t u16LoadVolt;             //0x00B0    负载电压
    uint16_t u16LoadFren;             //0x00B1    负载频率
    uint16_t u16LoadCurr;             //0x00B2    负载电流
    uint16_t u16LoadPercent;          //0x00B3    负载百分比

//0x00B4-0x00BF   预留
}LoadInformation;

//#define EMS_TO_CLOUD_03H_LOAD_INFO_START                          (0x00B0)
#define EMS_TO_CLOUD_03H_LOAD_INFO_LENGTH                         (sizeof(LoadInformation) / 2)




/******************************************************************
 0X03读实时数据逆变器信息数据：
*******************************************************************/
typedef struct
{
    int16_t  s16InvInductanceCurrU;                        //0x00C0 逆变器U相电感电流
    int16_t  s16InvInductanceCurrV;                        //0x00C1 逆变器V相电感电流
    int16_t  s16InvInductanceCurrW;                        //0x00C2 逆变器W相电感电流
    uint16_t u16InvVoltU;                                  //0x00C3 逆变器U相输出电压
    uint16_t u16InvVoltV;                                  //0x00C4 逆变器V相输出电压
    uint16_t u16InvVoltW;                                  //0x00C5 逆变器W相输出电压
    int16_t  s16InvCurrU;                                  //0x00C6 逆变器U相输出电流
    int16_t  s16InvCurrV;                                  //0x00C7 逆变器V相输出电流
    int16_t  s16InvCurrW;                                  //0x00C8 逆变器W相输出电流
    uint16_t u16InvOutputFreq;                             //0x00C9 逆变器输出频率
    int16_t  s16InvLoadCurrU;                              //0x00CA 逆变器U相负载电流
    int16_t  s16InvLoadCurrV;                              //0x00CB 逆变器V相负载电流
    int16_t  s16InvLoadCurrW;                              //0x00CC 逆变器W相负载电流
    int16_t  s16InvLoadCurrWattU;                          //0x00CD 逆变器U相负载侧有功功率
    int16_t  s16InvLoadCurrWattV;                          //0x00CE 逆变器V相负载侧有功功率
    int16_t  s16InvLoadCurrWattW;                          //0x00CF 逆变器W相负载侧有功功率
    int16_t  s16InvLoadCurrVarU;                           //0x00D0 逆变器U相负载侧无功功率
    int16_t  s16InvLoadCurrVarV;                           //0x00D1 逆变器V相负载侧无功功率
    int16_t  s16InvLoadCurrVarW;                           //0x00D2 逆变器W相负载侧无功功率
    uint16_t u16GenVoltU;                                  //0x00D3 发电机U相输出电压
    int16_t  s16GenVoltV;                                  //0x00D4 发电机V相输出电压
    int16_t  s16GenVoltW;                                  //0x00D5 发电机W相输出电压
    int16_t  s16GenCurrU;                                  //0x00D6 发电机U相输出电流
    int16_t  s16GenCurrV;                                  //0x00D7 发电机V相输出电流
    int16_t  s16GenCurrW;                                  //0x00D8 发电机W相输出电流
    uint16_t u16GenFreq;                                   //0x00D9 发电机频率
    int16_t  s16GenWattU;                                  //0x00DA 发电机U相有功功率
    int16_t  s16GenWattV;                                  //0x00DB 发电机V相有功功率
    int16_t  s16GenWattW;                                  //0x00DC 发电机W相有功功率
    int16_t  s16GenVarU;                                   //0x00DD 发电机U相无功功率
    int16_t  s16GenVarV;                                   //0x00DE 发电机V相无功功率
    int16_t  s16GenVarW;                                   //0x00DF 发电机W相无功功率
    uint16_t u16GenCap;                                    //0x00E0 发电机容量
//0x00E1  逆变器故障
    struct
    {
        union
        {
            uint16_t u16Error;
            struct
            {
                uint16_t bInvErr1               : 1;       //BIT0 逆变器故障1
                uint16_t bFwFastOC1             : 1;       //BIT1 软件过流快检1
                uint16_t bHwOV1                 : 1;       //BIT2 硬件过流1
                uint16_t bFwSlowOC1             : 1;       //BIT3 软件过流慢检1
                uint16_t bInvRlyErr1            : 1;       //BIT4 逆变器继电器故障1
                uint16_t bOTP1                  : 1;       //BIT5 过温故障1
                uint16_t bOVP1                  : 1;       //BIT6 过压故障1
                uint16_t bIgbtErr1              : 1;       //BIT7 IGBT故障1
                uint16_t bInductanceOT1         : 1;       //BIT8 电感过温1
                uint16_t bVoltDcComponentErr1   : 1;       //BIT9 电压直流分量故障1
                uint16_t bCurrDcComponentErr1   : 1;       //BIT10 电流直流分量故障1
                uint16_t bReserved1             : 1;       //BIT11 预留
                uint16_t bReserved2             : 1;       //BIT12 预留
                uint16_t bReserved3             : 1;       //BIT13 预留
                uint16_t bReserved4             : 1;       //BIT14 预留
                uint16_t bReserved5             : 1;       //BIT15 预留
            }Bits;
        }DeviceFault1_t;                                   //0x00E1 设备故障1
//0x00E2  并机故障
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
        }ParallelSysFault_t;                               //0x00E2 并机故障
    }InvFault_t;
//0x00E3-0x00FF  预留    
}InvInformation;

//#define EMS_TO_CLOUD_03H_INV_INFO_START                          (0x00C0)
#define EMS_TO_CLOUD_03H_INV_INFO_LENGTH                         (sizeof(InvInformation) / 2)


typedef struct
{
    uint16_t u16TotalGenerateTime;                       //0x0100 总发电时间
    uint16_t u16PVGenerateOnDay;                         //0x0101 当日PV发电量
    uint16_t u16LoadConsumptionOnDay;                    //0x0102 当日负载用电量
    uint16_t u16OutputOnDay;                             //0x0103 当日输出电量
    uint16_t u16InputOnDay;                              //0x0104 当日出入电量
    uint16_t u16CharOnDay;                               //0x0105 当日充电电量
    uint16_t u16DisCharOnDay;                            //0x0106 当日放电电量
    uint16_t u16PVGenerateOnMonth;                       //0x0107 当月PV发电量
    uint16_t u16LoadConsumptionOnMonth;                  //0x0108 当月负载用电量
    uint16_t u16OutputOnMonth;                           //0x0109 当月输出电量
    uint16_t u16InputOnMonth;                            //0x010A 当月出入电量
    uint16_t u16CharOnMonth;                             //0x010B 当月充电电量
    uint16_t u16DisCharOnMonth;                          //0x010C 当月放电电量
    uint32_t u32PVGenerateOnYear;                        //0x010D-0x010E 当年PV发电量
    uint32_t u32LoadConsumptionOnYear;                   //0x010F-0x0110 当年负载用电量
    uint32_t u32OutputOnYear;                            //0x0111-0x0112 当年输出电量
    uint32_t u32InputOnYear;                             //0x0113-0x0114 当年出入电量
    uint32_t u32CharOnYear;                              //0x0115-0x0116 当年充电电量
    uint32_t u32DisCharOnYear;                           //0x0117-0x0118 当年放电电量
    uint32_t u32PVGenerateTotal;                         //0x0119-0x011A 累积PV发电量
    uint32_t u32LoadConsumptionTotal;                    //0x011B-0x011C 累积负载用电量
    uint32_t u32OutputTotal;                             //0x011D-0x011E 累积输出电量
    uint32_t u32InputTotal;                              //0x011F-0x0120 累积出入电量
    uint32_t u32CharTotal;                               //0x0121-0x0122 累积充电电量
    uint32_t u32DisCharTotal;                            //0x0123-0x0124 累积放电电量
//0x0125-0x01FF  预留
}SystemStatistical;


//#define EMS_TO_CLOUD_03H_GIRD_INFO_START                          (0x0100)
#define EMS_TO_CLOUD_03H_GIRD_INFO_LENGTH                         (sizeof(SystemStatistical) / 2)


/******************************************************************
 0X10(写单个或多个寄存器)写设置参数 能量管理数据：
*******************************************************************/


/*功能：BMS_CLOUD 10功能码协议地址识别表*/
typedef enum
{
    EMS_TO_CLOUD_10H_SYS_PARAM_START               =  0x0000,
    EMS_TO_CLOUD_10H_SYS_PARAM_END                 =  0x001F,
    EMS_TO_CLOUD_10H_PV_CTRL_PARAM_START           =  0x0020,
    EMS_TO_CLOUD_10H_PV_CTRL_PARAM_END             =  0x002F,
    EMS_TO_CLOUD_10H_BAT_SET_PARAM_START           =  0x0030,
    EMS_TO_CLOUD_10H_BAT_SET_PARAM_END             =  0x004F,
    EMS_TO_CLOUD_10H_INV_CTRL_START                =  0x0050,
    EMS_TO_CLOUD_10H_INV_CTRL_END                  =  0x006F,
    EMS_TO_CLOUD_10H_GEN_PARAM_START               =  0x0070,
    EMS_TO_CLOUD_10H_GEN_PARAM_END                 =  0x007F,
    EMS_TO_CLOUD_10H_STRATEGY_TIME_PARAM_START     =  0x0080,
    EMS_TO_CLOUD_10H_STRATEGY_TIME_PARAM_END       =  0x00AF,
}EMS_DATA_CLOUD_10H_ADDRESS;



typedef struct
{
    uint16_t u16ProtocolFlag;                              //0x0000 协议标识
    uint16_t u16LanguageType;                              //0x0001 语言
    uint16_t u16SysYear;                                   //0x0002 日期校正-年
    uint16_t u16SysMonth;                                  //0x0003 日期校正-月
    uint16_t u16SysDay;                                    //0x0004 日期校正-日
    uint16_t u16SysWeek;                                   //0x0005 时间校正-周
    uint16_t u16SysHour;                                   //0x0006 时间校正-时
    uint16_t u16SysMinute;                                 //0x0007 时间校正-分
    uint16_t u16SysSecond;                                 //0x0008 时间校正-秒
    uint16_t u16IslandProt;                                //0x0009 孤岛保护
    uint16_t u16GroundProt;                                //0x000A 接地保护
    uint16_t u16InsulationResProt;                         //0x000B 绝缘阻抗保护
    //0x000B-0x001F 预留
}EmsSysParam_t;
//#define EMS_TO_CLOUD_10H_SYS_PARAM_START                       (0x0000)
#define EMS_TO_CLOUD_10H_SYS_PARAM_LENGTH                      (sizeof(EmsSysParam_t) / 2)


typedef struct
{
    uint16_t u16PVCtrlWay;                           //0x0020 光伏控制方式
    uint16_t u16OpenVolt;                            //0x0021 开路电压设置
    //0x0021-0x002F  预留
}EmsPvCtrlParam_t;

//#define EMS_TO_CLOUD_10H_PV_CTRL_PARAM_START                           (0x0020)
#define EMS_TO_CLOUD_10H_PV_CTRL_PARAM_LENGTH                          (sizeof(EmsPvCtrlParam_t) / 2)

//LI.ION电池BMS参数设置结构体
typedef struct {
    uint16_t u16ProtocolType;            //0x0031   电池协议类型:0:无电池 1:CVTE 2:派能
    uint16_t u16ComWayFlag;              //0x0032   通信方式 0:CAN 1:485通信 
    uint16_t u16EndOfCharSOC;            //0x0033   充电截止SOC
    uint16_t u16EndOfDisCharSOC;         //0x0034   放电截止SOC
    uint16_t u16MaxCharCurrent;          //0x0035   最大充电电流
    uint16_t u16MaxDisCharCurrent;       //0x0036   最大放电电流
}BMSLiIonParas;


//LEAD.ACID电池BMS参数设置结构体
typedef struct {
    uint16_t u16BatteryCapacity;         //0x0037   电池容量设置 
    uint16_t u16EndOfCharSOC;            //0x0038   充电截止SOC
    uint16_t u16EndOfDisCharSOC;         //0x0039   放电截止SOC
    uint16_t u16MaxCharCurrent;          //0x003A   最大充电电流
    uint16_t u16MaxDisCharCurrent;       //0x003B   最大放电电流
    uint16_t u16LowVoltShutPoint;        //0x003C   低压关机电压点 
    uint16_t u16FloatVoltPoint;          //0x003D   浮动电压点
    uint16_t u16ConstVoltCharPoint;      //0x003E   恒压充电电压点
}BMSLeadAcidParas;

//LCD屏电池BMS参数设置结构体
typedef struct {
    uint16_t u16Type;                        //0x0030   电池类型(默认0) 0:磷酸铁锂 1:铅酸电池
    BMSLiIonParas BatteryLiParas;
    BMSLeadAcidParas BatteryLeadParas; 
    //0x003E-0x004F  预留
}EmsBatteryParam_t;

//#define EMS_TO_CLOUD_10H_BAT_SET_PARAM_START                           (0x0030)
#define EMS_TO_CLOUD_10H_BAT_SET_PARAM_LENGTH                          (sizeof(EmsBatteryParam_t) / 2)

typedef struct
{
    uint16_t u16NoBackflowCtrl;                                //0x0050    防逆流控制
    uint16_t u16GridConnectRule;                               //0x0051    并网准则
    uint16_t u16ReactPowerControlWay;                          //0x0052    无功控制方式：0：无功控制 1：PF控制
    uint16_t u16ActivePower;                                    //0x0053    有功功率
    uint16_t u16ReactivePower;                                  //0x0054    无功功率
    int16_t  u16PowerFactor;                                   //0x0055    功率因数
    uint16_t u16SampSelect;                                    //0x0056    采样选择
    uint16_t u16PeakElecPrice;                                 //0x0057    峰段电价
    uint16_t u16FlatElecPrice;                                 //0x0058    平段电价
    uint16_t u16ValleyElecPrice;                               //0x0059    谷段电价
    //0x005A-0x006F 预留
}EmsInvCtrlParam_t;
//#define EMS_TO_CLOUD_10H_INV_CTRL_START                        (0x0050)
#define EMS_TO_CLOUD_10H_INV_CTRL_LENGTH                       (sizeof(EmsInvCtrlParam_t) / 2)


typedef struct
{
    uint16_t u16GenInterf;                                //0x0070 发电机接口设置
    uint16_t u16GenRatedPower;                            //0x0071 发电机额定功率
    uint16_t u16GenMaxPower;                              //0x0072 发电机最大功率
    uint16_t u16EmsFbdGenChgSOC;                          //0x0073 发电机禁止充电SOC(退出)
    uint16_t u16EmsSupplySOC;                             //0x0074 发电机补电模式SOC(接入)
    uint16_t u16AILoadExitSOC;                            //0x0075 智能负载退出SOC
    uint16_t u16AILoadEnterSOC;                           //0x0076 智能负载接入SOC
    //0x0077-0x007F 预留
}EmsGenParam_t;
//#define EMS_TO_CLOUD_10H_GEN_PARAM_START                           (0x0070)
#define EMS_TO_CLOUD_10H_GEN_PARAM_LENGTH                          (sizeof(EmsGenParam_t) / 2)


typedef struct
{
    uint16_t u16StrategySelect;                            //0x0080 策略选择
    uint16_t u16Peak1StartTime;                            //0x0081 峰谷模式/峰段1开始时分
    uint16_t u16Peak1EndTime;                              //0x0082 峰谷模式/峰段1结束时分
    uint16_t u16Peak2StartTime;                            //0x0083 峰谷模式/峰段2开始时分
    uint16_t u16Peak2EndTime;                              //0x0084 峰谷模式/峰段2结束时分
    uint16_t u16Peak3StartTime;                            //0x0085 峰谷模式/峰段3开始时分
    uint16_t u16Peak3EndTime;                              //0x0086 峰谷模式/峰段3结束时分
    uint16_t u16Valley1StartTime;                          //0x0087 峰谷模式/谷段1开始时分
    uint16_t u16Valley1EndTime;                            //0x0088 峰谷模式/谷段1结束时分
    uint16_t u16Valley2StartTime;                          //0x0089 峰谷模式/谷段2开始时分
    uint16_t u16Valley2EndTime;                            //0x008A 峰谷模式/谷段2结束时分
    uint16_t u16Valley3StartTime;                          //0x008B 峰谷模式/谷段3开始时分
    uint16_t u16Valley3EndTime;                            //0x008C 峰谷模式/谷段3结束时分
    uint16_t u16RegularChar1StartTime;                     //0x008D 定时充放电模式/充电时间段1开始时分
    uint16_t u16RegularChar1EndTime;                       //0x008E 定时充放电模式/充电时间段1结束时分
    uint16_t u16RegularChar2StartTime;                     //0x008F 定时充放电模式/充电时间段2开始时分
    uint16_t u16RegularChar2EndTime;                       //0x0090 定时充放电模式/充电时间段2结束时分
    uint16_t u16RegularChar3StartTime;                     //0x0091 定时充放电模式/充电时间段3开始时分
    uint16_t u16RegularChar3EndTime;                       //0x0092 定时充放电模式/充电时间段3结束时分
    uint16_t u16RegularDisChar1StartTime;                  //0x0093 定时充放电模式/放电时间段1开始时分
    uint16_t u16RegularDisChar1EndTime;                    //0x0094 定时充放电模式/放电时间段1结束时分
    uint16_t u16RegularDisChar2StartTime;                  //0x0095 定时充放电模式/放电时间段2开始时分
    uint16_t u16RegularDisChar2EndTime;                    //0x0096 定时充放电模式/放电时间段2结束时分
    uint16_t u16RegularDisChar3StartTime;                  //0x0097 定时充放电模式/放电时间段3开始时分
    uint16_t u16RegularDisChar3EndTime;                    //0x0098 定时充放电模式/放电时间段3结束时分
    //0x0098-0x00AF 预留
}EmsStrategyTimeParam_t;

//#define EMS_TO_CLOUD_10H_STRATEGY_TIME_PARAM_START                           (0x0080)
#define EMS_TO_CLOUD_10H_STRATEGY_TIME_PARAM_LENGTH                          (sizeof(EmsStrategyTimeParam_t) / 2)


typedef struct
{
    struct
    {
        TotalSysParam tEMSTotalParam;
        GridStdParam  tEMSGirdParm;
        PVInformation tEMSPVInfo;
        BatInformation tEMSBatInfo;
        LoadInformation tEMSLoadInfo;
        InvInformation tEMSInvGenInfo;
        SystemStatistical tEMSStatisticalInfo;
    }Register03H_t;

    struct
    {
        EmsSysParam_t tEmsSysParam;
        EmsPvCtrlParam_t tEmsPvControlWay;
        EmsBatteryParam_t tEmsBatteryDate;
        EmsInvCtrlParam_t tEmsInvCtrlParam;
        EmsGenParam_t tEmsGenParam;
        EmsStrategyTimeParam_t  tEmsStrategyTime;   
    }Register10H_t;

}InternalCloud_t;

extern InternalCloud_t tInternalCloudData;                //对接云平台内部通讯的数据结构

/*检查BMS_CLOUD协议功能码03H的通讯数据范围是否越界*/
extern MBErrorCode CheckEmsCloudComDataRange_03H(MBRTUFrame_t* ptMBFrame);
/*定位起始地址对应的英臻云平台协议功能码03H的数据结构地址*/
extern uint16_t* GetComDataToCloud_03H(MBRTUFrame_t* ptMBFrame);



/*系统数据获取*/
void GetTotalSysParamToCloudData(void);
/*电网并网的数据获取*/
void GetGirdParmInfoToCloudData(void);
/*PV数据获取*/
void GetPVInfoToCloudData(void);
/*电池的数据获取*/
void GetBatInfoToCloudData(void);
/*负载数据获取*/
void GetLoadInfoToCloudData(void);
/*逆变器和发电机数据获取*/
void GetInvGenInfoToCloudData(void);
/*统计数据获取*/
void GetSystemStatisticalToCloudData(void);

/*检查BMS_CLOUD协议功能码10H的通讯数据范围是否越界*/
extern MBErrorCode CheckEmsCloudComDataRange_10H(MBRTUFrame_t* ptMBFrame);

/*定位起始地址对应的英臻云平台协议功能码10H的数据结构地址*/
extern uint16_t* GetComDataToCloud_10H(MBRTUFrame_t* ptMBFrame);

/*设置系统参数时间*/
void GetCloudInputSysParamTimeSet(void);

typedef struct {
    uint16_t u16hour;
    uint16_t u16minute;
}CloudTime_t;
/*获取转换输入时间*/
CloudTime_t GetConvertCloudInputTime(uint16_t u16CloudTime);

/*获取输入尖峰平谷和定时充放电时间*/
void GetCloudInputTPFVTimeSet(void);

/*获取电池数据*/
void GetCloudBatteryDataSet(void);

/*逆变器控制参数设置*/
void GetCloudInputInvCtrlParamSet(void);

/*获取PV光伏参数设置*/
void GetCloudInputPvCtrlParamSet(void);

/*获取英臻通信下设参数设置*/
void SetComDataToCloud_10H(MBRTUFrame_t* ptMBFrame);

#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

