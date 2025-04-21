#pragma once
#include <Razel.h>

// 创建一个2D测试环境
class Sandbox2D :public Razel::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Razel::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Razel::Event& e) override;
private:
	Razel::OrthographicCameraController m_CameraController;

	// Temp
	Razel::Ref<Razel::VertexArray> m_SquareVA;
	Razel::Ref<Razel::Shader> m_FlatColorShader;
	Razel::Ref<Razel::Texture2D> m_CheckerboardTexture;
	Razel::Ref<Razel::Framebuffer> m_Framebuffer;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};

