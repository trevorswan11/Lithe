#include <Lithe.h>
#include <Lithe/Core/EntryPoint.h>

#include "ExampleLayer.h"

#include "Sandbox2D.h"
#include "Particles/ParticleSystemLayer.h"
#include "Game/GameLayer.h"

class Sandbox : public Lithe::Application
{
public:
	Sandbox()
	{
		Lithe::Application::GetWindow().SetVSync(true);
		Lithe::OrthographicCameraController camera(1280.0f / 720.0f, true);

		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D(camera));
		//PushLayer(new ParticleSystemLayer(camera));
		//PushLayer(new GameLayer(camera));
	}

	~Sandbox()
	{
	}
};

Lithe::Application* Lithe::CreateApplication()
{
	return new Sandbox();
}