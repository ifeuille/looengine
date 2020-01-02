
set(LOCAL_PUBLIC     
${MODULE_ROOT_PATH}/include/core/application/window.h
${MODULE_ROOT_PATH}/include/core/application/application.h
)

set(LOCAL_PRIVATE
   ${MODULE_ROOT_PATH}/source/core/application/window.cpp
   ${MODULE_ROOT_PATH}/source/core/application/application.cpp
)


if(LOO_PLATFORM_WINDOWS)
    set(LOCAL_PRIVATE ${LOCAL_PRIVATE} ${MODULE_ROOT_PATH}/source/core/application/winwindow.cpp)
elseif(LOO_PLATFORM_LINUX)
    set(LOCAL_PRIVATE ${LOCAL_PRIVATE} ${MODULE_ROOT_PATH}/source/core/application/linuxwindow.cpp)
elseif(LOO_PLATFORM_ANDROID)
    set(LOCAL_PRIVATE ${LOCAL_PRIVATE} ${MODULE_ROOT_PATH}/source/core/application/androidwindow.cpp)
elseif(LOO_PLATFORM_IOS)
    set(LOCAL_PRIVATE ${LOCAL_PRIVATE} ${MODULE_ROOT_PATH}/source/core/application/ioswindow.cpp)
endif()

source_group("core\\include\\core\\application" FILES ${LOCAL_PUBLIC})
source_group("core\\source\\core\\application" FILES ${LOCAL_PRIVATE})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} ${LOCAL_PUBLIC})
set(SOURCE_PRIVATE ${SOURCE_PRIVATE} ${LOCAL_PRIVATE})