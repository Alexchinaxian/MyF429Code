/***********************************************************************************************************************
* Copyright (c)  , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
* 文件名        : can_device.h
* 用途         : Can设备头文件
***********************************************************************************************************************/
#ifndef __CAN_Device_H__
#define __CAN_Device_H__

#include "HeadFile.h"
#include "MCU.h"

#define CAN_BUF_CNT					    (30)

#define FDCAN1_TX_PIN                   GPIO_PIN_5
#define FDCAN1_TX_GPIO_PORT             GPIOC
#define FDCAN1_TX_AF                    GPIO_AF3_FDCAN1
#define FDCAN1_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOC_CLK_ENABLE()

#define FDCAN1_RX_PIN                   GPIO_PIN_4
#define FDCAN1_RX_GPIO_PORT             GPIOC
#define FDCAN1_RX_AF                    GPIO_AF3_FDCAN1
#define FDCAN1_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOC_CLK_ENABLE()


#define FDCAN2_TX_PIN                   GPIO_PIN_3
#define FDCAN2_TX_GPIO_PORT             GPIOC
#define FDCAN2_TX_AF                    GPIO_AF3_FDCAN2
#define FDCAN2_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOC_CLK_ENABLE()

#define FDCAN2_RX_PIN                   GPIO_PIN_2
#define FDCAN2_RX_GPIO_PORT             GPIOC
#define FDCAN2_RX_AF                    GPIO_AF3_FDCAN2
#define FDCAN2_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOC_CLK_ENABLE()


typedef struct
{
    FDCAN_RxHeaderTypeDef CanRxHeader;
    uint8_t CanRxData[8];
}Can_RxMessageDef;

typedef struct
{
    uint32_t u32ID;
    uint8_t  u8Lenth;
    uint8_t  u8Data[8];
}Can_MessageDef;

typedef struct
{
    uint8_t  head;
    uint8_t  tail;
    Can_MessageDef Can_Message[CAN_BUF_CNT];
}Can_Fifo;

extern uint8_t u8Can1ReceiveFlag;   
extern uint8_t u8Can2ReceiveFlag;
extern FDCAN_HandleTypeDef hfdcan1,hfdcan2;

extern void CAN_Driver_Initial(void);
extern void CAN_Driver_DeInitial(void);
extern void can1_SendPacket(Can_MessageDef Can_SendMessage);
extern void can2_SendPacket(Can_MessageDef Can_SendMessage);
extern void can1_ReceivePacket(Can_MessageDef *Can_ReceiveMessage);
extern void can2_ReceivePacket(Can_MessageDef *Can_ReceiveMessage);

#endif
/***********************************************************************************************************************
* * Copyright (c)  CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
