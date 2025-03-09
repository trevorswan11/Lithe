#include "lipch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Lithe {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)	
	{
		LI_CORE_ASSERT(windowHandle, "widnowHandle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LI_CORE_ASSERT(status, "Failed to initialize Glad!");

		// Show the graphics driver that is being used
		LI_CORE_INFO("OpenGl Info:");
		LI_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		LI_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		LI_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

		#ifdef LI_ENABLE_ASSERTS
 			int versionMajor;
 			int versionMinor;
 			glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
 			glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
 
 			LI_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Lithe requires at least OpenGL version 4.5!");
 		#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}

}