#ifndef ELEVATOR_INTERFACE_H
#define ELEVATOR_INTERFACE_H

#include "./BaseState.h"
#include "./ElevatorEvent.h"


typedef enum {
	DOOR_CLOSE=0,
	DOOR_OPEN
}DoorState_t;

typedef enum{
	NOT_OVERTEMPERATURE=0,
	OVERTEMPERATURE
}Overtemperatur_t;

typedef enum{
	NOT_OVERWEIGHT = 0,
	OVERWEIGHT
}Overweight_t;

typedef enum{
	PARKING_FLOOR = 0,
	FIRST_FLOOR,
	SECOND_FLOOR,
	THIRD_FLOOR
}Floor_t;

typedef enum {
	NOT_DETECTED = 0,
	DETECTED
}HalSensor_t;

typedef enum {
	DEACTIVATED = 0,
	ACTIVATED
}LimitSwitch_t;


typedef struct ElevatorState
{
    StateContext_t ancesstor;  /* derive from BaseState */
    uint8_t currentFloor;      /* indicates the elevator current floor */
    uint8_t targetFloor;       /* indicates the elevator target floor */
    uint8_t betweenTwoFloor;   /* shows if elevator between two level */
    uint8_t status;            /* indicates that  elevator emergency variable event in bit */
    uint8_t directionMovement; /* Indicates Movement direction , 1 UP,2 DOWN and 0 STOP */
	
} Elevator_t;

typedef struct
{
	HalSensor_t hal_sensor_state;
	LimitSwitch_t Up_Limit_Switch_State, Down_Limit_Switch_State;
	DoorState_t Parking_Door_State, First_Door_State, Second_Door_State, Third_Door_State;
	Overtemperatur_t Over_Temperature_state;
	Overweight_t Over_Weight_State;

}Initial_State_t;

/* Constuctor to initialize context state object */
void Elevator_costructor(Elevator_t *me);
void ctor_callback(Elevator_t* cb_me);
#endif
