/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
文件 : RTC_Service.c
 用途 : RTC应用服务函数
***********************************************************************************************************************/
#ifndef _RTC_SERVICE_C_
#define _RTC_SERVICE_C_

#include "MCU.h"
#include "HeadFile.h"
#include "RTC_Service.h"

#if (RTCSIGNAL_SOURCE == MCU_RTC_MOUDLE)
    #include "rtc_driver.h"
#endif

#if (RTCSIGNAL_SOURCE == RTC_BL5372_MOUDLE)
    #include "BL5372_Device.h"
#endif

#if (RTCSIGNAL_SOURCE == RTC_PCF8563_MOUDLE)
    #include "PCF8563_Device.h"
#endif

#if RTC_SERVICE_MOUDLE

RTCStatus_TypeDef gEnumRTCStatus = RTC_STATE_NULL;
TimeInf_t SysRunTime;
//RTC读写时间操作测试全局变量
#if RTC_TEST
TimeInf_t SetTimeTest =                                                                                              //调试使用，后续数据绑定到通信部分或LCD部分，由用户设置
{
    .u16Year = 2023,
    .u8Month = 8,
    .u8Day = 1,
    .u8Week = 2,
    .u8Hour = 23,
    .u8Min = 58,
    .u8Sec = 58
};
#endif

static void RTCInit(void);
static void RTCRunning(void);
static void RTCDestruction(void);
static void Get_DeviceTime(void);
static void Set_DeviceTime(TimeInf_t tSetTime);

void Get_SysTime(TimeInf_t *tGetTime)
{
    memcpy(tGetTime, &SysRunTime, sizeof(TimeInf_t));
}

void Set_SysTime(TimeInf_t tSetTime)
{
    Set_DeviceTime(tSetTime);
}

void RTC_Handler(void)
{
    if (STATUS_FALSE == TimeTask_GetFlag_500ms)
    {
        return;
    }

    switch (gEnumRTCStatus)
    {
        case RTC_INIT://RTC模块初始化
        {
            RTCInit();
            gEnumRTCStatus = RTC_RUNNING;
        }
        break;

        case RTC_RUNNING://RTC模块运行
        {
            RTCRunning();
        }
        break;

        case RTC_DESTRCUCTION://RTC模块析构,用掉电检测村塾
        {
            RTCDestruction();
        }
        break;

        default:
            break;
    }
}

void RTC_Service_InitVar(void)
{
    memset(&SysRunTime, 0, sizeof(SysRunTime));
    gEnumRTCStatus = RTC_INIT;
}

/***************************************************************************
 功能:初始化驱动，全局变量等
****************************************************************************/
static void RTCInit(void)
{
#if (RTCSIGNAL_SOURCE == MCU_RTC_MOUDLE)
    MCU_RTC_Init();
#endif    
#if (RTCSIGNAL_SOURCE == RTC_BL5372_MOUDLE)
    BL5372_Device_Init();
#endif
#if (RTCSIGNAL_SOURCE == RTC_PCF8563_MOUDLE)
    PCF8563_Device_Init();
#endif   
}

/***************************************************************************
 功能:RTC总运行函数
****************************************************************************/
static void RTCRunning(void)
{
    Get_DeviceTime();
}

/***************************************************************************
 功能:RTC析构函数，用于掉电触发保护逻辑
****************************************************************************/
static void RTCDestruction(void)
{
    ;
}

static void Get_DeviceTime(void)
{
#if (RTCSIGNAL_SOURCE == MCU_RTC_MOUDLE)
    MCU_RTC_TimeInf_t Timebuff;
    memset(&Timebuff, 0, sizeof(Timebuff));

    MCU_RTC_Get_Time(&Timebuff);

    SysRunTime.u16Year = Timebuff.u8Year + 2000;
    memcpy(&SysRunTime.u8Month, &Timebuff.u8Month, 6);
#endif   
    
#if (RTCSIGNAL_SOURCE == RTC_BL5372_MOUDLE)
    BL5372_TimeInf_t Timebuff;
    memset(&Timebuff, 0, sizeof(Timebuff));

    BL5372_Device_Get_Time(&Timebuff);

    SysRunTime.u16Year = Timebuff.u8Year + 2000;
    memcpy(&SysRunTime.u8Month, &Timebuff.u8Month, 6);
#endif  
    
#if (RTCSIGNAL_SOURCE == RTC_PCF8563_MOUDLE)
    PCF8563_TimeInf_t Timebuff;
    memset(&Timebuff, 0, sizeof(PCF8563_TimeInf_t));

    PCF8563_Device_Get_Time(&Timebuff);
    SysRunTime.u16Year = Timebuff.u8YearH * 100 + Timebuff.u8YearL;
    memcpy(&SysRunTime.u8Month, &Timebuff.u8Month, 6);
#endif 
}

static void Set_DeviceTime(TimeInf_t tSetTime)
{
#if (RTCSIGNAL_SOURCE == MCU_RTC_MOUDLE)
    MCU_RTC_TimeInf_t Timebuff;
    memset(&Timebuff, 0, sizeof(Timebuff));
    
    Timebuff.u8Year = (uint8_t)(tSetTime.u16Year - 2000);
    memcpy(&Timebuff.u8Month, &tSetTime.u8Month, 6);
    MCU_RTC_Set_Time(Timebuff);
#endif
    
#if (RTCSIGNAL_SOURCE == RTC_BL5372_MOUDLE)
    BL5372_TimeInf_t Timebuff;
    memset(&Timebuff, 0, sizeof(Timebuff));
    
    Timebuff.u8Year = (uint8_t)(tSetTime.u16Year - 2000);
    memcpy(&Timebuff.u8Month, &tSetTime.u8Month, 6);
    BL5372_Device_Set_Time(Timebuff);
#endif
    
#if (RTCSIGNAL_SOURCE == RTC_PCF8563_MOUDLE)
    PCF8563_TimeInf_t Timebuff;
    memset(&Timebuff, 0, sizeof(Timebuff));

    Timebuff.u8YearH = (uint8_t)(tSetTime.u16Year / 100);
    Timebuff.u8YearL = (uint8_t)(tSetTime.u16Year % 100);
    memcpy(&Timebuff.u8Month, &tSetTime.u8Month, 6);
    PCF8563_Device_Set_Time(Timebuff);
#endif  
}

#endif
#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
