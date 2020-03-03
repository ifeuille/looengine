# Find or download Vulkan headers

if (NOT CMAKE_VERSION VERSION_LESS 3.7.0)
#	find_package( Vulkan )
endif ()


if (NOT Vulkan_FOUND)
	if (EXISTS "${LOO_THIRDPART_ROOT_DIR}/vulkan/vulkan_core.h")
		set( Vulkan_INCLUDE_DIRS "${LOO_THIRDPART_ROOT_DIR}" )
		set( Vulkan_FOUND TRUE )

	elseif (EXISTS "${LOO_THIRDPART_ROOT_DIR}/vulkan/include/vulkan/vulkan_core.h")
		set( Vulkan_INCLUDE_DIRS "${LOO_THIRDPART_ROOT_DIR}/vulkan/include" )
		set( Vulkan_FOUND TRUE )

	elseif (EXISTS "${LOO_THIRDPART_ROOT_DIR}/Vulkan-Headers/include/vulkan/vulkan_core.h")
		set( Vulkan_INCLUDE_DIRS "${LOO_THIRDPART_ROOT_DIR}/Vulkan-Headers/include" )
		set( Vulkan_FOUND TRUE )
	endif ()
endif ()

# select version
if (${LOO_EXTERNALS_USE_STABLE_VERSIONS})
	set( VULKAN_HEADERS_TAG "v1.2.132" )
else ()
	set( VULKAN_HEADERS_TAG "master" )
endif ()

# download
if (NOT Vulkan_FOUND AND NOT CMAKE_VERSION VERSION_LESS 3.11.0)
	FetchContent_Declare( ExternalVulkanHeaders
		GIT_REPOSITORY		https://github.com/KhronosGroup/Vulkan-Headers.git
		GIT_TAG				${VULKAN_HEADERS_TAG}
		SOURCE_DIR			"${LOO_THIRDPART_ROOT_DIR}/Vulkan-Headers"
	)
	
	FetchContent_GetProperties( ExternalVulkanHeaders )
	if (NOT ExternalVulkanHeaders_POPULATED)
		message( STATUS "downloading Vulkan-Headers" )
		FetchContent_Populate( ExternalVulkanHeaders )
	endif ()

	set( Vulkan_INCLUDE_DIRS "${LOO_THIRDPART_ROOT_DIR}/Vulkan-Headers/include" )
	set( Vulkan_FOUND TRUE )
endif ()


if (NOT Vulkan_FOUND)
	message( FATAL_ERROR "Vulkan headers is not found! Install VulkanSDK or download from https://github.com/KhronosGroup/Vulkan-Headers" )
endif ()

set( LOO_VULKAN_DEFINITIONS "LOO_ENABLE_VULKAN" )

if (FALSE)
	if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
		set( LOO_VULKAN_DEFINITIONS "${LOO_VULKAN_DEFINITIONS}" "VK_USE_PLATFORM_XCB_KHR=1" "VK_USE_PLATFORM_XLIB_KHR=1" )	# TODO

	elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Android")
		set( LOO_VULKAN_DEFINITIONS "${LOO_VULKAN_DEFINITIONS}" "-VK_USE_PLATFORM_ANDROID_KHR=1" )

	elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
		set( LOO_VULKAN_DEFINITIONS "${LOO_VULKAN_DEFINITIONS}" "VK_USE_PLATFORM_MACOS_MVK=1" )

	elseif (${CMAKE_SYSTEM_NAME} STREQUAL "iOS")
		set( LOO_VULKAN_DEFINITIONS "${LOO_VULKAN_DEFINITIONS}" "VK_USE_PLATFORM_IOS_MVK=1" )

	elseif (WIN32 OR ${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
		set( LOO_VULKAN_DEFINITIONS "${LOO_VULKAN_DEFINITIONS}" "VK_USE_PLATFORM_WIN32_KHR=1" )
		set( LOO_VULKAN_DEFINITIONS "${LOO_VULKAN_DEFINITIONS}" "NOMINMAX" "NOMCX" "NOIME" "NOSERVICE" "WIN32_LEAN_AND_MEAN" )
	endif ()
endif ()


add_library( "Vulkan-lib" INTERFACE )
target_include_directories( "Vulkan-lib" INTERFACE "${Vulkan_INCLUDE_DIRS}" )
target_compile_definitions( "Vulkan-lib" INTERFACE "${LOO_VULKAN_DEFINITIONS}" )
