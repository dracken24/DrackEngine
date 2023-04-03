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

typedef enum renderer_backend_type
{
	RENDERER_BACKEND_TYPE_VULKAN,
	RENDERER_BACKEND_TYPE_OPENGL,
	RENDERER_BACKEND_TYPE_DIRECTX
} renderer_backend_type;

typedef struct renderer_backend
{
	struct platformState* platState;
	uint64 frame_number;

	bl8 (*initialize)(struct renderer_backend* backend, const char* applicationName, struct platformState* platState);

	void (*shutdown)(struct renderer_backend* backend);

	void (*resized)(struct renderer_backend* backend, uint16 width, uint16 height);

	bl8 (*begin_frame)(struct renderer_backend* backend, fl32 deltaTime);
	bl8 (*end_frame)(struct renderer_backend* backend, fl32 deltaTime);    
} renderer_backend;

typedef struct renderPacket
{
	fl32 deltaTime;
} renderPacket;

#endif
