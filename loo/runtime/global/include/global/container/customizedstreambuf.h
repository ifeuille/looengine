
#ifndef LE_CUSTOMIZEDSTREAMBUF_HPP
#define LE_CUSTOMIZEDSTREAMBUF_HPP

#pragma once

#include <streambuf>
#include <vector>
#include <string>
#include "global/extstd/noncopyable.h"

namespace loo
{
	class MemInputStreamBuf : public std::streambuf, loo::noncopyable
	{
	public:
		MemInputStreamBuf (void const * p, std::streamsize num_bytes);
		MemInputStreamBuf (void const * begin, void const * end);

	protected:
		int_type uflow () override;
		int_type underflow () override;

		std::streamsize xsgetn (char_type* s, std::streamsize count) override;

		int_type pbackfail (int_type ch) override;
		std::streamsize showmanyc () override;

		pos_type seekoff (off_type off, std::ios_base::seekdir way, std::ios_base::openmode which) override;
		pos_type seekpos (pos_type sp, std::ios_base::openmode which) override;

	private:
		char_type const * const begin_;
		char_type const * const end_;
		char_type const * current_;
	};

	template <typename Callback>
	class CallbackOutputStreamBuf : public std::streambuf, loo::noncopyable
	{
	public:
		explicit CallbackOutputStreamBuf (Callback const & cb)
			: cb_ (cb)
		{
		}

		explicit CallbackOutputStreamBuf (Callback&& cb)
			: cb_ (std::move (cb))
		{
		}

	protected:
		std::streamsize xsputn (char_type const * s, std::streamsize count) override
		{
			return cb_ (s, count);
		}

		int_type overflow (int_type ch = traits_type::eof ()) override
		{
			return cb_ (&ch, 1);
		}

	private:
		Callback cb_;
	};


	class VectorStreamCallback : loo::noncopyable
	{
	public:
		explicit VectorStreamCallback (std::vector<std::streambuf::char_type>& data);
		VectorStreamCallback (VectorStreamCallback&& rhs);

		std::streambuf::int_type operator()(void const * buff, std::streamsize count);

	private:
		std::vector<std::streambuf::char_type>& data_;
	};

	class VectorOutputStreamBuf : public CallbackOutputStreamBuf<VectorStreamCallback>
	{
	public:
		explicit VectorOutputStreamBuf (std::vector<char_type>& data)
			: CallbackOutputStreamBuf<VectorStreamCallback> (VectorStreamCallback (data))
		{
		}
	};

	class StringStreamCallback : loo::noncopyable
	{
	public:
		explicit StringStreamCallback (std::basic_string<std::streambuf::char_type>& data);
		StringStreamCallback (StringStreamCallback&& rhs);

		std::streambuf::int_type operator()(void const * buff, std::streamsize count);

	private:
		std::basic_string<std::streambuf::char_type>& data_;
	};

	class StringOutputStreamBuf : public CallbackOutputStreamBuf<StringStreamCallback>
	{
	public:
		explicit StringOutputStreamBuf (std::basic_string<char_type>& data)
			: CallbackOutputStreamBuf<StringStreamCallback> (StringStreamCallback (data))
		{
		}
	};
}

#endif		// LE_CUSTOMIZEDSTREAMBUF_HPP
