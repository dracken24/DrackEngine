/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 17-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	  vulkanPipeline.cpp      *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include <renderer/vulkan/vulkanPipeline.hpp>

#include <renderer/vulkan/vulkanUtils.hpp>

#include <core/deMemory.hpp>
#include <core/logger.hpp>

#include <math/deMath.hpp>

bl8		VulkanGraphicsPipelineCreate(vulkanContext* context, vulkanRenderpass* renderpass,
			uint32 attributeCount, VkVertexInputAttributeDescription* attributes, uint32 descriptorSetLayoutCount,
			VkDescriptorSetLayout* descriptorSetLayouts, uint32 stageCount, VkPipelineShaderStageCreateInfo* stages,
			VkViewport viewport, VkRect2D scissor, bl8 isWireframe, vulkanPipeline* outPipeline)
{
	// Viewport state
	VkPipelineViewportStateCreateInfo viewportState = {VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO};
	viewportState.viewportCount = 1;
	viewportState.pViewports = &viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &scissor;

	// Rasterizer
	VkPipelineRasterizationStateCreateInfo rasterizerCreateInfo = {VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO};
	rasterizerCreateInfo.depthClampEnable = VK_FALSE;
	rasterizerCreateInfo.rasterizerDiscardEnable = VK_FALSE;
	rasterizerCreateInfo.polygonMode = isWireframe ? VK_POLYGON_MODE_LINE : VK_POLYGON_MODE_FILL;
	rasterizerCreateInfo.lineWidth = 1.0f;
	rasterizerCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizerCreateInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	rasterizerCreateInfo.depthBiasEnable = VK_FALSE;
	rasterizerCreateInfo.depthBiasConstantFactor = 0.0f;
	rasterizerCreateInfo.depthBiasClamp = 0.0f;
	rasterizerCreateInfo.depthBiasSlopeFactor = 0.0f;

	// Multisampling.
	VkPipelineMultisampleStateCreateInfo multisampling_create_info = {VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO};
	multisampling_create_info.sampleShadingEnable = VK_FALSE;
	multisampling_create_info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	multisampling_create_info.minSampleShading = 1.0f;
	multisampling_create_info.pSampleMask = 0;
	multisampling_create_info.alphaToCoverageEnable = VK_FALSE;
	multisampling_create_info.alphaToOneEnable = VK_FALSE;

	// Depth and stencil testing.
	VkPipelineDepthStencilStateCreateInfo depth_stencil = {VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO};
	depth_stencil.depthTestEnable = VK_TRUE;
	depth_stencil.depthWriteEnable = VK_TRUE;
	depth_stencil.depthCompareOp = VK_COMPARE_OP_LESS;
	depth_stencil.depthBoundsTestEnable = VK_FALSE;
	depth_stencil.stencilTestEnable = VK_FALSE;

	VkPipelineColorBlendAttachmentState color_blend_attachment_state;
	SetMemory(&color_blend_attachment_state, sizeof(VkPipelineColorBlendAttachmentState));
	color_blend_attachment_state.blendEnable = VK_TRUE;
	color_blend_attachment_state.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	color_blend_attachment_state.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	color_blend_attachment_state.colorBlendOp = VK_BLEND_OP_ADD;
	color_blend_attachment_state.srcAlphaBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	color_blend_attachment_state.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	color_blend_attachment_state.alphaBlendOp = VK_BLEND_OP_ADD;

	color_blend_attachment_state.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
													VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

	VkPipelineColorBlendStateCreateInfo color_blend_state_create_info = {VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO};
	color_blend_state_create_info.logicOpEnable = VK_FALSE;
	color_blend_state_create_info.logicOp = VK_LOGIC_OP_COPY;
	color_blend_state_create_info.attachmentCount = 1;
	color_blend_state_create_info.pAttachments = &color_blend_attachment_state;

	// Dynamic state
	const uint32 dynamic_state_count = 3;
	VkDynamicState dynamic_states[dynamic_state_count] = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR,
		VK_DYNAMIC_STATE_LINE_WIDTH};

	VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo = {VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO};
	dynamicStateCreateInfo.dynamicStateCount = dynamic_state_count;
	dynamicStateCreateInfo.pDynamicStates = dynamic_states;

	// Vertex input
	VkVertexInputBindingDescription bindingDescription;
	bindingDescription.binding = 0; // Binding index
	bindingDescription.stride = sizeof(vertex3d);
	bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX; // Move to next data entry for each vertex.

	// Attributes
	VkPipelineVertexInputStateCreateInfo vertexInputInfo = {VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO};
	vertexInputInfo.vertexBindingDescriptionCount = 1;
	vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
	vertexInputInfo.vertexAttributeDescriptionCount = attributeCount;
	vertexInputInfo.pVertexAttributeDescriptions = attributes;

	// Input assembly
	VkPipelineInputAssemblyStateCreateInfo inputAssembly = {VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO};
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssembly.primitiveRestartEnable = VK_FALSE;

	// Pipeline layout
	VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO};

	// Descriptor set layouts
	pipelineLayoutCreateInfo.setLayoutCount = descriptorSetLayoutCount;
	pipelineLayoutCreateInfo.pSetLayouts = descriptorSetLayouts;

	// Create the pipeline layout.
	VK_CHECK(vkCreatePipelineLayout(context->device.logicalDevice, &pipelineLayoutCreateInfo,
		context->allocator, &outPipeline->pipelineLayout));

	// Pipeline create
	VkGraphicsPipelineCreateInfo pipelineCreateInfo = {VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO};
	pipelineCreateInfo.stageCount = stageCount;
	pipelineCreateInfo.pStages = stages;
	pipelineCreateInfo.pVertexInputState = &vertexInputInfo;
	pipelineCreateInfo.pInputAssemblyState = &inputAssembly;

	pipelineCreateInfo.pViewportState = &viewportState;
	pipelineCreateInfo.pRasterizationState = &rasterizerCreateInfo;
	pipelineCreateInfo.pMultisampleState = &multisampling_create_info;
	pipelineCreateInfo.pDepthStencilState = &depth_stencil;
	pipelineCreateInfo.pColorBlendState = &color_blend_state_create_info;
	pipelineCreateInfo.pDynamicState = &dynamicStateCreateInfo;
	pipelineCreateInfo.pTessellationState = 0;

	pipelineCreateInfo.layout = outPipeline->pipelineLayout;

	pipelineCreateInfo.renderPass = renderpass->handle;
	pipelineCreateInfo.subpass = 0;
	pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
	pipelineCreateInfo.basePipelineIndex = -1;

	VkResult result = vkCreateGraphicsPipelines(
		context->device.logicalDevice,
		VK_NULL_HANDLE,
		1,
		&pipelineCreateInfo,
		context->allocator,
		&outPipeline->handle);

	if (VulkanResultIsSuccess(result))
	{
		DE_DEBUG("Graphics pipeline created!");
		return true;
	}

	DE_ERROR("vkCreateGraphicsPipelines failed with %s.", VulkanResultString(result, true));
	return false;
}

void	VulkanPipelineDestroy(vulkanContext* context, vulkanPipeline* pipeline)
{
	if (pipeline)
	{
		// Destroy pipeline
		if (pipeline->handle)
		{
			vkDestroyPipeline(context->device.logicalDevice, pipeline->handle, context->allocator);
			pipeline->handle = 0;
		}

		// Destroy layout
		if (pipeline->pipelineLayout)
		{
			vkDestroyPipelineLayout(context->device.logicalDevice, pipeline->pipelineLayout, context->allocator);
			pipeline->pipelineLayout = 0;
		}
	}
}

void	VulkanPipelineBind(vulkanCommandBuffer* commandBuffer, VkPipelineBindPoint bindPoint, vulkanPipeline* pipeline)
{
	vkCmdBindPipeline(commandBuffer->handle, bindPoint, pipeline->handle);
}
