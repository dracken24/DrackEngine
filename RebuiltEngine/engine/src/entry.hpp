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

#include "core/application.hpp"
#include "core/logger.hpp"
#include "core/kmemory.hpp"
#include "game_types.hpp"

// Externally-defined function to create a game.
extern bl8 create_game(game* out_game);

/**
 * The main entry point of the application.
 */
int main(void)
{

    initialize_memory();

    // Request the game instance from the application.
    game game_inst;
    if (!create_game(&game_inst)) {
        DE_FATAL("Could not create game!");
        return -1;
    }

    // Ensure the function pointers exist.
    if (!game_inst.render || !game_inst.update || !game_inst.initialize || !game_inst.onResize) {
        DE_FATAL("The game's function pointers must be assigned!");
        return -2;
    }

    // Initialization.
    if (!application_create(&game_inst)) {
        DE_FATAL("Application failed to create!.");
        return 1;
    }

    // Begin the game loop.
    if(!application_run()) {
        DE_INFO("Application did not shutdown gracefully.");
        return 2;
    }

    shutdown_memory();

    return 0;
}

#endif // MAIN_HPP
