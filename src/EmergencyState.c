#include "../inc/ElevatorState.h"

/**
  * @brief  State handler in emergency state
  * @param  me: Pointer to a context structure
  *         that contains the extended state information that need to be preserved .
  * @param  e: Pointer to current event catched,
  *         that contains the extended event information and current event Signal .
  * @retval State: Status Handled,Ignored or Transient 
  */
State Elevator_emergency(Elevator_t *me, Event_t const *e)
{
    switch (e->sig)
    {
    case ENTRY_SIG:
    {
        /* implement here code for motor to stop */

        return HANDLED();
    }

    case DOOR_SIG:
    {
        DoorEvt_t *event = (DoorEvt_t *)e;
        if (event->status == 1) /* a door is opened so stay in current position */
        {
            me->status |= 1 << (event->floor); /* preserve status */
            return HANDLED();
        }
        /* a door is closed so save status but not returned to check further at the end of switch */
        me->status &= ~(1 << (event->floor)); /* preserve status */
    }

    case OVERWEIGHT_SIG:
    {
        OverWeightEvt_t *event = (OverWeightEvt_t *)e;
        if (event->status == 1)
        {                             /* elevator overweighted */
            me->status |= OVER_WEIGHT; /* set overweight bit */
            return HANDLED();
        }
        /* no more overweight but not returned to check further at the end of switch  */
        me->status &= ~OVER_WEIGHT; /* clear overweight bit */
    }
    case OVERTEMPERATURE_SIG:
    {
        OverTemperatureEvt_t *event = (OverTemperatureEvt_t *)e;
        if (event->status == 1)
        {                                   /* elevator overtemperaure */
            me->status |= OVER_TEMPERATURE; /* set overtemperaure bit */
            return HANDLED();
        }
        /* no more overtemperaure but not returned to check further at the end of switch */
        me->status &= ~OVER_TEMPERATURE; /* clear overtemperaure bit */
    }
        // check for all event when all errors are gone */
        if (me->betweenTwoFloor) /* elevator stopped between two floor position */
        {
            if (me->status == 0) /* no more error exists */
            {
                me->directionMovement = 2;
                TRAN(&Elevator_move); /* go down to reach a level */
            }
        }
        else /* elevator stopped in a floor position */
        {
            if ((me->status & ((uint8_t) ~(1 << me->currentFloor))) == 0) /* no more error and all door closed except current floor door that can be opened */
            {
                TRAN(&Elevator_ready);
            }
        }
    }
    return HANDLED();
}

