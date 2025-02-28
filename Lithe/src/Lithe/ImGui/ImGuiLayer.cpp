#include "lipch.h"
#include "ImGuiLayer.h"

#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Lithe/Application.h"

// TEMPORARY: should not include glfw here
#include <GLFW/glfw3.h>

namespace Lithe {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer") {}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui_ImplOpenGL3_Init("#version 410");
		Application& app = Application::Get();
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate()
	{

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(LI_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(LI_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(LI_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(LI_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		
		dispatcher.Dispatch<KeyPressedEvent>(LI_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(LI_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		//dispatcher.Dispatch<KeyTypedEvent>(LI_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));

		dispatcher.Dispatch<WindowResizeEvent>(LI_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(e.GetMouseButton(), true);

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(e.GetMouseButton(), false);

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMousePosEvent(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseWheelEvent(e.GetXOffset(), e.GetYOffset());
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		return false;
	}

	/*bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
	}*/

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		return false;
	}

}