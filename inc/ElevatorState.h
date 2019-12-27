#ifndef ELEVATOR_STATE_H
#define ELEVATOR_STATE_H

#include "./BaseState.h"
#include "./ElevatorEvent.h"

typedef enum {
	DOOR_CLOSE=0,
	DOOR_OPEN
}DoorState_t;



typedef enum{
	NOT_OVERTEMPERATURE=0,
	OVERTEMPERATURE
}Overtemperatur_t;

typedef enum{
	NOT_OVERWEIGHT = 0,
	OVERWEIGHT
}Overweight_t;


typedef enum{
	PARKING_FLOOR=0,
	FIRST_FLOOR,
	SECOND_FLOOR,
	THIRD_FLOOR
}Floor_t;

typedef enum{
	STOP=0,
	UP_DIRECTION = 1,
	DOWN_DIRECTION=2
	
}Direction_t;

#define TRUE  1
#define FALSE 0

#define DOOR_OPEN_PARKING 1
#define DOOR_OPEN_FIRST 2
#define DOOR_OPEN_SECOND 4
#define DOOR_OPEN_THIRD 8

#define OVER_WEIGHT 16
#define OVER_TEMPERATURE 32

#define UP_LIMIT_SWITCH 64
#define DOWN_LIMIT_SWITCH 128

typedef struct ElevatorState
{
    StateContext_t ancesstor;  /* derive from BaseState */
    uint8_t currentFloor;      /* indicates the elevator current floor */
    uint8_t targetFloor;       /* indicates the elevator target floor */
    uint8_t betweenTwoFloor;   /* shows if elevator between two level */
    uint8_t status;            /* indicates that  elevator emergency variable event in bit */
    uint8_t directionMovement; /* Indicates Movement direction , 1 UP,2 DOWN and 0 STOP */
} Elevator_t;

/* Constuctor to initialize context state object */
void Elevator_costructor(Elevator_t *me);

State Elevator_initial(Elevator_t *me, Event_t const *e);   /* StateHandler to handle initialize state */
State Elevator_ready(Elevator_t *me, Event_t const *e);     /* StateHandler to handle ready state */
State Elevator_move(Elevator_t *me, Event_t const *e);      /* StateHandler to handle moveup state */
State Elevator_emergency(Elevator_t *me, Event_t const *e); /* StateHandler to handle emergency state */
#endif
