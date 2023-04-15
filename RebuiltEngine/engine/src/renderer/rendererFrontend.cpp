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

struct platformState;

// static rendererBackend* backend = 0;
//**********************************************************************//
//**                     Constructors / Destructor                    **//
//**********************************************************************//

Renderer::Renderer()
{
}

Renderer::Renderer(const Renderer &src)
{
	if (this != &src)
	{
		*this = src;
	}
}

Renderer &Renderer::operator=(const Renderer &src)
{
	if (this != &src)
	{
		_backend->beginFrame = src._backend->beginFrame;
		_backend->endFrame = src._backend->endFrame;
		_backend->frameNumber = src._backend->frameNumber;
		_backend->initialize = src._backend->initialize;
		_backend->platState = src._backend->platState;
		_backend->resized = src._backend->resized;
		_backend->shutdown = src._backend->shutdown;
	}
	return *this;
}

Renderer::~Renderer()
{
}

//**********************************************************************//
//**                          PUBLIC METHODS                          **//
//**********************************************************************//

bl8		Renderer::RendererInit(uint64 *memoryRequirement, void *state, const char *applicationName)
{
	*memoryRequirement = sizeof(rendererBackend);
	if (state == 0)
	{
		return true;
	}
	_backend = (rendererBackend *)state;

	// TODO: make this configurable.
	RendererBackendCreate(DE_RENDERER_BACKEND_TYPE_VULKAN, _backend);
	_backend->frameNumber = 0;

	if (!_backend->initialize(_backend, applicationName))
	{
		DE_FATAL("Renderer backend failed to initialize. Shutting down.");
		return false;
	}

	return true;
}

void	Renderer::RendererShutdown(void* state)
{
	if (_backend)
	{
		_backend->shutdown(_backend);
	}
	_backend = 0;
}

bl8		Renderer::RendererBeginFrame(fl32 deltaTime)
{
	return _backend->beginFrame(_backend, deltaTime);
}

bl8		Renderer::RendererEndFrame(fl32 deltaTime)
{
	bl8 result = _backend->endFrame(_backend, deltaTime);
	_backend->frameNumber++;

	return result;
}

void	Renderer::RendererOnResized(uint16 width, uint16 height)
{
	if (_backend)
	{
		_backend->resized(_backend, width, height);
	}
	else
	{
		DE_WARNING("renderer backend does not exist to accept resize: %i %i", width, height);
	}
}

bl8		Renderer::RendererDrawFrame(renderPacket* packet)
{
	// If the begin frame returned successfully, mid-frame operations may continue.
	if (RendererBeginFrame(packet->deltaTime))
	{

		// End the frame. If this fails, it is likely unrecoverable.
		if (!RendererEndFrame(packet->deltaTime))
		{
			DE_ERROR("RendererEndFrame failed frame #[%d]. Application shutting down...", _backend->frameNumber);
			return false;
		}
	}

	return true;
}
