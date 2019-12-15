#define osObjectsPublic // define objects in main module
#include "main.h"
#include "..\inc\Board_LED.h"
#include "..\inc\ElevatorEvent.h"
#include "..\inc\ElevatorState.h"
#include "..\inc\osObjects.h"
#include "stm32f10x.h"

static Elevator_t me;
osThreadId dispatchThread;
osThreadDef(state_dispatch, osPriorityNormal, 1, 0);
osMailQId qid_EventQueue; // mail queue id
osMailQDef(EventQueue, MAILQUEUE_EVENTS, Event_t);

int main()
{

	osKernelInitialize(); // initialize CMSIS-RTOS

	// initialize peripherals here

	// create 'thread' functions that start executing,
	// example: tid_name = osThreadCreate (osThread(name), NULL);

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
