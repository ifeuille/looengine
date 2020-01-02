#include "Math/Core.Random.h"
#include "HAL/Core.Mutex.h"

namespace le
{
	namespace core
	{
		std::mutex singleton_mutex_fast1;
		std::mutex singleton_mutex_fast2;
		std::mutex singleton_mutex_stable;
	}
}

#define MAX_RAND_UINT32 4294967296;

namespace le
{
	namespace core
	{
		//fast,but not stable
		unsigned long  Random::Xorshf96 ( )
		{
			le::core::MutextUniqueLock lock ( singleton_mutex_fast1 );
			static unsigned long x96_x = 123456789, x96_y = 362436069, x96_z = 521288629;
			//period 2^96-1
			unsigned long t;
			x96_x ^= x96_x << 16;
			x96_x ^= x96_x >> 5;
			x96_x ^= x96_x << 1;

			t = x96_x;
			x96_x = x96_y;
			x96_y = x96_z;
			x96_z = t ^ x96_x ^ x96_y;

			return x96_z;
		}

		//T= 2^128-1
		unsigned int  Random::Xorshift128 ( )
		{		
			le::core::MutextUniqueLock lock ( singleton_mutex_fast2 );
			static unsigned int x128_x = 123456789, x128_y = 362436069, x128_z = 521288629, x128_w = 932288624;
			//static Random* m_RanderInstance;

			uint32_t t = x128_x ^ (x128_x << 11);
			x128_x = x128_y; x128_y = x128_z; x128_z = x128_w;
			return x128_w = x128_w ^ (x128_w >> 19) ^ t ^ (t >> 8);
		}
		
		unsigned int Random::RandStable ( )
		{
			le::core::MutextUniqueLock lock ( singleton_mutex_stable );
			static bool inited = false;
			static std::random_device rd;
			static std::mt19937 mt;
			if (!inited)
			{
				inited = true;
				mt.seed ( rd ( ) );
			}
			return mt ( );
		}

		unsigned int Random::RandFast ( )
		{
#ifdef USE_XORSHFT128
			return Xorshift128 ( );
#else
			return rand ( );
#endif
		}

		int Random::RandInt ( EnumRanderType ert, int from, int to )
		{
			if (ert == ERT_FAST)
				return RandFast ( ) % (to - from + 1) + from;

			return RandStable ( ) % (to - from + 1) + from;

		}

		int Random::RandIntFast ( int from, int to )
		{
			return RandFast ( ) % (to - from + 1) + from;
		}

		int Random::RandIntStable ( int from, int to )
		{
			return RandStable ( ) % (to - from + 1) + from;
		}

		double Random::RandDoubleZTO ( EnumRanderType ert )
		{
			if (ert == ERT_FAST)
				return (double)RandFast ( ) / (double)MAX_RAND_UINT32;

			return (double)RandStable ( ) / (double)MAX_RAND_UINT32;
		}

		double Random::RandDoubleZTOFast ( )
		{
			return (double)RandFast ( ) / (double)MAX_RAND_UINT32;
		}

		double Random::RandDoubleZTOStable ( )
		{
			return (double)RandStable ( ) / (double)MAX_RAND_UINT32;
		}
	}
}