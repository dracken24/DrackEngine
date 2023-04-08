/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 07-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE:       vulkanFence.cpp        *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include <renderer/vulkan/vulkanFence.hpp>

#include <core/logger.hpp>

void	VulkanFenceCreate(vulkanContext *context, bl8 createSignaled,
			vulkanFence *outFence)
{

	// Make sure to signal the fence if required.
	outFence->isSignaled = createSignaled;
	VkFenceCreateInfo fence_create_info = {VK_STRUCTURE_TYPE_FENCE_CREATE_INFO};
	if (outFence->isSignaled)
	{
		fence_create_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
	}

	VK_CHECK(vkCreateFence(
		context->device.logicalDevice,
		&fence_create_info,
		context->allocator,
		&outFence->handle));
}

void	VulkanFenceDestroy(vulkanContext *context, vulkanFence *fence)
{
	if (fence->handle)
	{
		vkDestroyFence(
			context->device.logicalDevice,
			fence->handle,
			context->allocator);
		fence->handle = 0;
	}
	fence->isSignaled = false;
}

bl8		VulkanFenceWait(vulkanContext *context, vulkanFence *fence, uint64 timeoutNs)
{
	if (!fence->isSignaled)
	{
		VkResult result = vkWaitForFences(
			context->device.logicalDevice,
			1,
			&fence->handle,
			true,
			timeoutNs);
		switch (result)
		{
		case VK_SUCCESS:
			fence->isSignaled = true;
			return true;
		case VK_TIMEOUT:
			DE_WARNING("vk_fence_wait - Timed out");
			break;
		case VK_ERROR_DEVICE_LOST:
			DE_ERROR("vk_fence_wait - VK_ERROR_DEVICE_LOST.");
			break;
		case VK_ERROR_OUT_OF_HOST_MEMORY:
			DE_ERROR("vk_fence_wait - VK_ERROR_OUT_OF_HOST_MEMORY.");
			break;
		case VK_ERROR_OUT_OF_DEVICE_MEMORY:
			DE_ERROR("vk_fence_wait - VK_ERROR_OUT_OF_DEVICE_MEMORY.");
			break;
		default:
			DE_ERROR("vk_fence_wait - An unknown error has occurred.");
			break;
		}
	}
	else
	{
		// If already signaled, do not wait.
		return true;
	}

	return false;
}

void	VulkanFenceReset(vulkanContext *context, vulkanFence *fence)
{
	if (fence->isSignaled)
	{
		VK_CHECK(vkResetFences(context->device.logicalDevice, 1, &fence->handle));
		fence->isSignaled = false;
	}
}
