/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
文件 : NTC_Device.h 
 用途 : NTC热敏电阻头文件
***********************************************************************************************************************/
#include "MCU.h"
#include "HeadFile.h"





#if NTC_SDNT1608X104_DEVICE

extern int16_t CalculateAvgTemp_SDNT1608(uint16_t u16AvgTempSample);

#endif


#if NTC_HCS41A103F_C2205_DEVICE

extern int16_t CalculateAvgTemp_HCS41A103F8(uint16_t u16AvgTempSample);


#endif













/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
