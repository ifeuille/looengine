
set(LOCAL_PUBLIC     
${MODULE_ROOT_PATH}/include/core/application/window.h
${MODULE_ROOT_PATH}/include/core/application/application.h
${MODULE_ROOT_PATH}/include/core/application/input.h
${MODULE_ROOT_PATH}/include/core/application/keycode.h
${MODULE_ROOT_PATH}/include/core/application/syseventbus.h
)

set(LOCAL_PRIVATE
   ${MODULE_ROOT_PATH}/source/core/application/window.cpp
   ${MODULE_ROOT_PATH}/source/core/application/application.cpp
   ${MODULE_ROOT_PATH}/source/core/application/input.cpp
   ${MODULE_ROOT_PATH}/source/core/application/keycode.cpp
   ${MODULE_ROOT_PATH}/source/core/application/syseventbus.cpp
)


if(LOO_PLATFORM_WINDOWS)
    set(LOCAL_PRIVATE ${LOCAL_PRIVATE} ${MODULE_ROOT_PATH}/source/core/application/winwindow.cpp)
    set(LOCAL_PRIVATE ${LOCAL_PRIVATE} ${MODULE_ROOT_PATH}/source/core/application/windowinput.cpp)
elseif(LOO_PLATFORM_LINUX)
    set(LOCAL_PRIVATE ${LOCAL_PRIVATE} ${MODULE_ROOT_PATH}/source/core/application/linuxwindow.cpp)
    set(LOCAL_PRIVATE ${LOCAL_PRIVATE} ${MODULE_ROOT_PATH}/source/core/application/linuxinput.cpp)
elseif(LOO_PLATFORM_ANDROID)
    set(LOCAL_PRIVATE ${LOCAL_PRIVATE} ${MODULE_ROOT_PATH}/source/core/application/androidwindow.cpp)
    set(LOCAL_PRIVATE ${LOCAL_PRIVATE} ${MODULE_ROOT_PATH}/source/core/application/androidinput.cpp)
elseif(LOO_PLATFORM_IOS)
    set(LOCAL_PRIVATE ${LOCAL_PRIVATE} ${MODULE_ROOT_PATH}/source/core/application/ioswindow.cpp)
    set(LOCAL_PRIVATE ${LOCAL_PRIVATE} ${MODULE_ROOT_PATH}/source/core/application/iosinput.cpp)
endif()

source_group("core\\include\\core\\application" FILES ${LOCAL_PUBLIC})
source_group("core\\source\\core\\application" FILES ${LOCAL_PRIVATE})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} ${LOCAL_PUBLIC})
set(SOURCE_PRIVATE ${SOURCE_PRIVATE} ${LOCAL_PRIVATE})