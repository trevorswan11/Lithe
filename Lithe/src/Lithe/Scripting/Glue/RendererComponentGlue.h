#pragma once

namespace Lithe {

	static void SpriteRendererComponent_GetColor(UUID entityID, glm::vec4* outColor)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<SpriteRendererComponent>());

		auto& src = entity.GetComponent<SpriteRendererComponent>();
		*outColor = src.Color;
	}

	static void SpriteRendererComponent_SetColor(UUID entityID, glm::vec4* color)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<SpriteRendererComponent>());

		auto& src = entity.GetComponent<SpriteRendererComponent>();
		src.Color = *color;
	}

	static void SpriteRendererComponent_EnableSubtexture(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<SpriteRendererComponent>());

		auto& src = entity.GetComponent<SpriteRendererComponent>();
		src.SubTextureUsed = true;
	}

	static void SpriteRendererComponent_DisableSubtexture(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<SpriteRendererComponent>());

		auto& src = entity.GetComponent<SpriteRendererComponent>();
		src.SubTextureUsed = false;
	}

	static bool SpriteRendererComponent_SubtextureUsed(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<SpriteRendererComponent>());

		auto& src = entity.GetComponent<SpriteRendererComponent>();
		return src.SubTextureUsed;
	}

	static void SpriteRendererComponent_GetCoords(UUID entityID, glm::vec2* outCoords)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<SpriteRendererComponent>());

		auto& src = entity.GetComponent<SpriteRendererComponent>();
		*outCoords = src.Coords;
	}

	static void SpriteRendererComponent_SetCoords(UUID entityID, glm::vec2* coords)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<SpriteRendererComponent>());

		auto& src = entity.GetComponent<SpriteRendererComponent>();
		src.Coords = *coords;
	}

	static void SpriteRendererComponent_GetCellSize(UUID entityID, glm::vec2* outCellSize)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<SpriteRendererComponent>());

		auto& src = entity.GetComponent<SpriteRendererComponent>();
		*outCellSize = src.CellSize;
	}

	static void SpriteRendererComponent_SetCellSize(UUID entityID, glm::vec2* cellSize)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<SpriteRendererComponent>());

		auto& src = entity.GetComponent<SpriteRendererComponent>();
		src.CellSize = *cellSize;
	}

	static void SpriteRendererComponent_GetSpriteSize(UUID entityID, glm::vec2* outSpriteSize)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<SpriteRendererComponent>());

		auto& src = entity.GetComponent<SpriteRendererComponent>();
		*outSpriteSize = src.SpriteSize;
	}

	static void SpriteRendererComponent_SetSpriteSize(UUID entityID, glm::vec2* spriteSize)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<SpriteRendererComponent>());

		auto& src = entity.GetComponent<SpriteRendererComponent>();
		src.SpriteSize = *spriteSize;
	}

	static MonoString* SpriteRendererComponent_GetTextureAbsolutePath(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<SpriteRendererComponent>());

		auto& src = entity.GetComponent<SpriteRendererComponent>();
		if (auto& srcTexture = src.Texture)
		{
			if (auto texture2D = std::get_if<Ref<Texture2D>>(&*srcTexture))
				return ScriptEngine::CreateString(texture2D->get()->GetPath().c_str());
			else if (auto subTexture2D = std::get_if<Ref<SubTexture2D>>(&*srcTexture))
				return ScriptEngine::CreateString(subTexture2D->get()->GetTexture()->GetPath().c_str());
		}
		return ScriptEngine::CreateString("Texture not loaded correctly!");
	}

	static MonoString* SpriteRendererComponent_GetTextureRelativePath(UUID entityID)
	{
		MonoString* absolutePath = SpriteRendererComponent_GetTextureAbsolutePath(entityID);
		auto relativePath = FileSystem::MakeRelativePath(ScriptEngine::CreateString(absolutePath));
		return ScriptEngine::CreateString(relativePath.string().c_str());
	}

	static void SpriteRendererComponent_SetTexturePath(UUID entityID, MonoString* relativePath)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<SpriteRendererComponent>());

		auto& src = entity.GetComponent<SpriteRendererComponent>();
		if (auto& srcTexture = src.Texture)
		{
			auto path = Project::GetAssetFileSystemPath(ScriptEngine::CreateString(relativePath)).string();
			if (src.SubTextureUsed)
				srcTexture = Texture2D::Create(path);
			else
				srcTexture = SubTexture2D::CreateFromCoords(
					Texture2D::Create(path), src.Coords, src.CellSize, src.SpriteSize);
		}
	}

	static bool SpriteRendererComponent_IsLoaded(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<SpriteRendererComponent>());

		if (auto& srcTexture = entity.GetComponent<SpriteRendererComponent>().Texture)
		{
			if (auto texture2D = std::get_if<Ref<Texture2D>>(&*srcTexture))
				return texture2D->get()->IsLoaded();
			else if (auto subTexture2D = std::get_if<Ref<SubTexture2D>>(&*srcTexture))
				return subTexture2D->get()->GetTexture()->IsLoaded();
		}
		return false;
	}

	static void CircleRendererComponent_GetColor(UUID entityID, glm::vec4* outColor)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<CircleRendererComponent>());

		auto& crc = entity.GetComponent<CircleRendererComponent>();
		*outColor = crc.Color;
	}

	static void CircleRendererComponent_SetColor(UUID entityID, glm::vec4* color)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<CircleRendererComponent>());

		auto& crc = entity.GetComponent<CircleRendererComponent>();
		crc.Color = *color;
	}

	static float CircleRendererComponent_GetRadius(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<CircleRendererComponent>());

		auto& crc = entity.GetComponent<CircleRendererComponent>();
		return crc.Radius;
	}

	static void CircleRendererComponent_SetRadius(UUID entityID, float radius)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<CircleRendererComponent>());

		auto& crc = entity.GetComponent<CircleRendererComponent>();
		crc.Radius = radius;
	}

	static float CircleRendererComponent_GetThickness(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<CircleRendererComponent>());

		auto& crc = entity.GetComponent<CircleRendererComponent>();
		return crc.Thickness;
	}

	static void CircleRendererComponent_SetThickness(UUID entityID, float thickness)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<CircleRendererComponent>());

		auto& crc = entity.GetComponent<CircleRendererComponent>();
		crc.Thickness = thickness;
	}

	static float CircleRendererComponent_GetFade(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<CircleRendererComponent>());

		auto& crc = entity.GetComponent<CircleRendererComponent>();
		return crc.Fade;
	}

	static void CircleRendererComponent_SetFade(UUID entityID, float renderer)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<CircleRendererComponent>());

		auto& crc = entity.GetComponent<CircleRendererComponent>();
		crc.Fade = renderer;
	}

}
