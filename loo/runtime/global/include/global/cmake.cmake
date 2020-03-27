
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
${MODULE_ROOT_PATH}/include/global/types.h
)


set(LOCAL_PUBLIC_MATH
${MODULE_ROOT_PATH}/include/global/math/hash.h
${MODULE_ROOT_PATH}/include/global/math/math.h
${MODULE_ROOT_PATH}/include/global/math/color.h
${MODULE_ROOT_PATH}/include/global/math/random.h
${MODULE_ROOT_PATH}/include/global/math/rect.h
${MODULE_ROOT_PATH}/include/global/math/vec.h
${MODULE_ROOT_PATH}/include/global/math/matrix.h
${MODULE_ROOT_PATH}/include/global/math/compilemath.h
${MODULE_ROOT_PATH}/include/global/math/glminclude.h
)

set(LOCAL_PRIVATE
${MODULE_ROOT_PATH}/source/global/thread.cpp
${MODULE_ROOT_PATH}/source/global/utlis.cpp
${MODULE_ROOT_PATH}/source/global/time.cpp
)


set(LOCAL_PRIVATE_MATH
${MODULE_ROOT_PATH}/source/global/math/color.cpp
${MODULE_ROOT_PATH}/source/global/math/random.cpp
)


source_group("global\\include\\global" FILES ${LOCAL_PUBLIC})
source_group("global\\include\\global\\math" FILES ${LOCAL_PUBLIC_MATH})
source_group("global\\source\\global" FILES ${LOCAL_PRIVATE})
source_group("global\\source\\global\\math" FILES ${LOCAL_PRIVATE_MATH})

set(SOURCE_PUBLIC ${SOURCE_PUBLIC} 
${LOCAL_PUBLIC} 
${LOCAL_PUBLIC_CONTAINER}
${LOCAL_PUBLIC_MATH}
)


set(SOURCE_PRIVATE 
${SOURCE_PRIVATE} 
${LOCAL_PRIVATE} 
${LOCAL_PRIVATE_MATH}
)
include(${MODULE_ROOT_PATH}/include/global/template/cmake.cmake)
include(${MODULE_ROOT_PATH}/include/global/utils/cmake.cmake)
include(${MODULE_ROOT_PATH}/include/global/stream/cmake.cmake)
include(${MODULE_ROOT_PATH}/include/global/algorithms/cmake.cmake)
include(${MODULE_ROOT_PATH}/include/global/extstd/cmake.cmake)
include(${MODULE_ROOT_PATH}/include/global/container/cmake.cmake)