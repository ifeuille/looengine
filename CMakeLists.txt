

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
project("loo")
cmake_minimum_required(VERSION 3.4)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# version
# set(LOO_MAJOR_VERSION 0)
# set(LOO_MINOR_VERSION 0)
# set(LOO_PATCH_VERSION 0)
# set(LOO_VERSION ${LOO_MAJOR_VERSION}.${LOO_MINOR_VERSION}.${LOO_PATCH_VERSION})

find_path(LOO_PROJECT_DIR Logo.ico PATHS ../)

message("Output Binary path = ${LEngine_PROJECT_DIR}")
