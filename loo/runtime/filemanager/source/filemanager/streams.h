

#ifndef LE_CORE_STREAMS_HPP
#define LE_CORE_STREAMS_HPP

#include <atomic>
#include <fstream>
#include <string>

#include <CPP/7zip/IStream.h>
#include "global/extstd/noncopyable.h"
#include "filemanager/residentifier.h"
namespace loo
{
	namespace fm
	{
		class InStream : loo::noncopyable, public IInStream, public IStreamGetSize
		{
		public:
			// IUnknown
			STDMETHOD_ (ULONG, AddRef)();
			STDMETHOD_ (ULONG, Release)();
			STDMETHOD (QueryInterface)(REFGUID iid, void** out_object);

			// IInStream
			STDMETHOD (Read)(void* data, UInt32 size, UInt32* processed_size);
			STDMETHOD (Seek)(Int64 offset, UInt32 seek_origin, UInt64* new_position);

			// IStreamGetSize
			STDMETHOD (GetSize)(UInt64* size);

		public:
			explicit InStream (ResIdentifierPtr const & is);
			virtual ~InStream () = default;

		private:
			std::atomic<int32_t> ref_count_ = 1;

			ResIdentifierPtr is_;
			uint64_t stream_size_ = 0;
		};

		class OutStream : loo::noncopyable, public IOutStream
		{
		public:
			// IUnknown
			STDMETHOD_ (ULONG, AddRef)();
			STDMETHOD_ (ULONG, Release)();
			STDMETHOD (QueryInterface)(REFGUID iid, void** out_object);

			// IOutStream
			STDMETHOD (Write)(void const * data, UInt32 size, UInt32* processed_size);
			STDMETHOD (Seek)(Int64 offset, UInt32 seek_origin, UInt64* new_position);
			STDMETHOD (SetSize)(UInt64 new_size);

		public:
			explicit OutStream (std::shared_ptr<std::ostream> const & os);
			virtual ~OutStream () = default;

		private:
			std::atomic<int32_t> ref_count_ = 1;

			std::shared_ptr<std::ostream> os_;
		};
	}
}

#endif
