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

typedef struct	registeredEvent
{
	void*		listener;
	eventPtr	callback;
}	registeredEvent;

typedef struct eventCodeEntry
{
	registeredEvent* events;
} eventCodeEntry;

// This should be more than enough codes...
#define MAX_MESSAGE_CODES 16384

// State structure.
typedef struct eventSystemState
{
	// Lookup table for event codes.
	eventCodeEntry registered[MAX_MESSAGE_CODES];
} eventSystemState;

/**
 * Event system internal state.
 */
static eventSystemState	*statePtr;

bl8		EventInitialize(uint64 *memoryRequirement, void *state)
{
	*memoryRequirement = sizeof(eventSystemState);
	if (state == 0)
	{
		return false;
	}

	SetMemory(state, sizeof(state));
	statePtr = (eventSystemState *)state;

	return true;
}

void	EventShutdown(void *state)
{
	if (statePtr)
	{
		// Free the events arrays. And objects pointed to should be destroyed on their own.
		for (uint16 i = 0; i < MAX_MESSAGE_CODES; ++i)
		{
			if (statePtr->registered[i].events != 0)
			{
				DE_ArrayDestroy(statePtr->registered[i].events);
				statePtr->registered[i].events = 0;
			}
		}
	}

	statePtr = 0;
}

bl8		EventRegister(uint16 code, void* listener, eventPtr onEvent)
{
	if (!statePtr)
	{
		return false;
	}
	if (statePtr->registered[code].events == 0)
	{
		statePtr->registered[code].events = (registeredEvent *)DE_ArrayCreate(DE_ARRAY_DIN_DEFAULT_CAPACITY, sizeof(registeredEvent));
	}

	uint64 registered_count = DE_ArrayLength(statePtr->registered[code].events);
	for (uint64 i = 0; i < registered_count; ++i)
	{
		if (statePtr->registered[code].events[i].listener == listener)
		{
			// TODO: warn
			return false;
		}
	}

	// If at this point, no duplicate was found. Proceed with registration.
	registeredEvent	event;
	event.listener = listener;
	event.callback = onEvent;
	_DE_ArrayPush(statePtr->registered[code].events, &event);

	return true;
}

bl8		EventUnregister(uint16 code, void* listener, eventPtr onEvent)
{
	if (!statePtr)
	{
		return false;
	}

	// On nothing is registered for the code, boot out.
	if (statePtr->registered[code].events == 0)
	{
		// TODO: warn
		return false;
	}

	uint64 registered_count = DE_ArrayLength(statePtr->registered[code].events);
	for (uint64 i = 0; i < registered_count; ++i)
	{
		registeredEvent e = statePtr->registered[code].events[i];
		if (e.listener == listener && e.callback == onEvent)
		{
			// Found one, remove it
			registeredEvent poppedEvent;
			DE_ArrayPopAt(statePtr->registered[code].events, i, &poppedEvent);

			return true;
		}
	}

	// Not found.
	return false;
}

bl8		EventFire(uint16 code, void* sender, eventContext context)
{
	if (!statePtr)
	{
		return false;
	}

	// If nothing is registered for the code, boot out.
	if (statePtr->registered[code].events == 0)
	{
		return false;
	}

	uint64 registeredCount = DE_ArrayLength(statePtr->registered[code].events);
	for (uint64 i = 0; i < registeredCount; ++i)
	{
		registeredEvent e = statePtr->registered[code].events[i];
		if (e.callback(code, sender, e.listener, context))
		{
			// Message has been handled, do not send to other listeners.
			return true;
		}
	}

	// Not found.
	return false;
}
