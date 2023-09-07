#include "Mid_pdu.h"
/*������������Ȧ������״̬������ת��ΪMB�ֽ�����,������������ĳ���*/
static uint16_t ConvertBoolArrayToMBByteArray(bool *sData, uint16_t length, uint8_t *oData);

static uint16_t ConvertRegisterArrayToMBByteArray(uint16_t *sData, uint16_t length, uint8_t *oData);

/*��ΪRTU��վ��TCP�ͻ��ˣ�ʱ�����ɶ�дRTU��վ��TCP�����������������*/
uint16_t GenerateReadWriteCommand(ObjAccessInfo objInfo, bool *statusList, uint16_t *registerList, uint8_t *commandBytes)
{
  uint16_t index = 0;
  commandBytes[index++] = objInfo.unitID;               // ��վ��ַ
  commandBytes[index++] = objInfo.functionCode;         // ������
  commandBytes[index++] = objInfo.startingAddress >> 8; // ��ʼ��ַ���ֽ�
  commandBytes[index++] = objInfo.startingAddress;      // ��ʼ��ַ���ֽ�

  /*����վ����*/
  if ((objInfo.functionCode >= ReadCoilStatus) && (objInfo.functionCode <= ReadInputRegister))
  {
    commandBytes[index++] = objInfo.quantity >> 8;
    commandBytes[index++] = objInfo.quantity;
  }

  /*д������Ȧ���ݶ���*/
  if ((WriteSingleCoil == objInfo.functionCode) && (statusList != NULL))
  {
    commandBytes[index++] = (*statusList) ? 0xFF : 0x00;
    commandBytes[index++] = 0x00;
  }

  /*д�����Ĵ������ݶ���*/
  if ((objInfo.functionCode == WriteSingleRegister) && (registerList != NULL))
  {
    commandBytes[index++] = (*registerList) >> 8;
    commandBytes[index++] = (*registerList);
  }

  /*д�����Ȧ*/
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

  /*д����Ĵ���*/
  if ((objInfo.functionCode == WriteMultipleRegister) && (registerList != NULL))
  {
    commandBytes[index++] = objInfo.quantity >> 8; // �������ֽ�
    commandBytes[index++] = objInfo.quantity;      // �������ֽ�
    uint8_t byteArray[250];
    uint16_t bytesCount = ConvertRegisterArrayToMBByteArray(registerList, objInfo.quantity, byteArray);
    commandBytes[index++] = bytesCount; // �ֽ�����
    for (int i = 0; i < bytesCount; i++)
    {
      commandBytes[index++] = byteArray[i];
    }
  }
  return index;
}

/*���Ĵ���������Ĵ����ͱ��ּĴ���������ת��ΪMB�ֽ�����,������������ĳ���*/
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
/*������������Ȧ������״̬������ת��ΪMB�ֽ�����,������������ĳ���*/
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
