# cmake_minimum_required( VERSION 3.10 FATAL_ERROR )

# file( GLOB_RECURSE SOURCES "*.*" )
# add_library( "VulkanLoader" STATIC ${SOURCES} )
# source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} )
# target_include_directories( "VulkanLoader" PUBLIC ".." )
# set_property( TARGET "VulkanLoader" PROPERTY FOLDER "Extensions" )
# target_link_libraries( "VulkanLoader" PUBLIC "STL" )
# target_link_libraries( "VulkanLoader" PUBLIC "Vulkan-lib" )
# install( TARGETS "VulkanLoader" ARCHIVE DESTINATION "lib" )


project("vulkanloader")
cmake_minimum_required(VERSION 3.4)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
file( GLOB_RECURSE SOURCE_PUBLIC "*.*" )

set(MODULE_NAME vulkanloader)
set(EXTRA_LINKED_LIBRARIES "")
set(EXTRA_LINKED_LIBRARIES_PUBLIC "")
set(EXTRA_LINKED_LIBRARIES_INTERFACE "")
set(MODULE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(MODULE_ERSION 1)
set(MODULE_SOVERSION 1)
set(FOLDER_PATH Engine/Modules)

file( GLOB_RECURSE SOURCE_PUBLIC "*.h" )
file( GLOB_RECURSE SOURCE_PRIVATE "*.cpp" )
#file(GLOB_RECURSE SOURCE_PUBLIC ${PUBLIC_HDR_DIR}/${MODULE_NAME}/*.h)

#set(SOURCE_PRIVATE source/IfVK.cpp)
source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} )

#include(${CMAKE_CURRENT_SOURCE_DIR}/include/vkfg/cmake.cmake)

ADD_DEFINITIONS(-DVULKANLOADER_DLL_EXPORT)

dep_module_static(global)
add_dep_glm()
#find_package(Vulkan)
# if (Vulkan_FOUND)
# 	set(EXTRA_LINKED_LIBRARIES ${EXTRA_LINKED_LIBRARIES} ${Vulkan_LIBRARIES})
# 	include_directories(${Vulkan_INCLUDE_DIRS})
# 	link_directories(${Vulkan_LIBRARY_DIRS})
# else()
# 	message("Error : Not found vulkan !!")
# endif()

set(EXTRA_LINKED_LIBRARIES ${EXTRA_LINKED_LIBRARIES}  "Vulkan-lib")

add_static_module()
#depdent_module(ifvk looreflect)
#target_link_libraries( "vulkanloader" PUBLIC "Vulkan-lib" )

source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_PUBLIC} )
#target_include_directories( "vkfg" PUBLIC "vkfg" )
#target_include_directories( "vkfg" PRIVATE "vkfg/vulkan/device" )
set_property( TARGET "vulkanloader" PROPERTY FOLDER "" )


declare_module_static()