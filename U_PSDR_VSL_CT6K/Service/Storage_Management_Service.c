/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Storage_Manageent_Service.c 
 用途 : 存储管理服务
***********************************************************************************************************************/
#ifndef _LCD_STORAGEMANAGEMENT_C_
#define _LCD_STORAGEMANAGEMENT_C_

#include "HeadFile.h"
#include "Flash_Device.h"
#include "Storage_Management_Service.h"

#if STORAGE_SERVICE_MOUDLE

ExitFactoryParaCfg_t tExitFactoryParaCfg;                                                                               //出厂参数 Flash缓存
UserConfigParaCfg_t tUserConfigParaCfg;                                                                                 //用户配置参数 Flash缓存
HistoryParaCfg_t tHistoryParaCfg;                                                                                       //历史数据 Flash缓存
uint8_t ExitFactoryParaSaveFlag;                                                                                        //出厂参数 存储标志
uint8_t UserConfigParaSaveFlag;                                                                                         //用户配置参数 存储标志
uint8_t HistoryParaSaveFlag;                                                                                            //历史数据 存储标志
uint8_t LeaveFactoryParaSaveCnt = 3;                                                                                    //出厂参数工厂校正 写入次数

ExitFactoryPara_t ExitFactoryParaDaultTable;                                                                            //默认 出厂参数表
UserConfigPara_t UserConfigParaDaultTable;                                                                              //默认 用户配置参数表
HistoryPara_t HistoryParaDaultTable;                                                                                    //默认 默认历史数据参数表

StorageStatus_TypeDef gEnumStorageStatus = STORAGE_STATE_NULL;                                                          //存储模块状态机


/***********************************************************************************************************************
 功能：写 默认出厂参数表
***********************************************************************************************************************/
static void Storage_Service_ExitFactoryPara_DefaultWrite(uint8_t *pu8DefaultTable, uint16_t u16Index, uint16_t u16Length)
{
    uint16_t i = 0;
    uint8_t *pu8Temp;
    
    pu8Temp = (uint8_t *)tExitFactoryParaCfg.u8ExitFactoryParaTablCfg;
    
    for(i = 0; i < u16Length; i ++)
    {
        *(pu8Temp + u16Index) = *(pu8DefaultTable + u16Index);                                                          //赋值默认参数至tExitFactoryParaCfg缓存
        u16Index++;
    }
}

/***********************************************************************************************************************
 功能：写 默认用户配置参数表
***********************************************************************************************************************/
static void Storage_Service_UserConfigPara_DefaultWrite(uint8_t *pu8DefaultTable, uint16_t u16Index, uint16_t u16Length)
{
    uint16_t i = 0;
    uint8_t *pu8Temp;
    
    pu8Temp = (uint8_t *)tUserConfigParaCfg.u8UserConfigParaTablCfg;
    
    for(i = 0; i < u16Length; i ++)
    {
        *(pu8Temp + u16Index) = *(pu8DefaultTable + u16Index);                                                          //赋值默认参数至tUserConfigParaCfg缓存
        u16Index++;
    }
}

/***********************************************************************************************************************
 功能：写 默认历史记录参数表
***********************************************************************************************************************/
static void Storage_Service_HistoryPara_DefaultWrite(uint8_t *pu8DefaultTable, uint16_t u16Index, uint16_t u16Length)
{
    uint16_t i = 0;
    uint8_t *pu8Temp;
    
    pu8Temp = (uint8_t *)tHistoryParaCfg.u8HistoryParaTablCfg;
    
    for(i = 0; i < u16Length; i ++)
    {
        *(pu8Temp + u16Index) = *(pu8DefaultTable + u16Index);                                                          //赋值默认参数至tHistoryParaCfg缓存
        u16Index++;
    }
}

/***********************************************************************************************************************
 功能：出厂参数Checksum校验
***********************************************************************************************************************/
static uint8_t Storage_Service_ExitFactoryPara_CheckSumChk(uint16_t u16Length)
{
    uint32_t  u32SumTemp = 0;
    uint16_t   i = 0;
    uint8_t   *pu8Buf;
    
    pu8Buf = (uint8_t *)tExitFactoryParaCfg.u8ExitFactoryParaTablCfg;
    for(i = 0; i < u16Length; i++)
    {
        u32SumTemp += *(pu8Buf+i);
    }
    
    if(u32SumTemp == tExitFactoryParaCfg.tExitFactoryParaStructCfg.ExitFactoryParaCheckSum)
    {
        return(STATUS_TRUE);
    }
    else
    {
        return(STATUS_FALSE);
    }
}

/***********************************************************************************************************************
 功能：用户配置参数Checksum校验
***********************************************************************************************************************/
static uint8_t Storage_Service_UserConfigPara_CheckSumChk(uint16_t u16Length)
{
    uint32_t  u32SumTemp = 0;
    uint16_t   i = 0;
    uint8_t   *pu8Buf;
    
    pu8Buf = (uint8_t *)tUserConfigParaCfg.u8UserConfigParaTablCfg;
    for(i = 0; i < u16Length; i++)
    {
        u32SumTemp += *(pu8Buf+i);
    }
    
    if(u32SumTemp == tUserConfigParaCfg.UserConfigParaStructCfg.u16UserConfigParaCheckSum)
    {
        return(STATUS_TRUE);
    }
    else
    {
        return(STATUS_FALSE);
    }
}

/***********************************************************************************************************************
 功能：历史记录参数Checksum校验
***********************************************************************************************************************/
static uint8_t Storage_Service_HistoryPara_CheckSumChk(uint16_t u16Length)
{
    uint16_t  u16SumTemp = 0;
    uint16_t   i = 0;
    uint8_t   *pu8Buf;
    
    pu8Buf = (uint8_t *)tHistoryParaCfg.u8HistoryParaTablCfg;
    for(i = 0; i < u16Length; i++)
    {
        u16SumTemp += *(pu8Buf+i);
    }
    
    if(u16SumTemp == tHistoryParaCfg.tHistoryParaStructCfg.u16HistoryParaCheckSum)
    {
        return(STATUS_TRUE);
    }
    else
    {
        return(STATUS_FALSE);
    }
}

/***********************************************************************************************************************
 功能：读取 出厂默认参数表
***********************************************************************************************************************/
static void Storage_Service_ExitFactoryPara_Read(void)
{
    uint16_t u16ExitFactoryParaDefaultIndex = 0;
    uint8_t *pu8DefaultTable;
    uint8_t u8RepetitionsCnt = 3;                                                                                       //校验失败时，重复读取次数

    do
    {
        SPI_Flash_Device_GD25qxx_ReadBytes((uint8_t *)tExitFactoryParaCfg.u8ExitFactoryParaTablCfg, ParamAddr_ExitFactoryParaBase, ParamSize_ExitFactoryPara);
        if(Storage_Service_ExitFactoryPara_CheckSumChk(ParamSize_ExitFactoryPara - 2) == STATUS_TRUE)
        {
            return;
        }
    }while(--u8RepetitionsCnt != 0);

    pu8DefaultTable = (uint8_t *)(&ExitFactoryParaDaultTable);
    Storage_Service_ExitFactoryPara_DefaultWrite(pu8DefaultTable,u16ExitFactoryParaDefaultIndex,(ParamSize_ExitFactoryPara - 2));

    ExitFactoryParaSaveFlag = 1;                                                                                        //挂起存储标志
}

/***********************************************************************************************************************
 功能：读取 用户配置参数表
***********************************************************************************************************************/
static void Storage_Service_UserConfigPara_Read(void)
{
    uint16_t u16UserConfigParaDefaultIndex = 0;
    uint8_t *pu8DefaultTable;
    uint8_t u8RepetitionsCnt = 3;                                                                                       //校验失败时，重复读取次数

    do
    {
        SPI_Flash_Device_GD25qxx_ReadBytes((uint8_t *)tUserConfigParaCfg.u8UserConfigParaTablCfg, ParamAddr_UserConfigParaBase, ParamSize_UserConfigPara);//读出数据
        if(Storage_Service_UserConfigPara_CheckSumChk(ParamSize_UserConfigPara - 2) == STATUS_TRUE)                     //Checksum校验
        {
            return;
        }
    }while(--u8RepetitionsCnt != 0);

    pu8DefaultTable = (uint8_t *)(&UserConfigParaDaultTable);
    Storage_Service_UserConfigPara_DefaultWrite(pu8DefaultTable, u16UserConfigParaDefaultIndex, (ParamSize_UserConfigPara - 2));//写默认参数表到缓存

    UserConfigParaSaveFlag = 1;                                                                                         //挂起存储标志

}

/***********************************************************************************************************************
 功能：读取 历史记录参数表
***********************************************************************************************************************/
static void Storage_Service_HistoryPara_Read(void)
{
    uint16_t u16HistoryParaDefaultIndex = 0;
    uint8_t *pu8DefaultTable;
    uint8_t u8RepetitionsCnt = 3;                                                                                       //校验失败时，重复读取次数

    do
    {
        SPI_Flash_Device_GD25qxx_ReadBytes((uint8_t *)tHistoryParaCfg.u8HistoryParaTablCfg, ParamAddr_HistoryParaBase, ParamSize_HistoryPara);//读出数据
        if(Storage_Service_HistoryPara_CheckSumChk(ParamSize_HistoryPara - 2) == STATUS_TRUE)                           //Checksum校验
        {
            return;
        }
    }while(--u8RepetitionsCnt != 0);

    pu8DefaultTable = (uint8_t *)(&HistoryParaDaultTable);
    Storage_Service_HistoryPara_DefaultWrite(pu8DefaultTable,u16HistoryParaDefaultIndex,(ParamSize_HistoryPara - 2));  //写默认参数表到缓存

    HistoryParaSaveFlag = 1;                                                                                           //挂起存储标志
}

/***********************************************************************************************************************
 功能：写入 出厂默认参数表
***********************************************************************************************************************/
static void Storage_Service_ExitFactoryPara_Save(void)
{
    uint16_t  i;
    uint16_t  u16ChkSumTemp = 0;
    uint8_t   *u8Temp;
    uint8_t   u8RepetitionsCnt = 3;

    tExitFactoryParaCfg.tExitFactoryParaStructCfg.ExitFactoryParaCheckSum = 0;
    u8Temp = (uint8_t *)tExitFactoryParaCfg.u8ExitFactoryParaTablCfg;

    for(i = 0; i < (ParamSize_ExitFactoryPara - 2); i++)
    {
        tExitFactoryParaCfg.tExitFactoryParaStructCfg.ExitFactoryParaCheckSum += *(u8Temp + i);                         //计算校验和
    }

    do
    {
        SPI_Flash_Device_GD25qxx_WriteBytes(ParamAddr_ExitFactoryParaBase, ParamSize_ExitFactoryPara, (uint8_t *)tExitFactoryParaCfg.u8ExitFactoryParaTablCfg);//写参数
        SPI_Flash_Device_GD25qxx_ReadBytes((uint8_t *)&u16ChkSumTemp, ParamAddr_ExitFactoryParaBase + ParamSize_ExitFactoryPara - 2, 2);//读出Checksum，确认是否写入成功
        if(tExitFactoryParaCfg.tExitFactoryParaStructCfg.ExitFactoryParaCheckSum == u16ChkSumTemp)
        {
            return;
        }
    }while(--u8RepetitionsCnt != 0);
}

/***********************************************************************************************************************
 功能：写入 用户配置参数表
***********************************************************************************************************************/
static void Storage_Service_UserConfigPara_Save(void)
{
    uint16_t  i;
    uint16_t  u16ChkSumTemp = 0;
    uint8_t   *u8Temp;
    uint8_t   u8RepetitionsCnt = 3;

    tUserConfigParaCfg.UserConfigParaStructCfg.u16UserConfigParaCheckSum = 0;
    u8Temp = (uint8_t *)tUserConfigParaCfg.u8UserConfigParaTablCfg;

    for(i = 0; i < (ParamSize_UserConfigPara - 2); i++)
    {
        tUserConfigParaCfg.UserConfigParaStructCfg.u16UserConfigParaCheckSum += *(u8Temp + i);
    }

    do
    {
        SPI_Flash_Device_GD25qxx_WriteBytes(ParamAddr_UserConfigParaBase, ParamSize_UserConfigPara, (uint8_t *)tUserConfigParaCfg.u8UserConfigParaTablCfg);//写参数
        SPI_Flash_Device_GD25qxx_ReadBytes((uint8_t *)&u16ChkSumTemp, ParamAddr_UserConfigParaBase + ParamSize_UserConfigPara - 2, 2);//读出Checksum，确认是否写入成功
        if(tUserConfigParaCfg.UserConfigParaStructCfg.u16UserConfigParaCheckSum == u16ChkSumTemp)
        {
            return;
        }
    }while(--u8RepetitionsCnt != 0);
}

/***********************************************************************************************************************
 功能：写入 历史记录参数表
***********************************************************************************************************************/
static void Storage_Service_HistoryPara_Save(void)
{
    uint16_t  i;
    uint16_t  u16ChkSumTemp = 0;
    uint8_t   *u8Temp;
    uint8_t   u8RepetitionsCnt = 3;

    tHistoryParaCfg.tHistoryParaStructCfg.u16HistoryParaCheckSum = 0;
    u8Temp = (uint8_t *)tHistoryParaCfg.u8HistoryParaTablCfg;

    for(i = 0; i < (ParamSize_HistoryPara - 2); i++)
    {
        tHistoryParaCfg.tHistoryParaStructCfg.u16HistoryParaCheckSum += *(u8Temp + i);
    }

    do
    {
        SPI_Flash_Device_GD25qxx_WriteBytes(ParamAddr_HistoryParaBase, ParamSize_HistoryPara, (uint8_t *)tHistoryParaCfg.u8HistoryParaTablCfg);//写参数
        SPI_Flash_Device_GD25qxx_ReadBytes((uint8_t *)&u16ChkSumTemp, ParamAddr_HistoryParaBase + ParamSize_HistoryPara - 2, 2);//读出Checksum，确认是否写入成功
        if(tHistoryParaCfg.tHistoryParaStructCfg.u16HistoryParaCheckSum == u16ChkSumTemp)
        {
            return;
        }
    }while(--u8RepetitionsCnt != 0);
}

/***********************************************************************************************************************
 功能：ExitFactoryPara全局变量初始化默认值
***********************************************************************************************************************/
static void Storage_Service_ExitFactoryParaDaultTable_Init(void)
{
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tRGridVoltAdjPara.u16Proportion = 1000;                               //R相 电网电压 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tRGridVoltAdjPara.s16Intercept = 0;                                   //R相 电网电压 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tSGridVoltAdjPara.u16Proportion = 1000;                               //S相 电网电压 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tSGridVoltAdjPara.s16Intercept = 0;                                   //S相 电网电压 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tTGridVoltAdjPara.u16Proportion = 1000;                               //T相 电网电压 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tTGridVoltAdjPara.s16Intercept = 0;                                   //T相 电网电压 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tRGridCurrAdjPara.u16Proportion = 1000;                               //R相 电网电流 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tRGridCurrAdjPara.s16Intercept = 0;                                   //R相 电网电流 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tSGridCurrAdjPara.u16Proportion = 1000;                               //S相 电网电流 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tSGridCurrAdjPara.s16Intercept = 0;                                   //S相 电网电流 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tTGridCurrAdjPara.u16Proportion = 1000;                               //T相 电网电流 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tTGridCurrAdjPara.s16Intercept = 0;                                   //T相 电网电流 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tRInvVoltAdjPara.u16Proportion = 1000;                                //R相 逆变电压 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tRInvVoltAdjPara.s16Intercept = 0;                                    //R相 逆变电压 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tSInvVoltAdjPara.u16Proportion = 1000;                                //S相 逆变电压 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tSInvVoltAdjPara.s16Intercept = 0;                                    //S相 逆变电压 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tTInvVoltAdjPara.u16Proportion = 1000;                                //T相 逆变电压 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tTInvVoltAdjPara.s16Intercept = 0;                                    //T相 逆变电压 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tRInvCurrAdjPara.u16Proportion = 1000;                                //R相 逆变输出电流 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tRInvCurrAdjPara.s16Intercept = 0;                                    //R相 逆变输出电流 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tSInvCurrAdjPara.u16Proportion = 1000;                                //S相 逆变输出电流 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tSInvCurrAdjPara.s16Intercept = 0;                                    //S相 逆变输出电流 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tTInvCurrAdjPara.u16Proportion = 1000;                                //T相 逆变输出电流 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tTInvCurrAdjPara.s16Intercept = 0;                                    //T相 逆变输出电流 校正参数,截距系数,1000 倍

    ExitFactoryParaDaultTable.tTotalSampleAdjData.tRInvInductorCurrAdjPara.u16Proportion = 1000;                        //R相 逆变电感电流 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tRInvInductorCurrAdjPara.s16Intercept = 0;                            //R相 逆变电感电流 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tSInvInductorCurrAdjPara.u16Proportion = 1000;                        //S相 逆变电感电流 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tSInvInductorCurrAdjPara.s16Intercept = 0;                            //S相 逆变电感电流 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tTInvInductorCurrAdjPara.u16Proportion = 1000;                        //T相 逆变电感电流 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tTInvInductorCurrAdjPara.s16Intercept = 0;                            //T相 逆变电感电流 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tRGenVoltAdjPara.u16Proportion = 1000;                                //R相 发电机电压 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tRGenVoltAdjPara.s16Intercept = 0;                                    //R相 发电机电压 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tSGenVoltAdjPara.u16Proportion = 1000;                                //S相 发电机电压 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tSGenVoltAdjPara.s16Intercept = 0;                                    //S相 发电机电压 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tTGenVoltAdjPara.u16Proportion = 1000;                                //T相 发电机电压 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tTGenVoltAdjPara.s16Intercept = 0;                                    //T相 发电机电压 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tRGenCurrAdjPara.u16Proportion = 1000;                                //R相 发电机电流 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tRGenCurrAdjPara.s16Intercept = 0;                                    //R相 发电机电流 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tSGenCurrAdjPara.u16Proportion = 1000;                                //S相 发电机电流 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tSGenCurrAdjPara.s16Intercept = 0;                                    //S相 发电机电流 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tTGenCurrAdjPara.u16Proportion = 1000;                                //T相 发电机电流 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tTGenCurrAdjPara.s16Intercept = 0;                                    //T相 发电机电流 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tPBusVoltAdjPara.u16Proportion = 1000;                                //正(P) 母线电压 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tPBusVoltAdjPara.s16Intercept = 0;                                    //正(P) 母线电压 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tNBusVoltAdjPara.u16Proportion = 1000;                                //负(N) 母线电压 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tNBusVoltAdjPara.s16Intercept = 0;                                    //负(N) 母线电压 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tBuckBoostInducCurrAdjPara.u16Proportion = 1000;                      //Buck-Boost 电感电流 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tBuckBoostInducCurrAdjPara.s16Intercept = 0;                          //Buck-Boost 电感电流 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tMidBusVoltAdjPara.u16Proportion = 1000;                              //中间母线电压 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tMidBusVoltAdjPara.s16Intercept = 0;                                  //中间母线电压 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tBatVoltAdjPara.u16Proportion = 1000;                                 //电池电压 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tBatVoltAdjPara.s16Intercept = 0;                                     //电池电压 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tPV1VoltAdjPara.u16Proportion = 1000;                                 //PV1电压 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tPV1VoltAdjPara.s16Intercept = 0;                                     //PV1电压 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tPV1CurrAdjPara.u16Proportion = 1000;                                 //PV1电流 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tPV1CurrAdjPara.s16Intercept = 0;                                     //PV1电流 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tPV2VoltAdjPara.u16Proportion = 1000;                                 //PV2电压 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tPV2VoltAdjPara.s16Intercept = 0;                                     //PV2电压 校正参数,截距系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tPV2CurrAdjPara.u16Proportion = 1000;                                 //PV2电流 校正参数,比例系数,1000 倍
    ExitFactoryParaDaultTable.tTotalSampleAdjData.tPV2CurrAdjPara.s16Intercept = 0;                                     //PV2电流 校正参数,截距系数,1000 倍

    sprintf((char *)ExitFactoryParaDaultTable.u8CompanyId, "CVTE Co.,Ltd.");                                            //公司识别码
    sprintf((char *)ExitFactoryParaDaultTable.u8EESerialNumber, "CK-SXZBU23060043");                                    //序列号
}

/***********************************************************************************************************************
 功能：UserConfigPara全局变量初始化默认值
***********************************************************************************************************************/
static void Storage_Service_UserConfigParaDaultTable_Init(void)
{
    UserConfigParaDaultTable.u8LanguageType = LANGUAGE_ENGLISH;                                                         //语言
    UserConfigParaDaultTable.u8ClearFaultFlag = 0;                                                                      //清除故障
    UserConfigParaDaultTable.u8OperationRecordFlag = 0;                                                                 //清除操作记录
    UserConfigParaDaultTable.u8FactoryFlag = 0;                                                                         //恢复出厂设置
    UserConfigParaDaultTable.u8WifiResetFlag = 0;                                                                       //Wifi 复位
    UserConfigParaDaultTable.u8BLTResetFlag = 0;                                                                        //蓝牙复位
    UserConfigParaDaultTable.u8RemoteControl = 0;                                                                       //远程控制方式(默认 0) 0 本地 1远程
    UserConfigParaDaultTable.stCTRadio.u16CTCurrent = 0;                                                                //CT变比，电流变比
    UserConfigParaDaultTable.stCTRadio.u16CTVoltage = 0;                                                                //CT变比，电压变比
    UserConfigParaDaultTable.u8IRDetectionFlag = 0;                                                                     //绝缘阻抗检测(默认 0) 0 禁止 1 使能
    UserConfigParaDaultTable.stDspUsartParas.u8Address = 0x01;                                                          //DSP串口参数，通信地址
    UserConfigParaDaultTable.stDspUsartParas.u16BaudRate = 9600;                                                        //DSP串口参数，波特率
    UserConfigParaDaultTable.stTimeSync.u16Year = 23;                                                                   //默认时间设置，年
    UserConfigParaDaultTable.stTimeSync.u8Month = 6;                                                                    //默认时间设置，月
    UserConfigParaDaultTable.stTimeSync.u8Day = 12;                                                                     //默认时间设置，日
    UserConfigParaDaultTable.stTimeSync.u8Hour = 15;                                                                    //默认时间设置，时
    UserConfigParaDaultTable.stTimeSync.u8Min = 6;                                                                      //默认时间设置，分
    UserConfigParaDaultTable.stTimeSync.u8Sec = 30;                                                                     //默认时间设置，秒
    UserConfigParaDaultTable.stTimeSync.u16mSec = 50;                                                                   //默认时间设置，毫秒
    sprintf((char *)UserConfigParaDaultTable.stPasswordModify.u8ArrayOldPassword, "666666");                            //默认密码
    sprintf((char *)UserConfigParaDaultTable.stPasswordModify.u8ArrayNewPasswordFrist, "000000");                       //默认第一次输入密码
    sprintf((char *)UserConfigParaDaultTable.stPasswordModify.u8ArrayNewPasswordSecond, "000000");                      //默认第二次输入密码
    UserConfigParaDaultTable.stProtectEnable.u8IslandProtection = 0;                                                    //孤岛保护 使能
    UserConfigParaDaultTable.stProtectEnable.u8GroundProtection = 0;                                                    //接地保护 使能
    UserConfigParaDaultTable.stProtectEnable.u8LeakageProtection = 0;                                                   //漏电保护 使能
    UserConfigParaDaultTable.stProtectEnable.u8ArcPullingProtection = 0;                                                //拉弧保护 使能
    UserConfigParaDaultTable.stProtectEnable.u8OverheatProtection = 0;                                                  //过热保护 使能
    UserConfigParaDaultTable.stProtectEnable.u8LowVoltageCrossProtection = 0;                                           //低电压穿越保护 使能
    UserConfigParaDaultTable.stProtectEnable.u8HighVoltageCrossProtection = 0;                                          //高电压穿越保护 使能
    UserConfigParaDaultTable.stProtectEnable.u8LightProtection = 0;                                                     //防雷保护 使能
    UserConfigParaDaultTable.stProtectEnable.u8GeneratorProtection = 0;                                                 //发电机保护 使能
    UserConfigParaDaultTable.stProtectEnable.u8InsulationImpedanceProtection = 0;                                       //绝缘阻抗保护 使能
    UserConfigParaDaultTable.stProtectEnable.u8LowFrequencyCrossProtection = 0;                                         //低频率穿越保护 使能
    UserConfigParaDaultTable.stProtectEnable.u8HighFrequencyCrossProtection = 0;                                        //高频率穿越保护 使能
    UserConfigParaDaultTable.stProtectEnable.u8P_V_Protection = 0;                                                      //P(V)保护 使能
    UserConfigParaDaultTable.stProtectEnable.u8P_F_Protection = 0;                                                      //P(F)保护 使能
    UserConfigParaDaultTable.stProtectEnable.u8Q_V_Protection = 0;                                                      //Q(V)保护 使能
    UserConfigParaDaultTable.stProtectEnable.u8Q_P_Protection = 0;                                                      //Q(F)保护 使能
    UserConfigParaDaultTable.stProtectEnable.u8CPF_Protection = 0;                                                      //CPF保护 使能
    UserConfigParaDaultTable.stProtectEnable.u8CQ_Protection = 0;                                                       //CQ保护 使能
    
    UserConfigParaDaultTable.stStrategy.u8StrategyType = STRATEGY_GEN;                                                  //策略类别(默认0) 0:无策略 1:削峰填谷 2:定时充放电 3:自发自用 4:备电 5：发电机
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod1.u8StopSOC = 80;                            //削峰填谷策略参数，尖时SOC
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod1.s16Power = 3000;                           //削峰填谷策略参数，尖时功率
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod1.stPeriod.u8StartHour = 0;                  //削峰填谷策略参数，尖时起止时间
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod1.stPeriod.u8StartMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod1.stPeriod.u8StartSec = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod1.stPeriod.u8EndHour = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod1.stPeriod.u8EndMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod1.stPeriod.u8EndSec = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod2.u8StopSOC = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod2.s16Power = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod2.stPeriod.u8StartHour = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod2.stPeriod.u8StartMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod2.stPeriod.u8StartSec = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod2.stPeriod.u8EndHour = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod2.stPeriod.u8EndMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod2.stPeriod.u8EndSec = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod3.u8StopSOC = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod3.s16Power = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod3.stPeriod.u8StartHour = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod3.stPeriod.u8StartMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod3.stPeriod.u8StartSec = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod3.stPeriod.u8EndHour = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod3.stPeriod.u8EndMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stTipPeriod.stPeriod3.stPeriod.u8EndSec = 0;

    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod1.u8StopSOC = 0;                            //削峰填谷策略参数，峰时SOC
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod1.s16Power = 0;                             //削峰填谷策略参数，峰时功率
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod1.stPeriod.u8StartHour = 0;                 //削峰填谷策略参数，峰时起止时间
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod1.stPeriod.u8StartMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod1.stPeriod.u8StartSec = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod1.stPeriod.u8EndHour = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod1.stPeriod.u8EndMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod1.stPeriod.u8EndSec = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod2.u8StopSOC = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod2.s16Power = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod2.stPeriod.u8StartHour = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod2.stPeriod.u8StartMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod2.stPeriod.u8StartSec = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod2.stPeriod.u8EndHour = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod2.stPeriod.u8EndMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod2.stPeriod.u8EndSec = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod3.u8StopSOC = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod3.s16Power = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod3.stPeriod.u8StartHour = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod3.stPeriod.u8StartMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod3.stPeriod.u8StartSec = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod3.stPeriod.u8EndHour = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod3.stPeriod.u8EndMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stPeakPeriod.stPeriod3.stPeriod.u8EndSec = 0;

    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod1.u8StopSOC = 0;                            //削峰填谷策略参数，平时SOC
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod1.s16Power = 0;                             //削峰填谷策略参数，平时功率
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod1.stPeriod.u8StartHour = 0;                 //削峰填谷策略参数，平时起止时间
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod1.stPeriod.u8StartMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod1.stPeriod.u8StartSec = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod1.stPeriod.u8EndHour = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod1.stPeriod.u8EndMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod1.stPeriod.u8EndSec = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod2.u8StopSOC = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod2.s16Power = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod2.stPeriod.u8StartHour = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod2.stPeriod.u8StartMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod2.stPeriod.u8StartSec = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod2.stPeriod.u8EndHour = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod2.stPeriod.u8EndMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod2.stPeriod.u8EndSec = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod3.u8StopSOC = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod3.s16Power = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod3.stPeriod.u8StartHour = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod3.stPeriod.u8StartMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod3.stPeriod.u8StartSec = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod3.stPeriod.u8EndHour = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod3.stPeriod.u8EndMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stFlatPeriod.stPeriod3.stPeriod.u8EndSec = 0;

    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod1.u8StopSOC = 0;                          //削峰填谷策略参数，谷时SOC
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod1.s16Power = 0;                           //削峰填谷策略参数，谷时功率
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod1.stPeriod.u8StartHour = 0;               //削峰填谷策略参数，谷时起止时间
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod1.stPeriod.u8StartMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod1.stPeriod.u8StartSec = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod1.stPeriod.u8EndHour = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod1.stPeriod.u8EndMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod1.stPeriod.u8EndSec = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod2.u8StopSOC = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod2.s16Power = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod2.stPeriod.u8StartHour = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod2.stPeriod.u8StartMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod2.stPeriod.u8StartSec = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod2.stPeriod.u8EndHour = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod2.stPeriod.u8EndMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod2.stPeriod.u8EndSec = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod3.u8StopSOC = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod3.s16Power = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod3.stPeriod.u8StartHour = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod3.stPeriod.u8StartMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod3.stPeriod.u8StartSec = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod3.stPeriod.u8EndHour = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod3.stPeriod.u8EndMin = 0;
    UserConfigParaDaultTable.stStrategy.stTPFVStrategy.stValleyPeriod.stPeriod3.stPeriod.u8EndSec = 0;

    UserConfigParaDaultTable.stPV.u8PVControlWay = 0;                                                                   //PV参数，光伏控制方式(默认 0) 0独立 1 并联
    UserConfigParaDaultTable.stPV.u8IVCurveScan = 0;                                                                    //PV参数，IV曲线扫描(默认0) 0:禁止 1:扫描
    UserConfigParaDaultTable.stBMS.u8EnableFlag = 1;                                                                    //电池参数，BMS使能标志(默认 1) 0禁止 1 使能
    UserConfigParaDaultTable.stBMS.u8Type = BMS_TYPE_LFP;                                                               //电池参数，电池类型(默认4) 0:无电池 1:磷酸铁锂 2:铅酸电池 3:镍氢电池4:磷酸铁锂电池 5:锰酸锂电池 6: 钴酸锂电池7:三元材料电池 8: 聚合物锂离子电池9:钛酸锂电池
    UserConfigParaDaultTable.stBMS.u8WakeupFlag = 0;                                                                    //电池参数，电池唤醒标志(默认0) 0禁止 1使能
    UserConfigParaDaultTable.stBMS.u8ProtocolType = BMS_MANU_Pylon;                                                     //电池参数，电池协议类型(默认11):0:无电池 1:CVTE 2:LG 3:CATL 4:派能 5:Alpha 6:ESS 7:通用  8:FRONUS 9:Talegent 10:Tower 11:pylon
    UserConfigParaDaultTable.stBMS.stHMISetBMSParas.u8Address = 0x03;                                                   //电池参数，BMS通讯地址(默认 0x03)
    UserConfigParaDaultTable.stBMS.stHMISetBMSParas.u8BaudRate = 2;                                                     //电池参数，波特率(默认2) 0:2400 1:4800 2:9600 3:19200 4:38400 
    UserConfigParaDaultTable.stBMS.stHMISetBMSParas.u16MaxChargeCurrent = 10;                                           //电池参数，最大充电电流
    UserConfigParaDaultTable.stBMS.stHMISetBMSParas.u16MaxDisChargeCurrent = 10;                                        //电池参数，最大放电电流
    UserConfigParaDaultTable.stBMS.stHMISetBMSParas.u16HighVoltageProtectPoint = 500;                                   //电池参数，电池高压保护点
    UserConfigParaDaultTable.stBMS.stHMISetBMSParas.u16LowVoltageProtectPoint = 450;                                    //电池参数，电池低压保护点
    UserConfigParaDaultTable.stBMS.stHMISetBMSParas.u8ChargeFlag = 1;                                                   //电池参数，是否允许充电 0:禁止 1:使能 
    UserConfigParaDaultTable.stBMS.stHMISetBMSParas.u16ChargeCVVoltage = 520;                                           //电池参数，充电CV电压
    UserConfigParaDaultTable.stBMS.stHMISetBMSParas.u16ChargeFVVoltage = 500;                                           //电池参数，充电FV电压

    UserConfigParaDaultTable.stGrid.u8SellElectricityFlag = 0;                                                          //电网参数，电网买电标注(默认 0) 0禁止 1 卖电
    UserConfigParaDaultTable.stGrid.u8PreventReverseFlowControlFlag = 1;                                                //电网参数，防逆流控制标志(默认 0) 0禁止 1 使能
    UserConfigParaDaultTable.stGrid.u8SafetyRegulationType = 0;                                                         //电网参数，安规类别(默认0) 0:欧盟 1:英国 2:南非 3:澳大利亚
    /*
    UserConfigParaDaultTable.stGrid.stTimeDivisionElecPrice.stFlatPeriod = 0;
    UserConfigParaDaultTable.stGrid.stTimeDivisionElecPrice.stFlatPeriod = 0;
    UserConfigParaDaultTable.stGrid.stTimeDivisionElecPrice.stFlatPeriod = 0;
    UserConfigParaDaultTable.stGrid.stTimeDivisionElecPrice.stFlatPeriod = 0;
    */
    UserConfigParaDaultTable.stGrid.stMeterParars.u8Address = 0x02;                                                     //发电机参数，电表通讯地址(默认 0x02) 
    UserConfigParaDaultTable.stGrid.stMeterParars.u16BaudRate = 9600;                                                   //发电机参数，波特率(默认0) 0:9600 1:19200 2:38400 

    UserConfigParaDaultTable.stGen.stGenPara.u8EnableFlag = 0;                                                          //发电机参数，发电机使能标志(默认 0) 0禁止 1 使能
}

/***********************************************************************************************************************
 功能：HistoryPara全局变量初始化默认值
***********************************************************************************************************************/
static void Storage_Service_HistoryParaDaultTable_Init(void)
{
    ;
}

/***********************************************************************************************************************
 功能：数据范围检查
***********************************************************************************************************************/
void SystemPara_DataRangeCheck(void)
{
//出厂参数数 据范围检查
    if((900 > ExitFactoryParaDaultTable.tTotalSampleAdjData.tRGridVoltAdjPara.u16Proportion) || \
       (1100 < ExitFactoryParaDaultTable.tTotalSampleAdjData.tRGridVoltAdjPara.u16Proportion))
    {
        ExitFactoryParaDaultTable.tTotalSampleAdjData.tRGridVoltAdjPara.u16Proportion = 1000;
    }
    
    if((300 > ExitFactoryParaDaultTable.tTotalSampleAdjData.tRGridVoltAdjPara.s16Intercept) || \
       (-300 < ExitFactoryParaDaultTable.tTotalSampleAdjData.tRGridVoltAdjPara.s16Intercept))
    {
        ExitFactoryParaDaultTable.tTotalSampleAdjData.tRGridVoltAdjPara.s16Intercept = 0;
    }

//用户配置参数 数据范围检查


//历史数据参数 数据范围检查

}

/***********************************************************************************************************************
 功能：读取 存储参数
***********************************************************************************************************************/
void SystemPara_ReadData(void)
{
    StorageInit();
    gEnumStorageStatus = STORAGE_RUNNING;
    Delay_ms(100);
    Storage_Service_ExitFactoryPara_Read();                                                                             //读取出厂参数
    Storage_Service_UserConfigPara_Read();                                                                              //读取用户自定义配置参数
    Storage_Service_HistoryPara_Read();                                                                               //读取历史数据参数
    
}

/***********************************************************************************************************************
 功能：存储逻辑处理
***********************************************************************************************************************/
void SystemPara_Handler(void)
{
    
    if (STATUS_FALSE == TimeTask_GetFlag_100ms)
    {
        return;
    }

    switch (gEnumStorageStatus)
    {
        case STORAGE_INIT:                                                                                              //数据存储模块初始化
            {
                StorageInit();
                gEnumStorageStatus = STORAGE_RUNNING;
                
            }
            break;
        case STORAGE_RUNNING:                                                                                           //数据存储模块运行
            {
                StorageRunning();
                
            } 
            break;
        case STORAGE_DESTRCUCTION:                                                                                      //数据存储模块析构,用掉电检测
            {
                StorageDestruction();
            }
            break;
        default:
            break;
    }
}

/***********************************************************************************************************************
 功能：Storage模块全局变量初始化
************************************************************************************************************************/
void Storage_Service_InitVar(void)
{
    gEnumStorageStatus = STORAGE_INIT;

    Storage_Service_ExitFactoryParaDaultTable_Init();                                                                   //初始化 出厂参数
    Storage_Service_UserConfigParaDaultTable_Init();                                                                    //初始化 用户配置参数
    Storage_Service_HistoryParaDaultTable_Init();                                                                       //初始化 历史数据参数
}

/***********************************************************************************************************************
 功能：Storage模块析构
************************************************************************************************************************/
void Storage_Service_DestructionVar(void)
{
    StorageDestruction();
    gEnumStorageStatus = STORAGE_DESTRCUCTION;
}

/***********************************************************************************************************************
 功能：Storage模块硬件初始化
************************************************************************************************************************/
void Storage_Service_HwInit(void)
{
}

/***********************************************************************************************************************
 功能:初始化驱动，全局变量等
************************************************************************************************************************/
void StorageInit(void)
{   
    SPI_Flash_Device_GD25qxx_Init();
}

void Storage_Service_SaveData(uint16_t u16ParaAddr, uint32_t u32Write_length)
{
    ;
}


/***********************************************************************************************************************
 功能:Storage总运行函数
************************************************************************************************************************/
void StorageRunning(void)
{
    u32MinterCounter++;

    if(u32MinterCounter % 1 == 0)//立即存储
    {
    
        if(1 == ExitFactoryParaSaveFlag)
        {
            Storage_Service_ExitFactoryPara_Save();                                                                 //出厂参数
            ExitFactoryParaSaveFlag = 0;
        }
        if(1 == UserConfigParaSaveFlag)
        {
            Storage_Service_UserConfigPara_Save();                                                                  //用户配置参数
            UserConfigParaSaveFlag = 0;
        }
        if(1 == HistoryParaSaveFlag)
        {
            Storage_Service_HistoryPara_Save();                                                                   //历史信息
            HistoryParaSaveFlag = 0;
        }
        
        if(LeaveFactoryParaSaveCnt)
        {
            Storage_Service_ExitFactoryPara_Save();
            LeaveFactoryParaSaveCnt--;
        }
        //Storage_Service_UserConfigPara_Save();
    }
    else if(u32MinterCounter % 15 == 9000)                                                                          //15 分钟定时存储
    {
        ;
    }
    else if(u32MinterCounter % 60 == 36000)                                                                         //60 分钟定时存储
    {
        ;
    }
    else
    {
        return;
    }
}

/***********************************************************************************************************************
 功能:Storage析构函数，用于保存掉电触发储存实时运行数据
************************************************************************************************************************/
void StorageDestruction(void)
{

}

/***********************************************************************************************************************
 存储模块对外接口：(1) 出厂配置数据接口
************************************************************************************************************************/

/***********************************************************************************************************************
 功能:从FLASH读取出厂校正数据
************************************************************************************************************************/
void Flash_Device_SampleAdjData_Read(TotalSampleAdjData_t *ptTotalSampleAdjData,uint32_t u32Read_length)
{
    memcpy(ptTotalSampleAdjData, (&tExitFactoryParaCfg.tExitFactoryParaStructCfg.tTotalSampleAdjData), u32Read_length);
}

/***********************************************************************************************************************
 功能:出厂校正数据存储到Flash缓存区
************************************************************************************************************************/
void Flash_Device_SampleAdjData_Write(TotalSampleAdjData_t *ptTotalSampleAdjData,uint32_t u32Write_length)
{
    if(memcmp(ptTotalSampleAdjData, &tExitFactoryParaCfg.tExitFactoryParaStructCfg.tTotalSampleAdjData, u32Write_length) == 0)
    {
        return;
    }
    else
    {
        memcpy(&tExitFactoryParaCfg.tExitFactoryParaStructCfg.tTotalSampleAdjData, ptTotalSampleAdjData , u32Write_length);
        ExitFactoryParaSaveFlag = 1;
    }
}

/***********************************************************************************************************************
 功能:从FLASH读取出厂硬件版本数据
************************************************************************************************************************/
void Flash_Device_HardwareVersion_Read(uint8_t *pHardwareVersion,uint32_t u32Read_length)
{
    memcpy(pHardwareVersion, (&tExitFactoryParaCfg.tExitFactoryParaStructCfg.u8HardwareVersion), u32Read_length);
}

/***********************************************************************************************************************
 功能:出厂硬件版本数据存储到Flash缓存区
************************************************************************************************************************/
void Flash_Device_HardwareVersion_Write(uint8_t *pHardwareVersion,uint32_t u32Write_length)
{
    if(memcmp(pHardwareVersion, &tExitFactoryParaCfg.tExitFactoryParaStructCfg.u8HardwareVersion, u32Write_length) == 0)
    {
        return;
    }
    else
    {
        memcpy(&tExitFactoryParaCfg.tExitFactoryParaStructCfg.u8HardwareVersion, pHardwareVersion , u32Write_length);
        ExitFactoryParaSaveFlag = 1;
    }
}

/***********************************************************************************************************************
 功能:从FLASH读取出厂序列号数据
************************************************************************************************************************/
void Flash_Device_EESerialNumber_Read(uint8_t *pEESerialNumber,uint32_t u32Read_length)
{
    memcpy(pEESerialNumber, (&tExitFactoryParaCfg.tExitFactoryParaStructCfg.u8EESerialNumber), u32Read_length);
}

/***********************************************************************************************************************
 功能:出厂序列号数据存储到Flash缓存区
************************************************************************************************************************/
void Flash_Device_EESerialNumber_Write(uint8_t *pEESerialNumber,uint32_t u32Write_length)
{
    if(memcmp(pEESerialNumber, &tExitFactoryParaCfg.tExitFactoryParaStructCfg.u8EESerialNumber, u32Write_length) == 0)
    {
        return;
    }
    else
    {
        memcpy(&tExitFactoryParaCfg.tExitFactoryParaStructCfg.u8EESerialNumber, pEESerialNumber , u32Write_length);
        ExitFactoryParaSaveFlag = 1;
    }
}

/***********************************************************************************************************************
 存储模块对外接口：(2) 用户配置数据接口
************************************************************************************************************************/
/***********************************************************************************************************************
 功能:从FLASH读取故障告警数据
************************************************************************************************************************/
void Flash_Device_FaultData_Read(Fault_Info_History *pStFaultBuffer,uint32_t u32Read_length)
{
    memcpy(pStFaultBuffer, (&tHistoryParaCfg.tHistoryParaStructCfg.stFaultHistory), u32Read_length);
}

/***********************************************************************************************************************
 功能:故障告警数据存储到Flash缓存区
************************************************************************************************************************/
void Flash_Device_FaultData_Write(Fault_Info_History *pStFaultBuffer,uint32_t u32Write_length)
{
    if(memcmp(pStFaultBuffer, &tHistoryParaCfg.tHistoryParaStructCfg.stFaultHistory, u32Write_length) == 0)
    {
        return;
    }
    else
    {
        memcpy(&tHistoryParaCfg.tHistoryParaStructCfg.stFaultHistory, pStFaultBuffer , u32Write_length);
        HistoryParaSaveFlag = 1;
    }
}

/***********************************************************************************************************************
 功能:从FLASH读取操作记录数据
************************************************************************************************************************/
void Flash_Device_OperateRecord_Read(Record_Info *pStRecordBuffer,uint32_t u32Read_length)
{
    memcpy(pStRecordBuffer, (&tHistoryParaCfg.tHistoryParaStructCfg.stRecord), u32Read_length);
}

/***********************************************************************************************************************
 功能:操作记录数据存储到Flash缓存
************************************************************************************************************************/
void Flash_Device_OperateRecord_Write(Record_Info *pStRecordBuffer,uint32_t u32Write_length)
{
    if(memcmp(pStRecordBuffer, &tHistoryParaCfg.tHistoryParaStructCfg.stRecord, u32Write_length) == 0)
    {
        return;
    }
    else
    {
        memcpy(&tHistoryParaCfg.tHistoryParaStructCfg.stRecord, pStRecordBuffer, u32Write_length);
        HistoryParaSaveFlag = 1;
    }
}

/***********************************************************************************************************************
 功能:从FLASH读取统计数据
************************************************************************************************************************/
void Flash_Device_StatisticsData_Read(Display_DATA_STATISTICAL* pStStatisticsBuffer,uint32_t u32Read_length)
{
    memcpy(pStStatisticsBuffer, &tUserConfigParaCfg.UserConfigParaStructCfg.stStatistical, u32Read_length);
}

/***********************************************************************************************************************
 功能:统计数据存储到Flash缓存
************************************************************************************************************************/
void Flash_Device_StatisticsData_Write(Display_DATA_STATISTICAL* pStStatisticsBuffer,uint32_t u32Write_length)
{
    if(memcmp(pStStatisticsBuffer,&tUserConfigParaCfg.UserConfigParaStructCfg.stStatistical,u32Write_length) == 0)
    {
        return;
    }
    else
    {
        memcpy(&tUserConfigParaCfg.UserConfigParaStructCfg.stStatistical, pStStatisticsBuffer, u32Write_length);
        UserConfigParaSaveFlag = 1;
    }
}

/***********************************************************************************************************************
 功能:从FLASH读取分时电价数据
************************************************************************************************************************/
void Flash_Device_ElecPriceData_Read(Display_SET_Grid_TimeDivisionElecPrice* pStElecPriceBuffer,uint32_t u32Read_length)
{
    memcpy(pStElecPriceBuffer, (&tUserConfigParaCfg.UserConfigParaStructCfg.stGrid.stTimeDivisionElecPrice), u32Read_length);
}

/***********************************************************************************************************************
 功能:分时电价数据存储到Flash缓存
************************************************************************************************************************/
void Flash_Device_ElecPriceData_Write(Display_SET_Grid_TimeDivisionElecPrice* pStElecPriceBuffer,uint32_t u32Write_length)
{
    if(memcmp(pStElecPriceBuffer, (&tUserConfigParaCfg.UserConfigParaStructCfg.stGrid.stTimeDivisionElecPrice), u32Write_length) == 0)
    {
        return;
    }
    else
    {
        memcpy(&tUserConfigParaCfg.UserConfigParaStructCfg.stGrid.stTimeDivisionElecPrice, pStElecPriceBuffer, u32Write_length);
        UserConfigParaSaveFlag = 1;
    }
}

/***********************************************************************************************************************
 功能:从FLASH读取系统策略数据
************************************************************************************************************************/
void Flash_Device_StrategyData_Read(Display_SET_System_Strategy* pStStrategyBuffer,uint32_t u32Read_length)
{
    memcpy(pStStrategyBuffer, (&tUserConfigParaCfg.UserConfigParaStructCfg.stStrategy), u32Read_length);
}

/***********************************************************************************************************************
 功能:系统策略数据存储到Flash缓存
************************************************************************************************************************/
void Flash_Device_StrategyData_Write(Display_SET_System_Strategy* pStStrategyBuffer,uint32_t u32Write_length)
{
    if(memcmp(pStStrategyBuffer, (&tUserConfigParaCfg.UserConfigParaStructCfg.stStrategy), u32Write_length) == 0)
    {
        return;
    }
    else
    {
        memcpy(&tUserConfigParaCfg.UserConfigParaStructCfg.stStrategy, pStStrategyBuffer, u32Write_length);
        UserConfigParaSaveFlag = 1;
    }
}

/***********************************************************************************************************************
 功能:从FLASH读取语言类型数据
************************************************************************************************************************/
void Flash_Device_LanguageType_Read(uint8_t *pu8LanguageType)
{
    memcpy(pu8LanguageType, (&tUserConfigParaCfg.UserConfigParaStructCfg.u8LanguageType), 1);
}

/***********************************************************************************************************************
 功能:语言类型数据存储到Flash缓存
************************************************************************************************************************/
void Flash_Device_LanguageType_Write(uint8_t pu8LanguageType)
{
    if(tUserConfigParaCfg.UserConfigParaStructCfg.u8LanguageType == pu8LanguageType)
    {
        return;
    }
    else
    {
        memcpy(&tUserConfigParaCfg.UserConfigParaStructCfg.u8LanguageType, &pu8LanguageType, 1);
        UserConfigParaSaveFlag = 1;
    }
}

/***********************************************************************************************************************
 功能:从FLASH读取控制方式数据
************************************************************************************************************************/
void Flash_Device_ControlMode_Read(uint8_t *pu8ControlMode)
{
    memcpy(pu8ControlMode, (&tUserConfigParaCfg.UserConfigParaStructCfg.u8RemoteControl), 1);
}

/***********************************************************************************************************************
 功能:控制方式数据存储到Flash缓存
************************************************************************************************************************/
void Flash_Device_ControlMode_Write(uint8_t pu8ControlMode)
{
    if(tUserConfigParaCfg.UserConfigParaStructCfg.u8RemoteControl == pu8ControlMode)
    {
        return;
    }
    else
    {
        memcpy(&tUserConfigParaCfg.UserConfigParaStructCfg.u8RemoteControl, &pu8ControlMode, 1);
        UserConfigParaSaveFlag = 1;
    }
}

/***********************************************************************************************************************
 功能:从FLASH读取系统密码数据
************************************************************************************************************************/
void Flash_Device_Password_Read(uint8_t *pu8PassWord,uint32_t u32Read_length)
{
    memcpy(pu8PassWord, (&tUserConfigParaCfg.UserConfigParaStructCfg.stPasswordModify.u8ArrayOldPassword), u32Read_length);
}
/***********************************************************************************************************************
 功能:系统密码数据存储到Flash缓存
************************************************************************************************************************/
void Flash_Device_Password_Write(uint8_t *pu8Password,uint32_t u32Write_length)
{
    if(memcmp(pu8Password, (&tUserConfigParaCfg.UserConfigParaStructCfg.stPasswordModify.u8ArrayOldPassword), u32Write_length) == 0)
    {
        return;
    }
    else
    {
        memcpy(&tUserConfigParaCfg.UserConfigParaStructCfg.stPasswordModify.u8ArrayOldPassword, pu8Password, u32Write_length);
        UserConfigParaSaveFlag = 1;
    }
}

/***********************************************************************************************************************
 功能:从FLASH读取PCS串口数据
************************************************************************************************************************/
void Flash_Device_PCSSerial_Read(Display_SET_USART_Paras *pStPCSSerialBuffer,uint32_t u32Read_length)
{
    memcpy(pStPCSSerialBuffer, (&tUserConfigParaCfg.UserConfigParaStructCfg.stDspUsartParas), u32Read_length);
}

/***********************************************************************************************************************
 功能:PCS串口数据存储到Flash缓存
************************************************************************************************************************/
void Flash_Device_PCSSerial_Write(Display_SET_USART_Paras *pu8PCSSerial,uint32_t u32Write_length)
{
    if(memcmp(pu8PCSSerial, (&tUserConfigParaCfg.UserConfigParaStructCfg.stDspUsartParas), u32Write_length) == 0)
    {
        return;
    }
    else
    {
        memcpy(&tUserConfigParaCfg.UserConfigParaStructCfg.stDspUsartParas, pu8PCSSerial, u32Write_length);
        UserConfigParaSaveFlag = 1;
    }
}

/***********************************************************************************************************************
 功能:从FLASH读取CT变比信息
************************************************************************************************************************/
void Flash_Device_CTRadio_Read(Display_SET_System_CTRadio *pStCTRadioBuffer,uint32_t u32Read_length)
{
    memcpy(pStCTRadioBuffer, (&tUserConfigParaCfg.UserConfigParaStructCfg.stCTRadio), u32Read_length);
}

/***********************************************************************************************************************
 功能:CT变比信息存储到Flash缓存
************************************************************************************************************************/
void Flash_Device_CTRadio_Write(Display_SET_System_CTRadio *pStCTRadioBuffer,uint32_t u32Write_length)
{
    if(memcmp(pStCTRadioBuffer,(&tUserConfigParaCfg.UserConfigParaStructCfg.stCTRadio),u32Write_length) == 0)
    {
        return;
    }
    else
    {
        memcpy(&tUserConfigParaCfg.UserConfigParaStructCfg.stCTRadio, pStCTRadioBuffer, u32Write_length);
        UserConfigParaSaveFlag = 1;
    }
}

/***********************************************************************************************************************
 功能:从FLASH读取保护参数使能信息
************************************************************************************************************************/
void Flash_Device_ProtectInfo_Read(Display_SET_System_ProtectEnable *pStProtectInfoBuffer,uint32_t u32Read_length)
{
    memcpy(pStProtectInfoBuffer, (&tUserConfigParaCfg.UserConfigParaStructCfg.stProtectEnable), u32Read_length);
}

/***********************************************************************************************************************
 功能:保护参数使能信息存储到Flash缓存
************************************************************************************************************************/
void Flash_Device_ProtectInfo_Write(Display_SET_System_ProtectEnable *pStProtectInfoBuffer,uint32_t u32Write_length)
{
    if(memcmp(pStProtectInfoBuffer, (&tUserConfigParaCfg.UserConfigParaStructCfg.stProtectEnable), u32Write_length) == 0)
    {
        return;
    }
    else
    {
        memcpy(&tUserConfigParaCfg.UserConfigParaStructCfg.stProtectEnable, pStProtectInfoBuffer, u32Write_length);
        UserConfigParaSaveFlag = 1;
    }
}

/***********************************************************************************************************************
 功能:从FLASH读取绝缘阻抗使能数据
************************************************************************************************************************/
void Flash_Device_InsulationInfo_Read(uint8_t *pu8InsulationInfo)
{
    memcpy(pu8InsulationInfo, (&tUserConfigParaCfg.UserConfigParaStructCfg.u8IRDetectionFlag), 1);
}

/***********************************************************************************************************************
 功能:绝缘阻抗使能数据存储到Flash缓存
************************************************************************************************************************/
void Flash_Device_InsulationInfo_Write(uint8_t pu8InsulationInfo)
{
    if(tUserConfigParaCfg.UserConfigParaStructCfg.u8IRDetectionFlag == pu8InsulationInfo)
    {
        return;
    }
    else
    {
        memcpy(&tUserConfigParaCfg.UserConfigParaStructCfg.u8IRDetectionFlag, &pu8InsulationInfo, 1);
        UserConfigParaSaveFlag = 1;
    }
}

/***********************************************************************************************************************
 功能:从FLASH读取PV参数使能信息
************************************************************************************************************************/
void Flash_Device_PVInfo_Read(Display_SET_PV *pStPVBuffer,uint32_t u32Read_length)
{
    memcpy(pStPVBuffer, (&tUserConfigParaCfg.UserConfigParaStructCfg.stPV), u32Read_length);
}

/***********************************************************************************************************************
 功能:PV参数使能信息存储到Flash缓存
************************************************************************************************************************/
void Flash_Device_PVInfo_Write(Display_SET_PV *pStPVBuffer,uint32_t u32Write_length)
{
    if(memcmp(pStPVBuffer, (&tUserConfigParaCfg.UserConfigParaStructCfg.stPV), u32Write_length) == 0)
    {
        return;
    }
    else
    {
        memcpy(&tUserConfigParaCfg.UserConfigParaStructCfg.stPV, pStPVBuffer, u32Write_length);
        UserConfigParaSaveFlag = 1;
    }
}

/***********************************************************************************************************************
 功能:从FLASH读取BMS参数信息
************************************************************************************************************************/
void Flash_Device_BMSInfo_Read(Display_SET_BMS *pStBMSBuffer,uint32_t u32Read_length)
{
    memcpy(pStBMSBuffer, (&tUserConfigParaCfg.UserConfigParaStructCfg.stBMS), u32Read_length);
}
/***********************************************************************************************************************
 功能:BMS参数信息存储到Flash缓存
************************************************************************************************************************/
void Flash_Device_BMSInfo_Write(Display_SET_BMS *pStBMSBuffer,uint32_t u32Write_length)
{
    if(memcmp(pStBMSBuffer, (&tUserConfigParaCfg.UserConfigParaStructCfg.stBMS), u32Write_length) == 0)
    {
        return;
    }
    else
    {
        memcpy(&tUserConfigParaCfg.UserConfigParaStructCfg.stBMS, pStBMSBuffer, u32Write_length);
        UserConfigParaSaveFlag = 1;
    }
}

/***********************************************************************************************************************
 功能:从FLASH读取电网参数使能信息
************************************************************************************************************************/
void Flash_Device_GridInfo_Read(Display_SET_Grid *pStGridBuffer,uint32_t u32Read_length)
{
    memcpy(pStGridBuffer, (&tUserConfigParaCfg.UserConfigParaStructCfg.stGrid), u32Read_length);
}

/***********************************************************************************************************************
 功能:电网参数使能信息存储到Flash缓存
************************************************************************************************************************/
void Flash_Device_GridInfo_Write(Display_SET_Grid *pStGridBuffer,uint32_t u32Write_length)
{
    if(memcmp(pStGridBuffer, (&tUserConfigParaCfg.UserConfigParaStructCfg.stGrid), u32Write_length) == 0)
    {
        return;
    }
    else
    {
        memcpy(&tUserConfigParaCfg.UserConfigParaStructCfg.stGrid, pStGridBuffer, u32Write_length);
        UserConfigParaSaveFlag = 1;
    }
}

/***********************************************************************************************************************
 功能:从FLASH读取发电机使能信息
************************************************************************************************************************/
void Flash_Device_GenInfo_Read(Display_SET_Gen *pStGenBuffer,uint32_t u32Read_length)
{
    memcpy(pStGenBuffer, (&tUserConfigParaCfg.UserConfigParaStructCfg.stGen), u32Read_length);
}

/***********************************************************************************************************************
 功能:发电机使能信息存储到Flash缓存
************************************************************************************************************************/
void Flash_Device_GenInfo_Write(Display_SET_Gen *pStGenBuffer,uint32_t u32Write_length)
{
    if(memcmp(pStGenBuffer, (&tUserConfigParaCfg.UserConfigParaStructCfg.stGen), u32Write_length) == 0)
    {
        return;
    }
    else
    {
        memcpy(&tUserConfigParaCfg.UserConfigParaStructCfg.stGen, pStGenBuffer, u32Write_length);
        UserConfigParaSaveFlag = 1;
    }
}
/***********************************************************************************************************************
 功能:恢复出厂设置数据
************************************************************************************************************************/
void SystemPara_RestoreFactorySetData(void)
{
    Storage_Service_ExitFactoryParaDaultTable_Init();                                                                   //初始化 出厂参数

    Storage_Service_UserConfigParaDaultTable_Init();                                                                    //初始化 用户配置参数
    UserConfigParaSaveFlag = 1;
    //Storage_Service_HistoryParaDaultTable_Init();                                                                     //初始化 历史数据参数
    //HistoryParaSaveFlag = 1;
}
#endif
#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
