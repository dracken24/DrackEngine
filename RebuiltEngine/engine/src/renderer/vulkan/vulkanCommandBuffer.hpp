/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 06-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE:    vulkanCommandBuffer.hpp   *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef VULKAN_COMMAND_BUFFER_HPP
# define VULKAN_COMMAND_BUFFER_HPP

# include <renderer/vulkan/vulkanTypes.inl>

void	VulkanCommandBufferAllocate(vulkanContext *context, VkCommandPool pool,
			bl8 isPrimary, vulkanCommandBuffer *commandBuffer);

void	VulkanCommandBfferFree(vulkanContext *context, VkCommandPool pool,
			vulkanCommandBuffer *commandBuffer);

void	VulkanCommandBufferBegin(vulkanCommandBuffer *commandBuffer, bl8 isSingleUse,
			bl8 isRenderpassContinue, bl8 isSimultaneousUse);

void	VulkanCommandBufferEnd(vulkanCommandBuffer *commandBuffer);

void	VulkanCommandBufferUpdateSubmitted(vulkanCommandBuffer *commandBuffer);

void	VulkanCommandBufferReset(vulkanCommandBuffer *commandBuffer);

/**
 * Allocates and begins recording to commandBuffer.
 */
void	VulkanCommandBufferAllocateAndBeginSingleUse(vulkanContext *context,
			VkCommandPool pool, vulkanCommandBuffer *commandBuffer);

/**
 * Ends recording, submits to and waits for queue operation and frees the provided command buffer.
 */
void	VulkanCommandBufferEndSingleUse(vulkanContext *context, VkCommandPool pool,
			vulkanCommandBuffer *commandBuffer, VkQueue queue);

#endif
