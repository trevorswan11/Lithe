#include "lipch.h"
#include "Scene.h"

#include "Lithe/Scene/Components.h"
#include "Lithe/Scene/Entity.h"
#include "Lithe/Scene/ScriptableEntity.h"
#include "Lithe/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_circle_shape.h>

namespace Lithe {

	namespace Utils {

		const std::string WHITESPACE = " \n\r\t\f\v";

		static std::string string_ltrim(const std::string& s)
		{
			size_t start = s.find_first_not_of(WHITESPACE);
			return (start == std::string::npos) ? "" : s.substr(start);
		}

		static std::string string_rtrim(const std::string& s)
		{
			size_t end = s.find_last_not_of(WHITESPACE);
			return (end == std::string::npos) ? "" : s.substr(0, end + 1);
		}

		static std::string string_trim(const std::string& s) {
			return string_rtrim(string_ltrim(s));
		}

	}

	static b2BodyType RigidBody2DTypeToBox2DBody(RigidBody2DComponent::BodyType bodyType)
	{
		switch (bodyType)
		{
		case RigidBody2DComponent::BodyType::Static: return b2_staticBody;
		case RigidBody2DComponent::BodyType::Dynamic: return b2_dynamicBody;
		case RigidBody2DComponent::BodyType::Kinematic: return b2_kinematicBody;
		}

		LI_CORE_ASSERT(false);
		return b2_staticBody;
	}

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	template<typename... Component>
	static void CopyComponent(entt::registry& dst, entt::registry& src, const std::unordered_map<UUID, entt::entity>& enttMap)
	{
		([&]()
		{
			auto view = src.view<Component>();
			for (auto srcEntity : view)
			{
				entt::entity dstEntity = enttMap.at(src.get<IDComponent>(srcEntity).ID);

				auto& srcComponent = src.get<Component>(srcEntity);
				dst.emplace_or_replace<Component>(dstEntity, srcComponent);
			}
		}(), ...);
	}

	template<typename... Component>
	static void CopyComponent(ComponentGroup<Component...>, entt::registry& dst, entt::registry& src, const std::unordered_map<UUID, entt::entity>& enttMap)
	{
		CopyComponent<Component...>(dst, src, enttMap);
	}

	template<typename... Component>
	static void CopyComponentIfExists(Entity dst, Entity src)
	{
		([&]()
		{
			if (src.HasComponent<Component>())
				dst.AddOrReplaceComponent<Component>(src.GetComponent<Component>());
		}(), ...);
	}

	template<typename... Component>
	static void CopyComponentIfExists(ComponentGroup<Component...>, Entity dst, Entity src)
	{
		CopyComponentIfExists<Component...>(dst, src);
	}

	Ref<Scene> Scene::Copy(Ref<Scene> srcScene)
	{
		if (!srcScene || !srcScene->m_ViewportWidth || !srcScene->m_ViewportHeight) 
			return srcScene;
		Ref<Scene> dstScene = CreateRef<Scene>();
		dstScene->SetName(srcScene->GetName());

		dstScene->m_ViewportWidth = srcScene->m_ViewportWidth;
		dstScene->m_ViewportHeight = srcScene->m_ViewportHeight;

		auto& srcSceneRegistry = srcScene->m_Registry;
		auto& dstSceneRegistry = dstScene->m_Registry;
		std::unordered_map<UUID, entt::entity> enttMap;

		auto idView = srcSceneRegistry.view<IDComponent>();
		for (auto e : idView)
		{
			UUID uuid = srcSceneRegistry.get<IDComponent>(e).ID;
			const auto& name = srcSceneRegistry.get<TagComponent>(e).Tag;
			Entity newEntity = dstScene->CreateEntityWithUUID(uuid, name);
			enttMap[uuid] = (entt::entity)newEntity;
		}
		CopyComponent(AllComponents{}, dstSceneRegistry, srcSceneRegistry, enttMap);

		return dstScene;
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		return CreateEntityWithUUID(UUID(), name);
	}

	Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<IDComponent>(uuid);
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		m_EntityMap[uuid] = entity;
		m_EntityCount++;
		return entity;
	}

	Entity Scene::CloneEntity(Entity entity)
	{
		std::string name = entity.GetComponent<TagComponent>().Tag;
		Entity newEntity = CreateEntity(Utils::string_trim(name) + " - Copy");
		CopyComponentIfExists(AllComponents{}, newEntity, entity);
		m_EntityCount++;
		return newEntity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_EntityMap.erase(entity.GetUUID());
		m_EntityCount--;
		m_Registry.destroy(entity);
	}

	void Scene::OnRuntimeStart()
	{
		m_PhysicsWorld = new b2World({ 0.0f, -9.8f });
		auto view = m_Registry.view<RigidBody2DComponent>();
		for (auto e : view)
		{
			Entity entity{ e, this };
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& rb2d = entity.GetComponent<RigidBody2DComponent>();

			b2BodyDef bodyDef;
			bodyDef.type = RigidBody2DTypeToBox2DBody(rb2d.Type);
			bodyDef.position.Set(transform.Translation.x, transform.Translation.y);
			bodyDef.angle = transform.Rotation.z;

			b2Body* body = m_PhysicsWorld->CreateBody(&bodyDef);
			body->SetFixedRotation(rb2d.FixedRotation);
			rb2d.RuntimeBody = body;

			if (entity.HasComponent<BoxCollider2DComponent>())
			{
				auto& bc2d = entity.GetComponent<BoxCollider2DComponent>();

				b2PolygonShape boxShape;
				boxShape.SetAsBox(transform.Scale.x * bc2d.Size.x, transform.Scale.y * bc2d.Size.y);

				b2FixtureDef fixtureDef;
				fixtureDef.shape = &boxShape;
				fixtureDef.density = bc2d.Density;
				fixtureDef.friction = bc2d.Friction;
				fixtureDef.restitution = bc2d.Restitution;
				fixtureDef.restitutionThreshold = bc2d.RestitutionThreshold;
				body->CreateFixture(&fixtureDef);
			}

			if (entity.HasComponent<CircleCollider2DComponent>())
			{
				auto& cc2d = entity.GetComponent<CircleCollider2DComponent>();

				b2CircleShape circleShape;
				circleShape.m_p.Set(cc2d.Offset.x, cc2d.Offset.y);
				circleShape.m_radius = cc2d.Radius * transform.Scale.x;

				b2FixtureDef fixtureDef;
				fixtureDef.shape = &circleShape;
				fixtureDef.density = cc2d.Density;
				fixtureDef.friction = cc2d.Friction;
				fixtureDef.restitution = cc2d.Restitution;
				fixtureDef.restitutionThreshold = cc2d.RestitutionThreshold;
				body->CreateFixture(&fixtureDef);
			}
		}
	}

	void Scene::OnRuntimeStop()
	{
		delete m_PhysicsWorld;
		m_PhysicsWorld = nullptr;
	}

	void Scene::OnUpdateEditor(Timestep ts, EditorCamera& camera)
	{
		Renderer2D::BeginScene(camera);

		{
			LI_PROFILE_SCOPE("Editor Draw Sprites");

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawSpriteComponent(transform.GetTransform(), sprite, (int)entity);
			}
		}

		{
			LI_PROFILE_SCOPE("Editor Draw Circles");

			auto circleView = m_Registry.view<TransformComponent, CircleRendererComponent>();
			for (auto entity : circleView) // Intellisense may be angry here, but I swear it compiles
			{
				auto [transform, circle] = circleView.get<TransformComponent, CircleRendererComponent>(entity);

				Renderer2D::DrawCircleComponent(transform.GetTransform(), circle, (int)entity);
			}
		}

		/*Renderer2D::DrawLine(glm::vec3(2.0f), glm::vec3(5.0f), glm::vec4(1, 0, 1, 1));
		Renderer2D::DrawRect(glm::vec3(0.0f), glm::vec2(5.0f), glm::vec4(1, 0.5, 1, 1));*/

		Renderer2D::EndScene();
	}

	void Scene::OnUpdateRuntime(Timestep ts)
	{
		// Update Scripts
		{
			// Should be moved to a ScenePlay Func
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
				{
					if (!nsc.Instance)
					{
						nsc.Instance = nsc.InstantiateScript();
						nsc.Instance->m_Entity = Entity{ entity, this };
						nsc.Instance->OnCreate();
					}
					nsc.Instance->OnUpdate(ts);
				}
			);
		}

		// Physics
		{
			// TODO: expose to editor
			const int32_t velocityIterations = 6;
			const int32_t positionsIterations = 2;

			m_PhysicsWorld->Step(ts, velocityIterations, positionsIterations);

			// Retrieve transforms from Box2D
			auto view = m_Registry.view<RigidBody2DComponent>();
			for (auto e : view)
			{
				Entity entity{ e, this };
				auto& transform = entity.GetComponent<TransformComponent>();
				auto& rb2d = entity.GetComponent<RigidBody2DComponent>();

				b2Body* body = static_cast<b2Body*>(rb2d.RuntimeBody);
				const auto& position = body->GetPosition();
				transform.Translation.x = position.x;
				transform.Translation.y = position.y;
				transform.Rotation.z = body->GetAngle();
			}
		}

		// Render sprites
		Camera* primaryCamera = nullptr;
		glm::mat4 primaryCameraTransform;
		{
			auto group = m_Registry.group<CameraComponent>(entt::get<TransformComponent>);
			for (auto entity : group)
			{
				auto [transform, camera] = group.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary)
				{
					primaryCamera = &camera.Camera;
					primaryCameraTransform = transform.GetTransform();
					break;
				}
			}
		}

		// Render from main camera
		if (primaryCamera)
		{
			Renderer2D::BeginScene(*primaryCamera, primaryCameraTransform);

			{
				LI_PROFILE_SCOPE("Runtime Draw Sprites");

				auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
				for (auto entity : group)
				{
					auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

					Renderer2D::DrawSpriteComponent(transform.GetTransform(), sprite, (int)entity);
				}
			}

			{
				LI_PROFILE_SCOPE("Runtime Draw Circles");

				auto circleView = m_Registry.view<TransformComponent, CircleRendererComponent>();
				for (auto entity : circleView) // Intellisense may be angry here, but I swear it compiles
				{
					auto [transform, circle] = circleView.get<TransformComponent, CircleRendererComponent>(entity);

					Renderer2D::DrawCircleComponent(transform.GetTransform(), circle, (int)entity);
				}
			}

			Renderer2D::EndScene();
		}
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		// Resize all non fixed aspect ration cameras
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewportSize(width, height);
		}
	}

	Entity Scene::GetPrimaryCameraEntity()
	{
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			const auto& cameraComponent = view.get<CameraComponent>(entity);
			if (cameraComponent.Primary)
				return Entity(entity, this);
		}
		return {};
	}

}

// Fucking Slop -- do not touch unless you know EXACTLY what you are doing
namespace Lithe {

	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		static_assert(false);
	}

	template<>
	void Scene::OnComponentAdded<IDComponent>(Entity entity, IDComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		if (m_ViewportWidth > 0 && m_ViewportHeight > 0)
			component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<CircleRendererComponent>(Entity entity, CircleRendererComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<RigidBody2DComponent>(Entity entity, RigidBody2DComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<BoxCollider2DComponent>(Entity entity, BoxCollider2DComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<CircleCollider2DComponent>(Entity entity, CircleCollider2DComponent& component)
	{
	}

}
