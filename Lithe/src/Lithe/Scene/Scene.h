#pragma once

#include "Lithe/Core/Base.h"
#include "Lithe/Core/UUID.h"
#include "Lithe/Core/Timestep.h"

#include "Lithe/Renderer/EditorCamera.h"

#include <entt.hpp>

class b2World;

namespace Lithe {

	class Entity;
	class Scene
	{
	public:
		Scene() = default;
		~Scene();

		static Ref<Scene> Copy(Ref<Scene> srcScene);

		Entity CreateEntity(const std::string& name = std::string());
		Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
		Entity CloneEntity(Entity entity);
		void DestroyEntity(Entity entity);

		void OnRuntimeStart();
		void OnRuntimeStop();

		void OnSimulationStart();
		void OnSimulationStop();

		void OnUpdateRuntime(Timestep ts);
		void OnUpdateEditor(Timestep ts, EditorCamera& camera);
		void OnUpdateSimulation(Timestep ts, EditorCamera& camera, bool onlyRenderColliders = false);
		void OnViewportResize(uint32_t width, uint32_t height);

		Entity GetPrimaryCameraEntity();
		uint32_t GetEntityCount() const { return m_EntityCount; }

		bool Empty() const { return m_EntityCount == 0; }
		bool IsRunning() const { return m_IsRunning; }
		bool IsPaused() const { return m_IsPaused; }
		void SetPaused(bool paused) { m_IsPaused = paused; }
		void Step(int frames = 1);

		std::string GetName() const { return m_Name; }
		std::string& GetName() { return m_Name; }
		void SetName(const std::string& name) { m_Name = name; }

		int32_t GetVelocityIterations() const { return m_VelocityIterations; }
		int32_t& GetVelocityIterations() { return m_VelocityIterations; }
		void SetVelocityIterations(int32_t iterations) { m_VelocityIterations = iterations; }
		int32_t GetPositionIterations() const { return m_PositionsIterations; }
		int32_t& GetPositionIterations() { return m_PositionsIterations; }
		void SetPositionIterations(int32_t iterations) { m_PositionsIterations = iterations; }

		template<typename... Components>
		auto GetAllEntitiesWith()
		{
			return m_Registry.view<Components...>();
		}
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

		void OnPhysics2DStart();
		void OnPhysics2DStop();

		void RenderScene(EditorCamera& camera);
	private:
		std::string m_Name = "Untitled";
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0;
		uint32_t m_ViewportHeight = 0;
		bool m_IsRunning = false;
		bool m_IsPaused = false;
		int m_StepFrames = 0;

		b2World* m_PhysicsWorld = nullptr;
		int32_t m_VelocityIterations = 6;
		int32_t m_PositionsIterations = 2;

		std::unordered_map<UUID, entt::entity> m_EntityMap;
		uint32_t m_EntityCount = 0;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};

}
