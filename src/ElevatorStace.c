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
    case PARKING_SIG:
    {
        if (me->currentFloor > 0)
        {
            return TRAN(&Elevator_moveDown);
        }
        return IGNORED();
    }
    case FIRST_SIG:
    {
        if (me->currentFloor > 1)
        {
            return TRAN(&Elevator_moveDown);
        }
        else if (me->currentFloor < 1)
        {
            return TRAN(&Elevator_moveUp);
        }
        return IGNORED();
    }
    case SECOND_SIG:
    {
        if (me->currentFloor > 2)
        {
            return TRAN(&Elevator_moveDown);
        }
        else if (me->currentFloor < 2)
        {
            return TRAN(&Elevator_moveUp);
        }
        return IGNORED();
    }
    case THIRD_SIG:
    {
        if (me->currentFloor < 3)
        {
            return TRAN(&Elevator_moveUp);
        }
        return IGNORED();
    }
    case PARKINGDOOROPEN_SIG:
    {

        me->status |= DOOR_OPEN_PARKING; /* preserve status */

        if (me->currentFloor != 0)
        {
            return TRAN(&Elevator_emergency);
        }
        return IGNORED();
    }
    case FIRSTDOOROPEN_SIG:
    {
        me->status |= DOOR_OPEN_FIRST; /* preserve status */
        if (me->currentFloor != 1)
        {
            return TRAN(&Elevator_emergency);
        }
        return IGNORED();
    }
    case SECONDDOOROPEN_SIG:
    {
        me->status |= DOOR_OPEN_SECOND; /* preserve status */
        if (me->currentFloor != 2)
        {
            return TRAN(&Elevator_emergency);
        }
        return IGNORED();
    }
    case THIRDDOOROPEN_SIG:
    {
        me->status |= DOOR_OPEN_THIRD; /* preserve status */
        if (me->currentFloor != 3)
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