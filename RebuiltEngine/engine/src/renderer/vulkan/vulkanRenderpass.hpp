/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 06-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	 vulkanRenderpass.hpp     *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef VULKAN_RENDERPASS_HPP
# define VULKAN_RENDERPASS_HPP

#include <renderer/vulkan/vulkanTypes.inl>

void	VulkanRenderpassCreate(vulkanContext* context, vulkanRenderpass* renderpass,
			fl32 x, fl32 y, fl32 w, fl32 h,
			fl32 r, fl32 g, fl32 b, fl32 a,
			fl32 depth, uint32 stencil);

void	VulkanRenderpassDestroy(vulkanContext* context, vulkanRenderpass* renderpass);

void	VulkanRenderpassBegin(vulkanCommandBuffer* commandBuffer, vulkanRenderpass* renderpass,
			VkFramebuffer frameBuffer);

void	VulkanRenderpassEnd(vulkanCommandBuffer *commandBuffer, vulkanRenderpass *renderpass);

#endif
