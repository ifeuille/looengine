
set(LOCAL_PUBLIC
${MODULE_ROOT_PATH}/include/rhi/rendersettings.h 
${MODULE_ROOT_PATH}/include/rhi/dllexporter.h 
${MODULE_ROOT_PATH}/include/rhi/elementformat.h 
${MODULE_ROOT_PATH}/include/rhi/elementformat.h 
${MODULE_ROOT_PATH}/include/rhi/elementformat.h 
${MODULE_ROOT_PATH}/include/rhi/elementformat.h 
${MODULE_ROOT_PATH}/include/rhi/elementformat.h 
${MODULE_ROOT_PATH}/include/rhi/elementformat.h 
)

set(LOCAL_PRIVATE
${MODULE_ROOT_PATH}/source/rhi/empty.cpp
)



source_group("rhi\\include\\rhi" FILES ${LOCAL_PUBLIC})
source_group("rhi\\source\\rhi" FILES ${LOCAL_PRIVATE})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} 
${LOCAL_PUBLIC} 
)


set(SOURCE_PRIVATE 
${SOURCE_PRIVATE}
${LOCAL_PRIVATE}
)
