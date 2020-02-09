#pragma once

#include "vkfg/fg/mimaplevel.h"
#include "vkfg/fg/multisamples.h"
#include "vkfg/fg/imagelayer.h"
#include "vkfg/fg/imageswizzle.h"
#include "vkfg/fg/enums.h"

namespace loo
{
	namespace vkfg
	{
		//
		// Image Description
		//
		struct ImageDesc
		{
			// variables
			EImage				imageType = Default;
			loo::math::uint3				dimension;	// width, height, depth, layers
			EPixelFormat		format = Default;
			EImageUsage			usage = Default;
			ImageLayer			arrayLayers;
			MipmapLevel			maxLevel;
			MultiSamples		samples;	// if > 1 then enabled multisampling
			EQueueUsage			queues = Default;
			//bool				isLogical	= false;
			bool				isExternal = false;

			// methods
			ImageDesc () {}

			ImageDesc (EImage		imageType,
				const loo::math::uint3 &dimension,
				EPixelFormat	format,
				EImageUsage	usage,
				ImageLayer	arrayLayers = Default,
				MipmapLevel	maxLevel = Default,
				MultiSamples	samples = Default,
				EQueueUsage	queues = Default);

			void Validate ();

			ImageDesc&  SetType (EImage value) { imageType = value;  return *this; }
			ImageDesc&  SetDimension (const loo::math::uint2 &value) { dimension = loo::math::uint3{ value, 1 };  return *this; }
			ImageDesc&  SetDimension (const loo::math::uint3 &value) { dimension = value;  return *this; }
			ImageDesc&  SetUsage (EImageUsage value) { usage = value;  return *this; }
			ImageDesc&  SetFormat (EPixelFormat value) { format = value;  return *this; }
			ImageDesc&  SetQueues (EQueueUsage value) { queues = value;  return *this; }
			ImageDesc&  SetArrayLayers (uint value) { arrayLayers = ImageLayer{ value };  return *this; }
			ImageDesc&  SetMaxMipmaps (uint value) { maxLevel = MipmapLevel{ value };  return *this; }
			ImageDesc&  SetSamples (uint value) { samples = MultiSamples{ value };  return *this; }
		};

		//
		// Image View Description
		//
		struct ImageViewDesc
		{
			// variables
			EImage				viewType = Default;
			EPixelFormat		format = Default;
			MipmapLevel			baseLevel;
			uint				levelCount = 1;
			ImageLayer			baseLayer;
			uint				layerCount = 1;
			ImageSwizzle		swizzle;
			EImageAspect		aspectMask = Default;

			// methods
			ImageViewDesc () {}

			ImageViewDesc (EImage			viewType,
				EPixelFormat		format,
				MipmapLevel		baseLevel = Default,
				uint				levelCount = 1,
				ImageLayer		baseLayer = Default,
				uint				layerCount = 1,
				ImageSwizzle		swizzle = Default,
				EImageAspect		aspectMask = Default);

			explicit ImageViewDesc (const ImageDesc &desc);

			void Validate (const ImageDesc &desc);

			ND_ bool operator == (const ImageViewDesc &rhs) const;

			ImageViewDesc&  SetViewType (EImage value) { viewType = value;  return *this; }
			ImageViewDesc&  SetFormat (EPixelFormat value) { format = value;  return *this; }
			ImageViewDesc&  SetBaseLevel (uint value) { baseLevel = MipmapLevel{ value };  return *this; }
			ImageViewDesc&  SetLevels (uint base, uint count) { baseLevel = MipmapLevel{ base };  levelCount = count;  return *this; }
			ImageViewDesc&  SetBaseLayer (uint value) { baseLayer = ImageLayer{ value };  return *this; }
			ImageViewDesc&  SetArrayLayers (uint base, uint count) { baseLayer = ImageLayer{ base };  layerCount = count;  return *this; }
			ImageViewDesc&  SetSwizzle (ImageSwizzle value) { swizzle = value;  return *this; }
			ImageViewDesc&  SetAspect (EImageAspect value) { aspectMask = value;  return *this; }
		};
	}
}


namespace std
{
	template <>
	struct hash< loo::vkfg::ImageDesc >
	{
		ND_ size_t  operator () (const loo::vkfg::ImageDesc &value) const
		{
#if LOO_FAST_HASH
			return size_t (loo::HashOf (AddressOf (value), sizeof (value)));
#else
			loo::HashVal	result;
			result << loo::HashOf (value.imageType);
			result << loo::HashOf (value.dimension);
			result << loo::HashOf (value.format);
			result << loo::HashOf (value.usage);
			result << loo::HashOf (value.maxLevel);
			result << loo::HashOf (value.samples);
			return size_t (result);
#endif
		}
	};


	template <>
	struct hash< loo::vkfg::ImageViewDesc >
	{
		ND_ size_t  operator () (const loo::vkfg::ImageViewDesc &value) const
		{
#ifdef LOO_FAST_HASH	
			struct ImageViewDesc
			{
				// variables
				EImage				viewType = Default;
				EPixelFormat		format = Default;
				MipmapLevel			baseLevel;
				uint				levelCount = 1;
				ImageLayer			baseLayer;
				uint				layerCount = 1;
				ImageSwizzle		swizzle;
				EImageAspect		aspectMask = Default;

				// methods
				ImageViewDesc () {}

				ImageViewDesc (EImage			viewType,
					EPixelFormat		format,
					MipmapLevel		baseLevel = Default,
					uint				levelCount = 1,
					ImageLayer		baseLayer = Default,
					uint				layerCount = 1,
					ImageSwizzle		swizzle = Default,
					EImageAspect		aspectMask = Default);

				explicit ImageViewDesc (const ImageDesc &desc);

				void Validate (const ImageDesc &desc);

				ND_ bool operator == (const ImageViewDesc &rhs) const;

				ImageViewDesc&  SetViewType (EImage value) { viewType = value;  return *this; }
				ImageViewDesc&  SetFormat (EPixelFormat value) { format = value;  return *this; }
				ImageViewDesc&  SetBaseLevel (uint value) { baseLevel = MipmapLevel{ value };  return *this; }
				ImageViewDesc&  SetLevels (uint base, uint count) { baseLevel = MipmapLevel{ base };  levelCount = count;  return *this; }
				ImageViewDesc&  SetBaseLayer (uint value) { baseLayer = ImageLayer{ value };  return *this; }
				ImageViewDesc&  SetArrayLayers (uint base, uint count) { baseLayer = ImageLayer{ base };  layerCount = count;  return *this; }
				ImageViewDesc&  SetSwizzle (ImageSwizzle value) { swizzle = value;  return *this; }
				ImageViewDesc&  SetAspect (EImageAspect value) { aspectMask = value;  return *this; }
			}; _FAST_HASH
				return size_t (loo::HashOf (AddressOf (value), sizeof (value)));
#else
			loo::HashVal	result;
			result << loo::HashOf (value.viewType);
			result << loo::HashOf (value.format);
			result << loo::HashOf (value.baseLevel);
			result << loo::HashOf (value.levelCount);
			result << loo::HashOf (value.baseLayer);
			result << loo::HashOf (value.layerCount);
			result << loo::HashOf (value.swizzle);
			return size_t (result);
#endif
		}
	};

}	// std

