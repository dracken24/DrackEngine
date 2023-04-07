/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 06-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE:    vulkanFrameBuffer.cpp     *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include <renderer/vulkan/vulkanFrameBuffer.hpp>

#include <core/deMemory.hpp>

void	VulkanFramebufferCreate(vulkanContext *context, vulkanRenderpass *renderpass,
			uint32 width, uint32 height, uint32 attachmentCount,
			VkImageView *attachments, vulkanFramebuffer *framebuffer)
{
	// Take a copy of the attachments, renderpass and attachment count
	framebuffer->attachments = (VkImageView *)Mallocate(sizeof(VkImageView)
		* attachmentCount, DE_MEMORY_TAG_RENDERER);

	for (uint32 i = 0; i < attachmentCount; ++i)
	{
		framebuffer->attachments[i] = attachments[i];
	}
	framebuffer->renderpass = renderpass;
	framebuffer->attachmentCount = attachmentCount;

	// Creation info for the framebuffer
	VkFramebufferCreateInfo framebufferCreateInfo = {VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO};
	framebufferCreateInfo.renderPass = renderpass->handle;
	framebufferCreateInfo.attachmentCount = attachmentCount;
	framebufferCreateInfo.pAttachments = framebuffer->attachments;
	framebufferCreateInfo.width = width;
	framebufferCreateInfo.height = height;
	framebufferCreateInfo.layers = 1;

	VK_CHECK(vkCreateFramebuffer(
		context->device.logicalDevice,
		&framebufferCreateInfo,
		context->allocator,
		&framebuffer->handle));
}

void	VulkanFramebufferDestroy(vulkanContext *context, vulkanFramebuffer *framebuffer)
{
	vkDestroyFramebuffer(context->device.logicalDevice, framebuffer->handle, context->allocator);

	if (framebuffer->attachments)
	{
		FreeMem(framebuffer->attachments, sizeof(VkImageView)
			* framebuffer->attachmentCount, DE_MEMORY_TAG_RENDERER);
		framebuffer->attachments = 0;
	}

	framebuffer->handle = 0;
	framebuffer->attachmentCount = 0;
	framebuffer->renderpass = 0;
}
