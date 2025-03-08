#include "lipch.h"
#include "VertexArray.h"

#include "Lithe/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Lithe {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	LI_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLVertexArray();
		case RendererAPI::API::Vulcan:	LI_CORE_ASSERT(false, "RendererAPI::Vulcan is currently not supported!"); return nullptr;
		case RendererAPI::API::DirectX:	LI_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported!"); return nullptr;
		}

		LI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}