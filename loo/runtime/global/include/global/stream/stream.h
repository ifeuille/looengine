
#pragma once
#include "global/global.h"
#include "global/extstd/arrayview.h"
#include "global/extstd/string_view.h"
#include "global/extstd/bytes.h"
#include "global/extstd/memutils.h"
#include <memory>

namespace loo
{

	//
	// Read-only Stream
	//
	
	class RStream : public std::enable_shared_from_this< RStream >
	{
	public:
		RStream () {}

		RStream (const RStream &) = delete;
		RStream (RStream &&) = delete;
		virtual ~RStream () {}

		RStream&  operator = (const RStream &) = delete;
		RStream&  operator = (RStream &&) = delete;

		ND_ virtual bool	IsOpen ()			const = 0;
		ND_ virtual BytesU	Position ()			const = 0;
		ND_ virtual BytesU	Size ()				const = 0;
		ND_ BytesU			RemainingSize ()	const { return Size () - Position (); }

		virtual bool	SeekSet (BytesU pos) = 0;
		ND_ virtual BytesU	Read2 (OUT void *buffer, BytesU size) = 0;

		bool  Read (void *buffer, BytesU size);
		bool  Read (size_t length, OUT std::string &str);
		bool  Read (size_t count, OUT std::vector<uint8_t> &buf);


		template <typename T>
		EnableIf<IsPOD<T>, bool>  Read (OUT T &data)
		{
			return Read2 (AddressOf (data), BytesU::SizeOf (data)) == BytesU::SizeOf (data);
		}

		template <typename T>
		EnableIf<IsPOD<T>, bool>  Read (size_t count, OUT std::vector<T> &arr)
		{
			arr.resize (count);

			BytesU	size = BytesU::SizeOf (arr[0]) * arr.size ();

			return Read2 (arr.data (), size) == size;
		}
	};



	//
	// Write-only Stream
	//

	class WStream : public std::enable_shared_from_this< WStream >
	{
	public:
		WStream () {}

		WStream (const WStream &) = delete;
		WStream (WStream &&) = delete;
		virtual ~WStream () {}

		WStream&  operator = (const WStream &) = delete;
		WStream&  operator = (WStream &&) = delete;

		ND_ virtual bool	IsOpen ()	const = 0;
		ND_ virtual BytesU	Position ()	const = 0;
		ND_ virtual BytesU	Size ()		const = 0;

		ND_ virtual BytesU	Write2 (const void *buffer, BytesU size) = 0;
		virtual void	Flush () = 0;

		bool  Write (const void *buffer, BytesU size);
		bool  Write (nonstd::string_view str);
		bool  Write (ArrayView<uint8_t> buf);

		template <typename T>
		EnableIf<IsPOD<T>, bool>  Write (const T &data)
		{
			return Write2 (AddressOf (data), BytesU::SizeOf (data)) == BytesU::SizeOf (data);
		}
	};


}

