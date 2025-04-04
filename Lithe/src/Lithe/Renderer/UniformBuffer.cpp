#include "lipch.h"
#include "UniformBuffer.h"

#include "Lithe/Renderer/Renderer.h"

#include "Platform/Headless/HeadlessUniformBuffer.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"
#include "Platform/Vulkan/VulkanUniformBuffer.h"
#include "Platform/DirectX/DirectXUniformBuffer.h"

namespace Lithe {

	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::Headless:	return CreateRef<HeadlessUniformBuffer>(size, binding);
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLUniformBuffer>(size, binding);
			case RendererAPI::API::Vulkan:		return CreateRef<VulkanUniformBuffer>(size, binding);
			case RendererAPI::API::DirectX:		return CreateRef<DirectXUniformBuffer>(size, binding);
		}

		LI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
