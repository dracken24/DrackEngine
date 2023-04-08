/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 03-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE:     vulkanSwapchain.cpp      *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "renderer/vulkan/vulkanSwapchain.hpp"
#include <renderer/vulkan/vulkanDevice.hpp>
#include <renderer/vulkan/vulkanImage.hpp>

#include <core/logger.hpp>
#include <core/deMemory.hpp>

// #include <vulkan_core.h>

void	create(vulkanContext *context, uint32 width, uint32 height, vulkanSwapchain *swapchain);
void	destroy(vulkanContext *context, vulkanSwapchain *swapchain);

void	VulkanSwapchainCreate(vulkanContext *context, uint32 width, uint32 height,
			vulkanSwapchain *swapchain)
{
	// Simply create a new one.
	create(context, width, height, swapchain);
}

void	VulkanSwapchainRecreate(vulkanContext *context, uint32 width, uint32 height,
			vulkanSwapchain *swapchain)
{
	// Destroy the old and create a new one.
	destroy(context, swapchain);
	create(context, width, height, swapchain);
}

void	VulkanSwapchainDestroy(vulkanContext *context, vulkanSwapchain *swapchain)
{
	destroy(context, swapchain);
}

bl8		VulkanSwapchainAquireNextImageIndex(vulkanContext *context, vulkanSwapchain *swapchain,
			uint64 timeout, VkSemaphore availableSemaphore, VkFence fence, uint32 *imageIndex)
{
	VkResult result = vkAcquireNextImageKHR(
		context->device.logicalDevice,
		swapchain->handle,
		timeout,
		availableSemaphore,
		fence,
		imageIndex);

	if (result == VK_ERROR_OUT_OF_DATE_KHR)
	{
		// Trigger swapchain recreation, then boot out of the render loop.
		VulkanSwapchainRecreate(context, context->framebufferWidth, context->framebufferHeight, swapchain);
		return false;
	}
	else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
	{
		DE_FATAL("Failed to acquire swapchain image!");
		return false;
	}

	return true;
}

void	VulkanSwapchainPresent(vulkanContext *context, vulkanSwapchain *swapchain,
			VkQueue graphicQueue,VkQueue presentQueue, VkSemaphore presentSemaphore, uint32 imageIndex)
{
	// Return the image to the swapchain for presentation.
	VkPresentInfoKHR present_info = {VK_STRUCTURE_TYPE_PRESENT_INFO_KHR};
	present_info.waitSemaphoreCount = 1;
	present_info.pWaitSemaphores = &presentSemaphore;
	present_info.swapchainCount = 1;
	present_info.pSwapchains = &swapchain->handle;
	present_info.pImageIndices = &imageIndex;
	present_info.pResults = 0;

	VkResult result = vkQueuePresentKHR(presentQueue, &present_info);
	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
	{
		// Swapchain is out of date, suboptimal or a framebuffer resize has occurred. Trigger swapchain recreation.
		VulkanSwapchainRecreate(context, context->framebufferWidth, context->framebufferHeight, swapchain);
	}
	else if (result != VK_SUCCESS)
	{
		DE_FATAL("Failed to present swap chain image!");
	}

	// Increment (and loop) the index.
	context->currentFrame = (context->currentFrame + 1) % swapchain->maxFramesInFlight;
}

void	create(vulkanContext *context, uint32 width, uint32 height, vulkanSwapchain *swapchain)
{
	VkExtent2D swapchain_extent = {width, height};
	swapchain->maxFramesInFlight = 2;

	// Choose a swap surface format.
	bl8 found = false;
	for (uint32 i = 0; i < context->device.swapchainSupport.formatCount; ++i)
	{
		VkSurfaceFormatKHR format = context->device.swapchainSupport.formats[i];
		// Preferred formats
		if (format.format == VK_FORMAT_B8G8R8A8_UNORM &&
			format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		{
			swapchain->imageFormat = format;
			found = true;
			break;
		}
	}

	if (!found)
	{
		swapchain->imageFormat = context->device.swapchainSupport.formats[0];
	}

	VkPresentModeKHR present_mode = VK_PRESENT_MODE_FIFO_KHR;
	for (uint32 i = 0; i < context->device.swapchainSupport.presentModeCount; ++i)
	{
		VkPresentModeKHR mode = context->device.swapchainSupport.presentMode[i];
		if (mode == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			present_mode = mode;
			break;
		}
	}

	// Requery swapchain support.
	VulkanDeviceQuerySwapchainSupport(
		context->device.physicalDevice,
		context->surface,
		&context->device.swapchainSupport);

	// Swapchain extent
	if (context->device.swapchainSupport.capabilities.currentExtent.width != UINT32_MAX)
	{
		swapchain_extent = context->device.swapchainSupport.capabilities.currentExtent;
	}

	// Clamp to the value allowed by the GPU.
	VkExtent2D min = context->device.swapchainSupport.capabilities.minImageExtent;
	VkExtent2D max = context->device.swapchainSupport.capabilities.maxImageExtent;
	swapchain_extent.width = DE_CLAMP(swapchain_extent.width, min.width, max.width);
	swapchain_extent.height = DE_CLAMP(swapchain_extent.height, min.height, max.height);

	uint32 image_count = context->device.swapchainSupport.capabilities.minImageCount + 1;
	if (context->device.swapchainSupport.capabilities.maxImageCount > 0 && image_count
		> context->device.swapchainSupport.capabilities.maxImageCount)
	{
		image_count = context->device.swapchainSupport.capabilities.maxImageCount;
	}

	// Swapchain create info
	VkSwapchainCreateInfoKHR swapchain_create_info = {VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR};
	swapchain_create_info.surface = context->surface;
	swapchain_create_info.minImageCount = image_count;
	swapchain_create_info.imageFormat = swapchain->imageFormat.format;
	swapchain_create_info.imageColorSpace = swapchain->imageFormat.colorSpace;
	swapchain_create_info.imageExtent = swapchain_extent;
	swapchain_create_info.imageArrayLayers = 1;
	swapchain_create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	// Setup the queue family indices
	if (context->device.graphicsQueueIndex != context->device.presentQueueIndex)
	{
		uint32 queueFamilyIndices[] = {
			(uint32)context->device.graphicsQueueIndex,
			(uint32)context->device.presentQueueIndex};
		swapchain_create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		swapchain_create_info.queueFamilyIndexCount = 2;
		swapchain_create_info.pQueueFamilyIndices = queueFamilyIndices;
	}
	else
	{
		swapchain_create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		swapchain_create_info.queueFamilyIndexCount = 0;
		swapchain_create_info.pQueueFamilyIndices = 0;
	}

	swapchain_create_info.preTransform = context->device.swapchainSupport.capabilities.currentTransform;
	swapchain_create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapchain_create_info.presentMode = present_mode;
	swapchain_create_info.clipped = VK_TRUE;
	swapchain_create_info.oldSwapchain = 0;

	VK_CHECK(vkCreateSwapchainKHR(context->device.logicalDevice, &swapchain_create_info, context->allocator, &swapchain->handle));

	// Start with a zero frame index.
	context->currentFrame = 0;

	// Images
	swapchain->imageCount = 0;
	VK_CHECK(vkGetSwapchainImagesKHR(context->device.logicalDevice, swapchain->handle, &swapchain->imageCount, 0));
	if (!swapchain->images)
	{
		swapchain->images = (VkImage *)Mallocate(sizeof(VkImage) * swapchain->imageCount, DE_MEMORY_TAG_RENDERER);
	}
	if (!swapchain->views)
	{
		swapchain->views = (VkImageView *)Mallocate(sizeof(VkImageView) * swapchain->imageCount, DE_MEMORY_TAG_RENDERER);
	}
	VK_CHECK(vkGetSwapchainImagesKHR(context->device.logicalDevice, swapchain->handle, &swapchain->imageCount, swapchain->images));

	// Views
	for (uint32 i = 0; i < swapchain->imageCount; ++i)
	{
		VkImageViewCreateInfo view_info = {VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO};
		view_info.image = swapchain->images[i];
		view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
		view_info.format = swapchain->imageFormat.format;
		view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		view_info.subresourceRange.baseMipLevel = 0;
		view_info.subresourceRange.levelCount = 1;
		view_info.subresourceRange.baseArrayLayer = 0;
		view_info.subresourceRange.layerCount = 1;

		VK_CHECK(vkCreateImageView(context->device.logicalDevice, &view_info, context->allocator, &swapchain->views[i]));
	}

	// Depth resources
	if (!VulkanDeviceDetectDepthFormat(&context->device))
	{
		context->device.depthFormat = VK_FORMAT_UNDEFINED;
		DE_FATAL("Failed to find a supported format!");
	}

	// Create depth image and its view.
	VulkanImageCreate(
		context,
		VK_IMAGE_TYPE_2D,
		swapchain_extent.width,
		swapchain_extent.height,
		context->device.depthFormat,
		VK_IMAGE_TILING_OPTIMAL,
		VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		true,
		VK_IMAGE_ASPECT_DEPTH_BIT,
		&swapchain->depthAttachment);

	DE_INFO("Swapchain created successfully.");
}

void	destroy(vulkanContext *context, vulkanSwapchain *swapchain)
{
	vkDeviceWaitIdle(context->device.logicalDevice);
	VulkanImageDestroy(context, &swapchain->depthAttachment);

	// Only destroy the views, not the images, since those are owned by the swapchain and are thus
	// destroyed when it is.
	for (uint32 i = 0; i < swapchain->imageCount; ++i)
	{
		vkDestroyImageView(context->device.logicalDevice, swapchain->views[i], context->allocator);
	}

	vkDestroySwapchainKHR(context->device.logicalDevice, swapchain->handle, context->allocator);
}
