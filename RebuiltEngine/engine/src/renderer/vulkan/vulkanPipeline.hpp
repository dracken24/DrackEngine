/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 17-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	  vulkanPipeline.hpp      *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef VULKANPIPELINE_HPP
# define VULKANPIPELINE_HPP

# include <renderer/vulkan/vulkanTypes.inl>

bl8		VulkanGraphicsPipelineCreate(vulkanContext* context, vulkanRenderpass* renderpass,
			uint32 attributeCount, VkVertexInputAttributeDescription* attributes, uint32 descriptorSetLayoutCount,
			VkDescriptorSetLayout* descriptorSetLayouts, uint32 stageCount, VkPipelineShaderStageCreateInfo* stages,
			VkViewport viewport, VkRect2D scissor, bl8 isWireframe, vulkanPipeline* outPipeline);

void	VulkanPipelineDestroy(vulkanContext* context, vulkanPipeline* pipeline);

void	VulkanPipelineBind(vulkanCommandBuffer* commandBuffer, VkPipelineBindPoint bindPoint, vulkanPipeline* pipeline);

#endif
