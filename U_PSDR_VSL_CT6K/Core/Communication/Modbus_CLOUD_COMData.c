/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Modbus_CLOUD_COMData.c
 用途 : ModbusCLOUD协议相关函数
***********************************************************************************************************************/
#ifndef MODBUS_CLOUD_COMDATA_C_
#define MODBUS_CLOUD_COMDATA_C_

#include <stdlib.h>
#include <stdio.h>
#include "Modbus_CLOUD_COMData.h"
#include "RTC_Service.h"
#include "Modbus_PCS_COMData.h"
#include "Modbus_BMS_COMData.h"
#include "LCD_Service.h"
#include "Storage_Management_Service.h"

#pragma pack(1)
InternalCloud_t tInternalCloudData;                //对接云平台内部通讯的数据结构


/***********************************************************************************************************************
 功能：获取系统数据的数据接口
************************************************************************************************************************/
void GetTotalSysParamToCloudData(void)
{

    memset(&tInternalCloudData.Register03H_t.tEMSTotalParam,0,sizeof(tInternalCloudData.Register03H_t.tEMSTotalParam));
//设备类型
    uint16_t DeviceType = 5;
    tInternalCloudData.Register03H_t.tEMSTotalParam.u16DeviceType = DeviceType;

//机器串号
    uint16_t SerialNumber[8]={0};
    uint8_t i= 0;
    uint8_t SerialArray[16]={'A','E','B','2','6','6','6','6','0','0','0','0','1','1','1','1'};

    for (i = 0; i < 8; i++)
    {
        SerialNumber[i] = (SerialArray[2*i] << 8)+ SerialArray[2*i + 1];
    }
    memcpy(tInternalCloudData.Register03H_t.tEMSTotalParam.u16MachincePort,SerialNumber,sizeof(SerialNumber));

    
    //机器型号
    uint16_t MachinceType[10]={0};
    i= 0;
    uint8_t MachinceArray[20]={0,'1',2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9};

    for (i = 0; i < 10; i++)
    {
        MachinceType[i] = (MachinceArray[2*i] << 8)+ MachinceArray[2*i + 1];
    }
    memcpy(tInternalCloudData.Register03H_t.tEMSTotalParam.u16MachinceType,MachinceType,sizeof(MachinceType));

    //厂家信息
    uint16_t ManufactNumber[15]={0};
    i= 0;
    uint8_t ManufactArray[30]={0,1,'2',3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4};

    for (i = 0; i < 15; i++)
    {
        ManufactNumber[i] = (ManufactArray[2*i] << 8)+ ManufactArray[2*i + 1];
    }
    memcpy(tInternalCloudData.Register03H_t.tEMSTotalParam.u16ManufactInfo,ManufactNumber,sizeof(ManufactNumber));
    //获取系统语言
    uint16_t LanguageType = getSystemLanguageItem();
    tInternalCloudData.Register03H_t.tEMSTotalParam.u16LanguageType = LanguageType;

    
    //设备状态,预留
    //工作模式,预留
    //PV工作模式,预留
    //PV追踪模式,预留
    //并机状态,预留
    //电池工作状态,预留
    //电网工作状态,预留
    //发电机工作状态,预留
    tInternalCloudData.Register03H_t.tEMSTotalParam.u16DeviceStatus = 8;                               //0x0023 设备状态
    tInternalCloudData.Register03H_t.tEMSTotalParam.u16WorkMode = 9;                                   //0x0024 工作模式
    tInternalCloudData.Register03H_t.tEMSTotalParam.u16PVWorkMode = 10;                               //0x0025 PV工作模式
    tInternalCloudData.Register03H_t.tEMSTotalParam.u16PVTrackMode = 11;                                //0x0026 PV追踪模式
    tInternalCloudData.Register03H_t.tEMSTotalParam.u16ParallelStatus = 12;                             //0x002C 并机状态
    tInternalCloudData.Register03H_t.tEMSTotalParam.u16BatWorkStatus = 13;                              //0x0029 电池工作状态
    tInternalCloudData.Register03H_t.tEMSTotalParam.u16GirdWorkStatus = 14;                             //0x002A 电网工作状态
    tInternalCloudData.Register03H_t.tEMSTotalParam.u16GenWorkStatus = 15;                              //0x002B 发电机工作状态

    //PV1工作状态
    PVInformation_t tPV1Information;
    memset(&tPV1Information,0,sizeof(tPV1Information));
    GetPV1Information(&tPV1Information);
    tInternalCloudData.Register03H_t.tEMSTotalParam.u16PV1WorkStatus = tPV1Information.u16PVState;
    //PV2工作状态
    PVInformation_t tPV2Information;
    memset(&tPV2Information,0,sizeof(tPV2Information));
    GetPV2Information(&tPV2Information);
    tInternalCloudData.Register03H_t.tEMSTotalParam.u16PV2WorkStatus = tPV2Information.u16PVState;

    //DSP版本号(ASCII)
    Display_DSP_MCU_Version stVersion;
    memset(&stVersion,0,sizeof(Display_DSP_MCU_Version));
    GetDisplaySoftwareVersion(&stVersion);
    stVersion.u16MainDspVerV = 1;
    stVersion.u16MainDspVerB = 2;
    stVersion.u16MainDspVerD = 3;
    char tab_Dsp_Ver[12];
    sprintf(tab_Dsp_Ver,"V%03d.%03d.%03d",stVersion.u16MainDspVerV,stVersion.u16MainDspVerB,stVersion.u16MainDspVerD);
    uint16_t SerialNumber1[6]={0};
    for (i = 0; i < 6; i++)
    {
        SerialNumber1[i] = (tab_Dsp_Ver[2*i] << 8)+ tab_Dsp_Ver[2*i + 1];
    }
    memcpy(tInternalCloudData.Register03H_t.tEMSTotalParam.u16DspVersion,SerialNumber1,sizeof(SerialNumber1));
    //EMS版本号(ASCII)
    char tab_Ems_Ver[12];
    sprintf(tab_Ems_Ver,"V%03d.%03d.%03d",VER_V,VER_B,VER_D);
    uint16_t SerialNumber2[6]={0};
    for (i = 0; i < 6; i++)
    {
        SerialNumber2[i] = (tab_Ems_Ver[2*i] << 8)+ tab_Ems_Ver[2*i + 1];
    }
    memcpy(tInternalCloudData.Register03H_t.tEMSTotalParam.u16EmsVersion,SerialNumber2,sizeof(SerialNumber2));
    //BackUp版本号(ASCII)
    char tab_Bak_Ver[12];
    stVersion.u16BackMcuVerV = 3;
    stVersion.u16BackMcuVerB = 2;
    stVersion.u16BackMcuVerD = 1;
    sprintf(tab_Bak_Ver,"V%03d.%03d.%03d",stVersion.u16BackMcuVerV,stVersion.u16BackMcuVerB,stVersion.u16BackMcuVerD);
    uint16_t SerialNumber3[6]={0};
    for (i = 0; i < 6; i++)
    {
        SerialNumber3[i] = (tab_Bak_Ver[2*i] << 8)+ tab_Bak_Ver[2*i + 1];
    }
    memcpy(tInternalCloudData.Register03H_t.tEMSTotalParam.u16BackupVersion,SerialNumber3,sizeof(SerialNumber3));
    
    TotalParam_t tTotalParam;
    GetTotalParamInfo(&tTotalParam);
    memset(&tTotalParam ,0, sizeof(tTotalParam));
    //硬件版本号,预留
    //tInternalCloudData.Register03H_t.tEMSTotalParam.u16BHWVersion = tTotalParam.u16BHWVersion;                                      //0x003F 硬件版本号
    memcpy(tInternalCloudData.Register03H_t.tEMSTotalParam.u16BHWVersion,SerialNumber3,sizeof(SerialNumber3)); 
    tInternalCloudData.Register03H_t.tEMSTotalParam.s16InvRadiatorTemp = tTotalParam.s16InvRadiatorTemp;                            //0x0049 INV散热器温度值
    tInternalCloudData.Register03H_t.tEMSTotalParam.s16EnvironmentTemp = tTotalParam.s16EnvironmentTemp;                            //0x004A 环境温度
    tInternalCloudData.Register03H_t.tEMSTotalParam.s16DCDCRadiatorTemp = tTotalParam.s16DCDCRadiatorTemp;                          //0x004B DC-DC散热器温度


    memcpy(&tInternalCloudData.Register03H_t.tEMSTotalParam.SysFault_t.SysFault1_t,&(tTotalParam.SysFault_t.SysFault1_t),sizeof(tTotalParam.SysFault_t.SysFault1_t));
    memcpy(&tInternalCloudData.Register03H_t.tEMSTotalParam.SysFault_t.SysFault2_t,&(tTotalParam.SysFault_t.SysFault2_t),sizeof(tTotalParam.SysFault_t.SysFault2_t));
   
   //系统故障3
   //系统故障4 
   //此接口先预留
   //tInternalCloudData.Register03H_t.tEMSTotalParam.SysFault_t.SysFault3_t;
   //tInternalCloudData.Register03H_t.tEMSTotalParam.SysFault_t.SysFault4_t;

    memcpy(&tInternalCloudData.Register03H_t.tEMSTotalParam.u16SysState_t.u16SysState1_t,&(tTotalParam.u16SysState1_t),sizeof(tTotalParam.u16SysState1_t));
    memcpy(&tInternalCloudData.Register03H_t.tEMSTotalParam.u16SysState_t.u16SysState2_t,&(tTotalParam.u16SysState2_t),sizeof(tTotalParam.u16SysState2_t));


}




/***********************************************************************************************************************
 功能：获取电网并网的数据接口
************************************************************************************************************************/
void GetGirdParmInfoToCloudData(void)
{
    memset(&tInternalCloudData.Register03H_t.tEMSGirdParm,0,sizeof(tInternalCloudData.Register03H_t.tEMSGirdParm));
    
    InvInformation_t tInvInformation;
    memset(&tInvInformation ,0, sizeof(tInvInformation));
    GetInvInformation(&tInvInformation);

    /*电网U相电压 */
    tInternalCloudData.Register03H_t.tEMSGirdParm.tUGridVoltPara = tInvInformation.s16InvGirdVoltR;   //逆变器R相电网电压
    tInternalCloudData.Register03H_t.tEMSGirdParm.tVGridVoltPara = tInvInformation.s16InvGirdVoltS;   //逆变器S相电网电压
    tInternalCloudData.Register03H_t.tEMSGirdParm.tWGridVoltPara = tInvInformation.s16InvGirdVoltT;   //逆变器T相电网电压

    /*电网频率 */
    tInternalCloudData.Register03H_t.tEMSGirdParm.tGridFreqPara = tInvInformation.u16InvGridFreq;   //逆变器电网频率
    
    /*电网U相电流 */
    tInternalCloudData.Register03H_t.tEMSGirdParm.s16GridCurrU = tInvInformation.s16InvGridCurrR;   //逆变器R相电网电流
    tInternalCloudData.Register03H_t.tEMSGirdParm.s16GridCurrV = tInvInformation.s16InvGridCurrS;   //逆变器S相电网电流
    tInternalCloudData.Register03H_t.tEMSGirdParm.s16GridCurrW = tInvInformation.s16InvGridCurrT;   //逆变器T相电网电流


    /*并网U相视在功率 */
    //此接口先预留
    //tInternalCloudData.Register03H_t.tEMSGirdParm.tGridVoltParaWattU ;   
    //tInternalCloudData.Register03H_t.tEMSGirdParm.tGridVoltParaWattV ;   
    //tInternalCloudData.Register03H_t.tEMSGirdParm.tGridVoltParaWattW ;   
    
    /*并网U相有功功率 */
    tInternalCloudData.Register03H_t.tEMSGirdParm.s16GridLoadCurrWattU = tInvInformation.s16InvGridCurrT;   //逆变器R相电网有功功率
    tInternalCloudData.Register03H_t.tEMSGirdParm.s16GridLoadCurrWattV = tInvInformation.s16InvGridWattR;   //逆变器S相电网有功功率
    tInternalCloudData.Register03H_t.tEMSGirdParm.s16GridLoadCurrWattW = tInvInformation.s16InvGridWattT;   //逆变器T相电网有功功率

    /*并网U相无功功率 */
    tInternalCloudData.Register03H_t.tEMSGirdParm.s16GridvLoadCurrVarU = tInvInformation.s16InvGridVarR;   //逆变器R相电网无功功率
    tInternalCloudData.Register03H_t.tEMSGirdParm.s16GridvLoadCurrVarV = tInvInformation.s16InvGridVarS;   //逆变器S相电网无功功率
    tInternalCloudData.Register03H_t.tEMSGirdParm.s16GridvLoadCurrVarW = tInvInformation.s16InvGridVarT;   //逆变器t相电网无功功率

    //0x0070  电网故障1
    //0x0071  电网故障2
    memcpy(&tInternalCloudData.Register03H_t.tEMSGirdParm.GridFault.GridFault1_t, &tInvInformation.InvFault_t.GridFault_t,sizeof(tInvInformation.InvFault_t.GridFault_t));
    memcpy(&tInternalCloudData.Register03H_t.tEMSGirdParm.GridFault.GridFault2_t, &tInvInformation.InvFault_t.GridFault2_t,sizeof(tInvInformation.InvFault_t.GridFault2_t));
}

/***********************************************************************************************************************
 功能：获取PV的数据接口
************************************************************************************************************************/
void GetPVInfoToCloudData(void)
{
    memset(&tInternalCloudData.Register03H_t.tEMSPVInfo,0,sizeof(tInternalCloudData.Register03H_t.tEMSPVInfo));
    PVInformation_t tPV1Information;
    memset(&tPV1Information,0,sizeof(tPV1Information));
    GetPV1Information(&tPV1Information);
    tInternalCloudData.Register03H_t.tEMSPVInfo.u16PV1Volt = tPV1Information.u16PVVolt;                                    // PV电压 
    tInternalCloudData.Register03H_t.tEMSPVInfo.s16PV1Curr = tPV1Information.s16PVCurr;                                    // PV电流 
    tInternalCloudData.Register03H_t.tEMSPVInfo.s16PV1Watt = tPV1Information.s16PVLivePower;                               // 实时PV功率
    memcpy(&tInternalCloudData.Register03H_t.tEMSPVInfo.PVFault_t.PVFault1_t, &tPV1Information.PVFault_t.PVFault1_t,sizeof(tPV1Information.PVFault_t.PVFault1_t));                             

    PVInformation_t tPV2Information;
    memset(&tPV2Information,0,sizeof(tPV2Information));
    GetPV2Information(&tPV2Information);
    tInternalCloudData.Register03H_t.tEMSPVInfo.u16PV2Volt = tPV2Information.u16PVVolt;                                    // PV电压 
    tInternalCloudData.Register03H_t.tEMSPVInfo.s16PV2Curr = tPV2Information.s16PVCurr;                                    // PV电流 
    tInternalCloudData.Register03H_t.tEMSPVInfo.s16PV2Watt = tPV2Information.s16PVLivePower;                               // 实时PV功率
    memcpy(&tInternalCloudData.Register03H_t.tEMSPVInfo.PVFault_t.PVFault2_t, &tPV1Information.PVFault_t.PVFault1_t,sizeof(tPV1Information.PVFault_t.PVFault1_t));
}


/***********************************************************************************************************************
 功能：获取电池数据的数据接口
************************************************************************************************************************/
void GetBatInfoToCloudData(void)
{
    memset(&tInternalCloudData.Register03H_t.tEMSBatInfo,0,sizeof(tInternalCloudData.Register03H_t.tEMSBatInfo));
    BmsDataPylonAnalogInfo_t tBmsPylonAnalogInfo;
    memset(&tBmsPylonAnalogInfo ,0, sizeof(tBmsPylonAnalogInfo));
    GetBmsPylonAnalogInfo(&tBmsPylonAnalogInfo);

    tInternalCloudData.Register03H_t.tEMSBatInfo.u16BatTotalVolt = tBmsPylonAnalogInfo.u16SystemAvgVolt;                      //0x0090        电池总电压
    tInternalCloudData.Register03H_t.tEMSBatInfo.u16BatTotalCurr = tBmsPylonAnalogInfo.s16SystemTotalCurr;                    //0x0091        电池总电流
    tInternalCloudData.Register03H_t.tEMSBatInfo.u16LiveSOC = tBmsPylonAnalogInfo.u16SystemSOC;                               //0x0092        实时SOC
    tInternalCloudData.Register03H_t.tEMSBatInfo.u16AverSOH = tBmsPylonAnalogInfo.u16AvgSOH;                                  //0x0093        平均SOH
    tInternalCloudData.Register03H_t.tEMSBatInfo.u16MiniSOH = tBmsPylonAnalogInfo.u16MinSOH;                                  //0x0094        最小SOH
    
    //电池满充容量
    //电池剩余容量
    //云平台协议对应CVTE,目前BMS只开放派能协议,此接口先预留
    //tInternalCloudData.Register03H_t.tEMSBatInfo.u16BatCharCap;                                                             //0x0095        电池满充容量
    //tInternalCloudData.Register03H_t.tEMSBatInfo.u16BatRemainCap;                                                           //0x0096        电池剩余容量

    tInternalCloudData.Register03H_t.tEMSBatInfo.u16AverCycle = tBmsPylonAnalogInfo.u16AvgCycleCnt;                           //0x0097        平均循环次数
    tInternalCloudData.Register03H_t.tEMSBatInfo.u16MaxCycle = tBmsPylonAnalogInfo.u16MaxCycleCnt;                            //0x0098        最大循环次数
    tInternalCloudData.Register03H_t.tEMSBatInfo.u16SingUnitMaxVolt = tBmsPylonAnalogInfo.u16MaxSingleVolt;                   //0x0099        单体最高电压
    tInternalCloudData.Register03H_t.tEMSBatInfo.u16HighVoltbitNumber = tBmsPylonAnalogInfo.u16MaxSingleVoltPos;              //0x009A       单体最高电压所属位号
    tInternalCloudData.Register03H_t.tEMSBatInfo.u16SingUnitMiniVolt = tBmsPylonAnalogInfo.u16MinSingleVolt;                  //0x009B        单体最低电压
    tInternalCloudData.Register03H_t.tEMSBatInfo.u16LowVoltbitNumber = tBmsPylonAnalogInfo.u16MinSingleVoltPos;               //0x009C        单体最低电压所属位号
    tInternalCloudData.Register03H_t.tEMSBatInfo.u16SingCoreHighTemp = tBmsPylonAnalogInfo.s16SingleMaxTemp;                      //0x009D        单芯最高温度
    tInternalCloudData.Register03H_t.tEMSBatInfo.u16SingCoreHighTempbitNumber = tBmsPylonAnalogInfo.u16SingleMaxTempPos;      //0x009E        单芯最高温度所属位号
    tInternalCloudData.Register03H_t.tEMSBatInfo.u16SingCoreMiniTemp = tBmsPylonAnalogInfo.s16SingleMinTemp;                  //0x009F        单芯最低温度
    tInternalCloudData.Register03H_t.tEMSBatInfo.u16SingCoreMiniTempbitNumber = tBmsPylonAnalogInfo.u16SingleMinTempPos;        //0x00A0        单芯最低温度所属位号

    BmsDataPylonMutualInfo_t tBmsPylonMutualInfo;
    memset(&tBmsPylonMutualInfo ,0, sizeof(tBmsPylonMutualInfo));
    GetBmsPylonMutualInfo(&tBmsPylonMutualInfo);
    tInternalCloudData.Register03H_t.tEMSBatInfo.u16MaxCharCurr = tBmsPylonMutualInfo.s16MaxChgCurr;                           //0x00A1        最大充电电流
    tInternalCloudData.Register03H_t.tEMSBatInfo.u16MaxDisharCurr = tBmsPylonMutualInfo.s16MaxDischgCurr;                      //0x00A2        最大放电电流
    tInternalCloudData.Register03H_t.tEMSBatInfo.u16UpperLimitCharVolt = tBmsPylonMutualInfo.u16ChgVoltHighLimit;              //0x00A3        充电电压建议上限
    tInternalCloudData.Register03H_t.tEMSBatInfo.u16UpperLimitDischarVolt = tBmsPylonMutualInfo.u16DisChgVoltLowLimit;         //0x00A4        放电电压建议上限
    
    //电池故障1
    //电池告警1  
    //云平台协议对应CVTE,目前BMS只开放派能协议,此接口先预留
    //tInternalCloudData.Register03H_t.tEMSBatInfo.BatError_t.BatError1_t;
    //tInternalCloudData.Register03H_t.tEMSBatInfo.BatError_t.BatWarning1_t;

    //DCDC变换器故障    
    Display_DCDC_Fault_t ptDisplayDCDCFault;
    memset(&ptDisplayDCDCFault ,0, sizeof(ptDisplayDCDCFault));
    GetDisplayDCDCFault(&ptDisplayDCDCFault);
    memcpy(&tInternalCloudData.Register03H_t.tEMSBatInfo.DCDC_Error_t.DCDCError1_t,&(ptDisplayDCDCFault.DCDCError1_t),sizeof(ptDisplayDCDCFault.DCDCError1_t));
}

/***********************************************************************************************************************
 功能：获取负载的数据接口
************************************************************************************************************************/
void GetLoadInfoToCloudData(void)
{
    memset(&tInternalCloudData.Register03H_t.tEMSLoadInfo,0,sizeof(tInternalCloudData.Register03H_t.tEMSLoadInfo));
    Display_DATA_LOAD ptDisplayLoadData;
    memset(&ptDisplayLoadData,0,sizeof(ptDisplayLoadData));
    GetDisplayRealTimeLoadData(&ptDisplayLoadData);
    tInternalCloudData.Register03H_t.tEMSLoadInfo.u16LoadVolt = ptDisplayLoadData.u16LoadVoltage;
    tInternalCloudData.Register03H_t.tEMSLoadInfo.u16LoadCurr = ptDisplayLoadData.sLoadcurrent;
    
    //负载频率
    //负载百分比
    //此接口先预留
    //tInternalCloudData.Register03H_t.tEMSLoadInfo.u16LoadFren;
    //tInternalCloudData.Register03H_t.tEMSLoadInfo.u16LoadPercent;
}


/***********************************************************************************************************************
 功能：获取逆变器和发电机的数据接口
************************************************************************************************************************/
void GetInvGenInfoToCloudData(void)
{
    memset(&tInternalCloudData.Register03H_t.tEMSInvGenInfo,0,sizeof(tInternalCloudData.Register03H_t.tEMSInvGenInfo));
    
    InvInformation_t tInvInformation;
    memset(&tInvInformation ,0, sizeof(tInvInformation));
    GetInvInformation(&tInvInformation);
    /*逆变器U相电感电流 */
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16InvInductanceCurrU = tInvInformation.s16InvInductanceCurrR;
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16InvInductanceCurrV = tInvInformation.s16InvInductanceCurrS;
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16InvInductanceCurrW = tInvInformation.s16InvInductanceCurrT;
        
    /*逆变器U相输出电压 */
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.u16InvVoltU = tInvInformation.u16InvVoltR;
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.u16InvVoltV = tInvInformation.u16InvVoltS;
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.u16InvVoltW = tInvInformation.u16InvVoltT;
        
    /*逆变器U相输出电流 */
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16InvCurrU = tInvInformation.s16InvCurrR;
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16InvCurrV = tInvInformation.s16InvCurrS;
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16InvCurrW = tInvInformation.s16InvCurrT;

    /*逆变器输出频率*/
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.u16InvOutputFreq = tInvInformation.u16InvOutputFreq;
        
    /*逆变器U相负载电流 */
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16InvLoadCurrU = tInvInformation.s16InvLoadCurrR;
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16InvLoadCurrV = tInvInformation.s16InvLoadCurrS;
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16InvLoadCurrW = tInvInformation.s16InvLoadCurrT;
  
    /*逆变器U相负载侧有功功率 */
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16InvLoadCurrWattU = tInvInformation.s16InvLoadCurrWattR;
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16InvLoadCurrWattV = tInvInformation.s16InvLoadCurrWattS;
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16InvLoadCurrWattW = tInvInformation.s16InvLoadCurrWattT;

    /*逆变器U相负载侧无功功率 */
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16InvLoadCurrVarU = tInvInformation.s16InvLoadCurrVarR;
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16InvLoadCurrVarV = tInvInformation.s16InvLoadCurrVarS;
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16InvLoadCurrVarW = tInvInformation.s16InvLoadCurrVarT;
        
    /*发电机U相输出电压 */
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.u16GenVoltU = tInvInformation.u16GenVoltR;
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16GenVoltV = tInvInformation.s16GenVoltS;
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16GenVoltW = tInvInformation.s16GenVoltT;         
    /*发电机U相输出电流 */
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16GenCurrU = tInvInformation.s16GenCurrR;
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16GenCurrV = tInvInformation.s16GenCurrS;
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16GenCurrW = tInvInformation.s16GenCurrT;

    /*发电机频率 */
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.u16GenFreq = tInvInformation.u16GenFreq;
            
    /*发电机U相有功功率 */
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16GenWattU = tInvInformation.s16GenWattR;
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16GenWattV = tInvInformation.s16GenWattS;
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16GenWattW = tInvInformation.s16GenWattT;

    /*发电机U相无功功率 */
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16GenVarU = tInvInformation.s16GenVarR;
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16GenVarV = tInvInformation.s16GenVarS;
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.s16GenVarW = tInvInformation.s16GenVarT;

    /*发电机容量 */
    tInternalCloudData.Register03H_t.tEMSInvGenInfo.u16GenCap = tInvInformation.u16GenCap;

    //0x00E1 设备故障1
    memcpy(&tInternalCloudData.Register03H_t.tEMSInvGenInfo.InvFault_t.DeviceFault1_t,&(tInvInformation.InvFault_t.DeviceFault1_t),sizeof(tInvInformation.InvFault_t.DeviceFault1_t));
    //0x00E2  并机故障
    memcpy(&tInternalCloudData.Register03H_t.tEMSInvGenInfo.InvFault_t.ParallelSysFault_t,&(tInvInformation.InvFault_t.ParallelSysFault_t),sizeof(tInvInformation.InvFault_t.ParallelSysFault_t));
}


/***********************************************************************************************************************
 功能：获取统计数据的数据接口
************************************************************************************************************************/
void GetSystemStatisticalToCloudData(void)
{
    memset(&tInternalCloudData.Register03H_t.tEMSStatisticalInfo,0,sizeof(tInternalCloudData.Register03H_t.tEMSStatisticalInfo));
    Display_DATA_STATISTICAL *pSTATISTICAL = Display_Get_SystemStatistical();
    /*总发电时间*/
    //总发电时间预留
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u16TotalGenerateTime = 60000;
    /*光伏 */
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u16PVGenerateOnDay = pSTATISTICAL->stDayStatisticaldata.stPVPowerGeneration;
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u16PVGenerateOnMonth = pSTATISTICAL->stMonthStatisticaldata.stPVPowerGeneration;
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u32PVGenerateOnYear = pSTATISTICAL->stYearStatisticaldata.stPVPowerGeneration;
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u32PVGenerateTotal = pSTATISTICAL->stTotalStatisticaldata.stPVPowerGeneration;
        
    /*负载 */
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u16LoadConsumptionOnDay = pSTATISTICAL->stDayStatisticaldata.stLoadPowerGeneration;
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u16LoadConsumptionOnMonth = pSTATISTICAL->stMonthStatisticaldata.stLoadPowerGeneration;
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u32LoadConsumptionOnYear = pSTATISTICAL->stYearStatisticaldata.stLoadPowerGeneration;
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u32LoadConsumptionTotal = pSTATISTICAL->stTotalStatisticaldata.stLoadPowerGeneration;
        
    /*充电 */
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u16CharOnDay = pSTATISTICAL->stDayStatisticaldata.stChagePowerGeneration;
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u16CharOnMonth = pSTATISTICAL->stMonthStatisticaldata.stChagePowerGeneration;
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u32CharOnYear = pSTATISTICAL->stYearStatisticaldata.stChagePowerGeneration;
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u32CharTotal = pSTATISTICAL->stTotalStatisticaldata.stChagePowerGeneration;
        
    /*放电 */
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u16DisCharOnDay = pSTATISTICAL->stDayStatisticaldata.stDisChagePowerGeneration;
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u16DisCharOnMonth = pSTATISTICAL->stMonthStatisticaldata.stDisChagePowerGeneration;
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u32DisCharOnYear = pSTATISTICAL->stYearStatisticaldata.stDisChagePowerGeneration;
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u32DisCharTotal = pSTATISTICAL->stTotalStatisticaldata.stDisChagePowerGeneration;
        
    /*输出 */
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u16OutputOnDay = pSTATISTICAL->stDayStatisticaldata.stOutputPowerGeneration;
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u16OutputOnMonth = pSTATISTICAL->stMonthStatisticaldata.stOutputPowerGeneration;
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u32OutputOnYear = pSTATISTICAL->stYearStatisticaldata.stOutputPowerGeneration;
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u32OutputTotal = pSTATISTICAL->stTotalStatisticaldata.stOutputPowerGeneration; 
        
    /*输入 */
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u16InputOnDay = pSTATISTICAL->stDayStatisticaldata.stInputPowerGeneration;
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u16InputOnMonth = pSTATISTICAL->stMonthStatisticaldata.stInputPowerGeneration;
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u32InputOnYear = pSTATISTICAL->stYearStatisticaldata.stInputPowerGeneration;
    tInternalCloudData.Register03H_t.tEMSStatisticalInfo.u32InputTotal = pSTATISTICAL->stTotalStatisticaldata.stInputPowerGeneration;
}


/***********************************************************************************************************************
 功能：检查BMS_CLOUD协议功能码03H的通讯数据范围是否越界
************************************************************************************************************************/
MBErrorCode CheckEmsCloudComDataRange_03H(MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;

    if (EMS_TO_CLOUD_03H_SYS_PARAM_INFO_END >= (ptMBFrame->u16MBStartRegsAddr))
    {
        if((EMS_TO_CLOUD_03H_SYS_PARAM_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_03H_SYS_PARAM_INFO_START)) || \
           (EMS_TO_CLOUD_03H_SYS_PARAM_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_03H_SYS_PARAM_INFO_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if ((EMS_TO_CLOUD_03H_GRID_PARAM_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_03H_GRID_PARAM_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        if((EMS_TO_CLOUD_03H_GRID_PARAM_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_03H_GRID_PARAM_START)) || \
           (EMS_TO_CLOUD_03H_GRID_PARAM_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_03H_GRID_PARAM_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if ((EMS_TO_CLOUD_03H_PV_INFO_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_03H_PV_INFO_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        if((EMS_TO_CLOUD_03H_PV_INFO_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_03H_PV_INFO_START)) || \
           (EMS_TO_CLOUD_03H_PV_INFO_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_03H_PV_INFO_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if ((EMS_TO_CLOUD_03H_BAT_INFO_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_03H_BAT_INFO_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        if((EMS_TO_CLOUD_03H_BAT_INFO_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_03H_BAT_INFO_START)) || \
           (EMS_TO_CLOUD_03H_BAT_INFO_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_03H_BAT_INFO_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if ((EMS_TO_CLOUD_03H_LOAD_INFO_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_03H_LOAD_INFO_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        if((EMS_TO_CLOUD_03H_LOAD_INFO_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_03H_LOAD_INFO_START)) || \
           (EMS_TO_CLOUD_03H_LOAD_INFO_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_03H_LOAD_INFO_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if ((EMS_TO_CLOUD_03H_INV_INFO_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_03H_INV_INFO_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        if((EMS_TO_CLOUD_03H_INV_INFO_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_03H_INV_INFO_START)) || \
           (EMS_TO_CLOUD_03H_INV_INFO_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_03H_INV_INFO_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if ((EMS_TO_CLOUD_03H_GIRD_INFO_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_03H_GIRD_INFO_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        if((EMS_TO_CLOUD_03H_GIRD_INFO_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_03H_GIRD_INFO_START)) || \
           (EMS_TO_CLOUD_03H_GIRD_INFO_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_03H_GIRD_INFO_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else
    {
        eStatus = MB_DATA_ADD_ERROR;
    }

    return eStatus;
}


/***********************************************************************************************************************
 功能：定位起始地址对应的英臻云平台协议功能码03H的数据结构地址
************************************************************************************************************************/
uint16_t* GetComDataToCloud_03H(MBRTUFrame_t* ptMBFrame)
{
    uint16_t *pu8ObjBuf = NULL;
    if ((EMS_TO_CLOUD_03H_SYS_PARAM_INFO_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        GetTotalSysParamToCloudData();
        pu8ObjBuf = (uint16_t*)& tInternalCloudData.Register03H_t.tEMSTotalParam;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_03H_SYS_PARAM_INFO_START);
    }
    else if ((EMS_TO_CLOUD_03H_GRID_PARAM_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_03H_GRID_PARAM_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        GetGirdParmInfoToCloudData();
        pu8ObjBuf = (uint16_t*)& tInternalCloudData.Register03H_t.tEMSGirdParm;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_03H_GRID_PARAM_START);
    }
    else if ((EMS_TO_CLOUD_03H_PV_INFO_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_03H_PV_INFO_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        GetPVInfoToCloudData();
        pu8ObjBuf = (uint16_t*)& tInternalCloudData.Register03H_t.tEMSPVInfo;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_03H_PV_INFO_START);
    }
    else if ((EMS_TO_CLOUD_03H_BAT_INFO_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_03H_BAT_INFO_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        GetBatInfoToCloudData();
        pu8ObjBuf = (uint16_t*)& tInternalCloudData.Register03H_t.tEMSBatInfo;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_03H_BAT_INFO_START);
    }
    else if ((EMS_TO_CLOUD_03H_LOAD_INFO_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_03H_LOAD_INFO_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        GetLoadInfoToCloudData();
        pu8ObjBuf = (uint16_t*)& tInternalCloudData.Register03H_t.tEMSLoadInfo;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_03H_LOAD_INFO_START);
    }
    else if ((EMS_TO_CLOUD_03H_INV_INFO_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_03H_INV_INFO_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
         GetInvGenInfoToCloudData();
        pu8ObjBuf = (uint16_t*)& tInternalCloudData.Register03H_t.tEMSInvGenInfo;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_03H_INV_INFO_START);
    }
    else if ((EMS_TO_CLOUD_03H_GIRD_INFO_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_03H_GIRD_INFO_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        GetSystemStatisticalToCloudData();
        pu8ObjBuf = (uint16_t*)& tInternalCloudData.Register03H_t.tEMSStatisticalInfo;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_03H_GIRD_INFO_START);
    }
    else
    {
        ;
    }
    return pu8ObjBuf;

}




/***********************************************************************************************************************
 功能：检查BMS_CLOUD协议功能码10的通讯数据范围是否越界
************************************************************************************************************************/
MBErrorCode CheckEmsCloudComDataRange_10H(MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;

    if (EMS_TO_CLOUD_10H_SYS_PARAM_END >= (ptMBFrame->u16MBStartRegsAddr))
    {
        if((EMS_TO_CLOUD_10H_SYS_PARAM_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_10H_SYS_PARAM_START)) || \
           (EMS_TO_CLOUD_10H_SYS_PARAM_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_10H_SYS_PARAM_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if ((EMS_TO_CLOUD_10H_PV_CTRL_PARAM_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_10H_PV_CTRL_PARAM_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        if((EMS_TO_CLOUD_10H_PV_CTRL_PARAM_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_10H_PV_CTRL_PARAM_START)) || \
           (EMS_TO_CLOUD_10H_PV_CTRL_PARAM_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_10H_PV_CTRL_PARAM_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if ((EMS_TO_CLOUD_10H_BAT_SET_PARAM_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_10H_BAT_SET_PARAM_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        if((EMS_TO_CLOUD_10H_BAT_SET_PARAM_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_10H_BAT_SET_PARAM_START)) || \
           (EMS_TO_CLOUD_10H_BAT_SET_PARAM_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_10H_BAT_SET_PARAM_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if ((EMS_TO_CLOUD_10H_INV_CTRL_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_10H_INV_CTRL_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        if((EMS_TO_CLOUD_10H_INV_CTRL_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_10H_INV_CTRL_START)) || \
           (EMS_TO_CLOUD_10H_INV_CTRL_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_10H_INV_CTRL_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if ((EMS_TO_CLOUD_10H_GEN_PARAM_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_10H_GEN_PARAM_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        if((EMS_TO_CLOUD_10H_GEN_PARAM_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_10H_GEN_PARAM_START)) || \
           (EMS_TO_CLOUD_10H_GEN_PARAM_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_10H_GEN_PARAM_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else if ((EMS_TO_CLOUD_10H_STRATEGY_TIME_PARAM_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_10H_STRATEGY_TIME_PARAM_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        if((EMS_TO_CLOUD_10H_STRATEGY_TIME_PARAM_LENGTH <= (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_10H_STRATEGY_TIME_PARAM_START)) || \
           (EMS_TO_CLOUD_10H_STRATEGY_TIME_PARAM_LENGTH < (ptMBFrame->u16MBRegsNum + ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_10H_STRATEGY_TIME_PARAM_START)))
        {
            eStatus = MB_DATA_ADD_ERROR;
        }
        else
        {
            ;
        }
    }
    else
    {
        eStatus = MB_DATA_ADD_ERROR;
    }

    return eStatus;
}


/***********************************************************************************************************************
 功能：定位起始地址对应的英臻云平台协议功能码10H的数据结构地址
************************************************************************************************************************/
uint16_t* GetComDataToCloud_10H(MBRTUFrame_t* ptMBFrame)
{
    uint16_t *pu8ObjBuf = NULL;
    if ((EMS_TO_CLOUD_10H_SYS_PARAM_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        //memset(&tInternalCloudData.Register10H_t.tEmsSysParam,0,sizeof(tInternalCloudData.Register10H_t.tEmsSysParam));
        pu8ObjBuf = (uint16_t*)& tInternalCloudData.Register10H_t.tEmsSysParam;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_10H_SYS_PARAM_START);
    }
    else if ((EMS_TO_CLOUD_10H_PV_CTRL_PARAM_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_10H_PV_CTRL_PARAM_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        //memset(&tInternalCloudData.Register10H_t.tEmsPvControlWay,0,sizeof(tInternalCloudData.Register10H_t.tEmsPvControlWay));
        pu8ObjBuf = (uint16_t*)& tInternalCloudData.Register10H_t.tEmsPvControlWay;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_10H_PV_CTRL_PARAM_START);
    }
    else if ((EMS_TO_CLOUD_10H_BAT_SET_PARAM_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_10H_BAT_SET_PARAM_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        //memset(&tInternalCloudData.Register10H_t.tEmsBatteryDate,0,sizeof(tInternalCloudData.Register10H_t.tEmsBatteryDate));
        pu8ObjBuf = (uint16_t*)& tInternalCloudData.Register10H_t.tEmsBatteryDate;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_10H_BAT_SET_PARAM_START);
    }
    else if ((EMS_TO_CLOUD_10H_INV_CTRL_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_10H_INV_CTRL_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        //memset(&tInternalCloudData.Register10H_t.tEmsInvCtrlParam,0,sizeof(tInternalCloudData.Register10H_t.tEmsInvCtrlParam));
        pu8ObjBuf = (uint16_t*)& tInternalCloudData.Register10H_t.tEmsInvCtrlParam;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_10H_INV_CTRL_START);
    }
    else if ((EMS_TO_CLOUD_10H_GEN_PARAM_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_10H_GEN_PARAM_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        //memset(&tInternalCloudData.Register10H_t.tEmsGenParam,0,sizeof(tInternalCloudData.Register10H_t.tEmsGenParam));
        pu8ObjBuf = (uint16_t*)& tInternalCloudData.Register10H_t.tEmsGenParam;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_10H_GEN_PARAM_START);
    }
    else if ((EMS_TO_CLOUD_10H_STRATEGY_TIME_PARAM_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_10H_STRATEGY_TIME_PARAM_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        //memset(&tInternalCloudData.Register10H_t.tEmsStrategyTime,0,sizeof(tInternalCloudData.Register10H_t.tEmsStrategyTime));
        pu8ObjBuf = (uint16_t*)& tInternalCloudData.Register10H_t.tEmsStrategyTime;
        pu8ObjBuf += (ptMBFrame->u16MBStartRegsAddr - EMS_TO_CLOUD_10H_STRATEGY_TIME_PARAM_START);
    }
    else
    {
        ;
    }
    return pu8ObjBuf;

}

/*系统数据设置*/
extern TimeInf_t TimeSetNum;
void GetCloudInputSysParamTimeSet(void)
{
  //tInternalCloudData.Register03H_t.tEMSTotalParam.u16ProtocolFlag;                  //0x0000 协议标识 
  //gDisplay.stDisplaySet.u8LanguageType = (Language_TypeDef)tInternalCloudData.Register10H_t.tEmsSysParam.u16LanguageType;  //0x0001 语言
  setSystemLanguageItem((Language_TypeDef)tInternalCloudData.Register10H_t.tEmsSysParam.u16LanguageType);
  SystemLanguageInit();
  TimeSetNum.u16Year = tInternalCloudData.Register10H_t.tEmsSysParam.u16SysYear;                       //0x0002 日期校正-年
  TimeSetNum.u8Month = tInternalCloudData.Register10H_t.tEmsSysParam.u16SysMonth;                      //0x0003 日期校正-月
  TimeSetNum.u8Day = tInternalCloudData.Register10H_t.tEmsSysParam.u16SysDay;                         //0x0004 日期校正-日
  TimeSetNum.u8Week = tInternalCloudData.Register10H_t.tEmsSysParam.u16SysWeek;                       //0x0005 时间校正-周
  TimeSetNum.u8Hour = tInternalCloudData.Register10H_t.tEmsSysParam.u16SysHour;                       //0x0006 时间校正-时
  TimeSetNum.u8Min = tInternalCloudData.Register10H_t.tEmsSysParam.u16SysMinute;                      //0x0007 时间校正-分
  TimeSetNum.u8Sec = tInternalCloudData.Register10H_t.tEmsSysParam.u16SysSecond;                     //0x0008 时间校正-秒

  Set_SysTime(TimeSetNum);/*时间校准*/

  Display_SET_System_ProtectEnable *pStProtectEnable = Display_Get_ProtectPara();
  Flash_Device_ProtectInfo_Read(pStProtectEnable,sizeof(Display_SET_System_ProtectEnable));
  pStProtectEnable->u8IslandProtection = tInternalCloudData.Register10H_t.tEmsSysParam.u16IslandProt;                      //0x0009 孤岛保护
  pStProtectEnable->u8GroundProtection = tInternalCloudData.Register10H_t.tEmsSysParam.u16GroundProt;                      //0x000A 接地保护
  pStProtectEnable->u8InsulationImpedanceProtection = tInternalCloudData.Register10H_t.tEmsSysParam.u16InsulationResProt;  //0x000B 绝缘阻抗保护
  /*保护数据写FLASH*/
  Flash_Device_ProtectInfo_Write(pStProtectEnable,sizeof(Display_SET_System_ProtectEnable));
  return;
}

/*PV控制方式设置*/
void GetCloudInputPvCtrlParamSet(void)
{
    Display_SET_PV* pStPV= Display_Get_PVPara();
    pStPV->u8PVControlWay = tInternalCloudData.Register10H_t.tEmsPvControlWay.u16PVCtrlWay;                           //0x0020 光伏控制方式
    //uint16_t u16OpenVolt;                            //0x0021 开路电压设置
    /*PV控制方式数据写FLASH*/
    Flash_Device_PVInfo_Write(pStPV,sizeof(Display_SET_PV));
    return;
}


void GetCloudBatteryDataSet(void)
{
    Display_SET_BMS* pStBMS = Display_Get_BmsSetPara();
    Flash_Device_BMSInfo_Read(pStBMS,sizeof(Display_SET_BMS));   
    /*电池类型*/
    pStBMS->u8Type = (uint8_t)(tInternalCloudData.Register10H_t.tEmsBatteryDate.u16Type & 0x00FF); //0x0030   电池类型(默认0) 0:磷酸铁锂 1:铅酸电池
    /*Li电池设置*/
    pStBMS->u8ProtocolType = (uint8_t)tInternalCloudData.Register10H_t.tEmsBatteryDate.BatteryLiParas.u16ProtocolType; //0x0031   电池协议类型:0:无电池 1:CVTE 2:派能
    pStBMS->stHMISetBMSLiIonParas.u8ComWayFlag = (uint8_t)tInternalCloudData.Register10H_t.tEmsBatteryDate.BatteryLiParas.u16ComWayFlag; //0x0032   通信方式 0:CAN 1:485通信 
    pStBMS->stHMISetBMSLiIonParas.u8EndOfCharSOC = (uint8_t)tInternalCloudData.Register10H_t.tEmsBatteryDate.BatteryLiParas.u16EndOfCharSOC; //0x0033   充电截止SOC
    pStBMS->stHMISetBMSLiIonParas.u8EndOfDisCharSOC = (uint8_t)tInternalCloudData.Register10H_t.tEmsBatteryDate.BatteryLiParas.u16EndOfDisCharSOC; //0x0034   放电截止SOC
    pStBMS->stHMISetBMSLiIonParas.u16MaxCharCurrent = tInternalCloudData.Register10H_t.tEmsBatteryDate.BatteryLiParas.u16MaxCharCurrent; //0x0035   最大充电电流
    pStBMS->stHMISetBMSLiIonParas.u16MaxDisCharCurrent = tInternalCloudData.Register10H_t.tEmsBatteryDate.BatteryLiParas.u16MaxDisCharCurrent; //0x0036   最大放电电流
    /*Lead电池设置*/
    pStBMS->stHMISetBMSLeadAcidParas.u16BatteryCapacity = tInternalCloudData.Register10H_t.tEmsBatteryDate.BatteryLeadParas.u16BatteryCapacity; //0x0037   电池容量设置 
    pStBMS->stHMISetBMSLeadAcidParas.u8EndOfCharSOC = (uint8_t)tInternalCloudData.Register10H_t.tEmsBatteryDate.BatteryLeadParas.u16EndOfCharSOC; //0x0038   充电截止SOC
    pStBMS->stHMISetBMSLeadAcidParas.u8EndOfDisCharSOC = (uint8_t)tInternalCloudData.Register10H_t.tEmsBatteryDate.BatteryLeadParas.u16EndOfDisCharSOC; //0x0039   放电截止SOC
    pStBMS->stHMISetBMSLeadAcidParas.u16MaxCharCurrent = tInternalCloudData.Register10H_t.tEmsBatteryDate.BatteryLeadParas.u16MaxCharCurrent; //0x003A   最大充电电流
    pStBMS->stHMISetBMSLeadAcidParas.u16MaxDisCharCurrent = tInternalCloudData.Register10H_t.tEmsBatteryDate.BatteryLeadParas.u16MaxDisCharCurrent; //0x003B   最大放电电流
    pStBMS->stHMISetBMSLeadAcidParas.u16LowVoltShutPoint = tInternalCloudData.Register10H_t.tEmsBatteryDate.BatteryLeadParas.u16LowVoltShutPoint; //0x003C   低压关机电压点 
    pStBMS->stHMISetBMSLeadAcidParas.u16FloatVoltPoint = tInternalCloudData.Register10H_t.tEmsBatteryDate.BatteryLeadParas.u16FloatVoltPoint; //0x003D   浮动电压点
    pStBMS->stHMISetBMSLeadAcidParas.u16ConstVoltCharPoint = tInternalCloudData.Register10H_t.tEmsBatteryDate.BatteryLeadParas.u16ConstVoltCharPoint; //0x003E   恒压充电电压点
    //0x003E-0x004F  预留
    /*设置电池数据，写FLASH*/
    Flash_Device_BMSInfo_Write(pStBMS,sizeof(Display_SET_BMS));
    return;  
}

/*逆变器控制参数设置*/
void GetCloudInputInvCtrlParamSet(void)
{
    Display_SET_Grid* pStGrid = Display_Get_GridPara();
    /*防逆流设置*/
    pStGrid->u8PreventReverseFlowControlFlag = (uint8_t)tInternalCloudData.Register10H_t.tEmsInvCtrlParam.u16NoBackflowCtrl; //0x0050    防逆流控制

    pStGrid->u8SafetyRegulationType = (uint8_t)tInternalCloudData.Register10H_t.tEmsInvCtrlParam.u16GridConnectRule;        //0x0051    并网准则
    pStGrid->u8ReactPowerControlWay = (uint8_t)tInternalCloudData.Register10H_t.tEmsInvCtrlParam.u16ReactPowerControlWay;   //0x0052    无功控制方式：0：无功控制 1：PF控制
    //= tInternalCloudData.Register10H_t.tEmsInvCtrlParam.u16ActivePower;//未修改                 //0x0053    有功功率
    pStGrid->s16ReactPower = tInternalCloudData.Register10H_t.tEmsInvCtrlParam.u16ReactivePower;  //0x0054    无功功率
    pStGrid->s16PF = tInternalCloudData.Register10H_t.tEmsInvCtrlParam.u16PowerFactor;            //0x0055    功率因数
    // = tInternalCloudData.Register10H_t.tEmsInvCtrlParam.u16SampSelect; //未添加                //0x0056    采样选择
    pStGrid->stTimeDivisionElecPrice.stPeakPeriod.u8ElecPrice = (uint8_t)tInternalCloudData.Register10H_t.tEmsInvCtrlParam.u16PeakElecPrice;      //0x0057    峰段电价
    pStGrid->stTimeDivisionElecPrice.stFlatPeriod.u8ElecPrice = (uint8_t)tInternalCloudData.Register10H_t.tEmsInvCtrlParam.u16FlatElecPrice;      //0x0058    平段电价
    pStGrid->stTimeDivisionElecPrice.stValleyPeriod.u8ElecPrice = (uint8_t)tInternalCloudData.Register10H_t.tEmsInvCtrlParam.u16ValleyElecPrice;  //0x0059    谷段电价
    /*电网数据写FLASH*/
    Flash_Device_GridInfo_Write(pStGrid,sizeof(Display_SET_Grid));
    return;
}


/*发电机参数设置*/
void GetCloudInputGenParamSet(void)
{
    Display_SET_Gen* pStGen = Display_Get_GenPara();
    pStGen->u8DryNodeUse = (uint8_t)tInternalCloudData.Register10H_t.tEmsGenParam.u16GenInterf;                 //0x0070 发电机接口设置
    pStGen->stGenPara.u16RatedPower = tInternalCloudData.Register10H_t.tEmsGenParam.u16GenRatedPower;  //0x0071 发电机额定功率
    pStGen->stGenPara.u16MaxPower = tInternalCloudData.Register10H_t.tEmsGenParam.u16GenMaxPower;      //0x0072 发电机最大功率
    pStGen->stIntelLoad.u8CutDrySOC = (uint8_t)tInternalCloudData.Register10H_t.tEmsGenParam.u16AILoadExitSOC;  //0x0075 智能负载退出SOC
    pStGen->stIntelLoad.u8OnDrySOC = (uint8_t)tInternalCloudData.Register10H_t.tEmsGenParam.u16AILoadEnterSOC;  //0x0076 智能负载接入SOC
    /*发电机数据写FLASH*/
    Flash_Device_GenInfo_Write(pStGen,sizeof(Display_SET_Gen));
    
    /*发电机策略获取*/
    Display_SET_System_Strategy* pStStrategy = Display_Get_SystemStrategy();
    pStStrategy->stGenStrategy.u8ForbidSOC  = (uint8_t)tInternalCloudData.Register10H_t.tEmsGenParam.u16EmsFbdGenChgSOC;  //0x0073 发电机禁止充电SOC(退出)
    pStStrategy->stGenStrategy.u8SupplySOC = (uint8_t)tInternalCloudData.Register10H_t.tEmsGenParam.u16EmsSupplySOC;      //0x0074 发电机补电模式SOC(接入)
    /*设置发电机策略补电禁止SOC，写FLASH*/
    Flash_Device_StrategyData_Write(pStStrategy,sizeof(Display_SET_System_Strategy));
    return;
}

/*策略选择 时间转化为时分设置*/
CloudTime_t GetConvertCloudInputTime(uint16_t u16CloudTime)
{
    uint16_t u16Count = 0;
    uint16_t NumArray[4] = {0};
    CloudTime_t InputTime;
    memset(&InputTime, 0, sizeof(CloudTime_t));
    while (u16CloudTime!=0) {
        NumArray[u16Count++] = u16CloudTime%10;//取余数
        u16CloudTime/=10;
    }
    InputTime.u16hour = NumArray[3] *10 + NumArray[2];
    InputTime.u16minute = NumArray[1] *10 + NumArray[0];
    return InputTime;
}

void GetCloudInputTPFVTimeSet(void)
{
    /*策略选择*/
    //tInternalCloudData.Register10H_t.tEmsStrategyTime.u16StrategySelect; //0x0080 策略选择
    CloudTime_t CloudTimeTmp;
    /*峰段开始和结束时间*/
    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    Display_SET_Grid_TimeDivisionElecPrice* pStTimeDivisionElecPrice = Display_Get_ElecPrice();

    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16Peak1StartTime); //0x0081 峰谷模式/峰段1开始时分
    pStTimeDivisionElecPrice->stPeakPeriod.stPeriod1.u8StartHour = (uint8_t)CloudTimeTmp.u16hour;
    pStTimeDivisionElecPrice->stPeakPeriod.stPeriod1.u8StartMin = (uint8_t)CloudTimeTmp.u16minute;

    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16Peak1EndTime); //0x0082 峰谷模式/峰段1结束时分
    pStTimeDivisionElecPrice->stPeakPeriod.stPeriod1.u8EndHour = (uint8_t)CloudTimeTmp.u16hour;
    pStTimeDivisionElecPrice->stPeakPeriod.stPeriod1.u8EndMin = (uint8_t)CloudTimeTmp.u16minute;

    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16Peak2StartTime); //0x0083 峰谷模式/峰段2开始时分
    pStTimeDivisionElecPrice->stPeakPeriod.stPeriod2.u8StartHour = (uint8_t)CloudTimeTmp.u16hour;
    pStTimeDivisionElecPrice->stPeakPeriod.stPeriod2.u8StartMin = (uint8_t)CloudTimeTmp.u16minute;

    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16Peak2EndTime); //0x0084 峰谷模式/峰段2结束时分
    pStTimeDivisionElecPrice->stPeakPeriod.stPeriod2.u8EndHour = (uint8_t)CloudTimeTmp.u16hour;
    pStTimeDivisionElecPrice->stPeakPeriod.stPeriod2.u8EndMin = (uint8_t)CloudTimeTmp.u16minute;

    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16Peak3StartTime); //0x0085 峰谷模式/峰段3开始时分
    pStTimeDivisionElecPrice->stPeakPeriod.stPeriod3.u8StartHour = (uint8_t)CloudTimeTmp.u16hour;
    pStTimeDivisionElecPrice->stPeakPeriod.stPeriod3.u8StartMin = (uint8_t)CloudTimeTmp.u16minute;

    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16Peak3EndTime); //0x0086 峰谷模式/峰段3结束时分
    pStTimeDivisionElecPrice->stPeakPeriod.stPeriod3.u8EndHour = (uint8_t)CloudTimeTmp.u16hour;
    pStTimeDivisionElecPrice->stPeakPeriod.stPeriod3.u8EndMin = (uint8_t)CloudTimeTmp.u16minute;

    /*谷段开始和结束时间*/
    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16Valley1StartTime); //0x0087 峰谷模式/谷段1开始时分
    pStTimeDivisionElecPrice->stValleyPeriod.stPeriod1.u8StartHour = (uint8_t)CloudTimeTmp.u16hour;
    pStTimeDivisionElecPrice->stValleyPeriod.stPeriod1.u8StartMin = (uint8_t)CloudTimeTmp.u16minute;

    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16Valley1EndTime); //0x0088 峰谷模式/谷段1结束时分
    pStTimeDivisionElecPrice->stValleyPeriod.stPeriod1.u8EndHour = (uint8_t)CloudTimeTmp.u16hour;
    pStTimeDivisionElecPrice->stValleyPeriod.stPeriod1.u8EndMin = (uint8_t)CloudTimeTmp.u16minute;

    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16Valley2StartTime); //0x0089 峰谷模式/谷段2开始时分
    pStTimeDivisionElecPrice->stValleyPeriod.stPeriod2.u8StartHour = (uint8_t)CloudTimeTmp.u16hour;
    pStTimeDivisionElecPrice->stValleyPeriod.stPeriod2.u8StartMin = (uint8_t)CloudTimeTmp.u16minute;

    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16Valley2EndTime); //0x008A 峰谷模式/谷段2结束时分
    pStTimeDivisionElecPrice->stValleyPeriod.stPeriod2.u8EndHour = (uint8_t)CloudTimeTmp.u16hour;
    pStTimeDivisionElecPrice->stValleyPeriod.stPeriod2.u8EndMin = (uint8_t)CloudTimeTmp.u16minute;

    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16Valley3StartTime); //0x008B 峰谷模式/谷段3开始时分
    pStTimeDivisionElecPrice->stValleyPeriod.stPeriod3.u8StartHour = (uint8_t)CloudTimeTmp.u16hour;
    pStTimeDivisionElecPrice->stValleyPeriod.stPeriod3.u8StartMin = (uint8_t)CloudTimeTmp.u16minute;

    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16Valley3EndTime); //0x008C 峰谷模式/谷段3结束时分
    pStTimeDivisionElecPrice->stValleyPeriod.stPeriod3.u8EndHour = (uint8_t)CloudTimeTmp.u16hour;
    pStTimeDivisionElecPrice->stValleyPeriod.stPeriod3.u8EndMin = (uint8_t)CloudTimeTmp.u16minute;   
    /*设置峰谷时间参数，写FLASH*/
    Flash_Device_ElecPriceData_Write(pStTimeDivisionElecPrice,sizeof(Display_SET_Grid_TimeDivisionElecPrice));


    /*定时充电时间获取*/
    Display_SET_System_Strategy* pStStrategy = Display_Get_SystemStrategy();

    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16RegularChar1StartTime);  //0x008D 定时充放电模式/充电时间段1开始时分
    pStStrategy->stTimerStrategy.stChargePeriod.stPeriod1.stPeriod.u8StartHour = (uint8_t)CloudTimeTmp.u16hour;
    pStStrategy->stTimerStrategy.stChargePeriod.stPeriod1.stPeriod.u8StartMin = (uint8_t)CloudTimeTmp.u16minute;

    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16RegularChar1EndTime);   //0x008E 定时充放电模式/充电时间段1结束时分
    pStStrategy->stTimerStrategy.stChargePeriod.stPeriod1.stPeriod.u8EndHour = (uint8_t)CloudTimeTmp.u16hour;
    pStStrategy->stTimerStrategy.stChargePeriod.stPeriod1.stPeriod.u8EndMin = (uint8_t)CloudTimeTmp.u16minute;

    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16RegularChar2StartTime);   //0x008F 定时充放电模式/充电时间段2开始时分
    pStStrategy->stTimerStrategy.stChargePeriod.stPeriod2.stPeriod.u8StartHour = (uint8_t)CloudTimeTmp.u16hour;
    pStStrategy->stTimerStrategy.stChargePeriod.stPeriod2.stPeriod.u8StartMin = (uint8_t)CloudTimeTmp.u16minute;

    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16RegularChar2EndTime);    //0x0090 定时充放电模式/充电时间段2结束时分
    pStStrategy->stTimerStrategy.stChargePeriod.stPeriod2.stPeriod.u8EndHour = (uint8_t)CloudTimeTmp.u16hour;
    pStStrategy->stTimerStrategy.stChargePeriod.stPeriod2.stPeriod.u8EndMin = (uint8_t)CloudTimeTmp.u16minute;

    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16RegularChar3StartTime);  //0x0091 定时充放电模式/充电时间段3开始时分
    pStStrategy->stTimerStrategy.stChargePeriod.stPeriod3.stPeriod.u8StartHour = (uint8_t)CloudTimeTmp.u16hour;
    pStStrategy->stTimerStrategy.stChargePeriod.stPeriod3.stPeriod.u8StartMin = (uint8_t)CloudTimeTmp.u16minute;

    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16RegularChar3EndTime);   //0x0092 定时充放电模式/充电时间段3结束时分
    pStStrategy->stTimerStrategy.stChargePeriod.stPeriod3.stPeriod.u8EndHour = (uint8_t)CloudTimeTmp.u16hour;
    pStStrategy->stTimerStrategy.stChargePeriod.stPeriod3.stPeriod.u8EndMin = (uint8_t)CloudTimeTmp.u16minute;

    /*定时放电时间获取*/
    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16RegularDisChar1StartTime);  //0x0093 定时充放电模式/放电时间段1开始时分
    pStStrategy->stTimerStrategy.stDisChargePeriod.stPeriod1.stPeriod.u8StartHour = (uint8_t)CloudTimeTmp.u16hour;
    pStStrategy->stTimerStrategy.stDisChargePeriod.stPeriod1.stPeriod.u8StartMin = (uint8_t)CloudTimeTmp.u16minute;

    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16RegularDisChar1EndTime);   //0x0094 定时充放电模式/放电时间段1结束时分
    pStStrategy->stTimerStrategy.stDisChargePeriod.stPeriod1.stPeriod.u8EndHour = (uint8_t)CloudTimeTmp.u16hour;
    pStStrategy->stTimerStrategy.stDisChargePeriod.stPeriod1.stPeriod.u8EndMin = (uint8_t)CloudTimeTmp.u16minute;

    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16RegularDisChar2StartTime);   //0x0095 定时充放电模式/放电时间段2开始时分
    pStStrategy->stTimerStrategy.stDisChargePeriod.stPeriod2.stPeriod.u8StartHour = (uint8_t)CloudTimeTmp.u16hour;
    pStStrategy->stTimerStrategy.stDisChargePeriod.stPeriod2.stPeriod.u8StartMin = (uint8_t)CloudTimeTmp.u16minute;

    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16RegularDisChar2EndTime);    //0x0096 定时充放电模式/放电时间段2结束时分
    pStStrategy->stTimerStrategy.stDisChargePeriod.stPeriod2.stPeriod.u8EndHour = (uint8_t)CloudTimeTmp.u16hour;
    pStStrategy->stTimerStrategy.stDisChargePeriod.stPeriod2.stPeriod.u8EndMin = (uint8_t)CloudTimeTmp.u16minute;

    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16RegularDisChar3StartTime);  //0x0097 定时充放电模式/放电时间段3开始时分
    pStStrategy->stTimerStrategy.stDisChargePeriod.stPeriod3.stPeriod.u8StartHour = (uint8_t)CloudTimeTmp.u16hour;
    pStStrategy->stTimerStrategy.stDisChargePeriod.stPeriod3.stPeriod.u8StartMin = (uint8_t)CloudTimeTmp.u16minute;

    memset(&CloudTimeTmp, 0, sizeof(CloudTime_t));
    CloudTimeTmp = GetConvertCloudInputTime(tInternalCloudData.Register10H_t.tEmsStrategyTime.u16RegularDisChar3EndTime);   //0x0098 定时充放电模式/放电时间段3结束时分
    pStStrategy->stTimerStrategy.stDisChargePeriod.stPeriod3.stPeriod.u8EndHour = (uint8_t)CloudTimeTmp.u16hour;
    pStStrategy->stTimerStrategy.stDisChargePeriod.stPeriod3.stPeriod.u8EndMin = (uint8_t)CloudTimeTmp.u16minute;
    /*设置定时充放电策略，写FLASH*/
    Flash_Device_StrategyData_Write(pStStrategy,sizeof(Display_SET_System_Strategy));
    return;
}



/***********************************************************************************************************************
 功能：设置起始地址对应的英臻云平台协议功能码10H的数据结构地址
************************************************************************************************************************/
void SetComDataToCloud_10H(MBRTUFrame_t* ptMBFrame)
{
    if ((EMS_TO_CLOUD_10H_SYS_PARAM_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        GetCloudInputSysParamTimeSet();
    }
    else if ((EMS_TO_CLOUD_10H_PV_CTRL_PARAM_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_10H_PV_CTRL_PARAM_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        GetCloudInputPvCtrlParamSet();
    }
    else if ((EMS_TO_CLOUD_10H_BAT_SET_PARAM_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_10H_BAT_SET_PARAM_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        GetCloudBatteryDataSet();
    }
    else if ((EMS_TO_CLOUD_10H_INV_CTRL_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_10H_INV_CTRL_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        GetCloudInputInvCtrlParamSet();
    }
    else if ((EMS_TO_CLOUD_10H_GEN_PARAM_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_10H_GEN_PARAM_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        GetCloudInputGenParamSet();
    }
    else if ((EMS_TO_CLOUD_10H_STRATEGY_TIME_PARAM_START <= (ptMBFrame->u16MBStartRegsAddr)) && (EMS_TO_CLOUD_10H_STRATEGY_TIME_PARAM_END >= (ptMBFrame->u16MBStartRegsAddr)))
    {
        GetCloudInputTPFVTimeSet();
    }
    else
    {
        ;
    }
    return;

}

#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

