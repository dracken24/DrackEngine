/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 15-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	  vulkanObjShader.cpp     *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include <renderer/vulkan/shaders/vulkanObjShader.hpp>

#include <renderer/vulkan/vulkanShaderUtils.hpp>
#include <renderer/vulkan/vulkanPipeline.hpp>

#include <math/structs.hpp>

#include <core/deMemory.hpp>
#include <core/logger.hpp>

#define BUILTIN_SHADER_NAME_OBJECT "Builtin.ObjectShader"

//**********************************************************************//
//**                     Constructors / Destructor                    **//
//**********************************************************************//

// public
VulkanObjectShader::VulkanObjectShader(vulkanContext *context, vulkanObjectShader *outShader)
{
	VulkanObjectShaderCreate(context, outShader);
}

VulkanObjectShader::~VulkanObjectShader(void)
{

}

// private
VulkanObjectShader::VulkanObjectShader(void)
{

}

VulkanObjectShader::VulkanObjectShader(VulkanObjectShader const &copy)
{
	if (this != &copy)
	{
		*this = copy;
	}
}

VulkanObjectShader &VulkanObjectShader::operator=(VulkanObjectShader const &copy)
{
	if (this != &copy)
	{

	}

	return *this;
}

//**********************************************************************//
//**                          PUBLIC METHODS                          **//
//**********************************************************************//

bl8		VulkanObjectShader::VulkanObjectShaderCreate(vulkanContext *context, vulkanObjectShader *outShader)
{
	// Shader module init per stage.
	char stageTypeStrs[DE_OBJECT_SHADER_STAGE_COUNT][5] = {"vert", "frag"};
	VkShaderStageFlagBits stageTypes[DE_OBJECT_SHADER_STAGE_COUNT] = {VK_SHADER_STAGE_VERTEX_BIT, VK_SHADER_STAGE_FRAGMENT_BIT};

	for (uint32 i = 0; i < DE_OBJECT_SHADER_STAGE_COUNT; ++i)
	{
		if (!CreateShaderModule(context, BUILTIN_SHADER_NAME_OBJECT, stageTypeStrs[i], stageTypes[i], i, outShader->stages))
		{
			DE_ERROR("Unable to create %s shader module for '%s'.", stageTypeStrs[i], BUILTIN_SHADER_NAME_OBJECT);
			return false;
		}
	}

	// TODO: Descriptors

	// Pipeline creation
	VkViewport viewport;
	viewport.x = 0.0f;
	viewport.y = (fl32)context->framebufferHeight;
	viewport.width = (fl32)context->framebufferWidth;
	viewport.height = -(fl32)context->framebufferHeight;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	// Scissor
	VkRect2D scissor;
	scissor.offset.x = scissor.offset.y = 0;
	scissor.extent.width = context->framebufferWidth;
	scissor.extent.height = context->framebufferHeight;

	// Attributes
	uint32 offset = 0;
	const sint32 attribute_count = 1;
	VkVertexInputAttributeDescription attribute_descriptions[attribute_count];
	// Position
	VkFormat formats[attribute_count] = {
		VK_FORMAT_R32G32B32_SFLOAT};
	uint64 sizes[attribute_count] = {
		sizeof(Vector3)};
	for (uint32 i = 0; i < attribute_count; ++i)
	{
		attribute_descriptions[i].binding = 0;	// binding index - should match binding desc
		attribute_descriptions[i].location = i; // attrib location
		attribute_descriptions[i].format = formats[i];
		attribute_descriptions[i].offset = offset;
		offset += sizes[i];
	}

	// TODO: Desciptor set layouts.

	// Stages
	// NOTE: Should match the number of shader->stages.
	VkPipelineShaderStageCreateInfo stage_create_infos[DE_OBJECT_SHADER_STAGE_COUNT];
	SetMemory(stage_create_infos, sizeof(stage_create_infos));
	for (uint32 i = 0; i < DE_OBJECT_SHADER_STAGE_COUNT; ++i)
	{
		stage_create_infos[i].sType = outShader->stages[i].shaderStageCreateInfo.sType;
		stage_create_infos[i] = outShader->stages[i].shaderStageCreateInfo;
	}

	if (!VulkanGraphicsPipelineCreate(context, &context->mainRenderpass, attribute_count,
		attribute_descriptions, 0, 0, DE_OBJECT_SHADER_STAGE_COUNT, stage_create_infos,
		viewport, scissor, false, &outShader->pipeline))
	{
		DE_ERROR("Failed to load graphics pipeline for object shader.");
		return false;
	}

	return true;
}

void	VulkanObjectShader::VulkanObjectShaderDestroy(vulkanContext *context, struct vulkanObjectShader *shader)
{
	VulkanPipelineDestroy(context, &shader->pipeline);

	// Destroy shader modules.
	for (uint32 i = 0; i < DE_OBJECT_SHADER_STAGE_COUNT; ++i)
	{
		vkDestroyShaderModule(context->device.logicalDevice, shader->stages[i].handle, context->allocator);
		shader->stages[i].handle = 0;
	}
}

void	VulkanObjectShader::VulkanObjectShaderUse(vulkanContext *context, struct vulkanObjectShader *shader)
{
	uint32 imageIndex = context->imageIndex;
	VulkanPipelineBind(&context->graphicsCommandBuffers[imageIndex], VK_PIPELINE_BIND_POINT_GRAPHICS, &shader->pipeline);
}
