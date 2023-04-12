/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 11-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	 linearAllocator.cpp      *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include <memory/linearAllocator.hpp>

#include <core/deMemory.hpp>
#include <core/logger.hpp>

LinearAllocator::LinearAllocator(void)
{
}

LinearAllocator::LinearAllocator(uint64 totalSize, void *memory)
{
	_allocator.totalSize = totalSize;
	_allocator.allocated = 0;
	_allocator.ownsMemory = memory == 0;
	if (memory)
	{
		_allocator.memory = memory;
	}
	else
	{
		_allocator.memory = Mallocate(totalSize, DE_MEMORY_TAG_LINEAR_ALLOCATOR);
	}
}


LinearAllocator::LinearAllocator(LinearAllocator const &src)
{
	*this = src;
}

LinearAllocator	&LinearAllocator::operator=(LinearAllocator const &rhs)
{
	if (this != &rhs)
	{
		// TODO
	}
	return *this;
}

LinearAllocator::~LinearAllocator(void)
{
	_allocator.allocated = 0;
	if (_allocator.ownsMemory && _allocator.memory)
	{
		FreeMem(_allocator.memory, _allocator.totalSize, DE_MEMORY_TAG_LINEAR_ALLOCATOR);
	}
	_allocator.memory = 0;
	_allocator.totalSize = 0;
	_allocator.ownsMemory = false;
}

//****************************************************************************//

void	*LinearAllocator::LinearAllocatorAllocate(uint64 size)
{
	if (_allocator.memory)
	{
		if (_allocator.allocated + size > _allocator.totalSize)
		{
			uint64 remaining = _allocator.totalSize - _allocator.allocated;
			DE_ERROR("linear_allocator_allocate - Tried to allocate %lluB, only %lluB remaining.", size, remaining);
			
			return 0;
		}

		void *block = ((uint8 *)_allocator.memory) + _allocator.allocated;
		_allocator.allocated += size;
		
		return block;
	}

	DE_ERROR("linear_allocator_allocate - provided allocator not initialized.");

	return 0;
}

void	LinearAllocator::LinearAllocatorFreeAll(void)
{
	if (_allocator.memory)
	{
		_allocator.allocated = 0;
		SetMemory(_allocator.memory, _allocator.totalSize);
	}
}


// void	LinearAllocator::LinearAllocatorCreate(uint64 totalSize, void *memory, linearAlloc *allocator)
// {
// 	if (allocator)
// 	{
// 		allocator->totalSize = totalSize;
// 		allocator->allocated = 0;
// 		allocator->ownsMemory = memory == 0;
// 		if (memory)
// 		{
// 			allocator->memory = memory;
// 		}
// 		else
// 		{
// 			allocator->memory = Mallocate(totalSize, DE_MEMORY_TAG_LINEAR_ALLOCATOR);
// 		}
// 	}
// }

// void	LinearAllocator::LinearAllocatorDestroy(linearAlloc *allocator)
// {
// 	if (allocator)
// 	{
// 		allocator->allocated = 0;
// 		if (allocator->ownsMemory && allocator->memory)
// 		{
// 			FreeMem(allocator->memory, allocator->totalSize, DE_MEMORY_TAG_LINEAR_ALLOCATOR);
// 		}
// 		allocator->memory = 0;
// 		allocator->totalSize = 0;
// 		allocator->ownsMemory = false;
// 	}
// }
