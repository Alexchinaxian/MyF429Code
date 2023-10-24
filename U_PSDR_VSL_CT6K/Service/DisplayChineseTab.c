/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
文件 : DisplayChineseTab.c 
 用途 : 中文显示
***********************************************************************************************************************/
#include "DisplayChineseTab.h"
#include "LCD_KS0108_6800_Device.h"
#include "Modbus_PCS_COMData.h"
#include <stdlib.h>
#include <stdio.h>




//以下为中文显示示例代码
#if LCD_CHINESE_DISP_TEST
extern char tab_display[];
extern uint8_t gu8LCDEnglishFont;
extern DisplaySystem gDisplay;                  //Display数据结构全局变量

/***********************************************************************************************************************
 功能:HOME界面中文显示
************************************************************************************************************************/

void updateDisplayHomeData_Chinese(void)
{    
    if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_INIT)
    {
        /*字符串格式不要随意修改，影响UI布局*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Init   \n故障状态:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Init   \n故障状态: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Init   \n故障状态:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     主界面     \n工作模式:Init   \n故障状态:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }
    }
    else if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_FIT)
    {
        /*字符串格式不要随意修改，影响UI布局*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Fit    \n故障状态:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Fit    \n故障状态: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Fit    \n故障状态:Alarm   \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     主界面     \n工作模式:Fit    \n故障状态:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }  
    }
    else if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_MONITOR)
    {
        /*字符串格式不要随意修改，影响UI布局*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Monitor\n故障状态:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Monitor\n故障状态: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Monitor\n故障状态:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     主界面     \n工作模式:Monitor\n故障状态:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }  
    }
    else if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_STANDBY)
    {
        /*字符串格式不要随意修改，影响UI布局*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Standby\n故障状态:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Standby\n故障状态: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Standby\n故障状态:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     主界面     \n工作模式:Standby\n故障状态:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }  
    }
    else if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_TEST)
    {
        /*字符串格式不要随意修改，影响UI布局*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Test   \n故障状态:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Test   \n故障状态: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Test   \n故障状态:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     主界面     \n工作模式:Test   \n故障状态:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }  
    }
    else if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_PRESOFTSTART)
    {
        /*字符串格式不要随意修改，影响UI布局*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     主界面     \n工作模式:PreSof\n故障状态:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     主界面     \n工作模式:PreSof\n故障状态: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     主界面     \n工作模式:PreSof\n故障状态:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     主界面     \n工作模式:PreSof\n故障状态:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }  
    }
    else if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_SOFTSTART)
    {
        /*字符串格式不要随意修改，影响UI布局*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Softsta\n故障状态:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Softsta\n故障状态: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Softsta\n故障状态:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     主界面     \n工作模式:Softsta\n故障状态:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }  
    }
    else if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_SOFTSTARTWAIT)
    {
        /*字符串格式不要随意修改，影响UI布局*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Softsta\n故障状态:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Softsta\n故障状态: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Softsta\n故障状态:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     主界面     \n工作模式:Softsta\n故障状态:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }  
    }   
    else if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_RELAYCLOSED)
    {
        /*字符串格式不要随意修改，影响UI布局*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     主界面     \n工作模式:RelayCl\n故障状态:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     主界面     \n工作模式:RelayCl\n故障状态: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     主界面     \n工作模式:RelayCl\n故障状态:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     主界面     \n工作模式:RelayCl\n故障状态:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }  
    }
    else if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_RUN)
    {
        /*字符串格式不要随意修改，影响UI布局*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Running\n故障状态:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Running\n故障状态: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Running\n故障状态:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     主界面     \n工作模式:Running\n故障状态:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }  
    }
    else if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_FAULT)
    {
        /*字符串格式不要随意修改，影响UI布局*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Fault  \n故障状态:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Fault  \n故障状态: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Fault  \n故障状态:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     主界面     \n工作模式:Fault  \n故障状态:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }  
    }  
    else if(gDisplay.stDisplayHome.u8WorkSate == WORKSTATE_UPGRADE)
    {
        /*字符串格式不要随意修改，影响UI布局*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Upgrad\n故障状态:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Upgrad\n故障状态: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     主界面     \n工作模式:Upgrad\n故障状态:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     主界面     \n工作模式:Upgrad\n故障状态:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }  
    }
    else
    {
        /*字符串格式不要随意修改，影响UI布局*/
        if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_NORMAL)
        {
            sprintf(tab_display,"     主界面     \n工作模式:       \n故障状态:Normal \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_FAULT)
        {
            sprintf(tab_display,"     主界面     \n工作模式:       \n故障状态: Fault \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);                     
        }
        else if(gDisplay.stDisplayHome.u8FaultStatus == FAULTSTATE_ALARM)
        {
            sprintf(tab_display,"     主界面     \n工作模式:       \n故障状态:Alarm  \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);  
        }
        else
        {
            sprintf(tab_display,"     主界面     \n工作模式:       \n故障状态:       \nC:%-6.1fD:%-6.1f\n",gDisplay.stDisplayHome.f32ChagePowerGeneration,gDisplay.stDisplayHome.f32DisChagePowerGeneration);
        }   
    }
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 功能:中文LOGIN显示界面
****************************************************************************/
void updateDisplayLoginData_Chinese(char* sLoginPassword)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    sprintf(tab_display,"      登录      \n                \n密码:%s     \n                \n",sLoginPassword);
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 功能:设置SET中文界面
****************************************************************************/
void updateDisplaySetData_Chinese(uint8_t u8SetIndex)
{    
    if(u8SetIndex == SET_SYSTEM_Index)
    {
        sprintf(tab_display,"     设置       \n->系统设置      \n光伏设置        \n电池设置        \n");
        //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
        GUI_Display(tab_display, 0, 0);
    }
    else if(u8SetIndex == SET_PV_Index)
    {
        sprintf(tab_display,"     设置       \n系统设置        \n->光伏设置      \n电池设置        \n");
        //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
        GUI_Display(tab_display, 0, 0);
    }
    else if(u8SetIndex == SET_BATTERY_Index)
    {
        sprintf(tab_display,"     设置       \n系统设置        \n光伏设置        \n->电池设置      \n");
        //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
        GUI_Display(tab_display, 0, 0);
    }
    else if(u8SetIndex == SET_GRID_Index)
    {
        sprintf(tab_display,"     设置       \n->电网设置      \n发电机设置      \n                \n");
        //sprintf(tab_display,"     设置       \n->并网设置      \n发电机设置      \n升级设置        \n");
        //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
        GUI_Display(tab_display, 0, 0);
    }
    else if(u8SetIndex == SET_GEN_Index)
    {
        sprintf(tab_display,"     设置       \n电网设置        \n->发电机设置    \n                \n");
        //sprintf(tab_display,"     设置       \n并网设置        \n->发电机设置    \n升级设置        \n");
        //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
        GUI_Display(tab_display, 0, 0);
    }
    //else if(u8SetIndex == SET_UPGRADE_Index)
    //{
        //sprintf(tab_display,"     设置       \n并网设置        \n发电机设置      \n->升级设置      \n");
        //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
        //GUI_Display(tab_display, 0, 0);
    //}
    else
    {
                    
    }
}

/***************************************************************************
 功能:设置SET系统中文界面
****************************************************************************/
void updateDisplaySystemSetData_Chinese(uint8_t u8SetIndex)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    
    if(u8SetIndex == SET_SYSTEM_LANGUAGE_Index)
    {
        sprintf(tab_display,"    系统设置    \n->语言设置      \n时间设置        \n密码设置        \n");
    }
    else if(u8SetIndex == SET_SYSTEM_TIME_Index)
    {
        sprintf(tab_display,"    系统设置    \n语言设置        \n->时间设置      \n密码设置        \n");
    }
    else if(u8SetIndex == SET_SYSTEM_PASSWORD_Index)
    {
        sprintf(tab_display,"    系统设置    \n语言设置        \n时间设置        \n->密码设置      \n");
    }
    else if(u8SetIndex == SET_SYSTEM_CLEARFAULT_Index)
    {
        sprintf(tab_display,"    系统设置    \n->清除故障设置  \n清除记录设置    \n串口设置        \n");
    }
    else if(u8SetIndex == SET_SYSTEM_CLEARRECORD_Index)
    {
        sprintf(tab_display,"    系统设置    \n清除故障设置    \n->清除记录设置  \n串口设置        \n");
    }
//    else if(u8SetIndex == SET_SYSTEM_SERIAL_Index)
//    {
//        sprintf(tab_display,"    系统设置    \n清除故障设置    \n清除记录设置    \n->串口设置      \n");
//    }
    else if(u8SetIndex == SET_SYSTEM_FACTORY_Index)
    {
        sprintf(tab_display,"    系统设置    \n->出厂设置      \n复位设置        \n远程设置        \n");
    }
    else if(u8SetIndex == SET_SYSTEM_RESET_Index)
    {
        sprintf(tab_display,"    系统设置    \n出厂设置        \n->复位设置      \n远程设置        \n");
    }
    else if(u8SetIndex == SET_SYSTEM_REMOTECONTROL_Index)
    {
        sprintf(tab_display,"    系统设置    \n出厂设置        \n复位设置        \n->远程设置      \n");
    }   
    else if(u8SetIndex == SET_SYSTEM_STRATEGY_Index)
    {
        //sprintf(tab_display,"    系统设置    \n->策略设置      \n变压器设置      \n检测设置        \n");
        sprintf(tab_display,"    系统设置    \n->策略设置      \n检测设置        \n保护设置        \n");  
    }
    //else if(u8SetIndex == SET_SYSTEM_CT_Index)
    //{
    //    sprintf(tab_display,"    系统设置    \n策略设置        \n->变压器设置    \n检测设置        \n");
    //}
    else if(u8SetIndex == SET_SYSTEM_DETECTION_Index)
    {
        sprintf(tab_display,"    系统设置    \n策略设置        \n->检测设置      \n保护设置        \n");
        //sprintf(tab_display,"    系统设置    \n策略设置        \n变压器设置      \n->检测设置      \n");
    }
    else if(u8SetIndex == SET_SYSTEM_PROTECT_Index)
    {
        sprintf(tab_display,"    系统设置    \n策略设置        \n检测设置        \n->保护设置      \n");
        //sprintf(tab_display,"    系统设置    \n->保护设置      \n                \n                \n");
    }

    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}


/***************************************************************************
 功能:语言设置SET中文界面
****************************************************************************/
void updateDisplaySystemLanguageSetData_Chinese(Language_TypeDef u8SetIndex)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);  
    if(u8SetIndex ==  LANGUAGE_ENGLISH)
    {
        sprintf(tab_display,"    语言设置    \n->英语          \n汉语            \n西班牙语        \n"); 
    }
    else if(u8SetIndex == LANGUAGE_CHINESE)
    {
        sprintf(tab_display,"    语言设置    \n英语            \n->汉语          \n西班牙语        \n");
    }
    else if(u8SetIndex == LANGUAGE_SPANISH)
    {
        sprintf(tab_display,"    语言设置    \n英语            \n汉语            \n->西班牙语      \n");
    }
    else if(u8SetIndex == LANGUAGE_GERMAN)
    {
        sprintf(tab_display,"    语言设置    \n->德语          \n法语            \n波兰语          \n");
    }
    else if(u8SetIndex == LANGUAGE_FRENCH)
    { 
        sprintf(tab_display,"    语言设置    \n德语            \n->法语          \n波兰语          \n");
    }
    else if(u8SetIndex == LANGUAGE_POLISH)
    {
        sprintf(tab_display,"    语言设置    \n德语            \n法语            \n->波兰语        \n");
    }
    else if(u8SetIndex == LANGUAGE_ITALIAN)
    {
        sprintf(tab_display,"    语言设置    \n->意大利语      \n捷克语          \n荷兰语          \n");
    }
    else if(u8SetIndex == LANGUAGE_CZECH)
    {
        sprintf(tab_display,"    语言设置    \n意大利语        \n->捷克语        \n荷兰语          \n");
    }
    else if(u8SetIndex == LANGUAGE_DUTCH)
    {
        sprintf(tab_display,"    语言设置    \n意大利语        \n捷克语          \n->荷兰语        \n");
    }
    
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);     
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 功能:时间设置SET中文界面
****************************************************************************/
void updateDisplaySystemTimeSetData_Chinese(char* sDate,char* sTime,Week_TypeDef eWeek)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    
    char tab_week[10]; 
    memset(tab_week,0,10);
    
    if(eWeek == WEEK_MONDAY)
    {
        strcpy(tab_week, "星期一");
    }
    else if(eWeek == WEEK_TUESDAY)
    {
       strcpy(tab_week, "星期二");
    }
    else if(eWeek == WEEK_WEDNESDAY)
    {
       strcpy(tab_week, "星期三");
    }
    else if(eWeek == WEEK_THURSDAY)
    {
       strcpy(tab_week, "星期四");
    }
    else if(eWeek == WEEK_FRIDAY)
    {
       strcpy(tab_week, "星期五");
    }
    else if(eWeek == WEEK_SATURDAY)
    {
       strcpy(tab_week, "星期六");
    }
    else if(eWeek == WEEK_SUNDAY)
    {
       strcpy(tab_week, "星期天");
    }
     
    sprintf(tab_display,"    时间设置    \n日期:%s \n时间:%s   \n周:%s \n",sDate,sTime,tab_week);
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 功能:中文 设置系统Password界面
****************************************************************************/
void updateDisplaySystemPasswordSetData_Chinese(char* sOldPassword,char* sNewPassword,char* sConfirmPassword)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    sprintf(tab_display,"    密码设置    \n原密码:%s   \n新密码:%s   \n确认:%s     \n",sOldPassword,sNewPassword,sConfirmPassword);
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);
    GUI_Display(tab_display, 0, 0);
}


/***************************************************************************
 功能:中文 显示登陆密码校验错误信息
****************************************************************************/
void updateDisplayTipLoginError_Chinese(void)
{
    sprintf(tab_display,"      提示      \n  密码验证错误  \n     请重试.    \n                \n");
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 功能:中文 密码修改密码设置位数不够6位提示界面信息
****************************************************************************/
void updateDisplayTipPasswordShort_Chinese(void)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    sprintf(tab_display,"      提示      \n  输入六位密码, \n     请重试.    \n                \n");
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0);
}



/***************************************************************************
 功能:中文 密码修改旧的密码输入错误提示界面信息
****************************************************************************/
void updateDisplayTipOldPasswordError_Chinese(void)
{
    sprintf(tab_display,"      提示      \n 旧密码输入错误,\n     请重试.    \n                \n");
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 功能:中文 密码修改两次输入的新密码不一致提示界面信息
****************************************************************************/
void updateDisplayTipOldPasswordNotMatch_Chinese(void)
{
    sprintf(tab_display,"      提示      \n 新旧密码不匹配,\n     请重试.    \n                \n");
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
功能:中文 密码修改输入的新密码和历史密码重合提示界面信息
****************************************************************************/
void updateDisplayTipOldPasswordOverlaps_Chinese(void)
{
    sprintf(tab_display,"      提示      \n  新旧密码重复, \n     请重试.    \n                \n");
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 功能:设置系统通信复位设置中文界面信息
****************************************************************************/
void updateDisplaySystemCommResetData_Chinese(Baud_TypeDef u8SetIndex)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);    
    if(u8SetIndex == RESET_BLT_Index)
    {
        sprintf(tab_display,"    复位设置    \n->蓝牙复位      \n无线复位        \n                \n");                                                                               
    }
    else if(u8SetIndex == RESET_WIFI_Index)
    {
        sprintf(tab_display,"    复位设置    \n蓝牙复位        \n->无线复位      \n                \n");                                                                                  
    }

    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}


/***************************************************************************
 功能:设置系统串口设置中文界面信息
****************************************************************************/
void updateDisplaySystemSerialSetData_Chinese(bool_t bEnableFlag,char*strAddress,char*strBaud, SERIALUSE_TypeDef enumSerialUse)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);    
    if(enumSerialUse == SERIAL_USE_PCS)
    {
        if(bEnableFlag == STATUS_FALSE)
        {
            sprintf(tab_display,"  PCS 串口设置  \n使能:禁止       \n地址:%s        \n波特:%s    \n",strAddress,strBaud);
        }
        else
        {
            sprintf(tab_display,"  PCS 串口设置  \n使能:使能       \n地址:%s        \n波特:%s    \n",strAddress,strBaud);
        }        
    }
    else if(enumSerialUse == SERIAL_USE_Meter)
    {
        if(bEnableFlag == STATUS_FALSE)
        {
            sprintf(tab_display,"    电表设置    \n使能:禁止       \n地址:%s        \n波特:%s    \n",strAddress,strBaud);
        }
        else
        {
            sprintf(tab_display,"    电表设置    \n使能:使能       \n地址:%s        \n波特:%s    \n",strAddress,strBaud);
        }
    }
    
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}


/***************************************************************************
 功能:设置系统远程控制使能设置中文界面信息
****************************************************************************/
void updateDisplaySystemRemoteControlData_Chinese(ENABLE_TypeDef u8SetIndex)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    if(u8SetIndex == ENABLE_NO)
    {
        sprintf(tab_display,"    远程设置    \n->本地控制      \n远端控制        \n                \n");                                                                               
    }
    else if(u8SetIndex == ENABLE_YES)
    {
        sprintf(tab_display,"    远程设置    \n本地控制        \n->远端控制      \n                \n");                                                                                  
    }

    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}



/***************************************************************************
 功能:策略设置中文界面信息
****************************************************************************/
void updateDisplaySystemStrategySetData_Chinese(STRATEGY_TypeDef u8StrategyIndex)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    if(u8StrategyIndex == STRATEGY_NULL)
    {
        sprintf(tab_display,"    策略设置    \n->空            \n自发自用        \n尖峰平谷        \n");                                                                                  
    }
    else if(u8StrategyIndex == STRATEGY_SELF)
    {
        sprintf(tab_display,"    策略设置    \n空              \n->自发自用      \n尖峰平谷        \n");                                                                                  
    }
    else if(u8StrategyIndex == STRATEGY_TPFV)
    {
        sprintf(tab_display,"    策略设置    \n空              \n自发自用        \n->尖峰平谷      \n");                                                                               
    }
    else if(u8StrategyIndex == STRATEGY_REGULAR)
    {
        sprintf(tab_display,"    策略设置    \n->定时充放电    \n备电            \n发电机          \n");                                                                                  
    }
    else if(u8StrategyIndex == STRATEGY_BACKUP)
    {
        sprintf(tab_display,"    策略设置    \n定时充放电      \n->备电          \n发电机          \n");                                                                                  
    }
    else if(u8StrategyIndex == STRATEGY_GEN)
    {
        sprintf(tab_display,"    策略设置    \n定时充放电      \n备电            \n->发电机        \n");                                                                                  
    }

    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 功能:中文 系统SELF策略设置界面信息
****************************************************************************/
void updateDisplaySystemSelfStrategySetData_Chinese()
{  
    memset(tab_display,0,DISPLAY_CACHE_SIZE);  
    sprintf(tab_display,"    自发自用    \n                \n                \n                \n");                                                                                                                                                              
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0);
}
/***************************************************************************
 功能:中文  系统备电策略设置界面信息
****************************************************************************/
void updateDisplaySystemBackupStrategySetData_Chinese(char* strPower)
{  
    memset(tab_display,0,DISPLAY_CACHE_SIZE);  
    sprintf(tab_display,"    备电策略    \n                \n功率:%s \n                \n",strPower);                                                                                                                                
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0); 
}
/***************************************************************************
 功能:中文  系统发电机策略设置界面信息
****************************************************************************/
void updateDisplaySystemGenStrategySetData_Chinese(char* strForbidSOC,char* strSupplySOC)
{  
    memset(tab_display,0,DISPLAY_CACHE_SIZE);  
    //sprintf(tab_display,"   发电机策略   \n禁止SOC:%s        \n补电SOC:%s    \n                \n",strForbidSOC,strSupplySOC);
    sprintf(tab_display,"   发电机策略   \n禁止SOC:%s     \n补电SOC:%s     \n                \n",strForbidSOC,strSupplySOC);                                                                                                                                                              
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0);
    
}
/***************************************************************************
 功能:系统策略TPFV 中文界面信息
****************************************************************************/
void updateDisplaySystemTPFVStrategyAbstractSetData_Chinese(TPFV_TypeDef u8TPFVStrategyIndex)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
        /*
    if(u8TPFVStrategyIndex == TPFV_TIP)
    {
        sprintf(tab_display,"  尖峰平谷策略  \n->尖段          \n峰段            \n平段            \n"); 
    }
    else if(u8TPFVStrategyIndex == TPFV_PEAK)
    {
        sprintf(tab_display,"  尖峰平谷策略  \n尖段            \n->峰段          \n平段            \n");   
    }
    else if(u8TPFVStrategyIndex == TPFV_FLAT)
    {
        sprintf(tab_display,"  尖峰平谷策略  \n尖段            \n峰段            \n->平段          \n");  
    }
    else if(u8TPFVStrategyIndex == TPFV_VALLEY)
    {
        sprintf(tab_display,"  尖峰平谷策略  \n->谷段          \n                \n                \n");  
    } 
        */
    if(u8TPFVStrategyIndex == TPFV_PEAK)
    {
        sprintf(tab_display,"  尖峰平谷策略  \n->峰段          \n平段            \n谷段          \n");
    }
    else if(u8TPFVStrategyIndex == TPFV_FLAT)
    {
        sprintf(tab_display,"  尖峰平谷策略  \n峰段            \n->平段          \n谷段          \n");
    }
    else if(u8TPFVStrategyIndex == TPFV_VALLEY)
    {
        sprintf(tab_display,"  尖峰平谷策略  \n峰段            \n平段            \n->谷段          \n");
    }                 
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 功能:电网尖峰平谷分时设置 中文界面信息
****************************************************************************/

void updateDisplaySystemTPFVStrategySetData_Chinese(uint8_t sU8TPFVSetCounter,TPFV_TypeDef enum_tpfv)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    
    if(enum_tpfv == TPFV_TIP)
    {
        if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_ONE)
        {
            sprintf(tab_display,"      尖段      \n->时段 1        \n时段 2          \n时段 3          \n");
        }
        else if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_TWO)
        {
            sprintf(tab_display,"      尖段      \n时段 1          \n->时段 2        \n时段 3          \n");
        }
        else if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_THREE)
        {
            sprintf(tab_display,"      尖段      \n时段 1          \n时段 2          \n->时段 3        \n");
        }      
    }
    else if(enum_tpfv == TPFV_PEAK)
    {
        if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_ONE)
        {
            sprintf(tab_display,"      峰段      \n->时段 1        \n时段 2          \n时段 3          \n");
        }
        else if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_TWO)
        {
            sprintf(tab_display,"      峰段      \n时段 1          \n->时段 2        \n时段 3          \n");
        }
        else if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_THREE)
        {
            sprintf(tab_display,"      峰段      \n时段 1          \n时段 2          \n->时段 3        \n");
        }  
    }
    else if(enum_tpfv == TPFV_FLAT)
    {
        if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_ONE)
        {
            sprintf(tab_display,"      平段      \n->时段 1        \n时段 2          \n时段 3          \n");
        }
        else if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_TWO)
        {
            sprintf(tab_display,"      平段      \n时段 1          \n->时段 2        \n时段 3          \n");
        }
        else if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_THREE)
        {
            sprintf(tab_display,"      平段      \n时段 1          \n时段 2          \n->时段 3        \n");
        } 
    }
    else if(enum_tpfv == TPFV_VALLEY)
    {
        if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_ONE)
        {
            sprintf(tab_display,"      谷段      \n->时段 1        \n时段 2          \n时段 3          \n");
        }
        else if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_TWO)
        {
            sprintf(tab_display,"      谷段      \n时段 1          \n->时段 2        \n时段 3          \n");
        }
        else if(sU8TPFVSetCounter == STRATEGY_TPFV_PERIOD_THREE)
        {
            sprintf(tab_display,"      谷段      \n时段 1          \n时段 2          \n->时段 3        \n");
        }
    }  
                         
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 功能:中文 系统TPFV策略时间段设置界面信息
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
                        
            sprintf((char*)tab_display,"     尖段 1     \nSOC:%sPWR:%s\n开始:%s   \n结束:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);
                        
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
                        
            sprintf((char*)tab_display,"     尖段 2     \nSOC:%sPWR:%s\n开始:%s   \n结束:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);            
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
                        
            sprintf((char*)tab_display,"     尖段 3     \nSOC:%sPWR:%s\n开始:%s   \n结束:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);
            
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
             
            sprintf((char*)tab_display,"     峰段 1     \nSOC:%sPWR:%s\n开始:%s   \n结束:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);            
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
                        
            sprintf((char*)tab_display,"     峰段 2     \nSOC:%sPWR:%s\n开始:%s   \n结束:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);            
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
                        
            sprintf((char*)tab_display,"     峰段 3     \nSOC:%sPWR:%s\n开始:%s   \n结束:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);
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
            
            sprintf((char*)tab_display,"     平段 1     \nSOC:%sPWR:%s\n开始:%s   \n结束:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);
                        
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
                        
            sprintf((char*)tab_display,"     平段 2     \nSOC:%sPWR:%s\n开始:%s   \n结束:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);            
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
                        
            sprintf((char*)tab_display,"     平段 3     \nSOC:%sPWR:%s\n开始:%s   \n结束:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);
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
            
            sprintf((char*)tab_display,"     谷段 1     \nSOC:%sPWR:%s\n开始:%s   \n结束:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);
                        
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
                        
            sprintf((char*)tab_display,"     谷段 2     \nSOC:%sPWR:%s\n开始:%s   \n结束:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);            
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
                        
            sprintf((char*)tab_display,"     谷段 3     \nSOC:%sPWR:%s\n开始:%s   \n结束:%s   \n",strStopSOC,strPower,tab_StartTime_Temp,tab_EndTime_Temp);
        }  
    }  
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
功能:定时充放电设置中文界面信息
****************************************************************************/
void updateDisplaySystemRegularStrategyAbstractSetData_Chinese(REGULAR_TypeDef u8RegularStrategyIndex)   
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    
    if(u8RegularStrategyIndex == REGULAR_CHARGE)
    {
        sprintf(tab_display,"    定时策略    \n->充电          \n放电            \n                \n"); 
    }
    else if(u8RegularStrategyIndex == REGULAR_DISCHARGE)
    {
        sprintf(tab_display,"    定时策略    \n充电            \n->放电          \n                \n");   
    }
                     
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
功能:定时充放电设置中文界面信息
****************************************************************************/
void updateDisplaySystemRegularStrategySetData_Chinese(REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef u8RegularStrategyIndex)   
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);   
    if(enum_RegularClass == REGULAR_CHARGE)
    {
        if(u8RegularStrategyIndex == STRATEGY_REGULAR_PERIOD_ONE)
        {
            sprintf(tab_display,"      充电      \n->时段1         \n时段2           \n时段3           \n"); 
        }
        else if(u8RegularStrategyIndex == STRATEGY_REGULAR_PERIOD_TWO)
        {
            sprintf(tab_display,"      充电      \n时段1           \n->时段2         \n时段3           \n");    
        }
        else if(u8RegularStrategyIndex == STRATEGY_REGULAR_PERIOD_THREE)
        {
            sprintf(tab_display,"      充电      \n时段1           \n时段2           \n->时段3         \n");   
        } 
        else if(u8RegularStrategyIndex == STRATEGY_REGULAR_PERIOD_FOUR)
        {
            sprintf(tab_display,"      充电      \n->时段4         \n                \n                \n");   
        }         
    }
    else if(enum_RegularClass == REGULAR_DISCHARGE)
    {
        if(u8RegularStrategyIndex == STRATEGY_REGULAR_PERIOD_ONE)
        {
            sprintf(tab_display,"      放电      \n->时段1         \n时段2           \n时段3           \n"); 
        }
        else if(u8RegularStrategyIndex == STRATEGY_REGULAR_PERIOD_TWO)
        {
            sprintf(tab_display,"      放电      \n时段1           \n->时段2         \n时段3           \n");    
        }
        else if(u8RegularStrategyIndex == STRATEGY_REGULAR_PERIOD_THREE)
        {
            sprintf(tab_display,"      放电      \n时段1           \n时段2           \n->时段3         \n");   
        } 
        else if(u8RegularStrategyIndex == STRATEGY_REGULAR_PERIOD_FOUR)
        {
            sprintf(tab_display,"      放电      \n->时段4         \n                \n                \n");    
        }          
    }
                       
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 功能:中文 系统定时充放电时间段设置界面信息
****************************************************************************/
void updateDisplaySystemRegularStrategyPeriodSetData_Chinese(char* strStopSOC,char* strPower, char* strStartTime, char* strEndTime,REGULAR_TypeDef enum_RegularClass,REGULAR_Strategy_TypeDef enum_Period)
{ 
    memset(tab_display,0,DISPLAY_CACHE_SIZE); 
    if(enum_RegularClass == REGULAR_CHARGE)
    {
        if(enum_Period == STRATEGY_REGULAR_PERIOD_ONE)
        {                  
            sprintf(tab_display,"    充电时段1   \n功率:%sSOC:%s\n开始:%s   \n结束:%s   \n",strPower,strStopSOC,strStartTime,strEndTime);               
        }
        else if(enum_Period == STRATEGY_REGULAR_PERIOD_TWO)
        { 
            sprintf(tab_display,"    充电时段2   \n功率:%sSOC:%s\n开始:%s   \n结束:%s   \n",strPower,strStopSOC,strStartTime,strEndTime);          
        }
        else if(enum_Period == STRATEGY_REGULAR_PERIOD_THREE)
        {  
            sprintf(tab_display,"    充电时段3   \n功率:%sSOC:%s\n开始:%s   \n结束:%s   \n",strPower,strStopSOC,strStartTime,strEndTime);
        } 
        else if(enum_Period == STRATEGY_REGULAR_PERIOD_FOUR)
        {  
            sprintf(tab_display,"    充电时段4   \n功率:%sSOC:%s\n开始:%s   \n结束:%s   \n",strPower,strStopSOC,strStartTime,strEndTime);
        }         
    }
    else if(enum_RegularClass == REGULAR_DISCHARGE)
    {
        if(enum_Period == STRATEGY_REGULAR_PERIOD_ONE)
        {                  
            sprintf(tab_display,"    放电时段1   \n功率:%sSOC:%s\n开始:%s   \n结束:%s   \n",strPower,strStopSOC,strStartTime,strEndTime);               
        }
        else if(enum_Period == STRATEGY_REGULAR_PERIOD_TWO)
        { 
            sprintf(tab_display,"    放电时段2   \n功率:%sSOC:%s\n开始:%s   \n结束:%s   \n",strPower,strStopSOC,strStartTime,strEndTime);          
        }
        else if(enum_Period == STRATEGY_REGULAR_PERIOD_THREE)
        {  
            sprintf(tab_display,"    放电时段3   \n功率:%sSOC:%s\n开始:%s   \n结束:%s   \n",strPower,strStopSOC,strStartTime,strEndTime);
        } 
        else if(enum_Period == STRATEGY_REGULAR_PERIOD_FOUR)
        {  
            sprintf(tab_display,"    放电时段4   \n功率:%sSOC:%s\n开始:%s   \n结束:%s   \n",strPower,strStopSOC,strStartTime,strEndTime);
        }       
    }
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);
    GUI_Display(tab_display, 0, 0);
}



/***************************************************************************
 功能:实时统计数据显示 中文界面信息
****************************************************************************/
void updateDisplayStatisticsData_Chinese(uint8_t sU8StatisticsCounter)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);   
    if(sU8StatisticsCounter == PAGE_ONE)
    {
        float fPvData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stPVPowerGeneration / 10.0;        //后续优化除法
        float fInputData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stInputPowerGeneration / 10.0;        //后续优化除法
        float fOutputData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stOutputPowerGeneration / 10.0;        //后续优化除法
        sprintf(tab_display,"    当日统计    \n光伏:%8.1fkWh\n卖电:%8.1fkWh\n买电:%8.1fkWh\n",fPvData,fInputData,fOutputData);
    }
    else if(sU8StatisticsCounter == PAGE_TWO)                                                              
    {
        float fChargeData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stChagePowerGeneration / 10.0;       //后续优化除法
        float fDisChargeData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stDisChagePowerGeneration / 10.0; //后续优化除法
        float fLoadData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stLoadPowerGeneration / 10.0;    //后续优化除法
        sprintf(tab_display,"    当日统计    \n充电:%8.1fkWh\n放电:%8.1fkWh\n负载:%8.1fkWh\n",fChargeData,fDisChargeData,fLoadData);
    }    
    else if(sU8StatisticsCounter == PAGE_THREE)
    {
        float fPvData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stPVPowerGeneration / 10.0;        //后续优化除法
        float fInputData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stInputPowerGeneration / 10.0;        //后续优化除法
        float fOutputData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stOutputPowerGeneration / 10.0;//后续优化除法
        sprintf(tab_display,"    当月统计    \n光伏:%8.1fkWh\n卖电:%8.1fkWh\n买电:%8.1fkWh\n",fPvData,fInputData,fOutputData);
    }
    else if(sU8StatisticsCounter == PAGE_FOUR)
    {
        float fChargeData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stChagePowerGeneration / 10.0;       //后续优化除法
        float fDisChargeData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stDisChagePowerGeneration / 10.0; //后续优化除法
        float fLoadData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stLoadPowerGeneration / 10.0;    //后续优化除法
        sprintf(tab_display,"    当月统计    \n充电:%8.1fkWh\n放电:%8.1fkWh\n负载:%8.1fkWh\n",fChargeData,fDisChargeData,fLoadData);
    } 
    else if(sU8StatisticsCounter == PAGE_FIVE)
    {
        float fPvData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stPVPowerGeneration / 10.0;        //后续优化除法
        float fInputData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stInputPowerGeneration / 10.0;        //后续优化除法
        float fOutputData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stOutputPowerGeneration / 10.0;//后续优化除法
        sprintf(tab_display,"    当年统计    \n光伏:%8.1fkWh\n卖电:%8.1fkWh\n买电:%8.1fkWh\n",fPvData,fInputData,fOutputData);
    }
    else if(sU8StatisticsCounter == PAGE_SIX)
    {
        float fChargeData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stChagePowerGeneration / 10.0;       //后续优化除法
        float fDisChargeData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stDisChagePowerGeneration / 10.0; //后续优化除法
        float fLoadData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stLoadPowerGeneration / 10.0;    //后续优化除法
        sprintf(tab_display,"    当年统计    \n充电:%8.1fkWh\n放电:%8.1fkWh\n负载:%8.1fkWh\n",fChargeData,fDisChargeData,fLoadData);
    }  
    else if(sU8StatisticsCounter == PAGE_SEVEN)
    {
        float fPvData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stPVPowerGeneration / 10.0;        //后续优化除法
        float fInputData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stInputPowerGeneration / 10.0;        //后续优化除法
        float fOutputData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stOutputPowerGeneration / 10.0;//后续优化除法
        sprintf(tab_display,"    总共统计    \n光伏:%8.1fkWh\n卖电:%8.1fkWh\n买电:%8.1fkWh\n",fPvData,fInputData,fOutputData);
    }
    else if(sU8StatisticsCounter == PAGE_EIGHT)
    {
        float fChargeData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stChagePowerGeneration / 10.0;       //后续优化除法
        float fDisChargeData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stDisChagePowerGeneration / 10.0; //后续优化除法
        float fLoadData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stLoadPowerGeneration / 10.0;    //后续优化除法
        sprintf(tab_display,"    总共统计    \n充电:%8.1fkWh\n放电:%8.1fkWh\n负载:%8.1fkWh\n",fChargeData,fDisChargeData,fLoadData);
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
        float fPvData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stPVPowerGeneration / 10.0;        //后续优化除法
        float fLoadData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stLoadPowerGeneration / 10.0;    //后续优化除法
        float fOutputData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stOutputPowerGeneration / 10.0;//后续优化除法
        sprintf(tab_display,"    当日统计    \n光伏:%-8.1f   \n负载:%-8.1f   \n输出:%-8.1f   \n",fPvData,fLoadData,fOutputData);  
    }
    else if(sU8StatisticsCounter == PAGE_TWO)
    {
        float fInputData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stInputPowerGeneration / 10.0;        //后续优化除法
        float fChargeData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stChagePowerGeneration / 10.0;       //后续优化除法
        float fDisChargeData = gDisplay.stDisplayData.stStatistical.stDayStatisticaldata.stDisChagePowerGeneration / 10.0; //后续优化除法
        sprintf(tab_display,"    当日统计    \n输入:%-8.1f   \n充电:%-8.1f   \n放电:%-8.1f   \n",fInputData,fChargeData,fDisChargeData);  
    }    
    else if(sU8StatisticsCounter == PAGE_THREE)
    {
        float fPvData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stPVPowerGeneration / 10.0;        //后续优化除法
        float fLoadData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stLoadPowerGeneration / 10.0;    //后续优化除法
        float fOutputData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stOutputPowerGeneration / 10.0;//后续优化除法
        sprintf(tab_display,"    当月统计    \n光伏:%-8.1f   \n负载:%-8.1f   \n输出:%-8.1f   \n",fPvData,fLoadData,fOutputData);  
    }
    else if(sU8StatisticsCounter == PAGE_FOUR)
    {
        float fInputData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stInputPowerGeneration / 10.0;        //后续优化除法
        float fChargeData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stChagePowerGeneration / 10.0;       //后续优化除法
        float fDisChargeData = gDisplay.stDisplayData.stStatistical.stMonthStatisticaldata.stDisChagePowerGeneration / 10.0; //后续优化除法
        sprintf(tab_display,"    当月统计    \n输入:%-8.1f   \n充电:%-8.1f   \n放电:%-8.1f   \n",fInputData,fChargeData,fDisChargeData);  
    } 
    else if(sU8StatisticsCounter == PAGE_FIVE)
    {
        float fPvData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stPVPowerGeneration / 10.0;        //后续优化除法
        float fLoadData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stLoadPowerGeneration / 10.0;    //后续优化除法
        float fOutputData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stOutputPowerGeneration / 10.0;//后续优化除法
        sprintf(tab_display,"    当年统计    \n光伏:%-8.1f   \n负载:%-8.1f   \n输出:%-8.1f   \n",fPvData,fLoadData,fOutputData);  
    }
    else if(sU8StatisticsCounter == PAGE_SIX)
    {
        float fInputData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stInputPowerGeneration / 10.0;        //后续优化除法
        float fChargeData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stChagePowerGeneration / 10.0;       //后续优化除法
        float fDisChargeData = gDisplay.stDisplayData.stStatistical.stYearStatisticaldata.stDisChagePowerGeneration / 10.0; //后续优化除法
        sprintf(tab_display,"    当年统计    \n输入:%-8.1f   \n充电:%-8.1f   \n放电:%-8.1f   \n",fInputData,fChargeData,fDisChargeData);  
    }  
    else if(sU8StatisticsCounter == PAGE_SEVEN)
    {
        float fPvData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stPVPowerGeneration / 10.0;        //后续优化除法
        float fLoadData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stLoadPowerGeneration / 10.0;    //后续优化除法
        float fOutputData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stOutputPowerGeneration / 10.0;//后续优化除法
        sprintf(tab_display,"    总共统计    \n光伏:%-8.1f   \n负载:%-8.1f   \n输出:%-8.1f   \n",fPvData,fLoadData,fOutputData);  
    }
    else if(sU8StatisticsCounter == PAGE_EIGHT)
    {
        float fInputData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stInputPowerGeneration / 10.0;        //后续优化除法
        float fChargeData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stChagePowerGeneration / 10.0;       //后续优化除法
        float fDisChargeData = gDisplay.stDisplayData.stStatistical.stTotalStatisticaldata.stDisChagePowerGeneration / 10.0; //后续优化除法
        sprintf(tab_display,"    总共统计    \n输入:%-8.1f   \n充电:%-8.1f   \n放电:%-8.1f   \n",fInputData,fChargeData,fDisChargeData);  
    }    
    
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 功能:设置系统CT变比设置中文界面信息
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
 功能:设置系统绝缘检测使能设置中文界面信息
****************************************************************************/
void updateDisplaySystemInsulationDetetionData_Chinese(ENABLE_TypeDef u8SetIndex)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    
    if(u8SetIndex == ENABLE_YES)
    {
        sprintf(tab_display,"    检测设置    \n->使能          \n禁止            \n                \n");                                                                               
    }
    else if(u8SetIndex == ENABLE_NO)
    {
        sprintf(tab_display,"    检测设置    \n使能            \n->禁止          \n                \n");                                                                                  
    }
    
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
功能:中文 设置通过提示界面信息
****************************************************************************/
void updateDisplayTipSetPassed_Chinese(void)
{
    sprintf(tab_display,"      提示      \n                \n    设置成功    \n                \n");
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 功能:设置系统保护使能设置中文界面信息
****************************************************************************/
void updateDisplayProtectSetData_Chinese(PROTECTSETAction_TypeDef u8SetIndex)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    
    if(u8SetIndex == SET_PROTECT_ISLAND_Index)
    {
        sprintf(tab_display,"    保护设置    \n->孤岛          \n接地            \n漏电            \n");                                                                               
    }
//    else if(u8SetIndex == SET_PROTECT_GROUND_Index)
//    {
//        sprintf(tab_display,"    保护设置    \n孤岛            \n->接地          \n漏电            \n");                                                                                  
//    }
//    else if(u8SetIndex == SET_PROTECT_LEAKAGE_Index)
//    {
//        sprintf(tab_display,"    保护设置    \n孤岛            \n接地            \n->漏电          \n");                                                                                  
//    }
    /*  请保留此段代码，以防热管理策略失效，无法主动关闭热保护
    else if(u8SetIndex == SET_PROTECT_ARC_Index)
    {
        sprintf(tab_display,"    保护设置    \n->拉弧          \n过热            \n低电压穿越      \n");                                                                                  
    } 
    else if(u8SetIndex == SET_PROTECT_OVERHEAT_Index)
    {
        sprintf(tab_display,"    保护设置    \n拉弧            \n->过热          \n低电压穿越      \n");                                                                                  
    }
    else if(u8SetIndex == SET_PROTECT_LVRT_Index)
    {
        sprintf(tab_display,"    保护设置    \n拉弧            \n过热            \n->低电压穿越    \n");                                                                                  
    }  
    else if(u8SetIndex == SET_PROTECT_HVRT_Index)
    {
        sprintf(tab_display,"    保护设置    \n->高电压穿越    \n防雷            \n发电机          \n");                                                                                  
    }
    else if(u8SetIndex == SET_PROTECT_LIGHT_Index)
    {
        sprintf(tab_display,"    保护设置    \n高电压穿越      \n->防雷          \n发电机          \n");                                                                                  
    }
    else if(u8SetIndex == SET_PROTECT_GEN_Index)
    {
        sprintf(tab_display,"    保护设置    \n高电压穿越      \n防雷            \n->发电机        \n");                                                                                  
    }
    else if(u8SetIndex == SET_PROTECT_LFRT_Index)
    {
        sprintf(tab_display,"    保护设置    \n->低频率穿越    \n高频率穿越      \nP(V)            \n");                                                                                  
    }    
    else if(u8SetIndex == SET_PROTECT_HFRT_Index)
    {
        sprintf(tab_display,"    保护设置    \n低频率穿越      \n->高频率穿越    \nP(V)            \n");                                                                                  
    }
    else if(u8SetIndex == SET_PROTECT_P_V_Index)
    {
        sprintf(tab_display,"    保护设置    \n低频率穿越      \n高频率穿越      \n->P(V)          \n");                                                                                  
    }  
    else if(u8SetIndex == SET_PROTECT_P_F_Index)
    {
        sprintf(tab_display,"    保护设置    \n->P(F)          \nQ(V)            \nQ(P)            \n");                                                                                  
    } 
    else if(u8SetIndex == SET_PROTECT_Q_V_Index)
    {
        sprintf(tab_display,"    保护设置    \nP(F)            \n->Q(V)          \nQ(P)            \n");                                                                                  
    }     
    else if(u8SetIndex == SET_PROTECT_Q_P_Index)
    {
        sprintf(tab_display,"    保护设置    \nP(F)            \nQ(V)            \n->Q(P)          \n");                                                                                  
    }    
    else if(u8SetIndex == SET_PROTECT_CPF_Index)
    {
        sprintf(tab_display,"    保护设置    \n->CPF           \nCQ              \n                \n");                                                                                  
    }      
    else if(u8SetIndex == SET_PROTECT_CQ_Index)
    {
        sprintf(tab_display,"    保护设置    \nCPF             \n->CQ            \n                \n");                                                                                  
    }  
*/
//    else if(u8SetIndex == SET_PROTECT_ARC_Index)
//    {
//        sprintf(tab_display,"    保护设置    \n->拉弧          \n低电压穿越      \n高电压穿越      \n");                                                                                  
//    }
//    else if(u8SetIndex == SET_PROTECT_LVRT_Index)
//    {
//        sprintf(tab_display,"    保护设置    \n拉弧            \n->低电压穿越    \n高电压穿越      \n");                                                                                  
//    }  
//    else if(u8SetIndex == SET_PROTECT_HVRT_Index)
//    {
//        sprintf(tab_display,"    保护设置    \n拉弧            \n低电压穿越      \n->高电压穿越    \n");                                                                                  
//    }
//    else if(u8SetIndex == SET_PROTECT_LIGHT_Index)
//    {
//        sprintf(tab_display,"    保护设置    \n->防雷          \n发电机          \n低频率穿越      \n");                                                                                  
//    }
//    else if(u8SetIndex == SET_PROTECT_GEN_Index)
//    {
//        sprintf(tab_display,"    保护设置    \n防雷            \n->发电机        \n低频率穿越      \n");                                                                                  
//    }
//    else if(u8SetIndex == SET_PROTECT_LFRT_Index)
//    {
//        sprintf(tab_display,"    保护设置    \n防雷            \n发电机          \n->低频率穿越    \n");                                                                                  
//    }    
//    else if(u8SetIndex == SET_PROTECT_HFRT_Index)
//    {
//        sprintf(tab_display,"    保护设置    \n->高频率穿越    \nP(V)            \nP(F)            \n");                                                                                  
//    }
//    else if(u8SetIndex == SET_PROTECT_P_V_Index)
//    {
//        sprintf(tab_display,"    保护设置    \n高频率穿越      \n->P(V)          \nP(F)            \n");                                                                                  
//    }  
//    else if(u8SetIndex == SET_PROTECT_P_F_Index)
//    {
//        sprintf(tab_display,"    保护设置    \n高频率穿越      \nP(V)            \n->P(F)          \n");                                                                                  
//    } 
//    else if(u8SetIndex == SET_PROTECT_Q_V_Index)
//    {
//        sprintf(tab_display,"    保护设置    \n->Q(V)          \nQ(P)            \nCPF            \n");                                                                                  
//    }     
//    else if(u8SetIndex == SET_PROTECT_Q_P_Index)
//    {
//        sprintf(tab_display,"    保护设置    \nQ(V)            \n->Q(P)          \nCPF             \n");                                                                                  
//    }    
//    else if(u8SetIndex == SET_PROTECT_CPF_Index)
//    {
//        sprintf(tab_display,"    保护设置    \nQ(V)            \nQ(P)            \n->CPF           \n");                                                                                  
//    }      
//    else if(u8SetIndex == SET_PROTECT_CQ_Index)
//    {
//        sprintf(tab_display,"    保护设置    \n->CQ            \n                \n                \n");                                                                                  
//    }
//    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}
//荷兰语 设置系统保护使能设置界面信_中文

void updateDisplayProtectItemNameSetData_Chinese(ENABLE_CLASS_TypeDef enableClass, char * sEnableName_Chinese)
{
        //char sEnableName_Chinese[17] = {""}; 
        if(enableClass == ENABLE_CLASS_CURVE_SCAN)
        {  
            sprintf(sEnableName_Chinese   ,"%s","   IV曲线扫描   ");
        }
        else if(enableClass == ENABLE_CLASS_BATTERY_ENABLE)
        {
            sprintf(sEnableName_Chinese   ,"%s","    BMS 使能    ");
        }
        else if(enableClass == ENABLE_CLASS_BATTERY_WAKEUP)
        {
            sprintf(sEnableName_Chinese   ,"%s","    BMS 唤醒    ");
        }
        else if(enableClass == ENABLE_CLASS_SELL)
        {
            sprintf(sEnableName_Chinese   ,"%s","    电网卖电    ");
        }
        else if(enableClass == ENABLE_CLASS_ANTIREFLUX)
        {
            sprintf(sEnableName_Chinese   ,"%s","     防逆流     ");
        }    
        else if(enableClass == ENABLE_CLASS_GEN)
        {
            sprintf(sEnableName_Chinese   ,"%s","   发电机使能   ");
        }
        else if(enableClass == ENABLE_CLASS_ISLAND)
        {
            sprintf(sEnableName_Chinese   ,"%s","      孤岛      ");
        }
        else if(enableClass == ENABLE_CLASS_GROUND)
        {
            sprintf(sEnableName_Chinese   ,"%s","      接地      ");
        }
        else if(enableClass == ENABLE_CLASS_LEAKAGE)
        {
            sprintf(sEnableName_Chinese   ,"%s","      漏电      ");
        }
        else if(enableClass == ENABLE_CLASS_ARC)
        {
            sprintf(sEnableName_Chinese   ,"%s","      拉弧      ");
        }
        //else if(enableClass == ENABLE_CLASS_OVERHEAT)
        //{
            //sprintf(sEnableName_Chinese   ,"%s","      过热      ");
        //}
        else if(enableClass == ENABLE_CLASS_LVRT)
        {
            sprintf(sEnableName_Chinese   ,"%s","   低电压穿越   "); //LVRT：low voltage ride through 
        }
        else if(enableClass == ENABLE_CLASS_HVRT)
        {
            sprintf(sEnableName_Chinese   ,"%s","   高电压穿越   "); //HVRT：High voltage ride through
        }
        else if(enableClass == ENABLE_CLASS_LIGHT)
        {
            sprintf(sEnableName_Chinese   ,"%s","      防雷      ");
        }
        else if(enableClass == ENABLE_CLASS_GEN_PROTECT)
        {
            sprintf(sEnableName_Chinese   ,"%s","     发电机     ");
        }
        else if(enableClass == ENABLE_CLASS_INSULATION_IMPEDANCE)
        {
            sprintf(sEnableName_Chinese   ,"%s","    绝缘阻抗    ");  //II:Insulation impedance
        }
        else if(enableClass == ENABLE_CLASS_LFRT)
        {
            sprintf(sEnableName_Chinese   ,"%s","   低频率穿越   ");  //LVRT：low frequency ride through 
        }
        else if(enableClass == ENABLE_CLASS_HFRT)
        {
            sprintf(sEnableName_Chinese   ,"%s","   高频率穿越   ");  //HVRT：High frequency ride through
        }
        else if(enableClass == ENABLE_CLASS_P_V)
        {
            sprintf(sEnableName_Chinese   ,"%s","    P(V) 保护   ");  //
        }
        else if(enableClass == ENABLE_CLASS_P_F)
        {
            sprintf(sEnableName_Chinese   ,"%s","    P(F) 保护   ");  //
        }
        else if(enableClass == ENABLE_CLASS_Q_V)
        {
            sprintf(sEnableName_Chinese   ,"%s","    Q(V) 保护   ");  //
        }
        else if(enableClass == ENABLE_CLASS_Q_P)
        {
            sprintf(sEnableName_Chinese   ,"%s","    Q(P) 保护   ");  //
        }
        else if(enableClass == ENABLE_CLASS_CPF)
        {
            sprintf(sEnableName_Chinese   ,"%s","    CPF 保护    ");  //
        }
        else if(enableClass == ENABLE_CLASS_CQ)
        {
            sprintf(sEnableName_Chinese   ,"%s","     CQ 保护    ");  //
        }
}

/***************************************************************************
 功能:设置系统绝缘检测使能设置中文界面信息
****************************************************************************/
void updateDisplayProtectItemSetData_Chinese(ENABLE_TypeDef sU8ProtectSelected,char * sEnableName)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    if(sU8ProtectSelected == ENABLE_NO)
    {
       sprintf(tab_display,"%s\n使能            \n->禁止          \n                \n",sEnableName);
    }
    else
    {
       sprintf(tab_display,"%s\n->使能          \n禁止            \n                \n",sEnableName);
    } 
    
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 功能:光伏设置PVSET中文界面
****************************************************************************/
void updateDisplayPVSetData_Chinese(uint8_t u8PVSetIndex)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);    
    if(u8PVSetIndex == SET_PV_CONTROLWAY_Index)
    {
        sprintf(tab_display,"    光伏设置    \n->光伏控制方法  \nIV曲线扫描      \n                \n");
    }
    else if(u8PVSetIndex == SET_PV_CURVESCAN_Index)
    {
        sprintf(tab_display,"    光伏设置    \n光伏控制方法    \n->IV曲线扫描    \n                \n");
    }
    else
    {
                    
    }
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 功能:光伏控制方式设置PVCONTROLWAYSET中文界面
****************************************************************************/
void updateDisplayPVControlWaySetData_Chinese(uint8_t u8PVContWaySetIndex)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    if(u8PVContWaySetIndex == PV_WAY_ALONE)
    {
        sprintf(tab_display,"  光伏控制方法  \n->独立          \n并联            \n                \n");
    }
    else if(u8PVContWaySetIndex == PV_WAY_PARAL)
    {
        sprintf(tab_display,"  光伏控制方法  \n独立            \n->并联          \n                \n");
    }
    else
    {
                    
    }
    
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
    
}

/***************************************************************************
 功能:电池设置数据显示 中文界面信息
****************************************************************************/
void updateDisplayBMSSetData_Chinese(uint8_t sU8BMSSetCounter)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
       
    if(sU8BMSSetCounter == BMS_CLASS_BMS)
    {
        sprintf(tab_display,"    电池设置    \n->使能          \n类型            \n                \n"); 
    }
    //else if(sU8BMSSetCounter == BMS_CLASS_WAKEUP)
    //{
    //    sprintf(tab_display,"    电池设置    \n使能            \n->唤醒          \n厂商            \n");   
    //}
    //else if(sU8BMSSetCounter == BMS_CLASS_MANUFACTURER)
    //{
    //    sprintf(tab_display,"    电池设置    \n使能            \n唤醒            \n->厂商          \n");  
    //}
    else if(sU8BMSSetCounter == BMS_CLASS_TYPE)
    {
        sprintf(tab_display,"    电池设置    \n使能            \n->类型          \n                \n");  
    }
                  
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 功能:电池设置数据显示 中文界面信息
****************************************************************************/
void updateDisplayBatteryManufacturerSetData_Chinese(uint8_t sU8BatteryManufacturerCounter)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
       
    if(sU8BatteryManufacturerCounter == BMS_MANU_CVTE)
    {
        sprintf(tab_display,"    BMS 厂商    \n->CVTE          \nPylon           \n                \n"); 
    }
    //else if(sU8BatteryManufacturerCounter == BMS_MANU_LG)
    //{
    //    sprintf(tab_display,"    BMS 厂商    \nCVTE            \n->LG            \nPylon           \n");   
    //}
    else if(sU8BatteryManufacturerCounter == BMS_MANU_Pylon)
    {
        sprintf(tab_display,"    BMS 厂商    \nCVTE            \n->Pylon         \n                \n");  
    }
                  
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 功能:电池设置数据显示 中文界面信息
****************************************************************************/
void updateDisplayBatteryTypeSetData_Chinese(uint8_t sU8BatteryTypeCounter)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
       
    if(sU8BatteryTypeCounter ==  BMS_TYPE_LI_ION)
    {
        sprintf(tab_display,"    BMS 类型    \n->LI.ION        \nLEAD.ACID       \n                \n"); 
    }
    else if(sU8BatteryTypeCounter == BMS_TYPE_LEAD_ACID)
    {
        sprintf(tab_display,"    BMS 类型    \nLI.ION          \n->LEAD.ACID     \n                \n");   
    }

                  
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}
/***************************************************************************
 功能:电池设置数据显示 中文界面信息
****************************************************************************/
void updateDisplayGridSetData_Chinese(uint8_t sU8BMSSetCounter)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    #if 0  
    if(sU8BMSSetCounter == SET_GRID_Sell_Index)
    {
        sprintf(tab_display,"   电网设置 1   \n->卖电使能      \n防逆流          \n电表            \n"); 
    }
    //else if(sU8BMSSetCounter == SET_GRID_Antireflux_Index)
    //{
    //    sprintf(tab_display,"   电网设置 1   \n卖电使能        \n->防逆流        \n电表            \n");   
    //}
    else if(sU8BMSSetCounter == SET_GRID_Meter_Index)
    {
        sprintf(tab_display,"   电网设置 1   \n卖电使能        \n防逆流          \n->电表          \n");  
    }
    else if(sU8BMSSetCounter == SET_GRID_SR_Index)
    {
        sprintf(tab_display,"   电网设置 2   \n->安规          \n价格            \n                \n");  
    }
    else if(sU8BMSSetCounter == SET_GRID_Price_Index)
    {
        sprintf(tab_display,"   电网设置 2   \n安规            \n->价格          \n                \n");  
    }

    
    if(sU8BMSSetCounter == SET_GRID_Sell_Index)
    {
        sprintf(tab_display,"   电网设置 1   \n->卖电使能      \n电表            \n并网标准        \n"); 
    }
    else if(sU8BMSSetCounter == SET_GRID_Meter_Index)
    {
        sprintf(tab_display,"   电网设置 1   \n卖电使能        \n->电表          \n并网标准        \n");  
    }
    else if(sU8BMSSetCounter == SET_GRID_SR_Index)
    {
        sprintf(tab_display,"   电网设置 1   \n卖电使能        \n电表            \n->并网标准      \n");
    }
    else if(sU8BMSSetCounter == SET_GRID_Price_Index)
    {
        sprintf(tab_display,"   电网设置 2   \n->价格          \n无功控制方式    \n无功功率设置    \n");
    }
    else if(sU8BMSSetCounter == SET_GRID_ReactPowerWay_Index)
    {
        sprintf(tab_display,"   电网设置 2   \n价格            \n->无功控制方式  \n无功功率设置    \n");
    }
    else if(sU8BMSSetCounter == SET_GRID_ReactPower_Index)
    {
        sprintf(tab_display,"   电网设置 2   \n价格            \n无功控制方式    \n->无功功率设置  \n");
    }
    else if(sU8BMSSetCounter == SET_GRID_PF_Index)
    {
        sprintf(tab_display,"   电网设置 3   \n->功率因数      \n                \n                \n");
    }
     #endif           
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 功能:电网安规设置 中文界面信息
****************************************************************************/
void updateDisplayGridSRSetData_Chinese(uint8_t sU8BMSSetCounter)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
       
    if(sU8BMSSetCounter == SR_EURTEN)
    {
        sprintf(tab_display,"   电网标准 1   \n->EUR Union     \nDE              \nUK              \n"); 
    }
    else if(sU8BMSSetCounter == SR_DE)
    {
        sprintf(tab_display,"   电网标准 1   \nEUR Union       \n->DE            \nUK              \n");
    }
    else if(sU8BMSSetCounter == SR_UK)
    {
        sprintf(tab_display,"   电网标准 1   \nEUR Union       \nDE              \n->UK            \n");
    }
    else if(sU8BMSSetCounter == SR_ZA)
    {
        sprintf(tab_display,"   电网标准 2   \n->ZA            \nAU              \n                \n");
    }
    else if(sU8BMSSetCounter == SR_AU)
    {
        sprintf(tab_display,"   电网标准 2   \nZA              \n->AU            \n                \n");
    }
                  
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);  
}

/***************************************************************************
 功能:电网电价设置 中文界面信息
****************************************************************************/
void updateDisplayGridPriceSetData_Chinese(uint8_t sU8BMSSetCounter)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);   
    /*
    if(sU8BMSSetCounter == TPFV_TIP)
    {
        sprintf(tab_display,"   电网价格 1   \n->尖段          \n峰段            \n平段            \n"); 
    }
    else if(sU8BMSSetCounter == TPFV_PEAK)
    {
        sprintf(tab_display,"   电网价格 1   \n尖段            \n->峰段          \n平段            \n");   
    }
    else if(sU8BMSSetCounter == TPFV_FLAT)
    {
        sprintf(tab_display,"   电网价格 1   \n尖段            \n峰段            \n->平段          \n");  
    }
    else if(sU8BMSSetCounter == TPFV_VALLEY)
    {
        sprintf(tab_display,"   电网价格 2   \n->谷段          \n                \n                \n");  
    } 
    */                
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 

    if(sU8BMSSetCounter == TPFV_PEAK)
    {
        sprintf(tab_display,"   电网价格 1   \n->峰段          \n平段            \n谷段            \n");
    }
    else if(sU8BMSSetCounter == TPFV_FLAT)
    {
        sprintf(tab_display,"   电网价格 1   \n峰段            \n->平段          \n谷段            \n");
    }
    else if(sU8BMSSetCounter == TPFV_VALLEY)
    {
        sprintf(tab_display,"   电网价格 1   \n峰段            \n平段            \n->谷段          \n");
    }
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
  功能:无功功率设置中文界面
****************************************************************************/
void updateDisplayGridReactivePowerSetData_Chinese(char *ReactivePowerValue)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
       
    sprintf(tab_display,"  无功功率设置  \n                \n功率:%s W  \n                \n",ReactivePowerValue);
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
  功能:无功控制方式设置中文界面
****************************************************************************/
void updateDisplayGridReactPowerControlWaySetData_Chinese(uint8_t u8Way)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    if(u8Way == REACTPOWER_CONTROL_REACTPOWER)
    {
       sprintf(tab_display,"  无功控制方式  \n->无功功率控制  \n功率因数控制    \n                \n");
    }
    else
    {
       sprintf(tab_display,"  无功控制方式  \n无功功率控制    \n->功率因数控制  \n                \n");
    }
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
  功能:功率因数设置中文界面
****************************************************************************/
void updateDisplayGridPowerFactorSetData_Chinese(char* strPF)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
           
    sprintf(tab_display,"  功率因数设置  \n                \n功率 :%s %%\n                \n",strPF);
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);
    GUI_Display(tab_display, 0, 0); 
}

/***************************************************************************
 功能:中文 确认提示信息
****************************************************************************/
void updateDisplaySystemConfirm_Chinese(void)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    sprintf(tab_display,"                \n   确定或删除?  \n                \n                \n");
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);  
    GUI_Display(tab_display, 0, 0);
}
/***************************************************************************
 功能:电网尖峰平谷分时设置 中文界面信息
****************************************************************************/
void updateDisplayGridPriceTPFVSetData_Chinese(uint8_t sU8TPFVSetCounter, char* strPrice,TPFV_TypeDef enum_tpfv)
{
        memset(tab_display,0,DISPLAY_CACHE_SIZE);
    
    if(enum_tpfv == TPFV_TIP)
    {
        if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_PRICE)
        {
            sprintf(tab_display,"     尖段 1     \n->价格:%s    \n时段 1          \n时段 2          \n",strPrice);  
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_ONE)
        {
            sprintf(tab_display,"     尖段 1     \n价格:%s      \n->时段 1        \n时段 2          \n",strPrice);
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_TWO)
        {
            sprintf(tab_display,"     尖段 1     \n价格:%s      \n时段 1          \n->时段 2        \n",strPrice);
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_THREE)
        {
            sprintf(tab_display,"     尖段 2     \n->时段 3        \n                \n                \n");
        }
    }
    else if(enum_tpfv == TPFV_PEAK)
    {
        if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_PRICE)
        {
            sprintf(tab_display,"     峰段 1     \n->价格:%s    \n时段 1          \n时段 2          \n",strPrice);  
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_ONE)
        {
            sprintf(tab_display,"     峰段 1     \n价格:%s      \n->时段 1        \n时段 2          \n",strPrice);
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_TWO)
        {
            sprintf(tab_display,"     峰段 1     \n价格%s       \n时段 1          \n->时段 2        \n",strPrice);
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_THREE)
        {
            sprintf(tab_display,"     峰段 2     \n->时段 3        \n                \n                \n");
        }  
    }
    else if(enum_tpfv == TPFV_FLAT)
    {
        if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_PRICE)
        {
            sprintf(tab_display,"     平段 1     \n->价格:%s    \n时段 1          \n时段 2          \n",strPrice);  
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_ONE)
        {
            sprintf(tab_display,"     平段 1     \n价格:%s      \n->时段 1        \n时段 2          \n",strPrice);
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_TWO)
        {
            sprintf(tab_display,"     平段 1     \n价格:%s      \n时段 1          \n->时段 2        \n",strPrice);
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_THREE)
        {
            sprintf(tab_display,"     平段 2     \n->时段 3        \n                \n                \n");
        } 
    }
    else if(enum_tpfv == TPFV_VALLEY)
    {        
        if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_PRICE)
        {
            sprintf(tab_display,"     谷段 1     \n->价格:%s    \n时段 1          \n时段 2          \n",strPrice);  
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_ONE)
        {
            sprintf(tab_display,"     谷段 1     \n价格:%s      \n->时段 1        \n时段 2          \n",strPrice);
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_TWO)
        {
            sprintf(tab_display,"     谷段 1     \n价格:%s      \n时段 1          \n->时段 2        \n",strPrice);
        }
        else if(sU8TPFVSetCounter == PRICE_TPFV_PERIOD_THREE)
        {
            sprintf(tab_display,"     谷段 2     \n->时段 3        \n                \n                \n");
        } 
    }  
                         
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 功能:电网分时电价起始时间设置 中文界面信息
****************************************************************************/

void updateDisplayGridPriceTPFVTimePeriodSetData_Chinese(char* strStartTime, char* strEndTime, TPFV_TypeDef enum_tpfv, TPFV_Price_TypeDef enumTPFVPeriod)    
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    if(enum_tpfv == TPFV_PEAK)
    {    
        if(enumTPFVPeriod == PRICE_TPFV_PERIOD_ONE)
        {
            sprintf(tab_display,"     峰段 %d     \n开始:%s   \n结束:%s   \n                \n",enumTPFVPeriod,strStartTime,strEndTime); 
        }
        else if(enumTPFVPeriod == PRICE_TPFV_PERIOD_TWO)
        {
            sprintf(tab_display,"     峰段 %d     \n开始:%s   \n结束:%s   \n                \n",enumTPFVPeriod,strStartTime,strEndTime);   
        }
        else if(enumTPFVPeriod == PRICE_TPFV_PERIOD_THREE)
        {
            sprintf(tab_display,"     峰段 %d     \n开始:%s   \n结束:%s   \n                \n",enumTPFVPeriod,strStartTime,strEndTime); 
        }
    }
    else if(enum_tpfv == TPFV_FLAT)
    {
        if(enumTPFVPeriod == PRICE_TPFV_PERIOD_ONE)
        {
            sprintf(tab_display,"     平段 %d     \n开始:%s   \n结束:%s   \n                \n",enumTPFVPeriod,strStartTime,strEndTime); 
        }
        else if(enumTPFVPeriod == PRICE_TPFV_PERIOD_TWO)
        {
            sprintf(tab_display,"     平段 %d     \n开始:%s   \n结束:%s   \n                \n",enumTPFVPeriod,strStartTime,strEndTime);   
        }
        else if(enumTPFVPeriod == PRICE_TPFV_PERIOD_THREE)
        {
            sprintf(tab_display,"     平段 %d     \n开始:%s   \n结束:%s   \n                \n",enumTPFVPeriod,strStartTime,strEndTime); 
        }
    }
    else if(enum_tpfv == TPFV_VALLEY)
    {
        if(enumTPFVPeriod == PRICE_TPFV_PERIOD_ONE)
        {
            sprintf(tab_display,"     谷段 %d     \n开始:%s   \n结束:%s   \n                \n",enumTPFVPeriod,strStartTime,strEndTime); 
        }
        else if(enumTPFVPeriod == PRICE_TPFV_PERIOD_TWO)
        {
            sprintf(tab_display,"     谷段 %d     \n开始:%s   \n结束:%s   \n                \n",enumTPFVPeriod,strStartTime,strEndTime);   
        }
        else if(enumTPFVPeriod == PRICE_TPFV_PERIOD_THREE)
        {
            sprintf(tab_display,"     谷段 %d     \n开始:%s   \n结束:%s   \n                \n",enumTPFVPeriod,strStartTime,strEndTime); 
        }
    }
                         
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 功能:升级界面中文界面
****************************************************************************/
void  updateDisplayUpgradeData_Chinese(Upgrade_TypeDef u8UpgradeIndex)
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    if(u8UpgradeIndex == UPGRADE_EMS)
    {
        sprintf(tab_display,"    升级设置    \n->EMS           \nDSP             \n备用MCU         \n");   
    }
    else if(u8UpgradeIndex == UPGRADE_DSP)
    {
        sprintf(tab_display,"    升级设置    \nEMS             \n->DSP           \n备用MCU         \n");
    }
    else if(u8UpgradeIndex == UPGRADE_BACKUP_MCU)
    {
        sprintf(tab_display,"    升级设置    \nEMS             \nDSP             \n->备用MCU       \n");
    }
    else if(u8UpgradeIndex == UPGRADE_BMS)
    {
        sprintf(tab_display,"    升级设置    \n->BMS           \n                \n                \n");
    }
    
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);
    GUI_Display(tab_display, 0, 0); 
}


/*快捷方式操作*/

//ESC+DOWN
/***************************************************************************
 功能:系统数据显示 中文界面信息
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
            sprintf(tab_PVWay,"%s","独立   ");      
        }
        else
        {
            sprintf(tab_PVWay,"%s","并联   "); 
        }
                
        sprintf(tab_display,"   系统数据 %d   \n语言:%s    \n安规:%s       \nPV方式:%s \n",sU8SystemCounter+1,"汉语   ",tab_SR,tab_PVWay);
  
    }
    else if(sU8SystemCounter == PAGE_TWO)
    {
        char tab_Work[9] = {""}; 
        
        if(gDisplay.stDisplaySet.stStrategy.u8StrategyType == STRATEGY_TPFV)
        {
            sprintf(tab_Work,"%s","尖峰平谷");
        }
        else if(gDisplay.stDisplaySet.stStrategy.u8StrategyType == STRATEGY_REGULAR)
        {
            sprintf(tab_Work,"%s","定时    "); 
        }
        else if(gDisplay.stDisplaySet.stStrategy.u8StrategyType == STRATEGY_SELF)
        {
            sprintf(tab_Work,"%s","自发自用"); 
        }
        else if(gDisplay.stDisplaySet.stStrategy.u8StrategyType == STRATEGY_BACKUP)
        {
            sprintf(tab_Work,"%s","备电    "); 
        }
        else if(gDisplay.stDisplaySet.stStrategy.u8StrategyType == STRATEGY_GEN)
        {
            sprintf(tab_Work,"%s","发电机  "); 
        }
         
        char tab_Anti[5] = {""}; 
        
        if(gDisplay.stDisplaySet.stGrid.u8PreventReverseFlowControlFlag == ENABLE_YES)
        {   
            sprintf(tab_Anti,"%s","是  ");  
        }
        else
        {
            sprintf(tab_Anti,"%s","否  "); 
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
     
        sprintf(tab_display,"   系统数据 %d   \n模式:%s   \n防逆流:%s     \nBMS:%s      \n",sU8SystemCounter+1,tab_Work,tab_Anti,tab_BMS_Manufacturer);
  
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
        sprintf(tab_display,"   系统数据 %d   \nDSP:%s\nEMS:%s\nAux:%s\n",sU8SystemCounter+1,tab_Dsp_Version,tab_Ems_Version,tab_Bak_Version); 
    }
    else if(sU8SystemCounter == PAGE_FOUR)
    {
        float fSystemTemp = gDisplay.stDisplayData.stSystemData.s16SystemTemperature / 10.0;        //后续优化除法   
        sprintf(tab_display,"   系统数据 %d   \n系统温度:%-5.1f  \n                \n                \n",sU8SystemCounter+1,fSystemTemp); 
    }    
    
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 功能:实时数据显示 中文界面信息 Up + Down
****************************************************************************/
void updateDisplayRealtimeData_Chinese(uint8_t sU8RealtimeCounter)    
{
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    
    if(sU8RealtimeCounter == PAGE_ONE)
    {
        float fCurrent   = gDisplay.stDisplayData.stGridData.sGridcurrent / 10.0;
        float fVoltage   = gDisplay.stDisplayData.stGridData.u16GridVoltage / 10.0;
        float fFrequency = gDisplay.stDisplayData.stGridData.u16GridFrequency / 100.00;
        
        sprintf(tab_display,"   并网数据 1   \n电压:  %8.1fV\n电流:  %8.1fA\n频率: %8.2fHz\n",fVoltage,fCurrent,fFrequency);
    }
    else if(sU8RealtimeCounter == PAGE_TWO)
    {
        float fReactivePower   = gDisplay.stDisplayData.stGridData.sGridReactivePower / 10.0;
        float fGridActivePower = gDisplay.stDisplayData.stGridData.sGridActivePower / 10.0;
        
        sprintf(tab_display,"   并网数据 2   \n有功:    %6.1fW\n无功:  %6.1fVar\n                \n",fGridActivePower,fReactivePower);
    }    
    else if(sU8RealtimeCounter == PAGE_THREE)
    {
        float fVoltage   = gDisplay.stDisplayData.stPV.stPV1.u16PVVoltage / 10.0;
        float fCurrent   = gDisplay.stDisplayData.stPV.stPV1.sPVCurrent / 10.0;
        float fPower     = gDisplay.stDisplayData.stPV.stPV1.sPVPower / 10.0;
        
        sprintf(tab_display,"    PV1数据 1   \n电压:  %8.1fV\n电流:  %8.1fA\n功率:  %8.3fW\n",fVoltage,fCurrent,fPower);
    }
    else if(sU8RealtimeCounter == PAGE_FOUR)
    {
        float fVoltage   = gDisplay.stDisplayData.stPV.stPV2.u16PVVoltage / 10.0;
        float fCurrent   = gDisplay.stDisplayData.stPV.stPV2.sPVCurrent / 10.0;
        float fPower     = gDisplay.stDisplayData.stPV.stPV2.sPVPower / 10.0;
        
        sprintf(tab_display,"    PV2数据 1   \n电压:  %8.1fV\n电流:  %8.1fA\n功率:  %8.3fW\n",fVoltage,fCurrent,fPower);  
    } 
    else if(sU8RealtimeCounter == PAGE_FIVE)
    {
        float fVoltage   = gDisplay.stDisplayData.stLoad.u16LoadVoltage / 10.0;
        float fCurrent   = gDisplay.stDisplayData.stLoad.sLoadcurrent / 10.0;
        float fPower     = gDisplay.stDisplayData.stLoad.sLoadPower / 10.0;
        sprintf(tab_display,"   负载数据 1   \n电压:  %8.1fV\n电流:  %8.1fA\n功率:  %8.3fW\n",fVoltage,fCurrent,fPower);  
    } 
    else if(sU8RealtimeCounter == PAGE_SIX)
    {
        float fLoadRate = (float) gDisplay.stDisplayData.stLoad.sLoadPower / DEVICERATEDPOWER;
        sprintf(tab_display,"   负载数据 2   \n负载率:     %3.1f%%\n                \n                \n",fLoadRate);  
    } 
    else if(sU8RealtimeCounter == PAGE_SEVEN)
    {
        float fVoltage   = gDisplay.stDisplayData.stBMS.u16BMSVoltage / 10.0;
        float fCurrent   = gDisplay.stDisplayData.stBMS.sBMSCurrent / 10.0;
        if(gDisplay.stDisplayData.stBMS.sBMSCurrent > 0)
        {
            sprintf(tab_display,"   BMS数据 1    \n状态:       放电\n电压:  %8.1fV\n电压:  %8.1fA\n",fVoltage,fCurrent);
        }
        else if(gDisplay.stDisplayData.stBMS.sBMSCurrent <= 0)
        {
            fCurrent   = abs(gDisplay.stDisplayData.stBMS.sBMSCurrent);
            sprintf(tab_display,"   BMS数据 1    \n状态:       充电\n电压:  %8.1fV\n电压:  %8.1fA\n",fVoltage,fCurrent);
        }
    }  
    else if(sU8RealtimeCounter == PAGE_EIGHT)
    {
        float fSOC        = gDisplay.stDisplayData.stBMS.u8SOC;
        if(gDisplay.stDisplayData.stBMS.sBMSCurrent > 0)
        {
            float fPower   = gDisplay.stDisplayData.stBMS.sDisChargePower / 10.0;
            sprintf(tab_display,"   BMS数据 2    \n功率:  %8.1fW\nSOC:   %8.1f%%\n                \n",fPower,fSOC);
        }
        else if(gDisplay.stDisplayData.stBMS.sBMSCurrent <= 0)
        {
            float fPower   = abs(gDisplay.stDisplayData.stBMS.sChargePower) / 10.0;
            sprintf(tab_display,"   BMS数据 2    \n功率:  %8.1fW\nSOC:   %8.1f%%\n                \n",fPower,fSOC);
        }
//        float fOutPower   = gDisplay.stDisplayData.stBMS.sDisChargePower / 10.0;
//        float fSOC        = gDisplay.stDisplayData.stBMS.u8SOC;
//        float fSOH        = gDisplay.stDisplayData.stBMS.u8SOH;
           
//        sprintf(tab_display,"      BMS Data 2     \nOut-Power:%-8.1f   \nSOC:%-8.1f         \nSOH:%-8.1f         \n",fOutPower,fSOC,fSOH);  //Out-P 放电功率 
    } 
    else if(sU8RealtimeCounter == PAGE_NINE)
    {
        float fCurrent   = gDisplay.stDisplayData.stGenData.sGencurrent / 10.0;
        float fVoltage   = gDisplay.stDisplayData.stGenData.u16GenVoltage / 10.0;
        float fFrequency = gDisplay.stDisplayData.stGenData.u16GenFrequency / 100.00;
        
        sprintf(tab_display,"  发电机数据 1  \n电压:  %8.1fV\n电流:  %8.1fA\n频率: %8.2fHz\n",fVoltage,fCurrent,fFrequency);
    }
    else if(sU8RealtimeCounter == PAGE_TEN)
    {
        float fActivePower   = gDisplay.stDisplayData.stGenData.sGenPower / 10.0;
        
        sprintf(tab_display,"  发电机数据 2  \n有功:  %8.1fW\n                     \n                     \n",fActivePower);  
    }  
/*    if(sU8RealtimeCounter == PAGE_SEVEN)
    {
        float fOutPower   = gDisplay.stDisplayData.stBMS.sDisChargePower / 10.0;
        float fSOC        = gDisplay.stDisplayData.stBMS.u8SOC;
        float fSOH        = gDisplay.stDisplayData.stBMS.u8SOH;
           
        sprintf(tab_display,"      BMS Data 2     \nOut-Power:%-8.1f   \nSOC:%-8.1f         \nSOH:%-8.1f         \n",fOutPower,fSOC,fSOH);  //Out-P 放电功率 
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
        float fDOD     = gDisplay.stDisplayData.stBMS.u8DOD / 10.0;               //后续优化除法
        float fCurrent = gDisplay.stDisplayData.stBMS.sMaxChargeCurrent / 10.0;   //后续优化除法
        float fVoltage = gDisplay.stDisplayData.stBMS.u16MaxChargeVoltage / 10.0; //后续优化除法
           
        sprintf(tab_display,"      BMS Data 4     \nDOD:%-8.1f         \nCurrent-In-Max:%-6.1f\nVoltage-In-Max:%-6.1f\n",fDOD,fCurrent,fVoltage);  
    }  
    if(sU8RealtimeCounter == PAGE_TEN)
    {
        //
        float fUnderValtage = gDisplay.stDisplayData.stBMS.u16UnderValtagevalue / 10.0; //后续优化除法
        float fCurrent = gDisplay.stDisplayData.stBMS.sMaxDisChargeCurrent / 10.0;      //后续优化除法
        float fVoltage = gDisplay.stDisplayData.stBMS.u16MaxDisChargeVoltage / 10.0;    //后续优化除法
           
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
        float fCurrent   = gDisplay.stDisplayData.stGridData.sGridcurrent / 10.0;            //后续优化除法
        float fVoltage   = gDisplay.stDisplayData.stGridData.u16GridVoltage / 10.0;          //后续优化除法
        float fFrequency = gDisplay.stDisplayData.stGridData.u16GridFrequency / 100.00;      //后续优化除法
        sprintf(tab_display,"   并网数据 1   \n电压:%-8.1f   \n电流:%-8.1f   \n频率:%-8.2f    \n",fVoltage,fCurrent,fFrequency);
    }
    else if(sU8RealtimeCounter == PAGE_TWO)
    {
        float fReactivePower   = gDisplay.stDisplayData.stGridData.sGridReactivePower / 10.0;          //后续优化除法
        float fGridActivePower = gDisplay.stDisplayData.stGridData.sGridActivePower / 10.0;            //后续优化除法
           
        sprintf(tab_display,"   并网数据 2   \n有功:%-8.1f   \n无功:%-6.1f     \n                \n",fGridActivePower,fReactivePower);  
    }    
    if(sU8RealtimeCounter == PAGE_THREE)
    {
        float fVoltage   = gDisplay.stDisplayData.stPV.stPV1.u16PVVoltage / 10.0;  //后续优化除法
        float fCurrent   = gDisplay.stDisplayData.stPV.stPV1.sPVCurrent / 10.0;    //后续优化除法
        float fPower     = gDisplay.stDisplayData.stPV.stPV1.sPVPower / 10.0;      //后续优化除法
           
        sprintf(tab_display,"    PV1数据 1   \n电压:%-8.1f   \n电流:%-8.1f   \n功率:%-8.3f   \n",fVoltage,fCurrent,fPower);  
    }
    if(sU8RealtimeCounter == PAGE_FOUR)
    {
        float fVoltage   = gDisplay.stDisplayData.stPV.stPV2.u16PVVoltage / 10.0;  //后续优化除法
        float fCurrent   = gDisplay.stDisplayData.stPV.stPV2.sPVCurrent / 10.0;    //后续优化除法
        float fPower     = gDisplay.stDisplayData.stPV.stPV2.sPVPower / 10.0;      //后续优化除法
           
        sprintf(tab_display,"    PV1数据 2   \n电压:%-8.1f   \n电流:%-8.1f   \n功率:%-8.3f   \n",fVoltage,fCurrent,fPower);  
    } 
    if(sU8RealtimeCounter == PAGE_FIVE)
    {
        float fVoltage   = gDisplay.stDisplayData.stLoad.u16LoadVoltage / 10.0;  //后续优化除法
        float fCurrent   = gDisplay.stDisplayData.stLoad.sLoadcurrent / 10.0;    //后续优化除法
        float fPower     = gDisplay.stDisplayData.stLoad.sLoadPower / 10.0;      //后续优化除法
           
        sprintf(tab_display,"   负载数据 1   \n电压:%-8.1f   \n电流:%-8.1f   \nPWR:%-8.3f\n",fVoltage,fCurrent,fPower);  
    } 
    if(sU8RealtimeCounter == PAGE_SIX)
    {
        //
        float fVoltage   = gDisplay.stDisplayData.stBMS.u16BMSVoltage / 10.0;    //后续优化除法
        float fCurrent   = gDisplay.stDisplayData.stBMS.sBMSCurrent   / 10.0;    //后续优化除法
        float fInPower   = gDisplay.stDisplayData.stBMS.sChargePower  / 10.0;    //后续优化除法
           
        sprintf(tab_display,"   BMS数据 1    \n电压:%-8.1f   \n电流:%-8.1f   \n输入功:%-8.3f \n",fVoltage,fCurrent,fInPower);  //In-P 充电功率
    }  
    if(sU8RealtimeCounter == PAGE_SEVEN)
    {
        //
        float fOutPower   = gDisplay.stDisplayData.stBMS.sDisChargePower / 10.0;     //后续优化除法
        float fSOC        = gDisplay.stDisplayData.stBMS.u8SOC;                      //后续优化除法
        float fSOH        = gDisplay.stDisplayData.stBMS.u8SOH;                      //后续优化除法
           
        sprintf(tab_display,"   BMS数据 2    \n输出功:%-8.1f \nSOC:%-8.1f    \nSOH:%-8.1f    \n",fOutPower,fSOC,fSOH);  //Out-P 放电功率 
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
             
        float fCapacity   = gDisplay.stDisplayData.stBMS.u16BMSCapacity / 10.0;  //后续优化除法
        float fOverVoltage   = gDisplay.stDisplayData.stBMS.u16OverValtagevalue / 10.0;    //后续优化除法
    
        sprintf(tab_display,"   BMS数据 3    \n类型:%s      \n容量:%-8.1f   \n过压值:%-8.3f \n",tab_BMS_Type,fCapacity,fOverVoltage);  
    } 
    if(sU8RealtimeCounter == PAGE_NINE)
    {
        //
        float fDOD     = gDisplay.stDisplayData.stBMS.u8DOD / 10.0;               //后续优化除法
        float fCurrent = gDisplay.stDisplayData.stBMS.sMaxChargeCurrent / 10.0;   //后续优化除法
        float fVoltage = gDisplay.stDisplayData.stBMS.u16MaxChargeVoltage / 10.0; //后续优化除法
           
        sprintf(tab_display,"   BMS数据 4    \nDOD:%-8.1f    \n最大电流:%-6.1f \n最大电压:%-6.1f \n",fDOD,fCurrent,fVoltage);  
    }  
    if(sU8RealtimeCounter == PAGE_TEN)
    {
        //
        float fUnderValtage = gDisplay.stDisplayData.stBMS.u16UnderValtagevalue / 10.0; //后续优化除法
        float fCurrent = gDisplay.stDisplayData.stBMS.sMaxDisChargeCurrent / 10.0;      //后续优化除法
        float fVoltage = gDisplay.stDisplayData.stBMS.u16MaxDisChargeVoltage / 10.0;    //后续优化除法
           
        sprintf(tab_display,"   BMS数据 5    \n欠压值:%-7.1f  \n最大放电流:%-5.1f\n最大放电压:%-5.1f\n",fUnderValtage,fCurrent,fVoltage);  
    }    
    
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0); 
    GUI_Display(tab_display, 0, 0);
}

#endif


/***************************************************************************
 功能:中文 实时故障告警组装界面
****************************************************************************/
void updateDisplayRealFaultData_Chinese(uint8_t u8CurrentPage,uint8_t u8TotalPageNumber,uint8_t u8LastItemNumber)
{   
    memset(tab_display,0,DISPLAY_CACHE_SIZE); 
    Fault_Info_Real * pStReal = Display_Get_RealFaultData();
    if((u8CurrentPage == 0)&&(u8TotalPageNumber == 0))
    {
        sprintf(tab_display,"                \n                \n   无实时故障   \n                \n");
    }
    else if(((u8CurrentPage+1) == u8TotalPageNumber)&&(u8LastItemNumber == 1))
    {
        uint16_t u16TempCode  = pStReal->stRealFault[u8CurrentPage*DISPLAY_DATA_PERPAGE_MAX_ITEM+0].u16FaultCode;
        char tab_Fault_Name[DISPLAY_DATA_NAME_CACHE_SIZE-5]; //Display显示缓存
        memset(tab_Fault_Name,0,DISPLAY_DATA_NAME_CACHE_SIZE-5);
        getFaultNameByFaultCode_Chinese(tab_Fault_Name,u16TempCode);//根据故障码获取故障名称
        sprintf(tab_display,"   实时故障 %02d  \n%04x:%11s\n                \n                \n",u8CurrentPage+1,u16TempCode,tab_Fault_Name);
    }
    else if(((u8CurrentPage+1) == u8TotalPageNumber) &&(u8LastItemNumber == 2))
    {
        uint16_t u8TempCode1  = pStReal->stRealFault[u8CurrentPage*DISPLAY_DATA_PERPAGE_MAX_ITEM+0].u16FaultCode;
        char tab_Fault_Name1[DISPLAY_DATA_NAME_CACHE_SIZE-5]; //Display显示缓存
        memset(tab_Fault_Name1,0,DISPLAY_DATA_NAME_CACHE_SIZE-5);
        getFaultNameByFaultCode_Chinese(tab_Fault_Name1,u8TempCode1);//根据故障码获取故障名称

        uint16_t u8TempCode2  = pStReal->stRealFault[u8CurrentPage*DISPLAY_DATA_PERPAGE_MAX_ITEM+1].u16FaultCode;
        char tab_Fault_Name2[DISPLAY_DATA_NAME_CACHE_SIZE-5]; //Display显示缓存
        memset(tab_Fault_Name2,0,DISPLAY_DATA_NAME_CACHE_SIZE-5);
        getFaultNameByFaultCode_Chinese(tab_Fault_Name2,u8TempCode2);//根据故障码获取故障名称
        sprintf(tab_display,"   实时故障 %02d  \n%04x:%11s\n%04x:%11s\n                \n",u8CurrentPage+1,u8TempCode1,tab_Fault_Name1,u8TempCode2,tab_Fault_Name2);
    }
    else
    {
        uint16_t u8TempCode1  = pStReal->stRealFault[u8CurrentPage*DISPLAY_DATA_PERPAGE_MAX_ITEM+0].u16FaultCode;
        char tab_Fault_Name1[DISPLAY_DATA_NAME_CACHE_SIZE-5]; //Display显示缓存
        memset(tab_Fault_Name1,0,DISPLAY_DATA_NAME_CACHE_SIZE-5);
        getFaultNameByFaultCode_Chinese(tab_Fault_Name1,u8TempCode1);//根据故障码获取故障名称
        
        uint16_t u8TempCode2  = pStReal->stRealFault[u8CurrentPage*DISPLAY_DATA_PERPAGE_MAX_ITEM+1].u16FaultCode;
        char tab_Fault_Name2[DISPLAY_DATA_NAME_CACHE_SIZE-5]; //Display显示缓存
        memset(tab_Fault_Name2,0,DISPLAY_DATA_NAME_CACHE_SIZE-5);
        getFaultNameByFaultCode_Chinese(tab_Fault_Name2,u8TempCode2);//根据故障码获取故障名称
        
        uint16_t u8TempCode3  = pStReal->stRealFault[u8CurrentPage*DISPLAY_DATA_PERPAGE_MAX_ITEM+2].u16FaultCode;
        char tab_Fault_Name3[DISPLAY_DATA_NAME_CACHE_SIZE-5]; //Display显示缓存
        memset(tab_Fault_Name3,0,DISPLAY_DATA_NAME_CACHE_SIZE-5);
        getFaultNameByFaultCode_Chinese(tab_Fault_Name3,u8TempCode3);//根据故障码获取故障名称
        
        sprintf(tab_display,"   实时故障 %02d  \n%04x:%11s\n%04x:%11s\n%04x:%11s\n",u8CurrentPage+1,u8TempCode1,tab_Fault_Name1,u8TempCode2,tab_Fault_Name2,u8TempCode3,tab_Fault_Name3);    
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
                strncpy(Fault_Name,"Bs过压快检",10);//bus over voltage fast detection  总线过压快速检测
            }
            break;          
        case SYS_FAULT_BusSlowOV: 
            { 
                strncpy(Fault_Name,"Bs过压慢检",10);//bus over voltage slow detection  总线过压慢速检测
            } 
            break;      
        case SYS_FAULT_BusUV: 
            { 
                strncpy(Fault_Name,"总线欠压  ",10);//bus under voltage.
            } 
            break;      
        case SYS_FAULT_BusSoft: 
            { 
                strncpy(Fault_Name,"总线软起  ",10);//Bus Soft
            } 
            break;      
        case SYS_FAULT_EmsCommErr:
            { 
                strncpy(Fault_Name,"EMS 通信  ",10);//EMS Communication Error.   EMS 通信错误
            } 
            break;      
        case SYS_FAULT_OutputShort: 
            { 
                strncpy(Fault_Name,"输出短路  ",10);//Output short circuit fault.  输出短路故障
            } 
            break;        
        case SYS_FAULT_GFCIErrLv3:
            { 
                strncpy(Fault_Name,"GFCI 泄露2",10);//GFCI leakage fault 1.
            } 
            break;      
        case SYS_FAULT_GFCIErrLv2: 
            { 
                strncpy(Fault_Name,"GFCI 泄露2",10);//GFCI leakage fault 2.
            } 
            break;      
        case SYS_FAULT_GFCIErrLv1: 
            { 
                strncpy(Fault_Name,"GFCI 泄露1",10);//GFCI leakage fault 3.
            } 
            break;      
        case SYS_FAULT_SWSelfLock:
            { 
                strncpy(Fault_Name,"SW 自锁   ",10);//Software self-locking fault.
            } 
            break;      
        case SYS_FAULT_SysOT:
            {  
                strncpy(Fault_Name,"Sys 过温  ",10);//System over-temperature fault.
            } 
            break;      
        case SYS_FAULT_SysOL: 
            { 
                strncpy(Fault_Name,"Sys 过载  ",10);//System overload fault.
            } 
            break;      
        case SYS_FAULT_Epo:
            { 
                strncpy(Fault_Name,"紧急断电  ",10);//Emergency Power Off
            } 
            break;      
        case SYS_FAULT_SlaveCpuErr:
            { 
                strncpy(Fault_Name,"备CPU错误 ",10);//Slave CPU Error
            } 
            break;      
        case SYS_FAULT_IsoErr:
            { 
                strncpy(Fault_Name,"辅电源故障",10);//Auxiliary power source fault.
            } 
            break;      
        case SYS_FAULT_BusBoardBrkProt:
            { 
                strncpy(Fault_Name,"母线断保护",10);//Busbar disconnect protection fault.   母线断开保护故障。
            } 
            break;      
        case SYS_FAULT_GroundProt:
            { 
                strncpy(Fault_Name,"接地保护  ",10);//Ground protection fault.
            } 
            break;      
        case INV_FAULT_Grid10MinOV:
            { 
                strncpy(Fault_Name,"电网过电压",10);//Grid overvoltage fault (10 mins).
            } 
            break;      
        case INV_FAULT_GridOVLv2: 
            { 
                strncpy(Fault_Name,"Gd过压快检",10);//grid over voltage fast detection.
            } 
            break;      
        case INV_FAULT_GridOVLv1:
            { 
                strncpy(Fault_Name,"Gd过压慢检",10);//grid over voltage slow detection.
            } 
            break;      
        case INV_FAULT_GridUVLv3:
            { 
                strncpy(Fault_Name,"Gd欠压L3  ",10);//Grid undervoltage fault (level 3).
            } 
            break;      
        case INV_FAULT_GridUVLv2:
            { 
                strncpy(Fault_Name,"Gd欠压L2  ",10);//Grid undervoltage fault (level 2).
            } 
            break;      
        case INV_FAULT_GridUVLv1: 
            { 
                strncpy(Fault_Name,"Gd欠压L1  ",10);//Grid undervoltage fault (level 1).
            } 
            break;      
        case INV_FAULT_GridFastOverFreq:
            { 
                strncpy(Fault_Name,"Gd过频快检",10);//Grid overfrequency fast detection.
            } 
            break;      
        case INV_FAULT_GridSlowOverFreq:
            { 
                strncpy(Fault_Name,"Gd过频慢检",10);//Grid overfrequency slow detection.
            } 
            break;      
        case INV_FAULT_GridFastUnderFreq:
            { 
                strncpy(Fault_Name,"Gd欠频快检",10);//Grid underfrequency fast detection.
            } 
            break;      
        case INV_FAULT_GridSlowUnderFreq:
            { 
                strncpy(Fault_Name,"Gd欠频慢检",10);//Grid underfrequency slow detection.
            } 
            break;      
        case INV_FAULT_GridFastPowerDown:
            { 
                strncpy(Fault_Name,"Gd掉电快检",10);//Grid power outage fast fault.
            } 
            break;      
        case INV_FAULT_PllErr: 
            { 
                strncpy(Fault_Name,"锁相异常  ",10);
            } 
            break;      
        case INV_FAULT_SysLNReverse:
            { 
                strncpy(Fault_Name,"LN反接故障",10);//System LN reverse connection fault.
            } 
            break;        
        case INV_FAULT_FwFastOC1:
            { 
                strncpy(Fault_Name,"软过流快1 ",10);//Software overcurrent fast detection fault 1. 软件过流快检1故障
            } 
            break;      
        case INV_FAULT_HwOV1:
            { 
                strncpy(Fault_Name,"硬件过流1",10);//Hardware overcurrent  fault 1.
            } 
            break;      
        case INV_FAULT_FwSlowOC1:
            { 
                strncpy(Fault_Name,"软过流慢1 ",10);//Software overcurrent slow detection fault 1.
            } 
            break;      
        case INV_FAULT_InvRlyErr1:
            { 
                strncpy(Fault_Name,"逆变relay1",10);//Inverter relay fault 1.
            } 
            break;      
        case INV_FAULT_OTP1:
            { 
                strncpy(Fault_Name,"过温故障1 ",10);//Inverter overtemperature fault 1.
            } 
            break;      
        case INV_FAULT_OVP1:
            { 
                strncpy(Fault_Name,"过压故障1 ",10);//Inverter Overvoltage fault 1.
            } 
            break;      
        case INV_FAULT_IgbtErr1:
            { 
                strncpy(Fault_Name,"IGBT故障1 ",10);//Inverter IGBT fault 1.
            } 
            break;      
        case INV_FAULT_InductanceOT1:
            { 
                strncpy(Fault_Name,"电感过温1 ",10);//Inductor overtemperature 1.
            } 
            break;      
        case INV_FAULT_VoltDcComponentErr1:
            { 
                strncpy(Fault_Name,"电压直流1 ",10);//DC voltage component fault 1.
            } 
            break;      
        case INV_FAULT_CurrDcComponentErr1:
            { 
                strncpy(Fault_Name,"电流直流1 ",10);//DC Current component fault 1.
            } 
            break;      
        case INV_FAULT_CT_DisConnect:
            { 
                strncpy(Fault_Name,"软件流快2 ",10);//Software overcurrent fast detection fault 2.
            } 
            break;      
        case INV_FAULT_Meter_DisConnect: 
            { 
                strncpy(Fault_Name,"硬件过流2 ",10);//Hardware overcurrent  fault 2.
            } 
            break;      
        case INV_FAULT_FwSlowOC2:
            { 
                strncpy(Fault_Name,"软过流慢2 ",10);//Software overcurrent slow detection fault 2.
            } 
            break;      
        case INV_FAULT_InvRlyErr2: 
            { 
                strncpy(Fault_Name,"逆变relay2",10);//Inverter relay fault 2.逆变器继电器故障2
            } 
            break;      
        case INV_FAULT_OTP2: 
            { 
                strncpy(Fault_Name,"过温故障2 ",10);//Inverter overtemperature fault 2.
            } 
            break;      
        case INV_FAULT_OVP2: 
            { 
                strncpy(Fault_Name,"过压故障2 ",10);//Inverter Overvoltage fault 2.
            } 
            break;      
        case INV_FAULT_IgbtErr2:
            { 
                strncpy(Fault_Name,"IGBT故障2 ",10);//Inverter IGBT fault 2.
            } 
            break;      
        case INV_FAULT_InductanceOT2:
            { 
                strncpy(Fault_Name,"电感过温2 ",10);//Inductor overtemperature 2.
            } 
            break;      
        case INV_FAULT_VoltDcComponentErr2:
            { 
                strncpy(Fault_Name,"电压直流2 ",10);//DC voltage component fault 2.
            } 
            break;      
        case INV_FAULT_CurrDcComponentErr2:
            { 
                strncpy(Fault_Name,"电流直流2 ",10);//DC Current component fault 2.
            } 
            break;      
        case INV_FAULT_ParallelCanErr:
            { 
                strncpy(Fault_Name,"并机CAN   ",10);//Parallel operation CAN communication fault.
            } 
            break;      
        case INV_FAULT_ParaCurrShareErr:
            { 
                strncpy(Fault_Name,"并机均流  ",10);//Parallel operation current sharing fault.
            } 
            break;
        case INV_FAULT_IslandErr:
            { 
                strncpy(Fault_Name,"孤岛故障  ",10);//Island fault.
            } 
            break;
        case DCDC_FAULT_MidBusOVP:
            { 
                strncpy(Fault_Name,"中间过压  ",10);//Intermediate fault overvoltage protection fault.
            } 
            break;      
        case DCDC_FAULT_LLCHwOC:
            { 
                strncpy(Fault_Name,"LLC 硬过流",10);//LLC hardware overcurrent fault.
            } 
            break;      
        case DCDC_FAULT_BuckBoostHwOC:
            { 
                strncpy(Fault_Name,"BB硬件过流",10);//BuckBoost hardware overcurrent fault.
            } 
            break;      
        case DCDC_FAULT_BuckBoostSwOC:
            { 
                strncpy(Fault_Name,"BB软件过流",10);//BuckBoost software overcurrent fault.
            } 
            break;      
        case DCDC_FAULT_SOPChgOCP: 
            { 
                strncpy(Fault_Name,"SOP充过流 ",10);//SOP charging overcurrent protection fault.
            } 
            break;      
        case DCDC_FAULT_SOPDisChgOCP:
            { 
                strncpy(Fault_Name,"SOP放过流 ",10);//SOP discharging overcurrent protection fault.
            } 
            break;      
        case DCDC_FAULT_DCDCOverTemp:
            { 
                strncpy(Fault_Name,"DCDC过温  ",10);//DCDC overtemperature protection fault.
            } 
            break;      
        case PV1_FAULT_PvUV:
            { 
                strncpy(Fault_Name,"PV1 欠压  ",10);//PV 1 undervoltage.
            } 
            break;      
        case PV1_FAULT_PvOV:
            { 
                strncpy(Fault_Name,"PV1 过压  ",10);//PV 1 overvoltage.
            } 
            break;      
        case PV1_FAULT_PVIso:
            { 
                strncpy(Fault_Name,"PV1 ISO   ",10);//PV 1 ISO fault.
            } 
            break;      
        case PV1_FAULT_SWOC:
            { 
                strncpy(Fault_Name,"PV1 软过流",10);//PV 1 software overcurrent fault.
            } 
            break;      
        case PV1_FAULT_HWOC:
            { 
                strncpy(Fault_Name,"PV1 硬过流",10);//PV 1 hardware overcurrent fault.
            } 
            break;      
        case PV1_FAULT_LPLK:
            { 
                strncpy(Fault_Name,"1 低功锁定",10);//PV 1 Low Power Lock fault.
            } 
            break;      
        case PV2_FAULT_PvUV:
            { 
                strncpy(Fault_Name,"PV2 欠压  ",10);//PV 2 undervoltage
            } 
            break;      
        case PV2_FAULT_PvOV:
            { 
                strncpy(Fault_Name,"PV2 过压  ",10);//PV 2 overvoltage.
            } 
            break;      
        case PV2_FAULT_PVIso: 
            { 
                strncpy(Fault_Name,"PV2 ISO   ",10);//PV 2 ISO fault.
            } 
            break;      
        case PV2_FAULT_SWOC:
            { 
                strncpy(Fault_Name,"PV2 软过流",10);//PV 2 software overcurrent fault.
            } 
            break;      
        case PV2_FAULT_HWOC:
            { 
                strncpy(Fault_Name,"PV2 硬过流",10);//PV 2 hardware overcurrent fault.
            } 
            break;      
        case PV2_FAULT_LPLK:
            { 
                strncpy(Fault_Name,"2 低功锁定",10);//PV 2 Low Power Lock fault.
            } 
            break;      
        case BMS_ALERM_SingleVoltDiff:
            { 
                strncpy(Fault_Name,"单芯电压  ",10);//Single-cell voltage consistency alarm.
            } 
            break;      
        case BMS_ALERM_MosfetOT:
            { 
                strncpy(Fault_Name,"MOSFET高温",10);//MOSFET overtemperature alarm.
            } 
            break;      
        case BMS_ALERM_SingleUT:
            { 
                strncpy(Fault_Name,"单芯低温  ",10);//Single-cell under temperature alarm.
            } 
            break;      
        case BMS_ALERM_SingleOT: 
            { 
                strncpy(Fault_Name,"单芯高温  ",10);//Single-cell over temperature alarm.
            } 
            break;      
        case BMS_ALERM_SingleVoltUV:
            { 
                strncpy(Fault_Name,"单芯低压  ",10);//Single-cell under voltage alarm.
            } 
            break;        
        case BMS_ALERM_SingleVoltOV:
            { 
                strncpy(Fault_Name,"单芯高压  ",10);//Single-cell over voltage alarm.
            } 
            break;        
        case BMS_ALERM_TotalVoltUV:
            { 
                strncpy(Fault_Name,"模块低压  ",10);//Module total voltage under voltage alarm.
            } 
            break;      
        case BMS_ALERM_TotalVoltOV:
            { 
                strncpy(Fault_Name,"模块高压  ",10);//Module total voltage over voltage alarm.
            } 
            break;      
        case BMS_ALERM_InternalComErr:
            { 
                strncpy(Fault_Name,"内部通信  ",10);//Internal communication error alarm
            } 
            break;      
        case BMS_ALERM_OCD:
            { 
                strncpy(Fault_Name,"放电过流  ",10);//Discharge overcurrent alarm
            } 
            break;      
        case BMS_ALERM_OCC:
            { 
                strncpy(Fault_Name,"充电过流  ",10);//charge overcurrent alarm
            } 
            break;      
        case BMS_ALERM_SingleTempDiff:
            { 
                strncpy(Fault_Name,"单芯温度  ",10);//Single-cell temperature consistency alarm. 
            } 
            break;      
        case BMS_FAULT_MosfetOT:
            { 
                strncpy(Fault_Name,"MOSFET过温",10);//MOSFET overtemperature alarm.
            } 
            break;      
        case BMS_FAULT_SingleUT:
            { 
                strncpy(Fault_Name,"单芯欠温  ",10);//Single-cell undertemperature  fault.
            } 
            break;      
        case BMS_FAULT_SingleOT:
            { 
                strncpy(Fault_Name,"单芯过温  ",10);//Single-cell overtemperature  fault.
            } 
            break;      
        case BMS_FAULT_SingleUV:
            { 
                strncpy(Fault_Name,"单芯欠压  ",10);//Single-cell undervoltage  fault.
            } 
            break;      
        case BMS_FAULT_SingleOV:
            { 
                strncpy(Fault_Name,"单芯过压  ",10);//Single-cell overvoltage  fault.
            } 
            break;      
        case BMS_FAULT_TotalModeUV:
            { 
                strncpy(Fault_Name,"模块欠压  ",10);//Module total voltage under voltage fault.
            } 
            break;        
        case BMS_FAULT_TotalModeOV:
            { 
                strncpy(Fault_Name,"模块过压  ",10);//Module total voltage over voltage fault.
            } 
            break;      
        case BMS_FAULT_SysFault:
            { 
                strncpy(Fault_Name,"系统保护  ",10);//System  protection fault.
            } 
            break;      
        case BMS_FAULT_OCD:
            { 
                strncpy(Fault_Name,"放电过流  ",10);//Discharge overcurrent fault.
            } 
            break;      
        case BMS_FAULT_OCC:
            { 
                strncpy(Fault_Name,"充电过流  ",10);//charge overcurrent fault.
            } 
            break;
        case EMS_FAULT_PCS:
            { 
                strncpy(Fault_Name,"PCS通信   ",10);//PCS Communication fault.
            } 
            break;      
        case EMS_FAULT_METER:
            { 
                strncpy(Fault_Name,"电表通信  ",10);//Meter Communication fault.
            } 
            break;      
        case EMS_FAULT_BMS:
            { 
                strncpy(Fault_Name,"BMS通信   ",10);//Bms Communication fault.
            } 
            break;      
        case EMS_FAULT_CT:
            { 
                strncpy(Fault_Name,"CT通信    ",10);//CT Communication fault.
            } 
            break;     
        default:
            {
                strncpy(Fault_Name,"未定义    ",10);
            }
            break;
    }
}

/***************************************************************************
 功能:中文 操作记录显示组装界面
****************************************************************************/
void updateDisplayOperationRecordData_Chinese(uint8_t u8CurrentPage)
{   
    memset(tab_display,0,DISPLAY_CACHE_SIZE);
    Record_Info * pStRecord = Display_Get_OperationRecordData();
    
    if(pStRecord->u8RecordIndex == 0) 
    {
        sprintf(tab_display,"                \n                \n   无操作记录   \n                \n");
        GUI_Display(tab_display, 0, 0);
        return;
    }
    
    uint8_t u8TempCode  = pStRecord->stRecord[u8CurrentPage].u16RecordType;
    char tab_Operate_Name[DISPLAY_DATA_NAME_CACHE_SIZE-5];  //Display显示缓存
    memset(tab_Operate_Name,0,DISPLAY_DATA_NAME_CACHE_SIZE-5);
    getOperateNameByOperateCode_Chinese(tab_Operate_Name,u8TempCode); //根据故障码获取故障名称
    
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
    char tab_OperateObj_Name[DISPLAY_DATA_NAME_CACHE_SIZE-5];  //Display显示缓存
    memset(tab_OperateObj_Name,0,DISPLAY_DATA_NAME_CACHE_SIZE-5);
    getOperatObjeNameByOperateObjCode_Chinese(tab_OperateObj_Name,u8TempObj);
    
    sprintf(tab_display,"   操作记录 %02d  \n类型:%-11s\n发生:%-10s \nObj:%-11s\n",u8CurrentPage+1,tab_Operate_Name,tab_Time_Operate+5,tab_OperateObj_Name);  //O=Operate Time 操作时间
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);
    GUI_Display(tab_display, 0, 0);
}

/***************************************************************************
 功能:根据操作类型码获取操作名称
****************************************************************************/
void getOperateNameByOperateCode_Chinese(char* Operate_Name,uint8_t u8Code)
{

    switch(u8Code)
    {
        case RECORD_SET_Language:
            { 
                strncpy(Operate_Name,"语言设置  ",10);
            }
            break;
        case RECORD_SET_Time:
            { 
                strncpy(Operate_Name,"时间设置  ",10);
            }
            break;
        case RECORD_SET_Password:
            {
                strncpy(Operate_Name,"密码设置  ",10);
            }
            break;
        case RECORD_SET_ClearFault:
            { 
                strncpy(Operate_Name,"清除故障  ",10);
            }
            break;
        case RECORD_SET_ClearRecord:
            {
                strncpy(Operate_Name,"清除记录  ",10);
            }
            break;
         case RECORD_SET_Serial:
            {
                strncpy(Operate_Name,"串口设置  ",10);
            }
            break;
         case RECORD_SET_Factory:
            {
                strncpy(Operate_Name,"出厂设置  ",10);
            }
            break;
         case RECORD_SET_WIFI_RESET:
            {
                strncpy(Operate_Name,"无线复位  ",10);
            }
            break;
         case RECORD_SET_BLT_RESET:
            {
                strncpy(Operate_Name,"蓝牙复位  ",10);
            }
            break;
         case RECORD_SET_Local_Control:
            {
                strncpy(Operate_Name,"本地控制  ",10);
            }
            break;
         case RECORD_SET_Remote_Control:
            {
                strncpy(Operate_Name,"远程控制  ",10);
            }
            break;  
         case RECORD_SET_STRATEGY_SELFUSE:
            {
                strncpy(Operate_Name,"自发自用  ",10);
            }
            break;
         case RECORD_SET_TPFV_TIP_PERIOD_ONE:
            {
                strncpy(Operate_Name,"策略尖段 1",10);
            }
            break;
         case RECORD_SET_TPFV_TIP_PERIOD_TWO:
            {
                strncpy(Operate_Name,"策略尖段 2",10);
            }
            break;
         case RECORD_SET_TPFV_TIP_PERIOD_THREE:
            {
                strncpy(Operate_Name,"策略尖段 3",10);
            }
            break;
         case RECORD_SET_TPFV_PEAK_PERIOD_ONE:
            {
                strncpy(Operate_Name,"策略峰段 1",10);
            }
            break;
         case RECORD_SET_TPFV_PEAK_PERIOD_TWO:
            {
                strncpy(Operate_Name,"策略峰段 2",10);
            }
            break;
         case RECORD_SET_TPFV_PEAK_PERIOD_THREE:
            {
                strncpy(Operate_Name,"策略峰段 3",10);
            }
            break;
         case RECORD_SET_TPFV_FLAT_PERIOD_ONE:
            {
                strncpy(Operate_Name,"策略平段 1",10);
            }
            break;
         case RECORD_SET_TPFV_FLAT_PERIOD_TWO:
            {
                strncpy(Operate_Name,"策略平段 2",10);
            }
            break;
         case RECORD_SET_TPFV_FLAT_PERIOD_THREE:
            {
                strncpy(Operate_Name,"策略平段 3",10);
            }
            break;
         case RECORD_SET_TPFV_VALLEY_PERIOD_ONE:
            {
                strncpy(Operate_Name,"策略谷段 1",10);
            }
            break;
         case RECORD_SET_TPFV_VALLEY_PERIOD_TWO:
            {
                strncpy(Operate_Name,"策略谷段 2",10);
            }
            break;
         case RECORD_SET_TPFV_VALLEY_PERIOD_THREE:
            {
                strncpy(Operate_Name,"策略谷段 3",10);
            }
            break;
         case RECORD_SET_CHARGE_ONE:
            {
                strncpy(Operate_Name,"充电 1    ",10);
            }
            break;
         case RECORD_SET_CHARGE_TWO:
            {
                strncpy(Operate_Name,"充电 2    ",10);
            }
            break;
         case RECORD_SET_CHARGE_THREE:
            {
                strncpy(Operate_Name,"充电 3    ",10);
            }
            break;
         case RECORD_SET_CHARGE_FOUR:
            {
                strncpy(Operate_Name,"充电 4    ",10);
            }
            break;
         case RECORD_SET_DISCHARGE_ONE:
            {
                strncpy(Operate_Name,"放电 1    ",10);
            }
            break;
         case RECORD_SET_DISCHARGE_TWO:
            {
                strncpy(Operate_Name,"放电 2    ",10);
            }
            break;
         case RECORD_SET_DISCHARGE_THREE:
            {
                strncpy(Operate_Name,"放电 3    ",10);
            }
            break;
         case RECORD_SET_DISCHARGE_FOUR:
            {
                strncpy(Operate_Name,"放电 4    ",10);
            }
            break;
         case RECORD_SET_STRATEGY_BACKUP:
            {
                strncpy(Operate_Name,"备电策略  ",10);
            }
            break;
         case RECORD_SET_STRATEGY_GEN:
            {
                strncpy(Operate_Name,"发电机策略",10);
            }
            break;
         case RECORD_SET_SYSTEM_DETECTION:
            {
                strncpy(Operate_Name,"检测设置  ",10);
            }
            break;
         case RECORD_SET_PROTECT_ISLAND:
            {
                strncpy(Operate_Name,"孤岛保护  ",10);
            }
            break;
         case RECORD_SET_PROTECT_GROUND:
            {
                strncpy(Operate_Name,"接地保护  ",10);
            }
            break;
         case RECORD_SET_PROTECT_LEAKAG:
            {
                strncpy(Operate_Name,"漏电保护  ",10);
            }
            break;
         case RECORD_SET_PROTECT_ARC:
            {
                strncpy(Operate_Name,"拉弧保护  ",10);
            }
            break;
         case RECORD_SET_PROTECT_LVRT:
            {
                strncpy(Operate_Name,"低电压穿越",10);
            }
            break;
         case RECORD_SET_PROTECT_HVRT:
            {
                strncpy(Operate_Name,"高电压穿越",10);
            }
            break;
         case RECORD_SET_PROTECT_LIGHT:
            {
                strncpy(Operate_Name,"防雷保护  ",10);
            }
            break;
         case RECORD_SET_PROTECT_GEN:
            {
                strncpy(Operate_Name,"发电机保护",10);
            }
            break;
         case RECORD_SET_PROTECT_LFRT:
            {
                strncpy(Operate_Name,"低频率穿越",10);
            }
            break;
         case RECORD_SET_PROTECT_HFRT:
            {
                strncpy(Operate_Name,"高频率穿越",10);
            }
            break;
         case RECORD_SET_PROTECT_P_V:
            {
                strncpy(Operate_Name,"P(V)保护  ",10);
            }
            break;
         case RECORD_SET_PROTECT_P_F:
            {
                strncpy(Operate_Name,"P(F)保护  ",10);
            }
            break;
         case RECORD_SET_PROTECT_Q_V:
            {
                strncpy(Operate_Name,"Q(V)保护  ",10);
            }
            break;
         case RECORD_SET_PROTECT_Q_P:
            {
                strncpy(Operate_Name,"Q(P)保护  ",10);
            }
            break;
         case RECORD_SET_PROTECT_CPF:
            {
                strncpy(Operate_Name,"CPF保护   ",10);
            }
            break;
         case RECORD_SET_PROTECT_CQ:
            {
                strncpy(Operate_Name,"CQ保护使能",10);
            }
            break;
         case RECORD_SET_PV_CONTROLWAY:
            {
                strncpy(Operate_Name,"光伏控制  ",10);
            }
            break;
         case RECORD_SET_PV_SCAN:
            {
                strncpy(Operate_Name,"光伏IV扫描",10);
            }
            break;
         case RECORD_SET_BATTERY_ENABLE:
            {
                strncpy(Operate_Name,"电池使能  ",10);
            }
            break;
         case RECORD_SET_BATTERY_WAKEUP:
            {
                strncpy(Operate_Name,"电池唤醒  ",10);
            }
            break;
         case RECORD_SET_BATTERY_MANUFACT:
            {
                strncpy(Operate_Name,"电池厂商  ",10);
            }
            break;
         case RECORD_SET_BATTERY_TYPE:
            {
                strncpy(Operate_Name,"电池类型  ",10);
            }
            break;
         case RECORD_SET_SELL:
            {
                strncpy(Operate_Name,"电网卖电  ",10);
            }
            break;
         case RECORD_SET_GRID_METER:
            {
                strncpy(Operate_Name,"电表设置  ",10);
            }
            break;
         case RECORD_SET_GRID_SR:
            {
                strncpy(Operate_Name,"安规设置  ",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_TIP:
            {
                strncpy(Operate_Name,"尖时电价  ",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_TIP_PERIOD_ONE:
            {
                strncpy(Operate_Name,"电价尖时 1",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_TIP_PERIOD_TWO:
            {
                strncpy(Operate_Name,"电价尖时 2",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_TIP_PERIOD_THREE:
            {
                strncpy(Operate_Name,"电价尖时 3",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_PEAK:
            {
                strncpy(Operate_Name,"峰时电价  ",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_PEAK_PERIOD_ONE:
            {
                strncpy(Operate_Name,"电价峰时 1",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_PEAK_PERIOD_TWO:
            {
                strncpy(Operate_Name,"电价峰时 2",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_PEAK_PERIOD_THREE:
            {
                strncpy(Operate_Name,"电价峰时 3",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_FLAT:
            {
                strncpy(Operate_Name,"平时电价  ",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_FLAT_PERIOD_ONE:
            {
                strncpy(Operate_Name,"电价平时 1",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_FLAT_PERIOD_TWO:
            {
                strncpy(Operate_Name,"电价平时 2",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_FLAT_PERIOD_THREE:
            {
                strncpy(Operate_Name,"电价平时 3",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_VALLEY:
            {
                strncpy(Operate_Name,"谷时电价  ",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_VALLEY_PERIOD_ONE:
            {
                strncpy(Operate_Name,"电价谷时 1",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_VALLEY_PERIOD_TWO:
            {
                strncpy(Operate_Name,"电价谷时 2",10);
            }
            break;
         case RECORD_SET_GRID_TIMEDIVEPRICE_TPFV_VALLEY_PERIOD_THREE:
            {
                strncpy(Operate_Name,"电价谷时 3",10);
            }
            break;
         case RECORD_SET_GRID_REACTIVEPOWERCONTROLWAY:
            {
                strncpy(Operate_Name,"无功控制  ",10);
            }
            break;
         case RECORD_SET_GRID_REACTIVEPOWER:
            {
                strncpy(Operate_Name,"无功功率  ",10);
            }
            break;
         case RECORD_SET_GRID_POWERFACTOR:
            {
                strncpy(Operate_Name,"功率因数  ",10);
            }
            break;
         case RECORD_SET_GEN:
            {
                strncpy(Operate_Name,"发电机设置",10);
            }
            break;   
        default:
            {
                strncpy(Operate_Name,"未定义    ",10);
            }
            break;
    }
}


/***************************************************************************
 功能:根据操作对象码获取操作对象名称名称
****************************************************************************/
void getOperatObjeNameByOperateObjCode_Chinese(char* OperateObj_Name,uint8_t u8Code)
{
    switch(u8Code) 
    {
        case OPERATE_OBJ_LOCAL_EMS:
            { 
                strncpy(OperateObj_Name,"本地EMS   ",10);
            }
            break;
        case OPERATE_OBJ_REMOTE_EMS:
            { 
                strncpy(OperateObj_Name,"远端EMS   ",10);
            }
            break;
        case OPERATE_OBJ_UPPER_COMPUTER:
            { 
                strncpy(OperateObj_Name,"上位机    ",10);
            }
            break;
        default:
            {
                strncpy(OperateObj_Name,"未定义    ",10);
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
        sprintf(tab_display,"                \n                \n   无操作记录   \n                \n");
        GUI_Display(tab_display, 0, 0);
        return;
    }
    
    uint8_t u8TempCode  = pStRecord->stRecord[u8CurrentPage].u16RecordType;
    char tab_Operate_Name[DISPLAY_DATA_NAME_CACHE_SIZE-5];  //Display显示缓存
    memset(tab_Operate_Name,0,DISPLAY_DATA_NAME_CACHE_SIZE-5);
    getOperateNameByOperateCode(tab_Operate_Name,u8TempCode); //根据故障码获取故障名称
    
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
    char tab_OperateObj_Name[DISPLAY_DATA_NAME_CACHE_SIZE-5];  //Display显示缓存
    memset(tab_OperateObj_Name,0,DISPLAY_DATA_NAME_CACHE_SIZE-5);
    getOperatObjeNameByOperateObjCode(tab_OperateObj_Name,u8TempObj);
    
    sprintf(tab_display,"   操作记录 %02d  \n类型:%-11s\n发生: %-10s\nObj:%-11s\n",u8CurrentPage+1,tab_Operate_Name,tab_Time_Operate+5,tab_OperateObj_Name);  //O=Operate Time 操作时间
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);
    GUI_Display(tab_display, 0, 0);

}
#endif
/***************************************************************************
 功能:中文 历史故障告警组装界面
****************************************************************************/
void updateDisplayHistoryFaultData_Chinese(uint8_t u8CurrentPage)
{
    Fault_Info_History * pStHistory = Display_Get_HistoryFaultData();
    memset(tab_display,0,DISPLAY_CACHE_SIZE);

    if(pStHistory->u8HistoryFaultIndex == 0) 
    {
        sprintf(tab_display,"                \n                \n   无历史故障   \n                \n");
        GUI_Display(tab_display, 0, 0);
        return;
    }

    uint16_t u16TempCode  = pStHistory->stHistoryFault[u8CurrentPage].u16FaultCode;
    char tab_Fault_Name[DISPLAY_DATA_NAME_CACHE_SIZE-5];  //Display显示缓存
    memset(tab_Fault_Name,0,DISPLAY_DATA_NAME_CACHE_SIZE-5);
    getFaultNameByFaultCode_Chinese(tab_Fault_Name,u16TempCode); //根据故障码获取故障名称
    
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
    
    sprintf(tab_display,"   历史故障 %02d  \n%04x:%11s\n发生:%10s \n清除:%10s\n",u8CurrentPage+1,u16TempCode,tab_Fault_Name,tab_Time_Occur+5,tab_Time_Clear+5);  //O=Occur 故障产生时间  C=clear 故障清楚时间
    //GUI_DispStringAt((uint8_t*)tab_display, 0, 0);
    GUI_Display(tab_display, 0, 0);
}

#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

