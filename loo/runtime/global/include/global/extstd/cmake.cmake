
set(LOCAL_PUBLIC
${MODULE_ROOT_PATH}/include/global/extstd/filesystem.h
${MODULE_ROOT_PATH}/include/global/extstd/fs_std.h
${MODULE_ROOT_PATH}/include/global/extstd/noncopyable.h
${MODULE_ROOT_PATH}/include/global/extstd/string_view.h
${MODULE_ROOT_PATH}/include/global/extstd/any.h
${MODULE_ROOT_PATH}/include/global/extstd/atomicops.h
${MODULE_ROOT_PATH}/include/global/extstd/byte.h
${MODULE_ROOT_PATH}/include/global/extstd/invoke.h
${MODULE_ROOT_PATH}/include/global/extstd/optional.h
${MODULE_ROOT_PATH}/include/global/extstd/readerwriterqueue.h
${MODULE_ROOT_PATH}/include/global/extstd/span.h
${MODULE_ROOT_PATH}/include/global/extstd/status_value.h
${MODULE_ROOT_PATH}/include/global/extstd/type.h
${MODULE_ROOT_PATH}/include/global/extstd/value_ptr.h
${MODULE_ROOT_PATH}/include/global/extstd/variant.h
${MODULE_ROOT_PATH}/include/global/extstd/signal.h
${MODULE_ROOT_PATH}/include/global/extstd/operators.h
${MODULE_ROOT_PATH}/include/global/extstd/strtk.h
${MODULE_ROOT_PATH}/include/global/extstd/typetraits.h
${MODULE_ROOT_PATH}/include/global/extstd/arrayview.h
${MODULE_ROOT_PATH}/include/global/extstd/bufferview.h
${MODULE_ROOT_PATH}/include/global/extstd/staticstring.h
${MODULE_ROOT_PATH}/include/global/extstd/ntstringview.h
${MODULE_ROOT_PATH}/include/global/extstd/memutils.h
${MODULE_ROOT_PATH}/include/global/extstd/bytes.h
${MODULE_ROOT_PATH}/include/global/extstd/cast.h
${MODULE_ROOT_PATH}/include/global/extstd/bitmath.h
${MODULE_ROOT_PATH}/include/global/extstd/fixedarray.h
${MODULE_ROOT_PATH}/include/global/extstd/untypedallocator.h
${MODULE_ROOT_PATH}/include/global/extstd/ptr.h
${MODULE_ROOT_PATH}/include/global/extstd/fixedmap.h
${MODULE_ROOT_PATH}/include/global/extstd/union.h
${MODULE_ROOT_PATH}/include/global/extstd/arrayutils.h
${MODULE_ROOT_PATH}/include/global/extstd/umax.h
${MODULE_ROOT_PATH}/include/global/extstd/enumutils.h
${MODULE_ROOT_PATH}/include/global/extstd/defaulttypes.h
${MODULE_ROOT_PATH}/include/global/extstd/barrier.h
${MODULE_ROOT_PATH}/include/global/extstd/memwriter.h
${MODULE_ROOT_PATH}/include/global/extstd/linearallocator.h
${MODULE_ROOT_PATH}/include/global/extstd/atomicptr.h
${MODULE_ROOT_PATH}/include/global/extstd/dataracecheck.h
${MODULE_ROOT_PATH}/include/global/extstd/dummylock.h
${MODULE_ROOT_PATH}/include/global/extstd/lfdoublebuffer.h
${MODULE_ROOT_PATH}/include/global/extstd/lffixedlist.h
${MODULE_ROOT_PATH}/include/global/extstd/lffixedstack.h
${MODULE_ROOT_PATH}/include/global/extstd/lfindexedpool.h
${MODULE_ROOT_PATH}/include/global/extstd/spinlock.h
${MODULE_ROOT_PATH}/include/global/extstd/singleton.h
${MODULE_ROOT_PATH}/include/global/extstd/atomiccounter.h
${MODULE_ROOT_PATH}/include/global/extstd/typelist.h

)

set(LOCAL_PUBLIC_EXTSTD_ATOMIC_QUEUE
${MODULE_ROOT_PATH}/include/global/extstd/atomic_queue/atomic_queue_mutex.h
${MODULE_ROOT_PATH}/include/global/extstd/atomic_queue/atomic_queue.h
${MODULE_ROOT_PATH}/include/global/extstd/atomic_queue/barrier.h
${MODULE_ROOT_PATH}/include/global/extstd/atomic_queue/defs.h
${MODULE_ROOT_PATH}/include/global/extstd/atomic_queue/moodycamel.h
${MODULE_ROOT_PATH}/include/global/extstd/atomic_queue/spinlock.h
)
set(LOCAL_PUBLIC_EXTSTD_CONCURRENTQUEUE
${MODULE_ROOT_PATH}/include/global/extstd/concurrentqueue/blockingconcurrentqueue.h
${MODULE_ROOT_PATH}/include/global/extstd/concurrentqueue/concurrentqueue.h
${MODULE_ROOT_PATH}/include/global/extstd/concurrentqueue/lightweightsemaphore.h
)

set(LOCAL_PRIVATE
${MODULE_ROOT_PATH}/source/global/extstd/barrier.cpp

)



source_group("global\\include\\global\\extstd" FILES ${LOCAL_PUBLIC})
source_group("global\\include\\global\\extstd\\atomic_queue" FILES ${LOCAL_PUBLIC_EXTSTD_ATOMIC_QUEUE})
source_group("global\\include\\global\\extstd\\concurrentqueue" FILES ${LOCAL_PUBLIC_EXTSTD_CONCURRENTQUEUE})
source_group("global\\source\\global\\extstd" FILES ${LOCAL_PRIVATE})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} 
${LOCAL_PUBLIC} 
${LOCAL_PUBLIC_EXTSTD_ATOMIC_QUEUE} 
${LOCAL_PUBLIC_EXTSTD_CONCURRENTQUEUE} 
)


set(SOURCE_PRIVATE ${SOURCE_PRIVATE} 
${LOCAL_PRIVATE} 
)

