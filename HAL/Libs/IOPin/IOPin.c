/*
 * IOPin.c
 *
 *  Created on: 02-Jan-2019
 *      Author: mmanjrekar
 */

#include "IOPin.h"

GPIO_TypeDef *pPort[] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOF};

const _sPinConfig sPinConfig[] = {
		{AIN0, GPIO_Mode_AN, 0, GPIO_PuPd_NOPULL, 0, 0, 0}, // PA0 AI0
		{AIN1, GPIO_Mode_AN, 0, GPIO_PuPd_NOPULL, 0, 0, 0}, // PA1 AI1
		{AIN2, GPIO_Mode_AN, 0, GPIO_PuPd_NOPULL, 0, 0, 0}, // PA2 AI2
		{AIN3, GPIO_Mode_AN, 0, GPIO_PuPd_NOPULL, 0, 0, 0}, // PA3 AI3
		{FLASH_CS, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, 0, 0, 1}, // PA4 FLASH_CS*
		{SCK1, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_PinSource5, GPIO_AF_0, 0}, // PA5
		{MISO1, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_PinSource6, GPIO_AF_0, 0}, // PA6
		{MOSI1, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_PinSource7, GPIO_AF_0, 0}, // PA7
		{U1TX, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_PinSource9, GPIO_AF_1, 0}, // PA9
		{U1RX, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_PinSource10, GPIO_AF_1, 0}, // PA10

		{U4TX, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_PinSource10, GPIO_AF_0, 0}, // PC10
		{U4RX, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_PinSource11, GPIO_AF_0, 0}, // PC11

		{GSMPWRKEY, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, 0, 0, 0} // PD2 GSM Powerkey

};

void IO_Init(void)
{
	GPIO_TypeDef *pGPIOPort;
	uint8_t u8Index;
	GPIO_InitTypeDef GPIOInit;
	uint16_t u16NoOfPins;

	// Enable Clocks
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);

	u16NoOfPins = (sizeof(sPinConfig) / sizeof(sPinConfig[0]));
	for(u8Index = 0; u8Index < u16NoOfPins; u8Index++)
	{
		// Configure Pin
		GPIOInit.GPIO_Mode = sPinConfig[u8Index].u8Mode;
		GPIOInit.GPIO_OType = sPinConfig[u8Index].u8OType;
		GPIOInit.GPIO_PuPd = sPinConfig[u8Index].u8PuPd;
		GPIOInit.GPIO_Speed = GPIO_Speed_Level_2;
		pGPIOPort = pPort[((sPinConfig[u8Index].u32Pin & PORTMASK) >> 16)];
		GPIOInit.GPIO_Pin = sPinConfig[u8Index].u32Pin & PINMASK;
		GPIO_Init(pGPIOPort, &GPIOInit);
		// Check if this is an alternate function pin
		if(sPinConfig[u8Index].u8Mode == GPIO_Mode_AF)
		{
			GPIO_PinAFConfig(pGPIOPort, sPinConfig[u8Index].u8PinSrc, sPinConfig[u8Index].u8PinAF);
		}
		// Set initial pin state
		if(sPinConfig[u8Index].u8Mode == GPIO_Mode_OUT)
		{
			if(sPinConfig[u8Index].u8InitialState == 0)
			{
				GPIO_ResetBits(pGPIOPort, (sPinConfig[u8Index].u32Pin & PINMASK));
			}
			else
			{
				GPIO_SetBits(pGPIOPort, (sPinConfig[u8Index].u32Pin & PINMASK));
			}
		}
	}
}

void IO_SetOutputPin(uint32_t u32Pin)
{
	GPIO_TypeDef *pGPIOPort = pPort[((u32Pin & PORTMASK) >> 16)];
	uint16_t u16GPIOPin = u32Pin & PINMASK;

	GPIO_SetBits(pGPIOPort, u16GPIOPin);
}

void IO_ResetOutputPin(uint32_t u32Pin)
{
	GPIO_TypeDef *pGPIOPort = pPort[((u32Pin & PORTMASK) >> 16)];
	uint16_t u16GPIOPin = u32Pin & PINMASK;

	GPIO_ResetBits(pGPIOPort, u16GPIOPin);
}

bool IO_GetInputPinState(uint32_t u32Pin)
{
	GPIO_TypeDef *pGPIOPort = pPort[((u32Pin & PORTMASK) >> 16)];
	uint16_t u16GPIOPin = u32Pin & PINMASK;

	if(GPIO_ReadInputDataBit(pGPIOPort, u16GPIOPin) == Bit_RESET)
	{
		return false;
	}
	else
	{
		return true;
	}
}





