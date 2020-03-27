#include "vkfg/vulkan/pipeline/vcomputepipeline.h"
#include "vkfg/fg/enumutils.h"
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
		void VComputePipeline::PipelineInstance::UpdateHash ()
		{
#	if LOO_FAST_HASH
			_hash = loo::HashOf (&_hash, sizeof (*this) - sizeof (_hash));
#	else
			_hash = HashOf (layoutId) + HashOf (localGroupSize) +
				HashOf (flags) + HashOf (debugMode);
#	endif
		}
		//-----------------------------------------------------------------------------



		/*
		=================================================
			constructor
		=================================================
		*/
		VComputePipeline::VComputePipeline () :
			_localSizeSpec{ ComputePipelineDesc::UNDEFINED_SPECIALIZATION }
		{
		}

		/*
		=================================================
			destructor
		=================================================
		*/
		VComputePipeline::~VComputePipeline ()
		{
		}

		/*
		=================================================
			Create
		=================================================
		*/
		bool VComputePipeline::Create (const ComputePipelineDesc &desc, RawPipelineLayoutID layoutId, StringView dbgName)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);

			for (auto& sh : desc._shader.data)
			{
				auto*	vk_shader = UnionGetIf< PipelineDescription::VkShaderPtr > (&sh.second);
				CHECK_ERR (vk_shader);

				_shaders.push_back (ShaderModule{ *vk_shader, EShaderDebugMode_From (sh.first) });
			}
			CHECK_ERR (_shaders.size ());

			_baseLayoutId = PipelineLayoutID{ layoutId };
			_defaultLocalGroupSize = desc._defaultLocalGroupSize;
			_localSizeSpec = desc._localSizeSpec;
			_debugName = dbgName;

			return true;
		}

		/*
		=================================================
			Destroy
		=================================================
		*/
		void VComputePipeline::Destroy (VResourceManager &resMngr)
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

			_instances.clear ();
			_debugName.clear ();
			_shaders.clear ();

			_baseLayoutId = Default;
			_defaultLocalGroupSize = Default;
			_localSizeSpec = loo::math::uint3{ ComputePipelineDesc::UNDEFINED_SPECIALIZATION };
		}


	}
}