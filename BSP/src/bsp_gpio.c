#include "bsp_gpio.h"
// GPIO基本知识
/**
 * ***********************************************************
 * GPIO_Mode 四种模式
 *
 * GPIO_Mode_IN  输入
 * GPIO_Mode_OUT 输出
 * GPIO_Mode_AF  复用模式
 * GPIO_Mode_AN  模拟输入
 * ***********************************************************
 * GPIO_OType 输出模式
 *
 * GPIO_OType_PP 推挽输出
 * GPIO_OType_OD 开漏输出
 * ***********************************************************
 * GPIO_PuPd 设置上下拉模式，F4系列的上下拉电阻在输入输出的外端
 * 所有的输入输出都亦可以设置上下拉
 *
 * GPIO_PuPd_NOPULL   无上下拉
 * GPIO_PuPd_UP       上拉
 * GPIO_PuPd_DOWN     下拉
 * ***********************************************************
 * GPIO_Speed   用于设置GPIO的翻转速度
 *
 * GPIO_Speed_2MHz  低速
 * GPIO_Speed_25MHz 中
 * GPIO_Speed_50MHz 快
 * GPIO_Speed_100MHz 高速
 * ***********************************************************
 */

GPIO_InitTypeDef typeLED = {
    .GPIO_Pin = LED1_PIN,
    .GPIO_Mode = LED1_Mode, // 配置为输出口
    .GPIO_OType = LED1_OType,
    .GPIO_PuPd = LED1_PuPd,
    .GPIO_Speed = LED1_Speed};

void BSP_Led_Config(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);

  // LED1的初始化
  GPIO_Init(LED1_GPIO_Port, &typeLED);
}
