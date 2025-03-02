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

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		// Begin and end imgui window rendering

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}