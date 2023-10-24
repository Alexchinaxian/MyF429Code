/***********************************************************************************************************************
* Copyright (c)  , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
* 文件名       : iwdg_driver.c
* 用途         : iwdg_driver程序模块头文件
***********************************************************************************************************************/
#include "iwdg_driver.h"

static void MX_IWDG_Init(void)
{
  
    LL_IWDG_Enable(IWDG);
    LL_IWDG_EnableWriteAccess(IWDG);
    LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_64);
    LL_IWDG_SetReloadCounter(IWDG, 1250);
    while (LL_IWDG_IsReady(IWDG) != 1)
    {
    }

    __HAL_RCC_DBGMCU_CLK_ENABLE();  //打开时钟
    __HAL_DBGMCU_FREEZE_IWDG();	  //调试模式下，冻结看门狗计数器时钟
   //__HAL_DBGMCU_UNFREEZE_IWDG();	  //调试模式下，使能看门狗计数器时钟
    __HAL_RCC_DBGMCU_CLK_DISABLE();   //关闭时钟

    LL_IWDG_ReloadCounter(IWDG);

}

/***********************************************************************************************************************
功能： 喂狗
***********************************************************************************************************************/
void WatchDog_Reload(void)
{
    //fwdgt_counter_reload();  //喂狗,按照IWDG重装载寄存器FWDGT_RLR的值重装载IWDG计数器
    LL_IWDG_ReloadCounter(IWDG);
}

/***********************************************************************************************************************
功能： 看门狗初始化
***********************************************************************************************************************/
void WatchDog_Initial(void)
{
#if 0
    /* enable IRC40K */
    rcu_osci_on(RCU_IRC40K);//启动"内部40KHz振荡器"
    /* wait till IRC40K is ready */
    while(SUCCESS != rcu_osci_stab_wait(RCU_IRC40K))
    {
        //等待"内部40KHz振荡器稳定"
    }
    fwdgt_write_enable();//允许访问FWDGT_RLD(看门狗重装载寄存器)和FWDGT_PSC(看门狗预分频器寄存器)
    //configure FWDGT counter clock, 40KHz(IRC40K) / 64 = 0.625 KHz 0.0016s
    fwdgt_config(5 * 500, FWDGT_PSC_DIV64);
    //设置IWDG重装载值为2499,重装载寄存器IWDG_RLR有12位值,设置IWDG预分频值为64
    //独立看门狗的分频器输出周期为:64/40KHz=1.6ms
    //独立看门狗的复位周期为:2500*64/40KHz=4000ms
    fwdgt_counter_reload();  //喂狗,按照IWDG重装载寄存器FWDGT_RLR的值重装载IWDG计数器
    fwdgt_enable();  //使能IWDG
#endif
    MX_IWDG_Init();
}

/***********************************************************************************************************************
* * Copyright (c)  CVTE All rights reserved.  * * * END OF FILE
************************************************************************************************************************/
