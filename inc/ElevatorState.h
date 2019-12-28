#ifndef ELEVATOR_STATE_H
#define ELEVATOR_STATE_H

#include "./BaseState.h"
#include "./ElevatorEvent.h"
#include "./ElevatorInterface.h"


typedef enum{
	STOP = 0,
	UP_DIRECTION = 1,
	DOWN_DIRECTION = 2
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


State Elevator_initial(Elevator_t *me, Event_t const *e);   /* StateHandler to handle initialize state */
State Elevator_ready(Elevator_t *me, Event_t const *e);     /* StateHandler to handle ready state */
State Elevator_move(Elevator_t *me, Event_t const *e);      /* StateHandler to handle moveup state */
State Elevator_emergency(Elevator_t *me, Event_t const *e); /* StateHandler to handle emergency state */

#endif
