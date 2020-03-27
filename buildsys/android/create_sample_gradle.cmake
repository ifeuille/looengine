

cmake_minimum_required(VERSION 3.10)

set(SCRIPT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(ROOT_DIR ${ALL_ROOT})

set(VALID_ABI "armeabi" "armeabi-v7a" "arm64-v8a" "x86" "x86_64")

set(ANDROID_SAMPLE_TEMPLATE_DIR ${ROOT_DIR}/android/examples/_template)
set(GRADLE_BUILD_FILE ${ANDROID_SAMPLE_TEMPLATE_DIR}/build.gradle.in)
set(GRADLE_CMAKE_FILE ${ANDROID_SAMPLE_TEMPLATE_DIR}/CMakeLists.txt.in)
set(GRABLE_ANDROIDMAINFEST ${ANDROID_SAMPLE_TEMPLATE_DIR}/src/main/AndroidManifest.xml.in)
set(GRABLE_ANDROIDMAINFEST_DEBUG ${ANDROID_SAMPLE_TEMPLATE_DIR}/src/debug/AndroidManifest.xml.in)

include(${SCRIPT_DIR}/utils.cmake)

# script parameters
set(ANDROID_API 24 CACHE STRING "")
set(ARCH_ABI "arm64-v8a;armeabi-v7a" CACHE STRING "")
set(ASSET_DIRS "assets" CACHE PATHS "")
set(RES_DIRS "res" CACHE PATHS "")
set(JNI_LIBS_DIRS "jni" CACHE PATHS "")
set(NATIVE_SCRIPT "CMakeLists.txt" CACHE FILE "")
set(NATIVE_ARGUMENTS "ANDROID_TOOLCHAIN=clang;ANDROID_STL=c++_static" CACHE STRING "")
set(OUTPUT_DIR "${ROOT_DIR}/build/android_gradle" CACHE PATH "")
set(ENGINE_ROOT_DIR "../../" CACHE STRING "")
set(SAMPLE_NAME "noname" CACHE STRING "")
set(APP_ID "sample" CACHE STRING "")
set(ANDROID_LIB_NAME_VALUE "native-lib" CACHE STRING "")
set(ANDROID_LIB_NAME_VALUE_DEBUG "native-lib_d" CACHE STRING "")
set(ASSET_COPY "" CACHE STRING "")
set(PACKAGE_NAME "" CACHE STRING "")

#applicationId "com.loo.sample.%SAMPLE_NAME%"
# minSdkVersion
set(MIN_SDK_VERSION "minSdkVersion ${ANDROID_API}")
if(IS_DIRECTORY ${ALL_ROOT})
    file(RELATIVE_PATH ENGINE_ROOT_DIR ${OUTPUT_DIR} ${ALL_ROOT})
else()
    set(ENGINE_ROOT_DIR ${ALL_ROOT})
endif()

message("ALL_ROOT=${ALL_ROOT}")
message("ENGINE_ROOT_DIR=${ENGINE_ROOT_DIR}")
set(SAMPLE_NAME ${PROJECT_NAME})
set(APP_ID "applicationId \'com.loo.sample.${PROJECT_NAME}\'")
set(ANDROID_LIB_NAME_VALUE "android:value=\'${PROJECT_NAME}\'" )
set(PACKAGE_NAME "package=\"com.loo.sample.${SAMPLE_NAME}\"" )
set(ANDROID_LIB_NAME_VALUE_DEBUG "android:value=\'${PROJECT_NAME}_d\'" )

file(COPY ${ANDROID_SAMPLE_TEMPLATE_DIR}/src  DESTINATION ${OUTPUT_DIR}/  PATTERN     "*.in"    EXCLUDE)


foreach(JAVA_DIR ${JAVA_DIRS})
    if(NOT IS_ABSOLUTE ${JAVA_DIR})
        set(JAVA_DIR ${CMAKE_SOURCE_DIR}/${JAVA_DIR})
    endif()

    if(IS_DIRECTORY ${JAVA_DIR})
        file(RELATIVE_PATH JAVA_DIR ${OUTPUT_DIR} ${JAVA_DIR})
        list(APPEND JAVA_LIST ${JAVA_DIR})
    else()
        message(STATUS "Java dir not exists at `${JAVA_DIR}`")
    endif()
endforeach()

# ndk.abiFilters
set(ABI_LIST)

foreach(ABI_FILTER ${ARCH_ABI})
    if(${ABI_FILTER} IN_LIST VALID_ABI)
        list(APPEND ABI_LIST ${ABI_FILTER})
    else()
        message(STATUS "Filter abi is invalid `${ABI_FILTER}`")
    endif()
endforeach()

string_join(
    GLUE "', '"
    INPUT ${ABI_LIST}
    OUTPUT ABI_LIST)

if(NOT ${ABI_LIST})
    set(NDK_ABI_FILTERS "ndk { abiFilters '${ABI_LIST}' }")
else()
    message(FATAL_ERROR "Minimum one android arch abi required.")
endif()

# assets.srcDirs
set(ASSETS_LIST)

foreach(ASSET_DIR ${ASSET_DIRS})
    if(NOT IS_ABSOLUTE ${ASSET_DIR})
        set(ASSET_DIR ${CMAKE_SOURCE_DIR}/${ASSET_DIR})
    endif()

    if(IS_DIRECTORY ${ASSET_DIR})
        file(RELATIVE_PATH ASSET_DIR ${OUTPUT_DIR} ${ASSET_DIR})
        list(APPEND ASSETS_LIST ${ASSET_DIR})
    else()
        message(STATUS "Asset dir not exists at `${ASSET_DIR}`")
    endif()   
endforeach()

string_join(
    GLUE "', '"    
    INPUT ${ASSETS_LIST}
    OUTPUT ASSETS_LIST)

if(NOT ${ASSETS_LIST})
    set(ASSETS_SRC_DIRS "assets.srcDirs += [ '${ASSETS_LIST}' ]")
endif()

# res.srcDirs
set(RES_LIST)

foreach(RES_DIR ${RES_DIRS})
    if(NOT IS_ABSOLUTE ${RES_DIR})
        set(RES_DIR ${CMAKE_SOURCE_DIR}/${RES_DIR})
    endif()

    if(IS_DIRECTORY ${RES_DIR})
        file(RELATIVE_PATH RES_DIR ${OUTPUT_DIR} ${RES_DIR})
        list(APPEND RES_LIST ${RES_DIR})
    else()
        message(STATUS "Resource dir not exists at `${RES_DIR}`")
    endif()
endforeach()

string_join(
    GLUE "', '"    
    INPUT ${RES_LIST}
    OUTPUT RES_LIST)

if(NOT ${RES_LIST})
    set(RES_SRC_DIRS "res.srcDirs += [ '${RES_LIST}' ]")
endif()


# cmake.path
if(NOT IS_ABSOLUTE ${NATIVE_SCRIPT})
    set(NATIVE_SCRIPT ${CMAKE_SOURCE_DIR}/${NATIVE_SCRIPT})
endif()
message("NATIVE_SCRIPT=${NATIVE_SCRIPT}")
if(EXISTS ${NATIVE_SCRIPT})
    file(RELATIVE_PATH NATIVE_SCRIPT_TMP ${OUTPUT_DIR} ${NATIVE_SCRIPT})

    set(CMAKE_PATH "cmake {\n\t\t\tpath '${NATIVE_SCRIPT_TMP}'\n\t\t\tbuildStagingDirectory \'build-native\'\n\t\t\tversion \'3.10.2\'\n\t\t} ")
endif()


# cmake.arguments
set(ARGS_LIST)

foreach(NATIVE_ARG ${NATIVE_ARGUMENTS})
    list(APPEND ARGS_LIST "-D${NATIVE_ARG}")
endforeach()

list(APPEND ARGS_LIST "-DLOO_BUILD_TESTS_${SAMPLE_NAME}=1")

string_join(
    GLUE "', '"
    INPUT ${ARGS_LIST}
    OUTPUT ARGS_LIST)
    
if(NOT ${ARGS_LIST} AND EXISTS ${NATIVE_SCRIPT})
    set(CMAKE_ARGUMENTS "cmake {\n\t\t\t\targuments '${ARGS_LIST}' \n\t\t\t}")
endif()



configure_file(${GRADLE_BUILD_FILE} ${OUTPUT_DIR}/build.gradle)
#configure_file(${GRADLE_CMAKE_FILE} ${OUTPUT_DIR}/CMakeLists.txt)
configure_file(${GRABLE_ANDROIDMAINFEST} ${OUTPUT_DIR}/src/main/AndroidManifest.xml)
configure_file(${GRABLE_ANDROIDMAINFEST_DEBUG} ${OUTPUT_DIR}/src/debug/AndroidManifest.xml)

message(STATUS "Android Gradle Project (With Native Support) generated at:\n\t${OUTPUT_DIR}")
