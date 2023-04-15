/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 15-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	  vulkanObjShader.hpp       *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef VULKANOBJSHADER_HPP
# define VULKANOBJSHADER_HPP

#include <renderer/vulkan/vulkanTypes.inl>
#include <renderer/rendererTypes.inl>

class VulkanObjectShader
{
	//**********************************************************************//
	//**                     Constructors / Destructor                    **//
	//**********************************************************************//
	public:
		VulkanObjectShader(void);
		VulkanObjectShader(vulkanContext *context, vulkanObjectShader *outShader);
		~VulkanObjectShader(void);

	private:
		VulkanObjectShader(VulkanObjectShader const & copy);
		VulkanObjectShader &operator=(VulkanObjectShader const &copy);

	//**********************************************************************//
	//**                          PUBLIC METHODS                          **//
	//**********************************************************************//
	public:
		bl8		VulkanObjectShaderCreate(vulkanContext *context, vulkanObjectShader *outShader);
		void	VulkanObjectShaderDestroy(vulkanContext *context, struct vulkanObjectShader *shader);
		void	VulkanObjectShaderUse(vulkanContext *context, struct vulkanObjectShader *shader);
};

#endif
