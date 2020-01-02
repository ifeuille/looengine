#ifndef LE_CORE_PACKAGE_HPP
#define LE_CORE_PACKAGE_HPP
#include "global/global.h"
#include "filemanager/dllexporter.h"
#include "global/extstd/string_view.h"
#include "filemanager/residentifier.h"

struct IInArchive;

namespace loo
{
	namespace fm
	{
		class FILEMANAGER_EXPORT Package
		{
		public:
			explicit Package (ResIdentifierPtr const & archive_is);
			Package (ResIdentifierPtr const & archive_is, nonstd::string_view password);

			bool Locate (nonstd::string_view extract_file_path);
			ResIdentifierPtr Extract (nonstd::string_view extract_file_path, nonstd::string_view res_name);

			ResIdentifier* ArchiveStream () const
			{
				return archive_is_.get ();
			}

		private:
			uint32_t Find (nonstd::string_view extract_file_path);

		private:
			ResIdentifierPtr archive_is_;

			std::shared_ptr<IInArchive> archive_;
			std::string password_;

			uint32_t num_items_;
		};

		typedef std::shared_ptr<Package> PackagePtr;
	}
}

#endif		// LE_CORE_PACKAGE_HPP
