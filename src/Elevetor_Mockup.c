#include "UART.h"
#include "stdio.h"
#include "cmsis_os.h"
#include "ElevatorEvent.h"
extern osMailQId qid_EventQueue;

void ElevatorDoorOpen(int floor){
	char msg[30];
	size_t size;
	size=sprintf(msg,"door %d opened",floor);

	print((uint8_t*)msg,size);
	/* send a door close event to event Queue */
	DoorEvt_t *event=0;	
	event=osMailAlloc(qid_EventQueue,osWaitForever);
	if(event){/* make sure that event is allocated memory */
		event->ancestor.sig=DOOR_SIG;
		event->floor=floor; /* floor which door is opened */
		event->status=1; /* door is opened */
		osMailPut(qid_EventQueue,event);
	}
}


void ElevatorDoorClosed(int floor){
	char msg[30];
	size_t size;
	
	size= sprintf(msg,"\ndoor %d is closed",floor);
	print((uint8_t*)msg,size);
	
	DoorEvt_t *event=0;
	event=osMailAlloc(qid_EventQueue,osWaitForever);
	if(event){
		event->ancestor.sig=DOOR_SIG;
		event->floor=floor;
		event->status=0;
		osMailPut(qid_EventQueue,event);
	}
}

void HallSensorOn(void){
	char msg[30];
	size_t size;
	size=sprintf(msg,"\nhall sensor detected");
	print((uint8_t*) msg, size);
}

void HallSensorOff(void){
	print((uint8_t*)"\nhall sensor is off",19);
}
