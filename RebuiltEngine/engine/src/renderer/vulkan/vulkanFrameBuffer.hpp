/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 07-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE:    vulkanFrameBuffer.hpp     *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

// Has a reference to the attachements that are render to.
// Use to relay the swapchain to acrually render out image.

#ifndef VULKAN_FRAME_BUFFER_HPP
# define VULKAN_FRAME_BUFFER_HPP

# include <renderer/vulkan/vulkanTypes.inl>

void	VulkanFramebufferCreate(
			vulkanContext *context,
			vulkanRenderpass *renderpass,		// Renderpass that the framebuffer will be associated with.
			uint32 width,						// Width of the framebuffer.
			uint32 height,						// Height of the framebuffer.
			uint32 attachmentCount,				// Number of attachments.	
			VkImageView *attachments,			// The view of the attachments.
			vulkanFramebuffer *framebuffer);	// Out pointer to the framebuffer object.

void	VulkanFramebufferDestroy(vulkanContext *context, vulkanFramebuffer *framebuffer);

#endif
