

project("plog")
cmake_minimum_required(VERSION 3.4)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(MODULE_NAME plog)
set(EXTRA_LINKED_LIBRARIES "")
set(MODULE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(MODULE_ERSION 1)
set(MODULE_SOVERSION 1)
set(FOLDER_PATH Engine/Modules)

include(${CMAKE_CURRENT_SOURCE_DIR}/include/plog/cmake.cmake)
ADD_DEFINITIONS(-DPLOG_DLL_EXPORT)

add_module()
declare_module()
