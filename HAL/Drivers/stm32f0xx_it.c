/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "stm32f0xx.h"
#include "stm32f0xx_conf.h"
#include "Serial.h"

/** @addtogroup Template_Project
  * @{
  */

volatile uint32_t u32MSTick;
volatile uint32_t u32SecTick;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	u32MSTick++;
	if((u32MSTick % 1000) == 0)
	{
		u32SecTick++;
	}

}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

void USART1_IRQHandler(void)
{
	 if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	 {
		 Serial_RxCallback(eSerial_Debug, (uint8_t)USART_ReceiveData(USART1));
	 }

	 if (USART_GetITStatus(USART1, USART_IT_TXE) == SET)
	 {
		 Serial_TxCallback(eSerial_Debug);
	 }
}

void USART3_8_IRQHandler(void)
{
	 if (USART_GetITStatus(USART4, USART_IT_RXNE) == SET)
	 {
		 Serial_RxCallback(eSerial_GSM, (uint8_t)USART_ReceiveData(USART4));
	 }
	 else if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
	 {
		 Serial_RxCallback(eSerial_Modbus, (uint8_t)USART_ReceiveData(USART3));
	 }

	 if (USART_GetITStatus(USART4, USART_IT_TXE) == SET)
	 {
		 Serial_TxCallback(eSerial_GSM);
	 }
	 else if (USART_GetITStatus(USART3, USART_IT_TXE) == SET)
	 {
		 Serial_TxCallback(eSerial_Modbus);
	 }
}

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
