
#ifndef LOO_FM_RESIDENTIFIER_HPP
#define LOO_FM_RESIDENTIFIER_HPP
#include "filemanager/dllexporter.h"
#include "global/extstd/string_view.h"
#include <istream>
#include <vector>
#include <string>

namespace loo
{
	namespace fm
	{
		class FILEMANAGER_EXPORT ResIdentifier
		{
		public:
			ResIdentifier (nonstd::string_view name, uint64_t timestamp,
				std::shared_ptr<std::istream> const & is)
				: ResIdentifier (name, timestamp, is, std::shared_ptr<std::streambuf> ())
			{
			}
			ResIdentifier (nonstd::string_view name, uint64_t timestamp,
				std::shared_ptr<std::istream> const & is, std::shared_ptr<std::streambuf> const & streambuf)
				: res_name_ (name), timestamp_ (timestamp), istream_ (is), streambuf_ (streambuf)
			{
			}

			void ResName (nonstd::string_view name)
			{
				res_name_ = std::string (name);
			}
			std::string const & ResName () const
			{
				return res_name_;
			}

			void Timestamp (uint64_t ts)
			{
				timestamp_ = ts;
			}
			uint64_t Timestamp () const
			{
				return timestamp_;
			}

			void read (void* p, size_t size)
			{
				istream_->read (static_cast<char*>(p), static_cast<std::streamsize>(size));
			}

			int64_t gcount () const
			{
				return static_cast<int64_t>(istream_->gcount ());
			}

			void seekg (int64_t offset, std::ios_base::seekdir way)
			{
				istream_->seekg (static_cast<std::istream::off_type>(offset), way);
			}

			int64_t tellg ()
			{
				return static_cast<int64_t>(istream_->tellg ());
			}

			void clear ()
			{
				istream_->clear ();
			}

			operator bool () const
			{
				return !istream_->fail ();
			}

			bool operator!() const
			{
				return istream_->operator!();
			}

			std::istream& input_stream ()
			{
				return *istream_;
			}

		private:
			std::string res_name_;
			uint64_t timestamp_;
			std::shared_ptr<std::istream> istream_;
			std::shared_ptr<std::streambuf> streambuf_;
		};

		typedef std::shared_ptr<ResIdentifier> ResIdentifierPtr;

	}
}

#endif			// _KFL_RESIDENTIFIER_HPP