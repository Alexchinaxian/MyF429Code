/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
文件 : SR_VirtualDevice.c 
用途 : 用于安规数据处理
***********************************************************************************************************************/
#include "SR_VirtualDevice.h"

#ifndef _SR_VIRTUALDEVICE_C_
#define _SR_VIRTUALDEVICE_C_

SR_Standard gStStandard;
/***********************************************************************************************************************
 功能：安规初始化德国标准 
***********************************************************************************************************************/
void Germany_SR_Service_InitVar(void)
{
    gStStandard.stGermany.stEnableStatus.BitSRStatus.bSRGeneralParaFlag = 1;       //通用参数使能状态
    gStStandard.stGermany.stEnableStatus.BitSRStatus.bSRONGridCriteriaFlag = 1;    //并网准则使能状态
    gStStandard.stGermany.stEnableStatus.BitSRStatus.bSRThreePhaseFlag = 1;        //三相网络使能状态
    gStStandard.stGermany.stEnableStatus.BitSRStatus.bSRUnderVoltageFlag = 1;      //欠压保护使能状态
    gStStandard.stGermany.stEnableStatus.BitSRStatus.bSROverVoltageFlag = 1;       //过压保护使能状态
    gStStandard.stGermany.stEnableStatus.BitSRStatus.bSRUnderFrequencyFlag = 1;    //电网欠频使能状态
    gStStandard.stGermany.stEnableStatus.BitSRStatus.bSROverFrequencyFlag = 1;     //电网过频使能状态
    gStStandard.stGermany.stEnableStatus.BitSRStatus.bSROVRTFlag = 0;              //高电压穿越使能状态
    gStStandard.stGermany.stEnableStatus.BitSRStatus.bSRUVRTFlag = 0;              //低电压穿越使能状态
    
    gStStandard.stGermany.stGeneralPara.u16RatedPower = 4600;                  //额定功率
    gStStandard.stGermany.stGeneralPara.u16RatedVoltage = 2300;                //额定电压
    gStStandard.stGermany.stGeneralPara.u16RatedFrequency = 5000;              //额定频率
    gStStandard.stGermany.stGeneralPara.u16OFReturnValue  = 5020; //过频返回值
    gStStandard.stGermany.stGeneralPara.u16UFReturnValue  = 4750; //欠频返回值
    gStStandard.stGermany.stGeneralPara.u16OVReturnValue  = 1100; //过压返回值百分比
    gStStandard.stGermany.stGeneralPara.u16UVReturnValue  = 800;  //欠压返回值百分比
    
    /*快速电压波动 额定电压百分比 3% 间隔时间 10min=10*60s */
    gStStandard.stGermany.stRapidVoltageChange.u16IntervalTime = 10*60;
    gStStandard.stGermany.stRapidVoltageChange.u16RatedVoltagePercentage = 3;
    
    /*电压闪烁 闪烁强度 1 波动强度0.5 */
    gStStandard.stGermany.stFlicker.u16Plt = 10;
    gStStandard.stGermany.stFlicker.u16Plt = 5;
    
    /*换向缺口 额定电压百分比 5%*/
    gStStandard.stGermany.stCommunicationNotches.u16RatedVoltagePercentage = 5;
    
    /*并网准则 单相系统的最大功率不超过4.6KVA*/
    gStStandard.stGermany.stConnectionCriteria.u16SinglePhaseMaxPower = 4600;
    
    /*三项网络 三相输出功率偏差不能超过4.6KVA*/
    gStStandard.stGermany.stThreePhaseNetwork.u16PowerDeviation = 4600;
    
    /*过频 50.2~51.5Hz 4%PM/0.1Hz下降 */
    gStStandard.stGermany.stOverfrequency.st502To515.u16FrequencyStep = 4;
    gStStandard.stGermany.stOverfrequency.st502To515.s16PowerMaxPercentage = 1;
    
    /*过频 小于50.2 4%PM/0.1Hz下降 */
    gStStandard.stGermany.stOverfrequency.stLess502.u16TimeStep = 60;
    gStStandard.stGermany.stOverfrequency.stLess502.s16PowerMaxPercentage = 10;
    
    /*过频 大于51.5  0:无动作 1 断开 2 并网 选1 */
    gStStandard.stGermany.stOverfrequency.stOver515.u16GridAction = 1;
    
    /*过频50.2~51.5Hz  0:无动作 1 断开 2 并网 选0*/
    gStStandard.stGermany.stOverfrequency.stWithin.u16GridAction = 0;
    
    /*过频50.2~51.5Hz  */
    gStStandard.stGermany.stOverfrequency.stReconnect.s16PowerMaxPercentage = 0;
    gStStandard.stGermany.stOverfrequency.stReconnect.u16HoldTime = 60;
    gStStandard.stGermany.stOverfrequency.stReconnect.s16PowerMaxPercentage = 10;
    gStStandard.stGermany.stOverfrequency.stReconnect.u16TimeStep = 60;

    /*无功 3.68kVA 到13.8kVA  cosφ= 0.95 滞后到0.95超前，不需要由电网运营商提供的特性曲线 */
    gStStandard.stGermany.stReactivePower.stLess368.u16Powerfactor = 95;
    
    /*无功 3.68kVA 到13.8kVA  cosφ= 0.95 滞后到0.95超前范围内由电网运营商提供的特性曲线。*/
    gStStandard.stGermany.stReactivePower.st368To138.u16Powerfactor = 95;
    
    /*无功 3.68kVA 到13.8kVA  cosφ= 0.90滞后到0.90超前范围内由电网运营商提供的特性曲线。*/
    gStStandard.stGermany.stReactivePower.stMore138.u16Powerfactor = 90;
    
    /*过频保护 51.5Hz 100ms*/
    gStStandard.stGermany.stProtectionFunction.stOverFrequency.stLevelOne.u16Frequency    = 5150;
    gStStandard.stGermany.stProtectionFunction.stOverFrequency.stLevelOne.u16ResponseTime = 10;
    gStStandard.stGermany.stProtectionFunction.stOverFrequency.stLevelTwo.u16Frequency    = 5150;
    gStStandard.stGermany.stProtectionFunction.stOverFrequency.stLevelTwo.u16ResponseTime = 10;
    gStStandard.stGermany.stProtectionFunction.stOverFrequency.stLevelThr.u16Frequency    = 5150;
    gStStandard.stGermany.stProtectionFunction.stOverFrequency.stLevelThr.u16ResponseTime = 10;
    
    /*欠频保护 47.5Hz 100ms */
    gStStandard.stGermany.stProtectionFunction.stUnderFrequency.stLevelOne.u16Frequency    = 4750;
    gStStandard.stGermany.stProtectionFunction.stUnderFrequency.stLevelOne.u16ResponseTime = 10;
    gStStandard.stGermany.stProtectionFunction.stUnderFrequency.stLevelTwo.u16Frequency    = 4750;
    gStStandard.stGermany.stProtectionFunction.stUnderFrequency.stLevelTwo.u16ResponseTime = 10;
    gStStandard.stGermany.stProtectionFunction.stUnderFrequency.stLevelThr.u16Frequency    = 4750;
    gStStandard.stGermany.stProtectionFunction.stUnderFrequency.stLevelThr.u16ResponseTime = 10;

    /*1.1倍过压保护 100ms 110%*/
    gStStandard.stGermany.stProtectionFunction.stOverVoltage110.u16ResponseTime = 10;
    gStStandard.stGermany.stProtectionFunction.stOverVoltage110.u16RatedVoltagePercentage = 1100;
    
    /*1.15倍过压保护 100ms 115%*/
    gStStandard.stGermany.stProtectionFunction.stOverVoltage115.u16ResponseTime = 10;
    gStStandard.stGermany.stProtectionFunction.stOverVoltage115.u16RatedVoltagePercentage = 1150;
    
    /*欠压保护 100ms 80%*/
    gStStandard.stGermany.stProtectionFunction.stUnderVoltage.u16ResponseTime = 10;
    gStStandard.stGermany.stProtectionFunction.stUnderVoltage.u16RatedVoltagePercentage = 800;
    
    /*孤岛保护 5s*/
    gStStandard.stGermany.stIsland.u16ResponseTime = 5;
}

/***********************************************************************************************************************
 功能：指示灯、蜂鸣器管理模块全局变量初始化
***********************************************************************************************************************/
void EUTen_SR_Service_InitVar(void)
{
    gStStandard.stSREUTen.stEnableStatus.BitSRStatus.bSRGeneralParaFlag = 1;                                            //通用参数使能状态
    gStStandard.stSREUTen.stGeneralPara.u16RatedVoltage   = 2300;                                                       //额定电压
    gStStandard.stSREUTen.stGeneralPara.u16RatedPower     = 6000;                                                       //额定功率
    gStStandard.stSREUTen.stGeneralPara.u16RatedFrequency = 5000;                                                       //额定频率
    gStStandard.stSREUTen.stGeneralPara.u16UFReturnValue  = 4900;                                                       //欠频返回值
    gStStandard.stSREUTen.stGeneralPara.u16OFReturnValue  = 5100;                                                       //过频返回值
    gStStandard.stSREUTen.stGeneralPara.u16UVReturnValue  = 850;                                                        //欠压返回值百分比
    gStStandard.stSREUTen.stGeneralPara.u16OVReturnValue  = 1100;                                                       //过压返回值百分比

    gStStandard.stSREUTen.stEnableStatus.BitSRStatus.bSRUnderVoltageFlag = 1;                                           //电网欠压保护使能状态
    gStStandard.stSREUTen.stUVPT.stUVPTLevelOne.u16Voltage      = 850;
    gStStandard.stSREUTen.stUVPT.stUVPTLevelOne.u16ResponseTime = 1;
    gStStandard.stSREUTen.stUVPT.stUVPTLevelTwo.u16Voltage      = 850;
    gStStandard.stSREUTen.stUVPT.stUVPTLevelTwo.u16ResponseTime = 1;
    gStStandard.stSREUTen.stUVPT.stUVPTLevelThr.u16Voltage      = 850;
    gStStandard.stSREUTen.stUVPT.stUVPTLevelThr.u16ResponseTime = 1;

    gStStandard.stSREUTen.stEnableStatus.BitSRStatus.bSROverVoltageFlag = 1;                                            //电网过压保护使能状态
    gStStandard.stSREUTen.stOVPT.stOVPTLevelOne.u16Voltage      = 1150;
    gStStandard.stSREUTen.stOVPT.stOVPTLevelOne.u16ResponseTime = 1;
    gStStandard.stSREUTen.stOVPT.stOVPTLevelTwo.u16Voltage      = 1150;
    gStStandard.stSREUTen.stOVPT.stOVPTLevelTwo.u16ResponseTime = 1;
    gStStandard.stSREUTen.stOVPT.stOVPTLevelThr.u16Voltage      = 1150;
    gStStandard.stSREUTen.stOVPT.stOVPTLevelThr.u16ResponseTime = 1;

    gStStandard.stSREUTen.stEnableStatus.BitSRStatus.bSRUnderFrequencyFlag = 1;                                         //电网欠频使能状态
    gStStandard.stSREUTen.stOperatingFrequencyRange.stUnderFrequency.stLevelOne.u16Frequency    = 4900;
    gStStandard.stSREUTen.stOperatingFrequencyRange.stUnderFrequency.stLevelOne.u16ResponseTime = 1800;
    gStStandard.stSREUTen.stOperatingFrequencyRange.stUnderFrequency.stLevelTwo.u16Frequency    = 4750;
    gStStandard.stSREUTen.stOperatingFrequencyRange.stUnderFrequency.stLevelTwo.u16ResponseTime = 20; 
    gStStandard.stSREUTen.stOperatingFrequencyRange.stUnderFrequency.stLevelThr.u16Frequency    = 4700;
    gStStandard.stSREUTen.stOperatingFrequencyRange.stUnderFrequency.stLevelThr.u16ResponseTime = 0;
    
    gStStandard.stSREUTen.stEnableStatus.BitSRStatus.bSROverFrequencyFlag = 1;                                          //电网过频使能状态
    gStStandard.stSREUTen.stOperatingFrequencyRange.stOverFrequency.stLevelOne.u16Frequency    = 5100;
    gStStandard.stSREUTen.stOperatingFrequencyRange.stOverFrequency.stLevelOne.u16ResponseTime = 1800;
    gStStandard.stSREUTen.stOperatingFrequencyRange.stOverFrequency.stLevelTwo.u16Frequency    = 5150;
    gStStandard.stSREUTen.stOperatingFrequencyRange.stOverFrequency.stLevelTwo.u16ResponseTime = 900;
    gStStandard.stSREUTen.stOperatingFrequencyRange.stOverFrequency.stLevelThr.u16Frequency    = 5200;
    gStStandard.stSREUTen.stOperatingFrequencyRange.stOverFrequency.stLevelThr.u16ResponseTime = 0;
    
    gStStandard.stSREUTen.stEnableStatus.BitSRStatus.bSRReconnectFlag = 1;                                              //电网断开重连使能状态
    gStStandard.stSREUTen.stReconnect.u16Gradient              = 10;
    gStStandard.stSREUTen.stReconnect.u16BeginForbidAdjustTime = 120;
    
    gStStandard.stSREUTen.stEnableStatus.BitSRStatus.bSRLowFrequencyDerateFlag = 1;                                     //低频降额使能状态
    gStStandard.stSREUTen.stUnderFrequency.u16FrequencyThreshold = 4950;
    gStStandard.stSREUTen.stUnderFrequency.s16DerateSlope        = 10;
    
    gStStandard.stSREUTen.stEnableStatus.BitSRStatus.bSROVRTFlag = 0;                                                   //高电压穿越使能状态
    gStStandard.stSREUTen.stOVRT.stOVRTLevelOne.u16Voltage = 1110;
    gStStandard.stSREUTen.stOVRT.stOVRTLevelOne.u16ResponseTime = 6000;    //10ms
    gStStandard.stSREUTen.stOVRT.stOVRTLevelTwo.u16Voltage = 1150;
    gStStandard.stSREUTen.stOVRT.stOVRTLevelTwo.u16ResponseTime = 1000;    //10ms
    gStStandard.stSREUTen.stOVRT.stOVRTLevelThr.u16Voltage = 1200;
    gStStandard.stSREUTen.stOVRT.stOVRTLevelThr.u16ResponseTime = 20;     //10ms
    gStStandard.stSREUTen.stOVRT.stOVRTLevelFur.u16Voltage = 1200;
    gStStandard.stSREUTen.stOVRT.stOVRTLevelFur.u16ResponseTime = 20;     //10ms
    gStStandard.stSREUTen.stOVRT.stOVRTLevelFiv.u16Voltage = 1200;
    gStStandard.stSREUTen.stOVRT.stOVRTLevelFiv.u16ResponseTime = 20;     //10ms
    gStStandard.stSREUTen.stOVRT.stOVRTLevelSix.u16Voltage = 1200;
    gStStandard.stSREUTen.stOVRT.stOVRTLevelSix.u16ResponseTime = 20;     //10ms
    
    gStStandard.stSREUTen.stEnableStatus.BitSRStatus.bSRUVRTFlag = 0;                                                   //低电压穿越使能状态
    gStStandard.stSREUTen.stUVRT.stUVRTLevelOne.u16Voltage = 840;
    gStStandard.stSREUTen.stUVRT.stUVRTLevelOne.u16ResponseTime = 200;    //10ms
    gStStandard.stSREUTen.stUVRT.stUVRTLevelTwo.u16Voltage = 500;
    gStStandard.stSREUTen.stUVRT.stUVRTLevelTwo.u16ResponseTime = 100;    //10ms
    gStStandard.stSREUTen.stUVRT.stUVRTLevelThr.u16Voltage = 200;
    gStStandard.stSREUTen.stUVRT.stUVRTLevelThr.u16ResponseTime = 50;    //10ms
    gStStandard.stSREUTen.stUVRT.stUVRTLevelFur.u16Voltage = 200;
    gStStandard.stSREUTen.stUVRT.stUVRTLevelFur.u16ResponseTime = 50;     //10ms
    gStStandard.stSREUTen.stUVRT.stUVRTLevelFiv.u16Voltage = 200;
    gStStandard.stSREUTen.stUVRT.stUVRTLevelFiv.u16ResponseTime = 50;     //10ms
    gStStandard.stSREUTen.stUVRT.stUVRTLevelSix.u16Voltage = 200;
    gStStandard.stSREUTen.stUVRT.stUVRTLevelSix.u16ResponseTime = 50;     //10ms
    
    gStStandard.stSREUTen.stEnableStatus.BitSRStatus.bSROFPSFlag = 0;                                                   //过频功率响应使能状态
    gStStandard.stSREUTen.stOverFrequencyPowerResponse.u16StartFrequencyThreshold  = 5020;
    gStStandard.stSREUTen.stOverFrequencyPowerResponse.u16StopFrequencyThreshold   = 5200;
    gStStandard.stSREUTen.stOverFrequencyPowerResponse.u16StopTime                 = 30;
    gStStandard.stSREUTen.stOverFrequencyPowerResponse.u16Sagslope                 = 5;
    gStStandard.stSREUTen.stOverFrequencyPowerResponse.u16DelayTime                = 0;
    
    gStStandard.stSREUTen.stEnableStatus.BitSRStatus.bSRUFPSFlag = 0;                                                   //欠频功率响应使能状态
    gStStandard.stSREUTen.stUnderFrequencyPowerResponse.u16StartFrequencyThreshold = 4980;
    gStStandard.stSREUTen.stUnderFrequencyPowerResponse.u16StopFrequencyThreshold   = 4600;
    gStStandard.stSREUTen.stUnderFrequencyPowerResponse.u16StopTime                 = 30;
    gStStandard.stSREUTen.stUnderFrequencyPowerResponse.u16Sagslope                 = 5;
    gStStandard.stSREUTen.stUnderFrequencyPowerResponse.u16DelayTime                = 0;
    gStStandard.stSREUTen.stEnableStatus.BitSRStatus.bTenMInOVFlag = 0;                                                   //过压10分钟平均保护
    gStStandard.stSREUTen.stOvervoltage10minProtection.u16OverVoltagePercent = 1100;
    gStStandard.stSREUTen.stOvervoltage10minProtection.u16PercentTime = 600;
}

/***********************************************************************************************************************
 功能：指示灯、蜂鸣器管理模块全局变量初始化
***********************************************************************************************************************/
void SR_Service_InitVar(void)
{
    memset(&gStStandard,0,sizeof(SR_Standard));
    //欧盟十国标准安规初始化
    EUTen_SR_Service_InitVar();
    //德国标准安规初始化
    Germany_SR_Service_InitVar();
}

/***********************************************************************************************************************
 功能：根据lcd设置的安规国家获取对应国家的安规数据
***********************************************************************************************************************/
void* get_SRInfo(SR_TypeDef srType)
{
    if(srType == SR_EURTEN)
    {
        return (void*)&gStStandard.stSREUTen;
    }
    else if(srType == SR_DE)
    {
        return (void*)&gStStandard.stGermany;
    }
    else
    {
        return (void*)NULL;
    }
}

#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
