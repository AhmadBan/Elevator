#include "./BaseState.h"

#define DOOR_OPEN_PARKING 1
#define DOOR_OPEN_FIRST 2
#define DOOR_OPEN_SECOND 4
#define DOOR_OPEN_THIRD 8

#define OVER_WEGHT 16
#define OVER_TEMPERATURE 32

typedef struct ElevatorState
{
    StateContext ancesstor; /* derive from BaseState */
    uint8_t currentFloor;   /* indicates the current level that elevator stopped */
    uint8_t status;         /*indicates that  elevator emergency variable event in bit */

} Elevator_t;

void Elevator_costructor(Elevator_t *me, uint8_t currentfloor, uint8_t status); /* Constuctor to initialize context state object */

State Elevator_initial(Elevator_t *me, Event_t const *e);   /* StateHandler to handle initialize state */
State Elevator_ready(Elevator_t *me, Event_t const *e);     /* StateHandler to handle ready state */
State Elevator_moveUp(Elevator_t *me, Event_t const *e);    /* StateHandler to handle moveup state */
State Elevator_moveDown(Elevator_t *me, Event_t const *e);  /* StateHandler to handle movedown state */
State Elevator_emergency(Elevator_t *me, Event_t const *e); /* StateHandler to handle emergency state */
