#ifndef LOO_CORE_MATH_RECT_H
#define LOO_CORE_MATH_RECT_H
#include "global/global.h"
#include "global/math/vec.h"
#include "global/math/rect.h"

namespace loo
{
	namespace math
	{
		template <typename T>
		struct Rectangle
		{
			// types
			using Vec2_t = loo::math::Vec<T, 2>;
			using Self = loo::math::Rectangle<T>;


			// variables
			T	left, top;
			T	right, bottom;


			// methods
			constexpr Rectangle () :
				left{ T (0) }, top{ T (0) }, right{ T (0) }, bottom{ T (0) }
			{
				// check is supported cast Rectangle to array
				STATIC_ASSERT (offsetof (Self, left) + sizeof (T) == offsetof (Self, top), "");
				STATIC_ASSERT (offsetof (Self, top) + sizeof (T) == offsetof (Self, right), "");
				STATIC_ASSERT (offsetof (Self, right) + sizeof (T) == offsetof (Self, bottom), "");
				STATIC_ASSERT (sizeof (T[3]) == (offsetof (Self, bottom) - offsetof (Self, left)), "");
			}

			constexpr Rectangle (T left, T top, T right, T bottom) :
				left{ left }, top{ top }, right{ right }, bottom{ bottom } {}

			constexpr Rectangle (const Vec2_t &leftTop, const Vec2_t &rightBottom) :
				left{ leftTop.x }, top{ leftTop.y }, right{ rightBottom.x }, bottom{ rightBottom.y } {}

			constexpr explicit Rectangle (const Vec2_t &size) :
				Rectangle{ Vec2_t{}, size } {}

			constexpr Rectangle (const Self &other) :
				left{ other.left }, top{ other.top }, right{ other.right }, bottom{ other.bottom } {}

			template <typename B>
			constexpr explicit Rectangle (const Rectangle<B> &other) :
				left{ T (other.left) }, top{ T (other.top) }, right{ T (other.right) }, bottom{ T (other.bottom) } {}

			Self& LeftTop (const Vec2_t& v);
			Self& RightBottom (const Vec2_t& v);

			ND_ constexpr const T		Width ()		const { return right - left; }
			ND_ constexpr const T		Height ()		const { return bottom - top; }
			ND_ constexpr const T		CenterX ()		const { return (right + left) / T (2); }
			ND_ constexpr const T		CenterY ()		const { return (top + bottom) / T (2); }

			ND_ constexpr const Vec2_t	LeftTop ()		const { return { left, top }; }
			ND_ constexpr const Vec2_t	RightBottom ()	const { return { right, bottom }; }
			ND_ constexpr const Vec2_t	LeftBottom ()	const { return { left, bottom }; }
			ND_ constexpr const Vec2_t	RightTop ()		const { return { right, top }; }

			ND_ T const*				data ()			const { return std::addressof (left); }
			ND_ T *						data () { return std::addressof (left); }

			ND_ constexpr const Vec2_t	Size ()			const { return { Width (), Height () }; }
			ND_ constexpr const Vec2_t	Center ()		const { return { CenterX (), CenterY () }; }

			ND_ constexpr bool			IsEmpty ()		const { return loo::math::Equals (left, right) | Equals (top, bottom); }
			ND_ constexpr bool			IsInvalid ()	const { return (right < left) | (bottom < top); }
			ND_ constexpr bool			IsValid ()		const { return (not IsEmpty ()) & (not IsInvalid ()); }

			ND_ constexpr bool  IsNormalized () const;
			Self &			Normalize ();

			ND_ constexpr bool	Intersects (const Vec2_t &point) const;
			ND_ constexpr bool	Intersects (const Self &point) const;

			ND_ constexpr Self	Intersection (const Self &other) const;

			ND_ constexpr loo::math::bool4 operator == (const Self &rhs) const;

			Self&	Join (const Self &other);
			Self&	Join (const Vec2_t &point);

			Self&	Stretch (const Self &size);
			Self&	Stretch (const Vec2_t &size);
			Self&	Stretch (T size);
		};


		using RectU = Rectangle< uint32 >;
		using RectI = Rectangle< int >;
		using RectF = Rectangle< float >;


		/*
		=================================================
			LeftTop / RightBottom
		=================================================
		*/
		template <typename T>
		inline Rectangle<T>&  Rectangle<T>::LeftTop (const Vec2_t& v)
		{
			left = v.x;
			top = v.y;
			return *this;
		}

		template <typename T>
		inline Rectangle<T>&  Rectangle<T>::RightBottom (const Vec2_t& v)
		{
			right = v.x;
			bottom = v.y;
			return *this;
		}

		/*
		=================================================
			operator +
		=================================================
		*/
		template <typename T>
		inline constexpr Rectangle<T>&  operator += (Rectangle<T> &lhs, const loo::math::Vec<T,2> &rhs)
		{
			lhs.left += rhs.x;	lhs.right += rhs.x;
			lhs.top += rhs.y;	lhs.bottom += rhs.y;
			return lhs;
		}

		template <typename T>
		inline constexpr Rectangle<T>  operator + (const Rectangle<T> &lhs, const loo::math::Vec<T, 2> &rhs)
		{
			return Rectangle<T>{ lhs.left + rhs.x, lhs.top + rhs.y,
				lhs.right + rhs.x, lhs.bottom + rhs.y };
		}

		template <typename T>
		inline constexpr Rectangle<T>&  operator += (Rectangle<T> &lhs, const T &rhs)
		{
			return lhs += loo::math::Vec<T, 2>(rhs);
		}

		template <typename T>
		inline constexpr Rectangle<T>  operator + (const Rectangle<T> &lhs, const T &rhs)
		{
			return lhs + loo::math::Vec<T, 2> (rhs);
		}

		/*
		=================================================
			operator -
		=================================================
		*/
		template <typename T>
		inline constexpr Rectangle<T>&  operator -= (Rectangle<T> &lhs, const loo::math::Vec<T, 2> &rhs)
		{
			lhs.left -= rhs.x;	lhs.right -= rhs.x;
			lhs.top -= rhs.y;	lhs.bottom -= rhs.y;
			return lhs;
		}

		template <typename T>
		inline constexpr Rectangle<T>  operator - (const Rectangle<T> &lhs, const loo::math::Vec<T, 2> &rhs)
		{
			return Rectangle<T>{ lhs.left - rhs.x, lhs.top - rhs.y,
				lhs.right - rhs.x, lhs.bottom - rhs.y };
		}

		template <typename T>
		inline constexpr Rectangle<T>&  operator -= (Rectangle<T> &lhs, const T &rhs)
		{
			return lhs -= loo::math::Vec<T,2>(rhs);
		}

		template <typename T>
		inline constexpr Rectangle<T>  operator - (const Rectangle<T> &lhs, const T &rhs)
		{
			return lhs - loo::math::Vec<T,2>(rhs);
		}

		/*
		=================================================
			operator *
		=================================================
		*/
		template <typename T>
		inline constexpr Rectangle<T>&  operator *= (Rectangle<T> &lhs, const loo::math::Vec<T, 2> &rhs)
		{
			lhs.left *= rhs.x;	lhs.right *= rhs.x;
			lhs.top *= rhs.y;	lhs.bottom *= rhs.y;
			return lhs;
		}

		template <typename T>
		inline constexpr Rectangle<T>  operator * (const Rectangle<T> &lhs, const loo::math::Vec<T, 2> &rhs)
		{
			return Rectangle<T>{ lhs.left  * rhs.x, lhs.top    * rhs.y,
				lhs.right * rhs.x, lhs.bottom * rhs.y };
		}

		template <typename T>
		inline constexpr Rectangle<T>&  operator *= (Rectangle<T> &lhs, const T &rhs)
		{
			return lhs *= loo::math::Vec<T,2>(rhs);
		}

		template <typename T>
		inline constexpr Rectangle<T>  operator * (const Rectangle<T> &lhs, const T &rhs)
		{
			return lhs * loo::math::Vec<T,2>(rhs);
		}

		/*
		=================================================
			operator /
		=================================================
		*/
		template <typename T>
		inline constexpr Rectangle<T>&  operator /= (Rectangle<T> &lhs, const loo::math::Vec<T, 2> &rhs)
		{
			lhs.left /= rhs.x;	lhs.right /= rhs.x;
			lhs.top /= rhs.y;	lhs.bottom /= rhs.y;
			return lhs;
		}

		template <typename T>
		inline constexpr Rectangle<T>  operator / (const Rectangle<T> &lhs, const loo::math::Vec<T, 2> &rhs)
		{
			return Rectangle<T>{ lhs.left / rhs.x, lhs.top / rhs.y,
				lhs.right / rhs.x, lhs.bottom / rhs.y };
		}

		template <typename T>
		inline constexpr Rectangle<T>&  operator /= (Rectangle<T> &lhs, const T &rhs)
		{
			return lhs /= loo::math::Vec<T,2>(rhs);
		}

		template <typename T>
		inline constexpr Rectangle<T>  operator / (const Rectangle<T> &lhs, const T &rhs)
		{
			return lhs / loo::math::Vec<T,2>(rhs);
		}

		/*
		=================================================
			IsNormalized
		=================================================
		*/
		template <typename T>
		inline constexpr bool  Rectangle<T>::IsNormalized () const
		{
			return (left <= right) & (top <= bottom);
		}

		/*
		=================================================
			Normalize
		=================================================
		*/
		template <typename T>
		inline Rectangle<T>&  Rectangle<T>::Normalize ()
		{
			if (left > right)	std::swap (left, right);
			if (top > bottom)	std::swap (top, bottom);
			return *this;
		}

		/*
		=================================================
			Intersects
		=================================================
		*/
		template <typename T>
		inline constexpr bool  Rectangle<T>::Intersects (const Vec2_t &point) const
		{
			return (point.x >= left) & (point.x < right) & (point.y >= top) & (point.y < bottom);
		}

		template <typename T>
		inline constexpr bool  Rectangle<T>::Intersects (const Self &other) const
		{
			return	((left < other.right) & (right > other.left) & (bottom > other.top) & (top < other.bottom)) |
				((other.right < left) & (other.left > right) & (other.top > bottom) & (other.bottom < top));
		}

		/*
		=================================================
			operator ==
		=================================================
		*/
		template <typename T>
		inline constexpr loo::math::bool4  Rectangle<T>::operator == (const Self &rhs) const
		{
			return loo::math::bool4 ( left == rhs.left, top == rhs.top, right == rhs.right, bottom == rhs.bottom );
		}

		/*
		=================================================
			Intersection
		=================================================
		*/
		template <typename T>
		inline constexpr Rectangle<T>  Rectangle<T>::Intersection (const Self &other) const
		{
			Rectangle<T>	res;
			res.left = std::max (left, other.left);
			res.top = std::max (top, other.top);
			res.right = std::min (right, other.right);
			res.bottom = std::min (bottom, other.bottom);
			return res;
		}

		/*
		=================================================
			Join
		=================================================
		*/
		template <typename T>
		inline Rectangle<T>&  Rectangle<T>::Join (const Self &other)
		{
			left = std::min (left, other.left);
			top = std::min (top, other.top);
			right = std::max (right, other.right);
			bottom = std::max (bottom, other.bottom);
			return *this;
		}

		template <typename T>
		inline Rectangle<T>&  Rectangle<T>::Join (const Vec2_t &point)
		{
			left = std::min (left, point.x);
			top = std::min (top, point.y);
			right = std::max (right, point.x);
			bottom = std::max (bottom, point.y);
			return *this;
		}

		/*
		=================================================
			Stretch
		=================================================
		*/
		template <typename T>
		inline Rectangle<T>&  Rectangle<T>::Stretch (const Self &size)
		{
			left -= size.left;
			top -= size.top;
			right += size.right;
			bottom += size.bottom;
			return *this;
		}

		template <typename T>
		inline Rectangle<T>&  Rectangle<T>::Stretch (const Vec2_t &size)
		{
			const Vec2_t  half_size = size / T (2);

			left -= half_size.x;
			top -= half_size.y;
			right += half_size.x;
			bottom += half_size.y;
			return *this;
		}

		template <typename T>
		inline Rectangle<T>&  Rectangle<T>::Stretch (T size)
		{
			const T  half_size = size / T (2);

			left -= half_size;
			top -= half_size;
			right += half_size;
			bottom += half_size;
			return *this;
		}

		/*
		=================================================
			Equals
		=================================================
		*/
		template <typename T>
		ND_ inline constexpr loo::math::bool4  Equals (const Rectangle<T> &lhs, const Rectangle<T> &rhs, const T &err = std::numeric_limits<T>::epsilon () * T (2))
		{
			loo::math::bool4	res;
			res[0] = loo::math::Equals (lhs.left, rhs.left, err);
			res[1] = loo::math::Equals (lhs.top, rhs.top, err);
			res[2] = loo::math::Equals (lhs.right, rhs.right, err);
			res[3] = loo::math::Equals (lhs.bottom, rhs.bottom, err);
			return res;
		}


		//template<typename TP,typename TE, glm::qualifier Q>
		//class rect
		//{
		//public:
		//	typedef TP point_value_type;
		//	typedef TE extend_value_type;
		//	typedef glm::vec<2, TP, Q> point_type;
		//	typedef glm::vec<2, TE, Q> extend_type;

		//public:
		//	rect():offset(),extend(){}
		//	const point_value_type X()const { return offset.x; }
		//	const point_value_type Y()const { return offset.y; }
		//	const extend_value_type Width()const { return extend.x; }
		//	const extend_value_type Height()const { return extend.y; }

		//	const point_type& Offset()const { return offset; }
		//	const extend_type& Extend()const { return extend; }

		//private:
		//	point_type offset;
		//	extend_type extend;
		//};

		//typedef rect<loo::float32, loo::float32, glm::qualifier::defaultp> f32rect;
		//typedef rect<loo::float64, loo::float64, glm::qualifier::defaultp> f64rect;
		//typedef rect<int8, int8, glm::qualifier::defaultp> i8rect;
		//typedef rect<int16, int16, glm::qualifier::defaultp> i16rect;
		//typedef rect<int32, int32, glm::qualifier::defaultp> i32rect;
		//typedef rect<int64, int64, glm::qualifier::defaultp> i64rect;
		//typedef rect<uint32, uint32, glm::qualifier::defaultp> u32rect;
		//typedef rect<uint64, uint64, glm::qualifier::defaultp> u64rect;
		//
		//typedef rect<int32, uint32, glm::qualifier::defaultp> i32u32rect;
	}
}

#endif