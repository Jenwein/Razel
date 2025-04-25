#pragma once

#include "Razel/Renderer/Texture.h"

#include "Razel/Renderer/Camera.h"

#include "Razel/Renderer/OrthographicCameraController.h"
namespace Razel
{
	// 2D��Ⱦ��̬��,��װһЩ��Ⱦָ��,����������,���صײ���ȾAPI
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		// ������Ⱦ
		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const OrthographicCamera& camera);	//TODO:Remove
		static void EndScene();
		static void Flush();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);	
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawQuad(const glm::mat4 transform, glm::vec4 color);
		
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::mat4 transform, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));


	
		// ͳ��
		struct Statistics
		{
			uint32_t DrawCalls = 0;		// ��¼���Ƶ��õĴ���
			uint32_t QuadCount = 0;		// ��¼���Ƶ��ı�������

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }	// �����ܶ�������
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }		// ��������������
		};
		static void ResetStats();		// ����ͳ������
		static Statistics GetStats();	// ��ȡ��ǰ��ͳ������

	private:
		static void FlushAndReset();	// ����ˢ�º�������Ⱦ��״̬
	};
}

