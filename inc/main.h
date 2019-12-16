
#ifndef MAIN_H
#define MAIN_H
#include "stddef.h"
#include "stdint.h"
#include "stm32f10x.h"


#include "..\inc\Board_LED.h"
#include "..\inc\ElevatorEvent.h"
#include "..\inc\ElevatorState.h"

#define USARTz_RxPin GPIO_Pin_6
#define USARTz_TxPin GPIO_Pin_5
#define USARTz_GPIO GPIOD
#define USARTz_CLK RCC_APB1Periph_USART2
#define USARTz_GPIO_CLK RCC_APB2Periph_GPIOD
#define USARTz_Tx_DMA_Channel DMA1_Channel7
#define USARTz_Tx_DMA_FLAG DMA1_FLAG_TC7
#define USARTz_Rx_DMA_Channel DMA1_Channel6
#define USARTz_Rx_DMA_FLAG DMA1_FLAG_TC6
#define USARTz USART2
#define USARTz_DR_Base 0x40004404




void Thread_interrupt(void const *argument);
void state_dispatch(void const *num);
int Init_MailQueue(void);
void EXTI_Configuration(void);
#endif
