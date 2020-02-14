
#include "vkfg/vulkan/commandbuffer/vcommandpool.h"
#include "vkfg/vulkan/instance/vdevice.h"
#include "global/algorithms/stringutils.h"

namespace loo
{
	namespace vkfg
	{

		/*
		=================================================
			destructor
		=================================================
		*/
		VCommandPool::~VCommandPool ()
		{
			CHECK (not _pool);
		}

		/*
		=================================================
			Create
		=================================================
		*/
		bool VCommandPool::Create (const VDevice &dev, VDeviceQueueInfoPtr queue, StringView dbgName)
		{
			CHECK_ERR (queue);
			EXLOCK (RWDataRaceCheck,_drCheck);
			CHECK_ERR (not IsCreated ());

			VkCommandPoolCreateInfo	info = {};
			info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
			info.queueFamilyIndex = uint (queue->familyIndex);

			VK_CHECK (dev.vkCreateCommandPool (dev.GetVkDevice (), &info, null, OUT &_pool));

			if (dbgName.size ())
				dev.SetObjectName (uint64_t (_pool), dbgName, VK_OBJECT_TYPE_COMMAND_POOL);

			return true;
		}

		/*
		=================================================
			Destroy
		=================================================
		*/
		void VCommandPool::Destroy (const VDevice &dev)
		{
			EXLOCK (RWDataRaceCheck,_drCheck);

			if (_pool)
			{
				dev.vkDestroyCommandPool (dev.GetVkDevice (), _pool, null);
				_pool = VK_NULL_HANDLE;

				DEBUG_ONLY (
					LOO_LOGD ("Max command buffers: "s << ToString (_cmdBufCount));
				_cmdBufCount = 0;
				)
			}

			EXLOCK (SpinLock,_cmdGuard);
			_freePrimaries.clear ();
			_freeSecondaries.clear ();
		}

		/*
		=================================================
			ResetAll
		=================================================
		*/
		void VCommandPool::ResetAll (const VDevice &dev, VkCommandPoolResetFlags flags)
		{
			EXLOCK (RWDataRaceCheck,_drCheck);
			CHECK_ERR (IsCreated ()/*, void ()*/);

			VK_CALL (dev.vkResetCommandPool (dev.GetVkDevice (), _pool, flags));
		}

		/*
		=================================================
			TrimAll
		=================================================
		*/
		void VCommandPool::TrimAll (const VDevice &dev, VkCommandPoolTrimFlags flags)
		{
			EXLOCK (RWDataRaceCheck,_drCheck);
			CHECK_ERR (IsCreated ()/*, void ()*/);

			dev.vkTrimCommandPool (dev.GetVkDevice (), _pool, flags);
		}

		/*
		=================================================
			Reset
		=================================================
		*/
		void VCommandPool::Reset (const VDevice &dev, VkCommandBuffer cmd, VkCommandBufferResetFlags flags)
		{
			EXLOCK (RWDataRaceCheck,_drCheck);
			CHECK_ERR (IsCreated ()/*, void ()*/);

			VK_CALL (dev.vkResetCommandBuffer (cmd, flags));
		}

		/*
		=================================================
			RecyclePrimary / RecycleSecondary
		=================================================
		*/
		void VCommandPool::RecyclePrimary (VkCommandBuffer cmd) const
		{
			EXLOCK (SpinLock, _cmdGuard);
			_freePrimaries.push_back (cmd);
		}

		void VCommandPool::RecycleSecondary (VkCommandBuffer cmd) const
		{
			EXLOCK (SpinLock, _cmdGuard);
			_freeSecondaries.push_back (cmd);
		}

		/*
		=================================================
			AllocPrimary
		=================================================
		*/
		VkCommandBuffer  VCommandPool::AllocPrimary (const VDevice &dev)
		{
			SHAREDLOCK (RWDataRaceCheck, _drCheck);
			CHECK_ERR (IsCreated ()/*, VK_NULL_HANDLE*/);

			// use cache
			{
				EXLOCK (SpinLock, _cmdGuard);
				if (_freePrimaries.size ())
				{
					VkCommandBuffer  cmd = _freePrimaries.back ();
					_freePrimaries.pop_back ();
					return cmd;
				}
			}

			VkCommandBufferAllocateInfo	info = {};
			info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			info.pNext = null;
			info.commandPool = _pool;
			info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			info.commandBufferCount = 1;

			VkCommandBuffer	cmd = VK_NULL_HANDLE;
			VK_CHECK (dev.vkAllocateCommandBuffers (dev.GetVkDevice (), &info, OUT &cmd));

			DEBUG_ONLY (++_cmdBufCount);
			return cmd;
		}

		/*
		=================================================
			AllocSecondary
		=================================================
		*/
		VkCommandBuffer  VCommandPool::AllocSecondary (const VDevice &dev)
		{
			SHAREDLOCK (RWDataRaceCheck, _drCheck);
			CHECK_ERR (IsCreated ()/*, VK_NULL_HANDLE*/);

			// use cache
			{
				EXLOCK (SpinLock, _cmdGuard);
				if (_freeSecondaries.size ())
				{
					VkCommandBuffer  cmd = _freeSecondaries.back ();
					_freeSecondaries.pop_back ();
					return cmd;
				}
			}

			VkCommandBufferAllocateInfo	info = {};
			info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			info.pNext = null;
			info.commandPool = _pool;
			info.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
			info.commandBufferCount = 1;

			VkCommandBuffer  cmd = VK_NULL_HANDLE;
			VK_CHECK (dev.vkAllocateCommandBuffers (dev.GetVkDevice (), &info, OUT &cmd));

			DEBUG_ONLY (++_cmdBufCount);
			return cmd;
		}

		/*
		=================================================
			Deallocate
		=================================================
		*/
		void  VCommandPool::Deallocate (const VDevice &dev, VkCommandBuffer cmd)
		{
			SHAREDLOCK (RWDataRaceCheck, _drCheck);
			CHECK_ERR (IsCreated ()/*, void ()*/);

			dev.vkFreeCommandBuffers (dev.GetVkDevice (), _pool, 1, &cmd);

			//DEBUG_ONLY( --_cmdBufCount );
		}

	}
}