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
struct vulkan_context;

bl8		PlatformCreateVulkanSurface( struct platformState* platState,
			struct vulkan_context* context);

/**
 * Appends the names of required extensions for this platform to
 * the names_darray, which should be created and passed in.
 */
void	PlatformGetRequiredExtensionNames(const char*** names_darray);

#endif
