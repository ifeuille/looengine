#include "rhi/resources.h"


void loo::rhi::RHIResource::FlushPendingDeletes ()
{
	//check render thread
	auto Delete = [](std::vector<RHIResource*>& ToDelete)
	{
		for (size_t Index = 0; Index < ToDelete.size (); ++Index)
		{
			RHIResource* Ref = ToDelete[Index];
			assert (Ref->MarkedForDelete == 1);
			if (Ref->GetRefCount () == 0)// caches can bring dead objects back to life
			{
				CurrentDeleting = Ref;
				delete Ref;
				CurrentDeleting = nullptr;
			}
			else
			{
				Ref->MarkedForDelete = 0;
				//FPlatformMisc::MemoryBarrier();
			}
		}
	};

	while (1)
	{
		if (PendingDelets.size_approx () == 0)
		{
			break;
		}
		if (PlatformNeedExtraDeletionLatency ())
		{
			const int32 Index = DeferredDeletionQueue.size ();
			DeferredDeletionQueue.push_back (ResourcesToDelete ());
			ResourcesToDelete& ResourceBatch = DeferredDeletionQueue[Index];
			ResourceBatch.FrameDeleted = CurrentFrame;
			PendingDelets.pop_all (ResourceBatch.Resources);
			assert (ResourceBatch.Resources.size () > 0);
		}
		else
		{
			std::vector<RHIResource*> ToDelete;
			PendingDelets.pop_all (ToDelete);
			assert (ToDelete.size () > 0);
			Delete (ToDelete);
		}
	}
}

bool loo::rhi::RHIResource::Bypass ()
{
	return false;
	//return GRHICommandList.Bypass();
}
