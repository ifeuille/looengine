

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
project("loo")
cmake_minimum_required(VERSION 3.4)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# version
set(LOO_MAJOR_VERSION 0)
set(LOO_MINOR_VERSION 0)
set(LOO_PATCH_VERSION 0)
set(LOO_VERSION ${LOO_MAJOR_VERSION}.${LOO_MINOR_VERSION}.${LOO_PATCH_VERSION})

find_path(LOO_PROJECT_DIR Logo.ico PATHS ../)
message("Output Binary path = ${LOO_PROJECT_DIR}")

set(LOO_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(LOO_ENGINE_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/loo")


include(${LOO_ROOT_DIR}/buildsys/cmake/Options.cmake)
include(${LOO_ROOT_DIR}/buildsys/cmake/Common.cmake)
include(${LOO_ROOT_DIR}/buildsys/cmake/Platform.cmake)
include(${LOO_ROOT_DIR}/buildsys/cmake/Compiler.cmake)


message(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
message(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(LOO_OUTPUT_DIR "${LOO_PROJECT_DIR}/output/lib/${LOO_PLATFORM_NAME}")
set(LOO_BIN_DIR "${LOO_PROJECT_DIR}/output/bin/${LOO_PLATFORM_NAME}")

add_subdirectory(loo)
if(LOO_BUILD_PROJECTS)
    add_subdirectory(projects)
endif()
