#include "global/utlis.h"
#include <CPP/Common/MyWindows.h>
#include "ArchiveOpenCallback.h"

namespace loo
{
	namespace fm
	{
		ArchiveOpenCallback::ArchiveOpenCallback ( nonstd::string_view pw )
			: password_is_defined_ ( !pw.empty ( ) )
		{
			loo::global::Convert ( password_, pw );
		}

		STDMETHODIMP_ ( ULONG ) ArchiveOpenCallback::AddRef ( )
		{
			++ref_count_;
			return ref_count_;
		}

		STDMETHODIMP_ ( ULONG ) ArchiveOpenCallback::Release ( )
		{
			--ref_count_;
			if (0 == ref_count_)
			{
				delete this;
				return 0;
			}
			return ref_count_;
		}

		STDMETHODIMP ArchiveOpenCallback::QueryInterface ( REFGUID iid, void** out_object )
		{
			if (IID_ICryptoGetTextPassword == iid)
			{
				*out_object = static_cast<ICryptoGetTextPassword*>(this);
				this->AddRef ( );
				return S_OK;
			}
			else if (IID_IArchiveOpenCallback == iid)
			{
				*out_object = static_cast<IArchiveOpenCallback*>(this);
				this->AddRef ( );
				return S_OK;
			}
			else
			{
				return E_NOINTERFACE;
			}
		}

		STDMETHODIMP ArchiveOpenCallback::SetTotal ( UInt64 const * files, UInt64 const * bytes )
		{
			LOO_UNUSED ( files );
			LOO_UNUSED ( bytes );
			return S_OK;
		}

		STDMETHODIMP ArchiveOpenCallback::SetCompleted ( UInt64 const * files, UInt64 const * bytes )
		{
			LOO_UNUSED ( files );
			LOO_UNUSED ( bytes );
			return S_OK;
		}

		STDMETHODIMP ArchiveOpenCallback::CryptoGetTextPassword ( BSTR* password )
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
