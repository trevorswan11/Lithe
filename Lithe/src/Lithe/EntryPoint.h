#pragma once

#include "Core.h"

#ifdef LI_PLATFORM_WINDOWS

extern Lithe::Application* Lithe::CreateApplication();

int main(int argc, char** argv)
{
	Lithe::Log::Init();
	LI_CORE_WARN("Initialized Log");
	int a = 5;
	LI_INFO("Heyo! Var={0}", a);

	auto app = Lithe::CreateApplication();
	app->Run();
	delete app;
}

#endif