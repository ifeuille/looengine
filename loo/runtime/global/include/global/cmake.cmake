
set(LOCAL_PUBLIC
${MODULE_ROOT_PATH}/include/global/config.h
${MODULE_ROOT_PATH}/include/global/global.h
${MODULE_ROOT_PATH}/include/global/platform.h
${MODULE_ROOT_PATH}/include/global/architecture.h
${MODULE_ROOT_PATH}/include/global/compiler.h
)
set(LOCAL_PUBLIC_EXTSTD
${MODULE_ROOT_PATH}/include/global/extstd/filesystem.h
${MODULE_ROOT_PATH}/include/global/extstd/fs_std.h
)

set(LOCAL_PRIVATE
${MODULE_ROOT_PATH}/source/global/empty.cpp
)

source_group("global\\include\\global" FILES ${LOCAL_PUBLIC})
source_group("global\\include\\global\\extstd" FILES ${LOCAL_PUBLIC_EXTSTD})
source_group("global\\source\\global" FILES ${LOCAL_PRIVATE})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} 
${LOCAL_PUBLIC} 
${LOCAL_PUBLIC_EXTSTD})

set(SOURCE_PRIVATE ${SOURCE_PRIVATE} ${LOCAL_PRIVATE})