#ifndef LE_CORE_MUTEX_H
#define LE_CORE_MUTEX_H
#include <mutex>
#include <shared_mutex>
#include "global/global.h"

namespace loo
{
	namespace global
	{
		typedef std::lock_guard<std::mutex> MutextShareLock;
		typedef std::lock_guard<std::shared_mutex> SharedMutextShareLock;

		typedef std::unique_lock<std::mutex> MutextUniqueLock;
		typedef std::unique_lock<std::shared_mutex> SharedMutextUniqueLock;
	
//#if defined(LOO_CXX17_LIBRARY_OPTIONAL_SUPPORT)
//		typedef std::scoped_lock<std::mutex> MutextScopedLock;
//		typedef std::scoped_lock<std::shared_mutex> SharedMutextScopedeLock;
//#else
//		typedef boost::mutex::scoped_lock<std::mutex> MutextScopedLock;
//		typedef boost::mutex::scoped_lock<std::shared_mutex> SharedMutextScopedeLock;
//#endif
	}
}
#endif