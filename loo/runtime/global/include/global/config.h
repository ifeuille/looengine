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

#define LOO_FAST_HASH 0

#ifndef null
#	define null				nullptr
#endif

#define LOO_UNUSED(x) (void)(x)


#define DLL_SUFFIX LOO_OUTPUT_SUFFIX "." DLL_EXT_NAME
// helper macro
#define LOO_PRIVATE_GETARG_0( _0_, ... )				_0_
#define LOO_PRIVATE_GETARG_1( _0_, _1_, ... )		_1_
#define LOO_PRIVATE_GETARG_2( _0_, _1_, _2_, ... )	_2_
#define LOO_PRIVATE_GETRAW( _value_ )				_value_
#define LOO_PRIVATE_TOSTRING( ... )					#__VA_ARGS__
#define LOO_PRIVATE_UNITE_RAW( _arg0_, _arg1_ )		LOO_PRIVATE_UNITE( _arg0_, _arg1_ )
#define LOO_PRIVATE_UNITE( _arg0_, _arg1_ )			_arg0_ ## _arg1_


#ifndef STATIC_ASSERT
//#	define STATIC_ASSERT( ... ) \
//		static_assert(	LOO_PRIVATE_GETRAW( LOO_PRIVATE_GETARG_0( __VA_ARGS__ ) ), \
//						LOO_PRIVATE_GETRAW( LOO_PRIVATE_GETARG_1( __VA_ARGS__, LOO_PRIVATE_TOSTRING(__VA_ARGS__) ) ) )
#	define STATIC_ASSERT( v, arg ) \
	static_assert(v, arg);
#endif

#ifdef LOO_DEBUG
#	define LOO_ENABLE_DATA_RACE_CHECK
#else
//#	define LOO_OPTIMAL_MEMORY_ORDER
#endif

#ifndef INOUT
#define INOUT
#endif


#define DECLARE_CPP_NOTHING(NAME) namespace nothing\
{\
	int LOO_PRIVATE_UNITE_RAW (NOTHINGFUNC_,NAME)()\
	{\
		return 0;\
	}\
}

#endif //LOO_CORE_CONFIG_HPP