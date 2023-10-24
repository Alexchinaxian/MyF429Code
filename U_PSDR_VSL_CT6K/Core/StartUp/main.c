/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : main.c 
 用途 : 用户主函数
***********************************************************************************************************************/
#include "main.h"
#include "Key_Service.h"
#include "LCD_Service.h"
#include "Buzzer_Service.h"
#include "LCD_KS0108_6800_Device.h"
#include "COMMDeal.h"
#include "Storage_Management_Service.h"
#include "Energy_Management_Service.h"
#include "Battery_Protect_Service.h"
#include "Fault_Management_Service.h"
#include "Indication_Management_Service.h"
#include "Statistics_Management_Service.h"
#include "RTC_Service.h"
#include "NTC_DRM_Service.h"

/***********************************************************************************************************************
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
int main(void)
{
    MainProcess();
}

/***********************************************************************************************************************
 功能：main process
***********************************************************************************************************************/
void MainProcess(void)
{
    DISABLE_INTERRUPT();                      //关总中断

    GlobalVar_InitModules();                  //模块变量初始化
    //MCU_AppGetCRC32();                      //CRC计算
    MCU_InitSystemDriver();                   //硬件驱动初始化
    Delay_ms(200);                            //等待硬件驱动初始化稳定
    SystemPara_ReadData();                    //系统参数读取EE

    ENABLE_INTERRUPT();                       //开总中断
    
    #if MODULE_IWDG
        WatchDog_Initial();                       //看门狗初始化
    #endif
    
    while(1)
    {
    #if (BASE_TIME_1MS_DEBUG)
        Debug_BaseTimerStart();
    #endif
        Hardware_SetCLK();                    //时基置位
        Time_Handler();                       //基准时基
        //CheckTemp_Handler();                //温度采样
        //ADCPrameter_Handler();              //ADC采样
        Key_Handler();                        //按键输入
        EmsToPcsCommunicateHandler();         //PCS内部通信
        EmsToBmsCommunicateHandler();         //BMS通信
        EmsToDebugCommunicateHandler();       //外部调试通信
        EmsToMeterCommunicateHandler();       //电表通信
        EmsToBluetoothCommunicateHandler();   //蓝牙通信
        EmsToWifiGprsCommunicateHandler();    //WIFI/GPRS通信
        EmsToBmsCanCommunicateHandler();      //EMS与BMSCAN通信
        EmsToEmsCanCommunicateHandler();      //EMS并机CAN通信
        //Monitor_Handler();                  //监控通信, 这个部分预留给调试监控工具使用
        //SystemStatus_Handler();             //系统状态
        //SystemExecute_Handler();            //系统执行
        RTC_Handler();                        //RTC服务处理
        SystemPara_Handler();                 //参数处理，对EE数据进行保存
        StatisticsManagement_Handler();       //统计模块
        FaultManagement_Handler();            //故障告警管理
        Display_Handler();                    //显示处理
        BatteryProtect_Handler();             //电池保护
        EnergyManagement_Handler();           //能量管理
        IndicationManagement_Handler();       //指示灯管理
        //Buzzer_Handler();                   //蜂鸣器驱动
        NTC_DRM_ADC_Handler();                //DRM和NTC采样处理
        Hardware_DectectCLK();                //时基清除
    #if (BASE_TIME_1MS_DEBUG)
        Debug_BaseTimerEnd();
    #endif
    }
}
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

