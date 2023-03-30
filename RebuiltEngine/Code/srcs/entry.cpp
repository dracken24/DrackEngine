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
#include "../includes/core/deMemory.hpp"

bl8		CreateGame(Game* gameInst)
{
	DE_INFO("Creating game...");

	// Basic game configuration.
	gameInst->appConfigg.name = "DrackEngine";
	gameInst->appConfigg.width = 800;
	gameInst->appConfigg.height = 550;
	gameInst->appConfigg.x = 100;
	gameInst->appConfigg.y = 100;

	// Function pointers.
	gameInst->initialize = GameInit;
	gameInst->update = GameUpdate;
	gameInst->render = GameRender;
	gameInst->onResize = GameResize;

	gameInst->state = DE_Malloc(sizeof(gameInst->state) * 1, DE_MEMORY_TAG_GAME);

	DE_INFO("Game created.");
	return (true);
}

void	TEST_MEMORY(void)
{
	char	*str = (char *)DE_Malloc(sizeof(char) * 50000000, DE_MEMORY_TAG_STRING);
	Game	*game = (Game *)DE_Malloc(sizeof(Game) * 15000000, DE_MEMORY_TAG_DICT);
	char	*la = (char *)DE_Malloc(sizeof(char) * 500000000, DE_MEMORY_TAG_ENTITY);

	std::cout << DE_GetMemoryUsageString(DE_MEMORY_TAG_MAX_TAGS) << std::endl;

	DE_Free(str, sizeof(char) * 50000000, DE_MEMORY_TAG_STRING);
	DE_Free(game, sizeof(Game) * 15000000, DE_MEMORY_TAG_DICT);
	DE_Free(la, sizeof(char) * 500000000, DE_MEMORY_TAG_ENTITY);
}

// Main entry point for the application.
int main(void)
{
	// Initialize the platform.
	InitMemory();

	Core		core;

	// Create an instance of the game.
	Game		gameInst;
	if (!CreateGame(&gameInst))
	{
		DE_FATAL("Failed to create game.");
		return (-1);
	}
	std::cout << DE_GetMemoryUsageString(DE_MEMORY_TAG_MAX_TAGS) << std::endl;

	// Check if the game has a valid function pointer for initialize.
	if (!gameInst.render || !gameInst.update || !gameInst.initialize || !gameInst.onResize)
	{
		DE_FATAL("Game instance is missing a function pointer.");
		return (-2);
	}

	// TEST_MEMORY();
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
	// gameInst.platform.PlatformFree(gameInst.state, false);
	DE_Free(gameInst.state, sizeof(gameInst.state) * 1, DE_MEMORY_TAG_GAME);
	ShutdownMemory();
	std::cout << DE_GetMemoryUsageString(DE_MEMORY_TAG_MAX_TAGS) << std::endl;

	return (0);
}
