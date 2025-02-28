#include <Lithe.h>

class ExampleLayer : public Lithe::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
		LI_INFO("Example::Update");
	}

	void OnEvent(Lithe::Event& event) override
	{
		LI_TRACE("{0}", event);
	}
};

class Sandbox : public Lithe::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Lithe::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Lithe::Application* Lithe::CreateApplication()
{
	return new Sandbox();
}