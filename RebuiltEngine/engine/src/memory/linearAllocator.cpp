/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 11-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	 linearcpp      *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include <memory/linearAllocator.hpp>

#include <core/deMemory.hpp>
#include <core/logger.hpp>

void	LinearAllocatorCreate(uint64 totalSize, void *memory, linearAlloc *allocator)
{
	if (allocator)
	{
		allocator->totalSize = totalSize;
		allocator->allocated = 0;
		allocator->ownsMemory = memory == 0;
		if (memory)
		{
			allocator->memory = memory;
		}
		else
		{
			allocator->memory = Mallocate(totalSize, DE_MEMORY_TAG_LINEAR_ALLOCATOR);
		}
	}
}

void	LinearAllocatorDestroy(linearAlloc *allocator)
{
	if (allocator)
	{
		allocator->allocated = 0;
		if (allocator->ownsMemory && allocator->memory)
		{
			FreeMem(allocator->memory, allocator->totalSize, DE_MEMORY_TAG_LINEAR_ALLOCATOR);
		}
		allocator->memory = 0;
		allocator->totalSize = 0;
		allocator->ownsMemory = false;
	}
}

void	*LinearAllocatorAllocate(linearAlloc *allocator, uint64 size)
{
	if (allocator && allocator->memory)
	{
		if (allocator->allocated + size > allocator->totalSize)
		{
			uint64 remaining = allocator->totalSize - allocator->allocated;
			DE_ERROR("linear_allocator_allocate - Tried to allocate %lluB, only %lluB remaining.", size, remaining);
			return 0;
		}

		void *block = ((uint8 *)allocator->memory) + allocator->allocated;
		allocator->allocated += size;
		return block;
	}

	DE_ERROR("linear_allocator_allocate - provided allocator not initialized.");
	return 0;
}

void	LinearAllocatorFreeAll(linearAlloc *allocator)
{
	if (allocator && allocator->memory)
	{
		allocator->allocated = 0;
		SetMemory(allocator->memory, allocator->totalSize);
	}
}

