/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
文件 : Modbus_RTU_Slave.c 
用途 : Modbus协议从机相关功能
***********************************************************************************************************************/
#ifndef MODBUS_RTU_SLAVE_C_
#define MODBUS_RTU_SLAVE_C_

#include "Modbus_RTU_Slave.h"
#include "RTC_Service.h"
#include "Modbus.h"
#include "Storage_Management_Service.h"
#include "Modbus_CLOUD_COMData.h"
#include "LCD_Service.h"

extern uint8_t u8UartTxBuffer[DEV_ID_MAX][DEV_TX_BUFF_SIZE];
extern uint8_t u8UartRxBuffer[DEV_ID_MAX][DEV_RX_BUFF_SIZE];
TimeInf_t TimeSetNum;

#if MODBUS_RTU_SLAVE_MOUDLE

/***********************************************************************************************************************
 功能：从机RTU模式的初始化函数
************************************************************************************************************************/
void MB_Slave_RTU_InitVar(void)
{
    ;
}

/***********************************************************************************************************************
 功能：序列号的防呆码判断和存储函数
************************************************************************************************************************/
static void CheckSerialNumberErrorProof()
{
    uint8_t i = 0;
    uint8_t Errorflag = STATUS_FALSE;
    const uint8_t array[] = PROTECT_CODE;

    uint16_t Temp[SERIAL_NUMS];
    uint8_t SerialNumber[SERIAL_BYTES];

    for(i = 0;i < SERIAL_NUMS; i++)
    {
        Temp[i] = ReverseBytes(tInternalComData.Register0310H_t.tSysInfo.tSerialNum[i]);
    }
    memcpy(SerialNumber,Temp,SERIAL_BYTES);

    for(i = 0;i < PROT_CODE_NUMS;i++)
    {
        if(array[i] != SerialNumber[i])
        {
            Errorflag = STATUS_TRUE;
        }
    }

    if(Errorflag == STATUS_FALSE)
    {
        Flash_Device_EESerialNumber_Write(SerialNumber,SERIAL_BYTES);
    }
    Comm2WifiGprs_GetFlag_TxPackage = STATUS_TRUE;
}

/***********************************************************************************************************************
 功能：硬件号防呆码判断和存储函数
************************************************************************************************************************/
static void CheckModelCodeErrorProof()
{
    uint8_t i = 0;
    uint8_t Errorflag = STATUS_FALSE;
    const uint8_t array[] = PROTECT_CODE;

    uint16_t Temp[MODEL_NUMS];
    uint8_t ModelCode[MODEL_BYTES];

    for(i = 0;i < MODEL_NUMS;i++)
    {
        Temp[i] = ReverseBytes(tInternalComData.Register0310H_t.tSysInfo.tModelCode[i]);
    }
    memcpy(ModelCode,Temp,MODEL_BYTES);

    for(i = 0;i < PROT_CODE_NUMS; i++)
    {
        if(array[i] != ModelCode[i])
        {
            Errorflag = STATUS_TRUE;
        }
    }

    if(Errorflag == STATUS_FALSE)
    {
        Flash_Device_HardwareVersion_Write(ModelCode,MODEL_BYTES);
    }
    Comm2WifiGprs_GetFlag_TxPackage = STATUS_TRUE;

}

/***********************************************************************************************************************
 功能：从机RTU模式的回复函数
************************************************************************************************************************/
MBErrorCode MB_PCS_Slave_Response_RTU_Frame(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;
    uint8_t *pu8Buf = NULL;
    uint16_t *pu8ObjBuf = NULL;
    uint16_t u16CRC16 = 0;
    uint16_t u16Length = 0;
    uint8_t pu8ErrorCode = 0;
    uint8_t u8BytesNum = 0;
    uint8_t u8BitsNum = 0;
    uint16_t u16RegsNum = 0;
    uint16_t u16BytesNumMax = 0;
    uint16_t u16CoilsValue = 0;

    GetUsartTxBuf(u8Sciid,&pu8Buf);  //获取发送缓冲区地址信息

    if(MB_SLAVE_LOCAL_ADDR ==ptMBFrame->u8MBAddress)
    {
        /*判断功能码类别*/
    switch(ptMBFrame->u8FunctionCode)
    {
        /*功能码：写多个寄存器0x10*/
        case MB_FUNC_WRITE_MULTIPLE_REGISTERS:
            /*判断写多个寄存器指令的地址和个数是否越界*/
            if(MB_NO_ERR == (MB_RTU_10H_Range_Check(u8Sciid,ptMBFrame)))
            {
                /*无越界，判断PCS回复成功写多个寄存器的标志位是否置1*/
                if((STATUS_TRUE == WriteMultipleRegsFlag) || 
                   (EMS_TO_PCS_03H10H_SYS_PARAM_0x23xx == (ptMBFrame->u16MBStartRegsAddr & 0xFF00)) ||
                   (EMS_TO_PCS_10H_EMS_CONTROL_0x29xx == ptMBFrame->u16MBStartRegsAddr) ||
                   (EMS_TO_PCS_03H10H_TEMP_0x2634 == ptMBFrame->u16MBStartRegsAddr) ||
                   (EMS_TO_PCS_03H10H_SERIAL_0x2601 == ptMBFrame->u16MBStartRegsAddr) ||
                   (EMS_TO_PCS_03H10H_MODEL_0x2610 == ptMBFrame->u16MBStartRegsAddr))
                {
                    /*0x10正常响应：从机地址+功能码0x10+起始地址高位+起始地址低位+数量高位+数量低位+CRC低位+CRC高位*/
                    pu8Buf[u16Length++] = MB_SLAVE_LOCAL_ADDR;
                    pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode;
                    pu8Buf[u16Length++] = ptMBFrame->u16MBStartRegsAddr >> 8;
                    pu8Buf[u16Length++] = ptMBFrame->u16MBStartRegsAddr;
                    pu8Buf[u16Length++] = ptMBFrame->u16MBRegsNum >> 8;
                    pu8Buf[u16Length++] = ptMBFrame->u16MBRegsNum;
                    WriteMultipleRegsFlag = STATUS_FALSE;  //清除PCS写多个寄存器的标志位
                }
                else
                {
                    return eStatus;
                }
            }
            else
            {
                /*0x10非法数据地址响应：从机地址+(功能码+0x80)+异常码0x02+CRC低位+CRC高位*/
                pu8ErrorCode = MB_ILLEGAL_DATA_ADDRESS;
                pu8Buf[u16Length++] = MB_SLAVE_LOCAL_ADDR;
                pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode +MB_FUNC_ERROR;
                pu8Buf[u16Length++] = pu8ErrorCode;
            }
            break;
        /*功能码：读线圈0x01*/
        case MB_FUNC_READ_COILS:
            /*判断读线圈指令的地址和个数是否越界*/
            if(MB_NO_ERR == (MB_RTU_01H_Range_Check(u8Sciid,ptMBFrame)))
            {
                /*无越界，0x01正常响应：从机地址+功能码0x01+字节数+数据高位+数据低位+CRC低位+CRC高位*/
                pu8Buf[u16Length++] = MB_SLAVE_LOCAL_ADDR;
                pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode;

                u16BytesNumMax = GetRegsBytesNum(ptMBFrame);
                pu8Buf[u16Length++] = u16BytesNumMax;

                pu8ObjBuf = MB_RTU_01H_Register_Index(u8Sciid,ptMBFrame);
                for(u8BytesNum = 0; u8BytesNum < u16BytesNumMax; u8BytesNum++)//字节数循环
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
            }
            else
            {
                /*越界，0x01异常响应：从机地址+(功能码+0x80)+异常码0x02+CRC低位+CRC高位*/
                pu8ErrorCode = MB_ILLEGAL_DATA_ADDRESS;
                pu8Buf[u16Length++] = MB_SLAVE_LOCAL_ADDR;
                pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode + MB_FUNC_ERROR;
                pu8Buf[u16Length++] = pu8ErrorCode;
            }
            break;
        /*功能码：读寄存器0x03*/
        case MB_FUNC_READ_HOLDING_REGISTER:
            /*判断读寄存器指令的地址和个数是否越界*/
            if(MB_NO_ERR == (MB_RTU_03H_Range_Check(u8Sciid,ptMBFrame)))
            {
                /*无越界，0x03正常响应：从机地址+功能码0x03+(2*数据长度)+[数据高位+数据低位]+CRC低位+CRC高位*/
                pu8Buf[u16Length++] = MB_SLAVE_LOCAL_ADDR;
                pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode;
                pu8Buf[u16Length++] = 2*(ptMBFrame->u16MBRegsNum);
                
                pu8ObjBuf = MB_RTU_03H_Register_Index(u8Sciid,ptMBFrame);
                for(u16RegsNum = 0; u16RegsNum < ptMBFrame->u16MBRegsNum; u16RegsNum++)
                {
                    pu8Buf[u16Length++] = (*pu8ObjBuf) >> 8;
                    pu8Buf[u16Length++] = *pu8ObjBuf;
                    pu8ObjBuf++;
                }
            }
            else
            {
                /*越界，0x03异常响应：从机地址+(功能码+0x80)+异常码0x02+CRC低位+CRC高位*/
                pu8ErrorCode = MB_ILLEGAL_DATA_ADDRESS;
                pu8Buf[u16Length++] = MB_SLAVE_LOCAL_ADDR;
                pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode + MB_FUNC_ERROR;
                pu8Buf[u16Length++] = pu8ErrorCode;
            }
            break;
        /*功能码：写单个线圈0x05*/
        case MB_FUNC_WRITE_SINGLE_COIL:
            /*判断写单个线圈指令的地址和个数是否越界*/
            if(MB_NO_ERR == (MB_RTU_05H_Range_Check(u8Sciid,ptMBFrame)))
            {
                /*无越界，判断PCS回复成功写单个线圈的标志位是否置1*/
                if(STATUS_TRUE == WriteSingleCoilFlag)
                {
                    /*0x05正常响应：从机地址+功能码0x05+写入地址高位+写入地址低位+输出值高位+输出值低位+CRC低位+CRC高位*/
                    pu8Buf[u16Length++] = MB_SLAVE_LOCAL_ADDR;
                    pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode;
                    pu8Buf[u16Length++] = ptMBFrame->u16MBStartRegsAddr >> 8;
                    pu8Buf[u16Length++] = ptMBFrame->u16MBStartRegsAddr;
            
                    pu8ObjBuf = MB_RTU_05H_Register_Index(u8Sciid,ptMBFrame); 
                    pu8Buf[u16Length++] = (*pu8ObjBuf) >> 8;
                    pu8Buf[u16Length++] = *pu8ObjBuf;
                    WriteSingleCoilFlag = STATUS_FALSE;    //清除PCS写单个线圈的标志位
                }
                else
                {
                    ;
                }
            }
            else
            {
                /*0x05非法数据地址响应：从机地址+(功能码+0x80)+异常码0x02+CRC低位+CRC高位*/
                pu8ErrorCode = MB_ILLEGAL_DATA_ADDRESS;
                pu8Buf[u16Length++] = MB_SLAVE_LOCAL_ADDR;
                pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode +MB_FUNC_ERROR;
                pu8Buf[u16Length++] = pu8ErrorCode;
            }
            break;
        /*功能码：写多个线圈0x0F*/
        case MB_FUNC_WRITE_MULTIPLE_COILS:
            /*判断写多个线圈指令的地址和个数是否越界*/
            if(MB_NO_ERR == (MB_RTU_0FH_Range_Check(u8Sciid,ptMBFrame)))
            {
                /*无越界，判断PCS回复成功写多个线圈的标志位是否置1*/
                if(STATUS_TRUE == WriteMultipleCoilsFlag)
                {
                    /*0x0F正常响应：从机地址+功能码0x0F+起始地址高位+起始地址低位+输出数量高位+输出数量低位+CRC低位+CRC高位*/
                    pu8Buf[u16Length++] = MB_SLAVE_LOCAL_ADDR;
                    pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode;
                    pu8Buf[u16Length++] = ptMBFrame->u16MBStartRegsAddr >> 8;
                    pu8Buf[u16Length++] = ptMBFrame->u16MBStartRegsAddr;
                    pu8Buf[u16Length++] = ptMBFrame->u16MBRegsNum >> 8;
                    pu8Buf[u16Length++] = ptMBFrame->u16MBRegsNum;
                    WriteMultipleCoilsFlag = STATUS_FALSE; //清除PCS写多个线圈的标志位
                }
                else
                {
                    ;
                }
            }
            else
            {
                /*越界，0x0F异常响应：从机地址+(功能码+0x80)+异常码0x02+CRC低位+CRC高位*/
                pu8ErrorCode = MB_ILLEGAL_DATA_ADDRESS;
                pu8Buf[u16Length++] = MB_SLAVE_LOCAL_ADDR;
                pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode + MB_FUNC_ERROR;
                pu8Buf[u16Length++] = pu8ErrorCode;
            }
            break;
        /*功能码：非法功能码*/
        default:
            if(STATUS_TRUE == PcsReceiveErrorFlag)//PCS回复了异常码的标志位置1
            {
                /*转发PCS侧回复异常码*/
                pu8Buf[u16Length++] = ptMBFrame->u8MBAddress;
                pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode;
                pu8Buf[u16Length++] = ptMBFrame->u8ErrorCode;
                PcsReceiveErrorFlag = STATUS_FALSE;    //清除PCS回复异常码的标志位
            }
            else
            {
                /*非法功能响应：从机地址+(功能码+0x80)+异常码0x01+CRC低位+CRC高位*/
                pu8ErrorCode = MB_ILLEGAL_FUNCTION;
                pu8Buf[u16Length++] = MB_SLAVE_LOCAL_ADDR;
                pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode +MB_FUNC_ERROR;
                pu8Buf[u16Length++] = pu8ErrorCode;
            }
            break;
    }
    }
    if(MB_SLAVE_CLOUD_LOCAL_ADDR ==ptMBFrame->u8MBAddress)
    {
        /*判断功能码类别*/
        switch(ptMBFrame->u8FunctionCode)
        {   
            /*功能码：写多个寄存器0x10*/
            case MB_FUNC_WRITE_MULTIPLE_REGISTERS:
             /*判断写多个寄存器指令的地址和个数是否越界*/
            if(MB_NO_ERR == (MB_RTU_10H_Range_Check(u8Sciid,ptMBFrame)))
            {
            /*0x10正常响应：从机地址+功能码0x10+起始地址高位+起始地址低位+数量高位+数量低位+CRC低位+CRC高位*/
                pu8Buf[u16Length++] = MB_SLAVE_CLOUD_LOCAL_ADDR;
                pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode;
                pu8Buf[u16Length++] = ptMBFrame->u16MBStartRegsAddr >> 8;
                pu8Buf[u16Length++] = ptMBFrame->u16MBStartRegsAddr;
                pu8Buf[u16Length++] = ptMBFrame->u16MBRegsNum >> 8;
                pu8Buf[u16Length++] = ptMBFrame->u16MBRegsNum;
             }
            else
            {
                /*0x10非法数据地址响应：从机地址+(功能码+0x80)+异常码0x02+CRC低位+CRC高位*/
                pu8ErrorCode = MB_ILLEGAL_DATA_ADDRESS;
                pu8Buf[u16Length++] = MB_SLAVE_CLOUD_LOCAL_ADDR;
                pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode +MB_FUNC_ERROR;
                pu8Buf[u16Length++] = pu8ErrorCode;
            }
            break;
            /*功能码：读寄存器0x03*/
            case MB_FUNC_READ_HOLDING_REGISTER:
            case MB_FUNC_READ_INPUT_REGISTER:
            /*判断读寄存器指令的地址和个数是否越界*/
            if(MB_NO_ERR == (MB_RTU_03H_Range_Check(u8Sciid,ptMBFrame)))
            {
            
                pu8Buf[u16Length++] = MB_SLAVE_CLOUD_LOCAL_ADDR;
                pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode;
                pu8Buf[u16Length++] = 2*(ptMBFrame->u16MBRegsNum); 
                pu8ObjBuf = MB_RTU_03H_Register_Index(u8Sciid,ptMBFrame);
                for(u16RegsNum = 0; u16RegsNum < ptMBFrame->u16MBRegsNum; u16RegsNum++)
                {
                    pu8Buf[u16Length++] = (*pu8ObjBuf) >> 8;
                    pu8Buf[u16Length++] = *pu8ObjBuf;
                    pu8ObjBuf++;
                }
            }
            else
            {
                /*越界，0x03异常响应：从机地址+(功能码+0x80)+异常码0x02+CRC低位+CRC高位*/
                pu8ErrorCode = MB_ILLEGAL_DATA_ADDRESS;
                pu8Buf[u16Length++] = MB_SLAVE_CLOUD_LOCAL_ADDR;
                pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode + MB_FUNC_ERROR;
                pu8Buf[u16Length++] = pu8ErrorCode;
            }
            break;
            /*其他功能码暂不处理*/
            default:
                break;
        }
    }
    u16CRC16 = ModbusCRC16((uint8_t*)pu8Buf, u16Length);
    pu8Buf[u16Length++] = ( uint8_t )( u16CRC16 & 0xFF ); //CRC校验码先发低位
    pu8Buf[u16Length++] = ( uint8_t )( u16CRC16 >> 8 );   //CRC校验码再发高位
    pu8Buf[u16Length++] = 0;
    pu8Buf[u16Length++] = 0;

    UART_DmaStartTx(u8Sciid, u8UartTxBuffer[u8Sciid] , u16Length);//开启DMA发送

    return eStatus;
}

/***********************************************************************************************************************
 功能：BMS从机RTU模式的回复函数
************************************************************************************************************************/
static MBErrorCode MB_BMS_Slave_Response_RTU_Frame(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;
    uint8_t *pu8Buf = NULL;
    uint16_t u16CRC16 = 0;
    uint16_t u16Length = 0;

    GetUsartTxBuf(u8Sciid,&pu8Buf);  //获取发送缓冲区地址信息

    pu8Buf[u16Length++] = MB_SLAVE_LOCAL_ADDR;
    pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode;
    pu8Buf[u16Length++] = 2*(ptMBFrame->u16MBRegsNum);
    pu8Buf[u16Length++] = 0;
    pu8Buf[u16Length++] = 0;

    u16CRC16 = ModbusCRC16((uint8_t*)pu8Buf, u16Length);
    pu8Buf[u16Length++] = ( uint8_t )( u16CRC16 & 0xFF ); //CRC校验码先发低位
    pu8Buf[u16Length++] = ( uint8_t )( u16CRC16 >> 8 );   //CRC校验码再发高位
    pu8Buf[u16Length++] = 0;
    pu8Buf[u16Length++] = 0;

    UART_DmaStartTx(u8Sciid, u8UartTxBuffer[u8Sciid] , u16Length);//开启DMA发送

    return eStatus;
}

/***********************************************************************************************************************
 功能：Meter从机RTU模式的回复函数
************************************************************************************************************************/
static MBErrorCode MB_Meter_Slave_Response_RTU_Frame(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;
    uint8_t *pu8Buf = NULL;
    uint16_t u16CRC16 = 0;
    uint16_t u16Length = 0;

    GetUsartTxBuf(u8Sciid,&pu8Buf);  //获取发送缓冲区地址信息

    pu8Buf[u16Length++] = MB_SLAVE_LOCAL_ADDR;
    pu8Buf[u16Length++] = ptMBFrame->u8FunctionCode;
    pu8Buf[u16Length++] = 2*(ptMBFrame->u16MBRegsNum);
    pu8Buf[u16Length++] = 0;
    pu8Buf[u16Length++] = 0;

    u16CRC16 = ModbusCRC16((uint8_t*)pu8Buf, u16Length);
    pu8Buf[u16Length++] = ( uint8_t )( u16CRC16 & 0xFF ); //CRC校验码先发低位
    pu8Buf[u16Length++] = ( uint8_t )( u16CRC16 >> 8 );   //CRC校验码再发高位
    pu8Buf[u16Length++] = 0;
    pu8Buf[u16Length++] = 0;

    UART_DmaStartTx(u8Sciid, u8UartTxBuffer[u8Sciid] , u16Length);//开启DMA发送

    return eStatus;
}

/***********************************************************************************************************************
 功能：BLT从机RTU模式的回复函数
************************************************************************************************************************/
static MBErrorCode MB_BLT_Slave_Response_RTU_Frame(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;


    return eStatus;
}

/***********************************************************************************************************************
 功能：从机RTU模式的回复函数
************************************************************************************************************************/
MBErrorCode MB_Slave_Response_RTU_Frame(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;

    switch (u8Sciid)
    {
        case DEV_ID_PCS:
            eStatus = MB_PCS_Slave_Response_RTU_Frame(u8Sciid,ptMBFrame);
            break;
        case DEV_ID_BMS:
            eStatus = MB_BMS_Slave_Response_RTU_Frame(u8Sciid,ptMBFrame);
            break;
        case DEV_ID_WIFI_GPRS:
            eStatus = MB_PCS_Slave_Response_RTU_Frame(u8Sciid,ptMBFrame);
            break;
        case DEV_ID_BLT:
            eStatus = MB_BLT_Slave_Response_RTU_Frame(u8Sciid,ptMBFrame);
            break;
        case DEV_ID_METER:
            eStatus = MB_Meter_Slave_Response_RTU_Frame(u8Sciid,ptMBFrame);
            break;
        default:
            break;
    }
    return eStatus;
}

/***********************************************************************************************************************
 功能：系统时间校准函数
************************************************************************************************************************/
void MB_Time_Calibrate(TimeInf_t *SetTime,InternalComData_t* ptMBFrame)
{
    SetTime->u16Year = ptMBFrame->Register0310H_t.tSysParam.u16SysYear;        //年
    SetTime->u8Month = ptMBFrame->Register0310H_t.tSysParam.u16SysMonth;       //月
    SetTime->u8Day = ptMBFrame->Register0310H_t.tSysParam.u16SysDay;         //日
    SetTime->u8Hour = ptMBFrame->Register0310H_t.tSysParam.u16SysHour;        //时
    SetTime->u8Min = ptMBFrame->Register0310H_t.tSysParam.u16SysMinute;      //分
    SetTime->u8Sec = ptMBFrame->Register0310H_t.tSysParam.u16SysSecond;      //秒
    SetTime->u8Week = ptMBFrame->Register0310H_t.tSysParam.u16SysWeek;        //周
}

/***********************************************************************************************************************
 功能：PCS从机RTU模式的解析函数
************************************************************************************************************************/
static MBErrorCode MB_PCS_Slave_Parsing_RTU_Frame(uint8_t u8Sciid,uint8_t *pu8RxBuf,MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;
    uint16_t *pu8ObjBuf;
    uint16_t u16RegsNum = 0;
    uint8_t u8BytesNum = 0;
    uint8_t u8BitsNum = 0;
    uint16_t u16Temporary = 0;

    TotalSampleAdjData_t tTotalSampleAdjData;
    memset(&tTotalSampleAdjData,0,sizeof(tTotalSampleAdjData));

    ptMBFrame->u8MBAddress = pu8RxBuf[MB_ADU_ADDR_OFF];
    ptMBFrame->u8FunctionCode = pu8RxBuf[MB_ADU_FUNC_OFF];
    ptMBFrame->u16MBStartRegsAddr = (pu8RxBuf[MB_ADU_S_ADRR_OFF] << 8) + pu8RxBuf[MB_ADU_S_ADRR_OFF + 1];
    ptMBFrame->u16MBRegsNum = (pu8RxBuf[MB_ADU_N_REG_OFF] << 8) + pu8RxBuf[MB_ADU_N_REG_OFF + 1];

    /*debug口通信地址02 */    
    if(MB_SLAVE_LOCAL_ADDR == ptMBFrame->u8MBAddress)
    {
        switch (ptMBFrame->u8FunctionCode)
        {
            /*功能码：写多个寄存器0x10*/
            case MB_FUNC_WRITE_MULTIPLE_REGISTERS:
                /*检查写入数据的地址和个数是否越界*/
                if(MB_NO_ERR == (MB_RTU_10H_Range_Check(u8Sciid,ptMBFrame)))
                {
                    /*写入数据的地址和个数无越界*/
                    pu8ObjBuf = MB_RTU_10H_Register_Index(u8Sciid,ptMBFrame);
                    for(u16RegsNum = 0; u16RegsNum < ptMBFrame->u16MBRegsNum; u16RegsNum++)
                    {
                        *pu8ObjBuf = MergeData(&pu8RxBuf[MB_ADU_10H_DATA_OFF + u16RegsNum*2]);
                        pu8ObjBuf++;
                    }
                    //写入校准时间参数
                    if(EMS_TO_PCS_03H10H_SYS_PARAM_0x23xx == (ptMBFrame->u16MBStartRegsAddr & 0xFF00))
                    {
                        MB_Time_Calibrate(&TimeSetNum, &tInternalComData);
                        Set_SysTime(TimeSetNum);
                        Comm2WifiGprs_GetFlag_TxPackage = STATUS_TRUE;
                    }
                    //写入通讯使能参数
                    else if(EMS_TO_PCS_03H10H_TEMP_0x2634 == ptMBFrame->u16MBStartRegsAddr)
                    {
                        Comm2WifiGprs_GetFlag_TxPackage = STATUS_TRUE;
                    }
                    //写入远程控制使能
                    else if(EMS_TO_PCS_10H_EMS_CONTROL_0x29xx == ptMBFrame->u16MBStartRegsAddr)
                    {
                        u16Temporary = (pu8RxBuf[MB_ADU_0FH_DATA_OFF] << 8) + pu8RxBuf[MB_ADU_0FH_DATA_OFF + 1];
                        Display_Set_ControlWay(u16Temporary);
                        Comm2WifiGprs_GetFlag_TxPackage = STATUS_TRUE;
                    }
                    //写入能量管理参数
                    else if(EMS_TO_PCS_10H_EMS_PARAM_0x2Fxx == (ptMBFrame->u16MBStartRegsAddr & 0xFF00))
                    {
                        return eStatus;
                    }
                    //写入校准系数
                    else if(EMS_TO_PCS_03H10H_INV_STD_0x2Exx == (ptMBFrame->u16MBStartRegsAddr & 0xFF00))
                    {
                        memcpy(&tTotalSampleAdjData,&tInternalComData.Register0310H_t.tInvStdParam,sizeof(InvStdParam_t));
                        Flash_Device_SampleAdjData_Write(&tTotalSampleAdjData, sizeof(TotalSampleAdjData_t));
                        Comm2Pcs_GetFlag_TxPackage = STATUS_TRUE;//置起与PCS通讯的发送标志位
                    }
                    //写入序列号
                    else if(EMS_TO_PCS_03H10H_SERIAL_0x2601 == ptMBFrame->u16MBStartRegsAddr)
                    {
                        CheckSerialNumberErrorProof();
                    }
                    //写入硬件版本号
                    else if(EMS_TO_PCS_03H10H_MODEL_0x2610 == ptMBFrame->u16MBStartRegsAddr)
                    {
                        CheckModelCodeErrorProof();
                    }
                    else
                    {
                        Comm2Pcs_GetFlag_TxPackage = STATUS_TRUE;
                    }
                }
                else
                {
                    /*写入数据的地址和个数越界*/
                    Comm2WifiGprs_GetFlag_TxPackage = STATUS_TRUE;
                }
                break;
            /*功能码：写单个线圈0x05*/
            case MB_FUNC_WRITE_SINGLE_COIL:
                if(MB_NO_ERR == (MB_RTU_05H_Range_Check(u8Sciid,ptMBFrame)))
                {
                    pu8ObjBuf = MB_RTU_05H_Register_Index(u8Sciid,ptMBFrame); 
                    *pu8ObjBuf = MergeData(&pu8RxBuf[MB_ADU_N_REG_OFF]);
                    Comm2Pcs_GetFlag_TxPackage = STATUS_TRUE; 
                }
                else
                {
                    Comm2WifiGprs_GetFlag_TxPackage = STATUS_TRUE;
                }
                break;
            /*功能码：写多个线圈0x0F*/
            case MB_FUNC_WRITE_MULTIPLE_COILS:
                ptMBFrame->u8MBBytesNum = pu8RxBuf[MB_ADU_BYTE_NUM_OFF];
                
                if(MB_NO_ERR == (MB_RTU_0FH_Range_Check(u8Sciid,ptMBFrame)))
                {
                    pu8ObjBuf = MB_RTU_0FH_Register_Index(u8Sciid,ptMBFrame); 
                    for(u8BytesNum = 0; u8BytesNum < (ptMBFrame->u8MBBytesNum); u8BytesNum++)//外部字节数循环
                    {
                        for (u8BitsNum = 0; u8BitsNum < 8; u8BitsNum++)//内部位数循环
                        {
                            u16RegsNum++;
                            if(u16RegsNum <= ptMBFrame->u16MBRegsNum)//判断线圈的数据是否写入完毕
                            {
                                *pu8ObjBuf = (pu8RxBuf[u8BytesNum + MB_ADU_0FH_DATA_OFF] & (0x01 << u8BitsNum)) >> u8BitsNum;//将数据每8位对应地址放于线圈的结构体中
                                pu8ObjBuf++;
                            }
                            else
                            {
                                ;
                            }
                        }
                    }
                    //清除发电量
                    if(EMS_TO_PCS_01H_SYS_CTRL_0x017x == ptMBFrame->u16MBStartRegsAddr)
                    {
                        if(tInternalComData.Register010FH_t.tSysCtrlParam.u16GenerationClr == STATUS_TRUE)
                        {
                            Display_Clear_SystemStatistical();
                        }
                        Comm2Pcs_GetFlag_TxPackage = STATUS_TRUE;
                    }
                    else
                    {
                        Comm2Pcs_GetFlag_TxPackage = STATUS_TRUE;
                    }
                }
                else
                {
                    Comm2WifiGprs_GetFlag_TxPackage = STATUS_TRUE;
                }
                break;
            default:
                Comm2WifiGprs_GetFlag_TxPackage = STATUS_TRUE;
                break;
        }
    }
	/*对接英臻云平台通信地址01 */
    else if(MB_SLAVE_CLOUD_LOCAL_ADDR == ptMBFrame->u8MBAddress)
    {
        switch (ptMBFrame->u8FunctionCode)
        {
            /*功能码：写多个寄存器0x10*/
            case MB_FUNC_WRITE_MULTIPLE_REGISTERS:
                 /*检查写入数据的地址和个数是否越界*/
                if(MB_NO_ERR == (MB_RTU_10H_Range_Check(u8Sciid,ptMBFrame)))
                {
                    /*写入数据的地址和个数无越界*/
                    pu8ObjBuf = MB_RTU_10H_Register_Index(u8Sciid,ptMBFrame);
                    for(u16RegsNum = 0; u16RegsNum < ptMBFrame->u16MBRegsNum; u16RegsNum++)
                    {
                        *pu8ObjBuf = MergeData(&pu8RxBuf[MB_ADU_10H_DATA_OFF + u16RegsNum*2]);
                        pu8ObjBuf++;
                    }
                    SetComDataToCloud_10H(ptMBFrame);
                    Comm2WifiGprs_GetFlag_TxPackage = STATUS_TRUE;                  
                }
                else
                {
                    /*写入数据的地址和个数越界*/
                    Comm2WifiGprs_GetFlag_TxPackage = STATUS_TRUE;
                }
                break;
            /*0x03 读保持寄存器*/
            default:
                Comm2WifiGprs_GetFlag_TxPackage = STATUS_TRUE;
                break;
        }
    }
    else
    {
        /*从机地址错误，返回error*/
        eStatus = MB_SLAVE_ADD_ERROR;
    }
    return eStatus;
}

/***********************************************************************************************************************
 功能：BMS从机RTU模式的解析函数
************************************************************************************************************************/
static MBErrorCode MB_BMS_Slave_Parsing_RTU_Frame(uint8_t u8Sciid,uint8_t *pu8RxBuf,MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;

    ptMBFrame->u8MBAddress = pu8RxBuf[MB_ADU_ADDR_OFF];
    ptMBFrame->u8FunctionCode = pu8RxBuf[MB_ADU_FUNC_OFF];
    ptMBFrame->u16MBStartRegsAddr = (pu8RxBuf[MB_ADU_S_ADRR_OFF] << 8) + pu8RxBuf[MB_ADU_S_ADRR_OFF + 1];
    ptMBFrame->u16MBRegsNum = (pu8RxBuf[MB_ADU_N_REG_OFF] << 8) + pu8RxBuf[MB_ADU_N_REG_OFF + 1];

    /*检查从机地址，目前EMS作为从机的地址固定为01*/
    if(MB_SLAVE_LOCAL_ADDR != ptMBFrame->u8MBAddress)
    {
        /*从机地址错误，返回error*/
        eStatus = MB_SLAVE_ADD_ERROR;
    }
    else
    {
        Comm2Bms_GetFlag_TxPackage = STATUS_TRUE;
    }
    return eStatus;
}

/***********************************************************************************************************************
 功能：Meter从机RTU模式的解析函数
************************************************************************************************************************/
static MBErrorCode MB_Meter_Slave_Parsing_RTU_Frame(uint8_t u8Sciid,uint8_t *pu8RxBuf,MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;

    ptMBFrame->u8MBAddress = pu8RxBuf[MB_ADU_ADDR_OFF];
    ptMBFrame->u8FunctionCode = pu8RxBuf[MB_ADU_FUNC_OFF];
    ptMBFrame->u16MBStartRegsAddr = (pu8RxBuf[MB_ADU_S_ADRR_OFF] << 8) + pu8RxBuf[MB_ADU_S_ADRR_OFF + 1];
    ptMBFrame->u16MBRegsNum = (pu8RxBuf[MB_ADU_N_REG_OFF] << 8) + pu8RxBuf[MB_ADU_N_REG_OFF + 1];

    /*检查从机地址，目前EMS作为从机的地址固定为01*/
    if(MB_SLAVE_LOCAL_ADDR != ptMBFrame->u8MBAddress)
    {
        /*从机地址错误，返回error*/
        eStatus = MB_SLAVE_ADD_ERROR;
    }
    else
    {
        Comm2Meter_GetFlag_TxPackage = STATUS_TRUE;
    }
    return eStatus;
}

/***********************************************************************************************************************
 功能：BLT从机RTU模式的解析函数
************************************************************************************************************************/
static MBErrorCode MB_BLT_Slave_Parsing_RTU_Frame(uint8_t u8Sciid,uint8_t *pu8RxBuf,MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;
    return eStatus;
}

/***********************************************************************************************************************
 功能：从机RTU模式的解析函数
************************************************************************************************************************/
static MBErrorCode MB_Slave_Parsing_RTU_Frame(uint8_t u8Sciid,uint8_t *pu8RxBuf,MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;

    switch (u8Sciid)
    {
        case DEV_ID_PCS:
            eStatus = MB_PCS_Slave_Parsing_RTU_Frame(u8Sciid,pu8RxBuf,ptMBFrame);
            break;
        case DEV_ID_BMS:
            eStatus = MB_BMS_Slave_Parsing_RTU_Frame(u8Sciid,pu8RxBuf,ptMBFrame);
            break;
        case DEV_ID_WIFI_GPRS:
            eStatus = MB_PCS_Slave_Parsing_RTU_Frame(u8Sciid,pu8RxBuf,ptMBFrame);
            break;
        case DEV_ID_BLT:
            eStatus = MB_BLT_Slave_Parsing_RTU_Frame(u8Sciid,pu8RxBuf,ptMBFrame);
            break;
        case DEV_ID_METER:
            eStatus = MB_Meter_Slave_Parsing_RTU_Frame(u8Sciid,pu8RxBuf,ptMBFrame);
            break;
        default:
            break;
    }
    return eStatus;
}

/***********************************************************************************************************************
 功能：从机RTU模式的接收函数
************************************************************************************************************************/
MBErrorCode MB_Slave_Receive_RTU_Frame(uint8_t u8Sciid,MBRTUFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;
    uint16_t u16CRC = 0;
    uint8_t *pu8Buf;
    uint16_t u16Length = 0;

    GetUsartRxBuf(u8Sciid,&pu8Buf);            //获取接收缓冲区地址信息
    u16Length = GetUsartRxBufLength(u8Sciid);  //获取接收缓冲区长度信息
    UART_DmaStartRx(u8Sciid, u8UartRxBuffer[u8Sciid] , DEV_RX_BUFF_SIZE);  //开启DMA接收

    u16CRC = pu8Buf[u16Length - MB_ADU_SIZE_CRC]+ (pu8Buf[u16Length - MB_ADU_SIZE_CRC + 1] << 8); //提取CRC校验位

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
        eStatus = MB_Slave_Parsing_RTU_Frame(u8Sciid,pu8Buf,ptMBFrame);
        EmsCommunicateConnectFinish(u8Sciid);
    }
    return eStatus;
}


#endif /***Module End***/
#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
