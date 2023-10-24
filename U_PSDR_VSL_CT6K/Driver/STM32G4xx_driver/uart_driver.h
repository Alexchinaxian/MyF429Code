#ifndef __UART_DRIVER_H
#define __UART_DRIVER_H

#include "MCU.h"
#if 0
typedef enum
{
    PR_COM_ID1 = 0,
    PR_COM_ID2 = 1,
    PR_COM_ID3 = 2,
    PR_COM_ID4 = 3,
    PR_COM_ID5 = 4,
    PR_COM_ID6 = 5,
    DEV_ID_MAX，
} ComIDCode;
#endif
#define PR_USART1_CLKSOURCE                                             LL_RCC_USART1_CLKSOURCE_PCLK1
#define PR_USART2_CLKSOURCE                                             LL_RCC_USART2_CLKSOURCE_PCLK1
#define PR_USART3_CLKSOURCE                                             LL_RCC_USART3_CLKSOURCE_PCLK1
#define PR_USART4_CLKSOURCE                                             
#define PR_USART5_CLKSOURCE                                             
#define PR_USART6_CLKSOURCE                                             


#define PR_USART1_CLOCK                                                 LL_APB2_GRP1_PERIPH_USART1
#define PR_USART2_CLOCK                                                 LL_APB1_GRP1_PERIPH_USART2
#define PR_USART3_CLOCK                                                 LL_APB1_GRP1_PERIPH_USART3
#define PR_USART4_CLOCK                                                 LL_APB1_GRP1_PERIPH_USART4
#define PR_USART5_CLOCK                                                 LL_APB1_GRP1_PERIPH_USART5
#define PR_USART6_CLOCK                                                 LL_APB1_GRP1_PERIPH_USART6


#define PR_USART_DATAWIDTH_7B                                           LL_USART_DATAWIDTH_7B
#define PR_USART_DATAWIDTH_8B                                           LL_USART_DATAWIDTH_8B
#define PR_USART_DATAWIDTH_9B                                           LL_USART_DATAWIDTH_9B

#define PR_USART_STOPBITS_0_5                                           LL_USART_STOPBITS_0_5
#define PR_USART_STOPBITS_1                                             LL_USART_STOPBITS_1
#define PR_USART_STOPBITS_1_5                                           LL_USART_STOPBITS_1_5
#define PR_USART_STOPBITS_2                                             LL_USART_STOPBITS_2

#define PR_USART_PARITY_NONE                                            LL_USART_PARITY_NONE
#define PR_USART_PARITY_EVEN                                            LL_USART_PARITY_EVEN
#define PR_USART_PARITY_ODD                                             LL_USART_PARITY_ODD

#define PR_APB2_GRP1_EnableClock                                        LL_APB2_GRP1_EnableClock
#define PR_DMA_IsActiveFlag_TC3                                         LL_DMA_IsActiveFlag_TC3
#define PR_DMA_IsActiveFlag_TC4                                         LL_DMA_IsActiveFlag_TC4
#define PR_DMA_ClearFlag_TC3                                            LL_DMA_ClearFlag_TC3
#define PR_DMA_ClearFlag_TC4                                            LL_DMA_ClearFlag_TC4
#define PR_LPUART_IsActiveFlag_RXNE_RXFNE                               LL_LPUART_IsActiveFlag_RXNE_RXFNE
#define PR_LPUART_IsActiveFlag_TXE_TXFNF                                LL_LPUART_IsActiveFlag_TXE_TXFNF

#define PR_RCC_SetUSARTClockSource                                      LL_RCC_SetUSARTClockSource

extern void GetUsartRxBuf(uint8_t u8Sciid ,uint8_t ** pu8Frame);
extern void GetUsartTxBuf(uint8_t u8Sciid ,uint8_t ** pu8Frame);
extern uint16_t GetUsartRxBufLength(uint8_t u8Sciid);


extern void UART_Driver_Init(void);
extern void UART_DmaStartRx(uint8_t u8Port, uint8_t *pRxBuffer, uint32_t u32BufferSize);
extern void UART_DmaStartTx(uint8_t u8Port, uint8_t *pTxBuffer, uint32_t u32BufferSize);
extern void UART_DmaResetTx(uint8_t u8Port, uint8_t *u8TxBuffer, uint16_t u16BufferSize);

#endif
