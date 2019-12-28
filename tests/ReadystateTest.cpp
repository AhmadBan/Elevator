#include "CppUTest/TestHarness.h"
#include "INC/commonTest.h"
extern "C"
{
	/*
	* You can add your c-only include files here
	*/
#include "./INC/Fake_me.h"
#include "./INC/Fake_event.h"

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