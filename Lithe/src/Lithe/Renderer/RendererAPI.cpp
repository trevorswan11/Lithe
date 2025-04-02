#include "lipch.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Lithe {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

    Scope<RendererAPI> RendererAPI::Create()
    {
        switch (s_API)
        {
            case RendererAPI::API::None:    LI_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
			case RendererAPI::API::Vulcan:	LI_CORE_ASSERT(false, "RendererAPI::Vulcan is currently not supported!"); return nullptr;
			case RendererAPI::API::DirectX:	LI_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported!"); return nullptr;
        }

        LI_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
