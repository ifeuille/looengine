#ifndef LE_CORE_MATH_RECT_H
#define LE_CORE_MATH_RECT_H
#include "global/math/mathcore.h"

namespace loo
{
	namespace math
	{
		template<typename TP,typename TE, glm::qualifier Q>
		class rect
		{
		public:
			typedef TP point_value_type;
			typedef TE extend_value_type;
			typedef glm::vec<2, TP, Q> point_type;
			typedef glm::vec<2, TE, Q> extend_type;

		public:
			rect():offset(),extend(){}
			const point_value_type X()const { return offset.x; }
			const point_value_type Y()const { return offset.y; }
			const extend_value_type Width()const { return extend.x; }
			const extend_value_type Height()const { return extend.y; }

			const point_type& Offset()const { return offset; }
			const extend_type& Extend()const { return extend; }

		private:
			point_type offset;
			extend_type extend;
		};

		typedef rect<loo::float32, loo::float32, glm::qualifier::defaultp> f32rect;
		typedef rect<loo::float64, loo::float64, glm::qualifier::defaultp> f64rect;
		typedef rect<int8, int8, glm::qualifier::defaultp> i8rect;
		typedef rect<int16, int16, glm::qualifier::defaultp> i16rect;
		typedef rect<int32, int32, glm::qualifier::defaultp> i32rect;
		typedef rect<int64, int64, glm::qualifier::defaultp> i64rect;
		typedef rect<uint32, uint32, glm::qualifier::defaultp> u32rect;
		typedef rect<uint64, uint64, glm::qualifier::defaultp> u64rect;
		
		typedef rect<int32, uint32, glm::qualifier::defaultp> i32u32rect;
	}
}

#endif