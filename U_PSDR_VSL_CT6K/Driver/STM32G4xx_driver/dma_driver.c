/***********************************************************************************************************************
* Copyright (c)  , CVTE
* ***********************************************************************************************************************
* 文件名     : dma_driver.c
* 用途       :
************************************************************************************************************************/

#include "dma_driver.h"


extern uint8_t u8UartTxBuffer[DEV_ID_MAX][DEV_TX_BUFF_SIZE];
extern uint8_t u8UartRxBuffer[DEV_ID_MAX][DEV_RX_BUFF_SIZE];

#if EN_COM_PORT_1
/***********************************************************************************************************************
 功能：COM_PORT_1 + dma接收初始化函数
************************************************************************************************************************/
void DMA_Driver_ComPort1_Tx_Inital(void)
{
    LL_DMA_SetPeriphRequest(DEV_COM_PORT1_TX_DMA, DEV_COM_PORT1_TX_DMA_CHANNEL, DEV_COM_PORT1_TX_DMAMUX);
    LL_DMA_SetPeriphAddress(DEV_COM_PORT1_TX_DMA, DEV_COM_PORT1_TX_DMA_CHANNEL, (uint32_t)(&(DEV_COM_PORT1->TDR)));
    LL_DMA_SetMemoryAddress(DEV_COM_PORT1_TX_DMA, DEV_COM_PORT1_TX_DMA_CHANNEL, (uint32_t)(&u8UartTxBuffer[DEV_COM_PORT1_ID]));
    LL_DMA_SetDataLength(DEV_COM_PORT1_TX_DMA, DEV_COM_PORT1_TX_DMA_CHANNEL, DEV_COM_PORT1_DMA_TXBUFF_SIZE);
    LL_DMA_SetDataTransferDirection(DEV_COM_PORT1_TX_DMA, DEV_COM_PORT1_TX_DMA_CHANNEL, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
    LL_DMA_SetChannelPriorityLevel(DEV_COM_PORT1_TX_DMA, DEV_COM_PORT1_TX_DMA_CHANNEL, LL_DMA_PRIORITY_LOW);
    LL_DMA_SetMode(DEV_COM_PORT1_TX_DMA, DEV_COM_PORT1_TX_DMA_CHANNEL, LL_DMA_MODE_NORMAL);
    LL_DMA_SetPeriphIncMode(DEV_COM_PORT1_TX_DMA, DEV_COM_PORT1_TX_DMA_CHANNEL, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetMemoryIncMode(DEV_COM_PORT1_TX_DMA, DEV_COM_PORT1_TX_DMA_CHANNEL, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphSize(DEV_COM_PORT1_TX_DMA, DEV_COM_PORT1_TX_DMA_CHANNEL, LL_DMA_PDATAALIGN_BYTE);
    LL_DMA_SetMemorySize(DEV_COM_PORT1_TX_DMA, DEV_COM_PORT1_TX_DMA_CHANNEL, LL_DMA_MDATAALIGN_BYTE);
}

/***********************************************************************************************************************
 功能：COM_PORT_1 + dma接收初始化函数
************************************************************************************************************************/
void DMA_Driver_ComPort1_Rx_Inital(void)
{
    LL_DMA_SetPeriphRequest(DEV_COM_PORT1_RX_DMA, DEV_COM_PORT1_RX_DMA_CHANNEL, DEV_COM_PORT1_RX_DMAMUX);
    LL_DMA_SetPeriphAddress(DEV_COM_PORT1_RX_DMA, DEV_COM_PORT1_RX_DMA_CHANNEL, (uint32_t)(&(DEV_COM_PORT1->RDR)));
    LL_DMA_SetMemoryAddress(DEV_COM_PORT1_RX_DMA, DEV_COM_PORT1_RX_DMA_CHANNEL, (uint32_t)(&u8UartRxBuffer[DEV_COM_PORT1_ID]));
    LL_DMA_SetDataLength(DEV_COM_PORT1_RX_DMA, DEV_COM_PORT1_RX_DMA_CHANNEL, DEV_COM_PORT1_DMA_RXBUFF_SIZE);
    LL_DMA_SetDataTransferDirection(DEV_COM_PORT1_RX_DMA, DEV_COM_PORT1_RX_DMA_CHANNEL, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
    LL_DMA_SetChannelPriorityLevel(DEV_COM_PORT1_RX_DMA, DEV_COM_PORT1_RX_DMA_CHANNEL, LL_DMA_PRIORITY_LOW);
    LL_DMA_SetMode(DEV_COM_PORT1_RX_DMA, DEV_COM_PORT1_RX_DMA_CHANNEL, LL_DMA_MODE_NORMAL);
    LL_DMA_SetPeriphIncMode(DEV_COM_PORT1_RX_DMA, DEV_COM_PORT1_RX_DMA_CHANNEL, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetMemoryIncMode(DEV_COM_PORT1_RX_DMA, DEV_COM_PORT1_RX_DMA_CHANNEL, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphSize(DEV_COM_PORT1_RX_DMA, DEV_COM_PORT1_RX_DMA_CHANNEL, LL_DMA_PDATAALIGN_BYTE);
    LL_DMA_SetMemorySize(DEV_COM_PORT1_RX_DMA, DEV_COM_PORT1_RX_DMA_CHANNEL, LL_DMA_MDATAALIGN_BYTE);
}
#endif

#if EN_COM_PORT_2
/***********************************************************************************************************************
 功能：COM_PORT_2 + dma接收初始化函数
************************************************************************************************************************/
void DMA_Driver_ComPort2_Tx_Inital(void)
{
    LL_DMA_SetPeriphRequest(DEV_COM_PORT2_TX_DMA, DEV_COM_PORT2_TX_DMA_CHANNEL, DEV_COM_PORT2_TX_DMAMUX);
    LL_DMA_SetPeriphAddress(DEV_COM_PORT2_TX_DMA, DEV_COM_PORT2_TX_DMA_CHANNEL, (uint32_t)(&(DEV_COM_PORT2->TDR)));
    LL_DMA_SetMemoryAddress(DEV_COM_PORT2_TX_DMA, DEV_COM_PORT2_TX_DMA_CHANNEL, (uint32_t)&u8UartTxBuffer[DEV_COM_PORT2_ID]);
    LL_DMA_SetDataLength(DEV_COM_PORT2_TX_DMA, DEV_COM_PORT2_TX_DMA_CHANNEL, DEV_COM_PORT2_DMA_TXBUFF_SIZE);
    LL_DMA_SetDataTransferDirection(DEV_COM_PORT2_TX_DMA, DEV_COM_PORT2_TX_DMA_CHANNEL, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
    LL_DMA_SetChannelPriorityLevel(DEV_COM_PORT2_TX_DMA, DEV_COM_PORT2_TX_DMA_CHANNEL, LL_DMA_PRIORITY_LOW);
    LL_DMA_SetMode(DEV_COM_PORT2_TX_DMA, DEV_COM_PORT2_TX_DMA_CHANNEL, LL_DMA_MODE_NORMAL);
    LL_DMA_SetPeriphIncMode(DEV_COM_PORT2_TX_DMA, DEV_COM_PORT2_TX_DMA_CHANNEL, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetMemoryIncMode(DEV_COM_PORT2_TX_DMA, DEV_COM_PORT2_TX_DMA_CHANNEL, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphSize(DEV_COM_PORT2_TX_DMA, DEV_COM_PORT2_TX_DMA_CHANNEL, LL_DMA_PDATAALIGN_BYTE);
    LL_DMA_SetMemorySize(DEV_COM_PORT2_TX_DMA, DEV_COM_PORT2_TX_DMA_CHANNEL, LL_DMA_MDATAALIGN_BYTE);
}

/***********************************************************************************************************************
 功能：COM_PORT_2 + dma接收初始化函数
************************************************************************************************************************/
void DMA_Driver_ComPort2_Rx_Inital(void)
{
    LL_DMA_SetPeriphRequest(DEV_COM_PORT2_RX_DMA, DEV_COM_PORT2_RX_DMA_CHANNEL, DEV_COM_PORT2_RX_DMAMUX);
    LL_DMA_SetPeriphAddress(DEV_COM_PORT2_RX_DMA, DEV_COM_PORT2_RX_DMA_CHANNEL, (uint32_t)(&(DEV_COM_PORT2->RDR)));
    LL_DMA_SetMemoryAddress(DEV_COM_PORT2_RX_DMA, DEV_COM_PORT2_RX_DMA_CHANNEL, (uint32_t)&u8UartRxBuffer[DEV_COM_PORT2_ID]);
    LL_DMA_SetDataLength(DEV_COM_PORT2_RX_DMA, DEV_COM_PORT2_RX_DMA_CHANNEL, DEV_COM_PORT2_DMA_RXBUFF_SIZE);
    LL_DMA_SetDataTransferDirection(DEV_COM_PORT2_RX_DMA, DEV_COM_PORT2_RX_DMA_CHANNEL, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
    LL_DMA_SetChannelPriorityLevel(DEV_COM_PORT2_RX_DMA, DEV_COM_PORT2_RX_DMA_CHANNEL, LL_DMA_PRIORITY_LOW);
    LL_DMA_SetMode(DEV_COM_PORT2_RX_DMA, DEV_COM_PORT2_RX_DMA_CHANNEL, LL_DMA_MODE_NORMAL);
    LL_DMA_SetPeriphIncMode(DEV_COM_PORT2_RX_DMA, DEV_COM_PORT2_RX_DMA_CHANNEL, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetMemoryIncMode(DEV_COM_PORT2_RX_DMA, DEV_COM_PORT2_RX_DMA_CHANNEL, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphSize(DEV_COM_PORT2_RX_DMA, DEV_COM_PORT2_RX_DMA_CHANNEL, LL_DMA_PDATAALIGN_BYTE);
    LL_DMA_SetMemorySize(DEV_COM_PORT2_RX_DMA, DEV_COM_PORT2_RX_DMA_CHANNEL, LL_DMA_MDATAALIGN_BYTE);
}
#endif

#if EN_COM_PORT_3
/***********************************************************************************************************************
 功能：COM_PORT_3 + dma接收初始化函数
************************************************************************************************************************/
void DMA_Driver_ComPort3_Tx_Inital(void)
{
    LL_DMA_SetPeriphRequest(DEV_COM_PORT3_TX_DMA, DEV_COM_PORT3_TX_DMA_CHANNEL, DEV_COM_PORT3_TX_DMAMUX);
    LL_DMA_SetPeriphAddress(DEV_COM_PORT3_TX_DMA, DEV_COM_PORT3_TX_DMA_CHANNEL, (uint32_t)(&(DEV_COM_PORT3->TDR)));
    LL_DMA_SetMemoryAddress(DEV_COM_PORT3_TX_DMA, DEV_COM_PORT3_TX_DMA_CHANNEL, (uint32_t)(&u8UartTxBuffer[DEV_COM_PORT3_ID]));
    LL_DMA_SetDataLength(DEV_COM_PORT3_TX_DMA, DEV_COM_PORT3_TX_DMA_CHANNEL, DEV_COM_PORT3_DMA_TXBUFF_SIZE);
    LL_DMA_SetDataTransferDirection(DEV_COM_PORT3_TX_DMA, DEV_COM_PORT3_TX_DMA_CHANNEL, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
    LL_DMA_SetChannelPriorityLevel(DEV_COM_PORT3_TX_DMA, DEV_COM_PORT3_TX_DMA_CHANNEL, LL_DMA_PRIORITY_LOW);
    LL_DMA_SetMode(DEV_COM_PORT3_TX_DMA, DEV_COM_PORT3_TX_DMA_CHANNEL, LL_DMA_MODE_NORMAL);
    LL_DMA_SetPeriphIncMode(DEV_COM_PORT3_TX_DMA, DEV_COM_PORT3_TX_DMA_CHANNEL, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetMemoryIncMode(DEV_COM_PORT3_TX_DMA, DEV_COM_PORT3_TX_DMA_CHANNEL, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphSize(DEV_COM_PORT3_TX_DMA, DEV_COM_PORT3_TX_DMA_CHANNEL, LL_DMA_PDATAALIGN_BYTE);
    LL_DMA_SetMemorySize(DEV_COM_PORT3_TX_DMA, DEV_COM_PORT3_TX_DMA_CHANNEL, LL_DMA_MDATAALIGN_BYTE);
}

/***********************************************************************************************************************
 功能：COM_PORT_3 + dma接收初始化函数
************************************************************************************************************************/
void DMA_Driver_ComPort3_Rx_Inital(void)
{
    LL_DMA_SetPeriphRequest(DEV_COM_PORT3_RX_DMA, DEV_COM_PORT3_RX_DMA_CHANNEL, DEV_COM_PORT3_RX_DMAMUX);
    LL_DMA_SetPeriphAddress(DEV_COM_PORT3_RX_DMA, DEV_COM_PORT3_RX_DMA_CHANNEL, (uint32_t)(&(DEV_COM_PORT3->RDR)));
    LL_DMA_SetMemoryAddress(DEV_COM_PORT3_RX_DMA, DEV_COM_PORT3_RX_DMA_CHANNEL, (uint32_t)(&u8UartRxBuffer[DEV_COM_PORT3_ID]));
    LL_DMA_SetDataLength(DEV_COM_PORT3_RX_DMA, DEV_COM_PORT3_RX_DMA_CHANNEL, DEV_COM_PORT3_DMA_RXBUFF_SIZE);
    LL_DMA_SetDataTransferDirection(DEV_COM_PORT3_RX_DMA, DEV_COM_PORT3_RX_DMA_CHANNEL, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
    LL_DMA_SetChannelPriorityLevel(DEV_COM_PORT3_RX_DMA, DEV_COM_PORT3_RX_DMA_CHANNEL, LL_DMA_PRIORITY_LOW);
    LL_DMA_SetMode(DEV_COM_PORT3_RX_DMA, DEV_COM_PORT3_RX_DMA_CHANNEL, LL_DMA_MODE_NORMAL);
    LL_DMA_SetPeriphIncMode(DEV_COM_PORT3_RX_DMA, DEV_COM_PORT3_RX_DMA_CHANNEL, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetMemoryIncMode(DEV_COM_PORT3_RX_DMA, DEV_COM_PORT3_RX_DMA_CHANNEL, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphSize(DEV_COM_PORT3_RX_DMA, DEV_COM_PORT3_RX_DMA_CHANNEL, LL_DMA_PDATAALIGN_BYTE);
    LL_DMA_SetMemorySize(DEV_COM_PORT3_RX_DMA, DEV_COM_PORT3_RX_DMA_CHANNEL, LL_DMA_MDATAALIGN_BYTE);
}
#endif

#if EN_COM_PORT_4
/***********************************************************************************************************************
 功能：COM_PORT_4 + dma接收初始化函数
************************************************************************************************************************/
void DMA_Driver_ComPort4_Tx_Inital(void)
{
    LL_DMA_SetPeriphRequest(DEV_COM_PORT4_TX_DMA, DEV_COM_PORT4_TX_DMA_CHANNEL, DEV_COM_PORT4_TX_DMAMUX);
    LL_DMA_SetPeriphAddress(DEV_COM_PORT4_TX_DMA, DEV_COM_PORT4_TX_DMA_CHANNEL, (uint32_t)(&(DEV_COM_PORT4->TDR)));
    LL_DMA_SetMemoryAddress(DEV_COM_PORT4_TX_DMA, DEV_COM_PORT4_TX_DMA_CHANNEL, (uint32_t)(&u8UartTxBuffer[DEV_COM_PORT4_ID]));
    LL_DMA_SetDataLength(DEV_COM_PORT4_TX_DMA, DEV_COM_PORT4_TX_DMA_CHANNEL, DEV_COM_PORT4_DMA_TXBUFF_SIZE);
    LL_DMA_SetDataTransferDirection(DEV_COM_PORT4_TX_DMA, DEV_COM_PORT4_TX_DMA_CHANNEL, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
    LL_DMA_SetChannelPriorityLevel(DEV_COM_PORT4_TX_DMA, DEV_COM_PORT4_TX_DMA_CHANNEL, LL_DMA_PRIORITY_LOW);
    LL_DMA_SetMode(DEV_COM_PORT4_TX_DMA, DEV_COM_PORT4_TX_DMA_CHANNEL, LL_DMA_MODE_NORMAL);
    LL_DMA_SetPeriphIncMode(DEV_COM_PORT4_TX_DMA, DEV_COM_PORT4_TX_DMA_CHANNEL, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetMemoryIncMode(DEV_COM_PORT4_TX_DMA, DEV_COM_PORT4_TX_DMA_CHANNEL, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphSize(DEV_COM_PORT4_TX_DMA, DEV_COM_PORT4_TX_DMA_CHANNEL, LL_DMA_PDATAALIGN_BYTE);
    LL_DMA_SetMemorySize(DEV_COM_PORT4_TX_DMA, DEV_COM_PORT4_TX_DMA_CHANNEL, LL_DMA_MDATAALIGN_BYTE);
}

/***********************************************************************************************************************
 功能：COM_PORT_4 + dma接收初始化函数
************************************************************************************************************************/
void DMA_Driver_ComPort4_Rx_Inital(void)
{
    LL_DMA_SetPeriphRequest(DEV_COM_PORT4_RX_DMA, DEV_COM_PORT4_RX_DMA_CHANNEL, DEV_COM_PORT4_RX_DMAMUX);
    LL_DMA_SetPeriphAddress(DEV_COM_PORT4_RX_DMA, DEV_COM_PORT4_RX_DMA_CHANNEL, (uint32_t)(&(DEV_COM_PORT4->RDR)));
    LL_DMA_SetMemoryAddress(DEV_COM_PORT4_RX_DMA, DEV_COM_PORT4_RX_DMA_CHANNEL, (uint32_t)(&u8UartRxBuffer[DEV_COM_PORT4_ID]));
    LL_DMA_SetDataLength(DEV_COM_PORT4_RX_DMA, DEV_COM_PORT4_RX_DMA_CHANNEL, DEV_COM_PORT4_DMA_RXBUFF_SIZE);
    LL_DMA_SetDataTransferDirection(DEV_COM_PORT4_RX_DMA, DEV_COM_PORT4_RX_DMA_CHANNEL, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
    LL_DMA_SetChannelPriorityLevel(DEV_COM_PORT4_RX_DMA, DEV_COM_PORT4_RX_DMA_CHANNEL, LL_DMA_PRIORITY_LOW);
    LL_DMA_SetMode(DEV_COM_PORT4_RX_DMA, DEV_COM_PORT4_RX_DMA_CHANNEL, LL_DMA_MODE_NORMAL);
    LL_DMA_SetPeriphIncMode(DEV_COM_PORT4_RX_DMA, DEV_COM_PORT4_RX_DMA_CHANNEL, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetMemoryIncMode(DEV_COM_PORT4_RX_DMA, DEV_COM_PORT4_RX_DMA_CHANNEL, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphSize(DEV_COM_PORT4_RX_DMA, DEV_COM_PORT4_RX_DMA_CHANNEL, LL_DMA_PDATAALIGN_BYTE);
    LL_DMA_SetMemorySize(DEV_COM_PORT4_RX_DMA, DEV_COM_PORT4_RX_DMA_CHANNEL, LL_DMA_MDATAALIGN_BYTE);
}
#endif

#if EN_COM_PORT_5
/***********************************************************************************************************************
 功能：COM_PORT_5 + dma接收初始化函数
************************************************************************************************************************/
void DMA_Driver_ComPort5_Tx_Inital(void)
{
    LL_DMA_SetPeriphRequest(DEV_COM_PORT5_TX_DMA, DEV_COM_PORT5_TX_DMA_CHANNEL, DEV_COM_PORT5_TX_DMAMUX);
    LL_DMA_SetPeriphAddress(DEV_COM_PORT5_TX_DMA, DEV_COM_PORT5_TX_DMA_CHANNEL, (uint32_t)(&(DEV_COM_PORT5->TDR)));
    LL_DMA_SetMemoryAddress(DEV_COM_PORT5_TX_DMA, DEV_COM_PORT5_TX_DMA_CHANNEL, (uint32_t)(&u8UartTxBuffer[DEV_COM_PORT5_ID]));
    LL_DMA_SetDataLength(DEV_COM_PORT5_TX_DMA, DEV_COM_PORT5_TX_DMA_CHANNEL, DEV_COM_PORT5_DMA_TXBUFF_SIZE);
    LL_DMA_SetDataTransferDirection(DEV_COM_PORT5_TX_DMA, DEV_COM_PORT5_TX_DMA_CHANNEL, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
    LL_DMA_SetChannelPriorityLevel(DEV_COM_PORT5_TX_DMA, DEV_COM_PORT5_TX_DMA_CHANNEL, LL_DMA_PRIORITY_LOW);
    LL_DMA_SetMode(DEV_COM_PORT5_TX_DMA, DEV_COM_PORT5_TX_DMA_CHANNEL, LL_DMA_MODE_NORMAL);
    LL_DMA_SetPeriphIncMode(DEV_COM_PORT5_TX_DMA, DEV_COM_PORT5_TX_DMA_CHANNEL, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetMemoryIncMode(DEV_COM_PORT5_TX_DMA, DEV_COM_PORT5_TX_DMA_CHANNEL, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphSize(DEV_COM_PORT5_TX_DMA, DEV_COM_PORT5_TX_DMA_CHANNEL, LL_DMA_PDATAALIGN_BYTE);
    LL_DMA_SetMemorySize(DEV_COM_PORT5_TX_DMA, DEV_COM_PORT5_TX_DMA_CHANNEL, LL_DMA_MDATAALIGN_BYTE);
}

/***********************************************************************************************************************
 功能：COM_PORT_5 + dma接收初始化函数
************************************************************************************************************************/
void DMA_Driver_ComPort5_Rx_Inital(void)
{
    LL_DMA_SetPeriphRequest(DEV_COM_PORT5_RX_DMA, DEV_COM_PORT5_RX_DMA_CHANNEL, DEV_COM_PORT5_RX_DMAMUX);                           //DMA通道复用配置
    LL_DMA_SetPeriphAddress(DEV_COM_PORT5_RX_DMA, DEV_COM_PORT5_RX_DMA_CHANNEL, (uint32_t)(&(DEV_COM_PORT5->RDR)));                 //设置DMA外设地址
    LL_DMA_SetMemoryAddress(DEV_COM_PORT5_RX_DMA, DEV_COM_PORT5_RX_DMA_CHANNEL, (uint32_t)(&u8UartRxBuffer[DEV_COM_PORT5_ID]));     //设置DMA内存地址
    LL_DMA_SetDataLength(DEV_COM_PORT5_RX_DMA, DEV_COM_PORT5_RX_DMA_CHANNEL, DEV_COM_PORT5_DMA_RXBUFF_SIZE);                        //DMA传输字节数
    LL_DMA_SetDataTransferDirection(DEV_COM_PORT5_RX_DMA, DEV_COM_PORT5_RX_DMA_CHANNEL, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);         //DMA传输方向（外设至内存）
    LL_DMA_SetChannelPriorityLevel(DEV_COM_PORT5_RX_DMA, DEV_COM_PORT5_RX_DMA_CHANNEL, LL_DMA_PRIORITY_LOW);                        //DMA通道优先级
    LL_DMA_SetMode(DEV_COM_PORT5_RX_DMA, DEV_COM_PORT5_RX_DMA_CHANNEL, LL_DMA_MODE_NORMAL);                                         //传输模式（单次、循环）
    LL_DMA_SetPeriphIncMode(DEV_COM_PORT5_RX_DMA, DEV_COM_PORT5_RX_DMA_CHANNEL, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetMemoryIncMode(DEV_COM_PORT5_RX_DMA, DEV_COM_PORT5_RX_DMA_CHANNEL, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphSize(DEV_COM_PORT5_RX_DMA, DEV_COM_PORT5_RX_DMA_CHANNEL, LL_DMA_PDATAALIGN_BYTE);                               //一次从外设取单个字节
    LL_DMA_SetMemorySize(DEV_COM_PORT5_RX_DMA, DEV_COM_PORT5_RX_DMA_CHANNEL, LL_DMA_MDATAALIGN_BYTE);                               //一次放置与内存占用单个字节
}
#endif

#if EN_COM_PORT_6
/***********************************************************************************************************************
 功能：COM_PORT_6 + dma发送初始化函数
************************************************************************************************************************/
void DMA_Driver_ComPort6_Tx_Inital(void)
{
    LL_DMA_SetPeriphRequest(DEV_COM_PORT6_TX_DMA, DEV_COM_PORT6_TX_DMA_CHANNEL, DEV_COM_PORT6_TX_DMAMUX);
    LL_DMA_SetPeriphAddress(DEV_COM_PORT6_TX_DMA, DEV_COM_PORT6_TX_DMA_CHANNEL, (uint32_t)(&(DEV_COM_PORT6->TDR)));
    LL_DMA_SetMemoryAddress(DEV_COM_PORT6_TX_DMA, DEV_COM_PORT6_TX_DMA_CHANNEL, (uint32_t)&u8UartTxBuffer[DEV_COM_PORT6_ID]);
    LL_DMA_SetDataLength(DEV_COM_PORT6_TX_DMA, DEV_COM_PORT6_TX_DMA_CHANNEL, DEV_COM_PORT6_DMA_TXBUFF_SIZE);
    LL_DMA_SetDataTransferDirection(DEV_COM_PORT6_TX_DMA, DEV_COM_PORT6_TX_DMA_CHANNEL, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
    LL_DMA_SetChannelPriorityLevel(DEV_COM_PORT6_TX_DMA, DEV_COM_PORT6_TX_DMA_CHANNEL, LL_DMA_PRIORITY_LOW);
    LL_DMA_SetMode(DEV_COM_PORT6_TX_DMA, DEV_COM_PORT6_TX_DMA_CHANNEL, LL_DMA_MODE_NORMAL);
    LL_DMA_SetPeriphIncMode(DEV_COM_PORT6_TX_DMA, DEV_COM_PORT6_TX_DMA_CHANNEL, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetMemoryIncMode(DEV_COM_PORT6_TX_DMA, DEV_COM_PORT6_TX_DMA_CHANNEL, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphSize(DEV_COM_PORT6_TX_DMA, DEV_COM_PORT6_TX_DMA_CHANNEL, LL_DMA_PDATAALIGN_BYTE);
    LL_DMA_SetMemorySize(DEV_COM_PORT6_TX_DMA, DEV_COM_PORT6_TX_DMA_CHANNEL, LL_DMA_MDATAALIGN_BYTE);
}

/***********************************************************************************************************************
 功能：COM_PORT_6 + dma接收初始化函数
************************************************************************************************************************/
void DMA_Driver_ComPort6_Rx_Inital(void)
{
    LL_DMA_SetPeriphRequest(DEV_COM_PORT6_RX_DMA, DEV_COM_PORT6_RX_DMA_CHANNEL, DEV_COM_PORT6_RX_DMAMUX);
    LL_DMA_SetPeriphAddress(DEV_COM_PORT6_RX_DMA, DEV_COM_PORT6_RX_DMA_CHANNEL, (uint32_t)(&(DEV_COM_PORT6->RDR)));
    LL_DMA_SetMemoryAddress(DEV_COM_PORT6_RX_DMA, DEV_COM_PORT6_RX_DMA_CHANNEL, (uint32_t)&u8UartRxBuffer[DEV_COM_PORT6_ID]);
    LL_DMA_SetDataLength(DEV_COM_PORT6_RX_DMA, DEV_COM_PORT6_RX_DMA_CHANNEL, DEV_COM_PORT6_DMA_RXBUFF_SIZE);
    LL_DMA_SetDataTransferDirection(DEV_COM_PORT6_RX_DMA, DEV_COM_PORT6_RX_DMA_CHANNEL, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
    LL_DMA_SetChannelPriorityLevel(DEV_COM_PORT6_RX_DMA, DEV_COM_PORT6_RX_DMA_CHANNEL, LL_DMA_PRIORITY_LOW);
    LL_DMA_SetMode(DEV_COM_PORT6_RX_DMA, DEV_COM_PORT6_RX_DMA_CHANNEL, LL_DMA_MODE_NORMAL);
    LL_DMA_SetPeriphIncMode(DEV_COM_PORT6_RX_DMA, DEV_COM_PORT6_RX_DMA_CHANNEL, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetMemoryIncMode(DEV_COM_PORT6_RX_DMA, DEV_COM_PORT6_RX_DMA_CHANNEL, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphSize(DEV_COM_PORT6_RX_DMA, DEV_COM_PORT6_RX_DMA_CHANNEL, LL_DMA_PDATAALIGN_BYTE);
    LL_DMA_SetMemorySize(DEV_COM_PORT6_RX_DMA, DEV_COM_PORT6_RX_DMA_CHANNEL, LL_DMA_MDATAALIGN_BYTE);
}
#endif


/***********************************************************************************************************************
 功能：DMA的统一初始化函数
************************************************************************************************************************/
void DMA_Driver_Init(void)
{

    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);

#if EN_COM_PORT_1
    DMA_Driver_ComPort1_Tx_Inital();
    DMA_Driver_ComPort1_Rx_Inital();
#endif

#if EN_COM_PORT_2
    DMA_Driver_ComPort2_Tx_Inital();
    DMA_Driver_ComPort2_Rx_Inital();
#endif

#if EN_COM_PORT_3
    DMA_Driver_ComPort3_Tx_Inital();
    DMA_Driver_ComPort3_Rx_Inital();
#endif

#if EN_COM_PORT_4
    DMA_Driver_ComPort4_Tx_Inital();
    DMA_Driver_ComPort4_Rx_Inital();
#endif

#if EN_COM_PORT_5
    DMA_Driver_ComPort5_Tx_Inital();
    DMA_Driver_ComPort5_Rx_Inital();
#endif

#if EN_COM_PORT_6
    DMA_Driver_ComPort6_Tx_Inital();
    DMA_Driver_ComPort6_Rx_Inital();
#endif

}



/***********************************************************************************************************************
* Copyright (c)  CVTE All rights reserved.  * * * END OF FILE
************************************************************************************************************************/
