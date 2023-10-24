#ifndef __DISPLAY_SERVICE_H__
#define __DISPLAY_SERVICE_H__
#include "TypeDef.h"
#include "LCD_Device.h"
#include "HT1621_Device.h"
#include "string.h"

typedef enum
{
    FLASH_OFF = 0,
    FLASH_ON,
} LCD_FlashMode_t;

typedef enum
{
    LCD_COM_0 = 0,
    LCD_COM_1,
    LCD_COM_2,
    LCD_COM_3,
    LCD_COM_4,
    LCD_COM_5,
    LCD_COM_6,
    LCD_COM_7,

    LCD_COM_MAX,
    LCD_COM_NC = 0xFF,
}
LCD_COM_t;

typedef enum
{
    LCD_SEG_0 = 0,
    LCD_SEG_1,
    LCD_SEG_2,
    LCD_SEG_3,
    LCD_SEG_4,
    LCD_SEG_5,
    LCD_SEG_6,
    LCD_SEG_7,
    LCD_SEG_8,
    LCD_SEG_9,
    LCD_SEG_10,
    LCD_SEG_11,
    LCD_SEG_12,
    LCD_SEG_13,
    LCD_SEG_14,
    LCD_SEG_15,
    LCD_SEG_16,
    LCD_SEG_17,
    LCD_SEG_18,
    LCD_SEG_19,
    LCD_SEG_20,
    LCD_SEG_21,
    LCD_SEG_22,
    LCD_SEG_23,
    LCD_SEG_24,
    LCD_SEG_25,
    LCD_SEG_26,
    LCD_SEG_27,
    LCD_SEG_28,
    LCD_SEG_29,
    LCD_SEG_30,
    LCD_SEG_31,

    LCD_SEG_MAX,
    LCD_SEG_NC = 0xFF,
} LCD_SEG_t;

typedef enum
{
    SEG1_A = 0,
    SEG1_B,
    SEG1_C,
    SEG1_D,
    SEG1_E,
    SEG1_F,
    SEG1_G,
    SEG1_H,

    SEG2_A,
    SEG2_B,
    SEG2_C,
    SEG2_D,
    SEG2_E,
    SEG2_F,
    SEG2_G,
    SEG2_H,

    SEG3_A,
    SEG3_B,
    SEG3_C,
    SEG3_D,
    SEG3_E,
    SEG3_F,
    SEG3_G,
    SEG3_H,

    SEG4_A,
    SEG4_B,
    SEG4_C,
    SEG4_D,
    SEG4_E,
    SEG4_F,
    SEG4_G,
    SEG4_H,

    SEG5_A,
    SEG5_B,
    SEG5_C,
    SEG5_D,
    SEG5_E,
    SEG5_F,
    SEG5_G,
    SEG5_H,

    SEG6_A,
    SEG6_B,
    SEG6_C,
    SEG6_D,
    SEG6_E,
    SEG6_F,
    SEG6_G,
    SEG6_H,

    SEG7_A,
    SEG7_B,
    SEG7_C,
    SEG7_D,
    SEG7_E,
    SEG7_F,
    SEG7_G,
    SEG7_H,

    SEG8_A,
    SEG8_B,
    SEG8_C,
    SEG8_D,
    SEG8_E,
    SEG8_F,
    SEG8_G,
    SEG8_H,

    ICON_INLET_INPUT,
    ICON_INLET_BATT,
    ICON_INLET_TEMP,
    ICON_INLET_BPS,
    ICON_INLET_AC,
    ICON_INLET_PV,
    ICON_INLET_RST_R,
    ICON_INLET_RST_S,
    ICON_INLET_RST_T,
    ICON_INLET_KW_K,
    ICON_INLET_KW_W,
    ICON_INLET_KVA_K,
    ICON_INLET_KVA_V,
    ICON_INLET_KVA_A,
    ICON_INLET_PC_P,
    ICON_INLET_PC_C,
    ICON_INLET_HZ,

    ICON_OUTLET_OUTPUT,
    ICON_OUTLET_BATT,
    ICON_OUTLET_LOAD,
    ICON_OUTLET_KW_K,
    ICON_OUTLET_KW_W,
    ICON_OUTLET_KVA_K,
    ICON_OUTLET_KVA_V,
    ICON_OUTLET_KVA_A,
    ICON_OUTLET_PC_P,
    ICON_OUTLET_PC_C,
    ICON_OUTLET_HZ,

    ICON_FLOW_DUAL,
    ICON_FLOW_LINE,
    ICON_FLOW_PV,
    ICON_FLOW_PFC,
    ICON_FLOW_INV,
    ICON_FLOW_LOAD,

    ICON_FLOW_LINE2PFC,
    ICON_FLOW_LINE2LOAD1,
    ICON_FLOW_LINE2LOAD2,
    ICON_FLOW_PV2PFC,
    ICON_FLOW_PFC2INV,
    ICON_FLOW_PFC2BAT,
    ICON_FLOW_BAT2INV,
    ICON_FLOW_INV2LOAD,

    ICON_BATT_FRAME,
    ICON_BATT_25_PER,
    ICON_BATT_50_PER,
    ICON_BATT_75_PER,
    ICON_BATT_100_PER,

    ICON_LOAD_FRAME,
    ICON_LOAD_25_PER,
    ICON_LOAD_50_PER,
    ICON_LOAD_75_PER,
    ICON_LOAD_100_PER,

    ICON_ERROR_FRAME,
    ICON_ERROR_TEXT,
    ICON_ERROR_SHORT,
    ICON_ERROR_OVERLOAD,
    ICON_ERROR_LOWBATT,

    ICON_OTHER_TIME_H,
    ICON_OTHER_TIME_M,
    ICON_OTHER_TIMER,
    ICON_OTHER_FIX,
    ICON_OTHER_MENU_FRAME,
    ICON_OTHER_PARTLINE,
    ICON_OTHER_ECO,
    ICON_OTHER_CF,
    ICON_OTHER_MUTE,
    ICON_OTHER_P,

    ICON_MAX,
} LCD_Icon_Type_t;

typedef enum
{
    LCD_ID_B00449A,
    LCD_ID_B00449B,
    LCD_ID_MAX,
} LCD_TypeDefine_t;
#define LCD_BUFF_MAX_SUPPORT        32

typedef enum
{
    DIS_SEG1 = 0,
    DIS_SEG2,
    DIS_SEG3,

    DIS_SEGMAX,
} LCD_SEG_Group_Type_t;

typedef enum
{
    GROUP_INPUT = 0,
    GROUP_MENU,
    GROUP_OUTPUT,

    GROUP_MAX,
} LCD_Digitron_Group_Type_t;
typedef enum
{
    NIXIE_TUBE_1 = 0,
    NIXIE_TUBE_2,
    NIXIE_TUBE_3,
    NIXIE_TUBE_4,
    NIXIE_TUBE_5,
    NIXIE_TUBE_6,
    NIXIE_TUBE_7,
    NIXIE_TUBE_8,
    NIXIE_TUBE_MAX,
    NIXIE_TUBE_NC = 0xFF,
} LCD_Nixie_Tube_Type_t;

typedef enum
{
    /* 0 ~ 9...... */
    A = 10,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    o,

    rail,
    _,
    c,
    h,
    NONE,

    LED_SPEC_CHAR_NUM,
    LED_SPEC_CHAR_MAX = LED_SPEC_CHAR_NUM - 1,
} Leds_SpecChar_t;


typedef enum
{
    /* Menu */
    LED_STR_OPU = 0,
    LED_STR_OPF,
    LED_STR_OPP,
    LED_STR_MOD,
    LED_STR_CHP,
    LED_STR_RCC,
    LED_STR_MCC,
    LED_STR_MDF,
    LED_STR_LRS,
    LED_STR_TRS,
    LED_STR_MIP,
    LED_STR_PWS,
    LED_STR_OLG,
    LED_STR_MUE,
    LED_STR_BTG,
    LED_STR_BTB,
    LED_STR_BAT,
    LED_STR_BAL,
    LED_STR_BAU,
    LED_STR_BCV,
    LED_STR_BFL,
    LED_STR_LLV,
    LED_STR_LHV,
    LED_STR_LWD,
    LED_STR_SRE,
    LED_STR_STD,
    LED_STR_PAR_MOD,
    LED_STR_SBA,
    LED_STR_EQM,
    LED_STR_EQV,
    LED_STR_EQT,
    LED_STR_EQO,
    LED_STR_EQI,
    LED_STR_EQN,

    /* Switch */
    LED_STR_PNG,
    LED_STR_GRD,
    LED_STR_PV,
    LED_STR_PBG,
    LED_STR_ON,
    LED_STR_OFF,


    LED_STR_NUM,
} Leds_String_t;

extern void LCD_Initial(void);
extern void LCD_Data_Refresh(void);
extern void LCD_Set_ICON_ONOFF(LCD_Icon_Type_t u8Icon_Index, EN_t data, LCD_FlashMode_t flash_mode);
extern void LCD_Set_SEG_Data(LCD_Nixie_Tube_Type_t numb, Leds_SpecChar_t data, EN_t point_en, LCD_FlashMode_t flash_mode);
extern void LCD_Set_Display_Interger(LCD_Digitron_Group_Type_t group_type, uint16_t data, uint8_t decimal);
extern void LCD_Set_Display_Number_AUTO(LCD_Digitron_Group_Type_t group_type, float32_t data, uint8_t decimal);
extern void LCD_Set_SEG_Menu(LCD_Digitron_Group_Type_t group_type, Leds_SpecChar_t string, uint8_t data);
extern void LCD_Set_Display_String(LCD_Digitron_Group_Type_t group_type, Leds_SpecChar_t *string);





extern void Display_Service_Set_ICON_ONOFF(LCD_Icon_Type_t u8Icon_Index, EN_t data, LCD_FlashMode_t flash_mode);
extern void Display_Service_Set_Display_Interger(LCD_Digitron_Group_Type_t group_type, uint16_t data, uint8_t decimal);
extern void Display_Service_Set_Display_String(LCD_Digitron_Group_Type_t group_type, Leds_SpecChar_t *string);
extern void Display_Service_Set_SEG_Menu(LCD_Digitron_Group_Type_t group_type, Leds_SpecChar_t string, uint8_t data);
extern void Display_Service_Data_Refresh(void);

#endif
