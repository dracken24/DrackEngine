/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 24-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	      main.hpp            *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "../includes/core/core.hpp"

Core    *g_core = new Core;

int main(void)
{
	DE_ASSERT(true);

	DE_FATAL("Hello World! %f", 1.0f);
	DE_ERROR("Hello World! %f", 1.0f);
	DE_WARNING("Hello World! %f", 1.0f);
	DE_INFO("Hello World! %f", 1.0f);
	DE_DEBUG("Hello World! %f", 1.0f);
	DE_TRACE("Hello World! %f lol %s", 1.0f, "test");

	// std::cout << std::endl;

	// DE_ASSERT(1 == 2);

	// platformState state;
	if (g_core->platform.platformStart(&g_core->platform.platformState, "DrackEngine", {100, 100}, {1280, 720}))
	{
		while (true)
		{
			g_core->platform.platformUpdate(&g_core->platform.platformState);
		}
	}
	else
	{
		DE_FATAL("Failed to start platform\n");
	}

	g_core->platform.platformShutdown(&g_core->platform.platformState);


	delete g_core;

	return (0);
}
