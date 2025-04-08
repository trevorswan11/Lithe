#include "lipch.h"
#include "AudioEngine.h"

namespace Lithe {

	AudioEngine* AudioEngine::s_Instance = nullptr;

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
			ma_engine_uninit(&s_Instance->m_Engine);
			s_Instance->m_Initialized = false;
		}
		delete s_Instance;
		s_Instance = nullptr;
	}

	void AudioEngine::PlaySound(const char* filepath)
	{
		if (!m_Initialized) return;

		if (ma_engine_play_sound(&m_Engine, filepath, NULL) != MA_SUCCESS)
			LI_CORE_ERROR("Failed to play sound: {0}", filepath);
		else
			LI_CORE_INFO("Playing sound: {0}", filepath);
	}

}
