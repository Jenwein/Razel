#include "rzpch.h"
#include "Framebuffer.h"

#include "Razel/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Razel {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    RZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
		}

		RZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
