/***********************************************************************************************************************
* Copyright (c)  , CVTE
* ***********************************************************************************************************************
* 文件名     : crc_driver.c
* 用途       :
************************************************************************************************************************/

#include "crc_driver.h"
#include <string.h>

/***********************************************************************************************************************
Global variables and funtions
************************************************************************************************************************/



/***********************************************************************************************************************
功能： 初始化硬件CRC
***********************************************************************************************************************/
void CRC_Dev_Initail(void)
{
    //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
}


/***********************************************************************************************************************
功能： 硬件CRC32计算
***********************************************************************************************************************/
uint32_t GetCRC32(uint32_t * Buffer, uint32_t Length)
{
    //CRC_ResetDR();
    //return CRC_CalcBlockCRC(Buffer, Length);
    return 0;
}

/***********************************************************************************************************************
* Copyright (c)  CVTE All rights reserved.  * * * END OF FILE
************************************************************************************************************************/
