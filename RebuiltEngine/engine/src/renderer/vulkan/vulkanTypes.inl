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

	VkCommandPool						graphicsCommandPool;

	VkFormat							depthFormat;
}	vulkanDevice;

typedef struct	vulkanImage
{
    VkImage handle;
    VkDeviceMemory memory;
    VkImageView view;
    uint32 width;
    uint32 height;
}	vulkanImage;

typedef enum	vulkanRenderPassState
{
	READY,
	RECORDING,
	IN_RENDER_PASS,
	RECORDING_ENDED,
	SUBMITTED,
	NOT_ALLOCATED
}	vulkanRenderPassState;

typedef struct vulkanRenderpass
{
	VkRenderPass handle;
	fl32 x, y, w, h;
	fl32 r, g, b, a;

	fl32	depth;
	uint32	stencil;

	vulkanRenderPassState	state;
}	vulkanRenderpass;

typedef struct	vulkanFramebuffer
{
	VkFramebuffer		handle;
	uint32				attachmentCount;
	VkImageView			*attachments;
	vulkanRenderpass	*renderpass;
}	vulkanFramebuffer;

typedef struct vulkanSwapchain
{
	VkSurfaceFormatKHR			imageFormat;
	uint8						maxFramesInFlight;
	VkSwapchainKHR				handle;
	uint32						imageCount;
	VkImage						*images;
	VkImageView					*imageViews;
	VkImageView					*views;

	vulkanImage					depthAttachment;

	// framebuffers used for on-screen rendering.
	vulkanFramebuffer			*framebuffers;
}	vulkanSwapchain;

typedef enum	vulkanCommandBufferState
{
	DE_COMMAND_BUFFER_STATE_READY,
	DE_COMMAND_BUFFER_STATE_RECORDING,
	DE_COMMAND_BUFFER_STATE_IN_RENDER_PASS,
	DE_COMMAND_BUFFER_STATE_RECORDING_ENDED,
	DE_COMMAND_BUFFER_STATE_SUBMITTED,
	DE_COMMAND_BUFFER_STATE_NOT_ALLOCATED
}	vulkanCommandBufferState;

typedef struct	vulkanCommandBuffer
{
	VkCommandBuffer				handle;

	// Command buffer state.
	vulkanCommandBufferState	state;
}	vulkanCommandBuffer;

typedef struct	vulkanFence
{
	VkFence	handle;
	bl8		isSignaled;
}	vulkanFence;

typedef struct	vulkanContext
{
	// The framebuffer's current width and height.
	uint32						framebufferWidth;
	uint32						framebufferHeight;

	// Current generation of framebuffer size. If it does not match framebuffer_size_last_generation,
	// a new one should be generated.
	uint64						framebufferSizeGeneration;

	// The generation of the framebuffer when it was last created. Set to framebuffer_size_generation
	// when updated.
	uint64						framebufferSizeLastGeneration;

	vulkanSwapchain				swapchain;
	vulkanRenderpass			mainRenderpass;

	VkInstance					instance;
	VkAllocationCallbacks		*allocator;
	VkSurfaceKHR				surface;

	// myArray
	vulkanCommandBuffer			*graphicsCommandBuffers;

	VkSemaphore					*imageAvailableSemaphores;
	VkSemaphore					*queueCompleteSemaphores;

	uint32						InFlightFenceCount;
	vulkanFence					*inFlightFences;
	vulkanFence					**imagesInFlight;

#if defined(_DEBUG)
	VkDebugUtilsMessengerEXT	debugMessenger;
#endif

	vulkanDevice				device;

	uint32						imageIndex;
	uint32						currentFrame;

	bl8							recreatingSwapchain;

	sint32 (*findMemoryIndex)(uint32 typeFilter, uint32 propertyFlags);
}	vulkanContext;

#endif
