#pragma once

#include "OrthographicCameraController.h"
#include "Texture.h"
namespace Razel
{
	// 2D渲染静态类,封装一些渲染指令,管理场景数据,隐藏底层渲染API
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		// 场景渲染
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4 color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4 color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
	};
}

