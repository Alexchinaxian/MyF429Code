/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Statistics_Management_Service.h 
 用途 : 统计管理头文件
***********************************************************************************************************************/
#ifndef _STATISTICS_MANAGEMENT_H_
#define _STATISTICS_MANAGEMENT_H_

#include "HeadFile.h"
#include "LCD_Service.h"

#define COMM_QUERY_TIME_PERIOD           (2)              //数据通信查询周期单位s
#define COMM_CALCULATE_TIME_PERIOD       (300)            //计算周期300 / 60 = 5 min
#define PV_FILTER_LIST_MAX_COUNT         (150)            //光伏滤波list最大条数
#define LOAD_FILTER_LIST_MAX_COUNT       (150)            //负载滤波list最大条数
#define OUT_FILTER_LIST_MAX_COUNT        (150)            //输出滤波list最大条数
#define IN_FILTER_LIST_MAX_COUNT         (150)            //输入滤波list最大条数
#define CHARGE_FILTER_LIST_MAX_COUNT     (150)            //充电滤波list最大条数
#define DISCHARGE_FILTER_LIST_MAX_COUNT  (150)            //放电滤波list最大条数

typedef enum
{
    STATISTICS_INIT,          //统计管理模块初始化
    STATISTICS_RUNNING,       //统计管理模块运行
    STATISTICS_DESTRCUCTION,  //统计管理模块析构
    STATISTICS_STATE_NULL 
}StatisticsStatus_TypeDef;

//TPFV类型
typedef enum
{
    FILTER_AVERAGE,      //算术平均滤波法
    FILTER_MIDDLEVALUE,  //中位值滤波法
    FILTER_AMPLITUDE,    //限幅滤波法
    FILTER_NULL          //
}FilterAlgorithm_TypeDef;

typedef struct
{
    uint8_t  u8PVArryIndex;
    uint16_t arryU16PVPower[PV_FILTER_LIST_MAX_COUNT];
}PV_FilterList;

typedef struct
{
    uint8_t  u8LoadArryIndex;
    uint16_t arryU16LoadPower[LOAD_FILTER_LIST_MAX_COUNT];
}Load_FilterList;

typedef struct
{
    uint8_t  u8OutArryIndex;
    uint16_t arryU16OutPower[OUT_FILTER_LIST_MAX_COUNT];
}Out_FilterList;

typedef struct
{
    uint8_t  u8InArryIndex;
    uint16_t arryU16InPower[IN_FILTER_LIST_MAX_COUNT];
}In_FilterList;

typedef struct
{
    uint8_t  u8ChargeArryIndex;
    uint16_t arryU16ChargePower[DISCHARGE_FILTER_LIST_MAX_COUNT];
}Charge_FilterList;

typedef struct
{
    uint8_t  u8DisChargeArryIndex;
    uint16_t arryU16DisChargePower[DISCHARGE_FILTER_LIST_MAX_COUNT];
}DisCharge_FilterList;

typedef struct
{
    PV_FilterList        stArrayPV;
    Load_FilterList      stArrayLoad;
    Out_FilterList       stArrayOut;
    In_FilterList        stArrayIn;
    Charge_FilterList    stArrayCharge;
    DisCharge_FilterList stArrayDisCharge;
}PowerFilterList;

//统计数据滤波累加和结构体结构体
typedef struct {
    uint32_t stPVPowerSum;              //光伏发电量
    uint32_t stLoadPowerSum;            //负载用电量
    uint32_t stOutputPowerSum;          //输出发电量
    uint32_t stInputPowerSum;           //输入发电量
    uint32_t stChagePowerSum;           //充电发电量
    uint32_t stDisChagePowerSum;        //放电发电量
}STATISTICAL_DATA_SumPara;

//Statistics管理总初始化函数
void StatisticsInit(void);
//Statistics管理总运行函数
void StatisticsRunning(void);
//Statistics管理析构函数
void StatisticsDestruction(void);

//光伏求平均值滤波算法
uint16_t CalculatePVAverageFilterValue(uint16_t arryU16PVPower);
//负载求平均值滤波算法
uint16_t CalculateLoadAverageFilterValue(uint16_t arryU16LoadPower);
//输出求平均值滤波算法
uint16_t CalculateOutputAverageFilterValue(uint16_t arryU16OutputPower);
//输入求平均值滤波算法
uint16_t CalculateInputAverageFilterValue(uint16_t arryU16InputPower);
//充电求平均值滤波算法
uint16_t CalculateChargeAverageFilterValue(uint16_t arryU16ChargePower);
//放电求平均值滤波算法
uint16_t CalculateDisChargeAverageFilterValue(uint16_t arryU16DisChargePower);

//数据清零
void ClearZeroWithKeyNodes(Display_DATA_STATISTICAL *pSTATISTICAL);

//统计管理处理总入口函数,给main模块存储模块总接口函数
extern void StatisticsManagement_Handler(void);
//初始化变量函数
extern void Statistics_Service_InitVar(void);
//初始化变量函数
extern void Statistics_Service_HwInit(void);

#endif

/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
