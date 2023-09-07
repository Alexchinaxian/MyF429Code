#ifndef __bsp_gpio_h
#define __bsp_gpio_h
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
// LED1的定义
#define LED1_GPIO_Port GPIOH            // 端口设置为H
#define LED1_PIN GPIO_Pin_10            // PIN脚设置为 10
#define LED1_Mode GPIO_Mode_OUT         // 输出模式
#define LED1_OType GPIO_OType_PP        // 推挽输出
#define LED1_PuPd GPIO_PuPd_UP          // 上拉输出
#define LED1_Speed GPIO_Speed_25MHz     // 设置为中等速度
#define LED1_Clock RCC_AHB1Periph_GPIOH // 时钟为AHB1
/*************************************************************************************/
//  按键1的定义
#define KEY1_PIN GPIO_Pin_0
#define KEY1_GPIO_PORT GPIOA
#define KEY1_GPIO_CLK RCC_APB1Periph_GPIOA
/*************************************************************************************/

// 按键2的定义
#define KEY2_PIN GPIO_Pin_13
#define KEY2_GPIO_PORT GPIOC
#define KEY2_GPIO_CLK RCC_AHB1Periph_GPIOC
/*************************************************************************************/

void BSP_Led_Config(void);
#endif
