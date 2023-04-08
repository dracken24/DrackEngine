/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 03-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE:     vulkanSwapchain.hpp      *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

// swapchain is a queue of images waiting to be presented on the screen.
// Do the same job than a framebuffer in opnGL.

#ifndef VULKANSWAPCHAIN_HPP
# define VULKANSWAPCHAIN_HPP

#include <renderer/vulkan/vulkanTypes.inl>
#include <renderer/vulkan/vulkanImage.hpp>

class VulkanSwapchain
{
	public:
		VulkanSwapchain(void);
		~VulkanSwapchain(void);

		// Create a swapchain.
		void	VulkanSwapchainCreate(vulkanContext *context, uint32 width, uint32 height,
					vulkanSwapchain *swapchain);

		// ex: Recreate the swapchain when the window is resized.
		void	VulkanSwapchainRecreate(vulkanContext *context, uint32 width, uint32 height,
					vulkanSwapchain *swapchain);

		// Destroy the swapchain.
		void	VulkanSwapchainDestroy(vulkanContext *context, vulkanSwapchain *swapchain);

		// Acquire the next image in the swapchain queue.
		bl8		VulkanSwapchainAquireNextImageIndex(vulkanContext *context, vulkanSwapchain *swapchain,
					uint64 timeout, VkSemaphore availableSemaphore, VkFence fence, uint32 *imageIndex);

		// Present the image to the screen.
		void	VulkanSwapchainPresent(vulkanContext *context, vulkanSwapchain *swapchain,
					VkQueue graphicQueue,VkQueue presentQueue, VkSemaphore presentSemaphore, uint32 imageIndex);

	private:
		void	create(vulkanContext *context, uint32 width, uint32 height, vulkanSwapchain *swapchain);
		void	destroy(vulkanContext *context, vulkanSwapchain *swapchain);

	private:
		VulkanImage		_image;
};

#endif
