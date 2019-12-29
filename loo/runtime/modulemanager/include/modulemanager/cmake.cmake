
set(LOCAL_PUBLIC
${MODULE_ROOT_PATH}/include/modulemanager/dllloader.h
${MODULE_ROOT_PATH}/include/modulemanager/dllexport.h
${MODULE_ROOT_PATH}/include/modulemanager/moduleinterface.h
${MODULE_ROOT_PATH}/include/modulemanager/modulemanager.h
)

set(LOCAL_PRIVATE
${MODULE_ROOT_PATH}/source/modulemanager/dllloader.cpp
${MODULE_ROOT_PATH}/source/modulemanager/modulemanager.cpp
)

source_group("modulemanager\\include\\modulemanager" FILES ${LOCAL_PUBLIC})
source_group("modulemanager\\source\\modulemanager" FILES ${LOCAL_PRIVATE})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} ${LOCAL_PUBLIC})
set(SOURCE_PRIVATE ${SOURCE_PRIVATE} ${LOCAL_PRIVATE})