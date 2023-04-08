/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 05-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	   vulkanImage.hpp        *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef VULKANIMAGE_HPP
# define VULKANIMAGE_HPP

# include <renderer/vulkan/vulkanTypes.inl>

class VulkanImage
{
	public:
		VulkanImage(void);
		~VulkanImage(void);

		void	VulkanImageCreate(vulkanContext *context, VkImageType imageType, uint32 width, uint32 height,
					VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags memoryFlags,
						bl32 createView, VkImageAspectFlags viewAspectFlags, vulkanImage *image);

		void	VulkanImageViewCreate(vulkanContext *context, VkFormat format,
					vulkanImage *image, VkImageAspectFlags aspectFlags);

		void	VulkanImageDestroy(vulkanContext *context, vulkanImage *image);

	private:

};

#endif
