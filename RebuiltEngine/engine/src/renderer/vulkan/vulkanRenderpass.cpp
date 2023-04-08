/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 06-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	 vulkanRenderpass.hpp     *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include <renderer/vulkan/vulkanRenderpass.hpp>

#include <core/deMemory.hpp>

// KEEP: Change background color
void	VulkanRenderpassCreate(vulkanContext* context, vulkanRenderpass* renderpass,
			fl32 x, fl32 y, fl32 w, fl32 h, RgbaFl32 color, fl32 depth, uint32 stencil)
{
	renderpass->x = x;
	renderpass->y = y;
	renderpass->w = w;
	renderpass->h = h;

	renderpass->r = color.r;
	renderpass->g = color.g;
	renderpass->b = color.b;
	renderpass->a = color.a;

	renderpass->depth = depth;
	renderpass->stencil = stencil;

	// Main subpass
	VkSubpassDescription subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

	// Attachments TODO: make this configurable.
	uint32 attachmentDescriptionCount = 2;
	VkAttachmentDescription attachmentDescriptions[attachmentDescriptionCount];

	// Color attachment
	VkAttachmentDescription color_attachment;
	color_attachment.format = context->swapchain.imageFormat.format; // TODO: configurable
	color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
	color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;     // Do not expect any particular layout before render pass starts.
	color_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR; // Transitioned to after the render pass
	color_attachment.flags = 0;

	attachmentDescriptions[0] = color_attachment;

	VkAttachmentReference color_attachment_reference;
	color_attachment_reference.attachment = 0; // Attachment description array index
	color_attachment_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &color_attachment_reference;

	// Depth attachment, if there is one
	VkAttachmentDescription depthAttachment = {};
	depthAttachment.format = context->device.depthFormat;
	depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	attachmentDescriptions[1] = depthAttachment;

	// Depth attachment reference
	VkAttachmentReference depthAttachmentReference;
	depthAttachmentReference.attachment = 1;
	depthAttachmentReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	// TODO: other attachment types (input, resolve, preserve)

	// Depth stencil data.
	subpass.pDepthStencilAttachment = &depthAttachmentReference;

	// Input from a shader
	subpass.inputAttachmentCount = 0;
	subpass.pInputAttachments = 0;

	// Attachments used for multisampling colour attachments
	subpass.pResolveAttachments = 0;

	// Attachments not used in this subpass, but must be preserved for the next.
	subpass.preserveAttachmentCount = 0;
	subpass.pPreserveAttachments = 0;

	// Render pass dependencies. TODO: make this configurable.
	VkSubpassDependency dependency;
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.srcAccessMask = 0;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	dependency.dependencyFlags = 0;

	// Render pass create.
	VkRenderPassCreateInfo renderPassCreateInfo = {VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO};
	renderPassCreateInfo.attachmentCount = attachmentDescriptionCount;
	renderPassCreateInfo.pAttachments = attachmentDescriptions;
	renderPassCreateInfo.subpassCount = 1;
	renderPassCreateInfo.pSubpasses = &subpass;
	renderPassCreateInfo.dependencyCount = 1;
	renderPassCreateInfo.pDependencies = &dependency;
	renderPassCreateInfo.pNext = 0;
	renderPassCreateInfo.flags = 0;

	VK_CHECK(vkCreateRenderPass(
		context->device.logicalDevice,
		&renderPassCreateInfo,
		context->allocator,
		&renderpass->handle));
}

void	VulkanRenderpassDestroy(vulkanContext *context, vulkanRenderpass *renderpass)
{
	if (renderpass && renderpass->handle)
	{
		vkDestroyRenderPass(context->device.logicalDevice, renderpass->handle, context->allocator);
		renderpass->handle = 0;
	}
}

void	VulkanRenderpassBegin(vulkanCommandBuffer *commandBuffer, vulkanRenderpass *renderpass,
			VkFramebuffer frameBuffer)
{

	VkRenderPassBeginInfo beginInfo = {VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};
	beginInfo.renderPass = renderpass->handle;
	beginInfo.framebuffer = frameBuffer;
	beginInfo.renderArea.offset.x = renderpass->x;
	beginInfo.renderArea.offset.y = renderpass->y;
	beginInfo.renderArea.extent.width = renderpass->w;
	beginInfo.renderArea.extent.height = renderpass->h;

	VkClearValue clearValues[2];
	SetMemory(clearValues, sizeof(VkClearValue) * 2);
	clearValues[0].color.float32[0] = renderpass->r;
	clearValues[0].color.float32[1] = renderpass->g;
	clearValues[0].color.float32[2] = renderpass->b;
	clearValues[0].color.float32[3] = renderpass->a;
	clearValues[1].depthStencil.depth = renderpass->depth;
	clearValues[1].depthStencil.stencil = renderpass->stencil;

	beginInfo.clearValueCount = 2;
	beginInfo.pClearValues = clearValues;

	vkCmdBeginRenderPass(commandBuffer->handle, &beginInfo, VK_SUBPASS_CONTENTS_INLINE);
	commandBuffer->state = DE_COMMAND_BUFFER_STATE_IN_RENDER_PASS;
}

void	VulkanRenderpassEnd(vulkanCommandBuffer *commandBuffer, vulkanRenderpass *renderpass)
{
	vkCmdEndRenderPass(commandBuffer->handle);
	commandBuffer->state = DE_COMMAND_BUFFER_STATE_RECORDING;
}
