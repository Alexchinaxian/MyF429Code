/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Buzzer_Device.c 
 用途 : 蜂鸣器设备驱动
***********************************************************************************************************************/
#ifndef __BUZZER_DEVICE_C__
#define __BUZZER_DEVICE_C__

#include "Buzzer_Device.h"
#include "gpio_driver.h"
#include "tim_driver.h"

#if MODULE_BUZZER

/***********************************************************************************************************************
 功能：蜂鸣器驱动接口函数
***********************************************************************************************************************/
void Buzzer_Device_Cntrl(uint8_t u8BuzzerOn,uint8_t u8BuzzerOff,uint8_t u8BuzzerBlink,uint8_t u8BeepTimes,uint16_t u16Period)
{
    static  uint16_t wBeepCnt = 0;
    static  uint16_t wBeepTimer = 0;
    
    if(u8BuzzerOn)
    {
        DEV_BUZZER_ON();
    } 
    else if(u8BuzzerOff)
    {
        DEV_BUZZER_OFF();
    }
    else if(u8BuzzerBlink)
    {
        if( wBeepCnt < u8BeepTimes)
        {
            if((wBeepTimer & 0x01) == 0)
            {
                DEV_BUZZER_ON();
                wBeepCnt ++;
            }
            else
            {
                DEV_BUZZER_OFF();
            }
        }
        else
        {
            DEV_BUZZER_OFF();
        }
        if( (++wBeepTimer) >= u16Period) 
        {
            wBeepCnt = 0;
            wBeepTimer = 0;
        }
    }
}


/***********************************************************************************************************************
功能：发电机灯驱动接口函数
***********************************************************************************************************************/
void LED_Device_GenCntrl(uint8_t u8BuzzerOn,uint8_t u8BuzzerOff,uint8_t u8BuzzerBlink,uint8_t u8BeepTimes,uint16_t u16Period)
{
    static  uint16_t wBeepCnt = 0;
    
    if(u8BuzzerOn) 
    {
        DEV_LED_GEN_ON();
    } 
    else if(u8BuzzerOff)
    {
        DEV_LED_GEN_OFF();
    }
    else if(u8BuzzerBlink)
    {
        if( wBeepCnt < u8BeepTimes)
        {            
            DEV_LED_GEN_ON();
        }
        else
        {
            DEV_LED_GEN_OFF();
        }
        
        if( (++wBeepCnt) >= u16Period)
        {
            wBeepCnt = 0;
        }        
    }
}

/***********************************************************************************************************************
 功能：电网灯驱动接口函数
***********************************************************************************************************************/
void LED_Device_GridCntrl(uint8_t u8BuzzerOn,uint8_t u8BuzzerOff,uint8_t u8BuzzerBlink,uint8_t u8BeepTimes,uint16_t u16Period)
{
    static  uint16_t wBeepCnt = 0;
    
    if(u8BuzzerOn) 
    {
        DEV_LED_GRID_ON();
    } 
    else if(u8BuzzerOff)
    {
        DEV_LED_GRID_OFF();
    }
    else if(u8BuzzerBlink)
    {
        if( wBeepCnt < u8BeepTimes)
        {            
            DEV_LED_GRID_ON();
        }
        else
        {
            DEV_LED_GRID_OFF();
        }
        
        if( (++wBeepCnt) >= u16Period)
        {
            wBeepCnt = 0;
        }
    }
}

/***********************************************************************************************************************
 功能：故障LED灯驱动接口函数
***********************************************************************************************************************/
void LED_Device_FaultCntrl(uint8_t u8BuzzerOn,uint8_t u8BuzzerOff,uint8_t u8BuzzerBlink,uint8_t u8BeepTimes,uint16_t u16Period)
{
    static  uint16_t wBeepCnt = 0;
    
    if(u8BuzzerOn) 
    {
        DEV_LED_FAULT_ON();
    } 
    else if(u8BuzzerOff)
    {
        DEV_LED_FAULT_OFF();
    }
    else if(u8BuzzerBlink)
    {
        if( wBeepCnt < u8BeepTimes)
        {            
            DEV_LED_FAULT_ON();
        }
        else
        {
            DEV_LED_FAULT_OFF();
        }
        
        if( (++wBeepCnt) >= u16Period)
        {
            wBeepCnt = 0;
        }
    }
}

/***********************************************************************************************************************
 功能：干接点DRY_RLY1驱动接口函数
***********************************************************************************************************************/
void DRY_RLY1_DeviceCntrl(uint8_t u8DryRlyAction)
{
    if(u8DryRlyAction == STATUS_TRUE)
    {
        DEV_DRY_RLY1_ON();
    }
    else
    {
        DEV_DRY_RLY1_OFF();
    }
}

/***********************************************************************************************************************
 功能：干接点DRY_RLY2驱动接口函数
***********************************************************************************************************************/
void DRY_RLY2_DeviceCntrl(uint8_t u8DryRlyAction)
{
    if(u8DryRlyAction == STATUS_TRUE)
    {
        DEV_DRY_RLY2_ON();
    }
    else
    {
        DEV_DRY_RLY2_OFF();
    }
}
#endif
#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

