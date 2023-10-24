/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : DisplayChineseTab.h 
 用途 : 用于存放中文显示信息表，ANSI编码格式
***********************************************************************************************************************/
#ifndef __CHINESE_TAB_H__
#define __CHINESE_TAB_H__
#include "HeadFile.h"
#include "LCD_Service.h"

#if LCD_CHINESE_DISP_TEST


//中文HOME界面 
extern void updateDisplayHomeData_Chinese(void);
//中文LOGIN界面
extern void updateDisplayLoginData_Chinese(char* sLoginPassword);
//中文SET界面
extern void updateDisplaySetData_Chinese(uint8_t u8SetIndex);
//中文SystemSet界面
extern void updateDisplaySystemSetData_Chinese(uint8_t u8SetIndex);
//中文LanguageSystemSet界面
extern void updateDisplaySystemLanguageSetData_Chinese(Language_TypeDef u8SetIndex);
//中文 设置系统Time界面
extern void updateDisplaySystemTimeSetData_Chinese(char* sDate,char* sTime,Week_TypeDef eWeek);
//中文 设置系统Password界面
extern void updateDisplaySystemPasswordSetData_Chinese(char* sOldPassword,char* sNewPassword,char* sConfirmPassword);
//中文 登陆密码错误提示界面信息
extern void updateDisplayTipLoginError_Chinese(void);
//中文 密码修改密码设置位数不够6位提示界面信息
extern void updateDisplayTipPasswordShort_Chinese(void);
//中文 密码修改旧的密码输入错误提示界面信息
extern void updateDisplayTipOldPasswordError_Chinese(void);
//中文 密码修改两次输入的新密码不一致提示界面信息
extern void updateDisplayTipOldPasswordNotMatch_Chinese(void);
//中文 密码修改输入的新密码和历史密码重合提示界面信息
extern void updateDisplayTipOldPasswordOverlaps_Chinese(void);
//中文 设置系统通信复位设置界面信息
extern void updateDisplaySystemCommResetData_Chinese(Baud_TypeDef u8SetIndex);
//中文 设置系统串口设置界面信息
extern void updateDisplaySystemSerialSetData_Chinese(bool_t bEnableFlag,char*strAddress,char*strBaud,SERIALUSE_TypeDef enumSerialUse);
//中文 设置系统通信复位设置界面信息
extern void updateDisplaySystemRemoteControlData_Chinese(ENABLE_TypeDef u8SetIndex);
//中文 系统策略设置界面信息
extern void updateDisplaySystemStrategySetData_Chinese(STRATEGY_TypeDef u8StrategyIndex);
//中文 系统备电策略设置界面信息
extern void updateDisplaySystemBackupStrategySetData_Chinese(char* strPower);
//中文 系统TPFV策略时间段设置界面信息
extern void updateDisplaySystemSelfStrategySetData_Chinese(void);
//中文 发电机策略设置界面信息
extern void updateDisplaySystemGenStrategySetData_Chinese(char* strForbidSOC,char* strSupplySOC);  
//中文 系统TPFV策略设置界面信息
extern void updateDisplaySystemTPFVStrategyAbstractSetData_Chinese(TPFV_TypeDef u8TPFVStrategyIndex);
//中文 系统TPFV策略设置界面信息
extern void updateDisplaySystemTPFVStrategySetData_Chinese(uint8_t sU8TPFVSetCounter,TPFV_TypeDef enum_tpfv);
//中文 系统TPFV策略时间段设置界面信息
extern void updateDisplaySystemTPFVStrategyPeriodSetData_Chinese(char* strStopSOC,char* strPower, TPFV_TypeDef enum_tpfv, TPFV_Strategy_TypeDef enumTPFVPeriod);
//中文 设置系统绝缘检测设置界面信息
extern void updateDisplaySystemInsulationDetetionData_Chinese(ENABLE_TypeDef u8SetIndex);
//中文 定时充放电策略设置界面信息
extern void updateDisplaySystemRegularStrategySetData_Chinese(REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef u8RegularStrategyIndex);
//中文 定时充放电策略时间段设置界面信息
extern void updateDisplaySystemRegularStrategyPeriodSetData_Chinese(char* strStopSOC,char* strPower, char* strStartTime, char* strEndTime,REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef enum_Period);
//中文 定时充放电策略设置界面信息
extern void updateDisplaySystemRegularStrategyAbstractSetData_Chinese(REGULAR_TypeDef u8RegularStrategyIndex);
//中文 设置系统CT变比设置界面信息
//extern void updateDisplaySystemCTRatioData_Chinese(bool_t bEnableFlag,char* sCurrentCT,char* sVoltageCT);
//中文 实时统计数据界面
extern void updateDisplayStatisticsData_Chinese(uint8_t sU8StatisticsCounter);
//中文 设置通过提示界面信息
extern void updateDisplayTipSetPassed_Chinese(void);
//中文 设置系统保护使能设置界面信息
extern void updateDisplayProtectSetData_Chinese(PROTECTSETAction_TypeDef u8SetIndex);
extern void updateDisplayProtectItemNameSetData_Chinese(ENABLE_CLASS_TypeDef enableClass,char * sEnableName_Chinese);
extern void updateDisplayProtectItemSetData_Chinese(ENABLE_TypeDef sU8ProtectSelected,char * sEnableName);
//中文 光伏设置界面
extern void updateDisplayPVSetData_Chinese(uint8_t u8PVSetIndex);
//中文 光伏控制设置界面
extern void updateDisplayPVControlWaySetData_Chinese(uint8_t u8PVContWaySetIndex);
//中文 电池设置设置界面
extern void updateDisplayBMSSetData_Chinese(uint8_t sU8BMSSetCounter);
//中文 电池厂商设置设置界面
extern void updateDisplayBatteryManufacturerSetData_Chinese(uint8_t sU8BatteryManufacturerCounter);
//中文 电网设置设置界面
extern void updateDisplayGridSetData_Chinese(uint8_t sU8GridCounter);
//中文 电网安规设置设置界面
extern void updateDisplayGridSRSetData_Chinese(uint8_t sU8GridCounter);
//中文 电网电价设置设置界面
extern void updateDisplayGridPriceSetData_Chinese(uint8_t sU8BMSSetCounter);
//中文 尖峰平谷分时电价设置设置界面
extern void updateDisplayGridPriceTPFVSetData_Chinese(uint8_t sU8TPFVSetCounter, char* strPrice,TPFV_TypeDef enum_tpfv);
//中文 分时电价起始时间设置设置界面
extern void updateDisplayGridPriceTPFVTimePeriodSetData_Chinese(char* strStartTime, char* strEndTime, TPFV_TypeDef enum_tpfv, TPFV_Price_TypeDef enumTPFVPeriod);
//中文 系统数据界面
extern void updateDisplaySystemData_Chinese(uint8_t sU8SystemCounter);
//中文 实时数据界面
extern void updateDisplayRealtimeData_Chinese(uint8_t sU8RealtimeCounter);
//中文 实时故障告警界面
extern void updateDisplayRealFaultData_Chinese(uint8_t u8CurrentPage,uint8_t u8TotalPageNumber,uint8_t u8LastItemNumber);
//中文 操作记录界面
extern void updateDisplayOperationRecordData_Chinese(uint8_t u8CurrentPage);
//中文 历史故障告警界面
extern void updateDisplayHistoryFaultData_Chinese(uint8_t u8CurrentPage);
//根据故障码获取故障名称
extern void getFaultNameByFaultCode_Chinese(char* Fault_Name,uint16_t u16Code);
//根据操作对象码获取操作对象名称名称
extern void getOperatObjeNameByOperateObjCode_Chinese(char* OperateObj_Name,uint8_t u8Code);
//根据操作类型码获取操作名称
extern void getOperateNameByOperateCode_Chinese(char* Operate_Name,uint8_t u8Code);
//中文 升级界面
extern void updateDisplayUpgradeData_Chinese(Upgrade_TypeDef u8UpgradeIndex);
// 功能:电池设置数据显示 中文界面信息
extern void updateDisplayBatteryTypeSetData_Chinese(uint8_t sU8BatteryTypeCounter);
//功能:无功控制方式设置中文界面
extern void updateDisplayGridReactPowerControlWaySetData_Chinese(uint8_t u8Way);
//中文 无功功率设置界面
extern void updateDisplayGridReactivePowerSetData_Chinese(char *ReactivePowerValue);
//中文 无功控制方式设置界面
extern void updateDisplayGridReactPowerControlWaySetData_English(uint8_t u8Way);
//中文 功率设置界面
extern void updateDisplayGridPowerFactorSetData_Chinese(char* strPF);
//设置ok 中文界面组装
extern void updateDisplaySystemConfirm_Chinese(void);  
#endif
#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

