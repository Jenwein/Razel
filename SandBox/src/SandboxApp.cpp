#include <Razel.h>
#include <Razel/Core/EntryPoint.h>

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"
#include "ExampleLayer.h"
#include "Sandbox2D.h"


class Sandbox : public Razel::Application
{
public:
	Sandbox(Razel::ApplicationCommandLineArgs args)
		:Application("SandBox", args)
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());

	}
	~Sandbox()
	{
	}

};

Razel::Application* Razel::CreateApplication(Razel::ApplicationCommandLineArgs args)
{
	return new Sandbox(args);
}