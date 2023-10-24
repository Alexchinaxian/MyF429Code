/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
文件 : tim_driver.c 
 用途 : Timer 驱动接口
***********************************************************************************************************************/
#include "tim_driver.h"



static void TIM_Driver_TIM1_Initial(void)
{
    LL_TIM_InitTypeDef TIM_InitStruct = {0};
    LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};
    LL_TIM_BDTR_InitTypeDef TIM_BDTRInitStruct = {0};
    
    LL_RCC_SetTIMClockSource(LL_RCC_TIM1_CLKSOURCE_PCLK1);
    
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* Peripheral clock enable */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
    
    /* USER CODE BEGIN TIM1_Init 1 */
    
    /* USER CODE END TIM1_Init 1 */
    TIM_InitStruct.Prescaler = 0;
    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload = DEV_BUZZER_PWM_RELOAD;
    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    TIM_InitStruct.RepetitionCounter = 0;
    LL_TIM_Init(DEV_BUZZER_PWM_TIMER, &TIM_InitStruct);
    LL_TIM_DisableARRPreload(DEV_BUZZER_PWM_TIMER);
    LL_TIM_OC_EnablePreload(DEV_BUZZER_PWM_TIMER, DEV_BUZZER_PWM_CHANNEL);
    TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
    TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_ENABLE;
    TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_ENABLE;
    TIM_OC_InitStruct.CompareValue = DEV_BUZZER_PWM_COMPARE;
    TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
    TIM_OC_InitStruct.OCNPolarity = LL_TIM_OCPOLARITY_HIGH;
    TIM_OC_InitStruct.OCIdleState = LL_TIM_OCIDLESTATE_LOW;
    TIM_OC_InitStruct.OCNIdleState = LL_TIM_OCIDLESTATE_LOW;
    LL_TIM_OC_Init(DEV_BUZZER_PWM_TIMER, DEV_BUZZER_PWM_CHANNEL, &TIM_OC_InitStruct);
    LL_TIM_OC_DisableFast(DEV_BUZZER_PWM_TIMER, DEV_BUZZER_PWM_CHANNEL);
    LL_TIM_SetTriggerOutput(DEV_BUZZER_PWM_TIMER, LL_TIM_TRGO_RESET);
    LL_TIM_SetTriggerOutput2(DEV_BUZZER_PWM_TIMER, LL_TIM_TRGO2_RESET);
    LL_TIM_DisableMasterSlaveMode(DEV_BUZZER_PWM_TIMER);
    TIM_BDTRInitStruct.OSSRState = LL_TIM_OSSR_DISABLE;
    TIM_BDTRInitStruct.OSSIState = LL_TIM_OSSI_DISABLE;
    TIM_BDTRInitStruct.LockLevel = LL_TIM_LOCKLEVEL_OFF;
    TIM_BDTRInitStruct.DeadTime = 0;
    TIM_BDTRInitStruct.BreakState = LL_TIM_BREAK_DISABLE;
    TIM_BDTRInitStruct.BreakPolarity = LL_TIM_BREAK_POLARITY_HIGH;
    TIM_BDTRInitStruct.BreakFilter = LL_TIM_BREAK_FILTER_FDIV1;
    TIM_BDTRInitStruct.BreakAFMode = LL_TIM_BREAK_AFMODE_INPUT;
    TIM_BDTRInitStruct.Break2State = LL_TIM_BREAK2_DISABLE;
    TIM_BDTRInitStruct.Break2Polarity = LL_TIM_BREAK2_POLARITY_HIGH;
    TIM_BDTRInitStruct.Break2Filter = LL_TIM_BREAK2_FILTER_FDIV1;
    TIM_BDTRInitStruct.Break2AFMode = LL_TIM_BREAK_AFMODE_INPUT;
    TIM_BDTRInitStruct.AutomaticOutput = LL_TIM_AUTOMATICOUTPUT_DISABLE;
    LL_TIM_BDTR_Init(DEV_BUZZER_PWM_TIMER, &TIM_BDTRInitStruct);
    /* USER CODE BEGIN TIM1_Init 2 */
    
    /* USER CODE END TIM1_Init 2 */
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOC);
      /**TIM1 GPIO Configuration
      PC8     ------> TIM1_CH1
      */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_8;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_2;
    LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    
    LL_TIM_EnableCounter(DEV_BUZZER_PWM_TIMER);
    LL_TIM_GenerateEvent_UPDATE(DEV_BUZZER_PWM_TIMER);
    TIM_Driver_TIM1_PWM_Enable(DEV_BUZZER_PWM_TIMER);

}

static void TIM_Driver_TIM15_Initial(void)
{
    LL_TIM_InitTypeDef TIM_InitStruct = {0};
    LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};
    LL_TIM_BDTR_InitTypeDef TIM_BDTRInitStruct = {0};
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* Peripheral clock enable */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM15);


    /* USER CODE BEGIN TIM15_Init 1 */

    /* USER CODE END TIM15_Init 1 */
    TIM_InitStruct.Prescaler = 0;
    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload = 64 * DEV_BASE_TIMER_PERIOD;
    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    TIM_InitStruct.RepetitionCounter = 0;
    LL_TIM_Init(DEV_BASE_TIMER, &TIM_InitStruct);
    LL_TIM_DisableARRPreload(DEV_BASE_TIMER);
    TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
    TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.CompareValue = 0;
    TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
    TIM_OC_InitStruct.OCNPolarity = LL_TIM_OCPOLARITY_HIGH;
    TIM_OC_InitStruct.OCIdleState = LL_TIM_OCIDLESTATE_LOW;
    TIM_OC_InitStruct.OCNIdleState = LL_TIM_OCIDLESTATE_LOW;
    LL_TIM_OC_Init(DEV_BASE_TIMER, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);
    LL_TIM_OC_DisableFast(DEV_BASE_TIMER, LL_TIM_CHANNEL_CH1);
    TIM_BDTRInitStruct.OSSRState = LL_TIM_OSSR_DISABLE;
    TIM_BDTRInitStruct.OSSIState = LL_TIM_OSSI_DISABLE;
    TIM_BDTRInitStruct.LockLevel = LL_TIM_LOCKLEVEL_OFF;
    TIM_BDTRInitStruct.DeadTime = 0;
    TIM_BDTRInitStruct.BreakState = LL_TIM_BREAK_DISABLE;
    TIM_BDTRInitStruct.BreakPolarity = LL_TIM_BREAK_POLARITY_HIGH;
    TIM_BDTRInitStruct.BreakFilter = LL_TIM_BREAK_FILTER_FDIV1;
    TIM_BDTRInitStruct.AutomaticOutput = LL_TIM_AUTOMATICOUTPUT_DISABLE;
    LL_TIM_BDTR_Init(DEV_BASE_TIMER, &TIM_BDTRInitStruct);
    /* USER CODE BEGIN TIM15_Init 2 */
    
    /* USER CODE END TIM15_Init 2 */
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOE);
      /**TIM15 GPIO Configuration
      PE0     ------> TIM15_CH1
      */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_0;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
    LL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    LL_TIM_EnableCounter(DEV_BASE_TIMER);

}
void TIM1_PwmDisable(void)
{
    uint32_t tmp = 0;

    tmp = tmp | ((uint32_t)(TIM_CCER_CC1E | TIM_CCER_CC1NE));
    tmp = tmp | ((uint32_t)(TIM_CCER_CC2E | TIM_CCER_CC2NE));

    /* Reset the CCxNE Bit */
    TIM1->CCER &=  ~tmp;
}

void TIM_Driver_TIM1_PWM_Enable(TIM_TypeDef *TIMx)
{

#if 0
    uint32_t    tmp = 0;

    TIM1_PwmDisable();//reset CCER

    tmp = 0;
    tmp = tmp | ((uint32_t)(DEV_BUZZER_PWM_CHANNEL));
    /* Set or reset the CCxNE Bit */
    TIM1->CCER |= tmp;
#else
    LL_TIM_CC_EnableChannel(DEV_BUZZER_PWM_TIMER,DEV_BUZZER_PWM_CHANNEL);
#endif
}

void TIM_Driver_TIM1_PWM_Disable(TIM_TypeDef *TIMx)
{
    uint32_t    tmp = 0;

    tmp = 0;
    tmp = tmp | ((uint32_t)(TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E));
    tmp = tmp | ((uint32_t)(TIM_CCER_CC1NE | TIM_CCER_CC2NE | TIM_CCER_CC3NE));

    /* Reset the CCxNE Bit */
    TIMx->CCER &=  ~tmp;
    TIMx->BDTR &= ~(TIM_BDTR_MOE);
    TIMx->CR1 &= ~(TIM_CR1_CEN);
    TIMx->CNT = 0;
}


void Tim_Driver_Initial(void)
{
    TIM_Driver_TIM1_Initial();
    TIM_Driver_TIM15_Initial();
}


void Tim_Driver_Set_Freq(TIM_TypeDef *PR_TIMx, uint32_t PR_Channel, uint16_t PR_Prescaler, uint32_t PR_Autoreload, uint32_t PR_CompareValue)
{
    LL_TIM_SetAutoReload(PR_TIMx, (PR_Prescaler - 1));
    switch (PR_Channel)
    {
        case PR_TIM_CHANNEL_CH1:
        case PR_TIM_CHANNEL_CH1N:
            LL_TIM_OC_SetCompareCH1(PR_TIMx, PR_CompareValue);
            break;
        case PR_TIM_CHANNEL_CH2:
        case PR_TIM_CHANNEL_CH2N:
            LL_TIM_OC_SetCompareCH2(PR_TIMx, PR_CompareValue);
            break;
        case PR_TIM_CHANNEL_CH3:
        case PR_TIM_CHANNEL_CH3N:
            LL_TIM_OC_SetCompareCH3(PR_TIMx, PR_CompareValue);
            break;
        case PR_TIM_CHANNEL_CH4:
            LL_TIM_OC_SetCompareCH4(PR_TIMx, PR_CompareValue);
            break;
        default:
            break;
    }
}

void Tim_Driver_Set_Enable(TIM_TypeDef *TIMx, uint32_t Channel, EN_t enable)
{
    if(EN_ENABLE == enable)
    {
        LL_TIM_CC_EnableChannel(TIMx, Channel);
    }
    else
    {
        LL_TIM_CC_DisableChannel(TIMx, Channel);
    }
}















/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
