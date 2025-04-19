#pragma once

namespace Lithe {

	static MonoString* AudioComponent_GetPath(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<AudioComponent>());

		auto& ac = entity.GetComponent<AudioComponent>();
		return ScriptEngine::CreateString(ac.Path.c_str());
	}

	static void AudioComponent_SetPath(UUID entityID, MonoString* textString)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<AudioComponent>());

		auto& ac = entity.GetComponent<AudioComponent>();
		ac.Path = ScriptEngine::CreateString(textString);
	}

	static float AudioComponent_GetVolume(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<AudioComponent>());

		auto& ac = entity.GetComponent<AudioComponent>();
		return ac.Volume;
	}

	static void AudioComponent_SetVolume(UUID entityID, float volume)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<AudioComponent>());

		auto& ac = entity.GetComponent<AudioComponent>();
		ac.Volume = volume;
	}

	static bool AudioComponent_GetLooping(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<AudioComponent>());

		auto& ac = entity.GetComponent<AudioComponent>();
		return ac.Looping;
	}

	static void AudioComponent_SetLooping(UUID entityID, bool looping)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<AudioComponent>());

		auto& ac = entity.GetComponent<AudioComponent>();
		ac.Looping = looping;
	}

	static bool AudioComponent_GetPlayOnStart(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<AudioComponent>());

		auto& ac = entity.GetComponent<AudioComponent>();
		return ac.PlayOnStart;
	}

	static void AudioComponent_SetPlayOnStart(UUID entityID, bool playOnStart)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<AudioComponent>());

		auto& ac = entity.GetComponent<AudioComponent>();
		ac.PlayOnStart = playOnStart;
	}

	static bool AudioComponent_IsValid(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<AudioComponent>());

		auto& ac = entity.GetComponent<AudioComponent>();
		return ac.IsValid();
	}

	static bool AudioComponent_IsPlaying(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<AudioComponent>());

		auto& ac = entity.GetComponent<AudioComponent>();
		return ac.IsPlaying();
	}

	static bool AudioComponent_IsInitialized(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<AudioComponent>());

		auto& ac = entity.GetComponent<AudioComponent>();
		return ac.IsInitialized();
	}

	static void AudioComponent_Init(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<AudioComponent>());

		auto& ac = entity.GetComponent<AudioComponent>();
		ac.Init();
	}

	static void AudioComponent_Play(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<AudioComponent>());

		auto& ac = entity.GetComponent<AudioComponent>();
		ac.Play();
	}

	static void AudioComponent_Stop(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		LI_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		LI_CORE_ASSERT(entity);
		LI_CORE_ASSERT(entity.HasComponent<AudioComponent>());

		auto& ac = entity.GetComponent<AudioComponent>();
		ac.Stop();
	}

}
