#pragma once

#include <defines.hpp>

#include <string>

typedef enum memory_tag
{
	// For temporary use. Should be assigned one of the below or have a new tag created.
	DE_MEMORY_TAG_UNKNOWN,
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
} memory_tag;

DE_API void initialize_memory();
DE_API void shutdown_memory();

DE_API void* kallocate(uint64 size, memory_tag tag);

DE_API void kfree(void* block, uint64 size, memory_tag tag);

DE_API void* kzero_memory(void* block, uint64 size);

DE_API void* kcopy_memory(void* dest, const void* source, uint64 size);

DE_API void* kset_memory(void* dest, sint32 value, uint64 size);

DE_API std::string get_memory_usage_str();
