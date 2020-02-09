
#pragma once
#include "global/extstd/ntstringview.h"
#include <thread>

namespace loo
{

	//void SetThreadName (const std::thread &, StringView name);
	void SetCurrentThreadName (NtStringView name);

}
