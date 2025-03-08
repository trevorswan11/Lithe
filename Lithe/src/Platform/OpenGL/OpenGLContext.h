#pragma once

#include "Lithe/Core/Base.h"
#include "Lithe/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Lithe {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_windowHandle;
	};

}