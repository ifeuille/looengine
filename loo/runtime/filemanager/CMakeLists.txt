project("filemanager")
cmake_minimum_required(VERSION 3.4)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(MODULE_NAME filemanager)
set(EXTRA_LINKED_LIBRARIES "")
# 设置该模块的root direction,方便子文件夹里的文件进行引用
set(MODULE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(MODULE_ERSION 1)
set(MODULE_SOVERSION 1)
set(FOLDER_PATH Engine/Modules)
if(LOO_PLATFORM_ANDROID)
    #include_directories(${LOO_THIRDPART_ROOT_DIR}/android_native_app_glue)
    set(EXTRA_LINKED_LIBRARIES ${EXTRA_LINKED_LIBRARIES}              
    native_app_glue
    )
endif()
include(${CMAKE_CURRENT_SOURCE_DIR}/include/filemanager/cmake.cmake)
ADD_DEFINITIONS(-DFILEMANAGER_DLL_EXPORT)

add_dep_link_dir()
dep_module_static(global)
include_directories(${LOO_THIRDPART_ROOT_DIR}/7z)
set(EXTRA_LINKED_LIBRARIES ${EXTRA_LINKED_LIBRARIES}  "7zxa")
set(EXTRA_LINKED_LIBRARIES ${EXTRA_LINKED_LIBRARIES}  "LZMA")
add_module()
depdent_module(filemanager modulemanager)

declare_module()
