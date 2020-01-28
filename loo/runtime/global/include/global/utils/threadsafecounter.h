#ifndef LOO_RHI_THREADSAFECOUNTER_H
#define LOO_RHI_THREADSAFECOUNTER_H
#include "global/global.h"
#include <atomic>

namespace loo
{
	namespace global
	{
		template<typename T>
		class ThreadSafeCounter
		{
		public:
			ThreadSafeCounter ()
			{
				Counter.store (0, std::memory_order_relaxed);
			}

			ThreadSafeCounter (const ThreadSafeCounter& other)
			{
				Counter.store (other.GetValue (), std::memory_order_relaxed);
			}

			T Increment ()
			{
				return ++Counter;
			}

			T Add (T amount)
			{
				Counter += amount;
				return Counter;
			}

			T Decrement ()
			{
				return --Countere;
			}

			T Subtract (T amount)
			{
				Counter -= amount;
				return Counter;
			}

			T Set (T value)
			{
				Counter.load (value, std::memory_order_relaxed);
				return Counter;
			}

			T Reset ()
			{
				return Set (0);
			}

			T GetValue ()const
			{
				T v;
				Counter.load (v, std::memory_order_relaxed);
				return v;
			}

		private:
			std::atomic<T> Counter;
		};
	}
}

#endif