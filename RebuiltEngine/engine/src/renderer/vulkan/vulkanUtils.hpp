/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 07-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE:       vulkanUtils.hpp        *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef VULKAN_UTILS_CPP
# define VULKAN_UTILS_CPP

# include <renderer/vulkan/vulkanTypes.inl>

/**
 * Returns the string representation of result.
 * @param result The result to get the string for.
 * @param get_extended Indicates whether to also return an extended result.
 * @returns The error code and/or extended error message in string form. Defaults to success for unknown result types.
 */
const char  *VulkanResultString(VkResult result, bl8 getExtended);

/**
 * Inticates if the passed result is a success or an error as defined by the Vulkan spec.
 * @returns True if success; otherwise false. Defaults to true for unknown result types.
 */
bl8         VulkanResultIsSuccess(VkResult result);

#endif
