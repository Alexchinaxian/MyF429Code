/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
文件 : NTC_Device.c 
 用途 : NTC热敏电阻采样
***********************************************************************************************************************/
#include "NTC_Device.h"


#if NTC_SDNT1608X104_DEVICE
static const uint16_t u16NTCTempSampleTab_SDNT1608[151] =          //-30℃~120℃
{
    4090,    4090,    4089,    4089,    4088,    4088,    4088,    4087,    4087,    4086, \
    4085,    4085,    4084,    4084,    4083,    4082,    4081,    4080,    4080,    4079, \
    4078,    4077,    4076,    4075,    4073,    4072,    4071,    4070,    4068,    4067, \
    4065,    4064,    4062,    4060,    4058,    4056,    4054,    4052,    4050,    4048, \
    4045,    4043,    4040,    4038,    4035,    4032,    4029,    4026,    4023,    4019, \
    4016,    4012,    4008,    4005,    4000,    3996,    3992,    3987,    3983,    3978, \
    3973,    3968,    3962,    3957,    3951,    3945,    3939,    3933,    3926,    3920, \
    3913,    3906,    3898,    3891,    3883,    3875,    3867,    3858,    3849,    3841, \
    3831,    3822,    3812,    3802,    3792,    3782,    3771,    3760,    3749,    3737, \
    3725,    3713,    3701,    3688,    3675,    3662,    3649,    3635,    3621,    3607, \
    3592,    3577,    3562,    3547,    3531,    3515,    3499,    3482,    3465,    3448, \
    3431,    3413,    3395,    3377,    3359,    3340,    3321,    3302,    3283,    3263, \
    3243,    3223,    3203,    3182,    3161,    3140,    3119,    3098,    3076,    3054, \
    3032,    3010,    2988,    2965,    2943,    2920,    2897,    2874,    2851,    2828, \
    2805,    2781,    2758,    2734,    2711,    2687,    2663,    2639,    2616,    2592, \
    2568
};

int16_t CalculateAvgTemp_SDNT1608(uint16_t u16AvgTempSample)
{
    uint8_t bLowIndex,bHighIndex,bMidIndex;
    int16_t bTemperature;

    bLowIndex = 0;                                                                                                      //最低温度采样范围
    bHighIndex = 150;                                                                                                   //最高温度采样范围
    u16AvgTempSample = (int16_t)(((int32_t)u16AvgTempSample * 4096) >> 12);                                             //
    if(u16AvgTempSample >= u16NTCTempSampleTab_SDNT1608[bLowIndex])                                                     //下限限制
    {
        bTemperature = -300;
    }
    else if(u16AvgTempSample <= u16NTCTempSampleTab_SDNT1608[bHighIndex])                                               //上限限制
    {
        bTemperature = 1200;
    }
    else                                                                                                                //二分法查找
    {
        while((bLowIndex + 1) < bHighIndex)
        {
            bMidIndex = (bLowIndex + bHighIndex) >> 1;
            if(u16AvgTempSample == u16NTCTempSampleTab_SDNT1608[bMidIndex])
            {
                bTemperature = (bMidIndex + 1 - 30) * 10;
                bTemperature = (int16_t)(((int32_t)bTemperature * 530 - 23290) >> 9);                                   //环境温度校正
                bTemperature = bTemperature + 0;                                                                        //校正参数，b，后续根据调试情况配置
                return  bTemperature;
            }
            if(u16AvgTempSample > u16NTCTempSampleTab_SDNT1608[bMidIndex])
            {
                bHighIndex = bMidIndex;
            }
            else
            {
                bLowIndex = bMidIndex;
            }
        }
        bTemperature = (bLowIndex + 1 - 30) * 10;
    }

    bTemperature = (int16_t)(((int32_t)bTemperature * 530 - 23290) >> 9);                                               //环境温度校正

    return  bTemperature;
}

#endif


#if NTC_HCS41A103F_C2205_DEVICE

static const uint16_t u16NTCTempSampleTab_HCS41A103F8[151] =          //-30℃~120℃
{
    4051,    4047,    4044,    4041,    4037,    4033,    4029,    4024,    4020,    4015, \
    4009,    4004,    3998,    3992,    3985,    3979,    3972,    3964,    3956,    3948, \
    3939,    3930,    3921,    3911,    3901,    3890,    3878,    3867,    3854,    3841, \
    3828,    3814,    3800,    3785,    3769,    3753,    3736,    3718,    3700,    3682, \
    3662,    3642,    3622,    3601,    3579,    3556,    3533,    3509,    3485,    3460, \
    3434,    3408,    3381,    3353,    3325,    3296,    3266,    3236,    3206,    3175, \
    3143,    3111,    3079,    3046,    3012,    2978,    2944,    2910,    2875,    2839, \
    2804,    2768,    2732,    2696,    2660,    2623,    2587,    2550,    2513,    2477, \
    2440,    2404,    2367,    2331,    2294,    2258,    2222,    2186,    2151,    2115, \
    2080,    2046,    2011,    1977,    1943,    1910,    1877,    1844,    1812,    1780, \
    1749,    1718,    1687,    1657,    1628,    1599,    1570,    1542,    1514,    1487, \
    1461,    1434,    1409,    1383,    1359,    1334,    1311,    1287,    1265,    1242, \
    1220,    1199,    1178,    1158,    1138,    1118,    1099,    1080,    1062,    1044, \
    1027,    1010,    993,     977,     961,     946,     930,     916,     901,     887,  \
    874,     860,     847,     835,     822,     810,     798,     787,     776,     765,  \
    754
};

int16_t CalculateAvgTemp_HCS41A103F8(uint16_t u16AvgTempSample)
{
    uint8_t bLowIndex,bHighIndex,bMidIndex;
    int16_t bTemperature;

    bLowIndex = 0;                                                                                                      //最低温度采样范围
    bHighIndex = 150;                                                                                                   //最高温度采样范围
    u16AvgTempSample = (int16_t)(((int32_t)u16AvgTempSample * 4096) >> 12);                                             //校正参数，k，后续根据调试情况配置
    if(u16AvgTempSample >= u16NTCTempSampleTab_HCS41A103F8[bLowIndex])                                                  //下限限制
    {
        bTemperature = -300;
    }
    else if(u16AvgTempSample <= u16NTCTempSampleTab_HCS41A103F8[bHighIndex])                                            //上限限制
    {
        bTemperature = 1200;
    }
    else                                                                                                                //二分法查找
    {
        while((bLowIndex + 1) < bHighIndex)
        {
            bMidIndex = (bLowIndex + bHighIndex) >> 1;
            if(u16AvgTempSample == u16NTCTempSampleTab_HCS41A103F8[bMidIndex])
            {
                bTemperature = (bMidIndex + 1 - 30) * 10;
                bTemperature = (int16_t)(((int32_t)bTemperature * 500 - 5660) >> 9);                                    //DCDC、INV温度 校正参数
                return  bTemperature;
            }
            if(u16AvgTempSample > u16NTCTempSampleTab_HCS41A103F8[bMidIndex])
            {
                bHighIndex = bMidIndex;
            }
            else
            {
                bLowIndex = bMidIndex;
            }
        }
        bTemperature = (bLowIndex + 1 - 30) * 10;
    }

    bTemperature = (int16_t)(((int32_t)bTemperature * 500 - 5660) >> 9);                                                //DCDC、INV温度

    return  bTemperature;
}

#endif






/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
