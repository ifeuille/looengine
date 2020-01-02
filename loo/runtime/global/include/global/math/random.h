#ifndef LE_CORE_RANDOM_H
#define LE_CORE_RANDOM_H
#include "Core.DllExport.h"
#include "Core.Types.h"
#include "Math/Core.Math.h"
#include <cmath>
#include <random>


namespace le
{
	namespace core
	{

		//random 
		using glm::ballRand;
		using glm::circularRand;
		using glm::diskRand;
		using glm::gaussRand;
		using glm::linearRand;
		using glm::sphericalRand;


		///** Returns a random integer between 0 and RAND_MAX, inclusive */
		//static LE_FORCEINLINE int32 Rand ( ) { return rand ( ); }

		///** Seeds global random number functions Rand() and FRand() */
		//static LE_FORCEINLINE void RandInit ( int32 Seed ) { srand ( Seed ); }

		///** Returns a random float between 0 and 1, inclusive. */
		//static LE_FORCEINLINE float FRand ( ) { return Rand ( ) / (float)RAND_MAX; }

		enum EnumRanderType
		{
			ERT_FAST = 0,
			ERT_STABLE = 1,
		};

		class CORE_EXPORT Random
		{
		private:

			//fast,but not stable
			static unsigned long Xorshf96 ( );
			//T= 2^128-1
			static unsigned int Xorshift128 ( );
		public:
			/** Seeds global random number functions Rand() and FRand() */
			static LE_FORCEINLINE  void RandInit ( int32 Seed ) { srand ( Seed ); }
			/** Returns a random integer between 0 and RAND_MAX, inclusive */
			static LE_FORCEINLINE int32 Rand ( ) { return rand ( ); }
			/** Returns a random float between 0 and 1, inclusive. */
			static LE_FORCEINLINE float FRand ( ) { return Rand ( ) / (float)RAND_MAX; }

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