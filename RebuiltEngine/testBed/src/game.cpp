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

//*** NOTE: Thoses functions work with pointer functions enum in gameType.hpp ***//

// Function pointer to game's initialize function.
bl8		GameInit(struct Game *gameInstance)
{
	DE_DEBUG("Initializing engine ...");
	return (true);
}

// Function pointer to game's update function.
bl8		GameUpdate(struct Game *gameInstance, fl32 deltaTime)
{
	// DE_DEBUG("Updating game in game.cpp ...");
	return (true);
}

// Function pointer to game's render function.
bl8		GameRender(struct Game *gameInstance, fl32 deltaTime)
{
	// DE_DEBUG("Rendering game in game.cpp ...");
	return (true);
}

// Function pointer to handle resizes, if applicable.
void	GameResize(struct Game *gameInstance, uint32 width, uint32 height)
{
	DE_DEBUG("Resizing windows ...");
}
