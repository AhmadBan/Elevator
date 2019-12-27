#include "CppUTest/TestHarness.h"

extern "C"
{
	/*
	* You can add your c-only include files here
	*/
#include "./INC/Fake_me.h"
}

TEST_GROUP(ReadyState)
{
	void setup()
	{
		FakeMe_Create();
	}  

	void teardown()
	{

	}
};

Event_t MakeanEvent(Signal_t Signal){
	Event_t e;
	e.sig = Signal ;
	return e;
}

DoorEvt MakeaDoorEvent( Floor_t floor, DoorState_t status){
	DoorEvt e;
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
	OverTemperatureEvt e;
	e.ancestor.sig = OVERTEMPERATURE_SIG;
	e.status = state;
	return e;

}

OverWeightEvt_t MakeanOverWeightEvent(Overweight_t state){
	OverWeightEvt e;
	e.ancestor.sig = OVERWEIGHT_SIG;
	e.status = state;
	return e;

}

 

void CheckState(void* statehandler, uint8_t current, uint8_t target, uint8_t status, uint8_t btf, uint8_t direction){
	FUNCTIONPOINTERS_EQUAL(statehandler, GetMe().ancesstor.state);
	BYTES_EQUAL(target, GetMe().targetFloor);
	BYTES_EQUAL(direction, GetMe().directionMovement);
	BYTES_EQUAL(status, GetMe().status);
	BYTES_EQUAL(btf, GetMe().betweenTwoFloor);
	BYTES_EQUAL(current, GetMe().currentFloor);
}

TEST(ReadyState, EntrySignalBetweentTwoFloor)
{
	Event_t e = MakeanEvent(ENTRY_SIG);
	UpdateBetweenTwoFloor(TRUE);
	
	ExecuteState(&e);
	CheckState(Elevator_ready, PARKING_FLOOR, PARKING_FLOOR, 0, FALSE, STOP);
	
}

TEST(ReadyState, PushParkingButtonWhenInParkingDoorClose)
{
	FloorBtnEvt_t e=MakeaBtnEvent(PARKING_FLOOR);
	MakeFakeCondition(PARKING_FLOOR, PARKING_FLOOR, DOOR_OPEN_PARKING,RESET, FALSE, STOP);
	ExecuteState(&e.ancestor);
	CheckState(Elevator_ready, PARKING_FLOOR, PARKING_FLOOR, 0, FALSE, STOP);

}

TEST(ReadyState, PushFirstFloorButtonWhenInParkingDoorClosed)
{
	FloorBtnEvt_t e = MakeaBtnEvent(FIRST_FLOOR);
	MakeFakeCondition(PARKING_FLOOR, PARKING_FLOOR, DOOR_OPEN_PARKING,RESET, FALSE, STOP);

	UpdateCurrentFloor(PARKING_FLOOR);
	ExecuteState(&e.ancestor);
	CheckState(Elevator_move, PARKING_FLOOR, FIRST_FLOOR, 0, FALSE, UP_DIRECTION);

}

TEST(ReadyState, PushFirstFloorButtonWhenInParkingDoorOpen)
{

	FloorBtnEvt_t e = MakeaBtnEvent(FIRST_FLOOR);
	MakeFakeCondition(PARKING_FLOOR, PARKING_FLOOR, DOOR_OPEN_PARKING,SET ,FALSE, STOP);

	ExecuteState(&e.ancestor);
	CheckState(Elevator_ready, PARKING_FLOOR, FIRST_FLOOR, DOOR_OPEN_PARKING, FALSE, STOP);
	
}

TEST(ReadyState, DoorcloseGoingToFirstFloorWhenInParking)
{
	DoorEvt_t e = MakeaDoorEvent(PARKING_FLOOR, DOOR_CLOSE);
	MakeFakeCondition(PARKING_FLOOR, FIRST_FLOOR, DOOR_OPEN_PARKING, SET ,FALSE, STOP);

	ExecuteState(&e.ancestor);
	CheckState(Elevator_move, PARKING_FLOOR, FIRST_FLOOR, 0, FALSE, UP_DIRECTION);
	
}


TEST(ReadyState, PushThirdButtonWhenInParkingDoorClosed)
{
	FloorBtnEvt_t e = MakeaBtnEvent(THIRD_FLOOR);
	MakeFakeCondition(PARKING_FLOOR, PARKING_FLOOR, DOOR_OPEN_PARKING, RESET,FALSE, STOP);

	ExecuteState(&e.ancestor);
	CheckState(Elevator_move, PARKING_FLOOR, THIRD_FLOOR, 0, FALSE, UP_DIRECTION);

}

TEST(ReadyState, PushThirdFloorButtonWhenInParkingDoorOpen)
{
	FloorBtnEvt_t e = MakeaBtnEvent(THIRD_FLOOR);
	MakeFakeCondition(PARKING_FLOOR, PARKING_FLOOR, DOOR_OPEN_PARKING,SET ,FALSE, STOP);
	ExecuteState(&e.ancestor);
	CheckState(Elevator_ready, PARKING_FLOOR, THIRD_FLOOR, DOOR_OPEN_PARKING, FALSE, STOP);

}

TEST(ReadyState, DoorcloseGoingToFirstFloorWhenInThird)
{
	DoorEvt_t e = MakeaDoorEvent(THIRD_FLOOR, DOOR_CLOSE);
	MakeFakeCondition(THIRD_FLOOR, FIRST_FLOOR, DOOR_OPEN_THIRD, SET,FALSE, STOP);
	ExecuteState(&e.ancestor);
	CheckState(Elevator_move,THIRD_FLOOR , FIRST_FLOOR, 0, FALSE, DOWN_DIRECTION);
}

TEST(ReadyState, PushFirstFloorBtnWhenInThirdDoorOpen)
{
	FloorBtnEvt_t e = MakeaBtnEvent(FIRST_FLOOR);
	MakeFakeCondition(THIRD_FLOOR, THIRD_FLOOR, DOOR_OPEN_THIRD,SET ,FALSE, STOP);
	ExecuteState(&e.ancestor);
	CheckState(Elevator_ready, THIRD_FLOOR, FIRST_FLOOR, DOOR_OPEN_THIRD, FALSE, STOP);
}

TEST(ReadyState, OverWeightActivateWhenInSecondFloorDoorOpen)
{
	OverWeightEvt_t e = MakeanOverWeightEvent( OVERWEIGHT);

	MakeFakeCondition(SECOND_FLOOR, SECOND_FLOOR, DOOR_OPEN_SECOND, SET ,FALSE, STOP);

	ExecuteState(&e.ancestor);
	CheckState(Elevator_emergency, SECOND_FLOOR, SECOND_FLOOR, DOOR_OPEN_SECOND|OVER_WEIGHT, FALSE, STOP);
	
}

TEST(ReadyState, OverTempActivateWhenInFirstFloorDoorOpen)
{
	OverTemperatureEvt_t e = MakeanOverTempEvent(OVERTEMPERATURE);

	MakeFakeCondition(FIRST_FLOOR, FIRST_FLOOR, DOOR_OPEN_FIRST, SET,FALSE, STOP);

	ExecuteState(&e.ancestor);
	CheckState(Elevator_emergency, FIRST_FLOOR, FIRST_FLOOR, DOOR_OPEN_FIRST | OVER_TEMPERATURE, FALSE, STOP);



}

TEST(ReadyState, ParkingDoorOpenWhenInFirstFloor)
{
	DoorEvt_t e = MakeaDoorEvent(PARKING_FLOOR,DOOR_OPEN);

	MakeFakeCondition(FIRST_FLOOR, FIRST_FLOOR, DOOR_OPEN_FIRST, SET,FALSE, STOP);

	ExecuteState(&e.ancestor);
	CheckState(Elevator_emergency, FIRST_FLOOR, FIRST_FLOOR, DOOR_OPEN_FIRST | DOOR_OPEN_PARKING, FALSE, STOP);

}

TEST(ReadyState, ThirdDoorOpenWhenInFirstFloor)
{
	DoorEvt_t e = MakeaDoorEvent(THIRD_FLOOR, DOOR_OPEN);
	MakeFakeCondition(FIRST_FLOOR, FIRST_FLOOR, DOOR_OPEN_FIRST,SET ,FALSE, STOP);
	ExecuteState(&e.ancestor);
	CheckState(Elevator_emergency, FIRST_FLOOR, FIRST_FLOOR, DOOR_OPEN_FIRST | DOOR_OPEN_THIRD, FALSE, STOP);

	
}


TEST(ReadyState, SecondDoorOpenWhenInFirstFloor)
{
	DoorEvt_t e = MakeaDoorEvent(SECOND_FLOOR, DOOR_OPEN);
	MakeFakeCondition(FIRST_FLOOR, FIRST_FLOOR, DOOR_OPEN_FIRST,SET,FALSE,STOP);
	ExecuteState(&e.ancestor);
	CheckState(Elevator_emergency, FIRST_FLOOR, FIRST_FLOOR, DOOR_OPEN_FIRST | DOOR_OPEN_SECOND, FALSE, STOP);

	
}