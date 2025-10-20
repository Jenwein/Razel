#pragma once

#include "Razel/Renderer/Camera.h"
#include "Razel/Renderer/EditorCamera.h"

// Forward declaration
namespace Razel {
	class Model;
}

namespace Razel
{
	class Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();

		// 场景渲染
		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const EditorCamera& camera);
		static void EndScene();

		// 绘制函数
		static void DrawModel(const Ref<Model>& model, const glm::mat4& transform);

		// 统计 (暂时不实现)
		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t ModelCount = 0;
		};
		static void ResetStats();
		static Statistics GetStats();

	private:
		// 批处理函数 (暂时不实现)
		static void StartBatch();
		static void NextBatch();
		static void Flush();
	};
}