#ifndef FAKE_EVENT_H
#define FAKE_EVENT_H
#include "../../inc/ElevatorState.h"
#include "../../inc/ElevatorEvent.h"


Event_t MakeanEvent(Signal_t Signal);

DoorEvt_t MakeaDoorEvent(Floor_t floor, DoorState_t status);
FloorBtnEvt_t MakeaBtnEvent(Floor_t floor);
OverTemperatureEvt_t MakeanOverTempEvent(Overtemperatur_t state);

OverWeightEvt_t MakeanOverWeightEvent(Overweight_t state);
#endif