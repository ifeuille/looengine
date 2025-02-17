
#include "global/stream/filestream.h"
#include "global/template/externalstring.h"
#include "global/utils/log.h"

#ifdef LOO_PLATFORM_WINDOWS
#	define fread	_fread_nolock
#	define fwrite	_fwrite_nolock
#	define fflush	_fflush_nolock
#	define fclose	_fclose_nolock
#	define ftell	_ftelli64_nolock
#	define fseek	_fseeki64_nolock
#endif

#if defined(LOO_PLATFORM_LINUX)
#	define fseek	fseeko
#	define ftell	ftello
#endif
#if defined(LOO_PLATFORM_LINUX) or defined(LOO_PLATFORM_ANDROID)
#   define fopen_s( _outFile_, _name_, _mode_ ) (*_outFile_=fopen(_name_, _mode_))
#endif


namespace loo
{

	/*
	=================================================
		constructor
	=================================================
	*/
	FileRStream::FileRStream (nonstd::string_view filename)
	{
		fopen_s (OUT &_file, filename.data (), "rb");

		if (_file)
			_fileSize = _GetSize ();
		else
			utils::slog.i << "Can't open file: \"" << filename.data() << '"' << utils::io::endl;
	}

	FileRStream::FileRStream (const char *filename) : FileRStream{ nonstd::string_view{filename} }
	{}

	FileRStream::FileRStream (const std::string &filename) : FileRStream( nonstd::string_view(filename) )
	{}

	/*
	=================================================
		constructor
	=================================================
	*/

	FileRStream::FileRStream (const fs::path &path)
	{
#	ifdef LOO_PLATFORM_WINDOWS
		_wfopen_s (OUT &_file, path.c_str (), L"rb");
#	else
		fopen_s (OUT &_file, path.c_str (), "rb");
#	endif

		if (_file)
			_fileSize = _GetSize ();
		else
			LOO_LOGI ("Can't open file: \"" << path.string () << '"');
	}


	/*
	=================================================
		destructor
	=================================================
	*/
	FileRStream::~FileRStream ()
	{
		if (_file)
			fclose (_file);
	}

	/*
	=================================================
		_GetSize
	=================================================
	*/
	BytesU  FileRStream::_GetSize () const
	{
		ASSERT (IsOpen ());

		const int64_t	curr = ftell (_file);
		CHECK (fseek (_file, 0, SEEK_END) == 0);

		const int64_t	size = ftell (_file);
		CHECK (fseek (_file, curr, SEEK_SET) == 0);

		return BytesU (uint64_t (size));
	}

	/*
	=================================================
		SeekSet
	=================================================
	*/
	bool  FileRStream::SeekSet (BytesU pos)
	{
		ASSERT (IsOpen ());

		if (pos == _position)
			return true;

		_position = std::min (pos, _fileSize);

		return (fseek (_file, int64_t (pos), SEEK_SET) == 0);
	}

	/*
	=================================================
		Read2
	=================================================
	*/
	BytesU  FileRStream::Read2 (OUT void *buffer, BytesU size)
	{
		ASSERT (IsOpen ());

		BytesU	readn{ fread (buffer, 1, size_t (size), _file) };

		_position += readn;

		return readn;
	}
	//-----------------------------------------------------------------------------



	/*
	=================================================
		constructor
	=================================================
	*/
	FileWStream::FileWStream (nonstd::string_view filename)
	{
		fopen_s (OUT &_file, filename.data (), "wb");

		if (not _file)
			utils::slog.i << "Can't open file: \"" << filename.data () << '"' << utils::io::endl;
	}

	FileWStream::FileWStream (const char *filename) : FileWStream{ nonstd::string_view{filename} }
	{}

	FileWStream::FileWStream (const std::string &filename) : FileWStream( nonstd::string_view(filename))
	{}

	/*
	=================================================
		constructor
	=================================================
	*/
	FileWStream::FileWStream (const fs::path &path)
	{
#	ifdef LOO_PLATFORM_WINDOWS
		_wfopen_s (OUT &_file, path.c_str (), L"wb");
#	else
		fopen_s (OUT &_file, path.c_str (), "wb");
#	endif

		if (not _file)
			utils::slog.i << "Can't open file: \"" << path.string().c_str() << '"' << utils::io::endl;
	}

	/*
	=================================================
		destructor
	=================================================
	*/
	FileWStream::~FileWStream ()
	{
		if (_file)
			fclose (_file);
	}

	/*
	=================================================
		Position
	=================================================
	*/
	BytesU  FileWStream::Position () const
	{
		ASSERT (IsOpen ());

		return BytesU (uint64_t (ftell (_file)));
	}

	/*
	=================================================
		Size
	=================================================
	*/
	BytesU  FileWStream::Size () const
	{
		ASSERT (IsOpen ());

		const int64_t	curr = ftell (_file);
		CHECK (fseek (_file, 0, SEEK_END) == 0);

		const int64_t	size = ftell (_file);
		CHECK (fseek (_file, curr, SEEK_SET) == 0);

		return BytesU (uint64_t (size));
	}

	/*
	=================================================
		Write2
	=================================================
	*/
	BytesU  FileWStream::Write2 (const void *buffer, BytesU size)
	{
		ASSERT (IsOpen ());

		return BytesU (fwrite (buffer, 1, size_t (size), _file));
	}

	/*
	=================================================
		Flush
	=================================================
	*/
	void  FileWStream::Flush ()
	{
		ASSERT (IsOpen ());

		CHECK (fflush (_file) == 0);
	}


}
