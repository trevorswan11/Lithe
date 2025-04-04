#include "lipch.h"
#include "Buffer.h"

#include "Lithe/Renderer/Renderer.h"

#include "Platform/Headless/HeadlessBuffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/Vulkan/VulkanBuffer.h"
#include "Platform/DirectX/DirectXBuffer.h"

namespace Lithe {

	// --------------------------- VERTEX BUFFER ---------------------------

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::Headless:	return CreateRef<HeadlessVertexBuffer>(size);
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLVertexBuffer>(size);
			case RendererAPI::API::Vulkan:		return CreateRef<VulkanVertexBuffer>(size);
			case RendererAPI::API::DirectX:		return CreateRef<DirectXVertexBuffer>(size);
		}

		LI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::Headless:	return CreateRef<HeadlessVertexBuffer>(vertices, size);
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLVertexBuffer>(vertices, size);
			case RendererAPI::API::Vulkan:		return CreateRef<VulkanVertexBuffer>(vertices, size);
			case RendererAPI::API::DirectX:		return CreateRef<DirectXVertexBuffer>(vertices, size);
		}

		LI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	// --------------------------- INDEX BUFFER ---------------------------

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::Headless:	return CreateRef<HeadlessIndexBuffer>(indices, count);
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLIndexBuffer>(indices, count);
			case RendererAPI::API::Vulkan:		return CreateRef<VulkanIndexBuffer>(indices, count);
			case RendererAPI::API::DirectX:		return CreateRef<DirectXIndexBuffer>(indices, count);
		}

		LI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
