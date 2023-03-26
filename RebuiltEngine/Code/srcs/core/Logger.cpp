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

#include "../../includes/core/core.hpp"

bl8		logInit()
{
	return (true);
}

void	logShutdown()
{

}

DE_API void	logMessage(logLevel level, const char *message, ...)
{
	const char	*levelStr[6] = {"[*FATAL*] ", "[*ERROR*] ", "[*WARNING*] ",
		"[*INFO*] ", "[*DEBUG*] ", "[*TRACE*] "};
	// bl8	isAnError = level < LOG_LEVEL_WARNING;

	char	outMessage[32000];
	memset(outMessage, 0, sizeof(outMessage));

	__builtin_va_list args;
	va_start(args, message);
	vsnprintf(outMessage, 32000, message, args);
	va_end(args);

	char	outBuffer[32001];
	snprintf(outBuffer, sizeof(outBuffer), "%s%s\n", levelStr[level], outMessage);

	// Color for Debug Log messages
	std::string color;
	if (level == LOG_LEVEL_FATAL || level == LOG_LEVEL_ERROR)
		color = T_RED;
	else if (level == LOG_LEVEL_WARNING)
		color = T_YELLOW;
	else if (level == LOG_LEVEL_INFO)
		color = T_GREEN;
	else if (level == LOG_LEVEL_DEBUG)
		color = T_BLUE;
	else if (level == LOG_LEVEL_TRACE)
		color = T_CYAN;
	else
		color = T_WHITE;

	// printf("%s%s", color.c_str(), outBuffer);
	std::cout << color << outBuffer << T_RESET;
}
