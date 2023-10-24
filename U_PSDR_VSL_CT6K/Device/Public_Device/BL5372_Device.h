#ifndef __BL5372_DEVICE_H__
#define __BL5372_DEVICE_H__

#include "main.h"
#include "TypeDef.h"
#include "RTC_service.h"

#if (RTCSIGNAL_SOURCE == RTC_BL5372_MOUDLE)

//时间结构体
typedef struct
{
    uint8_t  u8Year;
    uint8_t  u8Month;
    uint8_t  u8Day;
    uint8_t  u8Week;
    uint8_t  u8Hour;
    uint8_t  u8Min;
    uint8_t  u8Sec;
} BL5372_TimeInf_t;

#define BL5372_ADDRESS_SEC_REG_ADDR        (0x00)                                                                       //秒寄存器
#define BL5372_ADDRESS_MIN_REG_ADDR        (0x01)                                                                       //分寄存器
#define BL5372_ADDRESS_HOUR_REG_ADDR       (0x02)                                                                       //时寄存器
#define BL5372_ADDRESS_WEEK_REG_ADDR       (0x03)                                                                       //周寄存器
#define BL5372_ADDRESS_DAY_REG_ADDR        (0x04)                                                                       //天寄存器
#define BL5372_ADDRESS_MON_REG_ADDR        (0x05)                                                                       //月寄存器
#define BL5372_ADDRESS_YEAR_REG_ADDR       (0x06)                                                                       //年寄存器
#define BL5372_ADDRESS_ADJ_REG_ADDR        (0x07)                                                                       //调整寄存器
#define BL5372_ADDRESS_CTRL1_REG_ADDR      (0x0E)                                                                       //控制寄存器1
#define BL5372_ADDRESS_CTRL2_REG_ADDR      (0x0F)                                                                       //控制寄存器2

#define WRITE_MODE                         (0x64)                                                                       //写模式
#define READ_MODE                          (0x65)                                                                       //读模式

//设置SDA的输入/输出模式
#define BL5372_I2C_SDA_SET_IO_MODE(IO_MODE)            (GPIO_Driver_SetPinMode(DEV_BL5372_SDA_PORT, DEV_BL5372_SDA_PIN, IO_MODE))
//设置SCL/SDA的读写数据
#define BL5372_I2C_SCL_WRITE_IO_STATUS(IO_STATUS)      (GPIO_Driver_WriteOutputPin(DEV_BL5372_SCL_PORT, DEV_BL5372_SCL_PIN, IO_STATUS))
#define BL5372_I2C_SDA_WRITE_IO_STATUS(IO_STATUS)      (GPIO_Driver_WriteOutputPin(DEV_BL5372_SDA_PORT, DEV_BL5372_SDA_PIN, IO_STATUS))
#define BL5372_I2C_SDA_READ_IO_STATUS()                (GPIO_Driver_ReadInputPin(DEV_BL5372_SDA_PORT, DEV_BL5372_SDA_PIN))
//设置忙延时等待2us
#define BL5372_I2C_DELAY_US                            (10)                                                              //说明：这个地方IIC的速率是多少，比如200K

extern void BL5372_Device_Get_Time(BL5372_TimeInf_t *pGetTime);
extern void BL5372_Device_Set_Time(BL5372_TimeInf_t stSetTime);
extern void BL5372_Device_InitVar(void);
extern void BL5372_Device_Init(void);

#endif
#endif
