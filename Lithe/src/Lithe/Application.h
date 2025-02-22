#pragma once

#include "Core.h"

namespace Lithe {
	class LITHE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


