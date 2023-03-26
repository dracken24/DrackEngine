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

# include "../core/defines.hpp"
# include "../utils/structs.hpp"

# include <string>

typedef struct  PlatformState
{
	void	*intetnalState;
}	PlatformState;

class	Platform
{
		//****************************************************************************//
		//**       						Constructors                            	**//
		//****************************************************************************//

	public:
		Platform(void);
		~Platform(void);

	//****************************************************************************//
	//**       						PUBLIC METHODS                          	**//
	//****************************************************************************//
	
	// Platform states
		bl8		platformStart(PlatformState *platform, std::string appName,
					Vector2si position, Vector2si size);
		void	platformShutdown(PlatformState *platform);
		bl8		platformUpdate(PlatformState *platform);

	// Dealing with memory
		void	*platformAllocator(uint64 size, bl8 align);
		void	platformFree(void *memPtr, bl8 align);
		void	*platZeroMem(void *memPtr, uint64 size);
		void	*platCopyMem(void *destPtr, const void *srcPtr, uint64 size);
		void	*platSetMem(void *drstPtr, sint32 value, uint64 size);

	// Dealing with messages
		void	platconsoleWrite(std::string str, uint8 color);
		void	platconsoleWriteError(std::string str, uint8 color);

	// Time
		dbl64	platGetAbsoluteTime(void);
		void	platSleep(uint64 timeMs);

	//****************************************************************************//
	public:
		PlatformState	platformState;
};

#endif
