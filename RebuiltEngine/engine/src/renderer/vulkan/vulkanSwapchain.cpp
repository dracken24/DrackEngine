/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 25-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE:     vulkanSwapchain.cpp      *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "renderer/vulkan/vulkanSwapchain.hpp"

#include <core/logger.hpp>
#include <core/deMemory.hpp>
#include <renderer/vulkan/vulkanDevice.hpp>

void	create(vulkanContext *context, uint32 width, uint32 height, vulkanSwapchain *swapchain);
void	destroy(vulkanContext *context, vulkanSwapchain *swapchain);
