#pragma once

#include "Base.h"

#ifdef LI_PLATFORM_WINDOWS

extern Lithe::Application* Lithe::CreateApplication();

int main(int argc, char** argv)
{
	Lithe::Log::Init();
	LI_CORE_INFO("Initialized Log");
	LI_INFO("Initialized Log");

	auto app = Lithe::CreateApplication();
	app->Run();
	delete app;
}

#endif