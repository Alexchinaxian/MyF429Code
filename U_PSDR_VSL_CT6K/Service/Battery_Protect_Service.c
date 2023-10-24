/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Battery_Protect_Service.c
 用途 : 电池保护服务
***********************************************************************************************************************/
#ifndef _BATTERY_PROTECT_C_
#define _BATTERY_PROTECT_C_

#include "stdlib.h"
#include "HeadFile.h"
#include "Flash_Device.h"
#include "RTC_Service.h"
#include "Modbus_PCS_COMData.h"
#include "Modbus_BMS_COMData.h"
#include "Battery_Protect_Service.h"
#include "Energy_Management_Service.h"

#if BATTERY_SERVICE_MOUDLE

/*电池类型*/
uint8_t u8BatteryType = BMS_TYPE_LI_ION;
/*电池保护功能模块状态*/
static BatteryStatus_TypeDef gEnumBatteryStatus = BATTERY_STATE_NULL;
///*PCS上报电池核心数据*/
//static BatteryCorePara_TypeDef stBatteryCorePara;
///*铅酸电池核心数据*/
//static LeadBattery_Paras_TypeDef LeadBattery_Paras;
/*PCS上报电池核心数据*/
BatteryCorePara_TypeDef stBatteryCorePara;
/*铅酸电池核心数据*/
LeadBattery_Paras_TypeDef LeadBattery_Paras;
/*BMS保护全局变量*/
Battery_Protect_Para_t Battery_Protect_Para;

//Battery管理总初始化函数
static void BatteryInit(void);
//Battery管理总运行函数
static void BatteryRunning(void);
//Battery管理析构函数
static void BatteryDestruction(void);
//获取屏幕下设的保护参数
static void GetProtectParas(void);
//实现保护功能
static void ImplementProtectFunction(void);  
//弱电池保护
static void WeakBatteryProtect(void);

static uint8_t LeadBattery_ConstantCurrent_Charge(void);
static uint8_t LeadBattery_ConstantVoltage_Charge(void);
static uint8_t LeadBattery_Charge(void);
static uint8_t LeadBattery_Floating_Charge(void);
static uint8_t LeadBattery_Charge(void);
static uint8_t LeadBattery_DisCharge(void);
static uint8_t LeadBattery_SOC_OCV(uint16_t u16Voltage);
static uint8_t LeadBattery_SOC_Integral(uint8_t u8InitiateSOC, uint8_t u8InitiateSOH, int16_t s16Current); 
static void LeadBattery_Running(void);
static void GetBatteryCoreData(BatteryCorePara_TypeDef* pBatteryCorePara);

LeadBattery_ChargeState_Value_TypeDef  LeadBattery_ChargeState_Table[] =                         //充电电流安倍系数扩大100倍
{
    {564,  20},                      
    {564,  15},
    {535,  1 },
};

LeadBattery_DisCharge_Value_TypeDef  LeadBattery_DisCharge_Table[] =                              //放电电流安倍系数扩大100倍
{
    {5,   456},
    {30,  432},
    {100, 432},
    {300, 384},
};

void BatteryProtect_Handler(void)
{
    if (STATUS_FALSE == TimeTask_GetFlag_1s)
    {
        return;
    }
    switch (gEnumBatteryStatus)
    {
        case BATTERY_INIT://电池保护模块初始化
        {
            BatteryInit();
            gEnumBatteryStatus = BATTERY_RUNNING;
        }
        break;

        case BATTERY_RUNNING://电池保护模块运行
        {
            BatteryRunning();
        }
        break;

        case BATTERY_DESTRCUCTION://电池保护模块析构,用掉电检测村塾
        {
            BatteryDestruction();
        }
        break;

        default:
            break;
    }
}

/***********************************************************************************************************************
 功能：电池保护模块全局变量初始化
***********************************************************************************************************************/
void Battery_Service_InitVar(void)
{
    gEnumBatteryStatus = BATTERY_INIT;
    memset(&Battery_Protect_Para, 0, sizeof(Battery_Protect_Para_t));
}

/***********************************************************************************************************************
 功能：电池保护模块析构
***********************************************************************************************************************/
void Battery_Protect_DestructionVar(void)
{
    BatteryDestruction();
    gEnumBatteryStatus = BATTERY_DESTRCUCTION;
}

/***********************************************************************************************************************
 功能：电池保护模块硬件初始化
***********************************************************************************************************************/
void Battery_Service_HwInit(void)
{
}

/***************************************************************************
 功能:初始化驱动，全局变量等
****************************************************************************/
static void BatteryInit(void)
{
    LeadBattery_Paras.u8LastSOH = 100;
}

/***************************************************************************
 功能:电池保护总运行函数
****************************************************************************/
static void BatteryRunning(void)
{                                                                                                                           
    GetProtectParas(); 
    if(u8BatteryType == BMS_TYPE_LEAD_ACID )
    {
        LeadBattery_Running(); 
    }
    ImplementProtectFunction();  
    WeakBatteryProtect();
}

/***************************************************************************
 功能:电池保护析构函数，用于掉电触发保护逻辑
****************************************************************************/
static void BatteryDestruction(void)
{

}

/***********************************************************************************************************************
 功能：获取保护参数
************************************************************************************************************************/
static void GetProtectParas(void)
{
    //获取屏幕下设参数
    Display_SET_BMS*  pDisplay_Set_BMS = Display_Get_BmsSetPara();                                                         
    u8BatteryType = pDisplay_Set_BMS ->u8Type;
   
    if(u8BatteryType == BMS_TYPE_LI_ION)                                                                                      //磷酸铁锂
    {   
        Display_DATA_BMS stRealBMS;
        memset(&stRealBMS, 0, sizeof(stRealBMS));
        GetDisplayRealTimeBmsData(&stRealBMS);
        
        Battery_Protect_Para.u16BMSSOC = stRealBMS.u8SOC *10;
        Battery_Protect_Para.u8NowSOC = stRealBMS.u8SOC;
        Battery_Protect_Para.u16BMSVoltage = stRealBMS.u16BMSVoltage;
        Battery_Protect_Para.u16MaxChargeVoltage = stRealBMS.u16MaxChargeVoltage;
        Battery_Protect_Para.u16MaxDisChargeVoltage = 469;

        Battery_Protect_Para.u8ChargeStopSOC = pDisplay_Set_BMS->stHMISetBMSLiIonParas.u8EndOfCharSOC;
        Battery_Protect_Para.u8ChargeLimitSOC = Battery_Protect_Para.u8ChargeStopSOC - SOC_RETURNDIFFERENCE;                    //充电SOC回差
        Battery_Protect_Para.u8DisChargeStopSOC = pDisplay_Set_BMS->stHMISetBMSLiIonParas.u8EndOfDisCharSOC;
        Battery_Protect_Para.u8DisChargeLimitSOC = Battery_Protect_Para.u8DisChargeStopSOC + SOC_RETURNDIFFERENCE;              //放电SOC回差
        //电压电流限制   

        
        if((stRealBMS.sMaxChargeCurrent == 0) || (stRealBMS.sMaxChargeCurrent >= pDisplay_Set_BMS->stHMISetBMSLiIonParas.u16MaxCharCurrent))
        {
            Battery_Protect_Para.s16MaxChargeCurrent = pDisplay_Set_BMS->stHMISetBMSLiIonParas.u16MaxCharCurrent;
        }
        else
        {
            Battery_Protect_Para.s16MaxChargeCurrent = stRealBMS.sMaxChargeCurrent;    
        }

        if((stRealBMS.sMaxDisChargeCurrent == 0) || (stRealBMS.sMaxDisChargeCurrent >= pDisplay_Set_BMS->stHMISetBMSLiIonParas.u16MaxDisCharCurrent))
        {
            Battery_Protect_Para.s16MaxDisChargeCurrent = pDisplay_Set_BMS->stHMISetBMSLiIonParas.u16MaxDisCharCurrent;           
        } 
        else
        {
            Battery_Protect_Para.s16MaxDisChargeCurrent = stRealBMS.sMaxDisChargeCurrent;
        }
    }
    else if(u8BatteryType == BMS_TYPE_LEAD_ACID)                                                                                   
    {        
        Battery_Protect_Para.u8ChargeStopSOC = pDisplay_Set_BMS->stHMISetBMSLeadAcidParas.u8EndOfCharSOC;
        Battery_Protect_Para.u8ChargeLimitSOC = Battery_Protect_Para.u8ChargeStopSOC - SOC_RETURNDIFFERENCE;                    //充电SOC回差
        Battery_Protect_Para.u8DisChargeStopSOC = pDisplay_Set_BMS->stHMISetBMSLeadAcidParas.u8EndOfDisCharSOC;
        Battery_Protect_Para.u8DisChargeLimitSOC = Battery_Protect_Para.u8DisChargeStopSOC + SOC_RETURNDIFFERENCE;              //放电SOC回差
        
        LeadBattery_Paras.u8NominalCapacity = pDisplay_Set_BMS ->stHMISetBMSLeadAcidParas.u16BatteryCapacity;
        
        Battery_Protect_Para.u16MaxChargeVoltage = LeadBattery_ChargeState_Table[CONSTANTCURRENT_STAGE].u16LimitVoltage;               
        Battery_Protect_Para.s16MaxChargeCurrent = LeadBattery_Paras.u8NominalCapacity * 3;                     //最大充电电流0.3C
        if(Battery_Protect_Para.s16MaxChargeCurrent >= pDisplay_Set_BMS->stHMISetBMSLeadAcidParas.u16MaxCharCurrent)
        {
            Battery_Protect_Para.s16MaxChargeCurrent = pDisplay_Set_BMS->stHMISetBMSLeadAcidParas.u16MaxCharCurrent;      
        }
        
        Battery_Protect_Para.u16MaxDisChargeVoltage = LeadBattery_DisCharge_Table[2].u16LimitVoltage;
        Battery_Protect_Para.s16MaxDisChargeCurrent = LeadBattery_Paras.u8NominalCapacity * 10;                  //最大放电电流1C
        if(Battery_Protect_Para.s16MaxDisChargeCurrent >= pDisplay_Set_BMS->stHMISetBMSLeadAcidParas.u16MaxDisCharCurrent)
        {
            Battery_Protect_Para.s16MaxDisChargeCurrent = pDisplay_Set_BMS->stHMISetBMSLeadAcidParas.u16MaxDisCharCurrent;      
        }
        
        for(uint8_t i = 0; i < 4; i++)                                                                             //电压关机电压
        {
            if(LeadBattery_DisCharge_Table[i].u16LimitVoltage < pDisplay_Set_BMS->stHMISetBMSLeadAcidParas.u16LowVoltShutPoint)          //低压关机点
            {
                LeadBattery_DisCharge_Table[i].u16LimitVoltage = pDisplay_Set_BMS->stHMISetBMSLeadAcidParas.u16LowVoltShutPoint;
            }        
        } 
        
        if(LeadBattery_ChargeState_Table[CONSTANTCURRENT_STAGE].u16LimitVoltage >= pDisplay_Set_BMS->stHMISetBMSLeadAcidParas.u16ConstVoltCharPoint)           //恒流阶段限压点
        {
            LeadBattery_ChargeState_Table[CONSTANTCURRENT_STAGE].u16LimitVoltage =  pDisplay_Set_BMS->stHMISetBMSLeadAcidParas.u16ConstVoltCharPoint;
        }

        if(LeadBattery_ChargeState_Table[CONSTANTVOLTAGE_STAGE].u16LimitVoltage >= pDisplay_Set_BMS->stHMISetBMSLeadAcidParas.u16ConstVoltCharPoint)           //恒压充电电压点
        {
            LeadBattery_ChargeState_Table[CONSTANTVOLTAGE_STAGE].u16LimitVoltage =  pDisplay_Set_BMS->stHMISetBMSLeadAcidParas.u16ConstVoltCharPoint;
        }
    
        if(LeadBattery_ChargeState_Table[FLOATINGCHARGE_STAGE].u16LimitVoltage >= pDisplay_Set_BMS->stHMISetBMSLeadAcidParas.u16FloatVoltPoint)               //浮充电压点
        {
            LeadBattery_ChargeState_Table[FLOATINGCHARGE_STAGE].u16LimitVoltage =  pDisplay_Set_BMS->stHMISetBMSLeadAcidParas.u16FloatVoltPoint;
        }

    }
}

/***********************************************************************************************************************
 功能：实现保护功能
************************************************************************************************************************/
static void ImplementProtectFunction(void)                
{
    if(Battery_Protect_Para.u8NowSOC <= Battery_Protect_Para.u8DisChargeStopSOC)                           //低SOC保护   
    {
        Battery_Protect_Para.eDisChargeState = STOP;                                                                                     
    }
    else if(Battery_Protect_Para.u8NowSOC > Battery_Protect_Para.u8DisChargeLimitSOC)                      //回差保护
    {
        Battery_Protect_Para.eDisChargeState = RUNNING;
    }
    else
    {
    }

    if(Battery_Protect_Para.u8NowSOC >= Battery_Protect_Para.u8ChargeStopSOC)                               //高SOC保护
    {
        Battery_Protect_Para.eChargeState = STOP;                                                            
    }
    else if(Battery_Protect_Para.u8NowSOC < Battery_Protect_Para.u8ChargeLimitSOC)                          //回差保护
    {
        Battery_Protect_Para.eChargeState = RUNNING;
    }
    else
    {
    }

    if(Battery_Protect_Para.eDisChargeState == STOP)
    {
        Battery_Protect_Para.s16MaxDisChargeCurrent = 0;    
    }
    
    if(Battery_Protect_Para.eChargeState == STOP)
    {
        Battery_Protect_Para.s16MaxChargeCurrent = 0;    
    } 
}

/***************************************************************************
 功能:弱电池保护
****************************************************************************/
static void WeakBatteryProtect(void)
{
    static uint8_t u8LastDisChargeState = RUNNING;
    static uint8_t u8RepairCount = 0;

    if(u8LastDisChargeState != Battery_Protect_Para.eDisChargeState)
    {
        if(Battery_Protect_Para.eDisChargeState == STOP)
        {
            Battery_Protect_Para.WeakBatteryPara[u8RepairCount].u8LowSOC_Count ++;

        }

        u8LastDisChargeState = Battery_Protect_Para.eDisChargeState;
    }

    if(Battery_Protect_Para.WeakBatteryPara[u8RepairCount].u8LowSOC_Count == 1)                                              //第一次触发截止SOC，转充电，充电至修复SOC
    {
        Battery_Protect_Para.eChargeState = RUNNING;                                                     

        if(Battery_Protect_Para.u8NowSOC > SOC_REPAIR)                                           //修复完成
        {
            Battery_Protect_Para.s16MaxChargeCurrent = 0;

        }
    }
    else if(Battery_Protect_Para.WeakBatteryPara[u8RepairCount].u8LowSOC_Count == 2)                                         //第二次触发截止SOC，转充电，充电至截止SOC
    {
        Battery_Protect_Para.eChargeState = RUNNING;                                                

        if(Battery_Protect_Para.u8NowSOC >= Battery_Protect_Para.u8ChargeStopSOC)                        //修复完成
        {

            Battery_Protect_Para.WeakBatteryPara[u8RepairCount].u8LowSOC_Count = 0;
//            Get_SysTime(&WeakBatteryPara[u8RepairCount].tCompleteRepairTime);                          //获取完成修复时间
            Battery_Protect_Para.WeakBatteryPara[u8RepairCount].u32CompleteRepairTimestamp = u32SysTimestamp;                 //完成修复时间戳
            u8RepairCount ++;
        }
    }
    else
    {
    }

    if(u8RepairCount == 1)
    {
        if(Battery_Protect_Para.WeakBatteryPara[1].u32CompleteRepairTimestamp - Battery_Protect_Para.WeakBatteryPara[0].u32CompleteRepairTimestamp < 86400)
        {
            Battery_Protect_Para.eWeakBatteryFault = BATTERY_ERROR;
        }
        else
        {
            Battery_Protect_Para.eWeakBatteryFault = BATTERY_OK;

        }

        memcpy(&Battery_Protect_Para.WeakBatteryPara[0], &Battery_Protect_Para.WeakBatteryPara[1], sizeof(WeakBattery_ParaDef));
        u8RepairCount = 0;
    }
}


/***********************************************************************************************************************
 功能：恒流充电阶段
************************************************************************************************************************/
static uint8_t LeadBattery_ConstantCurrent_Charge(void)                
{
//    Battery_Protect_Para.u16MaxChargeVoltage = MIN(Battery_Protect_Para.u16MaxChargeVoltage, LeadBattery_ChargeState_Table[CONSTANTCURRENT_STAGE].u16LimitVoltage);
    if(Battery_Protect_Para.u16MaxChargeVoltage >= LeadBattery_ChargeState_Table[CONSTANTCURRENT_STAGE].u16LimitVoltage)
    {
        Battery_Protect_Para.u16MaxChargeVoltage = LeadBattery_ChargeState_Table[CONSTANTCURRENT_STAGE].u16LimitVoltage;                                  
    }
    
//    Battery_Protect_Para.s16MaxChargeCurrent = MIN(Battery_Protect_Para.s16MaxChargeCurrent, LeadBattery_ChargeState_Table[CONSTANTCURRENT_STAGE].s16LimitCurrentFactor * LeadBattery_Paras.u8NominalCapacity /10);
    if(Battery_Protect_Para.s16MaxChargeCurrent >= LeadBattery_ChargeState_Table[CONSTANTCURRENT_STAGE].s16LimitCurrentFactor * LeadBattery_Paras.u8NominalCapacity /10)
    {
        Battery_Protect_Para.s16MaxChargeCurrent = LeadBattery_ChargeState_Table[CONSTANTCURRENT_STAGE].s16LimitCurrentFactor * LeadBattery_Paras.u8NominalCapacity /10;                                  
    }
    
    if(stBatteryCorePara.u16BatVolt >= LeadBattery_ChargeState_Table[CONSTANTVOLTAGE_STAGE].u16LimitVoltage)              //达到恒压点
    {
        LeadBattery_Paras.eChargeStage =  CONSTANTVOLTAGE_STAGE;       
    }    
    return  0;
}

/***********************************************************************************************************************
 功能：恒压充电阶段
************************************************************************************************************************/
static uint8_t LeadBattery_ConstantVoltage_Charge(void)           
{
//    Battery_Protect_Para.u16MaxChargeVoltage = MIN(Battery_Protect_Para.u16MaxChargeVoltage, LeadBattery_ChargeState_Table[CONSTANTVOLTAGE_STAGE].u16LimitVoltage);
    if(Battery_Protect_Para.u16MaxChargeVoltage >= LeadBattery_ChargeState_Table[CONSTANTVOLTAGE_STAGE].u16LimitVoltage)
    {
        Battery_Protect_Para.u16MaxChargeVoltage = LeadBattery_ChargeState_Table[CONSTANTVOLTAGE_STAGE].u16LimitVoltage;                                  
    }
    
//    Battery_Protect_Para.s16MaxChargeCurrent = MIN(Battery_Protect_Para.s16MaxChargeCurrent, LeadBattery_ChargeState_Table[CONSTANTVOLTAGE_STAGE].s16LimitCurrentFactor * LeadBattery_Paras.u8NominalCapacity /10);
    if(Battery_Protect_Para.s16MaxChargeCurrent >= LeadBattery_ChargeState_Table[CONSTANTVOLTAGE_STAGE].s16LimitCurrentFactor * LeadBattery_Paras.u8NominalCapacity /10)
    {
        Battery_Protect_Para.s16MaxChargeCurrent = LeadBattery_ChargeState_Table[CONSTANTVOLTAGE_STAGE].s16LimitCurrentFactor * LeadBattery_Paras.u8NominalCapacity /10;                                  
    }
    
    if(abs(stBatteryCorePara.s16ChgCurr) < LeadBattery_ChargeState_Table[FLOATINGCHARGE_STAGE].s16LimitCurrentFactor * LeadBattery_Paras.u8NominalCapacity /10)              //电流小于转灯电流，0.1C
    {
        LeadBattery_Paras.eChargeStage =  FLOATINGCHARGE_STAGE;       
    }    
    return  0;
}

/***********************************************************************************************************************
 功能：浮充充电阶段
************************************************************************************************************************/
static uint8_t LeadBattery_Floating_Charge(void)          
{
//    Battery_Protect_Para.u16MaxChargeVoltage = MIN(Battery_Protect_Para.u16MaxChargeVoltage, LeadBattery_ChargeState_Table[CONSTANTVOLTAGE_STAGE].u16LimitVoltage);
    if(Battery_Protect_Para.u16MaxChargeVoltage >= LeadBattery_ChargeState_Table[FLOATINGCHARGE_STAGE].u16LimitVoltage)
    {
        Battery_Protect_Para.u16MaxChargeVoltage = LeadBattery_ChargeState_Table[FLOATINGCHARGE_STAGE].u16LimitVoltage;                                  
    }
    
//    Battery_Protect_Para.s16MaxChargeCurrent = MIN(Battery_Protect_Para.s16MaxChargeCurrent, LeadBattery_ChargeState_Table[CONSTANTVOLTAGE_STAGE].s16LimitCurrentFactor * LeadBattery_Paras.u8NominalCapacity /10);
    if(Battery_Protect_Para.s16MaxChargeCurrent >= LeadBattery_ChargeState_Table[FLOATINGCHARGE_STAGE].s16LimitCurrentFactor * LeadBattery_Paras.u8NominalCapacity /10)
    {
        Battery_Protect_Para.s16MaxChargeCurrent = LeadBattery_ChargeState_Table[FLOATINGCHARGE_STAGE].s16LimitCurrentFactor * LeadBattery_Paras.u8NominalCapacity /10;                                  
    }
    
    if(abs(stBatteryCorePara.s16ChgCurr) < LeadBattery_ChargeState_Table[FLOATINGCHARGE_STAGE].s16LimitCurrentFactor)              //电流小于0.1A，趋近于0，最小分辨率
    { 
        Battery_Protect_Para.s16MaxChargeCurrent = 0;                                                                             //停机
    }    
    return  0;
}

/***********************************************************************************************************************
 功能：浮充充电阶段
************************************************************************************************************************/
static uint8_t LeadBattery_Charge(void)          
{
    switch (LeadBattery_Paras.eChargeStage)
    {
    	case CONSTANTCURRENT_STAGE:
            LeadBattery_ConstantCurrent_Charge();
    		break;
    	case CONSTANTVOLTAGE_STAGE:
            LeadBattery_ConstantVoltage_Charge();
    		break;
        case FLOATINGCHARGE_STAGE:
            LeadBattery_Floating_Charge();
    		break;
    	default:
    		break;
    }
    return  0;
}
/***********************************************************************************************************************
 功能：放电管理
************************************************************************************************************************/
static uint8_t LeadBattery_DisCharge(void)          
{
      //根据实时放电电流，相应提高放电截止电压
//    Battery_Protect_Para.s16MaxDisChargeCurrent = LeadBattery_Paras.u8NominalCapacity * 10;       
    if(stBatteryCorePara.s16ChgCurr < LeadBattery_DisCharge_Table[0].s16CurrentRange * LeadBattery_Paras.u8NominalCapacity /10)              
    {
//        Battery_Protect_Para.u16MaxDisChargeVoltage = MAX(Battery_Protect_Para.u16MaxDisChargeVoltage, LeadBattery_DisCharge_Table[0].u16LimitVoltage);
        if(Battery_Protect_Para.u16MaxDisChargeVoltage < LeadBattery_DisCharge_Table[0].u16LimitVoltage)
        {                
            Battery_Protect_Para.u16MaxDisChargeVoltage = LeadBattery_DisCharge_Table[0].u16LimitVoltage;
        }
    }
    else if(stBatteryCorePara.s16ChgCurr < LeadBattery_DisCharge_Table[1].s16CurrentRange * LeadBattery_Paras.u8NominalCapacity /10)              
    {
//        Battery_Protect_Para.u16MaxDisChargeVoltage = MAX(Battery_Protect_Para.u16MaxDisChargeVoltage, LeadBattery_DisCharge_Table[1].u16LimitVoltage);
        if(Battery_Protect_Para.u16MaxDisChargeVoltage < LeadBattery_DisCharge_Table[1].u16LimitVoltage)
        {                
            Battery_Protect_Para.u16MaxDisChargeVoltage = LeadBattery_DisCharge_Table[1].u16LimitVoltage;
        }
    }

    else if(stBatteryCorePara.s16ChgCurr < LeadBattery_DisCharge_Table[2].s16CurrentRange * LeadBattery_Paras.u8NominalCapacity /10)              
    {
//        Battery_Protect_Para.u16MaxDisChargeVoltage = MAX(Battery_Protect_Para.u16MaxDisChargeVoltage, LeadBattery_DisCharge_Table[2].u16LimitVoltage);
        if(Battery_Protect_Para.u16MaxDisChargeVoltage < LeadBattery_DisCharge_Table[2].u16LimitVoltage)
        {                
            Battery_Protect_Para.u16MaxDisChargeVoltage = LeadBattery_DisCharge_Table[2].u16LimitVoltage;
        }
    }
//    else if(stBatteryCorePara.s16ChgCurr < LeadBattery_DisCharge_Table[3].s16CurrentRange * LeadBattery_Paras.u8NominalCapacity /10)   //暂时只做1C放电           
//    {
////        Battery_Protect_Para.u16MaxDisChargeVoltage = MAX(Battery_Protect_Para.u16MaxDisChargeVoltage, LeadBattery_DisCharge_Table[3].u16LimitVoltage);
//        if(Battery_Protect_Para.u16MaxDisChargeVoltage < LeadBattery_DisCharge_Table[3].u16LimitVoltage)
//        {                
//            Battery_Protect_Para.u16MaxDisChargeVoltage = LeadBattery_DisCharge_Table[3].u16LimitVoltage;
//        }
//    }
    else  
    {
        Battery_Protect_Para.s16MaxDisChargeCurrent = 0;                                                                 //限流失败，关机   
    }
    return  0;
    
////    for(uint8_t i = 0; i <= 3; i ++)
//    for(uint8_t i = 0; i <= 2; i ++)
//    {
//        if(stBatteryCorePara.s16ChgCurr < LeadBattery_DisCharge_Table[i].s16CurrentRange * LeadBattery_Paras.u8NominalCapacity /10)   //暂时只做1C放电           
//        {
//        //        Battery_Protect_Para.u16MaxDisChargeVoltage = MAX(Battery_Protect_Para.u16MaxDisChargeVoltage, LeadBattery_DisCharge_Table[i].u16LimitVoltage);
//            if(Battery_Protect_Para.u16MaxDisChargeVoltage < LeadBattery_DisCharge_Table[i].u16LimitVoltage)
//            {                
//                Battery_Protect_Para.u16MaxDisChargeVoltage = LeadBattery_DisCharge_Table[i].u16LimitVoltage;
//            }
//            return  0;
//        }    
//    }    
//    Battery_Protect_Para.s16MaxDisChargeCurrent = 0;                                                                   //限流失败，关机   
}

/***********************************************************************************************************************
 功能：静态电池SOC估算，开路电压OCV曲线法
************************************************************************************************************************/
static uint8_t LeadBattery_SOC_OCV(uint16_t u16Voltage)                           
{
    uint8_t u8SOC = 0;
    
    uint32_t u32Voltage = u16Voltage;
    if(u32Voltage > 528)
    {
        u8SOC = 100;   
    }
    else if((u32Voltage >= 520) && (u32Voltage <= 528))                   //kx+b,根据Matlab模型拟合OCV曲线确定函数关系
    { 
        u8SOC = (u32Voltage*1000 - 483440) / 452;
    }   
    else if((u32Voltage < 520) && (u32Voltage >= 454))
    {
        u8SOC = (u32Voltage*1000 - 454080) / 824;       
    }
    else if(u32Voltage < 454)
    {
         u8SOC = 0;
    }   
    
    return u8SOC;  
}

/***********************************************************************************************************************
 功能：动态电池SOC估算,安时积分法
************************************************************************************************************************/
static uint8_t LeadBattery_SOC_Integral(uint8_t u8InitiateSOC, uint8_t u8InitiateSOH, int16_t s16Current)          
{
    uint8_t u8SOC = 0;   
    
    int16_t s16FilterCurrent = CalculateAverageFilterValue(s16Current);
    
    LeadBattery_Paras.s32CapacityIntegral += s16FilterCurrent;                                                          //秒积分，扩大10倍
    LeadBattery_Paras.s32CapacityIntegral /= COULOMBICEFFICIENCY;                                                       //除以昆仑效率
    LeadBattery_Paras.u16ActualCapacity = LeadBattery_Paras.u8NominalCapacity * u8InitiateSOH;                          //实际容量,扩大100倍  
    
    float fIncrementSOC = (float)LeadBattery_Paras.s32CapacityIntegral /(float)LeadBattery_Paras.u16ActualCapacity /3.6;
    u8SOC = (int8_t)u8InitiateSOC - (int8_t)fIncrementSOC;
    
//    u8SOC = u8InitiateSOC - LeadBattery_Paras.s32CapacityIntegral * COULOMBICEFFICIENCY /LeadBattery_Paras.u32ActualCapacity /3.6;                     //充电为负，放电为正  
//    u8SOC = u8InitiateSOC - LeadBattery_Paras.s32CapacityIntegral /3600 /10 *COULOMBICEFFICIENCY /(LeadBattery_Paras.u32ActualCapacity /100) *100;  
    
    if(u8SOC == 0)
    {
        u8SOC = u8InitiateSOC;         
    }    
    else if(u8SOC > 100)
    {
        u8SOC = 100;   
    }  
    return u8SOC;  
}

/***********************************************************************************************************************
 功能：铅酸电池管理系统
************************************************************************************************************************/
static void LeadBattery_Running(void)          
{    
    static  uint8_t u8StartTime = 0;
    //获取PCS上报的电池核心数据   
    memset(&stBatteryCorePara, 0, sizeof(BatteryCorePara_TypeDef));
    GetBatteryCoreData(&stBatteryCorePara);
    
    //以放电表第三档1C放电做放电参数
//    Battery_Protect_Para.u16MaxDisChargeVoltage = MAX(Battery_Protect_Para.u16MaxDisChargeVoltage, LeadBattery_DisCharge_Table[2].u16LimitVoltage);
    if(Battery_Protect_Para.u16MaxDisChargeVoltage < LeadBattery_DisCharge_Table[2].u16LimitVoltage)
    {
        Battery_Protect_Para.u16MaxDisChargeVoltage = LeadBattery_DisCharge_Table[2].u16LimitVoltage;
    }
    
//    Battery_Protect_Para.s16MaxDisChargeCurrent = MIN(Battery_Protect_Para.s16MaxDisChargeCurrent, LeadBattery_DisCharge_Table[2].s16CurrentRange * LeadBattery_Paras.u8NominalCapacity /10);
    if(Battery_Protect_Para.s16MaxDisChargeCurrent >= LeadBattery_DisCharge_Table[2].s16CurrentRange * LeadBattery_Paras.u8NominalCapacity /10)
    {
        Battery_Protect_Para.s16MaxDisChargeCurrent = LeadBattery_DisCharge_Table[2].s16CurrentRange * LeadBattery_Paras.u8NominalCapacity /10;  
    }

    //以充电表恒流充电参数做充电参数    
//    Battery_Protect_Para.u16MaxChargeVoltage = MIN(Battery_Protect_Para.u16MaxChargeVoltage, LeadBattery_ChargeState_Table[CONSTANTCURRENT_STAGE].u16LimitVoltage);    
    if(Battery_Protect_Para.u16MaxChargeVoltage >= LeadBattery_ChargeState_Table[CONSTANTCURRENT_STAGE].u16LimitVoltage)
    {
        Battery_Protect_Para.u16MaxChargeVoltage = LeadBattery_ChargeState_Table[CONSTANTCURRENT_STAGE].u16LimitVoltage;
    }
    
//    Battery_Protect_Para.s16MaxChargeCurrent = MIN(Battery_Protect_Para.s16MaxChargeCurrent, LeadBattery_ChargeState_Table[CONSTANTCURRENT_STAGE].s16LimitCurrentFactor * LeadBattery_Paras.u8NominalCapacity /10);
    if(Battery_Protect_Para.s16MaxChargeCurrent >= LeadBattery_ChargeState_Table[CONSTANTCURRENT_STAGE].s16LimitCurrentFactor * LeadBattery_Paras.u8NominalCapacity /10)
    {
        Battery_Protect_Para.s16MaxChargeCurrent = LeadBattery_ChargeState_Table[CONSTANTCURRENT_STAGE].s16LimitCurrentFactor * LeadBattery_Paras.u8NominalCapacity /10;
    }    

    //状态机切换
    if(abs(stBatteryCorePara.s16ChgCurr) <= CLOSETOZERO)       //电流为0
    {   
        switch (LeadBattery_Paras.eLeadBattery_LastState)                                                         //上次状态
        {
        	case STATIC_STATE:
                LeadBattery_Paras.eLeadBattery_State = STATIC_STATE;       		
            break;
        	case RECOVER_STATE:
                LeadBattery_Paras.eLeadBattery_State = RECOVER_STATE;
                LeadBattery_Paras.u16RecoverTime ++;
                if(LeadBattery_Paras.u16RecoverTime >= RECOVERTIME)                                                       //持续恢复15min到静置状态
                {       
                    LeadBattery_Paras.eLeadBattery_State = STATIC_STATE;                                          //从恢复跳转到静置
                    LeadBattery_Paras.u16RecoverTime = 0;
                }
            break;
            case RUNNING_STATE:
                LeadBattery_Paras.eLeadBattery_State = RECOVER_STATE;        		                              //从运行跳转到恢复
            break;
        	default:	
            break;
        }
       u8StartTime = 0;
    }
    else if(abs(stBatteryCorePara.s16ChgCurr) > CLOSETOZERO)       //电流不为0
    {   
        u8StartTime ++;                                                                                              //等待电池母线上电容充电结束
        if(u8StartTime > 2)
        {
            LeadBattery_Paras.eLeadBattery_State = RUNNING_STATE;                                                     //电流改变
            LeadBattery_Paras.u16RecoverTime = 0;
            u8StartTime = 0;
        }
        
    }
    //核心功能
    switch (LeadBattery_Paras.eLeadBattery_State)
    {
    	case STATIC_STATE:
            if(LeadBattery_Paras.eLeadBattery_LastState == RECOVER_STATE)                                         //恢复跳到静置，进行SOH计算
            {
                LeadBattery_Paras.u8EndSOC = LeadBattery_SOC_OCV(stBatteryCorePara.u16BatVolt);                   //计算前先用开路电压法更新SOC
                LeadBattery_Paras.u8SOCStaticDifference = abs(LeadBattery_Paras.u8EndSOC - LeadBattery_Paras.u8StartSOC);
                
                if(LeadBattery_Paras.u8SOCStaticDifference >= 50)                                                 //SOC发生较大变化
                {
                    uint32_t u32CapacityChange = LeadBattery_Paras.u8SOCStaticDifference *LeadBattery_Paras.u8NominalCapacity *360;
                    LeadBattery_Paras.u8NowSOH =  abs(LeadBattery_Paras.s32CapacityIntegral) /u32CapacityChange;
//                    LeadBattery_Paras.u8NowSOH =  LeadBattery_Paras.s32CapacityIntegral /LeadBattery_Paras.u8SOCStaticDifference /LeadBattery_Paras.u8NominalCapacity /360;
                    LeadBattery_Paras.u8LastSOH = LeadBattery_Paras.u8NowSOH;                                     //动态积分/静态SOC变化/标称容量
                }
            }
            LeadBattery_Paras.u8NowSOC = LeadBattery_SOC_OCV(stBatteryCorePara.u16BatVolt);                                  //电流
            LeadBattery_Paras.u8StartSOC = LeadBattery_Paras.u8NowSOC;
            LeadBattery_Paras.s32CapacityIntegral = 0;
            LeadBattery_Paras.eChargeStage = CONSTANTCURRENT_STAGE;
        break;
    	case RUNNING_STATE: 
            if(stBatteryCorePara.s16ChgCurr > CLOSETOZERO)                                                                     //放电管理
            { 
                LeadBattery_DisCharge();
            }
            else if(stBatteryCorePara.s16ChgCurr < -CLOSETOZERO)                                                               //充电管理
            { 
                LeadBattery_Charge();
            }
    		LeadBattery_Paras.u8NowSOC = LeadBattery_SOC_Integral(LeadBattery_Paras.u8StartSOC, LeadBattery_Paras.u8LastSOH, stBatteryCorePara.s16ChgCurr);
            LeadBattery_Paras.u8EndSOC = LeadBattery_Paras.u8NowSOC;
        break;
    	case RECOVER_STATE:
    		LeadBattery_Paras.u8NowSOC = LeadBattery_Paras.u8EndSOC;                                              //恢复状态钳住运行安时积分SOC
            LeadBattery_Paras.eChargeStage = CONSTANTCURRENT_STAGE;
        break;
        default:
    		break;
    }
    LeadBattery_Paras.eLeadBattery_LastState = LeadBattery_Paras.eLeadBattery_State;
    Battery_Protect_Para.u8NowSOC = LeadBattery_Paras.u8NowSOC;
    Battery_Protect_Para.u16BMSSOC = Battery_Protect_Para.u8NowSOC *10; 
    Battery_Protect_Para.u16BMSVoltage = stBatteryCorePara.u16BatVolt;
}

/***************************************************************************
功能:平均值滤波
****************************************************************************/
int16_t CalculateAverageFilterValue(int16_t s16value)
{
    uint8_t u8ArrayIndex = 0;
    int16_t s16FilterValue = 0;
    int32_t s32Total = 0;
    static int16_t s16Array[ArrayMax] = {0,};
    
    memmove(&s16Array[1], &s16Array[0], sizeof(int16_t) * u8ArrayIndex);
    s16Array[0] =  s16value;
    
    if(u8ArrayIndex == ArrayMax)
    {
        u8ArrayIndex = ArrayMax - 1;
        
    }
    else
    {
        u8ArrayIndex++;
    }
    
    for(int i=0; i<u8ArrayIndex; i++)
    {
        s32Total = s32Total + s16Array[i];
    }
    
    s16FilterValue =  s32Total / u8ArrayIndex;
    return  s16FilterValue;
}

/***********************************************************************************************************************
 功能：获取PCS上报的电池核心数据接口
************************************************************************************************************************/
static void GetBatteryCoreData(BatteryCorePara_TypeDef* pBatteryCorePara)
{
    DCDCInformation_t stBatteryInformation;    
    memset(&stBatteryInformation, 0, sizeof(stBatteryInformation));
    GetDCDCInformation(&stBatteryInformation);
    
    pBatteryCorePara ->u16BatVolt  = stBatteryInformation.u16BatVolt;
    pBatteryCorePara ->s16ChgCurr  = stBatteryInformation.s16ChgCurr;
    pBatteryCorePara ->s16BatPower = stBatteryInformation.s16BatPower;
    pBatteryCorePara ->u16BatState = stBatteryInformation.u16BatState;
} 

/***************************************************************************
 功能:LCD屏电池包的数据绑定（铅酸）
****************************************************************************/
void GetDisplayRealTimeLeadBatteryData(Display_DATA_BMS* ptDisplayBmsData)
{
    ptDisplayBmsData->u16BMSVoltage = (uint16_t) (stBatteryCorePara.u16BatVolt / 100);                //后续优化
    ptDisplayBmsData->sBMSCurrent = (int16_t) (stBatteryCorePara.s16ChgCurr / 10);                  //后续优化                                                                             //???
    ptDisplayBmsData->u8SOC = (uint8_t) (LeadBattery_Paras.u8NowSOC & 0x00FF);
    ptDisplayBmsData->u8SOH = (uint8_t) (LeadBattery_Paras.u8NowSOH & 0x00FF);
    
    ptDisplayBmsData->sMaxChargeCurrent = (int16_t) (Battery_Protect_Para.s16MaxChargeCurrent);
    ptDisplayBmsData->u16MaxChargeVoltage = (uint16_t) (Battery_Protect_Para.u16MaxChargeVoltage);       //后续优化                                                     //???
    ptDisplayBmsData->sMaxDisChargeCurrent = (int16_t) (Battery_Protect_Para.s16MaxDisChargeCurrent);
    ptDisplayBmsData->u16MaxDisChargeVoltage = (uint16_t) (Battery_Protect_Para.u16MaxDisChargeVoltage);  //后续优化
}

/***********************************************************************************************************************
 功能：获取BMS保护参数
************************************************************************************************************************/
void GetBMSProtectParam(Battery_Protect_Para_t* pBattery_Protect_Para)
{
    memcpy(pBattery_Protect_Para, &Battery_Protect_Para, sizeof(Battery_Protect_Para_t));
}
#endif
#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
 
