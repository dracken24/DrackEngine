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

#include "rendererFrontend.hpp"
#include "rendererBackend.hpp"

#include "core/logger.hpp"
#include "core/deMemory.hpp"

struct platformState;

// Backend render context.
static rendererBackend* backend = 0;

bl8 RendererInit(const char* applicationName, struct platformState* platState)
{
	backend = (rendererBackend *)Mallocate(sizeof(rendererBackend), DE_MEMORY_TAG_RENDERER);

	// TODO: make this configurable.
	RendererBackendCreate(DE_RENDERER_BACKEND_TYPE_VULKAN, platState, backend);
	backend->frameNumber = 0;

	if (!backend->initialize(backend, applicationName, platState))
	{
		DE_FATAL("Renderer backend failed to initialize. Shutting down.");
		return false;
	}

	return true;
}

void RendererShutdown()
{
	FreeMem(backend, sizeof(rendererBackend), DE_MEMORY_TAG_RENDERER);
}

bl8 RendererBeginFrame(fl32 deltaTime)
{
	return backend->beginFrame(backend, deltaTime);
}

bl8 RendererEndFrame(fl32 deltaTime)
{
	bl8 result = backend->endFrame(backend, deltaTime);
	backend->frameNumber++;
	return result;
}

bl8 RendererDrawFrame(renderPacket* packet)
{
	// If the begin frame returned successfully, mid-frame operations may continue.
	if (RendererBeginFrame(packet->deltaTime))
	{

		// End the frame. If this fails, it is likely unrecoverable.
		bl8 result = RendererEndFrame(packet->deltaTime);

		if (!result) {
			DE_ERROR("RendererEndFrame failed. Application shutting down...");
			return false;
		}
	}

	return true;
}
