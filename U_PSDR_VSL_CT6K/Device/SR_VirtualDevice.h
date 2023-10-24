/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
文件 : SR_VirtualDevice.h 
用途 : 安规头文件
***********************************************************************************************************************/
#ifndef _SR_VIRTUALDEVICE_H_
#define _SR_VIRTUALDEVICE_H_

#include "HeadFile.h"

//安规类型
typedef enum
{
    SR_EURTEN,  //欧盟十国
    SR_DE,      //德国
    SR_UK,      //英国
    SR_ZA,      //南非
    SR_AU,      //澳大利亚
    SR_NULL     //
}SR_TypeDef;

//安规类别使能结构体
typedef struct 
{
    union
    {
        uint16_t u16SRStatus;
        struct
        {
            uint16_t bSRONGridCriteriaFlag      :1;    //并网准则使能状态
            uint16_t bSRGeneralParaFlag         :1;    //通用参数使能状态
            uint16_t bSRThreePhaseFlag          :1;    //三相网络使能状态
            uint16_t bSRUnderVoltageFlag        :1;    //欠压保护使能状态
            uint16_t bSROverVoltageFlag         :1;    //过压保护使能状态
            uint16_t bSRUnderFrequencyFlag      :1;    //电网欠频使能状态
            uint16_t bSROverFrequencyFlag       :1;    //电网过频使能状态
            uint16_t bSROVRTFlag                :1;    //高电压穿越使能状态
            uint16_t bSRUVRTFlag                :1;    //低电压穿越使能状态
            uint16_t bSRReconnectFlag           :1;    //电网重连使能状态
            uint16_t bSRLowFrequencyDerateFlag  :1;    //低频降使能状态
            uint16_t bSROFPSFlag                :1;    //过频功率响应
            uint16_t bSRUFPSFlag                :1;    //欠频功率响应
            uint16_t bTenMInOVFlag              :1;    //过压10分钟平均保护
            uint16_t bReserve1                  :1;    //预留1
            uint16_t bReserve2                  :1;    //预留2
        }BitSRStatus;
    };
}SR_Enable_Status;

typedef struct 
{
    uint16_t u16RatedVoltage;     //额定电压
    uint16_t u16RatedPower;       //额定功率
    uint16_t u16RatedFrequency;   //额定频率
    uint16_t u16UFReturnValue;    //欠频返回值
    uint16_t u16OFReturnValue;    //过频返回值
    uint16_t u16UVReturnValue;    //欠压返回值百分比
    uint16_t u16OVReturnValue;    //过压返回值百分比
}SR_General_Para;

//安规 德国 快速电压波动
typedef struct {
    uint16_t u16RatedVoltagePercentage;  //额定电压百分比 3%
    uint16_t u16IntervalTime; //间隔时间 10*60s
}SR_Germany_RapidVoltageChange;

//安规 德国 电压闪烁
typedef struct {
    uint16_t u16Pst;  // 闪烁强度 1
    uint16_t u16Plt;  // 0.5
}SR_Germany_Flicker;

//安规 德国 换向缺口
typedef struct {
    uint16_t u16RatedVoltagePercentage;  // 额定电压百分比 5%
}SR_Germany_CommunicationNotches;

//安规 德国 并网准则
typedef struct {
    uint16_t u16SinglePhaseMaxPower;  // 单相系统的最大功率不超过4.6KVA
}SR_Germany_ConnectionCriteria;

//安规 德国 三相网络
typedef struct {
    uint16_t u16PowerDeviation;  // 三相输出功率偏差不能超过4.6KVA
}SR_Germany_ThreePhaseNetwork;

//安规 德国 50.2~51.5Hz
typedef struct {
    uint16_t u16FrequencyStep;    // 4%PM/0.1Hz下降
    int16_t  s16PowerMaxPercentage;
}SR_Germany_Overfrequency_502_515;

//安规 德国 小于50.2
typedef struct {
    uint16_t u16TimeStep;         // 10%额度最大有功功率/min增加
    int16_t  s16PowerMaxPercentage;
}SR_Germany_Overfrequency_less_502;

//安规 德国 超过51.5Hz
typedef struct {
    uint16_t u16GridAction;         // 0:无动作 1 断开 2 并网 选1
}SR_Germany_Overfrequency_Over_515;

//安规 德国 50.2~51.5Hz
typedef struct {
    uint16_t u16GridAction;         // 0:无动作 1 断开 2 并网 选0
}SR_Germany_Overfrequency_Within;

//安规 德国 断开重连
typedef struct {
    uint16_t u16FrequencyLimit; //frequency限制 50.05 维持一分钟             
    uint16_t u16HoldTime;
    int16_t  s16PowerMaxPercentage;     // 重新并网，10%额度最大有功功率/min增加 
    uint16_t u16TimeStep;  
}SR_Germany_Overfrequency_Reconnect;      

//安规 德国 过频保护
typedef struct {
    SR_Germany_Overfrequency_502_515   st502To515; // 50.2~51.5Hz
    SR_Germany_Overfrequency_less_502  stLess502;  //小于50.2
    SR_Germany_Overfrequency_Over_515  stOver515;  //超过51.5Hz
    SR_Germany_Overfrequency_Within    stWithin;   //50.2~51.5Hz
    SR_Germany_Overfrequency_Reconnect stReconnect;//断开重连
}SR_Germany_Overfrequency;

//安规 德国 最大视在功率小与等于3.68kVA
typedef struct {
    uint16_t u16Powerfactor;        //cosφ= 0.95 滞后到0.95超前，不需要由电网运营商提供的特性曲线。             
}SR_Germany_ReactivePower_Less368;  

//安规 德国 最大视在功率3.68kVA 到13.8kVA
typedef struct {
    uint16_t u16Powerfactor;        //cosφ= 0.95 滞后到0.95超前范围内由电网运营商提供的特性曲线。             
}SR_Germany_ReactivePower_368_138; 

//安规 德国 最大视在功率大于13.8kVA
typedef struct {
    uint16_t u16Powerfactor;        //cosφ= 0.90滞后到0.90超前范围内由电网运营商提供的特性曲线。             
}SR_Germany_ReactivePower_More138; 

//安规 德国 无功功率
typedef struct {
    SR_Germany_ReactivePower_Less368  stLess368;   //小与等于3.68kVA
    SR_Germany_ReactivePower_368_138  st368To138;  //3.68kVA 到13.8kVA
    SR_Germany_ReactivePower_More138  stMore138;   //大于13.8kVA
}SR_Germany_ReactivePower;

//安规 德国 保护功能 欠压保护
typedef struct {
    uint16_t u16RatedVoltagePercentage;  //额定电压百分比 80%
    uint16_t u16ResponseTime; //响应时间 100ms
}SR_Germany_ProtectionFunction_UnderVoltage;

//安规 德国 保护功能 1.1倍过压保护
typedef struct {
    uint16_t u16RatedVoltagePercentage;  //额定电压百分比 110%
    uint16_t u16ResponseTime; //响应时间 100ms
}SR_Germany_ProtectionFunction_OverVoltage110;

//安规 德国 保护功能 1.15倍过压保护
typedef struct {
    uint16_t u16RatedVoltagePercentage;  //额定电压百分比 115%
    uint16_t u16ResponseTime; //响应时间 100ms
}SR_Germany_ProtectionFunction_OverVoltage115;

//安规 德国 保护功能 电网欠频
typedef struct {
    uint16_t u16Frequency;    //47.5Hz
    uint16_t u16ResponseTime; //响应时间 100ms
}SR_Germany_ProtectionFunction_UnderFrequency;

//安规 德国 保护功能 电网欠频
typedef struct {
    SR_Germany_ProtectionFunction_UnderFrequency stLevelOne;   //一级欠频
    SR_Germany_ProtectionFunction_UnderFrequency stLevelTwo;   //二级欠频
    SR_Germany_ProtectionFunction_UnderFrequency stLevelThr;   //三级欠频
}SR_Germany_UnderFrequency;

//安规 德国 保护功能 电网过频
typedef struct {
    uint16_t u16Frequency;  //51.5Hz
    uint16_t u16ResponseTime; //响应时间 100ms
}SR_Germany_ProtectionFunction_OverFrequency;

//安规 德国 保护功能 电网过频
typedef struct {
    SR_Germany_ProtectionFunction_OverFrequency stLevelOne;   //一级欠频
    SR_Germany_ProtectionFunction_OverFrequency stLevelTwo;   //一级欠频
    SR_Germany_ProtectionFunction_OverFrequency stLevelThr;   //一级欠频
}SR_Germany_OverFrequency;

//安规 德国 保护功能
typedef struct {
    SR_Germany_ProtectionFunction_UnderVoltage    stUnderVoltage;     //欠压保护
    SR_Germany_ProtectionFunction_OverVoltage110  stOverVoltage110;   //1.1倍过压保护
    SR_Germany_ProtectionFunction_OverVoltage115  stOverVoltage115;   //1.15倍过压保护
    SR_Germany_UnderFrequency                     stUnderFrequency;   //47.5Hz
    SR_Germany_OverFrequency                      stOverFrequency;    //51.5Hz
}SR_Germany_ProtectionFunction;

//安规 德国 孤岛保护
typedef struct {
    uint16_t u16ResponseTime; //响应时间 5s
}SR_Germany_Island;

//安规 德国 
typedef struct {
    SR_General_Para stGeneralPara;    //通用参数
    SR_Enable_Status stEnableStatus;  //德国安规标准使能项
    SR_Germany_RapidVoltageChange stRapidVoltageChange;//快速电压波动
    SR_Germany_Flicker stFlicker;//电压闪烁
    SR_Germany_CommunicationNotches stCommunicationNotches;//换向缺口
    SR_Germany_ConnectionCriteria stConnectionCriteria;//并网准则
    SR_Germany_ThreePhaseNetwork stThreePhaseNetwork;//三项网络
    SR_Germany_Overfrequency stOverfrequency;//过频
    SR_Germany_ReactivePower stReactivePower;//无功
    SR_Germany_ProtectionFunction stProtectionFunction;//保护功能
    SR_Germany_Island stIsland;//孤岛保护
}SR_Germany;

//安规 欧盟十国  工作频率范围 要求
typedef struct {
    int16_t u16LowestRequirementsTime;  //最低要求时间 值为-2 则是无要求 值为-1 则是长期可靠运行
    int16_t u16StrictRequirementsTime;  //严格要求时间
}SR_EUTen_OperatingFrequencyRange_Require;

//安规 欧盟十国 保护功能 电网欠频
typedef struct {
    uint16_t u16Frequency;    //47.5Hz
    uint16_t u16ResponseTime; //响应时间 100ms
}SR_EUTen_ProtectionFunction_UnderFrequency;

//安规 欧盟十国 保护功能 电网欠频
typedef struct {
    SR_Germany_ProtectionFunction_UnderFrequency stLevelOne;   //一级欠频
    SR_Germany_ProtectionFunction_UnderFrequency stLevelTwo;   //二级欠频
    SR_Germany_ProtectionFunction_UnderFrequency stLevelThr;   //三级欠频
}SR_EUTen_UnderFrequency;

//安规 欧盟十国 保护功能 电网过频
typedef struct {
    uint16_t u16Frequency;  //51.5Hz
    uint16_t u16ResponseTime; //响应时间 100ms
}SR_EUTen_ProtectionFunction_OverFrequency;

//安规 欧盟十国 保护功能 电网过频
typedef struct {
    SR_Germany_ProtectionFunction_OverFrequency stLevelOne;   //一级欠频
    SR_Germany_ProtectionFunction_OverFrequency stLevelTwo;   //一级欠频
    SR_Germany_ProtectionFunction_OverFrequency stLevelThr;   //一级欠频
}SR_EUTen_OverFrequency;

//安规 欧盟十国  工作频率范围
typedef struct {
    SR_EUTen_UnderFrequency stUnderFrequency;
    SR_EUTen_OverFrequency  stOverFrequency;
}SR_EUTen_OperatingFrequencyRange;

//安规 欧盟十国  低频有功功率输送的最低要求 
typedef struct {
    uint16_t u16FrequencyThreshold;    //频率阈值
    int16_t  s16DerateSlope;           //降额斜率
}SR_EUTen_UnderFrequencyLowestRequirements_condition;

//安规 欧盟十国  低频有功功率输送的最低要求
typedef struct {
    SR_EUTen_UnderFrequencyLowestRequirements_condition stLess495; //频率＜49.5Hz 每降低1Hz最大允许降低Pmax的10%
    SR_EUTen_UnderFrequencyLowestRequirements_condition stLess490; //频率＜49Hz   每降低1Hz最大允许降低Pmax的2%
}SR_EUTen_UnderFrequencyLowestRequirements;

//安规 欧盟十国  连续工作电压范围
typedef struct {
    uint16_t u16StartRatedVoltagePercentage; //85%Un~110%Un
    uint16_t u16EndRatedVoltagePercentage;   //85%Un~110%Un
}SR_EUTen_ContinuousOperatingVoltageRage;

//安规 欧盟十国  频率变化率
typedef struct {
    uint16_t u16SynchronousGenSagCoefficient;    //非同步发电技术频率变化率 2Hz/s
    uint16_t u16AsynchronousGenSagCoefficient;   //非同步发电技术频率变化率 1Hz/s
}SR_EUTen_SagCoefficient;

typedef struct {
    uint16_t u16Voltage;      //额定电压百分比
    uint16_t u16ResponseTime; //响应时间 100ms
}SR_EUTen_OVPT_Protect;

//安规 欧盟十国  过压保护
typedef struct {
    SR_EUTen_OVPT_Protect stOVPTLevelOne;   //一级过压保护
    SR_EUTen_OVPT_Protect stOVPTLevelTwo;   //二级过压保护
    SR_EUTen_OVPT_Protect stOVPTLevelThr;   //三级过压保护
}SR_EUTen_OverVolt_Pro;

typedef struct {
    uint16_t u16Voltage;      //额定电压百分比
    uint16_t u16ResponseTime; //响应时间 100ms
}SR_EUTen_UVPT_Protect;

//安规 欧盟十国  欠压保护
typedef struct {
    SR_EUTen_UVPT_Protect stUVPTLevelOne;   //一级欠压保护
    SR_EUTen_UVPT_Protect stUVPTLevelTwo;   //二级欠压保护
    SR_EUTen_UVPT_Protect stUVPTLevelThr;   //三级欠压保护
}SR_EUTen_UnderVolt_Pro;

typedef struct {
    uint16_t u16Voltage;    //51.5Hz
    uint16_t u16ResponseTime; //响应时间 100ms
}SR_EUTen_UVRT_Protect;

//安规 欧盟十国  低电压穿越
typedef struct {
    SR_EUTen_UVRT_Protect stUVRTLevelOne;   //一级低电压穿越
    SR_EUTen_UVRT_Protect stUVRTLevelTwo;   //二级低电压穿越
    SR_EUTen_UVRT_Protect stUVRTLevelThr;   //三级低电压穿越
    SR_EUTen_UVRT_Protect stUVRTLevelFur;   //四级低电压穿越
    SR_EUTen_UVRT_Protect stUVRTLevelFiv;   //五级低电压穿越
    SR_EUTen_UVRT_Protect stUVRTLevelSix;   //六级低电压穿越
}SR_EUTen_UVRT_Asynchronous;

typedef struct {
    uint16_t u16Voltage;    //51.5Hz
    uint16_t u16ResponseTime; //响应时间 100ms
}SR_EUTen_OVRT_Protect;

//安规 欧盟十国  高电压穿越
typedef struct {
    SR_EUTen_OVRT_Protect stOVRTLevelOne;   //一级高电压穿越
    SR_EUTen_OVRT_Protect stOVRTLevelTwo;   //二级高电压穿越
    SR_EUTen_OVRT_Protect stOVRTLevelThr;   //三级高电压穿越
    SR_EUTen_OVRT_Protect stOVRTLevelFur;   //四级高电压穿越
    SR_EUTen_OVRT_Protect stOVRTLevelFiv;   //五级高电压穿越
    SR_EUTen_OVRT_Protect stOVRTLevelSix;   //六级高电压穿越
}SR_EUTen_OVRT;

//安规 欧盟十国  功率响应
typedef struct {
    uint16_t u16StartFrequencyThreshold; //频率阈值可设f1 50.2Hz~52Hz 默认设置50.2Hz
    uint16_t u16StopFrequencyThreshold;  //停用阈值fstop  50Hz~f1
    uint16_t u16StopTime;                //停用时间    0~600s    默认设置30s
    uint16_t u16Sagslope;                //下降斜率    2%~12%    默认设置5%
    uint16_t u16DelayTime;               //有意延迟时间    0~2s    默认设置0s
}SR_EUTen_FrequencyPowerResponse;

//安规 欧盟十国  无功功率支持电压
typedef struct {
    uint16_t u16CHP150Limit_PFStart; //终端容量<150kVA cosφ=0.95滞后到cosφ=0.95
    uint16_t u16CHP150Limit_PFEnd;   //终端容量<150kVA cosφ=0.95滞后到cosφ=0.95
    uint16_t u16InductionGenerator_PFStart; //φ = 0,95欠激励到cos φ = 1。
    uint16_t u16InductionGenerator_PFEnd;   //φ = 0,95欠激励到cos φ = 1。    
    uint16_t u16Direct_PFStart; //0.95以上
    uint16_t u16Direct_PFEnd;   //0.95以上。
}SR_EUTen_ReactivePowerVoltageSupport;

//安规 欧盟十国  保护要求
typedef struct {
    uint16_t u16FrequencyPrecision;   //频率测量±0.05Hz；
    uint16_t u16VoltagePrecision;      //电压测量±1%Un；
    uint16_t u16ResetTime;             //重置时间≤50ms；
    uint16_t u16VoltageNominalRatio;   //低于电压标称值的 2%    
    uint16_t u16FrequencyNominalRatio; //频率低于0.2Hz。
}SR_EUTen_ProtectionRequirements;

//安规 欧盟十国  电压阈值阶段参数
typedef struct {
    uint16_t u16RatedVoltageStartRange;    //；
    uint16_t u16RatedVoltageEndRange;      //；
    uint16_t u16RatedVoltageStep;          //；
    uint16_t u16OperationTimeStartRange;   //；
    uint32_t u32OperationTimeEndRange;    //；
    uint16_t u16OperationTimeStep;         //；    
}SR_EUTen_VoltageThresholdStagePara;

//安规 欧盟十国  频率阈值阶段参数
typedef struct {
    uint16_t u16FrequencyStartRange;       //；
    uint16_t u16FrequencyEndRange;         //；
    uint16_t u16FrequencyStep;             //；
    uint16_t u16OperationTimeStartRange;   //；
    uint32_t u32OperationTimeEndRange;     //；
    uint16_t u16OperationTimeStep;         //；    
}SR_EUTen_FrequencyThresholdStagePara;

//安规 欧盟十国  
typedef struct {
    //阈值阶段1
    SR_EUTen_VoltageThresholdStagePara stThresholdStageOne; 
    //阈值阶段2
    SR_EUTen_VoltageThresholdStagePara stThresholdStageTwo;     
}SR_EUTen_AbnormalProtection;

//安规 欧盟十国  
typedef struct {
    //阈值阶段1
    SR_EUTen_FrequencyThresholdStagePara stThresholdStageOne; 
    //阈值阶段2
    SR_EUTen_FrequencyThresholdStagePara stThresholdStageTwo;
    uint16_t u16RatedVoltageStartRange;    //；
    uint16_t u16RatedVoltageEndRange;      //；
}SR_EUTen_FrequencyAbnormalProtection;

//安规 欧盟十国  过压10分钟平均保护
typedef struct {
    uint16_t u16OverVoltagePercent;    //过压百分比
    uint16_t u16PercentTime; //保护时间 
}SR_EUTen_Overvoltage10minProtection;

//安规 德国 断开重连
typedef struct {
    uint16_t u16Gradient; //默认设置为10%Pn/min。
    uint16_t u16BeginForbidAdjustTime; //可在1分钟至10分钟(随机值，均匀分布)或更晚后连接。
}SR_EUTen_Reconnect;

//安规 欧盟十国 
typedef struct {
    SR_General_Para stGeneralPara;              //通用参数
    SR_Enable_Status stEnableStatus;            //欧盟十国安规标准使能项
    SR_EUTen_Reconnect stReconnect;             //断开重连
    SR_EUTen_Overvoltage10minProtection stOvervoltage10minProtection;//过压10分钟平均保护
    /****************************过频保护*************************************
        低频保护阈值阶段1
        阈值在（47-50）Hz，按0.1Hz步长调整；
        操作时间在（0.1-100）s，按0.1s步长调整。
        低频保护阈值阶段2
        阈值在（47-50）Hz，按0.1Hz步长调整；
        操作时间在（0.1-5）s，按0.05s步长调整。
        频率保护在输入电压在20%Un~120%Un之间应能正常工作，在输入电压低于20%Un时应被抑制。
        在0.2Un以下，频率保护被抑制。只有在欠压保护的情况下才可能发生断开。
    *****************************************************************************/
    SR_EUTen_FrequencyAbnormalProtection stUnderFrequencyProtection;
    /****************************过频保护*************************************
        过频保护阈值阶段1
        阈值在（50-52）Hz，按0.1Hz步长调整；
        操作时间在（0.1-100）s，按0.1s步长调整。
        过频保护阈值阶段2
        阈值在（50-52）Hz，按0.1Hz步长调整；
        操作时间在（0.1-5）s，按0.05s步长调整。 
    频率保护在输入电压在20%Un~120%Un之间应能正常工作，在输入电压低于20%Un时应被抑制。
    *****************************************************************************/
    SR_EUTen_FrequencyAbnormalProtection stOverFrequencyProtection;
    /****************************过压保护*************************************
        过压阈值阶段1
        阈值在（1.0-1.2）Un，按0.01Un步长调整；
        操作时间在（0.1-100）s，按0.1s步长调整。
        过压阈值阶段1
        阈值在（1.0-1.3）Un，按0.01Un步长调整；
        操作时间在（0.1-5）s，按0.05s步长调整。
    *****************************************************************************/
    SR_EUTen_AbnormalProtection stOvervoltageProtection;//过压保护
    /****************************欠压保护*************************************
        欠压阈值阶段1
        阈值在（0.2-1）Un，按0.01Un步长调整；
        操作时间在（0.1-100）s，按0.1s步长调整。
        欠压阈值阶段1
        阈值在（0.2-1）Un，按0.01Un步长调整；
        操作时间在（0.1-5）s，按0.05s步长调整。
    *****************************************************************************/
    SR_EUTen_AbnormalProtection stUndervoltageProtection;               //欠压保护
    SR_EUTen_ProtectionRequirements stProtectionRequirements;           //保护要求
    SR_EUTen_ReactivePowerVoltageSupport stReactivePowerVoltageSupport; //无功功率支持电压
    /****************************过频功率响应*************************************
        频率阈值可设f1 50.2Hz~52Hz 默认设置50.2Hz
        停用阈值fstop  50Hz~f1    
        停用时间    0~600s    默认设置30s    
        下降斜率    2%~12%    默认设置5%    
        有意延迟时间    0~2s    默认设置0s    
    *****************************************************************************/
    SR_EUTen_FrequencyPowerResponse stOverFrequencyPowerResponse; //过频功率响应
    /****************************欠频功率响应*************************************
        频率阈值可设f1 46Hz~49.8Hz 默认设置46Hz
        停用阈值fstop  50Hz~f1    
        停用时间    0~600s    默认设置30s    
        下降斜率    2%~12%    默认设置5%    
        有意延迟时间    0~2s    默认设置0s    
    *****************************************************************************/
    SR_EUTen_FrequencyPowerResponse stUnderFrequencyPowerResponse;          //欠频功率响应

    SR_EUTen_OverVolt_Pro stOVPT;                                           //过压保护
    SR_EUTen_UnderVolt_Pro stUVPT;                                          //欠压保护
    SR_EUTen_UVRT_Asynchronous stUVRT;                                      //低电压穿越
    SR_EUTen_OVRT stOVRT;                                                   //高电压穿越
    SR_EUTen_SagCoefficient stSagCoefficient;                               //频率变化率
    SR_EUTen_ContinuousOperatingVoltageRage stVoltageRage;                  //连续工作电压范围
    SR_EUTen_UnderFrequencyLowestRequirements_condition stUnderFrequency;   //低频有功功率输送的最低要求
    SR_EUTen_OperatingFrequencyRange stOperatingFrequencyRange;             //工作频率范围
}SR_EUTen;

//安规 通用 谐波
typedef struct {
    SR_EUTen   stSREUTen;    //欧盟十国
    SR_Germany stGermany;    //德国
}SR_Standard;

//安规 通用 并网准则
typedef struct {
    uint16_t u16SinglePhaseMaxPower; // 单相系统的最大功率不超过4.6KVA
}SR_Universal_ConnectionCriteria;

//安规 通用 三相网络
typedef struct {
    uint16_t u16PowerDeviation;      // 三相输出功率偏差不能超过4.6KVA
}SR_Universal_ThreePhaseNetwork;

//安规 通用 欠压保护
typedef struct {
    uint16_t u16RatedVoltagePercentage;  //额定电压百分比
    uint16_t u16ResponseTime;            //响应时间 100ms
}SR_Universal_ProtectionFunction_UnderVoltage;

//安规 通用 欠压保护
typedef struct {
    SR_Universal_ProtectionFunction_UnderVoltage stLevelOne;  //一级欠压保护
    SR_Universal_ProtectionFunction_UnderVoltage stLevelTwo;  //二级欠压保护
    SR_Universal_ProtectionFunction_UnderVoltage stLevelThr;  //三级欠压保护
}SR_Universal_UnderVoltage;

//安规 通用 过压保护
typedef struct {
    uint16_t u16RatedVoltagePercentage;  //额定电压百分比 
    uint16_t u16ResponseTime;            //响应时间 100ms
}SR_Universal_ProtectionFunction_OverVoltage;

//安规 通用 过压保护
typedef struct {
    SR_Universal_ProtectionFunction_OverVoltage stLevelOne;  //一级过压保护
    SR_Universal_ProtectionFunction_OverVoltage stLevelTwo;  //二级过压保护
    SR_Universal_ProtectionFunction_OverVoltage stLevelThr;  //三级过压保护
}SR_Universal_OverVoltage;

//安规 通用 电网欠频
typedef struct {
    uint16_t u16Frequency;    //47.5Hz
    uint16_t u16ResponseTime; //响应时间 100ms
}SR_Universal_ProtectionFunction_UnderFrequency;

//安规 通用 电网欠频
typedef struct {
    SR_Universal_ProtectionFunction_UnderFrequency stLevelOne;  //一级欠频
    SR_Universal_ProtectionFunction_UnderFrequency stLevelTwo;  //二级欠频
    SR_Universal_ProtectionFunction_UnderFrequency stLevelThr;  //三级欠频
}SR_Universal_UnderFrequency;

//安规 通用 电网过频
typedef struct {
    uint16_t u16Frequency;  //51.5Hz
    uint16_t u16ResponseTime; //响应时间 100ms
}SR_Universal_ProtectionFunction_OverFrequency;

//安规 通用 电网过频
typedef struct {
    SR_Universal_ProtectionFunction_OverFrequency  stLevelOne; //一级过频
    SR_Universal_ProtectionFunction_OverFrequency  stLevelTwo; //一级过频
    SR_Universal_ProtectionFunction_OverFrequency  stLevelThr; //一级过频
}SR_Universal_OverFrequency;

//安规 通用 穿越
typedef struct {
    int16_t sRatedVoltagePercent;    //100%Un
    int16_t sSupportTime;            //15%Un
}SR_Universal_RT;

//安规 通用 高电压穿越
typedef struct {
     SR_Universal_RT stOVRT1;
     SR_Universal_RT stOVRT2;
     SR_Universal_RT stOVRT3;
     SR_Universal_RT stOVRT4;
     SR_Universal_RT stOVRT5;
     SR_Universal_RT stOVRT6;
}SR_Universal_OVRT;

//安规 通用 低电压穿越
typedef struct {
     SR_Universal_RT stUVRT1;
     SR_Universal_RT stUVRT2;
     SR_Universal_RT stUVRT3;
     SR_Universal_RT stUVRT4;
     SR_Universal_RT stUVRT5;
     SR_Universal_RT stUVRT6;
}SR_Universal_UVRT;

//安规 通用 断开重连
typedef struct {
    uint16_t u16Gradient;              //默认设置为10%Pn/min。
    uint16_t u16BeginForbidAdjustTime; //可在1分钟至10分钟(随机值，均匀分布)或更晚后连接。
}SR_Universal_Reconnect;

//安规 通用  低频有功功率输送的最低要求 
typedef struct {
    uint16_t u16FrequencyThreshold;    //频率阈值
    int16_t  s16DerateSlope;           //降额斜率
}SR_Universal_UnderFrequencyLowestRequirements_condition;

//安规 通用  功率响应
typedef struct {
    uint16_t u16StartFrequencyThreshold; //频率阈值可设f1 50.2Hz~52Hz 默认设置50.2Hz
    uint16_t u16StopFrequencyThreshold;  //停用阈值fstop  50Hz~f1
    uint16_t u16StopTime;                //停用时间    0~600s    默认设置30s
    uint16_t u16Sagslope;                //下降斜率    2%~12%    默认设置5%
    uint16_t u16DelayTime;               //有意延迟时间    0~2s    默认设置0s
}SR_Universal_FrequencyPowerResponse;
//安规 通用  过压10分钟平均保护
typedef struct {
    uint16_t u16OverVoltagePercent;    //过压百分比
    uint16_t u16PercentTime; //保护时间 
}SR_Universal_Overvoltage10minProtection;

//安规 通用 
typedef struct 
{
    uint16_t                                                u16SRType;         //安规国家
    SR_Enable_Status                                        stEnableStatus;    //安规类别使能
    SR_General_Para                                         stGeneralPara;     //通用参数
    SR_Universal_ConnectionCriteria                         stSRONGridCriteria;//并网准则
    SR_Universal_ThreePhaseNetwork                          stThreePhase;      //三相网络
    SR_Universal_UnderVoltage                               stUnderVoltage;    //欠压保护
    SR_Universal_OverVoltage                                stOverVoltage;     //过压保护
    SR_Universal_UnderFrequency                             stUnderFrequency;  //电网欠频
    SR_Universal_OverFrequency                              stOverFrequency;   //电网过频
    SR_Universal_OVRT                                       stOVRT;            //高电压穿越
    SR_Universal_UVRT                                       stUVRT;            //低电压穿越
    SR_Universal_Reconnect                                  stReconnect;       //电网断开重连
    SR_Universal_UnderFrequencyLowestRequirements_condition stLFActionPower;   //低频降功率
    SR_Universal_FrequencyPowerResponse                     stOFPS;            //过频功率响应
    SR_Universal_FrequencyPowerResponse                     stUFPS;            //欠频功率响应
    SR_Universal_Overvoltage10minProtection                 stTenMinOV;        //欠频功率响应
}SR_Universal;

//安规服务德国标准初始化变量函数
extern void Germany_SR_Service_InitVar(void);

//安规服务欧盟十国标准初始化变量函数
extern void EUTen_SR_Service_InitVar(void);

//安规服务初始化变量函数
extern void SR_Service_InitVar(void);

//获取安规数据
void* get_SRInfo(SR_TypeDef srType);
#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
