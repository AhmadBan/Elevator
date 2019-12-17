#define osObjectsPublic // define objects in main module
#include "main.h"
#include "GPIO.h"
#include "DMA.h"
#include "RCC.h"
#include "EXTI.h"
#include "UART.h"
#include "..\inc\osObjects.h"

static Elevator_t me;
osThreadId dispatchThread;
osThreadDef(state_dispatch, osPriorityNormal, 1, 0);
osMailQId qid_EventQueue; // mail queue id
osMailQDef(EventQueue, MAILQUEUE_EVENTS, EVENT_TYPE);

uint8_t testforzero[10]={1,2,3,4,5,6,7,8,9,10};

int main()
{

	osKernelInitialize(); // initialize CMSIS-RTOS

	/* Init System Clock */
	Clock_Configuration();
	/* System Clocks Configuration */
	RCC_Configuration();
	/* Configure the GPIO ports */
	GPIO_Configuration();
	/* Configure the EXTI */
	EXTI_Configuration();
	/* Configure the UART ports */
	UART_Configuration();
	while (DMA_GetFlagStatus(USARTz_Tx_DMA_FLAG) == RESET)
	{
	}
	print((uint8_t *)"uart config", 12);
	EXTI_Configuration();

	//Construct state context and events
	Elevator_costructor(&me, 0);

	// Init and create event queue
	Init_MailQueue();

	// create 'dispatch'thread and interrupt(event) thread functions that start executing,
	dispatchThread = osThreadCreate(osThread(state_dispatch), (void *)0);

	osKernelStart();
}

void state_dispatch(void const *num)
{
	Event_t *pMail = 0;
	osEvent evt;
	Base_init((StateContext_t *)&me, (Event_t const *)0);

	while (1)
	{
		evt = osMailGet(qid_EventQueue, osWaitForever); // wait for mail
		if (evt.status == osEventMail)
		{
			pMail = evt.value.p;

			if (pMail)
			{
				Base_dispatch((StateContext_t *)&me, (Event_t const *)pMail); // process data

				osMailFree(qid_EventQueue, pMail); // free memory allocated for mail
			}
		}
	}
}

int Init_MailQueue(void)
{
	qid_EventQueue = osMailCreate(osMailQ(EventQueue), NULL); // create mail queue
	if (!qid_EventQueue)
	{
		while (1)
		{

		} // Mail Queue object not created, handle failure
	}
	return (0);
}
