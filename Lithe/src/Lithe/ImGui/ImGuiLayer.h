#pragma once

#include "Lithe/Layer.h"
#include "Lithe/Events/MouseEvent.h"
#include "Lithe/Events/KeyEvent.h"
#include "Lithe/Events/ApplicationEvent.h"

namespace Lithe {

	class LITHE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		
		bool OnWindowResizeEvent(WindowResizeEvent& e);

		// Code from @ DaveKobrin on GitHub

		static int Key2ImGuiKey(const int key);
		static void UpdateMods(const int key, const bool isPressed);
	private:
		float m_Time = 0.0f;
	};

}