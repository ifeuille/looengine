#ifndef LE_CORE_TIMER_HPP
#define LE_CORE_TIMER_HPP

namespace loo
{
	namespace global
	{
		class Timer
		{
		public:
			Timer(); // postcondition: elapsed()==0
			void restart(); // postcondition: elapsed()==0

			// return elapsed time in seconds
			double elapsed() const;

			// return estimated maximum value for elapsed()
			double elapsed_max() const;

			// return minimum value for elapsed()
			double elapsed_min() const;

			double current_time() const;

			uint64 getTimeInNanoseconds ()const;

		private:
			double start_time_;
		};
	}
}

#endif		// _KFL_TIMER_HPP
