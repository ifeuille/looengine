PROJECT(corelib)
 
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
set(MODULE_NAME corelib)

set(MODULE_ERSION 1)
set(MODULE_SOVERSION 1)
set(SOURCE_PUBLIC "")
set(SOURCE_PRIVATE "")
set(MODULE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

include(tools/_tools.cmake)
include(kernel/_kernel.cmake)
include(io/_io.cmake)
include(global/_global.cmake)

add_definitions(-DLOO_BUILD_CORELIB)

#INCLUDE_DIRECTORIES(${LOO_RUNTIME_ROOT_DIR}/${MODULE_NAME}/Public)
INCLUDE_DIRECTORIES(${LOO_ENGINE_INCLUDE_ROOT_DIR} ${LOO_ENGINE_PRIVATE_INCLUDE_ROOT_DIR})
add_module()
declare_module()

set_property(TARGET ${MODULE_NAME} PROPERTY FOLDER "loo/engine")