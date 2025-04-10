#include "rzpch.h"

#include "Razel/Renderer/Buffer.h"
#include "Razel/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Razel
{
	
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: RZ_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices,size);
			case RendererAPI::API::DirectX11: RZ_CORE_ASSERT(false, "RendererAPI::API::DirectX11 is currently not supported!"); return nullptr;
			default: break;
		}
		RZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: RZ_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(size);
		case RendererAPI::API::DirectX11: RZ_CORE_ASSERT(false, "RendererAPI::API::DirectX11 is currently not supported!"); return nullptr;
		default: break;
		}
		RZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: RZ_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices,count);
			case RendererAPI::API::DirectX11: RZ_CORE_ASSERT(false, "RendererAPI::API::DirectX11 is currently not supported!"); return nullptr;
			default: break;
		}
		RZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}

}