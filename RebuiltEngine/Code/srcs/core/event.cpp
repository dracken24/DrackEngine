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
#include "../../../Code/includes/core/logger.hpp"

#include <vector>

typedef struct registeredEvent
{
	void *listener;
	EventPointer callback;
} registeredEvent;

typedef struct eventCodeEntry
{
	std::vector<registeredEvent> events;
} eventCodeEntry;

// This should be more than enough codes...
#define DE_MAX_MESSAGE_CODES 16384

// State structure.
typedef struct eventSystemState
{
	// Lookup table for event codes.
	std::vector<eventCodeEntry> registered[DE_MAX_MESSAGE_CODES];
} eventSystemState;

//
static bl8 is_initialized = false;
static eventSystemState state;

bl8 EventInit(void)
{
	DE_DEBUG("EventInit: Initializing event system.");
	if (is_initialized == true)
	{
		return false;
	}

	is_initialized = true;

	return true;
}

void EventShutdown(void)
{
	// DE_DEBUG("EventShutdown: Shutting down event system.");
	// Free the events arrays. And objects pointed to should be destroyed on their own.
	for (uint16 i = 0; i < DE_MAX_MESSAGE_CODES; ++i)
	{
		if (state.registered[i].size() > 0)
		{
			state.registered[i].clear();
		}
	}
}

bl8 EventRegister(uint16 code, void *listener, EventPointer on_event)
{
	if (is_initialized == false)
	{
		return false;
	}

	if (state.registered[code].size() == 0)
	{
		eventCodeEntry entry;
		state.registered[code].push_back(entry);
	}

	for (size_t it = 0; it < state.registered->at(code).events.size(); ++it)
	{
		if (state.registered->at(code).events.at(it).listener == listener)
		{
			// TODO: warn
			return false;
		}
	}

	// If at this point, no duplicate was found. Proceed with registration.
	registeredEvent event;
	event.listener = listener;
	event.callback = on_event;
	state.registered->at(code).events.push_back(event);

	return true;
}

bl8 EventUnregister(uint16 code, void *listener, EventPointer pntEvent)
{
	// DE_DEBUG("EventUnregister: Unregistering event for code %d", code);
	if (is_initialized == false)
	{
		return false;
	}

	// On nothing is registered for the code, boot out.
	if (state.registered[code].size() == 0)
	{
		// TODO: warn
		return false;
	}

	for (size_t it = 0; it < state.registered->at(code).events.size(); ++it)
	{
		registeredEvent event = state.registered->at(code).events.at(it);
		if (event.listener == listener && event.callback == pntEvent)
		{
			// Found one, remove it
			state.registered->at(code).events.erase(state.registered->at(code).events.begin() + it);
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
	if (state.registered[code].size() == 0)
	{
		return false;
	}

	for (size_t it = 0; it < state.registered->at(code).events.size(); ++it)
	{
		registeredEvent currentEvent = state.registered->at(code).events.at(it);
		if (currentEvent.callback(code, sender, currentEvent.listener, context))
		{
			// Message has been handled, do not send to other listeners.
			return true;
		}
	}

	// Not found.
	return false;
}