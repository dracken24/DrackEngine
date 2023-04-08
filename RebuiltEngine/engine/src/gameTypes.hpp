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

# include <core/application.hpp>
# include <structs.hpp>

// Represents the basic game state in a game.
// Called for creation by the application.

typedef struct	game
{
	// The application configuration.
	appConfig appConfig;

	// Function pointer to game's initialize function.
	bl8		(*initialize)(struct game *gameInstance);

	// Function pointer to game's update function.
	bl8 	(*update)(struct game *gameInstance, fl32 deltaTime);

	// Function pointer to game's render function.
	bl8 	(*render)(struct game *gameInstance, fl32 deltaTime);

	// Function pointer to handle resizes, if applicable.
	void	(*onResize)(struct game *gameInstance, uint32 width, uint32 height);

	// Game-specific game state. Created and managed by the game.
	void	*state;

	// // For allocator functions.
	// Platform platform;
	RgbaFl32	bgColor;// Background color
}	game;

#endif // GAME_TYPE_HPP