/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : LCD_Device.h 
 用途 : LCD设备驱动头文件
***********************************************************************************************************************/
#ifndef _LcdDriver_H
#define _LcdDriver_H

#include"HeadFile.h"

#define LCD_COLUMN_SIZE                             (128)       //LCD最多128点阵列
#define LCD_ROW_SIZE                                (  8)       //LCD最多8行，每行8个点阵列

#define DISPLAY_ON                                  (  1)       //显示开启
#define DISPLAY_OFF                                 (  0)       //显示关闭

#define Ks0108_CMD_Disp_ON                          (0x3F)      //显示开关控制指令
#define Ks0108_CMD_Disp_OFF                         (0x3E)
#define Ks0108_CMD_Set_Addr                         (0x40)      //列点阵的地址定位控制指令
#define Ks0108_CMD_Set_Page                         (0xB8)      //行点阵的地址定位控制指令
#define Ks0108_CMD_Disp_Start_Line                  (0xC0)      //起始行控制指令

//显示模式
#define GUI_TEXTMODE_NORMAL                         (0)
#define GUI_TEXTMODE_REVERSE                        (1<<0)
#define GUI_TEXTMODE_UNDERLINE                      (1<<1)
//对齐方式
#define GUI_TA_LEFT                                 (0<<4)
#define GUI_TA_HCENTER                              (1<<4)
#define GUI_TA_RIGHT                                (2<<4)
#define GUI_JUST_TEXT                               (1<<7)

//英文的两种字体
#define En_8x16                                     (0)
#define En_5x8                                      (1)

//字体宽度定义
#define En_8x16_Column_SIZE                         (8)
#define En_8x16_Row_SIZE                            (2)
#define En_8x16_CharacterSpace_SIZE                 (0)
#define En_5x8_Column_SIZE                          (5)
#define En_5x8_Row_SIZE                             (2)
#define En_5x8_CharacterSpace_SIZE                  (1)

//一行显示字符数
#define En_ROW_SIZE                                 (21)
#define CH_ROW_SIZE                                 (16)

#define UNDELINE_BLINK_SPEED                        (8)
//英文字体宽度定义
extern uint8_t u8ColumnSizeOfChar;
extern uint8_t u8RowSizeOfChar;
extern uint8_t gu8CharacterSpace;
extern uint8_t gu8SingleRowSize;


extern uint8_t gu8ColumnSizeOfChar;   

//中文字体宽度定义
#define Chinese_Column_SIZE  16
#define Chinese_Row_SIZE  2

extern uint8_t GetSingleRowSize(void);
extern void SetSingleRowSize(uint8_t u8Size);
extern uint8_t GUI_SetTextMode(uint8_t TextMode);
extern void GUI_SetEnFont(uint8_t EnFont);
extern void GUI_DispCharAt(uint8_t u8Char, uint8_t u8Column, uint8_t u8Row);
extern void GUI_Init(void);
extern void LCD_Device_KS0108_6800_InitVar(void);
extern void GUI_Clear(void);
extern void GUI_DispStringAt(uint8_t const *pStr,uint8_t u8Column,uint8_t u8Row);
extern void GUI_DrawIcon(uint8_t      const *pu8Icon, uint8_t u8Column, uint8_t u8Row);
extern void GUI_DrawIcon16X16(uint8_t        const *pu8Icon, uint8_t u8Column, uint8_t u8Row);
extern void GUI_DispDecAt(uint16_t u16DecimalData, uint16_t u8Column, uint16_t u8Row, uint8_t u8Length);
extern void GUI_DispHexAt(uint32_t u16DecimalData, uint8_t u8Column, uint8_t u8Row, uint8_t u8Length);
extern void HBar(uint8_t u8Row, uint8_t u8StartColumn, uint8_t u8EndColumn,uint8_t u8Percent);
extern void TipDisp( uint8_t u8StartColumn, uint8_t u8StartRow, uint8_t u8EndColumn, uint8_t u8EndRow);
extern void TipClr( uint8_t u8StartColumn, uint8_t u8StartRow, uint8_t u8EndColumn, uint8_t u8EndRow);
extern void Display_Number(uint16_t u16Number, uint8_t u8Column, uint8_t u8Row, uint8_t u8Length);
extern void Display_SignedNumber(int s16Number,uint8_t u8Column,uint16_t u8Row,uint8_t u8Length);
extern void Display_Decimal(unsigned long int u32Number, char u8Column, uint16_t u8Row, uint8_t u8INT, uint8_t u8DEC);
extern void Display_SignedDecimal(long int s32Number, char u8Column, uint16_t u8Row, uint8_t u8INT, uint8_t u8DEC);
extern void Display_Set_UnderLine_Blink_Position(uint8_t u8Enable, uint8_t u8StartPosition, uint8_t u8EndPosition);
extern void GUI_Display(char *pStr, uint8_t u8Column, uint8_t u8Row);
extern void GUI_LCD_ON(void);
extern void GUI_LCD_OFF(void);
#if LCD_ATE_TEST
extern void Display_Ate_Test(void);
#endif


#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

