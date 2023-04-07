/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 06-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE:    vulkanCommandBuffer.cpp   *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include <renderer/vulkan/vulkanCommandBuffer.hpp>

#include <core/deMemory.hpp>

void	VulkanCommandBufferAllocate(vulkanContext *context, VkCommandPool pool,
			bl8 isPrimary, vulkanCommandBuffer *commandBuffer)
{

	SetMemory(commandBuffer, sizeof(commandBuffer));

	VkCommandBufferAllocateInfo allocateInfo = {VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO};
	allocateInfo.commandPool = pool;
	allocateInfo.level = isPrimary ? VK_COMMAND_BUFFER_LEVEL_PRIMARY : VK_COMMAND_BUFFER_LEVEL_SECONDARY;
	allocateInfo.commandBufferCount = 1;
	allocateInfo.pNext = 0;

	commandBuffer->state = DE_COMMAND_BUFFER_STATE_NOT_ALLOCATED;
	VK_CHECK(vkAllocateCommandBuffers(
		context->device.logicalDevice,
		&allocateInfo,
		&commandBuffer->handle));
	commandBuffer->state = DE_COMMAND_BUFFER_STATE_READY;
}

void	VulkanCommandBfferFree(vulkanContext *context, VkCommandPool pool,
			vulkanCommandBuffer *commandBuffer)
{
	vkFreeCommandBuffers(
		context->device.logicalDevice,
		pool,
		1,
		&commandBuffer->handle);

	commandBuffer->handle = 0;
	commandBuffer->state = DE_COMMAND_BUFFER_STATE_NOT_ALLOCATED;
}

void	VulkanCommandBufferBegin(vulkanCommandBuffer *commandBuffer, bl8 isSingleUse,
			bl8 isRenderpassContinue, bl8 isSimultaneousUse)
{

	VkCommandBufferBeginInfo beginInfo = {VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};
	beginInfo.flags = 0;
	if (isSingleUse)
	{
		beginInfo.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	}
	if (isRenderpassContinue)
	{
		beginInfo.flags |= VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
	}
	if (isSimultaneousUse)
	{
		beginInfo.flags |= VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
	}

	VK_CHECK(vkBeginCommandBuffer(commandBuffer->handle, &beginInfo));
	commandBuffer->state = DE_COMMAND_BUFFER_STATE_RECORDING;
}

void	VulkanCommandBufferEnd(vulkanCommandBuffer *commandBuffer)
{
	VK_CHECK(vkEndCommandBuffer(commandBuffer->handle));
	commandBuffer->state = DE_COMMAND_BUFFER_STATE_RECORDING_ENDED;
}

void	VulkanCommandBufferUpdateSubmitted(vulkanCommandBuffer *commandBuffer)
{
	commandBuffer->state = DE_COMMAND_BUFFER_STATE_SUBMITTED;
}

void	VulkanCommandBufferReset(vulkanCommandBuffer *commandBuffer)
{
	commandBuffer->state = DE_COMMAND_BUFFER_STATE_READY;
}

void	VulkanCommandBufferAllocateAndBeginSingleUse(vulkanContext *context,
			VkCommandPool pool, vulkanCommandBuffer *commandBuffer)
{
	VulkanCommandBufferAllocate(context, pool, true, commandBuffer);
	VulkanCommandBufferBegin(commandBuffer, true, false, false);
}

void	VulkanCommandBufferEndSingleUse(vulkanContext *context, VkCommandPool pool,
			vulkanCommandBuffer *commandBuffer, VkQueue queue)
{

	// End the command buffer.
	VulkanCommandBufferEnd(commandBuffer);

	// Submit the queue
	VkSubmitInfo submitInfo = {VK_STRUCTURE_TYPE_SUBMIT_INFO};
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer->handle;
	VK_CHECK(vkQueueSubmit(queue, 1, &submitInfo, 0));

	// Wait for it to finish
	VK_CHECK(vkQueueWaitIdle(queue));

	// Free the command buffer.
	VulkanCommandBfferFree(context, pool, commandBuffer);
}
