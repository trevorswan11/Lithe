#pragma once

#include "lipch.h"

#include "Lithe/Events/ApplicationEvent.h"

namespace Lithe {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	class LITHE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


