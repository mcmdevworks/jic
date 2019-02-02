/*
 * main.c
 *
 *  Created on: 08-Dec-2018
 *      Author: mmanjrekar
 */

#include "stm32f0xx_conf.h"
#include "Serial.h"
#include "IOPin.h"


void Delay(uint32_t delay)
{
	uint32_t delay_timeout = u32MSTick + delay;
	while(u32MSTick < delay_timeout);
}

void DirectGSM(void)
{
	uint8_t byte;

	// Power up the modem
	Delay(5000);
	IO_SetOutputPin(GSMPWRKEY);
	Delay(5000);
	IO_ResetOutputPin(GSMPWRKEY);
	// Go into forever
	while(1)
	{
		if(Serial_RxGetCount(eSerial_Debug))
		{
			byte = Serial_ReadByte(eSerial_Debug);
			Serial_WriteByte(eSerial_GSM, byte);
		}
		if(Serial_RxGetCount(eSerial_GSM))
		{
			byte = Serial_ReadByte(eSerial_GSM);
			Serial_WriteByte(eSerial_Debug, byte);
		}

	}

}

int main(void)
{
	/* Adding a comment here to test git */
	SysTick_Config(SystemCoreClock / 1000);

	Board_Init();

	return 0;
}

