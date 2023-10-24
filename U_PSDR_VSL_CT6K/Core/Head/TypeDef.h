/***********************************************************************************************************************
* Copyright (c)  , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
* 文件名        : typeDef.h
* 用途         : 重定义头文件
***********************************************************************************************************************/

/* 定义类型 */
#ifndef __TYPEDEF_H_
#define __TYPEDEF_H_

#include <stdint.h>

/***********************************************************************************************************************
* * Macro definitions
***********************************************************************************************************************/

//#define NULL (0x00)

#define _WEAK_FUNC_DEFINE_            __attribute__((weak))

typedef int                 int16;
typedef long                int32;
//typedef long long           int64;
//typedef unsigned long long  uint64;
typedef unsigned int        uint16;
typedef unsigned long       uint32;
//typedef unsigned long long  uint64_t;

typedef unsigned char uchar;
//typedef signed char char;
typedef unsigned short ushort;
//typedef signed short short;
typedef unsigned int uint;
//typedef signed int lint;
typedef unsigned long int ulint;
typedef signed long int lint;

#define float32_t               float

#define U8_DEFAULT_MAX_VALUE    (0xFF)
#define U16_DEFAULT_MAX_VALUE   (0xFFFF)

#define BIT0000_0000        (0x00)          //
#define BIT0000_0001        (0x01)          //bit0
#define BIT0000_0010        (0x02)          //bit1
#define BIT0000_0100        (0x04)          //bit2
#define BIT0000_1000        (0x08)          //bit3
#define BIT0001_0000        (0x10)          //bit4
#define BIT0010_0000        (0x20)          //bit5
#define BIT0100_0000        (0x40)          //bit6
#define BIT1000_0000        (0x80)          //bit7


#define BIT(x)              ((1UL)<<(x))

#define BIT0                (0x00000001)
#define BIT1                (0x00000002)
#define BIT2                (0x00000004)
#define BIT3                (0x00000008)
#define BIT4                (0x00000010)
#define BIT5                (0x00000020)
#define BIT6                (0x00000040)
#define BIT7                (0x00000080)
#define BIT8                (0x00000100)
#define BIT9                (0x00000200)
#define BIT10               (0x00000400)
#define BIT11               (0x00000800)
#define BIT12               (0x00001000)
#define BIT13               (0x00002000)
#define BIT14               (0x00004000)
#define BIT15               (0x00008000)
#define BIT16               (0x00010000)
#define BIT17               (0x00020000)
#define BIT18               (0x00040000)
#define BIT19               (0x00080000)
#define BIT20               (0x00100000)
#define BIT21               (0x00200000)
#define BIT22               (0x00400000)
#define BIT23               (0x00800000)
#define BIT24               (0x01000000)
#define BIT25               (0x02000000)
#define BIT26               (0x04000000)
#define BIT27               (0x08000000)
#define BIT28               (0x10000000)
#define BIT29               (0x20000000)
#define BIT30               (0x40000000)
#define BIT31               (0x80000000)



/***********************************************************************************************************************
* * Macro Define_Temp
***********************************************************************************************************************/
#define TEMP_NEGATIVE_1     (-10)
#define TEMP_NEGATIVE_0_5   (-5)
#define TEMP_0              (0)
#define TEMP_0_5            (5)
#define TEMP_1              (10)
#define TEMP_1_5            (15)
#define TEMP_2              (20)
#define TEMP_2_5            (25)
#define TEMP_3              (30)
#define TEMP_3_5            (35)
#define TEMP_4              (40)
#define TEMP_4_5            (45)
#define TEMP_5              (50)
#define TEMP_5_5            (55)
#define TEMP_6              (60)
#define TEMP_7              (70)
#define TEMP_8              (80)
#define TEMP_9              (90)
#define TEMP_10             (100)
#define TEMP_11             (110)
#define TEMP_12             (120)
#define TEMP_13             (130)
#define TEMP_14             (140)
#define TEMP_15             (150)
#define TEMP_16             (160)
#define TEMP_17             (170)
#define TEMP_18             (180)
#define TEMP_19             (190)
#define TEMP_20             (200)
#define TEMP_21             (210)
#define TEMP_22             (220)
#define TEMP_23             (230)
#define TEMP_24             (240)
#define TEMP_25             (250)
#define TEMP_26             (260)
#define TEMP_27             (270)
#define TEMP_28             (280)
#define TEMP_29             (290)
#define TEMP_30             (300)
#define TEMP_31             (310)
#define TEMP_32             (320)
#define TEMP_33             (330)
#define TEMP_34             (340)
#define TEMP_35             (350)
#define TEMP_37				(370)
#define TEMP_39             (390)
#define TEMP_42             (420)
#define TEMP_43             (430)
#define TEMP_47             (470)
#define TEMP_51             (510)
#define TEMP_57             (570)
#define TEMP_58             (580)
#define TEMP_59             (590)
#define TEMP_64             (640)


#define _nop_()             __NOP()

#define U32_DUMMY           (0xFFFFFFFF)
#define U16_DUMMY           (0xFFFF)
#define U8_DUMMY            (0xFF)

#define INC_U32(x)          do { if((x) < U32_DUMMY) {(x)++;} }while(0)
#define INC_U16(x)          do { if((x) < U16_DUMMY) {(x)++;} }while(0)
#define INC_U8(x)           do { if((x) < U8_DUMMY) {(x)++;} }while(0)

#define DEC_U32(x)          do { if((x) > 0) {(x)--;} }while(0)
#define DEC_U16(x)          do { if((x) > 0) {(x)--;} }while(0)
#define DEC_U8(x)           do { if((x) > 0) {(x)--;} }while(0)


/***********************************************************************************************************************
* * Enum definitions
***********************************************************************************************************************/
typedef enum
{
    STATUS_FALSE = 0,
    STATUS_TRUE,
} bool_t;

typedef enum
{
    EN_DISABLE = 0,
    EN_ENABLE,
} EN_t;

typedef enum
{
    IO_LOW = 0,
    IO_HIGH,
} IO_t;


/***********************************************************************************************************************
 * 字类型
***********************************************************************************************************************/
typedef union
{
    uint16_t Word;

    struct
    {
        uint8_t ByteL;
        uint8_t ByteH;
    } Bytes;

    struct
    {
        uint8_t Bak0           : 1;   //Bit0  预留位
        uint8_t Bak1           : 1;   //Bit1  预留位
        uint8_t Bak2           : 1;   //Bit2  预留位
        uint8_t Bak3           : 1;   //Bit3  预留位
        uint8_t Bak4           : 1;   //Bit4  预留位
        uint8_t Bak5           : 1;   //Bit5  预留位
        uint8_t Bak6           : 1;   //Bit6  预留位
        uint8_t Bak7           : 1;   //Bit7  预留位

        uint8_t Bak8           : 1;   //Bit8  预留位
        uint8_t Bak9           : 1;   //Bit9  预留位
        uint8_t Bak10          : 1;   //Bit10 预留位
        uint8_t Bak11          : 1;   //Bit11 预留位
        uint8_t Bak12          : 1;   //Bit12 预留位
        uint8_t Bak13          : 1;   //Bit13 预留位
        uint8_t Bak14          : 1;   //Bit14 预留位
        uint8_t Bak15          : 1;   //Bit15 预留位
    } Bits;
} word_type_t;

/***********************************************************************************************************************
 * 双字类型
***********************************************************************************************************************/
typedef union
{
    uint32_t u32LWord;
    uint8_t u8aByte[4];
    struct
    {
        uint16_t u16ByteL;
        uint16_t u16ByteH;
    } U16bytes;

    struct
    {
        uint8_t ByteLL;
        uint8_t ByteLH;
        uint8_t ByteHL;
        uint8_t ByteHH;
    } Bytes;

    struct
    {
        uint8_t Bak0           : 1;   //Bit0  预留位
        uint8_t Bak1           : 1;   //Bit1  预留位
        uint8_t Bak2           : 1;   //Bit2  预留位
        uint8_t Bak3           : 1;   //Bit3  预留位
        uint8_t Bak4           : 1;   //Bit4  预留位
        uint8_t Bak5           : 1;   //Bit5  预留位
        uint8_t Bak6           : 1;   //Bit6  预留位
        uint8_t Bak7           : 1;   //Bit7  预留位

        uint8_t Bak8           : 1;   //Bit8  预留位
        uint8_t Bak9           : 1;   //Bit9  预留位
        uint8_t Bak10          : 1;   //Bit10 预留位
        uint8_t Bak11          : 1;   //Bit11 预留位
        uint8_t Bak12          : 1;   //Bit12 预留位
        uint8_t Bak13          : 1;   //Bit13 预留位
        uint8_t Bak14          : 1;   //Bit14 预留位
        uint8_t Bak15          : 1;   //Bit15 预留位

        uint8_t Bak16          : 1;   //Bit16 预留位
        uint8_t Bak17          : 1;   //Bit17 预留位
        uint8_t Bak18          : 1;   //Bit18 预留位
        uint8_t Bak19          : 1;   //Bit19 预留位
        uint8_t Bak20          : 1;   //Bit20 预留位
        uint8_t Bak21          : 1;   //Bit21 预留位
        uint8_t Bak22          : 1;   //Bit22 预留位
        uint8_t Bak23          : 1;   //Bit23 预留位

        uint8_t Bak24          : 1;   //Bit24 预留位
        uint8_t Bak25          : 1;   //Bit25 预留位
        uint8_t Bak26          : 1;   //Bit26 预留位
        uint8_t Bak27          : 1;   //Bit27 预留位
        uint8_t Bak28          : 1;   //Bit28 预留位
        uint8_t Bak29          : 1;   //Bit29 预留位
        uint8_t Bak30          : 1;   //Bit30 预留位
        uint8_t Bak31          : 1;   //Bit31 预留位
    } Bits;
} long_type_t;

#endif
/***********************************************************************************************************************
* * Copyright (c)  CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
