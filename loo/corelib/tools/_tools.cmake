set(LOCAL_PUBLIC     
${MODULE_ROOT_PATH}/tools/loobytearray.h
)

set(LOCAL_PRIVATE
${MODULE_ROOT_PATH}/tools/loobytearray.cpp
)
source_group("corelib\\tools\\header" FILES ${LOCAL_PUBLIC})
source_group("corelib\\tools\\source" FILES ${LOCAL_PRIVATE})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} ${LOCAL_PUBLIC})
set(SOURCE_PRIVATE ${SOURCE_PRIVATE} ${LOCAL_PRIVATE})