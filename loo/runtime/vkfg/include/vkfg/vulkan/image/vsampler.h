
#pragma once

#include "vkfg/fg/samplerdesc.h"
#include "vkfg/vulkan/vcommon.h"

namespace loo
{
	namespace vkfg
	{

		//
		// Vulkan Sampler immutable data
		//

		class VSampler final
		{
			// variables
		private:
			VkSampler				_sampler = VK_NULL_HANDLE;
			HashVal					_hash;
			VkSamplerCreateInfo		_createInfo = {};

			DebugName_t				_debugName;

			mutable RWDataRaceCheck			_drCheck;


			// methods
		public:
			VSampler () {}
			VSampler (VSampler &&) = default;
			VSampler (const VDevice &dev, const SamplerDesc &desc);
			~VSampler ();

			bool Create (const VDevice &dev, StringView dbgName);
			void Destroy (VResourceManager &);

			ND_ bool	operator == (const VSampler &rhs) const;

			ND_ VkSampler					Handle ()		const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _sampler; }
			ND_ HashVal						GetHash ()		const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _hash; }
			//ND_ VkSamplerCreateInfo const&	CreateInfo ()	const	{ SHAREDLOCK(RWDataRaceCheck,  _drCheck );  return _createInfo; }


		private:
			ND_ static HashVal  _CalcHash (const VkSamplerCreateInfo &ci);
		};


	}	
}


namespace std
{
	template <>
	struct hash< loo::vkfg::VSampler > {
		ND_ size_t  operator () (const loo::vkfg::VSampler &value) const {
			return size_t (value.GetHash ());
		}
	};

}	// std
