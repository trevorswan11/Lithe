#pragma once

#include "Lithe/Core/Base.h"
#include "Lithe/Scene/Scene.h"

// --- Code written by TheCherno ---

namespace Lithe {

	class SceneSerializer
	{
	public:
		SceneSerializer(const Ref<Scene>& scene);

		void Serialize(const std::string& filepath);
		void SerializeRuntime(const std::string& filepath);

		bool Deserialize(const std::string& filepath);
		bool DeserializeRuntime(const std::string& filepath);
	private:
		Ref<Scene> m_Scene;
	};

}

