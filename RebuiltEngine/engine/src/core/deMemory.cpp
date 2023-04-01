/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 28-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	    deMemory.cpp          *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "core/deMemory.hpp"
#include "core/logger.hpp"
#include "platform/Platform.hpp"
#include "core/application.hpp"

struct memoryStats
{
	uint64	allocTotal;
	uint64	allocTagged[DE_MEMORY_TAG_MAX_TAGS];
};

static const char *memoryTagStrings[DE_MEMORY_TAG_MAX_TAGS + 1] = {
	"UNKNOWN    ",
	"ARRAY      ",
	"DARRAY     ",
	"DICT       ",
	"RING_QUEUE ",
	"BST        ",
	"STRING     ",
	"APPLICATION",
	"JOB        ",
	"TEXTURE    ",
	"MAT_INST   ",
	"RENDERER   ",
	"GAME       ",
	"TRANSFORM  ",
	"ENTITY     ",
	"ENTITY_NODE",
	"SCENE      ",
	"\n  TOTAL      "
};

static struct memoryStats		stats;

// Memory allocation function

void	InitMemory(void)
{
	Platform::PlatZeroMem(&stats, sizeof(struct memoryStats));
}

void	ShutdownMemory()
{
	
}

// void	AddMemoryTag(uint64 size, memoryTag tag)
// {
// 	if (tag == DE_MEMORY_TAG_UNKNOWN)
// 	{
// 		DE_WARNING("AddMemoryTag called using DE_MEMORY_TAG_UNKNOWN. Re-class this allocation.");
// 	}

// 	stats.allocTotal += size;
// 	stats.allocTagged[tag] += size;
// }

void	*DE_Malloc(uint64 size, memoryTag tag)
{
	if (tag == DE_MEMORY_TAG_UNKNOWN)
	{
		DE_WARNING("DE_Malloc called using MEMORY_TAG_UNKNOWN. Re-class this allocation.");
	}

	stats.allocTotal += size;
	stats.allocTagged[tag] += size;

	// TODO: Memory alignment
	void *block = Platform::PlatformAllocator(size, false);
	Platform::PlatZeroMem(block, size);
	return block;
}

void *DE_MemSet(void *block, uint64 size)
{
	return (Platform::PlatZeroMem(block, size));
}

void	DE_Free(void *block, uint64 size, memoryTag tag)
{
	if (tag == DE_MEMORY_TAG_UNKNOWN)
	{
		DE_WARNING("DE_Free called using DE_MEMORY_TAG_UNKNOWN. Re-class this allocation.");
	}

	stats.allocTotal -= size;
	stats.allocTagged[tag] -= size;

	// TODO: Memory alignment
	Platform::PlatformFree(block, false);
}

void *DE_CopyMemory(void *dest, const void *source, uint64 size)
{
	return (Platform::PlatCopyMem(dest, source, size));
}

void *DE_SetMemory(void *dest, sint32 value, uint64 size)
{
	return (Platform::PlatSetMem(dest, value, size));
}

std::string	DE_GetMemoryUsageString(memoryTag tag)
{
	const uint64 gib = 1024 * 1024 * 1024;
	const uint32 mib = 1024 * 1024;
	const uint16 kib = 1024;

	char buffer[8000] = "\nMemory in use for the engine :\n\n";
	uint64 offset = strlen(buffer);
	for (uint32 i = 0; i <= DE_MEMORY_TAG_MAX_TAGS; ++i)
	{
		char unit[4] = " Xb";
		float amount = 1.0f;

		if (i < DE_MEMORY_TAG_MAX_TAGS)
		{
			if (stats.allocTagged[i] >= gib)
			{
				unit[1] = 'G';
				amount = stats.allocTagged[i] / (float)gib;
			}
			else if (stats.allocTagged[i] >= mib)
			{
				unit[1] = 'M';
				amount = stats.allocTagged[i] / (float)mib;
			}
			else if (stats.allocTagged[i] >= kib)
			{
				unit[1] = 'K';
				amount = stats.allocTagged[i] / (float)kib;
			}
			else
			{
				unit[1] = 'B';
				unit[2] = 0;
				amount = (float)stats.allocTagged[i];
			}
		}
		else
		{
			if (stats.allocTotal >= gib)
			{
				unit[1] = 'G';
				amount = stats.allocTotal / (float)gib;
			}
			else if (stats.allocTotal >= mib)
			{
				unit[1] = 'M';
				amount = stats.allocTotal / (float)mib;
			}
			else if (stats.allocTotal >= kib)
			{
				unit[1] = 'K';
				amount = stats.allocTotal / (float)kib;
			}
			else
			{
				unit[1] = 'B';
				unit[2] = 0;
				amount = (float)stats.allocTotal;
			}
			snprintf(buffer + offset, 8000, "  %s: %.2f%s\n", memoryTagStrings[i], amount, unit);
			break ;
		}

		sint32 length = snprintf(buffer + offset, 8000, "  %s: %.2f%s\n", memoryTagStrings[i], amount, unit);
		offset += length;
	}

	std::string outString = buffer;
	return (outString);
}
