/***********************************************************************************************************************
* Copyright (c)  , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
* 文件名        : interrupt_driver.h
* 用途         : interrupt_driver
***********************************************************************************************************************/
#ifndef __INTERRUPT_DRIVER_H
#define __INTERRUPT_DRIVER_H

//#include "HAL_device.h"
#include "HeadFile.h"

#define INTERRUPT_DRIVER_MOUDLE (1)
#if INTERRUPT_DRIVER_MOUDLE

/***********************************************************************************************************************
* * Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
* * Enum definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
* * Typedef struct
***********************************************************************************************************************/
typedef union
{
    uint8_t Byte;
    struct
    {
        uint8_t CompDriver_UpCnt         : 1;    //Bit0  压缩机驱动上升下降   1为上升  0为下降
        uint8_t FocFanDriver_UpCnt       : 1;    //Bit1  风机驱动上升下降     1为上升  0为下降
        uint8_t AdcChgCmd                : 1;    //Bit2  通道切换
        uint8_t Bak3                     : 1;    //Bit3  预留位
        uint8_t Bak4                     : 1;    //Bit4  预留位
        uint8_t PfcDriver_UpCnt          : 1;    //Bit5  PFC 上升下降         1为上升  0为下降
        uint8_t Bak6                     : 1;    //Bit6  预留位
        uint8_t Bak7                     : 1;    //Bit7  预留位
    } Bits;
} PWM_flag_t;


/***********************************************************************************************************************
 * * Extern variables
***********************************************************************************************************************/
extern volatile PWM_flag_t tPwmFlag;


/***********************************************************************************************************************
 * * Extern functions
***********************************************************************************************************************/
extern void UserPFCDriver_FastLoop(void);


#endif /***Module End***/
#endif
/***********************************************************************************************************************
* * Copyright (c)  CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

