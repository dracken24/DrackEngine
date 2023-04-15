/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 29-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	      event.hpp           *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef EVENT_HPP
# define EVENT_HPP

# include "defines.hpp"

typedef struct eventContext
{
	// 128 bytes
	union {
		sint64	sint64[2];
		uint64	uint64[2];
		dbl64	dbl64[2];

		sint32	sint32[4];
		uint32	uint32[4];
		fl32	fl32[4];

		sint16	sint16[8];
		uint16	uint16[8];

		sint8	sint8[16];
		uint8	uint8[16];

		char	c[16];
	}	data;
}	eventContext;

// Should return true if handled.
typedef bl8	(*eventPtr)(uint16 code, void* sender, void* listenerInst, eventContext data);

bl8		EventInitialize(uint64 *memoryRequirement, void *state);
void	EventShutdown(void* state);

/**
 * Register to listen for when events are sent with the provided code. Events with duplicate
 * listener/callback combos will not be registered again and will cause this to return false.
 * @param code The event code to listen for.
 * @param listener A pointer to a listener instance. Can be 0/NULL.
 * @param onEvent The callback function pointer to be invoked when the event code is fired.
 * @returns true if the event is successfully registered; otherwise false.
 */
DE_API bl8	EventRegister(uint16 code, void* listener, eventPtr onEvent);

/**
 * Unregister from listening for when events are sent with the provided code. If no matching
 * registration is found, this function returns false.
 * @param code The event code to stop listening for.
 * @param listener A pointer to a listener instance. Can be 0/NULL.
 * @param onEvent The callback function pointer to be unregistered.
 * @returns true if the event is successfully unregistered; otherwise false.
 */
DE_API bl8	EventUnregister(uint16 code, void* listener, eventPtr onEvent);

/**
 * Fires an event to listeners of the given code. If an event handler returns 
 * true, the event is considered handled and is not passed on to any more listeners.
 * @param code The event code to fire.
 * @param sender A pointer to the sender. Can be 0/NULL.
 * @param data The event data.
 * @returns true if handled, otherwise false.
 */
DE_API bl8	EventFire(uint16 code, void* sender, eventContext context);

// System internal event codes. Application should use codes beyond 255.
typedef enum systemEventCode
{
	// Shuts the application down on the next frame.
	EVENT_CODE_APPLICATION_QUIT = 0x01,

	// Keyboard key pressed.
	/* Context usage:
	 * uint16 keyCode = data.data.uint16[0];
	 */
	EVENT_CODE_KEY_PRESSED = 0x02,

	// Keyboard key released.
	/* Context usage:
	 * uint16 keyCode = data.data.uint16[0];
	 */
	EVENT_CODE_KEY_RELEASED = 0x03,

	// Mouse button pressed.
	/* Context usage:
	 * uint16 button = data.data.uint16[0];
	 */
	EVENT_CODE_BUTTON_PRESSED = 0x04,

	// Mouse button released.
	/* Context usage:
	 * uint16 button = data.data.uint16[0];
	 */
	EVENT_CODE_BUTTON_RELEASED = 0x05,

	// Mouse moved.
	/* Context usage:
	 * uint16 x = data.data.uint16[0];
	 * uint16 y = data.data.uint16[1];
	 */
	EVENT_CODE_MOUSE_MOVED = 0x06,

	// Mouse moved.
	/* Context usage:
	 * uint8 z_delta = data.data.uint8[0];
	 */
	EVENT_CODE_MOUSE_WHEEL_UP = 0x07,
	EVENT_CODE_MOUSE_WHEEL_DOWN = 0x08,

	// Resized/resolution changed from the OS.
	/* Context usage:
	* uint16 width = data.data.uint16[0];
	* uint16 height = data.data.uint16[1];
	*/
	EVENT_CODE_RESIZED = 0x09,

	// Window moved.
	/* Context usage:
	* uint16 x = data.data.uint16[0];
	* uint16 y = data.data.uint16[1];
	*/
	EVENT_CODE_WINDOW_MOVE = 0x0A,

	MAX_EVENT_CODE = 0xFF
} systemEventCode;

#endif // EVENT_HPP
