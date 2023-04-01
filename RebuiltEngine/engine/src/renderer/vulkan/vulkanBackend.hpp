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

# include "renderer/renderBackend.hpp"

bl8		VulkanRendererBackendInitialize(rendererBackend *backend, std::string applicationName,
			struct PlatformState *platState);
void	VulkanRendererBackendShutdown(rendererBackend *backend);

void	VulkanRendererBackendOnResized(rendererBackend *backend, uint16 width, uint16 height);

bl8		VulkanRendererBackendBeginFrame(rendererBackend *backend, fl32 deltaTime);
bl8		VulkanRendererBackendEndFrame(rendererBackend *backend, fl32 deltaTime);

#endif
