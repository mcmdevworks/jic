/*
 * Serial.h
 *
 *  Created on: 01-Jan-2019
 *      Author: mmanjrekar
 */

#ifndef HAL_LIBS_SERIAL_SERIAL_H_
#define HAL_LIBS_SERIAL_SERIAL_H_

#include "stm32f0xx.h"
#include "stm32f0xx_conf.h"

typedef enum {
	eSerial_Debug = 0,
	eSerial_GSM,
	eSerial_Modbus,
	eSerial_Max
} _eSerialPort;

typedef enum {
	eSerial_8bits,
	eSerial_7bits,
	eSerial_9bits,
	eSerial_Maxbits
} _eSerialDataBits;

typedef enum {
	eSerial_1Stopbit,
	eSerial_2Stopbit,
	eSerial_1_5Stopbit,
	eSerial_MaxStopbit
} _eSerialStopBits;

typedef enum {
	eSerial_NoParity,
	eSerial_EvenParity,
	eSerial_OddParity,
	eSerial_UnknownParity
} _eSerialParity;

typedef struct {
	uint8_t  *pu8Buff;
	uint16_t u16PutIndex;
	uint16_t u16GetIndex;
	uint16_t u16MaxSize;
} __attribute__((packed)) _sRingBuffer;

typedef struct {
	USART_TypeDef *pPort;
	_sRingBuffer sRxBuff;
	_sRingBuffer sTxBuff;
} __attribute__((packed)) _sSerialPort;

bool Serial_InitBuffer(_eSerialPort ePort, uint8_t *pRxBuf, uint16_t u16RxBufSize, uint8_t *pTxBuf, uint16_t u16TxBufSize);
void Serial_TxCallback(_eSerialPort ePort);
void Serial_RxCallback(_eSerialPort ePort, uint8_t u8Byte);
void Serial_Write(_eSerialPort ePort, uint8_t *pu8Buf, uint16_t u16Len);
void Serial_WriteByte(_eSerialPort ePort, uint8_t u8Byte);
void Serial_WriteString(_eSerialPort ePort, char *pszStr);
uint8_t Serial_TxGetByte(_eSerialPort ePort);
uint16_t Serial_TxGetCount(_eSerialPort ePort);
void Serial_RxPutByte(_eSerialPort ePort, uint8_t u8Byte);
uint16_t Serial_RxGetCount(_eSerialPort ePort);
uint8_t Serial_ReadByte(_eSerialPort ePort);
uint16_t Serial_Read(_eSerialPort ePort, uint8_t *pBuf, uint16_t u16Len);

#endif /* HAL_LIBS_SERIAL_SERIAL_H_ */
