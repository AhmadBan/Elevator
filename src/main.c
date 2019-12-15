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
osMailQDef(EventQueue, MAILQUEUE_EVENTS, EVENT_TYPE);

int main()
{

	osKernelInitialize(); // initialize CMSIS-RTOS

	//Init Peripherals
	EXTI_Config();
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

void EXTI_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/* Configure PA.00 pin as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Enable AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	/* Connect EXTI0 Line to PA.00 pin */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0 | GPIO_PinSource1 | GPIO_PinSource2 | GPIO_PinSource3);

	/* Configure EXTI0-3 line */
	/* BUTTON PARKING,1 2,3,4 */

	EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1 | EXTI_Line2 | EXTI_Line3;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	/** LIMIT UP, LIMIT DOWN, OVERWEIGHT, OVERTEMPERATURE , HALSENSOR 
	 *	DOOR= PARKING, 1, 2, 3
	 **/

	EXTI_InitStructure.EXTI_Line = 0xfff0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI0 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_Init(&NVIC_InitStructure);
}
