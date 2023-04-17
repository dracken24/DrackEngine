/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 16-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	   vulkanBuffer.hpp       *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef VULKANBUFFER_HPP
# define VULKANBUFFER_HPP

# include <renderer/vulkan/vulkanTypes.inl>

class VulkanBuffer
{
	//**********************************************************************//
	//**                     Constructors / Destructor                    **//
	//**********************************************************************//
	public:
		VulkanBuffer(void);
		~VulkanBuffer(void);
	
	private:
		VulkanBuffer(VulkanBuffer const &copy);
		VulkanBuffer &operator=(VulkanBuffer const &copy);

	//**********************************************************************//
	//**                          PUBLIC METHODS                          **//
	//**********************************************************************//

	public:
		bl8		VulkanBufferCreate(vulkanContext *context,uint64 size, VkBufferUsageFlagBits usage,
					uint32 memoryPropertyFlags, bl8 bindOnCreate, vulkanBuffer *outBuffer);

		void	VulkanBufferDestroy(vulkanContext *context, vulkanBuffer *buffer);

		bl8		VulkanBufferResize(vulkanContext *context, uint64 newSize, vulkanBuffer *buffer,
					VkQueue queue, VkCommandPool pool);

		void	VulkanBufferBind(vulkanContext *context, vulkanBuffer *buffer, uint64 offset);

		void	*VulkanBufferLockMemory(vulkanContext *context, vulkanBuffer *buffer, uint64 offset,
					uint64 size, uint32 flags);
		void	VulkanBufferUnlockMemory(vulkanContext *context, vulkanBuffer *buffer);

		void	VulkanBufferLoadData(vulkanContext *context, vulkanBuffer *buffer, uint64 offset, uint64 size,
					uint32 flags, const void *data);

		void	VulkanBufferCopyTo(vulkanContext *context, VkCommandPool pool, VkFence fence, VkQueue queue,
					VkBuffer source, uint64 sourceOffset, VkBuffer dest, uint64 destOffset, uint64 size);
};

#endif
