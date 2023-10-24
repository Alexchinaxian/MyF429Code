#if 1

#include "Key_Device.h"
#include "BOARD_U_CNTL_VSL6K_A_STM32G0B1VET6.h"
#include "stm32g0xx_hal_gpio.h"

typedef struct
{
    uint16_t u16KeyValue;
    uint16_t u16GPIO_Pin;
    GPIO_TypeDef *ptGPIOx;
} KeyDevicePreset_t;

static KeyDevicePreset_t ptKeyDevicePreset[] =
{
    {DEV_KEY_UP,    DEV_KEY_UP_PIN,    DEV_KEY_UP_PORT},
    {DEV_KEY_DOWN,  DEV_KEY_DOWN_PIN,  DEV_KEY_DOWN_PORT},
    {DEV_KEY_ESC,   DEV_KEY_ESC_PIN,   DEV_KEY_ESC_PORT},
    {DEV_KEY_ENTER, DEV_KEY_ENTER_PIN, DEV_KEY_ENTER_PORT},
};

#define KEY_DEVICE_NUMBER_TOTAL  (sizeof(ptKeyDevicePreset)/sizeof(KeyDevicePreset_t))

uint16_t Key_Device_GetKeyValue(void)
{
    uint8_t i;
    uint16_t u16KeyValue = 0;
    for(i = 0; i < KEY_DEVICE_NUMBER_TOTAL; i++)
    {
        if(0 == GPIO_Driver_ReadInputPin(ptKeyDevicePreset[i].ptGPIOx, ptKeyDevicePreset[i].u16GPIO_Pin))
        {
            u16KeyValue |= ptKeyDevicePreset[i].u16KeyValue;
        }
    }
    return u16KeyValue;
}

#endif
