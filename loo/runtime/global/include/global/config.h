#ifndef LOO_CORE_CONFIG_HPP
#define LOO_CORE_CONFIG_HPP

#if !defined(__cplusplus)
#error C++ compiler required
#endif

#if defined(DEBUG)|defined(_DEBUG)
#define LOO_DEBUG 1
#endif

#define LOO_STRINGIZE(s) LOO_DO_STRINGIZE(s)
#define LOO_DO_STRINGIZE(s) #s

#define LOO_JOIN(X,Y) LOO_DO_JOIN(X,Y)
#define LOO_DO_JOIN(X, Y) LOO_DO_JOIN2(X, Y)
#define LOO_DO_JOIN2(X, Y) X##Y


#ifndef LOO_CODE_ANALYZER
#define STRUCT_OFFSET( struc, member )	offsetof(struc, member)
#else
#define STRUCT_OFFSET( struc, member )	__builtin_offsetof(struc, member)
#endif

#define STARTING_BUFFER_SIZE	512
#define STRING_BUFFER_SIZE_BIG 4096


#define LOO_MAKE_VERSION(major, minor, patch) \
    (((major) << 22) | ((minor) << 12) | (patch))
#define LOO_VERSION_MAJOR(version) ((std::uint32_t)(version) >> 22)
#define LOO_VERSION_MINOR(version) (((std::uint32_t)(version) >> 12) & 0x3ff)
#define LOO_VERSION_PATCH(version) ((std::uint32_t)(version) & 0xfff)
// name and version
#define LOO_ENGINE_NAME  "LooEngine"

//current api version
#define LOO_VERSION LOO_MAKE_VERSION(1,0,0)

//major-minor
#define LOO_VERSION_1_0 1
#define LOO_API_VERSION_1_0 LOO_MAKE_VERSION(1,0,0);
#define LOO_VERSION_STRING "1.0.0"

#define FG_FAST_HASH 0

#ifndef null
#	define null				nullptr
#endif



#endif //LOO_CORE_CONFIG_HPP