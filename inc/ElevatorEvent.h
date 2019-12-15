#include "./BaseEvent.h"

enum ElevatorSignals
{                             /* all signals for the Elevator FSM */
  FLOORBUTTON_SIG = USER_SIG, /* Push button to target floor */

  DOOR_SIG, /* Signal from parking door sensor opening */

  UPLIMITSWITCH_SIG,   /* Signal from up limiter switch */
  DOWNLIMITSWITCH_SIG, /* Signal from down limiter switch */

  HALSENSOR_SIG, /* Signal from HAL sensor */

  OVERWEIGHT_SIG,
  OVERTEMPERATURE_SIG

};
typedef struct OverWeightEvt
{
    Event_t ancestor;
    uint8_t status; /* 0 means no OverWeight 1 means OverWeight */
} OverWeightEvt_t;

typedef struct OverTemperatureEvt
{
    Event_t ancestor;
    uint8_t status; /* 0 means no OverTemperature 1 means OverTemperature */
} OverTemperatureEvt_t;

typedef struct FloorBtnEvt
{
    Event_t ancestor;
    uint8_t targetFloor;
} FloorBtnEvt_t;

typedef struct DoorOpeneEvt
{
    Event_t ancestor;
    uint8_t floor;
    uint8_t status; //0 close 1 open
} DoorOpenEvt_t;

void ElevatorEvent_constructor(void);
