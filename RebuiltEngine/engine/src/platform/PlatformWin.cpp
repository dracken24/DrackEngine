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

#include "platform/Platform.hpp"

#if DE_PLATFORM_WINDOWS
# include <Windows.h>
# include <Windowsx.h> // for platform input extraction

typedef struct  internalState
{
	HINSTANCE	hInstance;	// handle to the instance of the application
	HWND		hWnd;		// handle to the window
}	internalState;

bl8 	Platform::PlatformStart(PlatformState	*platform, std::string appName,
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
bl8 	Platform::PlatformStart(PlatformState	*platform, std::string appName,
			Vector2si position, Vector2si size)
{
	
}

void	Platform::PlatformStop(PlatformState	*platform)
{
	
}

bl8		Platform::PlatformUpdate(PlatformState	*platform)
{
	
}

// Dealing with memory
void	*Platform::PlatformAllocator(uint64 size, bl8 align)
{
	
}

void	Platform::PlatformFree(void *memPtr, bl8 align)
{
	
}

void	*Platform::PlatZeroMem(void *memPtr, uint64 size)
{
	
}

void	*Platform::PlatCopyMem(void *destPtr, const void *srcPtr, uint64 size)
{
	
}

void	*Platform::PlatSetMem(void *drstPtr, sint32 value, uint64 size)
{
	
}

// Dealing with messages

void	Platform::PlatconsoleWrite(std::string str, uint8 color)
{
	
}

void	Platform::PlatconsoleWriteError(std::string str, uint8 color)
{
	
}

// Time

dbl64	Platform::PlatGetAbsoluteTime(void)
{
	
}

dbl64	Platform::PlatSleep(uint64 timeMs)
{
	
}

#endif
