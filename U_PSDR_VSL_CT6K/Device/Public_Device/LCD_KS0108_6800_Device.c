/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : LCD_Device.c 
 用途 : LCD显示设备驱动
***********************************************************************************************************************/
#ifndef __LCD_KS0108__6800_DEVICE_C__
#define __LCD_KS0108__6800_DEVICE_C__

#include "LCD_KS0108_6800_Device.h"
#include "Chinese.h"
#include "ASCII.h"

#if LCD_DEVICE_KS0108_6800_MOUDLE

//液晶控制线
#define LCD_Bus(Data)   {GPIO_Driver_WriteOutputPin(DEV_LCD_DB_PORT,(Data << DEV_LCD_KS0108_D0_Pos),PR_GPIO_PIN_SET); \
                         Data ^= 0xFF; \
                         GPIO_Driver_WriteOutputPin(DEV_LCD_DB_PORT,(Data << DEV_LCD_KS0108_D0_Pos),PR_GPIO_PIN_RESET);} //设定6800并口协议的数据总线

/***********************************************************************************************************************
这部分由于硬件需要改版，高低电平、左半屏是哪个信号还没定，需要改版后再次对照硬件修改
***********************************************************************************************************************/
#define LCD_CS1_H()     {   GPIO_Driver_WriteOutputPin(DEV_LCD_CS1_PORT,DEV_LCD_CS1_PIN,GPIO_PIN_SET) ;  }
#define LCD_CS1_L()     {   GPIO_Driver_WriteOutputPin(DEV_LCD_CS1_PORT,DEV_LCD_CS1_PIN,GPIO_PIN_RESET) ;  }
#define LCD_CS2_H()     {   GPIO_Driver_WriteOutputPin(DEV_LCD_CS2_PORT,DEV_LCD_CS2_PIN,GPIO_PIN_SET) ;  }
#define LCD_CS2_L()     {   GPIO_Driver_WriteOutputPin(DEV_LCD_CS2_PORT,DEV_LCD_CS2_PIN,GPIO_PIN_RESET) ;  }
#define LCD_RS_H()      {   GPIO_Driver_WriteOutputPin(DEV_LCD_RS_PORT,DEV_LCD_KS0108_RS_PIN,GPIO_PIN_SET) ; }
#define LCD_RS_L()      {   GPIO_Driver_WriteOutputPin(DEV_LCD_RS_PORT,DEV_LCD_KS0108_RS_PIN,GPIO_PIN_RESET) ; }
#define LCD_RW_H()      {   GPIO_Driver_WriteOutputPin(DEV_LCD_RW_PORT,DEV_LCD_KS0108_RW_PIN,GPIO_PIN_SET) ; }
#define LCD_RW_L()      {   GPIO_Driver_WriteOutputPin(DEV_LCD_RW_PORT,DEV_LCD_KS0108_RW_PIN,GPIO_PIN_RESET) ; }
#define LCD_E_H()       {   GPIO_Driver_WriteOutputPin(DEV_LCD_EN_PORT,DEV_LCD_EN_PIN,GPIO_PIN_SET) ; }
#define LCD_E_L()       {   GPIO_Driver_WriteOutputPin(DEV_LCD_EN_PORT,DEV_LCD_EN_PIN,GPIO_PIN_RESET) ; }
#define LCD_RST_H()     {   GPIO_Driver_WriteOutputPin(DEV_LCD_RST_PORT,DEV_LCD_RST_PIN,GPIO_PIN_SET) ; }
#define LCD_RST_L()     {   GPIO_Driver_WriteOutputPin(DEV_LCD_RST_PORT,DEV_LCD_RST_PIN,GPIO_PIN_RESET) ; }

#define LCD_ON()        {   GPIO_Driver_WriteOutputPin(DEV_LCD_POWER_POS_PORT,DEV_LCD_POWER_POS_PIN,ENABLE); \
                            GPIO_Driver_WriteOutputPin(DEV_LCD_POWER_NEG_PORT,DEV_LCD_POWER_NEG_PIN,ENABLE);   }
#define LCD_OFF()       {   GPIO_Driver_WriteOutputPin(DEV_LCD_POWER_POS_PORT,DEV_LCD_POWER_POS_PIN,DISABLE); \
                            GPIO_Driver_WriteOutputPin(DEV_LCD_POWER_NEG_PORT,DEV_LCD_POWER_NEG_PIN,DISABLE);  }

//3个LCD片选信号，CS低电平有效
#define LCD_CS_LEFT()   {   LCD_CS1_L(); LCD_CS2_H();   }                                                               //左半屏选通
#define LCD_CS_RIGHT()  {   LCD_CS1_H(); LCD_CS2_L();   }                                                               //右半屏选通
#define LCD_CS_None()   {   LCD_CS1_H(); LCD_CS2_H();   }                                                               //左右屏均不选通

//LCD 相关全局变量
uint8_t gu8LCDEnglishFont = En_5x8;                                                                                     //英文字体
uint8_t gu8LCDTextMode = GUI_TEXTMODE_NORMAL;                                                                           //显示模式
uint8_t gu8ColumnSizeOfChar;                                                                                            //英文字体列点阵宽度
uint8_t gu8RowSizeOfChar;                                                                                               //英文字体行点阵宽度
uint8_t gu8CharacterSpace;                                                                                              //英文字体字符间距
uint8_t gu8RowPosition = 0;                                                                                             //当前系统行点阵坐标
uint8_t gu8ColumnPosition = 0;                                                                                          //当前系统列点阵坐标
uint8_t gu8SysCoordinate = STATUS_TRUE;                                                                                 //是否使用PosX PosY的标志   1-->不使用   0-->使用
uint8_t gu8SingleRowSize = En_ROW_SIZE;                                                                                 //每行字符数，默认英文语言配置

typedef struct
{
    uint8_t u8Enable;
    uint8_t u8StartPosition;
    uint8_t u8EndPosition;
}UnderlineBlinkPara_t;
UnderlineBlinkPara_t UnderlineBlinkPara;


//预留宏
#define  SomeNop()

/***********************************************************************************************************************
 功能：获取单行显示长度信息
***********************************************************************************************************************/
uint8_t GetSingleRowSize(void)
{
    return gu8SingleRowSize;
}

/***********************************************************************************************************************
 功能：设置单行显示长度信息
***********************************************************************************************************************/
void SetSingleRowSize(uint8_t u8Size)
{
    gu8SingleRowSize = u8Size;
}

/***********************************************************************************************************************
 功能：写命令到KS0108
***********************************************************************************************************************/
void WriteCommand_0108(uint8_t CmdData)
{
    Delay_us(2);

    LCD_E_L();          //E = 0
    Delay_us(2);

    LCD_RS_L();         //RS = 0
    Delay_us(2);

    LCD_RW_L();         //RW = 0
    Delay_us(2);

    LCD_Bus(CmdData);   //DB7~DB0写数据
    Delay_us(2);

    SomeNop();
    LCD_E_H();          //E = 1
    Delay_us(2);

    SomeNop();
    LCD_E_L();          //E = 0锁存
    Delay_us(2);
}

/***********************************************************************************************************************
 功能：写数据到KS0108
***********************************************************************************************************************/
void WriteData_0108(uint8_t Data)
{
    Delay_us(2);

    LCD_E_L();          //E = 0
    Delay_us(2);

    LCD_RS_H();         //RS = 1
    Delay_us(2);

    LCD_RW_L();         //RW = 0
    Delay_us(2);

    LCD_Bus(Data);      //DB7~DB0写数据
    Delay_us(2);

    SomeNop();
    LCD_E_H();          //E = 1
    Delay_us(2);

    SomeNop();
    LCD_E_L();          //E = 0锁存
    Delay_us(2);
}

/***********************************************************************************************************************
 功能：开启或关闭LCD显示
***********************************************************************************************************************/
void KS0108_DisplayOn(uint8_t Option)
{
    if (Option == 1)
    {
        WriteCommand_0108(Ks0108_CMD_Disp_ON);   //Option = 1   --->Disp On
    }
    else
    {
        WriteCommand_0108(Ks0108_CMD_Disp_OFF);  //Option = 0   --->Disp Off
    }
}

/***********************************************************************************************************************
 功能：设定KS0108显示起始行
***********************************************************************************************************************/
void KS0108_SetStartRow(uint8_t Row)
{
    WriteCommand_0108(Ks0108_CMD_Disp_Start_Line + Row);
}

/***********************************************************************************************************************
 功能：LCD上指定位置 显示指定数据
***********************************************************************************************************************/
void Display_Locate(uint8_t u8DisplayData, uint8_t u8Column, uint8_t u8Row)
{
    if((u8Column <= (LCD_COLUMN_SIZE - 1)) & (u8Row <= (LCD_ROW_SIZE - 1)))
    {
        if(u8Column <= 63)
        {
            LCD_CS_LEFT();                                           //左侧屏片选使能
            WriteCommand_0108(Ks0108_CMD_Set_Addr + u8Column);       //左侧屏起始点阵列定位
        }
        else if(u8Column <= 127)
        {
            LCD_CS_RIGHT();                                          //右侧屏片选使能
            WriteCommand_0108(Ks0108_CMD_Set_Addr + u8Column - 64);  //右侧屏起始点阵列定位
        }
        WriteCommand_0108(u8Row + Ks0108_CMD_Set_Page);              //起始行点阵定位
        WriteData_0108(u8DisplayData);                               //写数据
        LCD_CS_None();                                               //左右屏片选关闭
    }
}

/***********************************************************************************************************************
 功能：清空LCD显示内容
***********************************************************************************************************************/
void Display_Clear(void)
{
    uint8_t u8Column,u8Row;

//写0x00，清除左边屏
    LCD_CS_LEFT();                                          //左屏片选
    Delay_us(2);
    for(u8Row = 0; u8Row < 8; u8Row++)                      //0--7字符行，8个点阵行组成一个字符行
    {
        WriteCommand_0108(0 + Ks0108_CMD_Set_Addr);         //初始列，0--63
        WriteCommand_0108(u8Row + Ks0108_CMD_Set_Page);     //初始行，0--7
        for(u8Column = 0;u8Column < 64;u8Column++)          //0--63点阵列
        {
            WriteData_0108(0x00);                           //写0x00,清除显示
        }
    }
    KS0108_SetStartRow(0);
    Delay_us(2);

//写0x00，清除右边屏
    LCD_CS_RIGHT();
    Delay_us(2);
    for(u8Row = 0; u8Row < 8; u8Row++)                      //0--7字符行，8个点阵行组成一个字符行
    {
        WriteCommand_0108(0 + Ks0108_CMD_Set_Addr);         //初始列，0--63
        WriteCommand_0108(u8Row + Ks0108_CMD_Set_Page);     //初始行，0--7
        for(u8Column = 0;u8Column < 64;u8Column++)          //0--63点阵列
        {
            WriteData_0108(0x00);                           //写0x00,清除显示
        }
    }
    KS0108_SetStartRow(0);
    Delay_us(2);

//操作完毕，关闭片选
    LCD_CS_None();
    Delay_us(2);
}

/***********************************************************************************************************************
 功能：全部显示LCD显示内容
***********************************************************************************************************************/
#if LCD_ATE_TEST
void Display_Ate_Test(void)
{
        DISABLE_INTERRUPT();                      //关总中断
        uint8_t u8Column,u8Row;
    //写0xFF，点亮左边屏
        LCD_CS_LEFT();                                          //左屏片选
        for(u8Row = 0; u8Row < 8; u8Row++)                      //0--7字符行，8个点阵行组成一个字符行
        {
            WriteCommand_0108(0 + Ks0108_CMD_Set_Addr);         //初始列，0--63
            WriteCommand_0108(u8Row + Ks0108_CMD_Set_Page);     //初始行，0--7
            for(u8Column = 0;u8Column < 64;u8Column++)          //0--63点阵列
            {
                WriteData_0108(0xFF);                           //写0xFF,显示整个左半屏
            }
        }
        KS0108_SetStartRow(0);
        Delay_us(2);
    //写0xFF，点亮右边屏
        LCD_CS_RIGHT();
        Delay_us(2);
        for(u8Row = 0; u8Row < 8; u8Row++)                      //0--7字符行，8个点阵行组成一个字符行
        {
            WriteCommand_0108(0 + Ks0108_CMD_Set_Addr);         //初始列，0--63
            WriteCommand_0108(u8Row + Ks0108_CMD_Set_Page);     //初始行，0--7
            for(u8Column = 0;u8Column < 64;u8Column++)          //0--63点阵列
            {
                WriteData_0108(0xFF);                           //写0xFF,显示整个右半屏
            }
        }
        KS0108_SetStartRow(0);
        Delay_us(2);
    
    //操作完毕，关闭片选
        LCD_CS_None();
        Delay_us(2);
        ENABLE_INTERRUPT();                //开总中断
}
#endif

/***********************************************************************************************************************
 功能：初始化LCD显示
***********************************************************************************************************************/
void Display_Init(void)
{
    //左半屏操作
    LCD_CS_LEFT();                  //左屏片选
    Delay_us(2);
    KS0108_SetStartRow(0);          //设定起始行
    Delay_us(2);
    KS0108_DisplayOn(DISPLAY_ON);   //开启显示
    Delay_us(2);
    //右半屏操作
    LCD_CS_RIGHT();                 //右屏片选
    Delay_us(2);
    KS0108_SetStartRow(0);          //设定起始行
    Delay_us(2);
    KS0108_DisplayOn(DISPLAY_ON);   //开启显示
    Delay_us(2);
    //操作完毕，关闭左右屏片选
    LCD_CS_None();
    Delay_us(2);
}

/***********************************************************************************************************************
 功能：指定位置显示一个16x16的汉字
***********************************************************************************************************************/
void Display_Chinese(uint16_t u16UniCode, uint8_t u8Column, uint8_t u8Row)
{
    uint16_t u16CodeID;
    uint8_t i, u8ImgData;
    uint8_t u8ColumnTemp = u8Column;

    for(u16CodeID = 0; u16CodeID < hzNum; u16CodeID++)                      // 在字库里搜索汉字
    {
        if ( (hzIndex[2 * u16CodeID] == u16UniCode / 256) && (hzIndex[2 * u16CodeID + 1] == u16UniCode % 256) ) // 找到 指定汉字的 Index 后, 跳出循环
        {
            break;
        }
        else if(u16CodeID == (hzNum - 1))
        {
            GUI_DispCharAt('#', u8Column, u8Row);                           // 未检索到的汉字,显示"##"提示
            GUI_DispCharAt('#', u8Column + gu8ColumnSizeOfChar, u8Row);
            return;
        }
    }
    switch (gu8LCDTextMode)
    {
        case GUI_TEXTMODE_NORMAL :
            for(i=0; i<16; i++)                                             // 写汉字的上半部分  (一个汉字 32 个字节,  显示为2行 * 16列)
            {
                u8ImgData = hzdot[i + u16CodeID * 32];
                Display_Locate(u8ImgData, u8ColumnTemp, u8Row);
                u8ColumnTemp++;
            }
            u8ColumnTemp = u8Column;
            for(i=16; i<32; i++)                                            // 写汉字的下半部分
            {
                u8ImgData = hzdot[i + u16CodeID * 32];
                Display_Locate(u8ImgData, u8ColumnTemp, u8Row + 1);
                u8ColumnTemp++;
            }
            break;
        case GUI_TEXTMODE_REVERSE :
            for(i=0; i<16; i++)                                             // 写汉字的上半部分  (一个汉字 32 个字节,  显示为2行 * 16列)
            {
                u8ImgData = hzdot[i + u16CodeID * 32] ^ 0xFF;
                Display_Locate(u8ImgData, u8ColumnTemp, u8Row);
                u8ColumnTemp++;
            }
            u8ColumnTemp = u8Column;
            for(i=16; i<32; i++)                                            // 写汉字的下半部分
            {
                u8ImgData = hzdot[i + u16CodeID * 32] ^ 0xFF;
                Display_Locate(u8ImgData, u8ColumnTemp, u8Row + 1);
                u8ColumnTemp++;
            }
            break;
        case GUI_TEXTMODE_UNDERLINE :
            for(i=0; i<16; i++)                                             // 写汉字的上半部分  (一个汉字 32 个字节,  显示为2行 * 16列)
            {
                u8ImgData = hzdot[i + u16CodeID * 32];
                Display_Locate(u8ImgData, u8ColumnTemp, u8Row);
                u8ColumnTemp++;
            }
            u8ColumnTemp = u8Column;
            for(i=16; i<32; i++)                                            // 写汉字的下半部分
            {
                u8ImgData = hzdot[i + u16CodeID * 32] | 0x80;
                Display_Locate(u8ImgData, u8ColumnTemp, u8Row + 1);
                u8ColumnTemp++;
            }
             break;
        default :
             break;
    }
}

/***********************************************************************************************************************
 功能：指定位置显示一个ASCII
***********************************************************************************************************************/
void Display_ASCII(uint8_t u8Char, uint8_t u8Column, uint8_t u8Row)
{
    uint8_t i, u8ImgData;
    uint8_t u8ColumnTemp = u8Column;
    if(gu8LCDEnglishFont == En_5x8)                                           //ASCII字符显示采用5列点阵*8行点阵大小
    {
        Display_Locate(0x00, u8ColumnTemp, u8Row);                           //字符前空一点阵不显示任何数据
        u8ColumnTemp++;
        for(i = 0; i < 5; i++)                                               //显示5列点阵的数据，组合成ASCII字符图案
        {
            u8ImgData = gu8Chardot_5x8[i + (u8Char - 0x20) * En_5x8_Column_SIZE];  //查表，得到显示字符的每一列的显示驱动值
            Display_Locate(u8ImgData, u8ColumnTemp, u8Row);                  //点亮一列点阵
            u8ColumnTemp++;
        }
        //Display_Locate(0x00, u8ColumnTemp, u8Row);                           //字符后空两列点阵不显示任何数据
        //u8ColumnTemp++;
        //Display_Locate(0x00, u8ColumnTemp, u8Row);
    }
    else                                                                     //ASCII字符显示采用8列点阵*16行点阵大小
    {
        for(i = 0; i < 8; i++)                                               //上半部分前8点阵行显示
        {
            u8ImgData = gu8Chardot_8x16[i + (u8Char - 0x20) * Chinese_Column_SIZE];
            Display_Locate(u8ImgData, u8ColumnTemp, u8Row);
            u8ColumnTemp++;
        }
        u8ColumnTemp = u8Column;
        for(i = 8; i < 16; i++)                                              //下半部分后8点阵行显示
        {
            u8ImgData = gu8Chardot_8x16[i + (u8Char - 0x20) * Chinese_Column_SIZE];
            Display_Locate(u8ImgData, u8ColumnTemp, u8Row + 1);
            u8ColumnTemp++;
        }
   }
}

/***********************************************************************************************************************
 功能：指定位置反显示一个ASCII
***********************************************************************************************************************/
void Display_InvASCII(uint8_t u8Char, uint8_t u8Column, uint8_t u8Row)
{
    uint8_t i, u8ImgData;
    uint8_t u8ColumnTemp = u8Column;

    if(gu8LCDEnglishFont == En_5x8)                                           //ASCII字符显示采用5列点阵*8行点阵大小
    {
        Display_Locate(0xFF, u8ColumnTemp, u8Row);                           //字符前空一点阵不显示任何数据
        u8ColumnTemp++;
        for(i = 0; i < 5; i++)                                               //显示5列点阵的数据，组合成ASCII字符图案
        {
            u8ImgData = gu8Chardot_5x8[i + (u8Char - 0x20) * En_5x8_Column_SIZE] ^ 0xFF;  //查表，得到显示字符的每一列的显示驱动值
            Display_Locate(u8ImgData, u8ColumnTemp, u8Row);                  //点亮一列点阵
            u8ColumnTemp++;
        }
        Display_Locate(0xFF, u8ColumnTemp, u8Row);                           //字符后空两列点阵不显示任何数据
        u8ColumnTemp++;
        Display_Locate(0xFF, u8ColumnTemp, u8Row);
    }
    else                                                                     //ASCII字符显示采用8列点阵*16行点阵大小
    {
        for(i = 0; i < 8; i++)                                               //上半部分前8点阵行显示
        {
            u8ImgData = gu8Chardot_8x16[ i + (u8Char - 0x20) * Chinese_Column_SIZE] ^ 0xFF;
            Display_Locate(u8ImgData, u8ColumnTemp, u8Row);
            u8ColumnTemp++;
        }
        u8ColumnTemp = u8Column;
        for(i = 8; i < 16; i++)                                              //下半部分后8点阵行显示
        {
            u8ImgData = gu8Chardot_8x16[i + (u8Char - 0x20) * Chinese_Column_SIZE] ^ 0xFF;
            Display_Locate(u8ImgData, u8ColumnTemp, u8Row + 1);
            u8ColumnTemp++;
        }
    }
}

/***********************************************************************************************************************
 功能：指定位置显示一个带有下划线的ASCII
***********************************************************************************************************************/
void Display_ASCII_UnderLine(uint8_t u8Char, uint8_t u8Column, uint8_t u8Row)
{
    uint8_t i, u8ImgData;
    uint8_t u8ColumnTemp = u8Column;

    if(gu8LCDEnglishFont == En_5x8)                                           //ASCII字符显示采用5列点阵*8行点阵大小
    {
        Display_Locate(0x80, u8ColumnTemp, u8Row);                           //字符前空一点阵显示下划线第一列
        u8ColumnTemp++;
        for(i = 0; i < 5; i++)                                               //显示5列点阵的数据，组合成ASCII字符图案
        {
            u8ImgData = gu8Chardot_5x8[i + (u8Char - 0x20) * En_5x8_Column_SIZE] | 0x80;  //查表，得到显示字符的每一列的显示驱动值
            Display_Locate(u8ImgData, u8ColumnTemp, u8Row);                  //点亮一列点阵
            u8ColumnTemp++;
        }
        Display_Locate(0x80, u8ColumnTemp, u8Row);                           //字符后空两列点阵显示下划线最后两列
        u8ColumnTemp++;
        Display_Locate(0x80, u8ColumnTemp, u8Row);
    }
    else                                                                     //ASCII字符显示采用8列点阵*16行点阵大小
    {
        for(i = 0; i < 8; i++)                                               //上半部分前8点阵行显示
        {
            u8ImgData = gu8Chardot_8x16[i + (u8Char - 0x20) * Chinese_Column_SIZE];
            Display_Locate(u8ImgData, u8ColumnTemp, u8Row);
            u8ColumnTemp++;
        }
        u8ColumnTemp=u8Column;
        for(i = 8; i < 16; i++)                                              //下半部分后8点阵行显示
        {
            u8ImgData = gu8Chardot_8x16[i + (u8Char - 0x20) * Chinese_Column_SIZE] | 0x80;
            Display_Locate(u8ImgData, u8ColumnTemp, u8Row + 1);
            u8ColumnTemp++;
        }
    }
}

void Display_Set_UnderLine_Blink_Position(uint8_t u8Enable, uint8_t u8StartPosition, uint8_t u8EndPosition)
{
    UnderlineBlinkPara.u8Enable = u8Enable;
    UnderlineBlinkPara.u8StartPosition = u8StartPosition;
    UnderlineBlinkPara.u8EndPosition = u8EndPosition;
}


/***********************************************************************************************************************
 功能：设置文字显示模式
***********************************************************************************************************************/
uint8_t GUI_SetTextMode(uint8_t TextMode)
{
    gu8LCDTextMode = TextMode;                       //设定文本显示模式
    return gu8LCDTextMode;
}

/***********************************************************************************************************************
 功能：设置显示的英文字体
***********************************************************************************************************************/
void GUI_SetEnFont(uint8_t EnFont)
{
    if (EnFont == En_5x8)
    {
        gu8LCDEnglishFont = En_5x8;
        gu8ColumnSizeOfChar = En_5x8_Column_SIZE;
        gu8RowSizeOfChar = En_5x8_Row_SIZE;
    }
    else
    {
        gu8LCDEnglishFont = En_8x16;
        gu8ColumnSizeOfChar = En_8x16_Column_SIZE;
        gu8RowSizeOfChar = En_8x16_Row_SIZE;
    }
}

/***********************************************************************************************************************
 功能：使用配置的文字显示模式，在指定位置显示一个ASCII码
***********************************************************************************************************************/
void GUI_DispCharAt(uint8_t u8Char, uint8_t u8Column, uint8_t u8Row)
{
    switch (gu8LCDTextMode)                                     //文本显示模式
    {
        case GUI_TEXTMODE_NORMAL :
             Display_ASCII(u8Char, u8Column, u8Row);           //从第u8Row行，第u8Column列开始处，显示ASCII字符串pStr
             break;
        case GUI_TEXTMODE_REVERSE :
             Display_InvASCII(u8Char, u8Column, u8Row);        //以反显方式显示内容
             break;
        case GUI_TEXTMODE_UNDERLINE :
             Display_ASCII_UnderLine(u8Char, u8Column, u8Row); //以带下划线方式显示内容
             break;
        default :
             break;
    }
}

/***********************************************************************************************************************
 功能：初始化图形化界面的显示
***********************************************************************************************************************/
void GUI_Init(void)
{
    DISABLE_INTERRUPT();                //关总中断
    LCD_RST_L();                        //RST = 0
    Delay_us(2);                        //RST由0将要变为1，由于硬件RC滤波，操作需延时
    LCD_RST_H();                        //RST = 1
    LCD_RW_H();                         //RW = 1
    LCD_CS_None();                      //CS1 = 1,CS2 = 1
    Delay_us(2);                        //延时1us确保下一次操作是有效的
    Display_Clear();                    //清除当前显示值
    Display_Init();                     //初始化显示状态
    Display_Init();                     //初始化显示状态
    LCD_ON();                           //开启背光
    ENABLE_INTERRUPT();                //开总中断
}

/***********************************************************************************************************************
 功能：开启背光接口
***********************************************************************************************************************/
void GUI_LCD_ON(void)
{
    LCD_ON();                           //开启背光
}

/***********************************************************************************************************************
 功能：关闭背光接口
***********************************************************************************************************************/
void GUI_LCD_OFF(void)
{
    LCD_OFF();                           //关闭背光
}

/***********************************************************************************************************************
 功能：KS0108 ，6800协议，LCD驱动设备全局变量初始化
***********************************************************************************************************************/
void LCD_Device_KS0108_6800_InitVar(void)
{
    gu8LCDEnglishFont = En_5x8;                  //设定英文字体
    gu8LCDTextMode = GUI_TEXTMODE_NORMAL;       //设定文本显示模式
    gu8ColumnSizeOfChar = En_5x8_Column_SIZE;   //英文字体8*16，列宽度
    gu8RowSizeOfChar = En_5x8_Row_SIZE;         //英文字体8*16，行宽度
    gu8CharacterSpace = En_5x8_CharacterSpace_SIZE;//文字体8*16，字符间距
    gu8RowPosition = 0;                          //系统行坐标
    gu8ColumnPosition = 0;                       //系统列坐标
    gu8SysCoordinate = STATUS_TRUE;              //系统坐标使能
}

/***********************************************************************************************************************
 功能：清除图形化界面显示内容
***********************************************************************************************************************/
void GUI_Clear(void)
{
    DISABLE_INTERRUPT();                      //关总中断
    Display_Clear();
    ENABLE_INTERRUPT();                       //开总中断
}


void GUI_Display(char *pStr, uint8_t u8Column, uint8_t u8Row)
{
    DISABLE_INTERRUPT();                      //关总中断
    static uint8_t u8DisplayRow = 0;
    uint8_t pStrTemp[En_ROW_SIZE+1] = {0};
    uint8_t i = 0;


//    pStrTemp = strtok(pStr,delim);

    
    switch ( u8DisplayRow )
    {
        case 0 :
            for(i = 0; i < gu8SingleRowSize; i++)
            {
                pStrTemp[i] = pStr[i];
                if(pStr[i] == '\0')
                {
                    break;
                }
            }
            pStrTemp[gu8SingleRowSize] = '\0';
            GUI_DispStringAt((const uint8_t *)pStrTemp, 0, 0);
            u8DisplayRow = 1;
            break;
        case 1 :
            for(i = 0; i < gu8SingleRowSize; i++)
            {
                pStrTemp[i] = pStr[i + gu8SingleRowSize+1];
                if(pStr[i] == '\0')
                {
                    break;
                }
            }
            pStrTemp[gu8SingleRowSize] = '\0';
            GUI_DispStringAt((const uint8_t *)pStrTemp, 0, 2);
            u8DisplayRow = 2;
            break;
        case 2 :
            for(i = 0; i < gu8SingleRowSize; i++)
            {
                pStrTemp[i] = pStr[i + 2*gu8SingleRowSize + 2];
                if(pStr[i] == '\0')
                {
                    break;
                }
            }
            pStrTemp[gu8SingleRowSize] = '\0';
            GUI_DispStringAt((const uint8_t *)pStrTemp, 0, 4);
            u8DisplayRow = 3;
            break;
        case 3 :
            for(i = 0; i < gu8SingleRowSize; i++)
            {
                pStrTemp[i] = pStr[i + 3*gu8SingleRowSize + 3];
                if(pStr[i] == '\0')
                {
                    break;
                }
            }
            pStrTemp[gu8SingleRowSize] = '\0';
            GUI_DispStringAt((const uint8_t *)pStrTemp, 0, 6);
            u8DisplayRow = 0;
            break;
        default:
            break;;
    }
    ENABLE_INTERRUPT();                       //开总中断
}



/***********************************************************************************************************************
 功能：指定位置显示一个字符串（支持中英混合 当中英混合时英文字体强制为8x16 如果单单英文 按照设定字体）
     ：u8Column是指点阵列数，0~127，u8Row指的是8个点阵列组成的行数，0~7
***********************************************************************************************************************/
void GUI_DispStringAt(uint8_t const *pStr,uint8_t u8Column,uint8_t u8Row)
{
    uint8_t i,j;
    static uint8_t u8UnderLineBlinkState = 0;
    static uint8_t u8BlinkCnt = 0;
    i = 0;
    j = 0;

    if(0 != UnderlineBlinkPara.u8Enable)
    {
        if(0 == u8UnderLineBlinkState)
        {
            if(u8BlinkCnt++ >= UNDELINE_BLINK_SPEED)                        //闪烁速度值
            {
                u8BlinkCnt = 0;
            u8UnderLineBlinkState = 1;
            }
        }
        else
        {
            if(u8BlinkCnt++ >= UNDELINE_BLINK_SPEED)
            {
                u8BlinkCnt = 0;
            u8UnderLineBlinkState = 0;
            }
        }
    }
    else
    {
        u8UnderLineBlinkState = 0;
    }


    if (gu8SysCoordinate == STATUS_FALSE)                                    //没有提供坐标,则使用系统坐标
    {
        u8Column = gu8RowPosition;
        u8Row = gu8ColumnPosition;
    }
    while(pStr[i]!='\0')                                                    //不是字符串结束标志
    {
        if (pStr[i] < 0x80)                                                 //是ASCII
        {
             if(pStr[i] == '\n')                                            //是换行标识符
             {
                    u8Column = 0;
                    u8Row += gu8RowSizeOfChar;
             }
             else
             {
                if (u8Column > (LCD_COLUMN_SIZE-1))                               //换行
                {
                    u8Column = 0;
                    u8Row += gu8RowSizeOfChar;
                }

                if(1 == u8UnderLineBlinkState)
                {
                    if(((gu8LCDEnglishFont == En_5x8) && (j + u8Row * 11) >= UnderlineBlinkPara.u8StartPosition ) && ((j + u8Row * 11) <= UnderlineBlinkPara.u8EndPosition ))
                    {
                        gu8LCDTextMode = GUI_TEXTMODE_UNDERLINE;
                    }
                    else if(((gu8LCDEnglishFont == En_8x16) && (j + u8Row * 8) >= UnderlineBlinkPara.u8StartPosition ) && ((j + u8Row * 8) <= UnderlineBlinkPara.u8EndPosition ))
                    {
                        gu8LCDTextMode = GUI_TEXTMODE_UNDERLINE;
                    }
                    else
                    {
                        gu8LCDTextMode = GUI_TEXTMODE_NORMAL;
                    }
                }
                else
                {
                    gu8LCDTextMode = GUI_TEXTMODE_NORMAL;
                }

                switch (gu8LCDTextMode)
                {
                    case GUI_TEXTMODE_NORMAL :
                         Display_ASCII(pStr[i], u8Column, u8Row);           //从第u8Row行，第u8Column列开始处，显示ASCII字符串pStr
                         break;
                    case GUI_TEXTMODE_REVERSE :
                         Display_InvASCII(pStr[i], u8Column, u8Row);        //以反显方式显示内容
                         break;
                    case GUI_TEXTMODE_UNDERLINE :
                         Display_ASCII_UnderLine(pStr[i], u8Column, u8Row); //以带下划线方式显示内容
                         break;
                    default :
                         break;
                }
                u8Column += gu8ColumnSizeOfChar + gu8CharacterSpace;                             //显示完一个字符后，下一次起始位置定位
             }
        }
        else                                                                //是中文
        {
            if (u8Column > LCD_COLUMN_SIZE-16)                                    //换行
            {
                u8Column = 0;
                u8Row += Chinese_Row_SIZE;
            }

            if(1 == u8UnderLineBlinkState)
            {
                if(((j + u8Row * 8) >= UnderlineBlinkPara.u8StartPosition ) && ((j + u8Row * 8) <= UnderlineBlinkPara.u8EndPosition ))
                {
                    gu8LCDTextMode = GUI_TEXTMODE_UNDERLINE;
                }
                else
                {
                    gu8LCDTextMode = GUI_TEXTMODE_NORMAL;
                }
            }
            else
            {
                gu8LCDTextMode = GUI_TEXTMODE_NORMAL;
            }

            Display_Chinese(pStr[i] * 256 + pStr[i + 1], u8Column, u8Row);  //从第u8Row行，第u8Column列开始处，显示中文
            i++;
            u8Column += Chinese_Column_SIZE;                                //显示完一个字，下次定位改变
            j++;
        }
       pStr++;
       j++;
    }
    if (gu8SysCoordinate == STATUS_FALSE)                                    //更新保存当前行与列的定位位置
    {
        gu8RowPosition = u8Column;
        gu8ColumnPosition = u8Row;
    }
}

/***********************************************************************************************************************
 功能：指定位置显示一个32x32的图标
***********************************************************************************************************************/
void GUI_DrawIcon(uint8_t      const *pu8Icon, uint8_t u8Column, uint8_t u8Row)
{
    uint8_t i;
    uint16_t u16Count;
    u16Count = 0;
    if( u8Row > 4)                                                      //边界保护
    {
        u8Row = 4;
    }
    if(u8Column > (LCD_COLUMN_SIZE - 32))
    {
        u8Column = LCD_COLUMN_SIZE - 32;
    }
    for(i = 0; i < 32; i++)                                             //第一行
    {
        Display_Locate(pu8Icon[u16Count++], u8Column + i, u8Row);
    }
    for(i = 0; i < 32; i++)                                             //第二行
    {
        Display_Locate(pu8Icon[u16Count++], u8Column+i, u8Row + 1);
    }
    for(i = 0; i < 32; i++)                                             //第三行
    {
        Display_Locate(pu8Icon[u16Count++], u8Column + i, u8Row + 2);
    }
    for(i = 0; i < 32; i++)                                             //第四行
    {
        Display_Locate(pu8Icon[u16Count++], u8Column + i, u8Row + 3);
    }
}

/***********************************************************************************************************************
 功能：指定位置显示一个16x16的图标
***********************************************************************************************************************/
void GUI_DrawIcon16X16(uint8_t        const *pu8Icon, uint8_t u8Column, uint8_t u8Row)
{
    uint8_t i;
    uint16_t u16Count;
    u16Count = 0;
    if( u8Row > 4)                                              //边界保护
    {
        u8Row = 4;
    }
    if(u8Column >(LCD_COLUMN_SIZE - 16))
    {
        u8Column = LCD_COLUMN_SIZE - 16;
    }
    for(i = 0; i < 16; i++)                                           //第一行
    {
        Display_Locate(pu8Icon[u16Count++], u8Column + i, u8Row);
    }
    for(i = 0; i < 16; i++)                                           //第二行
    {
        Display_Locate(pu8Icon[u16Count++], u8Column + i, u8Row + 1);
    }
}
#if 1

/***********************************************************************************************************************
 功能：显示十进制数值 | 处理长度最多5个数字(因为INT16U--->65536) |
***********************************************************************************************************************/
void GUI_DispDecAt(uint16_t u16DecimalData, uint16_t u8Column, uint16_t u8Row, uint8_t u8Length)
{
    uint8_t i;
    uint8_t u8CharBuf[5];
    uint8_t u8HighByte;

    u8HighByte = 0;
    for(i = 0; i < 5; i++)                              //提取出十进制的每个数字
    {
        u8CharBuf[i] = (uint8_t)(u16DecimalData % 10);
        u16DecimalData = u16DecimalData / 10;
        if(u8CharBuf[i])
        {
            u8HighByte = i;
        }
    }
    i = 0;
    GUI_DispCharAt(u8CharBuf[i] + '0',u8Column + ((u8Length - 1) - i) * gu8ColumnSizeOfChar,u8Row);    //第0位无论如何也显示
    for(i = 1; i < u8Length; i++)
    {
        if(u8CharBuf[i])
        {
            GUI_DispCharAt(u8CharBuf[i]+'0',u8Column + ((u8Length-1)-i)*gu8ColumnSizeOfChar,u8Row);     //非零数据显示
        }
        else if(i > u8HighByte)
        {
            GUI_DispCharAt(' ',u8Column + ((u8Length-1)-i)*gu8ColumnSizeOfChar,u8Row);                  //无效的0，以空格显示
        }
    }
}

/***********************************************************************************************************************
 功能：显示一个数据的十六进制值
***********************************************************************************************************************/
void GUI_DispHexAt(uint32_t u16DecimalData, uint8_t u8Column, uint8_t u8Row, uint8_t u8Length)
{
    uint8_t i;
    uint8_t u8HexData;
    if(u8Length > 8)                                                                 //限制范围
    {
        u8Length = 8;
    }
    for(i = 0; i < u8Length; i++)
    {
        u8HexData = u16DecimalData & 0x0F;
        u16DecimalData = u16DecimalData >> 4;
        if(u8HexData < 0x0A)
        {
            GUI_DispCharAt(u8HexData + '0', u8Column + gu8ColumnSizeOfChar * (u8Length - 1 - i), u8Row);          //显示数字
        }
        else
        {
            GUI_DispCharAt(u8HexData - 0x0A + 'A', u8Column + gu8ColumnSizeOfChar * (u8Length - 1 - i), u8Row);   //显示字符
        }
    }
} 

/***********************************************************************************************************************
 功能：显示一个水平的进度条
***********************************************************************************************************************/
void HBar(uint8_t u8Row, uint8_t u8StartColumn, uint8_t u8EndColumn,uint8_t u8Percent)
{
    uint8_t u8Temp;
    uint8_t i;
    uint16_t u16Center;
    u16Center = (u8EndColumn - u8StartColumn);
    u16Center *= u8Percent;
    u16Center = (u16Center * 10) >> 10;                     //1/100 == *10>>10
    u8Temp = (uint8_t)u16Center;                            //计算得到u8Percent对应的点阵列数
    Display_Locate(0xFF, u8StartColumn, u8Row);             //显示起始列竖线
    Display_Locate(0xFF, u8EndColumn, u8Row);               //显示结束列竖线
    for(i = 1; i < u8Temp; i++)
    {
        Display_Locate(0xBD, u8StartColumn+i, u8Row);       //显示填充的部分进度条
    }
    for(i = u8StartColumn+u8Temp+1; i < u8EndColumn; i++)
    {
        Display_Locate(0x81, i, u8Row);                     //显示未填充的部分进度条
    }
}

/***********************************************************************************************************************
 功能：显示一个用于提示的文本框
***********************************************************************************************************************/
void TipDisp( uint8_t u8StartColumn, uint8_t u8StartRow, uint8_t u8EndColumn, uint8_t u8EndRow)
{
    uint8_t i;
    for(i = 0; i < u8EndColumn- u8StartColumn + 4; i++)            //显示上下边界
    {
        Display_Locate(0x01, u8StartColumn + i, u8StartRow);
        Display_Locate(0x0F, u8StartColumn + i, u8EndRow);
    }
    Display_Locate(0x01, u8StartColumn + 0, u8EndRow);
    Display_Locate(0x01, u8StartColumn + 1, u8EndRow);
    Display_Locate(0x03, u8StartColumn + 2, u8EndRow);
    Display_Locate(0x03, u8StartColumn + 3, u8EndRow);
    Display_Locate(0x07, u8StartColumn + 4, u8EndRow);
    Display_Locate(0x07, u8StartColumn + 5, u8EndRow);         //修正左下角，使之具有叠加的层次感

    for(i = 0; i < u8EndRow - u8StartRow; i++)              //显示左右边界
    {
        Display_Locate(0xFF, u8StartColumn, u8StartRow + i);
        Display_Locate(0xFF, u8EndColumn, u8StartRow + i);
        Display_Locate(0xFF, u8EndColumn + 1, u8StartRow + i);
        Display_Locate(0xFF, u8EndColumn + 2, u8StartRow + i);
        Display_Locate(0xFF, u8EndColumn + 3, u8StartRow + i);
    }
    Display_Locate(0xFC, u8EndColumn + 1, u8StartRow);         //修正右上角，使之具有叠加的层次感
    Display_Locate(0xF0, u8EndColumn + 2, u8StartRow);
    Display_Locate(0xC0, u8EndColumn + 3, u8StartRow);
}

/***********************************************************************************************************************
 功能：清除用于提示的文本框
***********************************************************************************************************************/
void TipClr( uint8_t u8StartColumn, uint8_t u8StartRow, uint8_t u8EndColumn, uint8_t u8EndRow)
{
    uint8_t i;
    uint8_t j;
    for(i = 0; i <= u8EndColumn + 3 - u8StartColumn; i++)
    {
        for(j = 0; j <= u8EndRow - u8StartRow; j++)
        {
            Display_Locate(0x00, u8StartColumn + i, u8StartRow + j);
        }
    }
}
#endif

#if 1
/***********************************************************************************************************************
 功能：显示不带符号的整数  
***********************************************************************************************************************/
void Display_Number(uint16_t u16Number, uint8_t u8Column, uint8_t u8Row, uint8_t u8Length)
{
    uint8_t u8DispNum;

    u8Column = ( u8Column + u8Length * 8 - 8 );
    for(; u8Length > 0; u8Length--)
    {
        u8DispNum = u16Number % 10 + 0x30;
        Display_ASCII(u8DispNum, u8Column, u8Row);
        u8Column -= 8;
        u16Number = u16Number / 10;
    }
}

/***********************************************************************************************************************
 功能：显示带符号的整数  
***********************************************************************************************************************/
void Display_SignedNumber(int s16Number,uint8_t u8Column,uint16_t u8Row,uint8_t u8Length)
{
    if(s16Number < 0)                                               //显示负数
    {
        Display_ASCII('-', u8Column, u8Row);
        Display_Number(-s16Number, u8Column + 8, u8Row, u8Length);
    }
    else                                                            //显示正数
    {
        Display_ASCII(' ', u8Column, u8Row);
        Display_Number(s16Number, u8Column + 8, u8Row, u8Length);
    }
}

/***********************************************************************************************************************
 功能：显示不带符号的小数 
***********************************************************************************************************************/
void Display_Decimal(unsigned long int u32Number, char u8Column, uint16_t u8Row, uint8_t u8INT, uint8_t u8DEC)
{
    uint8_t u8DispNum, u8Length;
    u8Column = ( u8Column + ( u8INT + u8DEC ) *8);

    for(u8Length = u8DEC; u8Length > 0; u8Length--)                  // 显示小数部分
    {
        u8DispNum = u32Number % 10 + 0x30;
        Display_ASCII(u8DispNum, u8Column, u8Row);
        u8Column -= 8;
        u32Number = u32Number / 10;
    }

    Display_ASCII('.', u8Column, u8Row);                // 显示小数点
    u8Column -= 8;

    for(u8Length = u8INT; u8Length > 0; u8Length--)                  // 显示整数部分
    {
        u8DispNum = u32Number % 10 + 0x30;
        Display_ASCII(u8DispNum, u8Column, u8Row);
        u8Column -= 8;
        u32Number = u32Number / 10;
    }
}

/***********************************************************************************************************************
 功能：显示带符号的小数 
***********************************************************************************************************************/
void Display_SignedDecimal(long int s32Number, char u8Column, uint16_t u8Row, uint8_t u8INT, uint8_t u8DEC)
{
    if(s32Number < 0)
    {
        Display_ASCII('-', u8Column, u8Row);
        Display_Decimal(-s32Number, u8Column+8, u8Row, u8INT, u8DEC);
    }
    else
    {
        Display_ASCII(' ',u8Column,u8Row);
        Display_Decimal(s32Number, u8Column+8, u8Row, u8INT, u8DEC);
    }
}
#endif

#endif
#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

