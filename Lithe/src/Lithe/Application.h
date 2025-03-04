#pragma once

#include "Core.h"

#include "Window.h"
#include "Lithe/LayerStack.h"
#include "Lithe/Events/Event.h"
#include "Lithe/Events/ApplicationEvent.h"

#include "Lithe/ImGui/ImGuiLayer.h"

#include "Lithe/Renderer/Shader.h"
#include "Lithe/Renderer/Buffer.h"

namespace Lithe {

	class LITHE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}


