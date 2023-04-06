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

#include <core/logger.hpp>
#include <core/deMemory.hpp>

// #include <vulkan_core.h>

VulkanSwapchain::VulkanSwapchain(void)
{

}

VulkanSwapchain::~VulkanSwapchain(void)
{

}



void	VulkanSwapchain::VulkanSwapchainCreate(vulkanContext *context, uint32 width, uint32 height,
			vulkanSwapchain *swapchain)
{
	// Simply create a new one.
	create(context, width, height, swapchain);
}

void	VulkanSwapchain::VulkanSwapchainRecreate(vulkanContext *context, uint32 width, uint32 height,
			vulkanSwapchain *swapchain)
{
	// Destroy the old and create a new one.
	destroy(context, swapchain);
	create(context, width, height, swapchain);
}

void	VulkanSwapchain::VulkanSwapchainDestroy(vulkanContext *context, vulkanSwapchain *swapchain)
{
	destroy(context, swapchain);
}

bl8		VulkanSwapchain::VulkanSwapchainAquireNextImage(vulkanContext *context, vulkanSwapchain *swapchain,
			uint64 timeout, VkSemaphore availableSemaphore, VkFence fence, uint32 *imageIndex)
{
	VkResult result = vkAcquireNextImageKHR(context->device.logicalDevice, swapchain->handle,
		timeout, availableSemaphore, fence, imageIndex);

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

void	VulkanSwapchain::VulkanSwapchainPresent(vulkanContext *context, vulkanSwapchain *swapchain,
			VkQueue graphicQueue, VkQueue presentQueue, VkSemaphore presentSemaphore, uint32 imageIndex)

{
	// Return the image to the swapchain for presentation.
	VkPresentInfoKHR presentInfo = {VK_STRUCTURE_TYPE_PRESENT_INFO_KHR};	// Structure type.
	presentInfo.waitSemaphoreCount = 1;										// waiting for the semaphore to be signaled before presenting.
	presentInfo.pWaitSemaphores = &presentSemaphore;						// Semaphore to wait on before presenting.
	presentInfo.swapchainCount = 1;											// Number of swapchains to present to.
	presentInfo.pSwapchains = &swapchain->handle;							// Swapchain to present to.
	presentInfo.pImageIndices = &imageIndex;								// Index of the image to present.
	presentInfo.pResults = 0;												// Optional array of VkResult values for each swapchain.

	// Perform presentation of a render image to the swapchain.
	VkResult result = vkQueuePresentKHR(presentQueue, &presentInfo);
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

void	VulkanSwapchain::create(vulkanContext *context, uint32 width, uint32 height, vulkanSwapchain *swapchain)
{
	VkExtent2D swapchainExtent = {width, height};
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
	VulkanDeviceQuerySwapchainSupport(context->device.physicalDevice, context->surface,
		&context->device.swapchainSupport);

	// Swapchain extent
	if (context->device.swapchainSupport.capabilities.currentExtent.width != UINT32_MAX)
	{
		swapchainExtent = context->device.swapchainSupport.capabilities.currentExtent;
	}

	// Clamp to the value allowed by the GPU.
	VkExtent2D min = context->device.swapchainSupport.capabilities.minImageExtent;
	VkExtent2D max = context->device.swapchainSupport.capabilities.maxImageExtent;
	swapchainExtent.width = DE_CLAMP(swapchainExtent.width, min.width, max.width);
	swapchainExtent.height = DE_CLAMP(swapchainExtent.height, min.height, max.height);

	uint32 image_count = context->device.swapchainSupport.capabilities.minImageCount + 1;
	if (context->device.swapchainSupport.capabilities.maxImageCount > 0 && image_count
		> context->device.swapchainSupport.capabilities.maxImageCount)
	{
		image_count = context->device.swapchainSupport.capabilities.maxImageCount;
	}

	// Swapchain create info
	VkSwapchainCreateInfoKHR swapchainCreateInfo = {VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR};
	swapchainCreateInfo.surface = context->surface;
	swapchainCreateInfo.minImageCount = image_count;
	swapchainCreateInfo.imageFormat = swapchain->imageFormat.format;
	swapchainCreateInfo.imageColorSpace = swapchain->imageFormat.colorSpace;
	swapchainCreateInfo.imageExtent = swapchainExtent;
	swapchainCreateInfo.imageArrayLayers = 1;
	swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	// Setup the queue family indices
	if (context->device.graphicsQueueIndex != context->device.presentQueueIndex)
	{
		uint32 queueFamilyIndices[] = {
			(uint32)context->device.graphicsQueueIndex,
			(uint32)context->device.presentQueueIndex};
		swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		swapchainCreateInfo.queueFamilyIndexCount = 2;
		swapchainCreateInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else
	{
		swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		swapchainCreateInfo.queueFamilyIndexCount = 0;
		swapchainCreateInfo.pQueueFamilyIndices = 0;
	}

	swapchainCreateInfo.preTransform = context->device.swapchainSupport.capabilities.currentTransform;
	swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapchainCreateInfo.presentMode = present_mode;
	swapchainCreateInfo.clipped = VK_TRUE;
	swapchainCreateInfo.oldSwapchain = 0;

	VK_CHECK(vkCreateSwapchainKHR(context->device.logicalDevice, &swapchainCreateInfo, context->allocator, &swapchain->handle));

	// Start with a zero frame index.
	context->currentFrame = 0;

	// Images
	swapchain->imageCount = 0;
	VK_CHECK(vkGetSwapchainImagesKHR(context->device.logicalDevice, swapchain->handle, &swapchain->imageCount, 0));
	if (!swapchain->images)
	{
		swapchain->images = (VkImage *)Mallocate(sizeof(VkImage) * swapchain->imageCount, DE_MEMORY_TAG_RENDERER);
	}
	if (!swapchain->imageViews)
	{
		swapchain->imageViews = (VkImageView *)Mallocate(sizeof(VkImageView) * swapchain->imageCount, DE_MEMORY_TAG_RENDERER);
	}
	VK_CHECK(vkGetSwapchainImagesKHR(context->device.logicalDevice, swapchain->handle, &swapchain->imageCount, swapchain->images));

	// Views
	for (uint32 i = 0; i < swapchain->imageCount; ++i)
	{
		VkImageViewCreateInfo viewInfo = {VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO};
		viewInfo.image = swapchain->images[i];
		viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		viewInfo.format = swapchain->imageFormat.format;
		viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		viewInfo.subresourceRange.baseMipLevel = 0;
		viewInfo.subresourceRange.levelCount = 1;
		viewInfo.subresourceRange.baseArrayLayer = 0;
		viewInfo.subresourceRange.layerCount = 1;

		VK_CHECK(vkCreateImageView(context->device.logicalDevice, &viewInfo, context->allocator,
			&swapchain->imageViews[i]));
	}

	// Depth resources
	if (!VulkanDeviceDetectDepthFormat(&context->device))
	{
		context->device.depthFormat = VK_FORMAT_UNDEFINED;
		DE_FATAL("Failed to find a supported format!");
	}

	// Create depth image and its view.
	_image.VulkanImageCreate( context, VK_IMAGE_TYPE_2D, swapchainExtent.width, swapchainExtent.height,
		context->device.depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, true, VK_IMAGE_ASPECT_DEPTH_BIT, &swapchain->depthAttachment);

	DE_INFO("Swapchain created successfully.");
}

void	VulkanSwapchain::destroy(vulkanContext *context, vulkanSwapchain *swapchain)
{
	_image.VulkanImageDestroy(context, &swapchain->depthAttachment);

	// Only destroy the views, not the images, since those are owned by the swapchain and are thus
	// destroyed when it is.
	for (uint32 i = 0; i < swapchain->imageCount; ++i)
	{
		vkDestroyImageView(context->device.logicalDevice, swapchain->imageViews[i], context->allocator);
	}

	vkDestroySwapchainKHR(context->device.logicalDevice, swapchain->handle, context->allocator);
}
