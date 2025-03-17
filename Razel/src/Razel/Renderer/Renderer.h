#pragma once

#include "RenderCommand.h"

namespace Razel
{
	class Renderer
	{
	public:
		// 设置场景信息
		static void BeginScene();
		
		// 结束场景，准备渲染
		static void EndScene();

		// 提交要渲染的几何体
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
		
		// 获取当前的渲染API
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	};
}