/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : COMMDeal_CVTE.c 
 用途 : 通信处理任务
***********************************************************************************************************************/
#include "CommDeal.h"
#include "NTC_DRM_Service.h"
#include "Storage_Management_Service.h"

#if COM_DEAL_MOUDLE

uint8_t u8MasterRegularSend03H    = 0;  //PCS通讯发送数据包数的计数值
uint8_t u8MasterRegularSendBMS    = 0;  //BMS通讯发送数据包数的计数值
uint8_t u8MasterRegularSendMeter  = 0;  //METER通讯发送数据包数的计数值

CommStatus_TypeDef gEnumEmsToPcsCommStatus         = COMM_STATE_NULL;         //PCS通信模块状态机
CommStatus_TypeDef gEnumEmsToBmsCommStatus         = COMM_STATE_NULL;         //BMS通信模块状态机
CommStatus_TypeDef gEnumEmsToWifiCommStatus        = COMM_STATE_NULL;         //Wifi通信模块状态机
CommStatus_TypeDef gEnumEmsToBLTCommStatus         = COMM_STATE_NULL;         //BLT通信模块状态机
CommStatus_TypeDef gEnumEmsToDebugCommStatus       = COMM_STATE_NULL;         //Debug通信模块状态机
CommStatus_TypeDef gEnumEmsToMeterCommStatus       = COMM_STATE_NULL;         //Meter通信模块状态机
CommStatus_TypeDef gEnumEmsToBmsCanCommStatus      = COMM_STATE_NULL;         //BMSCAN通信模块状态机
CommStatus_TypeDef gEnumEmsToEmsCanCommStatus      = COMM_STATE_NULL;         //EMS并机通信模块状态机

/*************************************************************************************************************
功能：通信处理模块全局变量初始化
*************************************************************************************************************/
void Comm_Module_InitVar(void)
{
    MBBmsProtocolType = BMS_MANU_Pylon;                 //初始化协议为派能协议

    gEnumEmsToPcsCommStatus       = COMM_INIT;          //初始化PCS通讯模块
    gEnumEmsToBmsCommStatus       = COMM_INIT;          //初始化Bms通讯模块
    gEnumEmsToWifiCommStatus      = COMM_INIT;          //初始化Wifi通讯模块
    gEnumEmsToBLTCommStatus       = COMM_INIT;          //初始化Blt通讯模块
    gEnumEmsToDebugCommStatus     = COMM_INIT;          //初始化Debug通讯模块
    gEnumEmsToMeterCommStatus     = COMM_INIT;          //初始化Meter通讯模块
    gEnumEmsToBmsCanCommStatus    = COMM_INIT;          //初始化BmsCan通讯模块
    gEnumEmsToEmsCanCommStatus    = COMM_INIT;          //初始化EMS并机通讯模块
    
    DEV_COM_PORT1_SELECT_PCS();                         //选通PCS通讯
    DEV_COM_BMS_RS485_RX_EN();                          //使BMS口的485通讯处于接收状态
    DEV_COM_WIFI_RS485_RX_EN();                         //使WIFI口的485通讯处于接收状态
    DEV_COM_AFCI_RS485_RX_EN();                         //使AFCI口的485通讯处于接收状态
    DEV_COM_METER_RS485_RX_EN();                        //使METER口的485通讯处于接收状态
}

/*************************************************************************************************************
功能：初始化读取存储的校准系数并下发给PCS
*************************************************************************************************************/
static void AdjustParamInit(void)
{
    TotalSampleAdjData_t tTotalSampleAdjData;
    memset(&tTotalSampleAdjData,0,sizeof(tTotalSampleAdjData));

    Flash_Device_SampleAdjData_Read(&tTotalSampleAdjData, sizeof(TotalSampleAdjData_t));
    memcpy(&tInternalComData.Register0310H_t.tInvStdParam,&tTotalSampleAdjData,sizeof(InvStdParam_t));
    externalSetFlag.Bits.bInvAdjParaFlag = STATUS_TRUE;
}

/*************************************************************************************************************
功能：初始化读取存储的序列号
*************************************************************************************************************/
static void SerialNumberInit(void)
{
    uint8_t i= 0;
    uint8_t SerialArray[SERIAL_BYTES];
    uint16_t SerialNumber[SERIAL_NUMS];
    Flash_Device_EESerialNumber_Read(SerialArray,SERIAL_BYTES);

    for (i = 0; i < SERIAL_NUMS; i++)
    {
        SerialNumber[i] = (SerialArray[2*i] << 8)+ SerialArray[2*i + 1];
    }
    memcpy(tInternalComData.Register0310H_t.tSysInfo.tSerialNum,SerialNumber,sizeof(SerialNumber));
}

/*************************************************************************************************************
功能：初始化读取存储的机型号
*************************************************************************************************************/
static void ModelCodeInit(void)
{
    uint8_t i= 0;
    uint8_t ModelArray[MODEL_BYTES];
    uint16_t ModelCode[MODEL_NUMS];
    Flash_Device_HardwareVersion_Read(ModelArray,MODEL_BYTES);

    for (i = 0; i < MODEL_NUMS; i++)
    {
       ModelCode[i] = (ModelArray[2*i] << 8) + ModelArray[2*i + 1];
    }
    memcpy(tInternalComData.Register0310H_t.tSysInfo.tModelCode,ModelCode,sizeof(ModelCode));
}

/*************************************************************************************************************
功能：Pcs通信模块初始化函数
*************************************************************************************************************/
static void EmsToPcsCommInit(void)
{
    AdjustParamInit();      //校准系数初始化读取存储值
    SerialNumberInit();     //序列号初始化读取存储值
    ModelCodeInit();        //机型号初始化读取存储值

    /*通讯部分版本号的绑定*/
    Display_Version pVersion;
    Display_Get_EMSVersion(&pVersion);
    tInternalComData.Register0310H_t.tSysInfo.u16ARMVersionV = pVersion.u8Version_V;
    tInternalComData.Register0310H_t.tSysInfo.u16ARMVersionB = pVersion.u8Version_B;
    tInternalComData.Register0310H_t.tSysInfo.u16ARMVersionD = pVersion.u8Version_D;
}

/*************************************************************************************************************
功能：Bms通信模块初始化函数
*************************************************************************************************************/
static void EmsToBmsCommInit(void)
{
    ;
}

/*************************************************************************************************************
功能：Wifi通信模块初始化函数
*************************************************************************************************************/
static void EmsToWifiCommInit(void)
{

}

/*************************************************************************************************************
功能：蓝牙通信模块初始化函数
*************************************************************************************************************/
static void EmsToBluetoothCommInit(void)
{
    ;
}

/*************************************************************************************************************
功能：Debug通信模块初始化函数
*************************************************************************************************************/
static void EmsToDebugCommInit(void)
{
    ;
}

/*************************************************************************************************************
功能：电表通信模块初始化函数
*************************************************************************************************************/
static void EmsToMeterCommInit(void)
{
    ;
}

/*************************************************************************************************************
功能：BmsCan通信模块初始化函数
*************************************************************************************************************/
static void EmsToBmsCanCommInit(void)
{
    ;
}

/*************************************************************************************************************
功能：Ems并机通信模块初始化函数
*************************************************************************************************************/
static void EmsToEmsCanCommInit(void)
{
    ;
}

/*************************************************************************************************************
功能：EMS与PCS通信发送服务函数
*************************************************************************************************************/
static void Comm2Pcs_Send_Service(void)
{
    if (TimeTask_GetFlag_100ms == STATUS_FALSE) //定时1s的标志位未置1时
    {
        return;
    }

    if(externalSetFlag.u16word != STATUS_FALSE)
    {
        if(externalSetFlag.Bits.bEnergyManageSetFlag == STATUS_TRUE) //能量管理信息下设
        {
            externalSetFlag.Bits.bEnergyManageSetFlag = STATUS_FALSE;
            MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_WRITE_MULTIPLE_REGISTERS,EMS_TO_PCS_10H_EMS_PARAM_0x2Fxx,PCS_10H_EMS_PARAM_LENGTH,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
            MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
        }
        else if(externalSetFlag.Bits.bPowerOnOffSetFlag == STATUS_TRUE) //启停控制信息下设
        {
            externalSetFlag.Bits.bPowerOnOffSetFlag = STATUS_FALSE;
            MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_WRITE_SINGLE_COIL,EMS_TO_PCS_05H_DATA_0x02xx,EMS_TO_PCS_Set_SingleReg_Length,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
            MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
        }
        else if(externalSetFlag.Bits.bGridStandardSetFlag == STATUS_TRUE) //并网标准信息下设
        {
            externalSetFlag.Bits.bGridStandardSetFlag = STATUS_FALSE;
            MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_WRITE_MULTIPLE_REGISTERS,EMS_TO_PCS_10H_SR_INFO_0x28xx,PCS_10H_SR_LENGTH,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
            MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
        }
        else if(externalSetFlag.Bits.bReactivePowerFlag == STATUS_TRUE) //无功功率下设
        {
            externalSetFlag.Bits.bReactivePowerFlag = STATUS_FALSE;
            MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_WRITE_MULTIPLE_REGISTERS,EMS_TO_PCS_10H_ACTIVE_POWER_0x2F02,EMS_TO_PCS_Set_SingleReg_Length,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
            MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
        }
        else if(externalSetFlag.Bits.bPowerFactorFlag == STATUS_TRUE) //功率因数下设
        {
            externalSetFlag.Bits.bPowerFactorFlag = STATUS_FALSE;
            MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_WRITE_MULTIPLE_REGISTERS,EMS_TO_PCS_10H_POWER_FACTOR_0x2F13,EMS_TO_PCS_Set_SingleReg_Length,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
            MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
        }
        else if(externalSetFlag.Bits.bInvAdjParaFlag == STATUS_TRUE) //校准系数下设
        {
            externalSetFlag.Bits.bInvAdjParaFlag = STATUS_FALSE;
            MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_WRITE_MULTIPLE_REGISTERS,EMS_TO_PCS_03H10H_INV_STD_0x2Exx,PCS_03H_10H_INV_STD_LENGTH,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
            MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
        }
        else
        {
            ;
        }
    }
    else if(Comm2Pcs_GetFlag_TxPackage == STATUS_TRUE) //当EMS与PCS通讯的发送标志位置1时
    {
        MB_Master_RTU_Retransmit(&gtMBSlaveRTUCMDFrame[DEV_ID_WIFI_GPRS],&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);//将从Debug口接收的数据复制到向PCS发送的数据结构中
        MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);//执行与PCS通讯的发送函数
        Comm2Pcs_GetFlag_TxPackage = STATUS_FALSE;//清除EMS与PCS通讯的发送标志位
    }
    else    //内部定时发送
    {
        u8MasterRegularSend03H++;
        switch (u8MasterRegularSend03H)
        {
            case RegularSend100ms:
                MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_HOLDING_REGISTER,EMS_TO_PCS_03H_TOTAL_PARAM_0x10xx,PCS_03H_TOTAL_PARAM_LENGTH,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                break;
            case RegularSend200ms:
                MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_HOLDING_REGISTER,EMS_TO_PCS_03H_PV1_INFO_0x110x,PCS_03H_PV1_INFO_LENGTH,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                break;
            case RegularSend300ms:
                MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_HOLDING_REGISTER,EMS_TO_PCS_03H_PV2_INFO_0x111x,PCS_03H_PV2_INFO_LENGTH,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                break;
            case RegularSend400ms:
                MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_HOLDING_REGISTER,0x1200,0x0020,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                break;
            case RegularSend500ms:
                MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_HOLDING_REGISTER,0x1220,(PCS_03H_INV_INFO_LENGTH - 0x0020),&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                break;
            case RegularSend600ms:
                MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_HOLDING_REGISTER,EMS_TO_PCS_03H_DCDC_INFO_0x13xx,PCS_03H_DCDC_INFO_LENGTH,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                break;
            case RegularSend700ms:
                MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_HOLDING_REGISTER,EMS_TO_PCS_03H10H_PV_CTRL_0x20xx,PCS_03H_10H_PV_CTRL_LENGTH,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                break;
            case RegularSend800ms:
                MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_HOLDING_REGISTER,EMS_TO_PCS_03H10H_INV_CTRL_0x21xx,PCS_03H_10H_INV_CTRL_LENGTH,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                break;
            case RegularSend900ms:
                MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_HOLDING_REGISTER,EMS_TO_PCS_03H10H_DCDC_CTRL_0x22xx,PCS_03H_10H_BAT_CTRL_LENGTH,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                break;
            case RegularSend1000ms:
                MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_HOLDING_REGISTER,EMS_TO_PCS_03H10H_COM_PARAM_0x24xx,PCS_03H_10H_COM_PARAM_LENGTH,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                break;
            case RegularSend1100ms:
                MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_HOLDING_REGISTER,EMS_TO_PCS_03H10H_LINE_VP_0x25xx,PCS_03H_10H_LINE_VP_LENGTH,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                break;
            case RegularSend1200ms:
                MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_HOLDING_REGISTER,EMS_TO_PCS_03H10H_INV_STD_0x2Exx,PCS_03H_10H_INV_STD_LENGTH,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                break;
            case RegularSend1300ms:
                MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_COILS,EMS_TO_PCS_01H_PROT_0x010x,PCS_01H_PROT_LENGTH,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                break;
            case RegularSend1400ms:
                MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_COILS,EMS_TO_PCS_01H_DEBUG_0x013x,PCS_01H_DEBUG_LENGTH,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                break;
            case RegularSend1500ms:
                MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_COILS,EMS_TO_PCS_01H_PROT_EN_0x015x,PCS_01H_PROT_EN_LENGTH,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                break;
            case RegularSend1600ms:
                MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_COILS,EMS_TO_PCS_01H_SYS_CTRL_0x017x,PCS_01H_SYS_CTRL_LENGTH,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                break;
            //Meter 定时发送
            case RegularSend1700ms:
                MB_Master_Meter_Retransmit(&gtMBMasterRTUCMDFrame[DEV_ID_PCS],&tInternalComData);
                MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                break;
            //温度和通讯状态 定时下发
            case RegularSend1800ms:
                MB_Master_TEMP_COM_Retransmit(&gtMBMasterRTUCMDFrame[DEV_ID_PCS],&tInternalComData);
                MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
                u8MasterRegularSend03H = 0;
                break;
#if 0
            //BMS 定时发送
            case RegularSend1600ms:
                MB_Master_BMS_Retransmit(&gtMBMasterRTUCMDFrame[DEV_ID_PCS],&tInternalComData);//向PCS发送的数据结构中写入数据
                MB_Master_Transmit_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);////执行与PCS通讯的发送函数
                break;
#endif
            default:
                break;
        }
    }
}

/*************************************************************************************************************
功能：EMS与PCS通信接收服务函数
*************************************************************************************************************/
static void Comm2Pcs_Receive_Service(void)
{
    if(Comm2Pcs_GetFlag_RxDecode == STATUS_TRUE)
    {
        MB_Master_Receive_RTU_Frame(DEV_ID_PCS,&gtMBMasterRTUCMDFrame[DEV_ID_PCS]);
        Comm2Pcs_GetFlag_RxDecode = STATUS_FALSE;
    }
    else
    {
        EmsCommunicateBreakCheck(DEV_ID_PCS,PcsTimeOutCounter);
    }
}

/*************************************************************************************************************
功能：EMS与BMS_Plyon协议通信发送服务函数
*************************************************************************************************************/
static void MB_Master_Send_ASCII_Plyon_Frame(void)
{
    u8MasterRegularSendBMS++;
    switch (u8MasterRegularSendBMS)
    {
        case RegularSend100ms:
            MB_Master_Transmit_ASCII_Prepare(MB_FUNC_ASCII_PYLON_61H,&gtMBMasterASCIICMDFrame[DEV_ID_BMS]);
            MB_Master_Transmit_ASCII_Frame(DEV_ID_BMS,&gtMBMasterASCIICMDFrame[DEV_ID_BMS]);
            break;
        case RegularSend200ms:
            MB_Master_Transmit_ASCII_Prepare(MB_FUNC_ASCII_PYLON_62H,&gtMBMasterASCIICMDFrame[DEV_ID_BMS]);
            MB_Master_Transmit_ASCII_Frame(DEV_ID_BMS,&gtMBMasterASCIICMDFrame[DEV_ID_BMS]);
            break;
        case RegularSend300ms:
            MB_Master_Transmit_ASCII_Prepare(MB_FUNC_ASCII_PYLON_63H,&gtMBMasterASCIICMDFrame[DEV_ID_BMS]);
            MB_Master_Transmit_ASCII_Frame(DEV_ID_BMS,&gtMBMasterASCIICMDFrame[DEV_ID_BMS]);
            u8MasterRegularSendBMS = 0;
            break;
        default:
            break;
    }
}

/*************************************************************************************************************
功能：EMS与BMS_CVTE协议通信发送服务函数
*************************************************************************************************************/
static void MB_Master_Send_RTU_Cvte_Frame(void)
{
    u8MasterRegularSendBMS++;
    switch (u8MasterRegularSendBMS)
    {
        case RegularSend100ms:
            MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_HOLDING_REGISTER,0x0000,0x0020,&gtMBMasterRTUCMDFrame[DEV_ID_BMS]);//BMS_CVTE版本信息
            MB_Master_Transmit_RTU_Frame(DEV_ID_BMS,&gtMBMasterRTUCMDFrame[DEV_ID_BMS]);
            break;
        case RegularSend200ms:
            MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_HOLDING_REGISTER,0x0020,0x0020,&gtMBMasterRTUCMDFrame[DEV_ID_BMS]);//BMS_CVTE主要信息
            MB_Master_Transmit_RTU_Frame(DEV_ID_BMS,&gtMBMasterRTUCMDFrame[DEV_ID_BMS]);
            break;
        case RegularSend300ms:
            MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_HOLDING_REGISTER,0x0040,0x0020,&gtMBMasterRTUCMDFrame[DEV_ID_BMS]);//BMS_CVTE电压信息
            MB_Master_Transmit_RTU_Frame(DEV_ID_BMS,&gtMBMasterRTUCMDFrame[DEV_ID_BMS]);
            break;
        case RegularSend400ms:
            MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_HOLDING_REGISTER,0x0060,0x0010,&gtMBMasterRTUCMDFrame[DEV_ID_BMS]);//BMS_CVTE温度信息
            MB_Master_Transmit_RTU_Frame(DEV_ID_BMS,&gtMBMasterRTUCMDFrame[DEV_ID_BMS]);
            u8MasterRegularSendBMS = 0;
            break;
        default:
            break;
    }
}

/*************************************************************************************************************
功能：EMS与BMS通信发送服务函数
*************************************************************************************************************/
static void Comm2Bms_Send_Service(void)
{
    if (TimeTask_GetFlag_500ms == STATUS_FALSE)
    {
        return;
    }

    switch(MBBmsProtocolType)
    {
        case BMS_MANU_Pylon:
            MB_Master_Send_ASCII_Plyon_Frame();
            break;
        case BMS_MANU_CVTE:
            MB_Master_Send_RTU_Cvte_Frame();
            break;
        default:
            break;
    }
}

/*************************************************************************************************************
功能：EMS与BMS通信接收服务函数
*************************************************************************************************************/
static void Comm2Bms_Receive_Service(void)
{
    if(Comm2Bms_GetFlag_RxDecode == STATUS_TRUE)
    {
        switch(MBBmsProtocolType)
        {
            case BMS_MANU_Pylon:
                MB_Master_Receive_ASCII_Frame(DEV_ID_BMS,&gtMBMasterASCIICMDFrame[DEV_ID_BMS]);
                break;
            case BMS_MANU_CVTE:
                MB_Master_Receive_RTU_Frame(DEV_ID_BMS,&gtMBMasterRTUCMDFrame[DEV_ID_BMS]);
                break;
            default:
                break;
        }
        Comm2Bms_GetFlag_RxDecode = STATUS_FALSE;
    }
    else
    {
        EmsCommunicateBreakCheck(DEV_ID_BMS,BmsTimeOutCounter);
    }
}

/*************************************************************************************************************
功能：ATE工厂模式EMS与BMS通信发送服务函数
*************************************************************************************************************/
static void Comm2Bms_ATE_Send_Service(void)
{
    if(Comm2Bms_GetFlag_TxPackage == STATUS_TRUE)
    {
        MB_Slave_Response_RTU_Frame(DEV_ID_BMS,&gtMBSlaveRTUCMDFrame[DEV_ID_BMS]);
        Comm2Bms_GetFlag_TxPackage = STATUS_FALSE;
    }
}

/*************************************************************************************************************
功能：ATE工厂模式EMS与BMS通信接收服务函数
*************************************************************************************************************/
static void Comm2Bms_ATE_Receive_Service(void)
{
    if(Comm2Bms_GetFlag_RxDecode == STATUS_TRUE)
    {
        MB_Slave_Receive_RTU_Frame(DEV_ID_BMS,&gtMBSlaveRTUCMDFrame[DEV_ID_BMS]);
        Comm2Bms_GetFlag_RxDecode = STATUS_FALSE;
    }
}

/*************************************************************************************************************
功能：EMS与WIFI/GPRS通信发送服务函数
*************************************************************************************************************/
static void Comm2WifiGprs_Send_Service(void)
{
    if(Comm2WifiGprs_GetFlag_TxPackage == STATUS_TRUE)
    {
        MB_Slave_Response_RTU_Frame(DEV_ID_WIFI_GPRS,&gtMBSlaveRTUCMDFrame[DEV_ID_WIFI_GPRS]);
        Comm2WifiGprs_GetFlag_TxPackage = STATUS_FALSE;
    }
}

/*************************************************************************************************************
功能：EMS与WIFI/GPRS通信接收服务函数
*************************************************************************************************************/
static void Comm2WifiGprs_Receive_Service(void)
{
    if(Comm2WifiGprs_GetFlag_RxDecode == STATUS_TRUE)
    {
        MB_Slave_Receive_RTU_Frame(DEV_ID_WIFI_GPRS,&gtMBSlaveRTUCMDFrame[DEV_ID_WIFI_GPRS]);
        Comm2WifiGprs_GetFlag_RxDecode = STATUS_FALSE;
    }
    else
    {
        EmsCommunicateBreakCheck(DEV_ID_WIFI_GPRS,WifiTimeOutCounter);
    }
}

/*************************************************************************************************************
功能：EMS与蓝牙通信发送服务函数
*************************************************************************************************************/
static void Comm2Bluetooth_Send_Service(void)
{
    ;
}

/*************************************************************************************************************
功能：EMS与蓝牙通信接收服务函数
*************************************************************************************************************/
static void Comm2Bluetooth_Receive_Service(void)
{

}

/*************************************************************************************************************
功能：EMS与外部Debug通信发送服务函数
*************************************************************************************************************/
static void Comm2Debug_Send_Service(void)
{
    if(Comm2Debug_GetFlag_TxPackage == STATUS_TRUE)
    {
        Comm2Debug_GetFlag_TxPackage = STATUS_FALSE;
    }
}

uint16_t BootCheckCnt;

/*************************************************************************************************************
功能：EMS与外部Debug通信接收服务函数
*************************************************************************************************************/
static void Comm2Debug_Receive_Service(void)
{
    uint8_t *pu8Buf = NULL;
    uint16_t u16Length;
    uint16_t i;

    if(Comm2Debug_GetFlag_RxDecode == STATUS_TRUE)
    {
        Comm2Debug_GetFlag_RxDecode = STATUS_FALSE;
        GetUsartRxBuf(DEV_ID_DEBUG,&pu8Buf);              //获取接收缓冲区地址信息
        u16Length = GetUsartRxBufLength(DEV_ID_DEBUG);    //获取接收缓冲区长度信息
        for(i = 0; i < u16Length; i++)
        {
            if(pu8Buf[i] == 0x7F)
            {
                if(BootCheckCnt++ >= 4)
                {
                    BootCheckCnt = 0;
                    NVIC_SystemReset();
                }
            }
            else
            {
                BootCheckCnt = 0;
            }
        }
    }
}

/*************************************************************************************************************
功能：EMS与电表通信发送服务函数
*************************************************************************************************************/
static void Comm2Meter_Send_Service(void)
{
    if (TimeTask_GetFlag_500ms == STATUS_FALSE)
    {
        return;
    }

    u8MasterRegularSendMeter++;
    switch (u8MasterRegularSendMeter)
    {
        case RegularSend100ms:
            MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_HOLDING_REGISTER,0x0000,0x0011,&gtMBMasterRTUCMDFrame[DEV_ID_METER]);
            MB_Master_Transmit_RTU_Frame(DEV_ID_METER,&gtMBMasterRTUCMDFrame[DEV_ID_METER]);
            break;
        case RegularSend200ms:
            MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_HOLDING_REGISTER,0x2000,0x0012,&gtMBMasterRTUCMDFrame[DEV_ID_METER]);
            MB_Master_Transmit_RTU_Frame(DEV_ID_METER,&gtMBMasterRTUCMDFrame[DEV_ID_METER]);
            break;
        case RegularSend300ms:
            MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_HOLDING_REGISTER,0x4000,0x0002,&gtMBMasterRTUCMDFrame[DEV_ID_METER]);
            MB_Master_Transmit_RTU_Frame(DEV_ID_METER,&gtMBMasterRTUCMDFrame[DEV_ID_METER]);
            break;
        case RegularSend400ms:
            MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_HOLDING_REGISTER,0x400A,0x0002,&gtMBMasterRTUCMDFrame[DEV_ID_METER]);
            MB_Master_Transmit_RTU_Frame(DEV_ID_METER,&gtMBMasterRTUCMDFrame[DEV_ID_METER]);
            break;
        case RegularSend500ms:
            MB_Master_Transmit_RTU_Prepare(0x01,MB_FUNC_READ_HOLDING_REGISTER,0x4014,0x0002,&gtMBMasterRTUCMDFrame[DEV_ID_METER]);
            MB_Master_Transmit_RTU_Frame(DEV_ID_METER,&gtMBMasterRTUCMDFrame[DEV_ID_METER]);
            u8MasterRegularSendMeter = 0;
            break;
        default:
            break;
    }
}

/*************************************************************************************************************
功能：EMS与电表通信接收服务函数
*************************************************************************************************************/
static void Comm2Meter_Receive_Service(void)
{
    if(Comm2Meter_GetFlag_RxDecode == STATUS_TRUE)
    {
        MB_Master_Receive_RTU_Frame(DEV_ID_METER,&gtMBMasterRTUCMDFrame[DEV_ID_METER]);
        Comm2Meter_GetFlag_RxDecode = STATUS_FALSE;
        sMeterDataUnified(MB_RTU_DDSU666);
    }
    else
    {
        EmsCommunicateBreakCheck(DEV_ID_METER,MeterTimeOutCounter);
    }
}

/*************************************************************************************************************
功能：ATE工厂模式EMS与电表通信发送服务函数
*************************************************************************************************************/
static void Comm2Meter_ATE_Send_Service(void)
{
    if(Comm2Meter_GetFlag_TxPackage == STATUS_TRUE)
    {
        MB_Slave_Response_RTU_Frame(DEV_ID_METER,&gtMBSlaveRTUCMDFrame[DEV_ID_METER]);
        Comm2Meter_GetFlag_TxPackage = STATUS_FALSE;
    }
}

/*************************************************************************************************************
功能：ATE工厂模式EMS与电表通信接收服务函数
*************************************************************************************************************/
static void Comm2Meter_ATE_Receive_Service(void)
{
    if(Comm2Meter_GetFlag_RxDecode == STATUS_TRUE)
    {
        MB_Slave_Receive_RTU_Frame(DEV_ID_METER,&gtMBSlaveRTUCMDFrame[DEV_ID_METER]);
        Comm2Meter_GetFlag_RxDecode = STATUS_FALSE;
    }
}

/*************************************************************************************************************
功能：EMS与BMSCAN通信发送服务函数
*************************************************************************************************************/
static void Comm2BmsCan_Send_Service(void)
{
    if (TimeTask_GetFlag_1s == STATUS_FALSE)
    {
        return;
    }
    
    BMSCan_SendPacket();
}

/*************************************************************************************************************
功能：EMS与BMS通信接收服务函数
*************************************************************************************************************/
static void Comm2BmsCan_Receive_Service(void)
{
    if (TimeTask_GetFlag_100ms == STATUS_FALSE)
    {
        return;
    }
    if(u8Can1ReceiveFlag == STATUS_TRUE)
    {
        tCommStatus.tCommDisconnectCnt.u8BmsCanDisconnectCnt = 0;
        tCommStatus.tCommDisconnectFlag.Bits.bEmsToBmsCanCommStateFlag = EMS_COMM_NORMAL; 
        BMSCan_ReceivePacket();
    }
    else
    {
        tCommStatus.tCommDisconnectCnt.u8BmsCanDisconnectCnt++;
        if(BmsTimeOutCounter <= tCommStatus.tCommDisconnectCnt.u8BmsCanDisconnectCnt)
        {
            memset(&tBmsCanDataPylon, 0, sizeof (tBmsCanDataPylon));
            tCommStatus.tCommDisconnectFlag.Bits.bEmsToBmsCanCommStateFlag = EMS_COMM_ERROR;       
            tCommStatus.tCommDisconnectCnt.u8BmsCanDisconnectCnt = 0;
        }
    }
}

/*************************************************************************************************************
功能：EMS与EMSCAN通信发送服务函数
*************************************************************************************************************/
static void Comm2EmsCan_Send_Service(void)
{
    if (TimeTask_GetFlag_500ms == STATUS_FALSE)
    {
        return;
    }    
    EMSCan_SendPacket();
}

/*************************************************************************************************************
功能：EMS与BMS通信接收服务函数
*************************************************************************************************************/
static void Comm2EmsCan_Receive_Service(void)
{
    if (TimeTask_GetFlag_500ms == STATUS_FALSE)
    {
        return;
    }
    EMSCan_ReceivePacket();
}

/*************************************************************************************************************
功能：EMS与PCS通信实现函数
*************************************************************************************************************/
void EmsToPcsCommunicateHandler(void)
{
    switch (gEnumEmsToPcsCommStatus)
    {
        case COMM_INIT:                                              //初始化状态
            {
                EmsToPcsCommInit();
                gEnumEmsToPcsCommStatus = COMM_RUNNING;
            }
            break;
        case COMM_RUNNING:                                           //运行状态
            {
                Comm2Pcs_Send_Service();
                Comm2Pcs_Receive_Service();
            }
            break;
        case COMM_DESTRCUCTION:                                      //析构状态
            {
                ;
            }
            break;
        default:
            break;
    }
}

/*************************************************************************************************************
功能：EMS与BMS通信实现函数
*************************************************************************************************************/
void EmsToBmsCommunicateHandler(void)
{
    switch (gEnumEmsToBmsCommStatus)
    {
        case COMM_INIT:                                              //初始化状态
            {
                EmsToBmsCommInit();
                gEnumEmsToBmsCommStatus = COMM_RUNNING;
            }
            break;
        case COMM_RUNNING:                                           //运行状态
            {
                if (tInternalComData.Register010FH_t.tSysCtrlParam.u16FactoryMode == STATUS_FALSE)
                {
                    Comm2Bms_Send_Service();
                    Comm2Bms_Receive_Service();
                }
                else
                {
                    Comm2Bms_ATE_Send_Service();
                    Comm2Bms_ATE_Receive_Service();
                }
            }
            break;
        case COMM_DESTRCUCTION:                                      //析构状态
            {
                ;
            }
            break;
        default:
            break;
    }
}

/*************************************************************************************************************
功能：EMS与WIFI/GPRS通信实现函数
*************************************************************************************************************/
void EmsToWifiGprsCommunicateHandler(void)
{
    switch (gEnumEmsToWifiCommStatus)
    {
        case COMM_INIT:                                              //初始化状态
            {
                EmsToWifiCommInit();
                gEnumEmsToWifiCommStatus = COMM_RUNNING;
            }
            break;
        case COMM_RUNNING:                                           //运行状态
            {
                Comm2WifiGprs_Send_Service();
                Comm2WifiGprs_Receive_Service();
            }
            break;
        case COMM_DESTRCUCTION:                                      //析构状态
            {
                ;
            }
            break;
        default:
            break;
    }
}

/*************************************************************************************************************
功能：EMS与蓝牙通信实现函数
*************************************************************************************************************/
void EmsToBluetoothCommunicateHandler(void)
{
    switch (gEnumEmsToBLTCommStatus)
    {
        case COMM_INIT:                                              //初始化状态
            {
                EmsToBluetoothCommInit();
                gEnumEmsToBLTCommStatus = COMM_RUNNING;
            }
            break;
        case COMM_RUNNING:                                           //运行状态
            {
                Comm2Bluetooth_Send_Service();
                Comm2Bluetooth_Receive_Service();
            }
            break;
        case COMM_DESTRCUCTION:                                      //析构状态
            {
                ;
            }
            break;
        default:
            break;
    }
}

/*************************************************************************************************************
功能：EMS与外部Debug口通信实现函数
*************************************************************************************************************/
void EmsToDebugCommunicateHandler(void)
{
    switch (gEnumEmsToDebugCommStatus)
    {
        case COMM_INIT:                                              //初始化状态
            {
                EmsToDebugCommInit();
                gEnumEmsToDebugCommStatus = COMM_RUNNING;
            }
            break;
        case COMM_RUNNING:                                           //运行状态
            {
                Comm2Debug_Send_Service();
                Comm2Debug_Receive_Service();
            }
            break;
        case COMM_DESTRCUCTION:                                      //析构状态
            {
                ;
            }
            break;
        default:
            break;
    }
}

/*************************************************************************************************************
功能：EMS与电表通信实现函数
*************************************************************************************************************/
void EmsToMeterCommunicateHandler(void)
{
    switch (gEnumEmsToMeterCommStatus)
    {
        case COMM_INIT:                                              //初始化状态
            {
                EmsToMeterCommInit();
                gEnumEmsToMeterCommStatus = COMM_RUNNING;
            }
            break;
        case COMM_RUNNING:                                           //运行状态
            {
                if (tInternalComData.Register010FH_t.tSysCtrlParam.u16FactoryMode == STATUS_FALSE)
                {
                    Comm2Meter_Send_Service();
                    Comm2Meter_Receive_Service();
                }
                else
                {
                    Comm2Meter_ATE_Send_Service();
                    Comm2Meter_ATE_Receive_Service();
                }
            }
            break;
        case COMM_DESTRCUCTION:                                      //析构状态
            {
                ;
            }
            break;
        default:
            break;
    }

#if IO_TEST
    if (STATUS_FALSE == TimeTask_GetFlag_1s) //定时1s的标志位未置1时
    {
        return;
    }

    GPIO_Driver_ToggleOutputPin(GPIOB,GPIO_PIN_11);//LCD.CS1
    GPIO_Driver_ToggleOutputPin(GPIOB,GPIO_PIN_12);//LCD.CS2
    GPIO_Driver_ToggleOutputPin(GPIOE,GPIO_PIN_4);//MasSCI.Control
    GPIO_Driver_ToggleOutputPin(GPIOF,GPIO_PIN_13);//LED.GRID
    GPIO_Driver_ToggleOutputPin(GPIOF,GPIO_PIN_12);//LED.GEN
    GPIO_Driver_ToggleOutputPin(GPIOE,GPIO_PIN_2);//WIFI.TEN
    GPIO_Driver_ToggleOutputPin(GPIOE,GPIO_PIN_3);//METER.TEN
#endif

}

/*************************************************************************************************************
功能：EMS与BMSCAN通信实现函数
*************************************************************************************************************/
void EmsToBmsCanCommunicateHandler(void)
{
    switch (gEnumEmsToBmsCanCommStatus)
    {
        case COMM_INIT:                                              //初始化状态
            {
                EmsToBmsCanCommInit();
                gEnumEmsToBmsCanCommStatus = COMM_RUNNING;
            }
            break;
        case COMM_RUNNING:                                           //运行状态
            {
                Comm2BmsCan_Send_Service();
                Comm2BmsCan_Receive_Service();
            }
            break;
        case COMM_DESTRCUCTION:                                      //析构状态
            {
                ;
            }
            break;
        default:
            break;
    }
}

/*************************************************************************************************************
功能：EMS并机通信实现函数
*************************************************************************************************************/
void EmsToEmsCanCommunicateHandler(void)
{
    switch (gEnumEmsToEmsCanCommStatus)
    {
        case COMM_INIT:                                              //初始化状态
            {
                EmsToEmsCanCommInit();
                gEnumEmsToEmsCanCommStatus = COMM_RUNNING;
            }
            break;
        case COMM_RUNNING:                                           //运行状态
            {
                Comm2EmsCan_Send_Service();
                Comm2EmsCan_Receive_Service();
            }
            break;
        case COMM_DESTRCUCTION:                                      //析构状态
            {
                ;
            }
            break;
        default:
            break;
    }
}

#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
