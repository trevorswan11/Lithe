#pragma once

#include "Lithe/Core/Base.h"

#include "Lithe/Core/Window.h"
#include "Lithe/Core/LayerStack.h"
#include "Lithe/Events/Event.h"
#include "Lithe/Events/ApplicationEvent.h"

#include "Lithe/Renderer/Renderer.h"

#include "Lithe/Core/Timestep.h"

#include "Lithe/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Lithe {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

		void Close();
	private:
		void Run();

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}


