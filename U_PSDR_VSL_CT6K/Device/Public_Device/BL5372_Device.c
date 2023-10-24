/***********************************************************************************************************************
* Copyright (c) , CVTE
* All rights reserved.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
* 文件    : BL5372_Device.c
* 用途     :RTC时钟芯片设备驱动文件
***********************************************************************************************************************/
#include "MCU.h"
#include "HeadFile.h"
#include "BL5372_Device.h"

#if (RTCSIGNAL_SOURCE == RTC_BL5372_MOUDLE)

/***********************************************************************************************************************
Global variables and funtions
************************************************************************************************************************/

/***********************************************************************************************************************
 功能：IIC发送start信号
************************************************************************************************************************/
void BL5372_Device_I2C_Start(void)
{
    BL5372_I2C_SDA_SET_IO_MODE(PR_GPIO_MODE_OUTPUT);                                                                    //设置SDA I/O口为输出
    BL5372_I2C_SDA_WRITE_IO_STATUS(IO_HIGH);                                                                            //SDA 高电平
    BL5372_I2C_SCL_WRITE_IO_STATUS(IO_HIGH);                                                                            //SCL 高电平
    Delay_us(BL5372_I2C_DELAY_US);
    BL5372_I2C_SDA_WRITE_IO_STATUS(IO_LOW);                                                                             //SDA 低电平
    Delay_us(BL5372_I2C_DELAY_US);
    BL5372_I2C_SCL_WRITE_IO_STATUS(IO_LOW);                                                                             //SCL低电平
    Delay_us(BL5372_I2C_DELAY_US);
}

/***********************************************************************************************************************
 功能：IIC发送stop信号
************************************************************************************************************************/
void BL5372_Device_I2C_Stop(void)
{
    BL5372_I2C_SDA_SET_IO_MODE(PR_GPIO_MODE_OUTPUT);                                                                    //设置SDA I/O口为输出
    BL5372_I2C_SDA_WRITE_IO_STATUS(IO_LOW);                                                                             //SDA 低电平
    Delay_us(BL5372_I2C_DELAY_US);
    BL5372_I2C_SCL_WRITE_IO_STATUS(IO_HIGH);                                                                            //SCL 高电平
    Delay_us(BL5372_I2C_DELAY_US);
    BL5372_I2C_SDA_WRITE_IO_STATUS(IO_HIGH);                                                                            //SDA 高电平
    Delay_us(BL5372_I2C_DELAY_US);
}

void BL5372_Device_I2C_ACK(void)
{
    BL5372_I2C_SDA_SET_IO_MODE(PR_GPIO_MODE_OUTPUT);                                                                    //设置SDA I/O口为输出
    BL5372_I2C_SCL_WRITE_IO_STATUS(IO_LOW);                                                                             //SCL 低电平
    BL5372_I2C_SDA_WRITE_IO_STATUS(IO_LOW);                                                                             //SDA 低电平
    Delay_us(BL5372_I2C_DELAY_US);
    BL5372_I2C_SCL_WRITE_IO_STATUS(IO_HIGH);                                                                            //SCL 高电平
    Delay_us(BL5372_I2C_DELAY_US);
    BL5372_I2C_SCL_WRITE_IO_STATUS(IO_LOW);                                                                             //SCL 低电平
    Delay_us(BL5372_I2C_DELAY_US);
    BL5372_I2C_SDA_WRITE_IO_STATUS(IO_HIGH);                                                                             //SDA 低电平
}

void BL5372_Device_I2C_NACK(void)
{
    BL5372_I2C_SDA_SET_IO_MODE(PR_GPIO_MODE_OUTPUT);                                                                    //设置SDA I/O口为输出
    BL5372_I2C_SCL_WRITE_IO_STATUS(IO_LOW);                                                                             //SCL 低电平
    BL5372_I2C_SDA_WRITE_IO_STATUS(IO_HIGH);                                                                             //SDA 低电平
    Delay_us(BL5372_I2C_DELAY_US);
    BL5372_I2C_SCL_WRITE_IO_STATUS(IO_HIGH);                                                                            //SCL 高电平
    Delay_us(BL5372_I2C_DELAY_US);
    BL5372_I2C_SCL_WRITE_IO_STATUS(IO_LOW);                                                                             //SCL 低电平
    Delay_us(BL5372_I2C_DELAY_US);
}
/***********************************************************************************************************************
 功能：IIC发送1位数据
************************************************************************************************************************/
void BL5372_Device_I2C_WriteBit(uint8_t u8Data)
{
    BL5372_I2C_SDA_SET_IO_MODE(PR_GPIO_MODE_OUTPUT);                                                                    //设置SDA I/O口为输出
    BL5372_I2C_SCL_WRITE_IO_STATUS(IO_LOW);                                                                             //SCL 低电平
    Delay_us(BL5372_I2C_DELAY_US);
    BL5372_I2C_SDA_WRITE_IO_STATUS(!!u8Data);                                                                           //SDA 数据，两次取反，uint8_t转换为bool
    Delay_us(BL5372_I2C_DELAY_US);
    BL5372_I2C_SCL_WRITE_IO_STATUS(IO_HIGH);                                                                            //SCL 高电平
    Delay_us(BL5372_I2C_DELAY_US);
}

/***********************************************************************************************************************
 功能：IIC读取1位数据
************************************************************************************************************************/
uint8_t BL5372_Device_I2C_ReadBit(void)
{
    uint8_t u8Data;
    BL5372_I2C_SCL_WRITE_IO_STATUS(IO_LOW);                                                                             //SCL 低电平
    BL5372_I2C_SDA_SET_IO_MODE(PR_GPIO_MODE_INPUT);                                                                     //设置SDA I/O口为输入
    Delay_us(BL5372_I2C_DELAY_US);
    BL5372_I2C_SCL_WRITE_IO_STATUS(IO_HIGH);                                                                            //SCL 高电平
    Delay_us(BL5372_I2C_DELAY_US);
    u8Data = BL5372_I2C_SDA_READ_IO_STATUS();
    Delay_us(BL5372_I2C_DELAY_US);
    BL5372_I2C_SCL_WRITE_IO_STATUS(IO_LOW);

    return (!!u8Data);
}

/***********************************************************************************************************************
 功能：IIC发送1个字节 从高位往低位发
************************************************************************************************************************/
void BL5372_Device_I2C_WriteByte(uint8_t u8Data)
{
    uint8_t i;

    for(i = 0; i < 8; i++)
    {
        BL5372_Device_I2C_WriteBit((u8Data & 0x80));
        u8Data <<= 1;
    }
}

/***********************************************************************************************************************
 功能：IIC读取1个字节 从高位往低位读
************************************************************************************************************************/
uint8_t BL5372_Device_I2C_ReadByte(void)
{
    uint8_t i, u8Data = 0;

    for(i = 0; i < 8; i++)
    {
        u8Data <<= 1;
        u8Data |= BL5372_Device_I2C_ReadBit();
    }

    return u8Data;
}

/***********************************************************************************************************************
 功能：十进制转为BCD码
***********************************************************************************************************************/
uint8_t BL5372_Device_Byte_to_BCD(uint8_t u8Value)
{
    return  (u8Value + (u8Value / 10) * 6);
}

/***********************************************************************************************************************
 功能：BCD码转为十进制
***********************************************************************************************************************/
uint8_t BL5372_Device_BCD_to_Byte(uint8_t u8Value)
{
    return (u8Value - (u8Value >> 4) * 6);
}

/***********************************************************************************************************************
 功能：BL5372写一个字节的数据
************************************************************************************************************************/
bool_t BL5372_Device_Write_Data(uint8_t u8Address, uint8_t u8Data)
{
    uint8_t u8Ack;
    DISABLE_INTERRUPT();                      //关总中断

    BL5372_Device_I2C_Start();                                                                                          //产生起始信号
    BL5372_Device_I2C_WriteByte(WRITE_MODE);                                                                            //发送设备寻址字节
    u8Ack = BL5372_Device_I2C_ReadBit();                                                                                //读取从设备回复信息

    if(u8Ack == I2C_NAK)
    {
        BL5372_Device_I2C_Stop();                                                                                       //NAK则发出停止信号

        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    BL5372_Device_I2C_WriteByte((uint8_t)((u8Address << 4) & 0xF0));                                                    //发送写入目标寄存器地址
    u8Ack = BL5372_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        BL5372_Device_I2C_Stop();                                                                                       //NAK则发出停止信号

        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    BL5372_Device_I2C_WriteByte((uint8_t)u8Data);                                                                       //写入一个字节的数据
    u8Ack = BL5372_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        BL5372_Device_I2C_Stop();                                                                                       //NAK则发出停止信号

        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    BL5372_Device_I2C_Stop();                                                                                           //写操作执行完毕，产生停止信号

    ENABLE_INTERRUPT();
    return STATUS_TRUE;
}

/***********************************************************************************************************************
 功能：BL5372读一个字节的数据
************************************************************************************************************************/
bool_t BL5372_Device_Read_Data(uint8_t u8Address, uint8_t *pu8Data)
{
    uint8_t u8Ack;
    DISABLE_INTERRUPT();                      //关总中断

    BL5372_Device_I2C_Start();                                                                                         //产生起始信号
    BL5372_Device_I2C_WriteByte(WRITE_MODE);                                                                           //发送设备寻址字节
    u8Ack = BL5372_Device_I2C_ReadBit();                                                                               //读取从设备回复信息

    if(u8Ack == I2C_NAK)
    {
        BL5372_Device_I2C_Stop();                                                                                      //NAK则发出停止信号

        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    //使用读模式传输模式2(0100)
    BL5372_Device_I2C_WriteByte(((u8Address << 4) & 0xF0) | 0x40);                                                   //发送读取的第一个寄存器地址
    u8Ack = BL5372_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        BL5372_Device_I2C_Stop();                                                                                       //NAK则发出停止信号

        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    *pu8Data = BL5372_Device_I2C_ReadByte();                                                                            //读取回复数据
    BL5372_Device_I2C_NACK();                                                                                           //回复NACK
    BL5372_Device_I2C_Stop();                                                                                           //读操作执行完毕，产生停止信号

    ENABLE_INTERRUPT();
    return STATUS_TRUE;
}

/***********************************************************************************************************************
 功能：BL5372设置时间
************************************************************************************************************************/
bool_t BL5372_Device_Write_Time(BL5372_TimeInf_t stTime)
{
    uint8_t u8Ack;
    DISABLE_INTERRUPT();                      //关总中断

    BL5372_Device_I2C_Start();                                                                                          //产生起始信号

    BL5372_Device_I2C_WriteByte(WRITE_MODE);                                                                           //发送设备写指令

    u8Ack = BL5372_Device_I2C_ReadBit();                                                                                //读取从设备回复响应信号

    if(u8Ack == I2C_NAK)
    {
        BL5372_Device_I2C_Stop();                                                                                       //NAK则发出停止信号
        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    BL5372_Device_I2C_WriteByte((BL5372_ADDRESS_SEC_REG_ADDR << 4) & 0xF0);                                             //发送写入的第一个寄存器地址

    u8Ack = BL5372_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        BL5372_Device_I2C_Stop();
        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    BL5372_Device_I2C_WriteByte(stTime.u8Sec);                                                                          //写入秒寄存器数据

    u8Ack = BL5372_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        BL5372_Device_I2C_Stop();
        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    BL5372_Device_I2C_WriteByte(stTime.u8Min);                                                                          //写入分寄存器数据

    u8Ack = BL5372_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        BL5372_Device_I2C_Stop();
        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    BL5372_Device_I2C_WriteByte(stTime.u8Hour);                                                                        //写入时寄存器数据

    u8Ack = BL5372_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        BL5372_Device_I2C_Stop();
        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    BL5372_Device_I2C_WriteByte(stTime.u8Week);                                                                        //写入周寄存器数据

    u8Ack = BL5372_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        BL5372_Device_I2C_Stop();
        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    BL5372_Device_I2C_WriteByte(stTime.u8Day);                                                                        //写入日寄存器数据

    u8Ack = BL5372_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        BL5372_Device_I2C_Stop();
        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    BL5372_Device_I2C_WriteByte(stTime.u8Month);                                                                      //写入月寄存器数据

    u8Ack = BL5372_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        BL5372_Device_I2C_Stop();
        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    BL5372_Device_I2C_WriteByte(stTime.u8Year);                                                                       //写入年寄存器数据
    u8Ack = BL5372_Device_I2C_ReadBit();

    if(u8Ack == I2C_NAK)
    {
        BL5372_Device_I2C_Stop();
        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    //写操作执行完毕，产生停止信号
    BL5372_Device_I2C_Stop();

    ENABLE_INTERRUPT();
    return STATUS_TRUE;
}

/***********************************************************************************************************************
 功能：BL5372读取时间
************************************************************************************************************************/
bool_t BL5372_Device_Read_Time(BL5372_TimeInf_t *pTime)
{
    uint8_t u8Ack;
    DISABLE_INTERRUPT();                      //关总中断

    BL5372_Device_I2C_Start();                                                                                         //产生起始信号
    BL5372_Device_I2C_WriteByte(READ_MODE);                                                                            //发送设备寻址字节

    u8Ack = BL5372_Device_I2C_ReadBit();                                                                                //读取从设备回复信息

    if(u8Ack == I2C_NAK)
    {
        BL5372_Device_I2C_Stop();                                                                                       //NAK则发出停止信号

        ENABLE_INTERRUPT();
        return STATUS_FALSE;
    }

    BL5372_Device_I2C_ReadByte();                                                                                       //读取回复数据 Ox0F CntL2
    BL5372_Device_I2C_ACK();

    pTime->u8Sec = BL5372_Device_I2C_ReadByte();                                                                        //读取回复数据 Ox00 秒
    BL5372_Device_I2C_ACK();

    pTime->u8Min = BL5372_Device_I2C_ReadByte();                                                                        //读取回复数据 Ox01 分
    BL5372_Device_I2C_ACK();

    pTime->u8Hour = BL5372_Device_I2C_ReadByte();                                                                       //读取回复数据 Ox02 时
    BL5372_Device_I2C_ACK();

    pTime->u8Week = BL5372_Device_I2C_ReadByte();                                                                       //读取回复数据 Ox03 周
    BL5372_Device_I2C_ACK();

    pTime->u8Day = BL5372_Device_I2C_ReadByte();                                                                        //读取回复数据 Ox04 日
    BL5372_Device_I2C_ACK();

    pTime->u8Month = BL5372_Device_I2C_ReadByte();                                                                      //读取回复数据 Ox05 月
    BL5372_Device_I2C_ACK();

    pTime->u8Year = BL5372_Device_I2C_ReadByte();                                                                       //读取回复数据 Ox06 年
    BL5372_Device_I2C_NACK();

    BL5372_Device_I2C_Stop();                                                                                           //读操作执行完毕，产生停止信号

    ENABLE_INTERRUPT();
    return STATUS_TRUE;
}

int8_t checkCalendar(BL5372_TimeInf_t stTime)
{
    int8_t timeErr = 0;

    if((stTime.u8Year >> 4) > 9 || (stTime.u8Year & 0x0F) > 9)
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

void BL5372_Device_Get_Time(BL5372_TimeInf_t *pGetTime)
{
    BL5372_TimeInf_t stGetData1;
    BL5372_TimeInf_t stGetData2;
    memset(&stGetData1, 0, sizeof(BL5372_TimeInf_t));
    memset(&stGetData2, 0, sizeof(BL5372_TimeInf_t));

    BL5372_Device_Read_Time(&stGetData1);

    if(checkCalendar(stGetData1) != 0)
    {
        return;
    }

    BL5372_Device_Read_Time(&stGetData2);

    if(checkCalendar(stGetData2) != 0)
    {
        return;
    }

    if(memcmp(&stGetData1, &stGetData2, 6) == 0)
    {
        pGetTime->u8Year = BL5372_Device_BCD_to_Byte(stGetData1.u8Year);
        pGetTime->u8Month = BL5372_Device_BCD_to_Byte(stGetData1.u8Month);
        pGetTime->u8Day = BL5372_Device_BCD_to_Byte(stGetData1.u8Day);
        pGetTime->u8Week = BL5372_Device_BCD_to_Byte(stGetData1.u8Week);
        pGetTime->u8Hour = BL5372_Device_BCD_to_Byte(stGetData1.u8Hour);
        pGetTime->u8Min = BL5372_Device_BCD_to_Byte(stGetData1.u8Min);
        pGetTime->u8Sec = BL5372_Device_BCD_to_Byte(stGetData1.u8Sec);
    }
}

void BL5372_Device_Set_Time(BL5372_TimeInf_t stSetTime)
{
    BL5372_TimeInf_t stTime;
    memset(&stTime, 0, sizeof(BL5372_TimeInf_t));

    stTime.u8Year = BL5372_Device_Byte_to_BCD(stSetTime.u8Year);
    stTime.u8Month = BL5372_Device_Byte_to_BCD(stSetTime.u8Month);
    stTime.u8Day = BL5372_Device_Byte_to_BCD(stSetTime.u8Day);
    stTime.u8Week = BL5372_Device_Byte_to_BCD(stSetTime.u8Week);
    stTime.u8Hour = BL5372_Device_Byte_to_BCD(stSetTime.u8Hour);
    stTime.u8Min = BL5372_Device_Byte_to_BCD(stSetTime.u8Min);
    stTime.u8Sec = BL5372_Device_Byte_to_BCD(stSetTime.u8Sec);

    if(checkCalendar(stTime) != 0)
    {
        return;
    }

    BL5372_Device_Write_Time(stTime);
}

void BL5372_Device_Init(void)
{
    uint8_t u8Cntrl1 = 0;
    uint8_t u8Cntrl2 = 0;

    BL5372_Device_Read_Data(BL5372_ADDRESS_CTRL1_REG_ADDR, &u8Cntrl1);
    BL5372_Device_Read_Data(BL5372_ADDRESS_CTRL2_REG_ADDR, &u8Cntrl2);

    if((u8Cntrl2 >> 4) != 2)
    {
        BL5372_Device_Write_Data(BL5372_ADDRESS_CTRL1_REG_ADDR, 0x00);
        BL5372_Device_Write_Data(BL5372_ADDRESS_CTRL2_REG_ADDR, 0x20);
    }
}

void BL5372_Device_InitVar(void)
{
    ;
}
#endif
/***********************************************************************************************************************
* * Copyright (c)  CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
