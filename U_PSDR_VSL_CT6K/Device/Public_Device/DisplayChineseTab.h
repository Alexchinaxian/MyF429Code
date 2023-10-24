/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 �ļ� : DisplayChineseTab.h 
 ��; : ���ڴ��������ʾ��Ϣ��ANSI�����ʽ
***********************************************************************************************************************/
#ifndef __CHINESE_TAB_H__
#define __CHINESE_TAB_H__
#include "HeadFile.h"
#include "LCD_Service.h"

#if LCD_CHINESE_DISP_TEST


//����HOME���� 
extern void updateDisplayHomeData_Chinese(void);
//����LOGIN����
extern void updateDisplayLoginData_Chinese(char* sLoginPassword);
//����SET����
extern void updateDisplaySetData_Chinese(uint8_t u8SetIndex);
//����SystemSet����
extern void updateDisplaySystemSetData_Chinese(uint8_t u8SetIndex);
//����LanguageSystemSet����
extern void updateDisplaySystemLanguageSetData_Chinese(Language_TypeDef u8SetIndex);
//���� ����ϵͳTime����
extern void updateDisplaySystemTimeSetData_Chinese(char* sDate,char* sTime,Week_TypeDef eWeek);
//���� ����ϵͳPassword����
extern void updateDisplaySystemPasswordSetData_Chinese(char* sOldPassword,char* sNewPassword,char* sConfirmPassword);
//���� ��½���������ʾ������Ϣ
extern void updateDisplayTipLoginError_Chinese(void);
//���� �����޸���������λ������6λ��ʾ������Ϣ
extern void updateDisplayTipPasswordShort_Chinese(void);
//���� �����޸ľɵ��������������ʾ������Ϣ
extern void updateDisplayTipOldPasswordError_Chinese(void);
//���� �����޸���������������벻һ����ʾ������Ϣ
extern void updateDisplayTipOldPasswordNotMatch_Chinese(void);
//���� �����޸���������������ʷ�����غ���ʾ������Ϣ
extern void updateDisplayTipOldPasswordOverlaps_Chinese(void);
//���� ����ϵͳͨ�Ÿ�λ���ý�����Ϣ
extern void updateDisplaySystemCommResetData_Chinese(Baud_TypeDef u8SetIndex);
//���� ����ϵͳ�������ý�����Ϣ
extern void updateDisplaySystemSerialSetData_Chinese(bool_t bEnableFlag,char*strAddress,char*strBaud,SERIALUSE_TypeDef enumSerialUse);
//���� ����ϵͳͨ�Ÿ�λ���ý�����Ϣ
extern void updateDisplaySystemRemoteControlData_Chinese(ENABLE_TypeDef u8SetIndex);
//���� ϵͳ�������ý�����Ϣ
extern void updateDisplaySystemStrategySetData_Chinese(STRATEGY_TypeDef u8StrategyIndex);
//���� ϵͳ����������ý�����Ϣ
extern void updateDisplaySystemBackupStrategySetData_Chinese(char* strPower);
//���� ϵͳTPFV����ʱ������ý�����Ϣ
extern void updateDisplaySystemSelfStrategySetData_Chinese(void);
//���� ������������ý�����Ϣ
extern void updateDisplaySystemGenStrategySetData_Chinese(char* strForbidSOC,char* strSupplySOC);  
//���� ϵͳTPFV�������ý�����Ϣ
extern void updateDisplaySystemTPFVStrategyAbstractSetData_Chinese(TPFV_TypeDef u8TPFVStrategyIndex);
//���� ϵͳTPFV�������ý�����Ϣ
extern void updateDisplaySystemTPFVStrategySetData_Chinese(uint8_t sU8TPFVSetCounter,TPFV_TypeDef enum_tpfv);
//���� ϵͳTPFV����ʱ������ý�����Ϣ
extern void updateDisplaySystemTPFVStrategyPeriodSetData_Chinese(char* strStopSOC,char* strPower, TPFV_TypeDef enum_tpfv, TPFV_Strategy_TypeDef enumTPFVPeriod);
//���� ����ϵͳ��Ե������ý�����Ϣ
extern void updateDisplaySystemInsulationDetetionData_Chinese(ENABLE_TypeDef u8SetIndex);
//���� ��ʱ��ŵ�������ý�����Ϣ
extern void updateDisplaySystemRegularStrategySetData_Chinese(REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef u8RegularStrategyIndex);
//���� ��ʱ��ŵ����ʱ������ý�����Ϣ
extern void updateDisplaySystemRegularStrategyPeriodSetData_Chinese(char* strStopSOC,char* strPower, char* strStartTime, char* strEndTime,REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef enum_Period);
//���� ��ʱ��ŵ�������ý�����Ϣ
extern void updateDisplaySystemRegularStrategyAbstractSetData_Chinese(REGULAR_TypeDef u8RegularStrategyIndex);
//���� ����ϵͳCT������ý�����Ϣ
//extern void updateDisplaySystemCTRatioData_Chinese(bool_t bEnableFlag,char* sCurrentCT,char* sVoltageCT);
//���� ʵʱͳ�����ݽ���
extern void updateDisplayStatisticsData_Chinese(uint8_t sU8StatisticsCounter);
//���� ����ͨ����ʾ������Ϣ
extern void updateDisplayTipSetPassed_Chinese(void);
//���� ����ϵͳ����ʹ�����ý�����Ϣ
extern void updateDisplayProtectSetData_Chinese(PROTECTSETAction_TypeDef u8SetIndex);
extern void updateDisplayProtectItemNameSetData_Chinese(ENABLE_CLASS_TypeDef enableClass,char * sEnableName_Chinese);
extern void updateDisplayProtectItemSetData_Chinese(ENABLE_TypeDef sU8ProtectSelected,char * sEnableName);
//���� ������ý���
extern void updateDisplayPVSetData_Chinese(uint8_t u8PVSetIndex);
//���� ����������ý���
extern void updateDisplayPVControlWaySetData_Chinese(uint8_t u8PVContWaySetIndex);
//���� ����������ý���
extern void updateDisplayBMSSetData_Chinese(uint8_t sU8BMSSetCounter);
//���� ��س����������ý���
extern void updateDisplayBatteryManufacturerSetData_Chinese(uint8_t sU8BatteryManufacturerCounter);
//���� �����������ý���
extern void updateDisplayGridSetData_Chinese(uint8_t sU8GridCounter);
//���� ���������������ý���
extern void updateDisplayGridSRSetData_Chinese(uint8_t sU8GridCounter);
//���� ��������������ý���
extern void updateDisplayGridPriceSetData_Chinese(uint8_t sU8BMSSetCounter);
//���� ���ƽ�ȷ�ʱ����������ý���
extern void updateDisplayGridPriceTPFVSetData_Chinese(uint8_t sU8TPFVSetCounter, char* strPrice,TPFV_TypeDef enum_tpfv);
//���� ��ʱ�����ʼʱ���������ý���
extern void updateDisplayGridPriceTPFVTimePeriodSetData_Chinese(char* strStartTime, char* strEndTime, TPFV_TypeDef enum_tpfv, TPFV_Price_TypeDef enumTPFVPeriod);
//���� ϵͳ���ݽ���
extern void updateDisplaySystemData_Chinese(uint8_t sU8SystemCounter);
//���� ʵʱ���ݽ���
extern void updateDisplayRealtimeData_Chinese(uint8_t sU8RealtimeCounter);
//���� ʵʱ���ϸ澯����
extern void updateDisplayRealFaultData_Chinese(uint8_t u8CurrentPage,uint8_t u8TotalPageNumber,uint8_t u8LastItemNumber);
//���� ������¼����
extern void updateDisplayOperationRecordData_Chinese(uint8_t u8CurrentPage);
//���� ��ʷ���ϸ澯����
extern void updateDisplayHistoryFaultData_Chinese(uint8_t u8CurrentPage);
//���ݹ������ȡ��������
extern void getFaultNameByFaultCode_Chinese(char* Fault_Name,uint16_t u16Code);
//���ݲ����������ȡ����������������
extern void getOperatObjeNameByOperateObjCode_Chinese(char* OperateObj_Name,uint8_t u8Code);
//���ݲ����������ȡ��������
extern void getOperateNameByOperateCode_Chinese(char* Operate_Name,uint8_t u8Code);
//���� ��������
extern void updateDisplayUpgradeData_Chinese(Upgrade_TypeDef u8UpgradeIndex);
// ����:�������������ʾ ���Ľ�����Ϣ
extern void updateDisplayBatteryTypeSetData_Chinese(uint8_t sU8BatteryTypeCounter);
//����:�޹����Ʒ�ʽ�������Ľ���
extern void updateDisplayGridReactPowerControlWaySetData_Chinese(uint8_t u8Way);
//���� �޹��������ý���
extern void updateDisplayGridReactivePowerSetData_Chinese(char *ReactivePowerValue);
//���� �޹����Ʒ�ʽ���ý���
extern void updateDisplayGridReactPowerControlWaySetData_English(uint8_t u8Way);
//���� �������ý���
extern void updateDisplayGridPowerFactorSetData_Chinese(char* strPF);
//����ok ���Ľ�����װ
extern void updateDisplaySystemConfirm_Chinese(void);  
#endif
#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

