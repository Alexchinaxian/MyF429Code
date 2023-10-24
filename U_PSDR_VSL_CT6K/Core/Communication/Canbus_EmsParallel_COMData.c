/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Canbus_EmsParallel_COMData.c
 用途 : CanbusEms并机协议相关函数
***********************************************************************************************************************/
#ifndef _CANBUS_EMSPARALLEL_COMDATA_C_
#define _CANBUS_EMSPARALLEL_COMDATA_C_

#include "Canbus_EmsParallel_COMData.h"

uint8_t u8Payload2[8] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};

Can_MessageDef EMSCan_SendMessage;
Can_MessageDef EMSCan_ReceiveMessage;

void EMSCan_SendPacket(void)
{
    EMSCan_SendMessage.u32ID = 0X01234567;
    EMSCan_SendMessage.u8Lenth = 8;
    memcpy(EMSCan_SendMessage.u8Data, u8Payload2, 8);
    can2_SendPacket(EMSCan_SendMessage);
}

void EMSCan_ReceivePacket(void)
{
    can2_ReceivePacket(&EMSCan_ReceiveMessage);
}

#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

