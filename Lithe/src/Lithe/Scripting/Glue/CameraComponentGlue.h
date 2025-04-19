#pragma once

namespace Lithe {

	static bool CameraComponent_GetPrimary(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<CameraComponent>());

		auto& camera = entity.GetComponent<CameraComponent>();
		return camera.Primary;
	}

	static void CameraComponent_SetPrimary(UUID entityID, bool primary)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<CameraComponent>());

		auto& camera = entity.GetComponent<CameraComponent>();
		camera.Primary = primary;
	}

	static bool CameraComponent_IsPrimary(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<CameraComponent>());

		auto& camera = entity.GetComponent<CameraComponent>();
		return camera.Primary;
	}

	static bool CameraComponent_GetFixedAspectRatio(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<CameraComponent>());

		auto& camera = entity.GetComponent<CameraComponent>();
		return camera.FixedAspectRatio;
	}

	static void CameraComponent_SetFixedAspectRatio(UUID entityID, bool aspectRatio)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<CameraComponent>());

		auto& camera = entity.GetComponent<CameraComponent>();
		camera.FixedAspectRatio = aspectRatio;
	}

	static bool CameraComponent_IsFixedAspectRatio(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<CameraComponent>());

		auto& camera = entity.GetComponent<CameraComponent>();
		return camera.FixedAspectRatio;
	}

}
