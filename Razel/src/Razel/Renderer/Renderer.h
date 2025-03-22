#pragma once

#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Shader.h"
namespace Razel
{
	class Renderer
	{
	public:
		// ���ó�����Ϣ
		static void BeginScene(OrthographicCamera& camera);
		
		// ����������׼����Ⱦ
		static void EndScene();

		// �ύҪ��Ⱦ�ļ�����
		static void Submit(const Ref<Shader>& shader,const Ref<VertexArray>& vertexArray,const glm::mat4& transform = glm::mat4(1.0f));
		
		// ��ȡ��ǰ����ȾAPI
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }


	private:
		// ��������
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix = glm::mat4(1.0f);
		};
		static SceneData* m_SceneData;
	};
}