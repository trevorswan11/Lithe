#pragma once

#include "Lithe/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Lithe {

	class HeadlessContext : public GraphicsContext
	{
	public:
		HeadlessContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}
