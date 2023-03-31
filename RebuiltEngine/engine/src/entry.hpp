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

#ifndef MAIN_HPP
# define MAIN_HPP

# include "core/core.hpp"
# include "core/logger.hpp"
# include "gameType.hpp"
# include "game.hpp"

// Tell game have an extern function to create the game.
extern bl8  CreateGame(Game* game);

// // Main entry point for the application.
// int main(void)
// {
// 	Core		core;

// 	// Create an instance of the game.
// 	Game		gameInst;
// 	if (!createGame(&gameInst))
// 	{
// 		DE_FATAL("Failed to create game.");
// 		return (-1);
// 	}

// 	// Check if the game has a valid function pointer for initialize.
// 	if (!gameInst.render || !gameInst.update || !gameInst.initialize || !gameInst.onResize)
// 	{
// 		DE_FATAL("Game instance is missing a function pointer.");
// 		return (-2);
// 	}

// 	// Initialize the engine.
// 	if (!core.applicationStart(&gameInst))
// 	{
// 		DE_INFO("Engine failed to start properly.");
// 		return (1);
// 	}

// 	// Run the engine loop.
// 	if (!core.applicationRun())
// 	{
// 		DE_INFO("Engine failed to close properly.");
// 		return (2);
// 	}

// 	// TODO: Function for free memory.
// 	delete (gameState*)gameInst.state;

// 	return (0);
// }

#endif
