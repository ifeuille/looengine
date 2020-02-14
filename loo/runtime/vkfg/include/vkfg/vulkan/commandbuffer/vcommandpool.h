
#pragma once

#include "vkfg/vulkan/vcommon.h"


namespace loo
{
	namespace vkfg
	{

		//
		// Vulkan Command Pool
		//

		class VCommandPool
		{
			// types
		private:
			using CmdBufPool_t = FixedArray< VkCommandBuffer, 32 >;


			// variables
		private:
			VkCommandPool			_pool = VK_NULL_HANDLE;

			mutable SpinLock		_cmdGuard;			// TODO: use lock-free ?
			mutable CmdBufPool_t	_freePrimaries;
			mutable CmdBufPool_t	_freeSecondaries;

			RWDataRaceCheck			_drCheck;

			DEBUG_ONLY (
				int					_cmdBufCount = 0;
			)


				// methods
		public:
			VCommandPool () {}
			~VCommandPool ();

			bool Create (const VDevice &dev, VDeviceQueueInfoPtr queue, StringView dbgName = Default);
			void Destroy (const VDevice &dev);

			ND_ VkCommandBuffer	AllocPrimary (const VDevice &dev);
			ND_ VkCommandBuffer	AllocSecondary (const VDevice &dev);

			void Deallocate (const VDevice &dev, VkCommandBuffer cmd);

			void ResetAll (const VDevice &dev, VkCommandPoolResetFlags flags);
			void TrimAll (const VDevice &dev, VkCommandPoolTrimFlags flags);

			void Reset (const VDevice &dev, VkCommandBuffer cmd, VkCommandBufferResetFlags flags);

			void RecyclePrimary (VkCommandBuffer cmd) const;
			void RecycleSecondary (VkCommandBuffer cmd) const;

			ND_ bool	IsCreated ()	const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _pool; }
		};


	}
}