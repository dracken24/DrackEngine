/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 25-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	  PlatformLinux.hpp       *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "platform.hpp"

// Linux platform layer.
#if DE_PLATFORM_LINUX

#include <core/logger.hpp>
#include <core/event.hpp>
#include <core/input.hpp>
#include <color.hpp>

#include "containers/arrayDinamic.hpp"

#include <xcb/xcb.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>  // sudo apt-get install libx11-dev
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>  // sudo apt-get install libxkbcommon-x11-dev
#include <sys/time.h>

#if _POSIX_C_SOURCE >= 199309L
#include <time.h>  // nanosleep
#else
#include <unistd.h>  // usleep
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string.h>

// For surface creation
#define VK_USE_PLATFORM_XCB_KHR
#include <vulkan/vulkan.h>
#include "renderer/vulkan/vulkanTypes.inl"

typedef struct	internalState
{
	Display*			display;
	xcb_connection_t*	connection;
	xcb_window_t		window;
	xcb_screen_t*		screen;
	xcb_atom_t			wmProtocols;
	xcb_atom_t			wmDeleteWin;
	VkSurfaceKHR		surface;
}	internalState;

// Key translation
keys	TranslateKeycode(uint32 x_keycode);

bl8		PlatformStartup(
			platformState* platState,
			const char* applicationName,
			sint32 x,
			sint32 y,
			sint32 width,
			sint32 height)
{
	// Create the internal state.
	platState->internalState = malloc(sizeof(internalState));
	internalState* state = (internalState*)platState->internalState;

	// Connect to X
	state->display = XOpenDisplay(NULL);

	// Turn off key repeats.
	XAutoRepeatOff(state->display);
	// XAutoRepeatOn(state->display);

	// Retrieve the connection from the display.
	state->connection = XGetXCBConnection(state->display);

	if (xcb_connection_has_error(state->connection))
	{
		DE_FATAL("Failed to connect to X server via XCB.");
		return false;
	}

	// Get data from the X server
	const struct xcb_setup_t* setup = xcb_get_setup(state->connection);

	// Loop through screens using iterator
	xcb_screen_iterator_t it = xcb_setup_roots_iterator(setup);
	int screenP = 0;
	for (sint32 s = screenP; s > 0; s--)
	{
		xcb_screen_next(&it);
	}

	// After screens have been looped through, assign it.
	state->screen = it.data;

	// Allocate a XID for the window to be created.
	state->window = xcb_generate_id(state->connection);

	// Register event types.
	// XCB_CW_BACK_PIXEL = filling then window bg with a single colour
	// XCB_CW_EVENT_MASK is required.
	uint32 eventMask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;

	// Listen for keyboard and mouse buttons
	uint32 eventValues = XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE |
		XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE |
		XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_POINTER_MOTION |
		XCB_EVENT_MASK_STRUCTURE_NOTIFY;

	// Values to be sent over XCB (bg colour, events)
	uint32 valueList[] = {state->screen->black_pixel, eventValues};

	// Create the window
	xcb_void_cookie_t cookie = xcb_create_window(
		state->connection,
		XCB_COPY_FROM_PARENT,  // depth
		state->window,
		state->screen->root,            // parent
		x,                              //x
		y,                              //y
		width,                          //width
		height,                         //height
		0,                              // No border
		XCB_WINDOW_CLASS_INPUT_OUTPUT,  //class
		state->screen->root_visual,
		eventMask,
		valueList);

	// Change the title
	xcb_change_property(
		state->connection,
		XCB_PROP_MODE_REPLACE,
		state->window,
		XCB_ATOM_WM_NAME,
		XCB_ATOM_STRING,
		8,  // data should be viewed 8 bits at a time
		strlen(applicationName),
		applicationName);

	// Tell the server to notify when the window manager
	// attempts to destroy the window.
	xcb_intern_atom_cookie_t wmDeleteCookie = xcb_intern_atom(state->connection, 0,
		strlen("wmDeleteWinDOW"), "wmDeleteWinDOW");
	xcb_intern_atom_cookie_t wmProtocolsCookie = xcb_intern_atom(state->connection, 0,
		strlen("wmProtocols"), "wmProtocols");
	xcb_intern_atom_reply_t *wmDeleteReply = xcb_intern_atom_reply(state->connection,
		wmDeleteCookie, NULL);
	xcb_intern_atom_reply_t *wmProtocolsReply = xcb_intern_atom_reply(state->connection,
		wmProtocolsCookie, NULL);

	state->wmDeleteWin = wmDeleteReply->atom;
	state->wmProtocols = wmProtocolsReply->atom;

	xcb_change_property(
		state->connection,
		XCB_PROP_MODE_REPLACE,
		state->window,
		wmProtocolsReply->atom,
		4,
		32,
		1,
		&wmProtocolsReply->atom);

	// Map the window to the screen
	xcb_map_window(state->connection, state->window);

	// Flush the stream
	sint32 streamResult = xcb_flush(state->connection);
	if (streamResult <= 0)
	{
		DE_FATAL("An error occurred when flusing the stream: %d", streamResult);
		return false;
	}

	return true;
}

void	PlatformShutdown(platformState* platState)
{
	// Simply cold-cast to the known type.
	internalState* state = (internalState*)platState->internalState;

	// WARNING:Turn key repeats back on since this is global for the OS... .
	XAutoRepeatOn(state->display);

	xcb_destroy_window(state->connection, state->window);
}

bl8		PlatformPumpMessages(platformState* platState)
{
	// Simply cold-cast to the known type.
	internalState* state = (internalState*)platState->internalState;

	xcb_generic_event_t* event;
	xcb_client_message_event_t* cm;

	bl8 quitFlagged = false;

	// Poll for events until null is returned.
	while (event != 0)
	{
		event = xcb_poll_for_event(state->connection);
		if (event == 0)
		{
			break;
		}

		// Input events
		switch (event->response_type & ~0x80)
		{
			case XCB_KEY_PRESS:
			case XCB_KEY_RELEASE:
			{
				// Key press event - xcb_key_press_event_t and xcb_key_release_event_t are the same
				xcb_key_press_event_t *kb_event = (xcb_key_press_event_t *)event;
				bl8 pressed = event->response_type == XCB_KEY_PRESS;
				xcb_keycode_t code = kb_event->detail;
				
				KeySym key_sym = XkbKeycodeToKeysym(
					state->display,
					(KeyCode)code,  //event.xkey.keycode,
					0,
					code & ShiftMask ? 1 : 0);

				keys key = TranslateKeycode(key_sym);

				// Pass to the input subsystem for processing.
				InputProcessKey(key, pressed);
			}
				break;

			// Mouse events
			case XCB_BUTTON_PRESS:
			case XCB_BUTTON_RELEASE:
			{
				xcb_button_press_event_t *mouseEvent = (xcb_button_press_event_t *)event;
				bl8 pressed = event->response_type == XCB_BUTTON_PRESS;
				buttons mouseButton = BUTTON_MAX_BUTTONS;

				switch (mouseEvent->detail)
				{
					case XCB_BUTTON_INDEX_1:
						mouseButton = BUTTON_LEFT;
						break;
					case XCB_BUTTON_INDEX_2:
						mouseButton = BUTTON_MIDDLE;
						break;
					case XCB_BUTTON_INDEX_3:
						mouseButton = BUTTON_RIGHT;
						break;
				}

				// Pass over to the input subsystem.
				if (mouseButton != BUTTON_MAX_BUTTONS)
				{
					DE_InputProcessButton(mouseButton, pressed);
				}

				// Mouse wheel
				if (mouseEvent->detail == XCB_BUTTON_INDEX_4)
				{
					// Mouse wheel up
					// DE_DEBUG("Mouse wheel up");
					DE_OnMouseWheel(1);
				}
				else if (mouseEvent->detail == XCB_BUTTON_INDEX_5)
				{
					// Mouse wheel down
					// DE_DEBUG("Mouse wheel down");
					DE_OnMouseWheel(-1);
				}
			}
				break;

			// Mouse move
			case XCB_MOTION_NOTIFY:
			{
				xcb_motion_notify_event_t *moveEvent = (xcb_motion_notify_event_t *)event;

				// Pass over to the input subsystem.
				DE_InputProcessMouseMove(moveEvent->event_x, moveEvent->event_y);
			}
				break;

			// Window events
			case XCB_CONFIGURE_NOTIFY:
			{
				// TODO: Resizing
				// DE_DEBUG("Resize me or move me, whatever...");

				xcb_configure_notify_event_t *resizeEvent = (xcb_configure_notify_event_t *)event;
				DE_OnWindowResize(resizeEvent->width, resizeEvent->height);
			}
				break;
			case XCB_CLIENT_MESSAGE:
			{
				cm = (xcb_client_message_event_t*)event;

				// Window close
				if (cm->data.data32[0] == state->wmDeleteWin)
				{
					quitFlagged = true;
				}
			}
				break;
			default:
				// Something else
				break;
		}

		free(event);
	}
	return !quitFlagged;
}

void*	PlatformAllocate(uint64 size, bl8 aligned)
{
	return malloc(size);
}
void	PlatformFree(void* block, bl8 aligned)
{
	free(block);
}

void*	PlatformSetMemory(void* block, uint64 size)
{
	return memset(block, 0, size);
}

void*	PlatformCopyMemory(void* dest, const void* source, uint64 size)
{
	return memcpy(dest, source, size);
}

void*	PlatformSetMemory(void* dest, sint32 value, uint64 size)
{

	return memset(dest, value, size);
}

void	PlatconsoleWrite(std::string message, uint8 color)
{
	// WARN,INFO,DEBUG,TRACE
	std::string colorStr[] = {T_YELLOW, T_GREEN, T_BLUE, T_CYAN};

	std::cout << colorStr[color - 2] << message << T_RESET;
}
void	PlatconsoleWriteError(std::string message, uint8 color)
{
	// FATAL,ERROR
	std::string colorStr[] = {T_RED, T_RED};

	std::cout << colorStr[color] << message << T_RESET;
}

dbl64	PlatformGetAbsoluteTime()
{
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);

	return now.tv_sec + now.tv_nsec * 0.000000001;
}

void	PlatformSleep(uint64 ms)
{
#if _POSIX_C_SOURCE >= 199309L
	struct timespec ts;
	ts.tv_sec = ms / 1000;
	ts.tv_nsec = (ms % 1000) * 1000 * 1000;
	nanosleep(&ts, 0);
#else
	if (ms >= 1000) {
		sleep(ms / 1000);
	}
	usleep((ms % 1000) * 1000);
#endif
}

void	PlatformGetRequiredExtensionNames(const char ***namesDarray)
{
	DE_ArrayPush(*namesDarray, &"VK_KHR_xcb_surface");  // VK_KHR_xlib_surface?
}

// Surface creation for Vulkan
bl8		PlatformCreateVulkanSurface(platformState *platState, vulkanContext *context)
{
	// Simply cold-cast to the known type.
	internalState *state = (internalState *)platState->internalState;

	VkXcbSurfaceCreateInfoKHR createInfo = {VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR};
	createInfo.connection = state->connection;
	createInfo.window = state->window;

	VkResult result = vkCreateXcbSurfaceKHR(context->instance, &createInfo,
						context->allocator, &state->surface);

	if (result != VK_SUCCESS)
	{
		DE_FATAL("Vulkan surface creation failed.");
		return false;
	}

	context->surface = state->surface;
	return true;
}

// Key translation
keys TranslateKeycode(uint32 xKeycode)
{
	switch (xKeycode)
	{
		case XK_BackSpace:
			return KEY_BACKSPACE;
		case XK_Return:
			return KEY_ENTER;
		case XK_Tab:
			return KEY_TAB;
			//case XK_Shift: return KEY_SHIFT;
			//case XK_Control: return KEY_CONTROL;

		case XK_Pause:
			return KEY_PAUSE;
		case XK_Caps_Lock:
			return KEY_CAPITAL;

		case XK_Escape:
			return KEY_ESCAPE;

			// Not supported
			// case : return KEY_CONVERT;
			// case : return KEY_NONCONVERT;
			// case : return KEY_ACCEPT;

		case XK_Mode_switch:
			return KEY_MODECHANGE;

		case XK_space:
			return KEY_SPACE;
		case XK_Prior:
			return KEY_PRIOR;
		case XK_Next:
			return KEY_NEXT;
		case XK_End:
			return KEY_END;
		case XK_Home:
			return KEY_HOME;
		case XK_Left:
			return KEY_LEFT;
		case XK_Up:
			return KEY_UP;
		case XK_Right:
			return KEY_RIGHT;
		case XK_Down:
			return KEY_DOWN;
		case XK_Select:
			return KEY_SELECT;
		case XK_Print:
			return KEY_PRINT;
		case XK_Execute:
			return KEY_EXECUTE;
		// case XK_snapshot: return KEY_SNAPSHOT; // not supported
		case XK_Insert:
			return KEY_INSERT;
		case XK_Delete:
			return KEY_DELETE;
		case XK_Help:
			return KEY_HELP;

		case XK_Meta_L:
			return KEY_LWIN;  // TODO: not sure this is right
		case XK_Meta_R:
			return KEY_RWIN;
			// case XK_apps: return KEY_APPS; // not supported

			// case XK_sleep: return KEY_SLEEP; //not supported

		case XK_KP_0:
			return KEY_NUMPAD0;
		case XK_KP_1:
			return KEY_NUMPAD1;
		case XK_KP_2:
			return KEY_NUMPAD2;
		case XK_KP_3:
			return KEY_NUMPAD3;
		case XK_KP_4:
			return KEY_NUMPAD4;
		case XK_KP_5:
			return KEY_NUMPAD5;
		case XK_KP_6:
			return KEY_NUMPAD6;
		case XK_KP_7:
			return KEY_NUMPAD7;
		case XK_KP_8:
			return KEY_NUMPAD8;
		case XK_KP_9:
			return KEY_NUMPAD9;
		case XK_multiply:
			return KEY_MULTIPLY;
		case XK_KP_Add:
			return KEY_ADD;
		case XK_KP_Separator:
			return KEY_SEPARATOR;
		case XK_KP_Subtract:
			return KEY_SUBTRACT;
		case XK_KP_Decimal:
			return KEY_DECIMAL;
		case XK_KP_Divide:
			return KEY_DIVIDE;
		case XK_F1:
			return KEY_F1;
		case XK_F2:
			return KEY_F2;
		case XK_F3:
			return KEY_F3;
		case XK_F4:
			return KEY_F4;
		case XK_F5:
			return KEY_F5;
		case XK_F6:
			return KEY_F6;
		case XK_F7:
			return KEY_F7;
		case XK_F8:
			return KEY_F8;
		case XK_F9:
			return KEY_F9;
		case XK_F10:
			return KEY_F10;
		case XK_F11:
			return KEY_F11;
		case XK_F12:
			return KEY_F12;
		case XK_F13:
			return KEY_F13;
		case XK_F14:
			return KEY_F14;
		case XK_F15:
			return KEY_F15;
		case XK_F16:
			return KEY_F16;
		case XK_F17:
			return KEY_F17;
		case XK_F18:
			return KEY_F18;
		case XK_F19:
			return KEY_F19;
		case XK_F20:
			return KEY_F20;
		case XK_F21:
			return KEY_F21;
		case XK_F22:
			return KEY_F22;
		case XK_F23:
			return KEY_F23;
		case XK_F24:
			return KEY_F24;

		case XK_Num_Lock:
			return KEY_NUMLOCK;
		case XK_Scroll_Lock:
			return KEY_SCROLL;

		case XK_KP_Equal:
			return KEY_NUMPAD_EQUAL;

		case XK_Shift_L:
			return KEY_LSHIFT;
		case XK_Shift_R:
			return KEY_RSHIFT;
		case XK_Control_L:
			return KEY_LCONTROL;
		case XK_Control_R:
			return KEY_RCONTROL;
		// case XK_Menu: return KEY_LMENU;
		case XK_Menu:
			return KEY_RMENU;

		case XK_semicolon:
			return KEY_SEMICOLON;
		case XK_plus:
			return KEY_PLUS;
		case XK_comma:
			return KEY_COMMA;
		case XK_minus:
			return KEY_MINUS;
		case XK_period:
			return KEY_PERIOD;
		case XK_slash:
			return KEY_SLASH;
		case XK_grave:
			return KEY_GRAVE;

		case XK_a:
		case XK_A:
			return KEY_A;
		case XK_b:
		case XK_B:
			return KEY_B;
		case XK_c:
		case XK_C:
			return KEY_C;
		case XK_d:
		case XK_D:
			return KEY_D;
		case XK_e:
		case XK_E:
			return KEY_E;
		case XK_f:
		case XK_F:
			return KEY_F;
		case XK_g:
		case XK_G:
			return KEY_G;
		case XK_h:
		case XK_H:
			return KEY_H;
		case XK_i:
		case XK_I:
			return KEY_I;
		case XK_j:
		case XK_J:
			return KEY_J;
		case XK_k:
		case XK_K:
			return KEY_K;
		case XK_l:
		case XK_L:
			return KEY_L;
		case XK_m:
		case XK_M:
			return KEY_M;
		case XK_n:
		case XK_N:
			return KEY_N;
		case XK_o:
		case XK_O:
			return KEY_O;
		case XK_p:
		case XK_P:
			return KEY_P;
		case XK_q:
		case XK_Q:
			return KEY_Q;
		case XK_r:
		case XK_R:
			return KEY_R;
		case XK_s:
		case XK_S:
			return KEY_S;
		case XK_t:
		case XK_T:
			return KEY_T;
		case XK_u:
		case XK_U:
			return KEY_U;
		case XK_v:
		case XK_V:
			return KEY_V;
		case XK_w:
		case XK_W:
			return KEY_W;
		case XK_x:
		case XK_X:
			return KEY_X;
		case XK_y:
		case XK_Y:
			return KEY_Y;
		case XK_z:
		case XK_Z:
			return KEY_Z;

		default:
			return (keys)0;
	}
}

#endif
