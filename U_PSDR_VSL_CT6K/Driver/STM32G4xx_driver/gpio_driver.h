/***********************************************************************************************************************
* Copyright (c)  , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
* 文件名        : gpio_driver.h
* 用途         :
***********************************************************************************************************************/
#ifndef __GPIO_DRIVER_H
#define __GPIO_DRIVER_H
#include "MCU.h"

/***********************************************************************************************************************
* * Macro definitions
***********************************************************************************************************************/
#define PR_GPIOA                        GPIOA
#define PR_GPIOB                        GPIOB
#define PR_GPIOC                        GPIOC
#define PR_GPIOD                        GPIOD
#define PR_GPIOE                        GPIOE
#define PR_GPIOF                        GPIOF

#define PR_GPIO_PIN_0                   LL_GPIO_PIN_0
#define PR_GPIO_PIN_1                   LL_GPIO_PIN_1
#define PR_GPIO_PIN_2                   LL_GPIO_PIN_2
#define PR_GPIO_PIN_3                   LL_GPIO_PIN_3
#define PR_GPIO_PIN_4                   LL_GPIO_PIN_4
#define PR_GPIO_PIN_5                   LL_GPIO_PIN_5
#define PR_GPIO_PIN_6                   LL_GPIO_PIN_6
#define PR_GPIO_PIN_7                   LL_GPIO_PIN_7
#define PR_GPIO_PIN_8                   LL_GPIO_PIN_8
#define PR_GPIO_PIN_9                   LL_GPIO_PIN_9
#define PR_GPIO_PIN_10                  LL_GPIO_PIN_10
#define PR_GPIO_PIN_11                  LL_GPIO_PIN_11
#define PR_GPIO_PIN_12                  LL_GPIO_PIN_12
#define PR_GPIO_PIN_13                  LL_GPIO_PIN_13
#define PR_GPIO_PIN_14                  LL_GPIO_PIN_14
#define PR_GPIO_PIN_15                  LL_GPIO_PIN_15

#define PR_GPIO_PIN_RESET                GPIO_PIN_RESET
#define PR_GPIO_PIN_SET                  GPIO_PIN_SET


#define PR_GPIO_MODE_INPUT              LL_GPIO_MODE_INPUT
#define PR_GPIO_MODE_OUTPUT             LL_GPIO_MODE_OUTPUT
#define PR_GPIO_MODE_ALTERNATE          LL_GPIO_MODE_ALTERNATE
#define PR_GPIO_MODE_ANALOG             LL_GPIO_MODE_ANALOG

#define PR_GPIO_OUTPUT_PUSHPULL         LL_GPIO_OUTPUT_PUSHPULL
#define PR_GPIO_OUTPUT_OPENDRAIN        LL_GPIO_OUTPUT_OPENDRAIN

#define PR_GPIO_SPEED_LOW               LL_GPIO_SPEED_LOW
#define PR_GPIO_SPEED_MEDIUM            LL_GPIO_SPEED_MEDIUM
#define PR_GPIO_SPEED_FAST              LL_GPIO_SPEED_FAST
#define PR_GPIO_SPEED_HIGH              LL_GPIO_SPEED_HIGH

#define PR_GPIO_PULL_NO                 LL_GPIO_PULL_NO
#define PR_GPIO_PULL_UP                 LL_GPIO_PULL_UP
#define PR_GPIO_PULL_DOWN               LL_GPIO_PULL_DOWN

#define PR_GPIO_AF_0                    LL_GPIO_AF_0
#define PR_GPIO_AF_1                    LL_GPIO_AF_1
#define PR_GPIO_AF_2                    LL_GPIO_AF_2
#define PR_GPIO_AF_3                    LL_GPIO_AF_3
#define PR_GPIO_AF_4                    LL_GPIO_AF_4
#define PR_GPIO_AF_5                    LL_GPIO_AF_5
#define PR_GPIO_AF_6                    LL_GPIO_AF_6
#define PR_GPIO_AF_7                    LL_GPIO_AF_7
#define PR_GPIO_AF_8                    LL_GPIO_AF_8
#define PR_GPIO_AF_9                    LL_GPIO_AF_9
#define PR_GPIO_AF_10                   LL_GPIO_AF_10
//#define PR_GPIO_AF_11                   LL_GPIO_AF_11
//#define PR_GPIO_AF_12                   LL_GPIO_AF_12
//#define PR_GPIO_AF_13                   LL_GPIO_AF_13
//#define PR_GPIO_AF_14                   LL_GPIO_AF_14
//#define PR_GPIO_AF_15                   LL_GPIO_AF_15







/***********************************************************************************************************************
* * Enum definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
* * Typedef struct
***********************************************************************************************************************/

/***********************************************************************************************************************
 * * Extern variables
***********************************************************************************************************************/

/***********************************************************************************************************************
 * * Extern functions
***********************************************************************************************************************/

extern void     GPIO_Driver_SetPinMode(GPIO_TypeDef *ptGPIOx, uint32_t u32GpioPin, uint32_t u32Mode);
extern void     GPIO_Driver_WriteOutputPin(GPIO_TypeDef *ptGPIOx, uint32_t u32GPIO_Pin, uint32_t u32Value);
extern uint32_t GPIO_Driver_ReadOutputPin(GPIO_TypeDef *ptGPIOx, uint32_t u32GPIO_Pin);
extern void     GPIO_Driver_ToggleOutputPin(GPIO_TypeDef *ptGPIOx, uint32_t u32GPIO_Pin);
extern uint32_t GPIO_Driver_ReadInputPin(GPIO_TypeDef *ptGPIOx, uint32_t u32GPIO_Pin);

extern void     GPIO_Driver_Initial(void);

#endif /***Module End***/

/***********************************************************************************************************************
* * Copyright (c)  CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
