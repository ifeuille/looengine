
#include "vkfg/fg/vertexinputstate.h"

namespace loo
{
	namespace vkfg
	{

		/*
		=================================================
			VertexAttrib::operator ==
		=================================================
		*/
		bool  VertexInputState::VertexAttrib::operator == (const VertexAttrib &rhs) const
		{
			return	id == rhs.id		and
				index == rhs.index	and
				type == rhs.type;
		}
		//-----------------------------------------------------------------------------



		/*
		=================================================
			constructor
		=================================================
		*/
		VertexInputState::VertexInput::VertexInput () :
			type{ EVertexType::Unknown },
			index{ VertexIndex_Unknown },
			bufferBinding{ BindingIndex_Auto }
		{}

		VertexInputState::VertexInput::VertexInput (EVertexType type, Bytes<uint> offset, uint bufferBinding) :
			type{ type },
			index{ VertexIndex_Unknown },
			offset{ offset },
			bufferBinding{ bufferBinding }
		{}

		/*
		=================================================
			ToDstType
		=================================================
		*/
		EVertexType  VertexInputState::VertexInput::ToDstType () const
		{
			const EVertexType	scalar_type = (type & EVertexType::_TypeMask);
			const EVertexType	vec_size = (type & EVertexType::_VecMask);
			const bool			is_float = EnumEq (type, EVertexType::NormalizedFlag) or
				EnumEq (type, EVertexType::ScaledFlag);
			const EVertexType	float_type = (EVertexType::_Float | vec_size);

			switch (scalar_type)
			{
			case EVertexType::_Byte:
			case EVertexType::_Short:
			case EVertexType::_Int:
				return is_float ? float_type : (EVertexType::_Int | vec_size);

			case EVertexType::_UByte:
			case EVertexType::_UShort:
			case EVertexType::_UInt:
				return is_float ? float_type : (EVertexType::_UInt | vec_size);

			case EVertexType::_Long:
				return is_float ? float_type : (EVertexType::_Long | vec_size);

			case EVertexType::_ULong:
				return is_float ? float_type : (EVertexType::_ULong | vec_size);

			case EVertexType::_Half:
			case EVertexType::_Float:
				return (EVertexType::_Float | vec_size);

			case EVertexType::_Double:
				return (EVertexType::_Double | vec_size);
			}

			RETURN_ERR ("invalid vertex type", float_type);
		}

		/*
		=================================================
			operator ==
		=================================================
		*/
		bool  VertexInputState::VertexInput::operator == (const VertexInput &rhs) const
		{
			// vertex location must be defined
			ASSERT (index != VertexIndex_Unknown);
			ASSERT (rhs.index != VertexIndex_Unknown);

			return	type == rhs.type		and
				index == rhs.index	and
				offset == rhs.offset	and
				bufferBinding == rhs.bufferBinding;
		}
		//-----------------------------------------------------------------------------



		/*
		=================================================
			constructor
		=================================================
		*/
		VertexInputState::BufferBinding::BufferBinding () :
			index (VertexIndex_Unknown), rate (EVertexInputRate::Unknown)
		{}

		VertexInputState::BufferBinding::BufferBinding (uint index, Bytes<uint> stride, EVertexInputRate rate) :
			index (index), stride (stride), rate (rate)
		{}

		/*
		=================================================
			operator ==
		=================================================
		*/
		bool  VertexInputState::BufferBinding::operator == (const BufferBinding &rhs) const
		{
			return	index == rhs.index	and
				stride == rhs.stride	and
				rate == rhs.rate;
		}
		//-----------------------------------------------------------------------------



		/*
		=================================================
			Add
		=================================================
		*/
		VertexInputState&  VertexInputState::Add (const VertexID &id, EVertexType type, BytesU offset, const VertexBufferID &bufferId)
		{
			ASSERT (id.IsDefined ());
			ASSERT (_vertices.count (id) == 0);

			auto	iter = _bindings.find (bufferId);
			CHECK (iter != _bindings.end ()/*, *this*/);

			_vertices.insert_or_assign (id, VertexInput{ type, Bytes<uint> (offset), iter->second.index });
			return *this;
		}

		/*
		=================================================
			Bind
		=================================================
		*/
		VertexInputState&  VertexInputState::Bind (const VertexBufferID &bufferId, Bytes<uint> stride, uint index, EVertexInputRate rate)
		{
			//ASSERT( _bindings.count( bufferId ) == 0 );

			if (index == BindingIndex_Auto)
				index = uint (_bindings.size ());

			_bindings.insert_or_assign (bufferId, BufferBinding (index, stride, rate));
			return *this;
		}

		VertexInputState&  VertexInputState::Bind (const VertexBufferID &bufferId, BytesU stride, uint index, EVertexInputRate rate)
		{
			return Bind (bufferId, Bytes<uint>{stride}, index, rate);
		}

		/*
		=================================================
			Clear
		=================================================
		*/
		void VertexInputState::Clear ()
		{
			_vertices.clear ();
			_bindings.clear ();
		}

		/*
		=================================================
			operator ==
		=================================================
		*/
		bool VertexInputState::operator == (const VertexInputState &rhs) const
		{
			return	_vertices == rhs._vertices	and
				_bindings == rhs._bindings;
		}

		/*
		=================================================
			ApplyAttribs
		----
			copy vertex attrib locations from 'attribs' to '_vertices'
		=================================================
		*/
		bool VertexInputState::ApplyAttribs (ArrayView<VertexAttrib> attribs)
		{
			ASSERT (attribs.size () == _vertices.size ());

			for (auto& attr : attribs)
			{
				auto	iter = _vertices.find (attr.id);
				ASSERT (iter != _vertices.end ());

				if (iter != _vertices.end ())
				{
					iter->second.index = attr.index;

					ASSERT (attr.type == iter->second.ToDstType ());
				}
			}
			return true;
		}

	}	

}

namespace std
{
	using namespace loo;
	using namespace loo::vkfg;

	/*
	=================================================
		hash::operator (VertexInput)
	=================================================
	*/
	size_t  hash< VertexInputState::VertexInput >::operator () (const VertexInputState::VertexInput &value) const
	{
		ASSERT (value.index != VertexInputState::VertexIndex_Unknown);	// vertex location must be defined

#if LOO_FAST_HASH
		return size_t (HashOf (AddressOf (value), sizeof (value)));
#else
		return size_t (HashOf (value.type) + HashOf (value.index) +
			HashOf (value.offset) + HashOf (value.bufferBinding));
#endif
	}

	/*
	=================================================
		hash::operator (BufferBinding)
	=================================================
	*/
	size_t  hash< VertexInputState::BufferBinding >::operator () (const VertexInputState::BufferBinding &value) const
	{
#if LOO_FAST_HASH
		return size_t (HashOf (AddressOf (value), sizeof (value)));
#else
		return size_t (HashOf (value.index) + HashOf (value.stride) + HashOf (value.rate));
#endif
	}

	/*
	=================================================
		hash::operator (VertexInputState)
	=================================================
	*/
	size_t  hash< VertexInputState >::operator () (const VertexInputState &value) const
	{
#if LOO_FAST_HASH
		return size_t (HashOf (AddressOf (value), sizeof (value)));
#else
		HashVal	result;
		result << HashOf (value._vertices.size ());
		result << HashOf (value._bindings.size ());

		for (auto& attr : value._vertices)
		{
			result << HashOf (attr.first);
			result << HashOf (attr.second);
		}

		for (auto& bind : value._bindings)
		{
			result << HashOf (bind.first);
			result << HashOf (bind.second);
		}
		return size_t (result);
#endif
	}

}	// std
