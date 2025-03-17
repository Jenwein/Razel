#include "rzpch.h"
#include "Renderer.h"

namespace Razel
{
	void Renderer::BeginScene()
	{
		// 设置场景信息

	}

	void Renderer::EndScene()
	{
		// 结束场景
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}