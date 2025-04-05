#pragma once
#include "Razel.h"

class ExampleLayer :public Razel::Layer
{
public:
	ExampleLayer();

	void OnUpdate(Razel::Timestep ts) override;

	void OnEvent(Razel::Event& e) override;
	void OnImGuiRender()override;

private:
	Razel::Ref<Razel::Shader> m_Shader;
	Razel::Ref<Razel::VertexArray> m_VertexArray;

	Razel::Ref<Razel::Shader> m_FlatColorShader;
	Razel::Ref<Razel::VertexArray> m_SquareVA;

	Razel::ShaderLibrary m_ShaderLibrary;

	Razel::Ref<Razel::Texture2D> m_Texture, m_CppTexture;

	glm::vec3 m_SquareColor = glm::vec3(0.2f, 0.3f, 0.8f);


	// 正交投影相机
	Razel::OrthographicCameraController m_CameraController;
};
