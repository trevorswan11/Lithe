#pragma once

#include "Lithe/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Lithe {

	class VulkanContext : public GraphicsContext
	{
	public:
		VulkanContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}
