#include "global/global.h"
#include "global/types.h"
#include "core/context.h"
#include "vkfg/vulkan/framework/vulkandeviceext.h"
#include "vkfg/vulkan/framework/vulkanswapchain.h"
#include "audio/audio.h"
#include <iostream>


class FWApp2 final :public loo::core::Application, public loo::VulkanDeviceFn,public loo::core::EventListener
{
	loo::vkfg::VulkanDeviceExt		vulkan;
	loo::vkfg::VulkanSwapchainPtr	swapchain;
	loo::String				title;
	VkCommandPool		cmdPool = VK_NULL_HANDLE;

	// initialize vulkan objects
	VkQueue				cmd_queue;
	VkCommandBuffer		cmd_buffers[2] = {};
	VkFence				fences[2] = {};
	VkSemaphore			semaphores[2] = {};

	int colorindex = 0;
	loo::math::RGBA32f colors[3] = {
		loo::math::RGBA32f (1,0,0,1),
		loo::math::RGBA32f (0,1,0,1),
		loo::math::RGBA32f (0,0,1,1),
	};


	//for audio

public:
	FWApp2 (const std::string& name, uint32_t appid, loo::core::ContextConfig setting)
		:Application(name, appid, setting)
	{
		VulkanDeviceFn_Init (vulkan);
		listen ((int)loo::core::SAppEventType::SAPP_EVENTTYPE_TOUCHES);
		listen ((int)loo::core::SAppEventType::SAPP_EVENTTYPE_TOUCHES_BEGAN);
		listen ((int)loo::core::SAppEventType::SAPP_EVENTTYPE_TOUCHES_ENDED);
	}
	virtual ~FWApp2 ()
	{

	}
	virtual bool OnCreate ()
	{
		// create window and vulkan device
		CHECK_ERR (vulkan.Create (main_wnd->GetVulkanSurface (), "Test", "Engine", VK_API_VERSION_1_1, "nvidia"));

		// this is a test and the test should fail for any validation error
		vulkan.CreateDebugUtilsCallback (loo::vkfg::DebugUtilsMessageSeverity_All,
			[](const loo::vkfg::VulkanDeviceExt::DebugReport &rep) { CHECK (not rep.isError); });


		// initialize swapchain
		{
			VkFormat		color_fmt = VK_FORMAT_UNDEFINED;
			VkColorSpaceKHR	color_space = VK_COLOR_SPACE_MAX_ENUM_KHR;

			swapchain.reset (new loo::vkfg::VulkanSwapchain{ vulkan });

CHECK_ERR (swapchain->ChooseColorFormat (INOUT color_fmt, INOUT color_space));

CHECK_ERR (swapchain->Create (
				loo::math::uint2 (main_wnd->Width (), main_wnd->Height ()),
				color_fmt, color_space));
		}

		cmd_queue = vulkan.GetVkQueues ().front ().handle;

		{
			VkCommandPoolCreateInfo		pool_info = {};
			pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			pool_info.queueFamilyIndex = vulkan.GetVkQueues ().front ().familyIndex;
			pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
			VK_CHECK (vkCreateCommandPool (vulkan.GetVkDevice (), &pool_info, null, OUT &cmdPool));

			VkCommandBufferAllocateInfo	info = {};
			info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			info.pNext = null;
			info.commandPool = cmdPool;
			info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			info.commandBufferCount = 2;
			VK_CHECK (vkAllocateCommandBuffers (vulkan.GetVkDevice (), &info, OUT cmd_buffers));

			VkFenceCreateInfo	fence_info = {};
			fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
			fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
			VK_CHECK (vkCreateFence (vulkan.GetVkDevice (), &fence_info, null, OUT &fences[0]));
			VK_CHECK (vkCreateFence (vulkan.GetVkDevice (), &fence_info, null, OUT &fences[1]));

			VkSemaphoreCreateInfo	sem_info = {};
			sem_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
			sem_info.flags = 0;
			VK_CALL (vkCreateSemaphore (vulkan.GetVkDevice (), &sem_info, null, OUT &semaphores[0]));
			VK_CALL (vkCreateSemaphore (vulkan.GetVkDevice (), &sem_info, null, OUT &semaphores[1]));
		}

		//init audio
		// init sokol-audio with default params, no callback
		saudio_desc sd = { 0 };
		saudio_setup (&sd);
		assert (saudio_channels () == 1);

		return true;
	}

	virtual bool OnResize (uint32_t width, uint32_t height)
	{
		if (width == 0 or height == 0)
			return false;

		VK_CALL (vkDeviceWaitIdle (vulkan.GetVkDevice ()));

		VK_CALL (vkResetCommandPool (vulkan.GetVkDevice (), cmdPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT));

		CHECK (swapchain->Recreate (loo::math::uint2 (width, height)));
		return true;
	}

	virtual bool OnDestroy ()
	{
		// destroy vulkan objects
		{
			VK_CALL (vkDeviceWaitIdle (vulkan.GetVkDevice ()));

			vkDestroySemaphore (vulkan.GetVkDevice (), semaphores[0], null);
			vkDestroySemaphore (vulkan.GetVkDevice (), semaphores[1], null);
			vkDestroyFence (vulkan.GetVkDevice (), fences[0], null);
			vkDestroyFence (vulkan.GetVkDevice (), fences[1], null);
			vkDestroyCommandPool (vulkan.GetVkDevice (), cmdPool, null);
			cmdPool = VK_NULL_HANDLE;
		}

		swapchain->Destroy ();
		swapchain.reset ();

		vulkan.Destroy ();

		// shutdown sokol-audio
		saudio_shutdown ();
		return false;
	}
	virtual bool OnSuspend ()
	{
		return false;
	}
	virtual bool OnResume ()
	{
		return false;
	}
	virtual bool DoUpdateOverlay ()
	{
		return false;
	}
	virtual uint32_t DoUpdate (uint64_t pass)
	{
		LOO_UNUSED (pass);
#define BUF_SIZE 32
		// a small intermediate buffer so we don't need to push
 // individual samples, which would be quite inefficient
		float buf[BUF_SIZE];
		int buf_pos = 0;
		uint32_t count = 0;


		// generate and push audio samples...
		int num_frames_expect = saudio_expect ();
		for (int i = 0; i < num_frames_expect; i++) {
			// simple square wave generator
			buf[buf_pos++] = (count++ & (1 << 3)) ? 0.5f : -0.5f;
			if (buf_pos == BUF_SIZE) {
				buf_pos = 0;
				saudio_push (buf, BUF_SIZE);
			}
		}

		return 0;
	}
	virtual bool OnRefresh ()
	{


		if (loo::math::Any (main_wnd->GetSize () == loo::math::uint2 (0))) {
			std::this_thread::sleep_for (std::chrono::milliseconds (16));
			return false;
		}

		//main_wnd->SetTitle (title + ("[FPS: "s << ToString (uint (swapchain->GetFramesPerSecond ())) << ']'));

		// wait and acquire next image
		{
			VK_CHECK (vkWaitForFences (vulkan.GetVkDevice (), 1, &fences[total_num_frames & 1], true, loo::UMax));
			VK_CHECK (vkResetFences (vulkan.GetVkDevice (), 1, &fences[total_num_frames & 1]));

			VK_CALL (swapchain->AcquireNextImage (semaphores[0]));
		}

		// build command buffer
		{
			VkCommandBufferBeginInfo	begin_info = {};
			begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
			VK_CALL (vkBeginCommandBuffer (cmd_buffers[total_num_frames & 1], &begin_info));


			// image layout undefined to transfer optimal
			VkImageMemoryBarrier	image_barrier1;
			image_barrier1.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			image_barrier1.pNext = null;
			image_barrier1.image = swapchain->GetCurrentImage ();
			image_barrier1.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			image_barrier1.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			image_barrier1.srcAccessMask = 0;
			image_barrier1.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			image_barrier1.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			image_barrier1.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			image_barrier1.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			image_barrier1.subresourceRange.baseMipLevel = 0;
			image_barrier1.subresourceRange.levelCount = 1;
			image_barrier1.subresourceRange.baseArrayLayer = 0;
			image_barrier1.subresourceRange.layerCount = 1;

			vkCmdPipelineBarrier (cmd_buffers[total_num_frames & 1], VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0,
				0, null, 0, null, 1, &image_barrier1);


			// clear image
			loo::math::RGBA32f				color = colors[colorindex];// { loo::math::HSVColor{ loo::math::Fract (float (total_num_frames) / 60.0f) } };
			VkClearColorValue	clear_value{ { color.r, color.g, color.b, color.a } };

			VkImageSubresourceRange	range;
			range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			range.baseArrayLayer = 0;
			range.layerCount = 1;
			range.baseMipLevel = 0;
			range.levelCount = 1;

			vkCmdClearColorImage (cmd_buffers[total_num_frames & 1], swapchain->GetCurrentImage (), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &clear_value, 1, &range);


			// image layout transfer optimal to present source
			VkImageMemoryBarrier	image_barrier2;
			image_barrier2.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			image_barrier2.pNext = null;
			image_barrier2.image = swapchain->GetCurrentImage ();
			image_barrier2.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			image_barrier2.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
			image_barrier2.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			image_barrier2.dstAccessMask = 0;
			image_barrier2.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			image_barrier2.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			image_barrier2.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			image_barrier2.subresourceRange.baseMipLevel = 0;
			image_barrier2.subresourceRange.levelCount = 1;
			image_barrier2.subresourceRange.baseArrayLayer = 0;
			image_barrier2.subresourceRange.layerCount = 1;

			vkCmdPipelineBarrier (cmd_buffers[total_num_frames & 1], VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0,
				0, null, 0, null, 1, &image_barrier2);


			VK_CALL (vkEndCommandBuffer (cmd_buffers[total_num_frames & 1]));
		}


		// submit commands
		{
			VkSemaphore				signal_semaphores[] = { semaphores[1] };
			VkSemaphore				wait_semaphores[] = { semaphores[0] };
			VkPipelineStageFlags	wait_dst_mask[] = { VK_PIPELINE_STAGE_TRANSFER_BIT };
			STATIC_ASSERT (loo::CountOf (wait_semaphores) == loo::CountOf (wait_dst_mask),"");

			VkSubmitInfo				submit_info = {};
			submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submit_info.commandBufferCount = 1;
			submit_info.pCommandBuffers = &cmd_buffers[total_num_frames & 1];
			submit_info.waitSemaphoreCount = loo::uint (loo::CountOf (wait_semaphores));
			submit_info.pWaitSemaphores = wait_semaphores;
			submit_info.pWaitDstStageMask = wait_dst_mask;
			submit_info.signalSemaphoreCount = loo::uint (loo::CountOf (signal_semaphores));
			submit_info.pSignalSemaphores = signal_semaphores;

			VK_CHECK (vkQueueSubmit (cmd_queue, 1, &submit_info, fences[total_num_frames & 1]));
		}

		// present
		VkResult	err = swapchain->Present (cmd_queue, { semaphores[1] });
		switch (err) {
		case VK_SUCCESS:
			break;

		case VK_SUBOPTIMAL_KHR:
		case VK_ERROR_SURFACE_LOST_KHR:
		case VK_ERROR_OUT_OF_DATE_KHR:
			VK_CALL (vkQueueWaitIdle (cmd_queue));
			VK_CALL (vkResetCommandPool (vulkan.GetVkDevice (), cmdPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT));
			CHECK (swapchain->Recreate (main_wnd->GetSize ()));
			break;

		default:
			ASSERT (false && "Present failed");
			break;
		}
		return true;
	}

	virtual bool onEvent (loo::core::Event* e)
	{
		std::cout << "event handle:id=" << e->type << std::endl;
		utils::slog.i<<"event handle:id="<< e->type << utils::io::endl;
		if (e->type == (int)loo::core::SAppEventType::SAPP_EVENTTYPE_TOUCHES
			or e->type == (int)loo::core::SAppEventType::SAPP_EVENTTYPE_TOUCHES_BEGAN)
		{
			colorindex = (++colorindex) % 3;
		}
		return true;
	}
};

int main ()
{
	FFWApp2	app("windows_0",loo::core::MainAppID,loo::core::ContextConfig());

	app.Create ();
	app.Run ();
	return 0;
}
