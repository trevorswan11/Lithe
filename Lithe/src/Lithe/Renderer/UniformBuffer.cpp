#include "lipch.h"
#include "UniformBuffer.h"

#include "Lithe/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLUniformBuffer.h"
#include "Platform/Vulkan/VulkanUniformBuffer.h"

namespace Lithe {

	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	LI_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return CreateRef<OpenGLUniformBuffer>(size, binding);
			case RendererAPI::API::Vulcan:	return CreateRef<VulkanUniformBuffer>(size, binding);
			case RendererAPI::API::DirectX:	LI_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported!"); return nullptr;
		}

		LI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
