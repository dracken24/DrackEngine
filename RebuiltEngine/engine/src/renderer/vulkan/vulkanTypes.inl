/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 26-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	   vulkanTypes.inl        *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef VULKANTYPES_INL
# define VULKANTYPES_INL

# include <defines.hpp>
# include <core/asserts.hpp>

# include <vulkan/vulkan.h>

// Checks the given expression's return value against VK_SUCCESS.
# define VK_CHECK(expr)					\
	{									\
		DE_ASSERT(expr == VK_SUCCESS);	\
	}

typedef struct	vulkanImage
{
    VkImage handle;
    VkDeviceMemory memory;
    VkImageView view;
    uint32 width;
    uint32 height;
}	vulkanImage;

typedef struct	vulkanSwapchainSupportInfo
{
	VkSurfaceCapabilitiesKHR	capabilities;
	uint32						formatCount;
	VkSurfaceFormatKHR			*formats;
	uint32						presentModeCount;
	VkPresentModeKHR			*presentMode;
}	vulkanSwapchainSupportInfo;

typedef struct	vulkanDevice
{
	VkPhysicalDevice			physicalDevice;
	VkDevice					logicalDevice;
	vulkanSwapchainSupportInfo	swapchainSupport;
	sint32						graphicsQueueIndex;
	sint32						presentQueueIndex;
	sint32						transferQueueIndex;

	VkQueue		graphicsQueue;
	VkQueue		presentQueue;
	VkQueue		transferQueue;

	VkPhysicalDeviceProperties			properties;
	VkPhysicalDeviceFeatures			features;
	VkPhysicalDeviceMemoryProperties	memory;

	VkFormat							depthFormat;
}	vulkanDevice;

typedef struct vulkanSwapchain
{
	VkSurfaceFormatKHR			imageFormat;
	uint8						maxFramesInFlight;
	VkSwapchainKHR				handle;
	uint32						imageCount;
	VkImage						*images;
	VkImageView					*imageViews;
	vulkanImage					depthAttachment;
	// VkExtent2D					extent;
}	vulkanSwapchain;

typedef struct	vulkanContext
{
	// The framebuffer's current width and height.
	uint32						framebufferWidth;
	uint32						framebufferHeight;

	uint32						currentFrame;

	VkInstance					instance;
	VkAllocationCallbacks		*allocator;
	VkSurfaceKHR				surface;

#if defined(_DEBUG)
	VkDebugUtilsMessengerEXT	debugMessenger;
#endif

	vulkanDevice				device;

	sint32 (*findMemoryIndex)(uint32 typeFilter, uint32 propertyFlags);
}	vulkanContext;

#endif
