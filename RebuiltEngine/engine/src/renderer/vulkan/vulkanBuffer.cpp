/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 16-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	   vulkanBuffer.cpp       *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include <renderer/vulkan/vulkanBuffer.hpp>

#include <renderer/vulkan/vulkanDevice.hpp>
#include <renderer/vulkan/vulkanCommandBuffer.hpp>
#include <renderer/vulkan/vulkanUtils.hpp>

#include <core/logger.hpp>
#include <core/deMemory.hpp>

//**********************************************************************//
//**                     Constructors / Destructor                    **//
//**********************************************************************//

VulkanBuffer::VulkanBuffer(void)
{

}

VulkanBuffer::VulkanBuffer(VulkanBuffer const &copy)
{
	if (this != &copy)
	{
		*this = copy;
	}
}

VulkanBuffer &VulkanBuffer::operator=(VulkanBuffer const &copy)
{
	if (this != &copy)
	{

	}

	return *this;
}

VulkanBuffer::~VulkanBuffer(void)
{

}

//**********************************************************************//
//**                          PUBLIC METHODS                          **//
//**********************************************************************//

bl8     VulkanBuffer::VulkanBufferCreate(vulkanContext *context, uint64 size, sint32 usage,
			uint32 memoryPropertyFlags, bl8 bindOnCreate, vulkanBuffer *outBuffer)
{
	SetMemory(outBuffer, sizeof(vulkanBuffer));
	outBuffer->totalSize = size;
	outBuffer->usage = usage;
	outBuffer->memoryPropertyFlags = memoryPropertyFlags;

	VkBufferCreateInfo bufferInfo = {VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO};
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE; // NOTE: Only used in one queue.

	VK_CHECK(vkCreateBuffer(context->device.logicalDevice, &bufferInfo, context->allocator, &outBuffer->handle));

	// Gather memory requirements.
	VkMemoryRequirements requirements;
	vkGetBufferMemoryRequirements(context->device.logicalDevice, outBuffer->handle, &requirements);
	outBuffer->memoryIndex = context->findMemoryIndex(requirements.memoryTypeBits, outBuffer->memoryPropertyFlags);
	if (outBuffer->memoryIndex == -1)
	{
		DE_ERROR("Unable to create vulkan buffer because the required memory type index was not found.");
		return false;
	}

	// Allocate memory info
	VkMemoryAllocateInfo allocateInfo = {VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO};
	allocateInfo.allocationSize = requirements.size;
	allocateInfo.memoryTypeIndex = (uint32)outBuffer->memoryIndex;

	// Allocate the memory.
	VkResult result = vkAllocateMemory(
		context->device.logicalDevice,
		&allocateInfo,
		context->allocator,
		&outBuffer->memory);

	if (result != VK_SUCCESS)
	{
		DE_ERROR("Unable to create vulkan buffer because the required memory allocation failed. Error: %i", result);
		return false;
	}

	if (bindOnCreate)
	{
		VulkanBufferBind(context, outBuffer, 0);
	}

	return true;
}

void    VulkanBuffer::VulkanBufferDestroy(vulkanContext *context, vulkanBuffer *buffer)
{
	if (buffer->memory)
	{
		vkFreeMemory(context->device.logicalDevice, buffer->memory, context->allocator);
		buffer->memory = 0;
	}
	if (buffer->handle)
	{
		vkDestroyBuffer(context->device.logicalDevice, buffer->handle, context->allocator);
		buffer->handle = 0;
	}

	buffer->totalSize = 0;
	buffer->usage = 0;
	buffer->isLocked = false;
}

bl8     VulkanBuffer::VulkanBufferResize(vulkanContext *context, uint64 newSize, vulkanBuffer *buffer,
			VkQueue queue, VkCommandPool pool)
{
	// Create new buffer.
	VkBufferCreateInfo bufferInfo = {VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO};
	bufferInfo.size = newSize;
	bufferInfo.usage = buffer->usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE; // NOTE: Only used in one queue.

	VkBuffer newBuffer;
	VK_CHECK(vkCreateBuffer(context->device.logicalDevice, &bufferInfo, context->allocator, &newBuffer));

	// Gather memory requirements.
	VkMemoryRequirements requirements;
	vkGetBufferMemoryRequirements(context->device.logicalDevice, newBuffer, &requirements);

	// Allocate memory info
	VkMemoryAllocateInfo allocateInfo = {VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO};
	allocateInfo.allocationSize = requirements.size;
	allocateInfo.memoryTypeIndex = (uint32)buffer->memoryIndex;

	// Allocate the memory.
	VkDeviceMemory newMemory;
	VkResult result = vkAllocateMemory(context->device.logicalDevice, &allocateInfo, context->allocator, &newMemory);
	if (result != VK_SUCCESS)
	{
		DE_ERROR("Unable to resize vulkan buffer because the required memory allocation failed. Error: %i", result);
		return false;
	}

	// Bind the new buffer's memory
	VK_CHECK(vkBindBufferMemory(context->device.logicalDevice, newBuffer, newMemory, 0));

	// Copy over the data
	VulkanBufferCopyTo(context, pool, 0, queue, buffer->handle, 0, newBuffer, 0, buffer->totalSize);

	// Make sure anything potentially using these is finished.
	vkDeviceWaitIdle(context->device.logicalDevice);

	// Destroy the old
	if (buffer->memory)
	{
		vkFreeMemory(context->device.logicalDevice, buffer->memory, context->allocator);
		buffer->memory = 0;
	}
	if (buffer->handle)
	{
		vkDestroyBuffer(context->device.logicalDevice, buffer->handle, context->allocator);
		buffer->handle = 0;
	}

	// Set new properties
	buffer->totalSize = newSize;
	buffer->memory = newMemory;
	buffer->handle = newBuffer;

	return true;
}

void    VulkanBuffer::VulkanBufferBind(vulkanContext *context, vulkanBuffer *buffer, uint64 offset)
{
	VK_CHECK(vkBindBufferMemory(context->device.logicalDevice, buffer->handle, buffer->memory, offset));
}

void    *VulkanBuffer::VulkanBufferLockMemory(vulkanContext *context, vulkanBuffer *buffer, uint64 offset,
			uint64 size, uint32 flags)
{
	void *data;
	VK_CHECK(vkMapMemory(context->device.logicalDevice, buffer->memory, offset, size, flags, &data));
	return data;
}

void    VulkanBuffer::VulkanBufferUnlockMemory(vulkanContext *context, vulkanBuffer *buffer)
{
	vkUnmapMemory(context->device.logicalDevice, buffer->memory);
}

void    VulkanBuffer::VulkanBufferLoadData(vulkanContext *context, vulkanBuffer *buffer, uint64 offset, uint64 size,
			uint32 flags, const void *data)
{
	void *dataPtr;
	VK_CHECK(vkMapMemory(context->device.logicalDevice, buffer->memory, offset, size, flags, &dataPtr));
	CopyMemory(dataPtr, data, size);
	vkUnmapMemory(context->device.logicalDevice, buffer->memory);
}

void    VulkanBuffer::VulkanBufferCopyTo(vulkanContext *context, VkCommandPool pool, VkFence fence, VkQueue queue,
			VkBuffer source, uint64 sourceOffset, VkBuffer dest, uint64 destOffset, uint64 size)
{
	vkQueueWaitIdle(queue);
	// Create a one-time-use command buffer.
	vulkanCommandBuffer tempCommandBuffer;
	VulkanCommandBufferAllocateAndBeginSingleUse(context, pool, &tempCommandBuffer);

	// Prepare the copy command and add it to the command buffer.
	VkBufferCopy copyRegion;
	copyRegion.srcOffset = sourceOffset;
	copyRegion.dstOffset = destOffset;
	copyRegion.size = size;

	vkCmdCopyBuffer(tempCommandBuffer.handle, source, dest, 1, &copyRegion);

	// Submit the buffer for execution and wait for it to complete.
	VulkanCommandBufferEndSingleUse(context, pool, &tempCommandBuffer, queue);
}
