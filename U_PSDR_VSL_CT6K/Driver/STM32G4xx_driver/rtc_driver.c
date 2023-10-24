/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : rtc_driver.c 
 用途 : rtc驱动
***********************************************************************************************************************/
#include "rtc_driver.h"

#if (RTCSIGNAL_SOURCE == MCU_RTC_MOUDLE)

LL_RTC_InitTypeDef RTC_InitStruct = {0};
LL_RTC_TimeTypeDef RTC_TimeStruct = {0};
LL_RTC_DateTypeDef RTC_DateStruct = {0};
    
void MX_RTC_Init(void)
{
    if(LL_RCC_GetRTCClockSource() != LL_RCC_RTC_CLKSOURCE_LSE)
    {
        FlagStatus pwrclkchanged = RESET;

        /* Update LSE configuration in Backup Domain control register */
        /* Requires to enable write access to Backup Domain if necessary */
        if (LL_APB1_GRP1_IsEnabledClock (LL_APB1_GRP1_PERIPH_PWR) != 1U)
        {
            /* Enables the PWR Clock and Enables access to the backup domain */
            LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
            pwrclkchanged = SET;
        }

        if (LL_PWR_IsEnabledBkUpAccess () != 1U)
        {
            /* Enable write access to Backup domain */
            LL_PWR_EnableBkUpAccess();

            while (LL_PWR_IsEnabledBkUpAccess () == 0U)
            {
            }
        }

        LL_RCC_ForceBackupDomainReset();
        LL_RCC_ReleaseBackupDomainReset();
        LL_RCC_LSE_SetDriveCapability(LL_RCC_LSEDRIVE_LOW);
        LL_RCC_LSE_Enable();

        /* Wait till LSE is ready */
        while(LL_RCC_LSE_IsReady() != 1)
        {
        }

        LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSE);

        /* Restore clock configuration if changed */
        if (pwrclkchanged == SET)
        {
            LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_PWR);
        }
    }

    /* Peripheral clock enable */
    LL_RCC_EnableRTC();
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_RTC);

    /* RTC interrupt Init */
    NVIC_SetPriority(RTC_TAMP_IRQn, 0);
    NVIC_EnableIRQ(RTC_TAMP_IRQn);

    RTC_InitStruct.HourFormat = LL_RTC_HOURFORMAT_24HOUR;
    RTC_InitStruct.AsynchPrescaler = 127;
    RTC_InitStruct.SynchPrescaler = 255;
    LL_RTC_Init(RTC, &RTC_InitStruct);

    /** Enable the TimeStamp
    */
    LL_RTC_TS_Enable(RTC);
    LL_RTC_TS_SetActiveEdge(RTC, LL_RTC_TIMESTAMP_EDGE_RISING);
    LL_RTC_EnableIT_TS(RTC);

}  

void MCU_RTC_Read_Time(MCU_RTC_TimeInf_t *pTime)
{
    pTime->u8Year  =  RTC_DateStruct.Year;
    pTime->u8Month = RTC_DateStruct.Month;
    pTime->u8Day   = RTC_DateStruct.Day;
    pTime->u8Week  = RTC_DateStruct.WeekDay;
    pTime->u8Hour  = RTC_TimeStruct.Hours;
    pTime->u8Min   = RTC_TimeStruct.Minutes;
    pTime->u8Sec   = RTC_TimeStruct.Seconds;
}

void MCU_RTC_Write_Time(MCU_RTC_TimeInf_t stTime)
{
    RTC_DateStruct.Year    =  stTime.u8Year;
    RTC_DateStruct.Month   =  stTime.u8Month;
    RTC_DateStruct.Day     =  stTime.u8Day;
    RTC_DateStruct.WeekDay =  stTime.u8Week;
    LL_RTC_DATE_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_DateStruct);
    
    RTC_TimeStruct.Hours   = stTime.u8Hour;
    RTC_TimeStruct.Minutes = stTime.u8Min;
    RTC_TimeStruct.Seconds = stTime.u8Sec;
    LL_RTC_DATE_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_DateStruct);
}
/***********************************************************************************************************************
 功能：十进制转为BCD码
***********************************************************************************************************************/
uint8_t MCU_RTC_Byte_to_BCD(uint8_t u8Value)
{
    return  (u8Value + (u8Value / 10) * 6);
}

/***********************************************************************************************************************
 功能：BCD码转为十进制
***********************************************************************************************************************/
uint8_t MCU_RTC_BCD_to_Byte(uint8_t u8Value)
{
    return (u8Value - (u8Value >> 4) * 6);
}

int8_t checkCalendar(MCU_RTC_TimeInf_t stTime)
{
    int8_t timeErr = 0;

    if((stTime.u8Year >> 4) > 9 || (stTime.u8Year & 0x0F) > 9)
        timeErr = -1;

    else if((stTime.u8Month >> 4) > 1 || (stTime.u8Month & 0x0F) > 9)
        timeErr = -1;
    else if(stTime.u8Month > 0x12 || stTime.u8Month == 0)
        timeErr = -1;

    else if((stTime.u8Day >> 4) > 3 || (stTime.u8Day & 0x0F) > 9)
        timeErr = -1;
    else if(stTime.u8Day > 0x31 || stTime.u8Day == 0)
        timeErr = -1;

    else if((stTime.u8Hour >> 4) > 2 || (stTime.u8Hour & 0x0F) > 9)
        timeErr = -1;
    else if(stTime.u8Hour > 0x23)
        timeErr = -1;

    else if((stTime.u8Min >> 4) > 5 || (stTime.u8Min & 0x0F) > 9)
        timeErr = -1;
    else if(stTime.u8Min > 0x59)
        timeErr = -1;

    else if((stTime.u8Sec >> 4) > 5 || (stTime.u8Sec & 0x0F) > 9)
        timeErr = -1;
    else if(stTime.u8Sec > 0x59)
        timeErr = -1;

    return timeErr;
}

void MCU_RTC_Get_Time(MCU_RTC_TimeInf_t *pGetTime)
{
    MCU_RTC_TimeInf_t stGetData1;
    MCU_RTC_TimeInf_t stGetData2;
    memset(&stGetData1, 0, sizeof(MCU_RTC_TimeInf_t));
    memset(&stGetData2, 0, sizeof(MCU_RTC_TimeInf_t));

    MCU_RTC_Read_Time(&stGetData1);

    if(checkCalendar(stGetData1)  != 0)
    {
        return;
    }

    MCU_RTC_Read_Time(&stGetData2);

    if(checkCalendar(stGetData2)  != 0)
    {
        return;
    }

    if(memcmp(&stGetData1, &stGetData2, 7) == 0)
    {
        pGetTime->u8Year  = MCU_RTC_BCD_to_Byte(stGetData1.u8Year);
        pGetTime->u8Month = MCU_RTC_BCD_to_Byte(stGetData1.u8Month);
        pGetTime->u8Week  = MCU_RTC_BCD_to_Byte(stGetData1.u8Week);
        pGetTime->u8Day   = MCU_RTC_BCD_to_Byte(stGetData1.u8Day);
        pGetTime->u8Hour  = MCU_RTC_BCD_to_Byte(stGetData1.u8Hour);
        pGetTime->u8Min   = MCU_RTC_BCD_to_Byte(stGetData1.u8Min);
        pGetTime->u8Sec   = MCU_RTC_BCD_to_Byte(stGetData1.u8Sec);
    }
}
                                                                                                                                                    
void MCU_RTC_Set_Time(MCU_RTC_TimeInf_t stSetTime)
{
    MCU_RTC_TimeInf_t stTime;
    memset(&stTime, 0, sizeof(MCU_RTC_TimeInf_t));

    stTime.u8Year  = MCU_RTC_Byte_to_BCD(stSetTime.u8Year);
    stTime.u8Month = MCU_RTC_Byte_to_BCD(stSetTime.u8Month);
    stTime.u8Week  = MCU_RTC_Byte_to_BCD(stSetTime.u8Week);
    stTime.u8Day   = MCU_RTC_Byte_to_BCD(stSetTime.u8Day);
    stTime.u8Hour  = MCU_RTC_Byte_to_BCD(stSetTime.u8Hour);
    stTime.u8Min   = MCU_RTC_Byte_to_BCD(stSetTime.u8Min);
    stTime.u8Sec   = MCU_RTC_Byte_to_BCD(stSetTime.u8Sec);

    if(checkCalendar(stTime) != 0)
    {
        return;
    }

    MCU_RTC_Write_Time(stTime);
}

void MCU_RTC_Init(void)
{
    MX_RTC_Init();
}

void MCU_RTC_InitVar(void)
{
    ;
}
#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
