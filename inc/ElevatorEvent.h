#include "./BaseEvent.h"

enum ElevatorSignals
{                             /* all signals for the Elevator FSM */
  FLOORBUTTON_SIG = USER_SIG, /* Push button to target floor */

  DOOROPEN_SIG, /* Signal from parking door sensor opening */

  UPLIMITSWITCH_SIG,   /* Signal from up limiter switch */
  DOWNLIMITSWITCH_SIG, /* Signal from down limiter switch */

  HALSENSOR_SIG, /* Signal from HAL sensor */

  OVERWEIGHT_SIG,
  OVERTEMPERATURE_SIG

};
typedef struct FloorBtnEvt
{
    Event_t ancestor;
    uint8_t targetFloor;
} FloorBtnEvt_t;

typedef struct DoorOpeneEvt
{
    Event_t ancestor;
    uint8_t floor;
} DoorOpenEvt_t;

void ElevatorEvent_constructor(void);