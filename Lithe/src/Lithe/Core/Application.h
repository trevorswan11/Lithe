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

	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			LI_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};

	enum class ApplicationRendererAPI
	{
		None = 0,
		OpenGL = 1,
		DirectX = 2,
		Vulkan = 3
	};

	struct ApplicationSpecification
	{
		std::string Name = "Lithe Engine";
		ApplicationCommandLineArgs CommandLineArgs = ApplicationCommandLineArgs();
		ApplicationRendererAPI ApplicationRendererAPI = ApplicationRendererAPI::OpenGL;
		std::string WorkingDirectory;
	};

	class Application
	{
	public:
		Application(ApplicationSpecification appSpec);
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		void Close();
		inline void SetWasMinimized(bool wasMinimized) { m_WasMinimized = wasMinimized; }
		inline bool GetWasMinimized() const { return m_WasMinimized; }

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline static Application& Get() { return *s_Instance; }

		ApplicationSpecification GetApplicationSpec() const { return m_AppSpec; }
		ApplicationCommandLineArgs GetCommandLineArgs() const { return m_AppSpec.CommandLineArgs; }

		void SubmitToMainThread(const std::function<void()>& function);
	private:
		void Run();

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		void ExecuteMainThreadQueue();
	private:
		ApplicationSpecification m_AppSpec;
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_WasMinimized = false;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		std::vector<std::function<void()>> m_MainThreadQueue;
		std::mutex m_MainThreadQueueMutex;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be defined in CLIENT
	Application* CreateApplication(ApplicationCommandLineArgs args);

}


