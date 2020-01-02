
#ifndef LE_CORE_ARRAYREF_HPP
#define LE_CORE_ARRAYREF_HPP
#include "global/global.h"
#include "global/utlis.h"
#include <vector>
#include <assert.h>

namespace loo
{
	namespace global
	{
		// ArrayRef, inspired by LLVM's ArrayRef (http://llvm.org/docs/doxygen/html/ArrayRef_8h_source.html)
		//
		// ArrayRef - Represent a constant reference to an array (0 or more elements
		// consecutively in memory), i.e. a start pointer and a size.  It allows
		// various APIs to take consecutive elements easily and conveniently.
		//
		// This class does not own the underlying data, it is expected to be used in
		// situations where the data resides in some other buffer, whose lifetime
		// extends past that of the ArrayRef. For this reason, it is not in general
		// safe to store an ArrayRef.
		//
		// This is intended to be trivially copyable, so it should be passed by value.
		template <typename T>
		class ArrayRef
		{
		public:
			typedef T const * iterator;
			typedef T const * const_iterator;
			typedef size_t size_type;

			typedef std::reverse_iterator<iterator> reverse_iterator;

		public:
			constexpr ArrayRef ()
				: data_ (nullptr), size_ (0)
			{
			}

			ArrayRef (ArrayRef const & rhs)
				: data_ (rhs.data ()), size_ (rhs.size ())
			{
			}

			constexpr ArrayRef (T const & t)
				: data_ (&t), size_ (1)
			{
			}

			constexpr ArrayRef (T const * data, size_t size)
				: data_ (data), size_ (size)
			{
			}

			constexpr ArrayRef (T const * begin, T const * end)
				: data_ (begin), size_ (end - begin)
			{
			}

			template <typename A>
			constexpr ArrayRef (std::vector<T, A> const & v)
				: data_ (v.data ()), size_ (v.size ())
			{
			}

			template <size_t N>
			constexpr ArrayRef (T const (&arr)[N])
				: data_ (arr), size_ (N)
			{
			}

			constexpr ArrayRef (std::initializer_list<T> const & v)
				: data_ (v.begin () == v.end () ? nullptr : v.begin ()), size_ (v.size ())
			{
			}

			template <typename U>
			constexpr ArrayRef (ArrayRef<U*> const & rhs,
				typename std::enable_if<std::is_convertible<U* const *, T const *>::value>::type* = 0)
				: data_ (rhs.data ()), size_ (rhs.size ())
			{
			}

			template <typename U, typename A>
			constexpr ArrayRef (std::vector<U*, A> const & v,
				typename std::enable_if<std::is_convertible<U* const *, T const *>::value>::type* = 0)
				: data_ (v.data ()), size_ (v.size ())
			{
			}

			constexpr iterator begin () const
			{
				return data_;
			}
			constexpr iterator end () const
			{
				return data_ + size_;
			}

			constexpr reverse_iterator rbegin () const
			{
				return reverse_iterator (this->end ());
			}
			constexpr reverse_iterator rend () const
			{
				return reverse_iterator (this->begin ());
			}

			constexpr T const * data () const
			{
				return data_;
			}

			constexpr size_t size () const
			{
				return size_;
			}

			constexpr bool empty () const
			{
				return size_ == 0;
			}

			constexpr T const & front () const
			{
				BOOST_ASSERT (!this->empty ());
				return data_[0];
			}

			constexpr T const & back () const
			{
				BOOST_ASSERT (!this->empty ());
				return data_[size_ - 1];
			}

			template <typename Alloc>
			ArrayRef<T> Copy (Alloc& alloc)
			{
				T* buff = alloc.template allocate<T> (size_);
				std::uninitialized_copy (this->begin (), this->end (), buff);
				return ArrayRef<T> (buff, size_);
			}

			constexpr ArrayRef<T> Slice (uint32_t n) const
			{
				BOOST_ASSERT_MSG (n <= this->size (), "Invalid specifier");
				return ArrayRef<T> (this->data () + n, this->size () - n);
			}

			constexpr ArrayRef<T> Slice (uint32_t n, uint32_t m) const
			{
				ASSERT_MSG (n + m <= this->size (), "Invalid specifier");
				return ArrayRef<T> (this->data () + n, m);
			}

			constexpr ArrayRef<T> DropBack (uint32_t n = 1) const
			{
				ASSERT_MSG (this->size () >= n, "Dropping more elements than exist");
				return this->Slice (0, this->Size () - n);
			}

			constexpr T const & operator[](size_t index) const
			{
				ASSERT_MSG (index < size_, "Invalid index!");
				return data_[index];
			}

			constexpr std::vector<T> ToVector () const
			{
				return std::vector<T> (data_, data_ + size_);
			}

		private:
			T const * data_;
			size_type size_;
		};

		template <typename T>
		inline bool operator==(ArrayRef<T> lhs, ArrayRef<T> rhs)
		{
			if (lhs.size () != rhs.size ())
			{
				return false;
			}
			return std::equal (lhs.begin (), lhs.end (), rhs.begin ());
		}

		template <typename T>
		inline bool operator!=(ArrayRef<T> lhs, ArrayRef<T> rhs)
		{
			return !(lhs == rhs);
		}

		template <typename T>
		ArrayRef<T> MakeArrayRef (T const & t)
		{
			return ArrayRef<T> (t);
		}

		template <typename T>
		ArrayRef<T> MakeArrayRef (T const * data, size_t size)
		{
			return ArrayRef<T> (data, size);
		}

		template <typename T>
		ArrayRef<T> MakeArrayRef (T const * begin, T const * end)
		{
			return ArrayRef<T> (begin, end);
		}

		template <typename T, typename A>
		ArrayRef<T> MakeArrayRef (std::vector<T, A> const & v)
		{
			return ArrayRef<T> (v);
		}

		template <typename T, size_t N>
		ArrayRef<T> MakeArrayRef (T const (&arr)[N])
		{
			return ArrayRef<T> (arr);
		}

		template <typename T>
		ArrayRef<T> MakeArrayRef (std::initializer_list<T> const & v)
		{
			return ArrayRef<T> (v);
		}
	}
}

#endif		// LE_CORE_ARRAYREF_HPP
