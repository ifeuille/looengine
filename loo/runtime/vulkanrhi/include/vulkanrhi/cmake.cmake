
set(LOCAL_PUBLIC
${MODULE_ROOT_PATH}/include/vulkanrhi/dllexporter.h 
)

set(LOCAL_PRIVATE
${MODULE_ROOT_PATH}/source/vulkanrhi/empty.cpp
${MODULE_ROOT_PATH}/source/vulkanrhi/vk_mem_alloc.h
)



source_group("vulkanrhi\\include\\vulkanrhi" FILES ${LOCAL_PUBLIC})
source_group("vulkanrhi\\source\\vulkanrhi" FILES ${LOCAL_PRIVATE})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} 
${LOCAL_PUBLIC} 
)


set(SOURCE_PRIVATE 
${SOURCE_PRIVATE}
${LOCAL_PRIVATE}
)
