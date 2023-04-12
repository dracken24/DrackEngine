/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 25-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	     logger.cpp           *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "core/application.hpp"
#include "platform/platform.hpp"
#include "core/logger.hpp"

typedef struct	loggerSystemState
{
	bl8 initialized;
}	loggerSystemState;

static loggerSystemState *statePtr;

bl8		LogInit(uint64* memoryRequirement, void* state)
{
	*memoryRequirement = sizeof(loggerSystemState);
	if (state == 0)
	{
		return true;
	}

	statePtr = (loggerSystemState *)state;
	statePtr->initialized = true;

	// TODO: remove when log message are fully implemented
	DE_FATAL("Hello World! %f", 1.0f);
	DE_ERROR("Hello World! %f", 1.0f);
	DE_WARNING("Hello World! %f", 1.0f);
	DE_INFO("Hello World! %f", 1.0f);
	DE_DEBUG("Hello World! %f", 1.0f);
	DE_TRACE("Hello World! %f lol %s", 1.0f, "test\n");

	// TODO: create log file.
	return (true);
}

void	LogShutdown(void* state)
{
	// TODO: cleanup logging/write queued entries.
	statePtr = 0;
}

// Platform platform;

void	LogMessage(logLevel level, const char *message, ...)
{
	const char	*levelStr[6] = {"[*FATAL*]   : ", "[*ERROR*]   : ", "[*WARNING*] : ",
		"[*INFO*]    : ", "[*DEBUG*]   : ", "[*TRACE*]   : "};
	bl8 shouldLog = level < DE_LOG_LEVEL_WARNING;

	char outMessage[32000];
	std::memset(outMessage, 0, sizeof(outMessage));

	va_list args;
	va_start(args, message);
	vsnprintf(outMessage, 32000, message, args);
	va_end(args);

	std::string outBuffer = levelStr[level];
	outBuffer += outMessage;
	outBuffer += "\n";

	if (shouldLog)
	{
		PlatconsoleWriteError(outBuffer, level);
	}
	else
	{
		PlatconsoleWrite(outBuffer, level);
	}
}

// From Code/includes/core/assert.hpp
void	ReportAssertionFailure(std::string const expression, std::string const message,
			std::string const file, sint32 line)
{
	LogMessage(DE_LOG_LEVEL_FATAL, "Assertion failed: %s, message: %s, file: %s, line: %d\n",
		expression.c_str(), message.c_str(), file.c_str(), line);
}
