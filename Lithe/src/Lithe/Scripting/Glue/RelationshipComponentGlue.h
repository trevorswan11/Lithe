#pragma once

namespace Lithe {

	static uint64_t RelationshipComponent_GetParent(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<RelationshipComponent>());

		auto& rc = entity.GetComponent<RelationshipComponent>();
		return rc.Parent;
	}

	static void RelationshipComponent_SetParent(UUID entityID, UUID parent)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<RelationshipComponent>());

		auto& rc = entity.GetComponent<RelationshipComponent>();
		rc.Parent = parent;
	}

	static uint64_t RelationshipComponent_GetFirstChild(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<RelationshipComponent>());

		auto& rc = entity.GetComponent<RelationshipComponent>();
		return rc.FirstChild;
	}

	static void RelationshipComponent_SetFirstChild(UUID entityID, UUID child)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<RelationshipComponent>());

		auto& rc = entity.GetComponent<RelationshipComponent>();
		rc.FirstChild = child;
	}

	static uint64_t RelationshipComponent_GetNextSibling(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<RelationshipComponent>());

		auto& rc = entity.GetComponent<RelationshipComponent>();
		return rc.NextSibling;
	}

	static void RelationshipComponent_SetNextSibling(UUID entityID, UUID sibling)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<RelationshipComponent>());

		auto& rc = entity.GetComponent<RelationshipComponent>();
		rc.NextSibling = sibling;
	}

	static uint64_t RelationshipComponent_GetPrevSibling(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<RelationshipComponent>());

		auto& rc = entity.GetComponent<RelationshipComponent>();
		return rc.PrevSibling;
	}

	static void RelationshipComponent_SetPrevSibling(UUID entityID, UUID sibling)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<RelationshipComponent>());

		auto& rc = entity.GetComponent<RelationshipComponent>();
		rc.PrevSibling = sibling;
	}

}
