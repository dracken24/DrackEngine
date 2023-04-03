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

#include "vulkanBackend.hpp"

#include "vulkanTypes.inl"
#include "vulkanPlatform.hpp"
#include "vulkanDevice.hpp"

#include "core/logger.hpp"
#include "core/deString.hpp"

#include "containers/arrayDinamic.hpp"

#include "platform/platform.hpp"

// static Vulkan context
static vulkanContext context;

VKAPI_ATTR VkBool32 VKAPI_ATTR	VkDebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageTypes,
				const VkDebugUtilsMessengerCallbackDataEXT *callbackData,
					void *user_data);

bl8		vulkanRendererBackendInitialize(rendererBackend* backend, const char* applicationName,
			struct platformState* platState)
{
	// TODO: custom allocator.
	context.allocator = 0;

	// Setup Vulkan instance.
	VkApplicationInfo appInfo = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
	appInfo.apiVersion = VK_API_VERSION_1_2;
	appInfo.pApplicationName = applicationName;
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "Kohi Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);

	VkInstanceCreateInfo create_info = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
	create_info.pApplicationInfo = &appInfo;

	// Obtain a list of required extensions
	const char **requiredExtensions = (const char **)ArrayDinCreate(const char *);
	ArrayDinPush(requiredExtensions, &VK_KHR_SURFACE_EXTENSION_NAME);  // Generic surface extension
	PlatformGetRequiredExtensionNames(&requiredExtensions);       // Platform-specific extension(s)

#if defined(_DEBUG)
	ArrayDinPush(requiredExtensions, &VK_EXT_DEBUG_UTILS_EXTENSION_NAME);  // debug utilities

	DE_DEBUG("Required extensions:");
	uint32 length = ArrayDinLength(requiredExtensions);
	for (uint32 i = 0; i < length; ++i)
	{
		DE_DEBUG(requiredExtensions[i]);
	}
#endif

	create_info.enabledExtensionCount = ArrayDinLength(requiredExtensions);
	create_info.ppEnabledExtensionNames = requiredExtensions;

	// Validation layers.
	const char** requiredValidationLayerNames = 0;
	uint32 requiredValidationLayerCount = 0;

// If validation should be done, get a list of the required validation layert names
// and make sure they exist. Validation layers should only be enabled on non-release builds.
#if defined(_DEBUG)
	DE_INFO("Validation layers enabled. Enumerating...");

	// The list of validation layers required.
	requiredValidationLayerNames = (const char **)ArrayDinCreate(const char*);
	ArrayDinPush(requiredValidationLayerNames, &"VK_LAYER_KHRONOS_validation");
	requiredValidationLayerCount = ArrayDinLength(requiredValidationLayerNames);

	// Obtain a list of available validation layers
	uint32 availableLayerCount = 0;
	VK_CHECK(vkEnumerateInstanceLayerProperties(&availableLayerCount, 0));
	VkLayerProperties *availableLayers = (VkLayerProperties *)ArrayDinReserve(VkLayerProperties, availableLayerCount);
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
	uint32  logSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT
							| VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
								| VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;  //|
																	  //    VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT};
	debugCreateInfo.messageSeverity = logSeverity;
	debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
		| VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT
			| VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;

	debugCreateInfo.pfnUserCallback = VkDebugCallback;

	PFN_vkCreateDebugUtilsMessengerEXT func =	(PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
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

	DE_INFO("Vulkan renderer initialized successfully.");

	return (true);
}

void	vulkanRendererBackendShutdown(rendererBackend* backend)
{

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

void	vulkanRendererBackendOnResized(rendererBackend* backend, uint16 width, uint16 height)
{
}

bl8		vulkanRendererBackendBeginFrame(rendererBackend* backend, fl32 deltaTime)
{
	return (true);
}

bl8		vulkanRendererBackendEndFrame(rendererBackend* backend, fl32 deltaTime)
{
	return (true);
}

VKAPI_ATTR VkBool32 VKAPI_ATTR	VkDebugCallback(
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
