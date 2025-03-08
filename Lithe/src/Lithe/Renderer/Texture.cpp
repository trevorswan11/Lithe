#include "lipch.h"
#include "Texture.h"

#include "Lithe/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Lithe {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	LI_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLTexture2D>(path);
		case RendererAPI::API::Vulcan:	LI_CORE_ASSERT(false, "RendererAPI::Vulcan is currently not supported!"); return nullptr;
		case RendererAPI::API::DirectX:	LI_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported!"); return nullptr;
		}

		LI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}