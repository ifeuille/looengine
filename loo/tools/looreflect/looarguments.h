#ifndef LOO_ARGUMENTS_H
#define LOO_ARGUMENTS_H
#include "stringlist.h"
namespace loo {
	class LooArguments {
	public:
		void Init (int argc, char** argv) {
			
			for (int i = 0; i < argc; ++i) {
				Arguments.push_back (argv[i]);
			}

		}
		LooStringList& arguments () {
			return Arguments;
		}
	private:
		LooStringList Arguments;
	};
	extern LooArguments g_LooArguments;
}

#endif