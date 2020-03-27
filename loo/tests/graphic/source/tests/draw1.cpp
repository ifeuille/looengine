#include "graphicapp.h"

bool GraphicApp::Test_Draw1 ()
{
	loo::vkfg::GraphicsPipelineDesc ppln;

	ppln.AddShader (loo::vkfg::EShader::Vertex,
		loo::vkfg::EShaderLangFormat::VKSL_100, "main", R"#(
#pragma shader_stage(vertex)
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout(location=0) out vec3  v_Color;

const vec2	g_Positions[3] = vec2[](
	vec2(0.0, -0.5),
	vec2(0.5, 0.5),
	vec2(-0.5, 0.5)
);

const vec3	g_Colors[3] = vec3[](
	vec3(1.0, 0.0, 0.0),
	vec3(0.0, 1.0, 0.0),
	vec3(0.0, 0.0, 1.0)
);

void main() {
	gl_Position	= vec4( g_Positions[gl_VertexIndex], 0.0, 1.0 );
	v_Color		= g_Colors[gl_VertexIndex];
}
)#");
	ppln.AddShader (loo::vkfg::EShader::Fragment, loo::vkfg::EShaderLangFormat::VKSL_100, "main", R"#(
#pragma shader_stage(fragment)
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout(location=0) out vec4  out_Color;

layout(location=0) in  vec3  v_Color;

void main() {
	out_Color = vec4(v_Color, 1.0);
}
)#");

	const loo::math::uint2 view_size = { 800,200 };
	loo::vkfg::ImageID image = _frameGraph->CreateImage (
		loo::vkfg::ImageDesc{
			loo::vkfg::EImage::Tex2D,
			loo::math::uint3{view_size.x,view_size.y,1},
			loo::vkfg::EPixelFormat::RGBA8_UNorm,
			loo::vkfg::EImageUsage::ColorAttachment | loo::vkfg::EImageUsage::TransferSrc
		},
		loo::Default,
		"RenderTarget"
	);

	loo::vkfg::GPipelineID pipeline = _frameGraph->CreatePipeline (ppln);

	bool data_is_correct = false;

	const auto OnLoaded = [OUT & data_is_correct](const loo::vkfg::ImageView& imageData)
	{
		const auto TestPixel = [&imageData](float x, float y, const loo::math::RGBA32f& color)
		{
			loo::uint ix = loo::uint ((x + 1.0f)*0.5f*float (imageData.Dimension ().x) + 0.5f);
			loo::uint iy = loo::uint ((y + 1.0f)*0.5f*float (imageData.Dimension ().y) + 0.5f);

			loo::math::RGBA32f col;
			imageData.Load (loo::math::uint3 (ix, iy, 0), OUT col);
			
			bool is_equal = loo::math::All (loo::math::Equals (col, color, 0.1f));
			ASSERT (is_equal);
			return is_equal;
		};

		data_is_correct = true;
		data_is_correct &= TestPixel ( 0.00f, -0.49f, loo::math::RGBA32f{ 1.0f, 0.0f, 0.0f, 1.0f });
		data_is_correct &= TestPixel ( 0.49f,  0.49f, loo::math::RGBA32f{ 0.0f, 1.0f, 0.0f, 1.0f });
		data_is_correct &= TestPixel (-0.49f,  0.49f, loo::math::RGBA32f{ 0.0f, 0.0f, 1.0f, 1.0f });

		data_is_correct &= TestPixel ( 0.00f, -0.51f, loo::math::RGBA32f{ 0.0f });
		data_is_correct &= TestPixel ( 0.51f,  0.51f, loo::math::RGBA32f{ 0.0f });
		data_is_correct &= TestPixel (-0.51f,  0.51f, loo::math::RGBA32f{ 0.0f });
		data_is_correct &= TestPixel ( 0.00f,  0.51f, loo::math::RGBA32f{ 0.0f });
		data_is_correct &= TestPixel ( 0.51f, -0.51f, loo::math::RGBA32f{ 0.0f });
		data_is_correct &= TestPixel (-0.51f, -0.51f, loo::math::RGBA32f{ 0.0f });
	};

	loo::vkfg::CommandBuffer cmd = _frameGraph->Begin (loo::vkfg::CommandBufferDesc{}.SetDebugFlags (loo::vkfg::EDebugFlags::Default));
	CHECK_ERR (cmd);

	loo::vkfg::LogicalPassID render_pass = cmd->CreateRenderPass (
		loo::vkfg::RenderPassDesc (view_size)
		.AddTarget (loo::vkfg::RenderTargetID::Color_0, image, loo::math::RGBA32f (0.0f), loo::vkfg::EAttachmentStoreOp::Store)
		.AddViewport (view_size)
	);

	cmd->AddTask (render_pass, loo::vkfg::DrawVertices ().Draw (3).SetPipeline (pipeline).SetTopology (loo::vkfg::EPrimitive::TriangleList));

	loo::vkfg::Task t_draw = cmd->AddTask (loo::vkfg::SubmitRenderPass{ render_pass });
	loo::vkfg::Task t_read = cmd->AddTask (loo::vkfg::ReadImage ().SetImage (image, loo::math::int2 (), view_size).SetCallback (OnLoaded).DependsOn (t_draw));
	LOO_UNUSED (t_read);

	CHECK_ERR (_frameGraph->Execute (cmd));
	CHECK_ERR (_frameGraph->WaitIdle ());
	CHECK_ERR (CompareDumps(TEST_NAME));
	CHECK_ERR (Visualize(TEST_NAME));
	CHECK_ERR (data_is_correct);

	DeleteResources (image, pipeline);
	LOO_LOGI (TEST_NAME << " - passed");
	return true;
}