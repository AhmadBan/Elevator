#include "BaseEvent.h"

typedef uint8_t State;                                     /* status returned from a state-handler function */
typedef State (*StateHandler)(void *me, Event_t const *e); // StateHandler pointer function typedef base
typedef struct StateContextBase
{                       /* Finite State Machine */
    StateHandler state; /* current active state */
} StateContext;

#define Context_constructor(this, init) ((this)->state = (init))
void Context_init(StateContext *me, Event_t const *e);
void Context_dispatch(StateContext *me, Event_t const *e);

#define EVT_HANDLED ((State)0)
#define EVT_IGNORED ((State)1)
#define EVT_TRAN ((State)2)
#define HANDLED() (EVT_HANDLED)
#define IGNORED() (EVT_IGNORED)
#define TRAN(target_) \
    (((StateContext *)me)->state = (StateHandler)(target_), EVT_TRAN)

