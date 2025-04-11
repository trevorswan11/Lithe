#include "lipch.h"
#include "AudioEngine.h"

namespace Lithe {

	AudioEngine* AudioEngine::s_Instance = nullptr;

	// === AudioEngine Implementation ===

	bool AudioEngine::Init()
	{
		if (s_Instance)
			return true;

		s_Instance = new AudioEngine();

		if (ma_engine_init(NULL, &s_Instance->m_Engine) != MA_SUCCESS)
		{
			LI_CORE_ERROR("Failed to initialize miniaudio.");
			delete s_Instance;
			s_Instance = nullptr;
			return false;
		}

		s_Instance->m_Initialized = true;
		LI_CORE_INFO("Initialized miniaudio successfully.");
		return true;
	}

	void AudioEngine::Shutdown()
	{
		if (s_Instance && s_Instance->m_Initialized)
		{
			s_Instance->m_TrackedSounds.clear();
			ma_engine_uninit(&s_Instance->m_Engine);
			s_Instance->m_Initialized = false;
		}
		delete s_Instance;
		s_Instance = nullptr;
		LI_CORE_INFO("Shutdown miniaudio successfully.");
	}

	Ref<Sound> AudioEngine::CreateSound(const char* filepath, float volume, bool loop)
	{
		if (auto& trackedSounds = s_Instance->m_TrackedSounds; (int)trackedSounds.size() > MAX_SOUNDS)
		{
			trackedSounds.erase(
				std::remove_if(trackedSounds.begin(), trackedSounds.end(),
					[](const WeakRef<Sound>& s) { return s.expired(); }),
				trackedSounds.end());
		}
		auto sound = CreateRef<Sound>(&s_Instance->m_Engine, filepath);
		if (sound->IsValid())
		{
			sound->SetVolume(volume);
			sound->SetLooping(loop);
		}
		s_Instance->m_TrackedSounds.push_back(sound);
		return sound;
	}

	void AudioEngine::SetGlobalVolume(float volume)
	{
		if (s_Instance) ma_engine_set_volume(&s_Instance->m_Engine, volume);
	}

	float AudioEngine::GetGlobalVolume()
	{
		if (s_Instance)
			return ma_engine_get_volume(&s_Instance->m_Engine);
		return 1.0f;
	}

	void AudioEngine::PauseAll()
	{
		if (s_Instance) ma_engine_stop(&s_Instance->m_Engine);
	}

	void AudioEngine::ResumeAll()
	{
		if (s_Instance) ma_engine_start(&s_Instance->m_Engine);
	}

	// === Sound Implementation ===

	Sound::Sound(ma_engine* engine, const char* filepath)
	{
		if (ma_sound_init_from_file(engine, filepath, 0, nullptr, nullptr, &m_Sound) == MA_SUCCESS)
		{
			m_Valid = true;
			m_Name = std::filesystem::path(filepath).stem().string();
			LI_CORE_TRACE("Creating sound: {0}", m_Name);
		}
		else 
			LI_CORE_ERROR("Failed to initialize sound.");
	}

	Sound::~Sound()
	{
		LI_CORE_TRACE("Destroying sound: {0}", m_Name);
		if (AudioEngine::s_Instance && m_Valid)
			ma_sound_uninit(&m_Sound);
	}

    void Sound::Play(float offsetSeconds)  
    {  
       if (!m_Valid) return; 
       ma_sound_start(&m_Sound);  
    }

	void Sound::Stop()
	{
		if (!m_Valid) return;
		ma_sound_stop(&m_Sound);
	}

	void Sound::SetVolume(float volume)
	{
		if (!m_Valid) return;
		ma_sound_set_volume(&m_Sound, volume);
	}

	void Sound::SetLooping(bool looping)
	{
		if (!m_Valid) return;
		ma_sound_set_looping(&m_Sound, looping);
	}

}
