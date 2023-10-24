/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : RTC_Device.h 
 用途 : RTC驱动头文件
***********************************************************************************************************************/
#ifndef _RTC_DEVICE_H_
#define _RTC_DEVICE_H_

#include "I2C_driver.h"


/* BL5372 的寻址字节为（0110010）,BIT0 = 0，代表写命令，BIT0 = 1代表读数据*/
#define BL5372_W_ADDR       (0x64)                                                                                      //写数据的器件寻址字节
#define BL5372_R_ADDR       (0x65)                                                                                      //读数据的器件寻址字节

#define WRITE_MODE          (0x0)
#define READ_MODE           (0x04)

#define SEC_REG_ADDR        (0x00)                                                                                      //秒寄存器
#define MIN_REG_ADDR        (0x01)                                                                                      //分寄存器
#define HOUR_REG_ADDR       (0x02)                                                                                      //时寄存器
#define WEEK_REG_ADDR       (0x03)                                                                                      //周寄存器
#define DAY_REG_ADDR        (0x04)                                                                                      //天寄存器
#define MON_REG_ADDR        (0x05)                                                                                      //月寄存器
#define YEAR_REG_ADDR       (0x06)                                                                                      //年寄存器
#define ADJ_REG_ADDR        (0x07)                                                                                      //调整寄存器
#define CTRL1_REG_ADDR      (0x0E)                                                                                      //控制寄存器1
#define CTRL2_REG_ADDR      (0x0F)                                                                                      //控制寄存器2
#define ONE_DAY_SECOND      (24*60*60L)                                                                                 //一天总秒数
#define ONE_YEAR_DAY        (365)                                                                                       //平年总天数，润年要加1
#define ONE_YEAR_SECOND     (365*24*60*60L)                                                                             //平年总秒数，润年要加24*60*60

typedef struct _time_info_
{
    uint8_t   Sec;                                                                                                      //秒
    uint8_t   Min;                                                                                                      //分
    uint8_t   Hour;                                                                                                     //时
    uint8_t   Day;                                                                                                      //日
    uint8_t   Month;                                                                                                    //月
    uint8_t   Week;                                                                                                     //星期
    uint8_t   Year;                                                                                                     //年
}tTimeInfo,*pTimeInfo;

extern void RTC_Device_BL5372_init(void);
extern void RTC_Device_BL5372_Set_Time(uint8_t *pu8SetTime);
extern void RTC_Device_BL5372_Get_Time(uint8_t *pu8GetTime);
extern uint32_t RTC_Device_DateTimeToSecond(pTimeInfo tTime);
extern void RTC_Device_SecondToDateTime(uint32_t u32Second,pTimeInfo tTime);


extern void EE_WritePage(uint8_t u8DevAddrByte, uint8_t u8RegistAddr, uint8_t u8Bytes, uint8_t *pu8WriteBuf);
extern void EE_ReadBytes(uint8_t u8DevAddrByte, uint8_t u8RegistAddr, uint8_t u8Bytes, uint8_t *pu8ReadBuf);

#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/


