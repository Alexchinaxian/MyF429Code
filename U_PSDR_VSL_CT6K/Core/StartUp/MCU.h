/***********************************************************************************************************************
* Copyright (c)  , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
* 文件名        : MCU.h
* 用途         : MCU相关头文件
***********************************************************************************************************************/

#ifndef __MCU_H__
#define __MCU_H__

#include "TypeDef.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "Config.h"

#if 1
/* Includes ------------------------------------------------------------------*/
/* LL Library Include */
#include "stm32g0b1xx.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_ll_pwr.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_adc.h"
#include "stm32g0xx_ll_comp.h"
#include "stm32g0xx_ll_cortex.h"
#include "stm32g0xx_ll_crc.h"
#include "stm32g0xx_ll_crs.h"
#include "stm32g0xx_ll_dac.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_i2c.h"
#include "stm32g0xx_ll_iwdg.h"
#include "stm32g0xx_ll_lptim.h"
#include "stm32g0xx_ll_lpuart.h"
#include "stm32g0xx_ll_rng.h"
#include "stm32g0xx_ll_rtc.h"
#include "stm32g0xx_ll_spi.h"
#include "stm32g0xx_ll_tim.h"
#include "stm32g0xx_ll_ucpd.h"
#include "stm32g0xx_ll_usart.h"
#include "stm32g0xx_ll_wwdg.h"


/* HAL Library Include */
#include "stm32g0xx_hal_cortex.h"
#include "stm32g0xx_hal.h"
//#include "stm32g0xx_hal_rtc.h"
//#include "stm32g0xx_hal_gpio.h"
//#include "stm32g0xx_hal_flash.h"
//#include "stm32g0xx_hal_flash_ex.h"
//#include "stm32g0xx_hal_spi.h"
#include "stm32g0xx_hal_fdcan.h"
#endif

#if 0 // (DEBUG_UART == DEV_UART_NONE)   后期调试时使用
#define printData(f_, ...)
#define printMsg(f_, ...)
#endif

#define BOARD_TYPE BOARD_U_CNTL_VSL6K_A_STM32G0B1VET6    //调试使用，后继整理
/***********************************************************************************************************************
* 选择板卡信息（在工程定义宏）
***********************************************************************************************************************/
#if (BOARD_TYPE == BOARD_U_CNTL_VSL6K_A_STM32G0B1VET6)
#include "BOARD_U_CNTL_VSL6K_A_STM32G0B1VET6.h"
#else
#error "Bad BOARD_TYPE"
#endif

/*******************************************************************************
 * Extern functions
*******************************************************************************/
extern void MCU_InitSystemDriver(void);
extern void HardFault_Handler(void);
extern void DMA1_Channel1_IRQHandler(void);
extern void DMA1_Channel2_3_IRQHandler(void);
extern void DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQHandler(void);
extern void BASE_TIME_IRQ_HANDLER(void);
extern void DEV_COM_PORT6_IRQ_HANDLER(void);
extern void DEV_COM_PORT2_IRQ_HANDLER(void);
extern void DEV_COM_PORT1_IRQ_HANDLER(void);
extern void NVIC_Initial(void);
extern void SysTick_Handler(void);
extern void Delay_us(uint16_t u16MicroSecond);
extern void Delay_ms(uint16_t u16MiliSecond);
extern void SysSoftwareReset(void);

#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
