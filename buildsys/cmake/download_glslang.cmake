# find or download GLSLANG

if (${LOO_EXTERNALS_USE_PREBUILD} AND ${LOO_ENABLE_GLSLANG})
    message( FATAL_ERROR "not supported" )

	add_library( "GLSLang-lib" INTERFACE )
	target_include_directories( "GLSLang-lib" INTERFACE "${LOO_THIRDPART_ROOT_DIR}/glslang/include" )
	target_compile_definitions( "GLSLang-lib" INTERFACE LOO_ENABLE_GLSLANG ENABLE_HLSL ENABLE_OPT AMD_EXTENSIONS NV_EXTENSIONS )
	set( LOO_GLSLANG_LIBRARIES
		"${LOO_THIRDPART_ROOT_DIR}/glslang/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SPIRV${CMAKE_STATIC_LIBRARY_SUFFIX}"
		"${LOO_THIRDPART_ROOT_DIR}/glslang/lib/${CMAKE_STATIC_LIBRARY_PREFIX}glslang${CMAKE_STATIC_LIBRARY_SUFFIX}"
		"${LOO_THIRDPART_ROOT_DIR}/glslang/lib/${CMAKE_STATIC_LIBRARY_PREFIX}OSDependent${CMAKE_STATIC_LIBRARY_SUFFIX}"
		"${LOO_THIRDPART_ROOT_DIR}/glslang/lib/${CMAKE_STATIC_LIBRARY_PREFIX}HLSL${CMAKE_STATIC_LIBRARY_SUFFIX}" )
	if (UNIX)
		set( LOO_GLSLANG_LIBNAMES "${LOO_GLSLANG_LIBNAMES}" "pthread" )
	endif ()
	set( LOO_GLSLANG_LIBRARIES ${LOO_GLSLANG_LIBRARIES}
		"${LOO_THIRDPART_ROOT_DIR}/glslang/lib/${CMAKE_STATIC_LIBRARY_PREFIX}OGLCompiler${CMAKE_STATIC_LIBRARY_SUFFIX}"
		"${LOO_THIRDPART_ROOT_DIR}/glslang/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SPIRV-Tools${CMAKE_STATIC_LIBRARY_SUFFIX}"
		"${LOO_THIRDPART_ROOT_DIR}/glslang/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SPIRV-Tools-opt${CMAKE_STATIC_LIBRARY_SUFFIX}" )
	set_property( TARGET "GLSLang-lib" PROPERTY INTERFACE_LINK_LIBRARIES "${LOO_GLSLANG_LIBRARIES}" )


elseif (${LOO_ENABLE_GLSLANG})
	set( LOO_EXTERNAL_GLSLANG_PATH "" CACHE PATH "path to glslang source" )
	mark_as_advanced( LOO_EXTERNAL_GLSLANG_PATH )

	# SPIRV-Tools require Python 2.7 for building
	if(LOO_PLATFORM_WINDOWS)
	find_package( PythonInterp 2.7 REQUIRED )
	find_package( PythonLibs 2.7 REQUIRED )
	endif()

	# reset to default
	if (NOT EXISTS "${LOO_EXTERNAL_GLSLANG_PATH}/CMakeLists.txt")
		message( STATUS "glslang is not found in ${LOO_EXTERNAL_GLSLANG_PATH}" )
		set( LOO_EXTERNAL_GLSLANG_PATH "${LOO_THIRDPART_ROOT_DIR}/glslang" CACHE PATH "" FORCE )
	else ()
		message( STATUS "glslang found in \"${LOO_EXTERNAL_GLSLANG_PATH}\"" )
	endif ()

	if (NOT EXISTS "${LOO_EXTERNAL_GLSLANG_PATH}/CMakeLists.txt")
		set( LOO_GLSLANG_REPOSITORY "https://github.com/KhronosGroup/glslang.git" )
	else ()
		set( LOO_GLSLANG_REPOSITORY "" )
	endif ()
	
	if (NOT EXISTS "${LOO_EXTERNAL_GLSLANG_PATH}/External/SPIRV-Tools/include")
		set( LOO_SPIRVTOOLS_REPOSITORY "https://github.com/KhronosGroup/SPIRV-Tools.git" )
	else ()
		set( LOO_SPIRVTOOLS_REPOSITORY "" )
	endif ()
	
	if (NOT EXISTS "${LOO_EXTERNAL_GLSLANG_PATH}/External/SPIRV-Tools/external/SPIRV-Headers/include")
		set( LOO_SPIRVHEADERS_REPOSITORY "https://github.com/KhronosGroup/SPIRV-Headers.git" )
	else ()
		set( LOO_SPIRVHEADERS_REPOSITORY "" )
	endif ()
	
	set( ENABLE_HLSL ON CACHE BOOL "glslang option" )
	set( ENABLE_OPT ON CACHE BOOL "glslang option" )
	set( ENABLE_AMD_EXTENSIONS ON CACHE BOOL "glslang option" )
	set( ENABLE_NV_EXTENSIONS ON CACHE BOOL "glslang option" )
	set( ENABLE_GLSLANG_BINARIES ON CACHE BOOL "glslang option" )
	mark_as_advanced( ENABLE_HLSL ENABLE_OPT ENABLE_AMD_EXTENSIONS ENABLE_NV_EXTENSIONS )

	if(NOT LOO_PLATFORM_WINDOWS)
		set(ENABLE_OPT OFF)
		set(ENABLE_GLSLANG_BINARIES OFF)
	endif()
	if (${LOO_EXTERNALS_USE_STABLE_VERSIONS})
		# stable release February 8, 2019
		set( GLSLANG_TAG "7.11.3113" )
		set( SPIRV_TOOLS_TAG "v2019.1" )
		set( SPIRV_HEADERS_TAG "1.3.7" )
	else ()
		set( GLSLANG_TAG "master" )
		set( SPIRV_TOOLS_TAG "master" )
		set( SPIRV_HEADERS_TAG "master" )
	endif ()

	#glslang
	if(NOT (LOO_GLSLANG_REPOSITORY STREQUAL  ""))
		FetchContent_Declare( ThirdPartGLSLang
			GIT_REPOSITORY		${LOO_GLSLANG_REPOSITORY}
			GIT_TAG				${GLSLANG_TAG}
			SOURCE_DIR			"${LOO_EXTERNAL_GLSLANG_PATH}"
		)
		
		FetchContent_GetProperties( ThirdPartGLSLang )
		if (NOT ThirdPartGLSLang_POPULATED)
			message( STATUS "downloading GLSLang" )
			FetchContent_Populate( ThirdPartGLSLang )
		endif ()
	endif()

	#spirv-tools
	if(NOT (LOO_SPIRVTOOLS_REPOSITORY STREQUAL  ""))
		FetchContent_Declare( ThirdPartSpirvTools
			GIT_REPOSITORY		${LOO_SPIRVTOOLS_REPOSITORY}
			GIT_TAG				${SPIRV_TOOLS_TAG}
			SOURCE_DIR			"${LOO_EXTERNAL_GLSLANG_PATH}/External/SPIRV-Tools"
		)
		
		FetchContent_GetProperties( ThirdPartSpirvTools )
		if (NOT ThirdPartSpirvTools_POPULATED)
			message( STATUS "downloading Spirv-tools" )
			FetchContent_Populate( ThirdPartSpirvTools )
		endif ()
	endif()

	#spirv-header
	if(NOT (LOO_SPIRVHEADERS_REPOSITORY STREQUAL  ""))
		FetchContent_Declare( ThirdPartSpirvHeader
			GIT_REPOSITORY		${LOO_SPIRVHEADERS_REPOSITORY}
			GIT_TAG				${SPIRV_HEADERS_TAG}
			SOURCE_DIR			"${LOO_EXTERNAL_GLSLANG_PATH}/External/SPIRV-Tools/external/SPIRV-Headers"
		)
		
		FetchContent_GetProperties( ThirdPartSpirvHeader )
		if (NOT TThirdPartSpirvHeader_POPULATED)
			message( STATUS "downloading Spirv-header" )
			FetchContent_Populate( ThirdPartSpirvHeader )
		endif ()
	endif()

	#顺序很重要..否则会有binary_dir冲突问题
	add_subdirectory(${LOO_EXTERNAL_GLSLANG_PATH}/External/SPIRV-Tools/external/SPIRV-Headers)
	if (${ENABLE_OPT})
		message("ENABLE_OPT=${ENABLE_OPT}")
		add_subdirectory(${LOO_EXTERNAL_GLSLANG_PATH}/External/SPIRV-Tools)
	endif()
	add_subdirectory(${LOO_EXTERNAL_GLSLANG_PATH})

	#glslang
	set_property(TARGET glslang PROPERTY FOLDER "thirdpart/glslang")
	set_property(TARGET OGLCompiler PROPERTY FOLDER "thirdpart/glslang")
	set_property(TARGET OSDependent PROPERTY FOLDER "thirdpart/glslang")
	set_property(TARGET SPIRV PROPERTY FOLDER "thirdpart/glslang")
	set_property(TARGET SPVRemapper PROPERTY FOLDER "thirdpart/glslang")

	set_property(TARGET HLSL PROPERTY FOLDER "thirdpart/glslang/HLSL")

	if (${ENABLE_OPT})

		set_property(TARGET spirv-tools-build-version PROPERTY FOLDER "thirdpart/glslang/spirv-tools build")
		set_property(TARGET spirv-tools-debuginfo PROPERTY FOLDER "thirdpart/glslang/spirv-tools build")
		set_property(TARGET spirv-tools-header-DebugInfo PROPERTY FOLDER "thirdpart/glslang/spirv-tools build")
		set_property(TARGET spirv-tools-spv-amd-gcn-shader PROPERTY FOLDER "thirdpart/glslang/spirv-tools build")
		set_property(TARGET spirv-tools-spv-amd-shader-ballot PROPERTY FOLDER "thirdpart/glslang/spirv-tools build")
		set_property(TARGET spirv-tools-spv-amd-shader-explicit-vertex-parameter PROPERTY FOLDER "thirdpart/glslang/spirv-tools build")
		set_property(TARGET spirv-tools-spv-amd-shader-trinary-minmax PROPERTY FOLDER "thirdpart/glslang/spirv-tools build")

		set_property(TARGET spirv-tools-cpp-example PROPERTY FOLDER "thirdpart/glslang/spriv-tools examples")

		set_property(TARGET spirv-as PROPERTY FOLDER "thirdpart/glslang/spirv-tools executables")
		set_property(TARGET spirv-cfg PROPERTY FOLDER "thirdpart/glslang/spirv-tools executables")
		set_property(TARGET spirv-dis PROPERTY FOLDER "thirdpart/glslang/spirv-tools executables")
		set_property(TARGET spirv-link PROPERTY FOLDER "thirdpart/glslang/spirv-tools executables")
		set_property(TARGET spirv-opt PROPERTY FOLDER "thirdpart/glslang/spirv-tools executables")
		set_property(TARGET spirv-reduce PROPERTY FOLDER "thirdpart/glslang/spirv-tools executables")
		set_property(TARGET spirv-stats PROPERTY FOLDER "thirdpart/glslang/spirv-tools executables")
		set_property(TARGET spirv-val PROPERTY FOLDER "thirdpart/glslang/spirv-tools executables")

		set_property(TARGET SPIRV-Tools PROPERTY FOLDER "thirdpart/glslang/spirv-tools libraries")
		set_property(TARGET SPIRV-Tools-link PROPERTY FOLDER "thirdpart/glslang/spirv-tools libraries")
		set_property(TARGET SPIRV-Tools-opt PROPERTY FOLDER "thirdpart/glslang/spirv-tools libraries")
		set_property(TARGET SPIRV-Tools-reduce PROPERTY FOLDER "thirdpart/glslang/spirv-tools libraries")
		set_property(TARGET SPIRV-Tools-shared PROPERTY FOLDER "thirdpart/glslang/spirv-tools libraries")
		set_property(TARGET spirv-tools-vimsyntax PROPERTY FOLDER "thirdpart/glslang/spirv-tools utilities")

		set_property(TARGET spirv-tools-pkg-config PROPERTY FOLDER "thirdpart/glslang/other")
		set_property(TARGET spirv-tools-shared-pkg-config PROPERTY FOLDER "thirdpart/glslang/other")
	
		
		set_property(TARGET core_tables PROPERTY FOLDER "thirdpart/glslang/other")
		set_property(TARGET enum_string_mapping PROPERTY FOLDER "thirdpart/glslang/other")
		set_property(TARGET extinst_tables PROPERTY FOLDER "thirdpart/glslang/other")


	endif()

	if(ENABLE_GLSLANG_BINARIES)
		set_property(TARGET spirv-remap PROPERTY FOLDER "thirdpart/glslang")
		set_property(TARGET glslangValidator PROPERTY FOLDER "thirdpart/glslang/tools")
		set_property(TARGET glslang-default-resource-limits PROPERTY FOLDER "thirdpart/glslang")
	endif()

	set_property(TARGET install-headers PROPERTY FOLDER "thirdpart/glslang/other")
	set_property(TARGET SPIRV-Headers-example PROPERTY FOLDER "thirdpart/glslang/other")
	set_property(TARGET SPIRV-Headers-example-1.1 PROPERTY FOLDER "thirdpart/glslang/other")


	set( LOO_GLSLANG_DEFINITIONS "LOO_ENABLE_GLSLANG" )
	
	if (${ENABLE_OPT})
		set( LOO_GLSLANG_DEFINITIONS "${LOO_GLSLANG_DEFINITIONS}" "ENABLE_OPT" )
	endif ()

	if (${ENABLE_HLSL})
		set( LOO_GLSLANG_DEFINITIONS "${LOO_GLSLANG_DEFINITIONS}" "ENABLE_HLSL" )
	endif ()

	if (${ENABLE_AMD_EXTENSIONS})
		set( LOO_GLSLANG_DEFINITIONS "${LOO_GLSLANG_DEFINITIONS}" "AMD_EXTENSIONS" )
	endif ()

	if (${ENABLE_NV_EXTENSIONS})
		set( LOO_GLSLANG_DEFINITIONS "${LOO_GLSLANG_DEFINITIONS}" "NV_EXTENSIONS" )
	endif ()

	# glslang libraries
	set( LOO_GLSLANG_LIBNAMES "SPIRV" "glslang" "OSDependent" "HLSL" )
	
	if (UNIX)
		set( LOO_GLSLANG_LIBNAMES "${LOO_GLSLANG_LIBNAMES}" "pthread" )
	endif ()

	set( LOO_GLSLANG_LIBNAMES "${LOO_GLSLANG_LIBNAMES}" "OGLCompiler" )
								
	if (${ENABLE_OPT})
		set( LOO_GLSLANG_LIBNAMES "${LOO_GLSLANG_LIBNAMES}" "SPIRV-Tools" "SPIRV-Tools-opt" )
	endif ()

    if (MSVC)
    #${CMAKE_DEBUG_POSTFIX}
    #glslang is d
    #loo is _d
		set( DBG_POSTFIX "d" )
	else ()
		set( DBG_POSTFIX "" )
	endif ()

    set( LOO_GLSLANG_LIBRARIES "" )
    message("CMAKE_STATIC_LIBRARY_SUFFIX=${CMAKE_STATIC_LIBRARY_SUFFIX}")
	foreach ( LIBNAME ${LOO_GLSLANG_LIBNAMES} )
		set( LOO_GLSLANG_LIBRARIES	"${LOO_GLSLANG_LIBRARIES}" "${LIBNAME}" )
	endforeach ()
	
	add_library( "GLSLang-lib" INTERFACE )
    set_property( TARGET "GLSLang-lib" PROPERTY INTERFACE_LINK_LIBRARIES "${LOO_GLSLANG_LIBRARIES}" )
	target_compile_definitions( "GLSLang-lib" INTERFACE "${LOO_GLSLANG_DEFINITIONS}" )
	add_dependencies( "GLSLang-lib" "glslang-main" )

endif ()
