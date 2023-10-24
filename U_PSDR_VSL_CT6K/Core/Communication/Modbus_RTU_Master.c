/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
文件 : Modbus_RTU_Master.c 
 用途 : Modbus RTU协议主机相关功能
***********************************************************************************************************************/
#ifndef MODBUS_RTU_MASTER_C_
#define MODBUS_RTU_MASTER_C_

#include "Modbus_RTU_Master.h"
#include "NTC_DRM_Service.h"

extern uint8_t u8UartTxBuffer[DEV_ID_MAX][DEV_TX_BUFF_SIZE];    //发送缓冲区
extern uint8_t u8UartRxBuffer[DEV_ID_MAX][DEV_RX_BUFF_SIZE];    //接收缓冲区

extern DisplaySystem gDisplay;                                  //Display数据结构全局变量

#if MODBUS_RTU_MASTER_MOUDLE

/*************************************************************************************************************
功能：主机RTU模式模块全局变量初始化
*************************************************************************************************************/
void MB_Master_RTU_InitVar(void)
{

}

/***********************************************************************************************************************
 功能：主机RTU模式发送参数的写入
************************************************************************************************************************/
void MB_Master_Transmit_RTU_Prepare(uint8_t u8Addr,uint8_t u8FuncCode,uint16_t u8StartRegs,uint16_t u8NumRegs,MBRTUFrame_t* ptMBFrame)
{
    ptMBFrame->u8MBAddress = u8Addr;
    ptMBFrame->u8FunctionCode = u8FuncCode;
    ptMBFrame->u16MBStartRegsAddr =u8StartRegs;
    ptMBFrame->u16MBRegsNum =u8NumRegs;
}

/***********************************************************************************************************************
 功能：主机RTU模式的数据转移
************************************************************************************************************************/
void MB_Master_RTU_Retransmit(MBRTUFrame_t* ptMBRTUFrame1,MBRTUFrame_t* ptMBRTUFrame2)
{
    ptMBRTUFrame2->u8FunctionCode = ptMBRTUFrame1->u8FunctionCode;
    ptMBRTUFrame2->u8MBAddress = ptMBRTUFrame1->u8MBAddress;
    ptMBRTUFrame2->u16MBStartRegsAddr = ptMBRTUFrame1->u16MBStartRegsAddr;
    ptMBRTUFrame2->u16MBRegsNum = ptMBRTUFrame1->u16MBRegsNum;
    ptMBRTUFrame2->u8MBBytesNum = ptMBRTUFrame1->u8MBBytesNum;
    ptMBRTUFrame2->u8ErrorCode = ptMBRTUFrame1->u8ErrorCode;
}

/***********************************************************************************************************************
 功能：BMS的数据转移
************************************************************************************************************************/
void MB_Master_BMS_Retransmit(MBRTUFrame_t* ptMBRTUFrame2,InternalComData_t *ptInternalComData)
{
    ptMBRTUFrame2->u8FunctionCode = MB_FUNC_WRITE_MULTIPLE_REGISTERS;
    ptMBRTUFrame2->u8MBAddress = DEV_ID_PCS;
    ptMBRTUFrame2->u16MBStartRegsAddr = EMS_TO_PCS_03H10H_BMS_0x2F03;
    ptMBRTUFrame2->u16MBRegsNum = EMS_TO_PCS_03H10H_BMS_Length;

    switch (BmsComWayType)
    {
    	case BMS_LI_ION_CAN:
            switch(MBBmsProtocolType)
            {
                case BMS_MANU_Pylon:
                    ptInternalComData->Register10H_t.tEmsParam.u16BmsVolt = tBmsCanDataPylon.AnalogQuantity.s16AvgVolt /10;
                    ptInternalComData->Register10H_t.tEmsParam.u16EmsMaxChgCurr = tBmsCanDataPylon.OperationLimit.s16ChgCurrLimit;
                    ptInternalComData->Register10H_t.tEmsParam.u16EmsMaxDisChgCurr = tBmsCanDataPylon.OperationLimit.s16DischgCurrLimit;
                    ptInternalComData->Register10H_t.tEmsParam.u16EmsLiveSOC = tBmsCanDataPylon.SOCandSOH.u16AvgSOC;
                    break;
                case BMS_MANU_CVTE:
                    ;
                    break;
                default:
                    break;
            }
    		break;
    	case BMS_LI_ION_485:
            switch(MBBmsProtocolType)
            {
                case BMS_MANU_Pylon:
                    ptInternalComData->Register10H_t.tEmsParam.u16BmsVolt = tBmsDataPylon.tBmsPylonAnalogInfo.u16SystemAvgVolt;
                    ptInternalComData->Register10H_t.tEmsParam.u16EmsMaxChgCurr = tBmsDataPylon.tBmsPylonMutualInfo.s16MaxChgCurr;
                    ptInternalComData->Register10H_t.tEmsParam.u16EmsMaxDisChgCurr = tBmsDataPylon.tBmsPylonMutualInfo.s16MaxDischgCurr;
                    ptInternalComData->Register10H_t.tEmsParam.u16EmsLiveSOC = tBmsDataPylon.tBmsPylonAnalogInfo.u16SystemSOC;
                    break;
                case BMS_MANU_CVTE:
                    ;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}
/***********************************************************************************************************************
 功能：Meter的数据转移
************************************************************************************************************************/
void MB_Master_Meter_Retransmit(MBRTUFrame_t* ptMBRTUFrame2,InternalComData_t *ptInternalComData)
{
    ptMBRTUFrame2->u8FunctionCode = MB_FUNC_WRITE_MULTIPLE_REGISTERS;
    ptMBRTUFrame2->u8MBAddress = MB_SLAVE_LOCAL_ADDR;
    ptMBRTUFrame2->u16MBStartRegsAddr = PCS_03H_10H_METER_START;
    ptMBRTUFrame2->u16MBRegsNum = PCS_03H_10H_METER_LENGTH;

    ptInternalComData->Register0310H_t.tMeterInfo.s16InstantTotalWatt = tUnifiedMeterData.sInstantTotalWatt;
    ptInternalComData->Register0310H_t.tMeterInfo.s16InstantTotalVar = tUnifiedMeterData.sInstantTotalVar;
    ptInternalComData->Register0310H_t.tMeterInfo.s16InstantTotalVA = tUnifiedMeterData.sInstantTotalVA;
    ptInternalComData->Register0310H_t.tMeterInfo.u16GridFreq = tUnifiedMeterData.u32GridFreq / 10;
    ptInternalComData->Register0310H_t.tMeterInfo.u16TotalPF = tUnifiedMeterData.u32TotalPF / 10;
    ptInternalComData->Register0310H_t.tMeterInfo.s16PhaseAVolt = tUnifiedMeterData.s32PhaseAVolt / 100;
    ptInternalComData->Register0310H_t.tMeterInfo.s16PhaseACurr = tUnifiedMeterData.s32PhaseACurr /100;
}

/***********************************************************************************************************************
 功能：温度和通讯状态的数据转移
************************************************************************************************************************/
void MB_Master_TEMP_COM_Retransmit(MBRTUFrame_t* ptMBRTUFrame2,InternalComData_t *ptInternalComData)
{
    Display_EnableDetection_Status pEnableDetection;
    Temperature_Real_t tTemperature;
    Display_Version pVersion;

    ptMBRTUFrame2->u8FunctionCode = MB_FUNC_WRITE_MULTIPLE_REGISTERS;
    ptMBRTUFrame2->u8MBAddress = MB_SLAVE_LOCAL_ADDR;
    ptMBRTUFrame2->u16MBStartRegsAddr = EMS_TO_PCS_03H10H_TEMP_0x2630;
    ptMBRTUFrame2->u16MBRegsNum = EMS_TO_PCS_03H10H_TEMP_Length;

    Get_NTC_Para(&tTemperature);
    ptInternalComData->Register0310H_t.tSysInfo.s16AmbientTemp = tTemperature.s16AmbientTemperatureReal;
    ptInternalComData->Register0310H_t.tSysInfo.s16INVTemp = tTemperature.s16INVTemperatureReal;
    ptInternalComData->Register0310H_t.tSysInfo.s16BatTemp = tTemperature.s16DCDCTemperatureReal;

    Display_Get_EnableDetection(&pEnableDetection);
    if(pEnableDetection.bControlWay == STATUS_FALSE)
    {
        ptInternalComData->Register0310H_t.tSysInfo.EmsCommEN_t.Bits.bMeterEn = pEnableDetection.bIsHasMeter;
        ptInternalComData->Register0310H_t.tSysInfo.EmsCommEN_t.Bits.bBMSEn = pEnableDetection.bIsHasBMS;
        ptInternalComData->Register0310H_t.tSysInfo.EmsCommEN_t.Bits.bCTEn = pEnableDetection.bIsHasCT;
    }

    ptInternalComData->Register0310H_t.tSysInfo.EmsCommState_t.Bits.bMeterCommState = tCommStatus.tCommDisconnectFlag.Bits.bEmsToMeterCommStateFlag;
    switch (BmsComWayType)
    {
        case BMS_LI_ION_CAN:
            ptInternalComData->Register0310H_t.tSysInfo.EmsCommState_t.Bits.bBMSCommState = tCommStatus.tCommDisconnectFlag.Bits.bEmsToBmsCanCommStateFlag;
            break;
        case BMS_LI_ION_485:
            ptInternalComData->Register0310H_t.tSysInfo.EmsCommState_t.Bits.bBMSCommState = tCommStatus.tCommDisconnectFlag.Bits.bEmsToBmsCommStateFlag; 
            break;
        default:
            break;
    }  
    Display_Get_EMSVersion(&pVersion);
    ptInternalComData->Register0310H_t.tSysInfo.u16ARMVersionV = pVersion.u8Version_V;
    ptInternalComData->Register0310H_t.tSysInfo.u16ARMVersionB = pVersion.u8Version_B;
    ptInternalComData->Register0310H_t.tSysInfo.u16ARMVersionD = pVersion.u8Version_D;
}


/***********************************************************************************************************************
 功能：主机RTU模式的发送函数
************************************************************************************************************************/
MBErrorCode MB_Master_Transmit_RTU_Frame(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;
    uint8_t  *pu8Buf = NULL;
    uint16_t *pu8ObjBuf = NULL;
    uint8_t  u8BytesNum = 0;
    uint8_t  u8BitsNum = 0;
    uint16_t u16CRC16 = 0;
    uint16_t u16Length = 0;
    uint16_t u16RegsNum = 0;
    uint16_t u16CoilsValue = 0;

    GetUsartTxBuf(u8Sciid,&pu8Buf);  //获取发送缓冲区地址信息

    switch (ptMBFrame->u8FunctionCode)
    {
        /*读保持寄存器命令(0x03)：从机地址+功能码0x03+起始地址高位+起始地址低位+寄存器数量高位+寄存器数量低位+CRC低位+CRC高位*/
        case MB_FUNC_READ_HOLDING_REGISTER:
            pu8Buf[u16Length++] = ptMBFrame->u8MBAddress;
            pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode;
            pu8Buf[u16Length++] = ptMBFrame->u16MBStartRegsAddr >> 8;
            pu8Buf[u16Length++] = ptMBFrame->u16MBStartRegsAddr;
            pu8Buf[u16Length++] = ptMBFrame->u16MBRegsNum >> 8;
            pu8Buf[u16Length++] = ptMBFrame->u16MBRegsNum;
            break;
        /*读线圈命令(0x01)：从机地址+功能码0x01+起始地址高位+起始地址低位+输出数量高位+输出数量低位+CRC低位+CRC高位*/
        case MB_FUNC_READ_COILS:
            pu8Buf[u16Length++] = ptMBFrame->u8MBAddress;
            pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode;
            pu8Buf[u16Length++] = ptMBFrame->u16MBStartRegsAddr >> 8;
            pu8Buf[u16Length++] = ptMBFrame->u16MBStartRegsAddr;
            pu8Buf[u16Length++] = ptMBFrame->u16MBRegsNum >> 8;
            pu8Buf[u16Length++] = ptMBFrame->u16MBRegsNum;
            break;
        /*写多个寄存器命令(0x10)：从机地址+功能码0x10+起始地址高位+起始地址低位+数量N高位+数量N低位+字节数2N+[写入数据高位+写入数据低位]+CRC低位+CRC高位*/
        case MB_FUNC_WRITE_MULTIPLE_REGISTERS:
            pu8Buf[u16Length++] = ptMBFrame->u8MBAddress;
            pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode;
            pu8Buf[u16Length++] = ptMBFrame->u16MBStartRegsAddr >> 8;
            pu8Buf[u16Length++] = ptMBFrame->u16MBStartRegsAddr;
            pu8Buf[u16Length++] = ptMBFrame->u16MBRegsNum >> 8;
            pu8Buf[u16Length++] = ptMBFrame->u16MBRegsNum;
            pu8Buf[u16Length++] = 2*(ptMBFrame->u16MBRegsNum);

            pu8ObjBuf = MB_RTU_10H_Register_Index(u8Sciid,ptMBFrame);
            for(u16RegsNum = 0; u16RegsNum < ptMBFrame->u16MBRegsNum; u16RegsNum++)
            {
                pu8Buf[u16Length++] = (*pu8ObjBuf) >> 8;
                pu8Buf[u16Length++] = *pu8ObjBuf;
                pu8ObjBuf++;
            }
            break;
        /*写单个线圈命令(0x05)：从机地址+功能码0x05+起始地址高位+起始地址低位+输出值高位+输出值低位+CRC低位+CRC高位*/
        case MB_FUNC_WRITE_SINGLE_COIL:
            pu8Buf[u16Length++] = ptMBFrame->u8MBAddress;
            pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode;
            pu8Buf[u16Length++] = ptMBFrame->u16MBStartRegsAddr >> 8;
            pu8Buf[u16Length++] = ptMBFrame->u16MBStartRegsAddr;
            pu8ObjBuf = MB_RTU_05H_Register_Index(u8Sciid,ptMBFrame);
            pu8Buf[u16Length++] = (*pu8ObjBuf) >> 8;
            pu8Buf[u16Length++] = *pu8ObjBuf;
            break;
        /*写多个线圈命令(0x0F)：从机地址+功能码0x0F+起始地址高位+起始地址低位+输出数量高位+输出数量低位+字节数+[输出值高位+输出值低位]+CRC低位+CRC高位*/
        case MB_FUNC_WRITE_MULTIPLE_COILS:
            pu8Buf[u16Length++] = ptMBFrame->u8MBAddress;
            pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode;
            pu8Buf[u16Length++] = ptMBFrame->u16MBStartRegsAddr >> 8;
            pu8Buf[u16Length++] = ptMBFrame->u16MBStartRegsAddr;
            pu8Buf[u16Length++] = ptMBFrame->u16MBRegsNum >> 8;
            pu8Buf[u16Length++] = ptMBFrame->u16MBRegsNum;
            pu8Buf[u16Length++] = ptMBFrame->u8MBBytesNum;

            pu8ObjBuf = MB_RTU_0FH_Register_Index(u8Sciid,ptMBFrame);
            for(u8BytesNum = 0; u8BytesNum < (ptMBFrame->u8MBBytesNum); u8BytesNum++)//外部字节数循环
            {
                for (u8BitsNum = 0; u8BitsNum < 8; u8BitsNum++)//内部位数循环
                {
                    u16RegsNum++;
                    if(u16RegsNum <= ptMBFrame->u16MBRegsNum) //判断线圈的数据是否写入完毕
                    {
                        u16CoilsValue += ((*pu8ObjBuf) << u8BitsNum);//将线圈的数据每8位合并为一个字节
                        pu8ObjBuf++;
                    }
                    else
                    {
                        u16CoilsValue += 0;
                    }
                }
                pu8Buf[u16Length++] = u16CoilsValue;
                u16CoilsValue = 0;
            }
            break;
        default:
            break;
    }

    u16CRC16 = ModbusCRC16((uint8_t*)pu8Buf, u16Length);
    pu8Buf[u16Length++] = ( uint8_t )( u16CRC16 & 0xFF );
    pu8Buf[u16Length++] = ( uint8_t )( u16CRC16 >> 8 );
    
    if(u8Sciid != DEV_COM_PORT6_ID)
    {
        pu8Buf[u16Length++] = 0;
        pu8Buf[u16Length++] = 0;
    }
    
    UART_DmaStartTx(u8Sciid, u8UartTxBuffer[u8Sciid] , u16Length);//开启DMA发送
    return eStatus;
}

/***********************************************************************************************************************
 功能：主机RTU模式的解析函数
************************************************************************************************************************/
static MBErrorCode MB_Master_Parsing_RTU_Frame(uint8_t u8Sciid,uint8_t *pu8RxBuf,MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;
    uint16_t *pu8ObjBuf = NULL;
    uint16_t u16RegsNum = 0;
    uint8_t  u8BytesNum = 0;
    uint8_t  u8BitsNum = 0;

    ptMBFrame->u8MBAddress = pu8RxBuf[MB_ADU_ADDR_OFF];
    ptMBFrame->u8FunctionCode = pu8RxBuf[MB_ADU_FUNC_OFF];

    switch(ptMBFrame->u8FunctionCode)
    {
        /*功能码：读线圈0x01*/
        case MB_FUNC_READ_COILS:
        /*判断从机返回的读取字节数和主机查询的字节数是否一致*/
            ptMBFrame ->u8MBBytesNum = GetRegsBytesNum(ptMBFrame);
            if((ptMBFrame ->u8MBBytesNum) == (uint16_t)pu8RxBuf[MB_ADU_S_ADRR_OFF])
            {
                pu8ObjBuf = MB_RTU_01H_Register_Index(u8Sciid,ptMBFrame);
                for(u8BytesNum = 0; u8BytesNum < (ptMBFrame ->u8MBBytesNum); u8BytesNum++)//外部字节数循环
                {
                    for (u8BitsNum = 0; u8BitsNum < 8; u8BitsNum++)//内部位数循环
                    {
                        u16RegsNum++;
                        if(u16RegsNum <= ptMBFrame->u16MBRegsNum)//判断线圈的数据是否写入完毕
                        {
                            *pu8ObjBuf = (pu8RxBuf[u8BytesNum + MB_ADU_03H_DATA_OFF] & (0x01 << u8BitsNum)) >> u8BitsNum;//将数据每8位对应地址放于线圈的结构体中
                            pu8ObjBuf++;
                        }
                        else
                        {
                            ;
                        }
                    }
                }
            }
            else
            {
                ;
            }
            break;
        /*功能码：读寄存器0x03*/
        case MB_FUNC_READ_HOLDING_REGISTER:
        /*判断从机返回的读取数据长度和主机查询的数据长度是否一致*/
            if(2*ptMBFrame->u16MBRegsNum == (uint16_t)pu8RxBuf[MB_ADU_S_ADRR_OFF])
            {
                pu8ObjBuf = MB_RTU_03H_Register_Index(u8Sciid,ptMBFrame);
                for(u16RegsNum = 0; u16RegsNum < (ptMBFrame->u16MBRegsNum); u16RegsNum++)
                {
                    *pu8ObjBuf = MergeData(&pu8RxBuf[MB_ADU_03H_DATA_OFF + u16RegsNum*2]);
                    pu8ObjBuf++;
                }
            }
            break;
        /*功能码：写多个寄存器0x10*/
        case MB_FUNC_WRITE_MULTIPLE_REGISTERS:
            /*判断从机返回的起始地址和数据个数与发送的是否一致*/
            if((ptMBFrame->u16MBStartRegsAddr == (pu8RxBuf[MB_ADU_S_ADRR_OFF] << 8) + pu8RxBuf[MB_ADU_S_ADRR_OFF + 1]) && \
               (ptMBFrame->u16MBRegsNum == (pu8RxBuf[MB_ADU_N_REG_OFF] << 8) + pu8RxBuf[MB_ADU_N_REG_OFF + 1]))
            {
                //电表，温度无需回复debug口，后续需要优化写法
                if((ptMBFrame->u16MBStartRegsAddr == EMS_TO_PCS_03H10H_METER_0x27xx) || (ptMBFrame->u16MBStartRegsAddr == EMS_TO_PCS_03H10H_TEMP_0x2630))
                {
                    WriteMultipleRegsFlag = STATUS_TRUE;  //PCS写入寄存器成功的标志位置1
                }
                else if(ptMBFrame->u16MBStartRegsAddr == EMS_TO_PCS_10H_EMS_PARAM_0x2Fxx)
                {
                    WriteMultipleRegsFlag = STATUS_TRUE;  //PCS写入寄存器成功的标志位置1
                }
                else
                {
                    WriteMultipleRegsFlag = STATUS_TRUE;  //PCS写入寄存器成功的标志位置1
                    Comm2WifiGprs_GetFlag_TxPackage = STATUS_TRUE;
                }
            }
            else
            {
                ;
            }
            break;
        /*功能码：写多个线圈0x0F*/
        case MB_FUNC_WRITE_MULTIPLE_COILS:
            /*判断从机返回的起始地址和数据个数与发送的是否一致*/
            if((ptMBFrame->u16MBStartRegsAddr == (pu8RxBuf[MB_ADU_S_ADRR_OFF] << 8) + pu8RxBuf[MB_ADU_S_ADRR_OFF + 1]) && \
               (ptMBFrame->u16MBRegsNum == (pu8RxBuf[MB_ADU_N_REG_OFF] << 8) + pu8RxBuf[MB_ADU_N_REG_OFF + 1]))
            {
                WriteMultipleCoilsFlag = STATUS_TRUE;  //PCS写多个线圈成功的标志位置1
                Comm2WifiGprs_GetFlag_TxPackage = STATUS_TRUE;
            }
            else
            {
                ;
            }
            break;
        /*功能码：写单个线圈0x05*/
        case MB_FUNC_WRITE_SINGLE_COIL:
        /*判断从机返回的起始地址与发送的是否一致*/
            if(ptMBFrame->u16MBStartRegsAddr == ((pu8RxBuf[MB_ADU_S_ADRR_OFF] << 8) + pu8RxBuf[MB_ADU_S_ADRR_OFF + 1]))
            {
                pu8ObjBuf = MB_RTU_05H_Register_Index(u8Sciid,ptMBFrame); 
                *pu8ObjBuf = MergeData(&pu8RxBuf[MB_ADU_N_REG_OFF]);
                WriteSingleCoilFlag = STATUS_TRUE;  //PCS写单个线圈成功的标志位置1
                Comm2WifiGprs_GetFlag_TxPackage = STATUS_TRUE;
            }
            break;
        /*功能码：异常功能码0x10+0x80*/
        case (MB_FUNC_ERROR + MB_FUNC_WRITE_MULTIPLE_REGISTERS):
            PcsReceiveErrorFlag = STATUS_TRUE;  //置起PCS回复异常功能码的标志位
            ptMBFrame->u8ErrorCode = pu8RxBuf[MB_ADU_S_ADRR_OFF];
            MB_Master_RTU_Retransmit(&gtMBMasterRTUCMDFrame[DEV_ID_PCS],&gtMBSlaveRTUCMDFrame[DEV_ID_WIFI_GPRS]);
            Comm2WifiGprs_GetFlag_TxPackage = STATUS_TRUE;
            break;
        /*功能码：异常功能码0x05+0x80*/
        case (MB_FUNC_ERROR + MB_FUNC_WRITE_SINGLE_COIL):
            PcsReceiveErrorFlag = STATUS_TRUE;  //置起PCS回复异常功能码的标志位
            ptMBFrame->u8ErrorCode = pu8RxBuf[MB_ADU_S_ADRR_OFF];
            MB_Master_RTU_Retransmit(&gtMBMasterRTUCMDFrame[DEV_ID_PCS],&gtMBSlaveRTUCMDFrame[DEV_ID_WIFI_GPRS]);
            Comm2WifiGprs_GetFlag_TxPackage = STATUS_TRUE;
            break;
        /*功能码：异常功能码0x0F+0x80*/
        case (MB_FUNC_ERROR + MB_FUNC_WRITE_MULTIPLE_COILS):
            PcsReceiveErrorFlag = STATUS_TRUE;  //置起PCS回复异常功能码的标志位
            ptMBFrame->u8ErrorCode = pu8RxBuf[MB_ADU_S_ADRR_OFF];
            MB_Master_RTU_Retransmit(&gtMBMasterRTUCMDFrame[DEV_ID_PCS],&gtMBSlaveRTUCMDFrame[DEV_ID_WIFI_GPRS]);
            Comm2WifiGprs_GetFlag_TxPackage = STATUS_TRUE;
            break;
        default:
            break;
    }

    return eStatus;
}

/***********************************************************************************************************************
 功能：主机RTU模式的接收函数
************************************************************************************************************************/
MBErrorCode MB_Master_Receive_RTU_Frame(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;
    uint8_t *pu8Buf = NULL;
    uint16_t u16CRC = 0;
    uint16_t u16Length = 0;

    GetUsartRxBuf(u8Sciid,&pu8Buf);              //获取接收缓冲区地址信息
    u16Length = GetUsartRxBufLength(u8Sciid);    //获取接收缓冲区长度信息
    UART_DmaStartRx(u8Sciid, u8UartRxBuffer[u8Sciid] , DEV_RX_BUFF_SIZE); //开启DMA接收

    u16CRC = pu8Buf[u16Length - MB_ADU_SIZE_CRC]+ (pu8Buf[u16Length - MB_ADU_SIZE_CRC + 1] << 8);  //提取CRC校验位

    /*判断CRC校验是否正确*/
    if(u16CRC != ModbusCRC16((uint8_t*)pu8Buf, u16Length - MB_ADU_SIZE_CRC))
    {
        /*CRC校验错误，返回Error*/
        return MB_CRC_ERR;
    }
    else
    {
        /*CRC校验成功，解析数据*/
        ptMBFrame->u16CRC16 = u16CRC;
        eStatus = MB_Master_Parsing_RTU_Frame(u8Sciid,pu8Buf,ptMBFrame);
        EmsCommunicateConnectFinish(u8Sciid);
    }
    return eStatus;
}

/***********************************************************************************************************************
 功能：电表数据IEEE745协议解码转换
************************************************************************************************************************/
int32_t Hex2Float_IEEE745(uint32_t u32HexData)
{
    int16_t s16IntNum = 0;
    int16_t s16FloatNum = 0;
    int32_t s32FloatData = 0;

    uint8_t u8SignalHex = 0;
    uint16_t u16IntNumHex = 0;

    uint8_t u8FloatBit = 0;

    /*提取HEX整数位*/
    u16IntNumHex = (int16_t)((u32HexData & 0x7F800000) >> 23);
    /*提取HEX符号位*/
    u8SignalHex = u32HexData >> 31;

    /*提取HEX小数位*/
//   u32FloatNumHex10 = (u32HexData & 0x400000) >> 22;  //取第10位
//   u32FloatNumHex11 = (u32HexData & 0x200000) >> 21;  //取第11位
    for(u8FloatBit = 0; u8FloatBit < 23; u8FloatBit++)
    {
        s16FloatNum = ((((u32HexData >> (22 - u8FloatBit)) & 0x00000001) * 10000) >> (u8FloatBit + 1)) + s16FloatNum;
    }
    /*HEX小数位转换为Float小数位，并保留0.01精度，具体计算方法参考IEEE745协议*/
//    s16FloatNum = (int16_t) ((u32FloatNumHex10 * 50)+(u32FloatNumHex11 * 25));  //小数保留0.01
    
    /*HEX小数位转换为Float小数位，并保留0.01精度，具体计算方法参考IEEE745协议*/
    s16IntNum =((100 << (u16IntNumHex - 117)) >> 10);

    if(u8SignalHex == 0)
    {
        s32FloatData = (int32_t)(s16IntNum * (10000 + s16FloatNum)) / 1000;
    }
    else
    {
        s32FloatData = -1 * ((int32_t)(s16IntNum * (10000 + s16FloatNum))) / 1000;
    }
    return s32FloatData;
}


#endif /***Module End***/
#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
