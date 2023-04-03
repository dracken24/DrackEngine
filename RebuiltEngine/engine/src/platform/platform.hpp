/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 25-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	    Platform.hpp          *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef PLATFORM_HPP
# define PLATFORM_HPP

# include "defines.hpp"
# include <string>

typedef struct	platformState
{
	void*	internalState;
}	platformState;

bl8 PlatformStartup(
	platformState* platState,
	const char* applicationName,
	sint32 x,
	sint32 y,
	sint32 width,
	sint32 height);

void	PlatformShutdown(platformState* platState);

bl8		PlatformPumpMessages(platformState* platState);

void*	PlatformAllocate(uint64 size, bl8 aligned);
void	PlatformFree(void* block, bl8 aligned);
void*	PlatformSetMemory(void* block, uint64 size);
void*	PlatformCopyMemory(void* dest, const void* source, uint64 size);
void*	PlatformSetMemory(void* dest, sint32 value, uint64 size);

void	PlatconsoleWrite(std::string message, uint8 color);
void	PlatconsoleWriteError(std::string message, uint8 color);

dbl64	PlatformGetAbsoluteTime();

// Sleep on the thread for the provided ms. This blocks the main thread.
// Should only be used for giving time back to the OS for unused update power.
// Therefore it is not exported.
void	PlatformSleep(uint64 ms);

#endif // !PLATFORM_HPP
