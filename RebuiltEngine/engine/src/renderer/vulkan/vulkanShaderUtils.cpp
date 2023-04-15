/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 15-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	vulkanShaderUtils.cpp     *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include <renderer/vulkan/vulkanShaderUtils.hpp>

#include "core/deString.hpp"
#include "core/logger.hpp"
#include "core/deMemory.hpp"

#include <platform/filesSystems.hpp>

bl8		CreateShaderModule(vulkanContext *context, const char *name,
			const char *type_str, VkShaderStageFlagBits shaderStageFlag,
			uint32 stageIndex, vulkanShaderStage *shaderStages)
{
	// Build file name.
	char file_name[512];
	StringFormat(file_name, "assets/shaders/%s.%s.spv", name, type_str);

	SetMemory(&shaderStages[stageIndex].createInfo, sizeof(VkShaderModuleCreateInfo));
	shaderStages[stageIndex].createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;

	// Obtain file handle.
	fileHandle handle;
	if (!FilesystemOpen(file_name, FILE_MODE_READ, true, &handle))
	{
		DE_ERROR("Unable to read shader module: %s.", file_name);
		return false;
	}

	// Read the entire file as binary.
	uint64 size = 0;
	uint8 *fileBuffer = 0;
	if (!FilesystemReadAllBytes(&handle, &fileBuffer, &size))
	{
		DE_ERROR("Unable to binary read shader module: %s.", file_name);
		return false;
	}
	shaderStages[stageIndex].createInfo.codeSize = size;
	shaderStages[stageIndex].createInfo.pCode = (uint32 *)fileBuffer;

	// Close the file.
	FilesystemClose(&handle);

	VK_CHECK(vkCreateShaderModule(context->device.logicalDevice, &shaderStages[stageIndex].createInfo,
		context->allocator, &shaderStages[stageIndex].handle));

	// Shader stage info. Main entry for shaders.
	SetMemory(&shaderStages[stageIndex].shaderStageCreateInfo, sizeof(VkPipelineShaderStageCreateInfo));
	shaderStages[stageIndex].shaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStages[stageIndex].shaderStageCreateInfo.stage = shaderStageFlag;
	shaderStages[stageIndex].shaderStageCreateInfo.module = shaderStages[stageIndex].handle;
	shaderStages[stageIndex].shaderStageCreateInfo.pName = "main";

	return true;
}
