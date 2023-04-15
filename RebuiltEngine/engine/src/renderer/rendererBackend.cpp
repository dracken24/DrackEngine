/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 31-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	 renderBackhand.cpp       *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "rendererBackend.hpp"

#include "vulkan/vulkanBackend.hpp"

bl8		RendererBackendCreate(rendererBackendType type, rendererBackend* rendererBackend)
{
	if (type == DE_RENDERER_BACKEND_TYPE_VULKAN)
	{
		rendererBackend->initialize = vulkanRendererBackendInitialize;
		rendererBackend->shutdown = vulkanRendererBackendShutdown;
		rendererBackend->beginFrame = vulkanRendererBackendBeginFrame;
		rendererBackend->endFrame = vulkanRendererBackendEndFrame;
		rendererBackend->resized = vulkanRendererBackendOnResized;
		
		return true;
	}

	return false;
}

void	RendererBackenDestroy(rendererBackend* rendererBackend)
{
	rendererBackend->initialize = 0;
	rendererBackend->shutdown = 0;
	rendererBackend->beginFrame = 0;
	rendererBackend->endFrame = 0;
	rendererBackend->resized = 0;
}
