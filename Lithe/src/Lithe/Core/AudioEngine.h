#pragma once

#include "Lithe/Core/Base.h"

#include <miniaudio.h>

namespace Lithe {

	class Sound
	{
	public:
		Sound(ma_engine* engine, const char* filepath);
		~Sound();

		void Play();
		void Stop();
		void SetVolume(float volume);
		void SetLooping(bool looping);
		bool IsValid() const { return m_Valid; }
	private:
		ma_sound m_Sound{};
		bool m_Valid = false;

		std::string m_Name;
	};

	class AudioEngine 
	{
	public:
		static bool Init();
		static void Shutdown();

		static Ref<Sound> CreateSound(const char* filepath, float volume = 1.0f, bool loop = false);

		static void SetGlobalVolume(float volume);
		static float GetGlobalVolume();
		static void PauseAll();
		static void ResumeAll();
		static void StopAll() { PauseAll(); }
	private:
		inline static AudioEngine& Get() { return *s_Instance; }

		AudioEngine() = default;
		~AudioEngine() = default;

		AudioEngine(const AudioEngine&) = delete;
		AudioEngine& operator=(const AudioEngine&) = delete;

		ma_engine* GetMAEngine() { return &m_Engine; }
	private:
		ma_engine m_Engine;
		bool m_Initialized = false;
		std::vector<WeakRef<Sound>> m_TrackedSounds;
	private:
		static AudioEngine* s_Instance;
		static const int MAX_SOUNDS = 10;

		friend class Sound;
	};

}

