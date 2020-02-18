

project("modulemanager")
cmake_minimum_required(VERSION 3.4)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(MODULE_NAME modulemanager)
set(EXTRA_LINKED_LIBRARIES "")
set(EXTRA_LINKED_LIBRARIES_PUBLIC "")
set(EXTRA_LINKED_LIBRARIES_INTERFACE "")
set(MODULE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(MODULE_ERSION 1)
set(MODULE_SOVERSION 1)
set(FOLDER_PATH Engine/Modules)

include(${CMAKE_CURRENT_SOURCE_DIR}/include/modulemanager/cmake.cmake)
ADD_DEFINITIONS(-DLOOMODULEMANAGER_DLL_EXPORT)

#dep_module_include(global)
add_dep_link_dir()

dep_module_static(global)

# set(EXTRA_LINKED_LIBRARIES ${EXTRA_LINKED_LIBRARIES} 
#     debug global${LOO_OUTPUT_SUFFIX}_d optimized global${KLAYGE_OUTPUT_SUFFIX}
# )

add_module()

declare_module()
