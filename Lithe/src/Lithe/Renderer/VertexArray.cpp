#include "lipch.h"
#include "VertexArray.h"

#include "Lithe/Renderer/Renderer.h"

#include "Platform/Headless/HeadlessVertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Platform/Vulkan/VulkanVertexArray.h"
#include "Platform/DirectX/DirectXVertexArray.h"

namespace Lithe {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::Headless:	return CreateRef<HeadlessVertexArray>();
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLVertexArray>();
			case RendererAPI::API::Vulkan:		return CreateRef<VulkanVertexArray>();
			case RendererAPI::API::DirectX:		return CreateRef<DirectXVertexArray>();
		}

		LI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
