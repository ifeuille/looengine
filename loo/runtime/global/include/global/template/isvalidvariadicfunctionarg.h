#ifndef LOO_GLOBAL_ISVALIDVARIADICFUNCTIONARG_H
#define LOO_GLOBAL_ISVALIDVARIADICFUNCTIONARG_H
#include "global/global.h"

namespace loo
{
	namespace global
	{

		/**
		* Tests if a type is a valid argument to a variadic function, e.g. printf.
		*/
		template <typename T>
		struct TIsValidVariadicFunctionArg
		{
		private:
			static uint32_t Tester (uint32_t) { return 0; }
			static uint32_t Tester (uint8_t) { return 0; }
			static uint32_t Tester (int32_t) { return 0; }
			static uint32_t Tester (uint64_t) { return 0; }
			static uint32_t Tester (int64_t) { return 0; }
			static uint32_t Tester (double) { return 0; }
			static uint32_t Tester (long) { return 0; }
			static uint32_t Tester (unsigned long) { return 0; }
			static uint32_t Tester (loo::WIDECHAR) { return 0; }
			static uint32_t Tester (bool) { return 0; }
			static uint32_t Tester (const void*) { return 0; }
			static uint8_t  Tester (...) { return 0; }

			static T DeclValT () { return T; }

		public:
			//编译器类型推导
			enum { Value = sizeof (Tester (DeclValT ())) == sizeof (uint32_t) };
		};

	}

}

#endif