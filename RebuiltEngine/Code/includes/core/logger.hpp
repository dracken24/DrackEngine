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
# define LOGGER_HPP

# include "defines.hpp"
# include <stdio.h>
# include <stdarg.h>
# include <cstring>
# include <iostream>

# define LOG_WARNING_ENABLED 1
# define LOG_INFO_ENABLED 1
# define LOG_DEBUG_ENABLED 1
# define LOG_TRACE_ENABLED 1

// Disable debug and trace logs in release builds
# if DE_RELEASE == 1
#  undef LOG_DEBUG_ENABLED 0
#  undef LOG_TRACE_ENABLED 0
# endif

typedef enum	logLevel
{
	LOG_LEVEL_FATAL =	0,
	LOG_LEVEL_ERROR =	1,
	LOG_LEVEL_WARNING =	2,
	LOG_LEVEL_INFO =	3,
	LOG_LEVEL_DEBUG =	4,
	LOG_LEVEL_TRACE =	5
}   logLevel;

bl8		logInit();
void	logShutdown();

DE_API void logMessage(logLevel level, const std::string& message, ...);

// Log an error message as a fatal error lvl.
# define DE_FATAL(message, ...) logMessage(LOG_LEVEL_FATAL, message, ##__VA_ARGS__);

# ifndef DE_ERROR
// Log an error message as an error lvl.
#  define DE_ERROR(message, ...) logMessage(LOG_LEVEL_ERROR, message, ##__VA_ARGS__);
# endif

# if LOG_WARNING_ENABLED == 1
// Log an error message as a warning lvl.
#  define DE_WARNING(message, ...) logMessage(LOG_LEVEL_WARNING, message, ##__VA_ARGS__);
# else
// if warnings are disabled, just ignore them
#  define DE_WARNING(message, ...);
# endif

# if LOG_INFO_ENABLED == 1
// Log an error message as an info lvl.
#  define DE_INFO(message, ...) logMessage(LOG_LEVEL_INFO, message, ##__VA_ARGS__);
# else
// if info logs are disabled, just ignore them
#  define DE_INFO(message, ...);
# endif

# if LOG_DEBUG_ENABLED == 1
// Log an error message as a debug lvl.
#  define DE_DEBUG(message, ...) logMessage(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
# else
// if debug logs are disabled, just ignore them
#  define DE_DEBUG(message, ...);
# endif

# if LOG_TRACE_ENABLED == 1
// Log an error message as a trace lvl.
#  define DE_TRACE(message, ...) logMessage(LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
# else
// if trace logs are disabled, just ignore them
#  define DE_TRACE(message, ...);
# endif

#endif
