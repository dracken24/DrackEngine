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

bl8		vulkan_device_create(vulkan_context* context);

void	vulkan_device_destroy(vulkan_context* context);

void	vulkan_device_query_swapchain_support(VkPhysicalDevice physical_device,
			VkSurfaceKHR surface, vulkan_swapchain_support_info* out_support_info);

#endif
