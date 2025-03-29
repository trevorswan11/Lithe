#include "EditorLayer.h"
#include "Lithe/Scene/SceneSerializer.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Lithe/Utils/PlatformUtils.h"

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

		m_ActiveScene = CreateRef<Scene>();
#if 0
		// Square
		auto squareA = m_ActiveScene->CreateEntity("Square A");
		squareA.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });

		auto squareB = m_ActiveScene->CreateEntity("Square B");
		squareB.AddComponent<SpriteRendererComponent>(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });
		squareB.GetComponent<TransformComponent>().Translation.x = -2.0f;

		// Cameras
		m_FirstCameraEntity = m_ActiveScene->CreateEntity("First Camera (A)");
		m_FirstCameraEntity.AddComponent<CameraComponent>().Primary = true;

		m_SecondCameraEntity = m_ActiveScene->CreateEntity("Second Camera (B)");
		m_SecondCameraEntity.AddComponent<CameraComponent>();

		class CameraController : public ScriptableEntity
		{
		public:
			void OnCreate()
			{
			}

			void OnDestroy()
			{

			}

			void OnUpdate(Timestep ts)
			{
				auto& translation = GetComponent<TransformComponent>().Translation;
				float speed = 5.0f;

				if (Input::IsKeyPressed(KeyCode::A))
					translation.x -= speed * ts;
				else if (Input::IsKeyPressed(KeyCode::D))
					translation.x += speed * ts;
				if (Input::IsKeyPressed(KeyCode::W))
					translation.y += speed * ts;
				else if (Input::IsKeyPressed(KeyCode::S))
					translation.y -= speed * ts;
			}
		};

		m_FirstCameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
#endif
		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
	}

	void EditorLayer::OnDetach()
	{
		LI_PROFILE_FUNCTION();

	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		LI_PROFILE_FUNCTION();

		if (FramebufferSpec spec = m_Framebuffer->GetSpec();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f &&
			(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);

			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}

		// Camera fix on Reopen
		if (Application::Get().GetWasMinimized())
		{
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			Application::Get().SetWasMinimized(false);
		}

		// Update
		if (m_ViewportFocused)
		{
			m_CameraController.OnUpdate(ts);
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
		}

		// Render
		Renderer2D::ResetStats();
		m_Framebuffer->Bind();
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();

		// Update Scene
		m_ActiveScene->OnUpdate(ts);

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		LI_PROFILE_FUNCTION();

		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

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

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Lithium DockSpace", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWidthSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		style.WindowMinSize.x = minWidthSizeX;

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New", "Ctrl+N"))
					NewScene();

				if (ImGui::MenuItem("Open...", "Ctrl+O"))
					OpenScene();

				if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
					SaveSceneAs();

				if (ImGui::MenuItem("Save", "Ctrl+S"))
					SaveScene();

				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		m_SceneHierarchyPanel.OnImGuiRender();

		ImGui::Begin("Stats");

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		{
			ImGui::Separator();
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
			ImGui::Separator();
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

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(LI_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		// Shortcuts
		if (e.GetRepeatCount() > 0)
			return false;

		bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
		bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);
		switch (e.GetKeyCode())
		{
			case Key::N:
			{
				if (control)
					NewScene();
				break;
			}
			case Key::O:
			{
				if (control)
					OpenScene();
				break;
			}
			case Key::S:
			{
				if (control && shift)
					SaveSceneAs();
				else if (control)
					SaveScene();

				break;
			}
			default:
				break;
		}
		return false;
	}

	void EditorLayer::NewScene()
	{
		m_ActiveScene = CreateRef<Scene>();
		m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
		m_SceneSaveCache = std::string();
		LI_INFO("Creating Scene");
	}

	void EditorLayer::OpenScene()
	{
		std::string filepath = FileDialogs::OpenFile("Lithe Scene (*.lithe)\0*.lithe\0");
		if (!filepath.empty())
		{
			m_ActiveScene->Reset();
			m_ActiveScene = CreateRef<Scene>();
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_SceneHierarchyPanel.SetContext(m_ActiveScene);

			SceneSerializer serializer(m_ActiveScene);
			serializer.Deserialize(filepath);
			m_SceneSaveCache = filepath;
			LI_INFO("Opening Scene: {0}", m_SceneSaveCache);
		}
	}

	void EditorLayer::SaveSceneAs()
	{
		std::string filepath = FileDialogs::SaveFile("Lithe Scene (*.lithe)\0*.lithe\0");
		if (!filepath.empty())
		{
			SceneSerializer serializer(m_ActiveScene);
			serializer.Serialize(filepath);
			m_SceneSaveCache = filepath;
			LI_INFO("Saving Scene: {0}", m_SceneSaveCache);
		}
	}

	void EditorLayer::SaveScene()
	{
		if (!m_SceneSaveCache.empty())
		{
			SceneSerializer serializer(m_ActiveScene);
			serializer.Serialize(m_SceneSaveCache);
			LI_INFO("Saving Scene: {0}", m_SceneSaveCache);
		}
		else
			SaveSceneAs();
	}

}
