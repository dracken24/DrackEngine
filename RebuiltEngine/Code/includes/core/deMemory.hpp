/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 27-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	    deMemory.hpp          *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef DEMEMORY_HPP
# define DEMEMORY_HPP

# include "defines.hpp"

# include <string>

typedef enum memoryTag
{
	DE_MEMORY_TAG_UNKNOWN,
	DE_MEMORY_TAG_ARRAY,
	DE_MEMORY_TAG_DARRAY,
	DE_MEMORY_TAG_DICT,
	DE_MEMORY_TAG_RING_QUEUE,
	DE_MEMORY_TAG_BST,
	DE_MEMORY_TAG_STRING,
	DE_MEMORY_TAG_APPLICATION,
	DE_MEMORY_TAG_JOB,
	DE_MEMORY_TAG_TEXTURE,
	DE_MEMORY_TAG_MATERIAL_INSTANCE,
	DE_MEMORY_TAG_RENDERER,
	DE_MEMORY_TAG_GAME,
	DE_MEMORY_TAG_TRANSFORM,
	DE_MEMORY_TAG_ENTITY,
	DE_MEMORY_TAG_ENTITY_NODE,
	DE_MEMORY_TAG_SCENE,

	DE_MEMORY_TAG_MAX_TAGS
}	memoryTag;

void				InitMemory(void);
void				ShutdownMemory(void);

// Alloc and track memory
DE_API void			*DE_Malloc(uint64 size, memoryTag tag);
DE_API void 		*DE_Calloc(void *memPtr, uint64 size);
DE_API void 		DE_Free(void *memPtr, uint64 size, memoryTag tag);
DE_API void 		*DE_CopyMemory(void *destPtr, const void *srcPtr, uint64 size);
DE_API void 		*DE_SetMemory(void *drstPtr, sint32 value, uint64 size);
DE_API std::string	DE_GetMemoryUsageString(memoryTag tag);

#endif
