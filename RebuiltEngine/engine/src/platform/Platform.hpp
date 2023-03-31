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
		bl8			PlatformStart(PlatformState *platform, std::string appName,
						Vector2si position, Vector2si size);
		void		PlatformShutdown(PlatformState *platform);
		bl8			PlatformUpdate(PlatformState *platform);

	// Dealing with memory
		static void	*PlatformAllocator(uint64 size, bl8 align);
		static void	PlatformFree(void *memPtr, bl8 align);

		static void	*PlatZeroMem(void *memPtr, uint64 size);
		static void	*PlatSetMem(void *drstPtr, sint32 value, uint64 size);
		static void	*PlatCopyMem(void *destPtr, const void *srcPtr, uint64 size);

	// Dealing with messages
		void		PlatconsoleWrite(std::string str, uint8 color);
		void		PlatconsoleWriteError(std::string str, uint8 color);

	// Time
		dbl64		PlatGetAbsoluteTime(void);
		void		PlatSleep(uint64 timeMs);

		//****************************************************************************//
	public:
		PlatformState	platformState;
};

#endif
