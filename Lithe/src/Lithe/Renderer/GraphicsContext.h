#pragma once

#include "Lithe/Core/Base.h"

namespace Lithe {

	class LITHE_API GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};

}