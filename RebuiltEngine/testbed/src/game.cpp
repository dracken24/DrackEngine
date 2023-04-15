/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 27-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	      game.cpp            *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "game.hpp"
#include <core/logger.hpp>
#include <core/deMemory.hpp>
#include <core/input.hpp>

//*** NOTE: Thoses functions work with pointer functions enum in gameType.hpp ***//

// Function pointer to game's initialize function.
bl8		GameInit(struct game *gameInstance)
{
	DE_DEBUG("Initializing engine ...");
	return (true);
}

// Function pointer to game's update function.
bl8		GameUpdate(struct game *gameInstance, fl32 deltaTime)
{
	static uint64 allocCount = 0;
	uint64 prevAllocCount = allocCount;
	allocCount = GetMemoryAllocCount();
	if (DE_OnKeyRelease(KEY_M) && DE_OnKeyDown(KEY_M))
	{
		DE_DEBUG("Allocations: %llu (%llu this frame)", allocCount, allocCount - prevAllocCount);
	}

	return (true);
}

// Function pointer to game's render function.
bl8		GameRender(struct game *gameInstance, fl32 deltaTime)
{
	return (true);
}

// Function pointer to handle resizes, if applicable.
void	GameResize(struct game *gameInstance, uint32 width, uint32 height)
{
	DE_DEBUG("Resizing windows ...");
}
