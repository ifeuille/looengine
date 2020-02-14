#include "vkfg/vulkan/instance/vframegraph.h"

namespace loo
{
	namespace vkfg
	{
		struct CreateFrameGraphVisitLocal
		{
			FrameGraph operator()(const VulkanDeviceInfo &vdi)const
			{
				CHECK (vdi.instance and vdi.physicalDevice and vdi.device and not vdi.queues.empty ());
				CHECK (VulkanLoader::Initialize ());
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4316)
#endif
				auto  fg = loo::global::MakeSharedPtr<VFrameGraph> (vdi);
				CHECK (fg->Initialize ());
#ifdef _MSC_VER
#pragma warning(pop)
#endif
				return fg;
			}
			template<typename T>
			FrameGraph operator()(const T &)const
			{
				ASSERT (false);
				return null;
			}
		};
		/*
		=================================================
			CreateFrameGraph
		=================================================
		*/
		FrameGraph  IFrameGraph::CreateFrameGraph (const DeviceInfo_t &ci)
		{
			auto visitfunc = CreateFrameGraphVisitLocal ();
			FrameGraph	result = Visit (ci, visitfunc);
			return result;
		}

	}
}