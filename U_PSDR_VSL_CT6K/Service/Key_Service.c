#if 1

#include "string.h"
#include "Key_Device.h"
#include "Key_Service.h"
#include "TimeTask.h"
#include "PublicFunc.h"

#define DEBOUNCE_COUNTER_10MS   (2)
#define KEYDOWN_100MS_COUNTER   (10)
#define KEYDOWN_200MS_COUNTER   (20)
#define KEYDOWN_300MS_COUNTER   (30)
#define KEYDOWN_500MS_COUNTER   (50)
#define KEYDOWN_800MS_COUNTER   (80)
#define KEYDOWN_1S_COUNTER      (100)
#define KEYDOWN_2S_COUNTER      (200)
#define KEYDOWN_5S_COUNTER      (500)
#define KEYDOWN_10S_COUNTER     (1000)

const KeyParameter_t ptKeyParameterPreset_Customer1[] =
{
    {DEV_KEY_UP,    KEYDOWN_2S_COUNTER, 0, MESSAGE_KEY_UP,    MESSAGE_KEY_UP},
    {DEV_KEY_DOWN,  KEYDOWN_2S_COUNTER, 0, MESSAGE_KEY_DOWN,  MESSAGE_KEY_DOWN},
    {DEV_KEY_ESC,   KEYDOWN_2S_COUNTER, 0, MESSAGE_KEY_ESC,   MESSAGE_KEY_ESC},
    {DEV_KEY_ENTER, KEYDOWN_2S_COUNTER, 0, MESSAGE_KEY_ENTER, MESSAGE_KEY_ENTERCONFIG},
};

const KeyParameter_t ptKeyParameterPreset_Customer2[] =
{
    {DEV_KEY_DOWN,  KEYDOWN_2S_COUNTER, 0, MESSAGE_KEY_UP,    MESSAGE_KEY_UP},
    {DEV_KEY_UP,    KEYDOWN_2S_COUNTER, 0, MESSAGE_KEY_DOWN,  MESSAGE_KEY_DOWN},
    {DEV_KEY_ESC,   KEYDOWN_2S_COUNTER, 0, MESSAGE_KEY_ESC,   MESSAGE_KEY_ESC},
    {DEV_KEY_ENTER, KEYDOWN_2S_COUNTER, 0, MESSAGE_KEY_ENTER, MESSAGE_KEY_ENTERCONFIG},
};

KeyParameter_t *ptKeyParameter_Current = (KeyParameter_t*)ptKeyParameterPreset_Customer1; //根据Model号和客制化设置该参数
uint8_t u8KeyNumberTotal = (sizeof(ptKeyParameterPreset_Customer1) / sizeof(KeyParameter_t));    //根据Model号和客制化设置该参数

typedef struct
{
    uint16_t u16KeyCurrentStatus;
    uint16_t u16KeyLastStatus;
    uint16_t u16KeyDebounceCounter;
    uint16_t u16KeyDownCounter;
    uint8_t u8KeyValueTableIndex;
    uint8_t u8Reserve;
    uint16_t u16Reserve;
} KeyServiceLocalVariable_t;

static KeyServiceLocalVariable_t tKeyServiceLocalVariable = {0};

/***********************************************************************************************************************
 功能：局部变量清理
************************************************************************************************************************/
void ClrKeyServiceLocalVariable(void)
{
    //memset(&tKeyServiceLocalVariable, 0, sizeof(tKeyServiceLocalVariable));
}

/***********************************************************************************************************************
 功能：按键消抖处理
************************************************************************************************************************/
static void Key_Time_Handler(void)
{
    if(tKeyServiceLocalVariable.u16KeyCurrentStatus != tKeyServiceLocalVariable.u16KeyLastStatus)
    {
        SubDecU16Cnt(&(tKeyServiceLocalVariable.u16KeyDebounceCounter));
    }
    else
    {
        if(tKeyServiceLocalVariable.u16KeyLastStatus != DEV_KEY_NULL)
        {
            SubDecU16Cnt(&(tKeyServiceLocalVariable.u16KeyDownCounter));
        }
    }
}

/***********************************************************************************************************************
 功能：按键消抖处理
************************************************************************************************************************/
static void Key_Debounce_Handler(void)
{
    uint16_t u16KeyValueNew = Key_Device_GetKeyValue();
    //新键值的到来，刷新消抖时间
    if(tKeyServiceLocalVariable.u16KeyCurrentStatus != u16KeyValueNew)
    {
        tKeyServiceLocalVariable.u16KeyDebounceCounter = DEBOUNCE_COUNTER_10MS;
        tKeyServiceLocalVariable.u16KeyCurrentStatus = u16KeyValueNew;
    }
}

/***********************************************************************************************************************
 功能：按键按下和松开的状态处理
************************************************************************************************************************/
static void Key_Status_Handler(void)
{
    uint8_t i;
    if(tKeyServiceLocalVariable.u16KeyLastStatus != tKeyServiceLocalVariable.u16KeyCurrentStatus)
    {
        if(tKeyServiceLocalVariable.u16KeyDebounceCounter == 0)   //消抖判断完成，认为是有效键
        {
            if(tKeyServiceLocalVariable.u16KeyCurrentStatus != 0) //有效按键按下，获取其长按时间
            {
                //获取有效按键在表中的下标
                for(i = 0; i < u8KeyNumberTotal; i++)
                {
                    if(ptKeyParameter_Current[i].u16KeyValue == tKeyServiceLocalVariable.u16KeyCurrentStatus)
                    {
                        tKeyServiceLocalVariable.u8KeyValueTableIndex = i;
                        break;
                    }
                }
                tKeyServiceLocalVariable.u16KeyDownCounter = ptKeyParameter_Current[tKeyServiceLocalVariable.u8KeyValueTableIndex].u16KeyLongPressCounterPreset;
            }
            else                                                  //按键松开
            {
                if(tKeyServiceLocalVariable.u16KeyDownCounter > 1)         //长按计时未结束，发出上一有效按键对应的短按Message
                {
//                    MessageQueue_PUSH_Tail_MSG(ptKeyParameter_Current[tKeyServiceLocalVariable.u8KeyValueTableIndex].MessageKeyShortPressPreset);
                }
                else                                                       //长按计时结束，发出上一有效按键对应的长按Message
                {
//                    MessageQueue_PUSH_Tail_MSG(ptKeyParameter_Current[tKeyServiceLocalVariable.u8KeyValueTableIndex].MessageKeyLongPressPreset);
                }
            }
            tKeyServiceLocalVariable.u16KeyLastStatus = tKeyServiceLocalVariable.u16KeyCurrentStatus;
        }
        else
        {
            ;
        }
    }
    else
    {
        ;
    } 
}

/***********************************************************************************************************************
 功能：键值处理
************************************************************************************************************************/
void Key_Handler(void)
{
    if (TimeTask_GetFlag_20ms == STATUS_FALSE)
    {
        return;
    }

    Key_Time_Handler();

    Key_Debounce_Handler();

    Key_Status_Handler();
}

#endif

