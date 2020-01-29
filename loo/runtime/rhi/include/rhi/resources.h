#ifndef LOO_RHI_RESOURCES_H
#define LOO_RHI_RESOURCES_H
#include "rhi/dllexporter.h"
#include "global/global.h"
#include "global/template/refcounting.h"
#include "elementformat.h"
#include "global/utils/threadsafecounter.h"
#include "global/extstd/readerwriterqueue.h"
#include "rhi/graphicdevice.h"
#include "rhi/rhi.h"

namespace loo
{
	namespace rhi
	{
#define DISABLE_RHI_DEFFERED_DELETE
		//declare
		class RHIViewport;

		class RHI_EXPORT RHIResource
		{
		public:
			RHIResource (bool InbDoNotDeferDelete = false)
			{

			}
			~RHIResource ()
			{


			}

			inline uint32 AddRef ()const
			{
				int32 newValue = NumRefs.Increment ();
				assert (newValue > 0);
				return uint32 (newValue);
			}

			inline uint32 Release ()const
			{
				int32 newValue = NumRefs.Decrement ();
				if (newValue == 0)
				{
					if (!DeferDelete ())
					{
						delete this;
					}
					else
					{
						if (MarkedForDelete == 1)
						{
							PendingDelets.enqueue (this);
						}
					}
				}
				assert (newValue >= 0);
				return uint32 (newValue);
			}

			inline uint32 GetRefCount ()const
			{
				int currentValue = NumRefs.GetValue ();
				assert (currentValue >= 0);
				return uint32 (currentValue);
			}

			void DoNoDeferDelete ()
			{
				assert (!MarkedForDelete);
				bDoNotDeferDelete = true;

			}

			static void FlushPendingDeletes ();

			inline static bool PlatformNeedExtraDeletionLatency ()
			{
				return  GIsRHIInitialized && false;
			}

			static bool Bypass ();

			// Transient resource tracking
			// We do this at a high level so we can catch errors even when transient resources are not supported
			void SetCommitted (bool bInCommitted)
			{
				//check(IsInRenderingThread());
				bCommitted = bInCommitted;
			}
			bool IsCommitted ()const
			{
				//check(IsInRenderingThread());
				return bCommitted;
			}
					   
		private:
			mutable loo::global::ThreadSafeCounter<int> NumRefs;
			mutable int32 MarkedForDelete;
			bool bDoNotDeferDelete;
			bool bCommitted;

			static moodycamel::ReaderWriterQueue<RHIResource, PLATFORM_CACHE_LINE_SIZE> PendingDelets;
			static RHIResource* CurrentDeleting;

			inline bool DeferDelete ()const
			{
#ifdef DISABLE_RHI_DEFFERED_DELETE
				return false;
#else
				return !bDoNotDeferDelete && (!Bypass ());
#endif
			}

			// Some APIs don't do internal reference counting, so we have to wait an extra couple of frames before deleting resources
			// to ensure the GPU has completely finished with them. This avoids expensive fences, etc.
			struct ResourcesToDelete
			{
				ResourcesToDelete (uint32 InFrameDelete = 0)
					:FrameDeleted (InFrameDelete)
				{

				}
				std::vector<RHIResource*> Resources;
				uint32 FrameDeleted;
			};
			static std::vector<ResourcesToDelete> DeferredDeletionQueue;
			static uint32 CurrentFrame;
		};


		class RHI_EXPORT RHICustomPresent : public RHIResource
		{
		public:
			explicit RHICustomPresent (RHIViewport* InViewport) :viewPort (InViewport) {}
			virtual ~RHICustomPresent () {};
			// Called when viewport is resized.
			virtual void OnBackBufferResize () = 0;

			// Called from render thread to see if a native present will be requested for this frame.
			// @return	true if native Present will be requested for this frame; false otherwise.  Must
			// match value subsequently returned by Present for this frame.
			virtual bool NeedsNativePresent () = 0;

			// Called from RHI thread to perform custom present.
			// @param InOutSyncInterval - in out param, indicates if vsync is on (>0) or off (==0).
			// @return	true if native Present should be also be performed; false otherwise. If it returns
			// true, then InOutSyncInterval could be modified to switch between VSync/NoVSync for the normal 
			// Present.  Must match value previously returned by NeedsNormalPresent for this frame.
			virtual bool Present (int32& InOutSyncInterval) = 0;

			// Called from RHI thread after native Present has been called
			virtual void PostPresent () {};

			// Called when rendering thread is acquired
			virtual void OnAcquireThreadOwnership () {}
			// Called when rendering thread is released
			virtual void OnReleaseThreadOwnership () {}
		private:
			RHIViewport* viewPort;
		};
		
		class RHI_EXPORT RHIViewport : public RHIResource
		{
		public:
			/**
			 * Returns access to the platform-specific native resource pointer.  This is designed to be used to provide plugins with access
			 * to the underlying resource and should be used very carefully or not at all.
			 *
			 * @return	The pointer to the native resource or NULL if it not initialized or not supported for this resource type for some reason
			 */
			virtual void* GetNativeSwapChain () const { return nullptr; }
			/**
			 * Returns access to the platform-specific native resource pointer to a backbuffer texture.  This is designed to be used to provide plugins with access
			 * to the underlying resource and should be used very carefully or not at all.
			 *
			 * @return	The pointer to the native resource or NULL if it not initialized or not supported for this resource type for some reason
			 */
			virtual void* GetNativeBackBufferTexture () const { return nullptr; }
			/**
			 * Returns access to the platform-specific native resource pointer to a backbuffer rendertarget. This is designed to be used to provide plugins with access
			 * to the underlying resource and should be used very carefully or not at all.
			 *
			 * @return	The pointer to the native resource or NULL if it not initialized or not supported for this resource type for some reason
			 */
			virtual void* GetNativeBackBufferRT () const { return nullptr; }

			/**
			 * Returns access to the platform-specific native window. This is designed to be used to provide plugins with access
			 * to the underlying resource and should be used very carefully or not at all.
			 *
			 * @return	The pointer to the native resource or NULL if it not initialized or not supported for this resource type for some reason.
			 * AddParam could represent any additional platform-specific data (could be null).
			 */
			virtual void* GetNativeWindow (void** AddParam = nullptr) const { return nullptr; }

			/**
			 * Sets custom Present handler on the viewport
			 */
			virtual void SetCustomPresent (class RHICustomPresent*) {}

			/**
			 * Returns currently set custom present handler.
			 */
			virtual class RHICustomPresent* GetCustomPresent () const { return nullptr; }

		};


		typedef RHIViewport* RHIViewportParamRef;
		typedef loo::global::TRefCountPtr<RHIViewport> RHIViewportRef;

		typedef loo::global::TRefCountPtr<RHICustomPresent> CustomPresentRHIRef;

	}
}

#endif