
#include "./INC/Fake_event.h"
#include "../inc/ElevatorEvent.h"

Event_t MakeanEvent(Signal_t Signal){
	Event_t e;
	e.sig = Signal;
	return e;
}

DoorEvt_t MakeaDoorEvent(Floor_t floor, DoorState_t status){
	DoorEvt_t e;
	e.ancestor.sig = DOOR_SIG;
	e.floor = floor;
	e.status = status;
	return e;
}

FloorBtnEvt_t MakeaBtnEvent(Floor_t floor){
	FloorBtnEvt_t e;
	e.ancestor.sig = FLOORBUTTON_SIG;
	e.targetFloor = floor;
	return e;

}

OverTemperatureEvt_t MakeanOverTempEvent(Overtemperatur_t state){
	OverTemperatureEvt_t e;
	e.ancestor.sig = OVERTEMPERATURE_SIG;
	e.status = state;
	return e;

}

OverWeightEvt_t MakeanOverWeightEvent(Overweight_t state){
	OverWeightEvt_t e;
	e.ancestor.sig = OVERWEIGHT_SIG;
	e.status = state;
	return e;

}