#include "Mid_pdu.h"
/*将布尔量（线圈和输入状态）数组转化为MB字节数组,返回最终数组的长度*/
static uint16_t ConvertBoolArrayToMBByteArray(bool *sData, uint16_t length, uint8_t *oData);

static uint16_t ConvertRegisterArrayToMBByteArray(uint16_t *sData, uint16_t length, uint8_t *oData);

/*作为RTU主站（TCP客户端）时，生成读写RTU从站（TCP服务器）对象的命令*/
uint16_t GenerateReadWriteCommand(ObjAccessInfo objInfo, bool *statusList, uint16_t *registerList, uint8_t *commandBytes)
{
  uint16_t index = 0;
  commandBytes[index++] = objInfo.unitID;               // 从站地址
  commandBytes[index++] = objInfo.functionCode;         // 功能码
  commandBytes[index++] = objInfo.startingAddress >> 8; // 起始地址高字节
  commandBytes[index++] = objInfo.startingAddress;      // 起始地址低字节

  /*读从站对象*/
  if ((objInfo.functionCode >= ReadCoilStatus) && (objInfo.functionCode <= ReadInputRegister))
  {
    commandBytes[index++] = objInfo.quantity >> 8;
    commandBytes[index++] = objInfo.quantity;
  }

  /*写单个线圈数据对象*/
  if ((WriteSingleCoil == objInfo.functionCode) && (statusList != NULL))
  {
    commandBytes[index++] = (*statusList) ? 0xFF : 0x00;
    commandBytes[index++] = 0x00;
  }

  /*写单个寄存器数据对象*/
  if ((objInfo.functionCode == WriteSingleRegister) && (registerList != NULL))
  {
    commandBytes[index++] = (*registerList) >> 8;
    commandBytes[index++] = (*registerList);
  }

  /*写多个线圈*/
  if ((objInfo.functionCode == WriteMultipleCoil) && (statusList != NULL))
  {
    commandBytes[index++] = objInfo.quantity >> 8;
    commandBytes[index++] = objInfo.quantity;
    uint8_t byteArray[250];
    uint16_t bytesCount = ConvertBoolArrayToMBByteArray(statusList, objInfo.quantity, byteArray);
    commandBytes[index++] = bytesCount;
    for (int i = 0; i < bytesCount; i++)
    {
      commandBytes[index++] = byteArray[i];
    }
  }

  /*写多个寄存器*/
  if ((objInfo.functionCode == WriteMultipleRegister) && (registerList != NULL))
  {
    commandBytes[index++] = objInfo.quantity >> 8; // 数量高字节
    commandBytes[index++] = objInfo.quantity;      // 数量低字节
    uint8_t byteArray[250];
    uint16_t bytesCount = ConvertRegisterArrayToMBByteArray(registerList, objInfo.quantity, byteArray);
    commandBytes[index++] = bytesCount; // 字节数量
    for (int i = 0; i < bytesCount; i++)
    {
      commandBytes[index++] = byteArray[i];
    }
  }
  return index;
}

/*将寄存器（输入寄存器和保持寄存器）数组转化为MB字节数组,返回最终数组的长度*/
static uint16_t ConvertRegisterArrayToMBByteArray(uint16_t *sData, uint16_t length, uint8_t *oData)
{
  uint16_t returnLength = 0;
  if (length > 0)
  {
    for (int i = 0; i < length; i++)
    {
      oData[returnLength++] = (sData[i] >> 8);
      oData[returnLength++] = sData[i];
    }
  }
  return returnLength;
}
/*将布尔量（线圈和输入状态）数组转化为MB字节数组,返回最终数组的长度*/
static uint16_t ConvertBoolArrayToMBByteArray(bool *sData, uint16_t length, uint8_t *oData)
{
  uint16_t returnLength = 0;
  if (length > 0)
  {
    returnLength = (length - 1) / 8 + 1;

    for (int i = 0; i < returnLength; i++)
    {
      for (int j = 0; j < 8; j++)
      {
        if ((i * 8 + j) < length)
        {
          oData[i] = oData[i] + ((uint8_t)sData[i * 8 + j] << j);
        }
      }
    }
  }

  return returnLength;
}
