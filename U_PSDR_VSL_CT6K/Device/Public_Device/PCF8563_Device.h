/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : RTC_Device.h
 用途 : RTC驱动头文件
***********************************************************************************************************************/
#ifndef _PCF8563_DEVICE_H_
#define _PCF8563_DEVICE_H_

#include "main.h"
#include "TypeDef.h"

#if (RTCSIGNAL_SOURCE == RTC_PCF8563_MOUDLE)

//时间结构体
typedef struct
{
    uint8_t  u8YearH;
    uint8_t  u8YearL;
    uint8_t  u8Month;
    uint8_t  u8Day;
    uint8_t  u8Week;
    uint8_t  u8Hour;
    uint8_t  u8Min;
    uint8_t  u8Sec;
} PCF8563_TimeInf_t;


#define PCF8563_ADDRESS_CTRL1_REG_ADDR      (0x00)                                                                       //控制寄存器1
#define PCF8563_ADDRESS_CTRL2_REG_ADDR      (0x01)                                                                       //控制寄存器2
#define PCF8563_ADDRESS_SEC_REG_ADDR        (0x02)                                                                       //秒寄存器
#define PCF8563_ADDRESS_MIN_REG_ADDR        (0x03)                                                                       //分寄存器
#define PCF8563_ADDRESS_HOUR_REG_ADDR       (0x04)                                                                       //时寄存器
#define PCF8563_ADDRESS_DAY_REG_ADDR        (0x05)                                                                       //天寄存器
#define PCF8563_ADDRESS_WEEK_REG_ADDR       (0x06)                                                                       //周寄存器
#define PCF8563_ADDRESS_MON_REG_ADDR        (0x07)                                                                       //月寄存器
#define PCF8563_ADDRESS_YEAR_REG_ADDR       (0x08)                                                                       //年寄存器
#define PCF8563_ADDRESS_ADJ_REG_ADDR        (0x0D)                                                                       //输出频率寄存器

#define WRITE_ADDRESS                       (0xA2)                                                                        //写模式设定
#define READ_ADDRESS                        (0xA3)                                                                        //读模式设定

//设置SDA的输入/输出模式
#define PCF8563_I2C_SDA_SET_IO_MODE(IO_MODE)            (GPIO_Driver_SetPinMode(DEV_BL5372_SDA_PORT, DEV_BL5372_SDA_PIN, IO_MODE))
//设置SCL/SDA的读写数据
#define PCF8563_I2C_SCL_WRITE_IO_STATUS(IO_STATUS)      (GPIO_Driver_WriteOutputPin(DEV_BL5372_SCL_PORT, DEV_BL5372_SCL_PIN, IO_STATUS))
#define PCF8563_I2C_SDA_WRITE_IO_STATUS(IO_STATUS)      (GPIO_Driver_WriteOutputPin(DEV_BL5372_SDA_PORT, DEV_BL5372_SDA_PIN, IO_STATUS))
#define PCF8563_I2C_SDA_READ_IO_STATUS()                (GPIO_Driver_ReadInputPin(DEV_BL5372_SDA_PORT, DEV_BL5372_SDA_PIN))
//设置忙延时等待2us
#define PCF8563_I2C_DELAY_US                             (4)                                                              //说明：这个地方IIC的速率是多少，比如200K

extern void PCF8563_Device_Get_Time(PCF8563_TimeInf_t *pGetTime);
extern void PCF8563_Device_Set_Time(PCF8563_TimeInf_t stSetTime);
extern void PCF8563_Device_InitVar(void);
extern void PCF8563_Device_Init(void);

#endif
#endif


