#include "rzpch.h"
#include "Razel/Renderer/Renderer3D.h"

#include "Razel/Renderer/RenderCommand.h"
#include "Razel/Renderer/Shader.h"
#include "Model.h"

namespace Razel
{
	struct Renderer3DData
	{
		Ref<Shader> ModelShader;
		glm::mat4 ViewProjectionMatrix;
	};

	static Renderer3DData s_Data;

	void Renderer3D::Init()
	{
		RZ_PROFILE_FUNCTION();
		s_Data.ModelShader = Shader::Create("assets/shaders/Renderer3D.glsl");
	}

	void Renderer3D::Shutdown()
	{
		RZ_PROFILE_FUNCTION();
	}

	void Renderer3D::BeginScene(const EditorCamera& camera)
	{
		RZ_PROFILE_FUNCTION();
		s_Data.ViewProjectionMatrix = camera.GetViewProjection();
	}

	void Renderer3D::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		RZ_PROFILE_FUNCTION();
		s_Data.ViewProjectionMatrix = camera.GetProjection() * glm::inverse(transform);
	}

	void Renderer3D::EndScene()
	{
		RZ_PROFILE_FUNCTION();
		// 目前没有批处理，所以这里为空
	}

	void Renderer3D::DrawModel(const Ref<Model>& model, const glm::mat4& transform)
	{
		s_Data.ModelShader->Bind();
		s_Data.ModelShader->SetMat4("u_ViewProjection", s_Data.ViewProjectionMatrix);
		s_Data.ModelShader->SetMat4("u_Transform", transform);

		model->Draw(s_Data.ModelShader);
	}


	// 其他函数暂时保持为空
	void Renderer3D::Flush() {}
	void Renderer3D::StartBatch() {}
	void Renderer3D::NextBatch() {}
	void Renderer3D::ResetStats() {}
	Renderer3D::Statistics Renderer3D::GetStats() { return {}; }

}