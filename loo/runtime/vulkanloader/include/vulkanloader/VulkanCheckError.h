#pragma once


#if 0 //ndef LOO_DEBUG
#	define VK_CALL( ... )		{ (void)(__VA_ARGS__); }
#	define VK_CHECK( ... )		{ if ((__VA_ARGS__) != VK_SUCCESS) return false; }

#else
#	define VK_CALL( ... ) \
	{ \
		const ::VkResult __vk_err__ = (__VA_ARGS__); \
		::loo::__vk_CheckErrors( __vk_err__, LOO_PRIVATE_TOSTRING( __VA_ARGS__ ), LOO_FUNCTION_NAME, __FILE__, __LINE__ ); \
	}

#	define LOO_PRIVATE_VK_CALL_R( _func_, _ret_, ... ) \
	{ \
		const ::VkResult __vk_err__ = (_func_); \
		if ( not ::loo::__vk_CheckErrors( __vk_err__, LOO_PRIVATE_TOSTRING( _func_ ), LOO_FUNCTION_NAME, __FILE__, __LINE__ ) ) \
			return _ret_; \
	}

#	define VK_CHECK( ... ) \
		LOO_PRIVATE_VK_CALL_R( LOO_PRIVATE_GETARG_0( __VA_ARGS__ ), LOO_PRIVATE_GETARG_1( __VA_ARGS__, ::loo::Default ) )
#endif


namespace loo
{

	bool __vk_CheckErrors (VkResult errCode, const char *vkcall, const char *func, const char *file, int line);
	
}	
