#include "rzpch.h"
#include "Razel/Renderer/GraphicsContext.h"

#include "Razel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Razel
{
	Scope<GraphicsContext>GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    RZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
			case RendererAPI::API::DirectX11:    RZ_CORE_ASSERT(false, "RendererAPI::DirectX11 is currently not supported!"); return nullptr;
		}

		RZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}