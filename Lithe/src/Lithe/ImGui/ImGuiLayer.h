#pragma once

#include "Lithe/Core/Layer.h"

#include "Lithe/Events/MouseEvent.h"
#include "Lithe/Events/KeyEvent.h"
#include "Lithe/Events/ApplicationEvent.h"

namespace Lithe {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block = true) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};

}