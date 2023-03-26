/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 25-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	    Platform.cpp          *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "../../includes/platform/Platform.hpp"

#if DE_PLATFORM_WINDOWS
# include <Windows.h>
# include <Windowsx.h> // for platform input extraction

typedef struct  internalState
{
	HINSTANCE	hInstance;	// handle to the instance of the application
	HWND		hWnd;		// handle to the window
}	internalState;

bl8 	Platform::platformStart(PlatformState	*platform, std::string appName,
			Vector2si position, Vector2si size)
{
    platform->intetnalState = new internalState;
	internalState *state = (internalState *)platform->intetnalState;

	// Create the window
	state->hInstance = GetModuleHandleA(0);
}

//****************************************************************************//
//**       						Constructors                            	**//
//****************************************************************************//

Platform::Platform(void)
{
	
}

Platform::~Platform(void)
{
	
}

//****************************************************************************//
//**       						PUBLIC METHODS                          	**//
//****************************************************************************//

// Platform states
bl8 	Platform::platformStart(PlatformState	*platform, std::string appName,
			Vector2si position, Vector2si size)
{
	
}

void	Platform::platformStop(PlatformState	*platform)
{
	
}

bl8		Platform::platformUpdate(PlatformState	*platform)
{
	
}

// Dealing with memory
void	*Platform::platformAllocator(uint64 size, bl8 align)
{
	
}

void	Platform::platformFree(void *memPtr, bl8 align)
{
	
}

void	*Platform::platZeroMem(void *memPtr, uint64 size)
{
	
}

void	*Platform::platCopyMem(void *destPtr, const void *srcPtr, uint64 size)
{
	
}

void	*Platform::platSetMem(void *drstPtr, sint32 value, uint64 size)
{
	
}

// Dealing with messages

void	Platform::platconsoleWrite(std::string str, uint8 color)
{
	
}

void	Platform::platconsoleWriteError(std::string str, uint8 color)
{
	
}

// Time

dbl64	Platform::platGetAbsoluteTime(void)
{
	
}

dbl64	Platform::platSleep(uint64 timeMs)
{
	
}

#endif
