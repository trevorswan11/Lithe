#include "lipch.h"
#include "Window.h"

#ifdef LI_PLATFORM_WINDOWS
 	#include "Platform/Windows/WindowsWindow.h"
 #endif
 
 namespace Lithe
 {
 
 	Scope<Window> Window::Create(const WindowProps& props)
 	{
 	    #ifdef LI_PLATFORM_WINDOWS
 	    	return CreateScope<WindowsWindow>(props);
 	    #else
 	    	LI_CORE_ASSERT(false, "Unknown platform!");
 	    	return nullptr;
 	    #endif
 	}
 
 }