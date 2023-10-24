/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Flash_Device.h 
 用途 : 存储Flash定义
***********************************************************************************************************************/
#ifndef __FLASH_DEVICE_H__
#define __FLASH_DEVICE_H__

#include "Flash_Driver.h"

#if MODULE_FLASH_ONCHIP

extern void Flash_Device_InitVar(void);
extern bool_t Flash_Device_WriteTbl(uint32_t u32Addr, uint8_t *pu8Buffer, uint32_t u32Count);
extern void Flash_Device_ReadTbl(uint32_t u32Addr, uint8_t *pu8Buffer, uint32_t u32Count);
extern bool_t Flash_Device_Erase(uint32_t u32TypeErase, uint32_t u32Bank, uint32_t u32NbPages, uint32_t u32Page);

#endif      /***Module End***/

#if MODULE_FLASH_EXTERN

bool_t SPI_Flash_Device_GD25qxx_Init(void);
void SPI_Flash_Device_GD25qxx_Test(void);
void GD25qxx_ReadStatusRegistor(void);

void SPI_Flash_Device_GD25qxx_EraseChip(void);
void SPI_Flash_Device_GD25qxx_EraseSector(uint32_t SectorAddr);
void SPI_Flash_Device_GD25qxx_EraseBlock(uint32_t BlockAddr);

uint32_t SPI_Flash_Device_GD25qxx_PageToSector(uint32_t PageAddress);
uint32_t SPI_Flash_Device_GD25qxx_PageToBlock(uint32_t PageAddress);
uint32_t SPI_Flash_Device_GD25qxx_SectorToBlock(uint32_t SectorAddress);
uint32_t SPI_Flash_Device_GD25qxx_SectorToPage(uint32_t SectorAddress);
uint32_t SPI_Flash_Device_GD25qxx_BlockToPage(uint32_t BlockAddress);

bool_t SPI_Flash_Device_GD25qxx_IsEmptyPage(uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_PageSize);
bool_t SPI_Flash_Device_GD25qxx_IsEmptySector(uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_SectorSize);
bool_t SPI_Flash_Device_GD25qxx_IsEmptyBlock(uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_BlockSize);

void SPI_Flash_Device_GD25qxx_WriteByte(uint8_t pBuffer, uint32_t WriteAddr_inBytes);
void SPI_Flash_Device_GD25qxx_WritePage(uint8_t *pBuffer, uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_PageSize);
void SPI_Flash_Device_GD25qxx_WriteSector(uint8_t *pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_SectorSize);
void SPI_Flash_Device_GD25qxx_WriteBlock(uint8_t *pBuffer, uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_BlockSize);
void SPI_Flash_Device_GD25qxx_WriteBytes(uint32_t u32StartAddr, uint32_t u32Length, uint8_t *pu8Buff);

void SPI_Flash_Device_GD25qxx_ReadByte(uint8_t *pBuffer, uint32_t Bytes_Address);
void SPI_Flash_Device_GD25qxx_ReadBytes(uint8_t *pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);
void SPI_Flash_Device_GD25qxx_ReadPage(uint8_t *pBuffer, uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_PageSize);
void SPI_Flash_Device_GD25qxx_ReadSector(uint8_t *pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_SectorSize);
void SPI_Flash_Device_GD25qxx_ReadBlock(uint8_t *pBuffer, uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_BlockSize);

#endif      /***Module End***/

#endif
/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/

