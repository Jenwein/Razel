#pragma once

#include "Razel/Renderer/Texture.h"

#include "Razel/Renderer/Camera.h"

#include "Razel/Renderer/OrthographicCameraController.h"
namespace Razel
{
	// 2D渲染静态类,封装一些渲染指令,管理场景数据,隐藏底层渲染API
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		// 场景渲染
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


	
		// 统计
		struct Statistics
		{
			uint32_t DrawCalls = 0;		// 记录绘制调用的次数
			uint32_t QuadCount = 0;		// 记录绘制的四边形数量

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }	// 返回总顶点数量
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }		// 返回总索引数量
		};
		static void ResetStats();		// 重置统计数据
		static Statistics GetStats();	// 获取当前的统计数据

	private:
		static void FlushAndReset();	// 用于刷新和重置渲染器状态
	};
}

