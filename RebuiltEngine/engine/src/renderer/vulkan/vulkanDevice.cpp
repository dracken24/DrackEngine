/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 31-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	   vulkanDevice.cpp       *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "vulkanDevice.hpp"
#include "../../includes/core/logger.hpp"
#include "../../includes/core/deMemory.hpp"
#include "../../includes/core/deString.hpp"
#include "../../container/myArray.hpp"

typedef struct	vulkanPhysicalDeviceRequirements
{
	bl8				graphics;
	bl8				present;
	bl8				compute;
	bl8				transfer;
	// darray
	const char **	deviceExtensionNames;
	bl8				samplerAnisotropy;
	bl8				discreteGpu;
}	vulkanPhysicalDeviceRequirements;

typedef struct vulkanPhysicalDeviceQueueFamilyInfo
{
	uint32 graphicsFamilyIndex;
	uint32 presentFamilyIndex;
	uint32 computeFamilyIndex;
	uint32 transferFamilyIndex;
} vulkanPhysicalDeviceQueueFamilyInfo;

bl8		SelectPhysicalDevice(vulkanContext *context);

bl8		PhysicalDeviceMeetsRequirements(
		VkPhysicalDevice device,
		VkSurfaceKHR surface,
		const VkPhysicalDeviceProperties *properties,
		const VkPhysicalDeviceFeatures *features,
		const vulkanPhysicalDeviceRequirements *requirements,
		vulkanPhysicalDeviceQueueFamilyInfo *outQueueFamilyInfo,
		vulkanSwapchainSupportInfo *outSwapchainSupport);

bl8		VulkanDeviceCreate(vulkanContext *context)
{
	if (!SelectPhysicalDevice(context))
	{
		return false;
	}

	DE_INFO("Creating logical device...");
	// NOTE: Do not create additional queues for shared indices.
	bl8 presentSharesGraphicsQueue = context->device.graphicsQueueIndex == context->device.presentQueueIndex;
	bl8 transferSharesGraphicsQueue = context->device.graphicsQueueIndex == context->device.transferQueueIndex;
	uint32 indexCount = 1;
	if (!presentSharesGraphicsQueue)
	{
		indexCount++;
	}
	if (!transferSharesGraphicsQueue)
	{
		indexCount++;
	}
	uint32 indices[indexCount];
	uint8 index = 0;
	indices[index++] = context->device.graphicsQueueIndex;
	if (!presentSharesGraphicsQueue)
	{
		indices[index++] = context->device.presentQueueIndex;
	}
	if (!transferSharesGraphicsQueue)
	{
		indices[index++] = context->device.transferQueueIndex;
	}

	VkDeviceQueueCreateInfo queueCreateInfos[indexCount];
	for (uint32 i = 0; i < indexCount; ++i)
	{
		queueCreateInfos[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfos[i].queueFamilyIndex = indices[i];
		queueCreateInfos[i].queueCount = 1;
		if (indices[i] == context->device.graphicsQueueIndex)
		{
			queueCreateInfos[i].queueCount = 2;
		}
		queueCreateInfos[i].flags = 0;
		queueCreateInfos[i].pNext = 0;
		fl32 queuePriority = 1.0f;
		queueCreateInfos[i].pQueuePriorities = &queuePriority;
	}

	// Request device features.
	// TODO: should be config driven
	VkPhysicalDeviceFeatures deviceFeatures = {};
	deviceFeatures.samplerAnisotropy = VK_TRUE; // Request anistrophy

	VkDeviceCreateInfo deviceCreateInfo = {VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO};
	deviceCreateInfo.queueCreateInfoCount = indexCount;
	deviceCreateInfo.pQueueCreateInfos = queueCreateInfos;
	deviceCreateInfo.pEnabledFeatures = &deviceFeatures;
	deviceCreateInfo.enabledExtensionCount = 1;
	const char *extensionNames = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
	deviceCreateInfo.ppEnabledExtensionNames = &extensionNames;

	// Deprecated and ignored, so pass nothing.
	deviceCreateInfo.enabledLayerCount = 0;
	deviceCreateInfo.ppEnabledLayerNames = 0;

	// Create the device.
	VK_CHECK(vkCreateDevice(
		context->device.physicalDevice,
		&deviceCreateInfo,
		context->allocator,
		&context->device.logicalDevice));

	DE_INFO("Logical device created.");

	// Get queues.
	vkGetDeviceQueue(
		context->device.logicalDevice,
		context->device.graphicsQueueIndex,
		0,
		&context->device.graphicsQueue);

	vkGetDeviceQueue(
		context->device.logicalDevice,
		context->device.presentQueueIndex,
		0,
		&context->device.presentQueue);

	vkGetDeviceQueue(
		context->device.logicalDevice,
		context->device.transferQueueIndex,
		0,
		&context->device.transferQueue);
	DE_INFO("Queues obtained.");

	return true;
}

void vulkanDeviceDestroy(vulkanContext *context)
{

	// Unset queues
	context->device.graphicsQueue = 0;
	context->device.presentQueue = 0;
	context->device.transferQueue = 0;

	// Destroy logical device
	DE_INFO("Destroying logical device...");
	if (context->device.logicalDevice)
	{
		vkDestroyDevice(context->device.logicalDevice, context->allocator);
		context->device.logicalDevice = 0;
	}

	// Physical devices are not destroyed.
	DE_INFO("Releasing physical device resources...");
	context->device.physicalDevice = 0;

	if (context->device.swapchainSupport.formats)
	{
		DE_Free(
			context->device.swapchainSupport.formats,
			sizeof(VkSurfaceFormatKHR) * context->device.swapchainSupport.formatCount,
			DE_MEMORY_TAG_RENDERER);
		context->device.swapchainSupport.formats = 0;
		context->device.swapchainSupport.formatCount = 0;
	}

	if (context->device.swapchainSupport.presentModes)
	{
		DE_Free(
			context->device.swapchainSupport.presentModes,
			sizeof(VkPresentModeKHR) * context->device.swapchainSupport.presentModeCount,
			DE_MEMORY_TAG_RENDERER);
		context->device.swapchainSupport.presentModes = 0;
		context->device.swapchainSupport.presentModeCount = 0;
	}

	DE_MemSet(
		&context->device.swapchainSupport.capabilities,
		sizeof(context->device.swapchainSupport.capabilities));

	context->device.graphicsQueueIndex = -1;
	context->device.presentQueueIndex = -1;
	context->device.transferQueueIndex = -1;
}

void VulkanDeviceQuerySwapchainSupport(
	VkPhysicalDevice physicalDevice,
	VkSurfaceKHR surface,
	vulkanSwapchainSupportInfo *outSupportInfo)
{
	// Surface capabilities
	VK_CHECK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice,
		surface, &outSupportInfo->capabilities));

	// Surface formats
	VK_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface,
		&outSupportInfo->formatCount, 0));

	if (outSupportInfo->formatCount != 0)
	{
		if (!outSupportInfo->formats)
		{
			outSupportInfo->formats = (VkSurfaceFormatKHR *)DE_Malloc(sizeof(VkSurfaceFormatKHR)
				* outSupportInfo->formatCount, DE_MEMORY_TAG_RENDERER);
		}
		VK_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(
			physicalDevice,
			surface,
			&outSupportInfo->formatCount,
			outSupportInfo->formats));
	}

	// Present modes
	VK_CHECK(vkGetPhysicalDeviceSurfacePresentModesKHR(
		physicalDevice,
		surface,
		&outSupportInfo->presentModeCount,
		0));
	if (outSupportInfo->presentModeCount != 0)
	{
		if (!outSupportInfo->presentModes)
		{
			outSupportInfo->presentModes = (VkPresentModeKHR *)DE_Malloc(sizeof(VkPresentModeKHR)
				* outSupportInfo->presentModeCount, DE_MEMORY_TAG_RENDERER);
		}
		VK_CHECK(vkGetPhysicalDeviceSurfacePresentModesKHR(
			physicalDevice,
			surface,
			&outSupportInfo->presentModeCount,
			outSupportInfo->presentModes));
	}
}

bl8		SelectPhysicalDevice(vulkanContext *context)
{
	uint32 physicalDeviceCount = 0;
	VK_CHECK(vkEnumeratePhysicalDevices(context->instance, &physicalDeviceCount, 0));
	if (physicalDeviceCount == 0)
	{
		DE_FATAL("No devices which support Vulkan were found.");
		return false;
	}

	VkPhysicalDevice physicalDevices[physicalDeviceCount];
	VK_CHECK(vkEnumeratePhysicalDevices(context->instance, &physicalDeviceCount, physicalDevices));
	for (uint32 i = 0; i < physicalDeviceCount; ++i)
	{
		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(physicalDevices[i], &properties);

		VkPhysicalDeviceFeatures features;
		vkGetPhysicalDeviceFeatures(physicalDevices[i], &features);

		VkPhysicalDeviceMemoryProperties memory;
		vkGetPhysicalDeviceMemoryProperties(physicalDevices[i], &memory);

		// TODO: These requirements should probably be driven by engine
		// configuration.
		vulkanPhysicalDeviceRequirements requirements = {};
		requirements.graphics = true;
		requirements.present = true;
		requirements.transfer = true;
		// NOTE: Enable this if compute will be required.
		// requirements.compute = true;
		requirements.samplerAnisotropy = true;
		requirements.discreteGpu = true;
		requirements.deviceExtensionNames = (const char **)MyArrayCreate(const char *);
		_MyArrayPush(requirements.deviceExtensionNames, &VK_KHR_SWAPCHAIN_EXTENSION_NAME);

		vulkanPhysicalDeviceQueueFamilyInfo queue_info = {};
		bl8 result = PhysicalDeviceMeetsRequirements(
			physicalDevices[i],
			context->surface,
			&properties,
			&features,
			&requirements,
			&queue_info,
			&context->device.swapchainSupport);

		if (result)
		{
			DE_INFO("Selected device: '%s'.", properties.deviceName);
			// GPU type, etc.
			switch (properties.deviceType)
			{
			default:
			case VK_PHYSICAL_DEVICE_TYPE_OTHER:
				DE_INFO("GPU type is Unknown.");
				break;
			case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
				DE_INFO("GPU type is Integrated.");
				break;
			case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
				DE_INFO("GPU type is Descrete.");
				break;
			case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
				DE_INFO("GPU type is Virtual.");
				break;
			case VK_PHYSICAL_DEVICE_TYPE_CPU:
				DE_INFO("GPU type is CPU.");
				break;
			}

			DE_INFO(
				"GPU Driver version: %d.%d.%d",
				VK_VERSION_MAJOR(properties.driverVersion),
				VK_VERSION_MINOR(properties.driverVersion),
				VK_VERSION_PATCH(properties.driverVersion));

			// Vulkan API version.
			DE_INFO(
				"Vulkan API version: %d.%d.%d",
				VK_VERSION_MAJOR(properties.apiVersion),
				VK_VERSION_MINOR(properties.apiVersion),
				VK_VERSION_PATCH(properties.apiVersion));

			// Memory information
			for (uint32 j = 0; j < memory.memoryHeapCount; ++j)
			{
				fl32 memory_size_gib = (((fl32)memory.memoryHeaps[j].size) / 1024.0f / 1024.0f / 1024.0f);
				if (memory.memoryHeaps[j].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)
				{
					DE_INFO("Local GPU memory: %.2f GiB", memory_size_gib);
				}
				else
				{
					DE_INFO("Shared System memory: %.2f GiB", memory_size_gib);
				}
			}

			context->device.physicalDevice = physicalDevices[i];
			context->device.graphicsQueueIndex = queue_info.graphicsFamilyIndex;
			context->device.presentQueueIndex = queue_info.presentFamilyIndex;
			context->device.transferQueueIndex = queue_info.transferFamilyIndex;
			// NOTE: set compute index here if needed.

			// Keep a copy of properties, features and memory info for later use.
			context->device.properties = properties;
			context->device.features = features;
			context->device.memory = memory;
			break;
		}
	}

	// Ensure a device was selected
	if (!context->device.physicalDevice)
	{
		DE_ERROR("No physical devices were found which meet the requirements.");
		return false;
	}

	DE_INFO("Physical device selected.");
	return true;
}

	bl8 PhysicalDeviceMeetsRequirements(
		VkPhysicalDevice device,
		VkSurfaceKHR surface,
		const VkPhysicalDeviceProperties *properties,
		const VkPhysicalDeviceFeatures *features,
		const vulkanPhysicalDeviceRequirements *requirements,
		vulkanPhysicalDeviceQueueFamilyInfo *outQueueInfo,
		vulkanSwapchainSupportInfo *outSwapchainSupport)
{
	// Evaluate device properties to determine if it meets the needs of our applcation.
	outQueueInfo->graphicsFamilyIndex = -1;
	outQueueInfo->presentFamilyIndex = -1;
	outQueueInfo->computeFamilyIndex = -1;
	outQueueInfo->transferFamilyIndex = -1;

	// Discrete GPU?
	if (requirements->discreteGpu)
	{
		if (properties->deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		{
			DE_INFO("Device is not a discrete GPU, and one is required. Skipping.");
			return false;
		}
	}

	uint32 queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, 0);
	VkQueueFamilyProperties queueFamilies[queueFamilyCount];
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies);

	// Look at each queue and see what queues it supports
	DE_INFO("Graphics | Present | Compute | Transfer | Name");
	uint8 min_transfer_score = 255;
	for (uint32 i = 0; i < queueFamilyCount; ++i)
	{
		uint8 current_transfer_score = 0;

		// Graphics queue?
		if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			outQueueInfo->graphicsFamilyIndex = i;
			++current_transfer_score;
		}

		// Compute queue?
		if (queueFamilies[i].queueFlags & VK_QUEUE_COMPUTE_BIT)
		{
			outQueueInfo->computeFamilyIndex = i;
			++current_transfer_score;
		}

		// Transfer queue?
		if (queueFamilies[i].queueFlags & VK_QUEUE_TRANSFER_BIT)
		{
			// Take the index if it is the current lowest. This increases the
			// liklihood that it is a dedicated transfer queue.
			if (current_transfer_score <= min_transfer_score)
			{
				min_transfer_score = current_transfer_score;
				outQueueInfo->transferFamilyIndex = i;
			}
		}

		// Present queue?
		VkBool32 supports_present = VK_FALSE;
		VK_CHECK(vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &supports_present));
		if (supports_present)
		{
			outQueueInfo->presentFamilyIndex = i;
		}
	}

	// Print out some info about the device
	DE_INFO("       %d |       %d |       %d |        %d | %s",
		outQueueInfo->graphicsFamilyIndex != -1,
		outQueueInfo->presentFamilyIndex != -1,
		outQueueInfo->computeFamilyIndex != -1,
		outQueueInfo->transferFamilyIndex != -1,
		properties->deviceName);

	if (
		(!requirements->graphics || (requirements->graphics && outQueueInfo->graphicsFamilyIndex != -1)) &&
		(!requirements->present || (requirements->present && outQueueInfo->presentFamilyIndex != -1)) &&
		(!requirements->compute || (requirements->compute && outQueueInfo->computeFamilyIndex != -1)) &&
		(!requirements->transfer || (requirements->transfer && outQueueInfo->transferFamilyIndex != -1)))
	{
		DE_INFO("Device meets queue requirements.");
		DE_TRACE("Graphics Family Index: %i", outQueueInfo->graphicsFamilyIndex);
		DE_TRACE("Present Family Index:  %i", outQueueInfo->presentFamilyIndex);
		DE_TRACE("Transfer Family Index: %i", outQueueInfo->transferFamilyIndex);
		DE_TRACE("Compute Family Index:  %i", outQueueInfo->computeFamilyIndex);

		// Query swapchain support.
		VulkanDeviceQuerySwapchainSupport(
			device,
			surface,
			outSwapchainSupport);

		if (outSwapchainSupport->formatCount < 1 || outSwapchainSupport->presentModeCount < 1)
		{
			if (outSwapchainSupport->formats)
			{
				DE_Free(outSwapchainSupport->formats, sizeof(VkSurfaceFormatKHR) * outSwapchainSupport->formatCount, DE_MEMORY_TAG_RENDERER);
			}
			if (outSwapchainSupport->presentModes)
			{
				DE_Free(outSwapchainSupport->presentModes, sizeof(VkPresentModeKHR) * outSwapchainSupport->presentModeCount, DE_MEMORY_TAG_RENDERER);
			}
			DE_INFO("Required swapchain support not present, skipping device.");
			return false;
		}

		// Device extensions.
		if (requirements->deviceExtensionNames)
		{
			uint32 availableExtensionCount = 0;
			VkExtensionProperties *availableExtensions = 0;
			VK_CHECK(vkEnumerateDeviceExtensionProperties(
				device,
				0,
				&availableExtensionCount,
				0));
			if (availableExtensionCount != 0)
			{
				availableExtensions = (VkExtensionProperties *)DE_Malloc(sizeof(VkExtensionProperties)
					* availableExtensionCount, DE_MEMORY_TAG_RENDERER);
				VK_CHECK(vkEnumerateDeviceExtensionProperties(
					device,
					0,
					&availableExtensionCount,
					availableExtensions));

				uint32 requiredExtensionCount = MyArrayLength(requirements->deviceExtensionNames);
				for (uint32 i = 0; i < requiredExtensionCount; ++i)
				{
					bl8 found = false;
					for (uint32 j = 0; j < availableExtensionCount; ++j)
					{
						if (StrEqual(requirements->deviceExtensionNames[i], availableExtensions[j].extensionName))
						{
							found = true;
							break;
						}
					}

					if (!found)
					{
						DE_INFO("Required extension not found: '%s', skipping device.", requirements->deviceExtensionNames[i]);
						DE_Free(availableExtensions, sizeof(VkExtensionProperties) * availableExtensionCount, DE_MEMORY_TAG_RENDERER);
						return false;
					}
				}
			}
			DE_Free(availableExtensions, sizeof(VkExtensionProperties) * availableExtensionCount, DE_MEMORY_TAG_RENDERER);
		}

		// Sampler anisotropy
		if (requirements->samplerAnisotropy && !features->samplerAnisotropy)
		{
			DE_INFO("Device does not support samplerAnisotropy, skipping.");
			return false;
		}

		// Device meets all requirements.
		return true;
	}

	return false;
}