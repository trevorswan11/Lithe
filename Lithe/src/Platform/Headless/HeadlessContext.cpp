#include "lipch.h"
#include "HeadlessContext.h"

#include <GLFW/glfw3.h>

namespace Lithe {

	HeadlessContext::HeadlessContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		LI_CORE_ASSERT(false);
	}

	void HeadlessContext::Init()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void HeadlessContext::SwapBuffers()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

}
