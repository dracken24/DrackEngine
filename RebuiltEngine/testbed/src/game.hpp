/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 27-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	      game.hpp            *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef GAME_HPP
# define GAME_HPP

# include <defines.hpp>
# include <gameTypes.hpp>

typedef struct gameState
{
	fl32 deltaTime;
} gameState;

//*** NOTE: Thoses functions work with pointer functions enum in gameType.hpp ***//

// Function pointer to game's initialize function.
bl8		GameInit(struct game *gameInst);

// Function pointer to game's update function.
bl8		GameUpdate(struct game *gameInst, fl32 deltaTime);

// Function pointer to game's render function.
bl8		GameRender(struct game *gameInst, fl32 deltaTime);

// Function pointer to handle resizes, if applicable.
void	GameResize(struct game *gameInst, uint32 width, uint32 height);

#endif