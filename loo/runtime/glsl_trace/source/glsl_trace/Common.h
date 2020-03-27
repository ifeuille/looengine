
#pragma once


#include "glsl_trace/ShaderTrace.h"
#if defined(LOO_ENABLE_GLSLANG)
#include "global/global.h"
#else
//#	undef NDEBUG
#	include <assert.h>

#	define OUT
#	define INOUT
# ifdef _MSC_VER
#	define not					!
#	define and					&&
#	define or					||
# endif
#	define CHECK_ERR( _expr_ )	{if (not (_expr_)) { assert(!(#_expr_)); return 0; } }
#	define RETURN_ERR( _msg_ )	{ assert(!(#_msg_)); return 0; }
#	define CHECK( _expr_ )		{ assert(_expr_); }
#	define ASSERT( _expr_ )		{ assert(_expr_); }
#endif
