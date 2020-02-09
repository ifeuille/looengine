include( CheckCXXSourceCompiles )

set( CMAKE_REQUIRED_FLAGS "-std=c++14" )

message( STATUS "Run compiler tests with flags: ${CMAKE_REQUIRED_FLAGS}" )

set( LOO_COMPILER_DEFINITIONS "" )
set( LOO_LINK_LIBRARIES "" )


#------------------------------------------------------------------------------
check_cxx_source_compiles(
	"#include <new>
	static constexpr size_t Align = std::hardware_destructive_interference_size;
	int main () {
		return 0;
	}"
	STD_CACHELINESIZE_SUPPORTED )

if (STD_CACHELINESIZE_SUPPORTED)
	set( LOO_COMPILER_DEFINITIONS "${LOO_COMPILER_DEFINITIONS}" "LOO_CACHE_LINE=std::hardware_destructive_interference_size" )
else ()
	set( LOO_COMPILER_DEFINITIONS "${LOO_COMPILER_DEFINITIONS}" "LOO_CACHE_LINE=64" ) # TODO
endif ()

#------------------------------------------------------------------------------
check_cxx_source_compiles(
	"#include <barrier>
	int main () {
		std::barrier  temp;
		return 0;
	}"
	STD_BARRIER_SUPPORTED )

if (STD_BARRIER_SUPPORTED)
	set( LOO_COMPILER_DEFINITIONS "${LOO_COMPILER_DEFINITIONS}" "LOO_STD_BARRIER" )
endif ()

#------------------------------------------------------------------------------
check_cxx_source_compiles(
	"#include <functional>
	int main () {
		char buffer[128] = {};
		(void)(std::_Hash_array_representation( reinterpret_cast<const unsigned char*>(buffer), std::size(buffer) ));
		return 0;
	}"
	HAS_HASHFN_HashArrayRepresentation )

if (HAS_HASHFN_HashArrayRepresentation)
	set( LOO_COMPILER_DEFINITIONS "${LOO_COMPILER_DEFINITIONS}" "LOO_HAS_HASHFN_HashArrayRepresentation" )
endif ()

#------------------------------------------------------------------------------
check_cxx_source_compiles(
	"#include <functional>
	int main () {
		char buffer[128] = {};
		(void)(std::__murmur2_or_cityhash<size_t>()( buffer, std::size(buffer) ));
		return 0;
	}"
	HAS_HASHFN_Murmur2OrCityhash )

if (HAS_HASHFN_Murmur2OrCityhash)
	set( LOO_COMPILER_DEFINITIONS "${LOO_COMPILER_DEFINITIONS}" "LOO_HAS_HASHFN_Murmur2OrCityhash" )
endif ()

#------------------------------------------------------------------------------
check_cxx_source_compiles(
	"#include <functional>
	int main () {
		char buffer[128] = {};
		(void)(std::_Hash_bytes( buffer, std::size(buffer), 0 ));
		return 0;
	}"
	HAS_HASHFN_HashBytes )

if (HAS_HASHFN_HashBytes)
	set( LOO_COMPILER_DEFINITIONS "${LOO_COMPILER_DEFINITIONS}" "LOO_HAS_HASHFN_HashBytes" )
endif ()

#------------------------------------------------------------------------------
check_cxx_source_compiles(
	"#include <new>
	static constexpr size_t Align = std::hardware_destructive_interference_size;
	int main () {
		return 0;
	}"
	STD_CACHELINESIZE_SUPPORTED )
if (STD_CACHELINESIZE_SUPPORTED)
	set( LOO_COMPILER_DEFINITIONS "${LOO_COMPILER_DEFINITIONS}" "LOO_CACHE_LINE=std::hardware_destructive_interference_size" )
else ()
	set( LOO_COMPILER_DEFINITIONS "${LOO_COMPILER_DEFINITIONS}" "LOO_CACHE_LINE=64" )
endif ()

message("LOO_CACHE_LINE=${LOO_CACHE_LINE}")
#------------------------------------------------------------------------------

set( CMAKE_REQUIRED_FLAGS "" )
set( LOO_COMPILER_DEFINITIONS "${LOO_COMPILER_DEFINITIONS}" CACHE INTERNAL "" FORCE )
set( LOO_LINK_LIBRARIES "${LOO_LINK_LIBRARIES}" CACHE INTERNAL "" FORCE )

#message( STATUS "Supported features = ${CMAKE_CXX_COMPILE_FEATURES}" )

