/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : RTC_Device.c 
 用途 : RTC驱动
***********************************************************************************************************************/
#include "RTC_Device.h"


/*存储格式：秒分时周天月年*/
/*平年中，当月及前面月份的总天数*/
int16_t gs8DayOfYear[13] = { 0,31,59,90,120,151,181,212,243,273,304,334,365 };
/*平年中，每个月的天数.月是从1开始*/
int16_t gs8DayOfMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

/***********************************************************************************************************************
 功能：十进制转为BCD码
***********************************************************************************************************************/
uint8_t RTC_Device_BL5372_Byte_to_BCD(uint8_t u8Value)
{
#if 0
    uint8_t u8BcdHigh = 0;

    while (u8Value >= 10)
    {
        u8BcdHigh++;
        u8Value -= 10;
    }

    return  ((uint8_t)(u8BcdHigh << 4) | u8Value);
#endif
    return  (u8Value + (u8Value / 10) * 6);
}

/***********************************************************************************************************************
 功能：BCD码转为十进制
***********************************************************************************************************************/
uint8_t RTC_Device_BL5372_BCD_to_Byte(uint8_t u8Value)
{
#if 0
    uint8_t u8Temp = 0;

    u8Temp = ((uint8_t)(u8Value & (uint8_t)0xF0) >> (uint8_t)0x4) * 10;

    return (u8Temp + (u8Value & (uint8_t)0x0F));
#endif
    return (u8Value - (u8Value>>4) * 6);
}

#if 1
/***********************************************************************************************************************
 功能：日期时间转换为秒数
***********************************************************************************************************************/
uint32_t RTC_Device_DateTimeToSecond(pTimeInfo tTime)
{
    uint8_t i;
    uint16_t u16LeapYear,u16Year;
    uint32_t u32Day,u32Sec,u32ySec;

    /*计算出已经过去的整年总共秒数，不包括今年*/
    u16Year = tTime->Year;
    for(i = 0, u32ySec = 0; i < u16Year; i++)
    {
        u32ySec += ONE_YEAR_SECOND;
        if(0 == (i % 4))
        {
            u32ySec += ONE_DAY_SECOND;
        }
    }

    /*计算出今年已过去的整天数，不包括今年*/
    u16LeapYear = u16Year % 4;
    u32Day = gs8DayOfYear[tTime->Month -1];
    u32Day += tTime->Day;//加上本月已过去的天数
    u32Day -= 1;//不包括今天
    if((0 == u16LeapYear) && (tTime->Month >2))
    {
        u32Day += 1;
    }

    /*计算出今天已过去的总秒数*/
    u32Sec = (tTime->Hour) * 3600L + (tTime->Min) *60L + tTime->Sec;
    u32Sec += u32ySec;
    u32Sec += (u32Day *ONE_DAY_SECOND);

    return u32Sec;
}

/***********************************************************************************************************************
 功能：秒数转换为时间日期
***********************************************************************************************************************/
void RTC_Device_SecondToDateTime(uint32_t u32Second,pTimeInfo tTime)
{
    uint8_t i,u8Month;
    uint16_t u16LeapYear,u16Year;
    uint32_t u32Sec;
    
    /*计算已过去的整年数*/
    for(i = 0, u16Year = 0; i < 100; i++)
    {
        u32Sec = ONE_YEAR_SECOND;
        if(0 == (i % 4))
        {
            u32Sec += ONE_DAY_SECOND;
        }
        if(u32Second < u32Sec)
        {
            break;
        }
        u16Year++;
        u32Second -= u32Sec;
    }
    tTime->Year = u16Year;
    
    /*计算出今年已过去的整月数*/
    u16LeapYear = u16Year % 4;
    for(i = 0, u8Month = 1; i < 12; i++)
    {
        u32Sec = gs8DayOfMonth[i];
        u32Sec *= ONE_DAY_SECOND;
        if((0 == u16LeapYear) && (2 == u8Month))
        {
            u32Sec += ONE_DAY_SECOND;
        }
        if(u32Second < u32Sec)
        {
            break;
        }
        u8Month++;
        u32Second -= u32Sec;
    }
    tTime->Month = u8Month;
    
    /*计算出本月已过去的整天数*/
    tTime->Day = u32Second / ONE_DAY_SECOND;
    tTime->Day += 1;
    
    /*计算出当天已过去的整小时数*/
    u32Second %= ONE_DAY_SECOND;
    tTime->Hour = u32Second / 3600L;
    
    /*计算出当天的分、秒*/
    u32Second %= 3600L;
    tTime->Min = u32Second / 60;
    tTime->Sec = u32Second % 60;
}
#endif

void EE_ReadBytes(uint8_t u8DevAddrByte, uint8_t u8RegistAddr, uint8_t u8Bytes, uint8_t *pu8ReadBuf)
{
#if 1
    while(LL_I2C_IsActiveFlag_BUSY(I2C2))
    {
        ;                                                                                                               //判断总线是否空闲
    }
    
    if(!LL_I2C_IsEnabled(I2C2))
    {
        LL_I2C_Enable(I2C2);
    }
    //LL_I2C_DisableAutoEndMode(I2C2);
    //LL_I2C_GenerateStartCondition(I2C2);
    LL_I2C_HandleTransfer(I2C2, u8DevAddrByte, LL_I2C_ADDRSLAVE_7BIT, 1, LL_I2C_MODE_SOFTEND, LL_I2C_GENERATE_START_WRITE);  //硬件传输设置
    Delay_us(10);
    while(LL_I2C_IsActiveFlag_TXIS(I2C2) == RESET);                                                                     //如果写好了
    {
        ;
    }
    LL_I2C_TransmitData8(I2C2,u8RegistAddr);                                                                        //发送读地址
    Delay_us(10);
    LL_I2C_GenerateStartCondition(I2C2);
    LL_I2C_HandleTransfer(I2C2, u8DevAddrByte, LL_I2C_ADDRSLAVE_7BIT, 1, LL_I2C_MODE_AUTOEND,LL_I2C_GENERATE_START_READ);
    //LL_I2C_EnableAutoEndMode(I2C2);
    Delay_us(10);
    //while(LL_I2C_IsActiveFlag_RXNE(I2C2) == RESET)
    {
        ;                                                                                                               //如果没有数据到达就等待
    }
    *pu8ReadBuf = LL_I2C_ReceiveData8(I2C2);
    Delay_us(10);
    while(LL_I2C_IsActiveFlag_STOP(I2C2) == RESET)
    {
        ;
    }
#endif

#if 0
    while(LL_I2C_IsActiveFlag_BUSY(I2C2))
    {
        ;                                                                                                               //判断总线是否空闲
    }

    if(!LL_I2C_IsEnabled(I2C2))
    {
        LL_I2C_Enable(I2C2);
    }
    LL_I2C_HandleTransfer(I2C2, BL5372_W_ADDR, LL_I2C_ADDRSLAVE_7BIT, 1, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);  //硬件传输设置
    while(LL_I2C_IsActiveFlag_TXIS(I2C2) == RESET);                                                                     //如果写好了
    {
        LL_I2C_TransmitData8(I2C2,u8RegistAddr);                                                                        //发送读地址
    }
    *pu8ReadBuf = LL_I2C_ReceiveData8(I2C2);
#endif
}

void EE_WritePage(uint8_t u8DevAddrByte, uint8_t u8RegistAddr, uint8_t u8Bytes, uint8_t *pu8WriteBuf)
{
    while(LL_I2C_IsActiveFlag_BUSY(I2C2) == SET); //判断总线是否空闲
    {
    LL_I2C_HandleTransfer(I2C2, u8DevAddrByte, LL_I2C_ADDRSLAVE_7BIT, 2, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE); //在从机地址的寄存器里写数据
    }
    Delay_us(10);
    if(!LL_I2C_IsEnabled(I2C2))
    {
        LL_I2C_Enable(I2C2);
    }

    while(LL_I2C_IsActiveFlag_TXIS(I2C2) == RESET);
    LL_I2C_TransmitData8(I2C2,u8RegistAddr);
    Delay_us(10);

    while(LL_I2C_IsActiveFlag_TXIS(I2C2) == RESET);
    LL_I2C_TransmitData8(I2C2,*pu8WriteBuf);
    Delay_us(10);

    while(LL_I2C_IsActiveFlag_STOP(I2C2) == RESET);
}

/***********************************************************************************************************************
 功能：从BL5372里读N个字节：有三种读方式
***********************************************************************************************************************/
void RTC_Device_BL5372_Read_Bytes(uint8_t u8RegistAddr,uint8_t *pu8ReadBuf,uint8_t u8Bytes)
{
    u8RegistAddr = (u8RegistAddr << 4) | WRITE_MODE;                                                                    //使用读模式的第一种方式
    EE_ReadBytes(BL5372_R_ADDR, u8RegistAddr, u8Bytes, pu8ReadBuf);                                                     //硬件IIC驱动
}

/***********************************************************************************************************************
 功能：写N个字节到BL5372里
***********************************************************************************************************************/
void RTC_Device_BL5372_Write_Bytes(uint8_t u8RegistAddr,uint8_t *pu8WriteBuf,uint8_t u8Bytes)
{
    u8RegistAddr = (u8RegistAddr << 4) | WRITE_MODE;
    EE_WritePage(BL5372_W_ADDR,u8RegistAddr,u8Bytes,pu8WriteBuf);                                                     //硬件IIC驱动
}

/***********************************************************************************************************************
 功能：设置时间
***********************************************************************************************************************/
void RTC_Device_BL5372_Set_Time(uint8_t *pu8SetTime)
{
    uint8_t i;
    uint8_t u8Data[7] = {0};
    //uint8_t u8TempData = 0;
    
    for(i = 0; i < 7; i ++)
    {
        u8Data[i] = RTC_Device_BL5372_Byte_to_BCD(pu8SetTime[i]);
    }
    
    //u8TempData = u8Data[3];                 //???
    //u8Data[3] = u8Data[5];                  //???
    //u8Data[5] = u8TempData;                 //???
    
    RTC_Device_BL5372_Write_Bytes(YEAR_REG_ADDR, u8Data, 7);
    RTC_Device_BL5372_Write_Bytes(MON_REG_ADDR, &u8Data[1], 7);
    RTC_Device_BL5372_Write_Bytes(DAY_REG_ADDR, &u8Data[2], 7);
    RTC_Device_BL5372_Write_Bytes(WEEK_REG_ADDR, &u8Data[3], 7);
    RTC_Device_BL5372_Write_Bytes(HOUR_REG_ADDR, &u8Data[4], 7);
    RTC_Device_BL5372_Write_Bytes(MIN_REG_ADDR, &u8Data[5], 7);
    RTC_Device_BL5372_Write_Bytes(SEC_REG_ADDR, &u8Data[6], 7);
}


/***********************************************************************************************************************
 功能：获取时间
***********************************************************************************************************************/
void RTC_Device_BL5372_Get_Time(uint8_t *pu8GetTime)
{
    uint8_t i;
    uint8_t u8TempData;
    uint8_t u8GetData[2][7] = {0};
    
    while(1)
    {
        RTC_Device_BL5372_Read_Bytes(YEAR_REG_ADDR, &u8GetData[0][0], 7);
        RTC_Device_BL5372_Read_Bytes(MON_REG_ADDR, &u8GetData[0][1], 7);
        RTC_Device_BL5372_Read_Bytes(DAY_REG_ADDR, &u8GetData[0][2], 7);
        RTC_Device_BL5372_Read_Bytes(WEEK_REG_ADDR, &u8GetData[0][3], 7);
        RTC_Device_BL5372_Read_Bytes(HOUR_REG_ADDR, &u8GetData[0][4], 7);
        RTC_Device_BL5372_Read_Bytes(MIN_REG_ADDR, &u8GetData[0][5], 7);
        RTC_Device_BL5372_Read_Bytes(SEC_REG_ADDR, &u8GetData[0][6], 7);

        RTC_Device_BL5372_Read_Bytes(YEAR_REG_ADDR, &u8GetData[1][0], 7);
        RTC_Device_BL5372_Read_Bytes(MON_REG_ADDR, &u8GetData[1][1], 7);
        RTC_Device_BL5372_Read_Bytes(DAY_REG_ADDR, &u8GetData[1][2], 7);
        RTC_Device_BL5372_Read_Bytes(WEEK_REG_ADDR, &u8GetData[1][3], 7);
        RTC_Device_BL5372_Read_Bytes(HOUR_REG_ADDR, &u8GetData[1][4], 7);
        RTC_Device_BL5372_Read_Bytes(MIN_REG_ADDR, &u8GetData[1][5], 7);
        RTC_Device_BL5372_Read_Bytes(SEC_REG_ADDR, &u8GetData[1][6], 7);

        
        if(u8GetData[0][2] == u8GetData[1][2])                                                                          //时相等
        {
            for(i = 0; i < 7; i ++)
            {
                pu8GetTime[i] = RTC_Device_BL5372_BCD_to_Byte(u8GetData[1][i]);
            }
            break;
        }
    }
    u8TempData = pu8GetTime[3];
    pu8GetTime[3] = pu8GetTime[5];
    pu8GetTime[5] = u8TempData;
}

/***********************************************************************************************************************
 功能：时钟芯片初始化
***********************************************************************************************************************/
void RTC_Device_BL5372_init(void)
{
    uint8_t u8InitFlag = 0;
    uint8_t u8InitData[] = {0x00, 0x00, 0x12, 0x00, 0x01, 0x01, 0x00};
    
    RTC_Device_BL5372_Read_Bytes(CTRL2_REG_ADDR, &u8InitFlag, 1);
    if(u8InitFlag & 0x10)                                                                                               //掉电判断
    {
        u8InitFlag = 0x00;
        RTC_Device_BL5372_Write_Bytes(ADJ_REG_ADDR, &u8InitFlag, 1);                                                    //禁止时间调整
        
        u8InitFlag = 0x20;
        RTC_Device_BL5372_Write_Bytes(CTRL2_REG_ADDR, &u8InitFlag, 1);                                                  //24小时制
        
        RTC_Device_BL5372_Write_Bytes(SEC_REG_ADDR, u8InitData, 7);                                                     //2000年1月1日，星期天 12点0分0秒
    }
}

/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

