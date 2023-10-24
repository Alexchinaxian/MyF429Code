/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
文件 : Modbus_ASCII_Master.c 
 用途 : Modbus ASCII协议主机相关功能
***********************************************************************************************************************/

#ifndef MODBUS_ASCII_MASTER_C_
#define MODBUS_ASCII_MASTER_C_

#include "Modbus_ASCII_Master.h"

extern uint8_t u8UartTxBuffer[DEV_ID_MAX][DEV_TX_BUFF_SIZE];
extern uint8_t u8UartRxBuffer[DEV_ID_MAX][DEV_RX_BUFF_SIZE];

#if MODBUS_ASCII_MASTER_MOUDLE

/***********************************************************************************************************************
 功能：主机ASCII模式发送参数的写入(派能协议)
************************************************************************************************************************/
void MB_Master_Transmit_ASCII_Prepare(uint16_t u16MBCID2,MBASCIIFrame_t* ptMBFrame)
{
    ptMBFrame->u8SOI = 0x7E;
    ptMBFrame->u16Ver = 0x3230;
    ptMBFrame->u16ADR = 0x3132;
    ptMBFrame->u16MBCID1 = 0x3436;
    ptMBFrame->u16MBCID2 = u16MBCID2;
    ptMBFrame->u32Length = 0x45303032;
    ptMBFrame->u16INFO = 0x3132;
    ptMBFrame->u8EOI = 0x0D;
}

/***********************************************************************************************************************
 功能：主机ASCII模式的发送函数(派能协议)
************************************************************************************************************************/
MBErrorCode MB_Master_Transmit_ASCII_Frame(uint8_t u8Sciid,MBASCIIFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;
    uint8_t  *pu8Buf;
    uint16_t u16BinLRC = 0;
    uint16_t u16Length = 0;

    GetUsartTxBuf(u8Sciid,&pu8Buf);  //获取发送缓冲区地址信息

    pu8Buf[u16Length++] = ptMBFrame->u8SOI;
    pu8Buf[u16Length++] = ptMBFrame->u16Ver >> 8;
    pu8Buf[u16Length++] = ptMBFrame->u16Ver;
    pu8Buf[u16Length++] = ptMBFrame->u16ADR >> 8;
    pu8Buf[u16Length++] = ptMBFrame->u16ADR;
    pu8Buf[u16Length++] = ptMBFrame->u16MBCID1 >> 8;
    pu8Buf[u16Length++] = ptMBFrame->u16MBCID1;
    pu8Buf[u16Length++] = ptMBFrame->u16MBCID2 >> 8;
    pu8Buf[u16Length++] = ptMBFrame->u16MBCID2;
    pu8Buf[u16Length++] = ptMBFrame->u32Length >> 24;
    pu8Buf[u16Length++] = ptMBFrame->u32Length >> 16;
    pu8Buf[u16Length++] = ptMBFrame->u32Length >> 8;
    pu8Buf[u16Length++] = ptMBFrame->u32Length;
    pu8Buf[u16Length++] = ptMBFrame->u16INFO >> 8;
    pu8Buf[u16Length++] = ptMBFrame->u16INFO;

    u16BinLRC = ModbusLRC((uint8_t*)(pu8Buf + 1),(u16Length - 1));
    pu8Buf[u16Length++] = ModbusBin2Char((u16BinLRC >> 12) & 0x000F);
    pu8Buf[u16Length++] = ModbusBin2Char((u16BinLRC >> 8) & 0x000F);
    pu8Buf[u16Length++] = ModbusBin2Char((u16BinLRC >> 4) & 0x000F);
    pu8Buf[u16Length++] = ModbusBin2Char(u16BinLRC & 0x000F);
    pu8Buf[u16Length++] = ptMBFrame->u8EOI;
	pu8Buf[u16Length++] = 0;
    pu8Buf[u16Length++] = 0;

    UART_DmaStartTx(u8Sciid, u8UartTxBuffer[u8Sciid] , u16Length);//开启DMA发送
    return eStatus;
}

/***********************************************************************************************************************
 功能：主机ASCII模式的接收函数(派能协议)
************************************************************************************************************************/
MBErrorCode MB_Master_Receive_ASCII_Frame(uint8_t u8Sciid,MBASCIIFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;
    uint8_t *pu8Buf;
    uint16_t u16LRC = 0;
    uint16_t u16Length = 0;

    GetUsartRxBuf(u8Sciid,&pu8Buf);              //获取接收缓冲区地址信息
    u16Length = GetUsartRxBufLength(u8Sciid);    //获取接收缓冲区长度信息
    UART_DmaStartRx(u8Sciid, u8UartRxBuffer[u8Sciid] , DEV_RX_BUFF_SIZE); //开启DMA接收

    u16LRC = (ModbusChar2Bin(pu8Buf[u16Length - 5]) << 12) \
           + (ModbusChar2Bin(pu8Buf[u16Length - 4]) << 8) \
           + (ModbusChar2Bin(pu8Buf[u16Length - 3]) << 4) \
           + (ModbusChar2Bin(pu8Buf[u16Length - 2]));//提取LRC校验位
    pu8Buf = pu8Buf + 1;
    /*判断CRC校验是否正确*/
    if(u16LRC != ModbusLRC((uint8_t*)pu8Buf, u16Length - 6))
    {
        /*CRC校验错误，返回Error*/
        return MB_CRC_ERR;
    }
    else
    {
        /*CRC校验成功，解析数据*/
        pu8Buf = pu8Buf - 1;
        ptMBFrame->u32LRC = u16LRC;
        eStatus = MB_Master_Parsing_ASCII_Frame(u8Sciid,pu8Buf,ptMBFrame);
        EmsCommunicateConnectFinish(u8Sciid);
    }
    return eStatus;
}

/***********************************************************************************************************************
 功能：主机ASCII模式的解析函数(派能协议)
************************************************************************************************************************/
MBErrorCode MB_Master_Parsing_ASCII_Frame(uint8_t u8Sciid,uint8_t *pu8RxBuf,MBASCIIFrame_t* ptMBFrame)
{
    MBErrorCode eStatus = MB_NO_ERR;

    ptMBFrame->u16Ver = (ModbusChar2Bin(pu8RxBuf[1]) << 4) + ModbusChar2Bin(pu8RxBuf[2]);
    ptMBFrame->u16ADR = (ModbusChar2Bin(pu8RxBuf[3]) << 4) + ModbusChar2Bin(pu8RxBuf[4]);
    ptMBFrame->u16MBCID1 = (ModbusChar2Bin(pu8RxBuf[5]) << 4) + ModbusChar2Bin(pu8RxBuf[6]);
    //ptMBFrame->u16MBCID2 = (ModbusChar2Bin(pu8RxBuf[7]) << 4) + ModbusChar2Bin(pu8RxBuf[8]);
    ptMBFrame->u32Length = (ModbusChar2Bin(pu8RxBuf[9]) << 12) + (ModbusChar2Bin(pu8RxBuf[10]) << 8) + (ModbusChar2Bin(pu8RxBuf[11]) << 4) + ModbusChar2Bin(pu8RxBuf[12]);

    switch(ptMBFrame->u16MBCID2)
    {
        /*控制标识码：获取电池系统运行模拟量信息0x61*/
        case MB_FUNC_ASCII_PYLON_61H:
            tBmsDataPylon.tBmsPylonAnalogInfo.u16SystemAvgVolt = (ModbusChar2Bin(pu8RxBuf[13]) << 12) + (ModbusChar2Bin(pu8RxBuf[14]) << 8)
                                                               + (ModbusChar2Bin(pu8RxBuf[15]) << 4) + ModbusChar2Bin(pu8RxBuf[16]);
            tBmsDataPylon.tBmsPylonAnalogInfo.s16SystemTotalCurr = (ModbusChar2Bin(pu8RxBuf[17]) << 12) + (ModbusChar2Bin(pu8RxBuf[18]) << 8)
                                                                 + (ModbusChar2Bin(pu8RxBuf[19]) << 4) + ModbusChar2Bin(pu8RxBuf[20]);
            tBmsDataPylon.tBmsPylonAnalogInfo.u16SystemSOC = (ModbusChar2Bin(pu8RxBuf[21]) << 4) + ModbusChar2Bin(pu8RxBuf[22]);
            tBmsDataPylon.tBmsPylonAnalogInfo.u16AvgCycleCnt = (ModbusChar2Bin(pu8RxBuf[23]) << 12) + (ModbusChar2Bin(pu8RxBuf[24]) << 8)
                                                             + (ModbusChar2Bin(pu8RxBuf[25]) << 4) + ModbusChar2Bin(pu8RxBuf[26]);
            tBmsDataPylon.tBmsPylonAnalogInfo.u16MaxCycleCnt = (ModbusChar2Bin(pu8RxBuf[27]) << 12) + (ModbusChar2Bin(pu8RxBuf[28]) << 8)
                                                             + (ModbusChar2Bin(pu8RxBuf[29]) << 4) + ModbusChar2Bin(pu8RxBuf[30]);
            tBmsDataPylon.tBmsPylonAnalogInfo.u16AvgSOH = (ModbusChar2Bin(pu8RxBuf[31]) << 4) + ModbusChar2Bin(pu8RxBuf[32]);
            tBmsDataPylon.tBmsPylonAnalogInfo.u16MinSOH = (ModbusChar2Bin(pu8RxBuf[33]) << 4) + ModbusChar2Bin(pu8RxBuf[34]);
            tBmsDataPylon.tBmsPylonAnalogInfo.u16MaxSingleVolt = (ModbusChar2Bin(pu8RxBuf[35]) << 12) + (ModbusChar2Bin(pu8RxBuf[36]) << 8)
                                                               + (ModbusChar2Bin(pu8RxBuf[37]) << 4) + ModbusChar2Bin(pu8RxBuf[38]);
            tBmsDataPylon.tBmsPylonAnalogInfo.u16MaxSingleVoltPos = (ModbusChar2Bin(pu8RxBuf[39]) << 12) + (ModbusChar2Bin(pu8RxBuf[40]) << 8)
                                                                  + (ModbusChar2Bin(pu8RxBuf[41]) << 4) + ModbusChar2Bin(pu8RxBuf[42]);
            tBmsDataPylon.tBmsPylonAnalogInfo.u16MinSingleVolt = (ModbusChar2Bin(pu8RxBuf[43]) << 12) + (ModbusChar2Bin(pu8RxBuf[44]) << 8)
                                                               + (ModbusChar2Bin(pu8RxBuf[45]) << 4) + ModbusChar2Bin(pu8RxBuf[46]);
            tBmsDataPylon.tBmsPylonAnalogInfo.u16MinSingleVoltPos = (ModbusChar2Bin(pu8RxBuf[47]) << 12) + (ModbusChar2Bin(pu8RxBuf[48]) << 8)
                                                                  + (ModbusChar2Bin(pu8RxBuf[49]) << 4) + ModbusChar2Bin(pu8RxBuf[50]);
            tBmsDataPylon.tBmsPylonAnalogInfo.s16SingleAvgTemp = (ModbusChar2Bin(pu8RxBuf[51]) << 12) + (ModbusChar2Bin(pu8RxBuf[52]) << 8)
                                                               + (ModbusChar2Bin(pu8RxBuf[53]) << 4) + ModbusChar2Bin(pu8RxBuf[54]);
            tBmsDataPylon.tBmsPylonAnalogInfo.s16SingleMaxTemp = (ModbusChar2Bin(pu8RxBuf[55]) << 12) + (ModbusChar2Bin(pu8RxBuf[56]) << 8)
                                                               + (ModbusChar2Bin(pu8RxBuf[57]) << 4) + ModbusChar2Bin(pu8RxBuf[58]);
            tBmsDataPylon.tBmsPylonAnalogInfo.u16SingleMaxTempPos = (ModbusChar2Bin(pu8RxBuf[59]) << 12) + (ModbusChar2Bin(pu8RxBuf[60]) << 8)
                                                                  + (ModbusChar2Bin(pu8RxBuf[61]) << 4) + ModbusChar2Bin(pu8RxBuf[62]);
            tBmsDataPylon.tBmsPylonAnalogInfo.s16SingleMinTemp = (ModbusChar2Bin(pu8RxBuf[63]) << 12) + (ModbusChar2Bin(pu8RxBuf[64]) << 8)
                                                               + (ModbusChar2Bin(pu8RxBuf[65]) << 4) + ModbusChar2Bin(pu8RxBuf[66]);
            tBmsDataPylon.tBmsPylonAnalogInfo.u16SingleMinTempPos = (ModbusChar2Bin(pu8RxBuf[67]) << 12) + (ModbusChar2Bin(pu8RxBuf[68]) << 8)
                                                                  + (ModbusChar2Bin(pu8RxBuf[69]) << 4) + ModbusChar2Bin(pu8RxBuf[70]);
            tBmsDataPylon.tBmsPylonAnalogInfo.s16MosfetAvgTemp = (ModbusChar2Bin(pu8RxBuf[71]) << 12) + (ModbusChar2Bin(pu8RxBuf[72]) << 8)
                                                               + (ModbusChar2Bin(pu8RxBuf[73]) << 4) + ModbusChar2Bin(pu8RxBuf[74]);
            tBmsDataPylon.tBmsPylonAnalogInfo.s16MosfetMaxTemp = (ModbusChar2Bin(pu8RxBuf[75]) << 12) + (ModbusChar2Bin(pu8RxBuf[76]) << 8)
                                                               + (ModbusChar2Bin(pu8RxBuf[77]) << 4) + ModbusChar2Bin(pu8RxBuf[78]);
            tBmsDataPylon.tBmsPylonAnalogInfo.u16MosfetMaxTempPos = (ModbusChar2Bin(pu8RxBuf[79]) << 12) + (ModbusChar2Bin(pu8RxBuf[80]) << 8)
                                                                  + (ModbusChar2Bin(pu8RxBuf[81]) << 4) + ModbusChar2Bin(pu8RxBuf[82]);
            tBmsDataPylon.tBmsPylonAnalogInfo.s16MosfetMinTemp = (ModbusChar2Bin(pu8RxBuf[83]) << 12) + (ModbusChar2Bin(pu8RxBuf[84]) << 8)
                                                               + (ModbusChar2Bin(pu8RxBuf[85]) << 4) + ModbusChar2Bin(pu8RxBuf[86]);
            tBmsDataPylon.tBmsPylonAnalogInfo.u16MosfetMinTempPos = (ModbusChar2Bin(pu8RxBuf[87]) << 12) + (ModbusChar2Bin(pu8RxBuf[88]) << 8)
                                                                  + (ModbusChar2Bin(pu8RxBuf[89]) << 4) + ModbusChar2Bin(pu8RxBuf[90]);
            tBmsDataPylon.tBmsPylonAnalogInfo.s16BmsAvgTemp = (ModbusChar2Bin(pu8RxBuf[91]) << 12) + (ModbusChar2Bin(pu8RxBuf[92]) << 8)
                                                            + (ModbusChar2Bin(pu8RxBuf[93]) << 4) + ModbusChar2Bin(pu8RxBuf[94]);
            tBmsDataPylon.tBmsPylonAnalogInfo.s16BmsMaxTemp = (ModbusChar2Bin(pu8RxBuf[95]) << 12) + (ModbusChar2Bin(pu8RxBuf[96]) << 8)
                                                            + (ModbusChar2Bin(pu8RxBuf[97]) << 4) + ModbusChar2Bin(pu8RxBuf[98]);
            tBmsDataPylon.tBmsPylonAnalogInfo.u16BmsMaxTempPos = (ModbusChar2Bin(pu8RxBuf[99]) << 12) + (ModbusChar2Bin(pu8RxBuf[100]) << 8)
                                                               + (ModbusChar2Bin(pu8RxBuf[101]) << 4) + ModbusChar2Bin(pu8RxBuf[102]);
            tBmsDataPylon.tBmsPylonAnalogInfo.s16BmsMinTemp = (ModbusChar2Bin(pu8RxBuf[103]) << 12) + (ModbusChar2Bin(pu8RxBuf[104]) << 8)
                                                            + (ModbusChar2Bin(pu8RxBuf[105]) << 4) + ModbusChar2Bin(pu8RxBuf[106]);
            tBmsDataPylon.tBmsPylonAnalogInfo.u16BmsMinTempPos = (ModbusChar2Bin(pu8RxBuf[107]) << 12) + (ModbusChar2Bin(pu8RxBuf[108]) << 8)
                                                               + (ModbusChar2Bin(pu8RxBuf[109]) << 4) + ModbusChar2Bin(pu8RxBuf[110]);
            break;
        /*控制标识码：获取电池组系统状态告警量信息0x62*/
        case MB_FUNC_ASCII_PYLON_62H:
            tBmsDataPylon.tBmsPylonAlarmInfo.SystemAlarm1_t.u16Warnning = (ModbusChar2Bin(pu8RxBuf[13]) << 4) + ModbusChar2Bin(pu8RxBuf[14]);
            tBmsDataPylon.tBmsPylonAlarmInfo.SystemAlarm2_t.u16Warnning = (ModbusChar2Bin(pu8RxBuf[15]) << 4) + ModbusChar2Bin(pu8RxBuf[16]);
            tBmsDataPylon.tBmsPylonAlarmInfo.SystemError1_t.u16Error = (ModbusChar2Bin(pu8RxBuf[17]) << 4) + ModbusChar2Bin(pu8RxBuf[18]);
            tBmsDataPylon.tBmsPylonAlarmInfo.SystemError2_t.u16Error = (ModbusChar2Bin(pu8RxBuf[19]) << 4) + ModbusChar2Bin(pu8RxBuf[20]);
            break;
        /*控制标识码：获取电池组系统充放电管理交互信息0x63*/
        case MB_FUNC_ASCII_PYLON_63H:
            tBmsDataPylon.tBmsPylonMutualInfo.u16ChgVoltHighLimit = (ModbusChar2Bin(pu8RxBuf[13]) << 12) + (ModbusChar2Bin(pu8RxBuf[14]) << 8)
                                                                  + (ModbusChar2Bin(pu8RxBuf[15]) << 4) + ModbusChar2Bin(pu8RxBuf[16]);
            tBmsDataPylon.tBmsPylonMutualInfo.u16DisChgVoltLowLimit = (ModbusChar2Bin(pu8RxBuf[17]) << 12) + (ModbusChar2Bin(pu8RxBuf[18]) << 8)
                                                                    + (ModbusChar2Bin(pu8RxBuf[19]) << 4) + ModbusChar2Bin(pu8RxBuf[20]);
            tBmsDataPylon.tBmsPylonMutualInfo.s16MaxChgCurr = (ModbusChar2Bin(pu8RxBuf[21]) << 12) + (ModbusChar2Bin(pu8RxBuf[22]) << 8)
                                                            + (ModbusChar2Bin(pu8RxBuf[23]) << 4) + ModbusChar2Bin(pu8RxBuf[24]);
            tBmsDataPylon.tBmsPylonMutualInfo.s16MaxDischgCurr = (ModbusChar2Bin(pu8RxBuf[25]) << 12) + (ModbusChar2Bin(pu8RxBuf[26]) << 8)
                                                               + (ModbusChar2Bin(pu8RxBuf[27]) << 4) + ModbusChar2Bin(pu8RxBuf[28]);
            tBmsDataPylon.tBmsPylonMutualInfo.ChgDischgStatus_t.u8Status = (ModbusChar2Bin(pu8RxBuf[29]) << 4) + ModbusChar2Bin(pu8RxBuf[30]);
            break;
        default:
            break;
    }
    return eStatus;
}

uint8_t ASCII2Hex8Bit(uint8_t* pAsciiDataBuff)
{
    uint8_t bHighByte;
    uint8_t bLowByte;
    uint8_t bvalue;

    bHighByte = ModbusChar2Bin(*pAsciiDataBuff);
    pAsciiDataBuff++;
    bLowByte = ModbusChar2Bin(*pAsciiDataBuff);
    bvalue = (bHighByte << 4) + bLowByte;

    return(bvalue);
}

uint16_t ASCII2Hex16Bit(uint8_t* pAsciiDataBuff)
{
    uint32_t bMostSigHighByte;
    uint32_t bSecondSigHighByte;
    uint32_t bThirdSigHighByte;
    uint32_t bLowSigByte;
    uint32_t bvalue;

    bMostSigHighByte = ModbusChar2Bin(*pAsciiDataBuff);
    pAsciiDataBuff++;
    bSecondSigHighByte = ModbusChar2Bin(*pAsciiDataBuff);
    pAsciiDataBuff++;
    bThirdSigHighByte = ModbusChar2Bin(*pAsciiDataBuff);
    pAsciiDataBuff++;
    bLowSigByte = ModbusChar2Bin(*pAsciiDataBuff);
    pAsciiDataBuff++;
    bvalue = (uint16_t)((bMostSigHighByte << 12) + (bSecondSigHighByte << 8) + (bThirdSigHighByte << 4) + bLowSigByte);

    return(bvalue);
}


uint8_t ModbusChar2Bin( uint8_t ucCharacter )
{
    if( ( ucCharacter >= '0' ) && ( ucCharacter <= '9' ) )
    {
        return ( uint8_t )( ucCharacter - '0' );
    }
    else if( ( ucCharacter >= 'A' ) && ( ucCharacter <= 'F' ) )
    {
        return ( uint8_t )( ucCharacter - 'A' + 0x0A );
    }
    else
    {
        return 0xFF;
    }
}

uint8_t ModbusBin2Char( uint8_t ucByte )
{
    if( ucByte <= 0x09 )
    {
        return ( uint8_t )( '0' + ucByte );
    }
    else if( ( ucByte >= 0x0A ) && ( ucByte <= 0x0F ) )
    {
        return ( uint8_t )( ucByte - 0x0A + 'A' );
    }
    return '0';
}



#endif /***Module End***/
#endif

/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

