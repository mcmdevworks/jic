/*
 * GSM.h
 *
 *  Created on: 01-Feb-2019
 *      Author: mmanjrekar
 */

#ifndef GSM_GSM_H_
#define GSM_GSM_H_

#include "stm32f0xx.h"
#include "stm32f0xx_conf.h"



typedef enum {
	GSM_PowerOnModem,
	GSM_SetupModem,
	GSM_NetReg,
	GSM_GPRSReg,
	GSM_Checks,
	GSM_OpenSocket,
	GSM_SendSocketData,
	GSM_ReadSocketData,
	GSM_CloseSocketData,

} _eGSMState;


#endif /* GSM_GSM_H_ */
