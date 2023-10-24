/***********************************************************************************************************************
* Copyright (c)  , CVTE
* ***********************************************************************************************************************
* 文件名     : crc_driver.c
* 用途       :
************************************************************************************************************************/

#include "interrupt_driver.h"

/*******************************************************************
**Global variables
*******************************************************************/
volatile PWM_flag_t tPwmFlag;


/***********************************************************************************************************************
 功能：外部中断线0_1中断
************************************************************************************************************************/
void EXTI0_1_IRQHandler(void)
{
#if 0
#if EN_PFC_FO
#if IRQ_EXTI0_1 == PFC_FO_EXIT_IRQ_HANDLE
    if (EXTI_GetITStatus(PFC_FO_EXTI_LINE) != RESET)
    {
        EXTI_ClearFlag(PFC_FO_EXTI_LINE);
        PFCDriver_PFC_FO_Deal();
    }
#endif
#endif

#if (MOTOR_FEEDBACK_EXTI == IRQ_EXTI0_1)
    //电机反馈中断回调函数
    if (GET_MOTOR_FEEDBACK_STATUS() != RESET)
    {
        CLR_MOTOR_FEEDBACK_STATUS();
        FanMotor_FeekBack_CallBack();
    }
#endif
#endif
}

/***********************************************************************************************************************
 功能：外部中断线2_3中断
************************************************************************************************************************/
void EXTI2_3_IRQHandler(void)
{
#if 0
#if EN_PFC_FO
#if IRQ_EXTI2_3 == PFC_FO_EXIT_IRQ_HANDLE
    if (EXTI_GetITStatus(PFC_FO_EXTI_LINE) != RESET)
    {
        EXTI_ClearFlag(PFC_FO_EXTI_LINE);
        PFCDriver_PFC_FO_Deal();
    }
#endif
#endif

#if (MOTOR_FEEDBACK_EXTI == IRQ_EXTI2_3)
    //电机反馈中断回调函数
    if (GET_MOTOR_FEEDBACK_STATUS() != RESET)
    {
        CLR_MOTOR_FEEDBACK_STATUS();
        FanMotor_FeekBack_CallBack();
    }
#endif
#endif
}

/***********************************************************************************************************************
 功能：外部中断线4_15中断
************************************************************************************************************************/
void EXTI4_15_IRQHandler(void)
{
#if 0
#if EN_PFC_FO
#if IRQ_EXTI4_15 == PFC_FO_EXIT_IRQ_HANDLE
    if (EXTI_GetITStatus(PFC_FO_EXTI_LINE) != RESET)
    {
        EXTI_ClearFlag(PFC_FO_EXTI_LINE);
        PFCDriver_PFC_FO_Deal();
    }
#endif
#endif

#if (MOTOR_FEEDBACK_EXTI == IRQ_EXTI4_15)
    //电机反馈中断回调函数
    if (GET_MOTOR_FEEDBACK_STATUS() != RESET)
    {
#if DCFANDRIVER_MOUDLE
        FanMotor_FeekBack_CallBack();
#endif
        CLR_MOTOR_FEEDBACK_STATUS();
    }
#endif
#endif
}

/***********************************************************************************************************************
 功能：DMA1 CH1 中断
************************************************************************************************************************/
void DMA1_Channel1_IRQHandler(void)
{
#if 0
    if (DMA_GetITStatus(DMA1_IT_TC1) != RESET)
    {
        DMA_ClearITPendingBit(DMA1_IT_TC1);

        if (tPwmFlag.Bits.AdcChgCmd)
        {
            tPwmFlag.Bits.AdcChgCmd = 0;
#if COMP_DRIVER_SAMPLE_CURR_UP
            tADVar.u16Comp_U_ADCValue = DmaAdVal_Comp_Curr_Buffer[0];
#else
            tADVar.u16Comp_V_ADCValue = DmaAdVal_Comp_Curr_Buffer[0];
#endif
        }
        else
        {
            tPwmFlag.Bits.AdcChgCmd = 1;
#if COMP_DRIVER_SAMPLE_CURR_UP
            tADVar.u16Comp_V_ADCValue = DmaAdVal_Comp_Curr_Buffer[0];
#else
            tADVar.u16Comp_U_ADCValue = DmaAdVal_Comp_Curr_Buffer[0];
#endif
        }
    }
#endif
}

/***********************************************************************************************************************
 功能：DMA1 CH4 5 中断
************************************************************************************************************************/
void DMA1_Channel4_5_IRQHandler(void)
{
#if 0
    if (DMA_GetITStatus(DMA1_IT_TC4) != RESET)
    {
        DMA_ClearITPendingBit(DMA1_IT_TC4);
        tADVar.u16PFC_Current_ADCValue = DmaAdVal_PFC_Sample_Buffer[DEV_PFC_CURRENT_SAMPLE_DATA];
        tADVar.u16AC_Voltage_ADCValue = DmaAdVal_PFC_Sample_Buffer[DEV_VAC_VOLTAGE_SAMPLE_DATA];
//        tADVar.u16CompIPM_ADCValue = DmaAdVal_PFC_Sample_Buffer[2];
//        tADVar.u16OHT_ADCValue = DmaAdVal_PFC_Sample_Buffer[3];
#if (PFC_DRIVER_TYPE)
        UserPFCDriver_FastLoop();                       //PFC快速环
#endif
    }
#endif
}

/***********************************************************************************************************************
* Copyright (c)  CVTE All rights reserved.  * * * END OF FILE
************************************************************************************************************************/
