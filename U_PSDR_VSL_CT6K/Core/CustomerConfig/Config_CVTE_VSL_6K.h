/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
文件 : Config_CVTE_VSL_6K.h 
用途 : CVTE 6K 离并网一体机EMS芯片配置表
***********************************************************************************************************************/
#include "stdint.h"
#include "TypeDef.h"

//此处暂未定义版本规则，后续更改备注说明
/***********************************************************************************************************************
 * 软件版本：年份 + 主版本 + 子版本
 * 监控版本：SWBP014000005V001
***********************************************************************************************************************/
#define ProgramNumData                      0x00000001


/***********************************************************************************************************************
 * 板卡配置相关
***********************************************************************************************************************/
#define EN_LCD_12864_KS0108                 (1)        //显示器使能
#define EN_DISPLAY_STB                      (0)        //显示器写使能引脚STB
#define EN_SWJ_JTAG                         (0)        //使能仿真端口
#define EN_VERTICAL_STEP                    (0)        //
#define EN_HORIZONTAL_STEP                  (0)        //
#define EN_AC_CONTROL                       (0)        //
#define EN_ANION                            (0)        //
#define EN_HEATER                           (0)        //
#define EN_VALVE                            (0)        //
#define EN_LED                              (1)        //LED灯
#define EN_KEY                              (1)        //按键
#define EN_IO_EXTEND_AW9523B                (0)        //IO扩展芯片
#define EN_EEPROM                           (0)        //EEPROM芯片
#define EN_EEPROM_WP                        (0)        //EEPROM写保护
#define EN_COM_PORT_1                       (1)        //用于内部通信
#define EN_COM_PORT_2                       (1)        //用于BMS通信
#define EN_COM_PORT_3                       (1)        //用于WIFI/GPRS
#define EN_COM_PORT_4                       (1)        //用于蓝牙通信
#define EN_COM_PORT_5                       (1)        //用于Debug痛惜
#define EN_COM_PORT_6                       (1)        //用于电表通信
#define EN_LPUART_1                         (0)        //低功耗串口1 集控板通讯
#define EN_SPI_1                            (1)        //片外扩展Flash通信
#define EN_SPI_2                            (0)        //预留
#define EN_SPI_3                            (0)        //预留
#define EN_IIC_1                            (0)        //预留
#define EN_IIC_2                            (0)        //预留
#define EN_IIC_3                            (0)        //预留
#define EN_ADC_1                            (1)        //温度及DRM采样
#define EN_ADC_2                            (0)        //温度及DRM采样
#define EN_DEBUG_UART                       (0)        //调试串口配置
#define EN_UART_SIM                         (0)        //模拟串口配置
#define EN_FAN_PWM                          (0)        //
#define EN_MOTOR_FEEDBACK                   (0)        //
#define EN_PG_ZERO_DETECTION                (0)        //
#define EN_REMOTE                           (0)        //
#define EN_TAPMOTOR                         (0)        //
#define EN_BASE_TIMER                       (1)        //基准时基定时器200us
#define EN_REMOTE_TIMER                     (0)        //
#define EN_BUZZER_PWM                       (1)        //蜂鸣器PWM
#define EN_MUSIC_BUZZER                     (0)        //蜂鸣器美音
#define EN_DMA_ADC                          (0)        //室内温度
#define EN_LINE_SCR                         (0)        //
#define EN_OUTPUT_SCR                       (0)        //
#define EN_LINE_L_RELAY                     (0)        //
#define EN_LINE_N_RELAY                     (0)        //
#define EN_OUTPUT_RELAY                     (0)        //


/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
