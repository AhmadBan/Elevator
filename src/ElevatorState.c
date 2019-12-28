#include "../inc/ElevatorState.h"
#include "../inc/ElevatorInterface.h"
enum{
	RESET = 0,
	SET
};

//----------------------------------Constructor----------------
void Elevator_costructor(Elevator_t *me)
{
	Initial_State_t cb_me = { 0 };

	//this part is under construction
	me->currentFloor = 0;
	me->targetFloor = 0;
	/*------------------------------*/

	/* Initiialize to zero */
	me->directionMovement = 0;
	me->status = 0;

	//call back that will be filled by user into cb_me variable based on hardware used
	ctor_callback(&cb_me);
	if (cb_me.hal_sensor_state == NOT_DETECTED)
		me->betweenTwoFloor = SET;
	if (cb_me.Up_Limit_Switch_State == ACTIVATED)
		me->status |= UP_LIMIT_SWITCH;
	if (cb_me.Down_Limit_Switch_State == ACTIVATED)
		me->status |= DOWN_LIMIT_SWITCH;
	if (cb_me.Parking_Door_State == DOOR_OPEN)
		me->status |= DOOR_OPEN_PARKING;
	if (cb_me.First_Door_State == DOOR_OPEN)
		me->status |= DOOR_OPEN_FIRST;
	if (cb_me.Second_Door_State == DOOR_OPEN)
		me->status |= DOOR_OPEN_SECOND;
	if (cb_me.Third_Door_State == DOOR_OPEN)
		me->status |= DOOR_OPEN_THIRD;
	if (cb_me.Over_Temperature_state == ACTIVATED)
		me->status |= OVER_TEMPERATURE;
	if (cb_me.Over_Weight_State == ACTIVATED)
		me->status |= OVER_WEIGHT;


	((StateContext_t *)me)->state = (StateHandler)Elevator_initial;/*  Initialize StateHandler function */

	Base_dispatch((StateContext_t *)me, (void*)0); /* process Initialize StateHandler */
}
