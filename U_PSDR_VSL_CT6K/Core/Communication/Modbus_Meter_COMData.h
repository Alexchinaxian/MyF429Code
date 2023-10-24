/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Modbus_Meter_COMData.h 
 用途 : modbus电表协议数据头文件
***********************************************************************************************************************/
#ifndef _MODBUS_METER_COMDATA_H_
#define _MODBUS_METER_COMDATA_H_

#include "HeadFile.h"
#include "Modbus.h"
#include "LCD_Service.h"

/***********************************************************************************************************************
 功能：Meter协议地址识别表
************************************************************************************************************************/
typedef enum
{
    Meter_DATA_03H_0x000x  =  0x0000,   //电表编程参数起始地址
    Meter_DATA_03H_0x200x  =  0x2000,   //电表主要数据起始地址
    Meter_DATA_03H_0x4000  =  0x4000,   //电表有功总电能起始地址
    Meter_DATA_03H_0x400A  =  0x400A,   //电表正向有功电能起始地址
    Meter_DATA_03H_0x4014  =  0x4014,   //电表反向有功电能起始地址
}METER_DATA_DDSU_ADDRESS;

typedef enum
{
    MB_RTU_DDSU666 = 0,
    MB_RTU_Reserved,
} MBModeMeter;
extern MBModeMeter MBProtocolTypeMeter; //电表类型

/******************************************************************
 Modbus电表协议公用数据结构
*******************************************************************/

typedef struct
{
    uint16_t u16PowerClear;                         //电能清零 R/W
    uint16_t u16Addr;                               //Modbus-RTU地址 R/W
    uint16_t u16BaudRate;                           //波特率
    uint16_t u16SwitchOut;                          //开关量输出
    int32_t  s32PhaseAVolt;                         //A 相电压
    int32_t  s32PhaseACurr;                         //A 相电流
    int32_t  sInstantTotalWatt;                     //瞬时总有功功率
    int32_t  sInstantTotalVar;                      //瞬时总无功功率
    int32_t  sInstantTotalVA;                       //瞬时总视在功率
    uint32_t u32TotalPF;                            //总功功率因数
    uint32_t u32GridFreq;                           //电网频率
    uint32_t u32TotalActiveEnergy;                  //有功总电能
    uint32_t u32PositiveActiveEnergy;               //正向有功电能
    uint32_t u32ReverseActiveEnergy;                //反向有功电能

    uint16_t u16Reserved0;                          //预留
    uint16_t u16Reserved1;                          //预留
    uint16_t u16Reserved2;                          //预留
    uint16_t u16Reserved3;                          //预留
    uint16_t u16Reserved4;                          //预留
} UnifiedMeterData_t;
extern UnifiedMeterData_t tUnifiedMeterData;

/******************************************************************
 Modbus电表_DDSU协议数据结构
*******************************************************************/

typedef struct
{
    uint16_t u16ProgramCode;                        //0x0000 编程密码 R/W
    uint16_t u16FWVersion;                          //0x0001 软件版本 R
    uint16_t u16PowerClear;                         //0x0002 电能清零 R/W
    uint16_t u16Reserved1;                          //0x0003 预留
    uint16_t u16Reserved2;                          //0x0004 预留
    uint16_t u16ChangeProtocol;                     //0x0005 协议切换设置 R/W
    uint16_t u16Addr;                               //0x0006 Modbus-RTU地址 R/W
    uint16_t u16Reserved3;                          //0x0007 预留
    uint16_t u16Reserved4;                          //0x0008 预留
    uint16_t u16Reserved5;                          //0x0009 预留
    uint16_t u16Reserved6;                          //0x000A 预留
    uint16_t u16Reserved7;                          //0x000B 预留
    uint16_t u16BaudRate;                           //0x000C 波特率 R/W
    uint16_t u16SwitchOut;                          //0x000D 开关量输出 R/W
    uint16_t u16Reserved8;                          //0x000E 预留
    uint16_t u16Reserved9;                          //0x000F 预留
    uint16_t u16Reserved10;                         //0x0010 预留

    int16_t  s16PhaseAVoltHi;                       //0x2000~0x2001 A 相电压 R
    int16_t  s16PhaseAVoltLo;                       //0x2000~0x2001 A 相电压 R
    int16_t  s16PhaseACurrHi;                       //0x2002~0x2003 A 相电流 R
    int16_t  s16PhaseACurrLo;                       //0x2002~0x2003 A 相电流 R
    uint16_t u16InstantTotalWattHi;                 //0x2004~0x2005 瞬时总有功功率 R
    uint16_t u16InstantTotalWattLo;                 //0x2004~0x2005 瞬时总有功功率 R
    uint16_t u16InstantTotalVarHi;                  //0x2006~0x2007 瞬时总无功功率 R
    uint16_t u16InstantTotalVarLo;                  //0x2006~0x2007 瞬时总无功功率 R
    uint16_t u16InstantTotalVAHi;                   //0x2008~0x2009 瞬时总视在功率 R
    uint16_t u16InstantTotalVALo;                   //0x2008~0x2009 瞬时总视在功率 R
    uint16_t u16TotalPFHi;                          //0x200A~0x200B 总功功率因数 R
    uint16_t u16TotalPFLo;                          //0x200A~0x200B 总功功率因数 R
    uint16_t u16Reserved11Hi;                       //0x200C~0x200D 预留
    uint16_t u16Reserved11Lo;                       //0x200C~0x200D 预留
    uint16_t u16GridFreqHi;                         //0x200E~0x200F 电网频率 R
    uint16_t u16GridFreqLo;                         //0x200E~0x200F 电网频率 R
    uint16_t u16Reserved12Hi;                       //0x2010~0x2011 预留
    uint16_t u16Reserved12Lo;                       //0x2010~0x2011 预留
    
    uint16_t u16TotalActiveEnergyHi;                //0x4000~0x4001 有功总电能 R
    uint16_t u16TotalActiveEnergyLo;                //0x4000~0x4001 有功总电能 R

    uint16_t u16PositiveActiveEnergyHi;             //0x400A~0x400B 正向有功电能 R
    uint16_t u16PositiveActiveEnergyLo;             //0x400A~0x400B 正向有功电能 R

    uint16_t u16ReverseActiveEnergyHi;              //0x4014~0x4015 反向有功电能 R
    uint16_t u16ReverseActiveEnergyLo;              //0x4014~0x4015 反向有功电能 R
} DDSUMeterData_t;
extern DDSUMeterData_t tDDSUMeterData;

extern uint16_t* GetMeterComDataIndex_03H(MBRTUFrame_t* ptMBFrame);                  //定位起始地址对应的Meter协议功能码03H的数据结构地址

extern void      sMeterDataUnified(MBModeMeter ProtocolType);                        //电表数据的统一换算
extern void GetDisplayRealTimeGridData(Display_DATA_Grid* ptDisplayGridData);



#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

