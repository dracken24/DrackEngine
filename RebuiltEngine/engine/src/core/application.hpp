/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 25-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	   application.hpp        *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef APPLICATION_HPP
# define APPLICATION_HPP

#include <memory/linearAllocator.hpp>

#include <core/timer.hpp>

# include <defines.hpp>

# include <string>

struct game;

typedef struct	applicationState
{
	game*			gameInst;
	bl8				isRunning;
	bl8				isSuspended;
	platformState	platform;
	sint16			width;
	sint16			height;
	Timer			timer;
	dbl64			lastTime;
	linearAlloc		systemAllocator;

	uint64	eventSystemMemoryRequirement;
	void	*eventSystemState;

	uint64	memorySystemMemoryRequirement;
	void	*memorySystemState;

	uint64	loggingSystemMemoryRequirement;
	void	*loggingSystemState;

	// uint64	inputSystemMemoryRequirement;
	// void	*inputSystemState;

	// uint64	platformSystemMemoryRequirement;
	// void	*platformSystemState;

	// uint64	rendererSystemMemoryRequirement;
	// void	*rendererSystemState;
}	applicationState;

// Application configuration.
typedef struct	appConfig
{
	sint16		x;	   // Window starting x position, if applicable.
	sint16		y;	   // Window starting y position, if applicable.
	sint16		width;  // Window starting width, if applicable.
	sint16		height; // Window starting height, if applicable.

	std::string	name; // The application name used in windowing, if applicable.
}	appConfig;

DE_API bl8		ApplicationCreate(struct game* gameInst);

DE_API bl8		ApplicationRun();

DE_API void		ApplicationGetFramebufferSize(uint32 *width, uint32 *height);

// void			ApplicationGetFrameBufferSize(uint32 *width, uint32 *height);

#endif // APPLICATION_HPP
