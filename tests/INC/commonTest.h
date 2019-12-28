#include "CppUTest/TestHarness.h"
extern "C"
{
	/*
	* You can add your c-only include files here
	*/
#include "./INC/Fake_me.h"
}

void CheckState(void* statehandler, uint8_t current, uint8_t target, uint8_t status, uint8_t btf, uint8_t direction);