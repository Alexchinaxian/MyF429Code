#include "bsp_rcc.h"

/** ***************时钟的基本知识******************************
 * ***********************************************************
 * HSE      高速外部时钟信号
 * HSI      高速的内部时钟时钟信号
 * PLL      锁相环
 * SYSCLK   系统时钟
 * HCLK     AHB总线时钟
 * APB2     总线时钟 PCLK
 * APB1     总线时钟 PCLK1
 * ***********************************************************
 * 晶振分为有源晶振和无源晶振
 * 有源晶振 OSC_IN 进   OSC_OUT脚 悬空
 * 无源晶振 OSC_IN 进   OSC_OUT脚 进   且在硬件上需要一个谐振电容
 *
 * ***********************************************************
 * 系统时钟来源可以是：HSI、PLLCLK、HSE
 * 一般使用HSE 或者 使用HSE倍频之后的的时钟作为系统时钟。
 * 注意：当HSE故障时 HSE会关闭且PLL也会被关闭，
 * 此时系统时钟会以高速的内部时钟作为备用的系统时钟，
 * 直到HSE恢复正常，对于STM32F429的内部时钟为16M
 *
 * ***********************************************************
 * PLL 锁相环
 * PLL的主要作用是对时钟进行倍频，然后把时钟输出到各个功能部件。
 * PLL： 主PLL 和 PLLI2S 之间均由HSI 或者HSE 来提供时钟输入信号
 * ***********************************************************
 */
