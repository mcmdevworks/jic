/*
 * IOPin.h
 *
 *  Created on: 02-Jan-2019
 *      Author: mmanjrekar
 */

#ifndef HAL_LIBS_IOPIN_IOPIN_H_
#define HAL_LIBS_IOPIN_IOPIN_H_

#include "stm32f0xx.h"
#include "stm32f0xx_conf.h"

#define PORTA         0x00000000
#define PORTB         0x00010000
#define PORTC         0x00020000
#define PORTD         0x00030000
#define PORTF         0x00040000

#define AIN0          (PORTA | GPIO_Pin_0)
#define AIN1          (PORTA | GPIO_Pin_1)
#define AIN2          (PORTA | GPIO_Pin_2)
#define AIN3          (PORTA | GPIO_Pin_3)
#define FLASH_CS      (PORTA | GPIO_Pin_4)
#define SCK1          (PORTA | GPIO_Pin_5)
#define MISO1         (PORTA | GPIO_Pin_6)
#define MOSI1         (PORTA | GPIO_Pin_7)
#define PA8           (PORTA | GPIO_Pin_8)
#define U1TX          (PORTA | GPIO_Pin_9)
#define U1RX          (PORTA | GPIO_Pin_10)
#define PA11          (PORTA | GPIO_Pin_11)
#define PA12          (PORTA | GPIO_Pin_12)
#define SWDIO         (PORTA | GPIO_Pin_13)
#define SWCLK         (PORTA | GPIO_Pin_14)
#define PA15          (PORTA | GPIO_Pin_15)

#define MBTXEN        (PORTB | GPIO_Pin_0)
#define RS485232SEL   (PORTB | GPIO_Pin_1)
#define SDI12         (PORTB | GPIO_Pin_2)
#define LED3          (PORTB | GPIO_Pin_3)
#define LED2          (PORTB | GPIO_Pin_4)
#define LED1          (PORTB | GPIO_Pin_5)
#define PB6           (PORTB | GPIO_Pin_6)
#define PB7           (PORTB | GPIO_Pin_7)
#define PB8           (PORTB | GPIO_Pin_8)
#define PB9           (PORTB | GPIO_Pin_9)
#define RS485232MUX   (PORTB | GPIO_Pin_10)
#define PB11          (PORTB | GPIO_Pin_11)
#define PB12          (PORTB | GPIO_Pin_12)
#define PB13          (PORTB | GPIO_Pin_13)
#define PB14          (PORTB | GPIO_Pin_14)
#define PB15          (PORTB | GPIO_Pin_15)

#define PC0           (PORTC | GPIO_Pin_0)
#define PC1           (PORTC | GPIO_Pin_1)
#define PC2           (PORTC | GPIO_Pin_2)
#define PC3           (PORTC | GPIO_Pin_3)
#define U3TX          (PORTC | GPIO_Pin_4)
#define U3RX          (PORTC | GPIO_Pin_5)
#define PULSECTR      (PORTC | GPIO_Pin_6)
#define PC7           (PORTC | GPIO_Pin_7)
#define PC8           (PORTC | GPIO_Pin_8)
#define PC9           (PORTC | GPIO_Pin_9)
#define U4TX          (PORTC | GPIO_Pin_10)
#define U4RX          (PORTC | GPIO_Pin_11)
#define PC12          (PORTC | GPIO_Pin_12)
#define PC13          (PORTC | GPIO_Pin_13)
#define PC14          (PORTC | GPIO_Pin_14)
#define PC15          (PORTC | GPIO_Pin_15)

#define GSMPWRKEY     (PORTD | GPIO_Pin_2)

#define PORTMASK      0xFFFF0000
#define PINMASK       0x0000FFFF

//#define PINMODE_INPUT    GPIO_Mode_IN
//#define PINMODE_OUTPUT   0
//#define PINMODE_ANALOG   0
//#define PINMODE_AF       0
//
//#define PINPULL_UP       0
//#define PINPULL_DOWN     1
//#define PINPULL_NONE     2
//
//#define PINPULL_UP       0
//#define PINPULL_DOWN     1
//#define PINPULL_FLOATING 2

typedef struct {
	uint32_t           u32Pin;
	GPIOMode_TypeDef   u8Mode;
	GPIOOType_TypeDef  u8OType;
	GPIOPuPd_TypeDef   u8PuPd;
	uint8_t            u8PinSrc;
	uint8_t            u8PinAF;
	uint8_t            u8InitialState;
} __attribute__((packed)) _sPinConfig;


void IO_Init(void);
void IO_SetOutputPin(uint32_t u32Pin);
void IO_ResetOutputPin(uint32_t u32Pin);
bool IO_GetInputPinState(uint32_t u32Pin);

#endif /* HAL_LIBS_IOPIN_IOPIN_H_ */
