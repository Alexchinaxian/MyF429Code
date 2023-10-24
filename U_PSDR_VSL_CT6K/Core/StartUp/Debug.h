#ifndef __DEBUG_H__
#define __DEBUG_H__
#include "main.h"

#if (DEBUG_TYPE == DEBUG_APP)
#define DEBUG_UART_TYPE                 DEV_UART_1
#define USE_DEBUG_RINGBUFFER            1
#endif

#if (DEBUG_TYPE == DEBUG_APP)

#if (DEBUG_UART_TYPE == DEV_UART_0)
#define DEBUG_TX_SENDDATA(x)            Dev_Uart_T0_SendData(x)
#define DEBUG_TXCALLBACK_ISR            Dev_Uart_T0_TxCallBack_ISR
#define DEBUG_RXCALLBACK_ISR            Dev_Uart_T0_RxCallBack_ISR
#elif (DEBUG_UART_TYPE == DEV_UART_1)
#define DEBUG_TX_SENDDATA(x)            Dev_Uart_T1_SendData(x)
#define DEBUG_TXCALLBACK_ISR            Dev_Uart_T1_TxCallBack_ISR
#define DEBUG_RXCALLBACK_ISR            Dev_Uart_T1_RxCallBack_ISR
#elif (DEBUG_UART_TYPE == DEV_UART_2)
#define DEBUG_TX_SENDDATA(x)            Dev_Uart_T2_SendData(x)
#define DEBUG_TXCALLBACK_ISR            Dev_Uart_T2_TxCallBack_ISR
#define DEBUG_RXCALLBACK_ISR            Dev_Uart_T2_RxCallBack_ISR
#elif (DEBUG_UART_TYPE == DEV_UART_3)
#define DEBUG_TX_SENDDATA(x)            Dev_Uart_T3_SendData(x)
#define DEBUG_TXCALLBACK_ISR            Dev_Uart_T3_TxCallBack_ISR
#define DEBUG_RXCALLBACK_ISR            Dev_Uart_T3_RxCallBack_ISR
#elif (DEBUG_UART_TYPE == DEV_UART_4)
#define DEBUG_TX_SENDDATA(x)            Dev_Uart_T4_SendData(x)
#define DEBUG_TXCALLBACK_ISR            Dev_Uart_T4_TxCallBack_ISR
#define DEBUG_RXCALLBACK_ISR            Dev_Uart_T4_RxCallBack_ISR
#elif (DEBUG_UART_TYPE == DEV_UART_5)
#define DEBUG_TX_SENDDATA(x)            Dev_Uart_T5_SendData(x)
#define DEBUG_TXCALLBACK_ISR            Dev_Uart_T5_TxCallBack_ISR
#define DEBUG_RXCALLBACK_ISR            Dev_Uart_T5_RxCallBack_ISR
#elif (DEBUG_UART_TYPE == DEV_UART_6)
#define DEBUG_TX_SENDDATA(x)            Dev_Uart_T6_SendData(x)
#define DEBUG_TXCALLBACK_ISR            Dev_Uart_T6_TxCallBack_ISR
#define DEBUG_RXCALLBACK_ISR            Dev_Uart_T6_RxCallBack_ISR
#elif (DEBUG_UART_TYPE == DEV_UART_7)
#define DEBUG_TX_SENDDATA(x)            Dev_Uart_T7_SendData(x)
#define DEBUG_TXCALLBACK_ISR            Dev_Uart_T7_TxCallBack_ISR
#define DEBUG_RXCALLBACK_ISR            Dev_Uart_T7_RxCallBack_ISR
#elif (DEBUG_UART_TYPE == DEV_UART_SIM)
#define DEBUG_TX_SENDDATA(x)            Dev_Uart_Sim_SendData(x)
#define DEBUG_TXCALLBACK_ISR            Dev_Uart_Sim_TxCallBack_ISR
#define DEBUG_RXCALLBACK_ISR            Dev_Uart_Sim_RxCallBack_ISR
#else
#error "Error Debug.c DEBUG_UART_TYPE"
#endif

extern void Debug_Initial(void);
extern void Debug_Handler(void);
extern void DEBUG_TXCALLBACK_ISR(void);
extern void DEBUG_RXCALLBACK_ISR(uint8_t Data);
extern void Debug_Timeout_WDT_Service_5ms(void);

#if USE_RTT
#include "SEGGER_RTT.h"
#define printData  printf
#define printMsg   printf
#elif USE_DEBUG_RINGBUFFER
#define printData                       printf
#define printMsg                        printf
#else
extern void printMsg(void *str);
extern void printData(void *str, int32_t value);
#endif

#else
#define Debug_Initial()
#define Debug_Handler()
#define DEBUG_TXCALLBACK_ISR()
#define DEBUG_RXCALLBACK_ISR(x)
#define printMsg(x)
#define printData(x, y)
#define Debug_Timeout_WDT_Service_5ms()
#endif



#endif