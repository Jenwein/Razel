#include "rzpch.h"

#include "Razel/Renderer/VertexArray.h"
#include "Razel/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Razel
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: RZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
			case RendererAPI::API::DirectX11: RZ_CORE_ASSERT(false, "RendererAPI::DirectX11 is currently not supported!"); return nullptr;
			default: break;
		}
		RZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}