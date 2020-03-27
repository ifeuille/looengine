
option(LOO_BUILD_TESTS "Build Tests" ON)
option(LOO_BUILD_PROJECTS "Build Projects" ON)
option(LOO_BUILD_SHARED "Build in Shared Mode" ON)
option(LOO_EXTERNALS_USE_STABLE_VERSIONS "Use Stable" ON)
option(LOO_ENABLE_GLSLANG "Use glslang" ON)


set( LOO_ENABLE_STDALLOC OFF CACHE BOOL "custom std allocators (optional)" )
set( LOO_ENABLE_GLSLANG ON CACHE BOOL "use glslang (optional, required for glsl compilation)" )
set( LOO_ENABLE_VMA ON CACHE BOOL "use Vulkan Memory Allocator (required)" )
set( LOO_ENABLE_OPENVR ON CACHE BOOL "use OpenVR (optional)" )
set( LOO_ENABLE_SIMPLE_COMPILER_OPTIONS OFF CACHE BOOL "use simplified compiler settings if you have problem with it" )
set( LOO_EXTERNALS_USE_STABLE_VERSIONS ON CACHE BOOL "use last stable version instead of master branch" )
set( LOO_EXTERNALS_USE_PREBUILD OFF CACHE BOOL "use stable prebuild libraries" )

