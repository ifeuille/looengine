
set(LOCAL_PUBLIC
${MODULE_ROOT_PATH}/include/vulkanrhi/dllexporter.h 
${MODULE_ROOT_PATH}/include/vulkanrhi/vulkangraphicdevice.h 
)

set(LOCAL_PRIVATE
${MODULE_ROOT_PATH}/source/vulkanrhi/empty.cpp
${MODULE_ROOT_PATH}/source/vulkanrhi/vk_mem_alloc.h
${MODULE_ROOT_PATH}/source/vulkanrhi/vulkangraphicdevice.cpp
${MODULE_ROOT_PATH}/source/vulkanrhi/vulkanglobal.h
${MODULE_ROOT_PATH}/source/vulkanrhi/vulkanrhiprivate.h
${MODULE_ROOT_PATH}/source/vulkanrhi/vulkanconfiguration.h
${MODULE_ROOT_PATH}/source/vulkanrhi/vulkancommandswrapper.h
${MODULE_ROOT_PATH}/source/vulkanrhi/vulkancommandsdirect.h
${MODULE_ROOT_PATH}/source/vulkanrhi/vulkancontext.h
${MODULE_ROOT_PATH}/source/vulkanrhi/vulkandevice.h
${MODULE_ROOT_PATH}/source/vulkanrhi/vulkandevice.cpp
${MODULE_ROOT_PATH}/source/vulkanrhi/vulkanqueue.h
${MODULE_ROOT_PATH}/source/vulkanrhi/vulkanqueue.cpp
${MODULE_ROOT_PATH}/source/vulkanrhi/vulkanglobal.cpp
${MODULE_ROOT_PATH}/source/vulkanrhi/vulkanlayer.cpp
)

set(LOCAL_PRIVATE_INSTANCE
${MODULE_ROOT_PATH}/source/vulkanrhi/instance/device.cpp
${MODULE_ROOT_PATH}/source/vulkanrhi/instance/device.h
${MODULE_ROOT_PATH}/source/vulkanrhi/instance/instance.h
${MODULE_ROOT_PATH}/source/vulkanrhi/instance/instance.cpp
)

set(NATIVE_PRIVATE "")


include_directories(${MODULE_ROOT_PATH}/source)

source_group("vulkanrhi\\include\\vulkanrhi" FILES ${LOCAL_PUBLIC})
source_group("vulkanrhi\\source\\vulkanrhi" FILES ${LOCAL_PRIVATE})
source_group("vulkanrhi\\source\\vulkanrhi\\instance" FILES ${LOCAL_PRIVATE_INSTANCE})

set(SOURCE_PUBLIC ${SOURCE_PUBLIC} 
${LOCAL_PUBLIC} 
)


set(SOURCE_PRIVATE 
${SOURCE_PRIVATE}
${LOCAL_PRIVATE}
${LOCAL_PRIVATE_INSTANCE}
)
