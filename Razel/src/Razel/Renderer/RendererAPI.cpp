#include "rzpch.h"

#include "Razel/Renderer/RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"
namespace Razel
{
	// ³õÊ¼Ä¬ÈÏOpenGL
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Razel::Scope<Razel::RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
			case RendererAPI::API::None:		RZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:		return CreateScope<OpenGLRendererAPI>();
			case RendererAPI::API::DirectX11:   RZ_CORE_ASSERT(false, "RendererAPI::DirectX11 is currently not supported!"); return nullptr;
		}

		RZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
