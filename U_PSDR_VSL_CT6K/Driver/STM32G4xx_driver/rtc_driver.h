/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : rtc_driver.h 
 用途 : rtc驱动头文件
***********************************************************************************************************************/
#ifndef __RTC_DRIVER_H
#define __RTC_DRIVER_H

#include "main.h"
#include "TypeDef.h"
#include "MCU.h"
#include "HeadFile.h"

#if (RTCSIGNAL_SOURCE == MCU_RTC_MOUDLE)

//时间结构体
typedef struct
{
    uint8_t  u8Year;
    uint8_t  u8Month;
    uint8_t  u8Day;
    uint8_t  u8Week;
    uint8_t  u8Hour;
    uint8_t  u8Min;
    uint8_t  u8Sec;
} MCU_RTC_TimeInf_t;

extern void MCU_RTC_Get_Time(MCU_RTC_TimeInf_t *pGetTime);
extern void MCU_RTC_Set_Time(MCU_RTC_TimeInf_t stSetTime);
extern void MCU_RTC_InitVar(void);
extern void MCU_RTC_Init(void);

#endif
#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
