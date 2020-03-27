

#pragma once


#define PRIVATE_COMP_RETURN_ERR( _text_, _ret_ ) \
		{if ( not loo::EnumEq( _compilerFlags, loo::vkfg::EShaderCompilationFlags::Quiet )) { \
			LOO_LOGE( _text_ ); \
		}else{ \
			LOO_LOGI( _text_ ); \
		}return (_ret_); \
		}

#define COMP_RETURN_ERR( ... ) \
		PRIVATE_COMP_RETURN_ERR( LOO_PRIVATE_GETARG_0( __VA_ARGS__ ),LOO_PRIVATE_GETARG_1( __VA_ARGS__, ::loo::Default ) )


#define PRIVATE_COMP_CHECK_ERR( _expr_, _ret_ ) \
		{if (( _expr_ )) {}\
		 else \
			PRIVATE_COMP_RETURN_ERR( LOO_PRIVATE_TOSTRING(_expr_), (_ret_) ) \
		}

#define COMP_CHECK_ERR( ... ) \
		PRIVATE_COMP_CHECK_ERR( LOO_PRIVATE_GETARG_0( __VA_ARGS__ ), LOO_PRIVATE_GETARG_1( __VA_ARGS__, ::loo::Default ) )

