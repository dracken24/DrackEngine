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

# include <defines.hpp>

struct platformState;
struct vulkanContext;

bl8		PlatformCreateVulkanSurface( struct platformState* platState,
			struct vulkanContext* context);

/**
 * Appends the names of required extensions for this platform to
 * the namesDE_Array, which should be created and passed in.
 */
void	PlatformGetRequiredExtensionNames(const char ***namesDE_Array);

#endif
