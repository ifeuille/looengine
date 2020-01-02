
#ifndef LE_CORE_ARCHIVE_OPEN_CALLBACK_HPP
#define LE_CORE_ARCHIVE_OPEN_CALLBACK_HPP


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
		class ArchiveOpenCallback : loo::noncopyable, public IArchiveOpenCallback, public ICryptoGetTextPassword
		{
		public:
			// IUnknown
			STDMETHOD_ ( ULONG, AddRef )();
			STDMETHOD_ ( ULONG, Release )();
			STDMETHOD ( QueryInterface )(REFGUID iid, void** out_object);

			// IArchiveOpenCallback
			STDMETHOD ( SetTotal )(UInt64 const * files, UInt64 const * bytes);
			STDMETHOD ( SetCompleted )(UInt64 const * files, UInt64 const * bytes);

			// ICryptoGetTextPassword
			STDMETHOD ( CryptoGetTextPassword )(BSTR *password);

		public:
			explicit ArchiveOpenCallback ( nonstd::string_view pw );
			virtual ~ArchiveOpenCallback ( ) = default;

		private:
			std::atomic<int32_t> ref_count_ = 1;

			bool password_is_defined_ = false;
			std::wstring password_;
		};
	}
}

#endif		// LE_CORE_ARCHIVE_OPEN_CALLBACK_HPP
