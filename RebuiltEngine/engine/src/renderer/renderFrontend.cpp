/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 31-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	 renderFronthand.cpp      *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "core/logger.hpp"
#include "core/deMemory.hpp"

#include "renderFrontend.hpp"
#include "renderBackend.hpp"

struct PlatformState;

// Backend render context.
static rendererBackend *backend = 0;

bl8		RendererInitialize(std::string applicationName, struct PlatformState *platState)
{
	backend = (rendererBackend *)DE_Malloc(sizeof(rendererBackend), DE_MEMORY_TAG_RENDERER);

	// TODO: make this configurable.
	RendererBackendCreate(DE_RENDER_BACKEND_TYPE_VULKAN, platState, backend);
	backend->frameNumber = 0;

	if (!backend->initialize(backend, applicationName, platState))
	{
		DE_FATAL("Renderer backend failed to initialize. Shutting down.");
		return false;
	}

	return true;
}

void	RendererShutdown(void)
{
	backend->shutdown(backend);
	DE_Free(backend, sizeof(rendererBackend), DE_MEMORY_TAG_RENDERER);
}

bl8		RendererBeginFrame(fl32 deltaTime)
{
	return backend->beginFrame(backend, deltaTime);
}

bl8		RendererEndFrame(fl32 deltaTime)
{
	bl8 result = backend->endFrame(backend, deltaTime);
	backend->frameNumber++;
	return result;
}

bl8		RendererDrawFrame(renderPacket *packet)
{
	// If the begin frame returned successfully, mid-frame operations may continue.
	if (RendererBeginFrame(packet->deltaTime))
	{

		// End the frame. If this fails, it is likely unrecoverable.
		bl8 result = RendererEndFrame(packet->deltaTime);

		if (!result)
		{
			DE_ERROR("renderer_end_frame failed. Application shutting down...");
			return false;
		}
	}

	return true;
}
