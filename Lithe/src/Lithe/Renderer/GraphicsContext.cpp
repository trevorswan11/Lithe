#include "lipch.h"
#include "Lithe/Renderer/GraphicsContext.h"

#include "Lithe/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Lithe {

    Scope<GraphicsContext> GraphicsContext::Create(void* window)
    {
        switch (Renderer::GetAPI())
        {
			case RendererAPI::API::None:	LI_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
			case RendererAPI::API::Vulcan:	LI_CORE_ASSERT(false, "RendererAPI::Vulcan is currently not supported!"); return nullptr;
			case RendererAPI::API::DirectX:	LI_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported!"); return nullptr;
        }

        LI_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}
