/***********************************************************************************************************************
* Copyright (c)  , CVTE
* ***********************************************************************************************************************
* 文件名     : uart_driver.c
* 用途       :通用异步串行通信
************************************************************************************************************************/

#include "uart_driver.h"
#include <string.h>
#include <stdlib.h>

/***********************************************************************************************************************
Global variables and funtions
************************************************************************************************************************/
uint8_t u8UartTxBuffer[DEV_ID_MAX][DEV_TX_BUFF_SIZE];
uint8_t u8UartRxBuffer[DEV_ID_MAX][DEV_RX_BUFF_SIZE];

/***********************************************************************************************************************
 功能：获取接收缓冲区地址信息
************************************************************************************************************************/
void GetUsartRxBuf(uint8_t u8Sciid ,uint8_t ** pu8Frame)
{
    *pu8Frame = ( uint8_t * ) &u8UartRxBuffer[u8Sciid][0];
}

/***********************************************************************************************************************
 功能：获取发送缓冲区地址信息
************************************************************************************************************************/
void GetUsartTxBuf(uint8_t u8Sciid ,uint8_t ** pu8Frame)
{
    *pu8Frame = ( uint8_t * ) &u8UartTxBuffer[u8Sciid][0];
}

/***********************************************************************************************************************
 功能：获取接收缓冲区长度信息
************************************************************************************************************************/
uint16_t GetUsartRxBufLength(uint8_t u8Sciid)
{
    uint16_t u16RxBufLength = 0;
    switch (u8Sciid)
    {
        case  DEV_COM_PORT1_ID:
            u16RxBufLength = DEV_COM_PORT1_DMA_RXBUFF_SIZE - DMA_Driver_GetDataLength(DEV_COM_PORT1_RX_DMA,DEV_COM_PORT1_RX_DMA_CHANNEL);
            break;
        case DEV_COM_PORT2_ID:
            u16RxBufLength = DEV_COM_PORT2_DMA_RXBUFF_SIZE - DMA_Driver_GetDataLength(DEV_COM_PORT2_RX_DMA,DEV_COM_PORT2_RX_DMA_CHANNEL);
            break;
        case DEV_COM_PORT3_ID:
            u16RxBufLength = DEV_COM_PORT3_DMA_RXBUFF_SIZE - DMA_Driver_GetDataLength(DEV_COM_PORT3_RX_DMA,DEV_COM_PORT3_RX_DMA_CHANNEL);
            break;
        case DEV_COM_PORT4_ID:
            u16RxBufLength = DEV_COM_PORT4_DMA_RXBUFF_SIZE - DMA_Driver_GetDataLength(DEV_COM_PORT4_RX_DMA,DEV_COM_PORT4_RX_DMA_CHANNEL);
            break;
        case DEV_COM_PORT5_ID:
            u16RxBufLength = DEV_COM_PORT5_DMA_RXBUFF_SIZE - DMA_Driver_GetDataLength(DEV_COM_PORT5_RX_DMA,DEV_COM_PORT5_RX_DMA_CHANNEL);
            break;
        case DEV_ID_METER:
            u16RxBufLength = DEV_COM_PORT6_DMA_RXBUFF_SIZE - DMA_Driver_GetDataLength(DEV_COM_PORT6_RX_DMA,DEV_COM_PORT6_RX_DMA_CHANNEL);
            break;
        default:
            u16RxBufLength = 0;
            break;
    }
    return u16RxBufLength;
}

#if EN_COM_PORT_1
/***********************************************************************************************************************
 功能：COM_PORT_1初始化函数
************************************************************************************************************************/
static void UART_Driver_ComPort1_Init(void)
{
    LL_USART_Disable(DEV_COM_PORT1);

    LL_USART_InitTypeDef USART_InitStruct = {0};
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    LL_RCC_SetUSARTClockSource(DEV_COM_PORT1_CLKSOURCE);

    LL_APB1_GRP1_EnableClock(DEV_COM_PORT1_CLOCK);

    GPIO_InitStruct.Pin = DEV_COM_PORT1_TX_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DEV_COM_PORT1_TX_PULL;
    GPIO_InitStruct.Alternate = DEV_COM_PORT1_TX_AF;
    LL_GPIO_Init(DEV_COM_PORT1_TX_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = DEV_COM_PORT1_RX_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DEV_COM_PORT1_RX_PULL;
    GPIO_InitStruct.Alternate = DEV_COM_PORT1_RX_AF;
    LL_GPIO_Init(DEV_COM_PORT1_RX_PORT, &GPIO_InitStruct);

    USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;
    USART_InitStruct.BaudRate = DEV_COM_PORT1_BAUDRATE;
    USART_InitStruct.DataWidth = DEV_COM_PORT1_WORDLEN;
    USART_InitStruct.StopBits = DEV_COM_PORT1_STOPBIT;
    USART_InitStruct.Parity = DEV_COM_PORT1_PARITY;
    USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
    USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
    LL_USART_Init(DEV_COM_PORT1, &USART_InitStruct);
    LL_USART_SetTXFIFOThreshold(DEV_COM_PORT1, LL_USART_FIFOTHRESHOLD_1_8);
    LL_USART_SetRXFIFOThreshold(DEV_COM_PORT1, LL_USART_FIFOTHRESHOLD_1_8);
    LL_USART_DisableFIFO(DEV_COM_PORT1);
    LL_USART_DisableOverrunDetect(DEV_COM_PORT1);
    LL_USART_ConfigAsyncMode(DEV_COM_PORT1);

    LL_USART_EnableDMAReq_RX(DEV_COM_PORT1);
    LL_USART_EnableDMAReq_TX(DEV_COM_PORT1);
    LL_USART_Enable(DEV_COM_PORT1);
#if 0
    while((!(LL_USART_IsActiveFlag_TEACK(DEV_COM_PORT1))) || (!(LL_USART_IsActiveFlag_REACK(DEV_COM_PORT1))))
    {
    }
#endif
}
#else
#define UART_Driver_ComPort1_Init()
#endif

#if EN_COM_PORT_2
/***********************************************************************************************************************
 功能：COM_PORT_2初始化函数
************************************************************************************************************************/
static void UART_Driver_ComPort2_Init(void)
{
    LL_USART_Disable(DEV_COM_PORT2);

    LL_USART_InitTypeDef USART_InitStruct = {0};
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    LL_RCC_SetUSARTClockSource(DEV_COM_PORT2_CLKSOURCE);

    LL_APB1_GRP1_EnableClock(DEV_COM_PORT2_CLOCK);

    GPIO_InitStruct.Pin = DEV_COM_PORT2_TX_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DEV_COM_PORT2_TX_PULL;
    GPIO_InitStruct.Alternate = DEV_COM_PORT2_TX_AF;
    LL_GPIO_Init(DEV_COM_PORT2_TX_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = DEV_COM_PORT2_RX_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DEV_COM_PORT2_RX_PULL;
    GPIO_InitStruct.Alternate = DEV_COM_PORT2_RX_AF;
    LL_GPIO_Init(DEV_COM_PORT2_RX_PORT, &GPIO_InitStruct);

    USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;
    USART_InitStruct.BaudRate = DEV_COM_PORT2_BAUDRATE;
    USART_InitStruct.DataWidth = DEV_COM_PORT2_WORDLEN;
    USART_InitStruct.StopBits = DEV_COM_PORT2_STOPBIT;
    USART_InitStruct.Parity = DEV_COM_PORT2_PARITY;
    USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
    USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
    LL_USART_Init(DEV_COM_PORT2, &USART_InitStruct);
    LL_USART_SetTXFIFOThreshold(DEV_COM_PORT2, LL_USART_FIFOTHRESHOLD_1_8);
    LL_USART_SetRXFIFOThreshold(DEV_COM_PORT2, LL_USART_FIFOTHRESHOLD_1_8);
    LL_USART_DisableFIFO(DEV_COM_PORT2);
    LL_USART_DisableOverrunDetect(DEV_COM_PORT2);
    LL_USART_ConfigAsyncMode(DEV_COM_PORT2);

    LL_USART_EnableDMAReq_RX(DEV_COM_PORT2);
    LL_USART_EnableDMAReq_TX(DEV_COM_PORT2);
    LL_USART_Enable(DEV_COM_PORT2);
#if 0
    while((!(LL_USART_IsActiveFlag_TEACK(DEV_COM_PORT2))) || (!(LL_USART_IsActiveFlag_REACK(DEV_COM_PORT2))))
    {
    }
#endif
}
#else
#define UART_Driver_ComPort2_Init()
#endif

#if EN_COM_PORT_3
/***********************************************************************************************************************
 功能：COM_PORT_3初始化函数
************************************************************************************************************************/
static void UART_Driver_ComPort3_Init(void)
{
    LL_USART_Disable(DEV_COM_PORT3);

    LL_USART_InitTypeDef USART_InitStruct = {0};
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    //LL_RCC_SetUSARTClockSource(DEV_COM_PORT3_CLKSOURCE);

    LL_APB1_GRP1_EnableClock(DEV_COM_PORT3_CLOCK);

    GPIO_InitStruct.Pin = DEV_COM_PORT3_TX_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DEV_COM_PORT3_TX_PULL;
    GPIO_InitStruct.Alternate = DEV_COM_PORT3_TX_AF;
    LL_GPIO_Init(DEV_COM_PORT3_TX_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = DEV_COM_PORT3_RX_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DEV_COM_PORT3_RX_PULL;
    GPIO_InitStruct.Alternate = DEV_COM_PORT3_RX_AF;
    LL_GPIO_Init(DEV_COM_PORT3_RX_PORT, &GPIO_InitStruct);

    USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;
    USART_InitStruct.BaudRate = DEV_COM_PORT3_BAUDRATE;
    USART_InitStruct.DataWidth = DEV_COM_PORT3_WORDLEN;
    USART_InitStruct.StopBits = DEV_COM_PORT3_STOPBIT;
    USART_InitStruct.Parity = DEV_COM_PORT3_PARITY;
    USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
    USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
    LL_USART_Init(DEV_COM_PORT3, &USART_InitStruct);
    LL_USART_SetTXFIFOThreshold(DEV_COM_PORT3, LL_USART_FIFOTHRESHOLD_1_8);
    LL_USART_SetRXFIFOThreshold(DEV_COM_PORT3, LL_USART_FIFOTHRESHOLD_1_8);
    LL_USART_DisableFIFO(DEV_COM_PORT3);
    LL_USART_ConfigAsyncMode(DEV_COM_PORT3);

    LL_USART_EnableDMAReq_RX(DEV_COM_PORT3);
    LL_USART_EnableDMAReq_TX(DEV_COM_PORT3);
    LL_USART_Enable(DEV_COM_PORT3);
#if 0
    while((!(LL_USART_IsActiveFlag_TEACK(DEV_COM_PORT3))) || (!(LL_USART_IsActiveFlag_REACK(DEV_COM_PORT3))))
    {
    }
#endif
}
#else
#define UART_Driver_ComPort3_Init()
#endif

#if EN_COM_PORT_4
/***********************************************************************************************************************
 功能：COM_PORT_4初始化函数
************************************************************************************************************************/
static void UART_Driver_ComPort4_Init(void)
{
    LL_USART_InitTypeDef USART_InitStruct = {0};
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};


    //LL_RCC_SetUSARTClockSource(DEV_COM_PORT4_CLKSOURCE);

    LL_APB1_GRP1_EnableClock(DEV_COM_PORT4_CLOCK);

    GPIO_InitStruct.Pin = DEV_COM_PORT4_TX_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DEV_COM_PORT4_TX_PULL;
    GPIO_InitStruct.Alternate = DEV_COM_PORT4_TX_AF;
    LL_GPIO_Init(DEV_COM_PORT4_TX_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = DEV_COM_PORT4_RX_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DEV_COM_PORT4_RX_PULL;
    GPIO_InitStruct.Alternate = DEV_COM_PORT4_RX_AF;
    LL_GPIO_Init(DEV_COM_PORT4_RX_PORT, &GPIO_InitStruct);

    USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;
    USART_InitStruct.BaudRate = DEV_COM_PORT4_BAUDRATE;
    USART_InitStruct.DataWidth = DEV_COM_PORT4_WORDLEN;
    USART_InitStruct.StopBits = DEV_COM_PORT4_STOPBIT;
    USART_InitStruct.Parity = DEV_COM_PORT4_PARITY;
    USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
    USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
    LL_USART_Init(DEV_COM_PORT4, &USART_InitStruct);
    LL_USART_DisableFIFO(DEV_COM_PORT4);
    LL_USART_SetTXFIFOThreshold(DEV_COM_PORT4, LL_USART_FIFOTHRESHOLD_1_8);
    LL_USART_SetRXFIFOThreshold(DEV_COM_PORT4, LL_USART_FIFOTHRESHOLD_1_8);
    LL_USART_ConfigAsyncMode(DEV_COM_PORT4);

    LL_USART_EnableDMAReq_RX(DEV_COM_PORT4);
    LL_USART_EnableDMAReq_TX(DEV_COM_PORT4);
    LL_USART_Enable(DEV_COM_PORT4);
#if 0
    while((!(LL_USART_IsActiveFlag_TEACK(DEV_COM_PORT4))) || (!(LL_USART_IsActiveFlag_REACK(DEV_COM_PORT4))))
    {
    }
#endif
}

#else
#define UART_Driver_ComPort4_Init()
#endif

#if EN_COM_PORT_5
/***********************************************************************************************************************
 功能：COM_PORT_5初始化函数
************************************************************************************************************************/
static void UART_Driver_ComPort5_Init(void)
{
    LL_USART_InitTypeDef USART_InitStruct = {0};
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    //LL_RCC_SetUSARTClockSource(DEV_COM_PORT5_CLKSOURCE);

    LL_APB1_GRP1_EnableClock(DEV_COM_PORT5_CLOCK);

    GPIO_InitStruct.Pin = DEV_COM_PORT5_TX_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DEV_COM_PORT5_TX_PULL;
    GPIO_InitStruct.Alternate = DEV_COM_PORT5_TX_AF;
    LL_GPIO_Init(DEV_COM_PORT5_TX_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = DEV_COM_PORT5_RX_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DEV_COM_PORT5_RX_PULL;
    GPIO_InitStruct.Alternate = DEV_COM_PORT5_RX_AF;
    LL_GPIO_Init(DEV_COM_PORT5_RX_PORT, &GPIO_InitStruct);

    USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;
    USART_InitStruct.BaudRate = DEV_COM_PORT5_BAUDRATE;
    USART_InitStruct.DataWidth = DEV_COM_PORT5_WORDLEN;
    USART_InitStruct.StopBits = DEV_COM_PORT5_STOPBIT;
    USART_InitStruct.Parity = DEV_COM_PORT5_PARITY;
    USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
    USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
    LL_USART_Init(DEV_COM_PORT5, &USART_InitStruct);
    LL_USART_DisableFIFO(DEV_COM_PORT5);
    LL_USART_SetTXFIFOThreshold(DEV_COM_PORT5, LL_USART_FIFOTHRESHOLD_1_8);
    LL_USART_SetRXFIFOThreshold(DEV_COM_PORT5, LL_USART_FIFOTHRESHOLD_1_8);
    LL_USART_ConfigAsyncMode(DEV_COM_PORT5);

    LL_USART_EnableDMAReq_RX(DEV_COM_PORT5);
    LL_USART_EnableDMAReq_TX(DEV_COM_PORT5);
    LL_USART_EnableIT_IDLE(DEV_COM_PORT5);
    LL_USART_EnableIT_RXNE(DEV_COM_PORT5);
    LL_USART_Enable(DEV_COM_PORT5);

    LL_USART_ClearFlag_IDLE(DEV_COM_PORT5);
}
#else
#define UART_Driver_ComPort5_Init()
#endif

#if EN_COM_PORT_6
/***********************************************************************************************************************
 功能：COM_PORT_6初始化函数
************************************************************************************************************************/
static void UART_Driver_ComPort6_Init(void)
{
    LL_USART_InitTypeDef USART_InitStruct = {0};
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    LL_RCC_SetUSARTClockSource(DEV_COM_PORT6_CLKSOURCE);

    LL_APB2_GRP1_EnableClock(DEV_COM_PORT6_CLOCK);

    GPIO_InitStruct.Pin = DEV_COM_PORT6_TX_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DEV_COM_PORT6_TX_PULL;
    GPIO_InitStruct.Alternate = DEV_COM_PORT6_TX_AF;
    LL_GPIO_Init(DEV_COM_PORT6_TX_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = DEV_COM_PORT6_RX_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DEV_COM_PORT6_RX_PULL;
    GPIO_InitStruct.Alternate = DEV_COM_PORT6_RX_AF;
    LL_GPIO_Init(DEV_COM_PORT6_RX_PORT, &GPIO_InitStruct);

    USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;
    USART_InitStruct.BaudRate = DEV_COM_PORT6_BAUDRATE;
    USART_InitStruct.DataWidth = DEV_COM_PORT6_WORDLEN;
    USART_InitStruct.StopBits = DEV_COM_PORT6_STOPBIT;
    USART_InitStruct.Parity = DEV_COM_PORT6_PARITY;
    USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
    USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
    LL_USART_Init(DEV_COM_PORT6, &USART_InitStruct);
    LL_USART_DisableFIFO(DEV_COM_PORT6);
    LL_USART_SetTXFIFOThreshold(DEV_COM_PORT6, LL_USART_FIFOTHRESHOLD_1_8);
    LL_USART_SetRXFIFOThreshold(DEV_COM_PORT6, LL_USART_FIFOTHRESHOLD_1_8);
    LL_USART_ConfigAsyncMode(DEV_COM_PORT6);

    LL_USART_EnableDMAReq_RX(DEV_COM_PORT6);
    LL_USART_EnableDMAReq_TX(DEV_COM_PORT6);
    LL_USART_Enable(DEV_COM_PORT6);

}
#else
#define UART_Driver_ComPort6_Init()
#endif

/***********************************************************************************************************************
 功能：uart的统一初始化函数
************************************************************************************************************************/
void UART_Driver_Init(void)
{
    UART_Driver_ComPort1_Init();
    UART_Driver_ComPort2_Init();
    UART_Driver_ComPort3_Init();
    UART_Driver_ComPort4_Init();
    UART_Driver_ComPort5_Init();
    UART_Driver_ComPort6_Init();

    UART_DmaStartRx(DEV_COM_PORT1_ID, u8UartRxBuffer[DEV_COM_PORT1_ID],  DEV_COM_PORT1_DMA_RXBUFF_SIZE);
    UART_DmaStartRx(DEV_COM_PORT2_ID, u8UartRxBuffer[DEV_COM_PORT2_ID],  DEV_COM_PORT2_DMA_RXBUFF_SIZE);
    UART_DmaStartRx(DEV_COM_PORT3_ID, u8UartRxBuffer[DEV_COM_PORT3_ID],  DEV_COM_PORT3_DMA_RXBUFF_SIZE);
    UART_DmaStartRx(DEV_COM_PORT4_ID, u8UartRxBuffer[DEV_COM_PORT4_ID],  DEV_COM_PORT4_DMA_RXBUFF_SIZE);
    UART_DmaStartRx(DEV_COM_PORT5_ID, u8UartRxBuffer[DEV_COM_PORT5_ID],  DEV_COM_PORT5_DMA_RXBUFF_SIZE);
    UART_DmaStartRx(DEV_COM_PORT6_ID, u8UartRxBuffer[DEV_COM_PORT6_ID],  DEV_COM_PORT6_DMA_RXBUFF_SIZE);

    UART_DmaResetTx(DEV_COM_PORT1_ID, u8UartTxBuffer[DEV_COM_PORT1_ID],  DEV_COM_PORT1_DMA_TXBUFF_SIZE);
    UART_DmaResetTx(DEV_COM_PORT2_ID, u8UartTxBuffer[DEV_COM_PORT2_ID],  DEV_COM_PORT2_DMA_TXBUFF_SIZE);
    UART_DmaResetTx(DEV_COM_PORT3_ID, u8UartTxBuffer[DEV_COM_PORT3_ID],  DEV_COM_PORT3_DMA_TXBUFF_SIZE);
    UART_DmaResetTx(DEV_COM_PORT4_ID, u8UartTxBuffer[DEV_COM_PORT4_ID],  DEV_COM_PORT4_DMA_TXBUFF_SIZE);
    UART_DmaResetTx(DEV_COM_PORT5_ID, u8UartTxBuffer[DEV_COM_PORT5_ID],  DEV_COM_PORT5_DMA_TXBUFF_SIZE);
    UART_DmaResetTx(DEV_COM_PORT6_ID, u8UartTxBuffer[DEV_COM_PORT6_ID],  DEV_COM_PORT6_DMA_TXBUFF_SIZE);

    memset(&u8UartTxBuffer, 0x00, DEV_ID_MAX * DEV_TX_BUFF_SIZE );
    memset(&u8UartRxBuffer, 0x00, DEV_ID_MAX * DEV_RX_BUFF_SIZE );
}

void UART_DmaStartRx(uint8_t u8Port, uint8_t *pRxBuffer, uint32_t u32BufferSize)
{
    switch(u8Port)
    {
        case DEV_COM_PORT1_ID:

            LL_USART_DisableDMAReq_RX(DEV_COM_PORT1);
            LL_USART_DisableIT_RTO(DEV_COM_PORT1);
            LL_DMA_DisableChannel(DEV_COM_PORT1_RX_DMA, DEV_COM_PORT1_RX_DMA_CHANNEL);
            PR_DMA_ClearFlag_COM_PORT1(DEV_COM_PORT1_RX_DMA);
            LL_DMA_SetMemoryAddress(DEV_COM_PORT1_RX_DMA, DEV_COM_PORT1_RX_DMA_CHANNEL, (uint32_t)pRxBuffer);
            LL_DMA_SetDataLength(DEV_COM_PORT1_RX_DMA, DEV_COM_PORT1_RX_DMA_CHANNEL, (uint32_t)u32BufferSize);
            LL_DMA_EnableChannel(DEV_COM_PORT1_RX_DMA, DEV_COM_PORT1_RX_DMA_CHANNEL);
            LL_USART_EnableDMAReq_RX(DEV_COM_PORT1);
            LL_USART_EnableIT_RTO(DEV_COM_PORT1);
            LL_USART_EnableDirectionRx(DEV_COM_PORT1);
        break;

        case DEV_COM_PORT2_ID:

            LL_USART_DisableDMAReq_RX(DEV_COM_PORT2);
            LL_USART_DisableIT_RTO(DEV_COM_PORT2);
            LL_DMA_DisableChannel(DEV_COM_PORT2_RX_DMA, DEV_COM_PORT2_RX_DMA_CHANNEL);
            PR_DMA_ClearFlag_COM_PORT2(DEV_COM_PORT2_RX_DMA);
            LL_DMA_SetMemoryAddress(DEV_COM_PORT2_RX_DMA, DEV_COM_PORT2_RX_DMA_CHANNEL, (uint32_t)pRxBuffer);
            LL_DMA_SetDataLength(DEV_COM_PORT2_RX_DMA, DEV_COM_PORT2_RX_DMA_CHANNEL, (uint32_t)u32BufferSize);
            LL_DMA_EnableChannel(DEV_COM_PORT2_RX_DMA, DEV_COM_PORT2_RX_DMA_CHANNEL);
            LL_USART_EnableDMAReq_RX(DEV_COM_PORT2);
            LL_USART_EnableIT_RTO(DEV_COM_PORT2);
            LL_USART_EnableDirectionRx(DEV_COM_PORT2);
        break;

        case DEV_COM_PORT3_ID:

            LL_USART_DisableDMAReq_RX(DEV_COM_PORT3);
            LL_USART_DisableIT_RTO(DEV_COM_PORT3);
            LL_DMA_DisableChannel(DEV_COM_PORT3_RX_DMA, DEV_COM_PORT3_RX_DMA_CHANNEL);
            PR_DMA_ClearFlag_COM_PORT3(DEV_COM_PORT3_RX_DMA);
            LL_DMA_SetMemoryAddress(DEV_COM_PORT3_RX_DMA, DEV_COM_PORT3_RX_DMA_CHANNEL, (uint32_t)pRxBuffer);
            LL_DMA_SetDataLength(DEV_COM_PORT3_RX_DMA, DEV_COM_PORT3_RX_DMA_CHANNEL, (uint32_t)u32BufferSize);
            LL_DMA_EnableChannel(DEV_COM_PORT3_RX_DMA, DEV_COM_PORT3_RX_DMA_CHANNEL);
            LL_USART_EnableDMAReq_RX(DEV_COM_PORT3);
            LL_USART_EnableIT_RTO(DEV_COM_PORT3);
            LL_USART_EnableDirectionRx(DEV_COM_PORT3);
        break;

        case DEV_COM_PORT4_ID:

            LL_USART_DisableDMAReq_RX(DEV_COM_PORT4);
            LL_USART_DisableIT_RTO(DEV_COM_PORT4);
            LL_DMA_DisableChannel(DEV_COM_PORT4_RX_DMA, DEV_COM_PORT4_RX_DMA_CHANNEL);
            PR_DMA_ClearFlag_COM_PORT4(DEV_COM_PORT4_RX_DMA);
            LL_DMA_SetMemoryAddress(DEV_COM_PORT4_RX_DMA, DEV_COM_PORT4_RX_DMA_CHANNEL, (uint32_t)pRxBuffer);
            LL_DMA_SetDataLength(DEV_COM_PORT4_RX_DMA, DEV_COM_PORT4_RX_DMA_CHANNEL, (uint32_t)u32BufferSize);
            LL_DMA_EnableChannel(DEV_COM_PORT4_RX_DMA, DEV_COM_PORT4_RX_DMA_CHANNEL);
            LL_USART_EnableDMAReq_RX(DEV_COM_PORT4);
            LL_USART_EnableIT_RTO(DEV_COM_PORT4);
            LL_USART_EnableDirectionRx(DEV_COM_PORT4);
        break;
        case DEV_COM_PORT5_ID:
        
            LL_USART_DisableDMAReq_RX(DEV_COM_PORT5);
            LL_USART_DisableIT_RTO(DEV_COM_PORT5);
            LL_DMA_DisableChannel(DEV_COM_PORT5_RX_DMA, DEV_COM_PORT5_RX_DMA_CHANNEL);
            PR_DMA_ClearFlag_COM_PORT5(DEV_COM_PORT5_RX_DMA);
            LL_DMA_SetMemoryAddress(DEV_COM_PORT5_RX_DMA, DEV_COM_PORT5_RX_DMA_CHANNEL, (uint32_t)pRxBuffer);
            LL_DMA_SetDataLength(DEV_COM_PORT5_RX_DMA, DEV_COM_PORT5_RX_DMA_CHANNEL, (uint32_t)u32BufferSize);
            LL_DMA_EnableChannel(DEV_COM_PORT5_RX_DMA, DEV_COM_PORT5_RX_DMA_CHANNEL);
            LL_USART_EnableDMAReq_RX(DEV_COM_PORT5);
            LL_USART_EnableIT_RTO(DEV_COM_PORT5);
            LL_USART_EnableDirectionRx(DEV_COM_PORT5);
        break;
        
        case DEV_COM_PORT6_ID:
        
            LL_USART_DisableDMAReq_RX(DEV_COM_PORT6);
            LL_USART_DisableIT_RTO(DEV_COM_PORT6);
            LL_DMA_DisableChannel(DEV_COM_PORT6_RX_DMA, DEV_COM_PORT6_RX_DMA_CHANNEL);
            PR_DMA_ClearFlag_COM_PORT6(DEV_COM_PORT6_RX_DMA);
            LL_DMA_SetMemoryAddress(DEV_COM_PORT6_RX_DMA, DEV_COM_PORT6_RX_DMA_CHANNEL, (uint32_t)pRxBuffer);
            LL_DMA_SetDataLength(DEV_COM_PORT6_RX_DMA, DEV_COM_PORT6_RX_DMA_CHANNEL, (uint32_t)u32BufferSize);
            LL_DMA_EnableChannel(DEV_COM_PORT6_RX_DMA, DEV_COM_PORT6_RX_DMA_CHANNEL);
            LL_USART_EnableDMAReq_RX(DEV_COM_PORT6);
            LL_USART_EnableIT_RTO(DEV_COM_PORT6);
            LL_USART_EnableDirectionRx(DEV_COM_PORT6);
        break;

    }
}

void UART_DmaStartTx(uint8_t u8Port, uint8_t *pTxBuffer, uint32_t u32BufferSize)
{
    switch(u8Port)
    {
        case DEV_COM_PORT1_ID:

            LL_DMA_DisableChannel(DEV_COM_PORT1_TX_DMA, DEV_COM_PORT1_TX_DMA_CHANNEL);
            LL_DMA_SetMemoryAddress(DEV_COM_PORT1_TX_DMA, DEV_COM_PORT1_TX_DMA_CHANNEL, (uint32_t)pTxBuffer);
            LL_DMA_SetDataLength(DEV_COM_PORT1_TX_DMA, DEV_COM_PORT1_TX_DMA_CHANNEL, (uint32_t)u32BufferSize);
            LL_DMA_EnableChannel(DEV_COM_PORT1_TX_DMA, DEV_COM_PORT1_TX_DMA_CHANNEL);

        break;

        case DEV_COM_PORT2_ID:

            DEV_COM_BMS_RS485_TX_EN();
            LL_DMA_DisableChannel(DEV_COM_PORT2_TX_DMA, DEV_COM_PORT2_TX_DMA_CHANNEL);
            LL_DMA_SetMemoryAddress(DEV_COM_PORT2_TX_DMA, DEV_COM_PORT2_TX_DMA_CHANNEL, (uint32_t)pTxBuffer);
            LL_DMA_SetDataLength(DEV_COM_PORT2_TX_DMA, DEV_COM_PORT2_TX_DMA_CHANNEL, (uint32_t)u32BufferSize);
            LL_DMA_EnableChannel(DEV_COM_PORT2_TX_DMA, DEV_COM_PORT2_TX_DMA_CHANNEL);
        break;

        case DEV_COM_PORT3_ID:

            DEV_COM_WIFI_RS485_TX_EN();
            LL_DMA_DisableChannel(DEV_COM_PORT3_TX_DMA, DEV_COM_PORT3_TX_DMA_CHANNEL);
            LL_DMA_SetMemoryAddress(DEV_COM_PORT3_TX_DMA, DEV_COM_PORT3_TX_DMA_CHANNEL, (uint32_t)pTxBuffer);
            LL_DMA_SetDataLength(DEV_COM_PORT3_TX_DMA, DEV_COM_PORT3_TX_DMA_CHANNEL, (uint32_t)u32BufferSize);
            LL_DMA_EnableChannel(DEV_COM_PORT3_TX_DMA, DEV_COM_PORT3_TX_DMA_CHANNEL);

        break;

        case DEV_COM_PORT4_ID:

            LL_DMA_DisableChannel(DEV_COM_PORT4_TX_DMA, DEV_COM_PORT4_TX_DMA_CHANNEL);
            LL_DMA_SetMemoryAddress(DEV_COM_PORT4_TX_DMA, DEV_COM_PORT4_TX_DMA_CHANNEL, (uint32_t)pTxBuffer);
            LL_DMA_SetDataLength(DEV_COM_PORT4_TX_DMA, DEV_COM_PORT4_TX_DMA_CHANNEL, (uint32_t)u32BufferSize);
            LL_DMA_EnableChannel(DEV_COM_PORT4_TX_DMA, DEV_COM_PORT4_TX_DMA_CHANNEL);
        
        break;

        case DEV_COM_PORT5_ID:

            DEV_COM_AFCI_RS485_TX_EN();
            LL_DMA_DisableChannel(DEV_COM_PORT5_TX_DMA, DEV_COM_PORT5_TX_DMA_CHANNEL);
            LL_DMA_SetMemoryAddress(DEV_COM_PORT5_TX_DMA, DEV_COM_PORT5_TX_DMA_CHANNEL, (uint32_t)pTxBuffer);
            LL_DMA_SetDataLength(DEV_COM_PORT5_TX_DMA, DEV_COM_PORT5_TX_DMA_CHANNEL, (uint32_t)u32BufferSize);
            LL_DMA_EnableChannel(DEV_COM_PORT5_TX_DMA, DEV_COM_PORT5_TX_DMA_CHANNEL);
        
        break;

        case DEV_COM_PORT6_ID:

            DEV_COM_METER_RS485_TX_EN();
            LL_DMA_DisableChannel(DEV_COM_PORT6_TX_DMA, DEV_COM_PORT6_TX_DMA_CHANNEL);
            LL_DMA_SetMemoryAddress(DEV_COM_PORT6_TX_DMA, DEV_COM_PORT6_TX_DMA_CHANNEL, (uint32_t)pTxBuffer);
            LL_DMA_SetDataLength(DEV_COM_PORT6_TX_DMA, DEV_COM_PORT6_TX_DMA_CHANNEL, (uint32_t)u32BufferSize);
            LL_DMA_EnableChannel(DEV_COM_PORT6_TX_DMA, DEV_COM_PORT6_TX_DMA_CHANNEL);
        
        break;
    }
}

void UART_DmaResetTx(uint8_t u8Port, uint8_t *u8TxBuffer, uint16_t u16BufferSize)
{
    switch(u8Port)
    {
        case DEV_COM_PORT1_ID:

            LL_DMA_DisableChannel(DEV_COM_PORT1_TX_DMA, DEV_COM_PORT1_TX_DMA_CHANNEL);
            LL_USART_DisableDMAReq_TX(DEV_COM_PORT1);
            //memset(u8TxBuffer, 0x00, u16BufferSize);
            LL_USART_EnableDMAReq_TX(DEV_COM_PORT1);

        break;

        case DEV_COM_PORT2_ID:

            LL_DMA_DisableChannel(DEV_COM_PORT2_TX_DMA, DEV_COM_PORT2_TX_DMA_CHANNEL);
            LL_USART_DisableDMAReq_TX(DEV_COM_PORT2);
            //memset(u8TxBuffer, 0x00, u16BufferSize);
            LL_USART_EnableDMAReq_TX((DEV_COM_PORT2));

        break;

        case DEV_COM_PORT3_ID:

            LL_DMA_DisableChannel(DEV_COM_PORT3_TX_DMA, DEV_COM_PORT3_TX_DMA_CHANNEL);
            LL_USART_DisableDMAReq_TX(DEV_COM_PORT3);
            //memset(u8TxBuffer, 0x00, u16BufferSize);
            LL_USART_EnableDMAReq_TX((DEV_COM_PORT3));

        break;

        case DEV_COM_PORT4_ID:

            LL_DMA_DisableChannel(DEV_COM_PORT4_TX_DMA, DEV_COM_PORT4_TX_DMA_CHANNEL);
            LL_USART_DisableDMAReq_TX(DEV_COM_PORT4);
            //memset(u8TxBuffer, 0x00, u16BufferSize);
            LL_USART_EnableDMAReq_TX((DEV_COM_PORT4));

        break;
        case DEV_COM_PORT5_ID:
        
            LL_DMA_DisableChannel(DEV_COM_PORT5_TX_DMA, DEV_COM_PORT5_TX_DMA_CHANNEL);
            LL_USART_DisableDMAReq_TX(DEV_COM_PORT5);
            //memset(u8TxBuffer, 0x00, u16BufferSize);
            LL_USART_EnableDMAReq_TX((DEV_COM_PORT5));
        
        break;
        case DEV_COM_PORT6_ID:
        
            LL_DMA_DisableChannel(DEV_COM_PORT6_TX_DMA, DEV_COM_PORT6_TX_DMA_CHANNEL);
            LL_USART_DisableDMAReq_TX(DEV_COM_PORT6);
            //memset(u8TxBuffer, 0x00, u16BufferSize);
            LL_USART_EnableDMAReq_TX((DEV_COM_PORT6));
        
        break;
    }
}


/***********************************************************************************************************************
* Copyright (c)  CVTE All rights reserved.  * * * END OF FILE
************************************************************************************************************************/
