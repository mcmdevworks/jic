/*
 * Socket.c
 *
 *  Created on: 01-Feb-2019
 *      Author: mmanjrekar
 */

#include "Socket.h"

/*
 * Global socket definitions
 *
 * IMPORTANT: Please check the maximum number of sockets supported by the GSM modem.
 *
 * */

_sSocket sSocket[MAX_SOCKETS];
static uint8_t u8ActiveSockets;
static _sSocket *psModemMutex = NULL;

bool Socket_Init(_sSocket *pSocket, char *pszHostIP, uint16_t u16Port, uint8_t u8ProtocolType)
{
	uint8_t i = 0;
	_sSocket *p = 0;
	bool bRet = false;

	if((pszHostIP == NULL) || (u16Port == 0) || (pSocket == NULL))
	{
		bRet = false;
	}
	else
	{
		for(i=0; i<MAX_SOCKETS; i++)
		{
			if(u8ActiveSockets < MAX_SOCKETS)
			{
				p = &sSocket[i];
				if((p->pszHostAddress == NULL) && (p->u16HostPort == 0))
				{
					// found a free socket
					pSocket = p;
					pSocket->pszHostAddress = pszHostIP;
					pSocket->u16HostPort = u16Port;
					pSocket->u8Protocol = u8ProtocolType;
					pSocket->bClosePending = false;
					pSocket->bOpenPending = false;
					pSocket->bReadPending = false;
					pSocket->bSendPending = false;
					pSocket->bBusy = false;
					pSocket->bIsOpen = false;
					pSocket->u32NextAttempt = 0;
					bRet = true;
					u8ActiveSockets++;

				}
			}
			else
			{
				bRet = false;
			}
		}
	}

	return bRet;
}


bool Socket_GetModemMutex(_sSocket *p)
{
	bool bRet = false;

	if((psModemMutex == NULL) && (p != NULL))
	{
		psModemMutex = p;
		bRet = true;
	}

	return bRet;
}


bool Socket_ReleaseModemMutex(_sSocket *p)
{
	bool bRet = false;

	if((psModemMutex != NULL) && (p != NULL))
	{
		if(psModemMutex == p)
		{
			psModemMutex = NULL;
			bRet = true;
		}
	}

	return bRet;
}


bool Socket_IsModemMutexTaken(void)
{
	if(psModemMutex == NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}


_eSocketAction Socket_ActionRequired(void)
{
	uint8_t i;
	_eSocketAction eRet = SocketAction_None;

	if(Socket_IsModemMutexTaken() == false)
	{
		for(i=0; i<u8ActiveSockets; i++)
		{
			if((sSocket[i].bIsOpen == false) && (sSocket[i].bOpenPending == true))
			{
				// Open a socket

			}
			else if((sSocket[i].bIsOpen == true) && (sSocket[i].bSendPending == true))
			{
				// Send Socket Data

			}
			else if((sSocket[i].bIsOpen == true) && (sSocket[i].bReadPending == true))
			{
				// Read Socket Data

			}
			else if((sSocket[i].bIsOpen == true) && (sSocket[i].bClosePending == true))
			{
				// Close Socket

			}
		}

	}
}


