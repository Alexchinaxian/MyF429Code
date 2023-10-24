/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
文件 : Config.h 
 用途 : 功能模块宏定义选项
***********************************************************************************************************************/
#ifndef __CONFIG_H_
#define __CONFIG_H_

#include "GlobalDefine.h"

//EMS 版本号
#define	VER_V    (1)
#define	VER_B    (2)
#define	VER_D    (7)

//功能模块宏定义
#define MODULE_MCU                      (1)        //MCU模块
#define MODULE_GLOBAL_VAR               (1)        //全局变量模块
#define MODULE_PUBLICFUNC               (1)        //公共函数模块
#define MODULE_TIMETASK                 (1)        //时基模块

#define MODULE_CAPABILITY_TEST          (0)        //能力测试模块
#define MODULE_FACTORYTEST              (0)        //工厂测试模块
#define MODULE_MONITOR                  (0)        //监控模块
#define MODULE_SYSTEMPARA               (0)        //系统参数模块
#define MODULE_SYSTEM_EXECUTE           (0)        //系统执行模块
#define MODULE_SYSTEM_STATUS            (0)        //系统状态模块
#define MODULE_SYSTEM_STATUS_FUNC       (0)        //系统功能模块

#define MODULE_MODBUS                   (0)        //Modbus协议模块
#define MODULE_CAN                      (0)        //CAN协议模块

#define MODULE_IWDG                     (1)        //独立看门狗模块
#define MODULE_BUZZER                   (1)        //蜂鸣器模块
#define MODULE_TEMPERATURE              (0)        //温度采样模块
#define MODULE_DISPXXXX_DRIVER          (0)        //显示器驱动模块
#define MODULE_EEPROM                   (0)        //EEPROM时序模块
#define MODULE_FLASH_ONCHIP             (0)        //片上FLASH时序模块
#define MODULE_FLASH_EXTERN             (1)        //外扩FLASH时序模块

#define BUZZER_SERVICE_MOUDLE           (1)
#define MODBUS_MOUDLE                   (1)
#define CANBUS_MOUDLE                   (1)
#define COM_DEAL_MOUDLE                 (1)
#define MODBUS_RTU_MASTER_MOUDLE        (1)
#define MODBUS_RTU_SLAVE_MOUDLE         (1)
#define MODBUS_ASCII_MASTER_MOUDLE      (1)
#define LCD_SERVICE_MOUDLE              (1)        //LCD显示模块使能
#define STORAGE_SERVICE_MOUDLE          (1)        //存储管理模块使能
#define ENERGY_SERVICE_MOUDLE           (1)        //能量管理模块使能
#define BATTERY_SERVICE_MOUDLE          (1)        //电池保护模块使能
#define FAULT_SERVICE_MOUDLE            (1)        //故障告警模块使能
#define INDICATION_SERVICE_MOUDLE       (1)        //指示灯模块使能
#define STATISTICS_SERVICE_MOUDLE       (1)        //统计模块使能
#define LCD_DEVICE_KS0108_6800_MOUDLE   (1)
#define RTC_SERVICE_MOUDLE              (1)        //时钟模块使能
#define RTCSIGNAL_SOURCE                (RTC_BL5372_MOUDLE)
#define MCU_RTC_MOUDLE                  (0x01)
#define RTC_BL5372_MOUDLE               (0x02)
#define RTC_PCF8563_MOUDLE              (0x03)
#define NTC_SDNT1608X104_DEVICE         (1)
#define NTC_HCS41A103F_C2205_DEVICE     (1)

#define IO_TEST                         (0)

#define RTC_TEST                        (0)
#define LCD_ATE_TEST                    (0)
#define LCD_CHINESE_DISP_TEST           (1)

#if (CVTE_INV_VSL_6K_EMS)
#include "Config_CVTE_VSL_6K.h"
#endif

#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE      
***********************************************************************************************************************/
