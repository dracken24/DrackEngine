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

#include <core/deMemory.hpp>
#include <entry.hpp>
#include "game.hpp"

// Define the function to create a game
bl8		createGame(game* outGame)
{
	// Application configuration.
	outGame->appConfig.x = 100;
	outGame->appConfig.y = 100;
	outGame->appConfig.width = 950;
	outGame->appConfig.height = 640;
	outGame->appConfig.name = "DrackEngine";
	outGame->bgColor = {0.2f, 0.0f, 0.4f, 0.2f};

	outGame->update = GameUpdate;
	outGame->render = GameRender;
	outGame->initialize = GameInit;
	outGame->onResize = GameResize;

	// Create the game state.
	outGame->state = Mallocate(sizeof(gameState), DE_MEMORY_TAG_GAME);

	return true;
}
