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

// typedef struct	linearAlloc
// {
// 	uint64	totalSize;
// 	uint64	allocated;
// 	void	*memory;
// 	bl8		ownsMemory;
// }	linearAlloc;

class	LinearAllocator
{
	public:
		LinearAllocator(void);
		LinearAllocator(uint64 totalSize, void *memory);

		LinearAllocator(LinearAllocator const &src);
		LinearAllocator	&operator=(LinearAllocator const &rhs);
		~LinearAllocator(void);
		// DE_API void	LinearAllocatorCreate(uint64 totalSize, void *memory, linearAlloc *allocator);
		// DE_API void	LinearAllocatorDestroy(linearAlloc *allocator);

	public:
		DE_API void	*LinearAllocatorAllocate(uint64 size);
		DE_API void	LinearAllocatorFreeAll(void);
	
	// private:
		uint64	_totalSize;
		uint64	_allocated;
		void	*_memory;
		bl8		_ownsMemory;
};


#endif
