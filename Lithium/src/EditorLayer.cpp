#include "EditorLayer.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Lithe {
	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), m_CameraController(1280.0f / 720.0f, true)
	{
	}

	EditorLayer::EditorLayer(OrthographicCameraController& camera)
		: Layer("EditorLayer"), m_CameraController(camera)
	{
	}

	void EditorLayer::OnAttach()
	{
		LI_PROFILE_FUNCTION();

		m_CheckerboardTexture = Texture2D::Create("assets/textures/CheckerboardExample.png");

		FramebufferSpec fbSpec;
		fbSpec.Width = Application::Get().GetWindow().GetWidth();
		fbSpec.Height = Application::Get().GetWindow().GetHeight();
		m_Framebuffer = Framebuffer::Create(fbSpec);

		m_CameraController.SetZoomLevel(5.0f);
	}

	void EditorLayer::OnDetach()
	{
		LI_PROFILE_FUNCTION();

	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		LI_PROFILE_FUNCTION();

		if (Lithe::FramebufferSpec spec = m_Framebuffer->GetSpec();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f &&
			(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
		}

		// Update
		if (m_ViewportFocused)
		{
			m_CameraController.OnUpdate(ts);
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
		}

		// Render
		Renderer2D::ResetStats();
		{
			LI_PROFILE_SCOPE("Sandbox2D Renderer Prep");
			m_Framebuffer->Bind();
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			RenderCommand::Clear();
		}

		{
			LI_PROFILE_SCOPE("Sandbox2D Renderer Draw");

			static float rotation = 0.0f;
			rotation += ts * 1.0f;

			Renderer2D::BeginScene(m_CameraController.GetCamera());

			Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);

			Renderer2D::DrawRotatedQuad({ -1.0f, -3.0f, 0.2f }, glm::radians(20.0f), { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
			Renderer2D::DrawQuad({ 0.5f, -0.5f, 0.2f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
			Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.2f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });

			Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, 0.3f }, rotation, { 1.0f, 1.0f }, m_CheckerboardTexture, m_SquareColor, 1.0f);

			Renderer2D::EndScene();

			Renderer2D::BeginScene(m_CameraController.GetCamera());

			for (float y = -5.0f; y < 5.0f; y += 0.5f)
			{
				for (float x = -5.0f; x < 5.0f; x += 0.5f)
				{
					glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
					Renderer2D::DrawQuad({ x, y, 0.1f }, { 0.45f, 0.45f }, color);
				}
			}
			Renderer2D::EndScene();
			m_Framebuffer->Unbind();
		}
	}

	void EditorLayer::OnImGuiRender()
	{
		LI_PROFILE_FUNCTION();

		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

		{
			LI_PROFILE_SCOPE("ImGui Average FPS");

			static float fpsHistory[100] = {};
			static int fpsIndex = 0;
			static float fpsSum = 0.0f;

			float currentFps = 1.0f / ImGui::GetIO().DeltaTime;
			fpsSum -= fpsHistory[fpsIndex];
			fpsSum += currentFps;
			fpsHistory[fpsIndex] = currentFps;

			fpsIndex = (fpsIndex + 1) % 100;
			float avgFps = fpsSum / 100.0f;
			ImGui::Text("Avg FPS: %.1f", avgFps);
		}

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		uintptr_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar();
		
		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		LI_PROFILE_FUNCTION();

		m_CameraController.OnEvent(e);
	}

}
