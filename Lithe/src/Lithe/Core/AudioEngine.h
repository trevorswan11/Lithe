#pragma once
#include <miniaudio.h>

namespace Lithe {

	class AudioEngine {
	public:
		inline static AudioEngine& Get() { return *s_Instance; }

		static bool Init();
		static void Shutdown();

		void PlaySound(const char* filepath);

		ma_engine* GetMAEngine() { return &m_Engine; }
	private:
		AudioEngine() = default;
		~AudioEngine() = default;

		AudioEngine(const AudioEngine&) = delete;
		AudioEngine& operator=(const AudioEngine&) = delete;
	private:
		ma_engine m_Engine;
		bool m_Initialized = false;
	private:
		static AudioEngine* s_Instance;
	};

}

