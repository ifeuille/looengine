#include "global/extstd/barrier.h"
#include "global/extstd/memutils.h"

DECLARE_CPP_NOTHING(BARRIER)

#if (LOO_BARRIER_MODE == 0)

# include "stl/Platforms/WindowsHeader.h"

namespace loo
{

	/*
	=================================================
		ArraySizeOf
	=================================================
	*/
	Barrier::Barrier (uint numThreads)
	{
		auto*	barrier_ptr = PlacementNew<SYNCHRONIZATION_BARRIER> (_data);

		CHECK (InitializeSynchronizationBarrier (barrier_ptr, numThreads, -1));
	}

	/*
	=================================================
		ArraySizeOf
	=================================================
	*/
	Barrier::~Barrier ()
	{
		CHECK (DeleteSynchronizationBarrier (BitCast<SYNCHRONIZATION_BARRIER *> (&_data[0])));
	}

	/*
	=================================================
		wait
	=================================================
	*/
	void Barrier::wait ()
	{
		EnterSynchronizationBarrier (BitCast<SYNCHRONIZATION_BARRIER *> (&_data[0]), SYNCHRONIZATION_BARRIER_FLAGS_NO_DELETE);
	}

}	// LOOC
#endif	// LOO_BARRIER_MODE == 0
