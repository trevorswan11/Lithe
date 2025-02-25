#include "lipch.h"

#include "Application.h"

#include "Lithe/Events/ApplicationEvent.h"

namespace Lithe {
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}