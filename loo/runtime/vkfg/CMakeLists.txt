project("vkfg")
cmake_minimum_required(VERSION 3.4)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
file( GLOB_RECURSE SOURCE_PUBLIC "*.*" )

set(MODULE_NAME vkfg)
set(EXTRA_LINKED_LIBRARIES "")
set(EXTRA_LINKED_LIBRARIES_PUBLIC "")
set(EXTRA_LINKED_LIBRARIES_INTERFACE "")
set(MODULE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(MODULE_ERSION 1)
set(MODULE_SOVERSION 1)
set(FOLDER_PATH Engine/Modules)

#include(${CMAKE_CURRENT_SOURCE_DIR}/include/vkfg/cmake.cmake)

ADD_DEFINITIONS(-DLOOVKFG_DLL_EXPORT)
ADD_DEFINITIONS(-DLOO_ENABLE_VULKAN_MEMORY_ALLOCATOR)
set(EXTRA_LINKED_LIBRARIES ${EXTRA_LINKED_LIBRARIES}  "Vulkan-lib")

dep_module_static(global)
#dep_module_static(ifvk)
dep_module_static(vulkanloader)
add_dep_glm()

# find_package(Vulkan)
# if (Vulkan_FOUND)
# 	set(EXTRA_LINKED_LIBRARIES ${EXTRA_LINKED_LIBRARIES} ${Vulkan_LIBRARIES})
# 	include_directories(${Vulkan_INCLUDE_DIRS})
# 	link_directories(${Vulkan_LIBRARY_DIRS})
# else()
# 	message("Error : Not found vulkan !!")
# endif()

add_static_module()
depdent_module(ifvk looreflect)



source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_PUBLIC} )
#target_include_directories( "vkfg" PUBLIC "vkfg" )
#target_include_directories( "vkfg" PRIVATE "vkfg/vulkan/device" )
set_property( TARGET "vkfg" PROPERTY FOLDER "" )


declare_module_static()
