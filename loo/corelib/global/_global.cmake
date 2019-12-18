set(LOCAL_PUBLIC     
${MODULE_ROOT_PATH}/global/loocompilerdetection.h
${MODULE_ROOT_PATH}/global/looglobal.h
${MODULE_ROOT_PATH}/global/loosystemdetection.h
${MODULE_ROOT_PATH}/global/looprocessordetection.h
${MODULE_ROOT_PATH}/global/looflags.h
${MODULE_ROOT_PATH}/global/lootypeinfo.h
)

set(LOCAL_PRIVATE
${MODULE_ROOT_PATH}/global/looglobal.cpp
${MODULE_ROOT_PATH}/global/archdetect.cpp
)

source_group("corelib\\global\\header" FILES ${LOCAL_PUBLIC})
source_group("corelib\\global\\source" FILES ${LOCAL_PRIVATE})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} ${LOCAL_PUBLIC})
set(SOURCE_PRIVATE ${SOURCE_PRIVATE} ${LOCAL_PRIVATE})