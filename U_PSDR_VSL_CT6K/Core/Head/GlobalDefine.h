/***********************************************************************************************************************
* Copyright (c)  , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
* 文件名        : GlobalDefine.h
* 用途         : 全局定义头文件
***********************************************************************************************************************/
#ifndef __GLOBALDEFINE_H_
#define __GLOBALDEFINE_H_

/***********************************************************************************************************************
**  Typedef definitions
***********************************************************************************************************************/
//项目定义
#define BOARD_U_CNTL_CT6K_A_STM32G0B1VET6           (0x01)
#define BOARD_U_CNTL_CT6K_A_XXXX                    (0x02)

//芯片定义
#define MCU_ST                          (0x01)
#define MCU_TI                          (0x02)

//调试端口
#define DEV_UART_NONE                   (0x00)        //无串口
#define DEV_UART_SIM                    (0x01)        //模拟串口
#define DEV_UART_1                      (0x02)        //串口1
#define DEV_UART_2                      (0x03)        //串口2
#define DEV_LPUART                      (0x04)        //低功耗串口

//EEPROM参数类型
#define EEDATA_CVTE_DP2_KFR_35GW        (0x01)            //EEPROM参数1
#define EEDATA_CVTE_BP1_KFR_35GW        (0x02)            //EEPROM参数2
#define EEDATA_MIWO_DP2_KFR_35GW        (0x03)            //EEPROM参数3

//故障显示类型
#define ERROR_CODE_SIGNAL_DISP          (0x01)
#define ERROR_CODE_CYCLE_DISP           (0x02)

//按键有效电平
#define HIGH_LEVEL                      (0x01)
#define LOW_LEVEL                       (0x02)

//参数存储类型
#define NULL_TYPE                       (0x00)
#define FLASH_TYPE                      (0x01)
#define EEPROM_TYPE                     (0x02)

//内外机协议类型
#define CVTE_COMM_PROTOCOL              (0x01)

//段选
#define DISP_GRID1_ADDR                 (0x00)
#define DISP_GRID2_ADDR                 (0x01)
#define DISP_GRID3_ADDR                 (0x02)
#define DISP_GRID4_ADDR                 (0x03)
#define DISP_GRID5_ADDR                 (0x04)

#endif
