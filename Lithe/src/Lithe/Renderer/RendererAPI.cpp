#include "lipch.h"
#include "RendererAPI.h"

#include "Platform/Headless/HeadlessRendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "Platform/Vulkan/VulkanRendererAPI.h"
#include "Platform/DirectX/DirectXRendererAPI.h"

namespace Lithe {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

    Scope<RendererAPI> RendererAPI::Create()
    {
        switch (s_API)
        {
            case RendererAPI::API::Headless:    return CreateScope<HeadlessRendererAPI>();
            case RendererAPI::API::OpenGL:		return CreateScope<OpenGLRendererAPI>();
			case RendererAPI::API::Vulkan:		return CreateScope<VulkanRendererAPI>();
			case RendererAPI::API::DirectX:		return CreateScope<DirectXRendererAPI>();
        }

        LI_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
