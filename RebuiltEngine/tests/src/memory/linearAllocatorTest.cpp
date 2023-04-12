/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 11-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE:   linearAllocatorTest.cpp    *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "linearAllocatorTest.hpp"
#include "../testManager.hpp"
#include "../expect.hpp"

#include <defines.hpp>

#include <memory/linearAllocator.hpp>

uint8	LinearAllocatorShouldCreateAndDestroy()
{
	linearAlloc alloc;
	LinearAllocatorCreate(sizeof(uint64), 0, &alloc);

	ExpectShouldNotBe(0, alloc.memory);
	ExpectShouldBe(sizeof(uint64), alloc.totalSize);
	ExpectShouldBe(0, alloc.allocated);

	LinearAllocatorDestroy(&alloc);

	ExpectShouldBe(0, alloc.memory);
	ExpectShouldBe(0, alloc.totalSize);
	ExpectShouldBe(0, alloc.allocated);

	return true;
}

uint8 LinearAllocatorSingleAllocationAllSpace()
{
	linearAlloc alloc;
	LinearAllocatorCreate(sizeof(uint64), 0, &alloc);

	// Single allocation.
	void *block = LinearAllocatorAllocate(&alloc,sizeof(uint64));

	// Validate it
	ExpectShouldNotBe(0, block);
	ExpectShouldBe(sizeof(uint64), alloc.allocated);

	LinearAllocatorDestroy(&alloc);

	return true;
}

uint8	LinearAllocatorMultiAllocationAllSpace()
{
	uint64 maxAllocs = 1024;
	linearAlloc alloc;
	LinearAllocatorCreate(sizeof(uint64) * maxAllocs, 0, &alloc);

	// Multiple allocations - full.
	void *block;
	for (uint64 i = 0; i < maxAllocs; ++i)
	{
		block = LinearAllocatorAllocate(&alloc, sizeof(uint64));
		// Validate it
		ExpectShouldNotBe(0, block);
		ExpectShouldBe(sizeof(uint64) * (i + 1), alloc.allocated);
	}

	LinearAllocatorDestroy(&alloc);

	return true;
}

uint8	LinearAllocatorMultiAllocationOverAllocate()
{
	uint64 max_allocs = 3;
	linearAlloc alloc;
	LinearAllocatorCreate(sizeof(uint64) * max_allocs, 0, &alloc);

	// Multiple allocations - full.
	void *block;
	for (uint64 i = 0; i < max_allocs; ++i)
	{
		block = LinearAllocatorAllocate(&alloc, sizeof(uint64));
		// Validate it
		ExpectShouldNotBe(0, block);
		ExpectShouldBe(sizeof(uint64) * (i + 1), alloc.allocated);
	}

	DE_DEBUG("Note: The following error is intentionally caused by this test.");

	// Ask for one more allocation. Should error and return 0.
	block = LinearAllocatorAllocate(&alloc, sizeof(uint64));
	// Validate it - allocated should be unchanged.
	ExpectShouldBe(0, block);
	ExpectShouldBe(sizeof(uint64) * (max_allocs), alloc.allocated);

	LinearAllocatorDestroy(&alloc);

	return true;
}

uint8	LinearAllocatorMultiAllocationAllSpaceThenFree()
{
	uint64 max_allocs = 1024;
	linearAlloc alloc;
	LinearAllocatorCreate(sizeof(uint64) * max_allocs, 0, &alloc);

	// Multiple allocations - full.
	void *block;
	for (uint64 i = 0; i < max_allocs; ++i)
	{
		block = LinearAllocatorAllocate(&alloc, sizeof(uint64));
		// Validate it
		ExpectShouldNotBe(0, block);
		ExpectShouldBe(sizeof(uint64) * (i + 1), alloc.allocated);
	}

	// Validate that pointer is reset.
	LinearAllocatorFreeAll(&alloc);
	ExpectShouldBe(0, alloc.allocated);

	LinearAllocatorDestroy(&alloc);

	return true;
}

void	LinearAllocatorRegisterTests(void)
{
	TestManagerRegisterTest(LinearAllocatorShouldCreateAndDestroy, (char *)"Linear allocator should create and destroy");
	TestManagerRegisterTest(LinearAllocatorSingleAllocationAllSpace, (char *)"Linear allocator single alloc for all space");
	TestManagerRegisterTest(LinearAllocatorMultiAllocationAllSpace, (char *)"Linear allocator multi alloc for all space");
	TestManagerRegisterTest(LinearAllocatorMultiAllocationOverAllocate, (char *)"Linear allocator try over allocate");
	TestManagerRegisterTest(LinearAllocatorMultiAllocationAllSpaceThenFree, (char *)"Linear allocator allocated should be 0 after free_all");
}
