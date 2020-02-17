
#pragma once
#include "global/types.h"
#include "glsl_trace/ShaderTrace.h"
#include "vulkanloader/VulkanLoader.h"


namespace loo
{
	namespace vkfg
	{
		template <typename T>
		class VCachedDebuggableShaderData;

		using VCachedDebuggableShaderModule = VCachedDebuggableShaderData< ShaderModuleVk_t >;
		using VCachedDebuggableSpirv = VCachedDebuggableShaderData< Array<uint> >;



		//
		// Vulkan Cached Shader Data (with debug info)
		//

		template <typename T>
		class VCachedDebuggableShaderData final : public PipelineDescription::IShaderData<T>
		{
			template <typename B> friend class VCachedDebuggableShaderData;

			// types
		public:
			using ShaderDebugUtils_t = nonstd::variant< NullUnion, ShaderTrace >;
			using ShaderDebugUtilsPtr = UniquePtr< ShaderDebugUtils_t >;


			// variables
		private:
			T						_data;
			StaticString<64>		_entry;
			StaticString<64>		_debugName;
			ShaderDebugUtilsPtr		_debugInfo;


			// methods
		public:
			VCachedDebuggableShaderData (StringView entry, T &&data, StringView dbgName) :
				_data{ std::move (data) }, _entry{ entry }, _debugName{ dbgName }
			{}

			VCachedDebuggableShaderData (StringView entry, T &&data, StringView dbgName, ShaderDebugUtilsPtr &&debugUtilsPtr) :
				_data{ std::move (data) }, _entry{ entry }, _debugName{ dbgName }, _debugInfo{ std::move (debugUtilsPtr) }
			{}

			VCachedDebuggableShaderData (VkShaderModule module, const PipelineDescription::SharedShaderPtr<Array<uint>> &spirvCache)
			{
				/*if constexpr (IsSameTypes< T, ShaderModuleVk_t >)
				{
					_data = BitCast<ShaderModuleVk_t> (module);
					_entry = spirvCache->GetEntry ();
					_debugName = spirvCache->GetDebugName ();

					if (auto other = DynCast<VCachedDebuggableSpirv> (spirvCache))
						_debugInfo = std::move (other->_debugInfo);
				}*/
			}


			~VCachedDebuggableShaderData ()
			{
			/*	if constexpr (IsSameTypes< T, ShaderModuleVk_t >)
				{
					CHECK (_data == VK_NULL_HANDLE);
				}*/
			}


			void Destroy (PFN_vkDestroyShaderModule fpDestroyShaderModule, VkDevice dev)
			{
				/*if constexpr (IsSameTypes< T, ShaderModuleVk_t >)
				{
					if (_data)
					{
						fpDestroyShaderModule (dev, BitCast<VkShaderModule> (_data), null);
						_data = ShaderModuleVk_t (0);
					}
				}*/
			}
			

			struct ParseDebugOutput_VisitFuncLocal
			{
				ArrayView<uint8_t>& debugOutput;
				Array<String> &result;
				ParseDebugOutput_VisitFuncLocal (ArrayView<uint8_t>& _debugOutput, Array<String> &_result)
					:debugOutput (_debugOutput), result (_result) {};
				bool operator()(const ShaderTrace &trace)const
				{ return trace.ParseShaderTrace (debugOutput.data (), debugOutput.size (), OUT result); }
				bool operator()(const NullUnion &)const { return false; }
			};
			bool ParseDebugOutput (EShaderDebugMode mode, ArrayView<uint8_t> debugOutput, OUT Array<String> &result) const override
			{
				CHECK_ERR (mode == EShaderDebugMode::Trace);
				if (not _debugInfo)
					return false;

				return Visit (*_debugInfo,
#if 1
					ParseDebugOutput_VisitFuncLocal(debugOutput, result)
#else
					[&](const ShaderTrace &trace) { return trace.ParseShaderTrace (debugOutput.data (), debugOutput.size (), OUT result); },
					[](const NullUnion &) { return false; }
#endif
				);
			}


			T const&	GetData () const override { return _data; }

			StringView	GetEntry () const override { return _entry; }

			StringView	GetDebugName () const override { return _debugName; }


			size_t		GetHashOfData () const override
			{
				//if constexpr (IsSameTypes< T, ShaderModuleVk_t >)
				//{
				//	ASSERT (!"not supported");
				//	return 0;
				//}
				//else
				{
					return size_t (HashOf (_data));
				}
			}
		};

		template <>
		class VCachedDebuggableShaderData<ShaderModuleVk_t> final : public PipelineDescription::IShaderData<ShaderModuleVk_t>
		{
			template <typename B> friend class VCachedDebuggableShaderData;

			// types
		public:
			using ShaderDebugUtils_t = nonstd::variant< NullUnion, ShaderTrace >;
			using ShaderDebugUtilsPtr = UniquePtr< ShaderDebugUtils_t >;


			// variables
		private:
			ShaderModuleVk_t		_data;
			StaticString<64>		_entry;
			StaticString<64>		_debugName;
			ShaderDebugUtilsPtr		_debugInfo;


			// methods
		public:
			VCachedDebuggableShaderData (StringView entry, ShaderModuleVk_t &&data, StringView dbgName) :
				_data{ std::move (data) }, _entry{ entry }, _debugName{ dbgName }
			{}

			VCachedDebuggableShaderData (StringView entry, ShaderModuleVk_t &&data, StringView dbgName, ShaderDebugUtilsPtr &&debugUtilsPtr) :
				_data{ std::move (data) }, _entry{ entry }, _debugName{ dbgName }, _debugInfo{ std::move (debugUtilsPtr) }
			{}

			VCachedDebuggableShaderData (VkShaderModule module, const PipelineDescription::SharedShaderPtr<Array<uint>> &spirvCache)
			{
				_data = BitCast<ShaderModuleVk_t> (module);
				_entry = spirvCache->GetEntry ();
				_debugName = spirvCache->GetDebugName ();

				if (auto other = DynCast<VCachedDebuggableSpirv> (spirvCache))
					_debugInfo = std::move (other->_debugInfo);
			}


			~VCachedDebuggableShaderData ()
			{
				CHECK (_data == VK_NULL_HANDLE);
			}


			void Destroy (PFN_vkDestroyShaderModule fpDestroyShaderModule, VkDevice dev)
			{
				if (_data)
				{
					fpDestroyShaderModule (dev, BitCast<VkShaderModule> (_data), null);
					_data = ShaderModuleVk_t (0);
				}
			}


			struct ParseDebugOutput_VisitFuncLocal
			{
				ArrayView<uint8_t>& debugOutput;
				Array<String> &result;
				ParseDebugOutput_VisitFuncLocal (ArrayView<uint8_t>& _debugOutput, Array<String> &_result)
					:debugOutput (_debugOutput), result (_result) {};
				bool operator()(const ShaderTrace &trace)const
				{
					return trace.ParseShaderTrace (debugOutput.data (), debugOutput.size (), OUT result);
				}
				bool operator()(const NullUnion &)const { return false; }
			};
			bool ParseDebugOutput (EShaderDebugMode mode, ArrayView<uint8_t> debugOutput, OUT Array<String> &result) const override
			{
				CHECK_ERR (mode == EShaderDebugMode::Trace);
				if (not _debugInfo)
					return false;

				return Visit (*_debugInfo,
#if 1
					ParseDebugOutput_VisitFuncLocal (debugOutput, result)
#else
					[&](const ShaderTrace &trace) { return trace.ParseShaderTrace (debugOutput.data (), debugOutput.size (), OUT result); },
					[](const NullUnion &) { return false; }
#endif
				);
			}


			ShaderModuleVk_t const&	GetData () const override { return _data; }

			StringView	GetEntry () const override { return _entry; }

			StringView	GetDebugName () const override { return _debugName; }


			size_t		GetHashOfData () const override
			{
				ASSERT (!"not supported");
				return 0;
			}
		};

	}
}