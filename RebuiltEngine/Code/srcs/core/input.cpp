/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 29-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	     input.cpp       *--*                  | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "../../includes/core/input.hpp"
#include "../../includes/core/deMemory.hpp"
#include "../../includes/core/logger.hpp"
#include "../../includes/core/event.hpp"

typedef struct keyboardState
{
	bl8 keys[256];
} keyboardState;

typedef struct mouseState
{
	sint16 x;
	sint16 y;
	uint8 buttons[BUTTON_MAX_BUTTONS];
} mouseState;

typedef struct inputState 
{
	keyboardState keyboard_current;
	keyboardState keyboard_previous;
	mouseState mouse_current;
	mouseState mouse_previous;
}	inputState;

// Internal input state
static bl8			initialized = false;
static inputState	state = {};

void	InputInit()
{
	DE_Calloc(&state, sizeof(inputState));
	initialized = true;
	DE_INFO("Input subsystem initialized.");
}

void	InputShutdown()
{
	// TODO: Add shutdown routines when needed.
	initialized = false;
}

void	InputUpdate(dbl64 delta_time)
{
	if (!initialized)
	{
		return;
	}

	// Copy current states to previous states.
	DE_CopyMemory(&state.keyboard_previous, &state.keyboard_current, sizeof(keyboardState));
	DE_CopyMemory(&state.mouse_previous, &state.mouse_current, sizeof(mouseState));
}

void	OnKeyProcess(keys key, bl8 pressed)
{
	// Only handle this if the state actually changed.
	if (state.keyboard_current.keys[key] != pressed)
	{
		// Update internal state.
		state.keyboard_current.keys[key] = pressed;

		// Fire off an event for immediate processing.
		eventContext context;
		context.data.u16[0] = key;
		EventFire(pressed ? DE_EVENT_CODE_KEY_PRESSED : DE_EVENT_CODE_KEY_RELEASED, 0, context);
	}
}

void	OnMouseButtonPress(buttons button, bl8 pressed)
{
	// If the state changed, fire an event.
	if (state.mouse_current.buttons[button] != pressed)
	{
		state.mouse_current.buttons[button] = pressed;

		// Fire the event.
		eventContext context;
		context.data.u16[0] = button;
		EventFire(pressed ? DE_EVENT_CODE_BUTTON_PRESSED : DE_EVENT_CODE_BUTTON_RELEASED, 0, context);
	}
}

void	OnMouseMove(sint16 x, sint16 y)
{
	// Only process if actually different
	if (state.mouse_current.x != x || state.mouse_current.y != y)
	{
		// NOTE: Enable this if debugging.
		// KDEBUG("Mouse pos: %i, %i!", x, y);

		// Update internal state.
		state.mouse_current.x = x;
		state.mouse_current.y = y;

		// Fire the event.
		eventContext context;
		context.data.u16[0] = x;
		context.data.u16[1] = y;
		EventFire(DE_EVENT_CODE_MOUSE_MOVED, 0, context);
	}
}

void	OnMouseWheel(sint8 z_delta)
{
	// NOTE: no internal state to update.

	// Fire the event.
	eventContext context;
	context.data.u8[0] = z_delta;
	EventFire(DE_EVENT_CODE_MOUSE_WHEEL, 0, context);
}

bl8		OnKeyPress(keys key)
{
	if (!initialized)
	{
		return false;
	}
	return state.keyboard_current.keys[key] == true;
}

bl8		OnKeyRelease(keys key)
{
	if (!initialized)
	{
		return true;
	}
	return state.keyboard_current.keys[key] == false;
}

bl8		OnKeyDown(keys key)
{
	if (!initialized)
	{
		return false;
	}
	return state.keyboard_previous.keys[key] == true;
}

bl8		OnKeyUP(keys key)
{
	if (!initialized)
	{
		return true;
	}
	return state.keyboard_previous.keys[key] == false;
}

// mouse input
bl8		OnMouseButtonPress(buttons button)
{
	if (!initialized)
	{
		return false;
	}
	return state.mouse_current.buttons[button] == true;
}

bl8		OnMouseButtonRelease(buttons button)
{
	if (!initialized)
	{
		return true;
	}
	return state.mouse_current.buttons[button] == false;
}

bl8		OnMouseButtonDown(buttons button)
{
	if (!initialized)
	{
		return false;
	}
	return state.mouse_previous.buttons[button] == true;
}

bl8		OnMouseButtonUp(buttons button)
{
	if (!initialized)
	{
		return true;
	}
	return state.mouse_previous.buttons[button] == false;
}

void	GetMousePosition(sint32* x, sint32* y)
{
	if (!initialized)
	{
		*x = 0;
		*y = 0;
		return;
	}
	*x = state.mouse_current.x;
	*y = state.mouse_current.y;
}

void	GetPreviousMousePosition(sint32 *x, sint32 *y)
{
	if (!initialized)
	{
		*x = 0;
		*y = 0;
		return;
	}
	*x = state.mouse_previous.x;
	*y = state.mouse_previous.y;
}
