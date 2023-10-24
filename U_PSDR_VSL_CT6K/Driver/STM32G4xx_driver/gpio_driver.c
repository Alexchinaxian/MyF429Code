/***********************************************************************************************************************
* Copyright (c)  , CVTE
* ***********************************************************************************************************************
* 文件名     : gpio_driver.c
* 用途       :
************************************************************************************************************************/

#include "gpio_driver.h"

/***********************************************************************************************************************
Global variables and funtions
************************************************************************************************************************/

typedef struct
{
    GPIO_TypeDef *ptGpiox;
    uint32_t u32GpioPin;
    uint32_t u32OutputType;
    uint32_t u32Pull;
} GPIO_Output_Port_t;

typedef struct
{
    GPIO_TypeDef *ptGpiox;
    uint32_t u32GpioPin;
    uint32_t u32Pull;
} GPIO_Input_Port_t;

//输出GPIO初始化结构体，可配置表
static GPIO_Output_Port_t ptGpioOutputPortTable[] =
{
    {.ptGpiox = PR_GPIOF, .u32GpioPin = PR_GPIO_PIN_13, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //LED_GRID_Pin
    {.ptGpiox = PR_GPIOF, .u32GpioPin = PR_GPIO_PIN_12, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //LED_GEN_Pin
    {.ptGpiox = PR_GPIOB, .u32GpioPin = PR_GPIO_PIN_13, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //Reserved
    {.ptGpiox = PR_GPIOB, .u32GpioPin = PR_GPIO_PIN_14, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //LED_FAULT_Pin

    {.ptGpiox = PR_GPIOB, .u32GpioPin = PR_GPIO_PIN_11, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //LCD_CS1_Pin
    {.ptGpiox = PR_GPIOB, .u32GpioPin = PR_GPIO_PIN_12, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //LCD_CS2_Pin
    {.ptGpiox = PR_GPIOC, .u32GpioPin = PR_GPIO_PIN_7,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //LCD_POWER_Pin
    {.ptGpiox = PR_GPIOD, .u32GpioPin = PR_GPIO_PIN_8,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //LCD_D0_Pin
    {.ptGpiox = PR_GPIOD, .u32GpioPin = PR_GPIO_PIN_9,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //LCD_D1_Pin
    {.ptGpiox = PR_GPIOD, .u32GpioPin = PR_GPIO_PIN_10, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //LCD_D2_Pin
    {.ptGpiox = PR_GPIOD, .u32GpioPin = PR_GPIO_PIN_11, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //LCD_D3_Pin
    {.ptGpiox = PR_GPIOD, .u32GpioPin = PR_GPIO_PIN_12, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //LCD_D4_Pin
    {.ptGpiox = PR_GPIOD, .u32GpioPin = PR_GPIO_PIN_13, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //LCD_D5_Pin
    {.ptGpiox = PR_GPIOD, .u32GpioPin = PR_GPIO_PIN_14, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //LCD_D6_Pin
    {.ptGpiox = PR_GPIOD, .u32GpioPin = PR_GPIO_PIN_15, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //LCD_D7_Pin
    {.ptGpiox = PR_GPIOA, .u32GpioPin = PR_GPIO_PIN_10, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //LCD_RS_Pin
    {.ptGpiox = PR_GPIOA, .u32GpioPin = PR_GPIO_PIN_11, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //LCD_RW_Pin
    {.ptGpiox = PR_GPIOA, .u32GpioPin = PR_GPIO_PIN_12, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //LCD_E_Pin
    {.ptGpiox = PR_GPIOA, .u32GpioPin = PR_GPIO_PIN_15, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_UP},     //LCD_RST_Pin
    {.ptGpiox = PR_GPIOC, .u32GpioPin = PR_GPIO_PIN_9,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //LCD_LEDK_Pin
    
    {.ptGpiox = PR_GPIOD, .u32GpioPin = PR_GPIO_PIN_0,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //DRY_RLY1_Pin
    {.ptGpiox = PR_GPIOD, .u32GpioPin = PR_GPIO_PIN_1,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //DRY_RLY2_Pin
    
    {.ptGpiox = PR_GPIOD, .u32GpioPin = PR_GPIO_PIN_4,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //BMS_TEN_Pin
    {.ptGpiox = PR_GPIOE, .u32GpioPin = PR_GPIO_PIN_3,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //METER_TEN_Pin
    {.ptGpiox = PR_GPIOE, .u32GpioPin = PR_GPIO_PIN_4,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //PCS_TEN_Pin
    {.ptGpiox = PR_GPIOE, .u32GpioPin = PR_GPIO_PIN_2,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //WIFI/GPRS_TEN_Pin
    {.ptGpiox = PR_GPIOE, .u32GpioPin = PR_GPIO_PIN_7,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //AFCI_TEN_Pin

    {.ptGpiox = PR_GPIOB, .u32GpioPin = PR_GPIO_PIN_3, .u32OutputType = LL_GPIO_OUTPUT_OPENDRAIN,  .u32Pull = LL_GPIO_PULL_UP},     //I2C_SCL
    {.ptGpiox = PR_GPIOB, .u32GpioPin = PR_GPIO_PIN_4, .u32OutputType = LL_GPIO_OUTPUT_OPENDRAIN,  .u32Pull = LL_GPIO_PULL_UP},     //I2C_SDA
#if DEV_GD25QXX_NSS_HARD_MODE

#else
    {.ptGpiox = PR_GPIOE, .u32GpioPin = PR_GPIO_PIN_12, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_UP},     //SPI_NSS
#endif

//    {.ptGpiox = PR_GPIOE, .u32GpioPin = PR_GPIO_PIN_13, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //SPI_CLK
//    {.ptGpiox = PR_GPIOE, .u32GpioPin = PR_GPIO_PIN_15, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL,  .u32Pull = PR_GPIO_PULL_NO},     //SPI_MOSI
};

//输入GPIO初始化结构体，可配置表
static GPIO_Input_Port_t ptGpioInputPortTable[] =
{
    {.ptGpiox = PR_GPIOB, .u32GpioPin = PR_GPIO_PIN_15, .u32Pull = PR_GPIO_PULL_NO},    //KEY_UP_Pin
    {.ptGpiox = PR_GPIOA, .u32GpioPin = PR_GPIO_PIN_8,  .u32Pull = PR_GPIO_PULL_NO},      //KEY_ESC_Pin
    {.ptGpiox = PR_GPIOA, .u32GpioPin = PR_GPIO_PIN_9,  .u32Pull = PR_GPIO_PULL_NO},     //KEY_ENTER_Pin
    {.ptGpiox = PR_GPIOC, .u32GpioPin = PR_GPIO_PIN_6,  .u32Pull = PR_GPIO_PULL_NO},      //KEY_DOWN_Pin

//    {.ptGpiox = PR_GPIOE, .u32GpioPin = PR_GPIO_PIN_14, .u32Pull = PR_GPIO_PULL_NO},     //SPI_MISO
};

//模拟GPIO初始化结构体，可配置表
static GPIO_Input_Port_t ptGpioAnalogPortTable[] =
{
    {.ptGpiox = PR_GPIOA, .u32GpioPin = PR_GPIO_PIN_0,  .u32Pull = PR_GPIO_PULL_NO},    //ADC1_IN0      DRM0
    {.ptGpiox = PR_GPIOA, .u32GpioPin = PR_GPIO_PIN_1,  .u32Pull = PR_GPIO_PULL_NO},    //ADC1_IN1      DRM1/5
    {.ptGpiox = PR_GPIOA, .u32GpioPin = PR_GPIO_PIN_2,  .u32Pull = PR_GPIO_PULL_NO},    //ADC1_IN2      DRM2/6
    {.ptGpiox = PR_GPIOA, .u32GpioPin = PR_GPIO_PIN_3,  .u32Pull = PR_GPIO_PULL_NO},    //ADC1_IN3      DRM3/7
    {.ptGpiox = PR_GPIOA, .u32GpioPin = PR_GPIO_PIN_4,  .u32Pull = PR_GPIO_PULL_NO},    //ADC1_IN4      DRM4/8
    {.ptGpiox = PR_GPIOA, .u32GpioPin = PR_GPIO_PIN_5,  .u32Pull = PR_GPIO_PULL_NO},    //ADC1_IN5      AMP.T
    {.ptGpiox = PR_GPIOA, .u32GpioPin = PR_GPIO_PIN_6,  .u32Pull = PR_GPIO_PULL_NO},    //ADC1_IN6      INVIGBT.T
    {.ptGpiox = PR_GPIOA, .u32GpioPin = PR_GPIO_PIN_7,  .u32Pull = PR_GPIO_PULL_NO},    //ADC1_IN7      DCDC_IGBT.T
};

//未使用GPIO初始化结构体，可配置表
static GPIO_Output_Port_t ptGpioUnusedPortTable[] =
{
    {.ptGpiox = PR_GPIOB, .u32GpioPin = PR_GPIO_PIN_0,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN},    
    {.ptGpiox = PR_GPIOB, .u32GpioPin = PR_GPIO_PIN_1,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN},    
    {.ptGpiox = PR_GPIOB, .u32GpioPin = PR_GPIO_PIN_2,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN},    
    {.ptGpiox = PR_GPIOB, .u32GpioPin = PR_GPIO_PIN_5,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN},    
    {.ptGpiox = PR_GPIOB, .u32GpioPin = PR_GPIO_PIN_10, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN},    
    {.ptGpiox = PR_GPIOC, .u32GpioPin = PR_GPIO_PIN_0,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN},    
    {.ptGpiox = PR_GPIOC, .u32GpioPin = PR_GPIO_PIN_1,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN},   
    {.ptGpiox = PR_GPIOC, .u32GpioPin = PR_GPIO_PIN_12, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN}, 
    {.ptGpiox = PR_GPIOC, .u32GpioPin = PR_GPIO_PIN_13, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN},   
    {.ptGpiox = PR_GPIOF, .u32GpioPin = PR_GPIO_PIN_11, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN},
    {.ptGpiox = PR_GPIOF, .u32GpioPin = PR_GPIO_PIN_10, .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN},
    {.ptGpiox = PR_GPIOF, .u32GpioPin = PR_GPIO_PIN_9,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN},
    {.ptGpiox = PR_GPIOF, .u32GpioPin = PR_GPIO_PIN_8,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN},
    {.ptGpiox = PR_GPIOF, .u32GpioPin = PR_GPIO_PIN_7,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN},
    {.ptGpiox = PR_GPIOF, .u32GpioPin = PR_GPIO_PIN_6,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN},
    {.ptGpiox = PR_GPIOF, .u32GpioPin = PR_GPIO_PIN_5,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN},
    {.ptGpiox = PR_GPIOF, .u32GpioPin = PR_GPIO_PIN_4,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN},
    {.ptGpiox = PR_GPIOF, .u32GpioPin = PR_GPIO_PIN_3,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN},
    {.ptGpiox = PR_GPIOE, .u32GpioPin = PR_GPIO_PIN_6,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN},    
    {.ptGpiox = PR_GPIOE, .u32GpioPin = PR_GPIO_PIN_5,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN},
    {.ptGpiox = PR_GPIOE, .u32GpioPin = PR_GPIO_PIN_1,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN},
    {.ptGpiox = PR_GPIOE, .u32GpioPin = PR_GPIO_PIN_0,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN}, 
    {.ptGpiox = PR_GPIOD, .u32GpioPin = PR_GPIO_PIN_7,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN},
    {.ptGpiox = PR_GPIOD, .u32GpioPin = PR_GPIO_PIN_2,  .u32OutputType = PR_GPIO_OUTPUT_PUSHPULL, .u32Pull = PR_GPIO_PULL_DOWN},    
};

#define GPIO_OUTPUT_PORT_NUMBER     (sizeof(ptGpioOutputPortTable) / sizeof(GPIO_Output_Port_t))
#define GPIO_INPUT_PORT_NUMBER      (sizeof(ptGpioInputPortTable) / sizeof(GPIO_Input_Port_t))
#define GPIO_ANALOG_PORT_NUMBER     (sizeof(ptGpioAnalogPortTable) / sizeof(GPIO_Input_Port_t))
#define GPIO_UNUSED_PORT_NUMBER     (sizeof(ptGpioUnusedPortTable) / sizeof(GPIO_Output_Port_t))
    
/***********************************************************************************************************************
 功能：设置GPIO模式为输出/输入/复用/模拟
************************************************************************************************************************/
void GPIO_Driver_SetPinMode(GPIO_TypeDef *ptGPIOx, uint32_t u32GpioPin, uint32_t u32Mode)
{
    LL_GPIO_SetPinMode(ptGPIOx, u32GpioPin, u32Mode);
}

/***********************************************************************************************************************
 功能：写GPIO的输出端口值
************************************************************************************************************************/
void GPIO_Driver_WriteOutputPin(GPIO_TypeDef *ptGPIOx, uint32_t u32GpioPin, uint32_t u32Value)
{
    if(u32Value)
    {
        LL_GPIO_SetOutputPin(ptGPIOx, u32GpioPin);
    }
    else
    {
        LL_GPIO_ResetOutputPin(ptGPIOx, u32GpioPin);
    }
}

/***********************************************************************************************************************
 功能：读GPIO的输出端口值
************************************************************************************************************************/
uint32_t GPIO_Driver_ReadOutputPin(GPIO_TypeDef *ptGPIOx, uint32_t u32GpioPin)
{
    return (LL_GPIO_ReadOutputPort(ptGPIOx) & u32GpioPin);
}

/***********************************************************************************************************************
 功能：翻转GPIO的输出端口值
************************************************************************************************************************/
void GPIO_Driver_ToggleOutputPin(GPIO_TypeDef *ptGPIOx, uint32_t u32GpioPin)
{
    LL_GPIO_TogglePin(ptGPIOx, u32GpioPin);
}

/***********************************************************************************************************************
 功能：读GPIO的输入端口值
************************************************************************************************************************/
uint32_t GPIO_Driver_ReadInputPin(GPIO_TypeDef *ptGPIOx, uint32_t u32GpioPin)
{
    return (LL_GPIO_ReadInputPort(ptGPIOx) & u32GpioPin);
}

/***********************************************************************************************************************
 功能：GPIO使能时钟
************************************************************************************************************************/
static void GPIO_EnablePeriphClockCmd(void)
{
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOC);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOD);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOE);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOF);
}

/***********************************************************************************************************************
 功能：配置GPIO初始化
************************************************************************************************************************/
void GPIO_Driver_Initial(void)
{
    uint8_t i;
    LL_GPIO_InitTypeDef GPIO_InitOutputStruct = {0};
    LL_GPIO_InitTypeDef GPIO_InitInputStruct = {0};

    //初始化GPIO时钟
    GPIO_EnablePeriphClockCmd();

    //复位GPIO输出状态
    
    //预留
    
    //初始化输出GPIO
    GPIO_InitOutputStruct.Mode = PR_GPIO_MODE_OUTPUT;
    for(i = 0; i < GPIO_OUTPUT_PORT_NUMBER; i++)
    {
        GPIO_InitOutputStruct.Pin = ptGpioOutputPortTable[i].u32GpioPin;
        GPIO_InitOutputStruct.Speed = LL_GPIO_SPEED_FREQ_LOW ;
        GPIO_InitOutputStruct.OutputType = ptGpioOutputPortTable[i].u32OutputType;
        GPIO_InitOutputStruct.Pull = ptGpioOutputPortTable[i].u32Pull;
        LL_GPIO_Init(ptGpioOutputPortTable[i].ptGpiox, &GPIO_InitOutputStruct);
    }

    //初始化输入GPIO
    GPIO_InitInputStruct.Mode = PR_GPIO_MODE_INPUT;
    for(i = 0; i < GPIO_INPUT_PORT_NUMBER; i++)
    {
        GPIO_InitInputStruct.Pin = ptGpioInputPortTable[i].u32GpioPin;
        GPIO_InitInputStruct.Pull = ptGpioInputPortTable[i].u32Pull;
        LL_GPIO_Init(ptGpioInputPortTable[i].ptGpiox, &GPIO_InitInputStruct);
    }

    //初始化模拟GPIO
    GPIO_InitInputStruct.Mode = PR_GPIO_MODE_ANALOG;
    for(i = 0; i < GPIO_ANALOG_PORT_NUMBER; i++)
    {
        GPIO_InitInputStruct.Pin = ptGpioAnalogPortTable[i].u32GpioPin;
        GPIO_InitInputStruct.Pull = ptGpioAnalogPortTable[i].u32Pull;
        LL_GPIO_Init(ptGpioAnalogPortTable[i].ptGpiox, &GPIO_InitInputStruct);
    }
    
    //初始化未使用GPIO
    GPIO_InitOutputStruct.Mode = PR_GPIO_MODE_OUTPUT;
    for(i = 0; i < GPIO_UNUSED_PORT_NUMBER; i++)
    {
        GPIO_InitOutputStruct.Pin = ptGpioUnusedPortTable[i].u32GpioPin;
        GPIO_InitOutputStruct.Speed = LL_GPIO_SPEED_FREQ_LOW ;
        GPIO_InitOutputStruct.OutputType = ptGpioUnusedPortTable[i].u32OutputType;
        GPIO_InitOutputStruct.Pull = ptGpioUnusedPortTable[i].u32Pull;
        LL_GPIO_Init(ptGpioUnusedPortTable[i].ptGpiox, &GPIO_InitOutputStruct);
    }
}

/***********************************************************************************************************************
* Copyright (c)  CVTE All rights reserved.  * * * END OF FILE
************************************************************************************************************************/
