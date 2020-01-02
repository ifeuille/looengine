#include "global/utlis.h"
#include "ArchiveExtractCallback.h"


namespace loo
{
	namespace fm
	{
		ArchiveExtractCallback::ArchiveExtractCallback (nonstd::string_view pw, std::shared_ptr<ISequentialOutStream> const & out_file_stream )
			: password_is_defined_ ( !pw.empty ( ) ), out_file_stream_ ( out_file_stream )
		{
			loo::global::Convert ( password_, pw );
		}

		STDMETHODIMP_ ( ULONG ) ArchiveExtractCallback::AddRef ( )
		{
			++ref_count_;
			return ref_count_;
		}

		STDMETHODIMP_ ( ULONG ) ArchiveExtractCallback::Release ( )
		{
			--ref_count_;
			if (0 == ref_count_)
			{
				delete this;
				return 0;
			}
			return ref_count_;
		}

		STDMETHODIMP ArchiveExtractCallback::QueryInterface ( REFGUID iid, void** out_object )
		{
			if (IID_ICryptoGetTextPassword == iid)
			{
				*out_object = static_cast<ICryptoGetTextPassword*>(this);
				this->AddRef ( );
				return S_OK;
			}
			else if (IID_IArchiveExtractCallback == iid)
			{
				*out_object = static_cast<IArchiveExtractCallback*>(this);
				this->AddRef ( );
				return S_OK;
			}
			else
			{
				return E_NOINTERFACE;
			}
		}

		STDMETHODIMP ArchiveExtractCallback::SetTotal ( UInt64 size )
		{
			LOO_UNUSED ( size );
			return S_OK;
		}

		STDMETHODIMP ArchiveExtractCallback::SetCompleted ( UInt64 const * complete_value )
		{
			LOO_UNUSED ( complete_value );
			return S_OK;
		}

		STDMETHODIMP ArchiveExtractCallback::GetStream ( UInt32 index, ISequentialOutStream** out_stream, Int32 ask_extract_mode )
		{
			LOO_UNUSED ( index );

			enum
			{
				kExtract = 0,
				kTest,
				kSkip,
			};

			if (kExtract == ask_extract_mode)
			{
				out_file_stream_->AddRef ( );
				*out_stream = out_file_stream_.get ( );
			}
			else
			{
				*out_stream = nullptr;
			}
			return S_OK;
		}

		STDMETHODIMP ArchiveExtractCallback::PrepareOperation ( Int32 ask_extract_mode )
		{
			LOO_UNUSED ( ask_extract_mode );
			return S_OK;
		}

		STDMETHODIMP ArchiveExtractCallback::SetOperationResult ( Int32 operation_result )
		{
			LOO_UNUSED ( operation_result );
			return S_OK;
		}

		STDMETHODIMP ArchiveExtractCallback::CryptoGetTextPassword ( BSTR* password )
		{
			if (password_is_defined_)
			{
#ifdef LOO_PLATFORM_WINDOWS_DESKTOP
				*password = SysAllocString ( password_.c_str ( ) );
#else
				*password = nullptr;
#endif
				return S_OK;
			}
			else
			{
				return E_ABORT;
			}
		}
	}

}