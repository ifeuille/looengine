#ifndef LOO_GLOBAL_TYPES_H
#define LOO_GLOBAL_TYPES_H
#pragma once
#include "global/global.h"
#include "global/math/math.h"
#include "global/math/vec.h"
#include "global/math/rect.h"

#include "global/extstd/ptr.h"
#include "global/extstd/any.h"
#include "global/extstd/byte.h"
#include "global/extstd/cast.h"
#include "global/extstd/bytes.h"
#include "global/extstd/type.h"
#include "global/extstd/typelist.h"
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
#include "global/extstd/enumutils.h"
#include "global/extstd/barrier.h"
#include "global/extstd/memwriter.h"
#include "global/extstd/linearallocator.h"
#include "global/extstd/atomicptr.h"
#include "global/extstd/dataracecheck.h"
#include "global/extstd/dummylock.h"
#include "global/extstd/lfdoublebuffer.h"
#include "global/extstd/lffixedlist.h"
#include "global/extstd/lffixedstack.h"
#include "global/extstd/lfindexedpool.h"
#include "global/extstd/spinlock.h"
#include "global/extstd/singleton.h"
#include "global/extstd/atomiccounter.h"

#include "global/container/appendable.h"
#include "global/container/inplace.h"
#include "global/container/iterators.h"
#include "global/container/bittree.h"
#include "global/container/untypedstorage.h"
#include "global/container/fixedtuplearray.h"
#include "global/container/chunkedindexedpool.h"
#include "global/container/cachedindexedpool.h"

#include "global/template/hash.h"
#include "global/template/flags.h"
#include "global/template/refcounting.h"
#include "global/template/externalstring.h"
#include "global/template/external.h"

#include "global/stream/stream.h"
#include "global/stream/memstream.h"
#include "global/stream/filestream.h"

#include "global/algorithms/stringutils.h"
#include "global/algorithms/stringparser.h"

namespace loo
{
	typedef nonstd::byte byte;
	typedef nonstd::string_view StringView;
	template <typename T>
	using Optional = nonstd::optional<T>;

}


#endif