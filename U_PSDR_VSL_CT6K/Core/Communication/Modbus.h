/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Modbus.h 
 用途 : modbus协议模块头文件
***********************************************************************************************************************/
#ifndef _MODBUS_H_
#define _MODBUS_H_

#include "HeadFile.h"

/*ModbusRTU一帧数据中的位组成*/
#define MB_ADU_ADDR_OFF                         (     0) //从机地址位
#define MB_ADU_FUNC_OFF                         (     1) //功能码位
#define MB_ADU_S_ADRR_OFF                       (     2) //起始地址位
#define MB_ADU_N_REG_OFF                        (     4) //数据数量位
#define MB_ADU_BYTE_NUM_OFF                     (     6) //字节数位
#define MB_ADU_10H_DATA_OFF                     (     7) //10H数据开始位
#define MB_ADU_0FH_DATA_OFF                     (     7) //0FH数据开始位
#define MB_ADU_03H_DATA_OFF                     (     3) //03H数据开始位
#define MB_ADU_SIZE_CRC                         (     2) //CRC校验的字节数

/*ModbusRTU一帧数据中的功能码类别*/
#define MB_FUNC_READ_COILS                      (     1) //0x01 读线圈
#define MB_FUNC_READ_DISCRETE_INPUTS            (     2) //0x02 读离散量输入
#define MB_FUNC_READ_HOLDING_REGISTER           (     3) //0x03 读保持寄存器
#define MB_FUNC_READ_INPUT_REGISTER             (     4) //0x04 读输入寄存器
#define MB_FUNC_WRITE_SINGLE_COIL               (     5) //0x05 写单个线圈
#define MB_FUNC_WRITE_SINGLE_REGISTER           (     6) //0x06 写单个寄存器
#define MB_FUNC_WRITE_MULTIPLE_COILS            (    15) //0x0F 写多个线圈
#define MB_FUNC_WRITE_MULTIPLE_REGISTERS        (    16) //0x10 写多个寄存器
#define MB_FUNC_READWRITE_MULTIPLE_REGISTERS    (    23) //0x17 读写多个寄存器

/*ModbusASCII一帧数据中的功能码类别*/
#define MB_FUNC_ASCII_PYLON_61H                 (0x3631) //0x61 派能获取电池组系统运行模拟量数据
#define MB_FUNC_ASCII_PYLON_62H                 (0x3632) //0x62 派能获取电池组系统状态告警量数据
#define MB_FUNC_ASCII_PYLON_63H                 (0x3633) //0x62 派能获取电池组系统充放电管理交互信息
#define MB_FUNC_ERROR                           (   128) //0x80 异常码

/*ModbusRTU一帧数据中的异常码类别*/
#define MB_ILLEGAL_FUNCTION                     (  0x01) //0x01 非法功能码
#define MB_ILLEGAL_DATA_ADDRESS                 (  0x02) //0x02 非法数据地址
#define MB_ILLEGAL_DATA_VALUE                   (  0x03) //0x03 非法数据值
#define MB_COMMUNICATE_BREAK                    (  0x04) //0x04 通讯断联


#define MB_SLAVE_CLOUD_LOCAL_ADDR               (  0x02) //英臻云平台从机地址
#define MB_SLAVE_LOCAL_ADDR                     (  0x01) //PCS从机地址

/*EMS通讯与各串口之间断联超时计数值*/
#define PcsTimeOutCounter                       (     3) //PCS通讯超时计数的次数
#define MeterTimeOutCounter                     (     3) //电表通讯超时计数的次数
#define BmsTimeOutCounter                       (     3) //BMS通讯超时计数的次数
#define WifiTimeOutCounter                      (     3) //WIFI通讯超时计数的次数
#define BltTimeOutCounter                       (     3) //蓝牙通讯超时计数的次数
#define AFCITimeOutCounter                      (     3) //AFCI通讯超时计数的次数

typedef enum
{
    MB_NO_ERR = 0,               //无错误
    MB_CRC_ERR,                  //CRC校验错误
    MB_SLAVE_ADD_ERROR,          //从机地址错误
    MB_FUNCTION_ERROR,           //功能码错误
    MB_DATA_ADD_ERROR,           //数据地址错误
    MB_PCS_BRK_ERROR,            //通讯断连错误
} MBErrorCode;

typedef struct
{
    uint8_t  u8FunctionCode;     //功能码
    uint8_t  u8MBAddress;        //从机地址
    uint16_t u16MBStartRegsAddr; //起始地址
    uint16_t u16MBRegsNum;       //数据个数
    uint8_t  u8MBBytesNum;       //字节个数
    uint16_t u16CRC16;           //CRC校验和
    uint8_t  u8ErrorCode;        //异常错误码
} MBRTUFrame_t;
extern MBRTUFrame_t gtMBSlaveRTUCMDFrame[];
extern MBRTUFrame_t gtMBMasterRTUCMDFrame[];

typedef struct
{
    uint8_t  u8SOI;              //起始标志位
    uint16_t u16Ver;             //通讯协议版本号
    uint16_t u16ADR;             //设备地址描述
    uint16_t u16MBCID1;          //设备标识码
    uint16_t u16MBCID2;          //控制标识码
    uint32_t u32Length;          //INFO字节长度
    uint32_t u16INFO;            //控制或应答信息
    uint32_t u32LRC;             //LRC校验
    uint8_t  u8EOI;              //结束标志位
    uint16_t u16ErrorCode;       //异常错误码
} MBASCIIFrame_t;
extern MBASCIIFrame_t gtMBMasterASCIICMDFrame[];

//通讯状态
typedef enum
{
    EMS_COMM_ERROR = 0,      //通讯错误
    EMS_COMM_NORMAL,         //通讯正常
}EMS_COMM_TypeDef;

typedef struct
{
    uint8_t u8PcsDisconnectCnt;    //EMS与PCS通信断联计数
    uint8_t u8MeterDisconnectCnt;  //EMS与电表通信断联计数
    uint8_t u8BmsDisconnectCnt;    //EMS与BMS通信断联计数
    uint8_t u8WifiDisconnectCnt;   //EMS与WIFI通信断联计数
    uint8_t u8BltDisconnectCnt;    //EMS与蓝牙通信断联计数
    uint8_t u8DebugDisconnectCnt;  //EMS与Debug通信断联计数
    uint8_t u8BmsCanDisconnectCnt; //EMS与BMSCan通信断联计数    
}CommDisconnectCnt_t;

typedef union
{
    uint8_t u8Bytes;
    struct
    {
        uint8_t bEmsToPcsCommStateFlag      : 1; //EMS与PCS通信状态标志位
        uint8_t bEmsToMeterCommStateFlag    : 1; //EMS与电表通信状态标志位
        uint8_t bEmsToBmsCommStateFlag      : 1; //EMS与BMS通信状态标志位
        uint8_t bEmsToWifiCommStateFlag     : 1; //EMS与WIFI通信状态标志位
        uint8_t bEmsToBltCommStateFlag      : 1; //EMS与蓝牙通信状态标志位
        uint8_t bEmsToDebugCommStateFlag    : 1; //EMS与Debug通信状态标志位
        uint8_t bEmsToBmsCanCommStateFlag   : 1; //EMS与BMScan通信状态标志位
        uint8_t bReserved2                  : 1; //预留
    }Bits;
}CommStateFlag_t;

typedef struct
{
    CommStateFlag_t tCommDisconnectFlag;         //EMS与各串口间通讯状态标志位
    CommDisconnectCnt_t tCommDisconnectCnt;      //EMS与各串口间通讯状态计数值
}CommStatus_t;
extern CommStatus_t tCommStatus;

extern void        Modbus_InitVar(void);                                                //Modbus协议全局变量初始化
extern uint16_t    ModbusLRC( uint8_t * pucFrame, uint16_t usLen );                     //计算LRC校验和
extern uint16_t    ModbusCRC16( uint8_t * pu8Frame, uint16_t u16Len );                  //计算CRC16校验和
extern uint16_t    MergeData(uint8_t *pu8Buf);                                          //合并数据
extern uint16_t    GetRegsBytesNum(MBRTUFrame_t* ptMBFrame);                            //计算数据长度对应的字节数
extern void        EmsCommunicateBreakCheck(uint8_t u8Sciid,uint8_t u8DetectCounter);   //通讯断联检测函数
extern void        EmsCommunicateConnectFinish(uint8_t u8Sciid);                        //通讯连接完成函数

#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

