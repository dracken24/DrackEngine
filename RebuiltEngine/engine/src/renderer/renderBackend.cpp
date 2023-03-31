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

#include "renderBackend.hpp"
#include "vulkan/vulkanBackend.hpp"

bl8		RendererBackendCreate(rendererBackendType type, struct PlatformState *platState,
			rendererBackend *outRendererBackend)
{
	outRendererBackend->platState = platState;

	if (type == DE_RENDER_BACKEND_TYPE_VULKAN)
	{
		outRendererBackend->initialize = VulkanRendererBackendInitialize;
		outRendererBackend->shutdown = VulkanRendererBackendShutdown;
		outRendererBackend->beginFrame = VulkanRendererBackendBeginFrame;
		outRendererBackend->endFrame = VulkanRendererBackendEndFrame;
		outRendererBackend->resized = VulkanRendererBackendOnResized;

		return true;
	}

	return false;
}

void RendererBackendDestroy(rendererBackend *rendererBackend)
{
	rendererBackend->initialize = 0;
	rendererBackend->shutdown = 0;
	rendererBackend->beginFrame = 0;
	rendererBackend->endFrame = 0;
	rendererBackend->resized = 0;
}
