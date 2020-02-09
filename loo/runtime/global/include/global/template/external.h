#ifndef LE_CORE_EXTERNAL_H
#define LE_CORE_EXTERNAL_H

#include "global/template/externalstring.h"
#include "global/utlis.h"

template <typename T, typename Allocator> void* operator new(std::size_t Size, std::vector<T, Allocator>& Array)
{
	//assert(Size == (std::size_t) sizeof(T));
	LOO_ASSERT (Size == (std::size_t) sizeof (T), "");
	const std::size_t Index = Array.size ();
	Array.resize (Index + 1);
	//const int32 Index = Array.AddUninitialized (1);
	return &Array[Index];
}
template <typename T, typename Allocator> void operator delete(void* ptr, std::vector<T, Allocator>& Array)
{
	LOO_ASSERT (false, "operator delete");
	LOO_UNUSED (Array);
	LOO_UNUSED (ptr);
}
template <typename T, typename Allocator> void* operator new(size_t Size, std::vector<T, Allocator>& Array, loo::int32 Index)
{
	LOO_ASSERT (Size == (std::size_t) sizeof (T), "");
	Array.InsertUninitialized (Index, 1);
	return &Array[Index];
}

template <typename T, typename Allocator> void operator delete(void* ptr, std::vector<T, Allocator>& Array, loo::int32 Index)
{
	Array.erase (Index);
	ptr = nullptr;
}

#ifdef __clang__
template <typename T>
auto ArrayCountHelper (T& t) -> typename std::enable_if<__is_array (T), char (&)[sizeof (t) / sizeof (t[0]) + 1]>::type;
#else
template <typename T, loo::uint32 N>
char (&ArrayCountHelper (const T (&)[N]))[N + 1];
#endif

// Number of elements in an array.
#define ARRAY_COUNT( array ) (sizeof(ArrayCountHelper(array)) - 1)

namespace loo
{
	namespace global
	{

		/*template <typename T, typename Allocator> void* operator new(size_t Size, std::vector<T, Allocator>& Array, le::core::int32 Index)
		{
			LE_ASSERT ((Count >= 0) & (Index >= 0) & (Index <= ArrayNum),"");
			const int32 OldNum = ArrayNum;
			if ((ArrayNum += Count) > ArrayMax)
			{
				ResizeGrow (OldNum);
			}
			ElementType* Data = GetData () + Index;
			RelocateConstructItems<ElementType> (Data + Count, Data, OldNum - Index);
		}*/
	}
}


#endif