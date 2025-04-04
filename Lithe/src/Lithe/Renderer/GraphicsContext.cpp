#include "lipch.h"
#include "Lithe/Renderer/GraphicsContext.h"

#include "Lithe/Renderer/Renderer.h"

#include "Platform/Headless/HeadlessContext.h"
#include "Platform/OpenGL/OpenGLContext.h"
#include "Platform/Vulkan/VulkanContext.h"
#include "Platform/DirectX/DirectXContext.h"

namespace Lithe {

    Scope<GraphicsContext> GraphicsContext::Create(void* window)
    {
        switch (Renderer::GetAPI())
        {
			case RendererAPI::API::Headless:	return CreateScope<HeadlessContext>(static_cast<GLFWwindow*>(window));
			case RendererAPI::API::OpenGL:		return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
			case RendererAPI::API::Vulkan:		return CreateScope<VulkanContext>(static_cast<GLFWwindow*>(window));
			case RendererAPI::API::DirectX:		return CreateScope<DirectXContext>(static_cast<GLFWwindow*>(window));
        }

        LI_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}
