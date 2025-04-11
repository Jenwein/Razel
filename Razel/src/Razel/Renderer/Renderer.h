#pragma once

#include "Razel/Renderer/RenderCommand.h"

#include "Razel/Renderer/OrthographicCamera.h"
#include "Razel/Renderer/Shader.h"
namespace Razel
{
	class Renderer
	{
	public:

		// 初始化渲染
		static void Init();

		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		// 设置场景信息,scene负责组织和管理所有需要渲染的
		static void BeginScene(OrthographicCamera& camera);
		
		// 结束场景，准备渲染
		static void EndScene();

		// 提交要渲染的几何体
		static void Submit(const Ref<Shader>& shader,const Ref<VertexArray>& vertexArray,const glm::mat4& transform = glm::mat4(1.0f));
		
		// 获取当前的渲染API
		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }


	private:
		// 场景数据
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix = glm::mat4(1.0f);
		};
		static SceneData* s_SceneData;
	};
}