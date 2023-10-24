/***********************************************************************************************************************
* Copyright (c)  , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
* 文件名        : dma_driver.h
* 用途         : dma_driver
***********************************************************************************************************************/
#ifndef __DMA_DRIVER_H
#define __DMA_DRIVER_H

#include "MCU.h"


#define DMA_DRIVER_MOUDLE (1)
#if DMA_DRIVER_MOUDLE



/***********************************************************************************************************************
* * Macro definitions
***********************************************************************************************************************/
#define PR_DMA1                           DMA1
#define PR_DMA2                           DMA2

#define PR_DMAMUX_REQ_USART1_TX           LL_DMAMUX_REQ_USART1_TX
#define PR_DMAMUX_REQ_USART1_RX           LL_DMAMUX_REQ_USART1_RX

#define PR_DMAMUX_REQ_USART2_TX           LL_DMAMUX_REQ_USART2_TX
#define PR_DMAMUX_REQ_USART2_RX           LL_DMAMUX_REQ_USART2_RX

#define PR_DMAMUX_REQ_USART3_TX           LL_DMAMUX_REQ_USART3_TX
#define PR_DMAMUX_REQ_USART3_RX           LL_DMAMUX_REQ_USART3_RX

#define PR_DMAMUX_REQ_USART4_TX           LL_DMAMUX_REQ_USART4_TX
#define PR_DMAMUX_REQ_USART4_RX           LL_DMAMUX_REQ_USART4_RX

#define PR_DMAMUX_REQ_USART5_TX           LL_DMAMUX_REQ_USART5_TX
#define PR_DMAMUX_REQ_USART5_RX           LL_DMAMUX_REQ_USART5_RX

#define PR_DMAMUX_REQ_USART6_TX           LL_DMAMUX_REQ_USART6_TX
#define PR_DMAMUX_REQ_USART6_RX           LL_DMAMUX_REQ_USART6_RX

#define PR_DMA_CHANNEL_1                  LL_DMA_CHANNEL_1
#define PR_DMA_CHANNEL_2                  LL_DMA_CHANNEL_2
#define PR_DMA_CHANNEL_3                  LL_DMA_CHANNEL_3
#define PR_DMA_CHANNEL_4                  LL_DMA_CHANNEL_4
#define PR_DMA_CHANNEL_5                  LL_DMA_CHANNEL_5
#define PR_DMA_CHANNEL_6                  LL_DMA_CHANNEL_6
#define PR_DMA_CHANNEL_7                  LL_DMA_CHANNEL_7
#define PR_DMA_CHANNEL_ALL                LL_DMA_CHANNEL_ALL

#define DMA_Driver_EnableIT_TC(pDMAx, u8Channel)                        LL_DMA_EnableIT_TC(pDMAx, u8Channel)
#define DMA_Driver_DisableIT_TC(pDMAx, u8Channel)                       LL_DMA_DisableIT_TC(pDMAx, u8Channel)

#define DMA_Driver_IsActiveFlag_TC1(pDMAx)                              LL_DMA_IsActiveFlag_TC1(pDMAx)
#define DMA_Driver_IsActiveFlag_TC2(pDMAx)                              LL_DMA_IsActiveFlag_TC2(pDMAx)
#define DMA_Driver_IsActiveFlag_TC3(pDMAx)                              LL_DMA_IsActiveFlag_TC3(pDMAx)
#define DMA_Driver_IsActiveFlag_TC4(pDMAx)                              LL_DMA_IsActiveFlag_TC4(pDMAx)
#define DMA_Driver_IsActiveFlag_TC5(pDMAx)                              LL_DMA_IsActiveFlag_TC5(pDMAx)
#define DMA_Driver_IsActiveFlag_TC6(pDMAx)                              LL_DMA_IsActiveFlag_TC6(pDMAx)
#define DMA_Driver_IsActiveFlag_TC7(pDMAx)                              LL_DMA_IsActiveFlag_TC7(pDMAx)
//#define DMA_Driver_IsActiveFlag_TC8(pDMAx)                              LL_DMA_IsActiveFlag_TC8(pDMAx)

#define DMA_Driver_ClearFlag_TC1(pDMAx)                                 LL_DMA_ClearFlag_TC1(pDMAx)
#define DMA_Driver_ClearFlag_TC2(pDMAx)                                 LL_DMA_ClearFlag_TC2(pDMAx)
#define DMA_Driver_ClearFlag_TC3(pDMAx)                                 LL_DMA_ClearFlag_TC3(pDMAx)
#define DMA_Driver_ClearFlag_TC4(pDMAx)                                 LL_DMA_ClearFlag_TC4(pDMAx)
#define DMA_Driver_ClearFlag_TC5(pDMAx)                                 LL_DMA_ClearFlag_TC5(pDMAx)
#define DMA_Driver_ClearFlag_TC6(pDMAx)                                 LL_DMA_ClearFlag_TC6(pDMAx)
#define DMA_Driver_ClearFlag_TC7(pDMAx)                                 LL_DMA_ClearFlag_TC7(pDMAx)
//#define DMA_Driver_ClearFlag_TC8(pDMAx)                                 LL_DMA_ClearFlag_TC8(pDMAx)

#define DMA_Driver_EnableChannel(pDMAx, u8Channel)                      LL_DMA_EnableChannel(pDMAx, u8Channel)
#define DMA_Driver_DisableChannel(pDMAx, u8Channel)                     LL_DMA_DisableChannel(pDMAx, u8Channel)
#define DMA_Driver_SetDataLength(pDMAx, u8Channel, u16Length)           LL_DMA_SetDataLength(pDMAx, u8Channel, u16Length)
#define DMA_Driver_GetDataLength(pDMAx, u8Channel)                      LL_DMA_GetDataLength(pDMAx, u8Channel)


/***********************************************************************************************************************
* * Enum definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
* * Typedef struct
***********************************************************************************************************************/

/***********************************************************************************************************************
 * * Extern variables
***********************************************************************************************************************/

/***********************************************************************************************************************
 * * Extern functions
***********************************************************************************************************************/



#if EN_COM_PORT_1
extern void DMA_Driver_ComPort1_Tx_Inital(void);
extern void DMA_Driver_ComPort1_Rx_Inital(void);
#else
#define DMA_Driver_ComPort1_Tx_Inital(void)
#define DMA_Driver_ComPort1_Rx_Inital(void)
#endif

#if EN_COM_PORT_2
extern void DMA_Driver_ComPort2_Tx_Inital(void);
extern void DMA_Driver_ComPort2_Rx_Inital(void);
#else
#define DMA_Driver_ComPort2_Tx_Inital(void)
#define DMA_Driver_ComPort2_Rx_Inital(void)
#endif

#if EN_COM_PORT_3
extern void DMA_Driver_ComPort3_Tx_Inital(void);
extern void DMA_Driver_ComPort3_Rx_Inital(void);
#else
#define DMA_Driver_ComPort3_Tx_Inital(void)
#define DMA_Driver_ComPort3_Rx_Inital(void)
#endif

#if EN_COM_PORT_4
extern void DMA_Driver_ComPort4_Tx_Inital(void);
extern void DMA_Driver_ComPort4_Rx_Inital(void);
#else
#define DMA_Driver_ComPort4_Tx_Inital(void)
#define DMA_Driver_ComPort4_Rx_Inital(void)
#endif

#if EN_COM_PORT_5
extern void DMA_Driver_ComPort5_Tx_Inital(void);
extern void DMA_Driver_ComPort5_Rx_Inital(void);
#else
#define DMA_Driver_ComPort5_Tx_Inital(void)
#define DMA_Driver_ComPort5_Rx_Inital(void)
#endif

#if EN_COM_PORT_6
extern void DMA_Driver_ComPort6_Tx_Inital(void);
extern void DMA_Driver_ComPort6_Rx_Inital(void);
#else
#define DMA_Driver_ComPort6_Tx_Inital(void)
#define DMA_Driver_ComPort6_Rx_Inital(void)
#endif

extern void DMA_Driver_Init(void);

#endif /***Module End***/
#endif
/***********************************************************************************************************************
* * Copyright (c)  CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
