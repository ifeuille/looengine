

project("vulkanrhi")
cmake_minimum_required(VERSION 3.4)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(MODULE_NAME vulkanrhi)
set(EXTRA_LINKED_LIBRARIES "")
set(MODULE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(MODULE_ERSION 1)
set(MODULE_SOVERSION 1)
set(FOLDER_PATH Engine/Modules)

include(${CMAKE_CURRENT_SOURCE_DIR}/include/vulkanrhi/cmake.cmake)
ADD_DEFINITIONS(-DVULKANRHI_DLL_EXPORT)


add_dep_link_dir()

dep_module_static(global)

add_module()
depdent_module(core modulemanager)
depdent_module(core filemanager)
depdent_module(core rhi)

declare_module()
