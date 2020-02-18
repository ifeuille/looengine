
if(LOO_PLATFORM_WINDOWS_STORE)
string(REPLACE "/permissive-" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif()

set(EXE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# change here
set(EXE_NAME graphic_test)
set(EXTRA_LINKED_LIBRARIES "")
# change here
# set(SOURCE_PUBLIC
# ${CMAKE_CURRENT_SOURCE_DIR}/header/config.h
# ${CMAKE_CURRENT_SOURCE_DIR}/header/graphicapp.h

# )
# set(SOURCE_PRIVATE
# ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
# ${CMAKE_CURRENT_SOURCE_DIR}/source/graphicapp.cpp
# ${CMAKE_CURRENT_SOURCE_DIR}/source/tests/draw1.cpp
# )

file( GLOB_RECURSE SOURCE_PUBLIC "*.h" )
file( GLOB_RECURSE SOURCE_PRIVATE "*.cpp" )
source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_PUBLIC} )
source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_PRIVATE} )



# change here
# source_group("graphic\\header" FILES ${SOURCE_PUBLIC})
# source_group("graphic\\source" FILES ${SOURCE_PRIVATE})
set(FOLDER_PATH tests)
set(EXTRA_LINKED_LIBRARIES ${EXTRA_LINKED_LIBRARIES}  PUBLIC GLSLang-lib)
set(EXTRA_LINKED_LIBRARIES ${EXTRA_LINKED_LIBRARIES}  "Vulkan-lib")

add_dep_link_dir()
dep_module_static(global)
dep_module_static(vulkanloader)
#dep_module_static(ifvk)
dep_module_static(vkfg)
dep_module_static(glsl_trace)
dep_module_static(pipeline_compiler)
#add_dep_7z()
#add_dep_glm()

include_directories(${EXE_ROOT_PATH}/header)
add_program(${EXE_NAME})

target_compile_definitions( ${EXE_NAME} PUBLIC "LOO_TEST_GRAPHS_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/Graphs\"" )
target_compile_definitions( ${EXE_NAME} PUBLIC "LOO_TEST_DUMPS_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/Dumps\"" )

# dep of core
depdent_module(${EXE_NAME} modulemanager)
depdent_module(${EXE_NAME} filemanager)
#depdent_module(${EXE_NAME} rhi)
depdent_module(${EXE_NAME} core)
depdent_module(core looreflect)

#target_link_libraries( "graphic_test" PUBLIC "GLSLang-lib" )

declare_program(${EXE_NAME})


