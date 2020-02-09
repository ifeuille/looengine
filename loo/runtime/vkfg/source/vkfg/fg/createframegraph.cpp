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
				//CHECK (VulkanLoader::Initialize ());

				FrameGraph  fg = null;// loo::global::MakeSharedPtr<VFrameGraph> (vdi);
				//CHECK (fg->Initialize ());

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