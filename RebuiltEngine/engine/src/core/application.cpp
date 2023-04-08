/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 25-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	      core.cpp            *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include <core/application.hpp>
#include <gameTypes.hpp>

#include <core/logger.hpp>

#include <platform/platform.hpp>
#include <core/deMemory.hpp>
#include <core/event.hpp>
#include <core/input.hpp>
#include <core/timer.hpp>
#include <structs.hpp>
#include <renderer/vulkan/vulkanBackend.hpp>

#include <xcb/xcb.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h> // sudo apt-get install libx11-dev
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h> // sudo apt-get install libxkbcommon-x11-dev

#include <renderer/rendererFrontend.hpp>

typedef struct applicationState
{
	game*			gameInst;
	bl8				isRunning;
	bl8				isSuspended;
	platformState	platform;
	sint16			width;
	sint16			height;
	Timer			timer;
	dbl64			lastTime;
} applicationState;

static bl8 initialized = false;
static applicationState appState;

static Vector2ui		mousePosition;
static fl32				mouseZoom = 0;
static Vector2ui16		screenSize;
static Vector2ui16		screenPos;

static Renderer			backend;

// Event handlers
bl8		ApplicationOnEvent(uint16 code, void* sender, void* listenerInst, eventContext context);
bl8		ApplicationOnKey(uint16 code, void* sender, void* listenerInst, eventContext context);
bl8		ApplicationOnMouseMove(uint16 code, void* sender, void* listenerInst, eventContext context);
bl8		ApplicationOnButton(uint16 code, void* sender, void* listenerInst, eventContext context);
bl8		ApplicationOnMouseWheel(uint16 code, void *sender, void *listenerInst, eventContext context);
bl8		ApplicationOnResize(uint16 code, void *sender, void *listenerInst, eventContext context);

//*****************************************************************************//

bl8		ApplicationCreate(game *gameInst)
{
	screenSize.x = gameInst->appConfig.width;
	screenSize.y = gameInst->appConfig.height;
	screenPos.x = gameInst->appConfig.x;
	screenPos.y = gameInst->appConfig.y;

	if (initialized)
	{
		DE_ERROR("ApplicationCreate called more than once.");
		return false;
	}

	appState.gameInst = gameInst;

	// Initialize subsystems.
	LogInit();
	DE_InputInit();

	// TODO: remove when log message are fully implemented
	DE_FATAL("Hello World! %f", 1.0f);
	DE_ERROR("Hello World! %f", 1.0f);
	DE_WARNING("Hello World! %f", 1.0f);
	DE_INFO("Hello World! %f", 1.0f);
	DE_DEBUG("Hello World! %f", 1.0f);
	DE_TRACE("Hello World! %f lol %s", 1.0f, "test\n");

	appState.isRunning = true;
	appState.isSuspended = false;

	if(!EventInitialize())
	{
		DE_ERROR("Event system failed initialization. Application cannot continue.");
		return false;
	}

	EventRegister(EVENT_CODE_APPLICATION_QUIT, 0, ApplicationOnEvent);
	EventRegister(EVENT_CODE_KEY_PRESSED, 0, ApplicationOnKey);
	EventRegister(EVENT_CODE_KEY_RELEASED, 0, ApplicationOnKey);
	EventRegister(EVENT_CODE_BUTTON_PRESSED, 0, ApplicationOnButton);
	EventRegister(EVENT_CODE_BUTTON_RELEASED, 0, ApplicationOnButton);
	EventRegister(EVENT_CODE_MOUSE_MOVED, 0, ApplicationOnMouseMove);
	EventRegister(EVENT_CODE_MOUSE_WHEEL_UP, 0, ApplicationOnMouseWheel);
	EventRegister(EVENT_CODE_MOUSE_WHEEL_DOWN, 0, ApplicationOnMouseWheel);
	EventRegister(EVENT_CODE_RESIZED, 0, ApplicationOnResize);

	if (!PlatformStartup(
			&appState.platform,
			gameInst->appConfig.name.c_str(),
			gameInst->appConfig.x,
			gameInst->appConfig.y,
			gameInst->appConfig.width,
			gameInst->appConfig.height)) {
		return false;
	}

	// Init vulkan, frontend and backend
	if (!backend.RendererInit(gameInst->appConfig.name.c_str(), &appState.platform))
	{
		DE_FATAL("Failed to initialize renderer. Aborting application.");
		return false;
	}

	// Initialize the game.
	if (!appState.gameInst->initialize(appState.gameInst))
	{
		DE_FATAL("Game failed to initialize.");
		return false;
	}

	appState.gameInst->onResize(appState.gameInst, appState.width, appState.height);

	initialized = true;

	return true;
}

bl8		ApplicationRun(void)
{
	appState.timer.TimerStart();
	appState.timer.TimerUpdate();
	appState.lastTime = appState.timer._timer.elapsedTime;
	dbl64 running_time = 0;
	uint8 framesCount = 0;
	dbl64 target_FPS = 1.0f / 60;

	DE_INFO(GetMemoryUsageStr().c_str());

	while (appState.isRunning)
	{
		if (!PlatformPumpMessages(&appState.platform))
		{
			appState.isRunning = false;
		}

		if (!appState.isSuspended)
		{
			// Update timer and get delta time.
			appState.timer.TimerUpdate();
			dbl64 currentTime = appState.timer._timer.elapsedTime;
			dbl64 delta = (currentTime - appState.lastTime);
			dbl64 frameStartTime = PlatformGetAbsoluteTime();

			if (!appState.gameInst->update(appState.gameInst, (fl32)delta))
			{
				DE_FATAL("Game update failed, shutting down.");
				appState.isRunning = false;
				break;
			}

			// Call the game's render routine.
			if (!appState.gameInst->render(appState.gameInst, (fl32)delta))
			{
				DE_FATAL("Game render failed, shutting down.");
				appState.isRunning = false;
				break;
			}

			// TODO: refactor packet creation
			renderPacket packet;
			packet.deltaTime = delta;
			backend.RendererDrawFrame(&packet);

			// Figure out how long the frame took and, if below
			dbl64 frameEndTime = PlatformGetAbsoluteTime();
			dbl64 frameElapsedTime = frameEndTime - frameStartTime;
			running_time += frameElapsedTime;
			dbl64 remainingSeconds = target_FPS - frameElapsedTime;

			if (remainingSeconds > 0)
			{
				uint64 remaining_ms = (remainingSeconds * 1000);

				// If there is time left, give it back to the OS.
				// std::cout << "Frame: " << (int)framesCount << std::endl;
				bl8 limitFrames = true;
				if (remaining_ms > 0 && limitFrames)
				{
					PlatformSleep(remaining_ms - 1);
				}

				framesCount++;
			}

			// NOTE: Input update/state copying should always be handled
			// after any input should be recorded; I.E. before this line.
			// As a safety, input is the last thing to be updated before
			// this frame ends.
			DE_InputUpdate(delta);

			// Update last time
			appState.lastTime = currentTime;
		}
	}

	appState.isRunning = false;

	DE_DEBUG("Application shutting down.");
	// Shutdown event system.
	EventUnregister(EVENT_CODE_APPLICATION_QUIT, 0, ApplicationOnEvent);
	EventUnregister(EVENT_CODE_KEY_PRESSED, 0, ApplicationOnKey);
	EventUnregister(EVENT_CODE_KEY_RELEASED, 0, ApplicationOnKey);
	EventUnregister(EVENT_CODE_BUTTON_PRESSED, 0, ApplicationOnButton);
	EventUnregister(EVENT_CODE_BUTTON_RELEASED, 0, ApplicationOnButton);
	EventUnregister(EVENT_CODE_MOUSE_MOVED, 0, ApplicationOnMouseMove);
	EventUnregister(EVENT_CODE_MOUSE_WHEEL_UP, 0, ApplicationOnMouseWheel);
	EventUnregister(EVENT_CODE_MOUSE_WHEEL_DOWN, 0, ApplicationOnMouseWheel);
	EventUnregister(EVENT_CODE_RESIZED, 0, ApplicationOnResize);

	EventShutdown();
	DE_InputShutdown();

	DE_DEBUG("Shutting down game.");
	backend.RendererShutdown();

	DE_DEBUG("Shutting down platform.");
	PlatformShutdown(&appState.platform);

	DE_DEBUG("Application shutdown complete.");
	return true;
}

void	ApplicationGetFrameBufferSize(uint32 *width, uint32 *height)
{
	*width = appState.gameInst->appConfig.width;
	*height = appState.gameInst->appConfig.height;
}

bl8 ApplicationOnEvent(uint16 code, void* sender, void* listenerInst, eventContext context)
{
	DE_DEBUG("EVENT: %d", code);
	switch (code)
	{
		case EVENT_CODE_APPLICATION_QUIT:
		{
			DE_INFO("EVENT_CODE_APPLICATION_QUIT recieved, shutting down.\n");
			appState.isRunning = false;
			return true;
		}
	}

	return false;
}

bl8 ApplicationOnKey(uint16 code, void* sender, void* listenerInst, eventContext context)
{
	if (code == EVENT_CODE_KEY_PRESSED)
	{
		uint16 keyCode = context.data.uint16[0];
		if (keyCode == KEY_ESCAPE)
		{
			// NOTE: Technically firing an event to itself, but there may be other listeners.
			eventContext data = {};
			EventFire(EVENT_CODE_APPLICATION_QUIT, 0, data);

			// Block anything else from processing this.
			return true;
		}
		else
		{
			DE_DEBUG("'%c' key pressed in window.", keyCode);
		}
	}
	else if (code == EVENT_CODE_KEY_RELEASED)
	{
		uint16 keyCode = context.data.uint16[0];
		if (keyCode)
		{
			DE_DEBUG("'%c' key released in window.", keyCode);
		}
	}

	return false;
}

bl8		ApplicationOnButton(uint16 code, void* sender, void* listenerInst, eventContext context)
{
	DE_DEBUG("EVENT button: %d", code);
	if (code == EVENT_CODE_BUTTON_PRESSED)
	{
		uint16 keyCode = context.data.uint16[0];
		if (keyCode == BUTTON_LEFT)
		{
			DE_DEBUG("Left mouse button pressed position: X: %d Y:%d", mousePosition.x, mousePosition.y);
		}
		else if (keyCode == BUTTON_RIGHT)
		{
			DE_DEBUG("Right mouse button pressed position: X: %d Y:%d", mousePosition.x, mousePosition.y);
		}
		else if (keyCode == BUTTON_MIDDLE)
		{
			DE_DEBUG("Middle mouse button pressed position: X: %d Y:%d", mousePosition.x, mousePosition.y);
		}
	}

	if (code == EVENT_CODE_BUTTON_RELEASED)
	{
		uint16 keyCode = context.data.uint16[0];
		if (keyCode == BUTTON_LEFT)
		{
			DE_DEBUG("Left mouse button released position: X: %d Y:%d", mousePosition.x, mousePosition.y);
		}
		else if (keyCode == BUTTON_RIGHT)
		{
			DE_DEBUG("Right mouse button released position: X: %d Y:%d", mousePosition.x, mousePosition.y);
		}
		else if (keyCode == BUTTON_MIDDLE)
		{
			DE_DEBUG("Middle mouse button released position: X: %d Y:%d", mousePosition.x, mousePosition.y);
		}
	}

	return false;
}

bl8		ApplicationOnMouseMove(uint16 code, void *sender, void *listenerInst, eventContext context)
{
	if (code == EVENT_CODE_MOUSE_MOVED)
	{
		uint32 x = context.data.uint16[0];
		uint32 y = context.data.uint16[1];

		DE_DEBUG("Mouse moved to (X: %d, Y: %d).", x, y);
		mousePosition.x = x;
		mousePosition.y = y;
	}

	return false;
}

bl8		ApplicationOnMouseWheel(uint16 code, void *sender, void *listenerInst, eventContext context)
{
	if (code == EVENT_CODE_MOUSE_WHEEL_UP)
	{
		mouseZoom += 1.0f;
		DE_DEBUG("Mouse wheel up: %f.", mouseZoom);
	}
	else if (code == EVENT_CODE_MOUSE_WHEEL_DOWN)
	{
		mouseZoom -= 1.0f;
		DE_DEBUG("Mouse wheel down: %f.", mouseZoom);
	}

	return false;
}

bl8		ApplicationOnResize(uint16 code, void *sender, void *listenerInst, eventContext context)
{
	if (code == EVENT_CODE_RESIZED)
	{
		uint16 X = context.data.uint16[0];
		uint16 Y = context.data.uint16[1];

		// Check if different. If so, trigger a resize event.
		if (X != appState.width || Y != appState.height)
		{
			appState.width = X;
			appState.height = Y;

			DE_DEBUG("Window resize: %i, %i", X, Y);

			// Handle minimization
			if (X == 0 || Y == 0)
			{
				DE_INFO("Window minimized, suspending application.");
				appState.isSuspended = true;
				return true;
			}
			else
			{
				if (appState.isSuspended)
				{
					DE_INFO("Window restored, resuming application.");
					appState.isSuspended = false;
				}
				appState.gameInst->onResize(appState.gameInst, X, Y);
				backend.RendererOnResized(X, Y);
			}
		}
	}

	return false;
}

void	ApplicationGetFramebufferSize(uint32 *width, uint32 *height)
{
	*width = appState.width;
	*height = appState.height;
}
