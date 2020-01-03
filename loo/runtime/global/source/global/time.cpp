#include "global/global.h"
#include <limits>
#include <chrono>
#include "global/time.h"

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
	}
}
