/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 27-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	    gameType.hpp          *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef GAME_TYPE_HPP
# define GAME_TYPE_HPP

# include "core/application.hpp"
# include "platform/Platform.hpp"

// Represents the basic game state in a game.
// Called for creation by the application.

typedef struct Game
{
	// The application configuration.
	appConfig	appConfigg;

	// Function pointer to game's initialize function.
	bl8 (*initialize)(struct Game *gameInstance);

	// Function pointer to game's update function.
	bl8 (*update)(struct Game *gameInstance, fl32 deltaTime);

	// Function pointer to game's render function.
	bl8 (*render)(struct Game *gameInstance, fl32 deltaTime);

	// Function pointer to handle resizes, if applicable.
	void (*onResize)(struct Game *gameInstance, uint32 width, uint32 height);

	// Game-specific game state. Created and managed by the game.
	void* state;

	// For allocator functions.
	Platform	platform;
}	Game;

#endif
