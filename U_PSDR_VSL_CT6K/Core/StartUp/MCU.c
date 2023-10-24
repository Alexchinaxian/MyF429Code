/***********************************************************************************************************************
* Copyright (c)  , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
* 文件名       : MCU.c
* 用途         : MCU相关函数
***********************************************************************************************************************/
#ifndef __MCU_C__
#define __MCU_C__

#include "MCU.h"
#include "HeadFile.h"
#include "COMMDeal.h"

/***********************************************************************************************************************
 功能：所有RCC模块的时钟初始化
************************************************************************************************************************/
void Clock_Initial(void)
{
#if 1
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
#if (INSTRUCTION_CACHE_ENABLE == 0U)
  __HAL_FLASH_INSTRUCTION_CACHE_DISABLE();
#endif /* INSTRUCTION_CACHE_ENABLE */

#if (PREFETCH_ENABLE != 0U)
  __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
#endif /* PREFETCH_ENABLE */
	
  /* Use SysTick as time base source and configure 1ms tick (default clock after Reset is HSI) */
  if (HAL_InitTick(TICK_INT_PRIORITY) != HAL_OK)
  {
    //status = HAL_ERROR;
  }
  else
  {
  /* Init the low level hardware */
  HAL_MspInit();
  }

  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
  while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2)
  {
  }

  /* HSE configuration and activation */
  LL_RCC_HSE_Enable();
  while(LL_RCC_HSE_IsReady() != 1)
  {
  }

  /* LSI configuration and activation */
  LL_RCC_LSI_Enable();
  while(LL_RCC_LSI_IsReady() != 1)
  {
  }

#if (RTCSIGNAL_SOURCE == MCU_RTC_MOUDLE)
  /* LSE configuration and activation */
  LL_RCC_LSE_Enable();
  while(LL_RCC_LSE_IsReady() != 1)
  {
  }
#endif

  
  LL_PWR_EnableBkUpAccess();
  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_1, 16, LL_RCC_PLLR_DIV_2);
  LL_RCC_PLL_Enable();
  LL_RCC_PLL_EnableDomain_SYS();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  }

  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Sysclk activation on the main PLL */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  }

  /* Set APB1 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(64000000);

   /* Update the time base */
  if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
  {
    //Error_Handler();
  }
#else
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
    while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2)
    {
    }
    
    /* HSE configuration and activation */
    LL_RCC_HSE_Enable();
    while(LL_RCC_HSE_IsReady() != 1)
    {
    }
    
    /* LSI configuration and activation */
    LL_RCC_LSI_Enable();
    while(LL_RCC_LSI_IsReady() != 1)
    {
    }
    
    LL_PWR_EnableBkUpAccess();
    /* Main PLL configuration and activation */
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_1, 16, LL_RCC_PLLR_DIV_2);
    LL_RCC_PLL_Enable();
    LL_RCC_PLL_EnableDomain_SYS();
    while(LL_RCC_PLL_IsReady() != 1)
    {
    }
    
    /* Set AHB prescaler*/
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    
    /* Sysclk activation on the main PLL */
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
    {
    }
    
    /* Set APB1 prescaler*/
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
    /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
    LL_SetSystemCoreClock(64000000);
    
     /* Update the time base */
    if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
    {
      //Error_Handler();
    }
#endif
}

/***********************************************************************************************************************
 功能：HardFault_Handler中断服务函数
************************************************************************************************************************/
void HardFault_Handler(void)
{
    while(1)
    {
        ;
    }
}

/***********************************************************************************************************************
 功能：DMA1通道1中断服务函数
************************************************************************************************************************/
void DMA1_Channel1_IRQHandler(void)
{

}

/***********************************************************************************************************************
 功能：DMA1通道2、3中断服务函数
************************************************************************************************************************/
void DMA1_Channel2_3_IRQHandler(void)
{
    if (LL_DMA_IsEnabledIT_TC(DEV_COM_PORT1_TX_DMA,DEV_COM_PORT1_TX_DMA_CHANNEL) && LL_DMA_IsActiveFlag_TC1(DEV_COM_PORT1_TX_DMA))
    {
        LL_DMA_ClearFlag_TC1(DEV_COM_PORT1_TX_DMA);
    }
}

/***********************************************************************************************************************
 功能：DMA1通道4~7、DMA2通道1~5中断服务函数
************************************************************************************************************************/
void DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQHandler(void)
{
    if (LL_DMA_IsEnabledIT_TC(DEV_COM_PORT2_TX_DMA,DEV_COM_PORT2_TX_DMA_CHANNEL) && LL_DMA_IsActiveFlag_TC4(DEV_COM_PORT2_TX_DMA))
    {
        LL_DMA_ClearFlag_TC4(DEV_COM_PORT2_TX_DMA);
        DEV_COM_BMS_RS485_RX_EN();
    }

    if (LL_DMA_IsEnabledIT_TC(DEV_COM_PORT3_TX_DMA,DEV_COM_PORT3_TX_DMA_CHANNEL) && LL_DMA_IsActiveFlag_TC6(DEV_COM_PORT3_TX_DMA))
    {
        LL_DMA_ClearFlag_TC6(DEV_COM_PORT3_TX_DMA);
        DEV_COM_WIFI_RS485_RX_EN();
    }

    if (LL_DMA_IsEnabledIT_TC(DEV_COM_PORT4_TX_DMA,DEV_COM_PORT4_TX_DMA_CHANNEL) && LL_DMA_IsActiveFlag_TC2(DEV_COM_PORT4_TX_DMA))
    {
        LL_DMA_ClearFlag_TC2(DEV_COM_PORT4_TX_DMA);
    }

    if (LL_DMA_IsEnabledIT_TC(DEV_COM_PORT5_TX_DMA,DEV_COM_PORT5_TX_DMA_CHANNEL) && LL_DMA_IsActiveFlag_TC3(DEV_COM_PORT5_TX_DMA))
    {
        LL_DMA_ClearFlag_TC3(DEV_COM_PORT5_TX_DMA);
        DEV_COM_AFCI_RS485_RX_EN();
    }

    if (LL_DMA_IsEnabledIT_TC(DEV_COM_PORT6_TX_DMA,DEV_COM_PORT6_TX_DMA_CHANNEL) && LL_DMA_IsActiveFlag_TC5(DEV_COM_PORT6_TX_DMA))
    {
        LL_DMA_ClearFlag_TC5(DEV_COM_PORT6_TX_DMA);
    }
}

/***********************************************************************************************************************
 功能：时基模块中断服务函数
************************************************************************************************************************/
void BASE_TIME_IRQ_HANDLER(void)
{
    BASE_TIMER_HANDLER();
    LL_TIM_ClearFlag_UPDATE(DEV_BASE_TIMER);
}

/***********************************************************************************************************************
 功能：FDCAN1中断服务函数
************************************************************************************************************************/
void TIM16_FDCAN_IT0_IRQHandler(void)
{
    HAL_FDCAN_IRQHandler(&hfdcan1);
}

/***********************************************************************************************************************
 功能：FDCAN2中断服务函数
***********************************************************************************************************************/
void TIM17_FDCAN_IT1_IRQHandler(void)
{
	HAL_FDCAN_IRQHandler(&hfdcan2);
}

/***********************************************************************************************************************
 功能：USART1中断服务函数
************************************************************************************************************************/
void USART1_IRQHandler(void)
{
    if (LL_USART_IsEnabledIT_IDLE(USART1) && LL_USART_IsActiveFlag_IDLE(USART1))
    {
        LL_USART_ClearFlag_IDLE(USART1);        /* Clear IDLE line flag */
        Comm2Meter_GetFlag_RxDecode = STATUS_TRUE;     /* EMS与电表的接收解包标志位置1 */
    }
    if (LL_USART_IsEnabledIT_TC(USART1) && LL_USART_IsActiveFlag_TC(USART1))
    {
        LL_USART_ClearFlag_TC(USART1);
        DEV_COM_METER_RS485_RX_EN();
    }
}

/***********************************************************************************************************************
 功能：USART2+LPUART2中断服务函数
************************************************************************************************************************/
void USART2_LPUART2_IRQHandler(void)
{
    if (LL_USART_IsEnabledIT_IDLE(USART2) && LL_USART_IsActiveFlag_IDLE(USART2))
    {
        LL_USART_ClearFlag_IDLE(USART2);        /* Clear IDLE line flag */
        Comm2Bms_GetFlag_RxDecode = STATUS_TRUE;      /* EMS与BMS的接收解包标志位置1 */
    }
}

/***********************************************************************************************************************
 功能：USART3_4_5_6_LPUART1中断服务函数
************************************************************************************************************************/
void USART3_4_5_6_LPUART1_IRQHandler(void)
{
    if (LL_USART_IsEnabledIT_IDLE(USART3) && LL_USART_IsActiveFlag_IDLE(USART3))
    {
        LL_USART_ClearFlag_IDLE(USART3);        /* Clear IDLE line flag */
        Comm2Pcs_GetFlag_RxDecode = STATUS_TRUE;      /* EMS与PCS的接收解包标志位置1 */
    }

    if (LL_USART_IsEnabledIT_IDLE(USART4) && LL_USART_IsActiveFlag_IDLE(USART4))
    {
        LL_USART_ClearFlag_IDLE(USART4);        /* Clear IDLE line flag */
        Comm2Bluetooth_GetFlag_RxDecode= STATUS_TRUE;    /* EMS与蓝牙通讯的接收解包标志位置1 */
    }

    if (LL_USART_IsEnabledIT_IDLE(USART5) && LL_USART_IsActiveFlag_IDLE(USART5))
    {
        LL_USART_ClearFlag_IDLE(USART5);        /* Clear IDLE line flag */
        Comm2Debug_GetFlag_RxDecode = STATUS_TRUE;      /* EMS与Debug通讯的接收解包标志位置1 */
    }

    if (LL_USART_IsEnabledIT_IDLE(USART6) && LL_USART_IsActiveFlag_IDLE(USART6))
    {
        LL_USART_ClearFlag_IDLE(USART6);        /* Clear IDLE line flag */
        Comm2WifiGprs_GetFlag_RxDecode= STATUS_TRUE;      /* EMS与WIFI/GPRS的接收解包标志位置1 */
    }
}
void SysTick_Handler(void)
{
    HAL_IncTick();
}

/***********************************************************************************************************************
 功能：NVIC初始化
************************************************************************************************************************/
void NVIC_Initial(void)
{

    /* DMA interrupt init */
    /* DMA1_Channel1_IRQn interrupt configuration */
    NVIC_SetPriority(DMA1_Channel1_IRQn, 0);
    NVIC_EnableIRQ(DMA1_Channel1_IRQn);
    /* DMA1_Channel2_3_IRQn interrupt configuration */
    NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0);
    NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
    /* DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQn interrupt configuration */
    NVIC_SetPriority(DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQn, 0);
    NVIC_EnableIRQ(DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQn);
    //LL_DMA_EnableIT_TC(DEV_COM_PORT1_TX_DMA,DEV_COM_PORT1_TX_DMA_CHANNEL);
    LL_DMA_EnableIT_TC(DEV_COM_PORT2_TX_DMA,DEV_COM_PORT2_TX_DMA_CHANNEL);
    LL_DMA_EnableIT_TC(DEV_COM_PORT3_TX_DMA,DEV_COM_PORT3_TX_DMA_CHANNEL);
    //LL_DMA_EnableIT_TC(DEV_COM_PORT4_TX_DMA,DEV_COM_PORT4_TX_DMA_CHANNEL);
    LL_DMA_EnableIT_TC(DEV_COM_PORT5_TX_DMA,DEV_COM_PORT5_TX_DMA_CHANNEL);
    LL_DMA_EnableIT_TC(DEV_COM_PORT6_TX_DMA,DEV_COM_PORT6_TX_DMA_CHANNEL);

    NVIC_SetPriority(DEV_COM_PORT1_IRQ, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), DEV_COM_PORT1_PRIORITY, 0));
    NVIC_EnableIRQ(DEV_COM_PORT1_IRQ);
    LL_USART_EnableIT_IDLE(DEV_COM_PORT1);

    NVIC_SetPriority(DEV_COM_PORT2_IRQ, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), DEV_COM_PORT2_PRIORITY, 0));
    NVIC_EnableIRQ(DEV_COM_PORT2_IRQ);
    LL_USART_EnableIT_IDLE(DEV_COM_PORT2);

    NVIC_SetPriority(DEV_COM_PORT3_IRQ, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), DEV_COM_PORT3_PRIORITY, 0));
    NVIC_EnableIRQ(DEV_COM_PORT3_IRQ);
    LL_USART_EnableIT_IDLE(DEV_COM_PORT3);

    NVIC_SetPriority(DEV_COM_PORT4_IRQ, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), DEV_COM_PORT4_PRIORITY, 0));
    NVIC_EnableIRQ(DEV_COM_PORT4_IRQ);
    LL_USART_EnableIT_IDLE(DEV_COM_PORT4);

    NVIC_SetPriority(DEV_COM_PORT5_IRQ, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), DEV_COM_PORT5_PRIORITY, 0));
    NVIC_EnableIRQ(DEV_COM_PORT5_IRQ);
    LL_USART_EnableIT_IDLE(DEV_COM_PORT5);

    NVIC_SetPriority(DEV_COM_PORT6_IRQ, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), DEV_COM_PORT6_PRIORITY, 0));
    NVIC_EnableIRQ(DEV_COM_PORT6_IRQ);
    LL_USART_EnableIT_IDLE(DEV_COM_PORT6);
    LL_USART_EnableIT_TC(DEV_COM_PORT6);

    /* TIM1 interrupt Init */
    NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 0);
    NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);

    /* TIM15 interrupt Init */
    NVIC_SetPriority(TIM15_IRQn, 0);
    NVIC_EnableIRQ(TIM15_IRQn);
    LL_TIM_EnableIT_UPDATE(DEV_BASE_TIMER);
}

/***********************************************************************************************************************
 功能：初始化系统外设
************************************************************************************************************************/
void MCU_InitSystemDriver(void)
{
    Clock_Initial();        //RCC时钟初始化
    GPIO_Driver_Initial();  //GPIO驱动初始化
    DMA_Driver_Init();      //DMA驱动初始化
    UART_Driver_Init();     //UART驱动初始化
    Tim_Driver_Initial();   //TIM驱动初始化
    ADC_Driver_Initial();   //ADC驱动初始化
    SPI_driver_Initial();   //SPI1初始化
    CAN_Driver_Initial();      //CAN初始化
    NVIC_Initial();         //NVIC中断控制器初始化
}

/***********************************************************************************************************************
 功能：微秒级延时函数
|    u16MicroSecond    |    实测    |
|           1          |   1.6us  |
|           2          |   2.6us  |
|           3          |   3.6us  |
|           4          |   4.6us  |
|           5          |   5.6us  |
|           7          |   7.6us  |
|          10          |  10.6us  |
|          50          |  50.6us  |
|          100         |  100.6us |
|         1000         | 1000.1us |
***********************************************************************************************************************/
void Delay_us(uint16_t u16MicroSecond)
{
    uint16_t i;
    //GPIO_Driver_WriteOutputPin(GPIOD,GPIO_PIN_8,GPIO_PIN_SET);  注意，该I/O需配置成高速模式进行测试
    for(i = 0; i < u16MicroSecond;i++)
    {
        //这里的NOP数量是通过I/O翻转的实测数据确定的
        _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
        _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
        _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
        _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
        _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
        _nop_();_nop_();_nop_();_nop_();_nop_();
    }
    //GPIO_Driver_WriteOutputPin(GPIOD,GPIO_PIN_8,GPIO_PIN_RESET);
}

/***********************************************************************************************************************
 功能：毫秒级延时函数
|    u16MiliSecond     |    实测  |
|           1          |  1.001ms |
|           2          |  2.002ms |
|           5          |  5.002ms |
|           7          |  7.002ms |
|          10          |  10.002ms|
|          20          |  19.999ms|
|          50          |  49.999ms|
|         100          | 100.001ms|
|         500          | 500.000ms|
|         1000         |1000.200ms|
***********************************************************************************************************************/
void Delay_ms(uint16_t u16MiliSecond)
{
    uint16_t i;
    uint16_t u16Count;
    //GPIO_Driver_WriteOutputPin(GPIOD,GPIO_PIN_8,GPIO_PIN_SET);  注意，该I/O需配置成高速模式进行测试
    for(i = 0; i < u16MiliSecond;i++)
    {
        u16Count = 10600;   //这里的NOP数量是通过I/O翻转的实测数据确定的
        while(u16Count)
        {
            _nop_();u16Count--;
        }
    }
    //GPIO_Driver_WriteOutputPin(GPIOD,GPIO_PIN_8,GPIO_PIN_RESET);
}

/***********************************************************************************************************************
功能：系统复位
***********************************************************************************************************************/
void SysSoftwareReset(void)

{
    DISABLE_INTERRUPT();                      //关总中断

    NVIC_SystemReset(); // 复位
}

#endif /***Module End***/
/***********************************************************************************************************************
* * Copyright (c)  CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
