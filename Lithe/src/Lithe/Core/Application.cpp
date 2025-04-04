#include "lipch.h"
#include "Application.h"

#include "Lithe/Core/Input.h"
#include "Lithe/Utils/PlatformUtils.h"

namespace Lithe {

	Application* Application::s_Instance = nullptr;

	Application::Application(ApplicationSpecification appSpec)
		: m_AppSpec(appSpec)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Scope<Window>(Window::Create(WindowProps(m_AppSpec.Name)));
		m_Window->SetEventCallback(LI_BIND_EVENT_FN(Application::OnEvent));

		if (!m_AppSpec.WorkingDirectory.empty())
			std::filesystem::current_path(m_AppSpec.WorkingDirectory);
		RendererAPI::SetRendererAPI((int)m_AppSpec.ApplicationRendererAPI);

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		LI_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		LI_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		LI_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		LI_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(LI_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(LI_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::Run()
	{
		LI_PROFILE_FUNCTION();

		while (m_Running)
		{
			LI_PROFILE_SCOPE("RunLoop");

			float time = Time::GetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				{
					LI_PROFILE_SCOPE("LayerStack OnUpdate");

					for (Layer* l : m_LayerStack)
						l->OnUpdate(timestep);
				}

				m_ImGuiLayer->Begin();
				{
					LI_PROFILE_SCOPE("LayerStack OnImGuiRender");

					for (Layer* l : m_LayerStack)
						l->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		LI_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			SetWasMinimized(true);
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

}
