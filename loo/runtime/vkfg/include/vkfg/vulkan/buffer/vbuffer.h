#pragma once

#include "vkfg/fg/bufferdesc.h"
#include "vkfg/fg/memorydesc.h"
#include "vkfg/fg/framegraph.h"
#include "vkfg/vulkan/vcommon.h"

namespace loo
{
	namespace vkfg
	{
		//
		// Vulkan Buffer immutable data
		//
		class VBuffer final
		{
			friend class VBufferUnitTest;

			// types
		private:
			using OnRelease_t = IFrameGraph::OnExternalBufferReleased_t;



			// variables
		private:
			VkBuffer				_buffer = VK_NULL_HANDLE;
			MemoryID				_memoryId;
			BufferDesc				_desc;
			EQueueFamilyMask		_queueFamilyMask = Default;
			VkAccessFlags			_readAccessMask = 0;

			DebugName_t				_debugName;
			OnRelease_t				_onRelease;

			RWDataRaceCheck			_drCheck;

			// methods
		public:
			VBuffer () {}
			VBuffer (VBuffer &&) = default;
			~VBuffer ();

			bool Create (VResourceManager &, const BufferDesc &desc, RawMemoryID memId, VMemoryObj &memObj,
				EQueueFamilyMask queueFamilyMask, StringView dbgName);

			bool Create (const VDevice &dev, const VulkanBufferDesc &desc, StringView dbgName, OnRelease_t &&onRelease);

			void Destroy (VResourceManager &);

			//void Merge (BufferViewMap_t &, OUT AppendableVkResources_t) const;

			//ND_ VkBufferView		GetView (const HashedBufferViewDesc &) const;

			ND_ VulkanBufferDesc	GetApiSpecificDescription () const;

			ND_ bool				IsReadOnly ()			const;

			ND_ VkBuffer			Handle ()				const { SHAREDLOCK (RWDataRaceCheck,_drCheck);  return _buffer; }
			ND_ RawMemoryID			GetMemoryID ()			const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _memoryId.Get (); }

			ND_ BufferDesc const&	Description ()			const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _desc; }
			ND_ BytesU				Size ()					const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _desc.size; }

			ND_ VkAccessFlags		GetAllReadAccessMask ()	const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _readAccessMask; }

			ND_ bool				IsExclusiveSharing ()	const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _queueFamilyMask == Default; }
			ND_ EQueueFamilyMask	GetQueueFamilyMask ()	const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _queueFamilyMask; }
			ND_ StringView			GetDebugName ()			const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _debugName; }
		};
	}
}