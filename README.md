# Welcome to OpenSource Elevator

This is an open source implementation of an elevator which I wish to develop using state machine method.

## Structure

The structure used here is highly isnpired by [QPC Framework](http://www.state-machine.com/qpc/)
(the framework is not used).

Keil RTX is used as RTOS.

System mainly consists of three main states Ready, Move, Emergency.

if Elevator is stopped in normal state it is in "Ready" state and in this state elevator is in a specifc floor (Parking , 1, 2 and 3). 

If elevator is moving then it is in "Move" state. 

If elevator detects any malfunctions by sensors then it transients from any state to "Emergency" state. In this state elevator stopps working until all sensors shows normal condition.

These are main initial states and in future states may increase.
The initial UML model presented as follows.

![Elevator UML](/uml.png)



## Elevator sensors
Elevator has 4 manual doors in each floor that a sensor attached to each door and shows if door is open or not.

Each floor has a push button in order to request elevator when it is in different floors. Floor has a push button in order to request elevator when it is in different floors. Also These push buttons are connected to buttons in cabin correspondingly.

There is a hal sensor in top of cabin that placed near guidance rail. Also there are magnets located in guidance rail correponding to each floor. When hal sensor meets Magnets then elevator knows it reaches a new floor so if it is target floor it stops and if it is not it update its position.


There is a temperature sensor located in motor to protect motor from overheating damages.

There is a sensor located on cabin to prevent overweight in cabin.

two limit switches are limiting the boundry of elevator movement located in bottom and top elevator.


there are some other sensors such as Governor, Automatic door,Revision buttons, Setting buttons and etc which I do not intend to implement but I may add the in future. 

## Programming Structure

As I mentioned earlier, programming structure is inspired from QPC which is developed by a genius Miro Samek. But since I am not still completely done with [his book](http://www.state-machine.com/psicc2/) I prefered not to use it. 

The main idea is there is a function that manages each state called StateHandler. A state can accpet an event process it and then it can either handle it or ignore it in itself or this event may cause a transient from this state to another state. 

All states are executed in an object that holds status of system which called "me". this "me" is something like "this" keyword in C++ or python. It contains some attributes needed for state management and also it contains current state funtion pointer.

RTOS has an exclusive task to dispatch states when an event rises. This task is blocked by Events MailQueue. So if there is no event CPU is free and this is the main idea behind event-driven programming(compared to pollin). Events are put into a MailQueue and then dispatch task gets them and processes them in StateHandler function in "me".

All StateHandler functions have the same signature and they accept "StateContext_t" ,"Event_t" structure as argument

"me" is an object derived from StateContext_t structure. In order to extend this object and add needed attributes for managing system, an extended structure "Elevator_t" created that inherits from "StateContext_t". So it can be upcasted as "StateContext_t" and passed to StateHander function and then downcasted in the function to retrieve attributes.
```markdown
/* base state */
typedef struct StateContextBase
{                       /* Finite State Machine */
    StateHandler state; /* current active state */
} StateContext_t;
/* extended state */
typedef struct ElevatorState
{
    StateContext_t ancesstor;  /* derive from BaseState */
    uint8_t currentFloor;      /* indicates the elevator current floor */
    uint8_t targetFloor;       /* indicates the elevator target floor */
    uint8_t betweenTwoFloor;   /* shows if elevator between two level */
    uint8_t status;            /* indicates that  elevator emergency variable event in bit */
    uint8_t directionMovement; /* Indicates Movement direction , 1 UP,2 DOWN and 0 STOP */
} Elevator_t;

```
Events are all extended from a "Event_t" structure so they can be passed to any function that accept "Event_t" which means all needed extension can be added to "Event_t" and passed object by upcasting  to a function and then retrieved by downcasting.
```markdown

typedef struct EventTag
{                 /* the event structure */
    Signal_t sig; /* signal of the event */
} Event_t;
/* an example extended event */
typedef struct DoorOpeneEvt
{
    Event_t ancestor;
    uint8_t floor;
    uint8_t status; //0 close 1 open
} DoorOpenEvt_t;
```

## Hardware
I intend to separate hardware layer from application layer so it can be easy to port it to other Microcontroller. However, Here I prefer to use STM32f4Discovery as my test platform because it is cheap, contains a lot of I/O and peripherals, easy to debug and work. and use HAL_Driver as hardware layer.

## Test
I intend to test application layer in CppUtest in VS2013. It can be exported to unity easily by scripts if needed.

