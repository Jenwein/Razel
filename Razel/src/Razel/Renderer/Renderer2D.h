#pragma once

#include "OrthographicCameraController.h"
#include "Texture.h"
namespace Razel
{
	// 2D��Ⱦ��̬��,��װһЩ��Ⱦָ��,����������,���صײ���ȾAPI
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		// ������Ⱦ
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4 color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4 color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
	};
}

