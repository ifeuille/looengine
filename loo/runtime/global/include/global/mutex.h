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

		/*typedef std::unique_lock< RWDataRaceCheck> EXLOCK_RWDataRaceCheck;
		typedef std::unique_lock< RWDataRaceCheck> SHAREDLOCK_RWDataRaceCheck;*/

//#if defined(LOO_CXX17_LIBRARY_OPTIONAL_SUPPORT)
//		typedef std::scoped_lock<std::mutex> MutextScopedLock;
//		typedef std::scoped_lock<std::shared_mutex> SharedMutextScopedeLock;
//#else
//		typedef boost::mutex::scoped_lock<std::mutex> MutextScopedLock;
//		typedef boost::mutex::scoped_lock<std::shared_mutex> SharedMutextScopedeLock;
//#endif
	}
}


#ifndef EXLOCK
#	define EXLOCK(T, _syncObj_ ) \
		std::unique_lock<T>	LOO_PRIVATE_UNITE_RAW( __scopeLock, __COUNTER__ ) ( _syncObj_ )
#endif

// shared lock
#ifndef SHAREDLOCK
#	define SHAREDLOCK(T, _syncObj_ ) \
		std::shared_lock<T>	LOO_PRIVATE_UNITE_RAW( __sharedLock, __COUNTER__ ) ( _syncObj_ )
#endif



#endif