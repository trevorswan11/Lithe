#pragma once

#include "Lithe/Core/Base.h"

#include "Lithe/Core/AudioEngine.h"

#ifdef LI_PLATFORM_WINDOWS

extern Lithe::Application* Lithe::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	Lithe::Log::Init();

	LI_PROFILE_BEGIN_SESSION("Startup", "LitheProfile-Startup.json");
	auto app = Lithe::CreateApplication({ argc, argv });
	Lithe::AudioEngine::Init();
	LI_PROFILE_END_SESSION();

	LI_PROFILE_BEGIN_SESSION("Runtime", "LitheProfile-Runtime.json");
	app->Run();
	LI_PROFILE_END_SESSION();
	
	LI_PROFILE_BEGIN_SESSION("Shutdown", "LitheProfile-Shutdown.json");
	Lithe::AudioEngine::Shutdown();
	delete app;
	LI_PROFILE_END_SESSION();
}

#endif
