project("global")
cmake_minimum_required(VERSION 3.4)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(MODULE_NAME global)
set(EXTRA_LINKED_LIBRARIES "")
set(MODULE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(MODULE_ERSION 1)
set(MODULE_SOVERSION 1)
set(FOLDER_PATH Engine/Modules)

include(${CMAKE_CURRENT_SOURCE_DIR}/include/global/cmake.cmake)
ADD_DEFINITIONS(-DLOOGLOBAL_DLL_EXPORT)
add_dep_glm()
add_static_module()
declare_module_static()
