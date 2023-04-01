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

# include "defines.hpp"

# include <string>

// RenderType structure
typedef enum rendererBackendType
{
	DE_RENDER_BACKEND_TYPE_VULKAN,
	DE_RENDER_BACKEND_TYPE_OPENGL,
	DE_RENDER_BACKEND_TYPE_DIRECTX
}	rendererBackendType;

typedef struct rendererBackend
{
	struct PlatformState	*platState;
	uint64					frameNumber;

	bl8		(*initialize)(struct rendererBackend *backend, std::string applicationName,
			struct PlatformState *platState);

	void	(*shutdown)(struct rendererBackend *backend);

	void	(*resized)(struct rendererBackend *backend, uint16 width, uint16 height);

	bl8		(*beginFrame)(struct rendererBackend *backend, fl32 deltaTime);
	bl8		(*endFrame)(struct rendererBackend *backend, fl32 deltaTime);
}	rendererBackend;

typedef struct renderPacket
{
	fl32	deltaTime;
}	renderPacket;

#endif
