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

#include "../../includes/core/core.hpp"
#include "../../includes/gameType.hpp"
#include "../../includes/core/input.hpp"
#include "../../includes/core/time.hpp"

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

	dbl64	runningTime = 0.0f;
	uint8	framesCount = 0;
	dbl64	targetFrameSec = 1.0f / 60.0f; // 60 fps

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
			engineState.lastTime = engineState.clock._clock.elapsedTime;
		}
	}

	engineState.isRunning = false;

	// Shutdown the engine
	InputShutdown();
	EventShutdown();
	ApplicationShutdown();

	return (true);
}

void	Core::ApplicationShutdown()
{
	DE_DEBUG("Core shutdown");

	engineState.platform.PlatformShutdown(&engineState.platform.platformState);
}
