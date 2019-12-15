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
    /* implement read sensors and initialize correct value fo now zero value*/
    me->status |= DOOR_OPEN_PARKING;

    return TRAN(&Elevator_ready); /* transient to ready state */
}

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
            /* implement code to close door */

            return HANDLED();
        }

        return IGNORED();
    }

    case DOOR_SIG:
    {
        DoorOpenEvt_t *event = (DoorOpenEvt_t *)e;
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
                    return TRAN(&Elevator_moveDown);
                }
                if ((me->currentFloor) < (me->targetFloor)) /* if target floor is Upper than the currentFloor */
                {
                    return TRAN(&Elevator_moveUp);
                }
            }
            return IGNORED();
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
/**
  * @brief  State handler in moveup state
  * @param  me: Pointer to a context structure
  *         that contains the extended state information that need to be preserved .
  * @param  e: Pointer to current event catched,
  *         that contains the extended event information and current event Signal .
  * @retval State: Status Handled,Ignored or Transient 
  */
State Elevator_moveUp(Elevator_t *me, Event_t const *e)
{
    switch (e->sig)
    {

    case ENTRY_SIG:
        /* implement here code for motor start to elevate up */
        me->betweenTwoFloor = 1;
        return HANDLED();

    case UPLIMITSWITCH_SIG:
    {
        me->status |= UP_LIMIT_SWITCH;
        return TRAN(&Elevator_emergency);
    }

    case DOOR_SIG:
    {

        DoorOpenEvt_t *event = (DoorOpenEvt_t *)e;
        /* in this state since all doors are already closed a door signal means a door is opened while moving up */
        /* in doubt to stop motor immediately before doing anything else it might save a life so stop motor procedure might be implemented here */

        me->status |= 1 << (event->floor); /* preserve status */
        return TRAN(&Elevator_emergency);
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
    case HALSENSOR_SIG:
        if (++me->currentFloor == me->targetFloor)
        {
            return TRAN(&Elevator_ready);
        }
        return HANDLED();
    }
    return IGNORED();
}

/**
  * @brief  State handler in movedown state
  * @param  me: Pointer to a context structure
  *         that contains the extended state information that need to be preserved .
  * @param  e: Pointer to current event catched,
  *         that contains the extended event information and current event Signal .
  * @retval State: Status Handled,Ignored or Transient 
  */
State Elevator_moveDown(Elevator_t *me, Event_t const *e)
{
    switch (e->sig)
    {

    case ENTRY_SIG:
        /* implement here code for start motor to go down */
        me->betweenTwoFloor = 1;

        return HANDLED();

    case UPLIMITSWITCH_SIG:
    {
        me->status |= UP_LIMIT_SWITCH;
        return TRAN(&Elevator_emergency);
    }

    case DOOR_SIG:
    {
        DoorOpenEvt_t *event = (DoorOpenEvt_t *)e;
        /* in this state since all doors are already closed a door signal means a door is opened while moving up */
        /* in doubt to stop motor immediately before doing anything else it might save a life so stop motor procedure might be implemented here */

        me->status |= 1 << (event->floor); /* preserve status */
        return TRAN(&Elevator_emergency);
    }

    case OVERWEIGHT_SIG:
    {
        //add send warning by voice or display
        /* in doubt to stop motor immediately before doing anything else it might save a life so stop motor procedure might be implemented here */

        me->status |= OVER_WEGHT; /* preserve status */
        return TRAN(&Elevator_emergency);
    }
    case OVERTEMPERATURE_SIG:
    {
        //add send warning by voice or display
        me->status |= OVER_TEMPERATURE; /* preserve status */
        return TRAN(&Elevator_emergency);
    }
    case HALSENSOR_SIG:

        if (--me->currentFloor == me->targetFloor)
        {
            return TRAN(&Elevator_ready);
        }
        return HANDLED();
    }
    return IGNORED();
}

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
        /* implement here code for motor to stop */

        return HANDLED();

    case DOOR_SIG:
    {
        DoorOpenEvt_t *event = (DoorOpenEvt_t *)e;
        if (event->status == 0)
        {
            me->status &= ~(1 << (event->floor)); /* preserve status */
            if (me->status)
                return TRAN(&Elevator_moveDown);
        }
        else
        {

            me->status |= 1 << (event->floor); /* preserve status */
            return HANDLED();
        }
        if (me->betweenTwoFloor) /* elevator stopped between two floor position */
        {
            if (me->status == 0) /* no more error exists */
            {
                TRAN(&Elevator_moveDown); /* go down to reach a level */
            }
        }
        else /* elevator stopped in a floor position */
        {
            if (me->status & ((uint8_t) ~(1 << me->currentFloor)) == 0) /* no more error and all door closed except current floor door that can be opened */
            {
                TRAN(&Elevator_ready);
            }
        }

        return HANDLED();
    }

    case OVERWEIGHT_SIG:
    {
        OverWeightEvt_t *event = (OverWeightEvt_t *)e;
        if (event->status == 1)
        {                             /* elevator overweighted */
            me->status |= OVER_WEGHT; /* set overweight bit */
            return HANDLED();
        }
        else
        {                              /* no more overweight */
            me->status &= ~OVER_WEGHT; /* clear overweight bit */
        }
        if (me->betweenTwoFloor) /* elevator stopped between two floor position */
        {
            if (me->status == 0) /* no more error exists */
            {
                TRAN(&Elevator_moveDown); /* go down to reach a level */
            }
        }
        else /* elevator stopped in a floor position */
        {
            if (me->status & ((uint8_t) ~(1 << me->currentFloor)) == 0) /* no more error and all door closed except current floor door that can be opened */
            {
                TRAN(&Elevator_ready);
            }
        }
    }
    case OVERTEMPERATURE_SIG:
    {
        OverTemperatureEvt_t *event = (OverTemperatureEvt_t *)e;
        if (event->status == 1)
        {                                   /* elevator overtemperaure */
            me->status |= OVER_TEMPERATURE; /* set overtemperaure bit */
            return HANDLED();
        }
        else
        {                                    /* no more overtemperaure */
            me->status &= ~OVER_TEMPERATURE; /* clear overtemperaure bit */
        }
        if (me->betweenTwoFloor) /* elevator stopped between two floor position */
        {
            if (me->status == 0) /* no more error exists */
            {
                TRAN(&Elevator_moveDown); /* go down to reach a level */
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
    }
    return IGNORED();
}
