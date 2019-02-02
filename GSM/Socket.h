/*
 * Socket.h
 *
 *  Created on: 01-Feb-2019
 *      Author: mmanjrekar
 */

#ifndef GSM_SOCKET_H_
#define GSM_SOCKET_H_

#include "stm32f0xx.h"
#include "stm32f0xx_conf.h"

#define MAX_SOCKETS      1

#define PROTOCOL_TCP     0
#define PROTOCOL_UDP     1


typedef struct {
	char *pszHostAddress;
	uint16_t u16HostPort;
	uint8_t u8Protocol;
	uint8_t *pu8SocketData;
	bool bOpenPending;
	bool bSendPending;
	bool bReadPending;
	bool bClosePending;
	bool bBusy;
	bool bIsOpen;
	uint32_t u32NextAttempt;
} __attribute__((packed)) _sSocket;


typedef enum {
	SocketAction_Open,
	SocketAction_Close,
	SocketAction_SendData,
	SocketAction_ReadData,
	SocketAction_None
} _eSocketAction;



_sSocket MQTTSocket;

#endif /* GSM_SOCKET_H_ */
