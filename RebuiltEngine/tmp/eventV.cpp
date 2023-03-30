/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 29-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	      event.cpp           *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "../../../Code/includes/core/deMemory.hpp"
#include "../../../Code/includes/core/event.hpp"

#include <vector>

typedef struct registeredEvent
{
    void *listener;
    EventPointer callback;
} registeredEvent;

// typedef struct eventCodeEntry
// {
// 	registeredEvent *events;
// } eventCodeEntry;

// This should be more than enough codes...
#define MAX_MESSAGE_CODES 16384

// State structure.
// typedef struct eventSystemState {
// 	// Lookup table for event codes.
// 	eventCodeEntry registered[MAX_MESSAGE_CODES];
// } eventSystemState;

/**
 * Event system internal state.
 */
static bl8 is_initialized = false;
// static eventSystemState state;
static std::vector<registeredEvent> state;

bl8 EventInit(void)
{
    if (is_initialized == true)
    {
        return false;
    }
    is_initialized = false;
    // DE_Calloc(&state, sizeof(state));

    is_initialized = true;

    return true;
}

void EventShutdown(void)
{
    // Free the events arrays. And objects pointed to should be destroyed on their own.
    state.clear();
}

bl8 EventRegister(uint16 code, void *listener, EventPointer on_event)
{
    if (is_initialized == false)
    {
        return false;
    }

    if (state[code].listener == nullptr)
    {
        registeredEvent newEvent;
        newEvent.listener = listener;
        newEvent.callback = on_event;
        state[code] = newEvent;
    }

    for (size_t i = 0; i < state.size(); ++i)
    {
        if (state[code].listener == listener)
        {
            // TODO: warn
            return false;
        }
    }

    // If at this point, no duplicate was found. Proceed with registration.
    registeredEvent event;
    event.listener = listener;
    event.callback = on_event;

    // eventCodeEntry entry;
    // entry.events = event;

    state.push_back(event);
    // darray_push(state.registered[code].events, event);

    return true;
}

bl8 EventUnregister(uint16 code, void *listener, EventPointer on_event)
{
    if (is_initialized == false)
    {
        return false;
    }

    // On nothing is registered for the code, boot out.
    if (state[code].listener == 0)
    {
        // TODO: warn
        return false;
    }

    for (size_t i = 0; i < state.size(); ++i)
    {
        registeredEvent e = state.at(i);
        if (e.listener == listener && e.callback == on_event)
        {
            // Found one, remove it
            state.erase(state.begin() + i);
            return true;
        }
    }

    // Not found.
    return false;
}

bl8 EventFire(uint16 code, void *sender, eventContext context)
{
    if (is_initialized == false)
    {
        return false;
    }

    // If nothing is registered for the code, boot out.
    if (state[code].listener == 0)
    {
        return false;
    }

    // uint64 registered_count = darray_length(state.registered[code].events);
    for (size_t i = 0; i < state.size(); ++i)
    {
        registeredEvent e = state.at(code);
        if (e.callback(code, sender, e.listener, context))
        {
            // Message has been handled, do not send to other listeners.
            return true;
        }
    }

    // Not found.
    return false;
}