#include "lipch.h"
#include "VulkanContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Lithe {

	VulkanContext::VulkanContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		LI_CORE_ASSERT(windowHandle, "widnowHandle is null!");
	}

	void VulkanContext::Init()
	{
		LI_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LI_CORE_ASSERT(status, "Failed to initialize Glad!");

		// Show the graphics driver that is being used
		LI_CORE_INFO("Vulkan Info:");
		LI_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		LI_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		LI_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

 		int versionMajor;
 		int versionMinor;
 		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
 		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
 
 		LI_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Lithe requires at least Vulkan version 4.5!");
	}

	void VulkanContext::SwapBuffers()
	{
		LI_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}
