#include <Lithe.h>
#include <Lithe/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Lithe::Application
{
public:
	Sandbox()
	{
		Lithe::Application::GetWindow().SetVSync(true);

		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Lithe::Application* Lithe::CreateApplication()
{
	return new Sandbox();
}