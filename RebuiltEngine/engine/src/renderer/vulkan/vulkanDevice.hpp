/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 31-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	   vulkanDevice.hpp       *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef VULKANDEVICE_HPP
# define VULKANDEVICE_HPP

# include <renderer/vulkan/vulkanTypes.inl>

bl8		VulkanDeviceCreate(vulkanContext *context);

void	VulkanDeviceDestroy(vulkanContext *context);

void	VulkanDeviceQuerySwapchainSupport(VkPhysicalDevice physicalDevice,
			VkSurfaceKHR surface, vulkanSwapchainSupportInfo *outSupportInfo);

#endif
