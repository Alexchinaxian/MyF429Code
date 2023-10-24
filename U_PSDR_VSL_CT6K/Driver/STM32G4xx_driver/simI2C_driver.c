/***********************************************************************************************************************
* Copyright (c) , CVTE
* All rights reserved.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
* 文件    : simI2C_driver.c
* 用途     : 模拟I2C驱动文件
***********************************************************************************************************************/

#include "simI2C_driver.h"
#include "PublicFunc.h"

/***********************************************************************************************************************
Global variables and funtions
************************************************************************************************************************/
typedef struct
{
    GPIO_TypeDef *ptGPIOx_SDA;
    GPIO_TypeDef *ptGPIOx_SCL;
    uint32_t u32GPIO_Pin_SDA;
    uint32_t u32GPIO_Pin_SCL;
} SimI2C_Table_t;

static const SimI2C_Table_t SimI2C_Preset_Table[SIMI2C_TYPE_MAX] =
{
    {DEV_EEPROM_SDA_PORT,   DEV_EEPROM_SCL_PORT,    DEV_EEPROM_SCL_PIN,     DEV_EEPROM_SDA_PIN},
    {DEV_BL5372_SDA_PORT,  DEV_BL5372_SCL_PORT,   DEV_BL5372_SCL_PIN,    DEV_BL5372_SDA_PIN},
};

//设置SDA的输入/输出模式
#define SIMI2C_SDA_SET_IO_MODE(SIMI2C_TYPE, IO_MODE)            (GPIO_Driver_SetPinMode(SimI2C_Preset_Table[SIMI2C_TYPE].ptGPIOx_SDA, SimI2C_Preset_Table[SIMI2C_TYPE].u32GPIO_Pin_SDA, IO_MODE))

//设置SCL/SDA的读写数据
#define SIMI2C_SCL_WRITE_IO_STATUS(SIMI2C_TYPE, IO_STATUS)      (GPIO_Driver_WriteOutputPin(SimI2C_Preset_Table[SIMI2C_TYPE].ptGPIOx_SCL, SimI2C_Preset_Table[SIMI2C_TYPE].u32GPIO_Pin_SCL, IO_STATUS))
#define SIMI2C_SDA_WRITE_IO_STATUS(SIMI2C_TYPE, IO_STATUS)      (GPIO_Driver_WriteOutputPin(SimI2C_Preset_Table[SIMI2C_TYPE].ptGPIOx_SDA, SimI2C_Preset_Table[SIMI2C_TYPE].u32GPIO_Pin_SDA, IO_STATUS))
#define SIMI2C_SDA_READ_IO_STATUS(SIMI2C_TYPE)                  (GPIO_Driver_ReadOutputPin(SimI2C_Preset_Table[SIMI2C_TYPE].ptGPIOx_SDA, SimI2C_Preset_Table[SIMI2C_TYPE].u32GPIO_Pin_SDA))

//设置忙延时等待2us
#define SIMI2C_DELAY_US                                         (2)

/***********************************************************************************************************************
 功能：IIC发送start信号
************************************************************************************************************************/
void SimI2C_Driver_Start(SimI2C_Type_t tSimI2C_Type)
{
    SIMI2C_SDA_SET_IO_MODE(tSimI2C_Type, PR_GPIO_MODE_OUTPUT);
    SIMI2C_SDA_WRITE_IO_STATUS(tSimI2C_Type, IO_HIGH);
    SIMI2C_SCL_WRITE_IO_STATUS(tSimI2C_Type, IO_HIGH);
    Delay_us(SIMI2C_DELAY_US);
    SIMI2C_SDA_WRITE_IO_STATUS(tSimI2C_Type, IO_LOW);
    Delay_us(SIMI2C_DELAY_US);
    SIMI2C_SCL_WRITE_IO_STATUS(tSimI2C_Type, IO_LOW);
    Delay_us(SIMI2C_DELAY_US);
}

/***********************************************************************************************************************
 功能：IIC发送stop信号
************************************************************************************************************************/
void SimI2C_Driver_Stop(SimI2C_Type_t tSimI2C_Type)
{
    SIMI2C_SDA_SET_IO_MODE(tSimI2C_Type, PR_GPIO_MODE_OUTPUT);
    SIMI2C_SDA_WRITE_IO_STATUS(tSimI2C_Type, IO_LOW);
    Delay_us(SIMI2C_DELAY_US);
    SIMI2C_SCL_WRITE_IO_STATUS(tSimI2C_Type, IO_HIGH);
    Delay_us(SIMI2C_DELAY_US);
    SIMI2C_SDA_WRITE_IO_STATUS(tSimI2C_Type, IO_HIGH);
    Delay_us(SIMI2C_DELAY_US);
}

/***********************************************************************************************************************
 功能：IIC发送1位数据
************************************************************************************************************************/
void SimI2C_Driver_WriteBit(SimI2C_Type_t tSimI2C_Type, uint8_t u8Data)
{
    SIMI2C_SDA_SET_IO_MODE(tSimI2C_Type, PR_GPIO_MODE_OUTPUT);
    SIMI2C_SCL_WRITE_IO_STATUS(tSimI2C_Type, IO_LOW);
    Delay_us(SIMI2C_DELAY_US);
    SIMI2C_SDA_WRITE_IO_STATUS(tSimI2C_Type, !!u8Data);
    Delay_us(SIMI2C_DELAY_US);
    SIMI2C_SCL_WRITE_IO_STATUS(tSimI2C_Type, IO_HIGH);
    Delay_us(SIMI2C_DELAY_US);
}

/***********************************************************************************************************************
 功能：IIC读取1位数据
************************************************************************************************************************/
uint8_t SimI2C_Driver_ReadBit(SimI2C_Type_t tSimI2C_Type)
{
    uint8_t u8Data;
    SIMI2C_SDA_SET_IO_MODE(tSimI2C_Type, PR_GPIO_MODE_INPUT);
    SIMI2C_SCL_WRITE_IO_STATUS(tSimI2C_Type, IO_LOW);
    Delay_us(SIMI2C_DELAY_US);
    SIMI2C_SDA_WRITE_IO_STATUS(tSimI2C_Type, IO_HIGH);
    Delay_us(SIMI2C_DELAY_US);
    u8Data = SIMI2C_SDA_READ_IO_STATUS(tSimI2C_Type);
    SIMI2C_SDA_WRITE_IO_STATUS(tSimI2C_Type, IO_LOW);

    return (!!u8Data);
}

/***********************************************************************************************************************
 功能：IIC发送1个字节 从高位往低位发
************************************************************************************************************************/
void SimI2C_Driver_WriteByte(SimI2C_Type_t tSimI2C_Type, uint8_t u8Data)
{
    uint8_t i;

    for(i = 0; i < 8; i++)
    {
        SimI2C_Driver_WriteBit(tSimI2C_Type, (u8Data & 0x80));
        u8Data <<= 1;
    }
}

/***********************************************************************************************************************
 功能：IIC读取1个字节 从高位往低位读
************************************************************************************************************************/
uint8_t SimI2C_Driver_ReadByte(SimI2C_Type_t tSimI2C_Type)
{
    uint8_t i, u8Data = 0;

    for(i = 0; i < 8; i++)
    {
        u8Data <<= 1;
        u8Data |= SimI2C_Driver_ReadBit(tSimI2C_Type);
    }

    return u8Data;
}
