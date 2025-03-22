#pragma once

#include "Lithe/Core/Base.h"
#include "Lithe/Core/KeyCodes.h"
#include "Lithe/Core/MouseCodes.h"

namespace Lithe {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePos();
		static float GetMouseX();
		static float GetMouseY();
	};

}