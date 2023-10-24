/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Storage_Manageent_Service.h 
 用途 : 存储管理头文件
***********************************************************************************************************************/
#ifndef _LCD_STORAGEMANAGEMENT_H_
#define _LCD_STORAGEMANAGEMENT_H_


#include "HeadFile.h"
#include "LCD_Service.h"
#include "Fault_Management_Service.h"
#include "Modbus_PCS_COMData.h"

#pragma pack(1)

static uint32_t u32MinterCounter = 0;

#define STORAGE_BMS_CACHE_SIZE (3)                                                                                      //BMS数据暂存缓存区大小
#define STORAGE_Grid_CACHE_SIZE (8)                                                                                     //电网数据缓存区大小

/***********************************************************************************************************************
 外部Flash模拟EEPROM数据类型
************************************************************************************************************************/
typedef struct
{
    uint16_t u16Proportion;                                                                                             //比例系数
    int16_t s16Intercept;                                                                                               //截距系数
}SampleAdjPara_t;                                                                                                       //两点校正参数数据结构

typedef struct
{
    SampleAdjPara_t tRGridVoltAdjPara;                                                                                  //R相 电网电压 校正参数
    SampleAdjPara_t tSGridVoltAdjPara;                                                                                  //S相 电网电压 校正参数
    SampleAdjPara_t tTGridVoltAdjPara;                                                                                  //T相 电网电压 校正参数
    SampleAdjPara_t tRGridCurrAdjPara;                                                                                  //R相 电网电流 校正参数
    SampleAdjPara_t tSGridCurrAdjPara;                                                                                  //S相 电网电流 校正参数
    SampleAdjPara_t tTGridCurrAdjPara;                                                                                  //T相 电网电流 校正参数
    SampleAdjPara_t tRInvVoltAdjPara;                                                                                   //R相 逆变电压 校正参数
    SampleAdjPara_t tSInvVoltAdjPara;                                                                                   //S相 逆变电压 校正参数
    SampleAdjPara_t tTInvVoltAdjPara;                                                                                   //T相 逆变电压 校正参数
    SampleAdjPara_t tRInvCurrAdjPara;                                                                                   //R相 逆变输出电流 校正参数
    SampleAdjPara_t tSInvCurrAdjPara;                                                                                   //S相 逆变输出电流 校正参数
    SampleAdjPara_t tTInvCurrAdjPara;                                                                                   //T相 逆变输出电流 校正参数
    SampleAdjPara_t tRInvInductorCurrAdjPara;                                                                           //R相 逆变电感电流 校正参数
    SampleAdjPara_t tSInvInductorCurrAdjPara;                                                                           //S相 逆变电感电流 校正参数
    SampleAdjPara_t tTInvInductorCurrAdjPara;                                                                           //T相 逆变电感电流 校正参数
    SampleAdjPara_t tRGenVoltAdjPara;                                                                                   //R相 发电机电压 校正参数
    SampleAdjPara_t tSGenVoltAdjPara;                                                                                   //S相 发电机电压 校正参数
    SampleAdjPara_t tTGenVoltAdjPara;                                                                                   //T相 发电机电压 校正参数
    SampleAdjPara_t tRGenCurrAdjPara;                                                                                   //R相 发电机电流 校正参数
    SampleAdjPara_t tSGenCurrAdjPara;                                                                                   //S相 发电机电流 校正参数
    SampleAdjPara_t tTGenCurrAdjPara;                                                                                   //T相 发电机电流 校正参数
    SampleAdjPara_t tPBusVoltAdjPara;                                                                                   //正(P) 母线电压 校正参数
    SampleAdjPara_t tNBusVoltAdjPara;                                                                                   //负(N) 母线电压 校正参数
    SampleAdjPara_t tBuckBoostInducCurrAdjPara;                                                                         //Buck-Boost 电感电流 校正参数
    SampleAdjPara_t tMidBusVoltAdjPara;                                                                                 //中间 母线电压 校正参数
    SampleAdjPara_t tBatVoltAdjPara;                                                                                    //电池电压 校正参数
    SampleAdjPara_t tPV1VoltAdjPara;                                                                                    //PV1电压 校正参数
    SampleAdjPara_t tPV1CurrAdjPara;                                                                                    //PV1电流 校正参数
    SampleAdjPara_t tPV2VoltAdjPara;                                                                                    //PV2电压 校正参数
    SampleAdjPara_t tPV2CurrAdjPara;                                                                                    //PV2电流 校正参数
}TotalSampleAdjData_t;                                                                                                  //出厂校正系数表数据结构

typedef struct
{
    TotalSampleAdjData_t tTotalSampleAdjData;
    uint8_t u8HardwareVersion[20];                                                                                      //硬件出厂版本
    uint8_t u8SoftwareVersion[20];                                                                                      //软件出厂版本
    uint8_t u8CompanyId[20];                                                                                            //公司识别码
    uint8_t u8EESerialNumber[20];                                                                                       //序列号内容
    uint16_t u16EEReseverd[100];                                                                                         //保留
    uint16_t  ExitFactoryParaCheckSum;                                                                                  //校验码
}ExitFactoryPara_t;                                                                                                     //用于存储用户进行恢复出厂设置时，不能重置的数据，例如：采样校正参数、出厂固化的版本哈、序列号等信息

typedef struct
{
    Language_TypeDef u8LanguageType;                                                                                    //语言种类默认 1) 0 中文 1 英文 2 西班牙语 3 德语 4 法语 5 波兰语 6 意大利语 7 捷克语 8 荷兰语
    uint8_t u8ClearFaultFlag;                                                                                           //清除故障
    uint8_t u8OperationRecordFlag;                                                                                      //清除操作记录
    uint8_t u8FactoryFlag;                                                                                              //出厂设置使能
    uint8_t u8WifiResetFlag;                                                                                            //Wifi 复位
    uint8_t u8BLTResetFlag;                                                                                             //蓝牙复位
    uint8_t u8RemoteControl;                                                                                            //远程控制方式(默认 0) 0 本地 1远程
    Display_SET_System_CTRadio         stCTRadio;                                                                       //CT变比
    uint8_t u8IRDetectionFlag;                                                                                          //绝缘阻抗检测(默认 0) 0 禁止 1 使能
    uint8_t u8ReservedFlag;                                                                                             //保留
    Display_SET_USART_Paras stDspUsartParas;                                                                            //串口参数显示设置
    Display_SET_System_TimeSync        stTimeSync;                                                                      //时间设置
    Display_SET_System_PasswordModify  stPasswordModify;                                                                //密码修改
    Display_SET_System_ProtectEnable   stProtectEnable;                                                                 //保护使能
    Display_SET_System_Strategy        stStrategy;                                                                      //策略参数
    Display_SET_PV                     stPV;                                                                            //PV参数
    Display_SET_BMS                    stBMS;                                                                           //电池参数
    Display_SET_Grid                   stGrid;                                                                          //电网参数
    Display_SET_Gen                    stGen;                                                                           //发电机参数
    Display_DATA_STATISTICAL stStatistical;                                                                             //统计数据
    uint16_t  Reserved[100];                                                                                            //保留
    uint16_t  u16UserConfigParaCheckSum;                                                                                //校验码
}UserConfigPara_t;                                                                                                      //用于存储用户自定义配置信息

typedef struct
{
    Fault_Info_History       stFaultHistory;                                                                            //历史故障
    Record_Info              stRecord;                                                                                  //操作记录
    uint16_t  u16HistoryParaCheckSum;                                                                                   //校验码
}HistoryPara_t;                                                                                                         //用于存放故障记录、故障现场实时数据、操作记录等非用户自定义配置数据

#define HARDWARE_SIZE                          (20)                                                                     //硬件版本号 字节数
#define SOFTWARE_SIZE                          (20)                                                                     //软件版本号 字节数
#define COMPANY_ID_SIZE                        (17)                                                                     //公司ID 字节数
#define SN_NUM_SIZE                            (20)                                                                     //生产序列号 字节数

/***********************************************************************************************************************
 ExitFactoryPara_t 存储地址划分
************************************************************************************************************************/
#define ParamAddr_ExitFactoryParaBase         (0x000000)                                                                //出厂参数的 基址
#define ParamSize_ExitFactoryPara             (sizeof(ExitFactoryPara_t))                                               //出厂参数的 大小

#define ParamAddr_tPV1VoltAdjPara             (ParamAddr_ExitFactoryParaBase)                                           //PV1电压校正参数 逻辑地址
#define ParamSize_tPV1VoltAdjPara             (sizeof(SampleAdjPara_t))                                                 //PV1电压校正参数 大小

#define ParamAddr_tPV2VoltAdjPara             (ParamAddr_tPV1VoltAdjPara + ParamSize_tPV1VoltAdjPara)                   //PV2电压校正参数 逻辑地址
#define ParamSize_tPV2VoltAdjPara             (sizeof(SampleAdjPara_t))                                                 //PV2电压校正参数 大小

#define ParamAddr_tBusVoltAdjPara             (ParamAddr_tPV1VoltAdjPara + ParamSize_tPV2VoltAdjPara)                   //母线电压校正参数 逻辑地址
#define ParamSize_tBusVoltAdjPara             (sizeof(SampleAdjPara_t))                                                 //母线电压校正参数 大小

#define ParamAddr_tMidBusVoltAdjPara          (ParamAddr_tBusVoltAdjPara + ParamSize_tBusVoltAdjPara)                   //中间电压校正参数 逻辑地址
#define ParamSize_tMidBusVoltAdjPara          (sizeof(SampleAdjPara_t))                                                 //中间电压校正参数 大小

#define ParamAddr_tGridVoltAdjPara            (ParamAddr_tMidBusVoltAdjPara + ParamSize_tMidBusVoltAdjPara)             //电网电压校正参数 逻辑地址
#define ParamSize_tGridVoltAdjPara            (sizeof(SampleAdjPara_t))                                                 //电网电压校正参数 大小

#define ParamAddr_tInvVoltAdjPara             (ParamAddr_tGridVoltAdjPara + ParamSize_tGridVoltAdjPara)                 //逆变电压校正参数 逻辑地址
#define ParamSize_tInvVoltAdjPara             (sizeof(SampleAdjPara_t))                                                 //逆变电压校正参数 大小

#define ParamAddr_tInvCurrAdjPara             (ParamAddr_tInvVoltAdjPara + ParamSize_tInvVoltAdjPara)                   //逆变电流校正参数 逻辑地址
#define ParamSize_tInvCurrAdjPara             (sizeof(SampleAdjPara_t))                                                 //逆变电流校正参数 大小

#define ParamAddr_tGridHCTCurrAdjPara         (ParamAddr_tInvCurrAdjPara + ParamSize_tInvCurrAdjPara)                   //电网HCT电流校正参数 逻辑地址
#define ParamSize_tGridHCTCurrAdjPara         (sizeof(SampleAdjPara_t))                                                 //电网HCT电流校正参数 大小

#define ParamAddr_tGridCTCurrAdjPara          (ParamAddr_tGridHCTCurrAdjPara + ParamSize_tGridHCTCurrAdjPara)           //电网CT电流校正参数 逻辑地址
#define ParamSize_tGridCTCurrAdjPara          (sizeof(SampleAdjPara_t))                                                 //电网CT电流校正参数 大小

#define ParamAddr_tPV1CurrAdjPara             (ParamAddr_tGridCTCurrAdjPara + ParamSize_tGridCTCurrAdjPara)             //PV1电流校正参数 逻辑地址
#define ParamSize_tPV1CurrAdjPara             (sizeof(SampleAdjPara_t))                                                 //PV1电流校正参数 大小

#define ParamAddr_tPV2CurrAdjPara             (ParamAddr_tPV1CurrAdjPara + ParamSize_tPV1CurrAdjPara)                   //PV2电流校正参数 逻辑地址
#define ParamSize_tPV2CurrAdjPara             (sizeof(SampleAdjPara_t))                                                 //PV2电流校正参数 大小

#define ParamAddr_tBatVoltAdjPara             (ParamAddr_tPV2CurrAdjPara + ParamSize_tPV2CurrAdjPara)                   //电池电压校正参数 逻辑地址
#define ParamSize_tBatVoltAdjPara             (sizeof(SampleAdjPara_t))                                                 //电池电压校正参数 大小

#define ParamAddr_tBatCurrAdjPara             (ParamAddr_tBatVoltAdjPara + ParamSize_tBatVoltAdjPara)                   //电池电流校正参数 逻辑地址
#define ParamSize_tBatCurrAdjPara             (sizeof(SampleAdjPara_t))                                                 //电池电流校正参数 大小

#define ParamAddr_u8HardwareVersion           (ParamAddr_tBatCurrAdjPara + ParamSize_tBatCurrAdjPara)                   //硬件出厂版本 逻辑地址
#define ParamSize_u8HardwareVersion           (HARDWARE_SIZE)                                                           //硬件出厂版本 大小

#define ParamAddr_u8SoftwareVersion           (ParamAddr_u8HardwareVersion + ParamSize_u8HardwareVersion)               //软件出厂版本 逻辑地址
#define ParamSize_u8SoftwareVersion           (HARDWARE_SIZE)                                                           //软件出厂版本 大小

#define ParamAddr_u8CompanyId                 (ParamAddr_u8HardwareVersion + ParamSize_u8SoftwareVersion)               //公司识别码 逻辑地址
#define ParamSize_u8CompanyId                 (SOFTWARE_SIZE)                                                           //公司识别码 大小

#define ParamAddr_u8EESerialNumber            (ParamAddr_u8CompanyId + ParamSize_u8CompanyId)                           //序列号内容 逻辑地址
#define ParamSize_u8EESerialNumber            (SOFTWARE_SIZE)                                                           //序列号内容 大小

/***********************************************************************************************************************
 UserConfigPara_t 存储地址划分
************************************************************************************************************************/
#define ParamAddr_UserConfigParaBase          (0x001000)                                                                //用户配置参数 基址
#define ParamSize_UserConfigPara              (sizeof(UserConfigPara_t))                                                //用户配置参数 大小

#define ParamAddr_u8LanguageType              (ParamAddr_UserConfigParaBase)                                            //语言种类 逻辑地址
#define ParamSize_u8LanguageType              (sizeof(Language_TypeDef))                                                //语言种类 大小

#define ParamAddr_u8ClearFaultFlag            (ParamAddr_u8LanguageType + ParamSize_u8LanguageType)                     //清除故障 逻辑地址
#define ParamSize_u8ClearFaultFlag            (sizeof(uint8_t))                                                         //清除故障 大小

#define ParamAddr_u8OperationRecordFlag       (ParamAddr_u8ClearFaultFlag + ParamSize_u8ClearFaultFlag)                 //清除操作记录 逻辑地址
#define ParamSize_u8OperationRecordFlag       (sizeof(uint8_t))                                                         //清除操作记录 大小

#define ParamAddr_u8FactoryFlag               (ParamAddr_u8OperationRecordFlag + ParamSize_u8OperationRecordFlag)       //出厂设置使能 逻辑地址
#define ParamSize_u8FactoryFlag               (sizeof(uint8_t))                                                         //出厂设置使能 大小

#define ParamAddr_u8WifiResetFlag             (ParamAddr_u8FactoryFlag + ParamSize_u8FactoryFlag)                       //Wifi复位 逻辑地址
#define ParamSize_u8WifiResetFlag             (sizeof(uint8_t))                                                         //Wifi复位 大小

#define ParamAddr_u8BLTResetFlag              (ParamAddr_u8WifiResetFlag + ParamSize_u8WifiResetFlag)                   //蓝牙复位 逻辑地址
#define ParamSize_u8BLTResetFlag              (sizeof(uint8_t))                                                         //蓝牙复位 大小

#define ParamAddr_u8RemoteControl             (ParamAddr_u8BLTResetFlag + ParamSize_u8BLTResetFlag)                     //远程控制方式 逻辑地址
#define ParamSize_u8RemoteControl             (sizeof(uint8_t))                                                         //远程控制方式 大小

#define ParamAddr_stCTRadio                   (ParamAddr_u8RemoteControl + ParamSize_u8RemoteControl)                   //CT变比 逻辑地址
#define ParamSize_stCTRadio                   (sizeof(Display_SET_System_CTRadio))                                      //CT变比 大小

#define ParamAddr_u8IRDetectionFlag           (ParamAddr_stCTRadio + ParamSize_stCTRadio)                               //绝缘阻抗检测 逻辑地址
#define ParamSize_u8IRDetectionFlag           (sizeof(uint8_t))                                                         //绝缘阻抗检测 大小

#define ParamAddr_stDspUsartParas             (ParamAddr_u8IRDetectionFlag + ParamSize_u8IRDetectionFlag)               //串口参数显示设置 逻辑地址
#define ParamSize_stDspUsartParas             (sizeof(Display_SET_USART_Paras))                                         //串口参数显示设置 大小

#define ParamAddr_stTimeSync                  (ParamAddr_stDspUsartParas + ParamSize_stDspUsartParas)                   //时间设置 逻辑地址
#define ParamSize_stTimeSync                  (sizeof(Display_SET_System_TimeSync))                                     //时间设置 大小

#define ParamAddr_stPasswordModify            (ParamAddr_stTimeSync + ParamSize_stTimeSync)                             //密码修改 逻辑地址
#define ParamSize_stPasswordModify            (sizeof(Display_SET_System_PasswordModify))                               //密码修改 大小

#define ParamAddr_stProtectEnable             (ParamAddr_stPasswordModify + ParamSize_stPasswordModify)                 //保护使能 逻辑地址
#define ParamSize_stProtectEnable             (sizeof(Display_SET_System_ProtectEnable))                                //保护使能 大小

#define ParamAddr_stStrategy                  (ParamAddr_stProtectEnable + ParamSize_stProtectEnable)                   //策略参数 逻辑地址
#define ParamSize_stStrategy                  (sizeof(Display_SET_System_Strategy))                                     //策略参数 大小

#define ParamAddr_stPV                        (ParamAddr_stStrategy + ParamSize_stStrategy)                             //PV参数 逻辑地址
#define ParamSize_stPV                        (sizeof(Display_SET_PV))                                                  //PV参数 大小

#define ParamAddr_stBMS                       (ParamAddr_stPV + ParamSize_stPV)                                         //电池参数 逻辑地址
#define ParamSize_stBMS                       (sizeof(Display_SET_BMS))                                                 //电池参数 大小

#define ParamAddr_stGrid                      (ParamAddr_stBMS + ParamSize_stBMS)                                       //电网参数 逻辑地址
#define ParamSize_stGrid                      (sizeof(Display_SET_Grid))                                                //电网参数 大小

#define ParamAddr_stGen                       (ParamAddr_stGrid + ParamSize_stGrid)                                     //发电机参数 逻辑地址
#define ParamSize_stGen                       (sizeof(Display_SET_Gen))                                                 //发电机参数 大小

#define ParamAddr_stStatistical               (ParamAddr_stGrid + ParamSize_stGrid)                                     //统计数据 逻辑地址
#define ParamSize_stStatistical               (sizeof(Display_DATA_STATISTICAL))                                        //统计数据 大小

/***********************************************************************************************************************
 HistoryPara_t 存储地址划分
************************************************************************************************************************/
#define ParamAddr_HistoryParaBase             (0x002000)                                                                //历史信息的 基址
#define ParamSize_HistoryPara                 (sizeof(HistoryPara_t))                                                   //历史信息的 大小

#define ParamAddr_stFaultHistory              (ParamAddr_HistoryParaBase)                                               //历史故障 逻辑基址
#define ParamSize_stFaultHistory              (sizeof(Fault_Info_History))                                              //历史故障 大小

#define ParamAddr_stRecord                    (ParamAddr_stFaultHistory + ParamSize_stFaultHistory)                     //操作记录 逻辑基址
#define ParamSize_stRecord                    (sizeof(Record_Info))                                                     //操作记录 大小

typedef union
{
    uint8_t u8ExitFactoryParaTablCfg[ParamSize_ExitFactoryPara];
    ExitFactoryPara_t tExitFactoryParaStructCfg;
}ExitFactoryParaCfg_t;                                                                                                  //出厂参数联合体数据类型

typedef union
{
    uint8_t u8UserConfigParaTablCfg[ParamSize_UserConfigPara];
    UserConfigPara_t UserConfigParaStructCfg;
}UserConfigParaCfg_t;                                                                                                   //用户配置参数联合体数据类型

typedef union
{
    uint8_t u8HistoryParaTablCfg[ParamSize_HistoryPara];
    HistoryPara_t tHistoryParaStructCfg;
}HistoryParaCfg_t;                                                                                                      //历史记录参数联合体数据类型

extern ExitFactoryParaCfg_t tExitFactoryParaCfg;
extern UserConfigParaCfg_t tUserConfigParaCfg;
extern HistoryParaCfg_t tHistoryParaCfg;

typedef enum
{
    STORAGE_INIT,                                                                                                       //数据存储模块初始化
    STORAGE_RUNNING,                                                                                                    //数据存储模块运行
    STORAGE_DESTRCUCTION,                                                                                               //数据存储模块析构
    STORAGE_STATE_NULL 
}StorageStatus_TypeDef;

//测试代码，开发完毕后删除
//extern void Storage_Service_UserConfigPara_DefaultReload(void);

//Storage总初始化函数
void StorageInit(void);
//Storage总运行函数
void StorageRunning(void);
//Storage析构函数
void StorageDestruction(void);

//显示处理总入口函数,给main模块存储模块总接口函数
extern void SystemPara_Handler(void);
//初始化变量函数
extern void Storage_Service_InitVar(void);
//初始化变量函数
extern void Storage_Service_HwInit(void);
//系统参数读取
extern void SystemPara_ReadData(void);

//读取ATE数据
extern void Flash_Device_ATE_Read(uint16_t *pu16Buffer,uint32_t u32Read_length);
//ATE数据存储
extern void Flash_Device_ATE_Write(uint16_t *pu16Buffer,uint32_t u32Write_length);

//读取出厂校正数据
void Flash_Device_SampleAdjData_Read(TotalSampleAdjData_t *ptTotalSampleAdjData,uint32_t u32Read_length);

//写入出厂校正数据
void Flash_Device_SampleAdjData_Write(TotalSampleAdjData_t *ptTotalSampleAdjData,uint32_t u32Write_length);

//读取硬件版本数据
void Flash_Device_HardwareVersion_Read(uint8_t *pHardwareVersion,uint32_t u32Read_length);

//写入硬件版本数据
void Flash_Device_HardwareVersion_Write(uint8_t *pHardwareVersion,uint32_t u32Write_length);

//读取序列号数据
void Flash_Device_EESerialNumber_Read(uint8_t *pEESerialNumber,uint32_t u32Read_length);

//写入序列号数据
void Flash_Device_EESerialNumber_Write(uint8_t *pEESerialNumber,uint32_t u32Write_length);

//读取操作故障数据
extern void Flash_Device_FaultData_Read(Fault_Info_History *pStFaultBuffer,uint32_t u32Read_length);
//故障记录数据存储
void Flash_Device_FaultData_Write(Fault_Info_History *pStFaultBuffer,uint32_t u32Write_length);

//读取操作记录数据
extern void Flash_Device_OperateRecord_Read(Record_Info *pStRecordBuffer,uint32_t u32Read_length);
//操作记录数据存储
void Flash_Device_OperateRecord_Write(Record_Info *pStRecordBuffer,uint32_t u32Write_length);

//读取统计数据
extern void Flash_Device_StatisticsData_Read(Display_DATA_STATISTICAL *pStStatisticsBuffer,uint32_t u32Read_length);
//统计数据存储
void Flash_Device_StatisticsData_Write(Display_DATA_STATISTICAL *pStStatisticsBuffer,uint32_t u32Write_length);

//读取分时电价数据
extern void Flash_Device_ElecPriceData_Read(Display_SET_Grid_TimeDivisionElecPrice *pStElecPriceBuffer,uint32_t u32Read_length);
//分时电价数据存储
void Flash_Device_ElecPriceData_Write(Display_SET_Grid_TimeDivisionElecPrice *pStElecPriceBuffer,uint32_t u32Write_length);

//读取分时电价数据
extern void Flash_Device_StrategyData_Read(Display_SET_System_Strategy *pStStrategyBuffer,uint32_t u32Read_length);
//分时电价数据存储
void Flash_Device_StrategyData_Write(Display_SET_System_Strategy *pStStrategyBuffer,uint32_t u32Write_length);

//读取语言设置类型
extern void Flash_Device_LanguageType_Read(uint8_t *pu8LanguageType);
//语言设置类型数据存储
void Flash_Device_LanguageType_Write(uint8_t pu8LanguageType);

//读取控制方式设置类型
extern void Flash_Device_ControlMode_Read(uint8_t *pu8ControlMode);
//控制方式数据存储
void Flash_Device_ControlMode_Write(uint8_t pu8ControlMode);

//读取系统密码
extern void Flash_Device_Password_Read(uint8_t *pu8Password,uint32_t u32Read_length);
//系统密码数据存储
void Flash_Device_Password_Write(uint8_t *pu8Password,uint32_t u32Write_length);

//读取PCS串口信息
extern void Flash_Device_PCSSerial_Read(Display_SET_USART_Paras *pStPCSSerialBuffer,uint32_t u32Read_length);
//PCS串口信息数据存储
void Flash_Device_PCSSerial_Write(Display_SET_USART_Paras *pu8PCSSerial,uint32_t u32Write_length);

//读取CT信息
extern void Flash_Device_CTRadio_Read(Display_SET_System_CTRadio *pStCTRadioBuffer,uint32_t u32Read_length);
//CT信息数据存储
void Flash_Device_CTRadio_Write(Display_SET_System_CTRadio *pStCTRadioBuffer,uint32_t u32Write_length);

//读取保护参数使能信息
void Flash_Device_ProtectInfo_Read(Display_SET_System_ProtectEnable *pStProtectInfoBuffer,uint32_t u32Read_length);
//保护参数使能信息存储
void Flash_Device_ProtectInfo_Write(Display_SET_System_ProtectEnable *pStProtectInfoBuffer,uint32_t u32Write_length);

//读取绝缘阻抗检测使能状态信息
extern void Flash_Device_InsulationInfo_Read(uint8_t *pu8InsulationInfo);
//绝缘阻抗检测使能状态信息存储
void Flash_Device_InsulationInfo_Write(uint8_t pu8InsulationInfo);

//读取保护参数使能信息
void Flash_Device_PVInfo_Read(Display_SET_PV *pStPVBuffer,uint32_t u32Read_length);
//保护参数使能信息存储
void Flash_Device_PVInfo_Write(Display_SET_PV *pStPVBuffer,uint32_t u32Write_length);

//读取电池信息
void Flash_Device_BMSInfo_Read(Display_SET_BMS *pStBMSBuffer,uint32_t u32Read_length);
//电池信息存储
void Flash_Device_BMSInfo_Write(Display_SET_BMS *pStBMSBuffer,uint32_t u32Write_length);

//读取电网信息
void Flash_Device_GridInfo_Read(Display_SET_Grid *pStGridBuffer,uint32_t u32Read_length);
//电网信息存储
void Flash_Device_GridInfo_Write(Display_SET_Grid *pStGridBuffer,uint32_t u32Write_length);

//读取发电机设置信息类型
extern void Flash_Device_GenInfo_Read(Display_SET_Gen *pStGenBuffer,uint32_t u32Read_length);
//发电机设置信息存储
void Flash_Device_GenInfo_Write(Display_SET_Gen *pStGenBuffer,uint32_t u32Write_length);

//恢复出厂设置数据
extern void SystemPara_RestoreFactorySetData(void);
#pragma pack()
#endif

/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
