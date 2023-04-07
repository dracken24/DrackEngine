/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 31-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	  vulkanBackend.cpp       *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include <renderer/vulkan/vulkanCommandBuffer.hpp>
#include <renderer/vulkan/vulkanRenderpass.hpp>
#include <renderer/vulkan/vulkanSwapchain.hpp>
#include <renderer/vulkan/vulkanPlatform.hpp>
#include <renderer/vulkan/vulkanBackend.hpp>
#include <renderer/vulkan/vulkanDevice.hpp>
#include <renderer/vulkan/vulkanTypes.inl>

#include <containers/arrayDinamic.hpp>

#include <platform/platform.hpp>

#include <core/deString.hpp>
#include <core/logger.hpp>

// static Vulkan context
static vulkanContext	context;
static VulkanSwapchain	vkImageSwapchain;
// static uint32 cachedFramebufferWidth = 0;
// static uint32 cachedFramebufferHeight = 0;

VKAPI_ATTR VkBool32 VKAPI_ATTR VkDebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageTypes,
	const VkDebugUtilsMessengerCallbackDataEXT *callbackData,
	void *user_data);

sint32	FindMemoryIndex(uint32 typeFilter, uint32 propertyFlags);
void	CreateCommandBuffers(rendererBackend *backend);
// void	RegenerateFramebuffers(rendererBackend *backend, vulkanSwapchain *swapchain,
// 			vulkanRenderpass *renderpass);

// 1: Start the initialization of vulkan platform
bl8 vulkanRendererBackendInitialize(rendererBackend *backend, const char *applicationName,
									struct platformState *platState)
{
	context.findMemoryIndex = FindMemoryIndex;

	// TODO: custom allocator.
	context.allocator = 0;

	// ApplicationGetFramebufferSize(&cachedFramebufferWidth, &cachedFramebufferHeight);
	// context.framebufferWidth = (cachedFramebufferWidth != 0) ? cachedFramebufferWidth : 800;
	// context.framebufferHeight = (cachedFramebufferHeight != 0) ? cachedFramebufferHeight : 600;
	// cached_framebufferWidth = 0;
	// cached_framebufferHeight = 0;

	// Setup Vulkan instance.
	VkApplicationInfo appInfo = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
	appInfo.apiVersion = VK_API_VERSION_1_2;
	appInfo.pApplicationName = applicationName;
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "DrackEngine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);

	VkInstanceCreateInfo create_info = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
	create_info.pApplicationInfo = &appInfo;

	// Obtain a list of required extensions
	const char **requiredExtensions = (const char **)DE_ArrayCreate(DE_ARRAY_DIN_DEFAULT_CAPACITY, sizeof(const char *));
	DE_ArrayPush(requiredExtensions, &VK_KHR_SURFACE_EXTENSION_NAME); // Generic surface extension
	PlatformGetRequiredExtensionNames(&requiredExtensions);			  // Platform-specific extension(s)

#if defined(_DEBUG)
	DE_ArrayPush(requiredExtensions, &VK_EXT_DEBUG_UTILS_EXTENSION_NAME); // debug utilities

	DE_DEBUG("Required extensions:");
	uint32 length = DE_ArrayLength(requiredExtensions);
	for (uint32 i = 0; i < length; ++i)
	{
		DE_DEBUG(requiredExtensions[i]);
	}
#endif

	create_info.enabledExtensionCount = DE_ArrayLength(requiredExtensions);
	create_info.ppEnabledExtensionNames = requiredExtensions;

	// Validation layers.
	const char **requiredValidationLayerNames = 0;
	uint32 requiredValidationLayerCount = 0;

// If validation should be done, get a list of the required validation layert names
// and make sure they exist. Validation layers should only be enabled on non-release builds.
#if defined(_DEBUG)
	DE_INFO("Validation layers enabled. Enumerating...");

	// The list of validation layers required.
	requiredValidationLayerNames = (const char **)DE_ArrayCreate(DE_ARRAY_DIN_DEFAULT_CAPACITY, sizeof(const char *));
	DE_ArrayPush(requiredValidationLayerNames, &"VK_LAYER_KHRONOS_validation");
	requiredValidationLayerCount = DE_ArrayLength(requiredValidationLayerNames);

	// Obtain a list of available validation layers
	uint32 availableLayerCount = 0;
	VK_CHECK(vkEnumerateInstanceLayerProperties(&availableLayerCount, 0));
	VkLayerProperties *availableLayers = (VkLayerProperties *)DE_ArrayReserve(VkLayerProperties, availableLayerCount);
	VK_CHECK(vkEnumerateInstanceLayerProperties(&availableLayerCount, availableLayers));

	// Verify all required layers are available.
	for (uint32 i = 0; i < requiredValidationLayerCount; ++i)
	{
		DE_INFO("Searching for layer: %s...", requiredValidationLayerNames[i]);
		bl8 found = false;
		for (uint32 j = 0; j < availableLayerCount; ++j)
		{
			if (StrCmp(requiredValidationLayerNames[i], availableLayers[j].layerName))
			{
				found = true;
				DE_INFO("Found.");
				break;
			}
		}

		if (!found)
		{
			DE_FATAL("Required validation layer is missing: %s", requiredValidationLayerNames[i]);
			return false;
		}
	}
	DE_INFO("All required validation layers are present.");
#endif

	create_info.enabledLayerCount = requiredValidationLayerCount;
	create_info.ppEnabledLayerNames = requiredValidationLayerNames;

	VK_CHECK(vkCreateInstance(&create_info, context.allocator, &context.instance));
	DE_INFO("Vulkan Instance created.");

	// Debugger
#if defined(_DEBUG)
	DE_DEBUG("Creating Vulkan debugger...");
	uint32 logSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT; //|
																																										 //    VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT};
	debugCreateInfo.messageSeverity = logSeverity;
	debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;

	debugCreateInfo.pfnUserCallback = VkDebugCallback;

	PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
		context.instance, "vkCreateDebugUtilsMessengerEXT");

	DE_ASSERT_MSG(func, "Failed to create debug messenger!");
	VK_CHECK(func(context.instance, &debugCreateInfo, context.allocator, &context.debugMessenger));
	DE_DEBUG("Vulkan debugger created.");
#endif

	// Surface
	DE_DEBUG("Creating Vulkan surface...");
	if (!PlatformCreateVulkanSurface(platState, &context))
	{
		DE_ERROR("Failed to create platform surface!");
		return (false);
	}
	DE_DEBUG("Vulkan surface created.\n");

	// Device creation
	if (!VulkanDeviceCreate(&context))
	{
		DE_ERROR("Failed to create device!");
		return (false);
	}

	// Swapchain creation
	vkImageSwapchain.VulkanSwapchainCreate(&context, context.framebufferWidth,
		context.framebufferHeight, &context.swapchain);

	VulkanRenderpassCreate(&context, &context.mainRenderpass,
		0, 0, context.framebufferWidth, context.framebufferHeight,
		0.0f, 0.0f, 0.2f, 1.0f,
		1.0f, 0);

	CreateCommandBuffers(backend);

	DE_INFO("Vulkan renderer initialized successfully.");

	return (true);
}

// Close the vulkan engine
void vulkanRendererBackendShutdown(rendererBackend *backend)
{
	// Command buffers
	for (uint32 i = 0; i < context.swapchain.imageCount; ++i)
	{
		if (context.graphicsCommandBuffers[i].handle)
		{
			VulkanCommandBfferFree(
				&context,
				context.device.graphicsCommandPool,
				&context.graphicsCommandBuffers[i]);
			context.graphicsCommandBuffers[i].handle = 0;
		}
	}

	// Renderpass
	DE_DEBUG("Destroying Vulkan renderpass...");
	VulkanRenderpassDestroy(&context, &context.mainRenderpass);
	
	vkImageSwapchain.VulkanSwapchainDestroy(&context, &context.swapchain);

	DE_DEBUG("Destroying Vulkan device...");
	VulkanDeviceDestroy(&context);

	DE_DEBUG("Destroying Vulkan surface...");
	if (context.surface)
	{
		vkDestroySurfaceKHR(context.instance, context.surface, context.allocator);
		context.surface = 0;
	}

	DE_DEBUG("Destroying Vulkan debugger...");
	if (context.debugMessenger)
	{
		PFN_vkDestroyDebugUtilsMessengerEXT func =
			(PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(context.instance, "vkDestroyDebugUtilsMessengerEXT");
		func(context.instance, context.debugMessenger, context.allocator);
	}

	DE_DEBUG("Destroying Vulkan instance...");
	if (context.instance)
		vkDestroyInstance(context.instance, context.allocator);
}

void vulkanRendererBackendOnResized(rendererBackend *backend, uint16 width, uint16 height)
{
}

// Start mount a frame for rendering
bl8 vulkanRendererBackendBeginFrame(rendererBackend *backend, fl32 deltaTime)
{
	return (true);
}

// Frame is done, present it to the screen
bl8 vulkanRendererBackendEndFrame(rendererBackend *backend, fl32 deltaTime)
{
	return (true);
}

VKAPI_ATTR VkBool32 VKAPI_ATTR VkDebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageTypes,
	const VkDebugUtilsMessengerCallbackDataEXT *callbackData,
	void *user_data)
{
	switch (messageSeverity)
	{
	default:
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
		DE_ERROR(callbackData->pMessage);
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
		DE_WARNING(callbackData->pMessage);
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
		DE_INFO(callbackData->pMessage);
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
		DE_TRACE(callbackData->pMessage);
		break;
	}

	return (VK_FALSE);
}

sint32 FindMemoryIndex(uint32 typeFilter, uint32 propertyFlags)
{
	VkPhysicalDeviceMemoryProperties memory_properties;
	vkGetPhysicalDeviceMemoryProperties(context.device.physicalDevice, &memory_properties);

	for (uint32 i = 0; i < memory_properties.memoryTypeCount; ++i)
	{
		// Check each memory type to see if its bit is set to 1.
		if (typeFilter & (1 << i) && (memory_properties.memoryTypes[i].propertyFlags & propertyFlags) == propertyFlags)
		{
			return i;
		}
	}

	DE_WARNING("Unable to find suitable memory type!");
	return -1;
}

void	CreateCommandBuffers(rendererBackend *backend)
{
	if (!context.graphicsCommandBuffers)
	{
		context.graphicsCommandBuffers = (vulkanCommandBuffer *)DE_ArrayReserve(vulkanCommandBuffer,
			context.swapchain.imageCount);

		for (uint32 i = 0; i < context.swapchain.imageCount; ++i)
		{
			SetMemory(&context.graphicsCommandBuffers[i], sizeof(vulkanCommandBuffer));
		}
	}

	for (uint32 i = 0; i < context.swapchain.imageCount; ++i)
	{
		if (context.graphicsCommandBuffers[i].handle)
		{
			VulkanCommandBfferFree(
				&context,
				context.device.graphicsCommandPool,
				&context.graphicsCommandBuffers[i]);
		}
		SetMemory(&context.graphicsCommandBuffers[i], sizeof(vulkanCommandBuffer));
		VulkanCommandBufferAllocate(
			&context,
			context.device.graphicsCommandPool,
			true,
			&context.graphicsCommandBuffers[i]);
	}

	DE_DEBUG("Vulkan command buffers created.");
}

// void regenerate_framebuffers(renderer_backend *backend, vulkan_swapchain *swapchain, vulkan_renderpass *renderpass)
// {
// 	for (u32 i = 0; i < swapchain->image_count; ++i)
// 	{
// 		// TODO: make this dynamic based on the currently configured attachments
// 		u32 attachment_count = 2;
// 		VkImageView attachments[] = {
// 			swapchain->views[i],
// 			swapchain->depth_attachment.view};

// 		vulkan_framebuffer_create(
// 			&context,
// 			renderpass,
// 			context.framebuffer_width,
// 			context.framebuffer_height,
// 			attachment_count,
// 			attachments,
// 			&context.swapchain.framebuffers[i]);
// 	}
// }
