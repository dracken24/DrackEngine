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

#include "core/input.hpp"
#include "core/event.hpp"
#include "core/deMemory.hpp"
#include "core/logger.hpp"

typedef struct keyboard_state
{
	bl8 keys[256];
} keyboard_state;

typedef struct mouse_state
{
	sint16 x;
	sint16 y;
	uint8 buttons[BUTTON_MAX_BUTTONS];
} mouse_state;

typedef struct input_state
{
	keyboard_state keyboard_current;
	keyboard_state keyboard_previous;
	mouse_state mouse_current;
	mouse_state mouse_previous;
} input_state;

// Internal input state
static bl8 initialized = false;
static input_state state = {};

void DE_InputInit(void)
{
	SetMemory(&state, sizeof(input_state));
	initialized = true;
	DE_INFO("Input subsystem initialized.");
}

void DE_InputShutdown(void)
{
	// TODO: Add shutdown routines when needed.
	initialized = false;
}

void DE_InputUpdate(dbl64 deltaTime)
{
	if (!initialized)
	{
		return;
	}

	// Copy current states to previous states.
	CopyMemory(&state.keyboard_previous, &state.keyboard_current, sizeof(keyboard_state));
	CopyMemory(&state.mouse_previous, &state.mouse_current, sizeof(mouse_state));
}

void InputProcessKey(keys key, bl8 pressed)
{
	// Only handle this if the state actually changed.
	if (state.keyboard_current.keys[key] != pressed)
	{
		// Update internal state.
		state.keyboard_current.keys[key] = pressed;

		// Fire off an event for immediate processing.
		eventContext context;
		context.data.uint16[0] = key;
		EventFire(pressed ? EVENT_CODE_KEY_PRESSED : EVENT_CODE_KEY_RELEASED, 0, context);
	}
}

void DE_InputProcessButton(buttons button, bl8 pressed)
{
	// If the state changed, fire an event.
	if (state.mouse_current.buttons[button] != pressed)
	{
		state.mouse_current.buttons[button] = pressed;

		// Fire the event.
		eventContext context;
		context.data.uint16[0] = button;
		EventFire(pressed ? EVENT_CODE_BUTTON_PRESSED : EVENT_CODE_BUTTON_RELEASED, 0, context);
	}
}

void DE_InputProcessMouseMove(sint16 x, sint16 y)
{
	// Only process if actually different
	if (state.mouse_current.x != x || state.mouse_current.y != y)
	{
		// NOTE: Enable this if debugging.
		// DE_DEBUG("Mouse pos: %i, %i!", x, y);

		// Update internal state.
		state.mouse_current.x = x;
		state.mouse_current.y = y;

		// Fire the event.
		eventContext context;
		context.data.uint16[0] = x;
		context.data.uint16[1] = y;
		EventFire(EVENT_CODE_MOUSE_MOVED, 0, context);
	}
}

void	DE_OnMouseWheel(bl8 z_delta)
{
	// NOTE: no internal state to update.

	// Fire the event.
	eventContext context;
	context.data.uint8[0] = z_delta;
	if (z_delta > 0)
	{
		EventFire(EVENT_CODE_MOUSE_WHEEL_UP, 0, context);
	}
	else
	{
		EventFire(EVENT_CODE_MOUSE_WHEEL_DOWN, 0, context);
	}
}

bl8		DE_OnKeyDown(keys key)
{
	if (!initialized)
	{
		return false;
	}
	return state.keyboard_current.keys[key] == true;
}

bl8		DE_OnKeyUP(keys key)
{
	if (!initialized)
	{
		return true;
	}
	return state.keyboard_current.keys[key] == false;
}

bl8		DE_OnKeyPress(keys key)
{
	if (!initialized)
	{
		return false;
	}
	return state.keyboard_previous.keys[key] == true;
}

bl8		DE_OnKeyRelease(keys key)
{
	if (!initialized)
	{
		return true;
	}
	return state.keyboard_previous.keys[key] == false;
}

// mouse input
bl8 DE_OnMouseButtonPress(buttons button)
{
	if (!initialized) {
		return false;
	}
	return state.mouse_current.buttons[button] == true;
}

bl8 DE_OnMouseButtonRelease(buttons button)
{
	if (!initialized)
	{
		return true;
	}
	return state.mouse_current.buttons[button] == false;
}

bl8 DE_OnMouseButtonDown(buttons button)
{
	if (!initialized)
	{
		return false;
	}
	return state.mouse_previous.buttons[button] == true;
}

bl8 DE_OnMouseButtonUp(buttons button)
{
	if (!initialized)
	{
		return true;
	}
	return state.mouse_previous.buttons[button] == false;
}

void DE_GetMousePosition(sint32* x, sint32* y)
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

void DE_GetPreviousMousePosition(sint32* x, sint32* y)
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

bl8 DE_OnWindowResizeMove(uint8 code, sint16 width, sint16 height,
	sint16 x, sint16 y)
{
	// NOTE: no internal state to update.
	// Fire the event.
	// DE_DEBUG("CODE: %i", code);
	eventContext context;
	if (code == 22)
	{
		context.data.uint16[0] = width;
		context.data.uint16[1] = height;
		context.data.c[15] = true;
	}
	else if (code == 150)
	{
		context.data.uint16[0] = x;
		context.data.uint16[1] = y;
		context.data.c[15] = false;
	}

	EventFire(EVENT_CODE_RESIZED, 0, context);

	return true;
}
