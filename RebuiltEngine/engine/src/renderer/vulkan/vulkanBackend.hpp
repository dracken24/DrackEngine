/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 31-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	  vulkanBackend.hpp       *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef VULKANBACKEND_HPP
# define VULKANBACKEND_HPP

# include "renderer/rendererBackend.hpp"

bl8		vulkan_renderer_backend_initialize(renderer_backend* backend, const char* applicationName,
			struct platformState* platState);
void	vulkan_renderer_backend_shutdown(renderer_backend* backend);

void	vulkan_renderer_backend_on_resized(renderer_backend* backend, uint16 width, uint16 height);

bl8		vulkan_renderer_backend_begin_frame(renderer_backend* backend, fl32 deltaTime);
bl8		vulkan_renderer_backend_end_frame(renderer_backend* backend, fl32 deltaTime);

#endif
