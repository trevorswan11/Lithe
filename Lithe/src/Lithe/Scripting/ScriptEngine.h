#pragma once

#include "Lithe/Core/Base.h"

namespace Lithe {

	class ScriptEngine
	{
	public:
		static void Init();
		static void Shutdown();
	private:
		static void InitMono();
		static void ShutdownMono();
	};

}

