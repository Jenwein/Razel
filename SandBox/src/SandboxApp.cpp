
#include <Razel.h>

class Sandbox : public Razel::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}

};



Razel::Application* Razel::CreateApplication()
{
	return new Sandbox();
}