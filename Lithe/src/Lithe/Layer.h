#pragma once

#include "Lithe/Base.h"
#include "Lithe/Events/Event.h"
#include "Lithe/Core/Timestep.h"

namespace Lithe {

	class LITHE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
		bool m_Enabled;
	};

}

