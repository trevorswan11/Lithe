#include "lipch.h"
#include "Scene.h"

#include "Lithe/Scene/Components.h"
#include "Lithe/Scene/Entity.h"
#include "Lithe/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace Lithe {

	Scene::Scene()
	{

	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		// Render sprites
		Camera* primaryCamera = nullptr;
		glm::mat4* primaryCameraTransform = nullptr;
		{
			auto group = m_Registry.group<CameraComponent>(entt::get<TransformComponent>);
			for (auto entity : group)
			{
				auto& [transform, camera] = group.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary)
				{
					primaryCamera = &camera.Camera;
					primaryCameraTransform = &transform.Transform;
					break;
				}
			}
		}

		// Render from main camera
		if (primaryCamera)
		{
			Renderer2D::BeginScene(primaryCamera->GetProjection(), *primaryCameraTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawQuad(transform, sprite.Color);
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

}