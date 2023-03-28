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

# include "core/core.hpp"

// Represents the basic game state in a game.
// Called for creation by the application.

typedef struct Game
{
	// The application configuration.
	appConfig	appConfigg;

	// Function pointer to game's initialize function.
	bl8 (*initialize)(struct Game* game_inst);

	// Function pointer to game's update function.
	bl8 (*update)(struct Game* game_inst, fl32 delta_time);

	// Function pointer to game's render function.
	bl8 (*render)(struct Game* game_inst, fl32 delta_time);

	// Function pointer to handle resizes, if applicable.
	void (*onResize)(struct Game* game_inst, uint32 width, uint32 height);

	// Game-specific game state. Created and managed by the game.
	void* state;

	// For allocator functions.
	Platform	platform;
}	Game;

#endif
