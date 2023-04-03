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

bl8		vulkanRendererBackendInitialize(rendererBackend* backend, const char* applicationName,
			struct platformState* platState);
void	vulkanRendererBackendShutdown(rendererBackend* backend);

void	vulkanRendererBackendOnResized(rendererBackend* backend, uint16 width, uint16 height);

bl8		vulkanRendererBackendBeginFrame(rendererBackend* backend, fl32 deltaTime);
bl8		vulkanRendererBackendEndFrame(rendererBackend* backend, fl32 deltaTime);

#endif
