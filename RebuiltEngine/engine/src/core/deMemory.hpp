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

# include <defines.hpp>

# include <string>

typedef enum	memoryTag
{
	// For temporary use. Should be assigned one of the below or have a new tag created.
	DE_MEMORY_TAG_UNKNOWN,
	DE_MEMORY_TAG_LINEAR_ALLOCATOR,
	DE_MEMORY_TAG_ARRAY,
	DE_MEMORY_TAG_MYARRAY,
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

DE_API void 		InitializeMemory(void);
DE_API void 		ShutdownMemory(void);

DE_API void			*Mallocate(uint64 size, memoryTag tag);

DE_API void 		FreeMem(void* block, uint64 size, memoryTag tag);

DE_API void			*SetMemory(void* block, uint64 size);

DE_API void			*CopyMemory(void* dest, const void* source, uint64 size);

DE_API void			*SetMemory(void* dest, sint32 value, uint64 size);

DE_API std::string	GetMemoryUsageStr();

#endif // !DEMEMORY_HPP
