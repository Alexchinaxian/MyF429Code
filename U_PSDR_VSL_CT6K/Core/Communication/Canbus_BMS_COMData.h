/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Canbus_Bms_COMData.h 
 用途 : CanbusBms协议协议数据头文件
***********************************************************************************************************************/
#ifndef _CANBUS_BMS_COMDATA_H_
#define _CANBUS_BMS_COMDATA_H_

#include "HeadFile.h"
#include "MCU.h"
#include "LCD_Service.h"
#include "Fault_Management_Service.h"
#include "Modbus.h"

/******************************************************************
 BMSCAN_Plyon协议发送报文ID
*******************************************************************/
typedef enum
{
    UNIVERSAL               = 0X0305,               //通用
    TURN_OFF                = 0X4800,               //关机
    HEARTBEAT_SIGNAL        = 0X1001,               //心跳
    PROTOCOL_CHANGE1        = 0X0020,               //协议切换1
    PROTOCOL_CHANGE2        = 0X0060,               //协议切换2
} BMSCan_SendID_t;

/******************************************************************
 BMSCAN_Plyon协议接收报文ID
*******************************************************************/
typedef enum
{
    OPERATION_LIMIT         = 0X0351,               //限压限流
    SOC_AND_SOH             = 0X0355,               //SOC与SOH
    ANALOG_QUANTITY         = 0X0356,               //模拟量
    PROTECT_AND_ALARM       = 0X0359,               //保护与告警
    BMS_REQUEST             = 0X035C,               //BMS请求
    BRAND                   = 0X035E,               //品牌
    BMS_CUSTOMIZED          = 0X0350,               //BMS定制   
} BMSCan_ReceiveID_t;

/******************************************************************
 BMSCAN_Plyon协议发送报文数据
*******************************************************************/
typedef struct
{
    uint16_t u16ChgVoltLimit;                       //充电电压限值
    int16_t  s16ChgCurrLimit;                       //充电电流限幅
    int16_t  s16DischgCurrLimit;                    //放电电流限值
    uint16_t u16DischgVoltLimit;                    //放电电压限值
}OperationLimit_TypeDef;                            //限压限流帧

typedef struct
{
    uint16_t u16AvgSOC;                             //SOC均值
    uint16_t u16AvgSOH;                             //SOH均值  
}SOCandSOH_TypeDef;                                //SOC和SOH帧

typedef struct
{
    int16_t s16AvgVolt;                            //电压均值
    int16_t s16TotalCurrent;                       //电流和值 
    int16_t s16AvgTemp;                            //温度均值                       
}AnalogQuantity_TypeDef;                            //模拟量帧

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
            uint8_t bHV                    : 1;     //BIT1 电压高压
            uint8_t bLV                    : 1;     //BIT2 电压过压
            uint8_t bHT                    : 1;     //BIT3 高温
            uint8_t bLT                    : 1;     //BIT4 低温
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
    uint8_t  u8ModuleNumbers;                       //模块数量
}ProtectAndAlarm_TypeDef;                           //保护与告警帧

typedef union
{
    uint8_t u8Error;
    struct
    {
        uint8_t bReserved0             : 1;         //BIT0 预留
        uint8_t bReserved1             : 1;         //BIT1 预留
        uint8_t bReserved2             : 1;         //BIT2 预留
        uint8_t bFullCharge            : 1;         //BIT3 充满
        uint8_t bForceCharge           : 2;         //BIT4~5 强充
        uint8_t bDischargeEnable       : 1;         //BIT6 放电使能
        uint8_t bChargeEnable          : 1;         //BIT7 充电使能
    }Bits;                                          //保护1
}BMSRequest_TypeDef;                                //BMS请求帧帧
                                    //品牌帧
typedef struct
{
    union
    {
        uint8_t u8Error;
        struct
        {
            uint8_t bReserved0             : 1;     //BIT0 预留
            uint8_t bReserved1             : 1;     //BIT1 预留
            uint8_t bReserved2             : 1;     //BIT2 预留
            uint8_t bReserved3             : 1;     //BIT3 预留
            uint8_t bReserved4             : 1;     //BIT4 预留
            uint8_t bReserved5             : 1;     //BIT5 预留
            uint8_t bChargeMosFail         : 1;     //BIT6 充电mos失效
            uint8_t bDischargeMosFail      : 1;     //BIT7 放电mos失效
        }Bits;
    }MosFail_t;                                     //mos失效
    union
    {
        uint8_t u8Error;
        struct
        {
            uint8_t bReserved0             : 1;     //BIT0 预留
            uint8_t bReserved1             : 1;     //BIT1 预留
            uint8_t bReserved2             : 1;     //BIT2 预留
            uint8_t bReserved3             : 1;     //BIT3 预留
            uint8_t bReserved4             : 1;     //BIT4 预留
            uint8_t bReserved5             : 1;     //BIT5 预留
            uint8_t bImbalance             : 1;     //BIT6 SOC不均衡
            uint8_t bFloatChargeRequest    : 1;     //BIT7 浮充请求
        }Bits;
    }SOCImbalance_t;                                //soc不均衡   
}BMS_Customized_TypeDef;                            //BMS定制帧

/*BMS_PYLON协议数据结构*/
typedef struct
{
    OperationLimit_TypeDef    OperationLimit;     //限压限流
    SOCandSOH_TypeDef         SOCandSOH;          //SOC与SOH
    AnalogQuantity_TypeDef    AnalogQuantity;     //模拟量帧
    ProtectAndAlarm_TypeDef   ProtectAndAlarm;    //保护与告警帧
    BMSRequest_TypeDef        BMSRequest;         //BMS请求帧帧
    char                      Brand[5];           //品牌帧
    BMS_Customized_TypeDef    BMS_Customized;     //BMS定制帧
}BmsCanDataPylon_TypeDef;

extern BmsCanDataPylon_TypeDef     tBmsCanDataPylon;       //BMSCan协议Pylon数据结构
extern void BMSCan_SendPacket(void);
extern void BMSCan_ReceivePacket(void);
extern void GetDisplayRealTimePlyonBMSCanData(Display_DATA_BMS* ptDisplayBmsData);
extern void GetDisplayBMSCanFault(Display_BMSCan_Fault_t* ptDisplayBmsFault);
#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

