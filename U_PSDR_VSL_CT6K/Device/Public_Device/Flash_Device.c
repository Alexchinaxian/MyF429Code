/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Flash_Device.c 
 用途 : Flash读写处理
***********************************************************************************************************************/
#ifndef __FLASH_DEVICE_C__
#define __FLASH_DEVICE_C__

#include "Flash_Driver.h"
#include "SPI_driver.h"

#if MODULE_FLASH_ONCHIP

/*********************************************以下是内部接口函数*******************************************************/
#if (FLASH_WRITE_SIZE == FLASH_DOUBLE_WORD)
/***********************************************************************************************************************
 功能：FLASH写数据，每次写2字（8byte）
***********************************************************************************************************************/
static uint8_t Flash_WriteDoubleWordTable(uint32_t u32Addr, uint8_t *pu8Buffer, uint32_t u32Count)
{
    uint8_t WriteFalshStatus = 0;

    uint32_t i;

    Flash_Bsp_Unlock();                                                                                                 //解锁

    for (i = 0; (i < u32Count) && (WriteFalshStatus == 0); i += 8) 
    {
        WriteFalshStatus = Flash_Bsp_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, u32Addr, (uint64_t)(*(uint64_t *)pu8Buffer));//按双字写入数据
        pu8Buffer += 8;
        u32Addr += 8;
    }
    Flash_Bsp_Lock();                                                                                                   //上锁

    if (WriteFalshStatus)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
#elif (FLASH_WRITE_SIZE == FLASH_WORD)

#elif (FLASH_WRITE_SIZE == FLASH_HALF_WORD)

#elif (FLASH_WRITE_SIZE == FLASH_BYTE)

#endif

/*********************************************以下是外部接口函数*******************************************************/


/***********************************************************************************************************************
 功能：FLASH全局变量初始化
***********************************************************************************************************************/
void Flash_Device_InitVar(void)
{
    Flash_Bsp_Init();
}

/***********************************************************************************************************************
 功能：FLASH写数据
***********************************************************************************************************************/
bool_t Flash_Device_WriteTbl(uint32_t u32Addr, uint8_t *pu8Buffer, uint32_t u32Count)
{
#if (FLASH_WRITE_SIZE == FLASH_DOUBLE_WORD)
    if (Flash_WriteDoubleWordTable(u32Addr,  pu8Buffer, u32Count))                                                      //按双字写内部Flash
    {
        return STATUS_TRUE;
    }
    else
    {
        return STATUS_FALSE;
    }
#elif (FLASH_WRITE_SIZE == FLASH_WORD)
    if (Flash_WriteWordTable(u32Addr,  pu8Buffer, u32Count))
    {
        return STATUS_TRUE;
    }
    else
    {
        return STATUS_FALSE;
    }
#elif (FLASH_WRITE_SIZE == FLASH_HALF_WORD)
    if (Flash_WriteHalfWordTable(u32Addr,  pu8Buffer, u32Count))
    {
        return STATUS_TRUE;
    }
    else
    {
        return STATUS_FALSE;
    }
#elif (FLASH_WRITE_SIZE == FLASH_BYTE)
    if (Flash_WriteDataByteTable(u32Addr,  pu8Buffer, u32Count))
    {
        return STATUS_TRUE;
    }
    else
    {
        return STATUS_FALSE;
    }
#endif
}

/***********************************************************************************************************************
 功能：FLASH读数据
***********************************************************************************************************************/
void Flash_Device_ReadTbl(uint32_t u32Addr, uint8_t *pu8Buffer, uint32_t u32Count)
{
    uint32_t i;

    for(i = 0; i < u32Count; i++)
    {
        pu8Buffer[i] = ((uint8_t)(*((uint8_t *)(u32Addr + i))));                                                        //读取数据
    }
}

/***********************************************************************************************************************
 功能：FLASH擦除
***********************************************************************************************************************/
bool_t Flash_Device_Erase(uint32_t u32TypeErase, uint32_t u32Bank, uint32_t u32NbPages, uint32_t u32Page)
{

    uint32_t PageError = 0;
    FLASH_EraseInitTypeDef pEraseInit;
    HAL_StatusTypeDef status = HAL_OK;
    
    Flash_Bsp_Unlock();
    pEraseInit.Banks = u32Bank;//FLASH_BANK_1
    pEraseInit.NbPages = u32NbPages;
    pEraseInit.Page = u32Page;//
    pEraseInit.TypeErase = u32TypeErase;//FLASH_TYPEERASE_PAGES
    status = Flash_Bsp_Erase(&pEraseInit, &PageError);
      
    Flash_Bsp_Lock();

    if (status)
    {
        return STATUS_TRUE;
    }
    else
    {
        return STATUS_FALSE;
    }
}

#endif      /***Module End***/

#if MODULE_FLASH_EXTERN                                                                                                 //外部SPI Flash驱动

#define GD25qxx_Delay(delay) Delay_ms(delay)

#define GD25QXX_DUMMY_BYTE                          (0xFF)                                                              //虚拟字节
extern SPI_HandleTypeDef hspi1;
typedef enum
{
    GD25Q10 = 1,
    GD25Q20,
    GD25Q40,
    GD25Q80,
    GD25Q16,
    GD25Q32,
    GD25Q64,
    GD25Q128,
    GD25Q256,
    GD25Q512,
} GD25QXX_ID_t;

typedef struct
{
    GD25QXX_ID_t tID;
    uint8_t u8UniqID[16];
    uint16_t u16PageSize;
    uint32_t u32PageCount;
    uint32_t u32SectorSize;
    uint32_t u32SectorCount;
    uint32_t u32BlockSize;
    uint32_t u32BlockCount;
    uint32_t u32CapacityInKiloByte;
    uint8_t u8StatusRegister1;
    uint8_t u8StatusRegister2;
    uint8_t u8StatusRegister3;
    uint8_t u8Lock;
} GD25qxx_t;

GD25qxx_t GD25qxx;

/***********************************************************************************************************************
 功能：SPI总线数据传输函数，它可以同时将数据从主机发送到从机并从从机接收数据
***********************************************************************************************************************/
static uint8_t GD25qxx_Spi(uint8_t u8Data)
{
    uint8_t u8Ret;
    HAL_SPI_TransmitReceive(&DEV_GD25QXX_SPI, &u8Data, &u8Ret, 1, 100);                                                 //跨层调用，后续挪移位置,1代表收发传输1字节，100代表超时时间为100ms
    return u8Ret;
}

/***********************************************************************************************************************
 功能：SPI FLASH读取Manufactory ID + MemoryType ID + Capacity ID
***********************************************************************************************************************/
static uint32_t GD25qxx_ReadID(void)
{
    uint32_t u32Temp = 0, u32Temp0 = 0, u32Temp1 = 0, u32Temp2 = 0;
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                                //CS拉低
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                                //CS拉低
#endif
    GD25qxx_Spi(0x9F);                                                                                                  //9FH，读取Manufactory ID+MemoryType ID+Capacity ID
    u32Temp0 = GD25qxx_Spi(GD25QXX_DUMMY_BYTE);                                                                         //发送虚拟字节，获取第一个传输的字节
    u32Temp1 = GD25qxx_Spi(GD25QXX_DUMMY_BYTE);                                                                         //发送虚拟字节，获取第二个传输的字节
    u32Temp2 = GD25qxx_Spi(GD25QXX_DUMMY_BYTE);                                                                         //发送虚拟字节，获取第三个传输的字节
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                               //CS拉高
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                                  //CS拉高
#endif
    u32Temp = (u32Temp0 << 16) | (u32Temp1 << 8) | u32Temp2;                                                            //组合成完整的ID，返回
    return u32Temp;
}

/***********************************************************************************************************************
 功能：SPI FLASH读取Unique ID
***********************************************************************************************************************/
static void GD25qxx_ReadUniqID(void)
{
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                                //CS拉低
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                                //CS拉低
#endif

    GD25qxx_Spi(0x4B);                                                                                                  //4BH，读取Unique ID
    
    GD25qxx_Spi(0x00);                                                                                                  //A23~A16
    GD25qxx_Spi(0x00);                                                                                                  //A15~A8
    GD25qxx_Spi(0x00);                                                                                                  //A7~A0

    for (uint8_t i = 0; i < 16; i++)
    {
        GD25qxx.u8UniqID[i] = GD25qxx_Spi(GD25QXX_DUMMY_BYTE);                                                            //获取128 bit Unique ID
    }
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                               //CS拉高
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                                  //CS拉高
#endif

}

/***********************************************************************************************************************
 功能：SPI FLASH写使能
***********************************************************************************************************************/
static void GD25qxx_WriteEnable(void)
{
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                                //CS拉低
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                                //CS拉低
#endif
    GD25qxx_Spi(0x06);                                                                                                  //06H，写操作使能指令
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                               //CS拉高
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                                  //CS拉高
#endif
    GD25qxx_Delay(1);                                                                                                   //延时1ms，确保命令执行完成
}

/***********************************************************************************************************************
 功能：SPI FLASH写禁止
***********************************************************************************************************************/
#if 0       //暂时未使用，屏蔽以消除编译器告警
static void GD25qxx_WriteDisable(void)
{
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                                //CS拉低
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                                //CS拉低
#endif
    GD25qxx_Spi(0x04);                                                                                                  //04H，写操作禁止指令
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                               //CS拉高
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                                  //CS拉高
#endif
    GD25qxx_Delay(1);                                                                                                   //延时1ms，确保命令执行完成
}
#endif
/***********************************************************************************************************************
 功能：SPI FLASH读状态寄存器
***********************************************************************************************************************/

static uint8_t GD25qxx_ReadStatusRegister(uint8_t u8SelectStatusRegister_1_2_3)
{
    uint8_t u8Status = 0;
    
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                                //CS拉低
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                                //CS拉低
#endif
    if (u8SelectStatusRegister_1_2_3 == 1)
    {
        GD25qxx_Spi(0x05);                                                                                              //05H指令，读取状态寄存器位S7~S0
        u8Status = GD25qxx_Spi(GD25QXX_DUMMY_BYTE);                                                                     //获取S7~S0
        GD25qxx.u8StatusRegister1 = u8Status;                                                                           //赋值暂存状态寄存器的值
    }
    else if (u8SelectStatusRegister_1_2_3 == 2)
    {
        GD25qxx_Spi(0x35);                                                                                              //35H指令，读取状态寄存器位S15~S8
        u8Status = GD25qxx_Spi(GD25QXX_DUMMY_BYTE);                                                                     //获取S15~S8
        GD25qxx.u8StatusRegister2 = u8Status;                                                                           //赋值暂存状态寄存器的值
    }
#if 0                                                                                                                   //GD25Q16E无该指令，屏蔽，其它型号若支持15，可开启
    else
    {
        GD25qxx_Spi(0x15);
        u8Status = GD25qxx_Spi(GD25QXX_DUMMY_BYTE);
        GD25qxx.u8StatusRegister3 = u8Status;
    }
#endif
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                               //CS拉高
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                                  //CS拉高
#endif
    return u8Status;
}

/***********************************************************************************************************************
 功能：SPI FLASH写状态寄存器
***********************************************************************************************************************/
#if 0       //暂时未使用，屏蔽以消除编译器告警
static void GD25qxx_WriteStatusRegister(uint8_t u8StatusRegister1Data, uint8_t u8StatusRegister2Data)
{
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                                //CS拉低
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                                //CS拉低
#endif
    GD25qxx_Spi(0x01);                                                                                                  //01H指令，写状态寄存器
    GD25qxx_Spi(u8StatusRegister1Data);                                                                                 //写入S7~S0
    GD25qxx_Spi(u8StatusRegister2Data);                                                                                 //写入S15~S8
    GD25qxx.u8StatusRegister1 = u8StatusRegister1Data;                                                                  //暂存写入的值至MCU 本地
    GD25qxx.u8StatusRegister2 = u8StatusRegister2Data;
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                               //CS拉高
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                                  //CS拉高
#endif
}
#endif

/***********************************************************************************************************************
 功能：SPI FLASH等待写操作结束
***********************************************************************************************************************/
static void GD25qxx_WaitForWriteEnd(void)
{
    GD25qxx_Delay(1);                                                                                                   //延时1ms
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                                //CS拉低
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                                //CS拉低
#endif
    GD25qxx_Spi(0x05);                                                                                                  //05H指令，读状态寄存器
    do
    {
        GD25qxx.u8StatusRegister1 = GD25qxx_Spi(GD25QXX_DUMMY_BYTE);                                                    //获取S7~S0
        //GD25qxx_Delay(1);                                                                                               //延时1ms
    } while ((GD25qxx.u8StatusRegister1 & 0x01) == 0x01);                                                               //WIP（S0） = 1时循环等待
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                               //CS拉高
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                                  //CS拉高
#endif
}

void GD25qxx_ReadStatusRegistor(void)
{
    GD25qxx_WriteEnable();                                                                                              //06H写使能

#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                                //CS拉低
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                                //CS拉低
#endif
    GD25qxx_Spi(0x05);                                                                                                  //05H指令，读状态寄存器
    GD25qxx.u8StatusRegister1 = GD25qxx_Spi(GD25QXX_DUMMY_BYTE);                                                        //获取S7~S0
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                               //CS拉高
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                                  //CS拉高
#endif

#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                                //CS拉低
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                                //CS拉低
#endif
    GD25qxx_Spi(0x35);                                                                                                  //35H指令，读状态寄存器
    GD25qxx.u8StatusRegister2 = GD25qxx_Spi(GD25QXX_DUMMY_BYTE);                                                        //获取S15~S8
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                               //CS拉高
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                                  //CS拉高
#endif

}

void SPI_Flash_Device_GD25qxx_Test(void)
{
    GD25qxx_ReadID();
}

/***********************************************************************************************************************
 功能：SPI FLASH初始化
***********************************************************************************************************************/
bool_t SPI_Flash_Device_GD25qxx_Init(void)
{
    bool_t bState = STATUS_TRUE;
    uint32_t u32DensityID;
  
    GD25qxx.u8Lock = 1;
    #if 0
    while (HAL_GetTick() < 100)                                                                                         //跨层调用，后续处理
    {
        GD25qxx_Delay(1);
    }
    #endif
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                               //CS拉高
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                                  //CS拉高
#endif
    GD25qxx_Delay(100);                                                                                                 //延时100ms

    u32DensityID = GD25qxx_ReadID();                                                                                    //9F读取ID信息

    switch (u32DensityID & 0x000000FF)                                                                                  //提取Capacity ID7-ID0
    {
    case 0x1A:
        GD25qxx.tID = GD25Q512;                                                                                         //512Mbit容量产品
        GD25qxx.u32BlockCount = 1024;                                                                                   //存储块数量，移植请自行修改该参数

        break;
    case 0x19:
        GD25qxx.tID = GD25Q256;                                                                                         //256Mbit容量产品
        GD25qxx.u32BlockCount = 512;                                                                                    //存储块数量，移植请自行修改该参数

        break;
    case 0x18:
        GD25qxx.tID = GD25Q128;                                                                                         //128Mbit容量产品
        GD25qxx.u32BlockCount = 256;                                                                                    //存储块数量，移植请自行修改该参数

        break;
    case 0x17:
        GD25qxx.tID = GD25Q64;                                                                                          //64Mbit容量产品
        GD25qxx.u32BlockCount = 128;                                                                                    //存储块数量，移植请自行修改该参数

        break;
    case 0x16:
        GD25qxx.tID = GD25Q32;                                                                                          //32Mbit容量产品
        GD25qxx.u32BlockCount = 64;                                                                                     //存储块数量，移植请自行修改该参数

        break;
    case 0x15:
        GD25qxx.tID = GD25Q16;                                                                                          //16Mbit容量产品
        GD25qxx.u32BlockCount = 32;                                                                                     //GD25Q16E，本项目使用的型号.32个存储块

        break;
    case 0x14:
        GD25qxx.tID = GD25Q80;                                                                                          //8Mbit容量产品
        GD25qxx.u32BlockCount = 16;                                                                                     //存储块数量，移植请自行修改该参数

        break;
    case 0x13:
        GD25qxx.tID = GD25Q40;                                                                                          //4Mbit容量产品
        GD25qxx.u32BlockCount = 8;                                                                                      //存储块数量，移植请自行修改该参数

        break;
    case 0x12:
        GD25qxx.tID = GD25Q20;                                                                                          //2Mbit容量产品
        GD25qxx.u32BlockCount = 4;                                                                                      //存储块数量，移植请自行修改该参数

        break;
    case 0x11:
        GD25qxx.tID = GD25Q10;                                                                                          //1Mbit容量产品
        GD25qxx.u32BlockCount = 2;                                                                                      //存储块数量，移植请自行修改该参数

        break;
    default:
        bState = STATUS_FALSE;
    
        break;
    }
    GD25qxx.u16PageSize = 256;                                                                                          //256 byte 每页
    GD25qxx.u32SectorSize = 256*16;                                                                                     //4k byte 每个扇区，每个扇区256byte，共16页
    GD25qxx.u32SectorCount = GD25qxx.u32BlockCount * 16;                                                                //每个block 有 16个sector
    GD25qxx.u32PageCount = (GD25qxx.u32SectorCount * GD25qxx.u32SectorSize) / GD25qxx.u16PageSize;                      //计算页数量
    GD25qxx.u32BlockSize = GD25qxx.u32SectorSize * 16;                                                                  //计算单个存储块的大小
    GD25qxx.u32CapacityInKiloByte = (GD25qxx.u32SectorCount * GD25qxx.u32SectorSize) / 1024;                            //KB单位的容量
    GD25qxx_ReadUniqID();                                                                                               //读取Unique ID
    GD25qxx_ReadStatusRegister(1);                                                                                      //读状态寄存器
    GD25qxx_ReadStatusRegister(2);
    //GD25qxx_ReadStatusRegister(3);                                                                                    //GD25Q16E无状态寄存器3

    GD25qxx.u8Lock = 0;

    return bState;
}

/***********************************************************************************************************************
 功能：SPI FLASH芯片擦除
***********************************************************************************************************************/
void SPI_Flash_Device_GD25qxx_EraseChip(void)
{
    while (GD25qxx.u8Lock == 1)
    {
        GD25qxx_Delay(1);
    }
    GD25qxx.u8Lock = 1;

    GD25qxx_WriteEnable();                                                                                              //06H写使能
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                                //CS拉低
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                                //CS拉低
#endif
    GD25qxx_Spi(0xC7);                                                                                                  //C7H，芯片擦除指令
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                               //CS拉高
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                                  //CS拉高
#endif
    GD25qxx_WaitForWriteEnd();                                                                                          //等待写操作完成

    GD25qxx_Delay(10);                                                                                                  //延时10ms
    GD25qxx.u8Lock = 0;
}

/***********************************************************************************************************************
 功能：SPI FLASH扇区擦除
***********************************************************************************************************************/
void SPI_Flash_Device_GD25qxx_EraseSector(uint32_t u32SectorAddr)
{
    while (GD25qxx.u8Lock == 1)
    {
        GD25qxx_Delay(1);
    }
    GD25qxx.u8Lock = 1;

    GD25qxx_WaitForWriteEnd();                                                                                          //等待上一次写操作完成
    u32SectorAddr = u32SectorAddr * GD25qxx.u32SectorSize;
    GD25qxx_WriteEnable();                                                                                              //06H写使能
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                                //CS拉低
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                                //CS拉低
#endif
    if (GD25qxx.tID >= GD25Q256)
    {
        GD25qxx_Spi(0x21);                                                                                              //扇区擦除指令
        GD25qxx_Spi((u32SectorAddr & 0xFF000000) >> 24);
    }
    else
    {
        GD25qxx_Spi(0x20);                                                                                              //20H，扇区擦除指令
    }
    GD25qxx_Spi((u32SectorAddr & 0xFF0000) >> 16);                                                                      //A23~A16
    GD25qxx_Spi((u32SectorAddr & 0xFF00) >> 8);                                                                         //A15~A8
    GD25qxx_Spi(u32SectorAddr & 0xFF);                                                                                  //A7~A0
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                               //CS拉高
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                                  //CS拉高
#endif
    GD25qxx_WaitForWriteEnd();                                                                                          //等待写操作完成

    GD25qxx_Delay(1);                                                                                                   //延时1ms
    GD25qxx.u8Lock = 0;
}

/***********************************************************************************************************************
 功能：SPI FLASH存储块擦除
***********************************************************************************************************************/
void SPI_Flash_Device_GD25qxx_EraseBlock(uint32_t u32BlockAddr)
{
    while (GD25qxx.u8Lock == 1)
    {
        GD25qxx_Delay(1);
    }
    GD25qxx.u8Lock = 1;

    GD25qxx_WaitForWriteEnd();                                                                                          //等待上一次写操作完成
    u32BlockAddr = u32BlockAddr * GD25qxx.u32SectorSize * 16;
    GD25qxx_WriteEnable();                                                                                              //06H写使能
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                                //CS拉低
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                                //CS拉低
#endif
    if (GD25qxx.tID >= GD25Q256)
    {
        GD25qxx_Spi(0xDC);
        GD25qxx_Spi((u32BlockAddr & 0xFF000000) >> 24);
    }
    else
    {
        GD25qxx_Spi(0xD8);                                                                                              //D8H，存储块擦除指令
    }
    GD25qxx_Spi((u32BlockAddr & 0xFF0000) >> 16);                                                                       //A23~A16
    GD25qxx_Spi((u32BlockAddr & 0xFF00) >> 8);                                                                          //A15~A8
    GD25qxx_Spi(u32BlockAddr & 0xFF);                                                                                   //A7~A0
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                               //CS拉高
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                                  //CS拉高
#endif
    GD25qxx_WaitForWriteEnd();                                                                                          //等待写操作完成

    GD25qxx_Delay(1);                                                                                                   //延时1ms
    GD25qxx.u8Lock = 0;
}

/***********************************************************************************************************************
 功能：转换 页相对地址 为 扇区相对地址
***********************************************************************************************************************/
uint32_t SPI_Flash_Device_GD25qxx_PageToSector(uint32_t u32PageAddress)
{
    return ((u32PageAddress * GD25qxx.u16PageSize) / GD25qxx.u32SectorSize);                                            //返回 扇区相对地址
}

/***********************************************************************************************************************
 功能：转换 页相对地址 为 存储块相对地址
***********************************************************************************************************************/
uint32_t SPI_Flash_Device_GD25qxx_PageToBlock(uint32_t u32PageAddress)
{
    return ((u32PageAddress * GD25qxx.u16PageSize) / GD25qxx.u32BlockSize);                                             //返回 存储块相对地址
}

/***********************************************************************************************************************
 功能：转换 扇区相对地址 为 存储块相对地址
***********************************************************************************************************************/
uint32_t SPI_Flash_Device_GD25qxx_SectorToBlock(uint32_t u32SectorAddress)
{
    return ((u32SectorAddress * GD25qxx.u32SectorSize) / GD25qxx.u32BlockSize);                                         //返回 存储块相对地址
}

/***********************************************************************************************************************
 功能：转换 扇区相对地址 为 页相对地址
***********************************************************************************************************************/
uint32_t SPI_Flash_Device_GD25qxx_SectorToPage(uint32_t u32SectorAddress)
{
    return (u32SectorAddress * GD25qxx.u32SectorSize) / GD25qxx.u16PageSize;                                            //返回 页相对地址
}

/***********************************************************************************************************************
 功能：转换 存储块相对地址 为 页相对地址
***********************************************************************************************************************/
uint32_t SPI_Flash_Device_GD25qxx_BlockToPage(uint32_t u32BlockAddress)
{
    return (u32BlockAddress * GD25qxx.u32BlockSize) / GD25qxx.u16PageSize;                                              //返回 页相对地址
}

/***********************************************************************************************************************
 功能：判断指定地址位置所在页面是否为空
***********************************************************************************************************************/
bool_t SPI_Flash_Device_GD25qxx_IsEmptyPage(uint32_t u32Page_Address, uint32_t u32OffsetInByte, uint32_t u32NumByteToCheck_up_to_PageSize)
{
    uint8_t pu8Buffer[32];
    uint32_t u32WorkAddress;
    uint32_t i;
    
    while (GD25qxx.u8Lock == 1)
    {
        GD25qxx_Delay(1);
    }
    GD25qxx.u8Lock = 1;
    
    if (((u32NumByteToCheck_up_to_PageSize + u32OffsetInByte) > GD25qxx.u16PageSize) || (0 == u32NumByteToCheck_up_to_PageSize))
    {
        u32NumByteToCheck_up_to_PageSize = GD25qxx.u16PageSize - u32OffsetInByte;
    }

    for (i = u32OffsetInByte; i < GD25qxx.u16PageSize; i += sizeof(pu8Buffer))
    {
#if DEV_GD25QXX_NSS_HARD_MODE
        SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                            //CS拉低
#else
        GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                            //CS拉低
#endif
        u32WorkAddress = (i + u32Page_Address * GD25qxx.u16PageSize);
        if (GD25qxx.tID >= GD25Q256)
        {
            GD25qxx_Spi(0x0C);
            GD25qxx_Spi((u32WorkAddress & 0xFF000000) >> 24);
        }
        else
        {
            GD25qxx_Spi(0x0B);                                                                                          //0BH指令，快速读取数据
        }
        GD25qxx_Spi((u32WorkAddress & 0xFF0000) >> 16);                                                                 //A23~A16
        GD25qxx_Spi((u32WorkAddress & 0xFF00) >> 8);                                                                    //A16~A8
        GD25qxx_Spi(u32WorkAddress & 0xFF);                                                                             //A7~A0
        GD25qxx_Spi(GD25QXX_DUMMY_BYTE);                                                                                //写虚拟字节
        HAL_SPI_Receive(&DEV_GD25QXX_SPI, pu8Buffer, sizeof(pu8Buffer), 100);                                           //接收数据
#if DEV_GD25QXX_NSS_HARD_MODE
        SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                               //CS拉高
#else
        GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                                  //CS拉高
#endif
        for (uint8_t j = 0; j < sizeof(pu8Buffer); j++)
        {
            if (pu8Buffer[j] != 0xFF)
            {
                GD25qxx.u8Lock = 0;
                return STATUS_FALSE;
            }
        }
    }
    if ((GD25qxx.u16PageSize + u32OffsetInByte) % sizeof(pu8Buffer) != 0)
    {
        i -= sizeof(pu8Buffer);
        for (; i < GD25qxx.u16PageSize; i++)
        {
#if DEV_GD25QXX_NSS_HARD_MODE
            SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                        //CS拉低
#else
            GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                        //CS拉低
#endif
            u32WorkAddress = (i + u32Page_Address * GD25qxx.u16PageSize);
            GD25qxx_Spi(0x0B);                                                                                          //0BH指令，快速读取数据
            if (GD25qxx.tID >= GD25Q256)
            {
                GD25qxx_Spi(0x0C);
                GD25qxx_Spi((u32WorkAddress & 0xFF000000) >> 24);
            }
            else
            {
                GD25qxx_Spi(0x0B);                                                                                      //0BH指令，快速读取数据
            }
            GD25qxx_Spi((u32WorkAddress & 0xFF0000) >> 16);                                                             //A23~A16
            GD25qxx_Spi((u32WorkAddress & 0xFF00) >> 8);                                                                //A16~A8
            GD25qxx_Spi(u32WorkAddress & 0xFF);                                                                         //A7~A0
            GD25qxx_Spi(GD25QXX_DUMMY_BYTE);                                                                            //写虚拟字节
            HAL_SPI_Receive(&DEV_GD25QXX_SPI, pu8Buffer, 1, 100);                                                       //接收数据
#if DEV_GD25QXX_NSS_HARD_MODE
            SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                       //CS拉高
#else
            GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                          //CS拉高
#endif
            if (pu8Buffer[0] != 0xFF)
            {
                GD25qxx.u8Lock = 0;
                return STATUS_FALSE;
            }
        }
    }

    GD25qxx.u8Lock = 0;
    return STATUS_TRUE;
}
/***********************************************************************************************************************
 功能：判断指定地址位置所在扇区是否为空
***********************************************************************************************************************/
bool_t SPI_Flash_Device_GD25qxx_IsEmptySector(uint32_t u32Sector_Address, uint32_t u32OffsetInByte, uint32_t u32NumByteToCheck_up_to_SectorSize)
{
    uint8_t pu8Buffer[32];
    uint32_t u32WorkAddress;
    uint32_t i;

    while (GD25qxx.u8Lock == 1)
    {
        GD25qxx_Delay(1);
    }
    GD25qxx.u8Lock = 1;
    if ((u32NumByteToCheck_up_to_SectorSize > GD25qxx.u32SectorSize) || (u32NumByteToCheck_up_to_SectorSize == 0))      //参数检查，u32NumByteToCheck_up_to_SectorSize范围为1~u32SectorSize
    {
        u32NumByteToCheck_up_to_SectorSize = GD25qxx.u32SectorSize;                                                     //超出范围重置为默认值u32SectorSize
    }

    for (i = u32OffsetInByte; i < GD25qxx.u32SectorSize; i += sizeof(pu8Buffer))                                        //32byte间隔，检查是否为空
    {
#if DEV_GD25QXX_NSS_HARD_MODE
        SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                            //CS拉低
#else
        GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                            //CS拉低
#endif
        u32WorkAddress = (i + u32Sector_Address * GD25qxx.u32SectorSize);                                               //计算当前地址
        if (GD25qxx.tID >= GD25Q256)
        {
            GD25qxx_Spi(0x0C);
            GD25qxx_Spi((u32WorkAddress & 0xFF000000) >> 24);
        }
        else
        {
            GD25qxx_Spi(0x0B);                                                                                          //0BH指令，高速读数据
        }
        GD25qxx_Spi((u32WorkAddress & 0xFF0000) >> 16);                                                                 //A23~A16
        GD25qxx_Spi((u32WorkAddress & 0xFF00) >> 8);                                                                    //A16~A8
        GD25qxx_Spi(u32WorkAddress & 0xFF);                                                                             //A7~A0
        GD25qxx_Spi(GD25QXX_DUMMY_BYTE);                                                                                //虚拟字节
        HAL_SPI_Receive(&DEV_GD25QXX_SPI, pu8Buffer, sizeof(pu8Buffer), 100);                                           //接收读取的数据
#if DEV_GD25QXX_NSS_HARD_MODE
        SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                           //CS拉高
#else
        GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                              //CS拉高
#endif
        for (uint8_t j = 0; j < sizeof(pu8Buffer); j++)
        {
            if (pu8Buffer[j] != 0xFF)
            {
                GD25qxx.u8Lock = 0;
                return STATUS_FALSE;                                                                                    //不等于0xFF（空），返回false
            }
        }
    }
    if ((GD25qxx.u32SectorSize + u32OffsetInByte) % sizeof(pu8Buffer) != 0)                                             //不为32byte整数部分的检查
    {
        i -= sizeof(pu8Buffer);
        for (; i < GD25qxx.u32SectorSize; i++)
        {
#if DEV_GD25QXX_NSS_HARD_MODE
            SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                        //CS拉低
#else
            GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                        //CS拉低
#endif
            u32WorkAddress = (i + u32Sector_Address * GD25qxx.u32SectorSize);
            if (GD25qxx.tID >= GD25Q256)
            {
                GD25qxx_Spi(0x0C);
                GD25qxx_Spi((u32WorkAddress & 0xFF000000) >> 24);
            }
            else
            {
                GD25qxx_Spi(0x0B);                                                                                      //0BH指令，高速读数据
            }
            GD25qxx_Spi((u32WorkAddress & 0xFF0000) >> 16);                                                             //A23~A16
            GD25qxx_Spi((u32WorkAddress & 0xFF00) >> 8);                                                                //A16~A8
            GD25qxx_Spi(u32WorkAddress & 0xFF);                                                                         //A7~A0
            GD25qxx_Spi(GD25QXX_DUMMY_BYTE);                                                                            //虚拟字节
            HAL_SPI_Receive(&DEV_GD25QXX_SPI, pu8Buffer, 1, 100);                                                       //接收读取的数据
#if DEV_GD25QXX_NSS_HARD_MODE
            SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                       //CS拉高
#else
            GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                          //CS拉高
#endif
            if (pu8Buffer[0] != 0xFF)
            {
                GD25qxx.u8Lock = 0;
                return STATUS_FALSE;                                                                                    //不等于0xFF（空），返回false
            }
        }
    }

    GD25qxx.u8Lock = 0;
    return STATUS_TRUE;
}

/***********************************************************************************************************************
 功能：判断指定地址位置所在存储块是否为空
***********************************************************************************************************************/
bool_t SPI_Flash_Device_GD25qxx_IsEmptyBlock(uint32_t u32Block_Address, uint32_t u32OffsetInByte, uint32_t u32NumByteToCheck_up_to_BlockSize)
{
    uint8_t pu8Buffer[32];
    uint32_t WorkAddress;
    uint32_t i;

    while (GD25qxx.u8Lock == 1)
    {
        GD25qxx_Delay(1);
    }
    GD25qxx.u8Lock = 1;
    if ((u32NumByteToCheck_up_to_BlockSize > GD25qxx.u32BlockSize) || (u32NumByteToCheck_up_to_BlockSize == 0))         //参数检查，u32NumByteToCheck_up_to_BlockSize范围为1~u32BlockSize
    {
        u32NumByteToCheck_up_to_BlockSize = GD25qxx.u32BlockSize;                                                       //超出范围重置为默认值u32BlockSize
    }

    for (i = u32OffsetInByte; i < GD25qxx.u32BlockSize; i += sizeof(pu8Buffer))
    {
#if DEV_GD25QXX_NSS_HARD_MODE
        SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                            //CS拉低
#else
        GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                            //CS拉低
#endif
        WorkAddress = (i + u32Block_Address * GD25qxx.u32BlockSize);

        if (GD25qxx.tID >= GD25Q256)
        {
            GD25qxx_Spi(0x0C);
            GD25qxx_Spi((WorkAddress & 0xFF000000) >> 24);
        }
        else
        {
            GD25qxx_Spi(0x0B);                                                                                          //0BH指令，高速读数据
        }
        GD25qxx_Spi((WorkAddress & 0xFF0000) >> 16);                                                                    //A23~A16
        GD25qxx_Spi((WorkAddress & 0xFF00) >> 8);                                                                       //A16~A8
        GD25qxx_Spi(WorkAddress & 0xFF);                                                                                //A7~A0
        GD25qxx_Spi(GD25QXX_DUMMY_BYTE);                                                                                //虚拟字节
        HAL_SPI_Receive(&DEV_GD25QXX_SPI, pu8Buffer, sizeof(pu8Buffer), 100);                                           //接收读取的数据
#if DEV_GD25QXX_NSS_HARD_MODE
        SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                           //CS拉高
#else
        GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                              //CS拉高
#endif
        for (uint8_t x = 0; x < sizeof(pu8Buffer); x++)
        {
            if (pu8Buffer[x] != 0xFF)
            {
                GD25qxx.u8Lock = 0;
                return STATUS_FALSE;                                                                                    //不等于0xFF（空），返回false
            }
        }
    }
    if ((GD25qxx.u32BlockSize + u32OffsetInByte) % sizeof(pu8Buffer) != 0)                                             //不为32byte整数部分的检查
    {
        i -= sizeof(pu8Buffer);
        for (; i < GD25qxx.u32BlockSize; i++)
        {
#if DEV_GD25QXX_NSS_HARD_MODE
            SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                        //CS拉低
#else
            GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                        //CS拉低
#endif
            WorkAddress = (i + u32Block_Address * GD25qxx.u32BlockSize);

            if (GD25qxx.tID >= GD25Q256)
            {
                GD25qxx_Spi(0x0C);
                GD25qxx_Spi((WorkAddress & 0xFF000000) >> 24);
            }
            else
            {
                GD25qxx_Spi(0x0B);                                                                                      //0BH指令，高速读数据
            }
            GD25qxx_Spi((WorkAddress & 0xFF0000) >> 16);                                                                //A23~A16
            GD25qxx_Spi((WorkAddress & 0xFF00) >> 8);                                                                   //A16~A8
            GD25qxx_Spi(WorkAddress & 0xFF);                                                                            //A7~A0
            GD25qxx_Spi(0);
            HAL_SPI_Receive(&DEV_GD25QXX_SPI, pu8Buffer, 1, 100);
#if DEV_GD25QXX_NSS_HARD_MODE
            SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                       //CS拉高
#else
            GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                          //CS拉高
#endif
            if (pu8Buffer[0] != 0xFF)
            {
                GD25qxx.u8Lock = 0;
                return STATUS_FALSE;                                                                                    //不等于0xFF（空），返回false
            }
        }
    }
    GD25qxx.u8Lock = 0;
    return STATUS_TRUE;
}

/***********************************************************************************************************************
 功能：SPI FLASH写一个字节
***********************************************************************************************************************/
void SPI_Flash_Device_GD25qxx_WriteByte(uint8_t pu8Buffer, uint32_t u32WriteAddr_inBytes)
{
    while (GD25qxx.u8Lock == 1)
    {
        GD25qxx_Delay(1);
    }
    GD25qxx.u8Lock = 1;

    GD25qxx_WaitForWriteEnd();                                                                                          //等待上一次写操作完成
    GD25qxx_WriteEnable();                                                                                              //06H写使能
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                                //CS拉低
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                                //CS拉低
#endif

    if (GD25qxx.tID >= GD25Q256)
    {
        GD25qxx_Spi(0x12);
        GD25qxx_Spi((u32WriteAddr_inBytes & 0xFF000000) >> 24);
    }
    else
    {
        GD25qxx_Spi(0x02);                                                                                              //02H，页编程
    }
    GD25qxx_Spi((u32WriteAddr_inBytes & 0xFF0000) >> 16);                                                               //A23~A16
    GD25qxx_Spi((u32WriteAddr_inBytes & 0xFF00) >> 8);                                                                  //A15~A8
    GD25qxx_Spi(u32WriteAddr_inBytes & 0xFF);                                                                           //A7~A0
    GD25qxx_Spi(pu8Buffer);                                                                                             //写Data
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                               //CS拉高
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                                  //CS拉高
#endif
    GD25qxx_WaitForWriteEnd();                                                                                          //等待写操作完成

    GD25qxx.u8Lock = 0;
}

/***********************************************************************************************************************
 功能：SPI FLASH写一页
***********************************************************************************************************************/
void SPI_Flash_Device_GD25qxx_WritePage(uint8_t *pu8Buffer, uint32_t u32Page_Address, uint32_t u32OffsetInByte, uint32_t u32NumByteToWrite_up_to_PageSize)
{
    while (GD25qxx.u8Lock == 1)
    {
        GD25qxx_Delay(1);
    }
    GD25qxx.u8Lock = 1;
    if (((u32NumByteToWrite_up_to_PageSize + u32OffsetInByte) > GD25qxx.u16PageSize) || \
       (0 == u32NumByteToWrite_up_to_PageSize))                                                                         //u32NumByteToWrite_up_to_PageSize参数检查
    {
        u32NumByteToWrite_up_to_PageSize = GD25qxx.u16PageSize - u32OffsetInByte;
    }

    if(u32OffsetInByte > GD25qxx.u16PageSize)                                                                           //u32OffsetInByte参数检查
    {
        return;
    }

    GD25qxx_WaitForWriteEnd();                                                                                          //等待上一次写操作完成
    GD25qxx_WriteEnable();                                                                                              //06H写使能
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                                //CS拉低
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                                //CS拉低
#endif
    u32Page_Address = (u32Page_Address * GD25qxx.u16PageSize) + u32OffsetInByte;                                        //计算u32Page_Address相对地址
    if (GD25qxx.tID >= GD25Q256)
    {
        GD25qxx_Spi(0x12);
        GD25qxx_Spi((u32Page_Address & 0xFF000000) >> 24);
    }
    else
    {
        GD25qxx_Spi(0x02);                                                                                              //02H,页编程指令
    }
    GD25qxx_Spi((u32Page_Address & 0xFF0000) >> 16);                                                                    //A23~A16
    GD25qxx_Spi((u32Page_Address & 0xFF00) >> 8);                                                                       //A15~A8
    GD25qxx_Spi(u32Page_Address & 0xFF);                                                                                //A7~A0
    HAL_SPI_Transmit(&DEV_GD25QXX_SPI, pu8Buffer, u32NumByteToWrite_up_to_PageSize, 100);                               //写入数据
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                               //CS拉高
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                                  //CS拉高
#endif
    GD25qxx_WaitForWriteEnd();                                                                                          //等待写操作完成

    GD25qxx_Delay(1);                                                                                                   //延时1ms
    GD25qxx.u8Lock = 0;
}

/***********************************************************************************************************************
 功能：SPI FLASH写扇区
***********************************************************************************************************************/
void SPI_Flash_Device_GD25qxx_WriteSector(uint8_t *pu8Buffer, uint32_t u32Sector_Address, uint32_t u32OffsetInByte, uint32_t u32NumByteToWrite_up_to_SectorSize)
{
    uint32_t u32StartPage;
    int32_t s32BytesToWrite;
    uint32_t u32LocalOffset;

    if ((u32NumByteToWrite_up_to_SectorSize > GD25qxx.u32SectorSize) || (u32NumByteToWrite_up_to_SectorSize == 0))      //u32NumByteToWrite_up_to_SectorSize参数检查
    {
        u32NumByteToWrite_up_to_SectorSize = GD25qxx.u32SectorSize;
    }

    if (u32OffsetInByte >= GD25qxx.u32SectorSize)                                                                       //u32OffsetInByte参数检查
    {
        return;
    }

    if ((u32OffsetInByte + u32NumByteToWrite_up_to_SectorSize) > GD25qxx.u32SectorSize)                                 //参数检查，计算s32BytesToWrite
    {
        s32BytesToWrite = GD25qxx.u32SectorSize - u32OffsetInByte;
    }
    else
    {
        s32BytesToWrite = u32NumByteToWrite_up_to_SectorSize;
    }
    u32StartPage = SPI_Flash_Device_GD25qxx_SectorToPage(u32Sector_Address) + (u32OffsetInByte / GD25qxx.u16PageSize);  //计算起始地址
    u32LocalOffset = u32OffsetInByte % GD25qxx.u16PageSize;                                                             //计算Offset地址
    do
    {
        SPI_Flash_Device_GD25qxx_WritePage(pu8Buffer, u32StartPage, u32LocalOffset, s32BytesToWrite);                   //按页写数据
        u32StartPage++;
        s32BytesToWrite -= GD25qxx.u16PageSize - u32LocalOffset;
        pu8Buffer += GD25qxx.u16PageSize - u32LocalOffset;
        u32LocalOffset = 0;
    } while (s32BytesToWrite > 0);

}

/***********************************************************************************************************************
 功能：SPI FLASH写存储块
***********************************************************************************************************************/
void SPI_Flash_Device_GD25qxx_WriteBlock(uint8_t *pu8Buffer, uint32_t u32Block_Address, uint32_t u32OffsetInByte, uint32_t u32NumByteToWrite_up_to_BlockSize)
{
    uint32_t u32StartPage;
    int32_t s32BytesToWrite;
    uint32_t u32LocalOffset;

    if ((u32NumByteToWrite_up_to_BlockSize > GD25qxx.u32BlockSize) || (u32NumByteToWrite_up_to_BlockSize == 0))         //u32NumByteToWrite_up_to_BlockSize参数检查
    {
        u32NumByteToWrite_up_to_BlockSize = GD25qxx.u32BlockSize;
    }

    if (u32OffsetInByte >= GD25qxx.u32BlockSize)                                                                        //u32OffsetInByte参数检查
    {
        return;
    }

    if ((u32OffsetInByte + u32NumByteToWrite_up_to_BlockSize) > GD25qxx.u32BlockSize)                                   //参数检查，计算s32BytesToWrite
    {
        s32BytesToWrite = GD25qxx.u32BlockSize - u32OffsetInByte;
    }
    else
    {
        s32BytesToWrite = u32NumByteToWrite_up_to_BlockSize;
    }
    u32StartPage = SPI_Flash_Device_GD25qxx_BlockToPage(u32Block_Address) + (u32OffsetInByte / GD25qxx.u16PageSize);    //计算起始地址
    u32LocalOffset = u32OffsetInByte % GD25qxx.u16PageSize;                                                             //计算Offset地址
    do
    {
        SPI_Flash_Device_GD25qxx_WritePage(pu8Buffer, u32StartPage, u32LocalOffset, s32BytesToWrite);                   //按页写数据
        u32StartPage++;
        s32BytesToWrite -= GD25qxx.u16PageSize - u32LocalOffset;
        pu8Buffer += GD25qxx.u16PageSize - u32LocalOffset;
        u32LocalOffset = 0;
    } while (s32BytesToWrite > 0);
}

/***********************************************************************************************************************
 功能：SPI FLASH读单个字节
***********************************************************************************************************************/
void SPI_Flash_Device_GD25qxx_ReadByte(uint8_t *pu8Buffer, uint32_t u32Bytes_Address)
{
    while (GD25qxx.u8Lock == 1)
    {
        GD25qxx_Delay(1);
    }
    GD25qxx.u8Lock = 1;

#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                                //CS拉低
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                                //CS拉低
#endif

    if (GD25qxx.tID >= GD25Q256)
    {
        GD25qxx_Spi(0x0C);
        GD25qxx_Spi((u32Bytes_Address & 0xFF000000) >> 24);
    }
    else
    {
        GD25qxx_Spi(0x0B);                                                                                              //0BH，高速按字节读数据
    }
    GD25qxx_Spi((u32Bytes_Address & 0xFF0000) >> 16);                                                                   //A23~A16
    GD25qxx_Spi((u32Bytes_Address & 0xFF00) >> 8);                                                                      //A15~A8
    GD25qxx_Spi(u32Bytes_Address & 0xFF);                                                                               //A7~A0
    GD25qxx_Spi(GD25QXX_DUMMY_BYTE);
    *pu8Buffer = GD25qxx_Spi(GD25QXX_DUMMY_BYTE);                                                                       //发送虚拟字节，读取数据
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                               //CS拉高
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                                  //CS拉高
#endif

    GD25qxx.u8Lock = 0;
}

/***********************************************************************************************************************
 功能：SPI FLASH读若干字节
***********************************************************************************************************************/
void SPI_Flash_Device_GD25qxx_ReadBytes(uint8_t *pu8Buffer, uint32_t u32ReadAddr, uint32_t u32NumByteToRead)
{
    while (GD25qxx.u8Lock == 1)
    {
        GD25qxx_Delay(1);
    }
    GD25qxx.u8Lock = 1;

#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                                //CS拉低
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                                //CS拉低
#endif

    if (GD25qxx.tID >= GD25Q256)
    {
        GD25qxx_Spi(0x0C);
        GD25qxx_Spi((u32ReadAddr & 0xFF000000) >> 24);
    }
    else
    {
        GD25qxx_Spi(0x0B);                                                                                              //0BH，高速按字节读数据
    }
    GD25qxx_Spi((u32ReadAddr & 0xFF0000) >> 16);                                                                        //A23~A16
    GD25qxx_Spi((u32ReadAddr & 0xFF00) >> 8);                                                                           //A15~A8
    GD25qxx_Spi(u32ReadAddr & 0xFF);                                                                                    //A7~A0
    GD25qxx_Spi(GD25QXX_DUMMY_BYTE);
    HAL_SPI_Receive(&DEV_GD25QXX_SPI, pu8Buffer, u32NumByteToRead, 2000);                                               //接收数据流
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                               //CS拉高
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                                  //CS拉高
#endif

    GD25qxx_Delay(1);
    GD25qxx.u8Lock = 0;
}

/***********************************************************************************************************************
 功能：SPI FLASH读页
***********************************************************************************************************************/
void SPI_Flash_Device_GD25qxx_ReadPage(uint8_t *pu8Buffer, uint32_t u32Page_Address, uint32_t u32OffsetInByte, uint32_t u32NumByteToRead_up_to_PageSize)
{
    while (GD25qxx.u8Lock == 1)
    {
        GD25qxx_Delay(1);
    }
    GD25qxx.u8Lock = 1;
    if ((u32NumByteToRead_up_to_PageSize > GD25qxx.u16PageSize) || (u32NumByteToRead_up_to_PageSize == 0))              //参数检查
    {
        u32NumByteToRead_up_to_PageSize = GD25qxx.u16PageSize;
    }
    if ((u32OffsetInByte + u32NumByteToRead_up_to_PageSize) > GD25qxx.u16PageSize)
    {
        u32NumByteToRead_up_to_PageSize = GD25qxx.u16PageSize - u32OffsetInByte;
    }

    u32Page_Address = u32Page_Address * GD25qxx.u16PageSize + u32OffsetInByte;                                          //计算页地址
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Enable(&DEV_GD25QXX_SPI);                                                                                //CS拉低
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_RESET);                                //CS拉低
#endif
    if (GD25qxx.tID >= GD25Q256)
    {
        GD25qxx_Spi(0x0C);
        GD25qxx_Spi((u32Page_Address & 0xFF000000) >> 24);
    }
    else
    {
        GD25qxx_Spi(0x0B);                                                                                              //0BH，高速按字节读数据
    }
    GD25qxx_Spi((u32Page_Address & 0xFF0000) >> 16);                                                                    //A23~A16
    GD25qxx_Spi((u32Page_Address & 0xFF00) >> 8);                                                                       //A15~A8
    GD25qxx_Spi(u32Page_Address & 0xFF);                                                                                //A7~A0
    GD25qxx_Spi(GD25QXX_DUMMY_BYTE);
    HAL_SPI_Receive(&DEV_GD25QXX_SPI, pu8Buffer, u32NumByteToRead_up_to_PageSize, 100);                                 //接收数据
#if DEV_GD25QXX_NSS_HARD_MODE
    SPI_driver_Disable(&DEV_GD25QXX_SPI);                                                                               //CS拉高
#else
    GPIO_Driver_WriteOutputPin(DEV_GD25QXX_CS_GPIO, DEV_GD25QXX_CS_PIN, GPIO_PIN_SET);                                  //CS拉高
#endif

    GD25qxx_Delay(1);
    GD25qxx.u8Lock = 0;
}

/***********************************************************************************************************************
 功能：SPI FLASH读扇区
***********************************************************************************************************************/
void SPI_Flash_Device_GD25qxx_ReadSector(uint8_t *pu8Buffer, uint32_t u32Sector_Address, uint32_t u32OffsetInByte, uint32_t u32NumByteToRead_up_to_SectorSize)
{
    uint32_t u32StartPage;
    int32_t s32BytesToRead;
    uint32_t u32LocalOffset;

    if ((u32NumByteToRead_up_to_SectorSize > GD25qxx.u32SectorSize) || (u32NumByteToRead_up_to_SectorSize == 0))        //参数检查
    {
        u32NumByteToRead_up_to_SectorSize = GD25qxx.u32SectorSize;
    }

    if (u32OffsetInByte >= GD25qxx.u32SectorSize)
    {
        return;
    }

    if ((u32OffsetInByte + u32NumByteToRead_up_to_SectorSize) > GD25qxx.u32SectorSize)
    {
        s32BytesToRead = GD25qxx.u32SectorSize - u32OffsetInByte;
    }
    else
    {
        s32BytesToRead = u32NumByteToRead_up_to_SectorSize;
    }
    u32StartPage = SPI_Flash_Device_GD25qxx_SectorToPage(u32Sector_Address) + (u32OffsetInByte / GD25qxx.u16PageSize);  //计算起始页
    u32LocalOffset = u32OffsetInByte % GD25qxx.u16PageSize;                                                             //计算偏移量
    do
    {
        SPI_Flash_Device_GD25qxx_ReadPage(pu8Buffer, u32StartPage, u32LocalOffset, s32BytesToRead);                     //按页读取数据
        u32StartPage++;
        s32BytesToRead -= GD25qxx.u16PageSize - u32LocalOffset;
        pu8Buffer += GD25qxx.u16PageSize - u32LocalOffset;
        u32LocalOffset = 0;
    } while (s32BytesToRead > 0);

}

/***********************************************************************************************************************
 功能：SPI FLASH读存储块
***********************************************************************************************************************/
void SPI_Flash_Device_GD25qxx_ReadBlock(uint8_t *pu8Buffer, uint32_t u32Block_Address, uint32_t u32OffsetInByte, uint32_t u32NumByteToRead_up_to_BlockSize)
{
    uint32_t u32StartPage;
    int32_t s32BytesToRead;
    uint32_t u32LocalOffset;

    if ((u32NumByteToRead_up_to_BlockSize > GD25qxx.u32BlockSize) || (u32NumByteToRead_up_to_BlockSize == 0))           //参数检查
    {
        u32NumByteToRead_up_to_BlockSize = GD25qxx.u32BlockSize;
    }

    if (u32OffsetInByte >= GD25qxx.u32BlockSize)
    {
        return;
    }

    if ((u32OffsetInByte + u32NumByteToRead_up_to_BlockSize) > GD25qxx.u32BlockSize)
    {
        s32BytesToRead = GD25qxx.u32BlockSize - u32OffsetInByte;
    }
    else
    {
        s32BytesToRead = u32NumByteToRead_up_to_BlockSize;
    }
    u32StartPage = SPI_Flash_Device_GD25qxx_BlockToPage(u32Block_Address) + (u32OffsetInByte / GD25qxx.u16PageSize);    //计算起始页
    u32LocalOffset = u32OffsetInByte % GD25qxx.u16PageSize;                                                             //计算偏移量
    do
    {
        SPI_Flash_Device_GD25qxx_ReadPage(pu8Buffer, u32StartPage, u32LocalOffset, s32BytesToRead);                     //按页读取数据
        u32StartPage++;
        s32BytesToRead -= GD25qxx.u16PageSize - u32LocalOffset;
        pu8Buffer += GD25qxx.u16PageSize - u32LocalOffset;
        u32LocalOffset = 0;
    } while (s32BytesToRead > 0);

}
uint8_t u8TempReadTab[4096] = {0};

/***********************************************************************************************************************
 功能：SPI FLASH写入任意区域数据
***********************************************************************************************************************/
void SPI_Flash_Device_GD25qxx_WriteBytes(uint32_t u32StartAddr, uint32_t u32Length, uint8_t *pu8Buff)
{
    uint16_t u16StartSectorID = 0;
    uint16_t u16EndSectorID = 0;
    uint16_t u16StartSectorOffset = 0;
    uint16_t u16EndSectorOffset = 0;
    uint16_t i;

    u16StartSectorID = u32StartAddr >> 12;
    u16StartSectorOffset = u32StartAddr - u16StartSectorID * GD25qxx.u32SectorSize;
    u16EndSectorID = (u32StartAddr + u32Length) >> 12;
    u16EndSectorOffset = (u32StartAddr + u32Length) - (u16EndSectorID * GD25qxx.u32SectorSize);
    for(i = u16StartSectorID; i <= u16EndSectorID; i++)
    {
        if(i == u16StartSectorID)
        {
            SPI_Flash_Device_GD25qxx_ReadSector(u8TempReadTab, i, 0, GD25qxx.u32SectorSize);
            if(0 != memcmp(&u8TempReadTab[u16StartSectorOffset], pu8Buff, GD25qxx.u32SectorSize - u16StartSectorOffset))
            {
                memcpy(&u8TempReadTab[u16StartSectorOffset], pu8Buff, GD25qxx.u32SectorSize - u16StartSectorOffset);
                SPI_Flash_Device_GD25qxx_EraseSector(i);
                SPI_Flash_Device_GD25qxx_WriteSector(u8TempReadTab, i, 0, GD25qxx.u32SectorSize);
            }
            pu8Buff += (GD25qxx.u32SectorSize - u16StartSectorOffset);
        }
        else if(i == u16EndSectorID)
        {
            SPI_Flash_Device_GD25qxx_ReadSector(u8TempReadTab, i, 0, GD25qxx.u32SectorSize);
            if(0 != memcmp(u8TempReadTab, pu8Buff, u16EndSectorOffset))
            {
                memcpy(u8TempReadTab, pu8Buff, u16EndSectorOffset);
                SPI_Flash_Device_GD25qxx_EraseSector(i);
                SPI_Flash_Device_GD25qxx_WriteSector(u8TempReadTab, i, 0, GD25qxx.u32SectorSize);
            }
            pu8Buff += u16EndSectorOffset;
        }
        else
        {
            SPI_Flash_Device_GD25qxx_ReadSector(u8TempReadTab, i, 0, GD25qxx.u32SectorSize);
            if(0 != memcmp(u8TempReadTab, pu8Buff, GD25qxx.u32SectorSize - u16StartSectorOffset))
            {
                memcpy(u8TempReadTab, pu8Buff, u16EndSectorOffset);
                SPI_Flash_Device_GD25qxx_EraseSector(i);
                SPI_Flash_Device_GD25qxx_WriteSector(u8TempReadTab, i, 0, GD25qxx.u32SectorSize);
            }
            pu8Buff += GD25qxx.u32SectorSize;
        }
    }
}


#endif      /***Module End***/

#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

