#ifndef __KEY_SERVICE_H__
#define __KEY_SERVICE_H__

#include "main.h"


/***********************************************************************************************************************
* * Macro definitions
***********************************************************************************************************************/

typedef enum
{
    MESSAGE_DUMMY = 0,

    MESSAGE_KEY_UP,
    MESSAGE_KEY_DOWN,
    MESSAGE_KEY_ESC,
    MESSAGE_KEY_ENTER,

    MESSAGE_KEY_ENTERCONFIG,

    MESSAGE_MAX,
    MESSAGE_ALL,
} KeyMessageType;

typedef struct
{
    uint16_t u16KeyValue;
    uint16_t u16KeyLongPressCounterPreset;
    uint16_t u16Reserve;
    KeyMessageType MessageKeyShortPressPreset;
    KeyMessageType MessageKeyLongPressPreset;
} KeyParameter_t;

extern const KeyParameter_t ptKeyParameterPreset_Customer1[];
extern const KeyParameter_t ptKeyParameterPreset_Customer2[];
extern KeyParameter_t *ptKeyParameter_Current;

extern void ClrKeyServiceLocalVariable(void);
extern void Key_Handler(void);


#endif
