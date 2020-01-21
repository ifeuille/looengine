project("ifvk")
cmake_minimum_required(VERSION 3.4)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(MODULE_NAME ifvk)
set(EXTRA_LINKED_LIBRARIES "")
set(MODULE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(MODULE_ERSION 1)
set(MODULE_SOVERSION 1)
set(FOLDER_PATH Engine/Modules)

set(PUBLIC_HDR_DIR      include)

file(GLOB_RECURSE SOURCE_PUBLIC ${PUBLIC_HDR_DIR}/${MODULE_NAME}/*.h)

set(SOURCE_PRIVATE source/IfVK.cpp)

# OS specific sources
if (WIN32)
    set(SOURCE_PRIVATE ${SOURCE_PRIVATE} source/IfVKWindows.cpp)
elseif (APPLE)
    set(SOURCE_PRIVATE ${SOURCE_PRIVATE} source/IfVKDarwin.cpp)
elseif (LINUX OR ANDROID)
    set(SOURCE_PRIVATE ${SOURCE_PRIVATE} source/IfVKLinuxAndroid.cpp)
else()
    message(FATAL_ERROR "Platform not supported. IfVK supports Linux, Android, MacOS X, and Windows.")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")

if (LINUX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

dep_module_static(global)
find_package(Vulkan)
if (Vulkan_FOUND)
	set(EXTRA_LINKED_LIBRARIES ${EXTRA_LINKED_LIBRARIES} ${Vulkan_LIBRARIES})
	include_directories(${Vulkan_INCLUDE_DIRS})
	link_directories(${Vulkan_LIBRARY_DIRS})
else()
	message("Error : Not found vulkan !!")
endif()

add_static_module()
declare_module_static()
