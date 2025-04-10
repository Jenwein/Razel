#pragma once

#include <glm/glm.hpp>
#include "Razel/Renderer/VertexArray.h"

namespace Razel
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1, DirectX11 = 2
		};
	public:
		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4 color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray,uint32_t count = 0) = 0;

		static Scope<RendererAPI> Create();

		inline static API GetAPI(){return s_API;}
	private:
		static API s_API;
	};
}