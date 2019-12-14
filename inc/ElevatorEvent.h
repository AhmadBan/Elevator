#include "BaseEvent.h"

enum ElevatorSignals
{                         /* all signals for the Elevator FSM */
  PARKING_SIG = USER_SIG, /* Button to Parking */
  FIRST_SIG,              /* Button to First floor */
  SECOND_SIG,             /* Button to Second floor */
  THIRD_SIG,              /* Button to Third floor */

  PARKINGDOOROPEN_SIG, /* Signal from parking door sensor opening */
  FIRSTDOOROPEN_SIG,   /* Signal from first floor door sensor opening */
  SECONDDOOROPEN_SIG,  /* Signal from second floor door sensor opening */
  THIRDDOOROPEN_SIG,   /* Signal from third floor door sensor opening */

  UPLIMITSWITCH_SIG,   /* Signal from up limiter switch */
  DOWNLIMITSWITCH_SIG, /* Signal from down limiter switch */

  HALSENSOR_SIG, /* Signal from HAL sensor */

  OVERWEIGHT_SIG,
  OVERTEMPERATURE_SIG

};



void ElevatorEvent_constructor(void);