/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 11-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	 linearAllocator.hpp      *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef LINEAR_ALLOCATOR_HPP
# define LINEAR_ALLOCATOR_HPP

# include <defines.hpp>

typedef struct	linearAlloc
{
	uint64	totalSize;
	uint64	allocated;
	void	*memory;
	bl8		ownsMemory;
	uint32	_systemTotalAllocatorSize;
}	linearAlloc;


DE_API void		LinearAllocatorCreate(uint64 totalSize, void *memory, linearAlloc *allocator);
DE_API void		LinearAllocatorDestroy(linearAlloc *allocator);

DE_API void		*LinearAllocatorAllocate(linearAlloc *allocator, uint64 size);
DE_API void		LinearAllocatorFreeAll(linearAlloc *allocator);

#endif
