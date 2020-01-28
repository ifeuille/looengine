#include "global/global.h"
#include <limits>
#include <chrono>
#include "global/time.h"
#include <time.h>
#include <assert.h>
#if defined(_WIN32)

#include <windows.h>

#elif defined(__unix__) || defined(__linux) || defined(__linux__) || defined(__ANDROID__) || defined(__EPOC32__) || defined(__QNX__)

#include <time.h>

#elif defined(__APPLE__)

#include <sys/time.h>

#endif

namespace loo
{
	namespace global
	{
		Timer::Timer()
		{
			this->restart();
		} // postcondition: elapsed()==0

		void Timer::restart()
		{
			start_time_ = this->current_time();
		} // postcondition: elapsed()==0

		// return elapsed time in seconds
		double Timer::elapsed() const
		{
			return this->current_time() - start_time_;
		}

		// return estimated maximum value for elapsed()
		double Timer::elapsed_max() const
		{
			return std::chrono::duration<double>::max().count();
		}

		// return minimum value for elapsed()
		double Timer::elapsed_min() const
		{
			return std::chrono::duration<double>::min().count();
		}

		double Timer::current_time() const
		{
			std::chrono::high_resolution_clock::time_point const tp = std::chrono::high_resolution_clock::now();
			return std::chrono::duration_cast<std::chrono::duration<double>>(tp.time_since_epoch()).count();
		}
		uint64 Timer::getTimeInNanoseconds () const
		{
#if defined(_WIN32)
			LARGE_INTEGER freq;
			LARGE_INTEGER count;
			QueryPerformanceCounter (&count);
			QueryPerformanceFrequency (&freq);
			assert (freq.LowPart != 0 || freq.HighPart != 0);

			if (count.QuadPart < MAXLONGLONG / 1000000) {
				assert (freq.QuadPart != 0);
				return count.QuadPart * 1000000 / freq.QuadPart;
			}
			else {
				assert (freq.QuadPart >= 1000000);
				return count.QuadPart / (freq.QuadPart / 1000000);
			}

#elif defined(__unix__) || defined(__linux) || defined(__linux__) || defined(__ANDROID__) || defined(__QNX__)
			struct timespec currTime;
			clock_gettime (CLOCK_MONOTONIC, &currTime);
			return (uint64_t)currTime.tv_sec * 1000000 + ((uint64_t)currTime.tv_nsec / 1000);

#elif defined(__EPOC32__)
			struct timespec currTime;
			/* Symbian supports only realtime clock for clock_gettime. */
			clock_gettime (CLOCK_REALTIME, &currTime);
			return (uint64_t)currTime.tv_sec * 1000000 + ((uint64_t)currTime.tv_nsec / 1000);

#elif defined(__APPLE__)
			struct timeval currTime;
			gettimeofday (&currTime, NULL);
			return (uint64_t)currTime.tv_sec * 1000000 + (uint64_t)currTime.tv_usec;

#else
#error "Not implemented for target OS"
#endif
		}
	}
}
