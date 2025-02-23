#include "lipch.h"

#include "Application.h"

#include "Lithe/Events/ApplicationEvent.h"

namespace Lithe {
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1200, 700);
		LI_TRACE(e);
		while (true);
	}
}