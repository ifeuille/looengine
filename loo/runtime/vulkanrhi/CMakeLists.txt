

project("vulkanrhi")
cmake_minimum_required(VERSION 3.4)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(MODULE_NAME vulkanrhi)
set(EXTRA_LINKED_LIBRARIES "")
set(EXTRA_LINKED_LIBRARIES_PUBLIC "")
set(EXTRA_LINKED_LIBRARIES_INTERFACE "")
set(MODULE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(MODULE_ERSION 1)
set(MODULE_SOVERSION 1)
set(FOLDER_PATH Engine/Modules)

include(${CMAKE_CURRENT_SOURCE_DIR}/include/vulkanrhi/cmake.cmake)
ADD_DEFINITIONS(-DVULKANRHI_DLL_EXPORT)


add_dep_link_dir()

dep_module_static(global)
dep_module_static(ifvk)
add_dep_glm()
find_package(Vulkan)
if (Vulkan_FOUND)
	set(EXTRA_LINKED_LIBRARIES ${EXTRA_LINKED_LIBRARIES} ${Vulkan_LIBRARIES})
	include_directories(${Vulkan_INCLUDE_DIRS})
	link_directories(${Vulkan_LIBRARY_DIRS})
else()
	message("Error : Not found vulkan !!")
endif()


add_module()
depdent_module(core modulemanager)
depdent_module(core filemanager)
depdent_module(core rhi)

declare_module()
