#include <Lithe.h>

#include "imgui/imgui.h"

class ExampleLayer : public Lithe::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
	}

	void OnEvent(Lithe::Event& event) override
	{
		// LI_TRACE("{0}", event);

		if (event.GetEventType() == Lithe::EventType::KeyPressed)
		{
			Lithe::KeyPressedEvent& e = (Lithe::KeyPressedEvent&)event;
			if (e.GetKeyCode() == LI_KEY_TAB)
				LI_TRACE("TAB HELP ME!");
			LI_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello, World!");
		ImGui::End();
	}
};

class Sandbox : public Lithe::Application
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

Lithe::Application* Lithe::CreateApplication()
{
	return new Sandbox();
}