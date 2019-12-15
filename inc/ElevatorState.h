#ifndef ELEVATOR_STATE_H
#define ELEVATOR_STATE_H

#include "./BaseState.h"
#include "./ElevatorEvent.h"

#define DOOR_OPEN_PARKING 1
#define DOOR_OPEN_FIRST 2
#define DOOR_OPEN_SECOND 4
#define DOOR_OPEN_THIRD 8

#define OVER_WEGHT 16
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
State Elevator_costructor(Elevator_t *me,
                         uint8_t currentFloor /* indicates the elevator current floor */
);

State Elevator_initial(Elevator_t *me, Event_t const *e);   /* StateHandler to handle initialize state */
State Elevator_ready(Elevator_t *me, Event_t const *e);     /* StateHandler to handle ready state */
State Elevator_move(Elevator_t *me, Event_t const *e);      /* StateHandler to handle moveup state */
State Elevator_emergency(Elevator_t *me, Event_t const *e); /* StateHandler to handle emergency state */
#endif
