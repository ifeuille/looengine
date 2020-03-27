
#pragma once

#include "vkfg/vulkan/image/vimage.h"
#include "vkfg/fg/enums.h"
#include "vkfg/fg/imagedatarange.h"


namespace loo
{
	namespace vkfg
	{

		//
		// Vulkan Image thread local
		//

		class VLocalImage final
		{
			friend class VImageUnitTest;

			// types
		public:
			using ImageRange = ImageDataRange;

			struct ImageState
			{
				// variables
				EResourceState		state = Default;
				VkImageLayout		layout = VK_IMAGE_LAYOUT_MAX_ENUM;
				VkImageAspectFlags	aspect = 0;
				ImageRange			range;
				VTask				task;

				// methods
				ImageState () {}

				ImageState (EResourceState state, VkImageLayout layout, const ImageRange &range, VkImageAspectFlags aspect, VTask task) :
					state{ state }, layout{ layout }, aspect{ aspect }, range{ range }, task{ task } {}
			};

		private:
			using SubRange = ImageRange::SubRange_t;

			struct ImageAccess
			{
				// variables
				SubRange				range;
				VkImageLayout			layout = VK_IMAGE_LAYOUT_MAX_ENUM;
				VkPipelineStageFlags	stages = 0;
				VkAccessFlags			access = 0;
				ExeOrderIndex			index = ExeOrderIndex::Initial;
				bool					isReadable : 1;
				bool					isWritable : 1;
				bool					invalidateBefore : 1;
				bool					invalidateAfter : 1;

				// methods
				ImageAccess () : isReadable{ false }, isWritable{ false }, invalidateBefore{ false }, invalidateAfter{ false } {}
			};

			using ImageViewMap_t = VImage::ImageViewMap_t;
			using AccessRecords_t = Array< ImageAccess >;		// TODO: fixed size array or custom allocator
			using AccessIter_t = AccessRecords_t::iterator;


			// variables
		private:
			Ptr<VImage const>			_imageData;		// readonly access is thread safe
			VkImageLayout				_finalLayout = VK_IMAGE_LAYOUT_GENERAL;

			mutable AccessRecords_t		_pendingAccesses;
			mutable AccessRecords_t		_accessForReadWrite;
			mutable bool				_isImmutable = false;


			// methods
		public:
			VLocalImage () {}
			VLocalImage (VLocalImage &&) = delete;
			~VLocalImage ();

			bool Create (const VImage *);
			void Destroy ();

			void SetInitialState (bool immutable, bool invalidate) const;
			void AddPendingState (const ImageState &) const;
			void ResetState (ExeOrderIndex index, VBarrierManager &barrierMngr, Ptr<VLocalDebugger> debugger) const;
			void CommitBarrier (VBarrierManager &barrierMngr, Ptr<VLocalDebugger> debugger) const;

			ND_ VkImageView			GetView (const VDevice &dev, bool isDefault, INOUT ImageViewDesc &desc) const { return _imageData->GetView (dev, isDefault, INOUT desc); }

			ND_ bool				IsCreated ()		const { return _imageData != null; }
			ND_ VkImage				Handle ()			const { return _imageData->Handle (); }
			ND_ VImage const*		ToGlobal ()			const { return _imageData.get (); }

			ND_ ImageDesc const&	Description ()		const { return _imageData->Description (); }
			ND_ VkImageAspectFlags	AspectMask ()		const { return _imageData->AspectMask (); }
			ND_ loo::math::uint3 const&		Dimension ()		const { return Description ().dimension; }
			ND_ uint const			Width ()			const { return Description ().dimension.x; }
			ND_ uint const			Height ()			const { return Description ().dimension.y; }
			ND_ uint const			Depth ()			const { return Description ().dimension.z; }
			ND_ uint const			ArrayLayers ()		const { return Description ().arrayLayers.Get (); }
			ND_ uint const			MipmapLevels ()		const { return Description ().maxLevel.Get (); }
			ND_ EPixelFormat		PixelFormat ()		const { return Description ().format; }
			ND_ EImage				ImageType ()		const { return Description ().imageType; }
			ND_ uint const			Samples ()			const { return Description ().samples.Get (); }

			ND_ StringView			GetDebugName ()		const { return _imageData->GetDebugName (); }


		private:
			bool _CreateView (const VDevice &, const HashedImageViewDesc &, OUT VkImageView &) const;

			ND_ static AccessIter_t	_FindFirstAccess (AccessRecords_t &arr, const SubRange &range);
			static void			_ReplaceAccessRecords (INOUT AccessRecords_t &arr, AccessIter_t iter, const ImageAccess &barrier);

		};


	}
}