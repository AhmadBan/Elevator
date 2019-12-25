# Welcome to Open Source Elevator

This is an open source implementation of an elevator which I wish to develop using state machine method.

## Structure
System consists of three layer. Application Layer, Hardware Layer, and Test Layer.
I used State machine diagram for application layer. and for hardware layer driver I will use Hal Driver or Stdperiph library developed by ST. and CppUTest will be used in Test. 

I used Keil RTX as RTOS so It can be helpful in future if I need a spare Thread for some task and It also provides me a MailQueue to buffer events.

## Application

System mainly consists of three main states Ready, Move, Emergency.

if Elevator is stopped in normal state it is in "Ready" state and in this state elevator is in a specific floor (Parking, 1, 2 and 3). 

If elevator is moving, then it is in "Move" state. 

If elevator detects any malfunctions by sensors, then it transients from any state to "Emergency" state. In this state elevator stops working until all sensors shows normal condition.

These are main initial states and in future states may increase.
The initial UML model presented as follows.

![Elevator UML](/uml.png)



## Elevator sensors
Elevator has 4 manual doors in each floor. A sensor attached to each door and shows if door is open or not.
(Almost all elevator has another automatic door in passenger cabin which have its own sensor and controlled by system, currently this door is ignored but it can be added in future)

Each floor has a push button in order to send a request for elevator when it is in different floors. Also These push buttons are connected to buttons in cabin correspondingly. (I assumed here that these buttons are connected to each other e.g. "2" button in cabin is connected to 2 button in floor 2 next to door and it is true for some elevator)

There is a hal sensor placed in top of cabin that points to guidance rail. Also there are magnets located in guidance rail corresponding to each floor. When hal sensor meets Magnets then elevator knows it reaches a new floor so if it is target floor it stops and if it is not it update its position. (Usually elevators use 2 speed stop which means hal when hal sensors detects first magnet it reduces speed until it detects the second magnet to completely stop. They either use simple Delta-Star circuit or in more advanced cases a 3-phase inverter is used to decrease speed softly and linearly. this way is not yet used here)


There is a temperature sensor located in motor to protect motor from overheating damages.

There is a sensor located on cabin to prevent overweight in cabin.

two limit switches are limiting the boundary of elevator movement located in bottom and top elevator. (In elevators when Up limit switch is active elevator can no longer move up but it can move down. The only situation I can imagine this switch is activated is when elevator is in revision state and controlled by user. Here we do not implement this state yet so if limit switch is activated it means there is a serious problem and needs to be supervised by an expert before continuing operation. (first safety))

There are 2 switches used for positioning. one of them is between Parking and 1, the other is between 2 and 3. if both switch are activated it means elevator is in 3. If both are deactivated it is in Parking. Finally, if down is activated and up is deactivated it is either is 1 or 2. Chances are elevator is in 1 or 2 and for some reason microcontroller lost position (e.g. reset or no power). Then it can find position by query this switches. At the moment I don't implement it and I will add a state of Lost Position in the future.


There are some other sensors, Interfaces and actuators such as Governor, Automatic door, Revision buttons, setting buttons, Speaker, LCDs, LEDs and etc. which I do not intend to implement but I may add the in future. 

## Programming Structure

The programming structure is highly inspired from [QPC Framework] (http://www.state-machine.com/qpc/) FSM Model which is developed by a genius embedded engineer Miro Samek. But since I am not still completely done with [his book] (http://www.state-machine.com/psicc2/) I preferred not to use it. 

The main idea is, there is a function that manages each state called StateHandler. A StateHandler function can accept an event, process it then either handle or ignore it in itself or this event may cause a transient to another state. 

All states are executed in an object that holds status of the system which is called "me". this "me" is something like "this" keyword in C++ or python. It contains some attributes needed for state management and also it contains current StateHandler function pointer.

RTOS has an exclusive task to dispatch states when an event rises. This task is blocked by Events MailQueue. So if there is no event CPU is free and this is the main idea behind event-driven programming (compared to polling). Events are put into a MailQueue and then dispatch task gets them and processes them in StateHandler function in "me".

All StateHandler functions have the same signature and they accept "me", "Event_t" structure pointer as argument
```markdown
typedef State (*StateHandler)(void *me, Event_t  const *e);

```

"me" is an object derived from StateContext_t structure. In order to extend this object and add needed attributes for managing system, an extended structure "Elevator_t" created that inherits from "StateContext_t". So it can be upcasted as "StateContext_t" and passed to StateHandler function and then downcasted in the function to retrieve attributes.
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
    uint8_t directionMovement; /* Indicates Movement direction, 1 UP,2 DOWN and 0 STOP */
} Elevator_t;

```
Events are all extended from a "Event_t" structure so they can be passed to any function that accept "Event_t" which means all needed extension can be added to "Event_t" and passed object by upcasting to a function and then retrieved by downcasting.
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
I intend to separate hardware layer from application layer so it can be easy to port it to other Microcontroller. However, Here I prefer to use STM32f4Discovery as my test platform because it is cheap, contains a lot of I/O and peripherals, easy to debug and work. and use HAL Driver as hardware layer.

## Test
I intend to test application layer in CppUTest in VS2013. It can be exported to unity easily by scripts if needed.

