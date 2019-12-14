#include "BaseState.h"

typedef struct ElevatorState
{
    StateContext ancesstor; /* derive from BaseState */
    uint8_t currentFloor;   /* indicates the current level that elevator stopped */
} Elevator_t;

void Elevator_costructor(Elevator_t *me, uint8_t currentfloor); /* Constuctor to initialize context state object */

State Elevator_initial(Elevator_t *me, Event_t const *e);   /* StateHandler to handle initialize state */
State Elevator_ready(Elevator_t *me, Event_t const *e);     /* StateHandler to handle ready state */
State Elevator_moveUp(Elevator_t *me, Event_t const *e);    /* StateHandler to handle moveup state */
State Elevator_moveDown(Elevator_t *me, Event_t const *e);  /* StateHandler to handle movedown state */
State Elevator_emergency(Elevator_t *me, Event_t const *e); /* StateHandler to handle emergency state */
