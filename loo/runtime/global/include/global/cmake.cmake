
set(LOCAL_PUBLIC
${MODULE_ROOT_PATH}/include/global/config.h
${MODULE_ROOT_PATH}/include/global/global.h
${MODULE_ROOT_PATH}/include/global/platform.h
${MODULE_ROOT_PATH}/include/global/architecture.h
${MODULE_ROOT_PATH}/include/global/compiler.h
${MODULE_ROOT_PATH}/include/global/thread.h
${MODULE_ROOT_PATH}/include/global/utlis.h
${MODULE_ROOT_PATH}/include/global/mutex.h
${MODULE_ROOT_PATH}/include/global/time.h
)
set(LOCAL_PUBLIC_EXTSTD
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

set(LOCAL_PUBLIC_CONTAINER
${MODULE_ROOT_PATH}/include/global/container/arrayref.h
${MODULE_ROOT_PATH}/include/global/container/comptr.h
${MODULE_ROOT_PATH}/include/global/container/customizedstreambuf.h
)

set(LOCAL_PUBLIC_MATH
${MODULE_ROOT_PATH}/include/global/math/hash.h
${MODULE_ROOT_PATH}/include/global/math/math.h
${MODULE_ROOT_PATH}/include/global/math/color.h
${MODULE_ROOT_PATH}/include/global/math/mathcore.h
${MODULE_ROOT_PATH}/include/global/math/random.h
${MODULE_ROOT_PATH}/include/global/math/rect.h
)

set(LOCAL_PRIVATE
${MODULE_ROOT_PATH}/source/global/thread.cpp
${MODULE_ROOT_PATH}/source/global/utlis.cpp
${MODULE_ROOT_PATH}/source/global/time.cpp
)

set(LOCAL_PRIVATE_CONTAINER
${MODULE_ROOT_PATH}/source/global/container/customizedstreambuf.cpp
)
set(LOCAL_PRIVATE_MATH
${MODULE_ROOT_PATH}/source/global/math/color.cpp
${MODULE_ROOT_PATH}/source/global/math/random.cpp
)

source_group("global\\include\\global" FILES ${LOCAL_PUBLIC})
source_group("global\\include\\global\\extstd" FILES ${LOCAL_PUBLIC_EXTSTD})
source_group("global\\include\\global\\extstd\\atomic_queue" FILES ${LOCAL_PUBLIC_EXTSTD_ATOMIC_QUEUE})
source_group("global\\include\\global\\extstd\\concurrentqueue" FILES ${LOCAL_PUBLIC_EXTSTD_CONCURRENTQUEUE})
source_group("global\\include\\global\\container" FILES ${LOCAL_PUBLIC_CONTAINER})
source_group("global\\include\\global\\math" FILES ${LOCAL_PUBLIC_MATH})
source_group("global\\source\\global" FILES ${LOCAL_PRIVATE})
source_group("global\\source\\global\\container" FILES ${LOCAL_PRIVATE_CONTAINER})
source_group("global\\source\\global\\math" FILES ${LOCAL_PRIVATE_MATH})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} 
${LOCAL_PUBLIC} 
${LOCAL_PUBLIC_EXTSTD}
${LOCAL_PUBLIC_EXTSTD_ATOMIC_QUEUE} 
${LOCAL_PUBLIC_EXTSTD_CONCURRENTQUEUE}
${LOCAL_PUBLIC_CONTAINER}
${LOCAL_PUBLIC_MATH}
)


set(SOURCE_PRIVATE 
${SOURCE_PRIVATE} 
${LOCAL_PRIVATE} 
${LOCAL_PRIVATE_CONTAINER}
${LOCAL_PRIVATE_MATH}
)
include(${MODULE_ROOT_PATH}/include/global/template/cmake.cmake)
