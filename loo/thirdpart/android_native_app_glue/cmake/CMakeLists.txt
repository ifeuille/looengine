PROJECT(AndroidNativeAppGlue C)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.6)

SET(NDK_VERSION 16b)

SET(ANAG_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")
SET(LOO_ROOT_DIR "${ANAG_PROJECT_DIR}/../..")

INCLUDE(${LOO_ROOT_DIR}/buildsys/cmake/Common.cmake)
INCLUDE(${LOO_ROOT_DIR}/buildsys/cmake/Platform.cmake)
INCLUDE(${LOO_ROOT_DIR}/buildsys/cmake/Compiler.cmake)

SET(ANAG_OUTPUT_DIR "${ANAG_PROJECT_DIR}/lib/${LOO_PLATFORM_NAME}")

FOREACH(flag_var
		CMAKE_C_FLAGS CMAKE_CXX_FLAGS)
	IF(LOO_COMPILER_MSVC)
		STRING(REPLACE "/W4" "/W0" ${flag_var} "${${flag_var}}")
		STRING(REPLACE "/WX" "/WX-" ${flag_var} "${${flag_var}}")
	ELSE()
		STRING(REPLACE "-Wall" "-w" ${flag_var} "${${flag_var}}")
		STRING(REPLACE "-Werror" "-Wno-error" ${flag_var} "${${flag_var}}")
	ENDIF()
ENDFOREACH()

SET(ANAG_SOURCES
	${ANAG_PROJECT_DIR}/android_native_app_glue.c
	${ANAG_PROJECT_DIR}/android_native_app_glue.h
)

target_include_directories(native_app_glue PUBLIC ${ANAG_PROJECT_DIR})
add_library()(native_app_glue STATIC ${ANAG_SOURCES})

    
set_property(TARGET native_app_glue PROPERTY FOLDER "ThirdParty")
