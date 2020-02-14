
#include "vkfg/vulkan/raytracing/vraytracingpipeline.h"
#include "vkfg/vulkan/instance/vresourcemanager.h"
#include "vkfg/vulkan/utils/venumcast.h"
#include "vkfg/vulkan/instance/vdevice.h"

namespace loo
{
	namespace vkfg
	{

		/*
		=================================================
			destructor
		=================================================
		*/
		VRayTracingPipeline::~VRayTracingPipeline ()
		{
			CHECK (not _baseLayoutId);
		}

		/*
		=================================================
			Create
		=================================================
		*/
		bool VRayTracingPipeline::Create (const RayTracingPipelineDesc &desc, RawPipelineLayoutID layoutId)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);

			_shaders.reserve (desc._shaders.size () * 2);

			for (auto& stage : desc._shaders)
			{
				const auto	vk_stage = VEnumCast (stage.second.shaderType);

				for (auto& sh : stage.second.data)
				{
					auto*	vk_shader = UnionGetIf< PipelineDescription::VkShaderPtr > (&sh.second);
					CHECK_ERR (vk_shader);

					_shaders.push_back (ShaderModule{ stage.first, vk_stage, *vk_shader, EShaderDebugMode_From (sh.first), stage.second.specConstants });
				}
			}

			std::sort (_shaders.begin (), _shaders.end (),
				[](auto& lhs, auto& rhs) { return lhs.shaderId < rhs.shaderId; });

			_baseLayoutId = PipelineLayoutID{ layoutId };
			return true;
		}

		/*
		=================================================
			Destroy
		=================================================
		*/
		void VRayTracingPipeline::Destroy (VResourceManager &resMngr)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);

			if (_baseLayoutId) {
				resMngr.ReleaseResource (_baseLayoutId.Release ());
			}

			_shaders.clear ();

			_baseLayoutId = Default;
		}


	}
}