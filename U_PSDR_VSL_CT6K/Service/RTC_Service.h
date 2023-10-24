/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
文件 : RTC_Service.h
 用途 : RTC服务头文件
***********************************************************************************************************************/
#ifndef __RTC_Service_H__
#define __RTC_Service_H__

#include "main.h"
#include "TypeDef.h"
#include "HeadFile.h"

typedef enum
{
    RTC_INIT,          //时钟管理模块初始化
    RTC_RUNNING,       //时钟管理模块运行
    RTC_DESTRCUCTION,  //时钟管理模块析构
    RTC_STATE_NULL
} RTCStatus_TypeDef;

//时间结构体
typedef struct
{
    uint16_t  u16Year;
    uint8_t  u8Month;
    uint8_t  u8Day;
    uint8_t  u8Week;
    uint8_t  u8Hour;
    uint8_t  u8Min;
    uint8_t  u8Sec;
} TimeInf_t;


extern TimeInf_t SysRunTime;

#if RTC_TEST
    extern TimeInf_t SetTimeTest;
#endif

extern void RTC_Service_InitVar(void);
extern void RTC_Handler(void);
extern void Get_SysTime(TimeInf_t *tGetTime);
extern void Set_SysTime(TimeInf_t tSetTime);



#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
