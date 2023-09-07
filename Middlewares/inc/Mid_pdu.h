#ifndef __mbpdu_h
#define __mbpdu_h

#include "stdint.h"
#include "stddef.h"
#include "stdbool.h"
#include "string.h"

/*����Modbus�Ĳ��������룬֧��01��02��03��04��05��06��15��16������*/
typedef enum
{
  ReadCoilStatus = 0x01,         /*����Ȧ״̬����������λ��״̬��*/
  ReadInputStatus = 0x02,        /*������λ״̬�����������λ��״̬��*/
  ReadHoldingRegister = 0x03,    /*�����ּĴ�������������ּĴ�������ֵ��*/
  ReadInputRegister = 0x04,      /*������Ĵ��������������Ĵ�������ֵ��*/
  WriteSingleCoil = 0x05,        /*ǿ�Ƶ�����Ȧ��ǿ�Ƶ������λ��״̬��*/
  WriteSingleRegister = 0x06,    /*Ԥ�Ƶ����Ĵ������趨һ���Ĵ�������ֵ��*/
  WriteMultipleCoil = 0x0F,      /*ǿ�ƶ����Ȧ��ǿ�ƶ�����λ��״̬��*/
  WriteMultipleRegister = 0x10,  /*Ԥ�ƶ���Ĵ������趨����Ĵ�������ֵ��*/
  ReadFileRecord = 0x14,         /*���ļ���¼*/
  WriteFileRecord = 0x15,        /*д�ļ���¼*/
  MaskWriteRegister = 0x16,      /*����д�Ĵ���*/
  ReadWriteMultiRegister = 0x17, /*��д����Ĵ���*/
  ReadDeviceID = 0x2B            /*���豸ʶ����*/
} FunctionCode;
/*������յ�ָ�������ʱ�Ĵ�����*/
typedef enum
{
  Modbus_OK = 0x00,            // �޴���
  InvalidFunctionCode = 0x01,  // ���Ϸ����ܴ���
  IllegalDataAddress = 0x02,   // �Ƿ������ݵ�ַ
  IllegalDataValues = 0x03,    // �Ƿ�������ֵ���߷�Χ
  SlaveFailure = 0x04,         // ��վ�豸����
  Acknowledgement = 0x05,      // ȷ��
  SlaveDeviceBusy = 0x06,      // �����豸æ
  MemoryParityError = 0x08,    // �洢��ż�Բ��
  GatewayDisabled = 0x0A,      // ����������·��
  GatewayResponseFailed = 0x0B // ����Ŀ���豸��Ӧʧ��
} ModbusStatus;

/*�������ڴ���Ҫ���ʴ�վ��������������Ϣ*/
typedef struct
{
  uint8_t unitID;
  FunctionCode functionCode;
  uint16_t startingAddress;
  uint16_t quantity;
} ObjAccessInfo;

uint16_t GenerateReadWriteCommand(ObjAccessInfo objInfo, bool *statusList, uint16_t *registerList, uint8_t *commandBytes);

#endif
