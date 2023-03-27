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

typedef struct appState
{
	bl8				isRunning;
	bl8				isSuspended;
	// PlatformState	*platform;
	Platform		platform;
	sint16			width;
	sint16			height;
	// clock			clock;
	dbl64			lastTime;
}	appState;

static bl8		init = false;
static appState	engineState;

//****************************************************************************//
//**       						Constructors                            	**//
//****************************************************************************//

DE_Core::DE_Core()
{
	DE_INFO("Core created");
}

DE_Core::~DE_Core()
{
	DE_INFO("Core destroyed");
}

//****************************************************************************//
//**       						PUBLIC METHODS                          	**//
//****************************************************************************//

// Global Methods for the Engine
bl8		DE_Core::applicationStart(appConfig *config)
{
	if (init)
	{
		DE_ERROR("Engine already started!");

		return (false);
	}

	// Init the engine sub-systems
	DE_INFO("Engine starting...\n");
	logInit();

	// TODO: remove when log message are fully implemented
	DE_FATAL("Hello World! %f", 1.0f);
	DE_ERROR("Hello World! %f", 1.0f);
	DE_WARNING("Hello World! %f", 1.0f);
	DE_INFO("Hello World! %f", 1.0f);
	DE_DEBUG("Hello World! %f", 1.0f);
	DE_TRACE("Hello World! %f lol %s", 1.0f, "test\n");

	engineState.isRunning = true;
	engineState.isSuspended = false;

	// Try initializing the platform
	if (!engineState.platform.platformStart(
		&engineState.platform.platformState,
		config->name,
		{config->x,
		config->y},
		{config->width,
		config->height}))
	{
		// if it fails, shutdown the engine
		return (false);
	}

	// Engine initialization is done
	init = true;

	return (true);
}

bl8	DE_Core::applicationRun()
{
	DE_INFO("Core update");

	while (engineState.isRunning)
	{
		if (!engineState.platform.platformUpdate(&engineState.platform.platformState))
		{
			engineState.isRunning = false;
		}
	}

	engineState.isRunning = false;

	// Shutdown the engine
	applicationShutdown();

	return (true);
}

void	DE_Core::applicationShutdown()
{
	DE_INFO("Core shutdown");

	engineState.platform.platformShutdown(&engineState.platform.platformState);
}
