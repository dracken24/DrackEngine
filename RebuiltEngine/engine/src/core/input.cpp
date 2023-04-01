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
#include "core/deMemory.hpp"
#include "core/logger.hpp"
#include "core/event.hpp"

#include <X11/keysym.h>

// // Key translation
// keys TranslateKeycode(uint32 keyCode)
// {
// 	switch (keyCode)
// 	{
// 	case XK_BackSpace:
// 		return KEY_BACKSPACE;
// 	case XK_Return:
// 		return KEY_ENTER;
// 	case XK_Tab:
// 		return KEY_TAB;
// 		// case XK_Shift: return KEY_SHIFT;
// 		// case XK_Control: return KEY_CONTROL;

// 	case XK_Pause:
// 		return KEY_PAUSE;
// 	case XK_Caps_Lock:
// 		return KEY_CAPITAL;

// 	case XK_Escape:
// 		return KEY_ESCAPE;

// 		// Not supported
// 		// case : return KEY_CONVERT;
// 		// case : return KEY_NONCONVERT;
// 		// case : return KEY_ACCEPT;

// 	case XK_Mode_switch:
// 		return KEY_MODECHANGE;

// 	case XK_space:
// 		return KEY_SPACE;
// 	case XK_Prior:
// 		return KEY_PRIOR;
// 	case XK_Next:
// 		return KEY_NEXT;
// 	case XK_End:
// 		return KEY_END;
// 	case XK_Home:
// 		return KEY_HOME;
// 	case XK_Left:
// 		return KEY_LEFT;
// 	case XK_Up:
// 		return KEY_UP;
// 	case XK_Right:
// 		return KEY_RIGHT;
// 	case XK_Down:
// 		return KEY_DOWN;
// 	case XK_Select:
// 		return KEY_SELECT;
// 	case XK_Print:
// 		return KEY_PRINT;
// 	case XK_Execute:
// 		return KEY_EXECUTE;
// 	// case XK_snapshot: return KEY_SNAPSHOT; // not supported
// 	case XK_Insert:
// 		return KEY_INSERT;
// 	case XK_Delete:
// 		return KEY_DELETE;
// 	case XK_Help:
// 		return KEY_HELP;

// 	case XK_Meta_L:
// 		return KEY_LWIN; // TODO: not sure this is right
// 	case XK_Meta_R:
// 		return KEY_RWIN;
// 		// case XK_apps: return KEY_APPS; // not supported

// 		// case XK_sleep: return KEY_SLEEP; //not supported

// 	case XK_KP_0:
// 		return KEY_NUMPAD0;
// 	case XK_KP_1:
// 		return KEY_NUMPAD1;
// 	case XK_KP_2:
// 		return KEY_NUMPAD2;
// 	case XK_KP_3:
// 		return KEY_NUMPAD3;
// 	case XK_KP_4:
// 		return KEY_NUMPAD4;
// 	case XK_KP_5:
// 		return KEY_NUMPAD5;
// 	case XK_KP_6:
// 		return KEY_NUMPAD6;
// 	case XK_KP_7:
// 		return KEY_NUMPAD7;
// 	case XK_KP_8:
// 		return KEY_NUMPAD8;
// 	case XK_KP_9:
// 		return KEY_NUMPAD9;
// 	case XK_multiply:
// 		return KEY_MULTIPLY;
// 	case XK_KP_Add:
// 		return KEY_ADD;
// 	case XK_KP_Separator:
// 		return KEY_SEPARATOR;
// 	case XK_KP_Subtract:
// 		return KEY_SUBTRACT;
// 	case XK_KP_Decimal:
// 		return KEY_DECIMAL;
// 	case XK_KP_Divide:
// 		return KEY_DIVIDE;
// 	case XK_F1:
// 		return KEY_F1;
// 	case XK_F2:
// 		return KEY_F2;
// 	case XK_F3:
// 		return KEY_F3;
// 	case XK_F4:
// 		return KEY_F4;
// 	case XK_F5:
// 		return KEY_F5;
// 	case XK_F6:
// 		return KEY_F6;
// 	case XK_F7:
// 		return KEY_F7;
// 	case XK_F8:
// 		return KEY_F8;
// 	case XK_F9:
// 		return KEY_F9;
// 	case XK_F10:
// 		return KEY_F10;
// 	case XK_F11:
// 		return KEY_F11;
// 	case XK_F12:
// 		return KEY_F12;
// 	case XK_F13:
// 		return KEY_F13;
// 	case XK_F14:
// 		return KEY_F14;
// 	case XK_F15:
// 		return KEY_F15;
// 	case XK_F16:
// 		return KEY_F16;
// 	case XK_F17:
// 		return KEY_F17;
// 	case XK_F18:
// 		return KEY_F18;
// 	case XK_F19:
// 		return KEY_F19;
// 	case XK_F20:
// 		return KEY_F20;
// 	case XK_F21:
// 		return KEY_F21;
// 	case XK_F22:
// 		return KEY_F22;
// 	case XK_F23:
// 		return KEY_F23;
// 	case XK_F24:
// 		return KEY_F24;

// 	case XK_Num_Lock:
// 		return KEY_NUMLOCK;
// 	case XK_Scroll_Lock:
// 		return KEY_SCROLL;

// 	case XK_KP_Equal:
// 		return KEY_NUMPAD_EQUAL;

// 	case XK_Shift_L:
// 		return KEY_LSHIFT;
// 	case XK_Shift_R:
// 		return KEY_RSHIFT;
// 	case XK_Control_L:
// 		return KEY_LCONTROL;
// 	case XK_Control_R:
// 		return KEY_RCONTROL;
// 	// case XK_Menu: return KEY_LMENU;
// 	case XK_Menu:
// 		return KEY_RMENU;

// 	case XK_semicolon:
// 		return KEY_SEMICOLON;
// 	case XK_plus:
// 		return KEY_PLUS;
// 	case XK_comma:
// 		return KEY_COMMA;
// 	case XK_minus:
// 		return KEY_MINUS;
// 	case XK_period:
// 		return KEY_PERIOD;
// 	case XK_slash:
// 		return KEY_SLASH;
// 	case XK_grave:
// 		return KEY_GRAVE;

// 	case XK_a:
// 	case XK_A:
// 		return KEY_A;
// 	case XK_b:
// 	case XK_B:
// 		return KEY_B;
// 	case XK_c:
// 	case XK_C:
// 		return KEY_C;
// 	case XK_d:
// 	case XK_D:
// 		return KEY_D;
// 	case XK_e:
// 	case XK_E:
// 		return KEY_E;
// 	case XK_f:
// 	case XK_F:
// 		return KEY_F;
// 	case XK_g:
// 	case XK_G:
// 		return KEY_G;
// 	case XK_h:
// 	case XK_H:
// 		return KEY_H;
// 	case XK_i:
// 	case XK_I:
// 		return KEY_I;
// 	case XK_j:
// 	case XK_J:
// 		return KEY_J;
// 	case XK_k:
// 	case XK_K:
// 		return KEY_K;
// 	case XK_l:
// 	case XK_L:
// 		return KEY_L;
// 	case XK_m:
// 	case XK_M:
// 		return KEY_M;
// 	case XK_n:
// 	case XK_N:
// 		return KEY_N;
// 	case XK_o:
// 	case XK_O:
// 		return KEY_O;
// 	case XK_p:
// 	case XK_P:
// 		return KEY_P;
// 	case XK_q:
// 	case XK_Q:
// 		return KEY_Q;
// 	case XK_r:
// 	case XK_R:
// 		return KEY_R;
// 	case XK_s:
// 	case XK_S:
// 		return KEY_S;
// 	case XK_t:
// 	case XK_T:
// 		return KEY_T;
// 	case XK_u:
// 	case XK_U:
// 		return KEY_U;
// 	case XK_v:
// 	case XK_V:
// 		return KEY_V;
// 	case XK_w:
// 	case XK_W:
// 		return KEY_W;
// 	case XK_x:
// 	case XK_X:
// 		return KEY_X;
// 	case XK_y:
// 	case XK_Y:
// 		return KEY_Y;
// 	case XK_z:
// 	case XK_Z:
// 		return KEY_Z;

// 	default:
// 		return (keys)0;
// 	}
// }

// Put keybord keys true if pressed, false if not.
typedef struct keyboardState
{
	bl8	keys[256];
}	keyboardState;

// Mouse buttons are true if pressed, false if not.
// Mouse position is in screen coordinates.
typedef struct mouseState
{
	sint16 x;
	sint16 y;
	uint8 buttons[BUTTON_MAX_BUTTONS];
}	mouseState;

// Input state structure.
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
	DE_MemSet(&state, sizeof(inputState));
	initialized = true;
	DE_INFO("Input subsystem ready.");
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
		return ;
	}

	// Copy current mouse and keyboard states to previous states.
	DE_CopyMemory(&state.keyboard_previous, &state.keyboard_current, sizeof(keyboardState));
	DE_CopyMemory(&state.mouse_previous, &state.mouse_current, sizeof(mouseState));
}

void	OnKeyProcess(keys key, bl8 pressed)
{
	DE_DEBUG("OnKeyProcess: Key#: %d key: %c pressed: %d", key, key, pressed);
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

void	OnMouseButtonPress(mouseButtons button, bl8 pressed)
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

bl8		OnKeyDown(keys key)
{
	if (!initialized)
	{
		return false;
	}
	return state.keyboard_current.keys[key] == true;
}

bl8		OnKeyUP(keys key)
{
	if (!initialized)
	{
		return true;
	}
	return state.keyboard_current.keys[key] == false;
}

bl8		OnKeyPress(keys key)
{
	if (!initialized)
	{
		return false;
	}
	return state.keyboard_previous.keys[key] == true;
}

bl8		OnKeyRelease(keys key)
{
	if (!initialized)
	{
		return true;
	}
	return state.keyboard_previous.keys[key] == false;
}

// mouse input
bl8		OnMouseButtonDown(mouseButtons button)
{
	if (!initialized)
	{
		return false;
	}
	return state.mouse_current.buttons[button] == true;
}

bl8		OnMouseButtonUp(mouseButtons button)
{
	if (!initialized)
	{
		return true;
	}
	return state.mouse_current.buttons[button] == false;
}

bl8		OnMouseButtonPress(mouseButtons button)
{
	if (!initialized)
	{
		return false;
	}
	return state.mouse_previous.buttons[button] == true;
}

bl8		OnMouseButtonRelease(mouseButtons button)
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
