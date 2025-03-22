#pragma once

#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Shader.h"
namespace Razel
{
	class Renderer
	{
	public:
		// 设置场景信息
		static void BeginScene(OrthographicCamera& camera);
		
		// 结束场景，准备渲染
		static void EndScene();

		// 提交要渲染的几何体
		static void Submit(const Ref<Shader>& shader,const Ref<VertexArray>& vertexArray,const glm::mat4& transform = glm::mat4(1.0f));
		
		// 获取当前的渲染API
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }


	private:
		// 场景数据
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix = glm::mat4(1.0f);
		};
		static SceneData* m_SceneData;
	};
}