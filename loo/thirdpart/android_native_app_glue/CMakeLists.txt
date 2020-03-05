
set(NATIVE_APP_GLUE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB NATIVE_APP_GLUE_FILES "${NATIVE_APP_GLUE_DIR}/*.c" "${NATIVE_APP_GLUE_DIR}/*.h")
add_library(native_app_glue STATIC ${NATIVE_APP_GLUE_FILES})
target_include_directories(native_app_glue PUBLIC ${NATIVE_APP_GLUE_DIR})
set_property(TARGET native_app_glue PROPERTY FOLDER "thirdpart")
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")