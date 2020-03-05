
if(LOO_PLATFORM_WINDOWS_STORE)
string(REPLACE "/permissive-" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif()

set(EXE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# change here
set(EXE_NAME testframework)

set(EXTRA_LINKED_LIBRARIES "")
# change here
set(SOURCE_PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/header/config.h

)
set(SOURCE_PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/test1.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/test2.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/test3.cpp
)

# change here
source_group("testframework\\header" FILES ${SOURCE_PUBLIC})
source_group("testframework\\source" FILES ${SOURCE_PRIVATE})
set(FOLDER_PATH tests)

add_dep_link_dir()
dep_module_static(global)
#dep_module_static(ifvk)
dep_module_static(vkfg)
dep_module_static(vulkanloader)
#add_dep_7z()
add_dep_glm()

include_directories(${EXE_ROOT_PATH}/header)
set(EXTRA_LINKED_LIBRARIES ${EXTRA_LINKED_LIBRARIES}  "Vulkan-lib")
add_program(${EXE_NAME})

# dep of core
depdent_module(${EXE_NAME} modulemanager)
depdent_module(${EXE_NAME} filemanager)
#depdent_module(${EXE_NAME} rhi)
depdent_module(${EXE_NAME} core)
depdent_module(${EXE_NAME} looreflect)
#depdent_module(${EXE_NAME} vkfg)

declare_program(${EXE_NAME})


