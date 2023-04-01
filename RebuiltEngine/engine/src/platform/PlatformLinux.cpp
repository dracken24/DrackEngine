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

#include "platform/Platform.hpp"

#if DE_PLATFORM_LINUX

# include "core/logger.hpp"
# include "core/input.hpp"
# include "core/event.hpp"
# include "color.hpp"
# include "renderer/vulkan/vulkanTypes.inl"

#include "container/myArray.hpp"
#include "core/deString.hpp"

# include <xcb/xcb.h>
# include <X11/keysym.h>
# include <X11/XKBlib.h>  // sudo apt-get install libx11-dev
# include <X11/Xlib.h>
# include <X11/Xlib-xcb.h>  // sudo apt-get install libxkbcommon-x11-dev

// For surface creation
# define VK_USE_PLATFORM_XCB_KHR
# include <vulkan/vulkan.h>
# include <vulkan/vulkan_xcb.h>

# include <sys/time.h>
# include <iostream>
# include <string>

# if _POSIX_C_SOURCE >= 199309L
#  include <time.h>   // for nanosleep
# else
#  include <unistd.h> // for usleep
# endif

struct vulkanContext;

	typedef struct internalState
{
	Display		        *display; // Connection to the Xlib server
	xcb_connection_t	*connection;
	xcb_window_t        window;
	xcb_screen_t        *screen;
	xcb_atom_t          wmProtocols;
	xcb_atom_t          wmDeleteWindow;
	VkSurfaceKHR		surface;
}	internalState;

// Key translation
keys	TranslateKeycode(uint32 x_keycode);

//****************************************************************************//
//**       						Constructors                            	**//
//****************************************************************************//

Platform::Platform(void)
{
	
}

Platform::~Platform(void)
{
	
}

//****************************************************************************//
//**       						PUBLIC METHODS                          	**//
//****************************************************************************//

// Platform states
bl8 	Platform::PlatformStart(PlatformState	*platform, std::string appName,
			Vector2si position, Vector2si size)
{
	// Create the internal state
	platform->intetnalState = new internalState;
	internalState *state = (internalState *)platform->intetnalState;

	// Connect to the Xlib server
	state->display = XOpenDisplay(NULL);

	// WARNING: Turn off keyboard autorepeat "WARNING" *Disable for entire OS*
	// Need to turn it back on when the program exits
	XAutoRepeatOff(state->display);

	// Retrieve the connexions for the display
	state->connection = XGetXCBConnection(state->display);

	if (xcb_connection_has_error(state->connection))
	{
		DE_FATAL("Failed to connect to X server via XCB"); 

		return (false);
	}

	// Get data from the X server
	const struct xcb_setup_t *setup = xcb_get_setup(state->connection);

	// Get the available screen
	xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
	int screenP = 0;
	for (sint32 i = screenP; i > 0; --i)
	{
		xcb_screen_next(&iter);
	}

	// Get the screen
	state->screen = iter.data;

	// Allocate a XID for the window
	state->window = xcb_generate_id(state->connection);

	// Register events types
	// XCB_CW_BACK_PIXEL : The background color of the window
	// XCB_CW_EVENT_MASK : The events that the window will receive
	uint32  eventMask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;

	// List of events handled by this program
	uint32 eventValues =	XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE |
							XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE |
							XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_POINTER_MOTION |
							XCB_EVENT_MASK_STRUCTURE_NOTIFY;
	
	// Values send over XCB "background color" and "event mask"
	uint32 valueList[] = { state->screen->black_pixel, eventValues };

	// Create the window
	xcb_void_cookie_t cookie = xcb_create_window(
		state->connection,				// Connection
		XCB_COPY_FROM_PARENT,			// Depth
		state->window,					// Window ID
		state->screen->root,			// Parent window
		position.x,						// X position of the window
		position.y,						// Y position of the window
		size.x,							// Width of the window
		size.y,							// Height of the window
		0,								// Border width
		XCB_WINDOW_CLASS_INPUT_OUTPUT,	// Class
		state->screen->root_visual,		// Visual
		eventMask,						// Event mask
		valueList);						// Value list

	// Change the window title
	xcb_change_property(
		state->connection,				// Connection
		XCB_PROP_MODE_REPLACE,			// Mode
		state->window,					// Window
		XCB_ATOM_WM_NAME,				// Property
		XCB_ATOM_STRING,				// Type
		8,								// Size of the data in bits
		appName.size(),					// Length of the data
		appName.c_str());				// Data

	// Tell the X server to notify us when the massger windows
	// attempts to kill the window
	xcb_intern_atom_cookie_t wm_delete_cookie = xcb_intern_atom(
		state->connection, 0, 16, "WM_DELETE_WINDOW");

	xcb_intern_atom_cookie_t wm_protocols_cookie = xcb_intern_atom(
		state->connection, 0, 12, "WM_PROTOCOLS");

	xcb_intern_atom_reply_t *wm_delete_reply = xcb_intern_atom_reply(
		state->connection, wm_delete_cookie, nullptr);

	xcb_intern_atom_reply_t *wm_protocols_reply = xcb_intern_atom_reply(
		state->connection, wm_protocols_cookie, nullptr);

	state->wmDeleteWindow = wm_delete_reply->atom;
	state->wmProtocols = wm_protocols_reply->atom;

	// Callback
	xcb_change_property(
		state->connection,
		XCB_PROP_MODE_REPLACE,
		state->window,
		state->wmProtocols,
		4,
		32,
		1,
		&state->wmDeleteWindow);

	// Map the window on the screen
	xcb_map_window(state->connection, state->window);

	// Flush the connection to the X server
	sint32 error = xcb_flush(state->connection);
	if (error <= 0)
	{
		DE_FATAL("Failed to flush the connection to the X server, error: %d", error);

		return (false);
	}

	return (true);
}

void	Platform::PlatformShutdown(PlatformState	*platform)
{
	internalState *state = (internalState *)platform->intetnalState;

	// Turn key autorepeat back on
	XAutoRepeatOn(state->display);

	xcb_destroy_window(state->connection, state->window);
}

bl8		Platform::PlatformUpdate(PlatformState	*platform)
{
	internalState *state = (internalState *)platform->intetnalState;

	xcb_generic_event_t *event;
	xcb_client_message_event_t *cm;

	bl8 quit = false;

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
			xcb_key_press_event_t *xcbEvent = (xcb_key_press_event_t *)event;
			bl8 pressed = event->response_type == XCB_KEY_PRESS;
			xcb_keycode_t code = xcbEvent->detail;
			
			KeySym key_sym = XkbKeycodeToKeysym(
				state->display,
				(KeyCode)code, // event.xkey.keycode,
				0,
				code & ShiftMask ? 1 : 0);

			keys key = TranslateKeycode(key_sym);

			// Pass to the input subsystem for processing.
			OnKeyProcess(key, pressed);

			switch (key)
			{
			case KEY_ESCAPE: // Quit on escape
				if (pressed)
				{
					quit = true;
				}
				break;
				default:
					break;
			}

		}
			break;
		case XCB_BUTTON_PRESS:
		case XCB_BUTTON_RELEASE:
		{
			xcb_button_press_event_t *mouseEvent = (xcb_button_press_event_t *)event;
			bl8 pressed = event->response_type == XCB_BUTTON_PRESS;
			mouseButtons mouseButton = BUTTON_MAX_BUTTONS;

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
				OnMouseButtonPress(mouseButton, pressed);
				DE_DEBUG("Mouse button: %d, pressed: %d", mouseButton, pressed);
				DE_DEBUG("Mouse position: X: %d, Y: %d", mouseEvent->event_x, mouseEvent->event_y);
			}
		}
			break;
		case XCB_MOTION_NOTIFY:
		{
			// Mouse move
			xcb_motion_notify_event_t *moveEvent = (xcb_motion_notify_event_t *)event;

			// Pass over to the input subsystem.
			OnMouseMove(moveEvent->event_x, moveEvent->event_y);
			DE_DEBUG("Mouse move: X: %d, Y: %d", moveEvent->event_x, moveEvent->event_y);
		}
			break;
		case XCB_CONFIGURE_NOTIFY:
		{
			DE_DEBUG("Window resize/move");
			// TODO: Resizing
		}
			break;

		case XCB_CLIENT_MESSAGE:
		{
			cm = (xcb_client_message_event_t *)event;
			DE_DEBUG("Client message");
			// Window close
			if (cm->data.data32[0] == state->wmDeleteWindow)
			{
				quit = true;
			}
		}
			break;
		default:
			// Something else
			break;
		}

		free(event);
	}
	return !quit;
}

// Dealing with memory

void *Platform::PlatformAllocator(uint64 size, bl8 align)
{
	DE_DEBUG("Allocating %d bytes", size);
	return (malloc(size));
}

// template <typename T>
void	Platform::PlatformFree(void *memPtr, bl8 align)
{
	std::free(memPtr);
}

void	*Platform::PlatZeroMem(void *memPtr, uint64 size)
{
	return (std::memset(memPtr, 0, size));
}

void	*Platform::PlatCopyMem(void *destPtr, const void *srcPtr, uint64 size)
{
	return (std::memcpy(destPtr, srcPtr, size));
}

void	*Platform::PlatSetMem(void *drstPtr, sint32 value, uint64 size)
{
	return (std::memset(drstPtr, value, size));
}

// Dealing with messages

void	Platform::PlatconsoleWrite(std::string str, uint8 color)
{
	std::string colorStr[] = { T_YELLOW, T_GREEN, T_BLUE, T_CYAN };

	std::cout << colorStr[color - 2] << str << T_RESET;
}

void	Platform::PlatconsoleWriteError(std::string str, uint8 color)
{
	std::string colorStr[] = { T_RED, T_RED };

	std::cout << colorStr[color] << str << T_RESET;
}

// Time

dbl64	Platform::PlatGetAbsoluteTime(void)
{
	struct timespec time;
	clock_gettime(CLOCK_MONOTONIC, &time);

	return (time.tv_sec + time.tv_nsec * 0.000000001);
}

void	Platform::PlatSleep(uint64 timeMs)
{
#if _POSIX_C_SOURCE >= 199309L
	struct timespec ts;
	ts.tv_sec = timeMs / 1000;
	ts.tv_nsec = (timeMs % 1000) * 1000 * 1000;
	nanosleep(&ts, &ts);
#else
	if (timeMs >= 1000)
		sleep(timeMs / 1000);
	usleep((timeMs % 1000) * 1000);
#endif
}

void	PlatformGetRequiredExtensionNames(const char ***namesArray)
{
	MyArrayPush(*namesArray, &"VK_KHR_xcb_surface"); // VK_KHR_xlib_surface?
}

// Surface creation for Vulkan
bl8		PlatformCreateVulkanSurface(PlatformState *platState, vulkanContext *context)
{
	// Simply cold-cast to the known type.
	internalState *state = (internalState *)platState->intetnalState;

	VkXcbSurfaceCreateInfoKHR create_info = {VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR};
	create_info.connection = state->connection;
	create_info.window = state->window;

	VkResult result = vkCreateXcbSurfaceKHR(
		context->instance,
		&create_info,
		context->allocator,
		&state->surface);
	if (result != VK_SUCCESS)
	{
		DE_FATAL("Vulkan surface creation failed.");
		return false;
	}

	context->surface = state->surface;
	return true;
}

// Key translation
keys TranslateKeycode(uint32 keyCode)
{
	switch (keyCode)
	{
	case XK_BackSpace:
		return KEY_BACKSPACE;
	case XK_Return:
		return KEY_ENTER;
	case XK_Tab:
		return KEY_TAB;
		// case XK_Shift: return KEY_SHIFT;
		// case XK_Control: return KEY_CONTROL;

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
		return KEY_LWIN; // TODO: not sure this is right
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
