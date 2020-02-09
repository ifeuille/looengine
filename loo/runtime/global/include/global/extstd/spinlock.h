

#pragma once
#include "global/global.h"
#include <atomic>
#include <mutex>
#include <thread>

namespace loo
{

	//
	// Spin Lock
	//

	struct SpinLock
	{
		// variables
	private:
		alignas(LOO_CACHE_LINE) std::atomic<uint>	_flag{ 0 };


		// methods
	public:
		SpinLock ()
		{}

		ND_ LOO_FORCEINLINE bool  try_lock ()
		{
			uint	exp = 0;
			return _flag.compare_exchange_strong ( exp, 1, std::memory_order_acquire, std::memory_order_relaxed);
		}


		// for std::lock_guard
		LOO_FORCEINLINE void  lock ()
		{
			uint	exp = 0;
			for (uint i = 0; not _flag.compare_exchange_weak ( exp, 1, std::memory_order_acquire, std::memory_order_relaxed); ++i)
			{
				if (i > 100) {
					i = 0;
					std::this_thread::yield ();
				}
				exp = 0;
			}
		}

		LOO_FORCEINLINE void  unlock ()
		{
#ifdef LOO_DEBUG
			uint	exp = 1;
			ASSERT (_flag.compare_exchange_strong ( exp, 0, std::memory_order_release, std::memory_order_relaxed));
#else
			_flag.store (0, memory_order_release);
#endif
		}
	};


}	// loo
