
#include "../inc/ElevatorState.h"


/**
  * @brief  State handler for in ready state
  * @param  me: Pointer to a context structure
  *         that contains the extended state information that need to be preserved .
  * @param  e: Pointer to current event catched,
  *         that contains the extended event information and current event Signal .
  * @retval State: Status Handled,Ignored or Transient 
  */
State Elevator_ready(Elevator_t *me, Event_t const *e)
{

    switch (e->sig)
    {
    case ENTRY_SIG:
        /* implement code to stop motor */
        me->betweenTwoFloor = 0;                                               /* no longer between two floor */
        if ((me->status & (1 << me->currentFloor)) != (1 << me->currentFloor)) /* check if automatic door is closed to open it */
        {
            /*implement code to open automatic door for stopped floor */
        }
        return HANDLED();
    case FLOORBUTTON_SIG:
    {
        FloorBtnEvt_t *event = (FloorBtnEvt_t *)e;

        if ((me->currentFloor) != (event->targetFloor))
        {
            me->targetFloor = event->targetFloor;
			if (me->status == 0){
				if (me->targetFloor > me->currentFloor)
					me->directionMovement = UP_DIRECTION;
				else
					me->directionMovement = DOWN_DIRECTION;
				return TRAN(&Elevator_move);
			}
			/* implement code to close door */

            return HANDLED();
        }

        return IGNORED();
    }

    case DOOR_SIG:
    {
        DoorEvt_t *event = (DoorEvt_t *)e;
        if (event->status == 1) /* a door is opened */
        {
            me->status |= 1 << (event->floor);    /* preserve status */
            if (me->currentFloor != event->floor) /* a door is open other than the door elevator stopped */
            {
                return TRAN(&Elevator_emergency);
            }
        }
        else /* a door is closed */
        {
            me->status &= ~(1 << event->floor); /* preserve status  */
            if (me->status == 0)                /* if all door are closed */
            {
                if ((me->currentFloor) > (me->targetFloor)) /* if target floor is lower than the currentFloor */
                {
                    me->directionMovement = DOWN_DIRECTION;
                    return TRAN(&Elevator_move);
                }
                if ((me->currentFloor) < (me->targetFloor)) /* if target floor is Upper than the currentFloor */
                {
                    me->directionMovement = UP_DIRECTION;
                    return TRAN(&Elevator_move);
                }
            }
        }

        return IGNORED();
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
    }
    return IGNORED();
}
