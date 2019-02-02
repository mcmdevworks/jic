/*
 * Serial.c
 *
 *  Created on: 01-Jan-2019
 *      Author: mmanjrekar
 */

#include "Serial.h"
#include <string.h>



/* Global Serial Ports */
_sSerialPort sSerialPort[eSerial_Max];
USART_TypeDef *pUSARTPorts[eSerial_Max] = {USART1, USART4, USART3};

void Serial_Init(void)
{
	USART_InitTypeDef UsartPort;

	/* Configure Debug Port */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_DeInit(&UsartPort);
	UsartPort.USART_BaudRate = 115200;
	UsartPort.USART_WordLength = USART_WordLength_8b;
	UsartPort.USART_StopBits = USART_StopBits_1;
	UsartPort.USART_Parity = USART_Parity_No;
	UsartPort.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	UsartPort.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &UsartPort);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	NVIC_EnableIRQ(USART1_IRQn);

	/* Configure GSM port */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART4, ENABLE);
	USART_DeInit(&UsartPort);
	UsartPort.USART_BaudRate = 115200;
	UsartPort.USART_WordLength = USART_WordLength_8b;
	UsartPort.USART_StopBits = USART_StopBits_1;
	UsartPort.USART_Parity = USART_Parity_No;
	UsartPort.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	UsartPort.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART4, &UsartPort);
	USART_ITConfig(USART4, USART_IT_RXNE, ENABLE);
	NVIC_EnableIRQ(USART3_8_IRQn);

	/* Configure Modbus port */

}

bool Serial_InitBuffer(_eSerialPort ePort, uint8_t *pRxBuf, uint16_t u16RxBufSize, uint8_t *pTxBuf, uint16_t u16TxBufSize)
{
	if((ePort >= eSerial_Max) || (pRxBuf == NULL) || (pTxBuf == NULL))
	{
		return false;
	}
	else
	{
		memset(&sSerialPort[ePort], 0, sizeof(sSerialPort[ePort]));
		sSerialPort[ePort].pPort = pUSARTPorts[ePort];
		sSerialPort[ePort].sRxBuff.pu8Buff = pRxBuf;
		sSerialPort[ePort].sRxBuff.u16GetIndex = 0;
		sSerialPort[ePort].sRxBuff.u16PutIndex = 0;
		sSerialPort[ePort].sRxBuff.u16MaxSize = u16RxBufSize;
		sSerialPort[ePort].sTxBuff.pu8Buff = pTxBuf;
		sSerialPort[ePort].sTxBuff.u16GetIndex = 0;
		sSerialPort[ePort].sTxBuff.u16PutIndex = 0;
		sSerialPort[ePort].sTxBuff.u16MaxSize = u16TxBufSize;
		return true;
	}
}

void Serial_TxCallback(_eSerialPort ePort)
{
	// Get the next byte from ring buffer
	if(Serial_TxGetCount(ePort) > 0)
	{
		USART_SendData(sSerialPort[ePort].pPort, (uint16_t)Serial_TxGetByte(ePort));
	}
	// Ring buffer is empty, end transmission
	else
	{
		USART_ITConfig(sSerialPort[ePort].pPort, USART_IT_TXE, DISABLE);
	}
}

void Serial_RxCallback(_eSerialPort ePort, uint8_t u8Byte)
{
	Serial_RxPutByte(ePort, u8Byte);
}

void Serial_Write(_eSerialPort ePort, uint8_t *pu8Buf, uint16_t u16Len)
{
	uint16_t i;

	for(i=0; i<u16Len; i++)
	{
		sSerialPort[ePort].sTxBuff.pu8Buff[sSerialPort[ePort].sTxBuff.u16PutIndex] = pu8Buf[i];
		sSerialPort[ePort].sTxBuff.u16PutIndex++;
		if(sSerialPort[ePort].sTxBuff.u16PutIndex >= sSerialPort[ePort].sTxBuff.u16MaxSize)
		{
			sSerialPort[ePort].sTxBuff.u16PutIndex = 0;
		}
	}
	/* Initiate Transfer */
	USART_ITConfig(sSerialPort[ePort].pPort, USART_IT_TXE, ENABLE);
}

void Serial_WriteByte(_eSerialPort ePort, uint8_t u8Byte)
{
	Serial_Write(ePort, &u8Byte, 1);
}

void Serial_WriteString(_eSerialPort ePort, char *pszStr)
{
	Serial_Write(ePort, (uint8_t*)pszStr, strlen(pszStr));
}

uint8_t Serial_TxGetByte(_eSerialPort ePort)
{
	uint8_t u8Byte = 0;

	if(sSerialPort[ePort].sTxBuff.u16PutIndex != sSerialPort[ePort].sTxBuff.u16GetIndex)
	{
		u8Byte = sSerialPort[ePort].sTxBuff.pu8Buff[sSerialPort[ePort].sTxBuff.u16GetIndex];
		sSerialPort[ePort].sTxBuff.u16GetIndex++;
		if(sSerialPort[ePort].sTxBuff.u16GetIndex >= sSerialPort[ePort].sTxBuff.u16MaxSize)
		{
			sSerialPort[ePort].sTxBuff.u16GetIndex = 0;
		}
	}
	return u8Byte;
}

uint16_t Serial_TxGetCount(_eSerialPort ePort)
{
	uint16_t u16Count = 0;
	uint16_t u16Index = sSerialPort[ePort].sTxBuff.u16GetIndex;

	while(u16Index != sSerialPort[ePort].sTxBuff.u16PutIndex)
	{
		u16Count++;
		u16Index++;
		if(u16Index >= sSerialPort[ePort].sTxBuff.u16MaxSize)
		{
			u16Index = 0;
		}
	}
	return u16Count;
}

void Serial_RxPutByte(_eSerialPort ePort, uint8_t u8Byte)
{
	sSerialPort[ePort].sRxBuff.pu8Buff[sSerialPort[ePort].sRxBuff.u16PutIndex] = u8Byte;
	sSerialPort[ePort].sRxBuff.u16PutIndex++;
	if(sSerialPort[ePort].sRxBuff.u16PutIndex >= sSerialPort[ePort].sRxBuff.u16MaxSize)
	{
		sSerialPort[ePort].sRxBuff.u16PutIndex = 0;
	}
}

uint16_t Serial_RxGetCount(_eSerialPort ePort)
{
	uint16_t u16Count = 0;
	uint16_t u16Index = sSerialPort[ePort].sRxBuff.u16GetIndex;

	while(u16Index != sSerialPort[ePort].sRxBuff.u16PutIndex)
	{
		u16Count++;
		u16Index++;
		if(u16Index >= sSerialPort[ePort].sRxBuff.u16MaxSize)
		{
			u16Index = 0;
		}
	}
	return u16Count;
}

uint8_t Serial_ReadByte(_eSerialPort ePort)
{
	uint8_t u8Byte;

	u8Byte = sSerialPort[ePort].sRxBuff.pu8Buff[sSerialPort[ePort].sRxBuff.u16GetIndex];
	if(sSerialPort[ePort].sRxBuff.u16GetIndex > sSerialPort[ePort].sRxBuff.u16MaxSize)
	{
		sSerialPort[ePort].sRxBuff.u16GetIndex = 0;
	}
	return u8Byte;
}

uint16_t Serial_Read(_eSerialPort ePort, uint8_t *pBuf, uint16_t u16Len)
{
	uint16_t u16Count = Serial_RxGetCount(ePort);
	uint16_t i;

	if(u16Count > 0)
	{
		if(u16Len > u16Count)
		{
			u16Len = u16Count;
		}
		for(i=0; i<u16Len; i++)
		{
			pBuf[i] = Serial_ReadByte(ePort);
		}
	}
	return u16Count;
}

