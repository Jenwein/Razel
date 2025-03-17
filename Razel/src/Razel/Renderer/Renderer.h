#pragma once

#include "RenderCommand.h"

namespace Razel
{
	class Renderer
	{
	public:
		// ���ó�����Ϣ
		static void BeginScene();
		
		// ����������׼����Ⱦ
		static void EndScene();

		// �ύҪ��Ⱦ�ļ�����
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
		
		// ��ȡ��ǰ����ȾAPI
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	};
}