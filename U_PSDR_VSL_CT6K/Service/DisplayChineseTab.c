/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
�ļ� : DisplayChineseTab.c 
 ��; : ������ʾ
***********************************************************************************************************************/
#include "DisplayChineseTab.h"
#include "LCD_KS0108_6800_Device.h"
#include "Modbus_PCS_COMData.h"
#include <stdlib.h>
#include <stdio.h>




//����Ϊ������ʾʾ������
#if LCD_CHINESE_DISP_TEST
extern char tab_display[];
extern uint8_t gu8LCDEnglishFont;
extern DisplaySystem gDisplay;                  //Display���ݽṹȫ�ֱ���

/***********************************************************************************************************************
 ����:HOME����������ʾ
************************************************************************************************************************/

void updateDisplayHomeData_Chinese(void)
{    
    if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_INIT)
    {
        /*�ַ�����ʽ��Ҫ�����޸ģ�Ӱ��UI����*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Init   \n����״̬:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Init   \n����״̬: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Init   \n����״̬:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Init   \n����״̬:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }
    }
    else if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_FIT)
    {
        /*�ַ�����ʽ��Ҫ�����޸ģ�Ӱ��UI����*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Fit    \n����״̬:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Fit    \n����״̬: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Fit    \n����״̬:Alarm   \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Fit    \n����״̬:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }  
    }
    else if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_MONITOR)
    {
        /*�ַ�����ʽ��Ҫ�����޸ģ�Ӱ��UI����*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Monitor\n����״̬:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Monitor\n����״̬: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Monitor\n����״̬:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Monitor\n����״̬:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }  
    }
    else if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_STANDBY)
    {
        /*�ַ�����ʽ��Ҫ�����޸ģ�Ӱ��UI����*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Standby\n����״̬:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Standby\n����״̬: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Standby\n����״̬:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Standby\n����״̬:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }  
    }
    else if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_TEST)
    {
        /*�ַ�����ʽ��Ҫ�����޸ģ�Ӱ��UI����*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Test   \n����״̬:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Test   \n����״̬: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Test   \n����״̬:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Test   \n����״̬:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }  
    }
    else if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_PRESOFTSTART)
    {
        /*�ַ�����ʽ��Ҫ�����޸ģ�Ӱ��UI����*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:PreSof\n����״̬:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:PreSof\n����״̬: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:PreSof\n����״̬:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     ������     \n����ģʽ:PreSof\n����״̬:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }  
    }
    else if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_SOFTSTART)
    {
        /*�ַ�����ʽ��Ҫ�����޸ģ�Ӱ��UI����*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Softsta\n����״̬:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Softsta\n����״̬: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Softsta\n����״̬:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Softsta\n����״̬:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }  
    }
    else if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_SOFTSTARTWAIT)
    {
        /*�ַ�����ʽ��Ҫ�����޸ģ�Ӱ��UI����*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Softsta\n����״̬:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Softsta\n����״̬: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Softsta\n����״̬:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Softsta\n����״̬:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }  
    }   
    else if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_RELAYCLOSED)
    {
        /*�ַ�����ʽ��Ҫ�����޸ģ�Ӱ��UI����*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:RelayCl\n����״̬:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:RelayCl\n����״̬: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:RelayCl\n����״̬:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     ������     \n����ģʽ:RelayCl\n����״̬:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }  
    }
    else if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_RUN)
    {
        /*�ַ�����ʽ��Ҫ�����޸ģ�Ӱ��UI����*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Running\n����״̬:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Running\n����״̬: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Running\n����״̬:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Running\n����״̬:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }  
    }
    else if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_FAULT)
    {
        /*�ַ�����ʽ��Ҫ�����޸ģ�Ӱ��UI����*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Fault  \n����״̬:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Fault  \n����״̬: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Fault  \n����״̬:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Fault  \n����״̬:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }  
    }  
    else if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_UPGRADE)
    {
        /*�ַ�����ʽ��Ҫ�����޸ģ�Ӱ��UI����*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Upgrad\n����״̬:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Upgrad\n����״̬: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Upgrad\n����״̬:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     ������     \n����ģʽ:Upgrad\n����״̬:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }  
    }
    else
    {
        /*�ַ�����ʽ��Ҫ�����޸ģ�Ӱ��UI����*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:       \n����״̬:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:       \n����״̬: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     ������     \n����ģʽ:       \n����״̬:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     ������     \n����ģʽ:       \n����״̬:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }   
    }
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 ����:����LOGIN��ʾ����
****************************************************************************/
void updateDisplayLoginData_Chinese(char* sLoginPassword)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    sprintf(tab_display,"      ��¼      \n                \n����:%s     \n                \n",sLoginPassword);
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 ����:����SET���Ľ���
****************************************************************************/
void updateDisplaySetData_Chinese(uint8_t u8SetIndex)
{    
    if(u8SetIndex == SET_SYSTEM_Index)
    {
        sprintf(tab_display,"     ����       \n->ϵͳ����      \n�������        \n�������        \n");
        //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
        GUI_Display(tab_display, 0, 0);
    }
    else if(u8SetIndex == SET_PV_Index)
    {
        sprintf(tab_display,"     ����       \nϵͳ����        \n->�������      \n�������        \n");
        //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
        GUI_Display(tab_display, 0, 0);
    }
    else if(u8SetIndex == SET_BATTERY_Index)
    {
        sprintf(tab_display,"     ����       \nϵͳ����        \n�������        \n->�������      \n");
        //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
        GUI_Display(tab_display, 0, 0);
    }
    else if(u8SetIndex == SET_GRID_Index)
    {
        sprintf(tab_display,"     ����       \n->��������      \n���������      \n                \n");
        //sprintf(tab_display,"     ����       \n->��������      \n���������      \n��������        \n");
        //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
        GUI_Display(tab_display, 0, 0);
    }
    else if(u8SetIndex == SET_GEN_Index)
    {
        sprintf(tab_display,"     ����       \n��������        \n->���������    \n                \n");
        //sprintf(tab_display,"     ����       \n��������        \n->���������    \n��������        \n");
        //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
        GUI_Display(tab_display, 0, 0);
    }
    //else if(u8SetIndex == SET_UPGRADE_Index)
    //{
        //sprintf(tab_display,"     ����       \n��������        \n���������      \n->��������      \n");
        //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
        //GUI_Display(tab_display, 0, 0);
    //}
    else
    {
                    
    }
}

/***************************************************************************
 ����:����SETϵͳ���Ľ���
****************************************************************************/
void updateDisplaySystemSetData_Chinese(uint8_t u8SetIndex)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    
    if(u8SetIndex == SET_SYSTEM_LANGUAGE_Index)
    {
        sprintf(tab_display,"    ϵͳ����    \n->��������      \nʱ������        \n��������        \n");
    }
    else if(u8SetIndex == SET_SYSTEM_TIME_Index)
    {
        sprintf(tab_display,"    ϵͳ����    \n��������        \n->ʱ������      \n��������        \n");
    }
    else if(u8SetIndex == SET_SYSTEM_PASSWORD_Index)
    {
        sprintf(tab_display,"    ϵͳ����    \n��������        \nʱ������        \n->��������      \n");
    }
    else if(u8SetIndex == SET_SYSTEM_CLEARFAULT_Index)
    {
        sprintf(tab_display,"    ϵͳ����    \n->�����������  \n�����¼����    \n��������        \n");
    }
    else if(u8SetIndex == SET_SYSTEM_CLEARRECORD_Index)
    {
        sprintf(tab_display,"    ϵͳ����    \n�����������    \n->�����¼����  \n��������        \n");
    }
//    else if(u8SetIndex == SET_SYSTEM_SERIAL_Index)
//    {
//        sprintf(tab_display,"    ϵͳ����    \n�����������    \n�����¼����    \n->��������      \n");
//    }
    else if(u8SetIndex == SET_SYSTEM_FACTORY_Index)
    {
        sprintf(tab_display,"    ϵͳ����    \n->��������      \n��λ����        \nԶ������        \n");
    }
    else if(u8SetIndex == SET_SYSTEM_RESET_Index)
    {
        sprintf(tab_display,"    ϵͳ����    \n��������        \n->��λ����      \nԶ������        \n");
    }
    else if(u8SetIndex == SET_SYSTEM_REMOTECONTROL_Index)
    {
        sprintf(tab_display,"    ϵͳ����    \n��������        \n��λ����        \n->Զ������      \n");
    }   
    else if(u8SetIndex == SET_SYSTEM_STRATEGY_Index)
    {
        //sprintf(tab_display,"    ϵͳ����    \n->��������      \n��ѹ������      \n�������        \n");
        sprintf(tab_display,"    ϵͳ����    \n->��������      \n�������        \n��������        \n");  
    }
    //else if(u8SetIndex == SET_SYSTEM_CT_Index)
    //{
    //    sprintf(tab_display,"    ϵͳ����    \n��������        \n->��ѹ������    \n�������        \n");
    //}
    else if(u8SetIndex == SET_SYSTEM_DETECTION_Index)
    {
        sprintf(tab_display,"    ϵͳ����    \n��������        \n->�������      \n��������        \n");
        //sprintf(tab_display,"    ϵͳ����    \n��������        \n��ѹ������      \n->�������      \n");
    }
    else if(u8SetIndex == SET_SYSTEM_PROTECT_Index)
    {
        sprintf(tab_display,"    ϵͳ����    \n��������        \n�������        \n->��������      \n");
        //sprintf(tab_display,"    ϵͳ����    \n->��������      \n                \n                \n");
    }

    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}


/***************************************************************************
 ����:��������SET���Ľ���
****************************************************************************/
void updateDisplaySystemLanguageSetData_Chinese(Language_TypeDef u8SetIndex)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);  
    if(u8SetIndex ==  LANGUAGE_ENGLISH)
    {
        sprintf(tab_display,"    ��������    \n->Ӣ��          \n����            \n��������        \n"); 
    }
    else if(u8SetIndex == LANGUAGE_CHINESE)
    {
        sprintf(tab_display,"    ��������    \nӢ��            \n->����          \n��������        \n");
    }
    else if(u8SetIndex == LANGUAGE_SPANISH)
    {
        sprintf(tab_display,"    ��������    \nӢ��            \n����            \n->��������      \n");
    }
    else if(u8SetIndex == LANGUAGE_GERMAN)
    {
        sprintf(tab_display,"    ��������    \n->����          \n����            \n������          \n");
    }
    else if(u8SetIndex == LANGUAGE_FRENCH)
    { 
        sprintf(tab_display,"    ��������    \n����            \n->����          \n������          \n");
    }
    else if(u8SetIndex == LANGUAGE_POLISH)
    {
        sprintf(tab_display,"    ��������    \n����            \n����            \n->������        \n");
    }
    else if(u8SetIndex == LANGUAGE_ITALIAN)
    {
        sprintf(tab_display,"    ��������    \n->�������      \n�ݿ���          \n������          \n");
    }
    else if(u8SetIndex == LANGUAGE_CZECH)
    {
        sprintf(tab_display,"    ��������    \n�������        \n->�ݿ���        \n������          \n");
    }
    else if(u8SetIndex == LANGUAGE_DUTCH)
    {
        sprintf(tab_display,"    ��������    \n�������        \n�ݿ���          \n->������        \n");
    }
    
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);     
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 ����:ʱ������SET���Ľ���
****************************************************************************/
void updateDisplaySystemTimeSetData_Chinese(char* sDate,char* sTime,Week_TypeDef eWeek)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    
    char tab_week[10]; 
    memset(tab_week,0,10);
    
    if(eWeek == WEEK_MONDAY)
    {
        strcpy(tab_week, "����һ");
    }
    else if(eWeek == WEEK_TUESDAY)
    {
       strcpy(tab_week, "���ڶ�");
    }
    else if(eWeek == WEEK_WEDNESDAY)
    {
       strcpy(tab_week, "������");
    }
    else if(eWeek == WEEK_THURSDAY)
    {
       strcpy(tab_week, "������");
    }
    else if(eWeek == WEEK_FRIDAY)
    {
       strcpy(tab_week, "������");
    }
    else if(eWeek == WEEK_SATURDAY)
    {
       strcpy(tab_week, "������");
    }
    else if(eWeek == WEEK_SUNDAY)
    {
       strcpy(tab_week, "������");
    }
     
    sprintf(tab_display,"    ʱ������    \n����:%s \nʱ��:%s   \n��:%s \n",sDate,sTime,tab_week);
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 ����:���� ����ϵͳPassword����
****************************************************************************/
void updateDisplaySystemPasswordSetData_Chinese(char* sOldPassword,char* sNewPassword,char* sConfirmPassword)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    sprintf(tab_display,"    ��������    \nԭ����:%s   \n������:%s   \nȷ��:%s     \n",sOldPassword,sNewPassword,sConfirmPassword);
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);
    GUI_Display(tab_display, 0, 0);
}


/***************************************************************************
 ����:���� ��ʾ��½����У�������Ϣ
****************************************************************************/
void updateDisplayTipLoginError_Chinese(void)
{
    sprintf(tab_display,"      ��ʾ      \n  ������֤����  \n     ������.    \n                \n");
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 ����:���� �����޸���������λ������6λ��ʾ������Ϣ
****************************************************************************/
void updateDisplayTipPasswordShort_Chinese(void)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    sprintf(tab_display,"      ��ʾ      \n  ������λ����, \n     ������.    \n                \n");
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0);
}



/***************************************************************************
 ����:���� �����޸ľɵ��������������ʾ������Ϣ
****************************************************************************/
void updateDisplayTipOldPasswordError_Chinese(void)
{
    sprintf(tab_display,"      ��ʾ      \n �������������,\n     ������.    \n                \n");
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 ����:���� �����޸���������������벻һ����ʾ������Ϣ
****************************************************************************/
void updateDisplayTipOldPasswordNotMatch_Chinese(void)
{
    sprintf(tab_display,"      ��ʾ      \n �¾����벻ƥ��,\n     ������.    \n                \n");
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
����:���� �����޸���������������ʷ�����غ���ʾ������Ϣ
****************************************************************************/
void updateDisplayTipOldPasswordOverlaps_Chinese(void)
{
    sprintf(tab_display,"      ��ʾ      \n  �¾������ظ�, \n     ������.    \n                \n");
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 ����:����ϵͳͨ�Ÿ�λ�������Ľ�����Ϣ
****************************************************************************/
void updateDisplaySystemCommResetData_Chinese(Baud_TypeDef u8SetIndex)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);    
    if(u8SetIndex == RESET_BLT_Index)
    {
        sprintf(tab_display,"    ��λ����    \n->������λ      \n���߸�λ        \n                \n");                                                                               
    }
    else if(u8SetIndex == RESET_WIFI_Index)
    {
        sprintf(tab_display,"    ��λ����    \n������λ        \n->���߸�λ      \n                \n");                                                                                  
    }

    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}


/***************************************************************************
 ����:����ϵͳ�����������Ľ�����Ϣ
****************************************************************************/
void updateDisplaySystemSerialSetData_Chinese(bool_t bEnableFlag,char*strAddress,char*strBaud, SERIALUSE_TypeDef enumSerialUse)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);    
    if(enumSerialUse == SERIAL_USE_PCS)
    {
        if(bEnableFlag == STATUS_FALSE)
        {
            sprintf(tab_display,"  PCS ��������  \nʹ��:��ֹ       \n��ַ:%s        \n����:%s    \n",strAddress,strBaud);
        }
        else
        {
            sprintf(tab_display,"  PCS ��������  \nʹ��:ʹ��       \n��ַ:%s        \n����:%s    \n",strAddress,strBaud);
        }        
    }
    else if(enumSerialUse == SERIAL_USE_Meter)
    {
        if(bEnableFlag == STATUS_FALSE)
        {
            sprintf(tab_display,"    �������    \nʹ��:��ֹ       \n��ַ:%s        \n����:%s    \n",strAddress,strBaud);
        }
        else
        {
            sprintf(tab_display,"    �������    \nʹ��:ʹ��       \n��ַ:%s        \n����:%s    \n",strAddress,strBaud);
        }
    }
    
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}


/***************************************************************************
 ����:����ϵͳԶ�̿���ʹ���������Ľ�����Ϣ
****************************************************************************/
void updateDisplaySystemRemoteControlData_Chinese(ENABLE_TypeDef u8SetIndex)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    if(u8SetIndex == ENABLE_NO)
    {
        sprintf(tab_display,"    Զ������    \n->���ؿ���      \nԶ�˿���        \n                \n");                                                                               
    }
    else if(u8SetIndex == ENABLE_YES)
    {
        sprintf(tab_display,"    Զ������    \n���ؿ���        \n->Զ�˿���      \n                \n");                                                                                  
    }

    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}



/***************************************************************************
 ����:�����������Ľ�����Ϣ
****************************************************************************/
void updateDisplaySystemStrategySetData_Chinese(STRATEGY_TypeDef u8StrategyIndex)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    if(u8StrategyIndex == STRATEGY_NULL)
    {
        sprintf(tab_display,"    ��������    \n->��            \n�Է�����        \n���ƽ��        \n");                                                                                  
    }
    else if(u8StrategyIndex == STRATEGY_SELF)
    {
        sprintf(tab_display,"    ��������    \n��              \n->�Է�����      \n���ƽ��        \n");                                                                                  
    }
    else if(u8StrategyIndex == STRATEGY_TPFV)
    {
        sprintf(tab_display,"    ��������    \n��              \n�Է�����        \n->���ƽ��      \n");                                                                               
    }
    else if(u8StrategyIndex == STRATEGY_REGULAR)
    {
        sprintf(tab_display,"    ��������    \n->��ʱ��ŵ�    \n����            \n�����          \n");                                                                                  
    }
    else if(u8StrategyIndex == STRATEGY_BACKUP)
    {
        sprintf(tab_display,"    ��������    \n��ʱ��ŵ�      \n->����          \n�����          \n");                                                                                  
    }
    else if(u8StrategyIndex == STRATEGY_GEN)
    {
        sprintf(tab_display,"    ��������    \n��ʱ��ŵ�      \n����            \n->�����        \n");                                                                                  
    }

    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 ����:���� ϵͳSELF�������ý�����Ϣ
****************************************************************************/
void updateDisplaySystemSelfStrategySetData_Chinese()
{  
    memset(tab_display,0,DISPLAY_CACHE_SIZE);  
    sprintf(tab_display,"    �Է�����    \n                \n                \n                \n");                                                                                                                                                              
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0);
}
/***************************************************************************
 ����:����  ϵͳ����������ý�����Ϣ
****************************************************************************/
void updateDisplaySystemBackupStrategySetData_Chinese(char* strPower)
{  
    memset(tab_display,0,DISPLAY_CACHE_SIZE);  
    sprintf(tab_display,"    �������    \n                \n����:%s \n                \n",strPower);                                                                                                                                
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0); 
}
/***************************************************************************
 ����:����  ϵͳ������������ý�����Ϣ
****************************************************************************/
void updateDisplaySystemGenStrategySetData_Chinese(char* strForbidSOC,char* strSupplySOC)
{  
    memset(tab_display,0,DISPLAY_CACHE_SIZE);  
    //sprintf(tab_display,"   ���������   \n��ֹSOC:%s        \n����SOC:%s    \n                \n",strForbidSOC,strSupplySOC);
    sprintf(tab_display,"   ���������   \n��ֹSOC:%s     \n����SOC:%s     \n                \n",strForbidSOC,strSupplySOC);                                                                                                                                                              
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0);
    
}
/***************************************************************************
 ����:ϵͳ����TPFV ���Ľ�����Ϣ
****************************************************************************/
void updateDisplaySystemTPFVStrategyAbstractSetData_Chinese(TPFV_TypeDef u8TPFVStrategyIndex)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
        /*
    if(u8TPFVStrategyIndex == TPFV_TIP)
    {
        sprintf(tab_display,"  ���ƽ�Ȳ���  \n->���          \n���            \nƽ��            \n"); 
    }
    else if(u8TPFVStrategyIndex == TPFV_PEAK)
    {
        sprintf(tab_display,"  ���ƽ�Ȳ���  \n���            \n->���          \nƽ��            \n");   
    }
    else if(u8TPFVStrategyIndex == TPFV_FLAT)
    {
        sprintf(tab_display,"  ���ƽ�Ȳ���  \n���            \n���            \n->ƽ��          \n");  
    }
    else if(u8TPFVStrategyIndex == TPFV_VALLEY)
    {
        sprintf(tab_display,"  ���ƽ�Ȳ���  \n->�ȶ�          \n                \n                \n");  
    } 
        */
    if(u8TPFVStrategyIndex == TPFV_PEAK)
    {
        sprintf(tab_display,"  ���ƽ�Ȳ���  \n->���          \nƽ��            \n�ȶ�          \n");
    }
    else if(u8TPFVStrategyIndex == TPFV_FLAT)
    {
        sprintf(tab_display,"  ���ƽ�Ȳ���  \n���            \n->ƽ��          \n�ȶ�          \n");
    }
    else if(u8TPFVStrategyIndex == TPFV_VALLEY)
    {
        sprintf(tab_display,"  ���ƽ�Ȳ���  \n���            \nƽ��            \n->�ȶ�          \n");
    }                 
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 ����:�������ƽ�ȷ�ʱ���� ���Ľ�����Ϣ
****************************************************************************/

void updateDisplaySystemTPFVStrategySetData_Chinese(uint8_t sU8TPFVSetCounter,TPFV_TypeDef enum_tpfv)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    
    if(enum_tpfv == TPFV_TIP)
    {
        if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_ONE)
        {
            sprintf(tab_display,"      ���      \n->ʱ�� 1        \nʱ�� 2          \nʱ�� 3          \n");
        }
        else if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_TWO)
        {
            sprintf(tab_display,"      ���      \nʱ�� 1          \n->ʱ�� 2        \nʱ�� 3          \n");
        }
        else if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_THREE)
        {
            sprintf(tab_display,"      ���      \nʱ�� 1          \nʱ�� 2          \n->ʱ�� 3        \n");
        }      
    }
    else if(enum_tpfv == TPFV_PEAK)
    {
        if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_ONE)
        {
            sprintf(tab_display,"      ���      \n->ʱ�� 1        \nʱ�� 2          \nʱ�� 3          \n");
        }
        else if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_TWO)
        {
            sprintf(tab_display,"      ���      \nʱ�� 1          \n->ʱ�� 2        \nʱ�� 3          \n");
        }
        else if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_THREE)
        {
            sprintf(tab_display,"      ���      \nʱ�� 1          \nʱ�� 2          \n->ʱ�� 3        \n");
        }  
    }
    else if(enum_tpfv == TPFV_FLAT)
    {
        if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_ONE)
        {
            sprintf(tab_display,"      ƽ��      \n->ʱ�� 1        \nʱ�� 2          \nʱ�� 3          \n");
        }
        else if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_TWO)
        {
            sprintf(tab_display,"      ƽ��      \nʱ�� 1          \n->ʱ�� 2        \nʱ�� 3          \n");
        }
        else if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_THREE)
        {
            sprintf(tab_display,"      ƽ��      \nʱ�� 1          \nʱ�� 2          \n->ʱ�� 3        \n");
        } 
    }
    else if(enum_tpfv == TPFV_VALLEY)
    {
        if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_ONE)
        {
            sprintf(tab_display,"      �ȶ�      \n->ʱ�� 1        \nʱ�� 2          \nʱ�� 3          \n");
        }
        else if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_TWO)
        {
            sprintf(tab_display,"      �ȶ�      \nʱ�� 1          \n->ʱ�� 2        \nʱ�� 3          \n");
        }
        else if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_THREE)
        {
            sprintf(tab_display,"      �ȶ�      \nʱ�� 1          \nʱ�� 2          \n->ʱ�� 3        \n");
        }
    }  
                         
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 ����:���� ϵͳTPFV����ʱ������ý�����Ϣ
****************************************************************************/
void updateDisplaySystemTPFVStrategyPeriodSetData_Chinese(char* strStopSOC,char* strPower, TPFV_TypeDef enum_tpfv, TPFV_Strategy_TypeDef enumTPFVPeriod)
{
    char tab_StartTime_Temp[9];
    memset(tab_StartTime_Temp,0,9);  
    char tab_EndTime_Temp[9] ;
    memset(tab_EndTime_Temp,0,9);
    memset(tab_display,0,DISPLAY_CACHE_SIZE);  
    
    if(enum_tpfv == TPFV_TIP)
    {
        if(enumTPFVPeriod == STRATEGY_TPFV_PERIOD_ONE)
        {    
            char tab_StartHour[2] ;                 
            uint8_t u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stTipPeriod.stPeriod1.u8StartHour;
            sprintf(tab_StartHour,"%02d",u8Temp);
            tab_StartTime_Temp[0] = tab_StartHour[0];
            tab_StartTime_Temp[1] = tab_StartHour[1];
            
            tab_StartTime_Temp[2] = ':';
            
            char tab_StartMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stTipPeriod.stPeriod1.u8StartMin;
            sprintf(tab_StartMin,"%02d",u8Temp);
            tab_StartTime_Temp[3] = tab_StartMin[0];
            tab_StartTime_Temp[4] = tab_StartMin[1];
                 
            tab_StartTime_Temp[5] = ':';
            
            char tab_StartSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stTipPeriod.stPeriod1.u8StartSec;
            sprintf(tab_StartSec,"%02d",u8Temp);
            tab_StartTime_Temp[6] = tab_StartSec[0];
            tab_StartTime_Temp[7] = tab_StartSec[1];
            
            char tab_EndHour[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stTipPeriod.stPeriod1.u8EndHour;
            sprintf(tab_EndHour,"%02d",u8Temp);
            tab_EndTime_Temp[0] = tab_EndHour[0];
            tab_EndTime_Temp[1] = tab_EndHour[1];
            
            tab_EndTime_Temp[2] = ':';
            
            char tab_EndMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stTipPeriod.stPeriod1.u8EndMin;
            sprintf(tab_EndMin,"%02d",u8Temp);
            tab_EndTime_Temp[3] = tab_EndMin[0];
            tab_EndTime_Temp[4] = tab_EndMin[1];
                 
            tab_EndTime_Temp[5] = ':';
            
            char tab_EndSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stTipPeriod.stPeriod1.u8EndSec;
            sprintf(tab_EndSec,"%02d",u8Temp);
            tab_EndTime_Temp[6] = tab_EndSec[0];
            tab_EndTime_Temp[7] = tab_EndSec[1];
                        
            sprintf((char*)tab_display,"     ��� 1     \nSOC:%sPWR:%s\n��ʼ:%s   \n����:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);
                        
        }
        else if(enumTPFVPeriod == STRATEGY_TPFV_PERIOD_TWO)
        { 
            char tab_StartHour[2] ;                 
            uint8_t u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stTipPeriod.stPeriod2.u8StartHour;
            sprintf(tab_StartHour,"%02d",u8Temp);
            tab_StartTime_Temp[0] = tab_StartHour[0];
            tab_StartTime_Temp[1] = tab_StartHour[1];
            
            tab_StartTime_Temp[2] = ':';
            
            char tab_StartMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stTipPeriod.stPeriod2.u8StartMin;
            sprintf(tab_StartMin,"%02d",u8Temp);
            tab_StartTime_Temp[3] = tab_StartMin[0];
            tab_StartTime_Temp[4] = tab_StartMin[1];
                 
            tab_StartTime_Temp[5] = ':';
            
            char tab_StartSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stTipPeriod.stPeriod2.u8StartSec;
            sprintf(tab_StartSec,"%02d",u8Temp);
            tab_StartTime_Temp[6] = tab_StartSec[0];
            tab_StartTime_Temp[7] = tab_StartSec[1];
            
            char tab_EndHour[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stTipPeriod.stPeriod2.u8EndHour;
            sprintf(tab_EndHour,"%02d",u8Temp);
            tab_EndTime_Temp[0] = tab_EndHour[0];
            tab_EndTime_Temp[1] = tab_EndHour[1];
            
            tab_EndTime_Temp[2] = ':';
            
            char tab_EndMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stTipPeriod.stPeriod2.u8EndMin;
            sprintf(tab_EndMin,"%02d",u8Temp);
            tab_EndTime_Temp[3] = tab_EndMin[0];
            tab_EndTime_Temp[4] = tab_EndMin[1];
                 
            tab_EndTime_Temp[5] = ':';
            
            char tab_EndSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stTipPeriod.stPeriod2.u8EndSec;
            sprintf(tab_EndSec,"%02d",u8Temp);
            tab_EndTime_Temp[6] = tab_EndSec[0];
            tab_EndTime_Temp[7] = tab_EndSec[1];
                        
            sprintf((char*)tab_display,"     ��� 2     \nSOC:%sPWR:%s\n��ʼ:%s   \n����:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);            
        }
        else if(enumTPFVPeriod == STRATEGY_TPFV_PERIOD_THREE)
        {  
            char tab_StartHour[2] ;                 
            uint8_t u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stTipPeriod.stPeriod3.u8StartHour;
            sprintf(tab_StartHour,"%02d",u8Temp);
            tab_StartTime_Temp[0] = tab_StartHour[0];
            tab_StartTime_Temp[1] = tab_StartHour[1];
            
            tab_StartTime_Temp[2] = ':';
            
            char tab_StartMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stTipPeriod.stPeriod3.u8StartMin;
            sprintf(tab_StartMin,"%02d",u8Temp);
            tab_StartTime_Temp[3] = tab_StartMin[0];
            tab_StartTime_Temp[4] = tab_StartMin[1];
                 
            tab_StartTime_Temp[5] = ':';
            
            char tab_StartSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stTipPeriod.stPeriod3.u8StartSec;
            sprintf(tab_StartSec,"%02d",u8Temp);
            tab_StartTime_Temp[6] = tab_StartSec[0];
            tab_StartTime_Temp[7] = tab_StartSec[1];
            
            char tab_EndHour[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stTipPeriod.stPeriod3.u8EndHour;
            sprintf(tab_EndHour,"%02d",u8Temp);
            tab_EndTime_Temp[0] = tab_EndHour[0];
            tab_EndTime_Temp[1] = tab_EndHour[1];
            
            tab_EndTime_Temp[2] = ':';
            
            char tab_EndMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stTipPeriod.stPeriod3.u8EndMin;
            sprintf(tab_EndMin,"%02d",u8Temp);
            tab_EndTime_Temp[3] = tab_EndMin[0];
            tab_EndTime_Temp[4] = tab_EndMin[1];
                 
            tab_EndTime_Temp[5] = ':';
            
            char tab_EndSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stTipPeriod.stPeriod3.u8EndSec;
            sprintf(tab_EndSec,"%02d",u8Temp);
            tab_EndTime_Temp[6] = tab_EndSec[0];
            tab_EndTime_Temp[7] = tab_EndSec[1];
                        
            sprintf((char*)tab_display,"     ��� 3     \nSOC:%sPWR:%s\n��ʼ:%s   \n����:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);
            
        }         
    }
    else if(enum_tpfv == TPFV_PEAK)
    {
        if(enumTPFVPeriod == STRATEGY_TPFV_PERIOD_ONE)
        {    
            char tab_StartHour[2] ;                 
            uint8_t u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stPeakPeriod.stPeriod1.u8StartHour;
            sprintf(tab_StartHour,"%02d",u8Temp);
            tab_StartTime_Temp[0] = tab_StartHour[0];
            tab_StartTime_Temp[1] = tab_StartHour[1];
            
            tab_StartTime_Temp[2] = ':';
            
            char tab_StartMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stPeakPeriod.stPeriod1.u8StartMin;
            sprintf(tab_StartMin,"%02d",u8Temp);
            tab_StartTime_Temp[3] = tab_StartMin[0];
            tab_StartTime_Temp[4] = tab_StartMin[1];
                 
            tab_StartTime_Temp[5] = ':';
            
            char tab_StartSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stPeakPeriod.stPeriod1.u8StartSec;
            sprintf(tab_StartSec,"%02d",u8Temp);
            tab_StartTime_Temp[6] = tab_StartSec[0];
            tab_StartTime_Temp[7] = tab_StartSec[1];
            
            char tab_EndHour[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stPeakPeriod.stPeriod1.u8EndHour;
            sprintf(tab_EndHour,"%02d",u8Temp);
            tab_EndTime_Temp[0] = tab_EndHour[0];
            tab_EndTime_Temp[1] = tab_EndHour[1];
            
            tab_EndTime_Temp[2] = ':';
            
            char tab_EndMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stPeakPeriod.stPeriod1.u8EndMin;
            sprintf(tab_EndMin,"%02d",u8Temp);
            tab_EndTime_Temp[3] = tab_EndMin[0];
            tab_EndTime_Temp[4] = tab_EndMin[1];
                 
            tab_EndTime_Temp[5] = ':';
            
            char tab_EndSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stPeakPeriod.stPeriod1.u8EndSec;
            sprintf(tab_EndSec,"%02d",u8Temp);
            tab_EndTime_Temp[6] = tab_EndSec[0];
            tab_EndTime_Temp[7] = tab_EndSec[1];
             
            sprintf((char*)tab_display,"     ��� 1     \nSOC:%sPWR:%s\n��ʼ:%s   \n����:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);            
        }
        else if(enumTPFVPeriod == STRATEGY_TPFV_PERIOD_TWO)
        { 
            char tab_StartHour[2] ;                 
            uint8_t u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stPeakPeriod.stPeriod2.u8StartHour;
            sprintf(tab_StartHour,"%02d",u8Temp);
            tab_StartTime_Temp[0] = tab_StartHour[0];
            tab_StartTime_Temp[1] = tab_StartHour[1];
            
            tab_StartTime_Temp[2] = ':';
            
            char tab_StartMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stPeakPeriod.stPeriod2.u8StartMin;
            sprintf(tab_StartMin,"%02d",u8Temp);
            tab_StartTime_Temp[3] = tab_StartMin[0];
            tab_StartTime_Temp[4] = tab_StartMin[1];
                 
            tab_StartTime_Temp[5] = ':';
            
            char tab_StartSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stPeakPeriod.stPeriod2.u8StartSec;
            sprintf(tab_StartSec,"%02d",u8Temp);
            tab_StartTime_Temp[6] = tab_StartSec[0];
            tab_StartTime_Temp[7] = tab_StartSec[1];
            
            char tab_EndHour[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stPeakPeriod.stPeriod2.u8EndHour;
            sprintf(tab_EndHour,"%02d",u8Temp);
            tab_EndTime_Temp[0] = tab_EndHour[0];
            tab_EndTime_Temp[1] = tab_EndHour[1];
            
            tab_EndTime_Temp[2] = ':';
            
            char tab_EndMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stPeakPeriod.stPeriod2.u8EndMin;
            sprintf(tab_EndMin,"%02d",u8Temp);
            tab_EndTime_Temp[3] = tab_EndMin[0];
            tab_EndTime_Temp[4] = tab_EndMin[1];
                 
            tab_EndTime_Temp[5] = ':';
            
            char tab_EndSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stPeakPeriod.stPeriod2.u8EndSec;
            sprintf(tab_EndSec,"%02d",u8Temp);
            tab_EndTime_Temp[6] = tab_EndSec[0];
            tab_EndTime_Temp[7] = tab_EndSec[1];
                        
            sprintf((char*)tab_display,"     ��� 2     \nSOC:%sPWR:%s\n��ʼ:%s   \n����:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);            
        }
        else if(enumTPFVPeriod == STRATEGY_TPFV_PERIOD_THREE)
        {  
            char tab_StartHour[2] ;                 
            uint8_t u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stPeakPeriod.stPeriod3.u8StartHour;
            sprintf(tab_StartHour,"%02d",u8Temp);
            tab_StartTime_Temp[0] = tab_StartHour[0];
            tab_StartTime_Temp[1] = tab_StartHour[1];
            
            tab_StartTime_Temp[2] = ':';
            
            char tab_StartMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stPeakPeriod.stPeriod3.u8StartMin;
            sprintf(tab_StartMin,"%02d",u8Temp);
            tab_StartTime_Temp[3] = tab_StartMin[0];
            tab_StartTime_Temp[4] = tab_StartMin[1];
                 
            tab_StartTime_Temp[5] = ':';
            
            char tab_StartSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stPeakPeriod.stPeriod3.u8StartSec;
            sprintf(tab_StartSec,"%02d",u8Temp);
            tab_StartTime_Temp[6] = tab_StartSec[0];
            tab_StartTime_Temp[7] = tab_StartSec[1];
            
            char tab_EndHour[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stPeakPeriod.stPeriod3.u8EndHour;
            sprintf(tab_EndHour,"%02d",u8Temp);
            tab_EndTime_Temp[0] = tab_EndHour[0];
            tab_EndTime_Temp[1] = tab_EndHour[1];
            
            tab_EndTime_Temp[2] = ':';
            
            char tab_EndMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stPeakPeriod.stPeriod3.u8EndMin;
            sprintf(tab_EndMin,"%02d",u8Temp);
            tab_EndTime_Temp[3] = tab_EndMin[0];
            tab_EndTime_Temp[4] = tab_EndMin[1];
                 
            tab_EndTime_Temp[5] = ':';
            
            char tab_EndSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stPeakPeriod.stPeriod3.u8EndSec;
            sprintf(tab_EndSec,"%02d",u8Temp);
            tab_EndTime_Temp[6] = tab_EndSec[0];
            tab_EndTime_Temp[7] = tab_EndSec[1];
                        
            sprintf((char*)tab_display,"     ��� 3     \nSOC:%sPWR:%s\n��ʼ:%s   \n����:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);
        }           
    }
    else if(enum_tpfv == TPFV_FLAT)
    {
        if(enumTPFVPeriod == STRATEGY_TPFV_PERIOD_ONE)
        {    
            char tab_StartHour[2] ;                 
            uint8_t u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stFlatPeriod.stPeriod1.u8StartHour;
            sprintf(tab_StartHour,"%02d",u8Temp);
            tab_StartTime_Temp[0] = tab_StartHour[0];
            tab_StartTime_Temp[1] = tab_StartHour[1];
            
            tab_StartTime_Temp[2] = ':';
            
            char tab_StartMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stFlatPeriod.stPeriod1.u8StartMin;
            sprintf(tab_StartMin,"%02d",u8Temp);
            tab_StartTime_Temp[3] = tab_StartMin[0];
            tab_StartTime_Temp[4] = tab_StartMin[1];
                 
            tab_StartTime_Temp[5] = ':';
            
            char tab_StartSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stFlatPeriod.stPeriod1.u8StartSec;
            sprintf(tab_StartSec,"%02d",u8Temp);
            tab_StartTime_Temp[6] = tab_StartSec[0];
            tab_StartTime_Temp[7] = tab_StartSec[1];
            
            char tab_EndHour[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stFlatPeriod.stPeriod1.u8EndHour;
            sprintf(tab_EndHour,"%02d",u8Temp);
            tab_EndTime_Temp[0] = tab_EndHour[0];
            tab_EndTime_Temp[1] = tab_EndHour[1];
            
            tab_EndTime_Temp[2] = ':';
            
            char tab_EndMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stFlatPeriod.stPeriod1.u8EndMin;
            sprintf(tab_EndMin,"%02d",u8Temp);
            tab_EndTime_Temp[3] = tab_EndMin[0];
            tab_EndTime_Temp[4] = tab_EndMin[1];
                 
            tab_EndTime_Temp[5] = ':';
            
            char tab_EndSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stFlatPeriod.stPeriod1.u8EndSec;
            sprintf(tab_EndSec,"%02d",u8Temp);
            tab_EndTime_Temp[6] = tab_EndSec[0];
            tab_EndTime_Temp[7] = tab_EndSec[1];
            
            sprintf((char*)tab_display,"     ƽ�� 1     \nSOC:%sPWR:%s\n��ʼ:%s   \n����:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);
                        
        }
        else if(enumTPFVPeriod == STRATEGY_TPFV_PERIOD_TWO)
        { 
            char tab_StartHour[2] ;                 
            uint8_t u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stFlatPeriod.stPeriod2.u8StartHour;
            sprintf(tab_StartHour,"%02d",u8Temp);
            tab_StartTime_Temp[0] = tab_StartHour[0];
            tab_StartTime_Temp[1] = tab_StartHour[1];
            
            tab_StartTime_Temp[2] = ':';
            
            char tab_StartMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stFlatPeriod.stPeriod2.u8StartMin;
            sprintf(tab_StartMin,"%02d",u8Temp);
            tab_StartTime_Temp[3] = tab_StartMin[0];
            tab_StartTime_Temp[4] = tab_StartMin[1];
                 
            tab_StartTime_Temp[5] = ':';
            
            char tab_StartSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stFlatPeriod.stPeriod2.u8StartSec;
            sprintf(tab_StartSec,"%02d",u8Temp);
            tab_StartTime_Temp[6] = tab_StartSec[0];
            tab_StartTime_Temp[7] = tab_StartSec[1];
            
            char tab_EndHour[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stFlatPeriod.stPeriod2.u8EndHour;
            sprintf(tab_EndHour,"%02d",u8Temp);
            tab_EndTime_Temp[0] = tab_EndHour[0];
            tab_EndTime_Temp[1] = tab_EndHour[1];
            
            tab_EndTime_Temp[2] = ':';
            
            char tab_EndMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stFlatPeriod.stPeriod2.u8EndMin;
            sprintf(tab_EndMin,"%02d",u8Temp);
            tab_EndTime_Temp[3] = tab_EndMin[0];
            tab_EndTime_Temp[4] = tab_EndMin[1];
                 
            tab_EndTime_Temp[5] = ':';
            
            char tab_EndSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stFlatPeriod.stPeriod2.u8EndSec;
            sprintf(tab_EndSec,"%02d",u8Temp);
            tab_EndTime_Temp[6] = tab_EndSec[0];
            tab_EndTime_Temp[7] = tab_EndSec[1];
                        
            sprintf((char*)tab_display,"     ƽ�� 2     \nSOC:%sPWR:%s\n��ʼ:%s   \n����:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);            
        }
        else if(enumTPFVPeriod == STRATEGY_TPFV_PERIOD_THREE)
        {  
            char tab_StartHour[2] ;                 
            uint8_t u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stFlatPeriod.stPeriod3.u8StartHour;
            sprintf(tab_StartHour,"%02d",u8Temp);
            tab_StartTime_Temp[0] = tab_StartHour[0];
            tab_StartTime_Temp[1] = tab_StartHour[1];
            
            tab_StartTime_Temp[2] = ':';
            
            char tab_StartMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stFlatPeriod.stPeriod3.u8StartMin;
            sprintf(tab_StartMin,"%02d",u8Temp);
            tab_StartTime_Temp[3] = tab_StartMin[0];
            tab_StartTime_Temp[4] = tab_StartMin[1];
                 
            tab_StartTime_Temp[5] = ':';
            
            char tab_StartSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stFlatPeriod.stPeriod3.u8StartSec;
            sprintf(tab_StartSec,"%02d",u8Temp);
            tab_StartTime_Temp[6] = tab_StartSec[0];
            tab_StartTime_Temp[7] = tab_StartSec[1];
            
            char tab_EndHour[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stFlatPeriod.stPeriod3.u8EndHour;
            sprintf(tab_EndHour,"%02d",u8Temp);
            tab_EndTime_Temp[0] = tab_EndHour[0];
            tab_EndTime_Temp[1] = tab_EndHour[1];
            
            tab_EndTime_Temp[2] = ':';
            
            char tab_EndMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stFlatPeriod.stPeriod3.u8EndMin;
            sprintf(tab_EndMin,"%02d",u8Temp);
            tab_EndTime_Temp[3] = tab_EndMin[0];
            tab_EndTime_Temp[4] = tab_EndMin[1];
                 
            tab_EndTime_Temp[5] = ':';
            
            char tab_EndSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stFlatPeriod.stPeriod3.u8EndSec;
            sprintf(tab_EndSec,"%02d",u8Temp);
            tab_EndTime_Temp[6] = tab_EndSec[0];
            tab_EndTime_Temp[7] = tab_EndSec[1];
                        
            sprintf((char*)tab_display,"     ƽ�� 3     \nSOC:%sPWR:%s\n��ʼ:%s   \n����:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);
        } 
    }
    else if(enum_tpfv == TPFV_VALLEY)
    {
        if(enumTPFVPeriod == STRATEGY_TPFV_PERIOD_ONE)
        {    
            char tab_StartHour[2] ;                 
            uint8_t u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stValleyPeriod.stPeriod1.u8StartHour;
            sprintf(tab_StartHour,"%02d",u8Temp);
            tab_StartTime_Temp[0] = tab_StartHour[0];
            tab_StartTime_Temp[1] = tab_StartHour[1];
            
            tab_StartTime_Temp[2] = ':';
            
            char tab_StartMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stValleyPeriod.stPeriod1.u8StartMin;
            sprintf(tab_StartMin,"%02d",u8Temp);
            tab_StartTime_Temp[3] = tab_StartMin[0];
            tab_StartTime_Temp[4] = tab_StartMin[1];
                 
            tab_StartTime_Temp[5] = ':';
            
            char tab_StartSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stValleyPeriod.stPeriod1.u8StartSec;
            sprintf(tab_StartSec,"%02d",u8Temp);
            tab_StartTime_Temp[6] = tab_StartSec[0];
            tab_StartTime_Temp[7] = tab_StartSec[1];
            
            char tab_EndHour[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stValleyPeriod.stPeriod1.u8EndHour;
            sprintf(tab_EndHour,"%02d",u8Temp);
            tab_EndTime_Temp[0] = tab_EndHour[0];
            tab_EndTime_Temp[1] = tab_EndHour[1];
            
            tab_EndTime_Temp[2] = ':';
            
            char tab_EndMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stValleyPeriod.stPeriod1.u8EndMin;
            sprintf(tab_EndMin,"%02d",u8Temp);
            tab_EndTime_Temp[3] = tab_EndMin[0];
            tab_EndTime_Temp[4] = tab_EndMin[1];
                 
            tab_EndTime_Temp[5] = ':';
            
            char tab_EndSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stValleyPeriod.stPeriod1.u8EndSec;
            sprintf(tab_EndSec,"%02d",u8Temp);
            tab_EndTime_Temp[6] = tab_EndSec[0];
            tab_EndTime_Temp[7] = tab_EndSec[1];
            
            sprintf((char*)tab_display,"     �ȶ� 1     \nSOC:%sPWR:%s\n��ʼ:%s   \n����:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);
                        
        }
        else if(enumTPFVPeriod == STRATEGY_TPFV_PERIOD_TWO)
        { 
            char tab_StartHour[2] ;                 
            uint8_t u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stValleyPeriod.stPeriod2.u8StartHour;
            sprintf(tab_StartHour,"%02d",u8Temp);
            tab_StartTime_Temp[0] = tab_StartHour[0];
            tab_StartTime_Temp[1] = tab_StartHour[1];
            
            tab_StartTime_Temp[2] = ':';
            
            char tab_StartMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stValleyPeriod.stPeriod2.u8StartMin;
            sprintf(tab_StartMin,"%02d",u8Temp);
            tab_StartTime_Temp[3] = tab_StartMin[0];
            tab_StartTime_Temp[4] = tab_StartMin[1];
                 
            tab_StartTime_Temp[5] = ':';
            
            char tab_StartSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stValleyPeriod.stPeriod2.u8StartSec;
            sprintf(tab_StartSec,"%02d",u8Temp);
            tab_StartTime_Temp[6] = tab_StartSec[0];
            tab_StartTime_Temp[7] = tab_StartSec[1];
            
            char tab_EndHour[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stValleyPeriod.stPeriod2.u8EndHour;
            sprintf(tab_EndHour,"%02d",u8Temp);
            tab_EndTime_Temp[0] = tab_EndHour[0];
            tab_EndTime_Temp[1] = tab_EndHour[1];
            
            tab_EndTime_Temp[2] = ':';
            
            char tab_EndMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stValleyPeriod.stPeriod2.u8EndMin;
            sprintf(tab_EndMin,"%02d",u8Temp);
            tab_EndTime_Temp[3] = tab_EndMin[0];
            tab_EndTime_Temp[4] = tab_EndMin[1];
                 
            tab_EndTime_Temp[5] = ':';
            
            char tab_EndSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stValleyPeriod.stPeriod2.u8EndSec;
            sprintf(tab_EndSec,"%02d",u8Temp);
            tab_EndTime_Temp[6] = tab_EndSec[0];
            tab_EndTime_Temp[7] = tab_EndSec[1];
                        
            sprintf((char*)tab_display,"     �ȶ� 2     \nSOC:%sPWR:%s\n��ʼ:%s   \n����:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);            
        }
        else if(enumTPFVPeriod == STRATEGY_TPFV_PERIOD_THREE)
        {  
            char tab_StartHour[2] ;                 
            uint8_t u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stValleyPeriod.stPeriod3.u8StartHour;
            sprintf(tab_StartHour,"%02d",u8Temp);
            tab_StartTime_Temp[0] = tab_StartHour[0];
            tab_StartTime_Temp[1] = tab_StartHour[1];
            
            tab_StartTime_Temp[2] = ':';
            
            char tab_StartMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stValleyPeriod.stPeriod3.u8StartMin;
            sprintf(tab_StartMin,"%02d",u8Temp);
            tab_StartTime_Temp[3] = tab_StartMin[0];
            tab_StartTime_Temp[4] = tab_StartMin[1];
                 
            tab_StartTime_Temp[5] = ':';
            
            char tab_StartSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stValleyPeriod.stPeriod3.u8StartSec;
            sprintf(tab_StartSec,"%02d",u8Temp);
            tab_StartTime_Temp[6] = tab_StartSec[0];
            tab_StartTime_Temp[7] = tab_StartSec[1];
            
            char tab_EndHour[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stValleyPeriod.stPeriod3.u8EndHour;
            sprintf(tab_EndHour,"%02d",u8Temp);
            tab_EndTime_Temp[0] = tab_EndHour[0];
            tab_EndTime_Temp[1] = tab_EndHour[1];
            
            tab_EndTime_Temp[2] = ':';
            
            char tab_EndMin[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stValleyPeriod.stPeriod3.u8EndMin;
            sprintf(tab_EndMin,"%02d",u8Temp);
            tab_EndTime_Temp[3] = tab_EndMin[0];
            tab_EndTime_Temp[4] = tab_EndMin[1];
                 
            tab_EndTime_Temp[5] = ':';
            
            char tab_EndSec[2] ;                 
            u8Temp = gDisplay.stDisplaySet.stGrid.stTimeDivisionElecPrice.stValleyPeriod.stPeriod3.u8EndSec;
            sprintf(tab_EndSec,"%02d",u8Temp);
            tab_EndTime_Temp[6] = tab_EndSec[0];
            tab_EndTime_Temp[7] = tab_EndSec[1];
                        
            sprintf((char*)tab_display,"     �ȶ� 3     \nSOC:%sPWR:%s\n��ʼ:%s   \n����:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);
        }  
    }  
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
����:��ʱ��ŵ��������Ľ�����Ϣ
****************************************************************************/
void updateDisplaySystemRegularStrategyAbstractSetData_Chinese(REGULAR_TypeDef u8RegularStrategyIndex)   
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    
    if(u8RegularStrategyIndex == REGULAR_CHARGE)
    {
        sprintf(tab_display,"    ��ʱ����    \n->���          \n�ŵ�            \n                \n"); 
    }
    else if(u8RegularStrategyIndex == REGULAR_DISCHARGE)
    {
        sprintf(tab_display,"    ��ʱ����    \n���            \n->�ŵ�          \n                \n");   
    }
                     
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
����:��ʱ��ŵ��������Ľ�����Ϣ
****************************************************************************/
void updateDisplaySystemRegularStrategySetData_Chinese(REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef u8RegularStrategyIndex)   
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);   
    if(enum_RegularClass == REGULAR_CHARGE)
    {
        if(u8RegularStrategyIndex == STRATEGY_REGULAR_PERIOD_ONE)
        {
            sprintf(tab_display,"      ���      \n->ʱ��1         \nʱ��2           \nʱ��3           \n"); 
        }
        else if(u8RegularStrategyIndex == STRATEGY_REGULAR_PERIOD_TWO)
        {
            sprintf(tab_display,"      ���      \nʱ��1           \n->ʱ��2         \nʱ��3           \n");    
        }
        else if(u8RegularStrategyIndex == STRATEGY_REGULAR_PERIOD_THREE)
        {
            sprintf(tab_display,"      ���      \nʱ��1           \nʱ��2           \n->ʱ��3         \n");   
        } 
        else if(u8RegularStrategyIndex == STRATEGY_REGULAR_PERIOD_FOUR)
        {
            sprintf(tab_display,"      ���      \n->ʱ��4         \n                \n                \n");   
        }         
    }
    else if(enum_RegularClass == REGULAR_DISCHARGE)
    {
        if(u8RegularStrategyIndex == STRATEGY_REGULAR_PERIOD_ONE)
        {
            sprintf(tab_display,"      �ŵ�      \n->ʱ��1         \nʱ��2           \nʱ��3           \n"); 
        }
        else if(u8RegularStrategyIndex == STRATEGY_REGULAR_PERIOD_TWO)
        {
            sprintf(tab_display,"      �ŵ�      \nʱ��1           \n->ʱ��2         \nʱ��3           \n");    
        }
        else if(u8RegularStrategyIndex == STRATEGY_REGULAR_PERIOD_THREE)
        {
            sprintf(tab_display,"      �ŵ�      \nʱ��1           \nʱ��2           \n->ʱ��3         \n");   
        } 
        else if(u8RegularStrategyIndex == STRATEGY_REGULAR_PERIOD_FOUR)
        {
            sprintf(tab_display,"      �ŵ�      \n->ʱ��4         \n                \n                \n");    
        }          
    }
                       
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 ����:���� ϵͳ��ʱ��ŵ�ʱ������ý�����Ϣ
****************************************************************************/
void updateDisplaySystemRegularStrategyPeriodSetData_Chinese(char* strStopSOC,char* strPower, char* strStartTime, char* strEndTime,REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef enum_Period)
{ 
    memset(tab_display,0,DISPLAY_CACHE_SIZE); 
    if(enum_RegularClass == REGULAR_CHARGE)
    {
        if(enum_Period == STRATEGY_REGULAR_PERIOD_ONE)
        {                  
            sprintf(tab_display,"    ���ʱ��1   \n����:%sSOC:%s\n��ʼ:%s   \n����:%s   \n",strPower,strStopSOC,strStartTime,strEndTime);               
        }
        else if(enum_Period == STRATEGY_REGULAR_PERIOD_TWO)
        { 
            sprintf(tab_display,"    ���ʱ��2   \n����:%sSOC:%s\n��ʼ:%s   \n����:%s   \n",strPower,strStopSOC,strStartTime,strEndTime);          
        }
        else if(enum_Period == STRATEGY_REGULAR_PERIOD_THREE)
        {  
            sprintf(tab_display,"    ���ʱ��3   \n����:%sSOC:%s\n��ʼ:%s   \n����:%s   \n",strPower,strStopSOC,strStartTime,strEndTime);
        } 
        else if(enum_Period == STRATEGY_REGULAR_PERIOD_FOUR)
        {  
            sprintf(tab_display,"    ���ʱ��4   \n����:%sSOC:%s\n��ʼ:%s   \n����:%s   \n",strPower,strStopSOC,strStartTime,strEndTime);
        }         
    }
    else if(enum_RegularClass == REGULAR_DISCHARGE)
    {
        if(enum_Period == STRATEGY_REGULAR_PERIOD_ONE)
        {                  
            sprintf(tab_display,"    �ŵ�ʱ��1   \n����:%sSOC:%s\n��ʼ:%s   \n����:%s   \n",strPower,strStopSOC,strStartTime,strEndTime);               
        }
        else if(enum_Period == STRATEGY_REGULAR_PERIOD_TWO)
        { 
            sprintf(tab_display,"    �ŵ�ʱ��2   \n����:%sSOC:%s\n��ʼ:%s   \n����:%s   \n",strPower,strStopSOC,strStartTime,strEndTime);          
        }
        else if(enum_Period == STRATEGY_REGULAR_PERIOD_THREE)
        {  
            sprintf(tab_display,"    �ŵ�ʱ��3   \n����:%sSOC:%s\n��ʼ:%s   \n����:%s   \n",strPower,strStopSOC,strStartTime,strEndTime);
        } 
        else if(enum_Period == STRATEGY_REGULAR_PERIOD_FOUR)
        {  
            sprintf(tab_display,"    �ŵ�ʱ��4   \n����:%sSOC:%s\n��ʼ:%s   \n����:%s   \n",strPower,strStopSOC,strStartTime,strEndTime);
        }       
    }
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);
    GUI_Display(tab_display, 0, 0);
}



/***************************************************************************
 ����:ʵʱͳ��������ʾ ���Ľ�����Ϣ
****************************************************************************/
void updateDisplayStatisticsData_Chinese(uint8_t sU8StatisticsCounter)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);   
    if(sU8StatisticsCounter == PAGE_ONE)
    {
        float fPvData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stPVPowerGeneration / 10.0;        //�����Ż�����
        float fInputData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stInputPowerGeneration / 10.0;        //�����Ż�����
        float fOutputData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stOutputPowerGeneration / 10.0;        //�����Ż�����
        sprintf(tab_display,"    ����ͳ��    \n���:%8.1fkWh\n����:%8.1fkWh\n���:%8.1fkWh\n",fPvData,fInputData,fOutputData);
    }
    else if(sU8StatisticsCounter == PAGE_TWO)                                                              
    {
        float fChargeData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stChagePowerGeneration / 10.0;       //�����Ż�����
        float fDisChargeData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stDisChagePowerGeneration / 10.0; //�����Ż�����
        float fLoadData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stLoadPowerGeneration / 10.0;    //�����Ż�����
        sprintf(tab_display,"    ����ͳ��    \n���:%8.1fkWh\n�ŵ�:%8.1fkWh\n����:%8.1fkWh\n",fChargeData,fDisChargeData,fLoadData);
    }    
    else if(sU8StatisticsCounter == PAGE_THREE)
    {
        float fPvData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stPVPowerGeneration / 10.0;        //�����Ż�����
        float fInputData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stInputPowerGeneration / 10.0;        //�����Ż�����
        float fOutputData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stOutputPowerGeneration / 10.0;//�����Ż�����
        sprintf(tab_display,"    ����ͳ��    \n���:%8.1fkWh\n����:%8.1fkWh\n���:%8.1fkWh\n",fPvData,fInputData,fOutputData);
    }
    else if(sU8StatisticsCounter == PAGE_FOUR)
    {
        float fChargeData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stChagePowerGeneration / 10.0;       //�����Ż�����
        float fDisChargeData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stDisChagePowerGeneration / 10.0; //�����Ż�����
        float fLoadData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stLoadPowerGeneration / 10.0;    //�����Ż�����
        sprintf(tab_display,"    ����ͳ��    \n���:%8.1fkWh\n�ŵ�:%8.1fkWh\n����:%8.1fkWh\n",fChargeData,fDisChargeData,fLoadData);
    } 
    else if(sU8StatisticsCounter == PAGE_FIVE)
    {
        float fPvData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stPVPowerGeneration / 10.0;        //�����Ż�����
        float fInputData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stInputPowerGeneration / 10.0;        //�����Ż�����
        float fOutputData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stOutputPowerGeneration / 10.0;//�����Ż�����
        sprintf(tab_display,"    ����ͳ��    \n���:%8.1fkWh\n����:%8.1fkWh\n���:%8.1fkWh\n",fPvData,fInputData,fOutputData);
    }
    else if(sU8StatisticsCounter == PAGE_SIX)
    {
        float fChargeData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stChagePowerGeneration / 10.0;       //�����Ż�����
        float fDisChargeData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stDisChagePowerGeneration / 10.0; //�����Ż�����
        float fLoadData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stLoadPowerGeneration / 10.0;    //�����Ż�����
        sprintf(tab_display,"    ����ͳ��    \n���:%8.1fkWh\n�ŵ�:%8.1fkWh\n����:%8.1fkWh\n",fChargeData,fDisChargeData,fLoadData);
    }  
    else if(sU8StatisticsCounter == PAGE_SEVEN)
    {
        float fPvData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stPVPowerGeneration / 10.0;        //�����Ż�����
        float fInputData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stInputPowerGeneration / 10.0;        //�����Ż�����
        float fOutputData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stOutputPowerGeneration / 10.0;//�����Ż�����
        sprintf(tab_display,"    �ܹ�ͳ��    \n���:%8.1fkWh\n����:%8.1fkWh\n���:%8.1fkWh\n",fPvData,fInputData,fOutputData);
    }
    else if(sU8StatisticsCounter == PAGE_EIGHT)
    {
        float fChargeData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stChagePowerGeneration / 10.0;       //�����Ż�����
        float fDisChargeData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stDisChagePowerGeneration / 10.0; //�����Ż�����
        float fLoadData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stLoadPowerGeneration / 10.0;    //�����Ż�����
        sprintf(tab_display,"    �ܹ�ͳ��    \n���:%8.1fkWh\n�ŵ�:%8.1fkWh\n����:%8.1fkWh\n",fChargeData,fDisChargeData,fLoadData);
    }    
    
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);

}
#if 0
void updateDisplayStatisticsData_Chinese(uint8_t sU8StatisticsCounter)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    
    if(sU8StatisticsCounter == PAGE_ONE)
    {
        float fPvData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stPVPowerGeneration / 10.0;        //�����Ż�����
        float fLoadData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stLoadPowerGeneration / 10.0;    //�����Ż�����
        float fOutputData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stOutputPowerGeneration / 10.0;//�����Ż�����
        sprintf(tab_display,"    ����ͳ��    \n���:%-8.1f   \n����:%-8.1f   \n���:%-8.1f   \n",fPvData,fLoadData,fOutputData);  
    }
    else if(sU8StatisticsCounter == PAGE_TWO)
    {
        float fInputData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stInputPowerGeneration / 10.0;        //�����Ż�����
        float fChargeData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stChagePowerGeneration / 10.0;       //�����Ż�����
        float fDisChargeData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stDisChagePowerGeneration / 10.0; //�����Ż�����
        sprintf(tab_display,"    ����ͳ��    \n����:%-8.1f   \n���:%-8.1f   \n�ŵ�:%-8.1f   \n",fInputData,fChargeData,fDisChargeData);  
    }    
    else if(sU8StatisticsCounter == PAGE_THREE)
    {
        float fPvData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stPVPowerGeneration / 10.0;        //�����Ż�����
        float fLoadData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stLoadPowerGeneration / 10.0;    //�����Ż�����
        float fOutputData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stOutputPowerGeneration / 10.0;//�����Ż�����
        sprintf(tab_display,"    ����ͳ��    \n���:%-8.1f   \n����:%-8.1f   \n���:%-8.1f   \n",fPvData,fLoadData,fOutputData);  
    }
    else if(sU8StatisticsCounter == PAGE_FOUR)
    {
        float fInputData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stInputPowerGeneration / 10.0;        //�����Ż�����
        float fChargeData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stChagePowerGeneration / 10.0;       //�����Ż�����
        float fDisChargeData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stDisChagePowerGeneration / 10.0; //�����Ż�����
        sprintf(tab_display,"    ����ͳ��    \n����:%-8.1f   \n���:%-8.1f   \n�ŵ�:%-8.1f   \n",fInputData,fChargeData,fDisChargeData);  
    } 
    else if(sU8StatisticsCounter == PAGE_FIVE)
    {
        float fPvData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stPVPowerGeneration / 10.0;        //�����Ż�����
        float fLoadData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stLoadPowerGeneration / 10.0;    //�����Ż�����
        float fOutputData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stOutputPowerGeneration / 10.0;//�����Ż�����
        sprintf(tab_display,"    ����ͳ��    \n���:%-8.1f   \n����:%-8.1f   \n���:%-8.1f   \n",fPvData,fLoadData,fOutputData);  
    }
    else if(sU8StatisticsCounter == PAGE_SIX)
    {
        float fInputData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stInputPowerGeneration / 10.0;        //�����Ż�����
        float fChargeData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stChagePowerGeneration / 10.0;       //�����Ż�����
        float fDisChargeData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stDisChagePowerGeneration / 10.0; //�����Ż�����
        sprintf(tab_display,"    ����ͳ��    \n����:%-8.1f   \n���:%-8.1f   \n�ŵ�:%-8.1f   \n",fInputData,fChargeData,fDisChargeData);  
    }  
    else if(sU8StatisticsCounter == PAGE_SEVEN)
    {
        float fPvData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stPVPowerGeneration / 10.0;        //�����Ż�����
        float fLoadData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stLoadPowerGeneration / 10.0;    //�����Ż�����
        float fOutputData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stOutputPowerGeneration / 10.0;//�����Ż�����
        sprintf(tab_display,"    �ܹ�ͳ��    \n���:%-8.1f   \n����:%-8.1f   \n���:%-8.1f   \n",fPvData,fLoadData,fOutputData);  
    }
    else if(sU8StatisticsCounter == PAGE_EIGHT)
    {
        float fInputData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stInputPowerGeneration / 10.0;        //�����Ż�����
        float fChargeData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stChagePowerGeneration / 10.0;       //�����Ż�����
        float fDisChargeData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stDisChagePowerGeneration / 10.0; //�����Ż�����
        sprintf(tab_display,"    �ܹ�ͳ��    \n����:%-8.1f   \n���:%-8.1f   \n�ŵ�:%-8.1f   \n",fInputData,fChargeData,fDisChargeData);  
    }    
    
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 ����:����ϵͳCT����������Ľ�����Ϣ
****************************************************************************/
void updateDisplaySystemCTRatioData_Chinese(bool_t bEnableFlag,char* sCurrentCT,char* sVoltageCT)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    if(bEnableFlag == STATUS_FALSE)
    {
        sprintf(tab_display,"  Transformer Ratio  \nEnable:forbid        \nCT:%s              \nVT:%s             \n",sCurrentCT,sVoltageCT);
    }
    else
    {
        sprintf(tab_display,"  Transformer Ratio  \nEnable:enable        \nCT:%s              \nVT:%s             \n",sCurrentCT,sVoltageCT);        
    }
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
    
}
#endif
/***************************************************************************
 ����:����ϵͳ��Ե���ʹ���������Ľ�����Ϣ
****************************************************************************/
void updateDisplaySystemInsulationDetetionData_Chinese(ENABLE_TypeDef u8SetIndex)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    
    if(u8SetIndex == ENABLE_YES)
    {
        sprintf(tab_display,"    �������    \n->ʹ��          \n��ֹ            \n                \n");                                                                               
    }
    else if(u8SetIndex == ENABLE_NO)
    {
        sprintf(tab_display,"    �������    \nʹ��            \n->��ֹ          \n                \n");                                                                                  
    }
    
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
����:���� ����ͨ����ʾ������Ϣ
****************************************************************************/
void updateDisplayTipSetPassed_Chinese(void)
{
    sprintf(tab_display,"      ��ʾ      \n                \n    ���óɹ�    \n                \n");
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 ����:����ϵͳ����ʹ���������Ľ�����Ϣ
****************************************************************************/
void updateDisplayProtectSetData_Chinese(PROTECTSETAction_TypeDef u8SetIndex)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    
    if(u8SetIndex == SET_PROTECT_ISLAND_Index)
    {
        sprintf(tab_display,"    ��������    \n->�µ�          \n�ӵ�            \n©��            \n");                                                                               
    }
//    else if(u8SetIndex == SET_PROTECT_GROUND_Index)
//    {
//        sprintf(tab_display,"    ��������    \n�µ�            \n->�ӵ�          \n©��            \n");                                                                                  
//    }
//    else if(u8SetIndex == SET_PROTECT_LEAKAGE_Index)
//    {
//        sprintf(tab_display,"    ��������    \n�µ�            \n�ӵ�            \n->©��          \n");                                                                                  
//    }
    /*  �뱣���˶δ��룬�Է��ȹ������ʧЧ���޷������ر��ȱ���
    else if(u8SetIndex == SET_PROTECT_ARC_Index)
    {
        sprintf(tab_display,"    ��������    \n->����          \n����            \n�͵�ѹ��Խ      \n");                                                                                  
    } 
    else if(u8SetIndex == SET_PROTECT_OVERHEAT_Index)
    {
        sprintf(tab_display,"    ��������    \n����            \n->����          \n�͵�ѹ��Խ      \n");                                                                                  
    }
    else if(u8SetIndex == SET_PROTECT_LVRT_Index)
    {
        sprintf(tab_display,"    ��������    \n����            \n����            \n->�͵�ѹ��Խ    \n");                                                                                  
    }  
    else if(u8SetIndex == SET_PROTECT_HVRT_Index)
    {
        sprintf(tab_display,"    ��������    \n->�ߵ�ѹ��Խ    \n����            \n�����          \n");                                                                                  
    }
    else if(u8SetIndex == SET_PROTECT_LIGHT_Index)
    {
        sprintf(tab_display,"    ��������    \n�ߵ�ѹ��Խ      \n->����          \n�����          \n");                                                                                  
    }
    else if(u8SetIndex == SET_PROTECT_GEN_Index)
    {
        sprintf(tab_display,"    ��������    \n�ߵ�ѹ��Խ      \n����            \n->�����        \n");                                                                                  
    }
    else if(u8SetIndex == SET_PROTECT_LFRT_Index)
    {
        sprintf(tab_display,"    ��������    \n->��Ƶ�ʴ�Խ    \n��Ƶ�ʴ�Խ      \nP(V)            \n");                                                                                  
    }    
    else if(u8SetIndex == SET_PROTECT_HFRT_Index)
    {
        sprintf(tab_display,"    ��������    \n��Ƶ�ʴ�Խ      \n->��Ƶ�ʴ�Խ    \nP(V)            \n");                                                                                  
    }
    else if(u8SetIndex == SET_PROTECT_P_V_Index)
    {
        sprintf(tab_display,"    ��������    \n��Ƶ�ʴ�Խ      \n��Ƶ�ʴ�Խ      \n->P(V)          \n");                                                                                  
    }  
    else if(u8SetIndex == SET_PROTECT_P_F_Index)
    {
        sprintf(tab_display,"    ��������    \n->P(F)          \nQ(V)            \nQ(P)            \n");                                                                                  
    } 
    else if(u8SetIndex == SET_PROTECT_Q_V_Index)
    {
        sprintf(tab_display,"    ��������    \nP(F)            \n->Q(V)          \nQ(P)            \n");                                                                                  
    }     
    else if(u8SetIndex == SET_PROTECT_Q_P_Index)
    {
        sprintf(tab_display,"    ��������    \nP(F)            \nQ(V)            \n->Q(P)          \n");                                                                                  
    }    
    else if(u8SetIndex == SET_PROTECT_CPF_Index)
    {
        sprintf(tab_display,"    ��������    \n->CPF           \nCQ              \n                \n");                                                                                  
    }      
    else if(u8SetIndex == SET_PROTECT_CQ_Index)
    {
        sprintf(tab_display,"    ��������    \nCPF             \n->CQ            \n                \n");                                                                                  
    }  
*/
//    else if(u8SetIndex == SET_PROTECT_ARC_Index)
//    {
//        sprintf(tab_display,"    ��������    \n->����          \n�͵�ѹ��Խ      \n�ߵ�ѹ��Խ      \n");                                                                                  
//    }
//    else if(u8SetIndex == SET_PROTECT_LVRT_Index)
//    {
//        sprintf(tab_display,"    ��������    \n����            \n->�͵�ѹ��Խ    \n�ߵ�ѹ��Խ      \n");                                                                                  
//    }  
//    else if(u8SetIndex == SET_PROTECT_HVRT_Index)
//    {
//        sprintf(tab_display,"    ��������    \n����            \n�͵�ѹ��Խ      \n->�ߵ�ѹ��Խ    \n");                                                                                  
//    }
//    else if(u8SetIndex == SET_PROTECT_LIGHT_Index)
//    {
//        sprintf(tab_display,"    ��������    \n->����          \n�����          \n��Ƶ�ʴ�Խ      \n");                                                                                  
//    }
//    else if(u8SetIndex == SET_PROTECT_GEN_Index)
//    {
//        sprintf(tab_display,"    ��������    \n����            \n->�����        \n��Ƶ�ʴ�Խ      \n");                                                                                  
//    }
//    else if(u8SetIndex == SET_PROTECT_LFRT_Index)
//    {
//        sprintf(tab_display,"    ��������    \n����            \n�����          \n->��Ƶ�ʴ�Խ    \n");                                                                                  
//    }    
//    else if(u8SetIndex == SET_PROTECT_HFRT_Index)
//    {
//        sprintf(tab_display,"    ��������    \n->��Ƶ�ʴ�Խ    \nP(V)            \nP(F)            \n");                                                                                  
//    }
//    else if(u8SetIndex == SET_PROTECT_P_V_Index)
//    {
//        sprintf(tab_display,"    ��������    \n��Ƶ�ʴ�Խ      \n->P(V)          \nP(F)            \n");                                                                                  
//    }  
//    else if(u8SetIndex == SET_PROTECT_P_F_Index)
//    {
//        sprintf(tab_display,"    ��������    \n��Ƶ�ʴ�Խ      \nP(V)            \n->P(F)          \n");                                                                                  
//    } 
//    else if(u8SetIndex == SET_PROTECT_Q_V_Index)
//    {
//        sprintf(tab_display,"    ��������    \n->Q(V)          \nQ(P)            \nCPF            \n");                                                                                  
//    }     
//    else if(u8SetIndex == SET_PROTECT_Q_P_Index)
//    {
//        sprintf(tab_display,"    ��������    \nQ(V)            \n->Q(P)          \nCPF             \n");                                                                                  
//    }    
//    else if(u8SetIndex == SET_PROTECT_CPF_Index)
//    {
//        sprintf(tab_display,"    ��������    \nQ(V)            \nQ(P)            \n->CPF           \n");                                                                                  
//    }      
//    else if(u8SetIndex == SET_PROTECT_CQ_Index)
//    {
//        sprintf(tab_display,"    ��������    \n->CQ            \n                \n                \n");                                                                                  
//    }
//    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}
//������ ����ϵͳ����ʹ�����ý�����_����

void updateDisplayProtectItemNameSetData_Chinese(ENABLE_CLASS_TypeDef enableClass, char * sEnableName_Chinese)
{
        //char sEnableName_Chinese[17] = {""}; 
        if(enableClass == ENABLE_CLASS_CURVE_SCAN)
        {  
            sprintf(sEnableName_Chinese   ,"%s","   IV����ɨ��   ");
        }
        else if(enableClass == ENABLE_CLASS_BATTERY_ENABLE)
        {
            sprintf(sEnableName_Chinese   ,"%s","    BMS ʹ��    ");
        }
        else if(enableClass == ENABLE_CLASS_BATTERY_WAKEUP)
        {
            sprintf(sEnableName_Chinese   ,"%s","    BMS ����    ");
        }
        else if(enableClass == ENABLE_CLASS_SELL)
        {
            sprintf(sEnableName_Chinese   ,"%s","    ��������    ");
        }
        else if(enableClass == ENABLE_CLASS_ANTIREFLUX)
        {
            sprintf(sEnableName_Chinese   ,"%s","     ������     ");
        }    
        else if(enableClass == ENABLE_CLASS_GEN)
        {
            sprintf(sEnableName_Chinese   ,"%s","   �����ʹ��   ");
        }
        else if(enableClass == ENABLE_CLASS_ISLAND)
        {
            sprintf(sEnableName_Chinese   ,"%s","      �µ�      ");
        }
        else if(enableClass == ENABLE_CLASS_GROUND)
        {
            sprintf(sEnableName_Chinese   ,"%s","      �ӵ�      ");
        }
        else if(enableClass == ENABLE_CLASS_LEAKAGE)
        {
            sprintf(sEnableName_Chinese   ,"%s","      ©��      ");
        }
        else if(enableClass == ENABLE_CLASS_ARC)
        {
            sprintf(sEnableName_Chinese   ,"%s","      ����      ");
        }
        //else if(enableClass == ENABLE_CLASS_OVERHEAT)
        //{
            //sprintf(sEnableName_Chinese   ,"%s","      ����      ");
        //}
        else if(enableClass == ENABLE_CLASS_LVRT)
        {
            sprintf(sEnableName_Chinese   ,"%s","   �͵�ѹ��Խ   "); //LVRT��low voltage ride through 
        }
        else if(enableClass == ENABLE_CLASS_HVRT)
        {
            sprintf(sEnableName_Chinese   ,"%s","   �ߵ�ѹ��Խ   "); //HVRT��High voltage ride through
        }
        else if(enableClass == ENABLE_CLASS_LIGHT)
        {
            sprintf(sEnableName_Chinese   ,"%s","      ����      ");
        }
        else if(enableClass == ENABLE_CLASS_GEN_PROTECT)
        {
            sprintf(sEnableName_Chinese   ,"%s","     �����     ");
        }
        else if(enableClass == ENABLE_CLASS_INSULATION_IMPEDANCE)
        {
            sprintf(sEnableName_Chinese   ,"%s","    ��Ե�迹    ");  //II:Insulation impedance
        }
        else if(enableClass == ENABLE_CLASS_LFRT)
        {
            sprintf(sEnableName_Chinese   ,"%s","   ��Ƶ�ʴ�Խ   ");  //LVRT��low frequency ride through 
        }
        else if(enableClass == ENABLE_CLASS_HFRT)
        {
            sprintf(sEnableName_Chinese   ,"%s","   ��Ƶ�ʴ�Խ   ");  //HVRT��High frequency ride through
        }
        else if(enableClass == ENABLE_CLASS_P_V)
        {
            sprintf(sEnableName_Chinese   ,"%s","    P(V) ����   ");  //
        }
        else if(enableClass == ENABLE_CLASS_P_F)
        {
            sprintf(sEnableName_Chinese   ,"%s","    P(F) ����   ");  //
        }
        else if(enableClass == ENABLE_CLASS_Q_V)
        {
            sprintf(sEnableName_Chinese   ,"%s","    Q(V) ����   ");  //
        }
        else if(enableClass == ENABLE_CLASS_Q_P)
        {
            sprintf(sEnableName_Chinese   ,"%s","    Q(P) ����   ");  //
        }
        else if(enableClass == ENABLE_CLASS_CPF)
        {
            sprintf(sEnableName_Chinese   ,"%s","    CPF ����    ");  //
        }
        else if(enableClass == ENABLE_CLASS_CQ)
        {
            sprintf(sEnableName_Chinese   ,"%s","     CQ ����    ");  //
        }
}

/***************************************************************************
 ����:����ϵͳ��Ե���ʹ���������Ľ�����Ϣ
****************************************************************************/
void updateDisplayProtectItemSetData_Chinese(ENABLE_TypeDef sU8ProtectSelected,char * sEnableName)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    if(sU8ProtectSelected == ENABLE_NO)
    {
       sprintf(tab_display,"%s\nʹ��            \n->��ֹ          \n                \n",sEnableName);
    }
    else
    {
       sprintf(tab_display,"%s\n->ʹ��          \n��ֹ            \n                \n",sEnableName);
    } 
    
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 ����:�������PVSET���Ľ���
****************************************************************************/
void updateDisplayPVSetData_Chinese(uint8_t u8PVSetIndex)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);    
    if(u8PVSetIndex == SET_PV_CONTROLWAY_Index)
    {
        sprintf(tab_display,"    �������    \n->������Ʒ���  \nIV����ɨ��      \n                \n");
    }
    else if(u8PVSetIndex == SET_PV_CURVESCAN_Index)
    {
        sprintf(tab_display,"    �������    \n������Ʒ���    \n->IV����ɨ��    \n                \n");
    }
    else
    {
                    
    }
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 ����:������Ʒ�ʽ����PVCONTROLWAYSET���Ľ���
****************************************************************************/
void updateDisplayPVControlWaySetData_Chinese(uint8_t u8PVContWaySetIndex)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    if(u8PVContWaySetIndex == PV_WAY_ALONE)
    {
        sprintf(tab_display,"  ������Ʒ���  \n->����          \n����            \n                \n");
    }
    else if(u8PVContWaySetIndex == PV_WAY_PARAL)
    {
        sprintf(tab_display,"  ������Ʒ���  \n����            \n->����          \n                \n");
    }
    else
    {
                    
    }
    
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
    
}

/***************************************************************************
 ����:�������������ʾ ���Ľ�����Ϣ
****************************************************************************/
void updateDisplayBMSSetData_Chinese(uint8_t sU8BMSSetCounter)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
       
    if(sU8BMSSetCounter == BMS_CLASS_BMS)
    {
        sprintf(tab_display,"    �������    \n->ʹ��          \n����            \n                \n"); 
    }
    //else if(sU8BMSSetCounter == BMS_CLASS_WAKEUP)
    //{
    //    sprintf(tab_display,"    �������    \nʹ��            \n->����          \n����            \n");   
    //}
    //else if(sU8BMSSetCounter == BMS_CLASS_MANUFACTURER)
    //{
    //    sprintf(tab_display,"    �������    \nʹ��            \n����            \n->����          \n");  
    //}
    else if(sU8BMSSetCounter == BMS_CLASS_TYPE)
    {
        sprintf(tab_display,"    �������    \nʹ��            \n->����          \n                \n");  
    }
                  
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 ����:�������������ʾ ���Ľ�����Ϣ
****************************************************************************/
void updateDisplayBatteryManufacturerSetData_Chinese(uint8_t sU8BatteryManufacturerCounter)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
       
    if(sU8BatteryManufacturerCounter == BMS_MANU_CVTE)
    {
        sprintf(tab_display,"    BMS ����    \n->CVTE          \nPylon           \n                \n"); 
    }
    //else if(sU8BatteryManufacturerCounter == BMS_MANU_LG)
    //{
    //    sprintf(tab_display,"    BMS ����    \nCVTE            \n->LG            \nPylon           \n");   
    //}
    else if(sU8BatteryManufacturerCounter == BMS_MANU_Pylon)
    {
        sprintf(tab_display,"    BMS ����    \nCVTE            \n->Pylon         \n                \n");  
    }
                  
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 ����:�������������ʾ ���Ľ�����Ϣ
****************************************************************************/
void updateDisplayBatteryTypeSetData_Chinese(uint8_t sU8BatteryTypeCounter)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
       
    if(sU8BatteryTypeCounter ==  BMS_TYPE_LI_ION)
    {
        sprintf(tab_display,"    BMS ����    \n->LI.ION        \nLEAD.ACID       \n                \n"); 
    }
    else if(sU8BatteryTypeCounter == BMS_TYPE_LEAD_ACID)
    {
        sprintf(tab_display,"    BMS ����    \nLI.ION          \n->LEAD.ACID     \n                \n");   
    }

                  
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}
/***************************************************************************
 ����:�������������ʾ ���Ľ�����Ϣ
****************************************************************************/
void updateDisplayGridSetData_Chinese(uint8_t sU8BMSSetCounter)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    #if 0  
    if(sU8BMSSetCounter == SET_GRID_Sell_Index)
    {
        sprintf(tab_display,"   �������� 1   \n->����ʹ��      \n������          \n���            \n"); 
    }
    //else if(sU8BMSSetCounter == SET_GRID_Antireflux_Index)
    //{
    //    sprintf(tab_display,"   �������� 1   \n����ʹ��        \n->������        \n���            \n");   
    //}
    else if(sU8BMSSetCounter == SET_GRID_Meter_Index)
    {
        sprintf(tab_display,"   �������� 1   \n����ʹ��        \n������          \n->���          \n");  
    }
    else if(sU8BMSSetCounter == SET_GRID_SR_Index)
    {
        sprintf(tab_display,"   �������� 2   \n->����          \n�۸�            \n                \n");  
    }
    else if(sU8BMSSetCounter == SET_GRID_Price_Index)
    {
        sprintf(tab_display,"   �������� 2   \n����            \n->�۸�          \n                \n");  
    }

    
    if(sU8BMSSetCounter == SET_GRID_Sell_Index)
    {
        sprintf(tab_display,"   �������� 1   \n->����ʹ��      \n���            \n������׼        \n"); 
    }
    else if(sU8BMSSetCounter == SET_GRID_Meter_Index)
    {
        sprintf(tab_display,"   �������� 1   \n����ʹ��        \n->���          \n������׼        \n");  
    }
    else if(sU8BMSSetCounter == SET_GRID_SR_Index)
    {
        sprintf(tab_display,"   �������� 1   \n����ʹ��        \n���            \n->������׼      \n");
    }
    else if(sU8BMSSetCounter == SET_GRID_Price_Index)
    {
        sprintf(tab_display,"   �������� 2   \n->�۸�          \n�޹����Ʒ�ʽ    \n�޹���������    \n");
    }
    else if(sU8BMSSetCounter == SET_GRID_ReactPowerWay_Index)
    {
        sprintf(tab_display,"   �������� 2   \n�۸�            \n->�޹����Ʒ�ʽ  \n�޹���������    \n");
    }
    else if(sU8BMSSetCounter == SET_GRID_ReactPower_Index)
    {
        sprintf(tab_display,"   �������� 2   \n�۸�            \n�޹����Ʒ�ʽ    \n->�޹���������  \n");
    }
    else if(sU8BMSSetCounter == SET_GRID_PF_Index)
    {
        sprintf(tab_display,"   �������� 3   \n->��������      \n                \n                \n");
    }
     #endif           
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 ����:������������ ���Ľ�����Ϣ
****************************************************************************/
void updateDisplayGridSRSetData_Chinese(uint8_t sU8BMSSetCounter)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
       
    if(sU8BMSSetCounter == SR_EURTEN)
    {
        sprintf(tab_display,"   ������׼ 1   \n->EUR Union     \nDE              \nUK              \n"); 
    }
    else if(sU8BMSSetCounter == SR_DE)
    {
        sprintf(tab_display,"   ������׼ 1   \nEUR Union       \n->DE            \nUK              \n");
    }
    else if(sU8BMSSetCounter == SR_UK)
    {
        sprintf(tab_display,"   ������׼ 1   \nEUR Union       \nDE              \n->UK            \n");
    }
    else if(sU8BMSSetCounter == SR_ZA)
    {
        sprintf(tab_display,"   ������׼ 2   \n->ZA            \nAU              \n                \n");
    }
    else if(sU8BMSSetCounter == SR_AU)
    {
        sprintf(tab_display,"   ������׼ 2   \nZA              \n->AU            \n                \n");
    }
                  
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);  
}

/***************************************************************************
 ����:����������� ���Ľ�����Ϣ
****************************************************************************/
void updateDisplayGridPriceSetData_Chinese(uint8_t sU8BMSSetCounter)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);   
    /*
    if(sU8BMSSetCounter == TPFV_TIP)
    {
        sprintf(tab_display,"   �����۸� 1   \n->���          \n���            \nƽ��            \n"); 
    }
    else if(sU8BMSSetCounter == TPFV_PEAK)
    {
        sprintf(tab_display,"   �����۸� 1   \n���            \n->���          \nƽ��            \n");   
    }
    else if(sU8BMSSetCounter == TPFV_FLAT)
    {
        sprintf(tab_display,"   �����۸� 1   \n���            \n���            \n->ƽ��          \n");  
    }
    else if(sU8BMSSetCounter == TPFV_VALLEY)
    {
        sprintf(tab_display,"   �����۸� 2   \n->�ȶ�          \n                \n                \n");  
    } 
    */                
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 

    if(sU8BMSSetCounter == TPFV_PEAK)
    {
        sprintf(tab_display,"   �����۸� 1   \n->���          \nƽ��            \n�ȶ�            \n");
    }
    else if(sU8BMSSetCounter == TPFV_FLAT)
    {
        sprintf(tab_display,"   �����۸� 1   \n���            \n->ƽ��          \n�ȶ�            \n");
    }
    else if(sU8BMSSetCounter == TPFV_VALLEY)
    {
        sprintf(tab_display,"   �����۸� 1   \n���            \nƽ��            \n->�ȶ�          \n");
    }
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
  ����:�޹������������Ľ���
****************************************************************************/
void updateDisplayGridReactivePowerSetData_Chinese(char *ReactivePowerValue)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
       
    sprintf(tab_display,"  �޹���������  \n                \n����:%s W  \n                \n",ReactivePowerValue);
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
  ����:�޹����Ʒ�ʽ�������Ľ���
****************************************************************************/
void updateDisplayGridReactPowerControlWaySetData_Chinese(uint8_t u8Way)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    if(u8Way == REACTPOWER_CONTROL_REACTPOWER)
    {
       sprintf(tab_display,"  �޹����Ʒ�ʽ  \n->�޹����ʿ���  \n������������    \n                \n");
    }
    else
    {
       sprintf(tab_display,"  �޹����Ʒ�ʽ  \n�޹����ʿ���    \n->������������  \n                \n");
    }
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
  ����:���������������Ľ���
****************************************************************************/
void updateDisplayGridPowerFactorSetData_Chinese(char* strPF)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
           
    sprintf(tab_display,"  ������������  \n                \n���� :%s %%\n                \n",strPF);
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);
    GUI_Display(tab_display, 0, 0); 
}

/***************************************************************************
 ����:���� ȷ����ʾ��Ϣ
****************************************************************************/
void updateDisplaySystemConfirm_Chinese(void)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    sprintf(tab_display,"                \n   ȷ����ɾ��?  \n                \n                \n");
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0);
}
/***************************************************************************
 ����:�������ƽ�ȷ�ʱ���� ���Ľ�����Ϣ
****************************************************************************/
void updateDisplayGridPriceTPFVSetData_Chinese(uint8_t sU8TPFVSetCounter, char* strPrice,TPFV_TypeDef enum_tpfv)
{
        memset(tab_display,0,DISPLAY_CACHE_SIZE);
    
    if(enum_tpfv == TPFV_TIP)
    {
        if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_PRICE)
        {
            sprintf(tab_display,"     ��� 1     \n->�۸�:%s    \nʱ�� 1          \nʱ�� 2          \n",strPrice);  
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_ONE)
        {
            sprintf(tab_display,"     ��� 1     \n�۸�:%s      \n->ʱ�� 1        \nʱ�� 2          \n",strPrice);
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_TWO)
        {
            sprintf(tab_display,"     ��� 1     \n�۸�:%s      \nʱ�� 1          \n->ʱ�� 2        \n",strPrice);
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_THREE)
        {
            sprintf(tab_display,"     ��� 2     \n->ʱ�� 3        \n                \n                \n");
        }
    }
    else if(enum_tpfv == TPFV_PEAK)
    {
        if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_PRICE)
        {
            sprintf(tab_display,"     ��� 1     \n->�۸�:%s    \nʱ�� 1          \nʱ�� 2          \n",strPrice);  
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_ONE)
        {
            sprintf(tab_display,"     ��� 1     \n�۸�:%s      \n->ʱ�� 1        \nʱ�� 2          \n",strPrice);
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_TWO)
        {
            sprintf(tab_display,"     ��� 1     \n�۸�%s       \nʱ�� 1          \n->ʱ�� 2        \n",strPrice);
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_THREE)
        {
            sprintf(tab_display,"     ��� 2     \n->ʱ�� 3        \n                \n                \n");
        }  
    }
    else if(enum_tpfv == TPFV_FLAT)
    {
        if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_PRICE)
        {
            sprintf(tab_display,"     ƽ�� 1     \n->�۸�:%s    \nʱ�� 1          \nʱ�� 2          \n",strPrice);  
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_ONE)
        {
            sprintf(tab_display,"     ƽ�� 1     \n�۸�:%s      \n->ʱ�� 1        \nʱ�� 2          \n",strPrice);
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_TWO)
        {
            sprintf(tab_display,"     ƽ�� 1     \n�۸�:%s      \nʱ�� 1          \n->ʱ�� 2        \n",strPrice);
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_THREE)
        {
            sprintf(tab_display,"     ƽ�� 2     \n->ʱ�� 3        \n                \n                \n");
        } 
    }
    else if(enum_tpfv == TPFV_VALLEY)
    {        
        if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_PRICE)
        {
            sprintf(tab_display,"     �ȶ� 1     \n->�۸�:%s    \nʱ�� 1          \nʱ�� 2          \n",strPrice);  
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_ONE)
        {
            sprintf(tab_display,"     �ȶ� 1     \n�۸�:%s      \n->ʱ�� 1        \nʱ�� 2          \n",strPrice);
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_TWO)
        {
            sprintf(tab_display,"     �ȶ� 1     \n�۸�:%s      \nʱ�� 1          \n->ʱ�� 2        \n",strPrice);
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_THREE)
        {
            sprintf(tab_display,"     �ȶ� 2     \n->ʱ�� 3        \n                \n                \n");
        } 
    }  
                         
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 ����:������ʱ�����ʼʱ������ ���Ľ�����Ϣ
****************************************************************************/

void updateDisplayGridPriceTPFVTimePeriodSetData_Chinese(char* strStartTime, char* strEndTime, TPFV_TypeDef enum_tpfv, TPFV_Price_TypeDef enumTPFVPeriod)    
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    if(enum_tpfv == TPFV_PEAK)
    {    
        if(enumTPFVPeriod == PRICE_TPFV_PERIOD_ONE)
        {
            sprintf(tab_display,"     ��� %d     \n��ʼ:%s   \n����:%s   \n                \n",enumTPFVPeriod,strStartTime,strEndTime); 
        }
        else if(enumTPFVPeriod == PRICE_TPFV_PERIOD_TWO)
        {
            sprintf(tab_display,"     ��� %d     \n��ʼ:%s   \n����:%s   \n                \n",enumTPFVPeriod,strStartTime,strEndTime);   
        }
        else if(enumTPFVPeriod == PRICE_TPFV_PERIOD_THREE)
        {
            sprintf(tab_display,"     ��� %d     \n��ʼ:%s   \n����:%s   \n                \n",enumTPFVPeriod,strStartTime,strEndTime); 
        }
    }
    else if(enum_tpfv == TPFV_FLAT)
    {
        if(enumTPFVPeriod == PRICE_TPFV_PERIOD_ONE)
        {
            sprintf(tab_display,"     ƽ�� %d     \n��ʼ:%s   \n����:%s   \n                \n",enumTPFVPeriod,strStartTime,strEndTime); 
        }
        else if(enumTPFVPeriod == PRICE_TPFV_PERIOD_TWO)
        {
            sprintf(tab_display,"     ƽ�� %d     \n��ʼ:%s   \n����:%s   \n                \n",enumTPFVPeriod,strStartTime,strEndTime);   
        }
        else if(enumTPFVPeriod == PRICE_TPFV_PERIOD_THREE)
        {
            sprintf(tab_display,"     ƽ�� %d     \n��ʼ:%s   \n����:%s   \n                \n",enumTPFVPeriod,strStartTime,strEndTime); 
        }
    }
    else if(enum_tpfv == TPFV_VALLEY)
    {
        if(enumTPFVPeriod == PRICE_TPFV_PERIOD_ONE)
        {
            sprintf(tab_display,"     �ȶ� %d     \n��ʼ:%s   \n����:%s   \n                \n",enumTPFVPeriod,strStartTime,strEndTime); 
        }
        else if(enumTPFVPeriod == PRICE_TPFV_PERIOD_TWO)
        {
            sprintf(tab_display,"     �ȶ� %d     \n��ʼ:%s   \n����:%s   \n                \n",enumTPFVPeriod,strStartTime,strEndTime);   
        }
        else if(enumTPFVPeriod == PRICE_TPFV_PERIOD_THREE)
        {
            sprintf(tab_display,"     �ȶ� %d     \n��ʼ:%s   \n����:%s   \n                \n",enumTPFVPeriod,strStartTime,strEndTime); 
        }
    }
                         
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 ����:�����������Ľ���
****************************************************************************/
void  updateDisplayUpgradeData_Chinese(Upgrade_TypeDef u8UpgradeIndex)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    if(u8UpgradeIndex == UPGRADE_EMS)
    {
        sprintf(tab_display,"    ��������    \n->EMS           \nDSP             \n����MCU         \n");   
    }
    else if(u8UpgradeIndex == UPGRADE_DSP)
    {
        sprintf(tab_display,"    ��������    \nEMS             \n->DSP           \n����MCU         \n");
    }
    else if(u8UpgradeIndex == UPGRADE_BACKUP_MCU)
    {
        sprintf(tab_display,"    ��������    \nEMS             \nDSP             \n->����MCU       \n");
    }
    else if(u8UpgradeIndex == UPGRADE_BMS)
    {
        sprintf(tab_display,"    ��������    \n->BMS           \n                \n                \n");
    }
    
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);
    GUI_Display(tab_display, 0, 0); 
}


/*��ݷ�ʽ����*/

//ESC+DOWN
/***************************************************************************
 ����:ϵͳ������ʾ ���Ľ�����Ϣ
****************************************************************************/
void updateDisplaySystemData_Chinese(uint8_t sU8SystemCounter)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    if(sU8SystemCounter == PAGE_ONE)
    {
        char tab_SR[10] = {""}; //zh-cn  
        if(gDisplay.stDisplaySet.stGrid.u8SafetyRegulationType == SR_EURTEN) 
        {
            sprintf(tab_SR,"%s","Eur Union");      
        }
        if(gDisplay.stDisplaySet.stGrid.u8SafetyRegulationType == SR_DE) 
        {
            sprintf(tab_SR,"%s","DE       ");      
        }
        else if(gDisplay.stDisplaySet.stGrid.u8SafetyRegulationType == SR_UK)
        {
            sprintf(tab_SR,"%s","UK       ");
        }
        else if(gDisplay.stDisplaySet.stGrid.u8SafetyRegulationType == SR_ZA)
        {
            sprintf(tab_SR,"%s","ZA       ");
        }
        else if(gDisplay.stDisplaySet.stGrid.u8SafetyRegulationType == SR_AU)
        {
            sprintf(tab_SR,"%s","AU       ");
        }
        else
        {
            sprintf(tab_SR,"%s","Null");
        }
        
        char tab_PVWay[7] = {""}; 

        if(gDisplay.stDisplaySet.stPV.u8PVControlWay == PV_WAY_ALONE) 
        {
            sprintf(tab_PVWay,"%s","����   ");      
        }
        else
        {
            sprintf(tab_PVWay,"%s","����   "); 
        }
                
        sprintf(tab_display,"   ϵͳ���� %d   \n����:%s    \n����:%s       \nPV��ʽ:%s \n",sU8SystemCounter+1,"����   ",tab_SR,tab_PVWay);
  
    }
    else if(sU8SystemCounter == PAGE_TWO)
    {
        char tab_Work[9] = {""}; 
        
        if(gDisplay.stDisplaySet.stStrategy.u8StrategyType == STRATEGY_TPFV)
        {
            sprintf(tab_Work,"%s","���ƽ��");
        }
        else if(gDisplay.stDisplaySet.stStrategy.u8StrategyType == STRATEGY_REGULAR)
        {
            sprintf(tab_Work,"%s","��ʱ    "); 
        }
        else if(gDisplay.stDisplaySet.stStrategy.u8StrategyType == STRATEGY_SELF)
        {
            sprintf(tab_Work,"%s","�Է�����"); 
        }
        else if(gDisplay.stDisplaySet.stStrategy.u8StrategyType == STRATEGY_BACKUP)
        {
            sprintf(tab_Work,"%s","����    "); 
        }
        else if(gDisplay.stDisplaySet.stStrategy.u8StrategyType == STRATEGY_GEN)
        {
            sprintf(tab_Work,"%s","�����  "); 
        }
         
        char tab_Anti[5] = {""}; 
        
        if(gDisplay.stDisplaySet.stGrid.u8PreventReverseFlowControlFlag == ENABLE_YES)
        {   
            sprintf(tab_Anti,"%s","��  ");  
        }
        else
        {
            sprintf(tab_Anti,"%s","��  "); 
        } 
        
        char tab_BMS_Manufacturer[7] = {""}; 
        
        if(gDisplay.stDisplaySet.stBMS.u8ProtocolType == BMS_MANU_CVTE)
        {   
            sprintf(tab_BMS_Manufacturer,"%s","CVTE  ");  
        }
        //else if(gDisplay.stDisplaySet.stBMS.u8ProtocolType == BMS_MANU_LG)
        //{
        //    sprintf(tab_BMS_Manufacturer,"%s","LG    ");
        //}
        else if(gDisplay.stDisplaySet.stBMS.u8ProtocolType == BMS_MANU_Pylon)
        {
            sprintf(tab_BMS_Manufacturer,"%s","Pylon ");
        }
     
        sprintf(tab_display,"   ϵͳ���� %d   \nģʽ:%s   \n������:%s     \nBMS:%s      \n",sU8SystemCounter+1,tab_Work,tab_Anti,tab_BMS_Manufacturer);
  
    }    
    else if(sU8SystemCounter == PAGE_THREE)
    {
        Display_DSP_MCU_Version stVersion;
        memset(&stVersion,0,sizeof(Display_DSP_MCU_Version));
        GetDisplaySoftwareVersion(&stVersion);
        char tab_Dsp_Version[13];
        sprintf(tab_Dsp_Version,"V%03d.%03d.%03d",stVersion.u16MainDspVerV,stVersion.u16MainDspVerB,stVersion.u16MainDspVerD);
        char tab_Ems_Version[13];
        sprintf(tab_Ems_Version,"V%03d.%03d.%03d",VER_V,VER_B,VER_D);
        char tab_Bak_Version[13];
        sprintf(tab_Bak_Version,"V%03d.%03d.%03d",stVersion.u16BackMcuVerV,stVersion.u16BackMcuVerB,stVersion.u16BackMcuVerD);
        sprintf(tab_display,"   ϵͳ���� %d   \nDSP:%s\nEMS:%s\nAux:%s\n",sU8SystemCounter+1,tab_Dsp_Version,tab_Ems_Version,tab_Bak_Version); 
    }
    else if(sU8SystemCounter == PAGE_FOUR)
    {
        float fSystemTemp = gDisplay.stDisplayData.stSystemData.s16SystemTemperature / 10.0;        //�����Ż�����   
        sprintf(tab_display,"   ϵͳ���� %d   \nϵͳ�¶�:%-5.1f  \n                \n                \n",sU8SystemCounter+1,fSystemTemp); 
    }    
    
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 ����:ʵʱ������ʾ ���Ľ�����Ϣ Up + Down
****************************************************************************/
void updateDisplayRealtimeData_Chinese(uint8_t sU8RealtimeCounter)    
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    
    if(sU8RealtimeCounter == PAGE_ONE)
    {
        float fCurrent   = gDisplay.stDisplayData.stGridData.sGridcurrent / 10.0;
        float fVoltage   = gDisplay.stDisplayData.stGridData.u16GridVoltage / 10.0;
        float fFrequency = gDisplay.stDisplayData.stGridData.u16GridFrequency / 100.00;
        
        sprintf(tab_display,"   �������� 1   \n��ѹ:  %8.1fV\n����:  %8.1fA\nƵ��: %8.2fHz\n",fVoltage,fCurrent,fFrequency);
    }
    else if(sU8RealtimeCounter == PAGE_TWO)
    {
        float fReactivePower   = gDisplay.stDisplayData.stGridData.sGridReactivePower / 10.0;
        float fGridActivePower = gDisplay.stDisplayData.stGridData.sGridActivePower / 10.0;
        
        sprintf(tab_display,"   �������� 2   \n�й�:    %6.1fW\n�޹�:  %6.1fVar\n                \n",fGridActivePower,fReactivePower);
    }    
    else if(sU8RealtimeCounter == PAGE_THREE)
    {
        float fVoltage   = gDisplay.stDisplayData.stPV.stPV1.u16PVVoltage / 10.0;
        float fCurrent   = gDisplay.stDisplayData.stPV.stPV1.sPVCurrent / 10.0;
        float fPower     = gDisplay.stDisplayData.stPV.stPV1.sPVPower / 10.0;
        
        sprintf(tab_display,"    PV1���� 1   \n��ѹ:  %8.1fV\n����:  %8.1fA\n����:  %8.3fW\n",fVoltage,fCurrent,fPower);
    }
    else if(sU8RealtimeCounter == PAGE_FOUR)
    {
        float fVoltage   = gDisplay.stDisplayData.stPV.stPV2.u16PVVoltage / 10.0;
        float fCurrent   = gDisplay.stDisplayData.stPV.stPV2.sPVCurrent / 10.0;
        float fPower     = gDisplay.stDisplayData.stPV.stPV2.sPVPower / 10.0;
        
        sprintf(tab_display,"    PV2���� 1   \n��ѹ:  %8.1fV\n����:  %8.1fA\n����:  %8.3fW\n",fVoltage,fCurrent,fPower);  
    } 
    else if(sU8RealtimeCounter == PAGE_FIVE)
    {
        float fVoltage   = gDisplay.stDisplayData.stLoad.u16LoadVoltage / 10.0;
        float fCurrent   = gDisplay.stDisplayData.stLoad.sLoadcurrent / 10.0;
        float fPower     = gDisplay.stDisplayData.stLoad.sLoadPower / 10.0;
        sprintf(tab_display,"   �������� 1   \n��ѹ:  %8.1fV\n����:  %8.1fA\n����:  %8.3fW\n",fVoltage,fCurrent,fPower);  
    } 
    else if(sU8RealtimeCounter == PAGE_SIX)
    {
        float fLoadRate = (float) gDisplay.stDisplayData.stLoad.sLoadPower / DEVICERATEDPOWER;
        sprintf(tab_display,"   �������� 2   \n������:     %3.1f%%\n                \n                \n",fLoadRate);  
    } 
    else if(sU8RealtimeCounter == PAGE_SEVEN)
    {
        float fVoltage   = gDisplay.stDisplayData.stBMS.u16BMSVoltage / 10.0;
        float fCurrent   = gDisplay.stDisplayData.stBMS.sBMSCurrent / 10.0;
        if(gDisplay.stDisplayData.stBMS.sBMSCurrent > 0)
        {
            sprintf(tab_display,"   BMS���� 1    \n״̬:       �ŵ�\n��ѹ:  %8.1fV\n��ѹ:  %8.1fA\n",fVoltage,fCurrent);
        }
        else if(gDisplay.stDisplayData.stBMS.sBMSCurrent <= 0)
        {
            fCurrent   = abs(gDisplay.stDisplayData.stBMS.sBMSCurrent);
            sprintf(tab_display,"   BMS���� 1    \n״̬:       ���\n��ѹ:  %8.1fV\n��ѹ:  %8.1fA\n",fVoltage,fCurrent);
        }
    }  
    else if(sU8RealtimeCounter == PAGE_EIGHT)
    {
        float fSOC        = gDisplay.stDisplayData.stBMS.u8SOC;
        if(gDisplay.stDisplayData.stBMS.sBMSCurrent > 0)
        {
            float fPower   = gDisplay.stDisplayData.stBMS.sDisChargePower / 10.0;
            sprintf(tab_display,"   BMS���� 2    \n����:  %8.1fW\nSOC:   %8.1f%%\n                \n",fPower,fSOC);
        }
        else if(gDisplay.stDisplayData.stBMS.sBMSCurrent <= 0)
        {
            float fPower   = abs(gDisplay.stDisplayData.stBMS.sChargePower) / 10.0;
            sprintf(tab_display,"   BMS���� 2    \n����:  %8.1fW\nSOC:   %8.1f%%\n                \n",fPower,fSOC);
        }
//        float fOutPower   = gDisplay.stDisplayData.stBMS.sDisChargePower / 10.0;
//        float fSOC        = gDisplay.stDisplayData.stBMS.u8SOC;
//        float fSOH        = gDisplay.stDisplayData.stBMS.u8SOH;
           
//        sprintf(tab_display,"      BMS Data 2     \nOut-Power:%-8.1f   \nSOC:%-8.1f         \nSOH:%-8.1f         \n",fOutPower,fSOC,fSOH);  //Out-P �ŵ繦�� 
    } 
    else if(sU8RealtimeCounter == PAGE_NINE)
    {
        float fCurrent   = gDisplay.stDisplayData.stGenData.sGencurrent / 10.0;
        float fVoltage   = gDisplay.stDisplayData.stGenData.u16GenVoltage / 10.0;
        float fFrequency = gDisplay.stDisplayData.stGenData.u16GenFrequency / 100.00;
        
        sprintf(tab_display,"  ��������� 1  \n��ѹ:  %8.1fV\n����:  %8.1fA\nƵ��: %8.2fHz\n",fVoltage,fCurrent,fFrequency);
    }
    else if(sU8RealtimeCounter == PAGE_TEN)
    {
        float fActivePower   = gDisplay.stDisplayData.stGenData.sGenPower / 10.0;
        
        sprintf(tab_display,"  ��������� 2  \n�й�:  %8.1fW\n                     \n                     \n",fActivePower);  
    }  
/*    if(sU8RealtimeCounter == PAGE_SEVEN)
    {
        float fOutPower   = gDisplay.stDisplayData.stBMS.sDisChargePower / 10.0;
        float fSOC        = gDisplay.stDisplayData.stBMS.u8SOC;
        float fSOH        = gDisplay.stDisplayData.stBMS.u8SOH;
           
        sprintf(tab_display,"      BMS Data 2     \nOut-Power:%-8.1f   \nSOC:%-8.1f         \nSOH:%-8.1f         \n",fOutPower,fSOC,fSOH);  //Out-P �ŵ繦�� 
    } 
    if(sU8RealtimeCounter == PAGE_EIGHT)
    {
        //
        char tab_BMS_Type[6] = {""};
        
        if(gDisplay.stDisplayData.stBMS.u8BMSType == BMS_TYPE_PB_AC)
        {
           sprintf(tab_BMS_Type,"%s","PB-AC"); 
        }
        else if(gDisplay.stDisplayData.stBMS.u8BMSType == BMS_TYPE_Ni_MH)
        {
            sprintf(tab_BMS_Type,"%s","NI-MH");
        }
        else if(gDisplay.stDisplayData.stBMS.u8BMSType == BMS_TYPE_LFP)
        {
            sprintf(tab_BMS_Type,"%s","LFP  ");
        }
        else if(gDisplay.stDisplayData.stBMS.u8BMSType == BMS_TYPE_MA_LI)
        {
            sprintf(tab_BMS_Type,"%s","MA-LI");
        }
        else if(gDisplay.stDisplayData.stBMS.u8BMSType == BMS_TYPE_LCO)
        {
            sprintf(tab_BMS_Type,"%s","LCO  ");
        }
        else if(gDisplay.stDisplayData.stBMS.u8BMSType == BMS_TYPE_NMP)
        {
            sprintf(tab_BMS_Type,"%s","NMP  ");
        }
        else if(gDisplay.stDisplayData.stBMS.u8BMSType == BMS_TYPE_LI_PO)
        {
            sprintf(tab_BMS_Type,"%s","LI-PO");
        }
        else if(gDisplay.stDisplayData.stBMS.u8BMSType == BMS_TYPE_LTO)
        {
            sprintf(tab_BMS_Type,"%s","LTO  ");
        }
             
        float fCapacity   = gDisplay.stDisplayData.stBMS.u16BMSCapacity / 10.0;
        float fOverVoltage   = gDisplay.stDisplayData.stBMS.u16OverValtagevalue / 10.0;
        
        sprintf(tab_display,"      BMS Data 3     \nType:%s           \nCapacity:%-8.1f    \nOver-Voltage:%-8.3f\n",tab_BMS_Type,fCapacity,fOverVoltage);  
    } 
    if(sU8RealtimeCounter == PAGE_NINE)
    {
        //
        float fDOD     = gDisplay.stDisplayData.stBMS.u8DOD / 10.0;               //�����Ż�����
        float fCurrent = gDisplay.stDisplayData.stBMS.sMaxChargeCurrent / 10.0;   //�����Ż�����
        float fVoltage = gDisplay.stDisplayData.stBMS.u16MaxChargeVoltage / 10.0; //�����Ż�����
           
        sprintf(tab_display,"      BMS Data 4     \nDOD:%-8.1f         \nCurrent-In-Max:%-6.1f\nVoltage-In-Max:%-6.1f\n",fDOD,fCurrent,fVoltage);  
    }  
    if(sU8RealtimeCounter == PAGE_TEN)
    {
        //
        float fUnderValtage = gDisplay.stDisplayData.stBMS.u16UnderValtagevalue / 10.0; //�����Ż�����
        float fCurrent = gDisplay.stDisplayData.stBMS.sMaxDisChargeCurrent / 10.0;      //�����Ż�����
        float fVoltage = gDisplay.stDisplayData.stBMS.u16MaxDisChargeVoltage / 10.0;    //�����Ż�����
           
        sprintf(tab_display,"      BMS Data 5     \nUnder-Voltage:%-7.1f\nCurrent-Out-Max:%-5.1f\nVoltage-Out-Max:%-5.1f\n",fUnderValtage,fCurrent,fVoltage);  
    }    
*/    
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}
#if 0
void updateDisplayRealtimeData_Chinese(uint8_t sU8RealtimeCounter)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);   
    if(sU8RealtimeCounter == PAGE_ONE)
    {
        float fCurrent   = gDisplay.stDisplayData.stGridData.sGridcurrent / 10.0;            //�����Ż�����
        float fVoltage   = gDisplay.stDisplayData.stGridData.u16GridVoltage / 10.0;          //�����Ż�����
        float fFrequency = gDisplay.stDisplayData.stGridData.u16GridFrequency / 100.00;      //�����Ż�����
        sprintf(tab_display,"   �������� 1   \n��ѹ:%-8.1f   \n����:%-8.1f   \nƵ��:%-8.2f    \n",fVoltage,fCurrent,fFrequency);
    }
    else if(sU8RealtimeCounter == PAGE_TWO)
    {
        float fReactivePower   = gDisplay.stDisplayData.stGridData.sGridReactivePower / 10.0;          //�����Ż�����
        float fGridActivePower = gDisplay.stDisplayData.stGridData.sGridActivePower / 10.0;            //�����Ż�����
           
        sprintf(tab_display,"   �������� 2   \n�й�:%-8.1f   \n�޹�:%-6.1f     \n                \n",fGridActivePower,fReactivePower);  
    }    
    if(sU8RealtimeCounter == PAGE_THREE)
    {
        float fVoltage   = gDisplay.stDisplayData.stPV.stPV1.u16PVVoltage / 10.0;  //�����Ż�����
        float fCurrent   = gDisplay.stDisplayData.stPV.stPV1.sPVCurrent / 10.0;    //�����Ż�����
        float fPower     = gDisplay.stDisplayData.stPV.stPV1.sPVPower / 10.0;      //�����Ż�����
           
        sprintf(tab_display,"    PV1���� 1   \n��ѹ:%-8.1f   \n����:%-8.1f   \n����:%-8.3f   \n",fVoltage,fCurrent,fPower);  
    }
    if(sU8RealtimeCounter == PAGE_FOUR)
    {
        float fVoltage   = gDisplay.stDisplayData.stPV.stPV2.u16PVVoltage / 10.0;  //�����Ż�����
        float fCurrent   = gDisplay.stDisplayData.stPV.stPV2.sPVCurrent / 10.0;    //�����Ż�����
        float fPower     = gDisplay.stDisplayData.stPV.stPV2.sPVPower / 10.0;      //�����Ż�����
           
        sprintf(tab_display,"    PV1���� 2   \n��ѹ:%-8.1f   \n����:%-8.1f   \n����:%-8.3f   \n",fVoltage,fCurrent,fPower);  
    } 
    if(sU8RealtimeCounter == PAGE_FIVE)
    {
        float fVoltage   = gDisplay.stDisplayData.stLoad.u16LoadVoltage / 10.0;  //�����Ż�����
        float fCurrent   = gDisplay.stDisplayData.stLoad.sLoadcurrent / 10.0;    //�����Ż�����
        float fPower     = gDisplay.stDisplayData.stLoad.sLoadPower / 10.0;      //�����Ż�����
           
        sprintf(tab_display,"   �������� 1   \n��ѹ:%-8.1f   \n����:%-8.1f   \nPWR:%-8.3f\n",fVoltage,fCurrent,fPower);  
    } 
    if(sU8RealtimeCounter == PAGE_SIX)
    {
        //
        float fVoltage   = gDisplay.stDisplayData.stBMS.u16BMSVoltage / 10.0;    //�����Ż�����
        float fCurrent   = gDisplay.stDisplayData.stBMS.sBMSCurrent   / 10.0;    //�����Ż�����
        float fInPower   = gDisplay.stDisplayData.stBMS.sChargePower  / 10.0;    //�����Ż�����
           
        sprintf(tab_display,"   BMS���� 1    \n��ѹ:%-8.1f   \n����:%-8.1f   \n���빦:%-8.3f \n",fVoltage,fCurrent,fInPower);  //In-P ��繦��
    }  
    if(sU8RealtimeCounter == PAGE_SEVEN)
    {
        //
        float fOutPower   = gDisplay.stDisplayData.stBMS.sDisChargePower / 10.0;     //�����Ż�����
        float fSOC        = gDisplay.stDisplayData.stBMS.u8SOC;                      //�����Ż�����
        float fSOH        = gDisplay.stDisplayData.stBMS.u8SOH;                      //�����Ż�����
           
        sprintf(tab_display,"   BMS���� 2    \n�����:%-8.1f \nSOC:%-8.1f    \nSOH:%-8.1f    \n",fOutPower,fSOC,fSOH);  //Out-P �ŵ繦�� 
    } 
    if(sU8RealtimeCounter == PAGE_EIGHT)
    {
        //
        char tab_BMS_Type[6] = {""};
        
        if(gDisplay.stDisplayData.stBMS.u8BMSType == BMS_TYPE_PB_AC)
        {
           sprintf(tab_BMS_Type,"%s","PB-AC"); 
        }
        else if(gDisplay.stDisplayData.stBMS.u8BMSType == BMS_TYPE_Ni_MH)
        {
            sprintf(tab_BMS_Type,"%s","NI-MH");
        }
        else if(gDisplay.stDisplayData.stBMS.u8BMSType == BMS_TYPE_LFP)
        {
            sprintf(tab_BMS_Type,"%s","LFP  ");
        }
        else if(gDisplay.stDisplayData.stBMS.u8BMSType == BMS_TYPE_MA_LI)
        {
            sprintf(tab_BMS_Type,"%s","MA-LI");
        }
        else if(gDisplay.stDisplayData.stBMS.u8BMSType == BMS_TYPE_LCO)
        {
            sprintf(tab_BMS_Type,"%s","LCO  ");
        }
        else if(gDisplay.stDisplayData.stBMS.u8BMSType == BMS_TYPE_NMP)
        {
            sprintf(tab_BMS_Type,"%s","NMP  ");
        }
        else if(gDisplay.stDisplayData.stBMS.u8BMSType == BMS_TYPE_LI_PO)
        {
            sprintf(tab_BMS_Type,"%s","LI-PO");
        }
        else if(gDisplay.stDisplayData.stBMS.u8BMSType == BMS_TYPE_LTO)
        {
            sprintf(tab_BMS_Type,"%s","LTO  ");
        }
             
        float fCapacity   = gDisplay.stDisplayData.stBMS.u16BMSCapacity / 10.0;  //�����Ż�����
        float fOverVoltage   = gDisplay.stDisplayData.stBMS.u16OverValtagevalue / 10.0;    //�����Ż�����
    
        sprintf(tab_display,"   BMS���� 3    \n����:%s      \n����:%-8.1f   \n��ѹֵ:%-8.3f \n",tab_BMS_Type,fCapacity,fOverVoltage);  
    } 
    if(sU8RealtimeCounter == PAGE_NINE)
    {
        //
        float fDOD     = gDisplay.stDisplayData.stBMS.u8DOD / 10.0;               //�����Ż�����
        float fCurrent = gDisplay.stDisplayData.stBMS.sMaxChargeCurrent / 10.0;   //�����Ż�����
        float fVoltage = gDisplay.stDisplayData.stBMS.u16MaxChargeVoltage / 10.0; //�����Ż�����
           
        sprintf(tab_display,"   BMS���� 4    \nDOD:%-8.1f    \n������:%-6.1f \n����ѹ:%-6.1f \n",fDOD,fCurrent,fVoltage);  
    }  
    if(sU8RealtimeCounter == PAGE_TEN)
    {
        //
        float fUnderValtage = gDisplay.stDisplayData.stBMS.u16UnderValtagevalue / 10.0; //�����Ż�����
        float fCurrent = gDisplay.stDisplayData.stBMS.sMaxDisChargeCurrent / 10.0;      //�����Ż�����
        float fVoltage = gDisplay.stDisplayData.stBMS.u16MaxDisChargeVoltage / 10.0;    //�����Ż�����
           
        sprintf(tab_display,"   BMS���� 5    \nǷѹֵ:%-7.1f  \n���ŵ���:%-5.1f\n���ŵ�ѹ:%-5.1f\n",fUnderValtage,fCurrent,fVoltage);  
    }    
    
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

#endif


/***************************************************************************
 ����:���� ʵʱ���ϸ澯��װ����
****************************************************************************/
void updateDisplayRealFaultData_Chinese(uint8_t u8CurrentPage,uint8_t u8TotalPageNumber,uint8_t u8LastItemNumber)
{   
    memset(tab_display,0,DISPLAY_CACHE_SIZE); 
    Fault_Info_Real * pStReal = Display_Get_RealFaultData();
    if((u8CurrentPage == 0)&&(u8TotalPageNumber == 0))
    {
        sprintf(tab_display,"                \n                \n   ��ʵʱ����   \n                \n");
    }
    else if(((u8CurrentPage+1) == u8TotalPageNumber)&&(u8LastItemNumber == 1))
    {
        uint16_t u16TempCode  = pStReal->stRealFault[u8CurrentPage*DISPLAY_DATA_PERPAGE_MAX_ITEM+0].u16FaultCode;
        char tab_Fault_Name[DISPLAY_DATA_NAME_CACHE_SIZE-5]; //Display��ʾ����
        memset(tab_Fault_Name,0,DISPLAY_DATA_NAME_CACHE_SIZE-5);
        getFaultNameByFaultCode_Chinese(tab_Fault_Name,u16TempCode);//���ݹ������ȡ��������
        sprintf(tab_display,"   ʵʱ���� %02d  \n%04x:%11s\n                \n                \n",u8CurrentPage+1,u16TempCode,tab_Fault_Name);
    }
    else if(((u8CurrentPage+1) == u8TotalPageNumber) &&(u8LastItemNumber == 2))
    {
        uint16_t u8TempCode1  = pStReal->stRealFault[u8CurrentPage*DISPLAY_DATA_PERPAGE_MAX_ITEM+0].u16FaultCode;
        char tab_Fault_Name1[DISPLAY_DATA_NAME_CACHE_SIZE-5]; //Display��ʾ����
        memset(tab_Fault_Name1,0,DISPLAY_DATA_NAME_CACHE_SIZE-5);
        getFaultNameByFaultCode_Chinese(tab_Fault_Name1,u8TempCode1);//���ݹ������ȡ��������

        uint16_t u8TempCode2  = pStReal->stRealFault[u8CurrentPage*DISPLAY_DATA_PERPAGE_MAX_ITEM+1].u16FaultCode;
        char tab_Fault_Name2[DISPLAY_DATA_NAME_CACHE_SIZE-5]; //Display��ʾ����
        memset(tab_Fault_Name2,0,DISPLAY_DATA_NAME_CACHE_SIZE-5);
        getFaultNameByFaultCode_Chinese(tab_Fault_Name2,u8TempCode2);//���ݹ������ȡ��������
        sprintf(tab_display,"   ʵʱ���� %02d  \n%04x:%11s\n%04x:%11s\n                \n",u8CurrentPage+1,u8TempCode1,tab_Fault_Name1,u8TempCode2,tab_Fault_Name2);
    }
    else
    {
        uint16_t u8TempCode1  = pStReal->stRealFault[u8CurrentPage*DISPLAY_DATA_PERPAGE_MAX_ITEM+0].u16FaultCode;
        char tab_Fault_Name1[DISPLAY_DATA_NAME_CACHE_SIZE-5]; //Display��ʾ����
        memset(tab_Fault_Name1,0,DISPLAY_DATA_NAME_CACHE_SIZE-5);
        getFaultNameByFaultCode_Chinese(tab_Fault_Name1,u8TempCode1);//���ݹ������ȡ��������
        
        uint16_t u8TempCode2  = pStReal->stRealFault[u8CurrentPage*DISPLAY_DATA_PERPAGE_MAX_ITEM+1].u16FaultCode;
        char tab_Fault_Name2[DISPLAY_DATA_NAME_CACHE_SIZE-5]; //Display��ʾ����
        memset(tab_Fault_Name2,0,DISPLAY_DATA_NAME_CACHE_SIZE-5);
        getFaultNameByFaultCode_Chinese(tab_Fault_Name2,u8TempCode2);//���ݹ������ȡ��������
        
        uint16_t u8TempCode3  = pStReal->stRealFault[u8CurrentPage*DISPLAY_DATA_PERPAGE_MAX_ITEM+2].u16FaultCode;
        char tab_Fault_Name3[DISPLAY_DATA_NAME_CACHE_SIZE-5]; //Display��ʾ����
        memset(tab_Fault_Name3,0,DISPLAY_DATA_NAME_CACHE_SIZE-5);
        getFaultNameByFaultCode_Chinese(tab_Fault_Name3,u8TempCode3);//���ݹ������ȡ��������
        
        sprintf(tab_display,"   ʵʱ���� %02d  \n%04x:%11s\n%04x:%11s\n%04x:%11s\n",u8CurrentPage+1,u8TempCode1,tab_Fault_Name1,u8TempCode2,tab_Fault_Name2,u8TempCode3,tab_Fault_Name3);    
    }
    pStReal = NULL;
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);
    GUI_Display(tab_display, 0, 0);
}

void getFaultNameByFaultCode_Chinese(char* Fault_Name,uint16_t u16Code)
{
    switch(u16Code)
    {
        case SYS_FAULT_BusFastOV:
            { 
                strncpy(Fault_Name,"Bs��ѹ���",10);//bus over voltage fast detection  ���߹�ѹ���ټ��
            }
            break;          
        case SYS_FAULT_BusSlowOV: 
            { 
                strncpy(Fault_Name,"Bs��ѹ����",10);//bus over voltage slow detection  ���߹�ѹ���ټ��
            } 
            break;      
        case SYS_FAULT_BusUV: 
            { 
                strncpy(Fault_Name,"����Ƿѹ  ",10);//bus under voltage.
            } 
            break;      
        case SYS_FAULT_BusSoft: 
            { 
                strncpy(Fault_Name,"��������  ",10);//Bus Soft
            } 
            break;      
        case SYS_FAULT_EmsCommErr:
            { 
                strncpy(Fault_Name,"EMS ͨ��  ",10);//EMS Communication Error.   EMS ͨ�Ŵ���
            } 
            break;      
        case SYS_FAULT_OutputShort: 
            { 
                strncpy(Fault_Name,"�����·  ",10);//Output short circuit fault.  �����·����
            } 
            break;        
        case SYS_FAULT_GFCIErrLv3:
            { 
                strncpy(Fault_Name,"GFCI й¶2",10);//GFCI leakage fault 1.
            } 
            break;      
        case SYS_FAULT_GFCIErrLv2: 
            { 
                strncpy(Fault_Name,"GFCI й¶2",10);//GFCI leakage fault 2.
            } 
            break;      
        case SYS_FAULT_GFCIErrLv1: 
            { 
                strncpy(Fault_Name,"GFCI й¶1",10);//GFCI leakage fault 3.
            } 
            break;      
        case SYS_FAULT_SWSelfLock:
            { 
                strncpy(Fault_Name,"SW ����   ",10);//Software self-locking fault.
            } 
            break;      
        case SYS_FAULT_SysOT:
            {  
                strncpy(Fault_Name,"Sys ����  ",10);//System over-temperature fault.
            } 
            break;      
        case SYS_FAULT_SysOL: 
            { 
                strncpy(Fault_Name,"Sys ����  ",10);//System overload fault.
            } 
            break;      
        case SYS_FAULT_Epo:
            { 
                strncpy(Fault_Name,"�����ϵ�  ",10);//Emergency Power Off
            } 
            break;      
        case SYS_FAULT_SlaveCpuErr:
            { 
                strncpy(Fault_Name,"��CPU���� ",10);//Slave CPU Error
            } 
            break;      
        case SYS_FAULT_IsoErr:
            { 
                strncpy(Fault_Name,"����Դ����",10);//Auxiliary power source fault.
            } 
            break;      
        case SYS_FAULT_BusBoardBrkProt:
            { 
                strncpy(Fault_Name,"ĸ�߶ϱ���",10);//Busbar disconnect protection fault.   ĸ�߶Ͽ��������ϡ�
            } 
            break;      
        case SYS_FAULT_GroundProt:
            { 
                strncpy(Fault_Name,"�ӵر���  ",10);//Ground protection fault.
            } 
            break;      
        case INV_FAULT_Grid10MinOV:
            { 
                strncpy(Fault_Name,"��������ѹ",10);//Grid overvoltage fault (10 mins).
            } 
            break;      
        case INV_FAULT_GridOVLv2: 
            { 
                strncpy(Fault_Name,"Gd��ѹ���",10);//grid over voltage fast detection.
            } 
            break;      
        case INV_FAULT_GridOVLv1:
            { 
                strncpy(Fault_Name,"Gd��ѹ����",10);//grid over voltage slow detection.
            } 
            break;      
        case INV_FAULT_GridUVLv3:
            { 
                strncpy(Fault_Name,"GdǷѹL3  ",10);//Grid undervoltage fault (level 3).
            } 
            break;      
        case INV_FAULT_GridUVLv2:
            { 
                strncpy(Fault_Name,"GdǷѹL2  ",10);//Grid undervoltage fault (level 2).
            } 
            break;      
        case INV_FAULT_GridUVLv1: 
            { 
                strncpy(Fault_Name,"GdǷѹL1  ",10);//Grid undervoltage fault (level 1).
            } 
            break;      
        case INV_FAULT_GridFastOverFreq:
            { 
                strncpy(Fault_Name,"Gd��Ƶ���",10);//Grid overfrequency fast detection.
            } 
            break;      
        case INV_FAULT_GridSlowOverFreq:
            { 
                strncpy(Fault_Name,"Gd��Ƶ����",10);//Grid overfrequency slow detection.
            } 
            break;      
        case INV_FAULT_GridFastUnderFreq:
            { 
                strncpy(Fault_Name,"GdǷƵ���",10);//Grid underfrequency fast detection.
            } 
            break;      
        case INV_FAULT_GridSlowUnderFreq:
            { 
                strncpy(Fault_Name,"GdǷƵ����",10);//Grid underfrequency slow detection.
            } 
            break;      
        case INV_FAULT_GridFastPowerDown:
            { 
                strncpy(Fault_Name,"Gd������",10);//Grid power outage fast fault.
            } 
            break;      
        case INV_FAULT_PllErr: 
            { 
                strncpy(Fault_Name,"�����쳣  ",10);
            } 
            break;      
        case INV_FAULT_SysLNReverse:
            { 
                strncpy(Fault_Name,"LN���ӹ���",10);//System LN reverse connection fault.
            } 
            break;        
        case INV_FAULT_FwFastOC1:
            { 
                strncpy(Fault_Name,"�������1 ",10);//Software overcurrent fast detection fault 1. ����������1����
            } 
            break;      
        case INV_FAULT_HwOV1:
            { 
                strncpy(Fault_Name,"Ӳ������1",10);//Hardware overcurrent  fault 1.
            } 
            break;      
        case INV_FAULT_FwSlowOC1:
            { 
                strncpy(Fault_Name,"�������1 ",10);//Software overcurrent slow detection fault 1.
            } 
            break;      
        case INV_FAULT_InvRlyErr1:
            { 
                strncpy(Fault_Name,"���relay1",10);//Inverter relay fault 1.
            } 
            break;      
        case INV_FAULT_OTP1:
            { 
                strncpy(Fault_Name,"���¹���1 ",10);//Inverter overtemperature fault 1.
            } 
            break;      
        case INV_FAULT_OVP1:
            { 
                strncpy(Fault_Name,"��ѹ����1 ",10);//Inverter Overvoltage fault 1.
            } 
            break;      
        case INV_FAULT_IgbtErr1:
            { 
                strncpy(Fault_Name,"IGBT����1 ",10);//Inverter IGBT fault 1.
            } 
            break;      
        case INV_FAULT_InductanceOT1:
            { 
                strncpy(Fault_Name,"��й���1 ",10);//Inductor overtemperature 1.
            } 
            break;      
        case INV_FAULT_VoltDcComponentErr1:
            { 
                strncpy(Fault_Name,"��ѹֱ��1 ",10);//DC voltage component fault 1.
            } 
            break;      
        case INV_FAULT_CurrDcComponentErr1:
            { 
                strncpy(Fault_Name,"����ֱ��1 ",10);//DC Current component fault 1.
            } 
            break;      
        case INV_FAULT_CT_DisConnect:
            { 
                strncpy(Fault_Name,"�������2 ",10);//Software overcurrent fast detection fault 2.
            } 
            break;      
        case INV_FAULT_Meter_DisConnect: 
            { 
                strncpy(Fault_Name,"Ӳ������2 ",10);//Hardware overcurrent  fault 2.
            } 
            break;      
        case INV_FAULT_FwSlowOC2:
            { 
                strncpy(Fault_Name,"�������2 ",10);//Software overcurrent slow detection fault 2.
            } 
            break;      
        case INV_FAULT_InvRlyErr2: 
            { 
                strncpy(Fault_Name,"���relay2",10);//Inverter relay fault 2.������̵�������2
            } 
            break;      
        case INV_FAULT_OTP2: 
            { 
                strncpy(Fault_Name,"���¹���2 ",10);//Inverter overtemperature fault 2.
            } 
            break;      
        case INV_FAULT_OVP2: 
            { 
                strncpy(Fault_Name,"��ѹ����2 ",10);//Inverter Overvoltage fault 2.
            } 
            break;      
        case INV_FAULT_IgbtErr2:
            { 
                strncpy(Fault_Name,"IGBT����2 ",10);//Inverter IGBT fault 2.
            } 
            break;      
        case INV_FAULT_InductanceOT2:
            { 
                strncpy(Fault_Name,"��й���2 ",10);//Inductor overtemperature 2.
            } 
            break;      
        case INV_FAULT_VoltDcComponentErr2:
            { 
                strncpy(Fault_Name,"��ѹֱ��2 ",10);//DC voltage component fault 2.
            } 
            break;      
        case INV_FAULT_CurrDcComponentErr2:
            { 
                strncpy(Fault_Name,"����ֱ��2 ",10);//DC Current component fault 2.
            } 
            break;      
        case INV_FAULT_ParallelCanErr:
            { 
                strncpy(Fault_Name,"����CAN   ",10);//Parallel operation CAN communication fault.
            } 
            break;      
        case INV_FAULT_ParaCurrShareErr:
            { 
                strncpy(Fault_Name,"��������  ",10);//Parallel operation current sharing fault.
            } 
            break;
        case INV_FAULT_IslandErr:
            { 
                strncpy(Fault_Name,"�µ�����  ",10);//Island fault.
            } 
            break;
        case DCDC_FAULT_MidBusOVP:
            { 
                strncpy(Fault_Name,"�м��ѹ  ",10);//Intermediate fault overvoltage protection fault.
            } 
            break;      
        case DCDC_FAULT_LLCHwOC:
            { 
                strncpy(Fault_Name,"LLC Ӳ����",10);//LLC hardware overcurrent fault.
            } 
            break;      
        case DCDC_FAULT_BuckBoostHwOC:
            { 
                strncpy(Fault_Name,"BBӲ������",10);//BuckBoost hardware overcurrent fault.
            } 
            break;      
        case DCDC_FAULT_BuckBoostSwOC:
            { 
                strncpy(Fault_Name,"BB�������",10);//BuckBoost software overcurrent fault.
            } 
            break;      
        case DCDC_FAULT_SOPChgOCP: 
            { 
                strncpy(Fault_Name,"SOP����� ",10);//SOP charging overcurrent protection fault.
            } 
            break;      
        case DCDC_FAULT_SOPDisChgOCP:
            { 
                strncpy(Fault_Name,"SOP�Ź��� ",10);//SOP discharging overcurrent protection fault.
            } 
            break;      
        case DCDC_FAULT_DCDCOverTemp:
            { 
                strncpy(Fault_Name,"DCDC����  ",10);//DCDC overtemperature protection fault.
            } 
            break;      
        case PV1_FAULT_PvUV:
            { 
                strncpy(Fault_Name,"PV1 Ƿѹ  ",10);//PV 1 undervoltage.
            } 
            break;      
        case PV1_FAULT_PvOV:
            { 
                strncpy(Fault_Name,"PV1 ��ѹ  ",10);//PV 1 overvoltage.
            } 
            break;      
        case PV1_FAULT_PVIso:
            { 
                strncpy(Fault_Name,"PV1 ISO   ",10);//PV 1 ISO fault.
            } 
            break;      
        case PV1_FAULT_SWOC:
            { 
                strncpy(Fault_Name,"PV1 �����",10);//PV 1 software overcurrent fault.
            } 
            break;      
        case PV1_FAULT_HWOC:
            { 
                strncpy(Fault_Name,"PV1 Ӳ����",10);//PV 1 hardware overcurrent fault.
            } 
            break;      
        case PV1_FAULT_LPLK:
            { 
                strncpy(Fault_Name,"1 �͹�����",10);//PV 1 Low Power Lock fault.
            } 
            break;      
        case PV2_FAULT_PvUV:
            { 
                strncpy(Fault_Name,"PV2 Ƿѹ  ",10);//PV 2 undervoltage
            } 
            break;      
        case PV2_FAULT_PvOV:
            { 
                strncpy(Fault_Name,"PV2 ��ѹ  ",10);//PV 2 overvoltage.
            } 
            break;      
        case PV2_FAULT_PVIso: 
            { 
                strncpy(Fault_Name,"PV2 ISO   ",10);//PV 2 ISO fault.
            } 
            break;      
        case PV2_FAULT_SWOC:
            { 
                strncpy(Fault_Name,"PV2 �����",10);//PV 2 software overcurrent fault.
            } 
            break;      
        case PV2_FAULT_HWOC:
            { 
                strncpy(Fault_Name,"PV2 Ӳ����",10);//PV 2 hardware overcurrent fault.
            } 
            break;      
        case PV2_FAULT_LPLK:
            { 
                strncpy(Fault_Name,"2 �͹�����",10);//PV 2 Low Power Lock fault.
            } 
            break;      
        case BMS_ALERM_SingleVoltDiff:
            { 
                strncpy(Fault_Name,"��о��ѹ  ",10);//Single-cell voltage consistency alarm.
            } 
            break;      
        case BMS_ALERM_MosfetOT:
            { 
                strncpy(Fault_Name,"MOSFET����",10);//MOSFET overtemperature alarm.
            } 
            break;      
        case BMS_ALERM_SingleUT:
            { 
                strncpy(Fault_Name,"��о����  ",10);//Single-cell under temperature alarm.
            } 
            break;      
        case BMS_ALERM_SingleOT: 
            { 
                strncpy(Fault_Name,"��о����  ",10);//Single-cell over temperature alarm.
            } 
            break;      
        case BMS_ALERM_SingleVoltUV:
            { 
                strncpy(Fault_Name,"��о��ѹ  ",10);//Single-cell under voltage alarm.
            } 
            break;        
        case BMS_ALERM_SingleVoltOV:
            { 
                strncpy(Fault_Name,"��о��ѹ  ",10);//Single-cell over voltage alarm.
            } 
            break;        
        case BMS_ALERM_TotalVoltUV:
            { 
                strncpy(Fault_Name,"ģ���ѹ  ",10);//Module total voltage under voltage alarm.
            } 
            break;      
        case BMS_ALERM_TotalVoltOV:
            { 
                strncpy(Fault_Name,"ģ���ѹ  ",10);//Module total voltage over voltage alarm.
            } 
            break;      
        case BMS_ALERM_InternalComErr:
            { 
                strncpy(Fault_Name,"�ڲ�ͨ��  ",10);//Internal communication error alarm
            } 
            break;      
        case BMS_ALERM_OCD:
            { 
                strncpy(Fault_Name,"�ŵ����  ",10);//Discharge overcurrent alarm
            } 
            break;      
        case BMS_ALERM_OCC:
            { 
                strncpy(Fault_Name,"������  ",10);//charge overcurrent alarm
            } 
            break;      
        case BMS_ALERM_SingleTempDiff:
            { 
                strncpy(Fault_Name,"��о�¶�  ",10);//Single-cell temperature consistency alarm. 
            } 
            break;      
        case BMS_FAULT_MosfetOT:
            { 
                strncpy(Fault_Name,"MOSFET����",10);//MOSFET overtemperature alarm.
            } 
            break;      
        case BMS_FAULT_SingleUT:
            { 
                strncpy(Fault_Name,"��оǷ��  ",10);//Single-cell undertemperature  fault.
            } 
            break;      
        case BMS_FAULT_SingleOT:
            { 
                strncpy(Fault_Name,"��о����  ",10);//Single-cell overtemperature  fault.
            } 
            break;      
        case BMS_FAULT_SingleUV:
            { 
                strncpy(Fault_Name,"��оǷѹ  ",10);//Single-cell undervoltage  fault.
            } 
            break;      
        case BMS_FAULT_SingleOV:
            { 
                strncpy(Fault_Name,"��о��ѹ  ",10);//Single-cell overvoltage  fault.
            } 
            break;      
        case BMS_FAULT_TotalModeUV:
            { 
                strncpy(Fault_Name,"ģ��Ƿѹ  ",10);//Module total voltage under voltage fault.
            } 
            break;        
        case BMS_FAULT_TotalModeOV:
            { 
                strncpy(Fault_Name,"ģ���ѹ  ",10);//Module total voltage over voltage fault.
            } 
            break;      
        case BMS_FAULT_SysFault:
            { 
                strncpy(Fault_Name,"ϵͳ����  ",10);//System  protection fault.
            } 
            break;      
        case BMS_FAULT_OCD:
            { 
                strncpy(Fault_Name,"�ŵ����  ",10);//Discharge overcurrent fault.
            } 
            break;      
        case BMS_FAULT_OCC:
            { 
                strncpy(Fault_Name,"������  ",10);//charge overcurrent fault.
            } 
            break;
        case EMS_FAULT_PCS:
            { 
                strncpy(Fault_Name,"PCSͨ��   ",10);//PCS Communication fault.
            } 
            break;      
        case EMS_FAULT_METER:
            { 
                strncpy(Fault_Name,"���ͨ��  ",10);//Meter Communication fault.
            } 
            break;      
        case EMS_FAULT_BMS:
            { 
                strncpy(Fault_Name,"BMSͨ��   ",10);//Bms Communication fault.
            } 
            break;      
        case EMS_FAULT_CT:
            { 
                strncpy(Fault_Name,"CTͨ��    ",10);//CT Communication fault.
            } 
            break;     
        default:
            {
                strncpy(Fault_Name,"δ����    ",10);
            }
            break;
    }
}

/***************************************************************************
 ����:���� ������¼��ʾ��װ����
****************************************************************************/
void updateDisplayOperationRecordData_Chinese(uint8_t u8CurrentPage)
{   
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    Record_Info * pStRecord = Display_Get_OperationRecordData();
    
    if(pStRecord->u8RecordIndex == 0) 
    {
        sprintf(tab_display,"                \n                \n   �޲�����¼   \n                \n");
        GUI_Display(tab_display, 0, 0);
        return;
    }
    
    uint8_t u8TempCode  = pStRecord->stRecord[u8CurrentPage].u16RecordType;
    char tab_Operate_Name[DISPLAY_DATA_NAME_CACHE_SIZE-5];  //Display��ʾ����
    memset(tab_Operate_Name,0,DISPLAY_DATA_NAME_CACHE_SIZE-5);
    getOperateNameByOperateCode_Chinese(tab_Operate_Name,u8TempCode); //���ݹ������ȡ��������
    
    char tab_Time_Operate[DISPLAY_TIME_CACHE_SIZE-5];
    memset(tab_Time_Operate,0,DISPLAY_TIME_CACHE_SIZE-5);
    uint16_t u16Year_Operate = pStRecord->stRecord[u8CurrentPage].stOperateTime.u16Year;
    uint8_t  u8Month_Operate = pStRecord->stRecord[u8CurrentPage].stOperateTime.u8Month;
    uint8_t  u8Day_Operate   = pStRecord->stRecord[u8CurrentPage].stOperateTime.u8Day;
    uint8_t  u8Hour_Operate  = pStRecord->stRecord[u8CurrentPage].stOperateTime.u8Hour;
    uint8_t  u8Min_Operate   = pStRecord->stRecord[u8CurrentPage].stOperateTime.u8Min;
    uint8_t  u8Sec_Operate   = pStRecord->stRecord[u8CurrentPage].stOperateTime.u8Sec;
    sprintf(tab_Time_Operate,"%02d%02d%02d%02d%02d%02d",u16Year_Operate,u8Month_Operate,u8Day_Operate,u8Hour_Operate,u8Min_Operate,u8Sec_Operate); 
    
    uint8_t u8TempObj  = pStRecord->stRecord[u8CurrentPage].u8RecordObj;
    char tab_OperateObj_Name[DISPLAY_DATA_NAME_CACHE_SIZE-5];  //Display��ʾ����
    memset(tab_OperateObj_Name,0,DISPLAY_DATA_NAME_CACHE_SIZE-5);
    getOperatObjeNameByOperateObjCode_Chinese(tab_OperateObj_Name,u8TempObj);
    
    sprintf(tab_display,"   ������¼ %02d  \n����:%-11s\n����:%-10s \nObj:%-11s\n",u8CurrentPage+1,tab_Operate_Name,tab_Time_Operate+5,tab_OperateObj_Name);  //O=Operate Time ����ʱ��
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 ����:���ݲ����������ȡ��������
****************************************************************************/
void getOperateNameByOperateCode_Chinese(char* Operate_Name,uint8_t u8Code)
{

    switch(u8Code)
    {
        case RECORD_SET_Language:
            { 
                strncpy(Operate_Name,"��������  ",10);
            }
            break;
        case RECORD_SET_Time:
            { 
                strncpy(Operate_Name,"ʱ������  ",10);
            }
            break;
        case RECORD_SET_Password:
            {
                strncpy(Operate_Name,"��������  ",10);
            }
            break;
        case RECORD_SET_ClearFault:
            { 
                strncpy(Operate_Name,"�������  ",10);
            }
            break;
        case RECORD_SET_ClearRecord:
            {
                strncpy(Operate_Name,"�����¼  ",10);
            }
            break;
         case RECORD_SET_Serial:
            {
                strncpy(Operate_Name,"��������  ",10);
            }
            break;
         case RECORD_SET_Factory:
            {
                strncpy(Operate_Name,"��������  ",10);
            }
            break;
         case RECORD_SET_WIFI_RESET:
            {
                strncpy(Operate_Name,"���߸�λ  ",10);
            }
            break;
         case RECORD_SET_BLT_RESET:
            {
                strncpy(Operate_Name,"������λ  ",10);
            }
            break;
         case RECORD_SET_Local_Control:
            {
                strncpy(Operate_Name,"���ؿ���  ",10);
            }
            break;
         case RECORD_SET_Remote_Control:
            {
                strncpy(Operate_Name,"Զ�̿���  ",10);
            }
            break;  
         case RECORD_SET_STRATEGY_SELFUSE:
            {
                strncpy(Operate_Name,"�Է�����  ",10);
            }
            break;
         case RECORD_SET_TPFV_TIP_PERIOD_ONE:
            {
                strncpy(Operate_Name,"���Լ�� 1",10);
            }
            break;
         case RECORD_SET_TPFV_TIP_PERIOD_TWO:
            {
                strncpy(Operate_Name,"���Լ�� 2",10);
            }
            break;
         case RECORD_SET_TPFV_TIP_PERIOD_THREE:
            {
                strncpy(Operate_Name,"���Լ�� 3",10);
            }
            break;
         case RECORD_SET_TPFV_PEAK_PERIOD_ONE:
            {
                strncpy(Operate_Name,"���Է�� 1",10);
            }
            break;
         case RECORD_SET_TPFV_PEAK_PERIOD_TWO:
            {
                strncpy(Operate_Name,"���Է�� 2",10);
            }
            break;
         case RECORD_SET_TPFV_PEAK_PERIOD_THREE:
            {
                strncpy(Operate_Name,"���Է�� 3",10);
            }
            break;
         case RECORD_SET_TPFV_FLAT_PERIOD_ONE:
            {
                strncpy(Operate_Name,"����ƽ�� 1",10);
            }
            break;
         case RECORD_SET_TPFV_FLAT_PERIOD_TWO:
            {
                strncpy(Operate_Name,"����ƽ�� 2",10);
            }
            break;
         case RECORD_SET_TPFV_FLAT_PERIOD_THREE:
            {
                strncpy(Operate_Name,"����ƽ�� 3",10);
            }
            break;
         case RECORD_SET_TPFV_VALLEY_PERIOD_ONE:
            {
                strncpy(Operate_Name,"���Թȶ� 1",10);
            }
            break;
         case RECORD_SET_TPFV_VALLEY_PERIOD_TWO:
            {
                strncpy(Operate_Name,"���Թȶ� 2",10);
            }
            break;
         case RECORD_SET_TPFV_VALLEY_PERIOD_THREE:
            {
                strncpy(Operate_Name,"���Թȶ� 3",10);
            }
            break;
         case RECORD_SET_CHARGE_ONE:
            {
                strncpy(Operate_Name,"��� 1    ",10);
            }
            break;
         case RECORD_SET_CHARGE_TWO:
            {
                strncpy(Operate_Name,"��� 2    ",10);
            }
            break;
         case RECORD_SET_CHARGE_THREE:
            {
                strncpy(Operate_Name,"��� 3    ",10);
            }
            break;
         case RECORD_SET_CHARGE_FOUR:
            {
                strncpy(Operate_Name,"��� 4    ",10);
            }
            break;
         case RECORD_SET_DISCHARGE_ONE:
            {
                strncpy(Operate_Name,"�ŵ� 1    ",10);
            }
            break;
         case RECORD_SET_DISCHARGE_TWO:
            {
                strncpy(Operate_Name,"�ŵ� 2    ",10);
            }
            break;
         case RECORD_SET_DISCHARGE_THREE:
            {
                strncpy(Operate_Name,"�ŵ� 3    ",10);
            }
            break;
         case RECORD_SET_DISCHARGE_FOUR:
            {
                strncpy(Operate_Name,"�ŵ� 4    ",10);
            }
            break;
         case RECORD_SET_STRATEGY_BACKUP:
            {
                strncpy(Operate_Name,"�������  ",10);
            }
            break;
         case RECORD_SET_STRATEGY_GEN:
            {
                strncpy(Operate_Name,"���������",10);
            }
            break;
         case RECORD_SET_SYSTEM_DETECTION:
            {
                strncpy(Operate_Name,"�������  ",10);
            }
            break;
         case RECORD_SET_PROTECT_ISLAND:
            {
                strncpy(Operate_Name,"�µ�����  ",10);
            }
            break;
         case RECORD_SET_PROTECT_GROUND:
            {
                strncpy(Operate_Name,"�ӵر���  ",10);
            }
            break;
         case RECORD_SET_PROTECT_LEAKAG:
            {
                strncpy(Operate_Name,"©�籣��  ",10);
            }
            break;
         case RECORD_SET_PROTECT_ARC:
            {
                strncpy(Operate_Name,"��������  ",10);
            }
            break;
         case RECORD_SET_PROTECT_LVRT:
            {
                strncpy(Operate_Name,"�͵�ѹ��Խ",10);
            }
            break;
         case RECORD_SET_PROTECT_HVRT:
            {
                strncpy(Operate_Name,"�ߵ�ѹ��Խ",10);
            }
            break;
         case RECORD_SET_PROTECT_LIGHT:
            {
                strncpy(Operate_Name,"���ױ���  ",10);
            }
            break;
         case RECORD_SET_PROTECT_GEN:
            {
                strncpy(Operate_Name,"���������",10);
            }
            break;
         case RECORD_SET_PROTECT_LFRT:
            {
                strncpy(Operate_Name,"��Ƶ�ʴ�Խ",10);
            }
            break;
         case RECORD_SET_PROTECT_HFRT:
            {
                strncpy(Operate_Name,"��Ƶ�ʴ�Խ",10);
            }
            break;
         case RECORD_SET_PROTECT_P_V:
            {
                strncpy(Operate_Name,"P(V)����  ",10);
            }
            break;
         case RECORD_SET_PROTECT_P_F:
            {
                strncpy(Operate_Name,"P(F)����  ",10);
            }
            break;
         case RECORD_SET_PROTECT_Q_V:
            {
                strncpy(Operate_Name,"Q(V)����  ",10);
            }
            break;
         case RECORD_SET_PROTECT_Q_P:
            {
                strncpy(Operate_Name,"Q(P)����  ",10);
            }
            break;
         case RECORD_SET_PROTECT_CPF:
            {
                strncpy(Operate_Name,"CPF����   ",10);
            }
            break;
         case RECORD_SET_PROTECT_CQ:
            {
                strncpy(Operate_Name,"CQ����ʹ��",10);
            }
            break;
         case RECORD_SET_PV_CONTROLWAY:
            {
                strncpy(Operate_Name,"�������  ",10);
            }
            break;
         case RECORD_SET_PV_SCAN:
            {
                strncpy(Operate_Name,"���IVɨ��",10);
            }
            break;
         case RECORD_SET_BATTERY_ENABLE:
            {
                strncpy(Operate_Name,"���ʹ��  ",10);
            }
            break;
         case RECORD_SET_BATTERY_WAKEUP:
            {
                strncpy(Operate_Name,"��ػ���  ",10);
            }
            break;
         case RECORD_SET_BATTERY_MANUFACT:
            {
                strncpy(Operate_Name,"��س���  ",10);
            }
            break;
         case RECORD_SET_BATTERY_TYPE:
            {
                strncpy(Operate_Name,"�������  ",10);
            }
            break;
         case RECORD_SET_SELL:
            {
                strncpy(Operate_Name,"��������  ",10);
            }
            break;
         case RECORD_SET_GRID_METER:
            {
                strncpy(Operate_Name,"�������  ",10);
            }
            break;
         case RECORD_SET_GRID_SR:
            {
                strncpy(Operate_Name,"��������  ",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_TIP:
            {
                strncpy(Operate_Name,"��ʱ���  ",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_TIP_PERIOD_ONE:
            {
                strncpy(Operate_Name,"��ۼ�ʱ 1",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_TIP_PERIOD_TWO:
            {
                strncpy(Operate_Name,"��ۼ�ʱ 2",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_TIP_PERIOD_THREE:
            {
                strncpy(Operate_Name,"��ۼ�ʱ 3",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_PEAK:
            {
                strncpy(Operate_Name,"��ʱ���  ",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_PEAK_PERIOD_ONE:
            {
                strncpy(Operate_Name,"��۷�ʱ 1",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_PEAK_PERIOD_TWO:
            {
                strncpy(Operate_Name,"��۷�ʱ 2",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_PEAK_PERIOD_THREE:
            {
                strncpy(Operate_Name,"��۷�ʱ 3",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_FLAT:
            {
                strncpy(Operate_Name,"ƽʱ���  ",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_FLAT_PERIOD_ONE:
            {
                strncpy(Operate_Name,"���ƽʱ 1",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_FLAT_PERIOD_TWO:
            {
                strncpy(Operate_Name,"���ƽʱ 2",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_FLAT_PERIOD_THREE:
            {
                strncpy(Operate_Name,"���ƽʱ 3",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_VALLEY:
            {
                strncpy(Operate_Name,"��ʱ���  ",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_VALLEY_PERIOD_ONE:
            {
                strncpy(Operate_Name,"��۹�ʱ 1",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_VALLEY_PERIOD_TWO:
            {
                strncpy(Operate_Name,"��۹�ʱ 2",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_VALLEY_PERIOD_THREE:
            {
                strncpy(Operate_Name,"��۹�ʱ 3",10);
            }
            break;
         case RECORD_SET_GRID_REACTIVEPOWERCONTROLWAY:
            {
                strncpy(Operate_Name,"�޹�����  ",10);
            }
            break;
         case RECORD_SET_GRID_REACTIVEPOWER:
            {
                strncpy(Operate_Name,"�޹�����  ",10);
            }
            break;
         case RECORD_SET_GRID_POWERFACTOR:
            {
                strncpy(Operate_Name,"��������  ",10);
            }
            break;
         case RECORD_SET_GEN:
            {
                strncpy(Operate_Name,"���������",10);
            }
            break;   
        default:
            {
                strncpy(Operate_Name,"δ����    ",10);
            }
            break;
    }
}


/***************************************************************************
 ����:���ݲ����������ȡ����������������
****************************************************************************/
void getOperatObjeNameByOperateObjCode_Chinese(char* OperateObj_Name,uint8_t u8Code)
{
    switch(u8Code) 
    {
        case OPERATE_OBJ_LOCAL_EMS:
            { 
                strncpy(OperateObj_Name,"����EMS   ",10);
            }
            break;
        case OPERATE_OBJ_REMOTE_EMS:
            { 
                strncpy(OperateObj_Name,"Զ��EMS   ",10);
            }
            break;
        case OPERATE_OBJ_UPPER_COMPUTER:
            { 
                strncpy(OperateObj_Name,"��λ��    ",10);
            }
            break;
        default:
            {
                strncpy(OperateObj_Name,"δ����    ",10);
            }
            break;
    }
}


#if 0
void updateDisplayHistoryFaultData_Chinese(uint8_t u8CurrentPage)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    Record_Info * pStRecord = Display_Get_OperationRecordData();
    
    if(pStRecord->u8RecordIndex == 0) 
    {
        sprintf(tab_display,"                \n                \n   �޲�����¼   \n                \n");
        GUI_Display(tab_display, 0, 0);
        return;
    }
    
    uint8_t u8TempCode  = pStRecord->stRecord[u8CurrentPage].u16RecordType;
    char tab_Operate_Name[DISPLAY_DATA_NAME_CACHE_SIZE-5];  //Display��ʾ����
    memset(tab_Operate_Name,0,DISPLAY_DATA_NAME_CACHE_SIZE-5);
    getOperateNameByOperateCode(tab_Operate_Name,u8TempCode); //���ݹ������ȡ��������
    
    char tab_Time_Operate[DISPLAY_TIME_CACHE_SIZE-5];
    memset(tab_Time_Operate,0,DISPLAY_TIME_CACHE_SIZE-5);
    uint16_t u16Year_Operate = pStRecord->stRecord[u8CurrentPage].stOperateTime.u16Year;
    uint8_t  u8Month_Operate = pStRecord->stRecord[u8CurrentPage].stOperateTime.u8Month;
    uint8_t  u8Day_Operate   = pStRecord->stRecord[u8CurrentPage].stOperateTime.u8Day;
    uint8_t  u8Hour_Operate  = pStRecord->stRecord[u8CurrentPage].stOperateTime.u8Hour;
    uint8_t  u8Min_Operate   = pStRecord->stRecord[u8CurrentPage].stOperateTime.u8Min;
    uint8_t  u8Sec_Operate   = pStRecord->stRecord[u8CurrentPage].stOperateTime.u8Sec;
    sprintf(tab_Time_Operate,"%4d%02d%02d%02d%02d%02d",u16Year_Operate,u8Month_Operate,u8Day_Operate,u8Hour_Operate,u8Min_Operate,u8Sec_Operate); 
    
    uint8_t u8TempObj  = pStRecord->stRecord[u8CurrentPage].u8RecordObj;
    char tab_OperateObj_Name[DISPLAY_DATA_NAME_CACHE_SIZE-5];  //Display��ʾ����
    memset(tab_OperateObj_Name,0,DISPLAY_DATA_NAME_CACHE_SIZE-5);
    getOperatObjeNameByOperateObjCode(tab_OperateObj_Name,u8TempObj);
    
    sprintf(tab_display,"   ������¼ %02d  \n����:%-11s\n����: %-10s\nObj:%-11s\n",u8CurrentPage+1,tab_Operate_Name,tab_Time_Operate+5,tab_OperateObj_Name);  //O=Operate Time ����ʱ��
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);
    GUI_Display(tab_display, 0, 0);

}
#endif
/***************************************************************************
 ����:���� ��ʷ���ϸ澯��װ����
****************************************************************************/
void updateDisplayHistoryFaultData_Chinese(uint8_t u8CurrentPage)
{
    Fault_Info_History * pStHistory = Display_Get_HistoryFaultData();
    memset(tab_display,0,DISPLAY_CACHE_SIZE);

    if(pStHistory->u8HistoryFaultIndex == 0) 
    {
        sprintf(tab_display,"                \n                \n   ����ʷ����   \n                \n");
        GUI_Display(tab_display, 0, 0);
        return;
    }

    uint16_t u16TempCode  = pStHistory->stHistoryFault[u8CurrentPage].u16FaultCode;
    char tab_Fault_Name[DISPLAY_DATA_NAME_CACHE_SIZE-5];  //Display��ʾ����
    memset(tab_Fault_Name,0,DISPLAY_DATA_NAME_CACHE_SIZE-5);
    getFaultNameByFaultCode_Chinese(tab_Fault_Name,u16TempCode); //���ݹ������ȡ��������
    
    char tab_Time_Occur[DISPLAY_TIME_CACHE_SIZE-5];
    uint16_t u16Year_Occur = pStHistory->stHistoryFault[u8CurrentPage].stOccurTime.u16Year;
    uint8_t  u8Month_Occur = pStHistory->stHistoryFault[u8CurrentPage].stOccurTime.u8Month;
    uint8_t  u8Day_Occur   = pStHistory->stHistoryFault[u8CurrentPage].stOccurTime.u8Day;
    uint8_t  u8Hour_Occur  = pStHistory->stHistoryFault[u8CurrentPage].stOccurTime.u8Hour;
    uint8_t  u8Min_Occur   = pStHistory->stHistoryFault[u8CurrentPage].stOccurTime.u8Min;
    uint8_t  u8Sec_Occur   = pStHistory->stHistoryFault[u8CurrentPage].stOccurTime.u8Sec;
    sprintf(tab_Time_Occur,"%02d%02d%02d%02d%02d%02d",u16Year_Occur,u8Month_Occur,u8Day_Occur,u8Hour_Occur,u8Min_Occur,u8Sec_Occur); 
    
    char tab_Time_Clear[DISPLAY_TIME_CACHE_SIZE-5];
    uint16_t u16Year_Clear = pStHistory->stHistoryFault[u8CurrentPage].stOccurTime.u16Year;
    uint8_t  u8Month_Clear = pStHistory->stHistoryFault[u8CurrentPage].stOccurTime.u8Month;
    uint8_t  u8Day_Clear   = pStHistory->stHistoryFault[u8CurrentPage].stOccurTime.u8Day;
    uint8_t  u8Hour_Clear  = pStHistory->stHistoryFault[u8CurrentPage].stOccurTime.u8Hour;
    uint8_t  u8Min_Clear   = pStHistory->stHistoryFault[u8CurrentPage].stOccurTime.u8Min;
    uint8_t  u8Sec_Clear   = pStHistory->stHistoryFault[u8CurrentPage].stOccurTime.u8Sec;
    sprintf(tab_Time_Clear,"%02d%02d%02d%02d%02d%02d",u16Year_Clear,u8Month_Clear,u8Day_Clear,u8Hour_Clear,u8Min_Clear,u8Sec_Clear);     
    
    sprintf(tab_display,"   ��ʷ���� %02d  \n%04x:%11s\n����:%10s \n���:%10s\n",u8CurrentPage+1,u16TempCode,tab_Fault_Name,tab_Time_Occur+5,tab_Time_Clear+5);  //O=Occur ���ϲ���ʱ��  C=clear �������ʱ��
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);
    GUI_Display(tab_display, 0, 0);
}

#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

