#pragma once

#include <Lithe.h>
#include "Panels/SceneHierarchyPanel.h"

namespace Lithe {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		EditorLayer(OrthographicCameraController& camera);
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);

		void NewScene();
		void OpenScene();
		void SaveSceneAs();
		void SaveScene();
	private:
		OrthographicCameraController m_CameraController;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;
		std::string m_SceneSaveCache;
		Entity m_FirstCameraEntity, m_SecondCameraEntity;

		bool m_PrimaryCamera = true;

		Ref<Texture2D> m_CheckerboardTexture;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = glm::vec2(0.0f);

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
	};

}
