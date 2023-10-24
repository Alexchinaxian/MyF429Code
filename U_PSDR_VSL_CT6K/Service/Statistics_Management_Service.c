/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Statistics_Management_Service.c 
 用途 : 统计管理服务
***********************************************************************************************************************/
#ifndef _STATISTICS_MANAGEMENT_C_
#define _STATISTICS_MANAGEMENT_C_

#include "HeadFile.h"
#include "RTC_Service.h"
#include "Storage_Management_Service.h"
#include "Statistics_Management_Service.h"
#include <stdlib.h>

#if STATISTICS_SERVICE_MOUDLE

/*统计管理模块状态*/
StatisticsStatus_TypeDef gEnumStatisticsStatus = STATISTICS_STATE_NULL;
/*总滤波list全局变量*/
PowerFilterList gStFilter;
/*系统1s计数器*/
uint64_t gU64TimeCounter;
/*计算周期累加和*/
STATISTICAL_DATA_SumPara  gStStaticticalSum;

FilterAlgorithm_TypeDef gFilterType;

void StatisticsManagement_Handler(void)
{       
    if (STATUS_FALSE == TimeTask_GetFlag_1s)
    {
        return;
    }

    switch (gEnumStatisticsStatus)
    {
        case STATISTICS_INIT://统计管理模块初始化
            {
                StatisticsInit();
                gEnumStatisticsStatus = STATISTICS_RUNNING;
            }     
            break;
        case STATISTICS_RUNNING://统计管理模块运行
            {               
                StatisticsRunning();
            } 
            break;
        case STATISTICS_DESTRCUCTION://统计管理模块析构,用掉电检测村塾
            {
                StatisticsDestruction();
            }
            break;
        default:
            ;
    }
}

/***********************************************************************************************************************
 功能：统计管理模块全局变量初始化
***********************************************************************************************************************/
void Statistics_Service_InitVar(void)
{
    gEnumStatisticsStatus = STATISTICS_INIT; //初始化状态
    memset(&gStFilter,0,sizeof(PowerFilterList));
    gU64TimeCounter = 0;
    memset(&gStStaticticalSum,0,sizeof(STATISTICAL_DATA_SumPara));
    gFilterType = FILTER_AVERAGE;
}

/***********************************************************************************************************************
 功能：统计管理模块析构
***********************************************************************************************************************/
void Statistics_Service_DestructionVar(void)
{
    StatisticsDestruction();
    gEnumStatisticsStatus = STATISTICS_DESTRCUCTION;  
}

/***********************************************************************************************************************
 功能：统计管理模块硬件初始化
***********************************************************************************************************************/
void Statistics_Service_HwInit(void)
{
}

/***************************************************************************
 功能:初始化驱动，全局变量等
****************************************************************************/
void StatisticsInit(void)
{   
      gU64TimeCounter = 0;
}

/***************************************************************************
 功能:统计管理总运行函数
****************************************************************************/
void StatisticsRunning(void)
{
    if(gU64TimeCounter % COMM_QUERY_TIME_PERIOD == 0)
    {
       //查询功率接口
       Display_Kind_Power stKindPower;
       memset(&stKindPower,0,sizeof(Display_Kind_Power));
       Display_Get_KindPower(&stKindPower);
        
       if(gFilterType == FILTER_AVERAGE)
       {
            uint16_t u16PVPower = CalculatePVAverageFilterValue(stKindPower.u16PVPower);
            gStStaticticalSum.stPVPowerSum += u16PVPower * COMM_QUERY_TIME_PERIOD;
           
            uint16_t u16LoadPower = CalculateLoadAverageFilterValue(stKindPower.u16tLoadPower);
            gStStaticticalSum.stLoadPowerSum += u16LoadPower * COMM_QUERY_TIME_PERIOD;
           
            if(stKindPower.s16GridPower >= 0) //充电为负 放电为正
            {
                uint16_t u16OutputPower = CalculateOutputAverageFilterValue(abs(stKindPower.s16GridPower));
                gStStaticticalSum.stOutputPowerSum += u16OutputPower * COMM_QUERY_TIME_PERIOD;
           
                uint16_t u16InputPower = CalculateInputAverageFilterValue(0);
                gStStaticticalSum.stInputPowerSum += u16InputPower * COMM_QUERY_TIME_PERIOD;
            }
            else
            {
                uint16_t u16OutputPower = CalculateOutputAverageFilterValue(0);
                gStStaticticalSum.stOutputPowerSum += u16OutputPower * COMM_QUERY_TIME_PERIOD;
           
                uint16_t u16InputPower = CalculateInputAverageFilterValue(abs(stKindPower.s16GridPower));
                gStStaticticalSum.stInputPowerSum += u16InputPower * COMM_QUERY_TIME_PERIOD;
            }
            
            uint16_t u16ChargePower = CalculateChargeAverageFilterValue(stKindPower.u16ChargePower);
            gStStaticticalSum.stChagePowerSum += u16ChargePower * COMM_QUERY_TIME_PERIOD;
           
            uint16_t u16DisChargePower = CalculateDisChargeAverageFilterValue(stKindPower.u16tDisChargePower);
            gStStaticticalSum.stDisChagePowerSum += u16DisChargePower * COMM_QUERY_TIME_PERIOD;
       }

    }
    
    if(gU64TimeCounter % COMM_CALCULATE_TIME_PERIOD == 0)
    {
        Display_DATA_STATISTICAL *pSTATISTICAL = Display_Get_SystemStatistical();
        
        /*光伏 5min 累加一次*/
        uint32_t stPVPowerSumTemp = gStStaticticalSum.stPVPowerSum / (1000 * 60 *60); 
        pSTATISTICAL->stDayStatisticaldata.stPVPowerGeneration   += stPVPowerSumTemp;
        pSTATISTICAL->stMonthStatisticaldata.stPVPowerGeneration += stPVPowerSumTemp;
        pSTATISTICAL->stYearStatisticaldata.stPVPowerGeneration  += stPVPowerSumTemp;
        pSTATISTICAL->stTotalStatisticaldata.stPVPowerGeneration += stPVPowerSumTemp;
        
        /*负载 5min 累加一次*/
        uint32_t stLoadPowerSumTemp = gStStaticticalSum.stLoadPowerSum / (1000 * 60 *60); 
        pSTATISTICAL->stDayStatisticaldata.stLoadPowerGeneration   += stLoadPowerSumTemp;
        pSTATISTICAL->stMonthStatisticaldata.stLoadPowerGeneration += stLoadPowerSumTemp;
        pSTATISTICAL->stYearStatisticaldata.stLoadPowerGeneration  += stLoadPowerSumTemp;
        pSTATISTICAL->stTotalStatisticaldata.stLoadPowerGeneration += stLoadPowerSumTemp;
        
        /*充电 5min 累加一次*/
        uint32_t stChagePowerSumTemp = gStStaticticalSum.stChagePowerSum / (1000 * 60 *60); 
        pSTATISTICAL->stDayStatisticaldata.stChagePowerGeneration   += stChagePowerSumTemp;
        pSTATISTICAL->stMonthStatisticaldata.stChagePowerGeneration += stChagePowerSumTemp;
        pSTATISTICAL->stYearStatisticaldata.stChagePowerGeneration  += stChagePowerSumTemp;
        pSTATISTICAL->stTotalStatisticaldata.stChagePowerGeneration += stChagePowerSumTemp;
        
        /*充电 5min 累加一次*/
        uint32_t stDisChagePowerSumTemp = gStStaticticalSum.stDisChagePowerSum / (1000 * 60 *60); 
        pSTATISTICAL->stDayStatisticaldata.stDisChagePowerGeneration   += stDisChagePowerSumTemp;
        pSTATISTICAL->stMonthStatisticaldata.stDisChagePowerGeneration += stDisChagePowerSumTemp;
        pSTATISTICAL->stYearStatisticaldata.stDisChagePowerGeneration  += stDisChagePowerSumTemp;
        pSTATISTICAL->stTotalStatisticaldata.stDisChagePowerGeneration += stDisChagePowerSumTemp;
        
        /*输出 5min 累加一次*/
        uint32_t stOutputPowerSumTemp = gStStaticticalSum.stOutputPowerSum / (1000 * 60 *60); 
        pSTATISTICAL->stDayStatisticaldata.stOutputPowerGeneration   += stOutputPowerSumTemp;
        pSTATISTICAL->stMonthStatisticaldata.stOutputPowerGeneration += stOutputPowerSumTemp;
        pSTATISTICAL->stYearStatisticaldata.stOutputPowerGeneration  += stOutputPowerSumTemp;
        pSTATISTICAL->stTotalStatisticaldata.stOutputPowerGeneration += stOutputPowerSumTemp; 
        
        /*输入 5min 累加一次*/
        uint32_t stInputPowerSumTemp = gStStaticticalSum.stInputPowerSum / (1000 * 60 *60); 
        pSTATISTICAL->stDayStatisticaldata.stInputPowerGeneration   += stInputPowerSumTemp;
        pSTATISTICAL->stMonthStatisticaldata.stInputPowerGeneration += stInputPowerSumTemp;
        pSTATISTICAL->stYearStatisticaldata.stInputPowerGeneration  += stInputPowerSumTemp;
        pSTATISTICAL->stTotalStatisticaldata.stInputPowerGeneration += stInputPowerSumTemp; 
        
        /*判断是否到清零节点*/
        ClearZeroWithKeyNodes(pSTATISTICAL);
        pSTATISTICAL = NULL;
    }
    
    gU64TimeCounter++ ;
    
}

/***************************************************************************
 功能:到达日，月，年节点数据清零
****************************************************************************/
void ClearZeroWithKeyNodes(Display_DATA_STATISTICAL *pSTATISTICAL)
{
    bool_t bClearFlag = STATUS_FALSE;

    TimeInf_t tab_SysTime;
    memset(&tab_SysTime, 0, sizeof(TimeInf_t));
    Get_SysTime(&tab_SysTime);

    int8_t u8Month = (int8_t)tab_SysTime.u8Month;
    int8_t u8Day   = (int8_t)tab_SysTime.u8Day;
    int8_t u8Hour  = (int8_t)tab_SysTime.u8Hour;
    int8_t u8Min   = (int8_t)tab_SysTime.u8Min;

    /*年数据清零*/
    if((u8Month == 12) && (u8Day == 31) && (u8Hour == 23) && (u8Min == 59))
    {
        pSTATISTICAL->stYearStatisticaldata.stChagePowerGeneration    = 0;
        pSTATISTICAL->stYearStatisticaldata.stDisChagePowerGeneration = 0;
        pSTATISTICAL->stYearStatisticaldata.stInputPowerGeneration    = 0;
        pSTATISTICAL->stYearStatisticaldata.stLoadPowerGeneration     = 0;
        pSTATISTICAL->stYearStatisticaldata.stOutputPowerGeneration   = 0;
        pSTATISTICAL->stYearStatisticaldata.stPVPowerGeneration       = 0;
        bClearFlag =  STATUS_TRUE;
    }

    /*月数据清零*/
    if(u8Month == 2)
    {
        if((u8Day == 29) || (u8Day == 28))
        {
            if((u8Hour == 23) && (u8Min == 59))
            {
                pSTATISTICAL->stMonthStatisticaldata.stChagePowerGeneration    = 0;
                pSTATISTICAL->stMonthStatisticaldata.stDisChagePowerGeneration = 0;
                pSTATISTICAL->stMonthStatisticaldata.stInputPowerGeneration    = 0;
                pSTATISTICAL->stMonthStatisticaldata.stLoadPowerGeneration     = 0;
                pSTATISTICAL->stMonthStatisticaldata.stOutputPowerGeneration   = 0;
                pSTATISTICAL->stMonthStatisticaldata.stPVPowerGeneration       = 0;
                bClearFlag =  STATUS_TRUE;
            }
        }
    }
    else if((u8Month == 4) || (u8Month == 6) ||(u8Month == 9)||(u8Month == 11))
    {
        if(u8Day == 30)
        {
            if((u8Hour == 23) && (u8Min == 59))
            {
                pSTATISTICAL->stMonthStatisticaldata.stChagePowerGeneration    = 0;
                pSTATISTICAL->stMonthStatisticaldata.stDisChagePowerGeneration = 0;
                pSTATISTICAL->stMonthStatisticaldata.stInputPowerGeneration    = 0;
                pSTATISTICAL->stMonthStatisticaldata.stLoadPowerGeneration     = 0;
                pSTATISTICAL->stMonthStatisticaldata.stOutputPowerGeneration   = 0;
                pSTATISTICAL->stMonthStatisticaldata.stPVPowerGeneration       = 0;
                bClearFlag =  STATUS_TRUE;
            }
        }
    }
    else
    {
        if(u8Day == 31)
        {
            if((u8Hour == 23) && (u8Min == 59))
            {
                pSTATISTICAL->stMonthStatisticaldata.stChagePowerGeneration    = 0;
                pSTATISTICAL->stMonthStatisticaldata.stDisChagePowerGeneration = 0;
                pSTATISTICAL->stMonthStatisticaldata.stInputPowerGeneration    = 0;
                pSTATISTICAL->stMonthStatisticaldata.stLoadPowerGeneration     = 0;
                pSTATISTICAL->stMonthStatisticaldata.stOutputPowerGeneration   = 0;
                pSTATISTICAL->stMonthStatisticaldata.stPVPowerGeneration       = 0;
                bClearFlag =  STATUS_TRUE;
            }
        }
    }

    /*天数据清零*/
    if((u8Hour == 23) && (u8Min == 59))
    {
        pSTATISTICAL->stDayStatisticaldata.stChagePowerGeneration    = 0;
        pSTATISTICAL->stDayStatisticaldata.stDisChagePowerGeneration = 0;
        pSTATISTICAL->stDayStatisticaldata.stInputPowerGeneration    = 0;
        pSTATISTICAL->stDayStatisticaldata.stLoadPowerGeneration     = 0;
        pSTATISTICAL->stDayStatisticaldata.stOutputPowerGeneration   = 0;
        pSTATISTICAL->stDayStatisticaldata.stPVPowerGeneration       = 0;
        bClearFlag =  STATUS_TRUE;
    }

    if(bClearFlag ==  STATUS_TRUE)
    {
        //存储到Flash
        Flash_Device_StatisticsData_Read(pSTATISTICAL, sizeof(Display_DATA_STATISTICAL));
    }
}

/***************************************************************************
功能:平均值滤波法计算光伏功率
****************************************************************************/
uint16_t CalculatePVAverageFilterValue(uint16_t arryU16PVPower)
{
    uint16_t  u16PVFilterPower = 0;
    
    memmove(&gStFilter.stArrayPV.arryU16PVPower[1],&gStFilter.stArrayPV.arryU16PVPower[0],sizeof(uint16_t)*gStFilter.stArrayPV.u8PVArryIndex);
    gStFilter.stArrayPV.arryU16PVPower[0] =  arryU16PVPower;
    
    if(gStFilter.stArrayPV.u8PVArryIndex == PV_FILTER_LIST_MAX_COUNT)
    {
        gStFilter.stArrayPV.u8PVArryIndex = PV_FILTER_LIST_MAX_COUNT - 1;
        
    }
    else
    {
        gStFilter.stArrayPV.u8PVArryIndex++;
    }
    
    uint32_t u32PVTotal = 0;
    for(int i=0;i<gStFilter.stArrayPV.u8PVArryIndex;i++)
    {
        u32PVTotal = u32PVTotal + gStFilter.stArrayPV.arryU16PVPower[i];
    }
    
    u16PVFilterPower =  u32PVTotal /  gStFilter.stArrayPV.u8PVArryIndex;
    return  u16PVFilterPower;
}

/***************************************************************************
 功能:平均值滤波法计算负载功率
****************************************************************************/
uint16_t CalculateLoadAverageFilterValue(uint16_t arryU16LoadPower)
{
    uint16_t  u16LoadFilterPower = 0;
    
    memmove(&gStFilter.stArrayLoad.arryU16LoadPower[1],&gStFilter.stArrayLoad.arryU16LoadPower[0],sizeof(uint16_t)*gStFilter.stArrayLoad.u8LoadArryIndex);
    gStFilter.stArrayLoad.arryU16LoadPower[0] =  arryU16LoadPower;
    
    if(gStFilter.stArrayLoad.u8LoadArryIndex == LOAD_FILTER_LIST_MAX_COUNT)
    {
        gStFilter.stArrayLoad.u8LoadArryIndex = LOAD_FILTER_LIST_MAX_COUNT - 1;
        
    }
    else
    {
        gStFilter.stArrayLoad.u8LoadArryIndex++;
    }
    
    uint32_t u32LoadTotal = 0;
    for(int i=0;i<gStFilter.stArrayLoad.u8LoadArryIndex;i++)
    {
        u32LoadTotal = u32LoadTotal + gStFilter.stArrayLoad.arryU16LoadPower[i];
    }
    
    u16LoadFilterPower =  u32LoadTotal /  gStFilter.stArrayLoad.u8LoadArryIndex;
    return  u16LoadFilterPower;
}

/***************************************************************************
 功能:平均值滤波法计算输出功率
****************************************************************************/
uint16_t CalculateOutputAverageFilterValue(uint16_t arryU16OutputPower)
{
    uint16_t  u16OutputFilterPower = 0;
    
    memmove(&gStFilter.stArrayOut.arryU16OutPower[1],&gStFilter.stArrayOut.arryU16OutPower[0],sizeof(uint16_t)*gStFilter.stArrayOut.u8OutArryIndex);
    gStFilter.stArrayOut.arryU16OutPower[0] =  arryU16OutputPower;
    
    if(gStFilter.stArrayOut.u8OutArryIndex == OUT_FILTER_LIST_MAX_COUNT)
    {
        gStFilter.stArrayOut.u8OutArryIndex = OUT_FILTER_LIST_MAX_COUNT - 1;
        
    }
    else
    {
        gStFilter.stArrayOut.u8OutArryIndex++;
    }
    
    uint32_t u32OutputTotal = 0;
    for(int i=0;i<gStFilter.stArrayOut.u8OutArryIndex;i++)
    {
        u32OutputTotal = u32OutputTotal + gStFilter.stArrayOut.arryU16OutPower[i];
    }
    
    u16OutputFilterPower =  u32OutputTotal /  gStFilter.stArrayOut.u8OutArryIndex;
    return  u16OutputFilterPower;
}

/***************************************************************************
 功能:平均值滤波法计算输入功率
****************************************************************************/
uint16_t CalculateInputAverageFilterValue(uint16_t arryU16InputPower)
{
    uint16_t  u16InputFilterPower = 0;
    
    memmove(&gStFilter.stArrayIn.arryU16InPower[1],&gStFilter.stArrayIn.arryU16InPower[0],sizeof(uint16_t)*gStFilter.stArrayIn.u8InArryIndex);
    gStFilter.stArrayIn.arryU16InPower[0] =  arryU16InputPower;
    
    if(gStFilter.stArrayIn.u8InArryIndex == IN_FILTER_LIST_MAX_COUNT)
    {
        gStFilter.stArrayIn.u8InArryIndex = IN_FILTER_LIST_MAX_COUNT - 1;
        
    }
    else
    {
        gStFilter.stArrayIn.u8InArryIndex++;
    }
    
    uint32_t u32InputTotal = 0;
    for(int i=0;i<gStFilter.stArrayIn.u8InArryIndex;i++)
    {
        u32InputTotal = u32InputTotal + gStFilter.stArrayIn.arryU16InPower[i];
    }
    
    u16InputFilterPower =  u32InputTotal /  gStFilter.stArrayIn.u8InArryIndex;
    return  u16InputFilterPower;
}

/***************************************************************************
 功能:平均值滤波法计算充电功率
****************************************************************************/
uint16_t CalculateChargeAverageFilterValue(uint16_t arryU16ChargePower)
{
    uint16_t  u16ChargeFilterPower = 0;
    
    memmove(&gStFilter.stArrayCharge.arryU16ChargePower[1],&gStFilter.stArrayCharge.arryU16ChargePower[0],sizeof(uint16_t)*gStFilter.stArrayCharge.u8ChargeArryIndex);
    gStFilter.stArrayCharge.arryU16ChargePower[0] =  arryU16ChargePower;
    
    if(gStFilter.stArrayCharge.u8ChargeArryIndex == CHARGE_FILTER_LIST_MAX_COUNT)
    {
        gStFilter.stArrayCharge.u8ChargeArryIndex = CHARGE_FILTER_LIST_MAX_COUNT - 1;
        
    }
    else
    {
        gStFilter.stArrayCharge.u8ChargeArryIndex++;
    }
    
    uint32_t u32InputTotal = 0;
    for(int i=0;i<gStFilter.stArrayCharge.u8ChargeArryIndex;i++)
    {
        u32InputTotal = u32InputTotal + gStFilter.stArrayCharge.arryU16ChargePower[i];
    }
    
    u16ChargeFilterPower =  u32InputTotal /  gStFilter.stArrayCharge.u8ChargeArryIndex;
    return  u16ChargeFilterPower;
}

/***************************************************************************
 功能:平均值滤波法计算放电功率
****************************************************************************/
uint16_t CalculateDisChargeAverageFilterValue(uint16_t arryU16DisChargePower)
{
    uint16_t  u16DisChargeFilterPower = 0;
    
    memmove(&gStFilter.stArrayDisCharge.arryU16DisChargePower[1],&gStFilter.stArrayDisCharge.arryU16DisChargePower[0],sizeof(uint16_t)*gStFilter.stArrayDisCharge.u8DisChargeArryIndex); //需要优化
    gStFilter.stArrayDisCharge.arryU16DisChargePower[0] =  arryU16DisChargePower;
    
    if(gStFilter.stArrayDisCharge.u8DisChargeArryIndex == DISCHARGE_FILTER_LIST_MAX_COUNT)
    {
        gStFilter.stArrayDisCharge.u8DisChargeArryIndex = DISCHARGE_FILTER_LIST_MAX_COUNT - 1;
        
    }
    else
    {
        gStFilter.stArrayDisCharge.u8DisChargeArryIndex++;
    }
    
    uint32_t u32InputTotal = 0;
    for(int i=0;i<gStFilter.stArrayDisCharge.u8DisChargeArryIndex;i++)
    {
        u32InputTotal = u32InputTotal + gStFilter.stArrayDisCharge.arryU16DisChargePower[i];
    }
    
    u16DisChargeFilterPower =  u32InputTotal /  gStFilter.stArrayDisCharge.u8DisChargeArryIndex;
    return  u16DisChargeFilterPower;
}

/***************************************************************************
 功能:统计管理析构函数，用于掉电触发保护逻辑
****************************************************************************/
void StatisticsDestruction(void)
{   

}

#endif
#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
