#include "../inc/ElevatorState.h"
/**
  * @brief  Initializes the Elevator starting state
  * @param  Elevator_t: pointer to a context structure
  *         that contains the extended state information and current state handler .
  * @retval state status Handled,Ignored or Transient 
  */
State Elevator_initial(Elevator_t *me, Event_t const *e)
{
    (void)e;
    me->currentFloor = 0; /* init elevator in parking floor */
    me->status |= DOOR_OPEN_PARKING;
    return TRAN(&Elevator_ready); /* transient to ready state */
}

/**
  * @brief  state handler for in ready state
  * @param  Elevator_t: pointer to a context structure
  *         that contains the extended state information and current state handler .
  * @retval state status Handled,Ignored or Transient 
  */
State Elevator_ready(Elevator_t *me, Event_t const *e)
{
    switch (e->sig)
    {
    case FLOORBUTTON_SIG:
    {
        FloorBtnEvt_t *event = (FloorBtnEvt_t *)e;

        if ((me->currentFloor) > (event->targetFloor))
        {
            return TRAN(&Elevator_moveDown);
        }
        if ((me->currentFloor) < (event->targetFloor))
        {
            return TRAN(&Elevator_moveUp);
        }
        return IGNORED();
    }

    case DOOROPEN_SIG:
    {
        DoorOpenEvt_t *event = (DoorOpenEvt_t *)e;

        me->status |= 1 << (event->floor); /* preserve status */

        if (me->currentFloor != 0)
        {
            return TRAN(&Elevator_emergency);
        }
        return IGNORED();
    }

    case OVERWEIGHT_SIG:
    {
        //add send warning by voice or display
        me->status |= OVER_WEGHT; /* preserve status */
        return TRAN(&Elevator_emergency);
    }
    case OVERTEMPERATURE_SIG:
    {
        //add send warning by voice or display
        me->status |= OVER_TEMPERATURE; /* preserve status */
        return TRAN(&Elevator_emergency);
    }
    }
    return IGNORED();
}

State Elevator_moveUp(Elevator_t *me, Event_t const *e);    /* StateHandler to handle moveup state */
State Elevator_moveDown(Elevator_t *me, Event_t const *e);  /* StateHandler to handle movedown state */
State Elevator_emergency(Elevator_t *me, Event_t const *e); /* StateHandler to handle emergency state */