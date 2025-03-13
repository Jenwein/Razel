
#include <Razel.h>
#include "imgui/imgui.h"
class ExampleLayer :public Razel::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		if (Razel::Input::IsKeyPressed(RZ_KEY_TAB))
		{
			RZ_TRACE("Tab key is pressed(poll)");
		}
	}

    void OnEvent(Razel::Event& event) override
    {
        if (event.GetEventType() == Razel::EventType::KeyPressed)
        {
			Razel::KeyPressedEvent& e = (Razel::KeyPressedEvent&)event;
            if (e.GetKeyCode() == RZ_KEY_TAB)
            {
                RZ_TRACE("Tab key is pressed (event)!");
            }
            RZ_TRACE("{0}", (char)e.GetKeyCode());
        }
    }
	void OnImGuiRender()override
	{
		//ImGui::Begin("Test");
		//ImGui::Text("Hello World");
		//ImGui::End();
	}
	
};

class Sandbox : public Razel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}

};

Razel::Application* Razel::CreateApplication()
{
	return new Sandbox();
}