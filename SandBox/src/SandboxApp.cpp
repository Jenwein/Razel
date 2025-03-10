
#include <Razel.h>

class ExampleLayer :public Razel::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		RZ_INFO("ExampleLayer::Update");
	}

	void OnEvent(Razel::Event& event)override
	{
		RZ_TRACE("{0}", event);
	}
	
};

class Sandbox : public Razel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverLayer(new Razel::ImGuiLayer());
	}
	~Sandbox()
	{

	}

};

Razel::Application* Razel::CreateApplication()
{
	return new Sandbox();
}