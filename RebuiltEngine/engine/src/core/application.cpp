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

#include <renderer/vulkan/vulkanBackend.hpp>

#include <renderer/rendererFrontend.hpp>

#include <platform/platform.hpp>

#include <core/application.hpp>
#include <core/deMemory.hpp>
#include <core/logger.hpp>
#include <core/event.hpp>
#include <core/input.hpp>
#include <core/timer.hpp>

#include <math/structs.hpp>

#include <gameTypes.hpp>

#include <xcb/xcb.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h> // sudo apt-get install libx11-dev
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h> // sudo apt-get install libxkbcommon-x11-dev


// static bl8 initialized = false;
applicationState *appliState = new applicationState;

static Vector2			mousePosition;
static fl32				mouseZoom = 0;
static Vector2			screenSize;
static Vector2			screenPos;

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
	DE_WARNING("ApplicationCreate called.1");
	if (gameInst->appState)
	{
		DE_ERROR("ApplicationCreate called more than once.");
		return false;
	}
	DE_WARNING("ApplicationCreate called.2");

	gameInst->appState = Mallocate(sizeof(applicationState), DE_MEMORY_TAG_APPLICATION);
	appliState = (applicationState *)gameInst->appState;
	appliState->gameInst = gameInst;

	// 64 mb of memory reserved for the allocator
	uint32	systemTotalAllocatorSize = 64 * 1024 * 1024;
	appliState->systemAllocator._memory = Mallocate(systemTotalAllocatorSize, DE_MEMORY_TAG_APPLICATION);

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

	appliState->isRunning = true;
	appliState->isSuspended = false;

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
			&appliState->platform,
			gameInst->appConfig.name.c_str(),
			gameInst->appConfig.x,
			gameInst->appConfig.y,
			gameInst->appConfig.width,
			gameInst->appConfig.height)) {
		return false;
	}

	// Init vulkan, frontend and backend
	if (!backend.RendererInit(gameInst->appConfig.name.c_str(), &appliState->platform))
	{
		DE_FATAL("Failed to initialize renderer. Aborting application.");
		return false;
	}

	// Initialize the game.
	if (!appliState->gameInst->initialize(appliState->gameInst))
	{
		DE_FATAL("Game failed to initialize.");
		return false;
	}

	appliState->gameInst->onResize(appliState->gameInst, appliState->width, appliState->height);

	// initialized = true;

	return true;
}

bl8		ApplicationRun(void)
{
	appliState->timer.TimerStart();
	appliState->timer.TimerUpdate();
	appliState->lastTime = appliState->timer._timer.elapsedTime;
	dbl64 running_time = 0;
	uint8 framesCount = 0;
	dbl64 target_FPS = 1.0f / 60;

	DE_INFO(GetMemoryUsageStr().c_str());

	int i = 0;
	while (appliState->isRunning)
	{
		if (!PlatformPumpMessages(&appliState->platform))
		{
			appliState->isRunning = false;
		}

		if (!appliState->isSuspended)
		{
			// Update timer and get delta time.
			appliState->timer.TimerUpdate();
			dbl64 currentTime = appliState->timer._timer.elapsedTime;
			dbl64 delta = (currentTime - appliState->lastTime);
			dbl64 frameStartTime = PlatformGetAbsoluteTime();

			if (!appliState->gameInst->update(appliState->gameInst, (fl32)delta))
			{
				DE_FATAL("Game update failed, shutting down.");
				appliState->isRunning = false;
				break;
			}

			// Call the game's render routine.
			if (!appliState->gameInst->render(appliState->gameInst, (fl32)delta))
			{
				DE_FATAL("Game render failed, shutting down.");
				appliState->isRunning = false;
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
			appliState->lastTime = currentTime;
		}
	}

	appliState->isRunning = false;

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
	PlatformShutdown(&appliState->platform);

	delete appliState;

	DE_DEBUG("Application shutdown complete.");
	return true;
}

void	ApplicationGetFrameBufferSize(uint32 *width, uint32 *height)
{
	*width = appliState->gameInst->appConfig.width;
	*height = appliState->gameInst->appConfig.height;
}

bl8 ApplicationOnEvent(uint16 code, void* sender, void* listenerInst, eventContext context)
{
	DE_DEBUG("EVENT: %d", code);
	switch (code)
	{
		case EVENT_CODE_APPLICATION_QUIT:
		{
			DE_INFO("EVENT_CODE_APPLICATION_QUIT recieved, shutting down.\n");
			appliState->isRunning = false;
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
		// DE_DEBUG("Code: %d, keyCode: %d", code, keyCode);
		if (keyCode == KEY_ESCAPE)
		{
			// NOTE: Technically firing an event to itself, but there may be other listeners.
			eventContext data = {};
			EventFire(EVENT_CODE_APPLICATION_QUIT, 0, data);

			// Block anything else from processing this.
			return true;
		}
		if (keyCode == KEY_TOP_1)
		{
			appliState->gameInst->bgColor.r += 0.1f;
		}
		if (keyCode == KEY_TOP_2)
		{
			appliState->gameInst->bgColor.r -= 0.1f;
		}
		if (keyCode == KEY_TOP_3)
		{
			appliState->gameInst->bgColor.g += 0.1f;
		}
		if (keyCode == KEY_TOP_4)
		{
			appliState->gameInst->bgColor.g -= 0.1f;
		}
		if (keyCode == KEY_TOP_5)
		{
			appliState->gameInst->bgColor.b += 0.1f;
		}
		if (keyCode == KEY_TOP_6)
		{
			appliState->gameInst->bgColor.b -= 0.1f;
		}

		DE_DEBUG("'%c' key pressed in window.", keyCode);
	}
	// else if (code == EVENT_CODE_KEY_RELEASED)
	// {
	// 	uint16 keyCode = context.data.uint16[0];
	// 	if (keyCode)
	// 	{
	// 		DE_DEBUG("'%c' key released in window.", keyCode);
	// 	}
	// }

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
			DE_DEBUG("Left mouse button pressed position: X: %.2f Y:%.2f", mousePosition.x, mousePosition.y);
		}
		else if (keyCode == BUTTON_RIGHT)
		{
			DE_DEBUG("Right mouse button pressed position: X: %.2f Y:%.2f", mousePosition.x, mousePosition.y);
		}
		else if (keyCode == BUTTON_MIDDLE)
		{
			DE_DEBUG("Middle mouse button pressed position: X: %.2f Y:%.2f", mousePosition.x, mousePosition.y);
		}
	}

	if (code == EVENT_CODE_BUTTON_RELEASED)
	{
		uint16 keyCode = context.data.uint16[0];
		if (keyCode == BUTTON_LEFT)
		{
			DE_DEBUG("Left mouse button released position: X: %.2f Y:%.2f", mousePosition.x, mousePosition.y);
		}
		else if (keyCode == BUTTON_RIGHT)
		{
			DE_DEBUG("Right mouse button released position: X: %.2f Y:%.2f", mousePosition.x, mousePosition.y);
		}
		else if (keyCode == BUTTON_MIDDLE)
		{
			DE_DEBUG("Middle mouse button released position: X: %.2f Y:%.2f", mousePosition.x, mousePosition.y);
		}
	}

	return false;
}

bl8		ApplicationOnMouseMove(uint16 code, void *sender, void *listenerInst, eventContext context)
{
	if (code == EVENT_CODE_MOUSE_MOVED)
	{
		fl32 x = static_cast<fl32>(context.data.uint16[0]);
		fl32 y = static_cast<fl32>(context.data.uint16[1]);

		mousePosition.x = x;
		mousePosition.y = y;

		DE_DEBUG("Mouse moved to (X: %.2f, Y: %.2f).", mousePosition.x, mousePosition.y);
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
		if (X != appliState->width || Y != appliState->height)
		{
			appliState->width = X;
			appliState->height = Y;

			DE_DEBUG("Window resize: %i, %i", X, Y);

			// Handle minimization
			if (X == 0 || Y == 0)
			{
				DE_INFO("Window minimized, suspending application.");
				appliState->isSuspended = true;
				return true;
			}
			else
			{
				if (appliState->isSuspended)
				{
					DE_INFO("Window restored, resuming application.");
					appliState->isSuspended = false;
				}
				appliState->gameInst->onResize(appliState->gameInst, X, Y);
				backend.RendererOnResized(X, Y);
			}
		}
	}

	return false;
}

void	ApplicationGetFramebufferSize(uint32 *width, uint32 *height)
{
	*width = appliState->width;
	*height = appliState->height;
}
