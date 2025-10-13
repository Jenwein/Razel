#include "rzpch.h"
#include "Razel/Renderer/Renderer3D.h"
#include "Razel/Renderer/VertexArray.h"
#include "Razel/Renderer/Shader.h"
#include "Razel/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Razel
{
	// TODO:Render3D

	// 渲染数据
	struct Renderer3DData
	{

	};

	static Renderer3DData s_Data;

	void Renderer3D::Init()
	{
		RZ_PROFILE_FUNCTION();

	}

	void Renderer3D::Shutdown()
	{
		RZ_PROFILE_FUNCTION();

	}

	void Renderer3D::BeginScene(const OrthographicCamera& camera)
	{
		RZ_PROFILE_FUNCTION();

		StartBatch();
	}

	void Renderer3D::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		RZ_PROFILE_FUNCTION();


		StartBatch();

	}

	void Renderer3D::BeginScene(const EditorCamera& camera)
	{
		RZ_PROFILE_FUNCTION();

		StartBatch();

	}

	void Renderer3D::EndScene()
	{
		RZ_PROFILE_FUNCTION();

		Flush();	//实际调用DrawCall
	}

	void Renderer3D::Flush()
	{
	}

	void Renderer3D::StartBatch()
	{
	}

	void Renderer3D::NextBatch()
	{
		Flush();
		StartBatch();
	}

	void Renderer3D::ResetStats()
	{
	}

	Renderer3D::Statistics Renderer3D::GetStats()
	{
		// TODO:tmp
		return Renderer3D::Statistics();
	}

}