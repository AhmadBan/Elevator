#include "cmsis_os.h" 
#include "Threads.h"
#include "..\inc\ElevatorEvent.h"
#include "..\inc\ElevatorState.h"

osThreadId dispatchThread;
Elevator_t me;
osThreadDef(State_Dispatch, osPriorityNormal, 1, 0);
osMailQId qid_EventQueue; // mail queue id
osMailQDef(EventQueue, MAILQUEUE_EVENTS, EVENT_TYPE);


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

void State_Dispatch(void const *num)
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




