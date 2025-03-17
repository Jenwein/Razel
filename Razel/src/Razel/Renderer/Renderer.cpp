#include "rzpch.h"
#include "Renderer.h"

namespace Razel
{
	void Renderer::BeginScene()
	{
		// ���ó�����Ϣ

	}

	void Renderer::EndScene()
	{
		// ��������
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}