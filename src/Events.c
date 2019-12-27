#include "..\inc\ElevatorEvent.h"
#include "..\inc\ElevatorState.h"
#include "Threads.h"
#include "cmsis_os.h"
#include "main.h"
#include "stm32f4xx_hal.h"
extern osMailQId qid_EventQueue; // mail queue id
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  DoorEvt_t *pMail; /* Down limit switch down Interrupt */
  pMail = osMailAlloc(qid_EventQueue, 0);
  if (pMail)
  {
    switch (GPIO_Pin)
    {
    case DownLimitSwitch_Pin:
      pMail->ancestor.sig = LIMITSWITCH_SIG;
      if (HAL_GPIO_ReadPin(DownLimitSwitch_GPIO_Port, GPIO_Pin) == SET)
      {
        pMail->status |= DOWN_LIMIT_SWITCH;
      }
      else
      {
        pMail->status &= ~DOWN_LIMIT_SWITCH;
      }

      break;
    case UpLimitSwitch_Pin:
      pMail->ancestor.sig = LIMITSWITCH_SIG;
      if (HAL_GPIO_ReadPin(UpLimitSwitch_GPIO_Port, GPIO_Pin) == SET)
      {
        pMail->status |= UP_LIMIT_SWITCH;
      }
      else
      {
        pMail->status &= ~UP_LIMIT_SWITCH;
      }

      break;
    case Overtemperature_Pin:
      pMail->ancestor.sig = OVERTEMPERATURE_SIG;
      pMail->status = HAL_GPIO_ReadPin(Overtemperature_GPIO_Port, Overtemperature_Pin);
      break;
    case OverWeight_Pin:
      pMail->ancestor.sig = OVERWEIGHT_SIG;
      pMail->status = HAL_GPIO_ReadPin(OverWeight_GPIO_Port, OverWeight_Pin);
      break;

    case DoorParking_Pin:
      pMail->ancestor.sig = DOOR_SIG;
      pMail->floor = 0;

      pMail->status = HAL_GPIO_ReadPin(DoorParking_GPIO_Port, DoorParking_Pin);
      break;

    case DoorFirstFloor_Pin:
      pMail->ancestor.sig = DOOR_SIG;
      pMail->floor = 1;

      pMail->status = HAL_GPIO_ReadPin(DoorFirstFloor_GPIO_Port, DoorFirstFloor_Pin);
      break;

    case DoorSecondFloor_Pin:
      pMail->ancestor.sig = DOOR_SIG;
      pMail->floor = 2;

      pMail->status = HAL_GPIO_ReadPin(DoorSecondFloor_GPIO_Port, DoorSecondFloor_Pin);
      break;

    case DoorThirdFloor_Pin:
      pMail->ancestor.sig = DOOR_SIG;
      pMail->floor = 3;

      pMail->status = HAL_GPIO_ReadPin(DoorThirdFloor_GPIO_Port, DoorThirdFloor_Pin);
      break;
    case HalSensor_Pin:
      pMail->ancestor.sig = HALSENSOR_SIG;
      pMail->status = HAL_GPIO_ReadPin(HalSensor_GPIO_Port, HalSensor_Pin);
      break;
    case ParkingBTN_Pin:
      pMail->ancestor.sig = FLOORBUTTON_SIG;
      ((FloorBtnEvt_t *)pMail)->targetFloor = 0;
      break;
    case FirstFloorBtn_Pin:
      pMail->ancestor.sig = FLOORBUTTON_SIG;
      ((FloorBtnEvt_t *)pMail)->targetFloor = 1;
      break;
    case SecondFloorBtn_Pin:
      pMail->ancestor.sig = FLOORBUTTON_SIG;
      ((FloorBtnEvt_t *)pMail)->targetFloor = 2;
      break;
    case ThirdFloorBtn_Pin:
      pMail->ancestor.sig = FLOORBUTTON_SIG;
      ((FloorBtnEvt_t *)pMail)->targetFloor = 3;
      break;
    }
    osMailPut(qid_EventQueue, pMail);
  }
}
