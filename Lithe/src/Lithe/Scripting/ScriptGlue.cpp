#include "lipch.h"
#include "ScriptGlue.h"

#include "Lithe/Scripting/ScriptEngine.h"

#include "Lithe/Core/Input.h"
#include "Lithe/Core/KeyCodes.h"
#include "Lithe/Core/MouseCodes.h"
#include "Lithe/Core/UUID.h"

#include "Lithe/Scene/Scene.h"
#include "Lithe/Scene/Entity.h"

#include "Lithe/Core/FileSystem.h"
#include "Lithe/Project/Project.h"
#include "Lithe/Utils/StringUtils.h"

#include "Lithe/Scripting/Glue/UtilsGlue.h"
#include "Lithe/Scripting/Glue/CameraComponentGlue.h"
#include "Lithe/Scripting/Glue/TransformComponentGlue.h"
#include "Lithe/Scripting/Glue/PhysicsComponentGlue.h"
#include "Lithe/Scripting/Glue/TextComponentGlue.h"
#include "Lithe/Scripting/Glue/AudioComponentGlue.h"
#include "Lithe/Scripting/Glue/RendererComponentGlue.h"
#include "Lithe/Scripting/Glue/RelationshipComponentGlue.h"

#include <mono/metadata/object.h>
#include <mono/metadata/reflection.h>

namespace Lithe {

	static std::unordered_map<MonoType*, std::function<bool(Entity)>> s_EntityHasComponentFuncs;

#define LI_ADD_INTERNAL_CALL(Name) mono_add_internal_call("Lithe.InternalCalls::" #Name, Name)

	static MonoObject* GetScriptInstance(UUID entityID)
	{
		return ScriptEngine::GetManagedInstance(entityID);
	}

	static bool Entity_HasComponent(UUID entityID, MonoReflectionType* componentType)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);

		MonoType* managedType = mono_reflection_type_get_type(componentType);
		LI_CORE_ASSERT(s_EntityHasComponentFuncs.find(managedType) != s_EntityHasComponentFuncs.end());
		return s_EntityHasComponentFuncs.at(managedType)(entity);
	}

	static uint64_t Entity_FindEntityByName(MonoString* name)
	{
		char* nameCStr = mono_string_to_utf8(name);

		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->FindEntityByName(nameCStr);
		mono_free(nameCStr);

		if (!entity)
			return 0;

		return entity.GetUUID();
	}

	static uint64_t Entity_GetGlobalEntity()
	{
		auto id = ScriptEngine::GetEntityContext();
		return id ? id : 0;
	}

	template<typename... Component>
	static void RegisterComponent()
	{
		([]()
			{
				std::string_view typeName = typeid(Component).name();
				size_t pos = typeName.find_last_of(':');
				std::string_view structName = typeName.substr(pos + 1);
				std::string managedTypename = fmt::format("Lithe.{}", structName);

				MonoType* managedType = mono_reflection_type_from_name(managedTypename.data(), ScriptEngine::GetCoreAssemblyImage());
				if (!managedType)
				{
					if (!Utils::StringContains(managedTypename, "ScriptComponent"))
						LI_CORE_ERROR("Could not find component type {}", managedTypename);
					return;
				}
				s_EntityHasComponentFuncs[managedType] = [](Entity entity) { return entity.HasComponent<Component>(); };
			}(), ...);
	}

	template<typename... Component>
	static void RegisterComponent(ComponentGroup<Component...>)
	{
		RegisterComponent<Component...>();
	}

	void ScriptGlue::RegisterComponents()
	{
		s_EntityHasComponentFuncs.clear();
		RegisterComponent(AllComponents{});
	}

	void ScriptGlue::RegisterFunctions()
	{
		LI_ADD_INTERNAL_CALL(Logger_LogTrace);
		LI_ADD_INTERNAL_CALL(Logger_LogInfo);
		LI_ADD_INTERNAL_CALL(Logger_LogWarn);
		LI_ADD_INTERNAL_CALL(Logger_LogError);
		LI_ADD_INTERNAL_CALL(Logger_LogCritical);

		LI_ADD_INTERNAL_CALL(GetScriptInstance);

		LI_ADD_INTERNAL_CALL(Entity_HasComponent);
		LI_ADD_INTERNAL_CALL(Entity_FindEntityByName);
		LI_ADD_INTERNAL_CALL(Entity_GetGlobalEntity);

		LI_ADD_INTERNAL_CALL(TransformComponent_GetTranslation);
		LI_ADD_INTERNAL_CALL(TransformComponent_SetTranslation);
		LI_ADD_INTERNAL_CALL(TransformComponent_GetRotation);
		LI_ADD_INTERNAL_CALL(TransformComponent_SetRotation);

		LI_ADD_INTERNAL_CALL(RigidBody2DComponent_ApplyLinearImpulse);
		LI_ADD_INTERNAL_CALL(RigidBody2DComponent_ApplyLinearImpulseToCenter);
		LI_ADD_INTERNAL_CALL(RigidBody2DComponent_GetLinearVelocity);
		LI_ADD_INTERNAL_CALL(RigidBody2DComponent_GetType);
		LI_ADD_INTERNAL_CALL(RigidBody2DComponent_SetType);

		LI_ADD_INTERNAL_CALL(TextComponent_GetText);
		LI_ADD_INTERNAL_CALL(TextComponent_SetText);
		LI_ADD_INTERNAL_CALL(TextComponent_GetColor);
		LI_ADD_INTERNAL_CALL(TextComponent_SetColor);
		LI_ADD_INTERNAL_CALL(TextComponent_GetKerning);
		LI_ADD_INTERNAL_CALL(TextComponent_SetKerning);
		LI_ADD_INTERNAL_CALL(TextComponent_GetLineSpacing);
		LI_ADD_INTERNAL_CALL(TextComponent_SetLineSpacing);

		LI_ADD_INTERNAL_CALL(Input_IsKeyDown);
		LI_ADD_INTERNAL_CALL(Input_IsMouseDown);
		LI_ADD_INTERNAL_CALL(Input_GetMousePosition);
		LI_ADD_INTERNAL_CALL(Input_GetMouseWorldPosition);

		LI_ADD_INTERNAL_CALL(AudioComponent_GetPath);
		LI_ADD_INTERNAL_CALL(AudioComponent_SetPath);
		LI_ADD_INTERNAL_CALL(AudioComponent_GetVolume);
		LI_ADD_INTERNAL_CALL(AudioComponent_SetVolume);
		LI_ADD_INTERNAL_CALL(AudioComponent_GetLooping);
		LI_ADD_INTERNAL_CALL(AudioComponent_SetLooping);
		LI_ADD_INTERNAL_CALL(AudioComponent_GetPlayOnStart);
		LI_ADD_INTERNAL_CALL(AudioComponent_SetPlayOnStart);
		LI_ADD_INTERNAL_CALL(AudioComponent_IsValid);
		LI_ADD_INTERNAL_CALL(AudioComponent_IsPlaying);
		LI_ADD_INTERNAL_CALL(AudioComponent_IsInitialized);
		LI_ADD_INTERNAL_CALL(AudioComponent_Init);
		LI_ADD_INTERNAL_CALL(AudioComponent_Play);
		LI_ADD_INTERNAL_CALL(AudioComponent_Stop);

		LI_ADD_INTERNAL_CALL(SpriteRendererComponent_GetColor);
		LI_ADD_INTERNAL_CALL(SpriteRendererComponent_SetColor);
		LI_ADD_INTERNAL_CALL(SpriteRendererComponent_EnableSubtexture);
		LI_ADD_INTERNAL_CALL(SpriteRendererComponent_DisableSubtexture);
		LI_ADD_INTERNAL_CALL(SpriteRendererComponent_SubtextureUsed);
		LI_ADD_INTERNAL_CALL(SpriteRendererComponent_GetCoords);
		LI_ADD_INTERNAL_CALL(SpriteRendererComponent_SetCoords);
		LI_ADD_INTERNAL_CALL(SpriteRendererComponent_GetCellSize);
		LI_ADD_INTERNAL_CALL(SpriteRendererComponent_SetCellSize);
		LI_ADD_INTERNAL_CALL(SpriteRendererComponent_GetSpriteSize);
		LI_ADD_INTERNAL_CALL(SpriteRendererComponent_SetSpriteSize);
		LI_ADD_INTERNAL_CALL(SpriteRendererComponent_GetTextureAbsolutePath);
		LI_ADD_INTERNAL_CALL(SpriteRendererComponent_GetTextureRelativePath);
		LI_ADD_INTERNAL_CALL(SpriteRendererComponent_SetTexturePath);
		LI_ADD_INTERNAL_CALL(SpriteRendererComponent_IsLoaded);

		LI_ADD_INTERNAL_CALL(CircleRendererComponent_GetColor);
		LI_ADD_INTERNAL_CALL(CircleRendererComponent_SetColor);
		LI_ADD_INTERNAL_CALL(CircleRendererComponent_GetRadius);
		LI_ADD_INTERNAL_CALL(CircleRendererComponent_SetRadius);
		LI_ADD_INTERNAL_CALL(CircleRendererComponent_GetThickness);
		LI_ADD_INTERNAL_CALL(CircleRendererComponent_SetThickness);
		LI_ADD_INTERNAL_CALL(CircleRendererComponent_GetFade);
		LI_ADD_INTERNAL_CALL(CircleRendererComponent_SetFade);

		LI_ADD_INTERNAL_CALL(CameraComponent_GetPrimary);
		LI_ADD_INTERNAL_CALL(CameraComponent_SetPrimary);
		LI_ADD_INTERNAL_CALL(CameraComponent_IsPrimary);
		LI_ADD_INTERNAL_CALL(CameraComponent_GetFixedAspectRatio);
		LI_ADD_INTERNAL_CALL(CameraComponent_SetFixedAspectRatio);
		LI_ADD_INTERNAL_CALL(CameraComponent_IsFixedAspectRatio);

		LI_ADD_INTERNAL_CALL(BoxCollider2DComponent_GetOffset);
		LI_ADD_INTERNAL_CALL(BoxCollider2DComponent_SetOffset);
		LI_ADD_INTERNAL_CALL(BoxCollider2DComponent_GetSize);
		LI_ADD_INTERNAL_CALL(BoxCollider2DComponent_SetSize);
		LI_ADD_INTERNAL_CALL(BoxCollider2DComponent_GetDensity);
		LI_ADD_INTERNAL_CALL(BoxCollider2DComponent_SetDensity);
		LI_ADD_INTERNAL_CALL(BoxCollider2DComponent_GetFriction);
		LI_ADD_INTERNAL_CALL(BoxCollider2DComponent_SetFriction);
		LI_ADD_INTERNAL_CALL(BoxCollider2DComponent_GetRestitution);
		LI_ADD_INTERNAL_CALL(BoxCollider2DComponent_SetRestitution);
		LI_ADD_INTERNAL_CALL(BoxCollider2DComponent_GetRestitutionThreshold);
		LI_ADD_INTERNAL_CALL(BoxCollider2DComponent_SetRestitutionThreshold);

		LI_ADD_INTERNAL_CALL(CircleCollider2DComponent_GetOffset);
		LI_ADD_INTERNAL_CALL(CircleCollider2DComponent_SetOffset);
		LI_ADD_INTERNAL_CALL(CircleCollider2DComponent_GetRadius);
		LI_ADD_INTERNAL_CALL(CircleCollider2DComponent_SetRadius);
		LI_ADD_INTERNAL_CALL(CircleCollider2DComponent_GetDensity);
		LI_ADD_INTERNAL_CALL(CircleCollider2DComponent_SetDensity);
		LI_ADD_INTERNAL_CALL(CircleCollider2DComponent_GetFriction);
		LI_ADD_INTERNAL_CALL(CircleCollider2DComponent_SetFriction);
		LI_ADD_INTERNAL_CALL(CircleCollider2DComponent_GetRestitution);
		LI_ADD_INTERNAL_CALL(CircleCollider2DComponent_SetRestitution);
		LI_ADD_INTERNAL_CALL(CircleCollider2DComponent_GetRestitutionThreshold);
		LI_ADD_INTERNAL_CALL(CircleCollider2DComponent_SetRestitutionThreshold);

		LI_ADD_INTERNAL_CALL(RelationshipComponent_GetParent);
		LI_ADD_INTERNAL_CALL(RelationshipComponent_SetParent);
		LI_ADD_INTERNAL_CALL(RelationshipComponent_GetFirstChild);
		LI_ADD_INTERNAL_CALL(RelationshipComponent_SetFirstChild);
		LI_ADD_INTERNAL_CALL(RelationshipComponent_GetNextSibling);
		LI_ADD_INTERNAL_CALL(RelationshipComponent_SetNextSibling);
		LI_ADD_INTERNAL_CALL(RelationshipComponent_GetPrevSibling);
		LI_ADD_INTERNAL_CALL(RelationshipComponent_SetPrevSibling);
	}

}
