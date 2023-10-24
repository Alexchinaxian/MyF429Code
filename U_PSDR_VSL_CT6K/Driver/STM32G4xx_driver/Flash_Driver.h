/***********************************************************************************************************************
* Copyright (c) , CVTE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 文件 : Flash_Driver.h 
 用途 : Flash BSP驱动定义
***********************************************************************************************************************/
#ifndef __FLASH_DRIVER_H__
#define __FLASH_DRIVER_H__

#include "MCU.h"

#if MODULE_FLASH_ONCHIP


/***********************************************************************************************************************
 * FLASH块写字节大小
***********************************************************************************************************************/
#define FLASH_BYTE                1
#define FLASH_HALF_WORD           2
#define FLASH_WORD                4
#define FLASH_DOUBLE_WORD         8

#define FLASH_WRITE_SIZE          FLASH_DOUBLE_WORD


extern void Flash_Bsp_Init(void);
extern void Flash_Bsp_Unlock(void);
extern void Flash_Bsp_Lock(void);
extern HAL_StatusTypeDef Flash_Bsp_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *PageError);
extern HAL_StatusTypeDef Flash_Bsp_Program(uint32_t TypeProgram, uint32_t Address, uint64_t Data);



#endif      /***Module End***/
#endif

/***********************************************************************************************************************
* * Copyright (c) , CVTE All rights reserved.  * * * END OF FILE
***********************************************************************************************************************/
