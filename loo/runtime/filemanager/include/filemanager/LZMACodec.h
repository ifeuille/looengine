
#ifndef LE_CORE_LZMA_CODEC_HPP
#define LE_CORE_LZMA_CODEC_HPP

#pragma once
#include "filemanager/dllexporter.h"
#include "global/container/arrayref.h"
#include "global/extstd/noncopyable.h"
#include "filemanager/residentifier.h"

namespace loo
{
	namespace fm
	{
		class FILEMANAGER_EXPORT LZMACodec : loo::noncopyable
		{
		public:
			LZMACodec ( );
			~LZMACodec ( );

			uint64_t Encode ( std::ostream& os, ResIdentifierPtr const & res, uint64_t len );
			uint64_t Encode ( std::ostream& os, loo::global::ArrayRef<uint8_t> input );
			void Encode ( std::vector<uint8_t>& output, ResIdentifierPtr const & res, uint64_t len );
			void Encode ( std::vector<uint8_t>& output, loo::global::ArrayRef<uint8_t> input );

			uint64_t Decode ( std::ostream& os, ResIdentifierPtr const & res, uint64_t len, uint64_t original_len );
			uint64_t Decode ( std::ostream& os, loo::global::ArrayRef<uint8_t> input, uint64_t original_len );
			void Decode ( std::vector<uint8_t>& output, ResIdentifierPtr const & res, uint64_t len, uint64_t original_len );
			void Decode ( std::vector<uint8_t>& output, loo::global::ArrayRef<uint8_t> input, uint64_t original_len );
			void Decode ( void* output, loo::global::ArrayRef<uint8_t> input, uint64_t original_len );
		};
	}
}

#endif		// LE_CORE_LZMA_CODEC_HPP
