/***********************************************************************************************************************
* Copyright (c) , CVTE
* All rights reserved.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
* 文件    : PublicFunc.c
* 用途     : 公共模块定义
***********************************************************************************************************************/
#ifndef __PUBLICFUNC_H_
#define __PUBLICFUNC_H_

#include "TypeDef.h"
//#include "HeadFile.h"


#if MODULE_PUBLICFUNC

#define MULTIPLE_10        10


/***********************************************************************************************************************
* Extern functions
***********************************************************************************************************************/
extern uint8_t PublicFunc_CompareAndGetState(uint8_t sts, uint8_t tmp, const uint8_t *dt, uint8_t u8Len);
extern bool_t PublicFunc_SysParaCheckSum(uint8_t *PSysparaBuf);
extern uint16_t PublicFunc_ComputeCRC16(uint8_t *p, uint8_t u8Len);
extern int16_t PublicFunc_DomainDivision(int16_t i16Field, int16_t i16CurrTemp, int16_t *pi16DemarcationData, int16_t i16DemarcationDataSize, uint8_t u8ReturnDiff);

extern uint8_t SubU8LimitCheck(uint8_t u8Ttarget, uint8_t u8TMin, uint8_t u8TMax);
extern int8_t SubS8LimitCheck(int8_t s8Ttarget, int8_t s8TMin, int8_t s8TMax);
extern uint16_t SubU16LimitCheck(uint16_t u16Ttarget, uint16_t u16TMin, uint16_t u16TMax);
extern int16_t SubS16LimitCheck(int16_t s16Ttarget, int16_t s16TMin, int16_t s16TMax);
extern void SubAddU8Cnt(uint8_t *pu8WkTime);
extern void SubAddU16Cnt(uint16_t *pu16WkTime);
extern void SubDecU8Cnt(uint8_t *pu8WkTime);
extern void SubDecU16Cnt(uint16_t *pu16WkTime);
extern int8_t Func_ValueRounding(int16_t s16Value);

//extern void Delay_us(uint32_t u32DelayTime);
extern void PublicFunc_Delay_ms(uint32_t u32DelayTime);
extern int16_t PublicFunc_U8DataMultipleToS16Data(uint8_t u8TmpData);
#endif
#endif         /***Module End***/
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
