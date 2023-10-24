/***********************************************************************************************************************
* Copyright (c)  , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
* 文件名        : GlobalVar.c
* 用途         : 全局变量
***********************************************************************************************************************/
#include "GlobalVar.h"

#include "Buzzer_Service.h"
#include "Modbus.h"
#include "COMMDeal.h"
#include "Modbus_RTU_Master.h"
#include "Modbus_RTU_Slave.h"
#include "LCD_Service.h"
#include "Storage_Management_Service.h"
#include "Energy_Management_Service.h"
#include "Battery_Protect_Service.h"
#include "Fault_Management_Service.h"
#include "Indication_Management_Service.h"
#include "Statistics_Management_Service.h"
#include "LCD_KS0108_6800_Device.h"
#if (RTCSIGNAL_SOURCE == MCU_RTC_MOUDLE)
    #include "rtc_driver.h"
#endif   
#if (RTCSIGNAL_SOURCE == RTC_BL5372_MOUDLE)
    #include "BL5372_Device.h"
#endif
#if (RTCSIGNAL_SOURCE == RTC_PCF8563_MOUDLE)
    #include "PCF8563_Device.h"
#endif

#if MODULE_GLOBAL_VAR
/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
SysConfig_t gtSysConfig;
ModelMessage_t gtModelMessage;                                     //
volatile ParallelSyncVar_t gtParallelSyncVar;                      //并机同步全局变量
volatile PowerPhaseVar_t gtPowerPhaseVar;                          //
volatile PowerStageDriverStatus_t gtPowerStageDriverStatus;        //

/***********************************************************************************************************************
 功能：全局变量初始化
***********************************************************************************************************************/
void Globalvar_InitVar(void)
{
    gtPowerPhaseVar.s16MaxSinPoint = 0;
    gtPowerPhaseVar.s16SinPointCount = 0;
    gtPowerPhaseVar.s16LineVoltageAlphaAxisValue = 0;
    gtPowerPhaseVar.s16LineVoltageBetaAxisValue = 0;
    gtPowerPhaseVar.s16PowerFrequency = 0;
    gtPowerPhaseVar.s16PowerPhase = 0;
}

/***********************************************************************************************************************
 功能：全局变量初始化
***********************************************************************************************************************/
void GlobalVar_InitModules(void)
{
    Globalvar_InitVar();

    TimeTask_InitVar();

//各个软件模块全局变量初始化，要求所有变量无论后继是否使用，必须都要初始化
#if BUZZER_SERVICE_MOUDLE
    Buzzer_Service_InitVar();
#endif

#if MODBUS_MOUDLE
    Modbus_InitVar();
#endif

#if COM_DEAL_MOUDLE
    Comm_Module_InitVar();
#endif

#if MODBUS_RTU_MASTER_MOUDLE
    MB_Master_RTU_InitVar();
#endif

#if MODBUS_RTU_SLAVE_MOUDLE
    MB_Slave_RTU_InitVar();
#endif

#if (RTCSIGNAL_SOURCE == MCU_RTC_MOUDLE)
    MCU_RTC_InitVar();
#endif
#if (RTCSIGNAL_SOURCE == RTC_BL5372_MOUDLE)
    BL5372_Device_InitVar();
#endif
#if (RTCSIGNAL_SOURCE == RTC_PCF8563_MOUDLE)
    PCF8563_Device_InitVar();
#endif

#if RTC_SERVICE_MOUDLE
    RTC_Service_InitVar();
#endif

#if LCD_SERVICE_MOUDLE
    Display_Service_InitVar();
#endif

#if STORAGE_SERVICE_MOUDLE
    Storage_Service_InitVar();
#endif

#if ENERGY_SERVICE_MOUDLE
    Energy_Service_InitVar();
#endif

#if BATTERY_SERVICE_MOUDLE
    Battery_Service_InitVar();
#endif

#if FAULT_SERVICE_MOUDLE
    Fault_Service_InitVar();
#endif

#if INDICATION_SERVICE_MOUDLE
    Indication_Service_InitVar();
#endif

#if STATISTICS_SERVICE_MOUDLE
    Statistics_Service_InitVar();
#endif

#if LCD_DEVICE_KS0108_6800_MOUDLE
    LCD_Device_KS0108_6800_InitVar();
#endif

}


#endif /***Module End***/
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
