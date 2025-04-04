#include "lipch.h"
#include "Framebuffer.h"

#include "Lithe/Renderer/Renderer.h"

#include "Platform/Headless/HeadlessFramebuffer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"
#include "Platform/Vulkan/VulkanFramebuffer.h"
#include "Platform/DirectX/DirectXFramebuffer.h"

namespace Lithe {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpec& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::Headless:	return CreateRef<HeadlessFramebuffer>(spec);
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLFramebuffer>(spec);
			case RendererAPI::API::Vulkan:		return CreateRef<VulkanFramebuffer>(spec);
			case RendererAPI::API::DirectX:		return CreateRef<DirectXFramebuffer>(spec);
		}

		LI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
