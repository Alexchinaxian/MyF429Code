#include "Debug.h"
#include "stdio.h"

#if (DEBUG_TYPE == DEBUG_APP)

#define DEBUG_TX_TIMEOUT_5MS  (100/5)

volatile uint8_t u8Debug_Timeout_Cnt = 0;
volatile uint8_t u8Debug_TxBusyFlag = 0;
volatile uint8_t u8Debug_HasKeyFlag = 0;
volatile uint8_t u8Debug_Key = 0;
uint32_t u32Debug_ResetCounter = 0;
uint8_t u8Debug_ResetFlag = 0;


/********************************************** Use RTT ***********************************************/
#if USE_RTT

void Debug_TxCallBack_ISR(void)
{

}

void Debug_RxCallBack_ISR(uint8_t Data)
{

}

int32_t Debug_HasKey(void)
{
    return SEGGER_RTT_HasKey();
}

int32_t Debug_GetKey(void)
{
    return SEGGER_RTT_GetKey();
}

void Debug_ClrKeyFlag(void)
{

}

void Debug_Timeout_WDT_Service_5ms(void)
{

}

#ifdef __MICROLIB
int fputc(int ch, FILE *f)
{
    uint8_t Data = ch;
    SEGGER_RTT_Write(0, &Data, 1);
    return ch;
}

#else
#include <rt_sys.h>
FILEHANDLE _sys_open (const char *name, int openmode)
{
    return (1);
}

int _sys_close (FILEHANDLE fh)
{
    return (-1);
}

int _sys_write (FILEHANDLE fh, const uint8_t *buf, uint32_t len, int mode)
{
    SEGGER_RTT_Write(0, buf, len);
    return (0);
}

int _sys_read (FILEHANDLE fh, uint8_t *buf, uint32_t len, int mode)
{
    return (-1);
}

int _sys_istty (FILEHANDLE fh)
{
    return (0);
}

int _sys_seek (FILEHANDLE fh, long pos)
{
    return (-1);
}

long _sys_flen (FILEHANDLE fh)
{
    return (0);
}
#endif
#elif USE_DEBUG_RINGBUFFER
/********************************************** Use Ringbuffer ***********************************************/
#define DEBUG_TX_BUFFER_LEN        1024
#define DEBUG_TX_BUFFER_MASK    (DEBUG_TX_BUFFER_LEN - 1)
uint8_t Debug_TX_Buffer[DEBUG_TX_BUFFER_LEN] = {0};
volatile uint8_t Debug_TX_Header = 0;
volatile uint8_t Debug_TX_Tailer = 0;

#define DEBUG_RX_BUFFER_LEN        256
#define DEBUG_RX_BUFFER_MASK    (DEBUG_RX_BUFFER_LEN - 1)
uint8_t Debug_RX_Buffer[DEBUG_RX_BUFFER_LEN] = {0};
volatile uint8_t Debug_RX_Header = 0;
volatile uint8_t Debug_RX_Tailer = 0;

void Debug_TxCallBack_ISR(void)
{
    if (Debug_TX_Tailer == Debug_TX_Header)
    {
        u8Debug_TxBusyFlag = 0;
    }
    else
    {
//        Debug_Tx_s8SendData(Debug_TX_Buffer[Debug_TX_Tailer++]);
        Debug_TX_Tailer &= DEBUG_TX_BUFFER_MASK;
    }
}

void Debug_RxCallBack_ISR(uint8_t Data)
{
    Debug_RX_Buffer[Debug_RX_Header++] = Data;
    Debug_RX_Header &= DEBUG_RX_BUFFER_MASK;
}

void Debug_PutChar(char ch)
{
    uint32_t FreeSpace;
    do
    {
        if (Debug_TX_Header < Debug_TX_Tailer)
        {
            FreeSpace = Debug_TX_Tailer - Debug_TX_Header;
        }
        else
        {
            FreeSpace = Debug_TX_Tailer + DEBUG_TX_BUFFER_MASK + 1 - Debug_TX_Header;
        }
    }
    while (FreeSpace < 2);
    Debug_TX_Buffer[Debug_TX_Header] = ch;
    if (!u8Debug_TxBusyFlag)
    {
        u8Debug_TxBusyFlag = 1;
//        Debug_Tx_s8SendData(ch);
    }
    else
    {
        Debug_TX_Header = (Debug_TX_Header + 1) & DEBUG_TX_BUFFER_MASK;
    }
}

uint8_t Debug_HasKey(void)
{
    if (Debug_RX_Header == Debug_RX_Tailer)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void Debug_ClrKeyFlag(void)
{

}

int32_t Debug_GetKey(void)
{
    uint8_t Data = Debug_RX_Buffer[Debug_RX_Tailer++];
    Debug_RX_Tailer &= DEBUG_RX_BUFFER_MASK;
    return Data;
}

FILE __stdout;
int fputc(int ch, FILE *f)
{
    Debug_PutChar(ch);
    return ch;
}

void Debug_Timeout_WDT_Reload(void)
{
    u8Debug_Timeout_Cnt = DEBUG_TX_TIMEOUT_5MS;
}

void Debug_Timeout_WDT_Service_5ms(void)
{
    if(u8Debug_Timeout_Cnt > 0)
    {
        u8Debug_Timeout_Cnt--;
        if(u8Debug_Timeout_Cnt == 0)
        {
            u8Debug_TxBusyFlag = 0;
        }
    }
}

void Debug_Timeout_WDT_Disable(void)
{
    u8Debug_Timeout_Cnt = 0;
}

#else
/********************************************** Not Ringbuffer ***********************************************/
void Debug_TxCallBack_ISR(void)
{
    u8Debug_TxBusyFlag = 0;
}

void Debug_RxCallBack_ISR(uint8_t Data)
{
    u8Debug_Key = Data;
    u8Debug_HasKeyFlag = 1;
}

void Debug_Timeout_WDT_Reload(void)
{
    u8Debug_Timeout_Cnt = DEBUG_TX_TIMEOUT_5MS;
}

void Debug_Timeout_WDT_Service_5ms(void)
{
    if(u8Debug_Timeout_Cnt > 0)
    {
        u8Debug_Timeout_Cnt--;
        if(u8Debug_Timeout_Cnt == 0)
        {
            u8Debug_TxBusyFlag = 0;
        }
    }
}

void Debug_Timeout_WDT_Disable(void)
{
    u8Debug_Timeout_Cnt = 0;
}

void Debug_PutChar(uint8_t s8SendData)
{
    Debug_Timeout_WDT_Reload();
    while (u8Debug_TxBusyFlag)
    {
    }
    u8Debug_TxBusyFlag = 1;
    Debug_Tx_s8SendData(s8SendData);
    Debug_Timeout_WDT_Disable();
}

uint8_t Debug_HasKey(void)
{
    return u8Debug_HasKeyFlag;
}

void Debug_ClrKeyFlag(void)
{
    u8Debug_HasKeyFlag = 0;
}

int8_t Debug_GetKey(void)
{
    return u8Debug_Key;
}


void printMsg(void *str)
{
    int8_t* ps8String = (int8_t*)str;
    int8_t s8SendData = *(ps8String++);
    while (s8SendData)
    {
        Debug_PutChar((uint8_t)s8SendData);
        s8SendData = *(ps8String++);
    }
}

void printData(void *str, int32_t Value)
{
    int8_t* ps8String = (int8_t*)str;
    int8_t s8SendData = *(ps8String++);
    uint8_t bNoneZero = FALSE;
    uint32_t u32Divider = 1000000000;
    int8_t s8DispValue;
    while (s8SendData)
    {
        if (s8SendData == (int8_t)'%')
        {
            s8SendData = *(ps8String++);
            if (s8SendData == (int8_t)'d' || s8SendData == (int8_t)'x')
            {
                if ((s8SendData == (int8_t)'d') && (Value < 0))
                {
                    Debug_PutChar('-');
                    Value *= -1;
                }
                if (Value)
                {
                    bNoneZero = FALSE;
                    u32Divider = 1000000000;
                    s8DispValue;
                    if (s8SendData == (int8_t)'x') u32Divider = 0x10000000;
                    while (u32Divider)
                    {
                        s8DispValue = Value / u32Divider;
                        Value -= s8DispValue * u32Divider;
                        if (s8DispValue) bNoneZero = STATUS_TRUE;
                        if (bNoneZero)
                        {
                            if (s8DispValue > 9)
                                s8DispValue += 55;
                            else
                                s8DispValue += 0x30;
                            Debug_PutChar(s8DispValue);
                        }
                        if (s8SendData == (int8_t)'d')
                            u32Divider /= 10;
                        else
                            u32Divider /= 0x10;
                    }
                }
                else
                {
                    Debug_PutChar('0');
                }
            }
        }
        else
        {
            Debug_PutChar(s8SendData);
        }
        s8SendData = *(ps8String++);
    }
}
#endif

void Debug_Initial(void)
{
#if USE_RTT
    SEGGER_RTT_Init();
#endif
    printData("\nBegin : %d\n", 123);
}

void Debug_Handler(void)
{
    if (Debug_HasKey())
    {
        Debug_ClrKeyFlag();
        u8Debug_Key = Debug_GetKey();
        u8Debug_ResetFlag = 0;

        switch (u8Debug_Key)
        {
            case 0x7F:
                u8Debug_ResetFlag = 1;
                break;
            case 'T':
                printMsg("Test\n");
                break;
            default:
                break;
        }
        if (u8Debug_ResetFlag == 1)
        {
            if (++u32Debug_ResetCounter >= 100)
            {
//                MCU_SystemReset();
            }
        }
        else
        {
            u32Debug_ResetCounter = 0;
        }
    }
}

#endif
