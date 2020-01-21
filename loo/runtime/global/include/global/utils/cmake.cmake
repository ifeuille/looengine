
set(LOCAL_PUBLIC
${MODULE_ROOT_PATH}/include/global/utils/path.h
${MODULE_ROOT_PATH}/include/global/utils/algorithm.h
${MODULE_ROOT_PATH}/include/global/utils/bitset.h
${MODULE_ROOT_PATH}/include/global/utils/log.h
${MODULE_ROOT_PATH}/include/global/utils/panic.h
${MODULE_ROOT_PATH}/include/global/utils/callstack.h
${MODULE_ROOT_PATH}/include/global/utils/cstring.h
)

set(LOCAL_PUBLIC_WIN32
${MODULE_ROOT_PATH}/include/global/utils/win32/stdtypes.h
)

set(LOCAL_PRIVATE
${MODULE_ROOT_PATH}/source/global/utils/path.cpp
${MODULE_ROOT_PATH}/source/global/utils/log.cpp
${MODULE_ROOT_PATH}/source/global/utils/panic.cpp
${MODULE_ROOT_PATH}/source/global/utils/callstack.cpp
${MODULE_ROOT_PATH}/source/global/utils/cstring.cpp
)



source_group("global\\include\\global\\utils" FILES ${LOCAL_PUBLIC})
source_group("global\\include\\global\\utils\\win32" FILES ${LOCAL_PUBLIC_WIN32})

source_group("global\\source\\global\\utils" FILES ${LOCAL_PRIVATE})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} 
${LOCAL_PUBLIC} 
${LOCAL_PUBLIC_WIN32}
)


set(SOURCE_PRIVATE ${SOURCE_PRIVATE} 
${LOCAL_PRIVATE} 
)

