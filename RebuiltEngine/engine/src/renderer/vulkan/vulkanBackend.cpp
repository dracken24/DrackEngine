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

#include "vulkanPlatform.hpp"
#include "vulkanTypes.inl"
#include "vulkanDevice.hpp"

#include "../../includes/core/logger.hpp"
#include "../../includes/platform/Platform.hpp"

#include "../../container/myArray.hpp"
#include "../../includes/core/deString.hpp"

// static Vulkan context
static vulkanContext context;

VKAPI_ATTR VkBool32 VKAPI_CALL vk_debug_callback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageTypes,
	const VkDebugUtilsMessengerCallbackDataEXT *callbackData,
	void *userData);

bl8 VulkanRendererBackendInitialize(rendererBackend *backend, std::string applicationName,
	struct PlatformState *platState)
{
	// TODO: custom allocator.
	context.allocator = 0;

	// Setup Vulkan instance.
	VkApplicationInfo app_info = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
	app_info.apiVersion = VK_API_VERSION_1_2;
	app_info.pApplicationName = applicationName.c_str();
	app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.pEngineName = "DrackEngine";
	app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);

	VkInstanceCreateInfo create_info = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
	create_info.pApplicationInfo = &app_info;

	// Obtain a list of required extensions
	const char **requiredExtensions = static_cast<const char **>(MyArrayCreate(const char *));
	_MyArrayPush(requiredExtensions, VK_KHR_SURFACE_EXTENSION_NAME); // Generic surface extension

	PlatformGetRequiredExtensionNames(&requiredExtensions); // Platform-specific extension(s)
#if defined(_DEBUG)
	_MyArrayPush(requiredExtensions, VK_EXT_DEBUG_UTILS_EXTENSION_NAME); // debug utilities

	DE_DEBUG("Required extensions:");
	uint32 length = MyArrayLength(requiredExtensions);
	for (uint32 i = 0; i < length; ++i)
	{
		DE_DEBUG(requiredExtensions[i]);
	}
#endif

	create_info.enabledExtensionCount = MyArrayLength(requiredExtensions);
	create_info.ppEnabledExtensionNames = requiredExtensions;

	// Validation layers.
	const char **requiredValidationLayerNames = 0;
	uint32 required_validation_layer_count = 0;

// If validation should be done, get a list of the required validation layert names
// and make sure they exist. Validation layers should only be enabled on non-release builds.
#if defined(_DEBUG)
	DE_INFO("Validation layers enabled. Enumerating...");

	// The list of validation layers required.
	requiredValidationLayerNames = (const char **)MyArrayCreate(const char *);
	_MyArrayPush(requiredValidationLayerNames, &"VK_LAYER_KHRONOS_validation");
	required_validation_layer_count = MyArrayLength(requiredValidationLayerNames);

	// Obtain a list of available validation layers
	uint32 availableLayerCount = 0;
	VK_CHECK(vkEnumerateInstanceLayerProperties(&availableLayerCount, 0));
	VkLayerProperties *availableLayers = (VkLayerProperties *)_MyArrayCreate(sizeof(VkLayerProperties), availableLayerCount);
	VK_CHECK(vkEnumerateInstanceLayerProperties(&availableLayerCount, availableLayers));

	// Verify all required layers are available.
	for (uint32 i = 0; i < required_validation_layer_count; ++i)
	{
		DE_INFO("Searching for layer: %s...", requiredValidationLayerNames[i]);
		bl8 found = false;
		for (uint32 j = 0; j < availableLayerCount; ++j)
		{
			if (StrEqual(requiredValidationLayerNames[i], availableLayers[j].layerName))
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

	create_info.enabledLayerCount = required_validation_layer_count;
	create_info.ppEnabledLayerNames = requiredValidationLayerNames;

	VK_CHECK(vkCreateInstance(&create_info, context.allocator, &context.instance));
	DE_INFO("Vulkan Instance created.");

	// Debugger
#if defined(_DEBUG)
	DE_DEBUG("Creating Vulkan debugger...");
	uint32 log_severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT; //|
	//    VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT};
	debugCreateInfo = {VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT};
	debugCreateInfo.messageSeverity = log_severity;
	debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
		| VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT
		| VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
	debugCreateInfo.pfnUserCallback = vk_debug_callback;

	PFN_vkCreateDebugUtilsMessengerEXT func =
		(PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(context.instance, "vkCreateDebugUtilsMessengerEXT");
	DE_ASSERT_MSG(func, "Failed to create debug messenger!");
	VK_CHECK(func(context.instance, &debugCreateInfo, context.allocator, &context.debugMessenger));
	DE_DEBUG("Vulkan debugger created.");
#endif

	// Surface
	DE_DEBUG("Creating Vulkan surface...");
	if (!PlatformCreateVulkanSurface(platState, &context))
	{
		DE_ERROR("Failed to create platform surface!");
		return false;
	}
	DE_DEBUG("Vulkan surface created.");

	// Device creation
	if (!VulkanDeviceCreate(&context))
	{
		DE_ERROR("Failed to create device!");
		return false;
	}

	DE_INFO("Vulkan renderer initialized successfully.");
	return true;
}

void	VulkanRendererBackendShutdown(rendererBackend *backend)
{
#if defined(_DEBUG)
	DE_DEBUG("Destroying Vulkan debugger...");
	if (context.debugMessenger)
	{
		PFN_vkDestroyDebugUtilsMessengerEXT func =
			(PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(context.instance, "vkDestroyDebugUtilsMessengerEXT");
		func(context.instance, context.debugMessenger, context.allocator);
	}

	DE_DEBUG("Destroying Vulkan instance...");
	vkDestroyInstance(context.instance, context.allocator);
#endif
}

void VulkanRendererBackendOnResized(rendererBackend *backend, uint16 width, uint16 height)
{
}

bl8	VulkanRendererBackendBeginFrame(rendererBackend *backend, fl32 deltaTime)
{
	return true;
}

bl8 VulkanRendererBackendEndFrame(rendererBackend *backend, fl32 deltaTime)
{
	return true;
}

VKAPI_ATTR VkBool32 VKAPI_CALL vkDebugCallback(
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
	return VK_FALSE;
}
