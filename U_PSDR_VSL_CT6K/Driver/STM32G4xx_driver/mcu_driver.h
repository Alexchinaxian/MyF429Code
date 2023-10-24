/***********************************************************************************************************************
* Copyright (c)  , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
* 文件名        : MCU_Driver.h
* 用途         : MCU_Driver部分
***********************************************************************************************************************/
#ifndef __STM32_MCU_H__
#define __STM32_MCU_H__

#include "MCU.h"
#include "HeadFile.h"

/***********************************************************************************************************************
* * Macro definitions
***********************************************************************************************************************/

#define NOP_DELAY              __NOP

#define ENABLE_INTERRUPT       __enable_irq
#define DISABLE_INTERRUPT      __disable_irq

#define DEBUG_VERSION          1

//#define FIRMWARE_VERSION_H     0x01
//#define FIRMWARE_VERSION_L     0x00

//#define APPLICATIONADDRESS     0x08001100
//#define APPCONFADDRESS         0x08001000
//#define APPDATALICATIONADDRESS     (0x080015d1 - APPLICATIONADDRESS)

//Flash size need to modify to 0x1EB00
//#define EE_FLASH_START_ADDR    0x0801FC00                       //内置EE起始地址:Page 127

//#define FLASHPAGESIZE           1024
//#define APP_PAGE_MAX            124

//#define AT_OK_FLAG              0xAA


//#define IO_REVERSE(a, b)  ((GPIO_ReadOutputDataBit((a),(b)))?(GPIO_SetPinOFF((a),(b))):(GPIO_SetPinON((a),(b))))

/*******************************************************************************
 * 配置外部中断宏说明（外部中断只能选择一个）
 * IRQ_EXTI0_1        : 使用EXTI0 ~ EXTI1
 * IRQ_EXTI2_3        : 使用EXTI2 ~ EXTI3
 * IRQ_EXTI4_15       : 使用EXTI4 ~ EXTI15
*******************************************************************************/
//#define IRQ_EXTI0_1                         (0x01)                //EXTI0 ~ EXTI1
//#define IRQ_EXTI2_3                         (0x02)                //EXTI2 ~ EXTI3
//#define IRQ_EXTI4_15                        (0x03)                //EXTI4 ~ EXTI15


/***********************************************************************************************************************
 * * Extern variables
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Extern functions
************************************************************************************************************************/
extern void MCU_NopDelay_1us(void);

extern void MCU_HardwareDiv_Signed_Init(void);
extern int32_t MCU_SignedHWDiv(int32_t s32Dividend, int32_t s32Divisor);

extern void MCU_HardwareDiv_Unsigned_Init(void);
extern uint32_t MCU_UnSignedHWDiv(uint32_t u32Dividend, uint32_t u32Divisor);
extern void MCU_HardwareSqrt_Init(void);
extern uint32_t MCU_HardwareSqrt(uint32_t u32Value);
#endif
/***********************************************************************************************************************
* * Copyright (c)  CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
