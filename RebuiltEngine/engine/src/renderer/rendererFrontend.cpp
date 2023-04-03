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
static renderer_backend* backend = 0;

bl8 renderer_initialize(const char* applicationName, struct platformState* platState)
{
	backend = (renderer_backend *)Mallocate(sizeof(renderer_backend), DE_MEMORY_TAG_RENDERER);

	// TODO: make this configurable.
	renderer_backend_create(RENDERER_BACKEND_TYPE_VULKAN, platState, backend);
	backend->frame_number = 0;

	if (!backend->initialize(backend, applicationName, platState))
	{
		DE_FATAL("Renderer backend failed to initialize. Shutting down.");
		return false;
	}

	return true;
}

void RendererShutdown()
{
	backend->shutdown(backend);
	FreeMem(backend, sizeof(renderer_backend), DE_MEMORY_TAG_RENDERER);
}

bl8 renderer_begin_frame(fl32 deltaTime)
{
	return backend->begin_frame(backend, deltaTime);
}

bl8 renderer_end_frame(fl32 deltaTime)
{
	bl8 result = backend->end_frame(backend, deltaTime);
	backend->frame_number++;
	return result;
}

bl8 RendererDrawFrame(renderPacket* packet)
{
	// If the begin frame returned successfully, mid-frame operations may continue.
	if (renderer_begin_frame(packet->deltaTime))
	{

		// End the frame. If this fails, it is likely unrecoverable.
		bl8 result = renderer_end_frame(packet->deltaTime);

		if (!result) {
			DE_ERROR("renderer_end_frame failed. Application shutting down...");
			return false;
		}
	}

	return true;
}
