/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Modbus_BMS_COMData.h 
 用途 : modbusBMS协议数据头文件
***********************************************************************************************************************/
#ifndef _MODBUS_BMS_COMDATA_H_
#define _MODBUS_BMS_COMDATA_H_

#include "HeadFile.h"
#include "Modbus.h"
#include "LCD_Service.h"
#include "Fault_Management_Service.h"
#include "Canbus_BMS_COMData.h"

extern BMS_Manu_TypeDef MBBmsProtocolType;
extern BMS_COMWAY_TypeDef BmsComWayType;
/******************************************************************
 Modbus BMS协议公用数据结构
*******************************************************************/
typedef struct
{
    uint16_t u16BMSDataStatus;
    uint16_t u16BMSDataVolt;
    int16_t  s16BMSDataChgCurr;
    int16_t  s16BMSDataDisChgCurr;
    int16_t  s16BMSDataTemp;
    uint16_t u16BMSDataSOC;
    uint16_t u16BMSDataRemainingCap;
    uint16_t u16BMSDataFullCap;
    union
    {
        uint16_t u16Word;
        struct
        {
            uint8_t bOverVoltProt         : 1;
            uint8_t bUnderVoltProt        : 1;
            uint8_t bOverCurrProt         : 1;
            uint8_t bShortCircuitProt     : 1;
            uint8_t bHighTempProt         : 1;
            uint8_t bUnderTempProt        : 1;
            uint8_t bSystemProt           : 1;
            uint8_t bLowPowerProt         : 1;
            uint8_t bSoftStartProt        : 1;
            uint8_t bReserved             : 7;
        }Bits;
    }BMSError_t;

    union
    {
        uint16_t u16Word;
        struct
        {
            uint8_t bOverVoltAlarm        : 1;
            uint8_t bUnderVoltAlarm       : 1;
            uint8_t bOverCurrAlarm        : 1;
            uint8_t bHighTempAlarm        : 1;
            uint8_t bLowTempAlarm         : 1;
            uint8_t bSystemAlarm          : 1;
            uint8_t bVoltDiffAlarm        : 1;
            uint8_t bOverChgAlarm         : 1;
            uint8_t bReverseAlarm         : 1;
            uint8_t bLowCapAlarm          : 1;
            uint8_t bLowPowerShutAlarm    : 1;
            uint8_t bReserved             : 5;
        }Bits;
    }BMSWarning_t;

    uint16_t u16BMSDataMaxChgCurr;
    uint16_t u16BMSDataCVVolt;
    uint16_t u16BMSDataReserved0;
    uint16_t u16BMSDataReserved1;
    uint16_t u16BMSDataReserved2;
    uint16_t u16BMSDataReserved3;
    uint16_t u16BMSDataReserved4;
} UnifiedBMSData_t;
extern UnifiedBMSData_t tUnifiedBMSData;

/******************************************************************
 Modbus BMS_CVTE协议数据结构
*******************************************************************/
typedef struct
{
    uint16_t u16SerialNumber[16];                   //0x0001~0x0010
    uint16_t u16McuVersion;                         //0x0011

    union
    {
        uint16_t u16Info;
        struct
        {
            uint8_t bBmsCompany           : 8;     //BIT0~BIT7
            uint8_t bBmsVersion           : 8;     //BIT8~BIT15
        }Bits;
    }BMSInfo_t;                                     //0x0012

    union
    {
        uint16_t u16Info;
        struct
        {
            uint8_t bbatteryType          : 8;     //BIT0~BIT7
            uint8_t bReserved             : 8;     //BIT8~BIT15
        }Bits;
    }BatteryInfo_t;                                 //0x0013

    uint16_t u16Reserved1;                          //0x0014
    uint16_t u16Reserved2;                          //0x0015
    uint16_t u16Reserved3;                          //0x0016
    uint16_t u16Reserved4;                          //0x0017
    uint16_t u16Reserved5;                          //0x0018
    uint16_t u16Reserved6;                          //0x0019
    uint16_t u16Reserved7;                          //0x001A
    uint16_t u16Reserved8;                          //0x001B
    uint16_t u16Reserved9;                          //0x001C
    uint16_t u16Reserved10;                         //0x001D
    uint16_t u16Reserved11;                         //0x001E
    uint16_t u16Reserved12;                         //0x001F
}BmsDataCvteVersionInfo_t;

typedef struct
{
    union
    {
        uint16_t u16Word;
        struct
        {
            uint8_t bMode                 : 2;     //BIT0~BIT1   状态
            uint8_t bErrorFlag            : 1;     //BIT2        错误位标志
            uint8_t bCellBalanceFlag      : 1;     //BIT3        电芯均衡状态
            uint8_t bSleepFlag            : 1;     //BIT4        休眠状态
            uint8_t bDischgFlag           : 1;     //BIT5        放电输出状态
            uint8_t bChgFlag              : 1;     //BIT6        充电输入状态
            uint8_t bBatTerminalFlag      : 1;     //BIT7        电池端子状态
            uint8_t bMasterOperationMode  : 2;     //BIT8~BIT9   主机操作模式
            uint8_t bSPStatus             : 2;     //BIT10~BIT11 SP状态
            uint8_t bRequestForceChg      : 1;     //BIT12       强制充电要求
            uint8_t bReserved13           : 1;     //BIT13       预留
            uint8_t bReserved14           : 1;     //BIT14       预留
            uint8_t bReserved15           : 1;     //BIT15       预留
        }Bits;
    }Status_t;                                      //0x0020 状态信息

    uint16_t u16Voltage;                            //0x0021 电池电压
    int16_t  s16Current;                            //0x0022 电池电流
    int16_t  s16MaxTemperature;                     //0x0023 电芯最高温度
    uint16_t u16SOC;                                //0x0024 SOC
    uint16_t u16RemainingCapacity;                  //0x0025 剩余容量
    uint16_t u16FullingCapacity;                    //0x0026 满充容量

    union
    {
        uint16_t u16Word;
        struct
        {
            uint8_t bOVP                  : 1;     //BIT0  过压保护
            uint8_t bUVP                  : 1;     //BIT1  欠压保护
            uint8_t bOCP                  : 1;     //BIT2  过流保护
            uint8_t bSCP                  : 1;     //BIT3  短路保护
            uint8_t bHTP                  : 1;     //BIT4  高温保护
            uint8_t bLTP                  : 1;     //BIT5  低温保护
            uint8_t bDVP                  : 1;     //BIT6  压差保护
            uint8_t bSysError             : 1;     //BIT7  系统故障保护
            uint8_t bSoftStart            : 1;     //BIT8  软启动保护
            uint8_t bReserved9            : 1;     //BIT9  预留
            uint8_t bReserved10           : 1;     //BIT10 预留
            uint8_t bReserved11           : 1;     //BIT11 预留
            uint8_t bReserved12           : 1;     //BIT12 预留
            uint8_t bReserved13           : 1;     //BIT13 预留
            uint8_t bReserved14           : 1;     //BIT14 预留
            uint8_t bReserved15           : 1;     //BIT15 预留
        }Bits;
    }Error_t;                                       //0x0027

    union
    {
        uint16_t u16Word;
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
    }Warning_t;                                     //0x0028

    uint16_t u16MaxChargeCurr;                      //0x0029 最大充电电流
    uint16_t u16CVVoltage;                          //0x002A CV电压
    uint16_t u16SOH;                                //0x002B SOH
    uint16_t u16CycleCnt;                           //0x002C 循环次数
    uint16_t u16RemainingChgTime;                   //0x002D 充电剩余时间
    uint16_t u16MaxCellVolt;                        //0x002E 单体最高电压
    uint16_t u16MaxCellVoltIndex;                   //0x002F 单体最高电压所属位号
    uint16_t u16MinCellVolt;                        //0x0030 单体最低电压
    uint16_t u16MinCellVoltIndex;                   //0x0031 单体最低电压所属位号
    uint16_t u16CellDiffVolt;                       //0x0032 电芯压差
    int16_t  s16MaxCellTemp;                        //0x0033 单芯最高温度
    int16_t  s16MaxCellTempIndex;                   //0x0034 单芯最高温度所属位号
    int16_t  s16MinCellTemp;                        //0x0035 单芯最低温度
    int16_t  s16MinCellTempIndex;                   //0x0036 单芯最低温度所属位号
    uint16_t u16Reserved37;                         //0x0037 预留
    uint16_t u16Reserved38;                         //0x0038 预留
    uint16_t u16Reserved39;                         //0x0039 预留
    uint16_t u16Reserved40;                         //0x003A 预留
    uint16_t u16Reserved41;                         //0x003B 预留
    uint16_t u16Reserved42;                         //0x003C 预留
    uint16_t u16Reserved43;                         //0x003D 预留
    uint16_t u16Reserved44;                         //0x003E 预留
    uint16_t u16Reserved45;                         //0x003F 预留
}BmsDataCvtePrimaryInfo_t;

typedef struct
{
    uint16_t u16CellNum;                            //0x0040 电池串数
    uint16_t u16CellVolt1;                          //0x0041 第1节电池电压
    uint16_t u16CellVolt2;                          //0x0042 第2节电池电压
    uint16_t u16CellVolt3;                          //0x0043 第3节电池电压
    uint16_t u16CellVolt4;                          //0x0044 第4节电池电压
    uint16_t u16CellVolt5;                          //0x0045 第5节电池电压
    uint16_t u16CellVolt6;                          //0x0046 第6节电池电压
    uint16_t u16CellVolt7;                          //0x0047 第7节电池电压
    uint16_t u16CellVolt8;                          //0x0048 第8节电池电压
    uint16_t u16CellVolt9;                          //0x0049 第9节电池电压
    uint16_t u16CellVolt10;                         //0x004A 第10节电池电压
    uint16_t u16CellVolt11;                         //0x004B 第11节电池电压
    uint16_t u16CellVolt12;                         //0x004C 第12节电池电压
    uint16_t u16CellVolt13;                         //0x004D 第13节电池电压
    uint16_t u16CellVolt14;                         //0x004E 第14节电池电压
    uint16_t u16CellVolt15;                         //0x004F 第15节电池电压
    uint16_t u16CellVolt16;                         //0x0050 第16节电池电压
    uint16_t u16CellVolt17;                         //0x0051 第17节电池电压
    uint16_t u16CellVolt18;                         //0x0052 第18节电池电压
    uint16_t u16CellVolt19;                         //0x0053 第19节电池电压
    uint16_t u16CellVolt20;                         //0x0054 第20节电池电压
    uint16_t u16CellVolt21;                         //0x0055 第21节电池电压
    uint16_t u16CellVolt22;                         //0x0056 第22节电池电压
    uint16_t u16CellVolt23;                         //0x0057 第23节电池电压
    uint16_t u16CellVolt24;                         //0x0058 第24节电池电压
    uint16_t u16CellVolt25;                         //0x0059 第25节电池电压
    uint16_t u16CellVolt26;                         //0x005A 第26节电池电压
}BmsDataCvteVoltageInfo_t;

typedef struct
{
    int16_t  s16AmbientTemp;                        //0x0060 环境温度
    int16_t  s16Mosfet1Temp;                        //0x0061 MOS1温度
    int16_t  s16Mosfet2Temp;                        //0x0062 MOS2温度
    int16_t  s16Mosfet3Temp;                        //0x0063 MOS3温度
    int16_t  s16NtcNum;                             //0x0064 NTC个数
    int16_t  s16NTC1Temp;                           //0x0065 第1个NTC温度
    int16_t  s16NTC2Temp;                           //0x0066 第2个NTC温度
    int16_t  s16NTC3Temp;                           //0x0067 第3个NTC温度
    int16_t  s16NTC4Temp;                           //0x0068 第4个NTC温度
    int16_t  s16NTC5Temp;                           //0x0069 第5个NTC温度
    int16_t  s16NTC6Temp;                           //0x006A 第6个NTC温度
    int16_t  s16NTC7Temp;                           //0x006B 第7个NTC温度
    int16_t  s16NTC8Temp;                           //0x006C 第8个NTC温度
    int16_t  s16NTC9Temp;                           //0x006D 第9个NTC温度
    int16_t  s16NTC10Temp;                          //0x006E 第10个NTC温度
}BmsDataCvteTempInfo_t;

/*BMS_CVTE协议数据结构*/
typedef struct
{
    BmsDataCvteVersionInfo_t tBmsCvteVersionInfo;  //版本信息
    BmsDataCvtePrimaryInfo_t tBmsCvtePrimaryInfo;  //主要信息
    BmsDataCvteVoltageInfo_t tBmsCvteVoltageInfo;  //电压信息
    BmsDataCvteTempInfo_t    tBmsCvteTempInfo;     //温度信息
}BmsDataCvte_t;
extern BmsDataCvte_t tBmsDataCvte;

/*BMS_CVTE协议首地址*/
#define BMS_CVTE_03H_VERSION_INFO_START            (0x0001)
#define BMS_CVTE_03H_PRIMARY_INFO_START            (0x0020)
#define BMS_CVTE_03H_VOLTAGE_INFO_START            (0x0040)
#define BMS_CVTE_03H_TEMP_INFO_START               (0x0060)

/*BMS_CVTE协议数据长度*/
#define BMS_CVTE_03H_VERSION_INFO_LENGTH           (sizeof(tBmsDataCvte.tBmsCvteVersionInfo) / 2)
#define BMS_CVTE_03H_PRIMARY_INFO_LENGTH           (sizeof(tBmsDataCvte.tBmsCvtePrimaryInfo) / 2)
#define BMS_CVTE_03H_VOLTAGE_INFO_LENGTH           (sizeof(tBmsDataCvte.tBmsCvteVoltageInfo) / 2)
#define BMS_CVTE_03H_TEMP_INFO_LENGTH              (sizeof(tBmsDataCvte.tBmsCvteTempInfo) / 2)

/******************************************************************
 BMS_Plyon协议获取电池组系统基本信息 60H
*******************************************************************/
typedef struct
{
    uint16_t u16DeviceName;                         //主机设备名称
    uint16_t u16ManufacturerName;                   //主机厂商名称
    uint16_t u16SoftwareVersion;                    //主机软件版本
    uint16_t u16BatteryNum;                         //电池数量
    uint16_t u16BatteryBarcode1;                    //电池1条形码
    uint16_t u16BatteryBarcode2;                    //电池2条形码
}BmsDataPylonBasicInfo_t;

/******************************************************************
 BMS_Plyon协议获取电池系统运行模拟量信息 61H
*******************************************************************/
typedef struct
{
    uint16_t u16SystemAvgVolt;                      //电池组系统总平均电压
    int16_t  s16SystemTotalCurr;                    //电池组系统总电流
    uint16_t u16SystemSOC;                          //电池组系统 SOC
    uint16_t u16AvgCycleCnt;                        //平均循环次数
    uint16_t u16MaxCycleCnt;                        //最大循环次数
    uint16_t u16AvgSOH;                             //平均 SOH
    uint16_t u16MinSOH;                             //最小 SOH
    uint16_t u16MaxSingleVolt;                      //单芯最高电压
    uint16_t u16MaxSingleVoltPos;                   //单芯最高电压所在模块
    uint16_t u16MinSingleVolt;                      //单芯最低电压
    uint16_t u16MinSingleVoltPos;                   //单芯最低电压所在模块
    int16_t  s16SingleAvgTemp;                      //单芯平均温度
    int16_t  s16SingleMaxTemp;                      //单芯最高温度
    uint16_t u16SingleMaxTempPos;                   //单芯最高温度所在模块
    int16_t  s16SingleMinTemp;                      //单芯最低温度
    uint16_t u16SingleMinTempPos;                   //单芯最低温度所在模块
    int16_t  s16MosfetAvgTemp;                      //MOSFET 平均温度
    int16_t  s16MosfetMaxTemp;                      //MOSFET 最高温度
    uint16_t u16MosfetMaxTempPos;                   //MOSFET 最高温度所在模块
    int16_t  s16MosfetMinTemp;                      //MOSFET 最低温度
    uint16_t u16MosfetMinTempPos;                   //MOSFET 最低温度所在模块
    int16_t  s16BmsAvgTemp;                         //BMS 平均温度
    int16_t  s16BmsMaxTemp;                         //BMS 最高温度
    uint16_t u16BmsMaxTempPos;                      //BMS 最高温度所在模块
    int16_t  s16BmsMinTemp;                         //BMS 最低温度
    uint16_t u16BmsMinTempPos;                      //BMS 最低温度所在模块
}BmsDataPylonAnalogInfo_t;

/******************************************************************
 BMS_Plyon协议获取电池组系统状态告警量数据 62H
*******************************************************************/
typedef struct
{
    union
    {
        uint16_t u16Warnning;
        struct
        {
            uint8_t bSingleVoltDiff        : 1;     //BIT0 单芯电压一致性告警
            uint8_t bMosfetOT              : 1;     //BIT1 MOSFET 高温
            uint8_t bSingleUT              : 1;     //BIT2 单芯温度低温
            uint8_t bSingleOT              : 1;     //BIT3 单芯温度高温
            uint8_t bSingleVoltUV          : 1;     //BIT4 单芯电压低压
            uint8_t bSingleVoltOV          : 1;     //BIT5 单芯电压高压
            uint8_t bTotalVoltUV           : 1;     //BIT6 模块总压低压
            uint8_t bTotalVoltOV           : 1;     //BIT7 模块总压高压
            uint8_t bReserved0             : 1;     //BIT8 预留
            uint8_t bReserved1             : 1;     //BIT9 预留
            uint8_t bReserved2             : 1;     //BIT10 预留
            uint8_t bReserved3             : 1;     //BIT11 预留
            uint8_t bReserved4             : 1;     //BIT12 预留
            uint8_t bReserved5             : 1;     //BIT13 预留
            uint8_t bReserved6             : 1;     //BIT14 预留
            uint8_t bReserved7             : 1;     //BIT15 预留
        }Bits;
    }SystemAlarm1_t;                                //系统告警状态 1

    union
    {
        uint16_t u16Warnning;
        struct
        {
            uint8_t bReserved0             : 1;     //BIT0 预留
            uint8_t bReserved1             : 1;     //BIT1 预留
            uint8_t bReserved2             : 1;     //BIT2 预留
            uint8_t bReserved3             : 1;     //BIT3 预留
            uint8_t bInternalComErr        : 1;     //BIT4 内部通信错误
            uint8_t bOCD                   : 1;     //BIT5 放电过流告警
            uint8_t bOCC                   : 1;     //BIT6 充电过流告警
            uint8_t bSingleTempDiff        : 1;     //BIT7 单芯温度一致性告警
            uint8_t bReserved4             : 1;     //BIT8 预留
            uint8_t bReserved5             : 1;     //BIT9 预留
            uint8_t bReserved6             : 1;     //BIT10 预留
            uint8_t bReserved7             : 1;     //BIT11 预留
            uint8_t bReserved8             : 1;     //BIT12 预留
            uint8_t bReserved9             : 1;     //BIT13 预留
            uint8_t bReserved10            : 1;     //BIT14 预留
            uint8_t bReserved11            : 1;     //BIT15 预留
        }Bits;
    }SystemAlarm2_t;                                //系统告警状态 2

    union
    {
        uint16_t u16Error;
        struct
        {
            uint8_t bReserved0             : 1;     //BIT0 预留
            uint8_t bMosfetOT              : 1;     //BIT1 MOSFET 过温
            uint8_t bSingleUT              : 1;     //BIT2 单芯温度欠温
            uint8_t bSingleOT              : 1;     //BIT3 单芯温度过温
            uint8_t bSingleUV              : 1;     //BIT4 单芯电压欠压
            uint8_t bSingleOV              : 1;     //BIT5 单芯电压过压
            uint8_t bTotalModeUV           : 1;     //BIT6 模块总压欠压
            uint8_t bTotalModeOV           : 1;     //BIT7 模块总压过压
            uint8_t bReserved1             : 1;     //BIT8 预留
            uint8_t bReserved2             : 1;     //BIT9 预留
            uint8_t bReserved3             : 1;     //BIT10 预留
            uint8_t bReserved4             : 1;     //BIT11 预留
            uint8_t bReserved5             : 1;     //BIT12 预留
            uint8_t bReserved6             : 1;     //BIT13 预留
            uint8_t bReserved7             : 1;     //BIT14 预留
        }Bits;
    }SystemError1_t;                                //系统保护状态 1

    union
    {
        uint16_t u16Error;
        struct
        {
            uint8_t bReserved0             : 1;     //BIT0 预留
            uint8_t bReserved1             : 1;     //BIT1 预留
            uint8_t bReserved2             : 1;     //BIT2 预留
            uint8_t bSysFault              : 1;     //BIT3 系统故障保护
            uint8_t bReserved3             : 1;     //BIT4 预留
            uint8_t bOCD                   : 1;     //BIT5 放电过流告警
            uint8_t bOCC                   : 1;     //BIT6 充电过流告警
            uint8_t bReserved4             : 1;     //BIT7 预留
            uint8_t bReserved5             : 1;     //BIT8 预留
            uint8_t bReserved6             : 1;     //BIT9 预留
            uint8_t bReserved7             : 1;     //BIT10 预留
            uint8_t bReserved8             : 1;     //BIT11 预留
            uint8_t bReserved9             : 1;     //BIT12 预留
            uint8_t bReserved10            : 1;     //BIT13 预留
            uint8_t bReserved11            : 1;     //BIT14 预留
            uint8_t bReserved12            : 1;     //BIT15 预留
        }Bits;
    }SystemError2_t;                                //系统保护状态 2
}BmsDataPylonAlarmInfo_t;

/******************************************************************
 BMS_Plyon协议获取电池组系统充放电管理交互信息 63H
*******************************************************************/
typedef struct
{
    uint16_t u16ChgVoltHighLimit;                   //充电电压建议上限
    uint16_t u16DisChgVoltLowLimit;                 //放电电压建议下限
    int16_t  s16MaxChgCurr;                         //最大充电电流
    int16_t  s16MaxDischgCurr;                      //最大放电电流

    union
    {
        uint8_t u8Status;
        struct
        {
            uint8_t bReserved0             : 1;     //BIT0 预留
            uint8_t bReserved1             : 1;     //BIT1 预留
            uint8_t bReserved2             : 1;     //BIT2 预留
            uint8_t bReserved3             : 1;     //BIT3 预留
            uint8_t bFullChgReq            : 1;     //BIT4 满充请求
            uint8_t bChgImmediately        : 1;     //BIT5 强充，立即充电
            uint8_t bDisChgEn              : 1;     //BIT6 放电使能
            uint8_t bChgEn                 : 1;     //BIT7 充电使能
        }Bits;
    }ChgDischgStatus_t;                             //充放电状态
} BmsDataPylonMutualInfo_t;

/*BMS_PYLON协议数据结构*/
typedef struct
{
    BmsDataPylonBasicInfo_t  tBmsPylonBasicInfo;    //系统基本信息
    BmsDataPylonAnalogInfo_t tBmsPylonAnalogInfo;   //运行模拟量信息
    BmsDataPylonAlarmInfo_t  tBmsPylonAlarmInfo;    //状态告警量信息
    BmsDataPylonMutualInfo_t tBmsPylonMutualInfo;   //充放电管理交互信息
}BmsDataPylon_t;
extern BmsDataPylon_t tBmsDataPylon;

/*BMS_PYLON协议数据长度*/
#define BMS_PYLON_60H_VERSION_INFO_LENGTH           (sizeof(tBmsDataPylon.tBmsPylonBasicInfo) / 2)
#define BMS_PYLON_61H_PRIMARY_INFO_LENGTH           (sizeof(tBmsDataPylon.tBmsPylonAnalogInfo) / 2)
#define BMS_PYLON_62H_VOLTAGE_INFO_LENGTH           (sizeof(tBmsDataPylon.tBmsPylonAlarmInfo) / 2)
#define BMS_PYLON_63H_TEMP_INFO_LENGTH              (sizeof(tBmsDataPylon.tBmsPylonMutualInfo) / 2)

/******************************************************************
 Modbus BMS_Growatt协议数据结构
*******************************************************************/
/******************************************************************
 Spec Query
*******************************************************************/
typedef struct
{
    union
    {
        uint16_t u16Version;
        struct
        {
            uint8_t bMCUVersion           : 8;     //BIT0~BIT7
            uint8_t bMCUSubVersion        : 8;     //BIT8~BIT15
        }Bits;
    }McuFwVersion_t;                                //0x0001 MCU Software version

    union
    {
        uint16_t u16Version;
        struct
        {
            uint8_t bGaugeVersion         : 8;     //BIT0~BIT7
            uint8_t bGaugeSubVersion      : 8;     //BIT8~BIT15
        }Bits;
    }GaugeVersion_t;                                //0x0002 Gauge Version

    union
    {
        uint32_t u32Version;
        struct
        {
            uint16_t bGaugeFRVersionLo   : 16;    //0x0003 Gauge FR Version低字节
            uint16_t bGaugeFRVersionHi   : 16;    //0x0004 Gauge FR Version高字节
        }Bits;
    }GaugeFRVersion_t;

/*此处协议中定义不明确，待测试确认后修改*/
    union
    {
        uint64_t u64Time;
        struct
        {
            uint8_t bSecond               : 6;     //BIT0~BIT5
            uint8_t bMinute               : 6;     //BIT6~BIT11
            uint8_t bHour                 : 5;     //BIT12~BIT16
            uint8_t bDay                  : 5;     //BIT17~BIT21
            uint8_t bMonth                : 4;     //BIT22~BIT25
            uint8_t bYear                 : 6;     //BIT26~BIT31
            uint8_t bReserved1             : 8;     //BIT32~BIT39
            uint8_t bReserved2             : 8;     //BIT40~BIT47
            uint8_t bReserved3             : 8;     //BIT48~BIT55
            uint8_t bReserved4             : 8;     //BIT56~BIT63
        }Bits;
    }DateTime_t;                                    //0x0005~0x0008 Date&Time

    uint16_t u16BarCode12;                          //0x0009 BarCode1-2Bytes
    uint16_t u16BarCode34;                          //0x000A BarCode3-4Bytes
    uint16_t u16BarCode56;                          //0x000B BarCode5~6bytes
    uint16_t u16BarCode78;                          //0x000C BarCode7~8bytes

    union
    {
        uint32_t u32CompanyCode;
        struct
        {
            uint8_t bBMSCompany          : 8;     //0x000D Bit0~Bit7
            uint8_t bBMSVersion          : 8;     //0x000D Bit8~Bit15
            uint8_t bPACKCompany         : 8;     //0x000E Bit0~Bit7
            uint8_t bPACKVersion         : 8;     //0x000E Bit8~Bit15
        }Bits;
    }CompanyCode_t;

    uint16_t u16UsingGap;                          //0x000F Using Gap
}BmsDataGrowattSpecQuery_t;

/******************************************************************
 Status Query
*******************************************************************/
typedef struct
{
    uint16_t u16GaugeICcurrent;                     //0x0010 Gauge IC current

    union
    {
        uint32_t u32Time;
        struct
        {
            uint8_t bSecond               : 6;     //BIT0~BIT5
            uint8_t bMinute               : 6;     //BIT6~BIT11
            uint8_t bHour                 : 5;     //BIT12~BIT16
            uint8_t bDay                  : 5;     //BIT17~BIT21
            uint8_t bMonth                : 4;     //BIT22~BIT25
            uint8_t bYear                 : 6;     //BIT26~BIT31
        }Bits;
    }DateTime_t;                                    //0x0011~0x0012 Date&Time

    union
    {
        uint16_t u16State;
        struct
        {
            uint8_t bMode                 : 2;     //BIT0~BIT1
            uint8_t bErrorFlag            : 1;     //BIT2
            uint8_t bCellBalanceFlag      : 1;     //BIT3
            uint8_t bSleepFlag            : 1;     //BIT4
            uint8_t bDischgFlag           : 1;     //BIT5
            uint8_t bChgFlag              : 1;     //BIT6
            uint8_t bBatTerminalFlag      : 1;     //BIT7
            uint8_t bMasterOperationMode  : 2;     //BIT8~BIT9
            uint8_t bSPStatus             : 2;     //BIT10~BIT11
            uint8_t bRequestForceChg      : 1;     //BIT12
            uint8_t bReserved13           : 1;     //BIT13
            uint8_t bReserved14           : 1;     //BIT14
            uint8_t bReserved15           : 1;     //BIT15
        }Bits;
    }Status_t;                                      //0x0013 Status

    union
    {
        uint16_t u16Word;
        struct
        {
            uint8_t bOCD                  : 1;     //BIT0  Over Current Discharge
            uint8_t bSCD                  : 1;     //BIT1  Short Circuit Discharge
            uint8_t bOVP                  : 1;     //BIT2  Over Voltage protection
            uint8_t bUVP                  : 1;     //BIT3  Under Volt Protect
            uint8_t bOTD                  : 1;     //BIT4  Over Temperature Discharge
            uint8_t bOTC                  : 1;     //BIT5  Over Temperature Charge
            uint8_t bUTD                  : 1;     //BIT6  Under Temperature Discharge
            uint8_t bUTC                  : 1;     //BIT7  Under Temperature Charge
            uint8_t bSoftStartFail        : 1;     //BIT8  Soft start fail
            uint8_t bPermanentFault       : 1;     //BIT9  Permanent Fault
            uint8_t bDeltaVFail           : 1;     //BIT10 Delta V Fail
            uint8_t bOCC                  : 1;     //BIT11 Over Current Charge
            uint8_t bMosfetOTP            : 1;     //BIT12 MOS Over Temperature
            uint8_t bEnvironmentOTP       : 1;     //BIT13 Environment Over Temperature
            uint8_t bEnvironmentUTP       : 1;     //BIT14 Environment Under Temperature
            uint8_t bReserved15           : 1;     //BIT15
        }Bits;
    }Error_t;                                       //0x0014 Error

    uint16_t u16SOC;                                //0x0015 SOC
    uint16_t u16Voltage;                            //0x0016 电压
    int16_t  s16Current;                            //0x0017 电流
    int16_t  s16Temperature;                        //0x0018 温度
    uint16_t u16MaxChargeCurrent;                   //0x0019 最大充电电流
    uint16_t u16GaugeRM;                            //0x001A 剩余容量
    uint16_t u16GaugeFCC;                           //0x001B 额定容量
    union
    {
        uint16_t u16Version;
        struct
        {
            uint8_t bHWVersion            : 8;     //BIT0~BIT7 硬件版本
            uint8_t bFWVersion            : 8;     //BIT8~BIT15 软件版本
        }Bits;
    }SnVersion_t;                                   //0x001C 版本

    uint16_t u16Delta;                              //0x001D 电池电压
    uint16_t u16CycleCount;                         //0x001E 周期计数值
    
    union
    {
        uint16_t u16Version;
        struct
        {
            uint8_t bBoxStatus            : 1;     //BIT0 接BOX状态
            uint8_t bReserved7            : 7;     //BIT1~7
            uint8_t bBatteryID            : 6;     //BIT8~13
            uint8_t bReserved15           : 2;     //BIT14~15
        }Bits;
    }RSVDForMasterBox_t;                            //0x001F Box Number information

    uint16_t u16SOH;                                //0x0020 SOH
    uint16_t u16CVVoltage;                          //0x0021 CV电压
    
    union
    {
        uint16_t u16Word;
        struct
        {
            uint8_t bOVSingle             : 1;     //BIT0 单体过压告警
            uint8_t bUVSingle             : 1;     //BIT1 单体欠压告警
            uint8_t bOVP                  : 1;     //BIT2 总压过压告警
            uint8_t bUVP                  : 1;     //BIT3 总压欠压告警
            uint8_t bOCC                  : 1;     //BIT4 放电过流告警
            uint8_t bOCD                  : 1;     //BIT5 充电过流告警
            uint8_t bOTD                  : 1;     //BIT6 放电高温告警
            uint8_t bUTD                  : 1;     //BIT7 放电低温告警
            uint8_t bOTC                  : 1;     //BIT8 充电高温告警
            uint8_t bUTC                  : 1;     //BIT9 充电低温告警
            uint8_t bMosfetOT             : 1;     //BIT10 MOS过温告警
            uint8_t bEnvironmentOT        : 1;     //BIT11 环境过温告警
            uint8_t bEnvironmentUT        : 1;     //BIT12 环境低温告警
            uint8_t bUVShutdown           : 1;     //BIT13 低压关机告警
            uint8_t bBatteryType          : 2;     //BIT14~15 电池类型
        }Bits;
    }Warning_t;                                     //0x0022

    uint16_t u16MaxDischargeCurr;                   //0x0023

    union
    {
        uint16_t u16Word;
        struct
        {
            uint8_t bParaDIPDiff          : 1;     //BIT0 并联模组拨码开关不一致
            uint8_t bFWVersionDiff        : 1;     //BIT1 模组软件版本不一致
            uint8_t bNoSN                 : 1;     //BIT2 没有SN号
            uint8_t bMasterMiss           : 1;     //BIT3 LMU 通信中断（主机丢失)
            uint8_t bSlaverMiss           : 1;     //BIT4 LMU 通信中断（从机丢失）
            uint16_t bReserved15          : 11;    //BIT5~15 预留
        }Bits;
    }ExtendError_t;                                 //0x0024

    uint16_t u16MaxCellVolt;                        //0x0025
    uint16_t u16MinCellVolt;                        //0x0026
    uint16_t u16MaxCellVoltNum;                     //0x0027
    uint16_t u16MinCellVoltNum;                     //0x0028
    uint16_t u16CellSeries;                         //0x0029 Cell series of single module
}BmsDataGrowattStatusQuery_t;

typedef struct
{
    uint16_t u16BatteryPackID;                      //0x0070 识别同一个BMS下的不同电池组的信息
}BatteryPackID_t;

/******************************************************************
 电池电池单体电压信息
*******************************************************************/
typedef struct
{
    uint16_t u16CellVoltage1;                       //0x0071 电池电压1
    uint16_t u16CellVoltage2;                       //0x0072 电池电压2
    uint16_t u16CellVoltage3;                       //0x0073 电池电压3
    uint16_t u16CellVoltage4;                       //0x0074 电池电压4
    uint16_t u16CellVoltage5;                       //0x0075 电池电压5
    uint16_t u16CellVoltage6;                       //0x0076 电池电压6
    uint16_t u16CellVoltage7;                       //0x0077 电池电压7
    uint16_t u16CellVoltage8;                       //0x0078 电池电压8
    uint16_t u16CellVoltage9;                       //0x0079 电池电压9
    uint16_t u16CellVoltage10;                      //0x007A 电池电压10
    uint16_t u16CellVoltage11;                      //0x007B 电池电压11
    uint16_t u16CellVoltage12;                      //0x007C 电池电压12
    uint16_t u16CellVoltage13;                      //0x007D 电池电压13
    uint16_t u16CellVoltage14;                      //0x007E 电池电压14
    uint16_t u16CellVoltage15;                      //0x007F 电池电压15
    uint16_t u16CellVoltage16;                      //0x0080 电池电压16
}CellVoltageStatus_t;

/******************************************************************
 并联时第二组电池电池单体电压信息
*******************************************************************/
typedef struct
{
    uint16_t u16SecCellVoltage1;                    //0x0081 电池电压1
    uint16_t u16SecCellVoltage2;                    //0x0082 电池电压2
    uint16_t u16SecCellVoltage3;                    //0x0083 电池电压3
    uint16_t u16SecCellVoltage4;                    //0x0084 电池电压4
    uint16_t u16SecCellVoltage5;                    //0x0085 电池电压5
    uint16_t u16SecCellVoltage6;                    //0x0086 电池电压6
    uint16_t u16SecCellVoltage7;                    //0x0087 电池电压7
    uint16_t u16SecCellVoltage8;                    //0x0088 电池电压8
    uint16_t u16SecCellVoltage9;                    //0x0089 电池电压9
    uint16_t u16SecCellVoltage10;                   //0x008A 电池电压10
    uint16_t u16SecCellVoltage11;                   //0x008B 电池电压11
    uint16_t u16SecCellVoltage12;                   //0x008C 电池电压12
    uint16_t u16SecCellVoltage13;                   //0x008D 电池电压13
    uint16_t u16SecCellVoltage14;                   //0x008E 电池电压14
    uint16_t u16SecCellVoltage15;                   //0x008F 电池电压15
    uint16_t u16SecCellVoltage16;                   //0x0090 电池电压16
}CellVoltageStatus2_t;

/*BMS_Growatt协议数据结构*/
typedef struct
{
    BmsDataGrowattSpecQuery_t   tBmsGrowattSpecQuery;          //规格查询 0x0001-0x000F
    BmsDataGrowattStatusQuery_t tBmsGrowattStatusQuery;        //状态查询 0x0010-0x0030
    BmsDataGrowattSpecQuery_t   tBmsGrowattSpecQuery2;         //并联第2组电池规格查询 0x0031-0x003F
    BmsDataGrowattStatusQuery_t tBmsGrowattStatusQuery2;       //并联第2组电池状态查询 0x0040
    BatteryPackID_t             tBmsGrowattBatteryPackID;      //不同电池组的信息 0x0070
    CellVoltageStatus_t         tBmsGrowattCellVoltageStatus;  //单体电压信息 0x0071~0x0080
    CellVoltageStatus2_t        tBmsGrowattCellVoltageStatus2; //第2组单体电压信息 0x0081~0x0090
}BMSDataGrowatt_t;
extern BMSDataGrowatt_t tBmsDataGrowatt;

/*功能：BMS_Growatt协议地址识别表*/
typedef enum
{
    BMS_Growatt_03H_SPEC_QUERY_START       =  0x0001,
    BMS_Growatt_03H_SPEC_QUERY_END         =  0x000F,
    BMS_Growatt_03H_STATUS_QUERY_START     =  0x0010,
    BMS_Growatt_03H_STATUS_QUERY_END       =  0x0029,
    BMS_Growatt_03H_SPEC_QUERY2_START      =  0x0031,
    BMS_Growatt_03H_SPEC_QUERY2_END        =  0x003F,
    BMS_Growatt_03H_STATUS_QUERY2_START    =  0x0040,
    BMS_Growatt_03H_STATUS_QUERY2_END      =  0x0052,
    BMS_Growatt_03H_BATTERY_PACK_ID_START  =  0x0070,
    BMS_Growatt_03H_CELL_VOL_STATUS_START  =  0x0071,
    BMS_Growatt_03H_CELL_VOL_STATUS_END    =  0x0080,
    BMS_Growatt_03H_CELL_VOL_STATUS2_START =  0x0081,
    BMS_Growatt_03H_CELL_VOL_STATUS2_END   =  0x0090,
}BMS_DATA_GROWATT_ADDRESS;

/*BMS_Growatt协议数据长度*/
#define BMS_Growatt_03H_SPEC_QUERY_LENGTH             (sizeof(tBmsDataGrowatt.tBmsGrowattSpecQuery) / 2)
#define BMS_Growatt_03H_STATUS_QUERY_LENGTH           (sizeof(tBmsDataGrowatt.tBmsGrowattStatusQuery) / 2)
#define BMS_Growatt_03H_SPEC_QUERY2_LENGTH            (sizeof(tBmsDataGrowatt.tBmsGrowattSpecQuery2) / 2)
#define BMS_Growatt_03H_STATUS_QUERY2_LENGTH          (sizeof(tBmsDataGrowatt.tBmsGrowattStatusQuery2) / 2)
#define BMS_Growatt_03H_BATTERY_PACK_ID_LENGTH        (sizeof(tBmsDataGrowatt.tBmsGrowattBatteryPackID) / 2)
#define BMS_Growatt_03H_CELL_VOL_STATUS_LENGTH        (sizeof(tBmsDataGrowatt.tBmsGrowattCellVoltageStatus) / 2)
#define BMS_Growatt_03H_CELL_VOL_STATUS2_LENGTH       (sizeof(tBmsDataGrowatt.tBmsGrowattCellVoltageStatus2) / 2)

/******************************************************************
 Modbus BMS_Iron协议数据结构
*******************************************************************/
typedef struct
{
    uint16_t u16CommandGroup;                       //获取模拟量量化后数据
    uint16_t u16SysSOC;                             //电池组容量 (SOC)
    uint16_t u16SysVoltage;                         //电池组总电压
    uint16_t u16BatNum;                             //电池数量
    uint16_t u16VoltPcs1;                           //电池单体电压 1
    uint16_t u16VoltPcs2;
    uint16_t u16VoltPcs3;
    uint16_t u16VoltPcs4;
    uint16_t u16VoltPcs5;
    uint16_t u16VoltPcs6;
    uint16_t u16VoltPcs7;
    uint16_t u16VoltPcs8;
    uint16_t u16VoltPcs9;
    uint16_t u16VoltPcs10;
    uint16_t u16VoltPcs11;
    uint16_t u16VoltPcs12;
    uint16_t u16VoltPcs13;
    uint16_t u16VoltPcs14;
    uint16_t u16VoltPcs15;
    uint16_t u16VoltPcs16;
    int16_t  s16AmbientTemp;                        //环境温度
    int16_t  s16BatPackTemp;                        //电池组温度
    int16_t  s16PCBATemp;                           //PCBA 板温度
    int16_t  s16BatTempNum;                         //电池温度数量
    int16_t  s16BatTemp1;                           //电池温度 n
    int16_t  s16BatTemp2;
    int16_t  s16BatTemp3;
    int16_t  s16BatTemp4;
    int16_t  s16BatTemp5;
    int16_t  s16BatTemp6;
    int16_t  s16BatTemp7;
    int16_t  s16BatTemp8;
    int16_t  s16BatTemp9;
    int16_t  s16BatTemp10;
    int16_t  s16BatTemp11;
    int16_t  s16BatTemp12;
    int16_t  s16BatTemp13;
    int16_t  s16BatTemp14;
    int16_t  s16BatTemp15;
    int16_t  s16BatTemp16;
    int16_t  s16SysCurrent;                         //电池组充、放电电流
    uint16_t u16InternalRegistor;                   //电池组内阻
    uint16_t u16SysSOH;                             //电池组健康状态 SOH
    uint16_t u16UserIqrNum;                         //用户自定义遥测内容数量 p
    uint16_t u16UserByteNum;                        //用户自定义字节
    uint16_t u16FullCapacity;                       //满充容量
    uint16_t u16RemainingCapacity;                  //剩余容量
    uint16_t u16SysCycleCnt;                        //循环次数
    union
    {
        uint16_t u16Status;
        struct
        {
            uint8_t bSingleOVPrt          : 1;     //BIT0 单节过压保护
            uint8_t bSingleUVPrt          : 1;     //BIT1 单节欠压保护
            uint8_t bTotalOVPrt           : 1;     //BIT2 总电压过压保护
            uint8_t bTotalUVPrt           : 1;     //BIT3 总电压欠压保护
            uint8_t bSingleOVAlarm        : 1;     //BIT4 单节高压报警
            uint8_t bSingleUVAlarm        : 1;     //BIT5 单节低压报警
            uint8_t bTotalOVAlarm         : 1;     //BIT6 总电压高压报警
            uint8_t bTotalUVAlarm         : 1;     //BIT7 总电压低压报警
            uint8_t bVoltDiffAlarm        : 1;     //BIT8 压差报警
            uint8_t bOVPCnt10             : 1;     //BIT9 连续过压保护 10 次，不再解除
            uint8_t bUVPCnt10             : 1;     //BIT10 连续欠压保护 10 次，不再解除
            uint8_t bTempDiffAlarm        : 1;     //BIT11 温差报警
            uint8_t bCellFail             : 1;     //BIT12 电芯失效
            uint8_t bFuseBurned           : 1;     //BIT13 熔断丝烧毁
            uint8_t bVoltDiffPrt          : 1;     //BIT14 压差保护
            uint8_t bStandby              : 1;     //BIT15 系统进入休眠状态
        }Bits;
    }VoltStatus_t;                                  //电压状态

    union
    {
        uint16_t u16Status;
        struct
        {
            uint8_t u8Charge               : 1;     //BIT0 充电
            uint8_t u8DisCharge            : 1;     //BIT1 放电
            uint8_t u8ChgOCPrt             : 1;     //BIT2 充电过流保护
            uint8_t u8ShortPrt             : 1;     //BIT3 短路保护
            uint8_t u8DisChgOCPrt1         : 1;     //BIT4 放电过流 1 保护
            uint8_t u8DisChgOCPrt2         : 1;     //BIT5 放电过流 2 保护
            uint8_t u8ChgOCAlarm           : 1;     //BIT6 充电电流报警
            uint8_t u8DisChgOCAlarm        : 1;     //BIT7 放电电流报警
            uint8_t u8OCPCnt10             : 1;     //BIT8 连续过流 10 次不再自动解除
            uint8_t u8ReverseConnect       : 1;     //BIT9 反接保护
            uint8_t u8CurrRatio            : 1;     //BIT10 电流值倍率
            uint8_t u8CurrLimit            : 1;     //BIT11 启动限流
            uint8_t u8CellFail             : 3;     //BIT12~14 电池状态
            uint8_t u8Reserved15           : 1;     //BIT15 预留
        }Bits;
    }CurrStatus_t;                                  //电流状态

    union
    {
        uint16_t u16Status;
        struct
        {
            uint8_t bChgOTPrt             : 1;     //BIT0 充电高温 (电芯) 保护
            uint8_t bChgUTPrt             : 1;     //BIT1 充电低温 (电芯) 保护
            uint8_t bDisChgOTPrt          : 1;     //BIT2 放电高温 (电芯) 保护
            uint8_t bDisChgUTPrt          : 1;     //BIT3 放电低温 (电芯) 保护
            uint8_t bAmbientOTPrt         : 1;     //BIT4 环境高温保护
            uint8_t bAmbientUTPrt         : 1;     //BIT5 环境低温保护
            uint8_t bPowerOTPrt           : 1;     //BIT6 功率高温保护
            uint8_t bPowerUTPrt           : 1;     //BIT7 功率低温保护
            uint8_t bChgOTAlarm           : 1;     //BIT8 充电高温 (电芯) 报警
            uint8_t bChgUTAlarm           : 1;     //BIT9 充电低温 (电芯) 报警
            uint8_t bDisChgOTAlarm        : 1;     //BIT10 放电高温 (电芯) 报警
            uint8_t bDisChgUTAlarm        : 1;     //BIT11 放电低温 (电芯) 报警
            uint8_t bAmbientOTAlarm       : 1;     //BIT12 环境高温报警
            uint8_t bAmbientUTAlarm       : 1;     //BIT13 环境低温报警
            uint8_t bPowerOTAlarm         : 1;     //BIT14 功率高温报警
            uint8_t bPowerUTAlarm         : 1;     //BIT15 压差保护
        }Bits;
    }TempStatus_t;                                  //温度状态

    union
    {
        uint16_t u16Warning;
        struct
        {
            uint8_t bVoltDiff             : 1;     //BIT0 压差报警
            uint8_t bChgMosfetDamage      : 1;     //BIT1 充电 FET 损坏报警
            uint8_t bSDFail               : 1;     //BIT2 外部 SD 卡失效报警
            uint8_t bSPIFail              : 1;     //BIT3 SPI 通信失效报警
            uint8_t bEepromFail           : 1;     //BIT4 EEPROM 失效报警
            uint8_t bLedAlarm             : 1;     //BIT5 LED 报警
            uint8_t bBuzzerAlarm          : 1;     //BIT6 Buzzer 报警
            uint8_t bLowPower             : 1;     //BIT7 低电量报警
            uint8_t bMosfetOTP            : 1;     //BIT8 MOS 高温保护
            uint8_t bHeatingFilmFail      : 1;     //BIT9 加热膜故障
            uint8_t bCurrLimitBoardFail   : 1;     //BIT10 限流板故障
            uint8_t bADCFail              : 1;     //BIT11 采样故障
            uint8_t bCellFault            : 1;     //BIT12 电芯故障
            uint8_t bNTCFault             : 1;     //BIT13 NTC 故障
            uint8_t bMosfetChgFault       : 1;     //BIT14 充电 MOS 故障
            uint8_t bMosfetDisChgFault    : 1;     //BIT15 放电 MOS 故障
        }Bits;
    }AlarmStatus_t;                                 //报警状态

    union
    {
        uint16_t u16Status;
        struct
        {
            uint8_t bChgFetSwitch         : 1;     //BIT0 充电管开关状态
            uint8_t bDisChgFetSwitch      : 1;     //BIT1 放电管状态
            uint8_t bDisChgFetDamage      : 1;     //BIT2 放电管损坏
            uint8_t bChgFetDamage         : 1;     //BIT3  充电管损坏
            uint8_t bCurrLimitMode        : 1;     //BIT4~5 限流模式
            uint8_t bHeatingFilmState     : 1;     //BIT6 加热膜开关状态
            uint8_t bMosfetCVState        : 1;     //BIT7 恒流 MOS 状态
            uint8_t bState4G              : 1;     //BIT8 4G开关状态
            uint8_t bChgSignal            : 1;     //BIT9 充电信号
            uint8_t bPackPower            : 1;     //BIT10 Pack 供电
            uint8_t bLedAlarm             : 1;     //BIT11 LED 报警状态
            uint8_t bBuzzerAlarm          : 1;     //BIT12 蜂鸣器状态
            uint8_t bAFEChipFault         : 1;     //BIT13 AFE 芯片故障
            uint8_t bAFEAlarmPinFault     : 1;     //BIT14 AFE 报警引脚故障
            uint8_t bLowPower             : 1;     //BIT15 低电量保护
        }Bits;
    }MosfetStatus_t;                                //MOSFET 状态

    union
    {
        uint16_t u16Status;
        struct
        {
            uint8_t bCell1                : 1;     //BIT0
            uint8_t bCell2                : 1;     //BIT1
            uint8_t bCell3                : 1;     //BIT2
            uint8_t bCell4                : 1;     //BIT3
            uint8_t bCell5                : 1;     //BIT4
            uint8_t bCell6                : 1;     //BIT5
            uint8_t bCell7                : 1;     //BIT6
            uint8_t bCell8                : 1;     //BIT7
            uint8_t bCell9                : 1;     //BIT8
            uint8_t bCell10               : 1;     //BIT9
            uint8_t bCell11               : 1;     //BIT10
            uint8_t bCell12               : 1;     //BIT11
            uint8_t bCell13               : 1;     //BIT12
            uint8_t bCell14               : 1;     //BIT13
            uint8_t bCell15               : 1;     //BIT14
            uint8_t bCell16               : 1;     //BIT15
        }Bits;
    }OverVoltProtL_t;                               //过压保护状态1~16节电池

    union
    {
        uint16_t u16Status;
        struct
        {
            uint8_t bCell1                : 1;     //BIT0
            uint8_t bCell2                : 1;     //BIT1
            uint8_t bCell3                : 1;     //BIT2
            uint8_t bCell4                : 1;     //BIT3
            uint8_t bCell5                : 1;     //BIT4
            uint8_t bCell6                : 1;     //BIT5
            uint8_t bCell7                : 1;     //BIT6
            uint8_t bCell8                : 1;     //BIT7
            uint8_t bCell9                : 1;     //BIT8
            uint8_t bCell10               : 1;     //BIT9
            uint8_t bCell11               : 1;     //BIT10
            uint8_t bCell12               : 1;     //BIT11
            uint8_t bCell13               : 1;     //BIT12
            uint8_t bCell14               : 1;     //BIT13
            uint8_t bCell15               : 1;     //BIT14
            uint8_t bCell16               : 1;     //BIT15
        }Bits;
    }UnderVoltProtL_t;                              //欠压保护状态1~16节电池

    union
    {
        uint16_t u16Status;
        struct
        {
            uint8_t bCell1                : 1;     //BIT0
            uint8_t bCell2                : 1;     //BIT1
            uint8_t bCell3                : 1;     //BIT2
            uint8_t bCell4                : 1;     //BIT3
            uint8_t bCell5                : 1;     //BIT4
            uint8_t bCell6                : 1;     //BIT5
            uint8_t bCell7                : 1;     //BIT6
            uint8_t bCell8                : 1;     //BIT7
            uint8_t bCell9                : 1;     //BIT8
            uint8_t bCell10               : 1;     //BIT9
            uint8_t bCell11               : 1;     //BIT10
            uint8_t bCell12               : 1;     //BIT11
            uint8_t bCell13               : 1;     //BIT12
            uint8_t bCell14               : 1;     //BIT13
            uint8_t bCell15               : 1;     //BIT14
            uint8_t bCell16               : 1;     //BIT15
        }Bits;
    }HighVoltAlarmL_t;                              //高压报警状态1~16节电池

    union
    {
        uint16_t u16Status;
        struct
        {
            uint8_t bCell1                : 1;     //BIT0
            uint8_t bCell2                : 1;     //BIT1
            uint8_t bCell3                : 1;     //BIT2
            uint8_t bCell4                : 1;     //BIT3
            uint8_t bCell5                : 1;     //BIT4
            uint8_t bCell6                : 1;     //BIT5
            uint8_t bCell7                : 1;     //BIT6
            uint8_t bCell8                : 1;     //BIT7
            uint8_t bCell9                : 1;     //BIT8
            uint8_t bCell10               : 1;     //BIT9
            uint8_t bCell11               : 1;     //BIT10
            uint8_t bCell12               : 1;     //BIT11
            uint8_t bCell13               : 1;     //BIT12
            uint8_t bCell14               : 1;     //BIT13
            uint8_t bCell15               : 1;     //BIT14
            uint8_t bCell16               : 1;     //BIT15
        }Bits;
    }LowVoltAlarmL_t;                               //低压报警状态1~16节电池

    union
    {
        uint16_t u16Status;
        struct
        {
            uint8_t bCell1                : 1;     //BIT0
            uint8_t bCell2                : 1;     //BIT1
            uint8_t bCell3                : 1;     //BIT2
            uint8_t bCell4                : 1;     //BIT3
            uint8_t bCell5                : 1;     //BIT4
            uint8_t bCell6                : 1;     //BIT5
            uint8_t bCell7                : 1;     //BIT6
            uint8_t bCell8                : 1;     //BIT7
            uint8_t bCell9                : 1;     //BIT8
            uint8_t bCell10               : 1;     //BIT9
            uint8_t bCell11               : 1;     //BIT10
            uint8_t bCell12               : 1;     //BIT11
            uint8_t bCell13               : 1;     //BIT12
            uint8_t bCell14               : 1;     //BIT13
            uint8_t bCell15               : 1;     //BIT14
            uint8_t bCell16               : 1;     //BIT15
        }Bits;
    }BalenceStatusL_t;                               //均衡状态1~16节电池

    union
    {
        uint16_t u16Status;
        struct
        {
            uint8_t bCell17               : 1;     //BIT0
            uint8_t bCell18               : 1;     //BIT1
            uint8_t bCell19               : 1;     //BIT2
            uint8_t bCell20               : 1;     //BIT3
            uint8_t bCell21               : 1;     //BIT4
            uint8_t bCell22               : 1;     //BIT5
            uint8_t bCell23               : 1;     //BIT6
            uint8_t bCell24               : 1;     //BIT7
            uint8_t bCell25               : 1;     //BIT8
            uint8_t bCell26               : 1;     //BIT9
            uint8_t bCell27               : 1;     //BIT10
            uint8_t bCell28               : 1;     //BIT11
            uint8_t bCell29               : 1;     //BIT12
            uint8_t bCell30               : 1;     //BIT13
            uint8_t bCell31               : 1;     //BIT14
            uint8_t bCell32               : 1;     //BIT15
        }Bits;
    }BalenceStatusH_t;                               //均衡状态17~32节电池

    union
    {
        uint16_t u16Status;
        struct
        {
            uint8_t bCell17               : 1;     //BIT0
            uint8_t bCell18               : 1;     //BIT1
            uint8_t bCell19               : 1;     //BIT2
            uint8_t bCell20               : 1;     //BIT3
            uint8_t bCell21               : 1;     //BIT4
            uint8_t bCell22               : 1;     //BIT5
            uint8_t bCell23               : 1;     //BIT6
            uint8_t bCell24               : 1;     //BIT7
            uint8_t bCell25               : 1;     //BIT8
            uint8_t bCell26               : 1;     //BIT9
            uint8_t bCell27               : 1;     //BIT10
            uint8_t bCell28               : 1;     //BIT11
            uint8_t bCell29               : 1;     //BIT12
            uint8_t bCell30               : 1;     //BIT13
            uint8_t bCell31               : 1;     //BIT14
            uint8_t bCell32               : 1;     //BIT15
        }Bits;
    }OverVoltProtH_t;                               //过压保护状态17~32节电池

    union
    {
        uint16_t u16Status;
        struct
        {
            uint8_t bCell17               : 1;     //BIT0
            uint8_t bCell18               : 1;     //BIT1
            uint8_t bCell19               : 1;     //BIT2
            uint8_t bCell20               : 1;     //BIT3
            uint8_t bCell21               : 1;     //BIT4
            uint8_t bCell22               : 1;     //BIT5
            uint8_t bCell23               : 1;     //BIT6
            uint8_t bCell24               : 1;     //BIT7
            uint8_t bCell25               : 1;     //BIT8
            uint8_t bCell26               : 1;     //BIT9
            uint8_t bCell27               : 1;     //BIT10
            uint8_t bCell28               : 1;     //BIT11
            uint8_t bCell29               : 1;     //BIT12
            uint8_t bCell30               : 1;     //BIT13
            uint8_t bCell31               : 1;     //BIT14
            uint8_t bCell32               : 1;     //BIT15
        }Bits;
    }UnderVoltProtH_t;                              //欠压保护状态17~32节电池

    union
    {
        uint16_t u16Status;
        struct
        {
            uint8_t bCell17               : 1;     //BIT0
            uint8_t bCell18               : 1;     //BIT1
            uint8_t bCell19               : 1;     //BIT2
            uint8_t bCell20               : 1;     //BIT3
            uint8_t bCell21               : 1;     //BIT4
            uint8_t bCell22               : 1;     //BIT5
            uint8_t bCell23               : 1;     //BIT6
            uint8_t bCell24               : 1;     //BIT7
            uint8_t bCell25               : 1;     //BIT8
            uint8_t bCell26               : 1;     //BIT9
            uint8_t bCell27               : 1;     //BIT10
            uint8_t bCell28               : 1;     //BIT11
            uint8_t bCell29               : 1;     //BIT12
            uint8_t bCell30               : 1;     //BIT13
            uint8_t bCell31               : 1;     //BIT14
            uint8_t bCell32               : 1;     //BIT15
        }Bits;
    }HighVoltAlarmH_t;                              //高压报警状态17~32节电池

    union
    {
        uint16_t u16Status;
        struct
        {
            uint8_t bCell17               : 1;     //BIT0
            uint8_t bCell18               : 1;     //BIT1
            uint8_t bCell19               : 1;     //BIT2
            uint8_t bCell20               : 1;     //BIT3
            uint8_t bCell21               : 1;     //BIT4
            uint8_t bCell22               : 1;     //BIT5
            uint8_t bCell23               : 1;     //BIT6
            uint8_t bCell24               : 1;     //BIT7
            uint8_t bCell25               : 1;     //BIT8
            uint8_t bCell26               : 1;     //BIT9
            uint8_t bCell27               : 1;     //BIT10
            uint8_t bCell28               : 1;     //BIT11
            uint8_t bCell29               : 1;     //BIT12
            uint8_t bCell30               : 1;     //BIT13
            uint8_t bCell31               : 1;     //BIT14
            uint8_t bCell32               : 1;     //BIT15
        }Bits;
    }LowVoltAlarmH_t;                               //低压报警状态17~32节电池

    union
    {
        uint16_t u16Status;
        struct
        {
            uint8_t bInitial              : 1;     //BIT0 初始化
            uint8_t bSelfTest             : 1;     //BIT1 自检
            uint8_t bReady                : 1;     //BIT2 就绪
            uint8_t bDischarge            : 1;     //BIT3 放电
            uint8_t bCharge               : 1;     //BIT4 充电
            uint8_t bFault                : 1;     //BIT5 故障
            uint8_t bPowerDown            : 1;     //BIT6 下电
            uint8_t bToolingMode          : 1;     //BIT 工装模式
            uint8_t bReserved15           : 8;     //BIT8~15 预留
        }Bits;
    }State_t;                                       //状态机

    union
    {
        uint16_t u16Status;
        struct
        {
            uint8_t bCharger              : 1;     //BIT0 充电机在线
            uint8_t bACCSignal            : 1;     //BIT1 ACC 信号
            uint8_t bONSignal             : 1;     //BIT2 ON 信号
            uint8_t bAerosol              : 1;     //BIT3 气溶胶检测
            uint8_t bBatDisChgLock        : 1;     //BIT4 电池放电锁定
            uint8_t bAntiTheftLock        : 1;     //BIT5 防盗锁定
            uint8_t bBatChgLock           : 1;     //BIT6 电池充电锁定
            uint8_t bReserved7            : 1;     //BIT7 预留
            uint8_t bPrePutMosfet         : 1;     //BIT8 预放 MOS 导通状态
            uint8_t bReserved9            : 1;     //BIT9 预留
            uint8_t bReserved10           : 1;     //BIT10 预留
            uint8_t bReserved11           : 1;     //BIT11 预留
            uint8_t bXtalFault            : 1;     //BIT12 晶振故障
            uint8_t bEPPFault             : 1;     //BIT13 EEP 故障
            uint8_t bReserved14           : 1;     //BIT14 预留
            uint8_t bReserved15           : 1;     //BIT15 预留
        }Bits;
    }AddIOState_t;                                  //输入输出状态额外读取位
} IronTowerBMSData_t;
extern IronTowerBMSData_t tIronTowerBMSData;

/******************************************************************
 Modbus BMS_Voltronic协议数据结构
*******************************************************************/
typedef struct
{
    /******************************************************************
     版本信息
    *******************************************************************/
    uint16_t u16ProtocolType;                       //0x0001 协议类型
    uint16_t u16ProtocolVersion;                    //0x0002 协议版本
    uint32_t u32FirmwareVersion;                    //0x0003~0x0004 软件版本
    uint32_t u32HardwareVersion;                    //0x0005~0x0006 硬件版本

    /******************************************************************
     BMS一般状态参数查询（Cell N*20+1 voltage: 0x0N11）
    *******************************************************************/
    uint16_t u16NumOfCell;                          //0x0010 电池数量
    uint16_t u16SingleVolt1;                        //0x0011 单体电池n电压
    uint16_t u16SingleVolt2;                        //0x0012
    uint16_t u16SingleVolt3;                        //0x0013
    uint16_t u16SingleVolt4;                        //0x0014
    uint16_t u16SingleVolt5;                        //0x0015
    uint16_t u16SingleVolt6;                        //0x0016
    uint16_t u16SingleVolt7;                        //0x0017
    uint16_t u16SingleVolt8;                        //0x0018
    uint16_t u16SingleVolt9;                        //0x0019
    uint16_t u16SingleVolt10;                       //0x001A
    uint16_t u16SingleVolt11;                       //0x001B
    uint16_t u16SingleVolt12;                       //0x001C
    uint16_t u16SingleVolt13;                       //0x001D
    uint16_t u16SingleVolt14;                       //0x001E
    uint16_t u16SingleVolt15;                       //0x001F
    uint16_t u16SingleVolt16;                       //0x0020
    uint16_t u16SingleVolt17;                       //0x0021
    uint16_t u16SingleVolt18;                       //0x0022
    uint16_t u16SingleVolt19;                       //0x0023
    uint16_t u16SingleVolt20;                       //0x0024
    uint16_t u16NumofTempSensor;                    //0x0025 温度传感器数量
    int16_t  s16Temp1;                              //0x0026 温度传感器n温度
    int16_t  s16Temp2;                              //0x0027 温度传感器n温度
    int16_t  s16Temp3;                              //0x0028 温度传感器n温度
    int16_t  s16Temp4;                              //0x0029 温度传感器n温度
    int16_t  s16Temp5;                              //0x002A 温度传感器n温度
    int16_t  s16Temp6;                              //0x002B 温度传感器n温度
    int16_t  s16Temp7;                              //0x002C 温度传感器n温度
    int16_t  s16Temp8;                              //0x002D 温度传感器n温度
    int16_t  s16Temp9;                              //0x002E 温度传感器n温度
    int16_t  s16Temp10;                             //0x002F 温度传感器n温度
    int16_t  s16ChgCurr;                            //0x0030 充电电流
    int16_t  s16DisChgCurr;                         //0x0031 放电电流
    uint16_t u16ModuleVolt;                         //0x0032 模块电压
    uint16_t u16ModuleSOC;                          //0x0033 SOC
    uint16_t u16ModuleTotalCapcity;                 //0x0034 总容量

    /******************************************************************
     BMS告警信息 Cell N*20+1/ N*20+2 voltage state: 0x0N41 
            00H: normal
            01H: below lower limit 
            02H: above higher limit 
            F0H: other error
    *******************************************************************/
    uint16_t u16NumOfCellState;                     //0x0040 电池数量
    uint16_t u16CellVoltState1;                     //0x0041 电池n n+1电压状态
    uint16_t u16CellVoltState3;                     //0x0042
    uint16_t u16CellVoltState5;                     //0x0043
    uint16_t u16CellVoltState7;                     //0x0044
    uint16_t u16CellVoltState9;                     //0x0045
    uint16_t u16CellVoltState11;                    //0x0046
    uint16_t u16CellVoltState13;                    //0x0047
    uint16_t u16CellVoltState15;                    //0x0048
    uint16_t u16CellVoltState17;                    //0x0049
    uint16_t u16CellVoltState19;                    //0x004A
    
    uint16_t u16NumofTempSensorState;               //0x0050 温度传感器数量
    int16_t  s16TempState1;                         //0x0051 电池n n+1温度状态
    int16_t  s16TempState3;                         //0x0052
    int16_t  s16TempState5;                         //0x0053
    int16_t  s16TempState7;                         //0x0054
    int16_t  s16TempState9;                         //0x0055
    
    uint16_t u16ChgVoltState;                       //0x0060 充电电压
    uint16_t u16DisChgVoltState;                    //0x0061 放电电压
    uint16_t u16CellChgVoltState;                   //0x0062 单体电池充电电压
    uint16_t u16CellDisChgVoltState;                //0x0063 单体电池放电电压
    uint16_t u16ModuleChgCurrState;                 //0x0064 充电电流
    uint16_t u16ModuleDisChgCurrState;              //0x0065 放电电流
    int16_t  s16ModuleChgTempState;                 //0x0066 充电温度
    int16_t  s16ModuleDischgTempState;              //0x0067 放电温度
    int16_t  s16CellChgTempState;                   //0x0068 单体电池充电温度
    int16_t  s16CellDischgTempState;                //0x0069 单体电池放电温度

    /******************************************************************
     电池充放电信息查询
    *******************************************************************/
    uint16_t u16ChgVoltLimit;                       //0x0070 充电电压限幅
    uint16_t u16DischgVoltLimit;                    //0x0071 放电电压限幅
    uint16_t u16ChgCurrLimit;                       //0x0072 充电电流限幅
    uint16_t u16DischgCurrLimit;                    //0x0073 放电电流限幅
    
    union
    {
        uint16_t u16Status;
        struct
        {
            uint8_t bReserved0             : 1;     //BIT0 预留
            uint8_t bReserved1             : 1;     //BIT1 预留
            uint8_t bReserved2             : 1;     //BIT2 预留
            uint8_t bReserved3             : 1;     //BIT3 预留
            uint8_t bFullChgReq            : 1;     //BIT4 满充请求
            uint8_t bChgImmediately2       : 1;     //BIT5 强充，建议立即充电
            uint8_t bChgImmediately        : 1;     //BIT6 强充，立即充电
            uint8_t bDisChgEn              : 1;     //BIT7 放电使能
            uint8_t bChgEn                 : 1;     //BIT8 充电使能
            uint8_t bReserved4             : 7;     //BIT9~15 预留
        }Bits;
    }ChgDischgStatus_t;                             //充放电状态
} VoltronicBmsData_t;
extern VoltronicBmsData_t tVoltronicBmsData;

/*BMS数据不同协议的统一整合*/
extern void BmsErrorUnified(uint8_t ProtocolType);
extern void BmsWarningUnified(uint8_t ProtocolType);
extern void sBmsDataUnified(uint8_t ProtocolType);

/*BMS数据地址的索引*/
extern uint16_t* GetBmsComDataIndex_03H(MBRTUFrame_t* ptMBFrame);
extern uint16_t* GetBmsCvteComDataIndex_03H(MBRTUFrame_t* ptMBFrame);
extern uint16_t* GetBmsGrowattComDataIndex_03H(MBRTUFrame_t* ptMBFrame);

/*BMS数据地址范围的检测*/
extern MBErrorCode CheckBmsComDataRange_03H(MBRTUFrame_t* ptMBFrame);
extern MBErrorCode CheckBmsCvteComDataRange_03H(MBRTUFrame_t* ptMBFrame);
extern MBErrorCode CheckBmsGrowattComDataRange_03H(MBRTUFrame_t* ptMBFrame);

/*BMS数据对LCD显示屏的数据接口*/
extern void GetDisplayRealTimeBmsData(Display_DATA_BMS* ptDisplayBmsData);

/*BMS派能协议数据对外接口*/
extern void GetPylonBasicInfo(BmsDataPylonBasicInfo_t* pBmsDataPylonBasicInfo,uint16_t u16Length);
extern void GetPylonAnalogInfo(BmsDataPylonAnalogInfo_t* pBmsDataPylonAnalogInfo,uint16_t u16Length);
extern void GetPylonAlarmInfo(BmsDataPylonAlarmInfo_t* pBmsDataPylonAlarmInfo,uint16_t u16Length);
extern void GetPylonMutualInfo(BmsDataPylonMutualInfo_t* pBmsDataPylonMutualInfo,uint16_t u16Length);

/*BMS故障数据总对外接口*/
extern void GetDisplayBMSFault(Display_BMS_Fault_t* ptDisplayBmsFault);
extern void SetBmsProtocolType(BMS_Manu_TypeDef ptBmsProtocolType);  
extern void SetBmsComWayType(BMS_COMWAY_TypeDef ptBmsComWayType);
extern void GetBmsPylonAnalogInfo(BmsDataPylonAnalogInfo_t* tBmsPylonAnalogInfo);
extern void GetBmsPylonMutualInfo(BmsDataPylonMutualInfo_t* tBmsPylonMutualInfo);
extern void GetBmsPylonAlarmInfo(BmsDataPylonAlarmInfo_t* tBmsPylonAlarmInfo);
#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

