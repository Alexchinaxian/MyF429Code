/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : COMMDeal.h 
 用途 : 通信口收发文件
***********************************************************************************************************************/
#ifndef __COMMDEAL_H_
#define __COMMDEAL_H_

#include "HeadFile.h"
#include "Modbus_RTU_Slave.h"
#include "Modbus_RTU_Master.h"
#include "Modbus_ASCII_Master.h"
#include "Canbus_Bms_COMData.h"
#include "Canbus_EmsParallel_COMData.h"

extern void Comm_Module_InitVar(void);                  //通信处理模块全局变量初始化
extern void EmsToPcsCommunicateHandler(void);           //EMS与PCS通信实现函数
extern void EmsToBmsCommunicateHandler(void);           //EMS与BMS通信实现函数
extern void EmsToWifiGprsCommunicateHandler(void);      //EMS与WIFI通信实现函数
extern void EmsToBluetoothCommunicateHandler(void);     //EMS与蓝牙通信实现函数
extern void EmsToDebugCommunicateHandler(void);         //EMS与DEBUG通信实现函数
extern void EmsToMeterCommunicateHandler(void);         //EMS与电表通信实现函数
extern void EmsToBmsCanCommunicateHandler(void);        //EMS与BMSCAN通信实现函数
extern void EmsToEmsCanCommunicateHandler(void);        //EMS并机CAN通信实现函数
typedef enum
{
    COMM_INIT,                                          //通信模块初始化
    COMM_RUNNING,                                       //通信模块运行
    COMM_DESTRCUCTION,                                  //通信模块析构
    COMM_STATE_NULL 
}CommStatus_TypeDef;

typedef enum
{
    RegularSend0ms = 0,
    RegularSend100ms,
    RegularSend200ms,
    RegularSend300ms,
    RegularSend400ms,
    RegularSend500ms,
    RegularSend600ms,
    RegularSend700ms,
    RegularSend800ms,
    RegularSend900ms,
    RegularSend1000ms,
    RegularSend1100ms,
    RegularSend1200ms,
    RegularSend1300ms,
    RegularSend1400ms,
    RegularSend1500ms,
    RegularSend1600ms,
    RegularSend1700ms,
    RegularSend1800ms,
    RegularSend1900ms,
    RegularSend2000ms,
    RegularSend2100ms,
    RegularSend2200ms,
    RegularSend2300ms,
    RegularSend2400ms,
    RegularSend2500ms,
    RegularSend2600ms,
    RegularSend2700ms,
    RegularSend2800ms,
    RegularSend2900ms,
    RegularSend3000ms,
} MasterRegularSendTimer03H;


#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

