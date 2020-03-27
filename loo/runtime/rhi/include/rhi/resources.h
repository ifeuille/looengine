#ifndef LOO_RHI_RESOURCES_H
#define LOO_RHI_RESOURCES_H
#include "rhi/dllexporter.h"
#include "global/global.h"
#include "global/template/refcounting.h"
#include "elementformat.h"
#include "global/utils/threadsafecounter.h"
#include "global/extstd/readerwriterqueue.h"


#include "rhi/instance.h"
#include "rhi/physicaldevice.h"
#include "rhi/graphicdevice.h"
#include "rhi/queue.h"
#include "rhi/commandpool.h"
#include "rhi/commandbuffer.h"


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
				return  /*GIsRHIInitialized &&*/ false;
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



	}
}

#endif