
#include "../../inc/ElevatorState.h"

typedef enum{
	RESET = 0,
	SET
}flag_t;

void FakeMe_Create(void);
Elevator_t GetMe(void);
void UpdateBetweenTwoFloor(uint8_t btf);
State ExecuteState(Event_t *e);
void UpdateStatus(uint8_t flag,flag_t act);
void UpdateTarget(uint8_t target);
void UpdateCurrentFloor(uint8_t current);
void UpdateDirection(uint8_t dir);
void MakeFakeCondition(uint8_t currentFloor, uint8_t targetFloor, uint8_t status, flag_t act, uint8_t btf, uint8_t dir);