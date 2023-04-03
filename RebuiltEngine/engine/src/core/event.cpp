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

#include <core/event.hpp>

#include <core/deMemory.hpp>
#include <containers/arrayDinamic.hpp>

typedef struct registeredEvent
{
    void* listener;
    eventPtr callback;
} registeredEvent;

typedef struct event_code_entry
{
    registeredEvent* events;
} event_code_entry;

// This should be more than enough codes...
#define MAX_MESSAGE_CODES 16384

// State structure.
typedef struct event_system_state
{
    // Lookup table for event codes.
    event_code_entry registered[MAX_MESSAGE_CODES];
} event_system_state;

/**
 * Event system internal state.
 */
static bl8 is_initialized = false;
static event_system_state state;

bl8 EventInitialize()
{
    if (is_initialized == true)
    {
        return false;
    }
    is_initialized = false;
    SetMemory(&state, sizeof(state));

    is_initialized = true;

    return true;
}

void EventShutdown()
{
    // Free the events arrays. And objects pointed to should be destroyed on their own.
    for(uint16 i = 0; i < MAX_MESSAGE_CODES; ++i)
    {
        if(state.registered[i].events != 0)
        {
            ArrayDinDestroy(state.registered[i].events);
            state.registered[i].events = 0;
        }
    }
}

bl8 EventRegister(uint16 code, void* listener, eventPtr onEvent)
{
    if(is_initialized == false)
    {
        return false;
    }

    if(state.registered[code].events == 0)
    {
        state.registered[code].events = (registeredEvent *)ArrayDinCreate(registeredEvent);
    }

    uint64 registered_count = ArrayDinLength(state.registered[code].events);
    for(uint64 i = 0; i < registered_count; ++i)
    {
        if(state.registered[code].events[i].listener == listener)
        {
            // TODO: warn
            return false;
        }
    }

    // If at this point, no duplicate was found. Proceed with registration.
    registeredEvent event;
    event.listener = listener;
    event.callback = onEvent;
    ArrayDinPushEvent(state.registered[code].events, event);

    return true;
}

bl8 EventUnregister(uint16 code, void* listener, eventPtr onEvent)
{
    if(is_initialized == false)
    {
        return false;
    }

    // On nothing is registered for the code, boot out.
    if(state.registered[code].events == 0)
    {
        // TODO: warn
        return false;
    }

    uint64 registered_count = ArrayDinLength(state.registered[code].events);
    for(uint64 i = 0; i < registered_count; ++i)
    {
        registeredEvent e = state.registered[code].events[i];
        if(e.listener == listener && e.callback == onEvent)
        {
            // Found one, remove it
            registeredEvent popped_event;
            ArrayDinPopAt(state.registered[code].events, i, &popped_event);
            return true;
        }
    }

    // Not found.
    return false;
}

bl8 EventFire(uint16 code, void* sender, eventContext context)
{
    if(is_initialized == false)
    {
        return false;
    }

    // If nothing is registered for the code, boot out.
    if(state.registered[code].events == 0)
    {
        return false;
    }

    uint64 registered_count = ArrayDinLength(state.registered[code].events);
    for(uint64 i = 0; i < registered_count; ++i)
    {
        registeredEvent e = state.registered[code].events[i];
        if(e.callback(code, sender, e.listener, context)) {
            // Message has been handled, do not send to other listeners.
            return true;
        }
    }

    // Not found.
    return false;
}
