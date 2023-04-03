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
}	vulkanDevice;

typedef struct	vulkanContext
{
	VkInstance					instance;
	VkAllocationCallbacks		*allocator;
	VkSurfaceKHR				surface;

#if defined(_DEBUG)
	VkDebugUtilsMessengerEXT	debugMessenger;
#endif

	vulkanDevice				device;
}	vulkanContext;

#endif
