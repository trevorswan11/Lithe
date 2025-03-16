#include "lipch.h"
#include "Input.h"

#ifdef LI_PLATFORM_WINDOWS
    #include "Platform/Windows/WindowsInput.h"
#endif

namespace Lithe {

    Scope<Input> Input::s_Instance = Input::Create();

    Scope<Input> Input::Create()
    {
        #ifdef LI_PLATFORM_WINDOWS
            return CreateScope<WindowsInput>();
        #else
            LI_CORE_ASSERT(false, "Unknown platform!");
            return nullptr;
        #endif
    }
}