#ifndef __bsp_gpio_h
#define __bsp_gpio_h
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
// LED1�Ķ���
#define LED1_GPIO_Port GPIOH            // �˿�����ΪH
#define LED1_PIN GPIO_Pin_10            // PIN������Ϊ 10
#define LED1_Mode GPIO_Mode_OUT         // ���ģʽ
#define LED1_OType GPIO_OType_PP        // �������
#define LED1_PuPd GPIO_PuPd_UP          // �������
#define LED1_Speed GPIO_Speed_25MHz     // ����Ϊ�е��ٶ�
#define LED1_Clock RCC_AHB1Periph_GPIOH // ʱ��ΪAHB1
/*************************************************************************************/
//  ����1�Ķ���
#define KEY1_PIN GPIO_Pin_0
#define KEY1_GPIO_PORT GPIOA
#define KEY1_GPIO_CLK RCC_APB1Periph_GPIOA
/*************************************************************************************/

// ����2�Ķ���
#define KEY2_PIN GPIO_Pin_13
#define KEY2_GPIO_PORT GPIOC
#define KEY2_GPIO_CLK RCC_AHB1Periph_GPIOC
/*************************************************************************************/

void BSP_Led_Config(void);
#endif
