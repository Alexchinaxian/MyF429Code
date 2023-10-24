/***********************************************************************************************************************
* Copyright (c) , CVTE
* All rights reserved.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
* 文件    : PCF8563_Device.c
* 用途     :RTC时钟芯片设备驱动文件
***********************************************************************************************************************/
#include "MCU.h"
#include "HeadFile.h"
#include "PCF8563_Device.h"

#if (RTCSIGNAL_SOURCE == RTC_PCF8563_MOUDLE)

/***********************************************************************************************************************
Global variables and funtions
************************************************************************************************************************/

/***********************************************************************************************************************
 功能：IIC发送start信号
************************************************************************************************************************/
void PCF8563_Device_I2C_Start(void)
{
    PCF8563_I2C_SDA_SET_IO_MODE(PR_GPIO_MODE_OUTPUT);                                                                    //设置SDA I/O口为输出
    PCF8563_I2C_SDA_WRITE_IO_STATUS(IO_HIGH);                                                                            //SDA 高电平
    PCF8563_I2C_SCL_WRITE_IO_STATUS(IO_HIGH);                                                                            //SCL 高电平
    Delay_us(PCF8563_I2C_DELAY_US);
    PCF8563_I2C_SDA_WRITE_IO_STATUS(IO_LOW);                                                                             //SDA 低电平
    Delay_us(PCF8563_I2C_DELAY_US);
    PCF8563_I2C_SCL_WRITE_IO_STATUS(IO_LOW);                                                                             //SCL低电平
    Delay_us(PCF8563_I2C_DELAY_US);
}

/***********************************************************************************************************************
 功能：IIC发送stop信号
************************************************************************************************************************/
void PCF8563_Device_I2C_Stop(void)
{
    PCF8563_I2C_SDA_SET_IO_MODE(PR_GPIO_MODE_OUTPUT);                                                                    //设置SDA I/O口为输出
    PCF8563_I2C_SDA_WRITE_IO_STATUS(IO_LOW);                                                                             //SDA 低电平
    Delay_us(PCF8563_I2C_DELAY_US);
    PCF8563_I2C_SCL_WRITE_IO_STATUS(IO_HIGH);                                                                            //SCL 高电平
    Delay_us(PCF8563_I2C_DELAY_US);
    PCF8563_I2C_SDA_WRITE_IO_STATUS(IO_HIGH);                                                                            //SDA 高电平
    Delay_us(PCF8563_I2C_DELAY_US);
}

void PCF8563_Device_I2C_ACK(void)
{
    PCF8563_I2C_SDA_SET_IO_MODE(PR_GPIO_MODE_OUTPUT);                                                                    //设置SDA I/O口为输出
    PCF8563_I2C_SCL_WRITE_IO_STATUS(IO_LOW);                                                                             //SCL 低电平
    PCF8563_I2C_SDA_WRITE_IO_STATUS(IO_LOW);                                                                             //SDA 低电平
    Delay_us(PCF8563_I2C_DELAY_US);
    PCF8563_I2C_SCL_WRITE_IO_STATUS(IO_HIGH);                                                                            //SCL 高电平
    Delay_us(PCF8563_I2C_DELAY_US);
    PCF8563_I2C_SCL_WRITE_IO_STATUS(IO_LOW);                                                                             //SCL 低电平
    Delay_us(PCF8563_I2C_DELAY_US);
    PCF8563_I2C_SDA_WRITE_IO_STATUS(IO_HIGH);                                                                             //SDA 低电平
}

void PCF8563_Device_I2C_NACK(void)
{
    PCF8563_I2C_SDA_SET_IO_MODE(PR_GPIO_MODE_OUTPUT);                                                                    //设置SDA I/O口为输出
    PCF8563_I2C_SCL_WRITE_IO_STATUS(IO_LOW);                                                                             //SCL 低电平
    PCF8563_I2C_SDA_WRITE_IO_STATUS(IO_HIGH);                                                                             //SDA 低电平
    Delay_us(PCF8563_I2C_DELAY_US);
    PCF8563_I2C_SCL_WRITE_IO_STATUS(IO_HIGH);                                                                            //SCL 高电平
    Delay_us(PCF8563_I2C_DELAY_US);
    PCF8563_I2C_SCL_WRITE_IO_STATUS(IO_LOW);                                                                             //SCL 低电平
    Delay_us(PCF8563_I2C_DELAY_US);
}
/***********************************************************************************************************************
 功能：IIC发送1位数据
************************************************************************************************************************/
void PCF8563_Device_I2C_WriteBit(uint8_t u8Data)
{
    PCF8563_I2C_SDA_SET_IO_MODE(PR_GPIO_MODE_OUTPUT);                                                                    //设置SDA I/O口为输出
    PCF8563_I2C_SCL_WRITE_IO_STATUS(IO_LOW);                                                                             //SCL 低电平
    Delay_us(PCF8563_I2C_DELAY_US);
    PCF8563_I2C_SDA_WRITE_IO_STATUS(!!u8Data);                                                                           //SDA 数据，两次取反，uint8_t转换为bool
    Delay_us(PCF8563_I2C_DELAY_US);
    PCF8563_I2C_SCL_WRITE_IO_STATUS(IO_HIGH);                                                                            //SCL 高电平
    Delay_us(PCF8563_I2C_DELAY_US);
}

/***********************************************************************************************************************
 功能：IIC读取1位数据
************************************************************************************************************************/
uint8_t PCF8563_Device_I2C_ReadBit(void)
{
    uint8_t u8Data;
    PCF8563_I2C_SCL_WRITE_IO_STATUS(IO_LOW);                                                                             //SCL 低电平
    PCF8563_I2C_SDA_SET_IO_MODE(PR_GPIO_MODE_INPUT);                                                                     //设置SDA I/O口为输入
    Delay_us(PCF8563_I2C_DELAY_US);
    PCF8563_I2C_SCL_WRITE_IO_STATUS(IO_HIGH);                                                                            //SCL 高电平
    Delay_us(PCF8563_I2C_DELAY_US);
    u8Data = PCF8563_I2C_SDA_READ_IO_STATUS();
    Delay_us(PCF8563_I2C_DELAY_US);
    PCF8563_I2C_SCL_WRITE_IO_STATUS(IO_LOW);

    return (!!u8Data);
}

/***********************************************************************************************************************
 功能：IIC发送1个字节 从高位往低位发
************************************************************************************************************************/
void PCF8563_Device_I2C_WriteByte(uint8_t u8Data)
{
    uint8_t i;

    for(i = 0; i < 8; i++)
    {
        PCF8563_Device_I2C_WriteBit((u8Data & 0x80));
        u8Data <<= 1;
    }
}

/***********************************************************************************************************************
 功能：IIC读取1个字节 从高位往低位读
************************************************************************************************************************/
uint8_t PCF8563_Device_I2C_ReadByte(void)
{
    uint8_t i, u8Data = 0;

    for(i = 0; i < 8; i++)
    {
        u8Data <<= 1;
        u8Data |= PCF8563_Device_I2C_ReadBit();
    }

    return u8Data;
}

/***********************************************************************************************************************
 功能：十进制转为BCD码
***********************************************************************************************************************/
uint8_t PCF8563_Device_Byte_to_BCD(uint8_t u8Value)
{
    return  (u8Value + (u8Value / 10) * 6);
}

/***********************************************************************************************************************
 功能：BCD码转为十进制
***********************************************************************************************************************/
uint8_t PCF8563_Device_BCD_to_Byte(uint8_t u8Value)
{
    return (u8Value - (u8Value >> 4) * 6);
}

/***********************************************************************************************************************
 功能：PCF8563发送一个字节的数据
************************************************************************************************************************/
bool_t PCF8563_Device_Write_Data(uint8_t u8Address, uint8_t u8Data)
{
    DISABLE_INTERRUPT();                      //关总中断

    uint8_t u8Ack;                                                                                                       //使用写模式传输模式0000

    PCF8563_Device_I2C_Start();                                                                                           //产生起始信号

    PCF8563_Device_I2C_WriteByte(WRITE_ADDRESS);                                                                         //发送设备寻址字节
    u8Ack = PCF8563_Device_I2C_ReadBit();                                                                                //读取从设备回复信息

    if(u8Ack == I2C_NAK)
    {
        PCF8563_Device_I2C_Stop();                                                                                       //NAK则发出停止信号

        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    PCF8563_Device_I2C_WriteByte((uint8_t)u8Address);                                                                    //发送读取的第一个寄存器地址
    u8Ack = PCF8563_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        PCF8563_Device_I2C_Stop();                                                                                       //NAK则发出停止信号

        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    PCF8563_Device_I2C_WriteByte((uint8_t)u8Data);                                                                       //写入一个字节的数据
    u8Ack = PCF8563_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        PCF8563_Device_I2C_Stop();                                                                                       //NAK则发出停止信号

        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    PCF8563_Device_I2C_Stop();                                                                                           //写操作执行完毕，产生停止信号

    ENABLE_INTERRUPT();
    return STATUS_TRUE;
}

/***********************************************************************************************************************
 功能：PCF8563读一个字节的数据
************************************************************************************************************************/
bool_t PCF8563_Device_Read_Data(uint8_t u8Address, uint8_t *pu8Data)
{
    DISABLE_INTERRUPT();                      //关总中断
    uint8_t u8Ack;

    PCF8563_Device_I2C_Start();                                                                                           //产生起始信号
    PCF8563_Device_I2C_WriteByte(READ_ADDRESS);                                               //发送设备寻址字节
    u8Ack = PCF8563_Device_I2C_ReadBit();                                                                                //读取从设备回复信息

    if(u8Ack == I2C_NAK)
    {
        PCF8563_Device_I2C_Stop();                                                                                       //NAK则发出停止信号

        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    //使用读模式传输模式2(0100)
    PCF8563_Device_I2C_WriteByte((uint8_t)u8Address);                                                                    //发送读取的第一个寄存器地址
    u8Ack = PCF8563_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        PCF8563_Device_I2C_Stop();                                                                                       //NAK则发出停止信号

        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    *pu8Data = PCF8563_Device_I2C_ReadByte();                                                                            //读取回复数据
    PCF8563_Device_I2C_NACK();                                                                                           //回复NACK
    PCF8563_Device_I2C_Stop();                                                                                           //读操作执行完毕，产生停止信号

    ENABLE_INTERRUPT();
    return STATUS_TRUE;
}

/***********************************************************************************************************************
 功能：PCF8563发送时间
************************************************************************************************************************/
bool_t PCF8563_Device_Write_Time(PCF8563_TimeInf_t stTime)
{
    DISABLE_INTERRUPT();                                                                                         //关总中断

    uint8_t u8Ack;                                                                                               //使用写模式传输模式0000

    PCF8563_Device_I2C_Start();                                                                                  //产生起始信号

    PCF8563_Device_I2C_WriteByte(WRITE_ADDRESS);                                                                 //发送设备寻址字节

    u8Ack = PCF8563_Device_I2C_ReadBit();                                                                        //读取从设备回复信息

    if(u8Ack == I2C_NAK)
    {
        PCF8563_Device_I2C_Stop();                                                                               //NAK则发出停止信号
        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    PCF8563_Device_I2C_WriteByte(PCF8563_ADDRESS_SEC_REG_ADDR);                                                  //发送读取的第一个寄存器地址

    u8Ack = PCF8563_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        PCF8563_Device_I2C_Stop();                                                                               //NAK则发出停止信号
        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    stTime.u8Sec &= 0x7F;
    PCF8563_Device_I2C_WriteByte(stTime.u8Sec);                                                                     //写入一个字节的数据

    u8Ack = PCF8563_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        PCF8563_Device_I2C_Stop();                                                                               //NAK则发出停止信号
        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    stTime.u8Min &= 0x7F;
    PCF8563_Device_I2C_WriteByte(stTime.u8Min);                                                                     //写入一个字节的数据

    u8Ack = PCF8563_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        PCF8563_Device_I2C_Stop();                                                                               //NAK则发出停止信号
        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    stTime.u8Hour &= 0x3F;
    PCF8563_Device_I2C_WriteByte(stTime.u8Hour);                                                                     //写入一个字节的数据

    u8Ack = PCF8563_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        PCF8563_Device_I2C_Stop();                                                                               //NAK则发出停止信号
        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    stTime.u8Day &= 0x3F;
    PCF8563_Device_I2C_WriteByte(stTime.u8Day);                                                                     //写入一个字节的数据

    u8Ack = PCF8563_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        PCF8563_Device_I2C_Stop();                                                                               //NAK则发出停止信号
        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    stTime.u8Week &= 0x07;
    PCF8563_Device_I2C_WriteByte(stTime.u8Week);                                                                     //写入一个字节的数据

    u8Ack = PCF8563_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        PCF8563_Device_I2C_Stop();                                                                               //NAK则发出停止信号
        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    stTime.u8Month &= 0x1F;

    if(stTime.u8YearH == 0x20)
    {
        stTime.u8Month &= 0x7F;
    }
    else if(stTime.u8YearH == 0x21)
    {
        stTime.u8Month |= 0x80;
    }

    PCF8563_Device_I2C_WriteByte(stTime.u8Month);                                                                     //写入一个字节的数据

    u8Ack = PCF8563_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        PCF8563_Device_I2C_Stop();                                                                               //NAK则发出停止信号
        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    PCF8563_Device_I2C_WriteByte(stTime.u8YearL);                                                                     //写入一个字节的数据
    u8Ack = PCF8563_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        PCF8563_Device_I2C_Stop();                                                                               //NAK则发出停止信号
        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }                                                                                                             //写操作执行完毕，产生停止信号

    PCF8563_Device_I2C_Stop();

    ENABLE_INTERRUPT();
    return STATUS_TRUE;
}

/***********************************************************************************************************************
 功能：PCF8563读取时间
************************************************************************************************************************/
bool_t PCF8563_Device_Read_Time(PCF8563_TimeInf_t *pTime)
{
    DISABLE_INTERRUPT();                      //关总中断

    uint8_t u8Ack;
    uint8_t u8Temp;

    PCF8563_Device_I2C_Start();                                                                                           //产生起始信号
    PCF8563_Device_I2C_WriteByte(WRITE_ADDRESS);                                               //发送设备寻址字节

    u8Ack = PCF8563_Device_I2C_ReadBit();                                                                                //读取从设备回复信息

    if(u8Ack == I2C_NAK)
    {
        PCF8563_Device_I2C_Stop();                                                                                       //NAK则发出停止信号
        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    PCF8563_Device_I2C_WriteByte(PCF8563_ADDRESS_SEC_REG_ADDR);                                                                 //发送读取的第一个寄存器地址

    u8Ack = PCF8563_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        PCF8563_Device_I2C_Stop();                                                                                       //NAK则发出停止信号
        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    PCF8563_Device_I2C_Start();                                                                                           //产生起始信号

    PCF8563_Device_I2C_WriteByte(READ_ADDRESS);                                               //发送设备寻址字节

    u8Ack = PCF8563_Device_I2C_ReadBit();                                                                                //读取从设备回复信息

    if(u8Ack == I2C_NAK)
    {
        PCF8563_Device_I2C_Stop();                                                                                       //NAK则发出停止信号

        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    pTime->u8Sec = PCF8563_Device_I2C_ReadByte() & 0x7F;            //秒                                                                    //读取回复数据
    PCF8563_Device_I2C_ACK();

    pTime->u8Min = PCF8563_Device_I2C_ReadByte() & 0x7F;            //分                                                                //读取回复数据
    PCF8563_Device_I2C_ACK();

    pTime->u8Hour = PCF8563_Device_I2C_ReadByte() & 0x3F;            //时
    PCF8563_Device_I2C_ACK();

    pTime->u8Day = PCF8563_Device_I2C_ReadByte() & 0x3F;            //日
    PCF8563_Device_I2C_ACK();

    pTime->u8Week = PCF8563_Device_I2C_ReadByte() & 0x07;            //星期
    PCF8563_Device_I2C_ACK();

    u8Temp = PCF8563_Device_I2C_ReadByte();                          //月
    PCF8563_Device_I2C_ACK();
    pTime->u8Month = u8Temp & 0x1F;

    if((u8Temp & 0x80) == 0)
    {
        pTime->u8YearH = 0x20;
    }
    else
    {
        pTime->u8YearH = 0x21;
    }

    pTime->u8YearL = PCF8563_Device_I2C_ReadByte();            //年
    PCF8563_Device_I2C_NACK();                                                                                           //回复NACK

    PCF8563_Device_I2C_Stop();                                                                                             //读操作执行完毕，产生停止信号

    ENABLE_INTERRUPT();
    return STATUS_TRUE;

}

int8_t checkCalendar(PCF8563_TimeInf_t stTime)
{
    int8_t timeErr = 0;

    if((stTime.u8YearH < 0x20) || (stTime.u8YearH > 0x21))
        timeErr = -1;

    if((stTime.u8YearL >> 4) > 9 || (stTime.u8YearL & 0x0F) > 9)
        timeErr = -1;

    else if((stTime.u8Month >> 4) > 1 || (stTime.u8Month & 0x0F) > 9)
        timeErr = -1;
    else if(stTime.u8Month > 0x12 || stTime.u8Month == 0)
        timeErr = -1;

    else if((stTime.u8Day >> 4) > 3 || (stTime.u8Day & 0x0F) > 9)
        timeErr = -1;
    else if(stTime.u8Day > 0x31 || stTime.u8Day == 0)
        timeErr = -1;

    else if((stTime.u8Hour >> 4) > 2 || (stTime.u8Hour & 0x0F) > 9)
        timeErr = -1;
    else if(stTime.u8Hour > 0x23)
        timeErr = -1;

    else if((stTime.u8Min >> 4) > 5 || (stTime.u8Min & 0x0F) > 9)
        timeErr = -1;
    else if(stTime.u8Min > 0x59)
        timeErr = -1;

    else if((stTime.u8Sec >> 4) > 5 || (stTime.u8Sec & 0x0F) > 9)
        timeErr = -1;
    else if(stTime.u8Sec > 0x59)
        timeErr = -1;

    return timeErr;
}

void PCF8563_Device_Get_Time(PCF8563_TimeInf_t *pGetTime)
{
    PCF8563_TimeInf_t stGetData1;
    PCF8563_TimeInf_t stGetData2;
    memset(&stGetData1, 0, sizeof(PCF8563_TimeInf_t));
    memset(&stGetData2, 0, sizeof(PCF8563_TimeInf_t));

    PCF8563_Device_Read_Time(&stGetData1);

    if(checkCalendar(stGetData1)  != 0)
    {
        return;
    }

    PCF8563_Device_Read_Time(&stGetData2);

    if(checkCalendar(stGetData2)  != 0)
    {
        return;
    }

    if(memcmp(&stGetData1, &stGetData2, 7) == 0)
    {
        pGetTime->u8YearH = PCF8563_Device_BCD_to_Byte(stGetData1.u8YearH);
        pGetTime->u8YearL = PCF8563_Device_BCD_to_Byte(stGetData1.u8YearL);
        pGetTime->u8Month = PCF8563_Device_BCD_to_Byte(stGetData1.u8Month);
        pGetTime->u8Week  = PCF8563_Device_BCD_to_Byte(stGetData1.u8Week);
        pGetTime->u8Day   = PCF8563_Device_BCD_to_Byte(stGetData1.u8Day);
        pGetTime->u8Hour  = PCF8563_Device_BCD_to_Byte(stGetData1.u8Hour);
        pGetTime->u8Min   = PCF8563_Device_BCD_to_Byte(stGetData1.u8Min);
        pGetTime->u8Sec   = PCF8563_Device_BCD_to_Byte(stGetData1.u8Sec);
    }
}

void PCF8563_Device_Set_Time(PCF8563_TimeInf_t stSetTime)
{
    PCF8563_TimeInf_t stTime;
    memset(&stTime, 0, sizeof(PCF8563_TimeInf_t));

    stTime.u8YearH = PCF8563_Device_Byte_to_BCD(stSetTime.u8YearH);
    stTime.u8YearL = PCF8563_Device_Byte_to_BCD(stSetTime.u8YearL);
    stTime.u8Month = PCF8563_Device_Byte_to_BCD(stSetTime.u8Month);
    stTime.u8Week = PCF8563_Device_Byte_to_BCD(stSetTime.u8Week);
    stTime.u8Day = PCF8563_Device_Byte_to_BCD(stSetTime.u8Day);
    stTime.u8Hour = PCF8563_Device_Byte_to_BCD(stSetTime.u8Hour);
    stTime.u8Min = PCF8563_Device_Byte_to_BCD(stSetTime.u8Min);
    stTime.u8Sec = PCF8563_Device_Byte_to_BCD(stSetTime.u8Sec);

    if(checkCalendar(stTime) != 0)
    {
        return;
    }

    PCF8563_Device_Write_Time(stTime);
}

void PCF8563_Device_Init(void)
{
    PCF8563_Device_Write_Data(PCF8563_ADDRESS_CTRL1_REG_ADDR, 0x00);
    PCF8563_Device_Write_Data(PCF8563_ADDRESS_CTRL2_REG_ADDR, 0x00);
    PCF8563_Device_Write_Data(PCF8563_ADDRESS_ADJ_REG_ADDR, 0x00);
}

void PCF8563_Device_InitVar(void)
{
    ;
}
#endif
/***********************************************************************************************************************
* * Copyright (c)  CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
