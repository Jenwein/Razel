#pragma once

#include "Razel/Renderer/Texture.h"

#include "Razel/Renderer/Camera.h"
#include "Razel/Renderer/EditorCamera.h"
#include "Razel/Renderer/OrthographicCameraController.h"
#include "Razel/Scene/Components.h"
namespace Razel
{
	// 2D渲染静态类,封装一些渲染指令,管理场景数据,隐藏底层渲染API
	class Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();

		// 场景渲染
		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const EditorCamera& camera);	//TODO:Remove
		static void BeginScene(const OrthographicCamera& camera);	//TODO:Remove
		//static void BeginScene(const PerspectiveCamera& camera);

		static void EndScene();
		static void Flush();

		static float GetLineWidth();
		static void SetLineWidth(float width);

		// 统计
		struct Statistics
		{
		};
		static void ResetStats();		// 重置统计数据
		static Statistics GetStats();	// 获取当前的统计数据

	private:

		static void StartBatch();
		static void NextBatch();
	};
}

