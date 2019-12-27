
#include "./INC/Fake_me.h"
#include "../inc/ElevatorState.h"

Elevator_t fakeMe;

void FakeMe_Create(void ){
	fakeMe.ancesstor.state = (StateHandler)Elevator_ready;		/* Initiates Elevator in ready state */
	fakeMe.betweenTwoFloor = FALSE;					/* Initiates Elevator stopped in floor */
	fakeMe.currentFloor = PARKING_FLOOR;			/* Initiates Elevator in Parking Floor */
	fakeMe.directionMovement = STOP;					
	fakeMe.status = 0;
	fakeMe.targetFloor = PARKING_FLOOR;
}

State ExecuteState(Event_t *e){
	return fakeMe.ancesstor.state(&fakeMe, e);
}

Elevator_t GetMe(void){
	return fakeMe;
}

void UpdateBetweenTwoFloor(uint8_t btf){
	fakeMe.betweenTwoFloor = btf;
}

void UpdateStatus(uint8_t flag, flag_t act){
	if (act==RESET)
		fakeMe.status &=~ flag;
	else
		fakeMe.status |= flag;
}

void UpdateTarget(uint8_t target){
	fakeMe.targetFloor=target;
}

void UpdateCurrentFloor(uint8_t current){
	fakeMe.currentFloor = current;
}

void UpdateDirection(uint8_t dir){
	fakeMe.directionMovement = dir;
}

void MakeFakeCondition(uint8_t currentFloor, uint8_t targetFloor, uint8_t status, flag_t act, uint8_t btf, uint8_t dir){
	UpdateCurrentFloor(currentFloor);
	UpdateTarget(targetFloor);
	UpdateStatus(status, act);
	UpdateBetweenTwoFloor(btf);
	UpdateDirection(dir);
}