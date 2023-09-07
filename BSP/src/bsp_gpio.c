#include "bsp_gpio.h"
// GPIO����֪ʶ
/**
 * ***********************************************************
 * GPIO_Mode ����ģʽ
 *
 * GPIO_Mode_IN  ����
 * GPIO_Mode_OUT ���
 * GPIO_Mode_AF  ����ģʽ
 * GPIO_Mode_AN  ģ������
 * ***********************************************************
 * GPIO_OType ���ģʽ
 *
 * GPIO_OType_PP �������
 * GPIO_OType_OD ��©���
 * ***********************************************************
 * GPIO_PuPd ����������ģʽ��F4ϵ�е�������������������������
 * ���е�������������������������
 *
 * GPIO_PuPd_NOPULL   ��������
 * GPIO_PuPd_UP       ����
 * GPIO_PuPd_DOWN     ����
 * ***********************************************************
 * GPIO_Speed   ��������GPIO�ķ�ת�ٶ�
 *
 * GPIO_Speed_2MHz  ����
 * GPIO_Speed_25MHz ��
 * GPIO_Speed_50MHz ��
 * GPIO_Speed_100MHz ����
 * ***********************************************************
 */

GPIO_InitTypeDef typeLED = {
    .GPIO_Pin = LED1_PIN,
    .GPIO_Mode = LED1_Mode, // ����Ϊ�����
    .GPIO_OType = LED1_OType,
    .GPIO_PuPd = LED1_PuPd,
    .GPIO_Speed = LED1_Speed};

void BSP_Led_Config(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);

  // LED1�ĳ�ʼ��
  GPIO_Init(LED1_GPIO_Port, &typeLED);
}
