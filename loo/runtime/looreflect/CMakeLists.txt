project("looreflect")
cmake_minimum_required(VERSION 3.4)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(MODULE_NAME looreflect)
set(EXTRA_LINKED_LIBRARIES "")
# 设置该模块的root direction,方便子文件夹里的文件进行引用
set(MODULE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(MODULE_ERSION 1)
set(MODULE_SOVERSION 1)
set(FOLDER_PATH Engine/Modules)

include(${CMAKE_CURRENT_SOURCE_DIR}/include/looreflect/cmake.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/include/object/cmake.cmake)
ADD_DEFINITIONS(-DLOOREFLECT_DLL_EXPORT)

add_dep_link_dir()
dep_module_static(global)

add_module()
declare_module()
