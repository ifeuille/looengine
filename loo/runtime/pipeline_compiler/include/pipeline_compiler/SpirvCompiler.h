
#pragma once

#include "pipeline_compiler/EShaderCompilationFlags.h"
#include "vkfg/fg/enums.h"
#include "glslang/Include/ResourceLimits.h"
#include "global/extstd/fs_std.h"
namespace FS = fs;

class TIntermNode;

namespace glslang
{
	class TType;
	class TIntermediate;
}

namespace loo
{
	namespace vkfg
	{

		//
		// SPIRV Compiler
		//

		class SpirvCompiler final
		{
			// types
		public:
			struct ShaderReflection
			{
				// types
				using TopologyBits_t = GraphicsPipelineDesc::TopologyBits_t;
				using Shader = PipelineDescription::Shader;
				using PipelineLayout = PipelineDescription::PipelineLayout;
				using VertexAttribs_t = GraphicsPipelineDesc::VertexAttribs_t;
				using FragmentOutputs_t = GraphicsPipelineDesc::FragmentOutputs_t;
				using SpecConstants_t = PipelineDescription::SpecConstants_t;


				// variables
				Shader				shader;
				PipelineLayout		layout;
				SpecConstants_t		specConstants;

				struct {
					TopologyBits_t		supportedTopology;
					VertexAttribs_t		vertexAttribs;

				}				vertex;

				struct {
					uint				patchControlPoints;

				}				tessellation;

				struct {
					FragmentOutputs_t	fragmentOutput;
					bool				earlyFragmentTests = true;

				}				fragment;

				struct {
					loo::math::uint3				localGroupSize;
					loo::math::uint3				localGroupSpecialization;

				}				compute;

				struct {
					loo::math::uint3				taskGroupSize;
					loo::math::uint3				taskGroupSpecialization;

					loo::math::uint3				meshGroupSize;
					loo::math::uint3				meshGroupSpecialization;

					EPrimitive			topology = Default;
					uint				maxPrimitives = 0;
					uint				maxIndices = 0;
					uint				maxVertices = 0;

				}				mesh;
			};

		private:
			struct GLSLangResult;
			class  ShaderIncluder;


			// variables
		private:
			Array<String> const&		_directories;
			EShaderCompilationFlags		_compilerFlags = Default;

			glslang::TIntermediate *	_intermediate = null;
			EShaderStages				_currentStage = Default;
			bool						_targetVulkan = true;
			uint						_spirvTraget = 0;		// spv_target_env

			TBuiltInResource			_builtinResource;


			// methods
		public:
			explicit SpirvCompiler (const Array<String> &);
			~SpirvCompiler ();

			bool SetCompilationFlags (EShaderCompilationFlags flags);

			bool SetDefaultResourceLimits ();
			bool SetCurrentResourceLimits (PhysicalDeviceVk_t physicalDevice);

			bool Compile (EShader shaderType, EShaderLangFormat srcShaderFmt, EShaderLangFormat dstShaderFmt,
				NtStringView entry, NtStringView source, StringView debugName,
				OUT PipelineDescription::Shader &outShader, OUT ShaderReflection &outReflection, OUT String &log);


		private:
			bool _ParseGLSL (EShader shaderType, EShaderLangFormat srcShaderFmt, EShaderLangFormat dstShaderFmt,
				NtStringView entry, ArrayView<const char *> source, INOUT ShaderIncluder &includer,
				OUT GLSLangResult &glslangData, INOUT String &log);

			bool _CompileSPIRV (const GLSLangResult &glslangData, OUT Array<uint> &spirv, INOUT String &log) const;
			bool _OptimizeSPIRV (INOUT Array<uint> &spirv, INOUT String &log) const;

			bool _BuildReflection (const GLSLangResult &glslangData, OUT ShaderReflection &reflection);

			bool _OnCompilationFailed (ArrayView<const char *> source, INOUT String &log) const;

			bool _ParseAnnotations (StringView source, INOUT ShaderReflection &) const;

			static void _GenerateResources (OUT TBuiltInResource& res);


			// GLSL deserializer
		private:
			bool _ProcessExternalObjects (TIntermNode* root, TIntermNode* node, INOUT ShaderReflection &result) const;

			bool _DeserializeExternalObjects (TIntermNode* node, INOUT ShaderReflection &result) const;

			bool _ProcessShaderInfo (INOUT ShaderReflection &result) const;

			bool _CalculateStructSize (const glslang::TType &bufferType, OUT BytesU &staticSize, OUT BytesU &arrayStride, OUT BytesU &offset) const;

			void _MergeWithGeometryInputPrimitive (INOUT GraphicsPipelineDesc::TopologyBits_t &topologyBits, /*TLayoutGeometry*/uint type) const;

			ND_ BindingIndex	_ToBindingIndex (uint index) const;
			ND_ EImage			_ExtractImageType (const glslang::TType &type) const;
			ND_ EVertexType		_ExtractVertexType (const glslang::TType &type) const;
			ND_ EPixelFormat	_ExtractImageFormat (/*TLayoutFormat*/uint format) const;
			ND_ EFragOutput		_ExtractFragmentOutputType (const glslang::TType &type) const;
		};


	}
}