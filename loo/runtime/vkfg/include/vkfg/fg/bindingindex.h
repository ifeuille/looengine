

#pragma once

#include "global/global.h"
#include "global/template/hash.h"
namespace loo
{

	namespace vkfg
	{
		//
		// Binding Index
		//
		struct BindingIndex
		{
			friend struct std::hash< BindingIndex >;
			using Index_t = uint16_t;

			// variables
		private:
			Index_t		_index1 = UMax;	// resource dependend index, may be optimized to minimize resource switches between pipelines, used in OpenGL, DirectX
			Index_t		_index2 = UMax;	// resource unique index in current pipeline, used in Vulkan, OpenCL, software renderer

		// methods
		public:
			BindingIndex () {}

			explicit BindingIndex (uint perResourceIndex, uint uniqueIndex) : _index1{ Index_t (perResourceIndex) }, _index2{ Index_t (uniqueIndex) } {}

			ND_ bool		operator == (const BindingIndex &rhs) const { return _index1 == rhs._index1 and _index2 == rhs._index2; }
			ND_ bool		operator != (const BindingIndex &rhs) const { return not (*this == rhs); }

			ND_ Index_t		GLBinding ()	const { return _index1; }
			ND_ Index_t		DXBinding ()	const { return _index1; }
			ND_ Index_t		VKBinding ()	const { return _index2; }
			ND_ Index_t		CLBinding ()	const { return _index2; }
			ND_ Index_t		SWBinding ()	const { return _index2; }
			ND_ Index_t		Unique ()		const { return _index2; }
		};
	}


}	// loo


namespace std
{
	template <>
	struct hash< loo::vkfg::BindingIndex >
	{
		ND_ size_t  operator () (const loo::vkfg::BindingIndex &value) const
		{
#if LOO_FAST_HASH
			return size_t (loo::HashOf (this, sizeof (this)));
#else
			return size_t (loo::HashOf (value._index1) + loo::HashOf (value._index2));
#endif
		}
	};

}	// std
