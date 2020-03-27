#    Project URL: https://github.com/floooh/sokol
#todo 更新为更强大的https://github.com/jarikomppa/soloud.git

project("audio")
cmake_minimum_required(VERSION 3.4)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
file( GLOB_RECURSE SOURCE_PUBLIC "*.*" )


set(MODULE_NAME audio)
set(EXTRA_LINKED_LIBRARIES "")
set(MODULE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(MODULE_ERSION 1)
set(MODULE_SOVERSION 1)
set(FOLDER_PATH Engine/Modules)
if(LOO_PLATFORM_ANDROID)
    set(EXTRA_LINKED_LIBRARIES ${EXTRA_LINKED_LIBRARIES}  OpenSLES)
endif()

source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_PUBLIC} )

ADD_DEFINITIONS(-DLOOAUDIO_DLL_EXPORT)
ADD_DEFINITIONS(-DSOKOL_IMPL)

add_module()
declare_module()
