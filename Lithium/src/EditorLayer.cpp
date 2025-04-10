#include "EditorLayer.h"
#include "Lithe/Scene/SceneSerializer.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Lithe/Utils/PlatformUtils.h"
#include "Lithe/Math/Math.h"

#include <ImGuizmo.h>

namespace Lithe {

	extern const std::filesystem::path g_AssetPath;
	static Ref<Font> s_Font;

	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), m_CameraController(1280.0f / 720.0f)
	{
		s_Font = Font::GetDefault();
	}

	void EditorLayer::OnAttach()
	{
		LI_PROFILE_FUNCTION();

		m_IconPlay = Texture2D::Create("assets/resources/PlayButton.png");
		m_IconSimulate = Texture2D::Create("assets/resources/SimulateButton.png");
		m_IconPause = Texture2D::Create("assets/resources/PauseButton.png");
		m_IconStop = Texture2D::Create("assets/resources/StopButton.png");
		m_IconStep = Texture2D::Create("assets/resources/StepButton.png");

		m_CameraIcon = Texture2D::Create("assets/resources/CameraIcon.png");

		FramebufferSpec fbSpec;
		fbSpec.Attachments = {
			FramebufferTextureFormat::RGBA8,
			FramebufferTextureFormat::RED_INTEGER,
			FramebufferTextureFormat::Depth
		};
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = Framebuffer::Create(fbSpec);

		m_EditorScene = CreateRef<Scene>();
		m_ActiveScene = m_EditorScene;

		auto commandLineArgs = Application::Get().GetCommandLineArgs();
		if (commandLineArgs.Count > 1)
		{
			auto sceneFilePath = commandLineArgs[1];
			SceneSerializer serializer(m_EditorScene);
			serializer.Deserialize(sceneFilePath);
		}
		else
			NewScene();

		m_EditorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);

#if 0
		// Entity
		auto square = m_ActiveScene->CreateEntity("Green Square");
		square.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });

		auto redSquare = m_ActiveScene->CreateEntity("Red Square");
		redSquare.AddComponent<SpriteRendererComponent>(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

		m_SquareEntity = square;

		m_CameraEntity = m_ActiveScene->CreateEntity("Camera A");
		m_CameraEntity.AddComponent<CameraComponent>();

		m_SecondCamera = m_ActiveScene->CreateEntity("Camera B");
		auto& cc = m_SecondCamera.AddComponent<CameraComponent>();
		cc.Primary = false;

		class CameraController : public ScriptableEntity
		{
		public:
			virtual void OnCreate() override
			{
				auto& translation = GetComponent<TransformComponent>().Translation;
				translation.x = rand() % 10 - 5.0f;
			}

			virtual void OnDestroy() override
			{
			}

			virtual void OnUpdate(Timestep ts) override
			{
				auto& translation = GetComponent<TransformComponent>().Translation;

				float speed = 5.0f;

				if (Input::IsKeyPressed(Key::A))
					translation.x -= speed * ts;
				if (Input::IsKeyPressed(Key::D))
					translation.x += speed * ts;
				if (Input::IsKeyPressed(Key::W))
					translation.y += speed * ts;
				if (Input::IsKeyPressed(Key::S))
					translation.y -= speed * ts;
			}
		};

		m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
		m_SecondCamera.AddComponent<NativeScriptComponent>().Bind<CameraController>();
#endif

		m_SceneHierarchyPanel.SetContext(m_EditorScene);
	}

	void EditorLayer::OnDetach()
	{
		LI_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		LI_PROFILE_FUNCTION();

		// Resize
		if (FramebufferSpec spec = m_Framebuffer->GetSpec();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
			m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);

			m_EditorScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}

		// Render
		Renderer2D::ResetStats();
		m_Framebuffer->Bind();
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();

		// Clear the entity ID attachment to -1
		m_Framebuffer->ClearAttachment(1, -1);

		switch (m_SceneState)
		{
			case SceneState::Edit:
			{
				m_EditorCamera.OnUpdate(ts, !m_ViewportHovered);

				m_EditorScene->OnUpdateEditor(ts, m_EditorCamera);
				break;
			}
			case SceneState::Simulate:
			{
				m_EditorCamera.OnUpdate(ts, !m_ViewportHovered);

				m_ActiveScene->OnUpdateSimulation(ts, m_EditorCamera, m_ShowPhysicsColliders && m_OnlyShowPhysicsColliders);
				break;
			}
			case SceneState::Play:
			{
				m_ActiveScene->OnUpdateRuntime(ts);
				break;
			}
		}

		auto [mx, my] = ImGui::GetMousePos();
		mx -= m_ViewportBounds[0].x;
		my -= m_ViewportBounds[0].y;
		glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
		my = viewportSize.y - my;

		int mouseX = (int)mx;
		int mouseY = (int)my;

		if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
		{
			int pixelData = m_Framebuffer->ReadPixel(1, mouseX, mouseY);
			m_HoveredEntity = pixelData == -1 ? Entity() : Entity{ (entt::entity)pixelData, 
				m_SceneState == SceneState::Edit ? m_EditorScene.get() : m_ActiveScene.get()};
		}

		OnOverlayRender();
		
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
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		style.WindowMinSize.x = minWinSizeX;

		m_SceneHierarchyPanel.OnImGuiRender();
		m_ContentBrowserPanel.OnImGuiRender();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport", NULL, ImGuiDockNodeFlags_NoTabBar);
		auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto viewportOffset = ImGui::GetWindowPos();
		m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
		m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		if (!ImGui::IsAnyItemActive())
			Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);
		else
			Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		uint64_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
			{
				const wchar_t* path = (const wchar_t*)payload->Data;
				OpenScene(std::filesystem::path(g_AssetPath) / path);
			}
			ImGui::EndDragDropTarget();
		}

		std::string fileTarget = m_ContentBrowserPanel.GetAndClearCurrentFile();
		if (!fileTarget.empty())
			OpenScene(fileTarget);

		// Gizmos
		Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();
		if (selectedEntity && m_GizmoType != -1)
		{
			glm::mat4& cameraProjection = glm::mat4(1.0f);
			glm::mat4 cameraView = glm::mat4(1.0f);
			switch (m_SceneState)
			{
				case SceneState::Simulate:
				case SceneState::Edit:
				{
					// Editor Camera
					cameraProjection = m_EditorCamera.GetProjection();
					cameraView = m_EditorCamera.GetViewMatrix();
					ImGuizmo::SetOrthographic(false);
					break;
				}
				case SceneState::Play:
				{
					// Runtime Camera
					auto cameraEntity = m_ActiveScene->GetPrimaryCameraEntity();
					if (!cameraEntity) return;
					const auto& camera = cameraEntity.GetComponent<CameraComponent>().Camera;
					cameraProjection = camera.GetProjection();
					cameraView = glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform());
					ImGuizmo::SetOrthographic(camera.IsOrthographic());
					break;
				}
			}
			ImGuizmo::SetDrawlist();

			float windowWidth = (float)ImGui::GetWindowWidth();
			float windowHeight = (float)ImGui::GetWindowHeight();
			ImGuizmo::SetRect(m_ViewportBounds[0].x, m_ViewportBounds[0].y, m_ViewportBounds[1].x - m_ViewportBounds[0].x, m_ViewportBounds[1].y - m_ViewportBounds[0].y);

			auto& tc = selectedEntity.GetComponent<TransformComponent>();
			glm::mat4 transform = tc.GetTransform();

			// Snapping
			bool snap = Input::IsKeyPressed(Key::LeftControl);
			float snapValue = m_GizmoType == ImGuizmo::OPERATION::ROTATE ? 45.0f : 0.5f;

			float snapValues[3] = { snapValue, snapValue, snapValue };

			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
				(ImGuizmo::OPERATION)m_GizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform),
				nullptr, snap ? snapValues : nullptr);

			if (ImGuizmo::IsUsing())
			{
				glm::vec3 translation, rotation, scale;
				Math::DecomposeTransform(transform, translation, rotation, scale);

				glm::vec3 deltaRotation = rotation - tc.Rotation;
				tc.Translation = translation;
				tc.Rotation += deltaRotation;
				tc.Scale = scale;
			}
		}
		
		ImGui::End();
		ImGui::PopStyleVar();

		UI_Toolbar();
		UI_MenuBar();
		UI_Stats();
		UI_Settings();
		UI_Fonts();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		if (m_SceneState == SceneState::Edit || m_SceneState == SceneState::Simulate)
			if (m_ViewportHovered)
				m_EditorCamera.OnEvent(e);
		else if (m_SceneState == SceneState::Play)
			m_CameraController.OnEvent(e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(LI_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
		dispatcher.Dispatch<MouseButtonPressedEvent>(LI_BIND_EVENT_FN(EditorLayer::OnMouseButtonPressed));
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		// Shortcuts
		if (e.IsRepeat())
			return false;

		bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
		bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);
		switch (e.GetKeyCode())
		{
			// File interactions
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

			// Scene Shortcuts
			case Key::D:
			{
				if (control)
					DuplicateSelectedEntity(shift);
				break;
			}

			// Gizmo Shortcuts
			case Key::Q:
				m_GizmoType = -1;
				break;
			case Key::W:
				m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
				break;
			case Key::E:
				m_GizmoType = ImGuizmo::OPERATION::ROTATE;
				break;
			case Key::R:
				m_GizmoType = ImGuizmo::OPERATION::SCALE;
				break;
			default:
				break;
		}
		return false;
	}

	bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == Mouse::ButtonLeft)
		{
			if (m_ViewportHovered && !ImGuizmo::IsOver() && !Input::IsKeyPressed(Key::LeftAlt))
				m_SceneHierarchyPanel.SetSelectedEntity(m_HoveredEntity);
		}
		return false;
	}

	void EditorLayer::OnOverlayRender()
	{
		if (!m_ActiveScene || m_ActiveScene->Empty()) return;
		if (m_SceneState == SceneState::Play)
		{
			Entity camera = m_ActiveScene->GetPrimaryCameraEntity();
			Renderer2D::BeginScene(camera.GetComponent<CameraComponent>().Camera, camera.GetComponent<TransformComponent>().GetTransform());
		}
		else
			Renderer2D::BeginScene(m_EditorCamera);

		if (m_ShowPhysicsColliders)
		{
			LI_PROFILE_SCOPE("Draw Physics Colliders");
			{
				LI_PROFILE_SCOPE("Circle Collider Rendering");

				auto view = m_ActiveScene->GetAllEntitiesWith<TransformComponent, CircleCollider2DComponent>();
				for (auto entity : view) // Intellisense may be angry here, but I swear it compiles
				{
					auto [tc, cc2d] = view.get<TransformComponent, CircleCollider2DComponent>(entity);

					glm::vec3 translation = tc.Translation + glm::vec3(cc2d.Offset, 0.001f);
					glm::vec3 scale = tc.Scale * glm::vec3(cc2d.Radius * 2.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), translation)
						* glm::scale(glm::mat4(1.0f), scale);

					Renderer2D::DrawCircle(transform, m_PhysicsColliderColor, 0.075f);
				}
			}

			{
				LI_PROFILE_SCOPE("Box Collider Rendering");

				auto view = m_ActiveScene->GetAllEntitiesWith<TransformComponent, BoxCollider2DComponent>();
				for (auto entity : view) // Intellisense may be angry here, but I swear it compiles
				{
					auto [tc, bc2d] = view.get<TransformComponent, BoxCollider2DComponent>(entity);

					glm::vec3 scale = tc.Scale * glm::vec3(bc2d.Size * 2.0f, 1.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), tc.Translation)
						* glm::rotate(glm::mat4(1.0f), tc.Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f))
						* glm::translate(glm::mat4(1.0f), glm::vec3(bc2d.Offset, 0.001f))
						* glm::scale(glm::mat4(1.0f), scale);

					Renderer2D::DrawRect(transform, m_PhysicsColliderColor);
				}
			}

		}

		if (m_RenderPrimaryCameraIcon)
		{
			LI_PROFILE_SCOPE("Camera Location Rendering");

			auto cameraEntity = m_EditorScene->GetPrimaryCameraEntity();
			if (cameraEntity && (m_SceneState == SceneState::Edit || m_SceneState == SceneState::Simulate))
			{
				const auto& cameraTransformComponent = cameraEntity.GetComponent<TransformComponent>();
				const auto& cameraTranslation = cameraTransformComponent.Translation;

				Renderer2D::DrawQuad(cameraTranslation, { 2.0f, 2.0f }, m_CameraIcon);
			}
		}

		Renderer2D::EndScene();
	}

	void EditorLayer::NewScene()
	{
		if (m_SceneState != SceneState::Edit)
			OnSceneStop();

		LITHIUM_INFO("Creating Scene");
		m_EditorScene = CreateRef<Scene>();
		m_EditorScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		m_SceneHierarchyPanel.SetContext(m_EditorScene);
		m_SaveSceneCache = std::nullopt;
	
		m_ActiveScene = m_EditorScene;
	}

	void EditorLayer::OpenScene()
	{
		std::optional<std::string> filepath = FileDialogs::OpenFile("Lithe Scene (*.lithe)\0*.lithe\0");
		if (filepath)
			OpenScene(*filepath);
	}

	void EditorLayer::OpenScene(const std::filesystem::path& path)
	{
		if (path.extension().string() != ".lithe")
		{
			LITHIUM_WARN("Could not load {0} - not a scene file", path.filename().string());
			return;
		}

		if (m_SceneState != SceneState::Edit)
			OnSceneStop();

		try
		{
			Ref<Scene> newScene = CreateRef<Scene>();
			SceneSerializer serializer(newScene);
			
			if (serializer.Deserialize(path.string()))
			{
				m_EditorScene = newScene;
				m_EditorScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
				m_SaveSceneCache = path.string();
				m_SceneHierarchyPanel.SetContext(m_EditorScene);

				LITHIUM_INFO("Opening Scene: {0}", *m_SaveSceneCache);

				m_ActiveScene = m_EditorScene;
			}
		}
		catch (const std::exception& e)
		{
			LITHIUM_ERROR("Failed to open scene {0}: {1}", path.string(), e.what());
		}
	}

	void EditorLayer::SaveSceneAs()
	{
		if (m_SceneState != SceneState::Edit)
			OnSceneStop();

		std::optional<std::string> filepath = FileDialogs::SaveFile("Lithe Scene (*.lithe)\0*.lithe\0");
		if (filepath)
		{
			SceneSerializer serializer(m_EditorScene);
			serializer.Serialize(*filepath);
			m_SaveSceneCache = *filepath;
			LITHIUM_INFO("Saving Scene: {0}", *m_SaveSceneCache);
		}
	}

	void EditorLayer::SaveScene()
	{
		if (m_SaveSceneCache)
		{
			SceneSerializer serializer(m_EditorScene);
			serializer.Serialize(*m_SaveSceneCache);
			LITHIUM_INFO("Saving Scene: {0}", *m_SaveSceneCache);
		}
		else
			SaveSceneAs();
	}

	void EditorLayer::DuplicateSelectedEntity(bool switchSelectedEntity)
	{
		if (m_SceneState != SceneState::Edit) return;

		Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();
		if (selectedEntity)
		{
			Entity clonedEntity = m_EditorScene->CloneEntity(selectedEntity);
			if (switchSelectedEntity) m_SceneHierarchyPanel.SetSelectedEntity(clonedEntity);
		}
	}

	void EditorLayer::OnScenePlay()
	{
		if (m_SceneState == SceneState::Simulate)
			OnSceneStop();

		if (m_EditorScene && m_EditorScene->GetEntityCount() > 0)
		{
			m_ActiveScene = Scene::Copy(m_EditorScene);
			m_SceneState = SceneState::Play;
			m_SceneHierarchyPanel.SetContext(m_ActiveScene);
			m_ActiveScene->OnRuntimeStart();
		}
	}

	void EditorLayer::OnSceneSimulate()
	{
		if (m_SceneState == SceneState::Play)
			OnSceneStop();

		if (m_EditorScene && m_EditorScene->GetEntityCount() > 0)
		{
			m_ActiveScene = Scene::Copy(m_EditorScene);
			m_SceneState = SceneState::Simulate;
			m_SceneHierarchyPanel.SetContext(m_ActiveScene);
			m_ActiveScene->OnSimulationStart();
		}
	}

	void EditorLayer::OnScenePause()
	{
		if (m_SceneState == SceneState::Edit)
			return;

		m_ActiveScene->SetPaused(true);
	}

	void EditorLayer::OnSceneStop()
	{
		LI_CORE_ASSERT(m_SceneState == SceneState::Play || m_SceneState == SceneState::Simulate);
		m_SceneState = SceneState::Edit;

		m_SceneHierarchyPanel.SetContext(m_EditorScene);
		if (m_SceneState == SceneState::Play)
			m_ActiveScene->OnRuntimeStop();
		else if (m_SceneState == SceneState::Simulate)
			m_ActiveScene->OnSimulationStop();
		m_ActiveScene = m_EditorScene;
	}

	void EditorLayer::UI_Toolbar()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 2.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		const auto& colors = ImGui::GetStyle().Colors;
		const auto& buttonHovered = colors[ImGuiCol_ButtonHovered];
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, 
			ImVec4(buttonHovered.x, buttonHovered.y, buttonHovered.z, 0.5f));
		const auto& buttonActive = colors[ImGuiCol_ButtonActive];
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, 
			ImVec4(buttonActive.x, buttonActive.y, buttonActive.z, 0.5f));
		ImGui::Begin("##toolbar", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiDockNodeFlags_NoTabBar);

		bool toolbarEnabled = !m_ActiveScene->Empty();
		ImVec4 tintColor = ImVec4(1, 1, 1, 1);
		if (!toolbarEnabled)
			tintColor.w = 0.5f;

		float size = ImGui::GetWindowHeight() - 4.0f;
		ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) - (size * 0.5f));

		bool hasPlayButton = m_SceneState == SceneState::Edit || m_SceneState == SceneState::Play;
		bool hasSimulateButton = m_SceneState == SceneState::Edit || m_SceneState == SceneState::Simulate;
		bool hasPauseButton = m_SceneState != SceneState::Edit;

		if (hasPlayButton)
		{
			Ref<Texture2D> icon = (m_SceneState == SceneState::Edit || m_SceneState == SceneState::Simulate) ? m_IconPlay : m_IconStop;
			if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(static_cast<uint64_t>(icon->GetRendererID())), ImVec2(size, size), ImVec2(0, 0), ImVec2(1, 1), 0, ImVec4(0.0f, 0.0f, 0.0f, 0.0f), tintColor) && toolbarEnabled)
			{
				if (m_SceneState == SceneState::Edit || m_SceneState == SceneState::Simulate)
					OnScenePlay();
				else if (m_SceneState == SceneState::Play)
					OnSceneStop();
			}
		}
		
		if (hasSimulateButton)
		{
			if (hasPlayButton) ImGui::SameLine();
			Ref<Texture2D> icon = (m_SceneState == SceneState::Edit || m_SceneState == SceneState::Play) ? m_IconSimulate : m_IconStop;
			if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(static_cast<uint64_t>(icon->GetRendererID())),
				ImVec2(size, size), ImVec2(0, 0), ImVec2(1, 1), 0, ImVec4(0.0f, 0.0f, 0.0f, 0.0f), tintColor) && toolbarEnabled)
			{
				if (m_SceneState == SceneState::Edit || m_SceneState == SceneState::Play)
					OnSceneSimulate();
				else if (m_SceneState == SceneState::Simulate)
					OnSceneStop();
			}
		}

		if (hasPauseButton)
		{
			bool isPaused = m_ActiveScene->IsPaused();
			ImGui::SameLine();
			{
				Ref<Texture2D> icon = m_IconPause;
				if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(static_cast<uint64_t>(icon->GetRendererID())),
					ImVec2(size, size), ImVec2(0, 0), ImVec2(1, 1), 0, ImVec4(0.0f, 0.0f, 0.0f, 0.0f), tintColor) && toolbarEnabled)
				{
					m_ActiveScene->SetPaused(!isPaused);
				}
			}

			if (isPaused)
			{
				ImGui::SameLine();
				{
					Ref<Texture2D> icon = m_IconStep;
					bool isPaused = m_ActiveScene->IsPaused();
					if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(static_cast<uint64_t>(icon->GetRendererID())),
						ImVec2(size, size), ImVec2(0, 0), ImVec2(1, 1), 0, ImVec4(0.0f, 0.0f, 0.0f, 0.0f), tintColor) && toolbarEnabled)
					{
						m_ActiveScene->Step();
					}
				}
			}
		}
		
		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor(3);
		ImGui::End();
	}

	void EditorLayer::UI_Settings()
	{
		ImGui::Begin("Settings");

		if (m_ActiveScene)
		{
			if (m_SceneState == SceneState::Play)
				ImGui::Text("Playing Scene: %s", m_ActiveScene->GetName().c_str());
			else if (m_SceneState == SceneState::Simulate)
				ImGui::Text("Simulating Scene: %s", m_ActiveScene->GetName().c_str());
			else
			{
				char buffer[256];
				memset(buffer, 0, sizeof(buffer));
				std::strncpy(buffer, m_ActiveScene->GetName().c_str(), sizeof(buffer));
				if (ImGui::InputText("Scene Name", buffer, sizeof(buffer)))
				{
					std::string newName = std::string(buffer);
					if (!newName.empty()) m_ActiveScene->SetName(newName);
				}
			}
		}

		ImGui::Separator();
		ImGui::Checkbox("Show Physics Colliders", &m_ShowPhysicsColliders);
		if (m_ShowPhysicsColliders)
			ImGui::ColorEdit4("Color", glm::value_ptr(m_PhysicsColliderColor));
		else
		{
			ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
			ImGui::ColorEdit4("Color", glm::value_ptr(m_PhysicsColliderColor));
			ImGui::PopItemFlag();
		}

		ImGui::Separator();

		if (ImGui::Checkbox("Only Show Colliders on Simulate", &m_OnlyShowPhysicsColliders) && m_OnlyShowPhysicsColliders)
			m_ShowPhysicsColliders = m_OnlyShowPhysicsColliders;

		ImGui::Separator();

		ImGui::Checkbox("Render Primary Camera Icon", &m_RenderPrimaryCameraIcon);

		ImGui::Separator();

		auto boldFont = ImGui::GetIO().Fonts->Fonts[(int)ImGuiFonts::Bold];
		{
			if (m_SceneState != SceneState::Edit)
				ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);

			ImGui::PushFont(boldFont);
			ImGui::Text("Physics Velocity Iterations:");
			ImGui::PopFont();
			auto& sceneVelocityItr = m_EditorScene->GetVelocityIterations();
			if (ImGui::SliderInt("##VelocityItr", &sceneVelocityItr, 6, 100))
				m_EditorScene->SetVelocityIterations(sceneVelocityItr);
			ImGui::PushFont(boldFont);
			ImGui::Text("Physics Position Iterations:");
			ImGui::PopFont();
			auto& scenePositionItr = m_EditorScene->GetPositionIterations();
			if (ImGui::SliderInt("##PositionItr", &scenePositionItr, 2, 100))
				m_EditorScene->SetPositionIterations(scenePositionItr);

			if (m_SceneState != SceneState::Edit)
				ImGui::PopItemFlag();
		}

		ImGui::End();
	}

	void EditorLayer::UI_Fonts()
	{
		ImGui::Begin("Font Atlas");
		ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<uint64_t>(s_Font->GetAtlasTexture()->GetRendererID())),
			{ 512,512 }, { 0, 1 }, { 1, 0 });
		ImGui::End();
	}

	void EditorLayer::UI_Stats()
	{
		ImGui::Begin("Stats");

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Circles: %d", stats.CircleCount);
		ImGui::Text("Lines: %d", stats.LineCount);
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
	}

	void EditorLayer::UI_MenuBar()
	{
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
				if (ImGui::MenuItem("Revert Changes"))
					if (m_SaveSceneCache) OpenScene(*m_SaveSceneCache);
				if (ImGui::MenuItem("Exit"))
					Application::Get().Close();
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Gizmos"))
			{
				if (ImGui::MenuItem("None", "Q"))
					m_GizmoType = -1;
				if (ImGui::MenuItem("Translate", "W"))
					m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
				if (ImGui::MenuItem("Rotate", "E"))
					m_GizmoType = ImGuizmo::OPERATION::ROTATE;
				if (ImGui::MenuItem("Scale", "R"))
					m_GizmoType = ImGuizmo::OPERATION::SCALE;
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Editor Camera"))
			{
				if (ImGui::MenuItem("Reset Camera"))
					m_EditorCamera.Reset();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
	}

}
