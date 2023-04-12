/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 25-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	     logger.hpp           *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "defines.hpp"
#include <stdio.h>
#include <stdarg.h>
#include <cstring>
#include <iostream>

#define LOG_WARNING_ENABLED true
#define LOG_INFO_ENABLED true
#define LOG_DEBUG_ENABLED true
#define LOG_TRACE_ENABLED true

// Disable debug and trace logs in release builds
#if DE_RELEASE == 1
#undef LOG_DEBUG_ENABLED 0
#undef LOG_TRACE_ENABLED 0
#endif

typedef enum	logLevel
{
	DE_LOG_LEVEL_FATAL = 0,
	DE_LOG_LEVEL_ERROR = 1,
	DE_LOG_LEVEL_WARNING = 2,
	DE_LOG_LEVEL_INFO = 3,
	DE_LOG_LEVEL_DEBUG = 4,
	DE_LOG_LEVEL_TRACE = 5
}	logLevel;

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Initializes logging system. Call twice; once with state = 0 to get		//
// required memory size,															//
// then a second time passing allocated memory to state.							//
//																					//
// @param memory_requirement A pointer to hold the required memory size of			//
// internal state.																	//
// @param state 0 if just requesting memory requirement, otherwise allocated		//
// block of memory.																	//
// @return b8 True on success; otherwise false.										//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//

bl8 LogInit(uint64 *memoryRequirement, void *state);
void LogShutdown(void *state);

DE_API void LogMessage(logLevel level, const char *message, ...);

// Log an error message as a fatal error lvl.
#define DE_FATAL(message, ...) LogMessage(DE_LOG_LEVEL_FATAL, message, ##__VA_ARGS__);

#ifndef DE_ERROR
// Log an error message as an error lvl.
#define DE_ERROR(message, ...) LogMessage(DE_LOG_LEVEL_ERROR, message, ##__VA_ARGS__);
#endif

#if LOG_WARNING_ENABLED == 1
// Log an error message as a warning lvl.
#define DE_WARNING(message, ...) LogMessage(DE_LOG_LEVEL_WARNING, message, ##__VA_ARGS__);
#else
// if warnings are disabled, just ignore them
#define DE_WARNING(message, ...) ;
#endif

#if LOG_INFO_ENABLED == 1
// Log an error message as an info lvl.
#define DE_INFO(message, ...) LogMessage(DE_LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#else
// if info logs are disabled, just ignore them
#define DE_INFO(message, ...) ;
#endif

#if LOG_DEBUG_ENABLED == 1
// Log an error message as a debug lvl.
#define DE_DEBUG(message, ...) LogMessage(DE_LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
#else
// if debug logs are disabled, just ignore them
#define DE_DEBUG(message, ...) ;
#endif

#if LOG_TRACE_ENABLED == 1
// Log an error message as a trace lvl.
#define DE_TRACE(message, ...) LogMessage(DE_LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
#else
// if trace logs are disabled, just ignore them
#define DE_TRACE(message, ...) ;
#endif

#endif
