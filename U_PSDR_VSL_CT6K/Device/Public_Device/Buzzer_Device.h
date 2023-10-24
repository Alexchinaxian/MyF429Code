#ifndef __BUZZER_DEVICE_H__
#define __BUZZER_DEVICE_H__

#include "TypeDef.h"
//#include "Board.h"

#define BUZZER_PER_500ms     (5)
#define BUZZER_PER_1000ms    (10)
#define BUZZER_PER_2000ms    (20)
#define BUZZER_PER_5000ms    (50)


#define BUZZER_NULL          (0)
#define BUZZER_ON            (1)
#define BUZZER_OFF           (1)
#define BUZZER_BLINK         (1)
#define BUZZER_BEEP_1TIME    (1)
#define BUZZER_BEEP_2TIME    (2)
#define BUZZER_BEEP_3TIME    (3)
#define BUZZER_BEEP_4TIME    (4)
#define BUZZER_BEEP_5TIME    (5)
#define BUZZER_BEEP_6TIME    (6)
#define BUZZER_BEEP_7TIME    (7)
#define BUZZER_BEEP_8TIME    (8)
#define BUZZER_BEEP_9TIME    (9)

extern void Buzzer_Device_Cntrl(uint8_t u8BuzzerOn,uint8_t u8BuzzerOff,uint8_t u8BuzzerBlink,uint8_t u8BeepTimes,uint16_t u16Period);

extern void LED_Device_GenCntrl(uint8_t u8BuzzerOn,uint8_t u8BuzzerOff,uint8_t u8BuzzerBlink,uint8_t u8BeepTimes,uint16_t u16Period);

extern void LED_Device_GridCntrl(uint8_t u8BuzzerOn,uint8_t u8BuzzerOff,uint8_t u8BuzzerBlink,uint8_t u8BeepTimes,uint16_t u16Period);

extern void LED_Device_FaultCntrl(uint8_t u8BuzzerOn,uint8_t u8BuzzerOff,uint8_t u8BuzzerBlink,uint8_t u8BeepTimes,uint16_t u16Period);

extern void DRY_RLY1_DeviceCntrl(uint8_t u8DryRlyAction);

extern void DRY_RLY2_DeviceCntrl(uint8_t u8DryRlyAction);
#endif
