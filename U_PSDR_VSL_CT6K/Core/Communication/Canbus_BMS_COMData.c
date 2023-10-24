/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Canbus_BMS_COMData.c
 用途 : CanbusBMS协议相关函数
***********************************************************************************************************************/
#ifndef _CANBUS_BMS_COMDATA_C_
#define _CANBUS_BMS_COMDATA_C_

#include "Canbus_BMS_COMData.h"

BmsCanDataPylon_TypeDef     tBmsCanDataPylon;       //BMSCan协议Pylon数据结构

uint8_t u8Payload1[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

Can_MessageDef BMSCan_SendMessage;
Can_MessageDef BMSCan_ReceiveMessage;

void BMSCan_SendPacket(void)
{
    BMSCan_SendMessage.u32ID = UNIVERSAL;
    BMSCan_SendMessage.u8Lenth = 8;
    memcpy(BMSCan_SendMessage.u8Data, u8Payload1, 8);
    can1_SendPacket(BMSCan_SendMessage);
}

void BMSCan_ReceivePacket(void)
{    
    can1_ReceivePacket(&BMSCan_ReceiveMessage);
    switch (BMSCan_ReceiveMessage.u32ID)
    {
        case OPERATION_LIMIT:
            memcpy(&tBmsCanDataPylon.OperationLimit.u16ChgVoltLimit, &BMSCan_ReceiveMessage.u8Data, sizeof(tBmsCanDataPylon.OperationLimit));
            break;                                              
        case SOC_AND_SOH:
            memcpy(&tBmsCanDataPylon.SOCandSOH.u16AvgSOC, &BMSCan_ReceiveMessage.u8Data, sizeof(tBmsCanDataPylon.SOCandSOH));
            break;
        case ANALOG_QUANTITY:
            memcpy(&tBmsCanDataPylon.AnalogQuantity.s16AvgVolt, &BMSCan_ReceiveMessage.u8Data, sizeof(tBmsCanDataPylon.AnalogQuantity));
            break;       
        case PROTECT_AND_ALARM:
            memcpy(&tBmsCanDataPylon.ProtectAndAlarm.Protect1_t, &BMSCan_ReceiveMessage.u8Data, sizeof(&tBmsCanDataPylon.ProtectAndAlarm));
            break;  
        case BMS_REQUEST:
            memcpy(&tBmsCanDataPylon.BMSRequest, &BMSCan_ReceiveMessage.u8Data, sizeof(tBmsCanDataPylon.BMSRequest));
            break;        
        case BRAND:
            memcpy(&tBmsCanDataPylon.Brand, &BMSCan_ReceiveMessage.u8Data, sizeof(tBmsCanDataPylon.Brand));
            break;
        case BMS_CUSTOMIZED:
            memcpy(&tBmsCanDataPylon.BMS_Customized.MosFail_t, &BMSCan_ReceiveMessage.u8Data, sizeof(tBmsCanDataPylon.BMS_Customized));
            break;               
        default:
            break;
    }
}

/***************************************************************************
 功能:LCD屏电池包的数据绑定（派能协议）
****************************************************************************/
void GetDisplayRealTimePlyonBMSCanData(Display_DATA_BMS* ptDisplayBmsData)
{
    ptDisplayBmsData->u16BMSVoltage = (uint16_t) (tBmsCanDataPylon.AnalogQuantity.s16AvgVolt / 10);                //后续优化
    ptDisplayBmsData->sBMSCurrent = tBmsCanDataPylon.AnalogQuantity.s16TotalCurrent / -1 ;                       //后续优化 ,这个电池充电为正，放电为负                                                                            //???   
    ptDisplayBmsData->u8SOC = (uint8_t) (tBmsCanDataPylon.SOCandSOH.u16AvgSOC & 0x00FF);
    ptDisplayBmsData->u8SOH = (uint8_t) (tBmsCanDataPylon.SOCandSOH.u16AvgSOH & 0x00FF);
    ptDisplayBmsData->sMaxChargeCurrent = (int16_t) (tBmsCanDataPylon.OperationLimit.s16ChgCurrLimit);
    ptDisplayBmsData->u16MaxChargeVoltage = (uint16_t) (tBmsCanDataPylon.OperationLimit.u16ChgVoltLimit);       //后续优化                                                     //???
    ptDisplayBmsData->sMaxDisChargeCurrent = (int16_t) (tBmsCanDataPylon.OperationLimit.s16DischgCurrLimit);
    ptDisplayBmsData->u16MaxDisChargeVoltage = (uint16_t) (tBmsCanDataPylon.OperationLimit.u16DischgVoltLimit);  //后续优化
}

/***********************************************************************************************************************
 功能：LCD显示屏查询电池包故障的接口
************************************************************************************************************************/
void GetDisplayBMSCanFault(Display_BMSCan_Fault_t* ptDisplayBmsFault)
{                                                                                                
    memcpy(ptDisplayBmsFault, &tBmsCanDataPylon.ProtectAndAlarm, sizeof(Display_BMSCan_Fault_t));
}

#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

