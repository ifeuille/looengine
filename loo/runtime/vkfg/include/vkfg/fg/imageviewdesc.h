
#pragma once

#include "vkfg/fg/imagedesc.h"

namespace loo
{
	namespace vkfg
	{

		//
		// Hashed Image View Description
		//

		struct HashedImageViewDesc
		{
			// variables
		private:
			ImageViewDesc		_desc;
			HashVal				_hash;

			// methods
		public:
			HashedImageViewDesc (const ImageViewDesc &desc) :
				_desc{ desc }, _hash{ HashOf (_desc) }
			{}

			HashedImageViewDesc (const ImageViewDesc &view, const ImageDesc &desc) : _desc{ view }
			{
				_desc.Validate (desc);
				_hash = HashOf (_desc);
			}

			HashedImageViewDesc (const ImageDesc &desc) :
				_desc{ desc }, _hash{ HashOf (_desc) }
			{}

			HashedImageViewDesc (const HashedImageViewDesc &other) = default;


			ND_ ImageViewDesc const&	Get ()	const { return _desc; }
			ND_ HashVal					Hash ()	const { return _hash; }

			ND_ bool  operator == (const HashedImageViewDesc &rhs)	const { return _desc == rhs._desc; }
		};


		struct HashOfImageViewDesc
		{
			ND_ size_t  operator () (const HashedImageViewDesc &value) const
			{
				return size_t (value.Hash ());
			}
		};

	}
}