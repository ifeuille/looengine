#pragma once
#include "vkfg/fg/vertexdesc.h"
#include "vkfg/fg/ids.h"

namespace loo
{
	namespace vkfg
	{
		//
		// Vertex Input State
		//
		class VertexInputState
		{
		public:
			struct VertexAttrib
			{
				VertexID id;
				uint index;
				EVertexType type;// float|int|uint <1,2,3,4,...> are available
				ND_ bool operator ==(const VertexAttrib& rhs)const;
			};
			
			using Self = VertexInputState;

			struct VertexInput
			{
				// variables
				EVertexType type;// src type, if src type is normalized short3, then dst type is float3.
				uint index;
				Bytes<uint> offset;
				uint bufferBinding;

				// methods
				VertexInput ();
				VertexInput (EVertexType type, Bytes<uint> offset, uint bufferBinding);

				ND_ EVertexType ToDstType () const;
				ND_ bool operator ==(const VertexInput& rhs)const;
				
			};

			struct BufferBinding
			{
				//variables
				uint index;
				Bytes<uint> stride;
				EVertexInputRate rate;

				//methods
				BufferBinding ();
				BufferBinding (uint index, Bytes<uint> stride, EVertexInputRate rate);
				ND_ bool  operator == (const BufferBinding &rhs) const;
			
			};

			static constexpr uint BindingIndex_Auto = UMax;
			static constexpr uint VertexIndex_Unknown = UMax;

			using Vertices_t = FixedMap< VertexID, VertexInput, LOO_MaxVertexAttribs >;
			using Bindings_t = FixedMap< VertexBufferID, BufferBinding, LOO_MaxVertexBuffers >;


			friend struct std::hash < VertexInputState::VertexInput >;
			friend struct std::hash < VertexInputState::BufferBinding >;
			friend struct std::hash < VertexInputState >;

			// variables
		private:
			Vertices_t _vertices;
			Bindings_t _bindings;

			// methods
		public:
			VertexInputState () {}
			
			template<typename ClassType,typename ValueType>
			Self& Add (const VertexID& id, ValueType ClassType:: * vertex, const VertexBufferID& bufferId = Default);

			template <typename ClassType, typename ValueType>
			Self & Add (const VertexID &id, ValueType ClassType:: *vertex, bool norm, const VertexBufferID &bufferId = Default);

			Self & Add (const VertexID &id, EVertexType type, BytesU offset, const VertexBufferID &bufferId = Default);
			
			Self & Bind (const VertexBufferID &bufferId, Bytes<uint> stride, uint index = BindingIndex_Auto, EVertexInputRate rate = EVertexInputRate::Vertex);
			Self & Bind (const VertexBufferID &bufferId, BytesU stride, uint index = BindingIndex_Auto, EVertexInputRate rate = EVertexInputRate::Vertex);
			
			void Clear ();

			bool ApplyAttribs (ArrayView<VertexAttrib> attribs);

			ND_ bool operator ==(const VertexInputState& rhs)const;

			ND_ Vertices_t const& Vertices ()const;
			ND_ Bindings_t const& BufferBindings ()const;

		};

		/*
		=================================================
			Add
		=================================================
		*/
		template<typename ClassType, typename ValueType>
		inline VertexInputState& VertexInputState::Add (const VertexID& id, ValueType ClassType::* vertex, const VertexBufferID& bufferId)
		{
			return Add (id, VertexDesc<ValueType>::attrib,
				OffsetOf (vertex),
				bufferId);
		}

		/*
		=================================================
			Add
		=================================================
		*/
		template<typename ClassType, typename ValueType>
		inline VertexInputState&  VertexInputState::Add (const VertexID &id, ValueType ClassType:: *vertex, bool norm, const VertexBufferID &bufferId)
		{
			const EVertexType attrib = VertexDesc<ValueType>::attrib;
			return Add (id,
				norm ? (attrib | EVertexType::NormalizedFlag):(attrib & ~EVertexType::NormalizedFlag),
				OffsetOf(vertex),
				bufferId);
		}



	}
}

namespace std
{
	template<>
	struct hash<loo::vkfg::VertexInputState::VertexInput> {
		ND_ size_t operator()(const loo::vkfg::VertexInputState::VertexInput&)const;
	};

	template <>
	struct hash < loo::vkfg::VertexInputState::BufferBinding > {
		ND_ size_t  operator () (const loo::vkfg::VertexInputState::BufferBinding &) const;
	};

	template <>
	struct hash < loo::vkfg::VertexInputState > {
		ND_ size_t  operator () (const loo::vkfg::VertexInputState &) const;
	};

}