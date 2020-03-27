
#include "global/stream/stream.h"
#include "global/template/externalstring.h"


namespace loo
{

	/*
	=================================================
		Read
	=================================================
	*/
	bool  RStream::Read (void *buffer, BytesU size)
	{
		return Read2 (buffer, size) == size;
	}

	/*
	=================================================
		Read
	=================================================
	*/
	bool  RStream::Read (size_t length, OUT std::string &str)
	{
		str.resize (length);

		BytesU	expected_size = BytesU::SizeOf (str[0]) * str.length ();
		BytesU	current_size = Read2 (&str[0], expected_size);

		str.resize (size_t (current_size / sizeof (str[0])));

		return str.length () == length;
	}

	/*
	=================================================
		Read
	=================================================
	*/
	bool  RStream::Read (size_t count, OUT std::vector<uint8_t> &buf)
	{
		buf.resize (count);

		BytesU	expected_size = BytesU::SizeOf (buf[0]) * buf.size ();
		BytesU	current_size = Read2 (buf.data (), expected_size);

		buf.resize (size_t (current_size / sizeof (buf[0])));

		return buf.size () == count;
	}
	//-----------------------------------------------------------------------------



	/*
	=================================================
		Write
	=================================================
	*/
	bool  WStream::Write (const void *buffer, BytesU size)
	{
		return Write2 (buffer, size) == size;
	}

	/*
	=================================================
		Write
	=================================================
	*/
	bool  WStream::Write (nonstd::string_view str)
	{
		if (str.empty ())
			return true;

		BytesU	size = SizeOf<nonstd::string_view::value_type> * str.length ();

		return Write2 (str.data (), size) == size;
	}

	/*
	=================================================
		Write
	=================================================
	*/
	bool  WStream::Write (ArrayView<uint8_t> buf)
	{
		const BytesU	size = BytesU::SizeOf (buf[0]) * buf.size ();

		return Write2 (buf.data (), size) == size;
	}

}
