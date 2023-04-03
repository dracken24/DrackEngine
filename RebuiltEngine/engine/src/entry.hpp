/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 27-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	     entry.hpp            *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef ENTRY_HPP
# define ENTRY_HPP

# include "core/application.hpp"
# include "core/logger.hpp"
# include "core/deMemory.hpp"
# include "gameTypes.hpp"

// Externally-defined function to create a game.
extern bl8	createGame(game* out_game);

/**
 * The main entry point of the application.
 */
int		main(void)
{

	InitializeMemory();

	// Request the game instance from the application.
	game	gameInst;
	if (!createGame(&gameInst))
	{
		DE_FATAL("Could not create game!");
		return (-1);
	}

	// Ensure the function pointers exist.
	if (!gameInst.render || !gameInst.update || !gameInst.initialize || !gameInst.onResize)
	{
		DE_FATAL("The game's function pointers must be assigned!");
		return (-2);
	}

	// Initialization.
	if (!ApplicationCreate(&gameInst))
	{
		DE_FATAL("Application failed to create!.");
		return (1);
	}

	// Begin the game loop.
	if(!ApplicationRun())
	{
		DE_INFO("Application did not shutdown gracefully.");
		return (2);
	}

	ShutdownMemory();

	return (0);
}

#endif // MAIN_HPP
