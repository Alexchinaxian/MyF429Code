#ifndef __SIMI2C_DRIVER_H
#define __SIMI2C_DRIVER_H

#include "MCU.h"
#include "gpio_driver.h"

typedef enum
{
    I2C_ACK = 0,
    I2C_NAK,
} I2C_Reply_t;

typedef enum
{
    SIMI2C_TYPE_INIT = 0,
    SIMI2C_TYPE_BL24C04F = SIMI2C_TYPE_INIT,
    SIMI2C_TYPE_AW9523B,
    SIMI2C_TYPE_MAX,
} SimI2C_Type_t;

extern void SimI2C_Driver_Start(SimI2C_Type_t tSimI2C_Type);
extern void SimI2C_Driver_Stop(SimI2C_Type_t tSimI2C_Type);

extern void SimI2C_Driver_WriteBit(SimI2C_Type_t tSimI2C_Type, uint8_t u8Data);
extern uint8_t SimI2C_Driver_ReadBit(SimI2C_Type_t tSimI2C_Type);

extern void SimI2C_Driver_WriteByte(SimI2C_Type_t tSimI2C_Type, uint8_t u8Data);
extern uint8_t SimI2C_Driver_ReadByte(SimI2C_Type_t tSimI2C_Type);

#endif
