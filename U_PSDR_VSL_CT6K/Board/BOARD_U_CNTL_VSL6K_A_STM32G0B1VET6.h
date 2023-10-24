/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
文件 : BOARD_U_CNTL_VSL6K_A_STM32G0B1VET6.h 
 用途 : 板卡硬件配置头文件
***********************************************************************************************************************/
#ifndef __BOARD_U_CNTL_CT6K_A_STM32G0B1VET6_H__
#define __BOARD_U_CNTL_CT6K_A_STM32G0B1VET6_H__

#include "HeadFile.h"

#define MPU_CLOCK                                (64)                                                                  //系统时钟频率,单位MHz

//蜂鸣器PWM驱动
#if EN_BUZZER_PWM
#define DEV_BUZZER_PWM_TIMER                    TIM1
#define DEV_BUZZER_PWM_PRESCALER                (SystemCoreClock / 1000000)
#define DEV_BUZZER_PWM_RELOAD                   (23435)                                                                //PWM frequency = 64000000/23435 = 2731Hz
#define DEV_BUZZER_PWM_COMPARE                  (16000)                                                                //PWM Duty = 16000/32000 = 50%
#define DEV_BUZZER_PWM_CHANNEL                  PR_TIM_CHANNEL_CH1
#define DEV_BUZZER_ON()                         PR_TIM_EnableAllOutputs(DEV_BUZZER_PWM_TIMER)
#define DEV_BUZZER_OFF()                        PR_TIM_DisableAllOutputs(DEV_BUZZER_PWM_TIMER)
#endif

//显示器驱动
#if EN_LCD_12864_KS0108
#define DEV_LCD_CS1_PORT                        PR_GPIOB
#define DEV_LCD_CS1_PIN                         PR_GPIO_PIN_11
#define DEV_LCD_CS2_PORT                        PR_GPIOB
#define DEV_LCD_CS2_PIN                         PR_GPIO_PIN_12
#define DEV_LCD_RS_PORT                         PR_GPIOA
#define DEV_LCD_KS0108_RS_PIN                   PR_GPIO_PIN_10
#define DEV_LCD_RW_PORT                         PR_GPIOA
#define DEV_LCD_KS0108_RW_PIN                   PR_GPIO_PIN_11
#define DEV_LCD_DB_PORT                         PR_GPIOD
#define DEV_LCD_DB0_PIN                         PR_GPIO_PIN_8
#define DEV_LCD_DB1_PIN                         PR_GPIO_PIN_9
#define DEV_LCD_DB2_PIN                         PR_GPIO_PIN_10
#define DEV_LCD_DB3_PIN                         PR_GPIO_PIN_11
#define DEV_LCD_DB4_PIN                         PR_GPIO_PIN_12
#define DEV_LCD_DB5_PIN                         PR_GPIO_PIN_13
#define DEV_LCD_DB6_PIN                         PR_GPIO_PIN_14
#define DEV_LCD_DB7_PIN                         PR_GPIO_PIN_15
#define DEV_LCD_EN_PORT                         PR_GPIOA
#define DEV_LCD_EN_PIN                          PR_GPIO_PIN_12
#define DEV_LCD_RST_PORT                        PR_GPIOA
#define DEV_LCD_RST_PIN                         PR_GPIO_PIN_15
#define DEV_LCD_POWER_POS_PORT                  PR_GPIOC
#define DEV_LCD_POWER_POS_PIN                   PR_GPIO_PIN_7
#define DEV_LCD_POWER_NEG_PORT                  PR_GPIOC
#define DEV_LCD_POWER_NEG_PIN                   PR_GPIO_PIN_9
#define DEV_LCD_KS0108_D0_Pos                   (8)
#endif

//失能仿真端口
#if EN_SWJ_JTAG

#endif

//按键
#if EN_KEY
//#define DEV_KEY_UP_PORT                         (PR_GPIOB)
//#define DEV_KEY_UP_PIN                          (PR_GPIO_PIN_15)
//#define DEV_KEY_DOWN_PORT                       (PR_GPIOC)
//#define DEV_KEY_DOWN_PIN                        (PR_GPIO_PIN_6)
#define DEV_KEY_DOWN_PORT                       (PR_GPIOB)
#define DEV_KEY_DOWN_PIN                        (PR_GPIO_PIN_15)
#define DEV_KEY_UP_PORT                         (PR_GPIOC)
#define DEV_KEY_UP_PIN                          (PR_GPIO_PIN_6)

#define DEV_KEY_ESC_PORT                        (PR_GPIOA)
#define DEV_KEY_ESC_PIN                         (PR_GPIO_PIN_8)
#define DEV_KEY_ENTER_PORT                      (PR_GPIOA)
#define DEV_KEY_ENTER_PIN                       (PR_GPIO_PIN_9)

#define DEV_KEY_NULL                            (0)
#define DEV_KEY_UP                              (KEY0)
#define DEV_KEY_DOWN                            (KEY1)
#define DEV_KEY_ESC                             (KEY2)
#define DEV_KEY_ENTER                           (KEY3)
#else
#define GET_KEY_STATUS()
#endif

//按键
#if EN_LED
#define DEV_LED_GRID_PORT                       (PR_GPIOF)
#define DEV_LED_GRID_PIN                        (PR_GPIO_PIN_13)

#define DEV_LED_GEN_PORT                        (PR_GPIOF)
#define DEV_LED_GEN_PIN                         (PR_GPIO_PIN_12)

#define DEV_LED_DRY_RLY1_PORT                   (PR_GPIOD)
#define DEV_LED_DRY_RLY1_PIN                    (PR_GPIO_PIN_0)

#define DEV_LED_DRY_RLY2_PORT                   (PR_GPIOD)
#define DEV_LED_DRY_RLY2_PIN                    (PR_GPIO_PIN_1)

#define DEV_LED_FAULT_PORT                      (PR_GPIOB)
#define DEV_LED_FAULT_PIN                       (PR_GPIO_PIN_14)


#define DEV_LED_GRID_ON()                       GPIO_Driver_WriteOutputPin(DEV_LED_GRID_PORT,DEV_LED_GRID_PIN,SET)
#define DEV_LED_GRID_OFF()                      GPIO_Driver_WriteOutputPin(DEV_LED_GRID_PORT,DEV_LED_GRID_PIN,RESET)

#define DEV_LED_GEN_ON()                        GPIO_Driver_WriteOutputPin(DEV_LED_GEN_PORT,DEV_LED_GEN_PIN,SET)
#define DEV_LED_GEN_OFF()                       GPIO_Driver_WriteOutputPin(DEV_LED_GEN_PORT,DEV_LED_GEN_PIN,RESET)

#define DEV_LED_FAULT_ON()                      GPIO_Driver_WriteOutputPin(DEV_LED_FAULT_PORT,DEV_LED_FAULT_PIN,SET)
#define DEV_LED_FAULT_OFF()                     GPIO_Driver_WriteOutputPin(DEV_LED_FAULT_PORT,DEV_LED_FAULT_PIN,RESET)

#define DEV_DRY_RLY1_ON()                       GPIO_Driver_WriteOutputPin(DEV_LED_DRY_RLY1_PORT,DEV_LED_DRY_RLY1_PIN,SET)
#define DEV_DRY_RLY1_OFF()                      GPIO_Driver_WriteOutputPin(DEV_LED_DRY_RLY1_PORT,DEV_LED_DRY_RLY1_PIN,RESET)

#define DEV_DRY_RLY2_ON()                       GPIO_Driver_WriteOutputPin(DEV_LED_DRY_RLY2_PORT,DEV_LED_DRY_RLY2_PIN,SET)
#define DEV_DRY_RLY2_OFF()                      GPIO_Driver_WriteOutputPin(DEV_LED_DRY_RLY2_PORT,DEV_LED_DRY_RLY2_PIN,RESET)
#endif

//SPI flash
#define DEV_GD25QXX_SPI                         hspi1                                                                   //调试前这里需要修改
#define DEV_GD25QXX_NSS_HARD_MODE               (0)                                                                     //片选硬件控制或软件控制

#if DEV_GD25QXX_NSS_HARD_MODE
#else
#define DEV_GD25QXX_CS_GPIO                     PR_GPIOE
#define DEV_GD25QXX_CS_PIN                      PR_GPIO_PIN_12
#endif

//RTC BL5372
#define DEV_BL5372_SCL_PORT                     PR_GPIOB
#define DEV_BL5372_SCL_PIN                      PR_GPIO_PIN_3

#define DEV_BL5372_SDA_PORT                     PR_GPIOB
#define DEV_BL5372_SDA_PIN                      PR_GPIO_PIN_4

//通信相关
#define DEV_RX_BUFF_SIZE                        (512)
#define DEV_TX_BUFF_SIZE                        (512)

//板卡内部通信 绑定
#define DEV_ID_PCS                              DEV_COM_PORT1_ID                                                        //第1路通信口定义为 内部通信
#define DEV_COM_PORT1_SLAVE_SELECT_PORT         PR_GPIOE
#define DEV_COM_PORT1_SLAVE_SELECT_PIN          PR_GPIO_PIN_4
#define DEV_COM_PORT1_SELECT_PCS()              GPIO_Driver_WriteOutputPin(DEV_COM_PORT1_SLAVE_SELECT_PORT, DEV_COM_PORT1_SLAVE_SELECT_PIN, GPIO_PIN_RESET)
#define DEV_COM_PORT1_SELECT_BACKUP()           GPIO_Driver_WriteOutputPin(DEV_COM_PORT1_SLAVE_SELECT_PORT, DEV_COM_PORT1_SLAVE_SELECT_PIN, GPIO_PIN_SET)

//BMS通信 绑定
#define DEV_ID_BMS                              DEV_COM_PORT2_ID                                                        //第2路通信口定义为 BMS通信
#define DEV_COM_BMS_RS485_EN_PORT               PR_GPIOD
#define DEV_COM_BMS_RS485_EN_PIN                PR_GPIO_PIN_4
#define DEV_COM_BMS_RS485_TX_EN()               GPIO_Driver_WriteOutputPin(DEV_COM_BMS_RS485_EN_PORT,DEV_COM_BMS_RS485_EN_PIN,GPIO_PIN_SET)
#define DEV_COM_BMS_RS485_RX_EN()               GPIO_Driver_WriteOutputPin(DEV_COM_BMS_RS485_EN_PORT,DEV_COM_BMS_RS485_EN_PIN,GPIO_PIN_RESET)

//WIFI/GPRS通信 绑定
#define DEV_ID_WIFI_GPRS                        DEV_COM_PORT3_ID                                                        //第3路通信口定义为 WIFI/GPRS通信
#define DEV_COM_WIFI_RS485_EN_PORT              PR_GPIOE
#define DEV_COM_WIFI_RS485_EN_PIN               PR_GPIO_PIN_2
#define DEV_COM_WIFI_RS485_TX_EN()              GPIO_Driver_WriteOutputPin(DEV_COM_WIFI_RS485_EN_PORT,DEV_COM_WIFI_RS485_EN_PIN,GPIO_PIN_SET)
#define DEV_COM_WIFI_RS485_RX_EN()              GPIO_Driver_WriteOutputPin(DEV_COM_WIFI_RS485_EN_PORT,DEV_COM_WIFI_RS485_EN_PIN,GPIO_PIN_RESET)

#define DEV_ID_BLT                              DEV_COM_PORT4_ID                                                        //第4路通信口定义为 蓝牙通信

//AFCI 或 Debug通信 绑定
#define DEV_ID_DEBUG                            DEV_COM_PORT5_ID                                                        //第5路通信口定义为 debug通信
#define DEV_COM_AFCI_RS485_EN_PORT              PR_GPIOE
#define DEV_COM_AFCI_RS485_EN_PIN               PR_GPIO_PIN_7
#define DEV_COM_AFCI_RS485_TX_EN()              GPIO_Driver_WriteOutputPin(DEV_COM_AFCI_RS485_EN_PORT,DEV_COM_AFCI_RS485_EN_PIN,GPIO_PIN_SET)
#define DEV_COM_AFCI_RS485_RX_EN()              GPIO_Driver_WriteOutputPin(DEV_COM_AFCI_RS485_EN_PORT,DEV_COM_AFCI_RS485_EN_PIN,GPIO_PIN_RESET)

//电表通信 绑定
#define DEV_ID_METER                            DEV_COM_PORT6_ID                                                        //第6路通信口定义为 电表485通信
#define DEV_COM_METER_RS485_EN_PORT             PR_GPIOE
#define DEV_COM_METER_RS485_EN_PIN              PR_GPIO_PIN_3
#define DEV_COM_METER_RS485_TX_EN()             GPIO_Driver_WriteOutputPin(DEV_COM_METER_RS485_EN_PORT,DEV_COM_METER_RS485_EN_PIN,GPIO_PIN_SET)
#define DEV_COM_METER_RS485_RX_EN()             GPIO_Driver_WriteOutputPin(DEV_COM_METER_RS485_EN_PORT,DEV_COM_METER_RS485_EN_PIN,GPIO_PIN_RESET)

#if 1
#define PR_COM_ID1                              0
#define PR_COM_ID2                              1
#define PR_COM_ID3                              2
#define PR_COM_ID4                              3
#define PR_COM_ID5                              4
#define PR_COM_ID6                              5
#define DEV_ID_MAX                              6
#endif

#if EN_COM_PORT_1
#define DEV_COM_PORT1                           USART3
#define DEV_COM_PORT1_ID                        PR_COM_ID3
#define DEV_COM_PORT1_BAUDRATE                  38400
#define DEV_COM_PORT1_WORDLEN                   PR_USART_DATAWIDTH_8B
#define DEV_COM_PORT1_STOPBIT                   PR_USART_STOPBITS_1
#define DEV_COM_PORT1_PARITY                    PR_USART_PARITY_NONE
#define DEV_COM_PORT1_TX_PORT                   PR_GPIOC
#define DEV_COM_PORT1_RX_PORT                   PR_GPIOC
#define DEV_COM_PORT1_TX_AF                     PR_GPIO_AF_0
#define DEV_COM_PORT1_RX_AF                     PR_GPIO_AF_0
#define DEV_COM_PORT1_TX_PIN                    PR_GPIO_PIN_10
#define DEV_COM_PORT1_RX_PIN                    PR_GPIO_PIN_11
#define DEV_COM_PORT1_TX_PULL                   PR_GPIO_PULL_NO
#define DEV_COM_PORT1_RX_PULL                   PR_GPIO_PULL_NO
#define DEV_COM_PORT1_PRIORITY                  (1)
#define DEV_COM_PORT1_TX_DMA                    PR_DMA1
#define DEV_COM_PORT1_TX_DMA_CHANNEL            PR_DMA_CHANNEL_2
#define DEV_COM_PORT1_RX_DMA                    PR_DMA1
#define DEV_COM_PORT1_RX_DMA_CHANNEL            PR_DMA_CHANNEL_1
#define DEV_COM_PORT1_DMA_TXBUFF_SIZE           (512)
#define DEV_COM_PORT1_DMA_RXBUFF_SIZE           (512)
#define PR_DMA_ClearFlag_COM_PORT1              LL_DMA_ClearFlag_GI1

#if(DEV_COM_PORT1_ID == PR_COM_ID1)
#define DEV_COM_PORT1_IRQ_HANDLER               USART1_IRQHandler
#define DEV_COM_PORT1_IRQ                       USART1_IRQn
#define DEV_COM_PORT1_TX_DMAMUX                 PR_DMAMUX_REQ_USART1_TX
#define DEV_COM_PORT1_RX_DMAMUX                 PR_DMAMUX_REQ_USART1_RX
#define DEV_COM_PORT1_CLOCK                     PR_USART1_CLOCK
#define DEV_COM_PORT1_CLKSOURCE                 PR_USART1_CLKSOURCE
#elif(DEV_COM_PORT1_ID == PR_COM_ID2)
#define DEV_COM_PORT1_IRQ_HANDLER               USART2_LPUART2_IRQHandler
#define DEV_COM_PORT1_IRQ                       USART2_LPUART2_IRQn
#define DEV_COM_PORT1_TX_DMAMUX                 PR_DMAMUX_REQ_USART2_TX
#define DEV_COM_PORT1_RX_DMAMUX                 PR_DMAMUX_REQ_USART2_RX
#define DEV_COM_PORT1_CLOCK                     PR_USART2_CLOCK
#define DEV_COM_PORT1_CLKSOURCE                 PR_USART2_CLKSOURCE
#elif(DEV_COM_PORT1_ID == PR_COM_ID3)
#define DEV_COM_PORT1_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT1_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT1_TX_DMAMUX                 PR_DMAMUX_REQ_USART3_TX
#define DEV_COM_PORT1_RX_DMAMUX                 PR_DMAMUX_REQ_USART3_RX
#define DEV_COM_PORT1_CLOCK                     PR_USART3_CLOCK
#define DEV_COM_PORT1_CLKSOURCE                 PR_USART3_CLKSOURCE
#elif(DEV_COM_PORT1_ID == PR_COM_ID4)
#define DEV_COM_PORT1_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT1_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT1_TX_DMAMUX                 PR_DMAMUX_REQ_USART4_TX
#define DEV_COM_PORT1_RX_DMAMUX                 PR_DMAMUX_REQ_USART4_RX
#define DEV_COM_PORT1_CLOCK                     PR_USART4_CLOCK
#define DEV_COM_PORT1_CLKSOURCE                 PR_USART4_CLKSOURCE
#elif(DEV_COM_PORT1_ID == PR_COM_ID5)
#define DEV_COM_PORT1_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT1_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT1_TX_DMAMUX                 PR_DMAMUX_REQ_USART5_TX
#define DEV_COM_PORT1_RX_DMAMUX                 PR_DMAMUX_REQ_USART5_RX
#define DEV_COM_PORT1_CLOCK                     PR_USART5_CLOCK
#define DEV_COM_PORT1_CLKSOURCE                 PR_USART5_CLKSOURCE
#elif(DEV_COM_PORT1_ID == PR_COM_ID6)
#define DEV_COM_PORT1_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT1_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT1_TX_DMAMUX                 PR_DMAMUX_REQ_USART6_TX
#define DEV_COM_PORT1_RX_DMAMUX                 PR_DMAMUX_REQ_USART6_RX
#define DEV_COM_PORT1_CLOCK                     PR_USART6_CLOCK
#define DEV_COM_PORT1_CLKSOURCE                 PR_USART6_CLKSOURCE
#endif
#endif

#if EN_COM_PORT_2
#define DEV_COM_PORT2                           USART2
#define DEV_COM_PORT2_ID                        PR_COM_ID2
#define DEV_COM_PORT2_BAUDRATE                  9600
#define DEV_COM_PORT2_WORDLEN                   PR_USART_DATAWIDTH_8B
#define DEV_COM_PORT2_STOPBIT                   PR_USART_STOPBITS_1
#define DEV_COM_PORT2_PARITY                    PR_USART_PARITY_NONE
#define DEV_COM_PORT2_TX_PORT                   PR_GPIOD
#define DEV_COM_PORT2_RX_PORT                   PR_GPIOD
#define DEV_COM_PORT2_TX_AF                     PR_GPIO_AF_0
#define DEV_COM_PORT2_RX_AF                     PR_GPIO_AF_0
#define DEV_COM_PORT2_TX_PIN                    PR_GPIO_PIN_5
#define DEV_COM_PORT2_RX_PIN                    PR_GPIO_PIN_6
#define DEV_COM_PORT2_TX_PULL                   PR_GPIO_PULL_NO
#define DEV_COM_PORT2_RX_PULL                   PR_GPIO_PULL_NO
#define DEV_COM_PORT2_PRIORITY                  (2)
#define DEV_COM_PORT2_TX_DMA                    PR_DMA1
#define DEV_COM_PORT2_TX_DMA_CHANNEL            PR_DMA_CHANNEL_4
#define DEV_COM_PORT2_RX_DMA                    PR_DMA1
#define DEV_COM_PORT2_RX_DMA_CHANNEL            PR_DMA_CHANNEL_3
#define DEV_COM_PORT2_DMA_TXBUFF_SIZE           (512)
#define DEV_COM_PORT2_DMA_RXBUFF_SIZE           (512)
#define PR_DMA_ClearFlag_COM_PORT2              LL_DMA_ClearFlag_GI3

#if(DEV_COM_PORT2_ID == PR_COM_ID1)
#define DEV_COM_PORT2_IRQ_HANDLER               USART1_IRQHandler
#define DEV_COM_PORT2_IRQ                       USART1_IRQn
#define DEV_COM_PORT2_TX_DMAMUX                 PR_DMAMUX_REQ_USART1_TX
#define DEV_COM_PORT2_CLOCK                     PR_USART1_CLOCK
#define DEV_COM_PORT2_CLKSOURCE                 PR_USART1_CLKSOURCE
#elif(DEV_COM_PORT2_ID == PR_COM_ID2)
#define DEV_COM_PORT2_IRQ_HANDLER               USART2_LPUART2_IRQHandler
#define DEV_COM_PORT2_IRQ                       USART2_LPUART2_IRQn
#define DEV_COM_PORT2_TX_DMAMUX                 PR_DMAMUX_REQ_USART2_TX
#define DEV_COM_PORT2_RX_DMAMUX                 PR_DMAMUX_REQ_USART2_RX
#define DEV_COM_PORT2_CLOCK                     PR_USART2_CLOCK
#define DEV_COM_PORT2_CLKSOURCE                 PR_USART2_CLKSOURCE
#elif(DEV_COM_PORT2_ID == PR_COM_ID3)
#define DEV_COM_PORT2_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT2_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT2_TX_DMAMUX                 PR_DMAMUX_REQ_USART3_TX
#define DEV_COM_PORT2_RX_DMAMUX                 PR_DMAMUX_REQ_USART3_RX
#define DEV_COM_PORT2_CLOCK                     PR_USART3_CLOCK
#define DEV_COM_PORT2_CLKSOURCE                 PR_USART3_CLKSOURCE
#elif(DEV_COM_PORT2_ID == PR_COM_ID4)
#define DEV_COM_PORT2_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT2_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT2_TX_DMAMUX                 PR_DMAMUX_REQ_USART4_TX
#define DEV_COM_PORT2_RX_DMAMUX                 PR_DMAMUX_REQ_USART4_RX
#define DEV_COM_PORT2_CLOCK                     PR_USART4_CLOCK
#define DEV_COM_PORT2_CLKSOURCE                 PR_USART4_CLKSOURCE
#elif(DEV_COM_PORT2_ID == PR_COM_ID5)
#define DEV_COM_PORT2_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT2_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT2_TX_DMAMUX                 PR_DMAMUX_REQ_USART5_TX
#define DEV_COM_PORT2_RX_DMAMUX                 PR_DMAMUX_REQ_USART5_RX
#define DEV_COM_PORT2_CLOCK                     PR_USART5_CLOCK
#define DEV_COM_PORT2_CLKSOURCE                 PR_USART5_CLKSOURCE
#elif(DEV_COM_PORT2_ID == PR_COM_ID6)
#define DEV_COM_PORT2_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT2_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT2_TX_DMAMUX                 PR_DMAMUX_REQ_USART6_TX
#define DEV_COM_PORT2_RX_DMAMUX                 PR_DMAMUX_REQ_USART6_RX
#define DEV_COM_PORT2_CLOCK                     PR_USART6_CLOCK
#define DEV_COM_PORT2_CLKSOURCE                 PR_USART6_CLKSOURCE
#endif
#endif

#if EN_COM_PORT_3
#define DEV_COM_PORT3                           USART6
#define DEV_COM_PORT3_ID                        PR_COM_ID6
#define DEV_COM_PORT3_BAUDRATE                  9600
#define DEV_COM_PORT3_WORDLEN                   PR_USART_DATAWIDTH_8B
#define DEV_COM_PORT3_STOPBIT                   PR_USART_STOPBITS_1
#define DEV_COM_PORT3_PARITY                    PR_USART_PARITY_NONE
#define DEV_COM_PORT3_TX_PORT                   PR_GPIOB
#define DEV_COM_PORT3_RX_PORT                   PR_GPIOB
#define DEV_COM_PORT3_TX_AF                     PR_GPIO_AF_8
#define DEV_COM_PORT3_RX_AF                     PR_GPIO_AF_8
#define DEV_COM_PORT3_TX_PIN                    PR_GPIO_PIN_8
#define DEV_COM_PORT3_RX_PIN                    PR_GPIO_PIN_9
#define DEV_COM_PORT3_TX_PULL                   PR_GPIO_PULL_NO
#define DEV_COM_PORT3_RX_PULL                   PR_GPIO_PULL_NO
#define DEV_COM_PORT3_PRIORITY                  (2)
#define DEV_COM_PORT3_TX_DMA                    PR_DMA1
#define DEV_COM_PORT3_TX_DMA_CHANNEL            PR_DMA_CHANNEL_6
#define DEV_COM_PORT3_RX_DMA                    PR_DMA1
#define DEV_COM_PORT3_RX_DMA_CHANNEL            PR_DMA_CHANNEL_5
#define DEV_COM_PORT3_DMA_TXBUFF_SIZE           (512)
#define DEV_COM_PORT3_DMA_RXBUFF_SIZE           (512)
#define PR_DMA_ClearFlag_COM_PORT3              LL_DMA_ClearFlag_GI5

#if(DEV_COM_PORT3_ID == PR_COM_ID1)
#define DEV_COM_PORT3_IRQ_HANDLER               USART1_IRQHandler
#define DEV_COM_PORT3_IRQ                       USART1_IRQn
#define DEV_COM_PORT3_TX_DMAMUX                 PR_DMAMUX_REQ_USART1_TX
#define DEV_COM_PORT3_RX_DMAMUX                 PR_DMAMUX_REQ_USART1_RX
#define DEV_COM_PORT3_CLOCK                     PR_USART1_CLOCK
#define DEV_COM_PORT3_CLKSOURCE                 PR_USART1_CLKSOURCE
#elif(DEV_COM_PORT3_ID == PR_COM_ID2)
#define DEV_COM_PORT3_IRQ_HANDLER               USART2_LPUART2_IRQHandler
#define DEV_COM_PORT3_IRQ                       USART2_LPUART2_IRQn
#define DEV_COM_PORT3_TX_DMAMUX                 PR_DMAMUX_REQ_USART2_TX
#define DEV_COM_PORT3_RX_DMAMUX                 PR_DMAMUX_REQ_USART2_RX
#define DEV_COM_PORT3_CLOCK                     PR_USART2_CLOCK
#define DEV_COM_PORT3_CLKSOURCE                 PR_USART2_CLKSOURCE
#elif(DEV_COM_PORT3_ID == PR_COM_ID3)
#define DEV_COM_PORT3_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT3_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT3_TX_DMAMUX                 PR_DMAMUX_REQ_USART3_TX
#define DEV_COM_PORT3_RX_DMAMUX                 PR_DMAMUX_REQ_USART3_RX
#define DEV_COM_PORT3_CLOCK                     PR_USART3_CLOCK
#define DEV_COM_PORT3_CLKSOURCE                 PR_USART3_CLKSOURCE
#elif(DEV_COM_PORT3_ID == PR_COM_ID4)
#define DEV_COM_PORT3_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT3_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT3_TX_DMAMUX                 PR_DMAMUX_REQ_USART4_TX
#define DEV_COM_PORT3_RX_DMAMUX                 PR_DMAMUX_REQ_USART4_RX
#define DEV_COM_PORT3_CLOCK                     PR_USART4_CLOCK
#define DEV_COM_PORT3_CLKSOURCE                 PR_USART4_CLKSOURCE
#elif(DEV_COM_PORT3_ID == PR_COM_ID5)
#define DEV_COM_PORT3_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT3_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT3_TX_DMAMUX                 PR_DMAMUX_REQ_USART5_TX
#define DEV_COM_PORT3_RX_DMAMUX                 PR_DMAMUX_REQ_USART5_RX
#define DEV_COM_PORT3_CLOCK                     PR_USART5_CLOCK
#define DEV_COM_PORT3_CLKSOURCE                 PR_USART5_CLKSOURCE
#elif(DEV_COM_PORT3_ID == PR_COM_ID6)
#define DEV_COM_PORT3_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT3_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT3_TX_DMAMUX                 PR_DMAMUX_REQ_USART6_TX
#define DEV_COM_PORT3_RX_DMAMUX                 PR_DMAMUX_REQ_USART6_RX
#define DEV_COM_PORT3_CLOCK                     PR_USART6_CLOCK
#define DEV_COM_PORT3_CLKSOURCE                 PR_USART6_CLKSOURCE
#endif
#endif

#if EN_COM_PORT_4
#define DEV_COM_PORT4                           USART4
#define DEV_COM_PORT4_ID                        PR_COM_ID4
#define DEV_COM_PORT4_BAUDRATE                  9600
#define DEV_COM_PORT4_WORDLEN                   PR_USART_DATAWIDTH_8B
#define DEV_COM_PORT4_STOPBIT                   PR_USART_STOPBITS_1
#define DEV_COM_PORT4_PARITY                    PR_USART_PARITY_NONE
#define DEV_COM_PORT4_TX_PORT                   PR_GPIOE
#define DEV_COM_PORT4_RX_PORT                   PR_GPIOE
#define DEV_COM_PORT4_TX_AF                     PR_GPIO_AF_0
#define DEV_COM_PORT4_RX_AF                     PR_GPIO_AF_0
#define DEV_COM_PORT4_TX_PIN                    PR_GPIO_PIN_8
#define DEV_COM_PORT4_RX_PIN                    PR_GPIO_PIN_9
#define DEV_COM_PORT4_TX_PULL                   PR_GPIO_PULL_NO
#define DEV_COM_PORT4_RX_PULL                   PR_GPIO_PULL_NO
#define DEV_COM_PORT4_PRIORITY                  (2)
#define DEV_COM_PORT4_TX_DMA                    PR_DMA2
#define DEV_COM_PORT4_TX_DMA_CHANNEL            PR_DMA_CHANNEL_2
#define DEV_COM_PORT4_RX_DMA                    PR_DMA1
#define DEV_COM_PORT4_RX_DMA_CHANNEL            PR_DMA_CHANNEL_7
#define DEV_COM_PORT4_DMA_TXBUFF_SIZE           (512)
#define DEV_COM_PORT4_DMA_RXBUFF_SIZE           (512)
#define PR_DMA_ClearFlag_COM_PORT4              LL_DMA_ClearFlag_GI7

#if(DEV_COM_PORT4_ID == PR_COM_ID1)
#define DEV_COM_PORT4_IRQ_HANDLER               USART1_IRQHandler
#define DEV_COM_PORT4_IRQ                       USART1_IRQn
#define DEV_COM_PORT4_TX_DMAMUX                 PR_DMAMUX_REQ_USART1_TX
#define DEV_COM_PORT4_RX_DMAMUX                 PR_DMAMUX_REQ_USART1_RX
#define DEV_COM_PORT4_CLOCK                     PR_USART1_CLOCK
#define DEV_COM_PORT4_CLKSOURCE                 PR_USART1_CLKSOURCE
#elif(DEV_COM_PORT4_ID == PR_COM_ID2)
#define DEV_COM_PORT4_IRQ_HANDLER               USART2_LPUART2_IRQHandler
#define DEV_COM_PORT4_IRQ                       USART2_LPUART2_IRQn
#define DEV_COM_PORT4_TX_DMAMUX                 PR_DMAMUX_REQ_USART2_TX
#define DEV_COM_PORT4_RX_DMAMUX                 PR_DMAMUX_REQ_USART2_RX
#define DEV_COM_PORT4_CLOCK                     PR_USART2_CLOCK
#define DEV_COM_PORT4_CLKSOURCE                 PR_USART2_CLKSOURCE
#elif(DEV_COM_PORT4_ID == PR_COM_ID3)
#define DEV_COM_PORT4_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT4_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT4_TX_DMAMUX                 PR_DMAMUX_REQ_USART3_TX
#define DEV_COM_PORT4_RX_DMAMUX                 PR_DMAMUX_REQ_USART3_RX
#define DEV_COM_PORT4_CLOCK                     PR_USART3_CLOCK
#define DEV_COM_PORT4_CLKSOURCE                 PR_USART3_CLKSOURCE
#elif(DEV_COM_PORT4_ID == PR_COM_ID4)
#define DEV_COM_PORT4_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT4_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT4_TX_DMAMUX                 PR_DMAMUX_REQ_USART4_TX
#define DEV_COM_PORT4_RX_DMAMUX                 PR_DMAMUX_REQ_USART4_RX
#define DEV_COM_PORT4_CLOCK                     PR_USART4_CLOCK
#define DEV_COM_PORT4_CLKSOURCE                 PR_USART4_CLKSOURCE
#elif(DEV_COM_PORT4_ID == PR_COM_ID5)
#define DEV_COM_PORT4_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT4_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT4_TX_DMAMUX                 PR_DMAMUX_REQ_USART5_TX
#define DEV_COM_PORT4_RX_DMAMUX                 PR_DMAMUX_REQ_USART5_RX
#define DEV_COM_PORT4_CLOCK                     PR_USART5_CLOCK
#define DEV_COM_PORT4_CLKSOURCE                 PR_USART5_CLKSOURCE

#elif(DEV_COM_PORT4_ID == PR_COM_ID6)
#define DEV_COM_PORT4_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT4_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT4_TX_DMAMUX                 PR_DMAMUX_REQ_USART6_TX
#define DEV_COM_PORT4_RX_DMAMUX                 PR_DMAMUX_REQ_USART6_RX
#define DEV_COM_PORT4_CLOCK                     PR_USART6_CLOCK
#define DEV_COM_PORT4_CLKSOURCE                 PR_USART6_CLKSOURCE
#endif
#endif

#if EN_COM_PORT_5
#define DEV_COM_PORT5                           USART5
#define DEV_COM_PORT5_ID                        PR_COM_ID5
#define DEV_COM_PORT5_BAUDRATE                  9600
#define DEV_COM_PORT5_WORDLEN                   PR_USART_DATAWIDTH_8B
#define DEV_COM_PORT5_STOPBIT                   PR_USART_STOPBITS_1
#define DEV_COM_PORT5_PARITY                    PR_USART_PARITY_NONE
#define DEV_COM_PORT5_TX_PORT                   PR_GPIOE
#define DEV_COM_PORT5_RX_PORT                   PR_GPIOE
#define DEV_COM_PORT5_TX_AF                     PR_GPIO_AF_3
#define DEV_COM_PORT5_RX_AF                     PR_GPIO_AF_3
#define DEV_COM_PORT5_TX_PIN                    PR_GPIO_PIN_10
#define DEV_COM_PORT5_RX_PIN                    PR_GPIO_PIN_11
#define DEV_COM_PORT5_TX_PULL                   PR_GPIO_PULL_NO
#define DEV_COM_PORT5_RX_PULL                   PR_GPIO_PULL_NO
#define DEV_COM_PORT5_PRIORITY                  (3)
#define DEV_COM_PORT5_TX_DMA                    PR_DMA2
#define DEV_COM_PORT5_TX_DMA_CHANNEL            PR_DMA_CHANNEL_3
#define DEV_COM_PORT5_RX_DMA                    PR_DMA2
#define DEV_COM_PORT5_RX_DMA_CHANNEL            PR_DMA_CHANNEL_1
#define DEV_COM_PORT5_DMA_TXBUFF_SIZE           (512)
#define DEV_COM_PORT5_DMA_RXBUFF_SIZE           (512)
#define PR_DMA_ClearFlag_COM_PORT5              LL_DMA_ClearFlag_GI1

#if(DEV_COM_PORT5_ID == PR_COM_ID1)
#define DEV_COM_PORT5_IRQ_HANDLER               USART1_IRQHandler
#define DEV_COM_PORT5_IRQ                       USART1_IRQn
#define DEV_COM_PORT5_TX_DMAMUX                 PR_DMAMUX_REQ_USART1_TX
#define DEV_COM_PORT5_RX_DMAMUX                 PR_DMAMUX_REQ_USART1_RX
#define DEV_COM_PORT5_CLOCK                     PR_USART1_CLOCK
#define DEV_COM_PORT5_CLKSOURCE                 PR_USART1_CLKSOURCE
#elif(DEV_COM_PORT5_ID == PR_COM_ID2)
#define DEV_COM_PORT5_IRQ_HANDLER               USART2_LPUART2_IRQHandler
#define DEV_COM_PORT5_IRQ                       USART2_LPUART2_IRQn
#define DEV_COM_PORT5_TX_DMAMUX                 PR_DMAMUX_REQ_USART2_TX
#define DEV_COM_PORT5_RX_DMAMUX                 PR_DMAMUX_REQ_USART2_RX
#define DEV_COM_PORT5_CLOCK                     PR_USART2_CLOCK
#define DEV_COM_PORT5_CLKSOURCE                 PR_USART2_CLKSOURCE
#elif(DEV_COM_PORT5_ID == PR_COM_ID3)
#define DEV_COM_PORT5_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT5_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT5_TX_DMAMUX                 PR_DMAMUX_REQ_USART3_TX
#define DEV_COM_PORT5_RX_DMAMUX                 PR_DMAMUX_REQ_USART3_RX
#define DEV_COM_PORT5_CLOCK                     PR_USART3_CLOCK
#define DEV_COM_PORT5_CLKSOURCE                 PR_USART3_CLKSOURCE
#elif(DEV_COM_PORT5_ID == PR_COM_ID4)
#define DEV_COM_PORT5_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT5_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT5_TX_DMAMUX                 PR_DMAMUX_REQ_USART4_TX
#define DEV_COM_PORT5_RX_DMAMUX                 PR_DMAMUX_REQ_USART4_RX
#define DEV_COM_PORT5_CLOCK                     PR_USART4_CLOCK
#define DEV_COM_PORT5_CLKSOURCE                 PR_USART4_CLKSOURCE
#elif(DEV_COM_PORT5_ID == PR_COM_ID5)
#define DEV_COM_PORT5_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT5_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT5_TX_DMAMUX                 PR_DMAMUX_REQ_USART5_TX
#define DEV_COM_PORT5_RX_DMAMUX                 PR_DMAMUX_REQ_USART5_RX
#define DEV_COM_PORT5_CLOCK                     PR_USART5_CLOCK
#define DEV_COM_PORT5_CLKSOURCE                 PR_USART5_CLKSOURCE
#elif(DEV_COM_PORT5_ID == PR_COM_ID6)
#define DEV_COM_PORT5_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT5_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT5_TX_DMAMUX                 PR_DMAMUX_REQ_USART6_TX
#define DEV_COM_PORT5_RX_DMAMUX                 PR_DMAMUX_REQ_USART6_RX
#define DEV_COM_PORT5_CLOCK                     PR_USART6_CLOCK
#define DEV_COM_PORT5_CLKSOURCE                 PR_USART6_CLKSOURCE
#endif
#endif

#if EN_COM_PORT_6
#define DEV_COM_PORT6                           USART1
#define DEV_COM_PORT6_ID                        PR_COM_ID1
#define DEV_COM_PORT6_BAUDRATE                  9600
#define DEV_COM_PORT6_WORDLEN                   PR_USART_DATAWIDTH_8B
#define DEV_COM_PORT6_STOPBIT                   PR_USART_STOPBITS_1
#define DEV_COM_PORT6_PARITY                    PR_USART_PARITY_NONE
#define DEV_COM_PORT6_TX_PORT                   PR_GPIOB
#define DEV_COM_PORT6_RX_PORT                   PR_GPIOB
#define DEV_COM_PORT6_TX_AF                     PR_GPIO_AF_0
#define DEV_COM_PORT6_RX_AF                     PR_GPIO_AF_0
#define DEV_COM_PORT6_TX_PIN                    PR_GPIO_PIN_6
#define DEV_COM_PORT6_RX_PIN                    PR_GPIO_PIN_7
#define DEV_COM_PORT6_TX_PULL                   PR_GPIO_PULL_NO
#define DEV_COM_PORT6_RX_PULL                   PR_GPIO_PULL_NO
#define DEV_COM_PORT6_PRIORITY                  (3)
#define DEV_COM_PORT6_TX_DMA                    PR_DMA2
#define DEV_COM_PORT6_TX_DMA_CHANNEL            PR_DMA_CHANNEL_5
#define DEV_COM_PORT6_RX_DMA                    PR_DMA2
#define DEV_COM_PORT6_RX_DMA_CHANNEL            PR_DMA_CHANNEL_4
#define DEV_COM_PORT6_DMA_TXBUFF_SIZE           (512)
#define DEV_COM_PORT6_DMA_RXBUFF_SIZE           (512)
#define PR_DMA_ClearFlag_COM_PORT6              LL_DMA_ClearFlag_GI4

#if(DEV_COM_PORT6_ID == PR_COM_ID1)
#define DEV_COM_PORT6_IRQ_HANDLER               USART1_IRQHandler
#define DEV_COM_PORT6_IRQ                       USART1_IRQn
#define DEV_COM_PORT6_TX_DMAMUX                 PR_DMAMUX_REQ_USART1_TX
#define DEV_COM_PORT6_RX_DMAMUX                 PR_DMAMUX_REQ_USART1_RX
#define DEV_COM_PORT6_CLOCK                     PR_USART1_CLOCK
#define DEV_COM_PORT6_CLKSOURCE                 PR_USART1_CLKSOURCE
#elif(DEV_COM_PORT6_ID == PR_COM_ID2)
#define DEV_COM_PORT6_IRQ_HANDLER               USART2_LPUART2_IRQHandler
#define DEV_COM_PORT6_IRQ                       USART2_LPUART2_IRQn
#define DEV_COM_PORT6_TX_DMAMUX                 PR_DMAMUX_REQ_USART2_TX
#define DEV_COM_PORT6_RX_DMAMUX                 PR_DMAMUX_REQ_USART2_RX
#define DEV_COM_PORT6_CLOCK                     PR_USART2_CLOCK
#define DEV_COM_PORT6_CLKSOURCE                 PR_USART2_CLKSOURCE
#elif(DEV_COM_PORT6_ID == PR_COM_ID3)
#define DEV_COM_PORT6_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT6_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT6_TX_DMAMUX                 PR_DMAMUX_REQ_USART3_TX
#define DEV_COM_PORT6_RX_DMAMUX                 PR_DMAMUX_REQ_USART3_RX
#define DEV_COM_PORT6_CLOCK                     PR_USART3_CLOCK
#define DEV_COM_PORT6_CLKSOURCE                 PR_USART3_CLKSOURCE
#elif(DEV_COM_PORT6_ID == PR_COM_ID4)
#define DEV_COM_PORT6_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT6_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT6_TX_DMAMUX                 PR_DMAMUX_REQ_USART4_TX
#define DEV_COM_PORT6_RX_DMAMUX                 PR_DMAMUX_REQ_USART4_RX
#define DEV_COM_PORT6_CLOCK                     PR_USART4_CLOCK
#define DEV_COM_PORT6_CLKSOURCE                 PR_USART4_CLKSOURCE
#elif(DEV_COM_PORT6_ID == PR_COM_ID5)
#define DEV_COM_PORT6_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT6_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT6_TX_DMAMUX                 PR_DMAMUX_REQ_USART5_TX
#define DEV_COM_PORT6_RX_DMAMUX                 PR_DMAMUX_REQ_USART5_RX
#define DEV_COM_PORT6_CLOCK                     PR_USART5_CLOCK
#define DEV_COM_PORT6_CLKSOURCE                 PR_USART5_CLKSOURCE
#elif(DEV_COM_PORT6_ID == PR_COM_ID6)
#define DEV_COM_PORT6_IRQ_HANDLER               USART3_4_5_6_LPUART1_IRQHandler
#define DEV_COM_PORT6_IRQ                       USART3_4_5_6_LPUART1_IRQn
#define DEV_COM_PORT6_TX_DMAMUX                 PR_DMAMUX_REQ_USART6_TX
#define DEV_COM_PORT6_RX_DMAMUX                 PR_DMAMUX_REQ_USART6_RX
#define DEV_COM_PORT6_CLOCK                     PR_USART6_CLOCK
#define DEV_COM_PORT6_CLKSOURCE                 PR_USART6_CLKSOURCE
#endif
#endif

//基准时基定时器200us
#if EN_BASE_TIMER
#define DEV_BASE_TIMER                          TIM15
#define DEV_BASE_TIMER_PRESCALER                (SystemCoreClock / 1000000)
#define DEV_BASE_TIMER_PERIOD                   (200)
#define DEV_BASE_TIMER_IRQn                     TIM15_IRQn
#define DEV_BASE_TIMER_PRIORITY                 2
#define BASE_TIME_IRQ_HANDLER                   TIM15_IRQHandler

#endif

//蜂鸣器PWM
#if EN_BUZZER_PWM
#define BUZZER_GPIO_PORT                        PR_GPIOB
#define BUZZER_GPIO_PIN                         PR_GPIO_PIN_9
#define BUZZER_GPIO_MODE                        PR_GPIO_MODE_ALTERNATE
#define BUZZER_GPIO_OUTPUTTYPE                  PR_GPIO_OUTPUT_PUSHPULL
#define BUZZER_GPIO_PULL                        PR_GPIO_PULL_NO
#define BUZZER_GPIO_AF                          PR_GPIO_AF_1

#define BUZZER_PWM_TIMER                        PR_TIM17
#define BUZZER_PWM_PRESCALER                    (SystemCoreClock / 1000000)
#define BUZZER_PWM_RELOAD                       2214
#define BUZZER_PWM_COMPARE                      0
#define BUZZER_PWM_CHANNEL                      PR_TIM_CHANNEL_CH1
#endif

//蜂鸣器美音
#if EN_MUSIC_BUZZER

#endif


#endif /***Module End***/


/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

