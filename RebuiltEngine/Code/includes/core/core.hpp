/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 25-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	      core.hpp            *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef CORE_HPP
# define CORE_HPP

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

# define GLFW_INCLUDE_VULKAN
# include <GLFW/glfw3.h>

# define GLM_FORCE_RADIANS
# define GLM_FORCE_DEPTH_ZERO_TO_ONE
# define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
# include <glm/gtc/matrix_transform.hpp>
# include <glm/glm.hpp>

# define GLM_ENABLE_EXPERIMENTAL
# include <glm/gtx/hash.hpp>

# include "../color.hpp"
# include "../core/logger.hpp"
# include "../core/defines.hpp"

# include <iostream>

class Core
{
	public:
		Core();
		~Core();

		// void	init();
		// void	run();
		// void	cleanup();

	//****************************************************************************//	

	public:
		// Logger		_logger;
};

#endif
