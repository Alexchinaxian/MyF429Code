/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Modbus_Meter_COMData.c
 用途 : ModbusMeter协议相关函数
***********************************************************************************************************************/
#ifndef MODBUS_METER_COMDATA_C_
#define MODBUS_METER_COMDATA_C_

#include "Modbus_Meter_COMData.h"
#include "Modbus_RTU_Master.h"


#define PROTO_NULL           (0x7FFF) //无效位填充

UnifiedMeterData_t tUnifiedMeterData; //电表协议公用数据结构
DDSUMeterData_t tDDSUMeterData;       //电表协议DDSU数据结构

/***********************************************************************************************************************
 功能：电表数据的统一换算
************************************************************************************************************************/
void sMeterDataUnified(MBModeMeter ProtocolType)
{
    switch ( ProtocolType )
    {
        case MB_RTU_DDSU666 :
            tUnifiedMeterData.s32PhaseACurr = Hex2Float_IEEE745((((uint32_t)(tDDSUMeterData.s16PhaseACurrHi)) << 16) + (uint32_t)tDDSUMeterData.s16PhaseACurrLo);
            tUnifiedMeterData.s32PhaseAVolt = Hex2Float_IEEE745((((uint32_t)(tDDSUMeterData.s16PhaseAVoltHi)) << 16) + (uint32_t)tDDSUMeterData.s16PhaseAVoltLo);
            tUnifiedMeterData.u16SwitchOut = tDDSUMeterData.u16SwitchOut;
            tUnifiedMeterData.u32GridFreq = Hex2Float_IEEE745((((uint32_t)(tDDSUMeterData.u16GridFreqHi)) << 16)  + (uint32_t)tDDSUMeterData.u16GridFreqLo);
            tUnifiedMeterData.sInstantTotalVA = Hex2Float_IEEE745((((uint32_t)(tDDSUMeterData.u16InstantTotalVAHi)) << 16)  + (uint32_t)tDDSUMeterData.u16InstantTotalVALo);
            tUnifiedMeterData.sInstantTotalVar = Hex2Float_IEEE745((((uint32_t)(tDDSUMeterData.u16InstantTotalVarHi)) << 16)  + (uint32_t)tDDSUMeterData.u16InstantTotalVarLo);
            tUnifiedMeterData.sInstantTotalWatt = Hex2Float_IEEE745((((uint32_t)(tDDSUMeterData.u16InstantTotalWattHi)) << 16)  + (uint32_t)tDDSUMeterData.u16InstantTotalWattLo);
            tUnifiedMeterData.u32PositiveActiveEnergy = Hex2Float_IEEE745((((uint32_t)(tDDSUMeterData.u16PositiveActiveEnergyHi)) << 16)  + (uint32_t)tDDSUMeterData.u16PositiveActiveEnergyLo);
            tUnifiedMeterData.u32ReverseActiveEnergy = Hex2Float_IEEE745((((uint32_t)(tDDSUMeterData.u16ReverseActiveEnergyHi)) << 16)  + (uint32_t)tDDSUMeterData.u16ReverseActiveEnergyLo);
            tUnifiedMeterData.u32TotalActiveEnergy = Hex2Float_IEEE745((((uint32_t)(tDDSUMeterData.u16TotalActiveEnergyHi)) << 16)  + (uint32_t)tDDSUMeterData.u16TotalActiveEnergyLo);
            tUnifiedMeterData.u32TotalPF = Hex2Float_IEEE745((((uint32_t)(tDDSUMeterData.u16TotalPFHi)) << 16)  + (uint32_t)tDDSUMeterData.u16TotalPFLo);
            tUnifiedMeterData.u16Reserved0 = PROTO_NULL;
            tUnifiedMeterData.u16Reserved1 = PROTO_NULL;
            tUnifiedMeterData.u16Reserved2 = PROTO_NULL;
            tUnifiedMeterData.u16Reserved3 = PROTO_NULL;
            tUnifiedMeterData.u16Reserved4 = PROTO_NULL;
            break;
        default:
            ;
    }
}

/***********************************************************************************************************************
 功能：定位起始地址对应的Meter协议功能码03H的数据结构地址 
************************************************************************************************************************/
uint16_t* GetMeterComDataIndex_03H(MBRTUFrame_t* ptMBFrame)
{
    uint16_t *pu8ObjBuf = NULL;

    if (Meter_DATA_03H_0x000x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFF00))
    {
        pu8ObjBuf = (uint16_t*)& tDDSUMeterData.u16ProgramCode;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - 0x0000);
    }
    else if (Meter_DATA_03H_0x200x == ((ptMBFrame->u16MBStartRegsAddr) & 0xFF00))
    {
        pu8ObjBuf = (uint16_t*)& tDDSUMeterData.s16PhaseAVoltHi;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - 0x2000);
    }
    else if (Meter_DATA_03H_0x4000 == (ptMBFrame->u16MBStartRegsAddr))
    {
        pu8ObjBuf = (uint16_t*)& tDDSUMeterData.u16TotalActiveEnergyHi;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - 0x4000);
    }
    else if (Meter_DATA_03H_0x400A == (ptMBFrame->u16MBStartRegsAddr))
    {
        pu8ObjBuf = (uint16_t*)& tDDSUMeterData.u16PositiveActiveEnergyHi;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - 0x400A);
    }
    else if (Meter_DATA_03H_0x4014 == (ptMBFrame->u16MBStartRegsAddr))
    {
        pu8ObjBuf = (uint16_t*)& tDDSUMeterData.u16ReverseActiveEnergyHi;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - 0x4014);
    }
    else
    {
        ;
    }

    return pu8ObjBuf;
}

/***************************************************************************
 功能:Meter协议数据绑定(电网数据)对外接口
****************************************************************************/
void GetDisplayRealTimeGridData(Display_DATA_Grid* ptDisplayGridData)
{
    ptDisplayGridData->u16GridVoltage = (uint16_t) (tUnifiedMeterData.s32PhaseAVolt / 100);       //电表：A相电压
    ptDisplayGridData->sGridcurrent = (int16_t) (tUnifiedMeterData.s32PhaseACurr / 100);          //电表：A相电流
    ptDisplayGridData->u16GridFrequency = (uint16_t) (tUnifiedMeterData.u32GridFreq / 10);        //电表：电网频率
    ptDisplayGridData->sGridActivePower = (int32_t) (tUnifiedMeterData.sInstantTotalWatt);        //电表：瞬时总有功功率
    ptDisplayGridData->sGridReactivePower = (int32_t) (tUnifiedMeterData.sInstantTotalVar);       //电表：瞬时总无功功率
}

#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

