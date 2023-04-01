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

#include "gameType.hpp"
#include "core/input.hpp"
#include "core/time.hpp"
#include "core/deMemory.hpp"

#include "renderer/renderFrontend.hpp"

typedef struct appState
{
	Game			*gameInstance;
	bl8				isRunning;
	bl8				isSuspended;
	Platform		platform;
	sint16			width;
	sint16			height;
	Clock			clock;
	dbl64			lastTime;
	dbl64			deltaTime;
}	appState;

static bl8		init = false;
static appState	engineState;

//****************************************************************************//
//**       						Constructors                            	**//
//****************************************************************************//

Core::Core()
{
	DE_DEBUG("Core created");
}

Core::~Core()
{
	DE_DEBUG("Core destroyed");
}

//****************************************************************************//
//**       						PUBLIC METHODS                          	**//
//****************************************************************************//

// Event handlers
bl8 ApplicationOnEvent(uint16 code, void *sender, void *listener_inst, eventContext context);
bl8 ApplicationOnKey(uint16 code, void *sender, void *listener_inst, eventContext context);

// Global Methods for the Engine
bl8		Core::ApplicationStart(Game *gameInstance)
{
	if (init)
	{
		DE_ERROR("Engine already started!");
		return (false);
	}

	engineState.gameInstance = gameInstance;

	// Init the engine sub-systems
	DE_INFO("Engine starting...\n");
	LogInit();
	InputInit();

	// TODO: remove when log message are fully implemented
	DE_FATAL("Hello World! %f", 1.0f);
	DE_ERROR("Hello World! %f", 1.0f);
	DE_WARNING("Hello World! %f", 1.0f);
	DE_INFO("Hello World! %f", 1.0f);
	DE_DEBUG("Hello World! %f", 1.0f);
	DE_TRACE("Hello World! %f lol %s", 1.0f, "test\n");

	engineState.isRunning = true;
	engineState.isSuspended = false;

	if (!EventInit())
	{
		DE_ERROR("Events initialization failed!");
		return (false);
	}
	// DE_INFO("HELP");
	EventRegister(DE_EVENT_CODE_APPLICATION_QUIT, 0, ApplicationOnEvent);
	// DE_INFO("HELP1");
	EventRegister(DE_EVENT_CODE_KEY_PRESSED, 0, ApplicationOnKey);
	// DE_INFO("HELP2");
	EventRegister(DE_EVENT_CODE_KEY_RELEASED, 0, ApplicationOnKey);
	// DE_INFO("HELP3");

	// Try initializing the platform
	if (!engineState.platform.PlatformStart(
		&engineState.platform.platformState,
		gameInstance->appConfigg.name,
		{gameInstance->appConfigg.x,
		gameInstance->appConfigg.y},
		{gameInstance->appConfigg.width,
		gameInstance->appConfigg.height}))
	{
		// if it fails, shutdown the engine
		return (false);
	}

	// Start Renderer
	if (!RendererInitialize(gameInstance->appConfigg.name, &engineState.platform.platformState))
	{
		DE_FATAL("Renderer initialization failed!");
		return (false);
	}

	// Initialize the game
	if (!engineState.gameInstance->initialize(engineState.gameInstance))
	{
		DE_FATAL("Game initialization failed!");
		return (false);
	}

	// Resize event
	engineState.gameInstance->onResize(engineState.gameInstance, engineState.width, engineState.height);

	// Engine initialization is done
	init = true;
	return (true);
}

// Main loop of the engine
bl8	Core::ApplicationRun()
{
	DE_DEBUG("Core update");

	// Start the clock for DeltaTime
	engineState.clock.ClockStart();
	engineState.clock.ClockUpdate();
	engineState.lastTime = engineState.clock._clock.elapsedTime;

	dbl64	runningTime = 0;
	uint64	framesCount = 0;
	dbl64	targetFrameSec = 1.0f / 60; // 60 fps

	while (engineState.isRunning)
	{
		if (!engineState.platform.PlatformUpdate(&engineState.platform.platformState))
		{
			engineState.isRunning = false;
		}

		// std::cout << "Frame: " << (int)framesCount << std::endl;

		// Update the game
		if (!engineState.isSuspended)
		{
			// Update the clock
			engineState.clock.ClockUpdate();
			dbl64 currentTime = engineState.clock._clock.elapsedTime;
			engineState.deltaTime = currentTime - engineState.lastTime;
			dbl64	frameStartTime = engineState.platform.PlatGetAbsoluteTime();

			if (!engineState.gameInstance->update(engineState.gameInstance, (fl32)engineState.deltaTime))
			{
				DE_FATAL("Game update failed!, shutting down...");
				engineState.isRunning = false;
				break ;
			}

			// Render the game
			if (!engineState.gameInstance->render(engineState.gameInstance, (fl32)engineState.deltaTime))
			{
				DE_FATAL("Game render failed!, shutting down...");
				engineState.isRunning = false;
				break ;
			}

			// TODO: refactor packet creation
			renderPacket	renderPkt;
			renderPkt.deltaTime = engineState.deltaTime;
			RendererDrawFrame(&renderPkt);

			// Update the last time
			dbl64	frameEndTime = engineState.platform.PlatGetAbsoluteTime();
			dbl64	frameElapsedTime = frameEndTime - frameStartTime;
			runningTime += frameElapsedTime;
			dbl64	remainingSec = targetFrameSec - frameElapsedTime;
			if (remainingSec > 0)
			{
				dbl64	remainingMs = remainingSec * 1000;

				// Sleep for the remaining time
				bl8	limitFrame = true;
				if (remainingMs > 0 && limitFrame)
				{
					// std::cout << "DeltaTime: " << engineState.deltaTime << std::endl;
					engineState.platform.PlatSleep(remainingMs - 1);
				}
				framesCount++;
			}
			// Catch all imput events for next frame
			InputUpdate(engineState.deltaTime);
			// std::cout << "DeltaTime: " << engineState.deltaTime << std::endl;

			// Update the last time
			engineState.lastTime = currentTime;
		}
	}

	engineState.isRunning = false;

	// Shutdown event system
	EventUnregister(DE_EVENT_CODE_APPLICATION_QUIT, 0, ApplicationOnEvent);
	EventUnregister(DE_EVENT_CODE_KEY_PRESSED, 0, ApplicationOnKey);
	EventUnregister(DE_EVENT_CODE_KEY_RELEASED, 0, ApplicationOnKey);
	EventShutdown();

	// Shutdown the renderer
	RendererShutdown();

	// Shutdown the engine
	InputShutdown();
	ApplicationShutdown();

	return (true);
}

void	Core::ApplicationShutdown()
{
	DE_DEBUG("Core shutdown");

	engineState.platform.PlatformShutdown(&engineState.platform.platformState);
}

bl8		ApplicationOnEvent(uint16 code, void *sender, void *listener_inst, eventContext context)
{
	DE_INFO("EVENT 1");
	switch (code)
	{
	case DE_EVENT_CODE_APPLICATION_QUIT:
		{
			DE_INFO("EVENT_CODE_APPLICATION_QUIT recieved, shutting down.\n");
			engineState.isRunning = false;
			return true;
		}
	}

	return false;
}

bl8		ApplicationOnKey(uint16 code, void *sender, void *listenerInst, eventContext context)
{
	if (code == DE_EVENT_CODE_KEY_PRESSED)
	{
		uint16 key_code = context.data.u16[0];
		if (key_code == KEY_ESCAPE)
		{
			// NOTE: Technically firing an event to itself, but there may be other listeners.
			eventContext data = {};
			EventFire(DE_EVENT_CODE_APPLICATION_QUIT, 0, data);

			// Block anything else from processing this.
			return true;
		}
		else if (key_code == KEY_A)
		{
			// Example on checking for a key
			DE_DEBUG("Explicit - A key pressed!");
		}
		else
		{
			DE_DEBUG("'%c' key pressed in window.", key_code);
		}
	}
	else if (code == DE_EVENT_CODE_KEY_RELEASED)
	{
		uint16 key_code = context.data.u16[0];
		if (key_code == KEY_B)
		{
			// Example on checking for a key
			DE_DEBUG("Explicit - B key released!");
		}
		else
		{
			DE_DEBUG("'%c' key released in window.", key_code);
		}
	}
	return false;
}
