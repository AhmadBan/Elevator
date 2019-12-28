#include "../inc/ElevatorState.h"

/**
  * @brief  State handler in moveup state
  * @param  me: Pointer to a context structure
  *         that contains the extended state information that need to be preserved .
  * @param  e: Pointer to current event catched,
  *         that contains the extended event information and current event Signal .
  * @retval State: Status Handled,Ignored or Transient 
  */
State Elevator_move(Elevator_t *me, Event_t const *e)
{
    switch (e->sig)
    {

    case ENTRY_SIG:
    {
        me->betweenTwoFloor = 1;
        if (me->directionMovement == DOWN_DIRECTION)
        {
            /* implement here code for motor start to elevate up */
        }
        else
        {
            /* implement here code for motor start to elevate down */
        }
        return HANDLED();
    }
    case LIMITSWITCH_SIG:
    {
        LimitSWEvt_t *event = (LimitSWEvt_t *)e;
        if ((event->status & 1) == 1)
        {
            me->status |= UP_LIMIT_SWITCH;
        }
        if ((event->status & 2) == 2)
            me->status |= DOWN_LIMIT_SWITCH;

        return TRAN(&Elevator_emergency);
    }
    case DOOR_SIG:
    {

        DoorEvt_t *event = (DoorEvt_t *)e;
        /* *
        * in this state since all doors are already closed a door signal means 
        * a door is opened while moving up  but an external guard is added to 
        * make sure if door is opened
        * */

        if (event->status == 1)
        {
            /* in this state since all doors are already closed a door signal means a door is opened while moving up */
            /* in doubt to stop motor immediately before doing anything else it might save a life so stop motor procedure might be implemented here */

            me->status |= 1 << (event->floor); /* preserve status */
            return TRAN(&Elevator_emergency);
        }
    }

    case OVERWEIGHT_SIG:
    {
        OverWeightEvt_t *event = (OverWeightEvt_t *)e;
        /* *
        * in this state since assumed no overweight existed so overweight signal means 
        * there is now an overweight but an external guard is added to make sure if 
        * overweight exists.
        * */
        if (event->status == 1)
        {
            //add send warning by voice or display
            me->status |= OVER_WEIGHT; /* preserve status */
            return TRAN(&Elevator_emergency);
        }
    }
    case OVERTEMPERATURE_SIG:
    {
        OverTemperatureEvt_t *event = (OverTemperatureEvt_t *)e;
        /* *
        * in this state since assumed no overtemperature existed so overtemperature signal means 
        * there is now an overwtemperature but an external guard is added to make sure if 
        * overtemperature exists.
        * */
        if (event->status == 1)
        {
            //add send warning by voice or display
            me->status |= OVER_TEMPERATURE; /* preserve status */
            return TRAN(&Elevator_emergency);
        }
    }
    case HALSENSOR_SIG:
    {
        if (me->directionMovement == 1)
        {
            if (++me->currentFloor == me->targetFloor)
            {
                return TRAN(&Elevator_ready);
            }
        }
        else
        {
            if (--me->currentFloor == me->targetFloor)
            {
                return TRAN(&Elevator_ready);
            }
        }
        return HANDLED();
    }
    }
    return IGNORED();
}

