
// #include "vulkanBackend.hpp"

// #include "vulkanTypes.inl"
// #include "vulkanPlatform.hpp"
// #include "vulkanDevice.hpp"

// #include "core/logger.hpp"
// #include "core/deString.hpp"

// #include "container/myArray.hpp"

// #include "platform/Platform.hpp"

// // static Vulkan context
// static vulkanContext context;

// VKAPI_ATTR VkBool32 VKAPI_CALL VDE_DEBUGCallback(
// 	VDE_DEBUGUtilsMessageSeverityFlagBitsEXT message_severity,
// 	VDE_DEBUGUtilsMessageTypeFlagsEXT message_types,
// 	const VDE_DEBUGUtilsMessengerCallbackDataEXT *callbackData,
// 	void *user_data);

// bl8 VulkanRendererBackendInitialize(rendererBackend *backend, const char *application_name, struct platform_state *plat_state)
// {
// 	// TODO: custom allocator.
// 	context.allocator = 0;

// 	// Setup Vulkan instance.
// 	VkApplicationInfo app_info = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
// 	app_info.apiVersion = VK_API_VERSION_1_2;
// 	app_info.pApplicationName = application_name;
// 	app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
// 	app_info.pEngineName = "Kohi Engine";
// 	app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);

// 	VkInstanceCreateInfo create_info = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
// 	create_info.pApplicationInfo = &app_info;

// 	// Obtain a list of required extensions
// 	const char **required_extensions = (const char **)MyArrayCreate(const char *);
// 	MyArrayPush(required_extensions, &VK_KHR_SURFACE_EXTENSION_NAME); // Generic surface extension
// 	PlatformGetRequiredExtensionNames(&required_extensions);	  // Platform-specific extension(s)
// #if defined(_DEBUG)
// 	MyArrayPush(required_extensions, &VK_EXT_DEBUG_UTILS_EXTENSION_NAME); // debug utilities

// 	DE_DEBUG("Required extensions:");
// 	uint32 length = MyArrayLength(required_extensions);
// 	for (uint32 i = 0; i < length; ++i)
// 	{
// 		DE_DEBUG(required_extensions[i]);
// 	}
// #endif

// 	create_info.enabledExtensionCount = MyArrayLength(required_extensions);
// 	create_info.ppEnabledExtensionNames = required_extensions;

// 	// Validation layers.
// 	const char **required_validation_layer_names = 0;
// 	uint32 required_validation_layer_count = 0;

// // If validation should be done, get a list of the required validation layert names
// // and make sure they exist. Validation layers should only be enabled on non-release builds.
// #if defined(_DEBUG)
// 	DE_INFO("Validation layers enabled. Enumerating...");

// 	// The list of validation layers required.
// 	required_validation_layer_names = (const char **)MyArrayCreate(const char *);
// 	MyArrayPush(required_validation_layer_names, &"VK_LAYER_KHRONOS_validation");
// 	required_validation_layer_count = MyArrayLength(required_validation_layer_names);

// 	// Obtain a list of available validation layers
// 	uint32 available_layer_count = 0;
// 	VK_CHECK(vkEnumerateInstanceLayerProperties(&available_layer_count, 0));
// 	VkLayerProperties *available_layers = (VkLayerProperties *)MyArrayReserve(VkLayerProperties, available_layer_count);
// 	VK_CHECK(vkEnumerateInstanceLayerProperties(&available_layer_count, available_layers));

// 	// Verify all required layers are available.
// 	for (uint32 i = 0; i < required_validation_layer_count; ++i)
// 	{
// 		DE_INFO("Searching for layer: %s...", required_validation_layer_names[i]);
// 		bl8 found = false;
// 		for (uint32 j = 0; j < available_layer_count; ++j)
// 		{
// 			if (StrEqual(required_validation_layer_names[i], available_layers[j].layerName))
// 			{
// 				found = true;
// 				DE_INFO("Found.");
// 				break;
// 			}
// 		}

// 		if (!found)
// 		{
// 			DE_FATAL("Required validation layer is missing: %s", required_validation_layer_names[i]);
// 			return false;
// 		}
// 	}
// 	DE_INFO("All required validation layers are present.");
// #endif

// 	create_info.enabledLayerCount = required_validation_layer_count;
// 	create_info.ppEnabledLayerNames = required_validation_layer_names;

// 	VK_CHECK(vkCreateInstance(&create_info, context.allocator, &context.instance));
// 	DE_INFO("Vulkan Instance created.");

// 	// Debugger
// #if defined(_DEBUG)
// 	DE_DEBUG("Creating Vulkan debugger...");
// 	uint32 log_severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
// 					   VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
// 					   VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT; //|
// 																	 //    VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;

// 	VDE_DEBUGUtilsMessengerCreateInfoEXT debug_create_info = {VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT};
// 	debug_create_info.messageSeverity = log_severity;
// 	debug_create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
// 	debug_create_info.pfnUserCallback = VkDebugCallback;

// 	PFN_vkCreateDebugUtilsMessengerEXT func =
// 		(PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(context.instance, "vkCreateDebugUtilsMessengerEXT");
// 	KASSERT_MSG(func, "Failed to create debug messenger!");
// 	VK_CHECK(func(context.instance, &debug_create_info, context.allocator, &context.debug_messenger));
// 	DE_DEBUG("Vulkan debugger created.");
// #endif

// 	// Surface
// 	DE_DEBUG("Creating Vulkan surface...");
// 	if (!platform_create_vulkan_surface(plat_state, &context))
// 	{
// 		KERROR("Failed to create platform surface!");
// 		return false;
// 	}
// 	DE_DEBUG("Vulkan surface created.");

// 	// Device creation
// 	if (!vulkan_device_create(&context))
// 	{
// 		KERROR("Failed to create device!");
// 		return false;
// 	}

// 	DE_INFO("Vulkan renderer initialized successfully.");
// 	return true;
// }

// void vulkan_renderer_backend_shutdown(renderer_backend *backend)
// {

// 	DE_DEBUG("Destroying Vulkan debugger...");
// 	if (context.debug_messenger)
// 	{
// 		PFN_vkDestroyDebugUtilsMessengerEXT func =
// 			(PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(context.instance, "vkDestroyDebugUtilsMessengerEXT");
// 		func(context.instance, context.debug_messenger, context.allocator);
// 	}

// 	DE_DEBUG("Destroying Vulkan instance...");
// 	vkDestroyInstance(context.instance, context.allocator);
// }

// void vulkan_renderer_backend_on_resized(renderer_backend *backend, u16 width, u16 height)
// {
// }

// bl8 vulkan_renderer_backend_begin_frame(renderer_backend *backend, f32 delta_time)
// {
// 	return true;
// }

// bl8 vulkan_renderer_backend_end_frame(renderer_backend *backend, f32 delta_time)
// {
// 	return true;
// }

// VKAPI_ATTR VkBool32 VKAPI_CALL VkDebugCallback(
// 	VDE_DEBUGUtilsMessageSeverityFlagBitsEXT message_severity,
// 	VDE_DEBUGUtilsMessageTypeFlagsEXT message_types,
// 	const VDE_DEBUGUtilsMessengerCallbackDataEXT *callbackData,
// 	void *user_data)
// {
// 	switch (message_severity)
// 	{
// 	default:
// 	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
// 		KERROR(callbackData->pMessage);
// 		break;
// 	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
// 		KWARN(callbackData->pMessage);
// 		break;
// 	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
// 		DE_INFO(callbackData->pMessage);
// 		break;
// 	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
// 		KTRACE(callbackData->pMessage);
// 		break;
// 	}
// 	return VK_false;
// }
