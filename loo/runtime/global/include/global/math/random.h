#ifndef LE_CORE_RANDOM_H
#define LE_CORE_RANDOM_H
#include "global/math/math.h"
#include <cmath>
#include <random>


namespace loo
{
	namespace math
	{

		//random 
		//using glm::ballRand;
		//using glm::circularRand;
		//using glm::diskRand;
		//using glm::gaussRand;
		//using glm::linearRand;
		//using glm::sphericalRand;


		///** Returns a random integer between 0 and RAND_MAX, inclusive */
		//static LOO_FORCEINLINE int32 Rand ( ) { return rand ( ); }

		///** Seeds global random number functions Rand() and FRand() */
		//static LOO_FORCEINLINE void RandInit ( int32 Seed ) { srand ( Seed ); }

		///** Returns a random float between 0 and 1, inclusive. */
		//static LOO_FORCEINLINE float FRand ( ) { return Rand ( ) / (float)RAND_MAX; }

		enum EnumRanderType
		{
			ERT_FAST = 0,
			ERT_STABLE = 1,
		};

		class Random
		{
		private:

			//fast,but not stable
			static unsigned long Xorshf96 ( );
			//T= 2^128-1
			static unsigned int Xorshift128 ( );
		public:
			/** Seeds global random number functions Rand() and FRand() */
			static LOO_FORCEINLINE  void RandInit ( int32 Seed ) { srand ( Seed ); }
			/** Returns a random integer between 0 and RAND_MAX, inclusive */
			static LOO_FORCEINLINE int32 Rand ( ) { return rand ( ); }
			/** Returns a random float between 0 and 1, inclusive. */
			static LOO_FORCEINLINE float FRand ( ) { return Rand ( ) / (float)RAND_MAX; }

			static unsigned int RandStable ( );

			static unsigned int RandFast ( );

			//rand  int[from,to]
			static int RandInt ( EnumRanderType ert, int from, int to );

			static int RandIntFast ( int from, int to );

			static int RandIntStable ( int from, int to );

			//[0,1]
			static double RandDoubleZTO ( EnumRanderType ert );

			static double RandDoubleZTOFast ( );

			static double RandDoubleZTOStable ( );



		};


	}
}
#endif