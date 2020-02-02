#ifndef LOO_GLOBAL_TYPES_H
#define LOO_GLOBAL_TYPES_H
#pragma once
#include "global/global.h"
#include "global/math/math.h"

#include "global/extstd/umax.h"
#include "global/extstd/ptr.h"
#include "global/extstd/typetraits.h"
#include "global/extstd/any.h"
#include "global/extstd/byte.h"
#include "global/extstd/cast.h"
#include "global/extstd/bytes.h"
#include "global/extstd/type.h"
#include "global/extstd/value_ptr.h"
#include "global/extstd/variant.h"
#include "global/extstd/signal.h"
#include "global/extstd/span.h"
#include "global/extstd/arrayview.h"
#include "global/extstd/string_view.h"
#include "global/extstd/status_value.h"
#include "global/extstd/fs_std.h"
#include "global/extstd/noncopyable.h"
#include "global/extstd/atomicops.h"
#include "global/extstd/readerwriterqueue.h"
#include "global/extstd/bufferview.h"
#include "global/extstd/staticstring.h"
#include "global/extstd/ntstringview.h"
#include "global/extstd/fixedarray.h"
#include "global/extstd/untypedallocator.h"
#include "global/extstd/fixedmap.h"
#include "global/extstd/union.h"
#include "global/extstd/optional.h"
#include "global/extstd/operators.h"
#include "global/extstd/arrayutils.h"


namespace loo
{
	typedef nonstd::byte byte;
}

#endif