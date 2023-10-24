/***********************************************************************************************************************
* Copyright (c)  , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
* 文件名        : can_driver.c
* 用途         : Can驱动部分
***********************************************************************************************************************/
#ifndef __CAN_Device_C__
#define __CAN_Device_C__

#include "can_driver.h"

#if CANBUS_MOUDLE

static Can_RxMessageDef Can1_Rx_Message,Can2_Rx_Message;

uint8_t u8Can1ReceiveFlag = STATUS_FALSE;   
uint8_t u8Can2ReceiveFlag = STATUS_FALSE;
FDCAN_HandleTypeDef hfdcan1,hfdcan2;
Can_Fifo  CAN1_RxFifo = {0};

static void pushCanData(Can_Fifo *fifo, Can_MessageDef *buf)
{
    uint8_t next = (fifo->head + 1) % CAN_BUF_CNT;
    if(next != fifo->tail)
    {
        Can_MessageDef *msg = &fifo->Can_Message[fifo->head];
        memcpy(msg, buf, sizeof(Can_MessageDef));
        fifo->head = next;
    }
}

//static uint8_t popCanData(Can_Fifo *fifo, Can_MessageDef *buf)
//{
//    uint8_t ret = 0;
//    if(fifo->head != fifo->tail)
//    {
//        Can_MessageDef *msg = &(fifo->Can_Message[fifo->tail]);
//        memcpy(buf, msg, sizeof(Can_MessageDef));
//        fifo->tail = (fifo->tail + 1) % CAN_BUF_CNT;
//        ret = 1;
//    }
//    return ret;
//}

static uint8_t read_Can_msg(Can_MessageDef *Can_Message)
{
    uint8_t ret = 0;
    if(CAN1_RxFifo.head != CAN1_RxFifo.tail)
    {
        Can_Message->u32ID = CAN1_RxFifo.Can_Message[CAN1_RxFifo.tail].u32ID;
        Can_Message->u8Lenth = CAN1_RxFifo.Can_Message[CAN1_RxFifo.tail].u8Lenth;
        memcpy(Can_Message->u8Data, CAN1_RxFifo.Can_Message[CAN1_RxFifo.tail].u8Data, CAN1_RxFifo.Can_Message[CAN1_RxFifo.tail].u8Lenth);
        CAN1_RxFifo.tail = (CAN1_RxFifo.tail + 1) % CAN_BUF_CNT;
        ret = 1;
    }
    return ret;
}

/***********************************************************************************************************************
 功能：初始化CAN1
***********************************************************************************************************************/	
void bsp_InitCan1(void)
{	 
    GPIO_InitTypeDef  GPIO_InitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
    FDCAN_FilterTypeDef sFilterConfig1;

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
    PeriphClkInitStruct.FdcanClockSelection = RCC_FDCANCLKSOURCE_PCLK1;

    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

    __HAL_RCC_FDCAN_CLK_ENABLE();
    FDCAN1_TX_GPIO_CLK_ENABLE();
    FDCAN1_RX_GPIO_CLK_ENABLE();

    GPIO_InitStruct.Pin       = FDCAN1_TX_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = FDCAN1_TX_AF;
    HAL_GPIO_Init(FDCAN1_TX_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin       = FDCAN1_RX_PIN;
    GPIO_InitStruct.Alternate = FDCAN1_RX_AF;
    HAL_GPIO_Init(FDCAN1_RX_GPIO_PORT, &GPIO_InitStruct);
    
    hfdcan1.Instance = FDCAN1;                        
    hfdcan1.Init.ClockDivider = FDCAN_CLOCK_DIV1;  
	hfdcan1.Init.FrameFormat = FDCAN_FRAME_CLASSIC; 
	hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;         
	hfdcan1.Init.AutoRetransmission = ENABLE;     
	hfdcan1.Init.TransmitPause = ENABLE;          
	hfdcan1.Init.ProtocolException = ENABLE;      
    
	hfdcan1.Init.NominalPrescaler = 4; 	 
	hfdcan1.Init.NominalSyncJumpWidth = 4; 
	hfdcan1.Init.NominalTimeSeg1 = 27; 	  
	hfdcan1.Init.NominalTimeSeg2 = 4;    

	hfdcan1.Init.DataPrescaler = 4;      
	hfdcan1.Init.DataSyncJumpWidth = 4;  
	hfdcan1.Init.DataTimeSeg1 = 27; 		
	hfdcan1.Init.DataTimeSeg2 = 4;      
		
	hfdcan1.Init.StdFiltersNbr = 1;         			
	hfdcan1.Init.ExtFiltersNbr = 0;         			

	hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION; 
	HAL_FDCAN_Init(&hfdcan1);

	sFilterConfig1.IdType = FDCAN_STANDARD_ID;             
	sFilterConfig1.FilterIndex = 0;   						
	sFilterConfig1.FilterType = FDCAN_FILTER_MASK;          
	sFilterConfig1.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;    
	sFilterConfig1.FilterID1 = 0x7FF;                      
	sFilterConfig1.FilterID2 = 0x000; 						
	HAL_FDCAN_ConfigFilter(&hfdcan1, &sFilterConfig1);   
	
    HAL_FDCAN_ConfigGlobalFilter(&hfdcan1, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE);

	HAL_FDCAN_Start(&hfdcan1);
    
    HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);

    NVIC_SetPriority(TIM16_FDCAN_IT0_IRQn, 0);
    NVIC_EnableIRQ(TIM16_FDCAN_IT0_IRQn);        	
}

/***********************************************************************************************************************
 功能：初始化CAN2
***********************************************************************************************************************/	
void bsp_InitCan2(void)
{	
    GPIO_InitTypeDef  GPIO_InitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
    FDCAN_FilterTypeDef sFilterConfig2;

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
    PeriphClkInitStruct.FdcanClockSelection = RCC_FDCANCLKSOURCE_PCLK1;

    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);


    __HAL_RCC_FDCAN_CLK_ENABLE();
    FDCAN2_TX_GPIO_CLK_ENABLE();
    FDCAN2_RX_GPIO_CLK_ENABLE();

    GPIO_InitStruct.Pin       = FDCAN2_TX_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = FDCAN2_TX_AF;
    HAL_GPIO_Init(FDCAN2_TX_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin       = FDCAN2_RX_PIN;
    GPIO_InitStruct.Alternate = FDCAN2_RX_AF;
    HAL_GPIO_Init(FDCAN2_RX_GPIO_PORT, &GPIO_InitStruct);

    hfdcan2.Instance = FDCAN2;                       
    hfdcan2.Init.ClockDivider = FDCAN_CLOCK_DIV1;
    hfdcan2.Init.FrameFormat = FDCAN_FRAME_CLASSIC; 
    hfdcan2.Init.Mode = FDCAN_MODE_NORMAL;         
    hfdcan2.Init.AutoRetransmission = ENABLE;     
    hfdcan2.Init.TransmitPause = ENABLE;        
    hfdcan2.Init.ProtocolException = ENABLE;      

    hfdcan2.Init.NominalPrescaler = 2; 	  
    hfdcan2.Init.NominalSyncJumpWidth = 4; 
    hfdcan2.Init.NominalTimeSeg1 = 27; 	 
    hfdcan2.Init.NominalTimeSeg2 = 4;      

    hfdcan2.Init.DataPrescaler = 2;     
    hfdcan2.Init.DataSyncJumpWidth = 4;  
    hfdcan2.Init.DataTimeSeg1 = 27; 		
    hfdcan2.Init.DataTimeSeg2 = 4;    
    
    hfdcan2.Init.StdFiltersNbr = 0;         			      
    hfdcan2.Init.ExtFiltersNbr = 1;         			

    hfdcan2.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION; 
    HAL_FDCAN_Init(&hfdcan2);

    sFilterConfig2.IdType = FDCAN_EXTENDED_ID;              
    sFilterConfig2.FilterIndex = 0;   						
    sFilterConfig2.FilterType = FDCAN_FILTER_MASK;         
    sFilterConfig2.FilterConfig = FDCAN_FILTER_TO_RXFIFO1; 
    sFilterConfig2.FilterID1 = 0x7FFF;                       
    sFilterConfig2.FilterID2 = 0x0000; 						
    HAL_FDCAN_ConfigFilter(&hfdcan2, &sFilterConfig2);     

    HAL_FDCAN_ConfigGlobalFilter(&hfdcan2, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE);
    
    HAL_FDCAN_Start(&hfdcan2);
    
    HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0);
    
    NVIC_SetPriority(TIM17_FDCAN_IT1_IRQn, 0);
    NVIC_EnableIRQ(TIM17_FDCAN_IT1_IRQn);  
}

/***********************************************************************************************************************
 功能：关闭CAN1
***********************************************************************************************************************/	
void bsp_DeInitCan1(void)
{
    __HAL_RCC_FDCAN_FORCE_RESET();
    __HAL_RCC_FDCAN_RELEASE_RESET();

    HAL_GPIO_DeInit(FDCAN1_TX_GPIO_PORT, FDCAN1_TX_PIN);
    HAL_GPIO_DeInit(FDCAN1_RX_GPIO_PORT, FDCAN1_RX_PIN);

    HAL_NVIC_DisableIRQ(TIM16_FDCAN_IT0_IRQn);
}

/***********************************************************************************************************************
 功能：关闭CAN2
***********************************************************************************************************************/
void bsp_DeInitCan2(void)
{
    __HAL_RCC_FDCAN_FORCE_RESET();
    __HAL_RCC_FDCAN_RELEASE_RESET();

    HAL_GPIO_DeInit(FDCAN2_TX_GPIO_PORT, FDCAN2_TX_PIN);
    HAL_GPIO_DeInit(FDCAN2_RX_GPIO_PORT, FDCAN2_RX_PIN);

    HAL_NVIC_DisableIRQ(TIM17_FDCAN_IT1_IRQn);
}
                                                                                                                                     
/***********************************************************************************************************************
 功能： CAN1中断服务程序-回调函数
***********************************************************************************************************************/
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    Can_MessageDef Can_ReceiveMessage;
    if (hfdcan == &hfdcan1)
	{
		if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
		{
			HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &Can1_Rx_Message.CanRxHeader, Can1_Rx_Message.CanRxData);
           
            Can_ReceiveMessage.u32ID = Can1_Rx_Message.CanRxHeader.Identifier;
            Can_ReceiveMessage.u8Lenth = Can1_Rx_Message.CanRxHeader.DataLength >> 16;
            memcpy(Can_ReceiveMessage.u8Data, Can1_Rx_Message.CanRxData, Can_ReceiveMessage.u8Lenth);
            
            pushCanData(&CAN1_RxFifo, &Can_ReceiveMessage);
            
            u8Can1ReceiveFlag = STATUS_TRUE;
		}
	}
}

/***********************************************************************************************************************
 功能： CAN2中断服务程序-回调函数
***********************************************************************************************************************/
void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs)
{
    if (hfdcan == &hfdcan2)
	{
		if ((RxFifo1ITs & FDCAN_IT_RX_FIFO1_NEW_MESSAGE) != RESET)
		{
			HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO1, &Can2_Rx_Message.CanRxHeader, Can2_Rx_Message.CanRxData);
            u8Can2ReceiveFlag = STATUS_TRUE;
		}
	}
}

/***********************************************************************************************************************
 功能： CAN初始化
***********************************************************************************************************************/
void CAN_Driver_Initial(void)
{
	bsp_InitCan1();
	bsp_InitCan2();
}     

/***********************************************************************************************************************
 功能： CAN失能
***********************************************************************************************************************/
void CAN_Driver_DeInitial(void)
{	
	bsp_DeInitCan1();
	bsp_DeInitCan2();
}

/***********************************************************************************************************************
 功能： CAN1发送数据
***********************************************************************************************************************/
void can1_SendPacket(Can_MessageDef Can_SendMessage)
{		
	FDCAN_TxHeaderTypeDef TxHeader = {0};

	TxHeader.Identifier = Can_SendMessage.u32ID;             		
	TxHeader.IdType = FDCAN_STANDARD_ID;     		
	TxHeader.TxFrameType = FDCAN_DATA_FRAME;		 
	TxHeader.DataLength = (uint32_t)Can_SendMessage.u8Lenth << 16;      
	TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE; 
	TxHeader.BitRateSwitch = FDCAN_BRS_OFF;           
	TxHeader.FDFormat = FDCAN_CLASSIC_CAN;               
	TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	TxHeader.MessageMarker = 0;                     
	
    HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, Can_SendMessage.u8Data); 
}

/***********************************************************************************************************************
 功能： CAN2发送数据
***********************************************************************************************************************/
void can2_SendPacket(Can_MessageDef Can_SendMessage)
{		
	FDCAN_TxHeaderTypeDef TxHeader = {0};
	
	TxHeader.Identifier = Can_SendMessage.u32ID;            		
	TxHeader.IdType = FDCAN_EXTENDED_ID;			
	TxHeader.TxFrameType = FDCAN_DATA_FRAME;		
	TxHeader.DataLength = (uint32_t)Can_SendMessage.u8Lenth << 16;		
	TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	TxHeader.BitRateSwitch = FDCAN_BRS_OFF;			
	TxHeader.FDFormat = FDCAN_CLASSIC_CAN;				
	TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	TxHeader.MessageMarker = 0;
	
    HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &TxHeader, Can_SendMessage.u8Data);   
}

/***********************************************************************************************************************
 功能： CAN1接收数据
***********************************************************************************************************************/
void can1_ReceivePacket(Can_MessageDef *Can_ReceiveMessage)
{		
//    Can_ReceiveMessage->u32ID = Can1_Rx_Message.CanRxHeader.Identifier;
//    Can_ReceiveMessage->u8Lenth = Can1_Rx_Message.CanRxHeader.DataLength >> 16;
//    memcpy(Can_ReceiveMessage->u8Data, Can1_Rx_Message.CanRxData, Can_ReceiveMessage->u8Lenth);
    
    if(read_Can_msg(Can_ReceiveMessage) == 1)
    {
        u8Can1ReceiveFlag = STATUS_TRUE;   
    }
    else 
    {
        u8Can1ReceiveFlag = STATUS_FALSE;
    }
}

/***********************************************************************************************************************
 功能： CAN2接收数据
***********************************************************************************************************************/
void can2_ReceivePacket(Can_MessageDef *Can_ReceiveMessage)
{		
    Can_ReceiveMessage->u32ID = Can2_Rx_Message.CanRxHeader.Identifier;
    Can_ReceiveMessage->u8Lenth = Can2_Rx_Message.CanRxHeader.DataLength >> 16;
    memcpy(Can_ReceiveMessage->u8Data, Can2_Rx_Message.CanRxData, Can_ReceiveMessage->u8Lenth);
    u8Can2ReceiveFlag = STATUS_FALSE;
}

#endif
#endif /***Module End***/
/***********************************************************************************************************************
* * Copyright (c)  CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
