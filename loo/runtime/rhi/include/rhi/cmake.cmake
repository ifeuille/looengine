
set(LOCAL_PUBLIC
${MODULE_ROOT_PATH}/include/rhi/rendersettings.h 
${MODULE_ROOT_PATH}/include/rhi/dllexporter.h 
${MODULE_ROOT_PATH}/include/rhi/commandbuffer.h 
${MODULE_ROOT_PATH}/include/rhi/featuresconfig.h 
${MODULE_ROOT_PATH}/include/rhi/graphicdevice.h 
${MODULE_ROOT_PATH}/include/rhi/resources.h
${MODULE_ROOT_PATH}/include/rhi/rhi.h
${MODULE_ROOT_PATH}/include/rhi/elementformat.h
${MODULE_ROOT_PATH}/include/rhi/descriptions.h
${MODULE_ROOT_PATH}/include/rhi/createinfo.h
${MODULE_ROOT_PATH}/include/rhi/renderutils.h
${MODULE_ROOT_PATH}/include/rhi/commandpool.h
)

set(LOCAL_PRIVATE
${MODULE_ROOT_PATH}/source/rhi/rhi.cpp
${MODULE_ROOT_PATH}/source/rhi/graphicdevice.cpp
${MODULE_ROOT_PATH}/source/rhi/renderutils.cpp
${MODULE_ROOT_PATH}/source/rhi/resources.cpp
${MODULE_ROOT_PATH}/source/rhi/commandbuffer.cpp
${MODULE_ROOT_PATH}/source/rhi/commandpool.cpp

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
