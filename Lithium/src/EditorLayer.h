#pragma once

#ifdef _MSVC_LANG
	#define _CRT_SECURE_NO_WARNINGS
#endif

#include <Lithe.h>
#include "Lithe/Renderer/EditorCamera.h"

#include "Panels/SceneHierarchyPanel.h"
#include "Panels/ContentBrowserPanel.h"

#include <optional>

namespace Lithe {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		void OnOverlayRender();

		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		void SaveSceneAs();
		void SaveScene();

		void DuplicateSelectedEntity(bool switchSelectedEntity = false);

		void OnScenePlay();
		void OnSceneSimulate();
		void OnScenePause();

		void OnSceneStop();

		// UI Panels
		void UI_Toolbar();
		void UI_Stats();
		void UI_MenuBar();
		void UI_Settings();
	private:
		OrthographicCameraController m_CameraController;
		Ref<Framebuffer> m_Framebuffer;
		EditorCamera m_EditorCamera;

		Ref<Scene> m_ActiveScene;
		Ref<Scene> m_EditorScene;
		std::optional<std::string> m_SaveSceneCache;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = glm::vec2(0.0f);
		glm::vec2 m_ViewportBounds[2];

		int m_GizmoType = -1;
		Entity m_HoveredEntity;
		bool m_ShowPhysicsColliders = false;
		bool m_OnlyShowPhysicsColliders = false;
		bool m_RenderPrimaryCameraIcon = true;
		glm::vec4 m_PhysicsColliderColor = { 0.0f, 1.0f, 0.0f, 1.0f };

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
		ContentBrowserPanel m_ContentBrowserPanel;

		enum class SceneState
		{
			Edit = 0, Play = 1, Simulate = 2
		};

		SceneState m_SceneState = SceneState::Edit;

		// Editor Resources
		Ref<Texture2D> m_IconPlay, m_IconSimulate, m_IconPause, m_IconStop, m_IconStep;
		Ref<Texture2D> m_CameraIcon;
	};

}
