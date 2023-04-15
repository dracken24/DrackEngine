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

	return true;
}

void	VulkanObjectShader::VulkanObjectShaderDestroy(vulkanContext *context, struct vulkanObjectShader *shader)
{
}

void	VulkanObjectShader::VulkanObjectShaderUse(vulkanContext *context, struct vulkanObjectShader *shader)
{
}
