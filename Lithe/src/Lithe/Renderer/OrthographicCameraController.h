#pragma once

#include "Lithe/Core/Base.h"
#include "Lithe/Renderer/OrthographicCamera.h"
#include "Lithe/Core/Timestep.h"

#include "Lithe/Events/ApplicationEvent.h"
#include "Lithe/Events/MouseEvent.h"

namespace Lithe {

	class OrthographicCameraController
	{
	public:
		struct CameraBounds
		{
			float Top, Bottom;
			float Left, Right;

			CameraBounds(float left, float right, float bottom, float top)
				: Top(top), Bottom(bottom), Left(left), Right(right) {}

			float GetWidth() const { return Right - Left; }
			float GetHeight() const { return Top - Bottom; }
		};
	public:
		OrthographicCameraController(float aspectratio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level)
		{ 
			m_ZoomLevel = level; 
			CalculateView();
		}

		CameraBounds& GetBounds() { return m_CameraBounds; }
		void SetBounds(CameraBounds bounds) { m_CameraBounds = bounds; }
		void SetBounds(float left, float right, float bottom, float top)
		{
			m_CameraBounds.Top = top;
			m_CameraBounds.Bottom = bottom;
			m_CameraBounds.Left = left;
			m_CameraBounds.Right = right;
		}
	private:
		void CalculateView();

		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;
		CameraBounds m_CameraBounds;

		bool m_Rotation;
		
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		// Counter-clockwise degrees
		float m_CameraRotation = 0.0f;

		float m_CameraTranslationSpeed = 5.0f, m_CameraRotaionSpeed = 180.0f;
	};

}
