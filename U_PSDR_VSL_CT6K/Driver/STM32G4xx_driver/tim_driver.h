
#ifndef __TIM_DRIVER_H
#define __TIM_DRIVER_H
#include "MCU.h"

#define PR_TIM1                                 TIM1
#define PR_TIM2                                 TIM2
#define PR_TIM3                                 TIM3
#define PR_TIM4                                 TIM4
//#define PR_TIM5                                 TIM5
#define PR_TIM6                                 TIM6
#define PR_TIM7                                 TIM7
//#define PR_TIM8                                 TIM8
#define PR_TIM15                                TIM15
#define PR_TIM16                                TIM16
#define PR_TIM17                                TIM17
//#define PR_TIM20                                TIM20

#define PR_TIM1_CLOCK_ENABLE                    LL_APB2_GRP1_EnableClock
#define PR_TIM2_CLOCK_ENABLE                    LL_APB1_GRP1_EnableClock
#define PR_TIM3_CLOCK_ENABLE                    LL_APB1_GRP1_EnableClock
#define PR_TIM4_CLOCK_ENABLE                    LL_APB1_GRP1_EnableClock
#define PR_TIM5_CLOCK_ENABLE                    LL_APB1_GRP1_EnableClock
#define PR_TIM6_CLOCK_ENABLE                    LL_APB1_GRP1_EnableClock
#define PR_TIM7_CLOCK_ENABLE                    LL_APB1_GRP1_EnableClock
#define PR_TIM8_CLOCK_ENABLE                    LL_APB2_GRP1_EnableClock
#define PR_TIM15_CLOCK_ENABLE                   LL_APB2_GRP1_EnableClock
#define PR_TIM16_CLOCK_ENABLE                   LL_APB2_GRP1_EnableClock
#define PR_TIM17_CLOCK_ENABLE                   LL_APB2_GRP1_EnableClock
#define PR_TIM20_CLOCK_ENABLE                   LL_APB2_GRP1_EnableClock

#define PR_TIM_EnableAllOutputs                 LL_TIM_EnableAllOutputs
#define PR_TIM_DisableAllOutputs                LL_TIM_DisableAllOutputs


#define PR_PERIPH_TIM1                          LL_APB2_GRP1_PERIPH_TIM1
#define PR_PERIPH_TIM2                          LL_APB1_GRP1_PERIPH_TIM2
#define PR_PERIPH_TIM3                          LL_APB1_GRP1_PERIPH_TIM3
#define PR_PERIPH_TIM4                          LL_APB1_GRP1_PERIPH_TIM4
//#define PR_PERIPH_TIM5                          LL_APB1_GRP1_PERIPH_TIM5
#define PR_PERIPH_TIM6                          LL_APB1_GRP1_PERIPH_TIM6
#define PR_PERIPH_TIM7                          LL_APB1_GRP1_PERIPH_TIM7
//#define PR_PERIPH_TIM8                          LL_APB2_GRP1_PERIPH_TIM8
#define PR_PERIPH_TIM15                         LL_APB2_GRP1_PERIPH_TIM15
#define PR_PERIPH_TIM16                         LL_APB2_GRP1_PERIPH_TIM16
#define PR_PERIPH_TIM17                         LL_APB2_GRP1_PERIPH_TIM17
//#define PR_PERIPH_TIM20                         LL_APB2_GRP1_PERIPH_TIM20

typedef struct
{
    TIM_TypeDef *PR_TIMx;
    void (*PR_TIMx_CLOCK_ENABLE)(uint32_t x);
    uint32_t PR_Periphs;
} Time2ClockTable_t;


// #define PR_TIM_COUNTERMODE_UP					LL_TIM_COUNTERMODE_UP
// #define PR_TIM_COUNTERMODE_DOWN					LL_TIM_COUNTERMODE_DOWN
// #define PR_TIM_COUNTERMODE_CENTER_DOWN			LL_TIM_COUNTERMODE_CENTER_DOWN
// #define PR_TIM_COUNTERMODE_CENTER_UP			LL_TIM_COUNTERMODE_CENTER_UP
// #define PR_TIM_COUNTERMODE_CENTER_UP_DOWN		LL_TIM_COUNTERMODE_CENTER_UP_DOWN

// #define PR_TIM_CLOCKDIVISION_DIV1				LL_TIM_CLOCKDIVISION_DIV1
// #define PR_TIM_CLOCKDIVISION_DIV2				LL_TIM_CLOCKDIVISION_DIV2
// #define PR_TIM_CLOCKDIVISION_DIV4				LL_TIM_CLOCKDIVISION_DIV4

// #define PR_TIM_CLOCKSOURCE_INTERNAL				LL_TIM_CLOCKSOURCE_INTERNAL
// #define PR_TIM_CLOCKSOURCE_EXT_MODE1			LL_TIM_CLOCKSOURCE_EXT_MODE1
// #define PR_TIM_CLOCKSOURCE_EXT_MODE2			LL_TIM_CLOCKSOURCE_EXT_MODE2

#define PR_TIM_CHANNEL_CH1                      LL_TIM_CHANNEL_CH1
#define PR_TIM_CHANNEL_CH1N                     LL_TIM_CHANNEL_CH1N
#define PR_TIM_CHANNEL_CH2                      LL_TIM_CHANNEL_CH2
#define PR_TIM_CHANNEL_CH2N                     LL_TIM_CHANNEL_CH2N
#define PR_TIM_CHANNEL_CH3                      LL_TIM_CHANNEL_CH3
#define PR_TIM_CHANNEL_CH3N                     LL_TIM_CHANNEL_CH3N
#define PR_TIM_CHANNEL_CH4                      LL_TIM_CHANNEL_CH4
//#define PR_TIM_CHANNEL_CH4N                     LL_TIM_CHANNEL_CH4N
#define PR_TIM_CHANNEL_CH5                      LL_TIM_CHANNEL_CH5
#define PR_TIM_CHANNEL_CH6                      LL_TIM_CHANNEL_CH6

extern void TIM_Driver_TIM1_Initial(void);
extern void TIM_Driver_TIM15_Initial(void);
extern void Tim_Driver_Initial(void);
extern void TIM1_PwmDisable(void);
extern void TIM_Driver_TIM1_PWM_Enable(TIM_TypeDef *TIMx);
extern void TIM_Driver_TIM1_PWM_Disable(TIM_TypeDef *TIMx);
extern void Tim_Driver_Set_Freq(TIM_TypeDef *PR_TIMx, uint32_t PR_Channel, uint16_t PR_Prescaler, uint32_t PR_Autoreload, uint32_t PR_CompareValue);
extern void Tim_Driver_Set_Enable(TIM_TypeDef *TIMx, uint32_t Channel, EN_t enable);
#endif
