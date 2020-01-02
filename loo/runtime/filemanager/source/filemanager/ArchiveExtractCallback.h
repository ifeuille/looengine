#ifndef LE_CORE_ARCHIVE_EXTRACT_CALLBACK_HPP
#define LE_CORE_ARCHIVE_EXTRACT_CALLBACK_HPP


#include <atomic>
#include <string>

#include <CPP/7zip/Archive/IArchive.h>
#include <CPP/7zip/IPassword.h>
#include "global/extstd/noncopyable.h"
#include "global/extstd/string_view.h"

namespace loo
{

	namespace fm
	{
		class ArchiveExtractCallback : loo::noncopyable, public IArchiveExtractCallback, public ICryptoGetTextPassword
		{
		public:
			// IUnknown
			STDMETHOD_ ( ULONG, AddRef )();
			STDMETHOD_ ( ULONG, Release )();
			STDMETHOD ( QueryInterface )(REFGUID iid, void** out_object);

			// IProgress
			STDMETHOD ( SetTotal )(UInt64 size);
			STDMETHOD ( SetCompleted )(UInt64 const * complete_value);

			// IExtractCallBack
			STDMETHOD ( GetStream )(UInt32 index, ISequentialOutStream** out_stream, Int32 ask_extract_mode);
			STDMETHOD ( PrepareOperation )(Int32 ask_extract_mode);
			STDMETHOD ( SetOperationResult )(Int32 operation_result);

			// ICryptoGetTextPassword
			STDMETHOD ( CryptoGetTextPassword )(BSTR* password);

		public:
			ArchiveExtractCallback ( nonstd::string_view pw, std::shared_ptr<ISequentialOutStream> const & out_file_stream );
			virtual ~ArchiveExtractCallback ( ) = default;

		private:
			std::atomic<int32_t> ref_count_ = 1;

			bool password_is_defined_;
			std::wstring password_;

			std::shared_ptr<ISequentialOutStream> out_file_stream_;
		};
	}
}

#endif		// LE_CORE_ARCHIVE_EXTRACT_CALLBACK_HPP
