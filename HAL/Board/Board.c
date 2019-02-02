/*
 * Board.c
 *
 *  Created on: 01-Feb-2019
 *      Author: mmanjrekar
 */

#include "stm32f0xx.h"
#include "stm32f0xx_conf.h"
#include "IOPin.h"
#include "Serial.h"

#define DEBUG_USART_TX_BUFF_MAX    256
#define DEBUG_USART_RX_BUFF_MAX    256
#define GSM_USART_TX_BUFF_MAX      4096
#define GSM_USART_RX_BUFF_MAX      4096

/* Global Serial Port Buffers */
uint8_t u8DebugTxBuffer[DEBUG_USART_TX_BUFF_MAX];
uint8_t u8DebugRxBuffer[DEBUG_USART_RX_BUFF_MAX];

uint8_t u8GSMTxBuffer[GSM_USART_TX_BUFF_MAX];
uint8_t u8GSMRxBuffer[GSM_USART_RX_BUFF_MAX];


void Board_Init(void)
{
	IO_Init();
	Serial_Init();
	Serial_InitBuffer(eSerial_Debug, u8DebugRxBuffer, DEBUG_USART_RX_BUFF_MAX, u8DebugTxBuffer, DEBUG_USART_TX_BUFF_MAX);
	Serial_InitBuffer(eSerial_GSM, u8GSMRxBuffer, GSM_USART_RX_BUFF_MAX, u8GSMTxBuffer, GSM_USART_TX_BUFF_MAX);
	//Serial_InitBuffer(eSerial_Debug, u8DebugRxBuffer, DEBUG_USART_RX_BUFF_MAX, u8DebugTxBuffer, DEBUG_USART_TX_BUFF_MAX);
}
