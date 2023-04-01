/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 25-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	   application.hpp        *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef APPLICATION_HPP
# define APPLICATION_HPP

# if _WIN32
#  define GLFW_EXPOSE_NATIVE_WIN32
#  define VK_USE_PLATFORM_WIN32_KHR
# endif
# if __APPLE__
#  define GLFW_EXPOSE_NATIVE_COCOA
# endif
# if __linux__
#  define GLFW_EXPOSE_NATIVE_X11
# endif

# include "logger.hpp"
# include "defines.hpp"
# include "event.hpp"

# include <iostream>

struct Game;

// Application configuration.
typedef struct appConfig
{
	sint16		x;		// Window starting x position, if applicable.
	sint16		y;		// Window starting y position, if applicable.
	sint16		width;	// Window starting width, if applicable.
	sint16		height;	// Window starting height, if applicable.

    std::string	name;	// The application name used in windowing, if applicable.
}	appConfig;

// Core = Engine and Application Layer
class Core
{
	//****************************************************************************//
	//**       						Constructors                            	**//
	//****************************************************************************//

	public:
		Core();
		~Core();

	//****************************************************************************//
	//**       						PUBLIC METHODS                          	**//
	//****************************************************************************//

	public:
	// Global Methods for the Engine
		DE_API bl8	ApplicationStart(struct Game *gameInstance);
		DE_API bl8	ApplicationRun();
		DE_API void	ApplicationShutdown();

	//****************************************************************************//
	//**       						Private Variables                          	**//
	//****************************************************************************//

	public:
		// Platform	platform;
	
	private:
		
};

#endif
