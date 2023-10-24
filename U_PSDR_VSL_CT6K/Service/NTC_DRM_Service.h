/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
文件 : NTC_DRM_Service.h 
 用途 : NTC和DRM采样头文件
***********************************************************************************************************************/
#ifndef __NTC_DRM_SERVICE_H__
#define __NTC_DRM_SERVICE_H__

#define AD_SAMPLE_PERIOD_POINTS                                 (64)

typedef enum
{
    TEMP_AMBIENT = 0,                                                                                                   //贴片NTC
    TEMP_DCDC,                                                                                                          //DCDC NTC
    TEMP_INV,                                                                                                           //INV NTC
    AD_MAX_SAMPLE_CHANNEL,
}AD_Sample_Channel_t;


typedef struct
{
    uint16_t u16AmbientTemperatureAvgAD;
    uint16_t u16INVTemperatureAvgAD;
    uint16_t u16DCDCTemperatureAvgAD;
}AD_Value_Avg_t;

typedef struct
{
    int16_t s16AmbientTemperatureReal;
    int16_t s16INVTemperatureReal;
    int16_t s16DCDCTemperatureReal;
}Temperature_Real_t;




extern AD_Value_Avg_t tAD_Value_Avg;
extern Temperature_Real_t tTemperature_Real;



extern void NTC_DRM_ADC_Handler(void);
extern void Get_NTC_Para(Temperature_Real_t *tTemperature);




#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
