

#pragma once

#include "global/global.h"
#include <mutex>	// for lock_guard

namespace loo
{

	//
	// Dummy Lock
	//

	struct DummyLock
	{
		void lock () {}
		void unlock () {}
	};



	//
	// Dummy Shared Lock
	//

	struct DummySharedLock
	{
		void lock () {}
		void unlock () {}

		void lock_shared () {}
		void unlock_shared () {}
	};


}	// loo
