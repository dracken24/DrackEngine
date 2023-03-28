/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 24-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	     entry.cpp            *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "../includes/gameType.hpp"
#include "../includes/game.hpp"

bl8		CreateGame(Game* game)
{
	DE_INFO("Creating game...");

	// Basic game configuration.
	game->appConfigg.name = "DrackEngine";
	game->appConfigg.width = 1280;
	game->appConfigg.height = 700;
	game->appConfigg.x = 100;
	game->appConfigg.y = 100;

	// Function pointers.
	game->initialize = GameInit;
	game->update = GameUpdate;
	game->render = GameRender;
	game->onResize = GameResize;

	game->state = game->platform.PlatformAllocator(sizeof(gameState), true);

	DE_INFO("Game created.");
	return (true);
}

// Main entry point for the application.
int main(void)
{
	Core		core;

	// Create an instance of the game.
	Game		gameInst;
	if (!CreateGame(&gameInst))
	{
		DE_FATAL("Failed to create game.");
		return (-1);
	}

	// Check if the game has a valid function pointer for initialize.
	if (!gameInst.render || !gameInst.update || !gameInst.initialize || !gameInst.onResize)
	{
		DE_FATAL("Game instance is missing a function pointer.");
		return (-2);
	}

	// Initialize the engine.
	if (!core.ApplicationStart(&gameInst))
	{
		DE_INFO("Engine failed to start properly.");
		return (1);
	}

	// Run the engine loop.
	if (!core.ApplicationRun())
	{
		DE_INFO("Engine failed to close properly.");
		return (2);
	}

	// TODO: Function for free memory.
	gameInst.platform.PlatformFree(gameInst.state, false);

	return (0);
}
