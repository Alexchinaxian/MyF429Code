/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
文件 : NTC_DRM_Service.c 
 用途 : NTC温度和DRM采样服务函数
***********************************************************************************************************************/
#ifndef __NTC_DRM_Service_H__
#define __NTC_DRM_Service_H__

#include "HeadFile.h"
#include "NTC_Device.h"
#include "NTC_DRM_Service.h"

extern ADC_HandleTypeDef hadc1;


AD_Value_Avg_t tAD_Value_Avg;
Temperature_Real_t tTemperature_Real;
uint16_t AD_ConvertTab[AD_MAX_SAMPLE_CHANNEL][AD_SAMPLE_PERIOD_POINTS]={0};                                             //AD转换数据存放位置


void NTC_DRM_ADC_Handler(void)
{
    static uint32_t u32ChannelSumA[7] = {0};

    uint8_t i;
    uint8_t j;
    if (0 == TimeTask_GetFlag_100ms)
    {
        return;
    }

    for(j = 0; j < AD_SAMPLE_PERIOD_POINTS; j++)
    {
        for(i = 0; i < AD_MAX_SAMPLE_CHANNEL; i++)
        {
            //这里跨层调用，后面优化代码时需要处理掉
            HAL_ADC_Start(&hadc1);                                                                                      //启动AD转换
            HAL_ADC_PollForConversion(&hadc1,10);                                                                       //阻塞式轮询转换，10ms超时时间设定
            AD_ConvertTab[i][j]=HAL_ADC_GetValue(&hadc1);
            u32ChannelSumA[i] += AD_ConvertTab[i][j];
        }
    }

    tAD_Value_Avg.u16AmbientTemperatureAvgAD = u32ChannelSumA[TEMP_AMBIENT] >> 6;                                       //采样值取AD_MAX_SAMPLE_CHANNEL个点的平均值
    tAD_Value_Avg.u16INVTemperatureAvgAD = u32ChannelSumA[TEMP_INV] >> 6;
    tAD_Value_Avg.u16DCDCTemperatureAvgAD = u32ChannelSumA[TEMP_DCDC] >> 6;
    u32ChannelSumA[TEMP_AMBIENT] = 0;
    u32ChannelSumA[TEMP_DCDC] = 0;
    u32ChannelSumA[TEMP_INV] = 0;
    
    tTemperature_Real.s16AmbientTemperatureReal = CalculateAvgTemp_SDNT1608(tAD_Value_Avg.u16AmbientTemperatureAvgAD);  //查表得到实际环境温度
    tTemperature_Real.s16INVTemperatureReal = CalculateAvgTemp_HCS41A103F8(tAD_Value_Avg.u16INVTemperatureAvgAD);       //查表得到实际INV温度
    tTemperature_Real.s16DCDCTemperatureReal = CalculateAvgTemp_HCS41A103F8(tAD_Value_Avg.u16DCDCTemperatureAvgAD);     //查表得到实际DCDC温度
}



void Get_NTC_Para(Temperature_Real_t *tTemperature)
{
    memcpy(tTemperature, &tTemperature_Real, sizeof(Temperature_Real_t));
}










#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

