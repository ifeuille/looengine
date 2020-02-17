# cmake_minimum_required( VERSION 3.10 FATAL_ERROR )

# if (${LOO_ENABLE_GLSLANG})
# 	file( GLOB_RECURSE SOURCES "*.*" )
# 	add_library( "GLSLTrace" STATIC ${SOURCES} )
# 	source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} )
# 	target_include_directories( "GLSLTrace" PUBLIC "." )
# 	set_property( TARGET "GLSLTrace" PROPERTY FOLDER "thirdpart" )
# 	target_link_libraries( "GLSLTrace" PUBLIC "global" )
# 	target_link_libraries( "GLSLTrace" PUBLIC "GLSLang-lib" )
# 	install( TARGETS "GLSLTrace" ARCHIVE DESTINATION "lib" )
# endif ()



project("glsl_trace")
cmake_minimum_required(VERSION 3.4)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
file( GLOB_RECURSE SOURCE_PUBLIC "*.*" )

set(MODULE_NAME glsl_trace)
set(EXTRA_LINKED_LIBRARIES "")
set(MODULE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(MODULE_ERSION 1)
set(MODULE_SOVERSION 1)
set(FOLDER_PATH Engine/Modules)

#include(${CMAKE_CURRENT_SOURCE_DIR}/include/vkfg/cmake.cmake)

set(EXTRA_LINKED_LIBRARIES ${EXTRA_LINKED_LIBRARIES}  "Vulkan-lib")
set(EXTRA_LINKED_LIBRARIES ${EXTRA_LINKED_LIBRARIES}  "GLSLang-lib")

dep_module_static(global)
dep_module_static(vulkanloader)

add_static_module()
depdent_module(ifvk looreflect)

source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_PUBLIC} )
#target_include_directories( "vkfg" PUBLIC "vkfg" )
#target_include_directories( "vkfg" PRIVATE "vkfg/vulkan/device" )
set_property( TARGET "glsl_trace" PROPERTY FOLDER "" )


declare_module_static()
