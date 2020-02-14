
#include "vkfg/vulkan/pipeline/vmeshpipeline.h"
#include "vkfg/vulkan/utils/venumcast.h"
#include "vkfg/vulkan/instance/vresourcemanager.h"
#include "vkfg/vulkan/instance/vdevice.h"

namespace loo
{
	namespace vkfg
	{

		/*
		=================================================
			PipelineInstance::UpdateHash
		=================================================
		*/
		void VMeshPipeline::PipelineInstance::UpdateHash ()
		{
#	if LOO_FAST_HASH
			_hash = loo::HashOf (&_hash, sizeof (*this) - sizeof (_hash));
#	else
			_hash = HashOf (layoutId) +
				HashOf (renderPassId) + HashOf (subpassIndex) +
				HashOf (renderState) + HashOf (dynamicState) +
				HashOf (viewportCount) + HashOf (debugMode);		//+ HashOf( flags );
#	endif
		}
		//-----------------------------------------------------------------------------



		/*
		=================================================
			destructor
		=================================================
		*/
		VMeshPipeline::~VMeshPipeline ()
		{
			CHECK (_instances.empty ());
		}

		/*
		=================================================
			Create
		=================================================
		*/
		bool VMeshPipeline::Create (const MeshPipelineDesc &desc, RawPipelineLayoutID layoutId, StringView dbgName)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);

			for (auto& stage : desc._shaders)
			{
				const auto	vk_stage = VEnumCast (stage.first);

				for (auto& sh : stage.second.data)
				{
					auto*	vk_shader = UnionGetIf< PipelineDescription::VkShaderPtr > (&sh.second);
					CHECK_ERR (vk_shader);

					_shaders.push_back (ShaderModule{ vk_stage, *vk_shader, EShaderDebugMode_From (sh.first) });
				}
			}
			CHECK_ERR (_shaders.size ());

			_baseLayoutId = PipelineLayoutID{ layoutId };
			_topology = desc._topology;
			_earlyFragmentTests = desc._earlyFragmentTests;
			_debugName = dbgName;

			return true;
		}

		/*
		=================================================
			Destroy
		=================================================
		*/
		void VMeshPipeline::Destroy (VResourceManager &resMngr)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);

			auto&	dev = resMngr.GetDevice ();

			for (auto& ppln : _instances) {
				dev.vkDestroyPipeline (dev.GetVkDevice (), ppln.second, null);
				resMngr.ReleaseResource (const_cast<PipelineInstance &>(ppln.first).layoutId);
			}

			if (_baseLayoutId) {
				resMngr.ReleaseResource (_baseLayoutId.Release ());
			}

			_shaders.clear ();
			_instances.clear ();
			_debugName.clear ();
			_baseLayoutId = Default;
			_topology = Default;
			_earlyFragmentTests = false;
		}


	}
}