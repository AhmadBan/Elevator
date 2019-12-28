#include "CppUTest/TestHarness.h"
#include "INC/commonTest.h"

extern "C"
{
	/*
	* You can add your c-only include files here
	*/
#include "./INC/Fake_me.h"
}

void CheckState(void* statehandler, uint8_t current, uint8_t target, uint8_t status, uint8_t btf, uint8_t direction){
	FUNCTIONPOINTERS_EQUAL(statehandler, GetMe().ancesstor.state);
	BYTES_EQUAL(target, GetMe().targetFloor);
	BYTES_EQUAL(direction, GetMe().directionMovement);
	BYTES_EQUAL(status, GetMe().status);
	BYTES_EQUAL(btf, GetMe().betweenTwoFloor);
	BYTES_EQUAL(current, GetMe().currentFloor);
}