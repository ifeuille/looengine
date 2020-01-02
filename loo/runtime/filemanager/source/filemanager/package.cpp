#define INITGUID
#include "filemanager/package.h"
#include "global/global.h"
#include "global/container/comptr.h"
#include "filemanager/residentifier.h"
#include "global/utlis.h"
#include <CPP/Common/MyWindows.h>
#include <algorithm>
#include <sstream>
#include <string>
#include <assert.h>
#if defined(LOO_COMPILER_CLANGC2)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable" // Ignore unused variable (mpl_assertion_in_line_xxx) in boost
#endif
//#include <boost/algorithm/string/predicate.hpp>
#if defined(LOO_COMPILER_CLANGC2)
#pragma clang diagnostic pop
#endif

#include <CPP/7zip/Archive/IArchive.h>

#include "Streams.h"
#include "ArchiveExtractCallback.h"
#include "ArchiveOpenCallback.h"
#include <string>
#include "modulemanager/dllloader.h"

#ifndef WINAPI
#ifdef _MSC_VER
#define WINAPI __stdcall
#else
#define WINAPI
#endif
#endif
#ifndef TMSG
#define TMSG(msg)		{ throw std::runtime_error(msg); }
#endif
#ifndef TIFHR
#define TIFHR(x) {if (static_cast<HRESULT>(x) < 0)TMSG(std::string(__FILE__)+":"+std::to_string(__LINE__));}
#endif

namespace
{
	using namespace loo::fm;

	// {23170F69-40C1-278A-1000-000110070000}
	DEFINE_GUID (CLSID_CFormat7z,
		0x23170F69, 0x40C1, 0x278A, 0x10, 0x00, 0x00, 0x01, 0x10, 0x07, 0x00, 0x00);

	typedef loo::uint32 (WINAPI *CreateObjectFunc)(const GUID* clsID, const GUID* interfaceID, void** outObject);

	HRESULT GetArchiveItemPath (std::shared_ptr<IInArchive> const & archive, uint32_t index, std::string& result)
	{
		PROPVARIANT prop;
		prop.vt = VT_EMPTY;
		TIFHR (archive->GetProperty (index, kpidPath, &prop));
		switch (prop.vt)
		{
		case VT_BSTR:
			loo::global::Convert (result, prop.bstrVal);
			return S_OK;

		case VT_EMPTY:
			result.clear ();
			return S_OK;

		default:
			return E_FAIL;
		}
	}

	HRESULT IsArchiveItemFolder (std::shared_ptr<IInArchive> const & archive, uint32_t index, bool &result)
	{
		PROPVARIANT prop;
		prop.vt = VT_EMPTY;
		TIFHR (archive->GetProperty (index, kpidIsDir, &prop));
		switch (prop.vt)
		{
		case VT_BOOL:
			result = (prop.boolVal != VARIANT_FALSE);
			return S_OK;

		case VT_EMPTY:
			result = false;
			return S_OK;

		default:
			return E_FAIL;
		}
	}

	class SevenZipLoader
	{
	public:
		static SevenZipLoader& Instance ()
		{
			static SevenZipLoader ret;
			return ret;
		}

		HRESULT CreateObject (const GUID* clsID, const GUID* interfaceID, void** outObject)
		{
			return createObjectFunc_ (clsID, interfaceID, outObject);
		}

	private:
		SevenZipLoader ()
		{
			//TODO: 验证 7z dll是否能成功加载
			dll_loader_.Load (DLL_PREFIX "7zxa" DLL_SUFFIX);

			createObjectFunc_ = (CreateObjectFunc)dll_loader_.GetProcAddress ("CreateObject");

			assert (createObjectFunc_);
		}

	private:
		loo::DllLoader dll_loader_;
		CreateObjectFunc createObjectFunc_;
	};
}

namespace loo
{
	namespace fm
	{
		Package::Package (ResIdentifierPtr const & archive_is)
			: Package (archive_is, "")
		{
		}

		Package::Package (ResIdentifierPtr const & archive_is, nonstd::string_view password)
			: archive_is_ (archive_is), password_ (password)
		{
			assert (archive_is);

			{
				IInArchive* tmp;
				if (SevenZipLoader::Instance ().CreateObject (&CLSID_CFormat7z, &IID_IInArchive, reinterpret_cast<void**>(&tmp)) < 0)
				{
					throw std::runtime_error ("Package::Package SevenZipLoader::Instance ().CreateObject failed");
				}
				archive_ = loo::global::MakeCOMPtr (tmp);
			}

			auto file = loo::global::MakeCOMPtr (new InStream (archive_is));
			auto ocb = loo::global::MakeCOMPtr (new ArchiveOpenCallback (password));
			TIFHR (archive_->Open (file.get (), 0, ocb.get ()));

			TIFHR (archive_->GetNumberOfItems (&num_items_));
		}

		bool Package::Locate (nonstd::string_view extract_file_path)
		{
			uint32_t real_index = this->Find (extract_file_path);
			return (real_index != 0xFFFFFFFF);
		}

		ResIdentifierPtr Package::Extract (nonstd::string_view extract_file_path, nonstd::string_view res_name)
		{
			uint32_t real_index = this->Find (extract_file_path);
			if (real_index != 0xFFFFFFFF)
			{
				auto decoded_file = loo::global::MakeSharedPtr<std::stringstream> ();
				auto out_stream = loo::global::MakeCOMPtr (new OutStream (decoded_file));
				auto ecb = loo::global::MakeCOMPtr (new ArchiveExtractCallback (password_, out_stream));
				TIFHR (archive_->Extract (&real_index, 1, false, ecb.get ()));

				PROPVARIANT prop;
				prop.vt = VT_EMPTY;
				TIFHR (archive_->GetProperty (real_index, kpidMTime, &prop));
				uint64_t mtime;
				if (prop.vt == VT_FILETIME)
				{
					mtime = (static_cast<uint64_t>(prop.filetime.dwHighDateTime) << 32)
						+ prop.filetime.dwLowDateTime;
					mtime -= 116444736000000000ULL;
				}
				else
				{
					mtime = archive_is_->Timestamp ();
				}

				return loo::global::MakeSharedPtr<ResIdentifier> (res_name, mtime, decoded_file);
			}
			return ResIdentifierPtr ();
		}

		uint32_t Package::Find (nonstd::string_view extract_file_path)
		{
			uint32_t real_index = 0xFFFFFFFF;

			for (uint32_t i = 0; i < num_items_; ++i)
			{
				bool is_folder = true;
				TIFHR (IsArchiveItemFolder (archive_, i, is_folder));
				if (!is_folder)
				{
					std::string file_path;
					TIFHR (GetArchiveItemPath (archive_, i, file_path));
					std::replace (file_path.begin (), file_path.end (), '\\', '/');
					if(extract_file_path == file_path)
			/*		if (!boost::algorithm::ilexicographical_compare (extract_file_path, file_path)
						&& !boost::algorithm::ilexicographical_compare (file_path, extract_file_path))*/
					{
						real_index = i;
						break;
					}
				}
			}
			if (real_index != 0xFFFFFFFF)
			{
				PROPVARIANT prop;
				prop.vt = VT_EMPTY;
				TIFHR (archive_->GetProperty (real_index, kpidIsAnti, &prop));
				if ((VT_BOOL == prop.vt) && (VARIANT_FALSE == prop.boolVal))
				{
					prop.vt = VT_EMPTY;
					TIFHR (archive_->GetProperty (real_index, kpidPosition, &prop));
					if (prop.vt != VT_EMPTY)
					{
						if ((prop.vt != VT_UI8) || (prop.uhVal.QuadPart != 0))
						{
							real_index = 0xFFFFFFFF;
						}
					}
				}
				else
				{
					real_index = 0xFFFFFFFF;
				}
			}

			return real_index;
		}
	}

}