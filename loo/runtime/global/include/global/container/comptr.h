
#ifndef LE_CORE_COMPTR_HPP
#define LE_CORE_COMPTR_HPP

#include "global/utlis.h"

namespace loo
{
	namespace global
	{
		// 得到COM对象的智能指针
		template <typename T>
		inline std::shared_ptr<T>
			MakeCOMPtr (T* p)
		{
			return p ? std::shared_ptr<T> (p, std::mem_fn (&T::Release)) : std::shared_ptr<T> ();
		}
	}
}

#endif		// _KFL_COMPTR_HPP
