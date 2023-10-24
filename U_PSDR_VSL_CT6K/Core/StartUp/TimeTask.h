/***********************************************************************************************************************
* Copyright (c) , CVTE
* All rights reserved.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
* 文件	: TimeTask.h
* 用途 	: 时间处理定义
***********************************************************************************************************************/
#ifndef __TIMETASK_H_
#define __TIMETASK_H_

#include "HeadFile.h"


#if MODULE_TIMETASK

/***********************************************************************************************************************
*  Macro definitions
***********************************************************************************************************************/
#define TimeTask_GetFlag_10ms   (tTimeTask.tTimeFlag.Bits.b10msFlag)    //10ms时基标志
#define TimeTask_GetFlag_20ms   (tTimeTask.tTimeFlag.Bits.b20msFlag)    //20ms时基标志
#define TimeTask_GetFlag_100ms  (tTimeTask.tTimeFlag.Bits.b100msFlag)   //100ms时基标志
#define TimeTask_GetFlag_500ms  (tTimeTask.tTimeFlag.Bits.b500msFlag)   //500ms时基标志
#define TimeTask_GetFlag_1s     (tTimeTask.tTimeFlag.Bits.b1sFlag)      //1s时基标志
#define TimeTask_GetFlag_1min   (tTimeTask.tTimeFlag.Bits.b1minFlag)    //1min时基标志


/***********************************************************************************************************************
*  Typedef definitions
***********************************************************************************************************************/
typedef union
{
    uint8_t u8Bytes;
    struct
    {
        uint8_t b1msFlag    : 1;	//BIT0 1ms时基标志
        uint8_t b5msFlag   	: 1;    //BIT1 5ms时基标志
        uint8_t b10msFlag   : 1;    //BIT2 10ms时基标志
        uint8_t b20msFlag   : 1;    //BIT3 20ms时基标志
        uint8_t b100msFlag  : 1;    //BIT4 100ms时基标志
        uint8_t b500msFlag  : 1;    //BIT5 500ms时基标志
        uint8_t b1sFlag     : 1;    //BIT6 1s时基标志
        uint8_t b1minFlag   : 1;    //BIT7 1min时基标志
    } Bits;
} TimeTaskFlag_t;

typedef struct
{
    uint8_t  u8Cnt200us;			//200us时基计时
    uint8_t	 u8Cnt1ms;              //1ms时基计时
    uint8_t  u8Cnt5ms;              //5ms时基计时
    uint8_t  u8Cnt10ms;             //10ms时基计时
    uint8_t  u8Cnt20ms;             //20ms时基计时
    uint8_t	 u8Cnt100ms;            //100ms时基计时
    uint8_t	 u8Cnt500ms;            //500ms时基计时
    uint8_t	 u8Cnt1s;               //1s时基计时
    uint16_t u8Cnt1min;             //1min时基计时
    TimeTaskFlag_t tTimeFlag;       //时基标志
    uint16_t u16TimeOutCnt;         //超时模块计数器计数值
} TimeTaskVar_t;


/***********************************************************************************************************************
*   Extern variables
***********************************************************************************************************************/
extern volatile TimeTaskVar_t tTimeTask;
extern volatile uint32_t  u32SysTimestamp;

/***********************************************************************************************************************
*   Extern functions
***********************************************************************************************************************/
extern void TimeTask_InitVar(void);
extern void Hardware_SetCLK(void);
extern void Hardware_DectectCLK(void);
extern void Time_Handler(void);
extern void BASE_TIMER_HANDLER(void);

#endif
#endif		/***Module End***/
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
