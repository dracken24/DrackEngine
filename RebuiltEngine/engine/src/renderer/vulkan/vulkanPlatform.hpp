/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 31-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	 vulkanPlatform.hpp       *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef VULKANPLATFORM_HPP
# define VULKANPLATFORM_HPP

# include "../../includes/core/defines.hpp"

# include <vector>
# include <string>

struct PlatformState;
struct vulkanContext;

bl8		PlatformCreateVulkanSurface(struct PlatformState *platState,
			struct vulkanContext *context);

/**
 * Appends the names of required extensions for this platform to
 * the names_darray, which should be created and passed in.
 */
void	PlatformGetRequiredExtensionNames(const char ***namesArray);

#endif
