#include <Lithe.h>

class Sandbox : public Lithe::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Lithe::Application* Lithe::CreateApplication()
{
	return new Sandbox();
}