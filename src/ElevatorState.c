#include "../inc/ElevatorState.h"
#include "main.h"
#include "stm32f4xx_hal.h"

/**
  * @brief  Initializes the Elevator starting state
  * @param  me: pointer to a context structure
  *         that contains the extended state information and current state handler.
  * @param  e: Pointer to current event catched,
  *         that contains the extended event information and current event Signal 
  *         not used here just to keep signature.
  * @retval state status Handled,Ignored or Transient 
  */
State Elevator_initial(Elevator_t *me, Event_t const *e)
{
  (void)e;

  if (me->status == 0)
  {
    if (me->betweenTwoFloor)
    {
      me->directionMovement = DOWN_DIRECTION;
      return TRAN(&Elevator_move);
    }
    else
    {
      return TRAN(&Elevator_ready);
    }
  }
  else
  {
    return TRAN(&Elevator_emergency);
  }
}

//----------------------------------Constructor----------------
void Elevator_costructor(Elevator_t *me)
{
	Event_t e;
	e.sig=ENTRY_SIG;
  //this part is under construction
  me->currentFloor = 0;
  me->targetFloor = 0;
  /*------------------------------*/

  /* Initiialize to zero */
  me->directionMovement = 0;
  me->status = 0;

  /* Read Sensors to initialize state attributes */
  if (HAL_GPIO_ReadPin(HalSensor_GPIO_Port, HalSensor_Pin) == SET)
    me->betweenTwoFloor = RESET;
  else
    me->betweenTwoFloor = SET;

  if (HAL_GPIO_ReadPin(DoorParking_GPIO_Port, DoorParking_Pin) == SET)/* Check if Parking Door is open or not */
    me->status |= DOOR_OPEN_PARKING;
  if (HAL_GPIO_ReadPin(DoorFirstFloor_GPIO_Port, DoorFirstFloor_Pin) == SET)/* Check if First floor Door is open or not */
    me->status |= DOOR_OPEN_FIRST;
  if (HAL_GPIO_ReadPin(DoorSecondFloor_GPIO_Port, DoorSecondFloor_Pin) == SET)/* Check if Second floor Door is open or not */
    me->status |= DOOR_OPEN_SECOND;
  if (HAL_GPIO_ReadPin(DoorThirdFloor_GPIO_Port, DoorThirdFloor_Pin) == SET)/* Check if Third floor Door is open or not */
    me->status |= DOOR_OPEN_THIRD;

  if (HAL_GPIO_ReadPin(Overtemperature_GPIO_Port, Overtemperature_Pin) == SET)/* Check if Over Temperature sensor is activated or not */
    me->status |= OVER_TEMPERATURE;
  if (HAL_GPIO_ReadPin(OverWeight_GPIO_Port, OverWeight_Pin) == SET)/* Check if Over Weight sensor is activated or not */
    me->status |= OVER_WEIGHT;

  if (HAL_GPIO_ReadPin(UpLimitSwitch_GPIO_Port, UpLimitSwitch_Pin) == SET)/* Check if Up limit switch is activated or not */
    me->status |= UP_LIMIT_SWITCH;

  if (HAL_GPIO_ReadPin(DownLimitSwitch_GPIO_Port, DownLimitSwitch_Pin) == SET)/* Check if Down limit switch is activated or not */
    me->status |= DOWN_LIMIT_SWITCH;

 ((StateContext_t *)me)->state = (StateHandler)Elevator_initial;/*  Initialize StateHandler function */

  Base_dispatch((StateContext_t *)me, &e); /* process Initialize StateHandler */
}
