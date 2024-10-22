


MACRO(add_program EXE_NAME)
    if(LOO_PLATFORM_ANDROID)
        add_library(${EXE_NAME} SHARED  ${SOURCE_PRIVATE}
        # ${LOO_THIRDPART_ROOT_DIR}/android_native_app_glue/android_native_app_glue.h
        #${LOO_THIRDPART_ROOT_DIR}/android_native_app_glue/android_native_app_glue.c
        )
        #include_directories(${LOO_THIRDPART_ROOT_DIR}/android_native_app_glue)
    else()
        add_executable(${EXE_NAME} ${SOURCE_PUBLIC} ${SOURCE_PRIVATE})
    endif()
ENDMACRO(add_program)

#EXTRA_LINKED_LIBRARIES
MACRO(declare_program EXE_NAME)  
    target_compile_definitions( ${EXE_NAME}  PUBLIC ${LOO_COMPILER_DEFINITIONS} )
    IF(LOO_PLATFORM_DARWIN)
        FIND_LIBRARY(APPKIT AppKit "/")
        SET(EXTRA_LINKED_LIBRARIES ${EXTRA_LINKED_LIBRARIES} ${APPKIT})
    ELSEIF(LOO_PLATFORM_IOS)
        FIND_LIBRARY(FOUNDATION Foundation "/")
        FIND_LIBRARY(QUARTZCORE QuartzCore "/")
        FIND_LIBRARY(UIKIT UIKit "/")
        FIND_LIBRARY(OPENGLES OpenGLES "/")
        FIND_LIBRARY(COREFOUNDATION CoreFoundation "/")
        FIND_LIBRARY(GLKIT GLKit "/")
        SET(EXTRA_LINKED_LIBRARIES ${EXTRA_LINKED_LIBRARIES} ${FOUNDATION} ${QUARTZCORE} ${UIKIT} ${OPENGLES} ${COREFOUNDATION} ${GLKIT})
    ENDIF()
    if(LOO_PLATFORM_ANDROID)
        SET(SO_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/libs/${LOO_ARCH_NAME})
		SET_TARGET_PROPERTIES(${EXE_NAME} PROPERTIES
			LIBRARY_OUTPUT_DIRECTORY ${SO_OUTPUT_DIR}
			LIBRARY_OUTPUT_DIRECTORY_DEBUG ${SO_OUTPUT_DIR}
			LIBRARY_OUTPUT_DIRECTORY_RELEASE ${SO_OUTPUT_DIR}
			LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${SO_OUTPUT_DIR}
			LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${SO_OUTPUT_DIR}
		)
	endif()

    SET_TARGET_PROPERTIES(${EXE_NAME} PROPERTIES
    PROJECT_LABEL ${EXE_NAME}
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

    IF(LOO_PLATFORM_ANDROID)
        SET_TARGET_PROPERTIES(${EXE_NAME} PROPERTIES OUTPUT_NAME ${EXE_NAME})
    ELSE()
        SET_TARGET_PROPERTIES(${EXE_NAME} PROPERTIES OUTPUT_NAME ${EXE_NAME}${LOO_OUTPUT_SUFFIX})
    ENDIF()

    IF(LOO_PLATFORM_DARWIN OR LOO_PLATFORM_WINDOWS_DESKTOP)
        SET_TARGET_PROPERTIES(${EXE_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${LOO_BIN_DIR}
            RUNTIME_OUTPUT_DIRECTORY_DEBUG ${LOO_BIN_DIR}
            RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LOO_BIN_DIR}
            RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${LOO_BIN_DIR}
            RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${LOO_BIN_DIR}
        )
    ENDIF()
    
    IF(LOO_PLATFORM_ANDROID)

        #add_library(native-app-glue STATIC ${LOO_THIRDPART_ROOT_DIR}/android_native_app_glue/android_native_app_glue.c)
     
        #set(CMAKE_SHARED_LINKER_FLAGS "-u ANativeActivity_onCreate" ${CMAKE_SHARED_LINKER_FLAGS} )

        #include_directories(${LOO_THIRDPART_ROOT_DIR}/android_native_app_glue)
        # find_library( log-lib log )
        # find_library( android-lib android )
        # find_library( z-lib z )
        #set_target_properties(${EXE_NAME} PROPERTIES LINK_FLAGS "-u ANativeActivity_onCreate")
        set(EXTRA_LINKED_LIBRARIES
            -Wl,-whole-archive
            native_app_glue
            -Wl,--no-whole-archive
            android
            log
            atomic
            ${EXTRA_LINKED_LIBRARIES}
        )
        #            -Wl,--no-whole-archive
        #     native_app_glue
     
    ENDIF()
    
    target_link_libraries(${EXE_NAME} ${EXTRA_LINKED_LIBRARIES})

    IF(LOO_PLATFORM_WINDOWS_STORE)
       
    ELSEIF(LOO_PLATFORM_ANDROID)

    ELSEIF(LOO_PLATFORM_IOS)
    
    ENDIF()

    IF(NOT LOO_PLATFORM_WINDOWS_STORE AND NOT LOO_PLATFORM_ANDROID AND NOT LOO_PLATFORM_IOS)
        ADD_POST_BUILD(${EXE_NAME} "")
        INSTALL(TARGETS ${EXE_NAME}
            RUNTIME DESTINATION ${LOO_BIN_DIR}
            LIBRARY DESTINATION ${LOO_BIN_DIR}
            ARCHIVE DESTINATION ${LOO_OUTPUT_DIR}
        )

        CREATE_PROJECT_USERFILE(LOO ${EXE_NAME})
    ENDIF()

    SET_TARGET_PROPERTIES(${EXE_NAME} PROPERTIES FOLDER "${FOLDER_PATH}")

ENDMACRO(declare_program)
