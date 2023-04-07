/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 07-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE:       vulkanFence.hpp        *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef VULKAN_FENCE_HPP
# define VULKAN_FENCE_HPP

# include <renderer/vulkan/vulkanTypes.inl>

void	VulkanFenceCreate(vulkanContext *context, bl8 createSignaled,
			vulkanFence *outFence);

void	VulkanFenceDestroy(vulkanContext *context, vulkanFence *fence);

bl8		VulkanFenceWait(vulkanContext *context, vulkanFence *fence, uint64 timeoutNs);

void	VulkanFenceReset(vulkanContext *context, vulkanFence *fence);

#endif
