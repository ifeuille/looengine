

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
project("loo")
cmake_minimum_required(VERSION 3.4)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# version
set(LOO_MAJOR_VERSION 1)
set(LOO_MINOR_VERSION 0)
set(LOO_PATCH_VERSION 0)
set(LOO_VERSION ${LOO_MAJOR_VERSION}.${LOO_MINOR_VERSION}.${LOO_PATCH_VERSION})

find_path(LOO_PROJECT_DIR Logo.ico PATHS .)
message("Output Binary path = ${LOO_PROJECT_DIR}")

set(LOO_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(LOO_ENGINE_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/loo")
set(LOO_THIRDPART_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/loo/thirdpart")
set(LOO_RUNTIME_ROOT_DIR "${LOO_ENGINE_ROOT_DIR}/runtime")

include(${LOO_ROOT_DIR}/buildsys/cmake/Options.cmake)
include(${LOO_ROOT_DIR}/buildsys/cmake/Common.cmake)
include(${LOO_ROOT_DIR}/buildsys/cmake/Platform.cmake)
include(${LOO_ROOT_DIR}/buildsys/cmake/Compiler.cmake)

include(${LOO_ROOT_DIR}/buildsys/cmake/compiler_tests.cmake)
include(${LOO_ROOT_DIR}/buildsys/cmake/Programs.cmake)
include(${LOO_ROOT_DIR}/buildsys/cmake/Modules.cmake)
include(${LOO_ROOT_DIR}/buildsys/cmake/Dependence.cmake)

if(LOO_PLATFORM_ANDROID)
     include(${LOO_ROOT_DIR}/buildsys/cmake/module/FindAdb.cmake)
     include(${LOO_ROOT_DIR}/buildsys/cmake/module/FindGradle.cmake)
endif()

set(LOO_OUTPUT_DIR "${LOO_PROJECT_DIR}/binary/libs/${LOO_PLATFORM_NAME}")
set(LOO_BIN_DIR "${LOO_PROJECT_DIR}/binary/bin/${LOO_PLATFORM_NAME}")

message(STATUS "This is LOO_OUTPUT_DIR dir " ${LOO_OUTPUT_DIR})
message(STATUS "This is LOO_BIN_DIR dir " ${LOO_BIN_DIR})



# always build
# m1,m2,m..
#  	|
# AllInEngine
#	|
# Other
add_custom_target(AllInEngine)
set_target_properties(AllInEngine PROPERTIES FOLDER "Engine")

add_subdirectory(loo)
if(LOO_BUILD_PROJECTS)
 #   add_subdirectory(projects)
endif()
