#pragma once

#include "Razel/Renderer/RenderCommand.h"

#include "Razel/Renderer/OrthographicCamera.h"
#include "Razel/Renderer/Shader.h"
namespace Razel
{
	class Renderer
	{
	public:

		// ��ʼ����Ⱦ
		static void Init();

		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		// ���ó�����Ϣ,scene������֯�͹���������Ҫ��Ⱦ��
		static void BeginScene(OrthographicCamera& camera);
		
		// ����������׼����Ⱦ
		static void EndScene();

		// �ύҪ��Ⱦ�ļ�����
		static void Submit(const Ref<Shader>& shader,const Ref<VertexArray>& vertexArray,const glm::mat4& transform = glm::mat4(1.0f));
		
		// ��ȡ��ǰ����ȾAPI
		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }


	private:
		// ��������
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix = glm::mat4(1.0f);
		};
		static SceneData* s_SceneData;
	};
}