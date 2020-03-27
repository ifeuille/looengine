#include "global/global.h"
#include "filemanager/LZMACodec.h"
#include <cstring>
#include <mutex>

#include <C/LzmaLib.h>
#include "filemanager/residentifier.h"
#include "modulemanager/dllloader.h"
#include "global/math/math.h"

namespace
{
	using namespace loo::fm;

	std::mutex singleton_mutex;

	typedef int (MY_STD_CALL *LzmaCompressFunc)(unsigned char* dest, size_t* destLen, unsigned char const * src, size_t srcLen,
		unsigned char* outProps, size_t* outPropsSize, /* *outPropsSize must be = 5 */
		int level,      /* 0 <= level <= 9, default = 5 */
		unsigned int dictSize,  /* default = (1 << 24) */
		int lc,        /* 0 <= lc <= 8, default = 3  */
		int lp,        /* 0 <= lp <= 4, default = 0  */
		int pb,        /* 0 <= pb <= 4, default = 2  */
		int fb,        /* 5 <= fb <= 273, default = 32 */
		int numThreads /* 1 or 2, default = 2 */);
	typedef int (MY_STD_CALL *LzmaUncompressFunc)(unsigned char* dest, size_t* destLen, unsigned char const * src, SizeT* srcLen,
		unsigned char const * props, size_t propsSize);

	class LZMALoader
	{
	public:
		static LZMALoader& Instance ( )
		{
			if (!instance_)
			{
				std::lock_guard<std::mutex> lock ( singleton_mutex );
				if (!instance_)
				{
					instance_ = loo::global::MakeUniquePtr<LZMALoader> ( );
				}
			}
			return *instance_;
		}

		int LzmaCompress ( unsigned char* dest, size_t* destLen, unsigned char const * src, size_t srcLen,
			unsigned char* outProps, size_t* outPropsSize, int level, unsigned int dictSize,
			int lc, int lp, int pb, int fb, int numThreads )
		{
			return lzma_compress_func_ ( dest, destLen, src, srcLen, outProps, outPropsSize, level, dictSize,
				lc, lp, pb, fb, numThreads );
		}
		int LzmaUncompress ( unsigned char* dest, size_t* destLen, unsigned char const * src, SizeT* srcLen,
			unsigned char const * props, size_t propsSize )
		{
			return lzma_uncompress_func_ ( dest, destLen, src, srcLen, props, propsSize );
		}

		LZMALoader ( )
		{
#if !(defined(LOO_PLATFORM_ANDROID) || defined(LOO_PLATFORM_IOS))
			dll_loader_.Load (DLL_PREFIX "LZMA" DLL_SUFFIX);

			lzma_compress_func_ = (LzmaCompressFunc)dll_loader_.GetProcAddress ( "LzmaCompress" );
			lzma_uncompress_func_ = (LzmaUncompressFunc)dll_loader_.GetProcAddress ( "LzmaUncompress" );
#else
			lzma_compress_func_ = ::LzmaCompress;
			lzma_uncompress_func_ = ::LzmaUncompress;
#endif

			assert ( lzma_compress_func_ );
			assert ( lzma_uncompress_func_ );
		}

	private:
#if !(defined(LOO_PLATFORM_ANDROID) || defined(LOO_PLATFORM_IOS))
		loo::DllLoader dll_loader_;
#endif
		LzmaCompressFunc lzma_compress_func_;
		LzmaUncompressFunc lzma_uncompress_func_;

		static std::unique_ptr<LZMALoader> instance_;
	};
	std::unique_ptr<LZMALoader> LZMALoader::instance_;
}

namespace loo
{
	namespace fm
	{
		LZMACodec::LZMACodec ( )
		{
		}

		LZMACodec::~LZMACodec ( )
		{
		}

		uint64_t LZMACodec::Encode ( std::ostream& os, ResIdentifierPtr const & is, uint64_t len )
		{
			auto input = loo::global::MakeUniquePtr<uint8_t[]> ( static_cast<size_t>(len) );
			is->read ( input.get ( ), static_cast<size_t>(len) );

			std::vector<uint8_t> output;
			this->Encode ( output, loo::global::MakeArrayRef ( input.get ( ), len ) );
			os.write ( reinterpret_cast<char*>(&output[0]), output.size ( ) * sizeof ( output[0] ) );

			return output.size ( );
		}

		uint64_t LZMACodec::Encode ( std::ostream& os, loo::global::ArrayRef<uint8_t> input )
		{
			std::vector<uint8_t> output;
			this->Encode ( output, input );
			os.write ( reinterpret_cast<char*>(&output[0]), output.size ( ) * sizeof ( output[0] ) );
			return output.size ( );
		}

		void LZMACodec::Encode ( std::vector<uint8_t>& output, ResIdentifierPtr const & is, uint64_t len )
		{
			auto input = loo::global::MakeUniquePtr<uint8_t[]> ( static_cast<size_t>(len) );
			is->read ( input.get ( ), static_cast<size_t>(len) );

			this->Encode ( output, loo::global::MakeArrayRef ( input.get ( ), len ) );
		}

		void LZMACodec::Encode ( std::vector<uint8_t>& output, loo::global::ArrayRef<uint8_t> input )
		{
			SizeT out_len = static_cast<SizeT>(loo::math::Max ( input.size ( ) * 11 / 10, static_cast<size_t>(32) ));
			output.resize ( LZMA_PROPS_SIZE + out_len );
			SizeT out_props_size = LZMA_PROPS_SIZE;
			LZMALoader::Instance ( ).LzmaCompress ( &output[LZMA_PROPS_SIZE], &out_len,
				static_cast<Byte const *>(input.data ( )), static_cast<SizeT>(input.size ( )),
				&output[0], &out_props_size, 5, loo::math::Min<uint32_t> ( static_cast<uint32_t>(input.size ( )), 1UL << 24 ), 3, 0, 2, 32, 1 );

			output.resize ( LZMA_PROPS_SIZE + out_len );
		}

		uint64_t LZMACodec::Decode ( std::ostream& os, ResIdentifierPtr const & is, uint64_t len, uint64_t original_len )
		{
			auto in_data = loo::global::MakeUniquePtr<uint8_t[]> ( static_cast<size_t>(len) );
			is->read ( in_data.get ( ), static_cast<size_t>(len) );

			std::vector<uint8_t> output;
			this->Decode ( output, loo::global::MakeArrayRef ( in_data.get ( ), len ), original_len );

			os.write ( reinterpret_cast<char*>(&output[0]), static_cast<std::streamsize>(output.size ( )) );

			return output.size ( );
		}

		uint64_t LZMACodec::Decode ( std::ostream& os, loo::global::ArrayRef<uint8_t> input, uint64_t original_len )
		{
			std::vector<uint8_t> output;
			this->Decode ( output, input, original_len );

			os.write ( reinterpret_cast<char*>(&output[0]), static_cast<std::streamsize>(output.size ( )) );

			return output.size ( );
		}

		void LZMACodec::Decode ( std::vector<uint8_t>& output, ResIdentifierPtr const & is, uint64_t len, uint64_t original_len )
		{
			std::vector<uint8_t> in_data ( static_cast<size_t>(len) );
			is->read ( &in_data[0], static_cast<size_t>(len) );

			this->Decode ( output, loo::global::MakeArrayRef ( in_data.data ( ), len ), original_len );
		}

		void LZMACodec::Decode ( std::vector<uint8_t>& output, loo::global::ArrayRef<uint8_t> input, uint64_t original_len )
		{
			output.resize ( static_cast<uint32_t>(original_len) );
			this->Decode ( &output[0], input, original_len );
		}

		void LZMACodec::Decode ( void* output, loo::global::ArrayRef<uint8_t> input, uint64_t original_len )
		{
			uint8_t const * p = static_cast<uint8_t const *>(input.data ( ));

			std::vector<uint8_t> in_data ( static_cast<size_t>(input.size ( )) );
			std::memcpy ( &in_data[0], p, static_cast<std::streamsize>(in_data.size ( )) );

			SizeT s_out_len = static_cast<SizeT>(original_len);

			SizeT s_src_len = static_cast<SizeT>(input.size ( ) - LZMA_PROPS_SIZE);
			int res = LZMALoader::Instance ( ).LzmaUncompress ( static_cast<Byte*>(output), &s_out_len, &in_data[LZMA_PROPS_SIZE], &s_src_len,
				&in_data[0], LZMA_PROPS_SIZE );
			assert( 0 == res );
			LOO_UNUSED (res);
		}
	}
}
