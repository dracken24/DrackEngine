#include "kmemory.hpp"

#include "core/logger.hpp"
#include "core/kstring.hpp"
#include "platform/platform.hpp"

// TODO: Custom string lib
#include <string.h>
#include <stdio.h>

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

static struct memoryStats stats;

void initialize_memory()
{
	platform_zero_memory(&stats, sizeof(stats));
}

void shutdown_memory() {
}

void* kallocate(uint64 size, memory_tag tag) {
	if (tag == DE_MEMORY_TAG_UNKNOWN) {
		DE_WARNING("kallocate called using DE_MEMORY_TAG_UNKNOWN. Re-class this allocation.");
	}

	stats.allocTotal += size;
	stats.allocTagged[tag] += size;

	// TODO: Memory alignment
	void* block = platform_allocate(size, false);
	platform_zero_memory(block, size);
	return block;
}

void kfree(void* block, uint64 size, memory_tag tag) {
	if (tag == DE_MEMORY_TAG_UNKNOWN) {
		DE_WARNING("kfree called using DE_MEMORY_TAG_UNKNOWN. Re-class this allocation.");
	}

	stats.allocTotal -= size;
	stats.allocTagged[tag] -= size;

	// TODO: Memory alignment
	platform_free(block, false);
}

void* kzero_memory(void* block, uint64 size) {
	return platform_zero_memory(block, size);
}

void* kcopy_memory(void* dest, const void* source, uint64 size) {
	return platform_copy_memory(dest, source, size);
}

void* kset_memory(void* dest, sint32 value, uint64 size) {
	return platform_set_memory(dest, value, size);
}

std::string	get_memory_usage_str(void)
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
			amount = (float)stats.allocTagged[i];
		else
			amount = (float)stats.allocTotal;

		if (stats.allocTagged[i] >= gib || (stats.allocTotal >= gib && i >= DE_MEMORY_TAG_MAX_TAGS))
		{
			unit[1] = 'G';
			amount /= (float)gib;
		}
		else if (stats.allocTagged[i] >= mib || (stats.allocTotal >= mib && i >= DE_MEMORY_TAG_MAX_TAGS))
		{
			unit[1] = 'M';
			amount /= (float)mib;
		}
		else if (stats.allocTagged[i] >= kib || (stats.allocTotal >= kib && i >= DE_MEMORY_TAG_MAX_TAGS))
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
		if (i >= DE_MEMORY_TAG_MAX_TAGS)
			break;
		offset += length;
	}

	std::string outString = buffer;
	return (outString);
}
