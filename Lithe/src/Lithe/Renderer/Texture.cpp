#include "lipch.h"
#include "Texture.h"

#include "Lithe/Renderer/Renderer.h"

#include "Platform/Headless/HeadlessTexture.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "Platform/Vulkan/VulkanTexture.h"
#include "Platform/DirectX/DirectXTexture.h"

namespace Lithe {
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::Headless:	return CreateRef<HeadlessTexture2D>(width, height);
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLTexture2D>(width, height);
			case RendererAPI::API::Vulkan:		return CreateRef<VulkanTexture2D>(width, height);
			case RendererAPI::API::DirectX:		return CreateRef<DirectXTexture2D>(width, height);
		}

		LI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::Headless:	return CreateRef<HeadlessTexture2D>(path);
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLTexture2D>(path);
			case RendererAPI::API::Vulkan:		return CreateRef<VulkanTexture2D>(path);
			case RendererAPI::API::DirectX:		return CreateRef<DirectXTexture2D>(path);
		}

		LI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
