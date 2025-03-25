#pragma once

#include "Lithe/Core/Base.h"
#include "Lithe/Core/Timestep.h"

#include <entt.hpp>

namespace Lithe {

	class Scene
	{
	public:
		Scene();
		~Scene();

		//Entity CreateEntity();
		entt::entity CreateEntity();

		// TEMPORARY!!!
		entt::registry& Reg() { return m_Registry; }

		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;
	};

}