project("core")
cmake_minimum_required(VERSION 3.4)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(MODULE_NAME core)
set(EXTRA_LINKED_LIBRARIES "")
# 设置该模块的root direction,方便子文件夹里的文件进行引用
set(MODULE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(MODULE_ERSION 1)
set(MODULE_SOVERSION 1)
set(FOLDER_PATH Engine/Modules)

file( GLOB_RECURSE SOURCE_PUBLIC "*.*" )
#file( GLOB_RECURSE SOURCE_PRIVATE "*.cpp" )
source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_PUBLIC} )
#source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_PRIVATE} )

#IF(LOO_PLATFORM_ANDROID)
#	INCLUDE_DIRECTORIES(${LOO_THIRDPART_ROOT_DIR}/android_native_app_glue)
#ENDIF()
#include(${CMAKE_CURRENT_SOURCE_DIR}/include/core/cmake.cmake)
#include(${CMAKE_CURRENT_SOURCE_DIR}/include/core/application/cmake.cmake)
#include(${CMAKE_CURRENT_SOURCE_DIR}/include/core/object/cmake.cmake)#include(${CMAKE_CURRENT_SOURCE_DIR}/include/core/vulkan/cmake.cmake)

ADD_DEFINITIONS(-DCORE_DLL_EXPORT)
set(EXTRA_LINKED_LIBRARIES ${EXTRA_LINKED_LIBRARIES}  "Vulkan-lib")

# if(LOO_PLATFORM_ANDROID)
#     set(EXTRA_LINKED_LIBRARIES ${EXTRA_LINKED_LIBRARIES}  "native_app_glue")
# endif()

add_dep_link_dir()
dep_module_static(global)
#dep_module_static(ifvk)
dep_module_static(vulkanloader)
dep_module_static(vkfg)
#add_dep_7z()
add_dep_glm()

add_module()
depdent_module(core modulemanager)
depdent_module(core filemanager)
#depdent_module(core rhi)
#depdent_module(core vulkanrhi)
depdent_module(core looreflect)

declare_module()
