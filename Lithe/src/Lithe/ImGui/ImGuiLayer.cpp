#include "lipch.h"
#include "ImGuiLayer.h"

#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Lithe/Application.h"
#include "Lithe/InputCodes.h"

// TEMPORARY: should not include glfw here
#include <GLFW/glfw3.h>
#include <glad/glad.h>

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
		dispatcher.Dispatch<KeyTypedEvent>(LI_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));

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

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
        UpdateMods(e.GetKeyCode(), true);

		ImGuiIO& io = ImGui::GetIO();
		io.AddKeyEvent((ImGuiKey)Key2ImGuiKey(e.GetKeyCode()), true);

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
        UpdateMods(e.GetKeyCode(), false);

        ImGuiIO& io = ImGui::GetIO();
        io.AddKeyEvent((ImGuiKey)Key2ImGuiKey(e.GetKeyCode()), false);

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
        ImGuiIO& io = ImGui::GetIO();
        int keycode = e.GetKeyCode();
        if (keycode > 0 && keycode < 0x10000)
            io.AddInputCharacter((unsigned short)keycode);

        return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		/*ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());*/

		return false;
	}

    int ImGuiLayer::Key2ImGuiKey(const int key)
    {
        switch (key)
        {
        case LI_KEY_TAB:            return ImGuiKey_Tab;
        case LI_KEY_LEFT:           return ImGuiKey_LeftArrow;
        case LI_KEY_RIGHT:          return ImGuiKey_RightArrow;
        case LI_KEY_UP:             return ImGuiKey_UpArrow;
        case LI_KEY_DOWN:           return ImGuiKey_DownArrow;
        case LI_KEY_PAGE_UP:        return ImGuiKey_PageUp;
        case LI_KEY_PAGE_DOWN:      return ImGuiKey_PageDown;
        case LI_KEY_HOME:           return ImGuiKey_Home;
        case LI_KEY_END:            return ImGuiKey_End;
        case LI_KEY_INSERT:         return ImGuiKey_Insert;
        case LI_KEY_DELETE:         return ImGuiKey_Delete;
        case LI_KEY_BACKSPACE:      return ImGuiKey_Backspace;
        case LI_KEY_SPACE:          return ImGuiKey_Space;
        case LI_KEY_ENTER:          return ImGuiKey_Enter;
        case LI_KEY_ESCAPE:         return ImGuiKey_Escape;
        case LI_KEY_APOSTROPHE:     return ImGuiKey_Apostrophe;
        case LI_KEY_COMMA:          return ImGuiKey_Comma;
        case LI_KEY_MINUS:          return ImGuiKey_Minus;
        case LI_KEY_PERIOD:         return ImGuiKey_Period;
        case LI_KEY_SLASH:          return ImGuiKey_Slash;
        case LI_KEY_SEMICOLON:      return ImGuiKey_Semicolon;
        case LI_KEY_EQUAL:          return ImGuiKey_Equal;
        case LI_KEY_LEFT_BRACKET:   return ImGuiKey_LeftBracket;
        case LI_KEY_BACKSLASH:      return ImGuiKey_Backslash;
        case LI_KEY_RIGHT_BRACKET:  return ImGuiKey_RightBracket;
        case LI_KEY_GRAVE_ACCENT:   return ImGuiKey_GraveAccent;
        case LI_KEY_CAPS_LOCK:      return ImGuiKey_CapsLock;
        case LI_KEY_SCROLL_LOCK:    return ImGuiKey_ScrollLock;
        case LI_KEY_NUM_LOCK:       return ImGuiKey_NumLock;
        case LI_KEY_PRINT_SCREEN:   return ImGuiKey_PrintScreen;
        case LI_KEY_PAUSE:          return ImGuiKey_Pause;
        case LI_KEY_KP_0:           return ImGuiKey_Keypad0;
        case LI_KEY_KP_1:           return ImGuiKey_Keypad1;
        case LI_KEY_KP_2:           return ImGuiKey_Keypad2;
        case LI_KEY_KP_3:           return ImGuiKey_Keypad3;
        case LI_KEY_KP_4:           return ImGuiKey_Keypad4;
        case LI_KEY_KP_5:           return ImGuiKey_Keypad5;
        case LI_KEY_KP_6:           return ImGuiKey_Keypad6;
        case LI_KEY_KP_7:           return ImGuiKey_Keypad7;
        case LI_KEY_KP_8:           return ImGuiKey_Keypad8;
        case LI_KEY_KP_9:           return ImGuiKey_Keypad9;
        case LI_KEY_KP_DECIMAL:     return ImGuiKey_KeypadDecimal;
        case LI_KEY_KP_DIVIDE:      return ImGuiKey_KeypadDivide;
        case LI_KEY_KP_MULTIPLY:    return ImGuiKey_KeypadMultiply;
        case LI_KEY_KP_SUBTRACT:    return ImGuiKey_KeypadSubtract;
        case LI_KEY_KP_ADD:         return ImGuiKey_KeypadAdd;
        case LI_KEY_KP_ENTER:       return ImGuiKey_KeypadEnter;
        case LI_KEY_KP_EQUAL:       return ImGuiKey_KeypadEqual;
        case LI_KEY_LEFT_SHIFT:     return ImGuiKey_LeftShift;
        case LI_KEY_LEFT_CONTROL:   return ImGuiKey_LeftCtrl;
        case LI_KEY_LEFT_ALT:       return ImGuiKey_LeftAlt;
        case LI_KEY_LEFT_SUPER:     return ImGuiKey_LeftSuper;
        case LI_KEY_RIGHT_SHIFT:    return ImGuiKey_RightShift;
        case LI_KEY_RIGHT_CONTROL:  return ImGuiKey_RightCtrl;
        case LI_KEY_RIGHT_ALT:      return ImGuiKey_RightAlt;
        case LI_KEY_RIGHT_SUPER:    return ImGuiKey_RightSuper;
        case LI_KEY_MENU:           return ImGuiKey_Menu;
        case LI_KEY_0:              return ImGuiKey_0;
        case LI_KEY_1:              return ImGuiKey_1;
        case LI_KEY_2:              return ImGuiKey_2;
        case LI_KEY_3:              return ImGuiKey_3;
        case LI_KEY_4:              return ImGuiKey_4;
        case LI_KEY_5:              return ImGuiKey_5;
        case LI_KEY_6:              return ImGuiKey_6;
        case LI_KEY_7:              return ImGuiKey_7;
        case LI_KEY_8:              return ImGuiKey_8;
        case LI_KEY_9:              return ImGuiKey_9;
        case LI_KEY_A:              return ImGuiKey_A;
        case LI_KEY_B:              return ImGuiKey_B;
        case LI_KEY_C:              return ImGuiKey_C;
        case LI_KEY_D:              return ImGuiKey_D;
        case LI_KEY_E:              return ImGuiKey_E;
        case LI_KEY_F:              return ImGuiKey_F;
        case LI_KEY_G:              return ImGuiKey_G;
        case LI_KEY_H:              return ImGuiKey_H;
        case LI_KEY_I:              return ImGuiKey_I;
        case LI_KEY_J:              return ImGuiKey_J;
        case LI_KEY_K:              return ImGuiKey_K;
        case LI_KEY_L:              return ImGuiKey_L;
        case LI_KEY_M:              return ImGuiKey_M;
        case LI_KEY_N:              return ImGuiKey_N;
        case LI_KEY_O:              return ImGuiKey_O;
        case LI_KEY_P:              return ImGuiKey_P;
        case LI_KEY_Q:              return ImGuiKey_Q;
        case LI_KEY_R:              return ImGuiKey_R;
        case LI_KEY_S:              return ImGuiKey_S;
        case LI_KEY_T:              return ImGuiKey_T;
        case LI_KEY_U:              return ImGuiKey_U;
        case LI_KEY_V:              return ImGuiKey_V;
        case LI_KEY_W:              return ImGuiKey_W;
        case LI_KEY_X:              return ImGuiKey_X;
        case LI_KEY_Y:              return ImGuiKey_Y;
        case LI_KEY_Z:              return ImGuiKey_Z;
        case LI_KEY_F1:             return ImGuiKey_F1;
        case LI_KEY_F2:             return ImGuiKey_F2;
        case LI_KEY_F3:             return ImGuiKey_F3;
        case LI_KEY_F4:             return ImGuiKey_F4;
        case LI_KEY_F5:             return ImGuiKey_F5;
        case LI_KEY_F6:             return ImGuiKey_F6;
        case LI_KEY_F7:             return ImGuiKey_F7;
        case LI_KEY_F8:             return ImGuiKey_F8;
        case LI_KEY_F9:             return ImGuiKey_F9;
        case LI_KEY_F10:            return ImGuiKey_F10;
        case LI_KEY_F11:            return ImGuiKey_F11;
        case LI_KEY_F12:            return ImGuiKey_F12;
        default:                    return ImGuiKey_None;
        }
    }

    void ImGuiLayer::UpdateMods(const int key, const bool isPressed)
    {
        ImGuiIO& io = ImGui::GetIO();

        switch (key)
        {
        case LI_KEY_LEFT_CONTROL:
        case LI_KEY_RIGHT_CONTROL:
            io.AddKeyEvent(ImGuiKey_ModCtrl, isPressed);
            break;
        case LI_KEY_LEFT_SHIFT:
        case LI_KEY_RIGHT_SHIFT:
            io.AddKeyEvent(ImGuiKey_ModShift, isPressed);
            break;
        case LI_KEY_LEFT_ALT:
        case LI_KEY_RIGHT_ALT:
            io.AddKeyEvent(ImGuiKey_ModAlt, isPressed);
            break;
        case LI_KEY_LEFT_SUPER:
        case LI_KEY_RIGHT_SUPER:
            io.AddKeyEvent(ImGuiKey_ModSuper, isPressed);
            break;
        }
    }
}