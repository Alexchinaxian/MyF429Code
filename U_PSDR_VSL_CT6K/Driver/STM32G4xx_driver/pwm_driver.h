#ifndef __PWM_DRIVER_H
#define __PWM_DRIVER_H
#include "MCU.h"

extern void PWM_Driver_SetFrequency(TIM_TypeDef *ptTIMx, uint32_t u32Channel, uint32_t u32Period);
extern void PWM_Driver_SetDuty(TIM_TypeDef *ptTIMx, uint32_t u32Channel, uint32_t u32Duty);
extern void PWM_Driver_StartOutput(TIM_TypeDef *ptTIMx, uint32_t u32Channel);
extern void PWM_Driver_StopOutput(TIM_TypeDef *ptTIMx, uint32_t u32Channel);
extern void PWM_Driver_UpdateGeneration(TIM_TypeDef *ptTIMx);

#endif
