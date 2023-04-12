#include <core/deMemory.hpp>

#include <core/logger.hpp>
#include <core/deString.hpp>
#include <platform/platform.hpp>

struct memoryStats
{
	uint64	allocTotal;
	uint64	allocTagged[DE_MEMORY_TAG_MAX_TAGS];
};

static const	char *memoryTagStrings[DE_MEMORY_TAG_MAX_TAGS + 1] = {
	"UNKNOWN     ",
	"LINEAR_ALLOC",
	"ARRAY       ",
	"DARRAY      ",
	"DICT        ",
	"RING_QUEUE  ",
	"BST         ",
	"STRING      ",
	"APPLICATION ",
	"JOB         ",
	"TEXTURE     ",
	"MAT_INST    ",
	"RENDERER    ",
	"GAME        ",
	"TRANSFORM   ",
	"ENTITY      ",
	"ENTITY_NODE ",
	"SCENE       ",
	"\n  TOTAL       "
};

typedef struct	memorySystemState
{
	struct memoryStats stats;
	uint64 allocCount;
}	memorySystemState;

// Pointer to system state.
static memorySystemState	*statePtr;

void	InitializeMemory(uint64* memoryRequirement, void* state)
{
	*memoryRequirement = sizeof(memorySystemState);
	if (state == 0)
	{
		return;
	}

	statePtr = (memorySystemState *)state;
	statePtr->allocCount = 0;

	PlatformSetMemory(&statePtr->stats, sizeof(statePtr->stats));
}

void	ShutdownMemory(void* state)
{
	statePtr = 0;
}

void*	Mallocate(uint64 size, memoryTag tag)
{
	if (tag == DE_MEMORY_TAG_UNKNOWN)
	{
		DE_WARNING("Mallocate called using DE_MEMORY_TAG_UNKNOWN. Re-class this allocation.");
	}

	if (statePtr)
	{
		statePtr->stats.allocTotal += size;
		statePtr->stats.allocTagged[tag] += size;
		statePtr->allocCount++;
	}

	// TODO: Memory alignment
	void* block = PlatformAllocate(size, false);
	PlatformSetMemory(block, size);

	return block;
}

void	FreeMem(void* block, uint64 size, memoryTag tag)
{
	if (tag == DE_MEMORY_TAG_UNKNOWN)
	{
		DE_WARNING("FreeMem called using DE_MEMORY_TAG_UNKNOWN. Re-class this allocation.");
	}

	if (statePtr)
	{
		statePtr->stats.allocTotal -= size;
		statePtr->stats.allocTagged[tag] -= size;
	}

	// TODO: Memory alignment
	PlatformFree(block, false);
}

void*	SetMemory(void* block, uint64 size)
{
	return PlatformSetMemory(block, size);
}

void*	CopyMemory(void* dest, const void* source, uint64 size)
{
	return PlatformCopyMemory(dest, source, size);
}

void*	SetMemory(void* dest, sint32 value, uint64 size)
{
	return PlatformSetMemory(dest, value, size);
}

std::string	GetMemoryUsageStr(void)
{
	const uint64 gib = 1024 * 1024 * 1024;
	const uint32 mib = 1024 * 1024;
	const uint16 kib = 1024;

	char buffer[8000] = "Memory in use for the engine :\n\n";
	uint64 offset = strlen(buffer);
	for (uint32 i = 0; i <= DE_MEMORY_TAG_MAX_TAGS; ++i)
	{
		char unit[4] = " Xb";
		float amount = 1.0f;

		if (i < DE_MEMORY_TAG_MAX_TAGS)
			amount = (float)statePtr->stats.allocTagged[i];
		else
			amount = (float)statePtr->stats.allocTotal;

		if (statePtr->stats.allocTagged[i] >= gib || (statePtr->stats.allocTotal
			>= gib && i >= DE_MEMORY_TAG_MAX_TAGS))
		{
			unit[1] = 'G';
			amount /= (float)gib;
		}
		else if (statePtr->stats.allocTagged[i] >= mib || (statePtr->stats.allocTotal
			>= mib && i >= DE_MEMORY_TAG_MAX_TAGS))
		{
			unit[1] = 'M';
			amount /= (float)mib;
		}
		else if (statePtr->stats.allocTagged[i] >= kib || (statePtr->stats.allocTotal
			>= kib && i >= DE_MEMORY_TAG_MAX_TAGS))
		{
			unit[1] = 'K';
			amount /= (float)kib;
		}
		else
		{
			unit[1] = 'B';
			unit[2] = 0;
		}

		sint32 length = snprintf(buffer + offset, 8000, "  %s: %.2f%s\n", memoryTagStrings[i], amount, unit);
		offset += length;
	}

	std::string outString = buffer;

	return (outString);
}

uint64	GetMemoryAllocCount(void)
{
	if (statePtr)
	{
		return statePtr->allocCount;
	}

	return 0;
}
