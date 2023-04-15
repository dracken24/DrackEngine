/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 31-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	   renderType.inl         *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef RENDERTYPE_INL
# define RENDERTYPE_INL

# include <defines.hpp>

typedef enum	rendererBackendType
{
	DE_RENDERER_BACKEND_TYPE_VULKAN,
	DE_RENDERER_BACKEND_TYPE_OPENGL,
	DE_RENDERER_BACKEND_TYPE_DIRECTX
}	rendererBackendType;

typedef struct	rendererBackend
{
	struct	platformState* platState;
	uint64	frameNumber;

	bl8		(*initialize)(struct rendererBackend* backend, const char* applicationName);

	void	(*shutdown)(struct rendererBackend* backend);

	void	(*resized)(struct rendererBackend* backend, uint16 width, uint16 height);

	// Mount an image to the renderer.
	bl8		(*beginFrame)(struct rendererBackend* backend, fl32 deltaTime);
	// Frame ready to be rendered.
	bl8		(*endFrame)(struct rendererBackend* backend, fl32 deltaTime);    
}	rendererBackend;

typedef struct	renderPacket
{
	fl32	deltaTime;
}	renderPacket;

#endif
