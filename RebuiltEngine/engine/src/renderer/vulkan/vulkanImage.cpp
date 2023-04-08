/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 05-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	   vulkanImage.cpp        *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include <renderer/vulkan/vulkanImage.hpp>
#include <renderer/vulkan/vulkanDevice.hpp>

#include <core/deMemory.hpp>
#include <core/logger.hpp>

VulkanImage::VulkanImage(void)
{
}

VulkanImage::~VulkanImage(void)
{
}

void	VulkanImage::VulkanImageCreate(vulkanContext *context, VkImageType imageType, uint32 width, uint32 height,
			VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags memoryFlags,
				bl32 createView, VkImageAspectFlags viewAspectFlags, vulkanImage *image)
{
	// Copy params
	image->width = width;
	image->height = height;

	// Creation info.
	VkImageCreateInfo imageCreateInfo = {VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO};
	imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
	imageCreateInfo.extent.width = width;
	imageCreateInfo.extent.height = height;
	imageCreateInfo.extent.depth = 1; // TODO: Support configurable depth.
	imageCreateInfo.mipLevels = 4;	// TODO: Support mip mapping
	imageCreateInfo.arrayLayers = 1;	// TODO: Support number of layers in the image.
	imageCreateInfo.format = format;
	imageCreateInfo.tiling = tiling;
	imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	imageCreateInfo.usage = usage;
	imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;		   // TODO: Configurable sample count.
	imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE; // TODO: Configurable sharing mode.

	VK_CHECK(vkCreateImage(context->device.logicalDevice, &imageCreateInfo, context->allocator, &image->handle));

	// Query memory requirements.
	VkMemoryRequirements memoryRequirements;
	vkGetImageMemoryRequirements(context->device.logicalDevice, image->handle, &memoryRequirements);

	sint32 memoryType = context->findMemoryIndex(memoryRequirements.memoryTypeBits, memoryFlags);
	if (memoryType == -1)
	{
		DE_ERROR("Required memory type not found. Image not valid.");
	}

	// Allocate memory
	VkMemoryAllocateInfo memoryAllocateInfo = {VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO};
	memoryAllocateInfo.allocationSize = memoryRequirements.size;
	memoryAllocateInfo.memoryTypeIndex = memoryType;
	VK_CHECK(vkAllocateMemory(context->device.logicalDevice, &memoryAllocateInfo, context->allocator, &image->memory));

	// Bind the memory
	VK_CHECK(vkBindImageMemory(context->device.logicalDevice, image->handle, image->memory, 0)); // TODO: configurable memory offset.

	// Create view
	if (createView)
	{
		image->view = 0;
		VulkanImageViewCreate(context, format, image, viewAspectFlags);
	}
}

void	VulkanImage::VulkanImageViewCreate(vulkanContext *context, VkFormat format,
			vulkanImage *image, VkImageAspectFlags aspectFlags)
{
	VkImageViewCreateInfo viewCreateInfo = {VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO};
	viewCreateInfo.image = image->handle;
	viewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D; // TODO: Make configurable.
	viewCreateInfo.format = format;
	viewCreateInfo.subresourceRange.aspectMask = aspectFlags;

	// TODO: Make configurable
	viewCreateInfo.subresourceRange.baseMipLevel = 0;
	viewCreateInfo.subresourceRange.levelCount = 1;
	viewCreateInfo.subresourceRange.baseArrayLayer = 0;
	viewCreateInfo.subresourceRange.layerCount = 1;

	VK_CHECK(vkCreateImageView(context->device.logicalDevice, &viewCreateInfo, context->allocator, &image->view));
}

void	VulkanImage::VulkanImageDestroy(vulkanContext *context, vulkanImage *image)
{
	if (image->view)
	{
		vkDestroyImageView(context->device.logicalDevice, image->view, context->allocator);
		image->view = 0;
	}
	if (image->memory)
	{
		vkFreeMemory(context->device.logicalDevice, image->memory, context->allocator);
		image->memory = 0;
	}
	if (image->handle)
	{
		vkDestroyImage(context->device.logicalDevice, image->handle, context->allocator);
		image->handle = 0;
	}
}

