/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 15-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	vulkanShaderUtils.hpp     *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef VULKANSHADERUTILS_HPP
# define VULKANSHADERUTILS_HPP

#include <renderer/vulkan/vulkanTypes.inl>

bl8		CreateShaderModule(vulkanContext *context, const char *name,
			const char *type_str, VkShaderStageFlagBits shaderStageFlag,
			uint32 stageIndex, vulkanShaderStage *shaderStages);

#endif
