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

#include "defines.hpp"

// For send short code message to the event system.
// short messages = faster program.
typedef struct eventContext 
{
	// 128 bytes
	union {
		sint64	i64[2];
		uint64	u64[2];
		dbl64	f64[2];

		sint32	i32[4];
		uint32	u32[4];
		fl32	f32[4];

		sint16	i16[8];
		uint16	u16[8];

		sint8	i8[16];
		uint8	u8[16];

		char	c[16];
	}	data;
} eventContext;

// Listener callback function pointer.
// Should return true if handled.
typedef bl8	(*EventPointer)(uint16 code, void *sender, void *listenerInst, eventContext data);

bl8		EventInit(void);
void	EventShutdown(void);

/**
 * Register to listen for new events
 * @param code The event code to listen for.
 * @param listener A pointer to a listener instance. Can be 0/NULL.
 * @param on_event The callback function pointer to be invoked when the event code is fired.
 * @returns TRUE if the event is successfully registered; otherwise false.
 */
DE_API bl8	EventRegister(uint16 code, void* listener, EventPointer pntEvent);

/**
 * Unregister from listening for when events are sent with the provided code. If no matching
 * registration is found, this function returns FALSE.
 * @param code The event code to stop listening for.
 * @param listener A pointer to a listener instance. Can be 0/NULL.
 * @param onEvent The callback function pointer to be unregistered.
 * @returns TRUE if the event is successfully unregistered; otherwise false.
 */
DE_API bl8	EventUnregister(uint16 code, void* listener, EventPointer onEvent);

/**
 * Fires an event to listeners of the given code. If an event handler returns 
 * TRUE, the event is considered handled and is not passed on to any more listeners.
 * @param code The event code to fire.
 * @param sender A pointer to the sender. Can be 0/NULL.
 * @param data The event data.
 * @returns TRUE if handled, otherwise FALSE.
 */
DE_API bl8	EventFire(uint16 code, void* sender, eventContext context);

// System internal event codes. Application should use codes beyond 255.
typedef enum systemEventCode
{
	// Shuts the application down on the next frame.
	DE_EVENT_CODE_APPLICATION_QUIT = 0x01,

	// Keyboard key pressed.
	/* Context usage:
	 * uint16 keyCode = data.data.u16[0];
	 */
	DE_EVENT_CODE_KEY_PRESSED = 0x02,

	// Keyboard key released.
	/* Context usage:
	 * uint16 keyCode = data.data.u16[0];
	 */
	DE_EVENT_CODE_KEY_RELEASED = 0x03,

	// Mouse button pressed.
	/* Context usage:
	 * uint16 button = data.data.u16[0];
	 */
	DE_EVENT_CODE_BUTTON_PRESSED = 0x04,

	// Mouse button released.
	/* Context usage:
	 * u16 button = data.data.u16[0];
	 */
	DE_EVENT_CODE_BUTTON_RELEASED = 0x05,

	// Mouse moved.
	/* Context usage:
	 * uint16 x = data.data.u16[0];
	 * uint16 y = data.data.u16[1];
	 */
	DE_EVENT_CODE_MOUSE_MOVED = 0x06,

	// Mouse moved.
	/* Context usage:
	 * uint8 deltaZ = data.data.u8[0];
	 */
	DE_EVENT_CODE_MOUSE_WHEEL = 0x07,

	// Resized/resolution changed from the OS.
	/* Context usage:
	 * uint16 width = data.data.u16[0];
	 * uint16 height = data.data.u16[1];
	 */
	DE_EVENT_CODE_RESIZED = 0x08,

	DE_MAX_EVENT_CODE = 0xFF
}	systemEventCode;

#endif
