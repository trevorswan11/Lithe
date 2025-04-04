#pragma once

#include "Lithe/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Lithe {

	class DirectXContext : public GraphicsContext
	{
	public:
		DirectXContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}
