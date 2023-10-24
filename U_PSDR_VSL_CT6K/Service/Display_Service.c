#include "Display_Service.h"

//////////////////////////////////////////////////////////////////////////////////////
#include "LCD_Device.h"
#include "HT1621_Device.h"
#include "string.h"

typedef struct
{
    LCD_COM_t COM;
    LCD_SEG_t SEG;
} LCD_Array_t;

LCD_Array_t LCDID_B00449A_ICON[ICON_MAX] =
{
    /*SEG1_A,               */{LCD_COM_3, LCD_SEG_29},
    /*SEG1_B,               */{LCD_COM_3, LCD_SEG_28},
    /*SEG1_C,               */{LCD_COM_1, LCD_SEG_28},
    /*SEG1_D,               */{LCD_COM_0, LCD_SEG_29},
    /*SEG1_E,               */{LCD_COM_1, LCD_SEG_29},
    /*SEG1_F,               */{LCD_COM_2, LCD_SEG_29},
    /*SEG1_G,               */{LCD_COM_2, LCD_SEG_28},
    /*SEG1_H,               */{LCD_COM_0, LCD_SEG_28},

    /*SEG2_A,               */{LCD_COM_3, LCD_SEG_27},
    /*SEG2_B,               */{LCD_COM_3, LCD_SEG_26},
    /*SEG2_C,               */{LCD_COM_1, LCD_SEG_26},
    /*SEG2_D,               */{LCD_COM_0, LCD_SEG_27},
    /*SEG2_E,               */{LCD_COM_1, LCD_SEG_27},
    /*SEG2_F,               */{LCD_COM_2, LCD_SEG_27},
    /*SEG2_G,               */{LCD_COM_2, LCD_SEG_26},
    /*SEG2_H,               */{LCD_COM_0, LCD_SEG_26},

    /*SEG3_A,               */{LCD_COM_3, LCD_SEG_25},
    /*SEG3_B,               */{LCD_COM_3, LCD_SEG_24},
    /*SEG3_C,               */{LCD_COM_1, LCD_SEG_24},
    /*SEG3_D,               */{LCD_COM_0, LCD_SEG_25},
    /*SEG3_E,               */{LCD_COM_1, LCD_SEG_25},
    /*SEG3_F,               */{LCD_COM_2, LCD_SEG_25},
    /*SEG3_G,               */{LCD_COM_2, LCD_SEG_24},
    /*SEG3_H,               */{LCD_COM_NC, LCD_SEG_NC},

    /*SEG4_A,               */{LCD_COM_3, LCD_SEG_20},
    /*SEG4_B,               */{LCD_COM_3, LCD_SEG_19},
    /*SEG4_C,               */{LCD_COM_1, LCD_SEG_19},
    /*SEG4_D,               */{LCD_COM_0, LCD_SEG_20},
    /*SEG4_E,               */{LCD_COM_1, LCD_SEG_20},
    /*SEG4_F,               */{LCD_COM_2, LCD_SEG_20},
    /*SEG4_G,               */{LCD_COM_2, LCD_SEG_19},
    /*SEG4_H,               */{LCD_COM_0, LCD_SEG_19},

    /*SEG5_A,               */{LCD_COM_3, LCD_SEG_18},
    /*SEG5_B,               */{LCD_COM_3, LCD_SEG_17},
    /*SEG5_C,               */{LCD_COM_1, LCD_SEG_17},
    /*SEG5_D,               */{LCD_COM_0, LCD_SEG_18},
    /*SEG5_E,               */{LCD_COM_1, LCD_SEG_18},
    /*SEG5_F,               */{LCD_COM_2, LCD_SEG_18},
    /*SEG5_G,               */{LCD_COM_2, LCD_SEG_17},
    /*SEG5_H,               */{LCD_COM_NC, LCD_SEG_NC},

    /*SEG6_A,               */{LCD_COM_3, LCD_SEG_15},
    /*SEG6_B,               */{LCD_COM_3, LCD_SEG_14},
    /*SEG6_C,               */{LCD_COM_1, LCD_SEG_14},
    /*SEG6_D,               */{LCD_COM_0, LCD_SEG_15},
    /*SEG6_E,               */{LCD_COM_1, LCD_SEG_15},
    /*SEG6_F,               */{LCD_COM_2, LCD_SEG_15},
    /*SEG6_G,               */{LCD_COM_2, LCD_SEG_14},
    /*SEG6_H,               */{LCD_COM_0, LCD_SEG_14},

    /*SEG7_A,               */{LCD_COM_3, LCD_SEG_13},
    /*SEG7_B,               */{LCD_COM_3, LCD_SEG_12},
    /*SEG7_C,               */{LCD_COM_1, LCD_SEG_12},
    /*SEG7_D,               */{LCD_COM_0, LCD_SEG_13},
    /*SEG7_E,               */{LCD_COM_1, LCD_SEG_13},
    /*SEG7_F,               */{LCD_COM_2, LCD_SEG_13},
    /*SEG7_G,               */{LCD_COM_2, LCD_SEG_12},
    /*SEG7_H,               */{LCD_COM_0, LCD_SEG_12},

    /*SEG8_A,               */{LCD_COM_3, LCD_SEG_11},
    /*SEG8_B,               */{LCD_COM_3, LCD_SEG_10},
    /*SEG8_C,               */{LCD_COM_1, LCD_SEG_10},
    /*SEG8_D,               */{LCD_COM_0, LCD_SEG_11},
    /*SEG8_E,               */{LCD_COM_1, LCD_SEG_11},
    /*SEG8_F,               */{LCD_COM_2, LCD_SEG_11},
    /*SEG8_G,               */{LCD_COM_2, LCD_SEG_10},
    /*SEG8_H,               */{LCD_COM_NC, LCD_SEG_NC},
    /*                      */
    /*ICON_INLET_INPUT,     */{LCD_COM_0, LCD_SEG_30},
    /*ICON_INLET_BATT,      */{LCD_COM_1, LCD_SEG_30},
    /*ICON_INLET_TEMP,      */{LCD_COM_2, LCD_SEG_30},
    /*ICON_INLET_BPS,       */{LCD_COM_3, LCD_SEG_30},
    /*ICON_INLET_AC,        */{LCD_COM_3, LCD_SEG_31},
    /*ICON_INLET_PV,        */{LCD_COM_2, LCD_SEG_31},
    /*ICON_INLET_RST_R,     */{LCD_COM_1, LCD_SEG_31},
    /*ICON_INLET_RST_S,     */{LCD_COM_0, LCD_SEG_31},
    /*ICON_INLET_RST_T,     */{LCD_COM_0, LCD_SEG_23},
    /*ICON_INLET_KW_K,      */{LCD_COM_3, LCD_SEG_23},
    /*ICON_INLET_KW_W,      */{LCD_COM_3, LCD_SEG_22},
    /*ICON_INLET_KVA_K,     */{LCD_COM_2, LCD_SEG_23},
    /*ICON_INLET_KVA_V,     */{LCD_COM_2, LCD_SEG_22},
    /*ICON_INLET_KVA_A,     */{LCD_COM_2, LCD_SEG_21},
    /*ICON_INLET_PC_P,      */{LCD_COM_1, LCD_SEG_23},
    /*ICON_INLET_PC_C,      */{LCD_COM_1, LCD_SEG_22},
    /*ICON_INLET_HZ,        */{LCD_COM_0, LCD_SEG_24},

    /*ICON_OUTLET_OUTPUT,   */{LCD_COM_3, LCD_SEG_7},
    /*ICON_OUTLET_BATT,     */{LCD_COM_2, LCD_SEG_7},
    /*ICON_OUTLET_LOAD,     */{LCD_COM_1, LCD_SEG_7},
    /*ICON_OUTLET_KW_K,     */{LCD_COM_3, LCD_SEG_9},
    /*ICON_OUTLET_KW_W,     */{LCD_COM_3, LCD_SEG_8},
    /*ICON_OUTLET_KVA_K,    */{LCD_COM_2, LCD_SEG_9},
    /*ICON_OUTLET_KVA_V,    */{LCD_COM_2, LCD_SEG_8},
    /*ICON_OUTLET_KVA_A,    */{LCD_COM_1, LCD_SEG_8},
    /*ICON_OUTLET_PC_P,     */{LCD_COM_1, LCD_SEG_9},
    /*ICON_OUTLET_PC_C,     */{LCD_COM_0, LCD_SEG_8},
    /*ICON_OUTLET_HZ,       */{LCD_COM_0, LCD_SEG_10},

    /*ICON_FLOW_DUAL,       */{LCD_COM_1, LCD_SEG_0},
    /*ICON_FLOW_LINE,       */{LCD_COM_2, LCD_SEG_0},
    /*ICON_FLOW_PV,         */{LCD_COM_3, LCD_SEG_0},
    /*ICON_FLOW_PFC,        */{LCD_COM_2, LCD_SEG_1},
    /*ICON_FLOW_INV,        */{LCD_COM_1, LCD_SEG_4},
    /*ICON_FLOW_LOAD,       */{LCD_COM_1, LCD_SEG_5},

    /*ICON_FLOW_LINE2PFC,   */{LCD_COM_1, LCD_SEG_1},
    /*ICON_FLOW_LINE2LOAD1, */{LCD_COM_0, LCD_SEG_1},
    /*ICON_FLOW_LINE2LOAD2, */{LCD_COM_0, LCD_SEG_4},
    /*ICON_FLOW_PV2PFC,     */{LCD_COM_3, LCD_SEG_1},
    /*ICON_FLOW_PFC2INV,    */{LCD_COM_0, LCD_SEG_3},
    /*ICON_FLOW_PFC2BAT,    */{LCD_COM_1, LCD_SEG_3},
    /*ICON_FLOW_BAT2INV,    */{LCD_COM_2, LCD_SEG_3},
    /*ICON_FLOW_INV2LOAD,   */{LCD_COM_2, LCD_SEG_4},

    /*ICON_BATT_FRAME,      */{LCD_COM_3, LCD_SEG_3},
    /*ICON_BATT_25_PER,     */{LCD_COM_3, LCD_SEG_2},
    /*ICON_BATT_50_PER,     */{LCD_COM_2, LCD_SEG_2},
    /*ICON_BATT_75_PER,     */{LCD_COM_1, LCD_SEG_2},
    /*ICON_BATT_100_PER,    */{LCD_COM_0, LCD_SEG_2},

    /*ICON_LOAD_FRAME,      */{LCD_COM_3, LCD_SEG_5},
    /*ICON_LOAD_25_PER,     */{LCD_COM_3, LCD_SEG_6},
    /*ICON_LOAD_50_PER,     */{LCD_COM_2, LCD_SEG_6},
    /*ICON_LOAD_75_PER,     */{LCD_COM_1, LCD_SEG_6},
    /*ICON_LOAD_100_PER,    */{LCD_COM_0, LCD_SEG_6},

    /*ICON_ERROR_FRAME,     */{LCD_COM_2, LCD_SEG_16},
    /*ICON_ERROR_TEXT,      */{LCD_COM_1, LCD_SEG_16},
    /*ICON_ERROR_SHORT,     */{LCD_COM_0, LCD_SEG_9},
    /*ICON_ERROR_OVERLOAD,  */{LCD_COM_0, LCD_SEG_7},
    /*ICON_ERROR_LOWBATT,   */{LCD_COM_3, LCD_SEG_4},

    /*ICON_OTHER_TIME_H,    */{LCD_COM_3, LCD_SEG_21},
    /*ICON_OTHER_TIME_M,    */{LCD_COM_1, LCD_SEG_21},
    /*ICON_OTHER_TIMER,     */{LCD_COM_0, LCD_SEG_21},
    /*ICON_OTHER_FIX,       */{LCD_COM_3, LCD_SEG_16},
    /*ICON_OTHER_MENU_FRAME,*/{LCD_COM_0, LCD_SEG_17},
    /*ICON_OTHER_PARTLINE,  */{LCD_COM_0, LCD_SEG_22},
    /*ICON_OTHER_ECO,       */{LCD_COM_0, LCD_SEG_0},
    /*ICON_OTHER_CF,        */{LCD_COM_0, LCD_SEG_5},
    /*ICON_OTHER_MUTE,      */{LCD_COM_0, LCD_SEG_16},
    /*ICON_OTHER_P,         */{LCD_COM_2, LCD_SEG_5},
};

LCD_Array_t LCDID_B00449B_ICON[ICON_MAX] =
{
    /*SEG1_A,               */{LCD_COM_3, LCD_SEG_27},
    /*SEG1_B,               */{LCD_COM_3, LCD_SEG_26},
    /*SEG1_C,               */{LCD_COM_1, LCD_SEG_26},
    /*SEG1_D,               */{LCD_COM_0, LCD_SEG_27},
    /*SEG1_E,               */{LCD_COM_1, LCD_SEG_27},
    /*SEG1_F,               */{LCD_COM_2, LCD_SEG_27},
    /*SEG1_G,               */{LCD_COM_2, LCD_SEG_26},
    /*SEG1_H,               */{LCD_COM_0, LCD_SEG_26},

    /*SEG2_A,               */{LCD_COM_3, LCD_SEG_29},
    /*SEG2_B,               */{LCD_COM_3, LCD_SEG_28},
    /*SEG2_C,               */{LCD_COM_1, LCD_SEG_28},
    /*SEG2_D,               */{LCD_COM_0, LCD_SEG_29},
    /*SEG2_E,               */{LCD_COM_1, LCD_SEG_29},
    /*SEG2_F,               */{LCD_COM_2, LCD_SEG_29},
    /*SEG2_G,               */{LCD_COM_2, LCD_SEG_28},
    /*SEG2_H,               */{LCD_COM_0, LCD_SEG_28},

    /*SEG3_A,               */{LCD_COM_3, LCD_SEG_25},
    /*SEG3_B,               */{LCD_COM_3, LCD_SEG_24},
    /*SEG3_C,               */{LCD_COM_1, LCD_SEG_24},
    /*SEG3_D,               */{LCD_COM_0, LCD_SEG_25},
    /*SEG3_E,               */{LCD_COM_1, LCD_SEG_25},
    /*SEG3_F,               */{LCD_COM_2, LCD_SEG_25},
    /*SEG3_G,               */{LCD_COM_2, LCD_SEG_24},
    /*SEG3_H,               */{LCD_COM_NC, LCD_SEG_NC},

    /*SEG4_A,               */{LCD_COM_3, LCD_SEG_20},
    /*SEG4_B,               */{LCD_COM_3, LCD_SEG_19},
    /*SEG4_C,               */{LCD_COM_1, LCD_SEG_19},
    /*SEG4_D,               */{LCD_COM_0, LCD_SEG_20},
    /*SEG4_E,               */{LCD_COM_1, LCD_SEG_20},
    /*SEG4_F,               */{LCD_COM_2, LCD_SEG_20},
    /*SEG4_G,               */{LCD_COM_2, LCD_SEG_19},
    /*SEG4_H,               */{LCD_COM_0, LCD_SEG_19},

    /*SEG5_A,               */{LCD_COM_3, LCD_SEG_18},
    /*SEG5_B,               */{LCD_COM_3, LCD_SEG_17},
    /*SEG5_C,               */{LCD_COM_1, LCD_SEG_17},
    /*SEG5_D,               */{LCD_COM_0, LCD_SEG_18},
    /*SEG5_E,               */{LCD_COM_1, LCD_SEG_18},
    /*SEG5_F,               */{LCD_COM_2, LCD_SEG_18},
    /*SEG5_G,               */{LCD_COM_2, LCD_SEG_17},
    /*SEG5_H,               */{LCD_COM_NC, LCD_SEG_NC},

    /*SEG6_A,               */{LCD_COM_3, LCD_SEG_15},
    /*SEG6_B,               */{LCD_COM_3, LCD_SEG_14},
    /*SEG6_C,               */{LCD_COM_1, LCD_SEG_14},
    /*SEG6_D,               */{LCD_COM_0, LCD_SEG_15},
    /*SEG6_E,               */{LCD_COM_1, LCD_SEG_15},
    /*SEG6_F,               */{LCD_COM_2, LCD_SEG_15},
    /*SEG6_G,               */{LCD_COM_2, LCD_SEG_14},
    /*SEG6_H,               */{LCD_COM_0, LCD_SEG_14},

    /*SEG7_A,               */{LCD_COM_3, LCD_SEG_13},
    /*SEG7_B,               */{LCD_COM_3, LCD_SEG_12},
    /*SEG7_C,               */{LCD_COM_1, LCD_SEG_12},
    /*SEG7_D,               */{LCD_COM_0, LCD_SEG_13},
    /*SEG7_E,               */{LCD_COM_1, LCD_SEG_13},
    /*SEG7_F,               */{LCD_COM_2, LCD_SEG_13},
    /*SEG7_G,               */{LCD_COM_2, LCD_SEG_12},
    /*SEG7_H,               */{LCD_COM_0, LCD_SEG_12},

    /*SEG8_A,               */{LCD_COM_3, LCD_SEG_11},
    /*SEG8_B,               */{LCD_COM_3, LCD_SEG_10},
    /*SEG8_C,               */{LCD_COM_1, LCD_SEG_10},
    /*SEG8_D,               */{LCD_COM_0, LCD_SEG_11},
    /*SEG8_E,               */{LCD_COM_1, LCD_SEG_11},
    /*SEG8_F,               */{LCD_COM_2, LCD_SEG_11},
    /*SEG8_G,               */{LCD_COM_2, LCD_SEG_10},
    /*SEG8_H,               */{LCD_COM_NC, LCD_SEG_NC},

    /*ICON_INLET_INPUT,     */{LCD_COM_0, LCD_SEG_30},
    /*ICON_INLET_BATT,      */{LCD_COM_1, LCD_SEG_30},
    /*ICON_INLET_TEMP,      */{LCD_COM_2, LCD_SEG_30},
    /*ICON_INLET_BPS,       */{LCD_COM_3, LCD_SEG_30},
    /*ICON_INLET_AC,        */{LCD_COM_3, LCD_SEG_31},
    /*ICON_INLET_PV,        */{LCD_COM_2, LCD_SEG_31},
    /*ICON_INLET_RST_R,     */{LCD_COM_1, LCD_SEG_31},
    /*ICON_INLET_RST_S,     */{LCD_COM_0, LCD_SEG_31},
    /*ICON_INLET_RST_T,     */{LCD_COM_0, LCD_SEG_23},
    /*ICON_INLET_KW_K,      */{LCD_COM_3, LCD_SEG_23},
    /*ICON_INLET_KW_W,      */{LCD_COM_3, LCD_SEG_22},
    /*ICON_INLET_KVA_K,     */{LCD_COM_2, LCD_SEG_23},
    /*ICON_INLET_KVA_V,     */{LCD_COM_2, LCD_SEG_22},
    /*ICON_INLET_KVA_A,     */{LCD_COM_2, LCD_SEG_21},
    /*ICON_INLET_PC_P,      */{LCD_COM_1, LCD_SEG_23},
    /*ICON_INLET_PC_C,      */{LCD_COM_1, LCD_SEG_22},
    /*ICON_INLET_HZ,        */{LCD_COM_0, LCD_SEG_24},

    /*ICON_OUTLET_OUTPUT,   */{LCD_COM_3, LCD_SEG_7},
    /*ICON_OUTLET_BATT,     */{LCD_COM_2, LCD_SEG_7},
    /*ICON_OUTLET_LOAD,     */{LCD_COM_1, LCD_SEG_7},
    /*ICON_OUTLET_KW_K,     */{LCD_COM_3, LCD_SEG_9},
    /*ICON_OUTLET_KW_W,     */{LCD_COM_3, LCD_SEG_8},
    /*ICON_OUTLET_KVA_K,    */{LCD_COM_2, LCD_SEG_9},
    /*ICON_OUTLET_KVA_V,    */{LCD_COM_2, LCD_SEG_8},
    /*ICON_OUTLET_KVA_A,    */{LCD_COM_1, LCD_SEG_8},
    /*ICON_OUTLET_PC_P,     */{LCD_COM_1, LCD_SEG_9},
    /*ICON_OUTLET_PC_C,     */{LCD_COM_0, LCD_SEG_8},
    /*ICON_OUTLET_HZ,       */{LCD_COM_0, LCD_SEG_10},

    /*ICON_FLOW_DUAL,       */{LCD_COM_1, LCD_SEG_0},
    /*ICON_FLOW_LINE,       */{LCD_COM_2, LCD_SEG_0},
    /*ICON_FLOW_PV,         */{LCD_COM_3, LCD_SEG_0},
    /*ICON_FLOW_PFC,        */{LCD_COM_2, LCD_SEG_1},
    /*ICON_FLOW_INV,        */{LCD_COM_1, LCD_SEG_4},
    /*ICON_FLOW_LOAD,       */{LCD_COM_1, LCD_SEG_5},

    /*ICON_FLOW_LINE2PFC,   */{LCD_COM_1, LCD_SEG_1},
    /*ICON_FLOW_LINE2LOAD1, */{LCD_COM_0, LCD_SEG_1},
    /*ICON_FLOW_LINE2LOAD2, */{LCD_COM_0, LCD_SEG_4},
    /*ICON_FLOW_PV2PFC,     */{LCD_COM_3, LCD_SEG_1},
    /*ICON_FLOW_PFC2INV,    */{LCD_COM_0, LCD_SEG_3},
    /*ICON_FLOW_PFC2BAT,    */{LCD_COM_1, LCD_SEG_3},
    /*ICON_FLOW_BAT2INV,    */{LCD_COM_2, LCD_SEG_3},
    /*ICON_FLOW_INV2LOAD,   */{LCD_COM_2, LCD_SEG_4},

    /*ICON_BATT_FRAME,      */{LCD_COM_3, LCD_SEG_3},
    /*ICON_BATT_25_PER,     */{LCD_COM_3, LCD_SEG_2},
    /*ICON_BATT_50_PER,     */{LCD_COM_2, LCD_SEG_2},
    /*ICON_BATT_75_PER,     */{LCD_COM_1, LCD_SEG_2},
    /*ICON_BATT_100_PER,    */{LCD_COM_0, LCD_SEG_2},

    /*ICON_LOAD_FRAME,      */{LCD_COM_3, LCD_SEG_5},
    /*ICON_LOAD_25_PER,     */{LCD_COM_3, LCD_SEG_6},
    /*ICON_LOAD_50_PER,     */{LCD_COM_2, LCD_SEG_6},
    /*ICON_LOAD_75_PER,     */{LCD_COM_1, LCD_SEG_6},
    /*ICON_LOAD_100_PER,    */{LCD_COM_0, LCD_SEG_6},

    /*ICON_ERROR_FRAME,     */{LCD_COM_2, LCD_SEG_16},
    /*ICON_ERROR_TEXT,      */{LCD_COM_1, LCD_SEG_16},
    /*ICON_ERROR_SHORT,     */{LCD_COM_0, LCD_SEG_9},
    /*ICON_ERROR_OVERLOAD,  */{LCD_COM_0, LCD_SEG_7},
    /*ICON_ERROR_LOWBATT,   */{LCD_COM_3, LCD_SEG_4},

    /*ICON_OTHER_TIME_H,    */{LCD_COM_3, LCD_SEG_21},
    /*ICON_OTHER_TIME_M,    */{LCD_COM_1, LCD_SEG_21},
    /*ICON_OTHER_TIMER,     */{LCD_COM_0, LCD_SEG_21},
    /*ICON_OTHER_FIX,       */{LCD_COM_3, LCD_SEG_16},
    /*ICON_OTHER_MENU_FRAME,*/{LCD_COM_0, LCD_SEG_17},
    /*ICON_OTHER_PARTLINE,  */{LCD_COM_0, LCD_SEG_22},
    /*ICON_OTHER_ECO,       */{LCD_COM_0, LCD_SEG_0},
    /*ICON_OTHER_CF,        */{LCD_COM_0, LCD_SEG_5},
    /*ICON_OTHER_MUTE,      */{LCD_COM_0, LCD_SEG_16},
    /*ICON_OTHER_P,         */{LCD_COM_2, LCD_SEG_5},
};

typedef struct
{
    LCD_TypeDefine_t tLCD_ID;                       //屏ID
    LCD_Array_t tLCD_Icon[ICON_MAX];                //屏坐标地址
    uint8_t u8LCD_Buff_Length;                      //屏显存长度
    uint8_t u8Flash_ARR_x100ms;                     //闪烁周期
    uint8_t u8Flash_CCR_x100ms;                     //闪烁占空比
    uint8_t u8Flash_CNT_x100ms;                     //闪烁时间计数器
    uint8_t u8LCD_Flash[LCD_BUFF_MAX_SUPPORT];      //闪烁使能（固定闪烁频率）
    uint8_t u8LCD_Data[LCD_BUFF_MAX_SUPPORT];       //数据缓存
    uint8_t u8LCD_Buff[LCD_BUFF_MAX_SUPPORT];       //显示缓存
} LCD_Data_t;
LCD_Data_t tLCD_Data;

//--屏显存长度 u8LCD_Buff_Length
uint8_t LCD_Length_Table[LCD_ID_MAX] =
{
    /*LCD_ID_B00449A    */32,
    /*LCD_ID_B00449B    */32,
};

//--屏坐标初始化，应对不同屏ID
void LCD_Location_Initial(void)
{
    if(LCD_ID_B00449A == tLCD_Data.tLCD_ID)
    {
        memcpy(&tLCD_Data.tLCD_Icon, LCDID_B00449A_ICON, sizeof(tLCD_Data.tLCD_Icon));
    }
    else if(LCD_ID_B00449B == tLCD_Data.tLCD_ID)
    {
        memcpy(&tLCD_Data.tLCD_Icon, LCDID_B00449B_ICON, sizeof(tLCD_Data.tLCD_Icon));
    }
    else
    {
        memcpy(&tLCD_Data.tLCD_Icon, LCDID_B00449A_ICON, sizeof(tLCD_Data.tLCD_Icon));
    }
}

// LCD ICON ON/OFF PS:LCD_Set_ICON_ONOFF(ICON_OTHER_FIX,EN_ENABLE);
void LCD_Set_ICON_ONOFF(LCD_Icon_Type_t u8Icon_Index, EN_t data, LCD_FlashMode_t flash_mode)
{
    if (EN_ENABLE == data)
    {
        tLCD_Data.u8LCD_Data[tLCD_Data.tLCD_Icon[u8Icon_Index].SEG] |= BIT(tLCD_Data.tLCD_Icon[u8Icon_Index].COM);
    }
    else
    {
        tLCD_Data.u8LCD_Data[tLCD_Data.tLCD_Icon[u8Icon_Index].SEG] &= ~BIT(tLCD_Data.tLCD_Icon[u8Icon_Index].COM);
    }
    if (FLASH_ON == flash_mode)
    {
        tLCD_Data.u8LCD_Flash[tLCD_Data.tLCD_Icon[u8Icon_Index].SEG] |= BIT(tLCD_Data.tLCD_Icon[u8Icon_Index].COM);
    }
    else
    {
        tLCD_Data.u8LCD_Flash[tLCD_Data.tLCD_Icon[u8Icon_Index].SEG] &= ~BIT(tLCD_Data.tLCD_Icon[u8Icon_Index].COM);
    }
}

/*
 *       A
 *      ---
 *    F|   | B
 *      -G-
 *    E|   | C
 *      ---        -
 *       D        H
 */

#define DIS_A       BIT(0)
#define DIS_B       BIT(1)
#define DIS_C       BIT(2)
#define DIS_D       BIT(3)
#define DIS_E       BIT(4)
#define DIS_F       BIT(5)
#define DIS_G       BIT(6)
#define DIS_H       BIT(7)

const uint8_t FontLibrary[LED_SPEC_CHAR_NUM] =
{
    /* 0 */(DIS_F | DIS_E | DIS_D | DIS_C | DIS_B | DIS_A),
    /* 1 */(DIS_C | DIS_B),
    /* 2 */(DIS_G | DIS_E | DIS_D | DIS_B | DIS_A),
    /* 3 */(DIS_G | DIS_D | DIS_C | DIS_B | DIS_A),
    /* 4 */(DIS_G | DIS_F | DIS_C | DIS_B),
    /* 5 */(DIS_G | DIS_F | DIS_D | DIS_C | DIS_A),
    /* 6 */(DIS_G | DIS_F | DIS_E | DIS_D | DIS_C | DIS_A),
    /* 7 */(DIS_C | DIS_B | DIS_A),
    /* 8 */(DIS_G | DIS_F | DIS_E | DIS_D | DIS_C | DIS_B | DIS_A),
    /* 9 */(DIS_G | DIS_F | DIS_D | DIS_C | DIS_B | DIS_A),

    /* A */(DIS_G | DIS_F | DIS_E | DIS_C | DIS_B | DIS_A),
    /* B */(DIS_G | DIS_F | DIS_E | DIS_D | DIS_C ),
    /* C */(DIS_F | DIS_E | DIS_D | DIS_A),
    /* D */(DIS_G | DIS_E | DIS_D | DIS_C | DIS_B),
    /* E */(DIS_G | DIS_F | DIS_E | DIS_D | DIS_A),
    /* F */(DIS_G | DIS_F | DIS_E | DIS_A),
    /* G */(DIS_F | DIS_E | DIS_D | DIS_C | DIS_A),
    /* H */(DIS_G | DIS_F | DIS_E | DIS_C | DIS_B),
    /* I */(DIS_F | DIS_E),
    /* J */(0),
    /* K */(0),
    /* L */(DIS_F | DIS_E | DIS_D),
    /* M */(DIS_G | DIS_E | DIS_C),
    /* N */(DIS_F | DIS_E | DIS_C | DIS_B | DIS_A),
    /* O */(DIS_F | DIS_E | DIS_D | DIS_C | DIS_B | DIS_A),
    /* P */(DIS_G | DIS_F | DIS_E | DIS_B | DIS_A),
    /* Q */(DIS_G | DIS_F | DIS_C | DIS_B | DIS_A),
    /* R */(DIS_G | DIS_F | DIS_E),
    /* S */(DIS_G | DIS_F | DIS_D | DIS_C | DIS_A),
    /* T */(DIS_G | DIS_F | DIS_E | DIS_D),
    /* U */(DIS_F | DIS_E | DIS_D | DIS_C | DIS_B),
    /* V */(DIS_G | DIS_F | DIS_B),
    /* W */(DIS_E | DIS_D | DIS_C),

    /* o */(DIS_G | DIS_E | DIS_D | DIS_C),

    /*rail*/(DIS_G),
    /* _ */(DIS_D),
    /* NONE  */0,
};

typedef enum
{
    SEG_A = 0,
    SEG_B,
    SEG_C,
    SEG_D,
    SEG_E,
    SEG_F,
    SEG_G,
    SEG_H,
    SEG_MAX,
} LCD_Section_Type_t;

uint8_t LCD_Nixie_Tube[NIXIE_TUBE_MAX][SEG_MAX] =
{
    {SEG1_A, SEG1_B, SEG1_C, SEG1_D, SEG1_E, SEG1_F, SEG1_G, SEG1_H},
    {SEG2_A, SEG2_B, SEG2_C, SEG2_D, SEG2_E, SEG2_F, SEG2_G, SEG2_H},
    {SEG3_A, SEG3_B, SEG3_C, SEG3_D, SEG3_E, SEG3_F, SEG3_G, SEG3_H},
    {SEG4_A, SEG4_B, SEG4_C, SEG4_D, SEG4_E, SEG4_F, SEG4_G, SEG4_H},
    {SEG5_A, SEG5_B, SEG5_C, SEG5_D, SEG5_E, SEG5_F, SEG5_G, SEG5_H},
    {SEG6_A, SEG6_B, SEG6_C, SEG6_D, SEG6_E, SEG6_F, SEG6_G, SEG6_H},
    {SEG7_A, SEG7_B, SEG7_C, SEG7_D, SEG7_E, SEG7_F, SEG7_G, SEG7_H},
    {SEG8_A, SEG8_B, SEG8_C, SEG8_D, SEG8_E, SEG8_F, SEG8_G, SEG8_H},
};

//--设置单个数码管数据
void LCD_Set_SEG_Data(LCD_Nixie_Tube_Type_t numb, Leds_SpecChar_t data, EN_t point_en, LCD_FlashMode_t flash_mode)
{
    uint8_t u8Temp_Data_A;
    uint8_t u8Display_Value = FontLibrary[data];
    uint8_t u8Icon_Index;
    for (u8Temp_Data_A = 0; u8Temp_Data_A < SEG_MAX; u8Temp_Data_A++)
    {
        u8Icon_Index  = LCD_Nixie_Tube[numb][u8Temp_Data_A];
        LCD_Set_ICON_ONOFF(u8Icon_Index, (u8Display_Value & 0x01), flash_mode);
        u8Display_Value >>= 1;
    }
    u8Icon_Index = LCD_Nixie_Tube[numb][SEG_H];
    LCD_Set_ICON_ONOFF(u8Icon_Index, point_en, flash_mode);
}


typedef struct
{
    LCD_Nixie_Tube_Type_t tDigitron_BIT_X[DIS_SEGMAX];
    uint8_t u8Digitron_Number;
} LCD_Digitron_Type_t;

LCD_Digitron_Type_t LCD_Digitron_Group[GROUP_MAX] =
{
    /* GROUP_INPUT    */{{NIXIE_TUBE_1, NIXIE_TUBE_2, NIXIE_TUBE_3    },    3},
    /* GROUP_MENU    */{{NIXIE_TUBE_4, NIXIE_TUBE_5, NIXIE_TUBE_NC    },    2},
    /* GROUP_OUTPUT    */{{NIXIE_TUBE_6, NIXIE_TUBE_7, NIXIE_TUBE_8    },     3},
};

//--数码管分组后，设置一组数码管显示的整数内容
void LCD_Set_Display_Interger(LCD_Digitron_Group_Type_t group_type, uint16_t data, uint8_t decimal)
{
    uint8_t u8Temp_Data_A;
    uint8_t u8Display_Lengths;
    uint8_t u8Integer_Cache[DIS_SEGMAX];
    uint16_t u16Data_Temp;
    u16Data_Temp = data;
    u8Display_Lengths = LCD_Digitron_Group[group_type].u8Digitron_Number;

    if(u8Display_Lengths > 0 )
    {
        if(u16Data_Temp < 0)
        {
            u16Data_Temp = -u16Data_Temp;
            u8Display_Lengths = u8Display_Lengths - 1;
            u8Integer_Cache[u8Display_Lengths] = rail;
        }
        if(u8Display_Lengths > 0)//针对可以显示多少位长度，进行数值限幅
        {
            switch (u8Display_Lengths)
            {
                case 1:
                    if(u16Data_Temp >= 10)
                    {
                        u16Data_Temp = 9;
                    }
                    break;
                case 2:
                    if(u16Data_Temp >= 100)
                    {
                        u16Data_Temp = 99;
                    }
                    break;
                case 3:
                    if(u16Data_Temp >= 1000)
                    {
                        u16Data_Temp = 999;
                    }
                    break;
                default:
                    break;
            }

            for (u8Temp_Data_A = 0; u8Temp_Data_A < u8Display_Lengths; u8Temp_Data_A++)
            {
                if(u8Temp_Data_A != 0)
                {
                    u16Data_Temp = u16Data_Temp / 10;
                    if(u16Data_Temp > 0)
                    {
                        u8Integer_Cache[u8Temp_Data_A] = u16Data_Temp % 10;
                    }
                    else
                    {
                        u8Integer_Cache[u8Temp_Data_A] = NONE;
                    }
                }
                else
                {
                    u8Integer_Cache[u8Temp_Data_A] = u16Data_Temp % 10;
                }
            }
        }
        else
        {
            memset(&u8Integer_Cache, NONE, sizeof(u8Integer_Cache));
        }
    }
    for (u8Temp_Data_A = 0; u8Temp_Data_A < LCD_Digitron_Group[group_type].u8Digitron_Number; u8Temp_Data_A++)
    {
        LCD_Set_SEG_Data(LCD_Digitron_Group[group_type].tDigitron_BIT_X[u8Temp_Data_A], u8Integer_Cache[u8Temp_Data_A], EN_DISABLE, FLASH_OFF);
    }
}

//--数码管分组后，设置一组数码管显示的浮点数内容
void LCD_Set_Display_Number_AUTO(LCD_Digitron_Group_Type_t group_type, float32_t data, uint8_t decimal)
{
    uint8_t i;
    uint8_t display_lengths;                    //数字显示数位
    uint8_t integer_lengths;                    //整数位
    uint8_t decimal_lengths;                    //小数位
    uint8_t integer_cache[DIS_SEGMAX];          //显示缓存
    EN_t point_cache[DIS_SEGMAX];               //小数点缓存
    float32_t data_temp;                        //浮点运算缓存
    uint32_t data_temp_integer;                 //整数运算缓存

    data_temp = data;
    display_lengths = LCD_Digitron_Group[group_type].u8Digitron_Number;
    if (display_lengths > 0)
    {
        if(data_temp < 0)//扣除负号
        {
            data_temp = -data_temp;
            display_lengths = display_lengths - 1;
            integer_cache[display_lengths] = rail;
        }
        if(display_lengths > 0)//扣掉负号后还剩多少位可以显示？
        {
            switch (display_lengths)
            {
                case 1:
                    if(data_temp >= 10.0)
                    {
                        data_temp = 9.0;

                    }
                    if (data_temp >= 1.0)
                    {
                        // integer_lengths = 1;
                        decimal_lengths = 0;
                    }
                    else
                    {
                        // integer_lengths = 0;
                        decimal_lengths = 1;
                    }
                    break;
                case 2:
                    if(data_temp >= 100.0)
                    {
                        data_temp = 99.0;
                    }
                    if(data_temp >= 10.0)
                    {
                        // integer_lengths = 2;
                        decimal_lengths = 0;
                    }
                    else if(data_temp >= 1.0)
                    {
                        // integer_lengths = 1;
                        decimal_lengths = 1;
                    }
                    else
                    {
                        // integer_lengths = 0;
                        decimal_lengths = 2;
                    }
                    break;
                case 3:
                    if(data_temp >= 1000.0)
                    {
                        data_temp = 999.0;
                    }
                    if(data_temp >= 100.0)
                    {
                        // integer_lengths = 3;
                        decimal_lengths = 0;
                    }
                    else if(data_temp >= 10.0)
                    {
                        // integer_lengths = 2;
                        decimal_lengths = 1;
                    }
                    else if(data_temp >= 1.0)
                    {
                        // integer_lengths = 1;
                        decimal_lengths = 2;
                    }
                    else
                    {
                        // integer_lengths = 0;
                        decimal_lengths = 3;
                    }
                    break;
                default:
                    break;
            }
            //显示缓存 负号默认左对齐，数据默认右对齐

            if(decimal_lengths > decimal)//根据给进来的浮点要求，结合可以显示的位数，重新设置浮点和整数显示的位数
            {
                decimal_lengths = decimal;
                integer_lengths = display_lengths - decimal_lengths;
            }

            data_temp_integer = (uint32_t)data_temp;//处理整数部分
            if(integer_lengths > 0)
            {
                for (i = 0; i < integer_lengths; i++)
                {
                    if(i != 0)
                    {
                        data_temp_integer = data_temp_integer / 10;
                        if(data_temp_integer > 0)
                        {
                            integer_cache[decimal_lengths + i] = data_temp_integer % 10;
                        }
                        else
                        {
                            integer_cache[decimal_lengths + i] = NONE;
                        }
                        point_cache[decimal_lengths + i] = EN_DISABLE;
                    }
                    else
                    {
                        integer_cache[decimal_lengths + i] = data_temp_integer % 10;
                        point_cache[decimal_lengths + i] = EN_ENABLE;
                    }
                }
            }
            else
            {

            }

            //处理小数部分
            if(decimal_lengths > 0)//小数位变整数位
            {
                for (i = 0; i < decimal_lengths; i++)
                {
                    data_temp = data_temp * 10;
                }
            }

            data_temp_integer = (uint32_t)data_temp;
            for (i = 0; i < decimal_lengths; i++)
            {
                data_temp_integer = data_temp_integer / 10;
                integer_cache[i] = data_temp_integer % 10;
                point_cache[i] = EN_DISABLE;
            }
        }
        else//没有数字位的情况
        {
            memset(&integer_cache, NONE, sizeof(integer_cache));
            memset(&point_cache, EN_DISABLE, sizeof(point_cache));
        }
    }

    for (i = 0; i < LCD_Digitron_Group[group_type].u8Digitron_Number; i++)
    {
        LCD_Set_SEG_Data(LCD_Digitron_Group[group_type].tDigitron_BIT_X[i], integer_cache[i], point_cache[i], FLASH_OFF);
    }
}

//--数码管分组后，对于菜单分组，做显示逻辑的补充处理
void LCD_Set_SEG_Menu(LCD_Digitron_Group_Type_t group_type, Leds_SpecChar_t string, uint8_t data)
{
    if(10 > data)
    {
        LCD_Set_SEG_Data(LCD_Digitron_Group[group_type].tDigitron_BIT_X[DIS_SEG1], string, EN_DISABLE, FLASH_OFF);
        LCD_Set_SEG_Data(LCD_Digitron_Group[group_type].tDigitron_BIT_X[DIS_SEG2], data, EN_DISABLE, FLASH_OFF);
    }
    else
    {
        LCD_Set_SEG_Data(LCD_Digitron_Group[group_type].tDigitron_BIT_X[DIS_SEG1], data / 10, EN_DISABLE, FLASH_OFF);
        LCD_Set_SEG_Data(LCD_Digitron_Group[group_type].tDigitron_BIT_X[DIS_SEG2], data, EN_DISABLE, FLASH_OFF);
    }
}

void LCD_Set_Display_String(LCD_Digitron_Group_Type_t group_type, Leds_SpecChar_t *string)
{
    uint8_t i;
    for (i = 0; i < LCD_Digitron_Group[group_type].u8Digitron_Number; i++)
    {
        LCD_Set_SEG_Data(LCD_Digitron_Group[group_type].tDigitron_BIT_X[i], string[LCD_Digitron_Group[group_type].u8Digitron_Number - 1 - i], EN_DISABLE, FLASH_OFF);
    }
}


/////////////////////////
//--
//--
void LCD_Initial(void)
{
    HT1621_Device_Initial();
    // SET_LCD_BACKLIGHT(EN_ENABLE);
    tLCD_Data.tLCD_ID = LCD_ID_B00449A;
    tLCD_Data.u8LCD_Buff_Length = LCD_Length_Table[tLCD_Data.tLCD_ID];

    tLCD_Data.u8Flash_ARR_x100ms = 20;
    tLCD_Data.u8Flash_CCR_x100ms = 10;
    tLCD_Data.u8Flash_CNT_x100ms = 0;

    memset(&(tLCD_Data.u8LCD_Buff), 0xFF, sizeof(tLCD_Data.u8LCD_Buff));
}

void Display_Service(void)
{
    uint8_t i;
    //-- 100ms时基
    {
        tLCD_Data.u8Flash_CNT_x100ms++;
        if(tLCD_Data.u8Flash_CNT_x100ms >= tLCD_Data.u8Flash_ARR_x100ms)
        {
            tLCD_Data.u8Flash_CNT_x100ms = 0;
        }

        //-- 100ms刷新一次数据
        if(tLCD_Data.u8Flash_CNT_x100ms <= tLCD_Data.u8Flash_CCR_x100ms)
        {
            //-- 点亮所有
            memcpy(&(tLCD_Data.u8LCD_Buff), &(tLCD_Data.u8LCD_Data), sizeof(tLCD_Data.u8LCD_Data));
        }
        else if(tLCD_Data.u8Flash_CNT_x100ms >= tLCD_Data.u8Flash_CCR_x100ms)
        {
            //-- 熄灭闪烁的
            for (i = 0; i < tLCD_Data.u8LCD_Buff_Length; i++)
            {
                tLCD_Data.u8LCD_Buff[i] = tLCD_Data.u8LCD_Data[i] & (~tLCD_Data.u8LCD_Flash[i]);
            }
        }
        else
        {

        }
    }
}

void LCD_Data_Refresh(void)
{

    HT1621_Device_Data_Refresh(tLCD_Data.u8LCD_Buff, tLCD_Data.u8LCD_Buff_Length);
}











//////////////////////////////////////////////////////////////////////////////////////












Leds_SpecChar_t Digitron_String[LED_STR_NUM][DIS_SEGMAX] =
{
    /* Menu */
    /*LED_STR_OPU,      */{O,       P,      U},
    /*LED_STR_OPF,      */{O,       P,      F},
    /*LED_STR_OPP,      */{O,       P,      P},
    /*LED_STR_MOD,      */{o,       O,      D},
    /*LED_STR_CHP,      */{C,       H,      P},
    /*LED_STR_RCC,      */{R,       C,      C},
    /*LED_STR_MCC,      */{M,       C,      C},
    /*LED_STR_MDF,      */{M,       D,      F},
    /*LED_STR_LRS,      */{L,       R,      S},
    /*LED_STR_TRS,      */{T,       R,      S},
    /*LED_STR_MIP,      */{M,       I,      P},
    /*LED_STR_PWS,      */{P,       W,      S},
    /*LED_STR_OLG,      */{O,       L,      G},
    /*LED_STR_MUE,      */{M,       U,      E},
    /*LED_STR_BTG,      */{B,       T,      G},
    /*LED_STR_BTB,      */{B,       T,      B},
    /*LED_STR_BAT,      */{B,       A,      T},
    /*LED_STR_BAL,      */{B,       A,      L},
    /*LED_STR_BAU,      */{B,       A,      U},
    /*LED_STR_BCV,      */{B,       C,      V},
    /*LED_STR_BFL,      */{B,       F,      L},
    /*LED_STR_LLV,      */{L,       L,      V},
    /*LED_STR_LHV,      */{L,       H,      V},
    /*LED_STR_LWD,      */{L,       W,      D},
    /*LED_STR_SRE,      */{S,       R,      E},
    /*LED_STR_STD,      */{S,       T,      D},
    /*LED_STR_PAR_MOD,  */{M,       O,      D},
    /*LED_STR_SBA,      */{S,       B,      A},
    /*LED_STR_EQM,      */{E,       Q,      M},
    /*LED_STR_EQV,      */{E,       Q,      V},
    /*LED_STR_EQT,      */{E,       Q,      T},
    /*LED_STR_EQO,      */{E,       Q,      O},
    /*LED_STR_EQI,      */{E,       Q,      I},
    /*LED_STR_EQN,      */{E,       Q,      N},
    /* Switch */
    /*LED_STR_PNG,      */{P,       N,      G},
    /*LED_STR_GRD,      */{G,       R,      D},
    /*LED_STR_PV,       */{NONE,    P,      V},
    /*LED_STR_PBG,      */{P,       B,      G},
    /*LED_STR_ON,       */{NONE,    O,      N},
    /*LED_STR_OFF,      */{O,       F,      F},

};

void Display_Service_Set_ICON_ONOFF(LCD_Icon_Type_t u8Icon_Index, EN_t data, LCD_FlashMode_t flash_mode)
{
    LCD_Set_ICON_ONOFF(u8Icon_Index, data, flash_mode);
}

void Display_Service_Set_Display_Interger(LCD_Digitron_Group_Type_t group_type, uint16_t data, uint8_t decimal)
{
    LCD_Set_Display_Interger(group_type, data, decimal);
}

void Display_Service_Set_Display_String(LCD_Digitron_Group_Type_t group_type, Leds_SpecChar_t *string)
{
    LCD_Set_Display_String(group_type, string);
}

void Display_Service_Data_Refresh(void)
{
    LCD_Data_Refresh();
}

void Display_Service_Set_SEG_Menu(LCD_Digitron_Group_Type_t group_type, Leds_SpecChar_t string, uint8_t data)
{
    LCD_Set_SEG_Menu(group_type, string, data);
}