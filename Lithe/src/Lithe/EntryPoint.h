#pragma once

#ifdef LI_PLATFORM_WINDOWS

extern Lithe::Application* Lithe::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Lithe::CreateApplication();
	app->Run();
	delete app;
}

#endif