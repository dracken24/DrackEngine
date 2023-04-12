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

LinearAllocator::LinearAllocator(void)
{
}

LinearAllocator::LinearAllocator(uint64 totalSize, void *memory)
{
	_totalSize = totalSize;
	_allocated = 0;
	_ownsMemory = memory == 0;
	if (memory)
	{
		_memory = memory;
	}
	else
	{
		_memory = Mallocate(totalSize, DE_MEMORY_TAG_LINEAR_ALLOCATOR);
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
	_allocated = 0;
	if (_ownsMemory && _memory)
	{
		FreeMem(_memory, _totalSize, DE_MEMORY_TAG_LINEAR_ALLOCATOR);
	}
	_memory = 0;
	_totalSize = 0;
	_ownsMemory = false;
}

//****************************************************************************//

void	*LinearAllocator::LinearAllocatorAllocate(uint64 size)
{
	if (_memory)
	{
		if (_allocated + size > _totalSize)
		{
			uint64 remaining = _totalSize - _allocated;
			DE_ERROR("linear_allocator_allocate - Tried to allocate %lluB, only %lluB remaining.", size, remaining);
			
			return 0;
		}

		void *block = ((uint8 *)_memory) + _allocated;
		_allocated += size;
		
		return block;
	}

	DE_ERROR("linear_allocator_allocate - provided allocator not initialized.");

	return 0;
}

void	LinearAllocator::LinearAllocatorFreeAll(void)
{
	if (_memory)
	{
		_allocated = 0;
		SetMemory(_memory, _totalSize);
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
