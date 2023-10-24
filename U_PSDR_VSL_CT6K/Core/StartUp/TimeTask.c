/***********************************************************************************************************************
* Copyright (c) , CVTE
* All rights reserved.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
* 文件    : TimeTask.c
* 用途    : 时间处理函数
***********************************************************************************************************************/
#include "TimeTask.h"
#include "Config.h"
#include "Modbus.h"			//调试使用，后面调整位置
#include "Buzzer_Service.h"
#if MODULE_TIMETASK
/***********************************************************************************************************************
  Global variables and functions
***********************************************************************************************************************/
volatile TimeTaskVar_t  tTimeTask;
volatile uint32_t  u32SysTimestamp = 0;
/***********************************************************************************************************************
  功能: 产生时间片
***********************************************************************************************************************/
void TimeTask_InitVar(void)
{
    tTimeTask.u8Cnt200us = 0;
    tTimeTask.u8Cnt1ms = 0;
    tTimeTask.u8Cnt5ms = 0;
    tTimeTask.u8Cnt10ms = 0;
    tTimeTask.u8Cnt20ms = 0;
    tTimeTask.u8Cnt100ms = 0;
    tTimeTask.u8Cnt500ms = 0;
    tTimeTask.u8Cnt1s = 0;
    tTimeTask.u8Cnt1min = 0;
    tTimeTask.tTimeFlag.u8Bytes = 0;
}
/***********************************************************************************************************************
  功能: 硬件定时产生时间片200us时基,中断中产生时间片
***********************************************************************************************************************/
void Hardware_SetCLK(void)
{
    if (tTimeTask.u8Cnt200us >= 5)       //1ms时间计数
    {
        tTimeTask.u8Cnt200us -= 5;
        if (++ tTimeTask.u8Cnt1ms >= 5)     //5ms时间计数
        {
            
            tTimeTask.u8Cnt1ms -= 5;
            if (++ tTimeTask.u8Cnt5ms >= 2)     //10ms时间计数
            {
                tTimeTask.u8Cnt5ms -= 2;
                TimeTask_GetFlag_10ms = STATUS_TRUE;
                if (++ tTimeTask.u8Cnt10ms >= 2)        //20ms时间计数
                {
                    tTimeTask.u8Cnt10ms -= 2;
                    TimeTask_GetFlag_20ms = STATUS_TRUE;
                    if (++ tTimeTask.u8Cnt20ms >= 5)        //100ms时间计数
                    {
                        tTimeTask.u8Cnt20ms -= 5;
                        TimeTask_GetFlag_100ms = STATUS_TRUE;
                        if (++ tTimeTask.u8Cnt100ms >= 5)       //500ms时间计数
                        {
                            tTimeTask.u8Cnt100ms -= 5;
                            TimeTask_GetFlag_500ms = STATUS_TRUE;
                            if (++ tTimeTask.u8Cnt500ms >= 2)       //1S时间计数
                            {
                                u32SysTimestamp ++;
                                tTimeTask.u8Cnt500ms -= 2;
                                TimeTask_GetFlag_1s = STATUS_TRUE;
                                if (++ tTimeTask.u8Cnt1s >= 60)     //1min时间计数
                                {                                  
                                    tTimeTask.u8Cnt1s -= 60;
                                    TimeTask_GetFlag_1min = STATUS_TRUE;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

/***********************************************************************************************************************
  功能: 时间片函数
***********************************************************************************************************************/
void Time_Handler(void)
{
//    MB_Slave_Poll();				//调试用，后续改函数名字
//    MB_Master_Poll();
//	Remote_Service();				//遥控输入时基
//	KeyDeal_Service();				//按键输入时基


    //SystemStatus_Service();         //系统状态时基
    //SystemExecute_Service();        //系统执行时基

//  ModeAuto_Service();             //自动模式时基
//  ModeCool_Service();             //制冷模式时基
//  ModeHeat_Service();             //制热模式时基
//  ModeDry_Service();              //除湿模式时基
//  ModeFan_Service();              //送风模式时基

//  FunHeater_Service();            //电加热时基
//  FanDrv_Service();               //风机负载时基
//  Display_Service();              //显示负载时基
//  RelayControl_Service();         //继电器负载时基

//  Memory_Service();               //掉电记忆时基
    //Buzzer_Service();               //蜂鸣器服务


//  AutoFan_Service();              //自动风时基

//#if (MACHINE_TYPE == DEF_SYSTEM_BP)
//  SystemBp_Service();             //变频继电器时基
//  Comm_Service();                 //通讯时基
//#endif

//  if(TimeTask_GetFlag_10ms EQU STATUS_TRUE)
//  {
//      IWDG_Reload();              //喂狗操作
//  }
}


#if EN_BASE_TIMER
/***********************************************************************************************************************
  功能: 200us定时中断
***********************************************************************************************************************/
void BASE_TIMER_HANDLER(void)
{
    tTimeTask.u8Cnt200us++;

//  StepMotor_Driver();

//  BuzzDeal_Time5msCnt();

//  FanDrv_FeedbackCalculate();
}
#endif

/***********************************************************************************************************************
  功能: 时基清零
***********************************************************************************************************************/
void Hardware_DectectCLK(void)
{
    #if MODULE_IWDG
       if (STATUS_TRUE == TimeTask_GetFlag_1s)                         //1s触发一次
        {
            WatchDog_Reload();
        }
    #endif   
        
    tTimeTask.tTimeFlag.u8Bytes = 0x00;
}

#endif      /***Module End***/
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
